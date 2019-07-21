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
#ifndef EE_PROXYSERVICE_H
#define EE_PROXYSERVICE_H

#include "egmVisualizersLibType.h"

#include <egf/EntityManager.h>
#include <egf/Entity.h>
#include <egf/EntityID.h>
#include <efd/MessageHandlerBase.h>
#include <efd/ISystemService.h>
#include <efd/AssetLocatorService.h>
#include <efd/StreamMessage.h>
#include <egf/EntityChangeMessage.h>
#include <ecr/ecrSystemServiceIDs.h>

#include <ecr/SceneGraphService.h>

namespace egmVisualizers
{

/**
    ProxyService handles the registration and management of 2D proxy textures and 3D proxy
    geometry.  When proxy entities are discovered, ProxyService registers scenegraphs
    with the SceneGraphService to update and render them.
*/
class EE_EGMVISUALIZERS_ENTRY ProxyService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ProxyService, efd::kCLASSID_ProxyService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

    /// @name Construction and Destruction
    //@{
protected:
    /// Virtual Destructor
    virtual ~ProxyService();

public:
    /// Default Constructor
    ProxyService();
    //@}

    /**
        This message handler is called when a new entity is discovered. The
        entity is inspected for any proxy related properties. If any
        are found, the scene graphs are registered with SceneGraphService.

        @param pMessage The entity message.
        @param targetChannel The channel that the message arrived on.
    */
    void HandleEntityDiscoverMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been removed from the entity manager.
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
        Asset locator response message handler
        @param pMessage The entity message.
        @param targetChannel The channel that the message arrived on.
    */
    void HandleAssetLocatorResponse(
        const efd::AssetLocatorResponse* pMessage,
        efd::Category targetChannel);

protected:
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual const char* GetDisplayName() const;
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnShutdown();

    void UpdateProperties(egf::Entity* pEntity, NiAVObject* pNode);

    efd::Bool CreateSceneGraph(egf::Entity* pEntity, const efd::utf8string& path);

    efd::Bool RecreateSceneGraph(
        ecr::SceneGraphService::SceneGraphHandle handle,
        const efd::utf8string& path);

    /// @name Cached services
    //@{
    efd::MessageService* m_pMessageService;
    egf::EntityManager* m_pEntityManager;
    ecr::SceneGraphService* m_pSceneGraphService;
    efd::AssetLocatorService* m_pAssetLocator;
    //@}

    /// Category used for my asset lookup responses
    efd::Category m_asset_lookup_callback;

    /// @name Map of proxy scene graphs for entities
    //@{
    typedef efd::map<egf::EntityID, ecr::SceneGraphService::SceneGraphHandle> EntitySceneGraphMap;
    EntitySceneGraphMap m_proxySceneGraphs;

    typedef efd::map<egf::EntityID, efd::utf8string> EntityStringMap;
    EntityStringMap m_pendingAssetLoads;
    //@}
};

typedef efd::SmartPointer<ProxyService> ProxyServicePtr;

}; // namespace

#endif // EE_PROXYSERVICE_H
