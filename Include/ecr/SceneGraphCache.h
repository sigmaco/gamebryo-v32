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
#ifndef EE_SCENEGRAPHCACHE_H
#define EE_SCENEGRAPHCACHE_H

#include "ecrLibType.h"

#include <ecr/ecrClassIDs.h>

#include <efd/MessageService.h>
#include <efd/AssetLocatorService.h>
#include <efd/AssetFactoryManager.h>
#include <efd/ReloadManager.h>
#include <ecr/NIFFactoryResponse.h>

#include <NiNode.h>
#include <NiTexturePalette.h>

class NiUpdateProcess;

namespace ecr
{

class SceneGraphCacheResponse;

/**
    The SceneGraphCache class is a helper for the scene graph service designed to pull code that
    manages the locating, loading and caching of scene graphs out of the Scene Graph Service.

    The SceneGraphCache class also managed reload requests for "gamebryo-scenegraph" (nif) files.
    Subscribers to the channel returned by the GetReloadCategory method
    will receive messages of type KFMCacheResponse when an asset refresh must be processed.

    Applications may wish to interface to this class if they load NIFs outside of the Scene
    Graph Service.

    This class is not thread safe.
*/
class EE_ECR_ENTRY SceneGraphCache : public efd::IBase, public efd::AssetChangeHandler

{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SceneGraphCache, efd::kCLASSID_SceneGraphCache, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// An enumeration of the possible states of assets
    enum AssetStatus
    {
        /// Not yet assigned. Assets in this state are not in the cache.
        AS_Invalid,

        /// Waiting on an asset locate. Assets in this state are not in the cache.
        AS_Locating,

        /// Waiting on a load. Assets in this state are not in the cache.
        AS_Loading,

        /// Waiting on a reload. A reloading asset has valid objects that can be used, but they will
        /// change later. We recommend you use the existing objects and request a reload, so that
        /// you receive the reload response and can update the objects.
        AS_Reloading,

        /// Available for use
        AS_Ready
    };

    /// Derive from the ISceneGraphCacheRequestData type to hold per-request data.
    typedef efd::MemObject ISceneGraphCacheRequestData;

protected:
    typedef efd::vector<efd::utf8string> FilePathVector;

    class RequestData : public efd::MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;

    public:
        RequestData();

        ~RequestData();

        /// The string that the asset was requested with
        efd::utf8string m_identifier;

        /// The response category
        efd::Category m_responseCategory;

        /// The response data
        ISceneGraphCacheRequestData* m_pResponseData;
    };
    typedef efd::SmartPointer<RequestData> RequestDataPtr;

    class PendingRequestData : public efd::MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;

    public:
        PendingRequestData();

        ~PendingRequestData();

        /// Status should be either locating or loading.
        AssetStatus m_status;

        /// The string that the asset was requested with
        efd::utf8string m_identifier;

        /// The set of outstanding filenames that go with this request. Some may be in the
        /// cache already, if loaded.
        FilePathVector m_filePaths;

        /// The number of paths in the cache so far
        efd::UInt32 m_cachedCount;

        /// Outstanding requests for this data
        efd::list<RequestDataPtr> m_requestList;
    };
    typedef efd::SmartPointer<PendingRequestData> PendingRequestDataPtr;

    /// Primary data repository for each cached scene graph.
    class EE_ECR_ENTRY SceneGraphCacheData : public efd::MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;

    public:
        SceneGraphCacheData();

        ~SceneGraphCacheData();

        /// Status
        AssetStatus m_status;

        /// The GUID (llid) for this asset, as returned by the asset locator service, or empty
        /// if the asset locator service was not used.
        efd::utf8string m_llid;

        /// The physical ID for this asset, or the file path if the locator service was not used
        efd::utf8string m_physicalID;

        /// The path that is used to index this data
        efd::utf8string m_filePath;

        /// The shared objects to clone for any new requests for this asset data.
        efd::vector<NiObjectPtr> m_objects;

        /// Outstanding requests for this data
        efd::list<PendingRequestDataPtr> m_requestList;
    };
    typedef efd::SmartPointer<SceneGraphCacheData> SceneGraphCacheDataPtr;

