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

#ifndef EE_CUBEPROPERTYVISUALIZER_H
#define EE_CUBEPROPERTYVISUALIZER_H

#include <egmVisualizers/IPropertyVisualizer.h>
#include <NiMaterialProperty.h>

namespace egmVisualizers
{

/**
    A visualizer for a simple wire cube.

    By default, the Position, Rotation, and Dimensions properties on the entity are used to
    create the visualizer mesh.  The properties used to drive the visualizer
    can be overridden by the extra data passed to the constructor.
*/
class EE_EGMVISUALIZERS_ENTRY CubePropertyVisualizer : public IPropertyVisualizer
{
public:
    /// @name Construction and Destruction
    //@{
    /**
        Constructor.  The extra data can be used to override which properties drive the visualizer.
        The string value of the extra data is used to find the property.  If that entry does not
        exist or it is specified as "Default", then the default property on the entity will be used.

        "Anchor" entry overrides default position property.
        "Orientation" entry overrides default rotation property.
        "Dimensions" entry overrides default dimensions property.
        "Color" entry specifies the color of the visualizer (no default).
        "Offset" entry specifies the position offset of the visualizer (no default).
    */
    CubePropertyVisualizer(egf::ExtraDataPtr spExtraData);
    //@}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void AddGeometry(ecr::SceneGraphService* pSceneGraphService, egf::Entity* pEntity);
    virtual void UpdateGeometry(ecr::SceneGraphService* pSceneGraphService, egf::Entity* pEntity);
    virtual void RemoveGeometry(ecr::SceneGraphService* pSceneGraphService);
    virtual PropertyChangeAction UpdateFromEntity(egf::Entity* pEntity);
    virtual void SetVisibility(bool isVisible);

protected:
    egf::ExtraDataPtr m_spExtraData;
    NiMeshPtr m_spMesh;
    NiMeshPtr m_spSolidMesh;
    NiMaterialPropertyPtr m_spMaterialProperty;
    NiMaterialPropertyPtr m_spSolidMaterialProperty;
    ecr::SceneGraphService::SceneGraphHandle m_cubeHandle;
    ecr::SceneGraphService::SceneGraphHandle m_solidCubeHandle;

    NiPoint3 m_dimensions;
    NiPoint3 m_anchor;
    NiPoint3 m_orientation;
    efd::Color m_color;
    efd::Float32 m_scale;
};

} // namespace

#endif
