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
#ifndef EE_MeshPrimitiveInFrustumFunctor_H
#define EE_MeshPrimitiveInFrustumFunctor_H

namespace egmToolServices
{

/*  Functor which tests if any primitive in a non-skinned mesh intersects a frustum.
    This is a full-on intersection check, and as such can be slow.  The Separating Axis Test is
    used, which is not the fastest mechanism but is generic with every primitive type.
*/
class MeshPrimitiveInFrustumFunctor
{
public:
    MeshPrimitiveInFrustumFunctor(
        NiCamera* pCamera,
        NiMesh* pMesh,
        efd::vector<efd::vector<NiPoint3> >* transformedVertices) :
        m_pMesh(pMesh), m_pCamera(pCamera), m_meshInFrustum(false),
        m_transformedVertices(transformedVertices)
    {
        CalculateFrustumPoints(pCamera->GetViewFrustum(), pCamera->GetWorldTransform(),
            m_frustumPoints);

        m_frustumPlanes = NiFrustumPlanes(*pCamera);

        // Pre-calculate all the frustum edges so we don't have to do it per-primitive
        NiPoint3 frustEdges[] = {
            m_frustumPoints[0] - m_frustumPoints[1],
            m_frustumPoints[0] - m_frustumPoints[3],
            m_frustumPoints[0] - m_frustumPoints[4],
            m_frustumPoints[1] - m_frustumPoints[5],
            m_frustumPoints[2] - m_frustumPoints[6],
            m_frustumPoints[3] - m_frustumPoints[7] };

        NiMemcpy(m_frustumEdges, 6 * sizeof(NiPoint3), frustEdges, 6 * sizeof(NiPoint3));
    }

    efd::Bool operator() (const NiUInt32* pIndices, NiUInt32 uiIndexCount, NiUInt32 uiPrimitiveIdx,
        NiUInt16 uiSubMesh)
    {
        EE_UNUSED_ARG(uiPrimitiveIdx);
        EE_UNUSED_ARG(uiIndexCount);

        if (PrimitiveInFrustum(pIndices, uiIndexCount, uiSubMesh))
        {
            m_meshInFrustum = true;
            return false;
        }

        return true;
    }

    efd::Bool IsMeshInFrustum()
    {
        return m_meshInFrustum;
    }
protected:
    NiMesh* m_pMesh;
    NiCamera* m_pCamera;
    NiPoint3 m_frustumPoints[8];
    efd::Bool m_meshInFrustum;
    NiFrustumPlanes m_frustumPlanes;
    NiPoint3 m_frustumEdges[6];

    efd::vector<efd::vector<NiPoint3> >* m_transformedVertices;

    // Uses the SAT to determine if a line, triangle, or quad is in the view frustum
    // The maximum uiIndexCount can be is 4
    // This does not handle strips - just single primitives
    efd::Bool PrimitiveInFrustum(
        const NiUInt32* pIndices,
        NiUInt32 uiIndexCount,
        NiUInt16 uiSubMesh)
    {
        // Array large enough to at least hold all the points for a quad
        NiPoint3 verts[4];

        for (efd::UInt32 vert = 0; vert < uiIndexCount; vert++)
            verts[vert] = (*m_transformedVertices)[uiSubMesh][ pIndices[vert] ];

        // 5 frustum normals + 1 triangle normal + 24 quad/frustum edge cross products
        // This will be big enough to hold the axes for triangles/lines as well
        const efd::UInt32 maxAxes = 30;
        NiPoint3 axes[maxAxes];
        efd::UInt32 numAxes = 0;

        for (efd::UInt32 i = 0; i < NiFrustumPlanes::MAX_PLANES; i++)
        {
            // No need to add the far plane, since the near plane will cover the same axis
            if (i != NiFrustumPlanes::FAR_PLANE)
            {
                axes[numAxes++] = m_frustumPlanes.GetPlane(i).GetNormal();
            }
        }

        // Add the primitive normal as a test axis
        if (uiIndexCount > 2)
            axes[numAxes++] = (verts[1] - verts[0]).Cross(verts[2] - verts[0]);

        for (efd::UInt32 edgeIdx = 0; edgeIdx < uiIndexCount; edgeIdx++)
        {
            NiPoint3 edge = verts[(edgeIdx+1)%uiIndexCount] - verts[edgeIdx];
            for (efd::UInt32 frustEdge = 0; frustEdge < 6; frustEdge++)
            {
                axes[numAxes++] = edge.Cross(m_frustumEdges[frustEdge]);
            }
        }

        bool ret = SeparatingAxisTest(axes, numAxes, verts, uiIndexCount, m_frustumPoints, 8);

        return ret;
    }

