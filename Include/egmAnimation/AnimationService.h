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
#ifndef EE_ANIMATIONSERVICE_H
#define EE_ANIMATIONSERVICE_H

#include "egmAnimationLibType.h"

#include <egf/Entity.h>
#include <efd/FixedString.h>
#include <efd/ISystemService.h>
#include <egf/EntityChangeMessage.h>

#include <ecr/SceneGraphService.h>
#include <ecr/CoreRuntimeMessages.h>
#include <ecr/ecrSystemServiceIDs.h>
#include <ecr/SceneGraphCacheResponse.h>
#include <egmAnimation/KFMCache.h>
#include <egmAnimation/KFMCacheResponse.h>

#include <NiActorManager.h>

#include "ActorMessages.h"

namespace egf
{
    class EntityManager;
}
namespace efd
{
    class MessageService;
}

namespace egmAnimation
{

/**
    The Animation Service provides an interface and a set of script built-ins for interfacing with
    the Gamebryo animation system. The service allows seamless integration of entities, scripts,
    and behaviors with Gamebryo's animation system without the need for extensive custom code. The
    animation service performs several major functions. It handles loading of KFM and KF assets,
    provides script built-ins for starting and ending sequences, provides registration services for
    text key callbacks, and stores actor managers for each KFM asset which it uses for per-frame
    updates.

    The Animation Service notifies other services when Actor models are ready for use and
    then unavailale for use. These messages are always matched. Services wishing to be informed
    of such messages must subscribe to the channel returned by GetMessageCategory() and must
    register handlers for egmAnimation::ActorAddedMessage and egmAnimation::ActorRemovedMessage.
    Cache messages are sent on the same channel.

    The animation service also handles rapid iteration functionality for applications. When the
    service receives notification of an update to a file associated with an actor, it will
    attempt to update that asset with the new data in the file. This includes changes to
    the scene graph that is being animated and individual KF sequence files.

    The following properties can be rapidly iterated on in AnimationService:
     - KfmAsset
     - Attachments

    The following properties can not: (An entity must be deleted and re-added to change these.)
     - InitialSequence
     - IsKfmAssetShared
     - IsNifAssetShared
     - AccumulatesTransforms

    The Animation Service manipulates the pose (position and rotation) on entities with the
    Actor model using the following rules:
    - Animations that use accumulation, and hence implicitly move the character while it animates,
      modify the Position and Rotation properties of the entity to track the global position of
      the Accumulation Root node in the animated scene graph. Animations without accumulate do not
      modify the entity position. When operating in tool mode all pose updating is de-activated.
    - When the Position or Rotation of an entity with the Actor model is set by another
      system (from script, another service, or during rapid iteration) it is assumed that the
      new pose refers to the Accumulation Root of the actor. The delta between the current
      Accumulation Root pose and the given pose is applied to the Nif Root of the actor's
      scene graph. This will place the actor in the requested location while moving the initial
      pose so that the actor will be in the same place when the animationsare reset and played
      again.

    We recommend that there be no objects in the scene graph that are unaffected by the
    Accumulation Root (that is, not transformed by the Accumulation Root transform). Such objects
    will behave oddly when the pose on the character is reset and their position will not be that
    reported by the entity's position.
*/
class EE_EGMANIMATION_ENTRY AnimationService :
    public efd::ISystemService,
    public egf::IPropertyCallback
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AnimationService, efd::kCLASSID_AnimationService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

    /// @name Construction and Destruction
    //@{
protected:
    /// Virtual destructor.
    virtual ~AnimationService();

public:
    /**
        Default constructor.

        When in tool mode the service does not update the Position and Rotation on the actor as
        accumulation moves it. All pose information on the entity is applied to the Nif Root of
        the actor when in tool mode.
    */
    AnimationService(const bool toolMode = false);
    //@}

    /// @name Active Animation Management

    //@{

    /// Set an entity's target animation to a given sequence (given by ID.)
    inline efd::Bool SetTargetAnimation(
        const egf::EntityID& entityID,
        NiActorManager::SequenceID sequenceID);

    /// Set an entity's target animation to a given sequence (given by name.)
    inline efd::Bool SetTargetAnimation(const egf::EntityID& entityID,
        const efd::utf8string& sequenceName);

