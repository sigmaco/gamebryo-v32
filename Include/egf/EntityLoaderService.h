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
#ifndef EE_ENTITYLOADERSERVICE_H
#define EE_ENTITYLOADERSERVICE_H

#include <egf/egfLibType.h>
#include <efd/IMessageHelperSystemService.h>
#include <egf/egfSystemServiceIDs.h>
#include <egf/EntityLoaderMessages.h>
#include <efd/MessageHandlerBase.h>
#include <egf/Entity.h>
#include <egf/Scheduler.h>
#include <efd/OrderedMap.h>
#include <efd/SystemFrameworkEnums.h>
#include <efd/IDs.h>
#include <efd/AssetID.h>
#include <egf/EntitySetLoadState.h>
#include <egf/BlockIdentification.h>


namespace egf
{
// Forward declarations
class EntityChangeMessage;
class SAXEntityParser;
class BlockLoadParameters;

/**
    The EntityLoaderService is an efd::ISystemService that is responsible for listening to and
    responding to Entity Set (block) Load and Unload requests. The process of loading and unloading
    a set of entities is performed in an ISystemService to allow for asynchronous loading of
    Entities. Entities are loaded / unloaded during the EntityLoaderService OnTick invocation by
    the Service world Manager.

    The EntityLoaderService uses the AssetLocatorService to find assets related to the Entity.
    If the RapidIterationService is enabled the Asset load requests can be forwarded to a remote
    AssetServer.

    Only one xblock file can be loaded per request. If you need to load multiple block files,
    you'll need to request them one at a time.

    Unload requests must use the same AssetID that was used to load the block.
 */
class EE_EGF_ENTRY EntityLoaderService : public efd::IMessageHelperSystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EntityLoaderService, efd::kCLASSID_EntityLoaderService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

    /// @name Construction and Destruction
    //@{
protected:
    ~EntityLoaderService();
public:
    EntityLoaderService();
    //@}

    /// @name Configuration settings
    /// Settings to control the general operation of the EntityLoaderService.
    //@{
    /**
        Sets the maximum number of entities to create during a single tick. If a block contains
        more entities that this limit than the block will be loaded incrementally over several
        ticks. If multiple blocks are being loaded concurrently this limit will apply to the total
        entities from all loading blocks; blocks will be loaded in the order requested until the
        limit is reached and remaining loading will continue on the next tick.

        If your game can preload blocks well in advance you may wish to use a low throttle to avoid
        possible frame rate hitches caused by loading and creating too many entities at once.
        Conversely, if you want to load a large block as quickly as possible regardless of frame
        rate hitches than you should use a large throttle.

        @note This method can be called at any time including during OnPreInit or OnInit.

        @param entities The maximum number of entities to parse each pass.
    */
    inline void SetMaxEntityLoadThrottle(efd::UInt32 entities);
    /**
        Gets the maximum number of entities to load at a time.

        @note This method can be called at any time including during OnPreInit or OnInit.

        @return efd::UInt32 The maximum number of entities to parse each pass.
    */
    inline efd::UInt32 GetMaxEntityLoadThrottle() const;

    /**
        Sets the maximum number of entities to unload at a time. When a block is being unloaded all
        of the entities created through that block are destroyed which can generate various
        lifecycle behaviors and notification messages. This throttle will reduce the number of
        entities that are destroyed on each tick to avoid potential frame rate hitches that could
        otherwise result.

        When a block is unloaded all entities in that block are immediately told to exit the world.
        This gives the appearance of the block immediately disappearing regardless of the unload
        throttle value. A lower unload throttle can prevent frame rate hitches but at the cost of
        holding on to memory associated with the block that is unloading for longer.

        @note This method can be called at any time including during OnPreInit or OnInit.

        @param entities The maximum number of entities to parse each pass.
    */
    inline void SetMaxEntityUnloadThrottle(efd::UInt32 entities);
    /**
        Gets the maximum number of entities to unload at a time.

        @note This method can be called at any time including during OnPreInit or OnInit.

        @return efd::UInt32 The maximum number of entities to parse each pass.
    */
    inline efd::UInt32 GetMaxEntityUnloadThrottle() const;
    //@}

