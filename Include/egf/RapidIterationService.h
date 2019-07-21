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
#ifndef EE_RAPIDITERATIONSERVICE_H
#define EE_RAPIDITERATIONSERVICE_H

#include <egf/egfLibType.h>
#include <efd/ISystemService.h>
#include <efd/utf8string.h>
#include <efd/Category.h>
#include <efd/MessageService.h>
#include <efd/NetMessage.h>
#include <efd/AssetLocatorService.h>
#include <efd/AssetChangeHandler.h>
#include <egf/egfSystemServiceIDs.h>

// Rapid iteration is disabled in shipping configurations
#ifndef EE_CONFIG_SHIPPING

#include <efdNetwork/NetService.h>


namespace efd
{
    class AssetLoadResponse;
    class NameResolutionMessage;
}

namespace egf
{

class SimDebugger;

/**
    This class is a central multiplexer to manage messages required during rapid iteration
    development scenarios. This is the main pathway for Toolbench to communicate global game
    control and asset management commands to a running game.

    During application development, you will normally want to create an instance of this system
    service in your application Main(). This will allow you to connect to your application from
    Toolbench, and to perform rapid iteration. This service provides the conduit for all the change
    notifications that are needed as you modify art assets, models, and scripts in development.
    Many of these changes can be immediately reflected in the running game via this service.
*/
class EE_EGF_ENTRY RapidIterationSystemService
    : public efd::ISystemService
    , public efd::AssetChangeHandler
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        RapidIterationSystemService,
        efd::kCLASSID_RapidIterationSystemService,
        efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// Construction and Destruction
    //@{
    RapidIterationSystemService();
protected:
    virtual ~RapidIterationSystemService();
    //@}

    /// OnPreInit performs internal initialization and registers itself as the
    /// asset change handler for core asset types (scripts, flat models and world).
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /// Performs initialization, including establishing network connections, beginning
    /// logging in Toolbench, and starting the simulation debugger.
    virtual efd::AsyncResult OnInit();

    /// Process reloads for the asset classes we handle.
    virtual efd::AsyncResult OnTick();

    /// Clean up internal objects and subscriptions.
    virtual efd::AsyncResult OnShutdown();

    /// Return the name of the service, in this case "RapidIterationSystemService".
    virtual const char* GetDisplayName() const;

public:
    /**
        Callback used for asset change notifications.

        The ReloadManager will invoke this callback for each registered tag. This service handles
        the reload functionality for several different asset types.

        @param assetId The unique asset Id for the changed asset
        @param tag The tag value that matched this handler's registration
    */
    virtual void HandleAssetChange(const efd::utf8string& assetId, const efd::utf8string& tag);

    /**
        Get the public listener channel.
        
        Messages directed to the service should be sent on this category. Toolbench already
        defines one category that it uses for all its messaging.

        May be called during PreInit or Init.
    */
    static const efd::Category& GetToolbenchPublicCategory();

    /**
        Get the category to which responses should be sent.
        
        All EntityLoaderServices will listen on a pre-defined category. Load request
        messages will go to that category.  We listen on this category for the responses.

        May be called during PreInit or Init.
    */
    static efd::Category GetPrivateCategory();

    /// Message handlers
    //@{
    virtual void HandleGameControlMessage(
        const efd::IMessage* pMessage,
        efd::Category targetChannel);
    void HandleAssetLocatorResponse(
        const efd::AssetLocatorResponse* pMessage,
        efd::Category targetChannel);
    void HandleNameResolutionResponse(
        const efd::NameResolutionMessage* pMessage,
        efd::Category targetChannel);
    virtual void HandleAssignNetIDMessage(
        const efd::AssignNetIDMessage* pAssignNetIDMessage,
        efd::Category targetCategory);
    void HandleAssetLoadResponse(
        const efd::AssetLoadResponse* pMessage,
        efd::Category targetCategory);
    //@}

    /**
        This method has been deprecated.
    */
    efd::Bool WaitForAssetServer(efd::TimeType timeout);

    /**
        Creates the SimDebugger instance, which is managed by RapidIterationService.

        May be called during PreInit or Init.

        @param pInstance An optional, derived instance of SimDebugger with game-specific extensions.
    */
    void CreateSimDebugger(egf::SimDebugger* pInstance = NULL);

    /**
        Destroys the SimDebugger instance, which is managed by RapidIterationService.
        
        This will normally happen on RapidIterationService shutdown, but can be called directly
        if needed earlier. May be called during PreInit or Init.
    */
    void DestroySimDebugger();

private:

    // Keep a local pointer for accessing the MessageService and NetService
    efd::MessageServicePtr m_spMessageService;
    efd::MessageServicePtr m_spToolsMsgService;
    efd::NetServicePtr m_spNetService;

    // Keep a local pointer for accessing the AssetLocatorService
    efd::AssetLocatorServicePtr m_spAssetService;
    /// Category used for my asset lookup responses
    efd::Category m_asset_lookup_callback;

    struct AssetLocation
    {
        // The asset ID.
        efd::utf8string m_assetId;

        // Location information reported by the AssetLocatorService.
        efd::AssetLocatorResponse::AssetLoc m_locationData;
    };

    typedef efd::list<AssetLocation> AssetLocationList;
    AssetLocationList m_flatModelLocationList;
    AssetLocationList m_assetLocationList;

    efd::set<efd::utf8string> m_pendingFlatModelLoads;

    // Process a set of reload operations from the provided asset location list.
    bool HandleReloads(AssetLocationList& locationList);

    // Initialization helpers
    void InitToolsMessaging(efd::ServiceManager *pServiceManager);
    void InitLogService(efd::ServiceManager *pServiceManager);
    void InitReloadManager(efd::ServiceManager* pServiceManager);
    void InitNameResolutionService(efd::ServiceManager* pServiceManager);
};

/// A SmartPointer for the RapidIterationSystemService class
typedef efd::SmartPointer<RapidIterationSystemService> RapidIterationSystemServicePtr;

} // end namespace efd

#endif // !defined(EE_CONFIG_SHIPPING)
#endif // EE_RAPIDITERATIONSERVICE_H