    /// Returns the sequence name of the entity's currently playing animation.
    /// If no animation is playing, NULL is returned.
    inline efd::utf8string GetCurrentAnimation(const egf::EntityID& entityID);

    /// Returns the sequence ID of the entity's currently playing animation.
    /// If no animation is playing, InvalidSequence is returned.
    inline NiActorManager::SequenceID GetCurrentAnimationId(const egf::EntityID& entityID);

    /// Returns the ID of the sequence that the entity is currently transitioning to.
    /// If not currently transitioning, InvalidSequence is returned.
    inline NiActorManager::SequenceID GetNextAnimationId(const egf::EntityID& entityID);

    /// Returns the name of the sequence that the entity is currently transitioning to.
    /// If not currently transitioning, NULL is returned.
    inline efd::utf8string GetNextAnimation(const egf::EntityID& entityID);

    /// Returns the ID of the sequence that the entity is currently transitioning to.
    /// If not currently transitioning, InvalidSequence is returned.
    inline NiActorManager::SequenceID GetTargetAnimationId(const egf::EntityID& entityID);

    /// Returns the name of the sequence that the entity will try to transition to next.
    /// If no target sequence, NULL is returned.
    inline efd::utf8string GetTargetAnimation(const egf::EntityID& entityID);

    /// Returns the current transition state for a given entity.
    inline NiActorManager::TransitionState GetTransitionState(const egf::EntityID& entityID);

    /// Returns the name for a given sequence ID in a given entity.
    /// If not found, NULL is returned.
    inline efd::utf8string GetAnimationNameFromId(
        const egf::EntityID& entityID,
        NiActorManager::SequenceID sequenceID);

    /// Returns the ID for a given sequence name in a given entity.
    /// If not found, InvalidSequence is returned.
    inline NiActorManager::SequenceID GetAnimationIdFromName(
        const egf::EntityID& entityID,
        const efd::utf8string& name);

    /**
        Activates a layered sequence on an entity.  See NiActorManager documentation for
        more information about these arguments.

        @param entityID Actor that owns the sequence.
        @param sequenceID Sequence ID to activate.
        @param autoDeactivate Whether to deactivate the sequence when it is complete.
        @param priority Sequence priority.
        @param weight Sequence weight.
        @param easeInTime Duration to ease this sequence in.
        @param easeOutTime Duration to ease this sequence out (if auto-deactivating.)
        @param timeSyncID Sequence to synchronize with.  InvalidSequence means no synchronization.
        @param freq Frequency to play this animation at.
        @param startFrame Frame to begin playing this animation at.
        @param additiveBlend Whether or not this sequence is additive.
        @param additiveRefFrame The base frame to generate additive deltas from.
        @return True if the sequence activated successfully.
    */
    virtual efd::Bool ActivateLayeredSequenceById(
        const egf::EntityID& entityID,
        NiActorManager::SequenceID sequenceID,
        efd::Bool autoDeactivate = true,
        efd::SInt32 priority = 0,
        efd::Float32 weight = 1.0f,
        efd::Float32 easeInTime = 0.0f,
        efd::Float32 easeOutTime = 0.0f,
        NiActorManager::SequenceID timeSyncID = NiKFMTool::SYNC_SEQUENCE_ID_NONE,
        efd::Float32 freq = NiActorManager::SEQUENCE_DATA_FREQUENCY,
        efd::Float32 startFrame = 0.0f,
        efd::Bool additiveBlend = false,
        efd::Float32 additiveRefFrame = 0.0f);

    /// Sets the frequency of an entity's sequence.
    /// @return True if successful, false if entity or sequence do not exist.
    inline efd::Bool SetSequenceFrequencyById(
        const egf::EntityID entityID,
        NiActorManager::SequenceID sequenceID,
        efd::Float32 frequency);

    /// Gets the frequency of an entity's sequence.
    /// @return True if successful, false if entity or sequence do not exist.
    inline efd::Bool GetSequenceFrequencyById(
        const egf::EntityID entityID,
        NiActorManager::SequenceID sequenceID,
        efd::Float32& frequency);