    /**
        A simple method for loading a block file in the current virtual process. Various parameters
        can optionally be passed via the BlockLoadParameters object in order to control what
        notifications are sent, how often they are sent and other factors controlling how the block
        is loaded. Any callback settings provided will remain in effect for the duration of the
        block and will receive additional notifications in the event the block is later unloaded.

        @code
            // Example usage:
            egf::BlockLoadParameters blp;
            blp.SetMessageCallback(m_myPrivateCategory);
            blp.SetAutoEnterWorld(false);
            pEntityLoaderService->RequestEntitySetLoad("urn:emergent-world:MyBlock", &blp);
        @endcode

        @param i_requestID Description of the block to load. This is the AssetID for the block
            resource plus an optional instance number if you wish to load multiple copies of the
            same block.
        @param i_pParameters An optional pointer to a structure containing configuration settings
            that specify how to load the block. If provided, settings from this structure are
            copied internally so the same BlockLoadParameters can be reused by the caller if
            desired.
        @return the state of the request.
    */
    efd::AsyncResult RequestEntitySetLoad(
        const BlockIdentification& i_requestID,
        const BlockLoadParameters* i_pParameters = NULL);

    /**
        Request the loading of a block file by passing an EntityLoadRequest.  This version of
        block file loading is equivalent to sending the EntityLoadRequest message to the
        private channel of this service.  You can directly call this method it you have a direct
        service pointer and you know you want to load the block file in the current virtual
        process.

        @param i_pMsg Pointer to an EntityLoadRequest message that contains block file data.
        @return the state of the request.
    */
    efd::AsyncResult RequestEntitySetLoad(const EntityLoadRequest* i_pMsg);

    /**
        Request that the entities from the already loaded block file enter the world.
        @param i_requestID The ID of a previously loaded block that should enter the world.
    */
    efd::AsyncResult RequestEntitySetEnterWorld(const BlockIdentification& i_requestID);

    /**
        Request that the entities from the already loaded block file exit the world.
        @param i_requestID The ID of the previously loaded block that should exit the world.
    */
    efd::AsyncResult RequestEntitySetExitWorld(const BlockIdentification& i_requestID);

    /**
        Request the unloading of a block file by passing an EntityLoadRequest.

        @note The original callbacks registered when the block was loaded will be notified of the
            block unload. You may pass an additional callback in the unload request but if the same
            callback was used during loading you will receive duplicate notifications. This applies
            to both behavior and message style callbacks.

        @param i_pMsg Pointer to an EntityLoadRequest message that contains block file data.
        @return the state of the request.
    */
    efd::AsyncResult RequestEntitySetUnload(const EntityLoadRequest* i_pMsg);

    /**
        Request the unloading of a block file with a message or behavior callback. By default a
        message based callback is used and one or more EntityLoadResult messages will be sent to the
        provided channel. If you specify the optional i_callback BehaviorID then one or more entity
        behavior events will instead be sent to the specified category.

        @note The original callbacks registered when the block was loaded will be notified of the
            block unload. You may pass an additional callback in the unload request but if the same
            callback was used during loading you will receive duplicate notifications. This applies
            to both behavior and message style callbacks.

        @param i_requestID ID of the block file to unload. This must match the ID used during the
            load request.
        @param i_entity The channel or EntityID destination for the callback
        @param i_context A user specified context that will be returned with the callback
        @param i_callback The behavior to invoke as a callback, or 0 to use a message callback
        @return the state of the request.
    */
    efd::AsyncResult RequestEntitySetUnload(
        const BlockIdentification& i_requestID,
        efd::Category i_entity = efd::kCAT_INVALID,
        efd::UInt32 i_context = 0,
        egf::BehaviorID i_callback = 0);

    /**
        Cancel the request for the loading of a block file.  By default a message based callback is
        used and a EntityLoadResult message will be sent to the provided channel. If you specify
        the optional i_callback BehaviorID then a behavior event will instead be sent to the
        specified category.

        @note The original callbacks registered when the block load was requested will be notified
            of the block load cancellation. You may pass an additional callback to this method but
            if the same callback was used during loading you will receive duplicate notifications.
            This applies to both behavior and message style callbacks.

       @param i_requestID The ID of the asset to cancel the request for. This must match the ID
            used during the load request.
       @param i_cb The Category to send the response message to.
       @param i_ctx The context to send with all response messages.
       @param i_callback The behavior to invoke as a callback, or 0 to use a message callback
       @return bool indicating the status of the request.
    */
    bool CancelLoadRequest(
        const BlockIdentification& i_requestID,
        efd::Category i_cb = efd::kCAT_INVALID,
        Context i_ctx = 0,
        egf::BehaviorID i_callback = 0);

