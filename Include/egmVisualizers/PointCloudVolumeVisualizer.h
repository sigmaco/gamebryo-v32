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

#ifndef EE_POINTCLOUDVOLUMEVISUALIZER_H
#define EE_POINTCLOUDVOLUMEVISUALIZER_H

#include <egmVisualizers/IPropertyVisualizer.h>
#include <egmVisualizers/CubePropertyVisualizer.h>
#include <NiMaterialProperty.h>

namespace egmVisualizers
{

/**
    A visualizer for a PhysX box.  This is only different from the Cube visualizers in that
    the origin of the visualizer is different.

    By default, the Position, Rotation, and Dimensions properties on the entity are used to
    create the visualizer mesh.  The properties used to drive the visualizer
    can be overridden by the extra data passed to the constructor.
*/
class EE_EGMVISUALIZERS_ENTRY PointCloudVolumeVisualizer : public CubePropertyVisualizer
{
public:
    /// @name Construction and Destruction
    //@{
    PointCloudVolumeVisualizer(egf::ExtraDataPtr spExtraData);
    //@}

    virtual void AddGeometry(ecr::SceneGraphService* pSceneGraphService, egf::Entity* pEntity);
    virtual void UpdateGeometry(ecr::SceneGraphService* pSceneGraphService, egf::Entity* pEntity);
    virtual void RemoveGeometry(ecr::SceneGraphService* pSceneGraphService);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual PropertyChangeAction UpdateFromEntity(egf::Entity* pEntity);

    virtual void SetVisibility(bool isVisible);
protected:
    void CreateDivisionMesh(ecr::SceneGraphService* pSceneGraphService);

    NiMeshPtr m_spDivisionMesh;
    NiMaterialPropertyPtr m_spDivisionsMaterialProperty;

    ecr::SceneGraphService::SceneGraphHandle m_divisionHandle;
    efd::UInt32 m_iXDivisions, m_iYDivisions, m_iZDivisions;
};

} // namespace

#endif // EE_POINTCLOUDVOLUMEVISUALIZER_H