    /// Sets the weight of an entity's sequence.
    /// @return True if successful, false if entity or sequence do not exist.
    inline efd::Bool SetSequenceWeightById(
        const egf::EntityID entityID,
        NiActorManager::SequenceID sequenceID,
        efd::Float32 weight);

    /// Gets the weight of an entity's sequence.
    /// @return True if successful, false if entity or sequence do not exist.
    inline efd::Bool GetSequenceWeightById(
        const egf::EntityID entityID,
        NiActorManager::SequenceID sequenceID,
        efd::Float32& weight);

    /// Gets the duration of an entity's sequence.
    /// @return True if successful, false if entity or sequence do not exist.
    inline efd::Bool GetSequenceDurationById(
        const egf::EntityID entityID,
        NiActorManager::SequenceID sequenceID,
        efd::Float32& duration);

    /**
        Deactivates a layered sequence on an entity.

        @param entityID The actor.
        @param sequenceID Sequence ID to deactivate.
        @param easeOutTime Duration to ease the sequence out.
        @return True if the sequences was succesfully deactivated.
    */
    virtual efd::Bool DeactivateLayeredSequenceById(
        const egf::EntityID& entityID,
        NiActorManager::SequenceID sequenceID,
        efd::Float32 easeOutTime);

    /// Gets a list of active sequences on an entity.
    inline void GetActiveSequences(
        const egf::EntityID& entityID,
        efd::vector<efd::utf8string>& sequences);

    /**
        Get the currently paused state of an Entity's actor manager.

        False is returned if the service does not know of the entity. When the
        entity is known and has an actor manager, the paused state of the actor manager
        is returned. Otherwise, the cached pause state, which will be used when the
        actor manager is created, is returned.
    */
    inline efd::Bool IsPaused(egf::EntityID entityID);

    /**
        Set the paused state of the entity's actor.
    */
    inline void SetPaused(egf::EntityID entityID, efd::Bool isPaused);

    //@}

    /// @name Text Key Registration

    //@{

    /// Registers a text key callback behavior function.  This behavior will be invoked for any
    /// text key events an entity fires.
    virtual efd::Bool ListenForTextKeyEvents(
        const egf::EntityID& entityID,
        const char* behaviorName,
        const char* textKey = NULL,
        const char* seqName = NULL);

    /// Clears all registered text key callbacks for a given entity.
    inline efd::Bool ClearRegisteredTextKeys(const egf::EntityID& entityID);

    //@}

    /**
        @name Asset Caching

        When an asset is cached, this service immediately loads it and will never unload it
        until it is removed from the cache.  When entities with shared actors request this
        asset, it will be cloned rather than loaded from disk, which can save having to repeatedly
        reload assets.

        Caching is a boolean state, not a reference count. If an asset is repeatedly cached,
        it will still be uncached during the first RemoveFromCache or RemoveAllFromCache.
    */
    //@{

    /**
        Load and cache any assets that match the provided asset ID.

        The assets may already be loaded from disk, in which case true is returned and the
        handles for the asset are returned. Otherwise, the caller must wait for a
        KFMCacheResponse message on the given category with a list of handles to
        the cached objects. The identifier in that message will be the urn from the given
        assetID.

        @param assetID The ID for the asset you wish to cache.
        @param pRequestData Data that will be passed back to you in the response to this cache
            request, if one is sent.
        @param responseCategory The category to send the response on when the recreate is
            completed. The message will only be sent if this function returns false.
        @param o_handles A vector of handles to cached actors that will be filled if
            the assets are already available (only when true is returned by this function).
            Information about the asset can be obtained by using the handle with functions
            in the egmAnimation::KFMCache returned by GetKFMCache.
        @result True if the assets for the requested ID were already in the cache, or could be
           cached immediately. False if you must wait on a message indicating the result of the
           caching operation.
    */
    efd::Bool Cache(
        const efd::AssetID& assetID,
        KFMCache::IKFMCacheRequestData* pRequestData,
        const efd::Category responseCategory,
        efd::vector<KFMCache::KFMCacheHandle>& o_handles);

    /**
        Un-cache KFM files direct from the handle that was provided when the
        KFM was cached.

        This must be called at some point if the asset is ever to leave the cache,
        but asset will only be removed from the cache when no other objects are using the
        cached data.

        @param i_handles The handles for the assets, as returned in the response to Cache or
            by CacheKFMFileName.
    */
    void UnCacheHandles(efd::vector<KFMCache::KFMCacheHandle>& i_handles);

