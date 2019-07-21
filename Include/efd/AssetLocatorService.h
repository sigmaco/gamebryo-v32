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
#ifndef EE_ASSETLOCATORSERVICE_H
#define EE_ASSETLOCATORSERVICE_H

#include <efd/AssetLocatorRequest.h>
#include <efd/AssetWeb.h>

namespace efd
{
/**
    The AssetLocatorService is a system service that is used by any application which integrates
    with the Emergent asset management system.

    At run-time, this service is used to translate logical asset names into physical asset
    locations for loading.

    The asset management system allows asset locations to be queried using a logical "Asset URI"
    name that may include either a GUID or a set of labels that specify which asset is needed.
    External asset management tools are used by the developer to manage asset labeling, and this
    data is accessible by the run-time via this system service.
*/
class EE_EFD_ENTRY AssetLocatorService : public IAssetLocatorService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AssetLocatorService, efd::kCLASSID_AssetLocatorService, IAssetLocatorService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:

    /**
        Constructor

        @param pServiceManager A pointer to the process ServiceManager instance
        @param GlobalTagSpace A set of tags that are automatically appended to every
            locate request. This limits the scope of the assets seen by the application
            to only those that include the specified tag(s). Format is "urn:tag1:tag2:etc."
    */
    AssetLocatorService(
        ServiceManager* pServiceManager,
        const efd::utf8string& GlobalTagSpace = efd::utf8string::NullString());

    /// @name Client API functions - connection related
    //@{

    /// Set the current connection state. 'True' will allow remote asset lookups. 'False' will
    /// ensure only local lookups are performed.
    void ConnectionEstablished(efd::Bool isConnected);

    /// Return current connection state. True is connected to a remote Asset Server.
    virtual bool IsConnected();

    /// Returns true if the AssetLocatorService is ready to respond to AssetLocate queries.
    virtual bool IsReady();

    /// The next request id we are going to give out
    static efd::UInt16 m_responseID;

    /**
        Open the specified asset web location.

        @param web_root The path of the asset-web to use for local asset lookups. This
            can be a relative path or a platform-specific absolute path.
    */
    efd::Bool AssetWebOpen(const efd::utf8string& web_root);

    /// Retrieve the asset web Author Id GUID value
    void GetAssetWebAuthorId(efd::utf8string& guid);
    //@}

    /// @name Client API functions - query related
    //@{

    /**
        Lookup the physical location of an asset based on logical Asset URI value.

        This is the main interface to the service functionality used by the client.  A logical
        asset URI is provided, and the location(s) of the corresponding asset(s) is returned in
        the asynchronous response.  The response is sent as a message of type
        AssetLocatorResponse.  In the event that there are no assets found matching the URI, then
        a response message with zero results is sent.

        Examples:
        - Asset URI                      Returns
        - urn:emergent-flat-model        All of the flat models known to asset manager
        - urn:emergent-world:Simple      All block files named 'Simple.xblock'
        - urn:gamebryo-scenegraph:Bob    The NIF file Bob.nif
        - urn:uuid:45fd58ab-345a-...     The asset with corresponding asset Id GUID value

        @param uri An asset URI value using either tag names or a GUID value.  All of the assets
            that match will be returned.
        @param callback Category that the response should be received on.
        @see GenerateAssetResponseCategory
        @param scope Controls whether the lookup is allowed to be handled by a remote Asset
            Server.
    */
    virtual efd::Bool AssetLocate(
        const efd::utf8string& uri,
        efd::Category callback,
        AssetLookupScope scope = ALS_LOCAL_OR_REMOTE);

    /**
            Lookup the physical location of an asset and return all asset browsing related
            information.

            This API is used by clients that want to present browsing information, like a GUI
            that enables a user to search through the asset-web.  It returns the asset location
            information exactly like the AssetLocate() API, and also returns information about
            additional tags that can be used to refine the search.

            This API is not intended for usage in a game.  It is provided for Tools that
            interface to the asset management system.

            @param uri An asset URI value using either tag names(preferred!) or a GUID value.
                       All of the assets that match will be returned.
            @param filePathHint Full pathname of the file.

            @return true if it succeeds, false if it fails.
    */
        virtual bool AssetBrowseInfo(
            const efd::utf8string& uri,
            const efd::utf8string& filePathHint = efd::utf8string::NullString());

    /**
            Retrieve the tag types and values that are known by the asset-web.

            This API is used by Tools to get the list of tags that are in use in the asset
            metadata. There are 3 categories of tags:  labels, classifications, and standard
            tags.  Each of the 3 sets may be retrieved individually.

            @param category An enum value indicating which category of tags is desired.

            @return true if it succeeds, false if it fails.
    */
    virtual bool AssetTagsInfo(AssetTagCategory category);

    //@}

    /// Child class used as a convenience for reading AssetLocatorService results
    class EE_EFD_ENTRY AssetLocationMap : public IBase
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(AssetLocationMap, efd::kCLASSID_AssetLocationMap, IBase);
        EE_DECLARE_CONCRETE_REFCOUNT;
        /// @endcond

    public:
        /**
            Constructor

            @param uri The Asset URI the results apply to
            @param loc The asset results stored in an AssetURLMap
        */
        AssetLocationMap(const efd::utf8string& uri, const AssetLocatorResponse::AssetURLMap& loc);

        /// Get the count of asset results in the location map
        efd::UInt32 Count() const;


        /// Get the asset URI value of the query that was used to produce this result set
        const efd::utf8string& Query() const;

        /// Returns True if a given tag is in the query URI
        efd::Bool HasTag(const efd::utf8string& tag) const;

        /**
            Get the Physical Asset ID

            @param index Index position in the array of results
            @returns A physical asset Id of the form "urn:uuid:A_GUID_VALUE"
        */
        const efd::utf8string& GetID(efd::UInt32 index) const;

