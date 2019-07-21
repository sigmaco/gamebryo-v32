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
#ifndef RELOADMANAGER_H
#define RELOADMANAGER_H

#include <efd/ISystemService.h>
#include <efd/utf8string.h>
#include <efd/Category.h>
#include <efd/AssetLocatorResponse.h>
#include <efd/AssetChangeHandler.h>
#include <efd/MessageService.h>


namespace efd
{
/**
    Central multiplexer for forwarding asset change notify events to interested parties.

    Components register with the ReloadManager a callback that's called when an asset change
    is detected with tag(s) that match handler criteria. The ReloadManager itself listens for
    Asset Change Notify events.
*/
class EE_EFD_ENTRY ReloadManager : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ReloadManager, efd::kCLASSID_ReloadManager, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

protected:
    /// Destructor
    virtual ~ReloadManager();

public:
    /// Constructor
    ReloadManager();

    /**
        Get the listener channel for the reload manager. Change notifications should be sent to
        this category.
    */
    static efd::Category GetReloadManagerCategory();

    /**
        Register a callback handler that gets invoked when an asset with the given tag is changed.

        This method may be called as soon as the service is created. It is recommended that change
        handlers be registered during OnPreInit of a related system service.

        @param tag The tag value that the handler is interested in. For example, you would use
            "gamebryo-animation" if the handler should be called any time an asset tagged as an
            animation is changed.
        @param handler Pointer to the handler method
    */
    void RegisterAssetChangeHandler(
        const efd::utf8string& tag,
        efd::AssetChangeHandler* handler);

    /**
        Unregister a callback handler.

        This method may be called as soon as the service is created. Any change handlers registered
        with RegisterAssetChangeHandler must be unregistered before the provided AssetChangeHandler
        object is destroyed to avoid possible crashes. It is recommended that any change handlers
        registered by a system service be unregistered in the OnShutdown method of that service.

        @param tag The tag value that the handler was interested in.
        @param handler Pointer to the no-longer-used handler method
    */
    void UnregisterAssetChangeHandler(
        const efd::utf8string& tag,
        efd::AssetChangeHandler* handler);

    /// @cond EMERGENT_INTERNAL

    /// Handle asset locator response messages - Asset Change Notify messages in particular.
    void HandleAssetLocatorResponse(
        const efd::AssetLocatorResponse* pMessage,
        efd::Category targetChannel);
    /// @endcond

protected:
    /// @name ISystemService methods
    //@{
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();
    const char* GetDisplayName() const;
    //@}

private:
    /// Helper method to invoke AssetChangeHandler instances when an asset changes.
    void InvokeHandlers(
        const efd::utf8string &uuid,
        const efd::AssetLocatorResponse::AssetLoc& assetLoc);

    /// list of asset change handler pointers
    typedef efd::vector<efd::AssetChangeHandler*> AssetChangeHandlerList;

    /// map of asset tag to handler list.
    typedef efd::map<efd::utf8string, AssetChangeHandlerList> AssetChangeHandlerMap;

    /// Cached pointer to the message service
    efd::MessageServicePtr m_spMessageService;

    /// map of changed assets to their tuples
    efd::AssetLocatorResponse::AssetURLMap m_changedAssets;

    /// map of asset tags to change handlers
    AssetChangeHandlerMap m_changeHandlers;
};

/// A SmartPointer for the ReloadManager class
typedef efd::SmartPointer<ReloadManager> ReloadManagerPtr;

} // end namespace efd

#endif // RELOADMANAGER_H
