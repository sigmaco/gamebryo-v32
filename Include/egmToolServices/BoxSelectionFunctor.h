// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef EE_BOXSELECTIONFUNCTOR_H
#define EE_BOXSELECTIONFUNCTOR_H

#include <ecr\SceneGraphService.h>

#include <NiMeshCullingProcess.h>
#include <NiSkinningMeshModifier.h>
#include <NiMeshAlgorithms.h>

#include "MeshPrimitiveInFrustumFunctor.h"

namespace egmToolServices
{

class BoxSelectionFunctor : public ecr::SceneGraphService::EntitySceneGraphFunctor
{
public:
    BoxSelectionFunctor(NiCameraPtr spCamera, NiMeshCullingProcessPtr spCuller)
    {
        m_spCamera = spCamera;
        m_spCuller = spCuller;
    }

    virtual ~BoxSelectionFunctor() { }

    void ClearSelections()
    {
        m_selections.clear();
    }

    const efd::vector<const egf::Entity*>& GetSelections() const
    {
        return m_selections;
    }

    virtual efd::Bool operator()(
        const egf::Entity* pEntity,
        const efd::vector<NiObjectPtr>& objects)
    {
        m_spCuller->GetVisibleSet()->RemoveAll();

        efd::vector<NiObjectPtr>::const_iterator objIter;
        for (objIter = objects.begin(); objIter != objects.end(); objIter++)
        {
            NiAVObjectPtr spScene = NiDynamicCast(NiAVObject, *objIter);
            if (!spScene)
                continue;

            m_spCuller->Cull(m_spCamera, spScene, 0);
        }

        // If the entity isn't culled, check it at a higher resolution
        if (m_spCuller->GetVisibleSet()->GetCount())
        {
            for (objIter = objects.begin(); objIter != objects.end(); objIter++)
            {
                NiAVObjectPtr spScene = NiDynamicCast(NiAVObject, *objIter);
                if (!spScene)
                    continue;

                if (SceneGraphInFrustum(spScene, m_spCamera))
                {
                    m_selections.push_back(pEntity);
                    break;
                }
            }
        }


        return false;
    }

    efd::Bool SceneGraphInFrustum(NiAVObject* pAVObj, NiCamera* pCamera)
    {
        if (pAVObj->GetAppCulled())
            return false;

        // If this is a node, move down its hierarchy
        NiNodePtr pNode = NiDynamicCast(NiNode, pAVObj);
        if (pNode)
        {
            // We can't assume that pNode->GetAt(iter) will yield a non-NULL child,
            // but we still must make sure we reach all the non-null children.
            unsigned int numChildren = pNode->GetChildCount();
            unsigned int childCount = 0;
            unsigned int iter = 0;
            while (childCount < numChildren)
            {
                NiAVObject* child = pNode->GetAt(iter);
                if (child != NULL)
                {
                    childCount++;
                    if (SceneGraphInFrustum(child, pCamera))
                    {
                        return true;
                    }
                }
                iter++;
            }
        }

        // If this is a mesh, grab the bounds data to test for collision
        NiMeshPtr pMesh = NiDynamicCast(NiMesh, pAVObj);
        if (pMesh)
        {
            NiSkinningMeshModifier* pSkinMod = NiGetModifier(NiSkinningMeshModifier, pMesh);

            if (pSkinMod)
            {
                return IsSkinnedMeshInFrustum(pSkinMod, pCamera);
            }
            else
            {
                return IsUnskinnedMeshInFrustum(pMesh, pCamera);
            }
        }
        else if (NiIsKindOf(NiRenderObject, pAVObj))
        {
            return true;
        }

        return false;
    }