    // Performs the separating axis test on two convex objects given the axes to test against.
    bool SeparatingAxisTest(
        NiPoint3* pAxes,
        NiUInt32 uiNumAxes,
        NiPoint3* pVertsObj1,
        NiUInt32 uiNumVertsObj1,
        NiPoint3* pVertsObj2,
        NiUInt32 uiNumVertsObj2)
    {
        for (efd::UInt32 axis = 0; axis < uiNumAxes; axis++)
        {
            const efd::Float32 tolerance = 0.0005f;
            if (pAxes[axis].SqrLength() <= tolerance)
                return false;

            efd::Float32 min1 = 0.0f, min2 = 0.0f, max1 = 0.0f, max2 = 0.0f;

            for (efd::UInt32 vert = 0; vert < uiNumVertsObj1; vert++)
            {
                efd::Float32 pos = pAxes[axis].Dot(pVertsObj1[vert]);
                if (vert == 0)
                {
                    min1 = pos;
                    max1 = pos;
                }
                else
                {
                    min1 = NiMin(min1, pos);
                    max1 = NiMax(max1, pos);
                }
            }

            for (efd::UInt32 vert = 0; vert < uiNumVertsObj2; vert++)
            {
                efd::Float32 pos = pAxes[axis].Dot(pVertsObj2[vert]);
                if (vert == 0)
                {
                    min2 = pos;
                    max2 = pos;
                }
                else
                {
                    min2 = NiMin(min2, pos);
                    max2 = NiMax(max2, pos);
                }
            }

            if (min1 > max2 || max1 < min2)
                return false;
        }

        return true;
    }

    void CalculateFrustumPoints(const NiFrustum &kSliceFrustum,
        const NiTransform &kTransform,
        NiPoint3 *akPoints)
    {
        NiPoint3 kCameraDir;
        kTransform.m_Rotate.GetCol(0, kCameraDir);

        // Note that scale is not applied anywhere in this code since the renderers do
        // not consider scale when constructing view matrices.
        if (kSliceFrustum.m_bOrtho)
        {
            // World-space viewport translation vectors.
            NiPoint3 kViewTL = kTransform.m_Rotate * NiPoint3(0.0f,
                kSliceFrustum.m_fTop, kSliceFrustum.m_fLeft);

            NiPoint3 kViewTR = kTransform.m_Rotate * NiPoint3(0.0f,
                kSliceFrustum.m_fTop, kSliceFrustum.m_fRight);

            NiPoint3 kViewBL = kTransform.m_Rotate * NiPoint3(0.0f,
                kSliceFrustum.m_fBottom, kSliceFrustum.m_fLeft);

            NiPoint3 kViewBR = kTransform.m_Rotate * NiPoint3(0.0f,
                kSliceFrustum.m_fBottom, kSliceFrustum.m_fRight);

            akPoints[0] = kTransform.m_Translate + kViewBL +
                kCameraDir * kSliceFrustum.m_fNear;
            akPoints[1] = kTransform.m_Translate + kViewTL +
                kCameraDir * kSliceFrustum.m_fNear;
            akPoints[2] = kTransform.m_Translate + kViewTR +
                kCameraDir * kSliceFrustum.m_fNear;
            akPoints[3] = kTransform.m_Translate + kViewBR +
                kCameraDir * kSliceFrustum.m_fNear;

            akPoints[4] = kTransform.m_Translate + kViewBL +
                kCameraDir * kSliceFrustum.m_fFar;
            akPoints[5] = kTransform.m_Translate + kViewTL +
                kCameraDir * kSliceFrustum.m_fFar;
            akPoints[6] = kTransform.m_Translate + kViewTR +
                kCameraDir * kSliceFrustum.m_fFar;
            akPoints[7] = kTransform.m_Translate + kViewBR +
                kCameraDir * kSliceFrustum.m_fFar;
        }
        else
        {
            // World-space viewport direction vectors.
            NiPoint3 kViewTL = kTransform.m_Rotate * NiPoint3(1.0f,
                kSliceFrustum.m_fTop, kSliceFrustum.m_fLeft);

            NiPoint3 kViewTR = kTransform.m_Rotate * NiPoint3(1.0f,
                kSliceFrustum.m_fTop, kSliceFrustum.m_fRight);

            NiPoint3 kViewBL = kTransform.m_Rotate * NiPoint3(1.0f,
                kSliceFrustum.m_fBottom, kSliceFrustum.m_fLeft);

            NiPoint3 kViewBR = kTransform.m_Rotate * NiPoint3(1.0f,
                kSliceFrustum.m_fBottom, kSliceFrustum.m_fRight);

            // Viewport direction vectors are in camera space. Multiplying by the distance to
            // the view planes has the effect of projecting them into a frustum in view space.
            akPoints[0] = kTransform.m_Translate + kViewBL * kSliceFrustum.m_fNear;
            akPoints[1] = kTransform.m_Translate + kViewTL * kSliceFrustum.m_fNear;
            akPoints[2] = kTransform.m_Translate + kViewTR * kSliceFrustum.m_fNear;
            akPoints[3] = kTransform.m_Translate + kViewBR * kSliceFrustum.m_fNear;

            akPoints[4] = kTransform.m_Translate + kViewBL * kSliceFrustum.m_fFar;
            akPoints[5] = kTransform.m_Translate + kViewTL * kSliceFrustum.m_fFar;
            akPoints[6] = kTransform.m_Translate + kViewTR * kSliceFrustum.m_fFar;
            akPoints[7] = kTransform.m_Translate + kViewBR * kSliceFrustum.m_fFar;
        }
    }
};

}; // egmToolServices namespace

#endif // EE_MeshPrimitiveInFrustumFunctor_H