    /**
        Reload the world having the given AssetUUID.

        The RapidIterationService will invoke this callback after fetching the updated world
        file from the AssetController. All instances matching the given asset ID will be reloaded.

        @param assetUUID The unique asset Id for the changed asset.
        @return The number of blocks reloaded.
    */
    virtual efd::UInt32 ReloadWorld(const efd::AssetID& assetUUID);

    /**
        Get the load status of a world by BlockIdentification.

        @param requestID The block identification of the world to check for.
        @return True if the world is loaded.
    */
    bool IsLoaded(const BlockIdentification& requestID);

public:

    /**
       Get my personal private channel.

       This is the same as calling GetEntityLoaderServiceCategory
       using the net ID of the local net service. The returned value is valid only
       after OnInit has completed.

       @return the private category that the EntityLoaderService listens to.
    */
    inline efd::Category GetPrivateChannel();

    /**
        Called by the RapidIterationService when a reset world is requested from a connected
        Toolbench.  In response to this request the Scheduler is paused, all entities are
        deleted, then we re-load all previously loaded block files before resuming the scheduler.
    */
    void OnWorldResetRequest();

    /// @cond EMERGENT_INTERNAL

    /**
        Function used to handle asset locator response messages.
    */
    void HandleAssetLocatorResponse(
        const efd::AssetLocatorResponse* pMessage,
        efd::Category targetCategory);

    /**
        Message handler for requests arriving via messaging.

        @param i_pMsg Pointer to the arriving message.
        @param targetChannel The channel the message was sent to.
    */
    void OnLoadRequest(const EntityLoadRequest* i_pMsg, efd::Category targetChannel);

    /**
        Message handler for scheduler cleared messages sent by the scheduler.

        @param i_pMsg pointer to the arriving message.
        @param targetChannel the channel the message was sent to.
    */
    void HandleSchedulerCleared(const efd::IMessage* i_pMsg, efd::Category targetChannel);

    /**
        Message handler for an internal unload response that is generated when processing
        a 'Reset' request.

        @param i_pMsg pointer to the arriving message.
        @param targetChannel the channel the message was sent to.
    */
    void HandleResetUnloadComplete(const egf::EntityLoadResult* i_pMsg, efd::Category targetChannel);

    /**
        Message handler for local entity creation messages.  When we load a block each created
        entity goes through various creation stages before it's finally created.  Once that
        finishes we receive this message.  When a block is loaded we wait until all entities
        in that block are created before we send out the "block load finished" callback.

        @param i_pMsg pointer to the arriving message.
        @param targetChannel the channel the message was sent to.
    */
    void OnEntityAdded(const EntityChangeMessage* i_pMsg, efd::Category targetChannel);

    /**
        Used to keep track of which entities have completed entering the world. Used in the
        auto enter world case to keep track of when to send entity set complete message.
        @param i_pMsg pointer to the arriving message.
        @param targetChannel the channel the message was sent to.
    */
    void OnEntityEnterWorld(const EntityChangeMessage* i_pMsg, efd::Category targetChannel);

    /**
        Message handler for local entity removed messages.  When we unload a block each destroyed
        entity goes through various destruction stages before it's finally destroyed.  Once that
        finishes we receive this message.  When a block is unloaded we wait until all entities
        in that block are destroyed before we send out the "block unload finished" callback.

        @param i_pMsg pointer to the arriving message.
        @param targetChannel the channel the message was sent to.
    */
    void OnEntityRemoved(const EntityChangeMessage* i_pMsg, efd::Category targetChannel);
    /// @endcond

protected:
    /// Registers dependencies
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /// OnInit creates internal objects, caches pointers to other services and subscribes
    /// to messages.
    virtual efd::AsyncResult OnInit();

    /// OnTick processes unload and then load requests.
    virtual efd::AsyncResult OnTick();

    /// OnShutdown processes any pending unloads and then performs clean up.
    virtual efd::AsyncResult OnShutdown();

    /// Return the name of the service, in this case "EntityLoaderService".
    virtual const char* GetDisplayName() const;