public:

    /**
        A handle to data in the cache, used to access data in the cache.

        It is a smart pointer, so setting a handle to zero is equivalent to releasing your
        interest in it. Handles with no external references may be uncached.
    */
    typedef SceneGraphCacheDataPtr SceneGraphCacheHandle;

    /// An invalid handle, equal to zero for purposes of comparison.
    static const SceneGraphCacheHandle k_invalidHandle;

    /**
        Constructor.

        The constructor prepares data structures for texture sharing.

        @param pTexturePalette The texture palette is used to facilitate texture sharing.
            The service will create a default palette if one is not provided in this constructor.
            The palette is stored as a smart pointer, so applications must not explicitly
            delete it.
    */
    SceneGraphCache(NiTexturePalette* pTexturePalette = NULL);

    /**
        Destructor.

        Cleans up any pending requests and empties the cache.
    */
    virtual ~SceneGraphCache();


    /**
        Init must be called before any other functions are called.

        The various services should be ready to receive requests.

        @param pMessageService The message service to use when sending messages.
        @param pAssetLocator The asset locator service used to find assets on disk.
        @param pAssetFactory The Asset Factory Manager used to load assets.
    */
    virtual void Init(
        efd::MessageService* pMessageService,
        efd::AssetLocatorService* pAssetLocator,
        efd::AssetFactoryManager* pAssetFactory);

    /// Shutdown must be called before the object is destructed in order to cleanly unsubscribe
    /// to messages.
    void Shutdown();

    /// Methods to Cache Scene Graphs
    //@{

    /**
        Cache the scene graphs referenced by a given identifier.

        The identifier may be a URN or raw filename. It's a urn if it contains a
        urn substring, otherwise a raw filename. A single URN may map to multiple files, and
        all files are cached.

        If the requested files are in the cache, the data for the item is returned in handles
        and the caller may use the handles to retrieve the objects. True is returned.

        Otherwise, false is returned and an ecr::SceneGraphCacheResponse message
        will be sent in response to this request when the requested scene graph objects are
        available, or on error.
    */
    virtual bool CacheSceneGraph(
        const efd::utf8string& identifier,
        const efd::Category responseCategory,
        ISceneGraphCacheRequestData* pResponseData,
        efd::vector<SceneGraphCacheHandle>& handles);

    /**
        Remove a scene graph from the cache, given a handle.

        This call removes the asset if the reference count indicates there are no
        references the handle (other than those necessary to call this function). It should
        be called immediately before a handle is set to zero in user code, so that the cache
        knows to check for removal of the asset.

        If there is a pending reload request for this asset at the time it is removed the
        response to that message will be delivered only if the asset still has a non-zero
        request count, otherwise no response will be sent for the reload.

        True is returned if the objects were in the cache, false if they were not in
        the cache.
    */
    virtual bool UnCacheSceneGraph(SceneGraphCacheHandle handle);

    /**
        Reload a scene graph.

        An ecr::SceneGraphCacheResponse message will be sent in response to this request when
        the requested scene graph has been reloaded, or on error.

        The ecr::SceneGraphCacheResponse will contain an result code of
        AssetCacheResponse::ACR_AssetNotFound if the original asset has been removed from the
        cache before the new asset is ready.

        If a reload is received while a reload is in progress the latter reload will get
        whatever was loaded with the first reload. We assume that the file on disk could not
        have changed between the time the file is actually loaded and the time the response
        is received.

        True is returned if the object was found in the cache and the reload has begun.
    */
    virtual bool ReloadSceneGraph(
        SceneGraphCacheHandle handle,
        efd::Category responseCategory,
        ISceneGraphCacheRequestData* pResponseData);

    //@}

    /**
        Replace a scene graph.

        An ecr::SceneGraphCacheResponse message will be sent in response to this request when
        the requested scene graph has been reloaded, or on error. The original handle continues
        to exist after the load, and a new handle will be returned in response. It is the
        application's responsibility to free the original handle.

        It is assumed that the identifier originally used for the asset is still the same (in
        other words, that the identifier is an Asset ID and the file that the ID refers to has
        changed). The Scene Graph Service uses this function to handle file renames or moves.

        Replacements are tracked by the file name, so multiple requests for the same original
        handle and the same file name will result in multiple responses with the same new handle.
        However, multiple request using the same identifier with different file names will result
        in one new handle for each distinct file name.

        True is returned if the object was found in the cache and the replacement has begun.
    */
    virtual bool ReplaceSceneGraph(
        SceneGraphCacheHandle handle,
        const efd::utf8string& newFileName,
        efd::Category responseCategory,
        ISceneGraphCacheRequestData* pResponseData);

    //@}

    /// Methods to Access Data by Handle
    //@{

    /**
        Get the current status of the asset.
    */
    inline AssetStatus GetStatus(SceneGraphCacheHandle handle) const;

    /**
        Get the number of top-level objects in a scene graph.

        This count may be zero when the NIF file failed to load. The asset is still in the cache
        so that reloads can be correctly handled.
    */
    inline efd::UInt32 GetObjectCount(SceneGraphCacheHandle handle) const;

    /**
        Get a top-level object in a scene graph by index.

        Index must be less than the value returned by GetObjectCount and it is not range-checked.
    */
    inline NiObject* GetObjectAt(
        SceneGraphCacheHandle handle,
        efd::UInt32 index) const;

    /**
        Get the physical ID for a cached scene graph
    */
    inline const efd::utf8string& GetPhysicalID(SceneGraphCacheHandle handle) const;

    /**
        Get the file name for a cached scene graph
    */
    inline const efd::utf8string& GetFilePath(SceneGraphCacheHandle handle) const;

    //@}

    /// Access to Internal Members
    //@{

    /// Get the texture palette used by this service.
    ///
    /// The returned value should be assigned to a smart pointer.
    inline NiTexturePalette* GetTexturePalette() const;

    /**
        Get the category used to send asset reloaded messages.
        
        The category is available after Init has been called. Services wishing to know
        when the asset associated with a given handle has been changed should register for
        messages of type ecr::SceneGraphCacheResponse on this category.
    */
    inline efd::Category GetReloadCategory() const;

    //@}

    /// @cond EMERGENT_INTERNAL

    // Asset locator response message handler
    void HandleAssetLocatorResponse(
        const efd::AssetLocatorResponse* pMessage,
        efd::Category targetChannel);

    // Asset load request response
    void HandleAssetLoadResponse(
        const NIFFactoryResponse* pResponse,
        efd::Category targetChannel);

    /// @endcond

