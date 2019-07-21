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
// Emergent Game Technologies, Calabasas, California 91302
// http://www.emergent.net
#pragma once
#ifndef ASSETCONFIGSERVICE_H
#define ASSETCONFIGSERVICE_H

#include <efd/MessageService.h>
#include <efd/AssetLocatorService.h>

namespace efd
{

/**
   The AssetConfigService manages the current state of the Asset Locator and allows
   configuration changes to be applied via .ini file, command-line, or command messages.

   Additionally, the AssetConfigService provides a central repository of the current
   configuration for use by other services.
*/
class EE_EFD_ENTRY AssetConfigService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AssetConfigService, efd::kCLASSID_AssetConfigService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:

    const static char* kConfigAssetWebSection;
    const static char* kConfigAssetLoaderSection;

    /// Constructor
    AssetConfigService();

    /**
        Rescans the entire asset-web root.
    */
    virtual void RescanAssetWebRoot();

    /**
        Open the asset-web at the specified path and use for local lookups.

        This will only affect lookups that are handled by the local process, not lookups
        that are forwarded to a remote Asset Server.

        @param web_root The root path for the asset-web directory
    */
    virtual efd::Bool OpenAssetWebLocal(const efd::utf8string& web_root);

    /**
        Open the asset-web at the specified path and use for remote lookups.

        This will send a request to a connected, remote Asset Server to change the path it uses
        as its asset-web.  Note: An asset is raised if there is no connected, remote server for
        your process.

        @param web_root The root path for the asset-web directory
    */
    efd::Bool OpenAssetWebRemote(const efd::utf8string& web_root);

    /**
        Retrieve the list of queries to test, if any, specified in the Config.ini file.

        These are URI values that appear under [AssetWeb] with the name of "QueryTest#".
        There may be one or more specified in the Config.ini. These are used to test some
        small number of asset lookups against the current metadata at startup.

        @param query List of URIReader objects for each query
    */
    void GetQueryTests(efd::vector<utf8string>& query) const;

    /**
        Retrieve the list of query test results, if any, specified in the Config.ini file.

        These are relative path to assets that appear under [AssetWeb] with the name of
        "QTestResult#". There may be one or more specified in the Config.ini. These are used to
        test some small number of asset lookups against the current metadata at startup.

        @param results List of relative path to assets expected to return from the test query
    */
    void GetQueryTestResults(efd::vector<utf8string>& results) const;

    /**
        Retrieve the value of a particular netry in the AssetWeb portion of the configuration.

        @param key Key for the property to be retrieved
        @param value [out] The value of the property
    */
    void GetConfigValue(const efd::utf8string& key, efd::utf8string& value);

    /**
        Gets the asset web root read in the configuration file.
        @return Current asset web root.
    */
    const efd::utf8string& GetAssetWebRoot() const;

    /**
        Gets a flag indicating if we're pre-loading the graphs for an asset web.
        @return True if pre-loading graphs, otherwise, false.
    */
    efd::Bool GetPreloadGraphs() const;

    /// @cond EMERGENT_INTERNAL

    /// Message handler for responses to config changes(server->client)
    void HandleConfigResponse(
        const efd::AssetConfigurationMessage* pMessage,
        efd::Category targetChannel);
    /// @endcond

protected:
    /// Destructor
    ~AssetConfigService();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::AsyncResult OnInit();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::AsyncResult OnTick();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::AsyncResult OnShutdown();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual const char* GetDisplayName() const;

    /// Get local configuration information using the ConfigManager service
    void ReadConfiguration();

    /// Root path for the configured asset-web
    efd::utf8string m_assetWebRoot;

    /// Preload Graphs in the asset-web
    efd::Bool m_preloadGraphs;

    /// Vector of any 'query test' commands
    efd::vector<utf8string> m_queryTests;
    /// Vector of any 'query tests results' commands
    efd::vector<utf8string> m_queryTestResults;

    /// Message service for communication with the application that is using assets
    MessageServicePtr m_spMessageService;
    /// Message service for communication to tools such as AssetController.exe
    MessageServicePtr m_spToolsMsgService;

private:

    /// Forward a config change response for processing by other listeners
    void SendLocalResponse(const efd::AssetConfigurationMessage* pMessage = NULL);
    efd::AssetLocatorService* m_pAssetLocator;
};

/// A SmartPointer for the AssetConfigService class
typedef efd::SmartPointer<AssetConfigService> AssetConfigServicePtr;

} // end namespace efd

#include "AssetConfigService.inl"

#endif // ASSET_CONFIG_SERVICE