    /// Stop caching all assets.
    void RemoveAllFromCache();

    //@}


    /**
        Get the NiActorManager object for a given entity.

        Returns the actor manager for the given entity, NULL if the entity is not known
        to the service.

        The AnimationService owns the pointer - applications must not delete it.
    */
    inline NiActorManager* GetActorManager(const egf::EntityID& entityID);

    /**
        Get the KFM Cache object used by the service to manage KFM assets.

        The cache is necessary to look up data related to egmAnimation::KFMCache::KFMCacheHandle
        objects.
    */
    inline KFMCache* GetKFMCache() const;

    /**
        Get the category used by this service to send any notifications of actors added and
        removed.

        The category is only valid after OnPreInit has completed.
    */
    inline efd::Category GetMessageCategory() const;

    /// @name Message Handling

    //@{

    /**
        This message handler is called when an entity is added to the world.
        The Animation Service starts updating the entity.

        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityEnterWorldMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been removed from the world.

        The Animation Service stops updating the entity.

        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityExitWorldMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been updated in the
        EntityManager.

        If the KFM asset property has been updated, the animation service
        queues the assets for reloading.

        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        Handle an KFM asset cached response message from the KFM cache.

        @param pResponse The cache response message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleCacheResponse(
        const egmAnimation::KFMCacheResponse* pResponse,
        efd::Category targetChannel);

    /**
        Handle a message indicating that scene graph assets have been added.

        This happens during rapid iteration. The animation service will update the NIF root
        of the associated actor manager with the new scene graph.

        @param pMessage The scene graph added message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleSceneGraphAddedMessage(
        const ecr::SceneGraphAddedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Handle a message indicating that scene graph assets have been removed.

        This happens during rapid iteration. The animation service will remove the NIF root
        for the associated actor.

        @param pMessage The scene graph removed message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleSceneGraphRemovedMessage(
        const ecr::SceneGraphRemovedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Handle a message indicating that scene graph assets have been cached.

        This message is processed when a cache request has been made for an actor.
        Other scene graph cache responses are ignored.

        @param pMessage The scene graphs cached response.
        @param targetChannel Channel the message was sent on.
    */
    void HandleSceneGraphCacheResponse(
        const ecr::SceneGraphCacheResponse* pMessage,
        efd::Category targetChannel);

    /**
        Handle an asset preload request.

        @param pRequest The entity that is requesting preload.
        @param targetChannel Channel the message was sent on, which asserts to
            egf::EntityManager::.
    */
    void HandlePreloadRequest(
        const egf::EntityPreloadRequest* pRequest,
        efd::Category targetChannel);

    //@}

    /// @cond EMERGENT_INTERNAL

    /**
        This method is called by the Actor built-in model to notify the service that
        an entity has been created that is of interest to the service.

        A corresponding RemoveEntityWithActorModel call will be made when the entity is
        removed.
    */
    virtual void AddEntityWithActorModel(egf::Entity* pEntity);

    /**
        This method is called by the Actor built-in model to notify the service that
        an entity has been removed.

        A corresponding AddEntityWithActorModel call will have been made when the entity was
        added.
    */
    virtual void RemoveEntityWithActorModel(egf::Entity* pEntity);

    /**
        Callback for built-in model property changes.

        The AnimationService registers itself to get property update callbacks
        from the PlaceableModel. This function is invoked to apply the property change.
    */
    virtual void OnPropertyUpdate(
        const egf::FlatModelID& modelID,
        egf::Entity* pEntity,
        const egf::PropertyID& propertyID,
        const egf::IProperty* pProperty,
        const efd::UInt32 tags);

    /// @endcond

protected:
    /// @name Methods Overridden from ISystemService

    //@{
    /// Returns the display name, "AnimationService".
    virtual const char* GetDisplayName() const;

    /// Subscribes to necessary messages for this service primarily asset notifications.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /// Sets up connections to other services necessary to operation, SceneGraphService,
    /// EntityManager, and ReloadService.
    virtual efd::AsyncResult OnInit();