    efd::Bool IsUnskinnedMeshInFrustum(
        NiMesh* pMesh,
        NiCamera* pCamera)
    {
        // For non-skinned meshes, check the triangles of the mesh to see if they're
        // in the frustum
        NiDataStreamElementLock vertexLock(pMesh,
            NiCommonSemantics::POSITION(), 0, NiDataStreamElement::F_FLOAT32_3,
            NiDataStream::LOCK_READ);

        // If the lock fails for some reason, defer to the bounding sphere check instead
        // of completely failing
        if (!vertexLock.IsLocked())
            return true;

        NiFrustumPlanes planes(*pCamera);

        // Perform check to see if the first point of the mesh is in the frustum.
        // If the mesh is entirely inside the frustum, this will succeed.
        // This is an early acceptance check and improves performance.
        if (vertexLock.count(0) > 0)
        {
            NiTStridedRandomAccessIterator<NiPoint3> vertexItr = vertexLock.begin<NiPoint3>(0);
            NiPoint3 point = pMesh->GetWorldTransform() * vertexItr[0];
            bool vertInFrustum = true;
            for (NiUInt32 plane = 0; plane < planes.MAX_PLANES; plane++)
            {
                if (planes.GetPlane(plane).WhichSide(point) ==
                    NiPlane::NEGATIVE_SIDE)
                {
                    vertInFrustum = false;
                    break;
                }
            }

            if (vertInFrustum)
                return true;
        }

        // Transform all the vertices; don't do this until after the previous check,
        // since it's not necessary to transform them if the first point is in the frustum.
        efd::vector<efd::vector<NiPoint3> > transformedVertices;
        TransformVertices(pMesh, vertexLock, transformedVertices);

        // Perform check to see if any of the mesh's points are inside the
        // frustum; this is an early acceptance case and improves performance
        for (NiUInt32 submesh = 0; submesh < transformedVertices.size(); submesh++)
        {
            for (NiUInt32 vert = 0; vert < transformedVertices[submesh].size(); vert++)
            {
                bool vertInFrustum = true;
                for (NiUInt32 plane = 0; plane < planes.MAX_PLANES; plane++)
                {
                    if (planes.GetPlane(plane).WhichSide(transformedVertices[submesh][vert]) ==
                        NiPlane::NEGATIVE_SIDE)
                    {
                        vertInFrustum = false;
                        break;
                    }
                }
                if (vertInFrustum)
                    return true;
            }
        }

        // If the early-acceptance fails, there still may be a collision, but we
        // must perform a more robust collision check
        MeshPrimitiveInFrustumFunctor functorPrimitive(pCamera, pMesh, &transformedVertices);
        NiMeshAlgorithms::ForEachPrimitiveAllSubmeshes(
            pMesh, functorPrimitive, NiDataStream::LOCK_READ, true);
        return functorPrimitive.IsMeshInFrustum();
    }

    efd::Bool IsSkinnedMeshInFrustum(
        NiSkinningMeshModifier *pSkinMod,
        NiCamera* pCamera)
    {
        // For skinned meshes, determine if bone bounding spheres are in the frustum
        NiBound* pBoneWorldBounds = pSkinMod->GetBoneBounds();
        NiUInt32 boneCount = pSkinMod->GetBoneCount();
        for (NiUInt32 ui = 0; ui < boneCount; ui++)
        {
            bool boneInFrustum = true;
            NiBound boneBound;
            boneBound.Update(pBoneWorldBounds[ui], pSkinMod->GetWorldBoneMatrix(ui));
            NiFrustumPlanes planes(*pCamera);
            for (unsigned int plane = 0; plane < planes.MAX_PLANES; plane++)
            {
                if (boneBound.WhichSide(planes.GetPlane(plane)) == NiPlane::NEGATIVE_SIDE)
                    boneInFrustum = false;
            }

            if (boneInFrustum)
            {
                return true;
            }
        }

        return false;
    }

    // Transforms all the vertices, since the vertices may likely be accessed multiple times and
    // there's no need to transform them more than once
    void TransformVertices(
        const NiMesh* pMesh,
        const NiDataStreamElementLock& vertexLock,
        efd::vector<efd::vector<NiPoint3> >& transformedVertices)
    {
        const NiTransform& transform = pMesh->GetWorldTransform();

        NiUInt32 numSubmeshes = vertexLock.GetSubmeshCount();

        transformedVertices = efd::vector<efd::vector<NiPoint3> >(numSubmeshes);
        for (NiUInt32 submesh = 0; submesh < numSubmeshes; submesh++)
        {
            NiUInt32 numVertices = vertexLock.count(submesh);
            transformedVertices[submesh] = efd::vector<NiPoint3>(numVertices);
            NiTStridedRandomAccessIterator<NiPoint3> vertexItr =
                vertexLock.begin<NiPoint3>(submesh);

            for (NiUInt32 vertex = 0; vertex < numVertices; vertex++)
            {
                transformedVertices[submesh][vertex] = transform * vertexItr[vertex];
            }
        }
    }
protected:
    efd::vector<const egf::Entity*> m_selections;
    NiCameraPtr m_spCamera;
    NiMeshCullingProcessPtr m_spCuller;
};

}; // egmToolServices namespace

#endif // EE_BOXSELECTIONFUNCTOR_H
