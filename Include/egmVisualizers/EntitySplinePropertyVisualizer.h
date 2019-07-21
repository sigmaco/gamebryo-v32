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

#ifndef SE_ENTITYSPLINEPROPERTYVISUALIZER_H
#define SE_ENTITYSPLINEPROPERTYVISUALIZER_H

#include <egmVisualizers/IPropertyVisualizer.h>
#include <NiMaterialProperty.h>
#include "VisualizerConnectionTracker.h"
#include "VisualizerVisibilityTracker.h"

namespace egmVisualizers
{

/// Stores information necessary for the connection visualizer
struct EntitySplineData
{
    egf::EntityID m_entityID;
    efd::Point3 m_point;
    NiMeshPtr m_spMesh;
    ecr::SceneGraphService::SceneGraphHandle m_connectionHandle;
};

/**
    A visualizer for a connection between two entities.

    By default, this visualizer will use a property named "Connection" to determine the
    connected entity and the Position property to determine the positions of each entity.
    The Connection can be changed by way of the extra data passed to the constructor.
*/
class EE_EGMVISUALIZERS_ENTRY EntitySplinePropertyVisualizer : public IPropertyVisualizer
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
    EntitySplinePropertyVisualizer(
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
    NiMaterialPropertyPtr m_spMaterialProperty;

    egf::EntityID m_owner;

    typedef efd::map<efd::utf8string, EntitySplineData> ConnectionMap;
    ConnectionMap m_connections;

    efd::map<efd::utf8string, egf::EntityID> m_oldConnections;

    efd::Color m_color;

    egf::EntityManager* m_pEntityManager;
    ecr::SceneGraphService* m_pSceneGraphService;

    VisualizerConnectionTracker* m_pConnectionTracker;
    VisualizerVisibilityTracker* m_pVisibilityTracker;

    PropertyChangeAction UpdateConnectionList(egf::Entity* pOwner, egf::Entity* pEntity);
};

}

#endif // SE_ENTITYSPLINEPROPERTYVISUALIZER_H