    /// Iterates over all the NiActorManager objects owned by the service and updates each
    /// with the current game time.
    virtual efd::AsyncResult OnTick();

    /// Shuts down the service and cleans up any referenced resources.
    virtual efd::AsyncResult OnShutdown();
    //@}

    class AnimationEventCallback;

    /**
     * This class is used by the text key callback system to match text keys based on what keys
     * of interest have been registered through the animation service.
    */
    class TextKeyBehavior : public NiTextKeyMatch
    {
        NiDeclareRTTI;
    public:
        /// @name Construction and Destruction
        //@{
        /// Default Constructor.
        TextKeyBehavior(const char* match, const char* behavior);
        //@}

        /// Invoke the behavior on the entity.
        virtual void InvokeBehavior(
            egf::Entity* pEntity,
            NiActorManager* pActorMgr,
            NiActorManager::SequenceID sequenceID,
            const NiFixedString& textKey,
            float eventTime);

        inline const NiFixedString& GetBehavior();
    protected:
        NiFixedString m_behavior;
    };
    typedef efd::SmartPointer<TextKeyBehavior> TextKeyBehaviorPtr;

    class TextKeyMatchAll : public TextKeyBehavior
    {
        NiDeclareRTTI;
    public:
        /// @name Construction and Destruction
        //@{
        /// Default Constructor.
        TextKeyMatchAll(const char* behavior);
        //@}

        // Always matches and sets the last matched key.
        virtual efd::Bool IsKeyMatch(const NiFixedString& textKey);
    };
    typedef efd::SmartPointer<TextKeyMatchAll> TextKeyMatchAllPtr;

    /**
        This is an overridden implementation of a callback object to handle
        actor callbacks.  It allows for sequences to be automatically eased out
        as well as automatically invoking behaviors for text keys events.
    */
    class AnimationEventCallback : public NiActorManager::CallbackObject
    {
    public:

        /// @name Construction and Destruction
        //@{
        /// Default Constructor.
        AnimationEventCallback();
        //@}

        // Event callbacks required by NiActorManager::CallbackObject.

        // This one does nothing.
        virtual void AnimActivated(
            NiActorManager* pActorMgr,
            NiActorManager::SequenceID sequenceID,
            NiControllerSequence* pSeq,
            float eventTime);

        // This one does nothing.
        virtual void AnimDeactivated(
            NiActorManager* pActorMgr,
            NiActorManager::SequenceID sequenceID,
            NiControllerSequence* pSeq,
            float eventTime);

        // This one does nothing.
        virtual void AnimCompleted(
            NiActorManager* pActorMgr,
            NiActorManager::SequenceID sequenceID,
            NiControllerSequence* pSeq,
            float eventTime);

        // Invokes the behavior associated with the key, if any.
        virtual void TextKeyEvent(
            NiActorManager* pActorMgr,
            NiActorManager::SequenceID sequenceID,
            const NiFixedString& textKey,
            const NiTextKeyMatch* pMatchObject,
            NiControllerSequence* pSeq,
            float eventTime);

        // Checks if we have an ease-out time for this sequence, and then deactivates.
        virtual void EndOfSequence(
            NiActorManager* pActorMgr,
            NiActorManager::SequenceID sequenceID,
            NiControllerSequence* pSeq,
            float eventTime);

        /// @name Storage of ease-out times for automatically deactivating sequences.
        //@{
        typedef efd::map<NiActorManager::SequenceID, efd::Float32> SequenceTimeMap;
        SequenceTimeMap m_easeOutTimes;
        //@}

        /// The entity associated with this callback object.
        egf::Entity* m_pEntity;
    };

    class ActorEntry;
    class AssetData;

    /// Class to hold information about preload requests
    class EntityPreloadData : public efd::MemObject
    {
    public:
        ActorEntry* m_pEntityData;
        efd::Category m_responseCategory;
    };

    // Generic KFM Cache request data for this service
    class KFMCacheRequestData : public KFMCache::IKFMCacheRequestData
    {
        EE_DECLARE_CONCRETE_REFCOUNT;
    public:
        KFMCacheRequestData();
        ~KFMCacheRequestData();

        // The asset data associated with this request. Only set if an entity has requested this
        // specific asset.
        AssetData* m_pAssetData;