    typedef efd::set< egf::EntityID > EntityIdSet;

    /**
        Helper method that actually calls EnterWorld on each Entity.
        @param pEntityManager The Entity Manager Service to use.
        @param entities The set of entities to call EnterWorld on.
    */
    efd::AsyncResult DoEntitySetEnterWorld(EntityManager* pEntityManager, EntityIdSet& entities);

    /**
        Helper method that actually calls ExitWorld on each Entity.
        @param pEntityManager The Entity Manager Service to use.
        @param entities The set of entities to call EnterWorld on.
    */
    efd::AsyncResult DoEntitySetExitWorld(EntityManager* pEntityManager, EntityIdSet& entities);

    /**
        Helper to send a response message to a bunch of callbacks.

        @param i_callbacks A map of the callbacks to send the messages to.
        @param i_elr The EntityLoadResult to pass along in the message.
        @param i_assetID The BlockIdentification of the asset concerned.
        @return The number of successful messages sent.
    */
    efd::UInt32 SendResult(
        const EntitySetLoadState::CallbackMap& i_callbacks,
        EntityLoadResult::Result i_elr,
        const BlockIdentification& i_assetID);

    /**
       Helper to send a single response message.

       @param i_cb A callback category.
       @param i_behavior The behavior.
       @param i_ctx The context to pass along in the message.
       @param i_elr The EntityLoadResult to send.
       @param i_requestID The BlockIdentification used in the original request.
       @return bool indicating the status of the send.
    */
    bool SendResult(
        efd::Category i_cb,
        egf::BehaviorID i_behavior,
        Context i_ctx,
        EntityLoadResult::Result i_elr,
        const BlockIdentification& i_requestID);

    /**
        Helper used in the set version of SendResult to see if the given result type should be sent
        based on the active callbacks specified when the block was loaded.
    */
    bool ShouldSendResult(EntityLoadResult::Result result, efd::UInt32 flags);

    /// Data structure for holding all information about a block during the loading process
    struct LoadData
    {
        LoadData();
        LoadData(EntitySetLoadState* pESLS);
        ~LoadData();

        EntitySetLoadStatePtr m_spEntitySetLoadState;
        SAXEntityParser* m_pParser;
        enum Steps
        {
            /// Create the SAXEntityParser and begin the parse
            lds_Initial,

            /// @name Block Loading states
            //@{

            /// Parse entities up to the load limit
            lds_Parse,
            /// Add new entities to the entity manager up to the load limit
            lds_AddEntites,
            //@}

            /// @name Block Unloading states
            //@{

            /// The first step of unloading a block, all entities are removed from the world
            lds_UnloadStarted,
            /// Step two of unloading, we delete the entities in batches
            lds_DestroyEntities,
            /// Final step of unloading, we wait for all the entities to be destroyed
            lds_WaitForDestruction,
            //@}

            // finished
            lds_Done,
        };
        Steps m_step;
    };

    /**
        Process as many entries from the loading queue as possible until the threshold is reached.

        @return The number of pending requests remaining.
    */
    efd::UInt32 ProcessLoadRequests();

    /**
        Look at a single load request and attempt to satisfy the request.

        @param bid The block being requested
        @param ld Data concerning the block
        @return A status indicating whether the request is complete, failed or in progress.
    */
    efd::AsyncResult ProcessLoadRequest(BlockIdentification& bid, LoadData& ld);

    /**
        Process as many entries from the unloading queue as possible until the threshold is reached.

        @return The number of pending requests remaining.
    */
    efd::UInt32 ProcessUnloadRequests();

    /**
       Look at a single load request and attempt to satisfy the request.

       @param bid The block being requested
       @param ld Data concerning the block
       @return The number of pending requests remaining.
    */
    efd::AsyncResult ProcessUnloadRequest(BlockIdentification& bid, LoadData& ld);

    /**
        Helper to kick off a load. This helper will decide whether we are reloading a world or
        loading a new one. Then it will call LoadNewWorld or ReloadWorld.

        @param[in] i_requestId The block being loaded
        @param[in,out] io_data Provides Entity Load data for the asset to be loaded.
        @param[out] o_loadResult A load result value that should be sent to all callbacks.
        @return The result of the loading process.
    */
    efd::AsyncResult LoadEntitySet(
        const BlockIdentification& i_requestId,
        EntityLoaderService::LoadData& io_data,
        EntityLoadResult::Result& o_loadResult);