        /**
            Get the Asset name property

            @param index Index position in the array of results
            @returns The name property of the asset, which is the filename without the file
                extension.
        */
        const efd::utf8string& GetName(efd::UInt32 index) const;

        /**
            Get the physical asset URL

            @param index Index position in the array of results
            @returns The URL, which is nominally a fully-qualified path to the asset data
        */
        const efd::utf8string& GetURL(efd::UInt32 index) const;

    private:

        struct AssetQueryResult
        {
            efd::utf8string assetID;
            efd::utf8string assetName;
            efd::utf8string assetURL;
        };

        efd::utf8string m_searchURI;
        efd::vector<AssetQueryResult> m_assetResults;
    };
    /// A SmartPointer for the AssetLocatorService::AssetLocationMap class
    typedef efd::SmartPointer<AssetLocationMap> AssetLocationMapPtr;

    /**
        Break apart an AssetLocatorResponse to gain easy access to the results

        @param pMessage Response message that is sent after a call to AssetLocate()
        @returns AssetLocationMap pointer
    */
    static AssetLocationMapPtr AssetLocationsFromResponseMsg(const efd::IMessage* pMessage);

    /// @cond EMERGENT_INTERNAL

    /// @name Message Handler functions
    //@{

    /**
        Handles a connect message from the CM.


        This method is registered with the local message service in OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar).

        @param pStreamMessage Pointer to an IMessage.
        @param channel Target category

    */
    virtual void HandleConnect(const efd::StreamMessage* pStreamMessage, efd::Category channel);

    /**
        Handles a close from the CM.

        This method is registered with the local message service in OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar).

        @param pStreamMessage Pointer to an IMessage.
        @param channel Target category
    */
    virtual void HandleDisconnect(const efd::StreamMessage* pStreamMessage, efd::Category channel);

    /**
        Handles an AssetConfigurationMessage Envelope message.

        This method is registered with the local message service in OnInit().

        @param pMessage Pointer to an IMessage.
        @param channel Target category.
    */
    virtual void HandleAssetConfigMsg(
        const efd::AssetConfigurationMessage* pMessage,
        efd::Category channel);

    /**
        Handles a AssetLocatorResponse Envelope message.  This method is registered
        with the local message service in OnInit().

        @param pMessage Pointer to an IMessage.
        @param targetChannel Target category.
    */
    virtual void HandleResponse(const efd::AssetLocatorResponse* pMessage, efd::Category channel);

    /**
        Handles a AssetTagsInforResponse message.

        This method is registered with the local message service in OnInit().

        @param pMessage Pointer to an IMessage.
        @param channel Target category.
    */
    virtual void HandleTagsInfoResponse(
        const efd::AssetTagsInfoResponse* pMessage,
        efd::Category channel);

    void AssetChangeReceived(const AssetLocatorResponse* Message, efd::Category channel);
    void AssetDataReceived(const FetchAssetDataResponse* Message, efd::Category channel);
    void AssetBrowseInfoReceived(const AssetBrowseInfoResponse* Message, efd::Category channel);
    //@}

    /// @endcond

protected:
    /// Destructor
    virtual ~AssetLocatorService();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnShutdown();
    const char* GetDisplayName() const;

    /// Metadata store. Will be read-only for this service.
    AssetWeb m_metastore;

    virtual void SendRequest(AssetLocatorRequest* pMessage, const Category &category);

    /// Perform local asset lookups using local metadata.
    void LocalLookup(const efd::utf8string& uri, efd::Category& callback);

    /// Keep track of the connection with the Asset Server.
    AssetClientDataState m_dataState;

    /// Hold a pointer to the local message service.
    MessageServicePtr m_spMessageService;

    /// Hold a pointer to the tools message service.
    MessageServicePtr m_spToolsMsgService;

    /// Map of outstanding query requests not yet responded
    efd::vector<efd::utf8string> m_PendingRequests;
    typedef efd::vector<efd::utf8string>::iterator RequestIterator;

    /// Change list - keeps track of the state of assets modified at run-time
    typedef enum {ASSET_MODIFIED, ASSET_LOADING} AssetChangeState;
    typedef efd::map<efd::utf8string, AssetChangeState> AssetChanges;

    AssetChanges m_asset_changes;
    efd::UInt32 m_fetching_from_server;

    void CheckChangeList(const AssetLocatorResponse::AssetURLMap& url_map);

    /// Helper functions for message creation, queuing, and handling.
    void MakeAssetURLMap(const TripleSet& triples, AssetLocatorResponse::AssetURLMap& url_map);

    void SendLocalResponse(
        const efd::utf8string& uri,
        const efd::Category& callback,
        const AssetLocatorResponse::AssetURLMap& url_map);

    void SendAssetFetchRequest(const efd::utf8string& uri);

    struct LocalResponseQueueEntry
    {
        efd::utf8string uri;
        efd::Category callback;
        AssetLocatorResponse::AssetURLMap urls;
    };

    void QueueLocalResponse(
        const efd::utf8string& uri,
        const efd::Category& callback,
        const AssetLocatorResponse::AssetURLMap& url_map);
    void FlushLocalResponseQueue();

    efd::vector<LocalResponseQueueEntry> m_local_response_queue;

    /// Global tags to apply to all searches
    efd::vector<efd::utf8string> m_globalTags;

    /// Category used as a callback for asset locate requests sent to the tools message service.
    efd::Category m_assetLocateChannel;
};

/// A SmartPointer for the AssetLocatorService class
typedef efd::SmartPointer<AssetLocatorService>AssetLocatorServicePtr;

} // end namespace efd

#endif // EE_ASSETLOCATORSERVICE_H