        // Pending response, only if this is a cache request.
        KFMCacheResponse* m_pResponse;

        /// Count of NIFs we are waiting on for cache requests.
        efd::UInt32 m_numOutstandingNIFs;
    };
    typedef efd::SmartPointer<KFMCacheRequestData> KFMCacheRequestDataPtr;

    /// Structure to hold information about actor assets
    EE_EGMANIMATION_ENTRY class AssetData : public efd::MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;
    public:
        AssetData();
        virtual ~AssetData();

        enum AssetDataState
        {
            ADS_Loading,
            ADS_Ready,
            ADS_Unloaded
        };

        /// Returns false if this entity is not being shared and can be removed.
        efd::Bool InUse() const;

        /**
            Remove the given entity from the preload list, if present

            Returns true if the entity was present in the preload list.
        */
        efd::Bool RemoveEntityFromPreload(egf::Entity* pEntity);

        inline NiActorManager::SequenceID GetSequenceID(const efd::utf8string& sequenceName) const;
        inline efd::utf8string GetSequenceName(const NiActorManager::SequenceID sequenceID) const;

        /// The current state, initially locating, then loading etc.
        AssetDataState m_state;

        /// The identifier that the asset was requested with, only valid while loading
        efd::utf8string m_identifier;

        /// May be either a physical ID or a path on disk.
        efd::utf8string m_physicalID;

        // Handle into the actor in the KFMCache.
        KFMCache::KFMCacheHandle m_cacheHandle;

        /// The set of entities sharing this asset data.
        efd::vector<ActorEntry*> m_entities;

        /// Mapping of sequence ID to names for the actor.
        efd::map<NiActorManager::SequenceID, efd::utf8string> m_sequenceNames;

        /// Mapping of sequence names to ID for the actor.
        efd::map<efd::utf8string, NiActorManager::SequenceID> m_sequenceIDs;

        /// The set of preload requests that we have not yet responded to.
        efd::vector<EntityPreloadData*> m_preloads;

        /// This pointer is non-NULL if there is an outstanding load for entity assets.
        KFMCacheRequestDataPtr m_spEntityLoadData;

        /// This pointer is non-NULL if there is an outstanding cache request that includes this
        /// asset.
        KFMCacheRequestDataPtr m_spCacheLoadData;

        /// Handle to the cached scene graph, if this asset is cached itself.
        ecr::SceneGraphCache::SceneGraphCacheHandle m_nifCacheHandle;

