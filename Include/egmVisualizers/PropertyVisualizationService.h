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
#ifndef EE_PROPERTYVISUALIZATIONSERVICE_H
#define EE_PROPERTYVISUALIZATIONSERVICE_H

#include <egf/Entity.h>
#include <egf/EntityID.h>
#include <efd/MessageHandlerBase.h>
#include <efd/ISystemService.h>
#include <efd/StreamMessage.h>
#include <egf/EntityChangeMessage.h>
#include <egf/FlatModelManager.h>
#include <ecr/ecrSystemServiceIDs.h>

#include "egmVisualizersLibType.h"
#include <ecr/SceneGraphService.h>
#include "PropertyVisualizerFactory.h"
#include "VisualizerVisibilityTracker.h"
#include "VisualizerConnectionTracker.h"

namespace egmVisualizers
{

/**
    A service that manages visualizers for entities that specify them in their mix-in extra data.
*/
class EE_EGMVISUALIZERS_ENTRY PropertyVisualizationService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        PropertyVisualizationService,
        efd::kCLASSID_PropertyVisualizationService,
        efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    PropertyVisualizationService();

    /// Virtual destructor.
    virtual ~PropertyVisualizationService();
    //@}

    /// Turn on rendering of property visualizers.
    ///
    /// This method may be called during PreInit or Init.
    void EnableVisualization();

    /**
        Turn off rendering of property visualizers.

        This method may be called during PreInit or Init.

        @param cleanup If true, delete visualizers.
    */
    void DisableVisualization(efd::Bool cleanup);

    /// Recreates the visualizers; typically used when an entity model changes but the entity is not
    /// removed and readded to the scene.
    void ResetVisualization();

    /**
        This message handler is called when a new entity is discovered. The
        entity is inspected for any property visualization properties.

        @param pMessage The entity message.
        @param targetChannel The channel that the message arrived on.
    */
    void HandleEntityDiscoverMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been removed from the EntityManager.
        @param pMessage The entity message.
        @param targetChannel The channel that the message arrived on.
    */
    void HandleEntityRemovedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when properties of an entity change.
        @param pMessage The entity message.
        @param targetChannel The channel that the message arrived on.
    */
    void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        Tells the service if a given entity is visible or not.
        The service needs to know if an entity is visible so that the property visualizers
        bound to that entity match the entity's visibility.
        This uses the VisualizerVisibilityTracker to make final visibility determinations.
        @param entityID The entity.
        @param source The source changing the visibility.
        @param category A unique integer ID used by the source to differentiate between multiple
            methods of changing invisibility.  Must be a number between 0-31.
        @param isVisible Whether the entity is visible or not.
    */
    void SetEntityVisibility(egf::EntityID entityID,
        const efd::utf8string& source,
        efd::UInt32 category,
        bool isVisible);

protected:

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnShutdown();

    void RegisterForEntityMessages();

    /// Created visualizers for each entity.
    efd::map<egf::EntityID, efd::map<efd::utf8string, IPropertyVisualizerPtr> > m_visualizers;

    /// Discovered entities with a property visualizer.
    efd::map<egf::EntityID, egf::Entity*> m_entities;

    /// Helper function for adding a visualizer for a single entity
    void AddVisualizers(egf::Entity* pEntity);

    ecr::RenderService* m_pRenderService;
    ecr::SceneGraphServicePtr m_spSceneGraphService;
    efd::MessageService* m_pMessageService;
    egf::FlatModelManager* m_pFlatModelManager;
    egf::EntityManager* m_pEntityManager;

    efd::Bool m_visualizersEnabled;

    VisualizerVisibilityTracker m_visibilityTracker;
    VisualizerConnectionTracker m_connectionTracker;
};

typedef efd::SmartPointer<PropertyVisualizationService> PropertyVisualizationServicePtr;

} // namespace

#endif
