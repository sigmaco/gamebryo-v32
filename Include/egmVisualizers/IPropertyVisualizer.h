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

#ifndef EE_IPROPERTYVISUALIZER_H
#define EE_IPROPERTYVISUALIZER_H

#include "egmVisualizersLibType.h"

#include <efd/RefCount.h>
#include <egf/Entity.h>
#include <ecr/SceneGraphService.h>
#include <NiMesh.h>

namespace egmVisualizers
{

/// The response needed from a property change.
enum PropertyChangeAction
{
    /// No action needs to be taken.
    PropertyChangeAction_None,

    /// Transforms (position, rotation, uniform scale) need to be updated.
    PropertyChangeAction_UpdateTransforms,

    /// Visualizer geometry needs to be updated.
    PropertyChangeAction_UpdateGeometry,

    /// Invalid action.
    PropertyChangeAction_InvalidValue
};

/**
    An abstract interface for a given type of visualization geometry.
*/
class EE_EGMVISUALIZERS_ENTRY IPropertyVisualizer : public efd::RefCount
{
public:
    /// Add a visualizer for the entity, registering it with the given scene graph service.
    virtual void AddGeometry(
        ecr::SceneGraphService* pSceneGraphService,
        egf::Entity* pEntity) = 0;

    /// Tick the given visualizer, updating the mesh based on entity property changes.
    virtual void UpdateGeometry(
        ecr::SceneGraphService* pSceneGraphService,
        egf::Entity* pEntity) = 0;

    /// Remove the visualizer for the given entity.
    virtual void RemoveGeometry(ecr::SceneGraphService* pSceneGraphService) = 0;

    /// Check which entity properties exist that are driving this visualizer,
    /// cache those values, and return the action required to update the
    /// visualization mesh based on which properties have changed.
    virtual PropertyChangeAction UpdateFromEntity(egf::Entity* pEntity) = 0;

    /// Hide/unhide geometry associated with the visualizer.
    virtual void SetVisibility(bool isVisible) = 0;
};

typedef efd::SmartPointer<IPropertyVisualizer> IPropertyVisualizerPtr;

} // namespace

#endif