        /// Was this asset explicitly cached?
        efd::Bool m_isCached;
    };
    typedef efd::SmartPointer<AssetData> AssetDataPtr;

    /// Structure to hold entity scene graph information
    EE_EGMANIMATION_ENTRY class ActorEntry : public efd::MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;
    public:
        ActorEntry();
        ~ActorEntry();

        // The actor manager
        NiActorManagerPtr m_spActorManager;

        // Only NULL if the asset couldn't load. But check with the AssetData to see if the
        // asset is ready for use.
        AssetDataPtr m_spAssetData;

        /// The callback object for this entity.
        AnimationEventCallback m_eventCallback;

        // An index to use when this object is not updated.
        static const efd::UInt32 kInvalidUpdateIndex;

        // The index of this entity in the update vector.
        efd::UInt32 m_updateIndex;

        // The entity this data belongs to.
        egf::Entity* m_pEntity;

        // The sequence ID of any currently playing sequence at the time the actor manager is
        // removed for any reason. Used to set the playing animation back again.
        NiActorManager::SequenceID m_currentSequenceID;

        // The most recently known paused state
        efd::Bool m_currentPaused;

        // Returns true if the data is waiting on it's asset to be available.
        efd::Bool IsWaitingOnAsset() const;

        inline efd::Bool IsAssetShared() const;
        inline void SetIsAssetShared(const efd::Bool bIsAssetShared);
        inline efd::Bool IsAccumulated() const;
        inline void SetIsAccumulated(const efd::Bool bIsAccumulated);
        inline efd::Bool IsInWorld() const;
        inline void SetIsInWorld(const efd::Bool inWorld);

    protected:
        enum FlagBits {
            IS_ASSET_SHARED = 0x01,
            IS_ACCUMULATED = 0x02,
            IS_IN_WORLD = 0x04
        };

        efd::UInt16 m_flags;
    };
    typedef efd::SmartPointer<ActorEntry> ActorEntryPtr;

    /// Returns true if the entity has been discovered and is known to have an actor model.
    inline efd::Bool ContainsEntity(const egf::EntityID& entityID, ActorEntry*& pActorEntry);

    /// Returns true and fills in the asset ID if an entity has the Actor property and a valid
    /// KFM asset ID.
    efd::Bool HasKFMAssetProperty(const egf::Entity* pEntity, efd::AssetID& kfmAssetID);

    /// Bring an entity into the world, which means adding it to the update list.
    virtual void EntityEnterWorld(ActorEntry* pData);

    /// Take an entity out of the world, which means removing it from the update list.
    virtual void EntityExitWorld(ActorEntry* pData);

    /// Push the transform information from the entity properties into the actor root
    void UpdateTransform(ActorEntry* pActorEntry);

    /// Add and Remove data from the update lists.
    inline void AddToUpdate(ActorEntry* pData);
    inline void RemoveFromUpdate(ActorEntry* pData);

    /// Handle a message indicating that the KFM cache has reloaded an asset
    void ProcessKFMCacheReload(const KFMCacheResponse* pMessage);

    /// Cache a set of handles returned by the KFM cache
    bool CacheHandles(
        KFMCacheRequestDataPtr spCacheData,
        efd::vector<KFMCache::KFMCacheHandle>& handles);

    // Send a message and returns true if all of the NIFs for a cache request have been loaded.
    bool CheckCompletedCacheRequest(KFMCacheRequestData* pRequestData);

    /// Convenience accessor for the URN -> asset data map.
    /// Returns the asset data if we know the mapping from URN to physical ID and hence asset.
    /// This does not imply that the asset is currently loaded or even located.
    AssetData* FindAssetData(const efd::utf8string& identifier) const;

    /// Makes a new AssetData object and starts the process of finding an actor manager for it.
    AssetData* CreateAssetData(const efd::utf8string& identifier);

    /// Create asset data for a given identifier using a handle that has already been loaded.
    /// This is used when caching assets.
    AssetData* CreateAssetDataWithHandle(KFMCache::KFMCacheHandle handle);

    /// Merge an asset data object with an existing one because the redundant data has
    /// been found to have the same physical ID as the existing data. This function assumes
    /// that the redundant data is newly loaded and that all entities using
    /// the data have not yet been set up with their actor managers.
    void MergeAssetData(AssetData* pExistingData, AssetData* pRedundantData);

    /// Remove asset data if not in use
    void RemoveUnusedAssetData(AssetDataPtr spAssetData);

    /// Mark a preload requested asset as found. The scene graph for the asset is requested for
    /// preload at this point.
    void MarkPreloadsAsFound(AssetData* pAssetData);

    /// Set up an AssetData object based on the handle from the KFM Cache.
    /// This sets the actor on any waiting entities and causes them to go looking for their
    /// scene graphs. The pAssetData will be merged with any existing data for the same
    /// asset. The correct data to use will be returned.
    AssetData* SetAssetDataFromKFMCache(
        AssetDataPtr spAssetData,
        KFMCache::KFMCacheHandle cacheHandle,
        bool usagePending);

    /// Set up an AssetData object after a reload.
    void SetAssetDataFromReload(AssetData* pAssetData);

    /// Add the entity to the asset data. This is called on existing asset data when a new
    /// entity is added to the service.
    void AddEntityToAssetData(AssetData* pAssetData, ActorEntry* pEntityData);

    /// Remove all traces of the entity from its asset data. Should only by used when the
    /// entity is having its asset changed or the entity is being deleted.
    void RemoveEntityFromAssetData(ActorEntry* pEntityData);

    /// Populates the name <-> id maps in the given AssetData.
    void CacheSequenceNames(AssetData* pAssetData);

    /// Invalidates an asset, which removes all traces of it
    virtual void OnAssetLoadFailure(AssetDataPtr spAssetData);

    /// Update an entity when it is discovered.
    virtual void UpdateDiscoveredEntity(ActorEntry* pActorEntry);

    /// Look up the reflector service and register for entity discovery,
    /// entity property change, entity removal messages, entity added, and asset locator.
    virtual efd::Bool SubscribeToMessages();

    /// Create a new ActorEntry object and add it to the map of known entities.
    /// New data has the entity set, but no asset data, not updated, etc; basically
    /// just a placeholder to remember we have the entity. NULL is returned if there is
    /// existing data. Properties are pulled from the entity in this method.
    ActorEntry* CreateEntityData(egf::Entity* pEntity);

    /// Unload a given actor from the AnimationService.
    void RemoveActorEntity(egf::Entity* pEntity);

    /// Set the actor manager for an entity.
    /// This will cause messages to be sent out only if the scene graph for the entity is
    /// available.
    void SetActorManager(AssetData* pAssetData, ActorEntry* pActorData);

    /// Unset the actor manager for an entity.
    /// This will cause messages to be sent out.
    void UnsetActorManager(ActorEntry* pActorData);

    /// Called when the actor manager or a sequence has been reloaded.
    void ResetActorManager(ActorEntry* pActorData);

    /// Set the scene graph associated with a given actor.
    void SetActorSceneGraph(ActorEntry* pActorData, NiAVObject* pSceneGraph);

    /// Remove the scene graph on an actor
    void UnsetActorSceneGraph(ActorEntry* pActorData);

    /// Send a message that a given actor was loaded.
    virtual void OnActorAdded(egf::Entity* pEntity);

    /// Send a message that a given actor was unloaded.
    virtual void OnActorRemoved(egf::Entity* pEntity);

    /// Replace the asset used by an entity. The pNewAssetData may be NULL. If so it is
    /// created from the given name and the new pointer is returned.
    void ReplaceAsset(
        ActorEntry* pActorData,
        AssetData*& pNewAssetData,
        const efd::utf8string& newActorName);

    /// Mapping from known entities to their actor data
    typedef efd::map<egf::EntityID, ActorEntryPtr> ActorMap;
    ActorMap m_entityData;

    /// Map of physical IDs to asset data (which has a 1-1 mapping to cached actors)
    typedef efd::map<efd::utf8string, AssetDataPtr> AssetMap;
    AssetMap m_assetsByPhysicalID;

    /// Map of all asset locator request URNs to the asset data representing it.
    efd::map<efd::utf8string, efd::utf8string> m_requestIDToPhysicalID;

    /// Vector of all assets to be updated
    efd::vector<ActorEntry*> m_toUpdate;

    /// Use a map to keep track of any assets that are loading but for which we do not yet have
    /// a physical ID. Key is the identifier for which the asset was requested.
    AssetMap m_pendingAssetLoads;

    /// @name Cached system services used frequently by the animation service.
    //@{
    efd::MessageService* m_pMessageService;
    egf::EntityManager* m_pEntityManager;
    ecr::SceneGraphService* m_pSceneGraphService;
    //@}

    /// @name Asset Tags used to handle asset responses
    //@{
    /// Unique tag identifier used to mark assets that contain animation data used by the
    /// animation service.
    efd::utf8string m_kAnimationTag;

    /// Unique tag identifier used to mark assets that contain animation key-frame data used by
    /// the animation service.
    efd::utf8string m_kAnimationKFTag;
    //@}

    /// @name Dynamic categories used for identifying the source or destination of messages.
    //@{
    efd::Category m_assetLoadCategory;
    efd::Category m_assetRefreshCategory;
    efd::Category m_cacheAddCategory;
    efd::Category m_cacheRemoveCategory;
    efd::Category m_assetPreloadRequestCategory;
    efd::Category m_assetPreloadResponseCategory;
    efd::Category m_kfmCacheCategory;
    efd::Category m_sceneGraphCacheCategory;
    efd::Category m_actorMessageCategory;
    //@}

    /// KFM Cache to handle our asset caching
    KFMCachePtr m_spKFMCache;

    /// When true, the service does not update pose information on the actor and all pose
    /// information is applied directly to the Nif Root fo the actor.
    bool m_toolMode;
};

typedef efd::SmartPointer<AnimationService> AnimationServicePtr;

} // namespace

#include "AnimationService.inl"

#endif