protected:
    /// Subscribe to messages.
    void Subscribe();

    /// Asset related message handlers
    virtual void HandleAssetChange(const efd::utf8string& physicalID, const efd::utf8string& tag);
    void HandleReloadRequest(const efd::AssetLocatorResponse* pMessage);

    /// Request an identifier that we know is a single file path
    void RequestFilePath(
        const efd::utf8string& identifier,
        const efd::utf8string& fileName,
        const efd::Category responseCategory,
        ISceneGraphCacheRequestData* pResponseData);

    /// Request an identifier that we know is a urn requiring location
    void RequestURN(
        const efd::utf8string& identifier,
        const efd::Category responseCategory,
        ISceneGraphCacheRequestData* pResponseData);

    /// Find the set of file paths for a given identifier, if we know it.
    FilePathVector* FindFilePaths(const efd::utf8string& identifier);

    /// Remove the file paths for a given identifier
    void AddFilePaths(const efd::utf8string& identifier, const FilePathVector& paths);

    /// Remove the file paths for a given identifier
    void RemoveFilePaths(const efd::utf8string& identifier);

    // Check to see if all asset shave been loaded and if so send the responses and close
    // out the requests for this identifier. Returns true if we completed the requests.
    bool CheckCompleteRequest(PendingRequestData* pPendingRequest);

    efd::MessageService* m_pMessageService;
    efd::AssetLocatorService* m_pAssetLocatorService;
    efd::AssetFactoryManager* m_pAssetFactoryManager;

    /// Map of requests indexed by the request identifier. Requests live in this map until the
    /// time the response is sent to the requestor and the file entries that result are
    /// marked AS_Ready. All entries are indexed by the original request identifier.
    efd::map<efd::utf8string, PendingRequestDataPtr> m_pendingRequests;

    /// Map of files that are the process of loading
    efd::map<efd::utf8string, SceneGraphCacheDataPtr> m_pendingFiles;

    /// Map of ready assets indexed by file path.
    efd::map<efd::utf8string, SceneGraphCacheDataPtr> m_cache;

    /// Map of all requested identifiers to the file paths they represent.
    efd::map<efd::utf8string, FilePathVector*> m_identifierCache;

    // Categories to use with the AssetFactoryManager
    efd::Category m_assetLoadCategory;
    efd::Category m_assetReloadCategory;

    // Categories to use with the AssetLocatorService
    efd::Category m_assetLocateCategory;
    efd::Category m_assetRefreshCategory;
    
    // The category on which we send reload notification
    efd::Category m_assetReloadResponseCategory;

    /// Texture palette to share loaded textures.
    NiTexturePalettePtr m_spPalette;

    // True if we have subscribed to messages
    bool m_subscribed;
};

typedef efd::SmartPointer<SceneGraphCache> SceneGraphCachePtr;

} // end namespace ecr

#include "SceneGraphCache.inl"

#endif // EE_SCENEGRAPHCACHE_H
