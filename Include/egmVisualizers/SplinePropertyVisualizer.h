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

#ifndef SE_SPLINEPROPERTYVISUALIZER_H
#define SE_SPLINEPROPERTYVISUALIZER_H

#include <egmVisualizers/IPropertyVisualizer.h>
#include <NiMaterialProperty.h>
#include "VisualizerConnectionTracker.h"
#include "VisualizerVisibilityTracker.h"

namespace egmVisualizers
{

/// Stores information necessary for the connection visualizer
struct SplineData
{
    efd::Point3 m_point;
    NiMeshPtr m_spMesh;
    NiMeshPtr m_spLineMesh;
    ecr::SceneGraphService::SceneGraphHandle m_meshHandle;
    ecr::SceneGraphService::SceneGraphHandle m_connectionLineHandle;
};

/**
    A visualizer for a connection between two entities.

    By default, this visualizer will use a property named "Connection" to determine the
    connected entity and the Position property to determine the positions of each entity.
    The Connection can be changed by way of the extra data passed to the constructor.
*/
class EE_EGMVISUALIZERS_ENTRY SplinePropertyVisualizer : public IPropertyVisualizer
{
public:
    /// @name Construction and Destruction
    //@{
    /**
        Constructor.  The extra data can be used to override which properties drive the visualizer.
        The string value of the extra data is used to find the property.  If that entry does not
        exist or it is specified as "Default", then the default property on the entity will be
        used.

        "Connection" entry overrides the EntityRef used to establish a connection between two
        entities.
        "Color" color of the line connecting the two entities.
        "Offset" a Point3 offsetting the end points of the line connecting the two entities.
    */
    SplinePropertyVisualizer(
        egf::ExtraDataPtr spExtraData,
        egf::EntityManager* pEntityManager,
        VisualizerConnectionTracker* pConnectionTracker,
        VisualizerVisibilityTracker* pVisibilityTracker);
    //@}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void AddGeometry(ecr::SceneGraphService*, egf::Entity*);
    virtual void UpdateGeometry(ecr::SceneGraphService*, egf::Entity*);
    virtual void RemoveGeometry(ecr::SceneGraphService*);
    virtual PropertyChangeAction UpdateFromEntity(egf::Entity* pEntity);
    virtual void SetVisibility(bool isVisible);
private:
    egf::ExtraDataPtr m_spExtraData;
    NiMaterialPropertyPtr m_spLineMaterialProperty;
    NiMaterialPropertyPtr m_spPointMaterialProperty;

    egf::EntityID m_owner;

    typedef efd::map<efd::utf8string, SplineData> ConnectionMap;
    ConnectionMap m_connections;

    efd::map<efd::utf8string, efd::Point3> m_oldConnections;

    efd::Color m_lineColor;
    efd::Color m_pointColor;
    efd::Point3 m_position;

    egf::EntityManager* m_pEntityManager;
    ecr::SceneGraphService* m_pSceneGraphService;

    VisualizerConnectionTracker* m_pConnectionTracker;
    VisualizerVisibilityTracker* m_pVisibilityTracker;

    PropertyChangeAction UpdateConnectionList(egf::Entity* pOwner, egf::Entity* pEntity);
};

}

#endif // SE_SPLINEPROPERTYVISUALIZER_H