    typedef efd::list<egf::EntityPtr> EntityList;

    /**
        Find all the entities we loaded previously for this set but are not in the new entity
        set. This represents entities that were removed from the world. We delete these from
        the simulator directly.

        @param requestID the id of the block asset containing the new entities.
        @param newEntityList A list of new entities created by parsing the block file.
    */
    void DeleteRemovedEntities(
        const BlockIdentification& requestID,
        const EntityList* newEntityList);

    /**
        Clean up all loaded worlds.
    */
    void CleanupAllLoadedWorlds();

    /// The maximum number of entities to attempt to parse each pass.
    efd::UInt32 m_maxEntityLoadThrottle;

    /// The number of entities loaded so far on his tick. Compared against m_maxEntityLoadThrottle
    /// to know when to stop processing block loads.
    efd::UInt32 m_entitiesLoadedThisTick;

    /// The maximum number of entities to attempt to unload each pass.
    efd::UInt32 m_maxEntityUnloadThrottle;

    /// The number of entities unloaded so far on his tick. Compared against
    /// m_maxEntityUnloadThrottle to know when to stop processing block unloads.
    efd::UInt32 m_entitiesUnloadedThisTick;

    /// A map of the Load Requests
    typedef efd::OrderedMap<BlockIdentification, LoadData> LoadRequestMap;
    LoadRequestMap m_loadRequests;
    LoadRequestMap m_unloadRequests;

    /**
        Once loaded we keep track of what things have been loaded.  This way we know what sets can
        be unloaded and what entities each set controls.
    */
    class WorldLoadedInfo : public efd::MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;

    protected:
        /// Protected Destructor. Use reference counting to destroy.
        ~WorldLoadedInfo() {}

    public:
        inline WorldLoadedInfo();

        /// Created Entity Count tracks the number of entities from this block that have finished
        /// their OnCreate life cycle.  When the count matches the expected number then we send
        /// out the block-load complete callback.  During rapid iteration as new entities are
        /// added to the block this number will continue to increase.
        efd::UInt32 m_createdCount;

        /// Tracks the number of entities that have entered the world.
        efd::UInt32 m_enteredWorldCount;

        /// If the load request for this block had a callback we remember it so we can use that
        /// to notify when the block is completely loaded.
        efd::SmartPointer<EntitySetLoadState> m_spEntitySetLoadState;

        /// Set of all entities in the block.
        EntityIdSet m_entities;

        /// Set of entities being loaded.
        EntityIdSet m_newEntities;

        /// The Original request ID used to load this block
        BlockIdentification m_originalRequestID;
    };
    typedef efd::SmartPointer<WorldLoadedInfo> WorldLoadedInfoPtr;

    void InvokeBlockLoadedBehaviors(const EntityIdSet& entities);

    /// Keeps track of all the loaded entity sets. Key is the Request URN.
    //@{
    typedef efd::map<BlockIdentification, WorldLoadedInfoPtr> LoadedWorldMap;
    LoadedWorldMap m_loaded;
    //@}

    /// Helper to map resulting UUID-style AssetIDs into originally resulted URN-style AssetIDs.
    BlockIdentification GetRequestID(const BlockIdentification& blockID) const;

    // mapping of a load request to the resultant block file asset UUID.
    typedef efd::map<efd::AssetID, efd::AssetID> RequestToUUIDMap;
    RequestToUUIDMap m_requestToUUIDMap;

    /// The private channel of the EntityLoaderService
    efd::Category m_myPrivateChannel;

    /// A FlatModelFactory instance to feed to EntitySetLoadState
    egf::FlatModelFactory* m_pFlatModelFactory;

    /// Our Message Service
    efd::MessageService* m_pMessageService;

    /// Worlds to load after all entities are removed during a reset.
    typedef efd::map<BlockIdentification, EntitySetLoadStatePtr> ResetWorldsToLoadMap;
    ResetWorldsToLoadMap m_worldsToLoadAfterReset;
};

/// A SmartPointer for the EntityLoaderService class
typedef efd::SmartPointer<EntityLoaderService> EntityLoaderServicePtr;

} // end namespace egf

#include <egf/EntityLoaderService.inl>

#endif // EE_ENTITYLOADERSERVICE_H
