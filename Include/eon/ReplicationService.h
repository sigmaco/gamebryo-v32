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
#ifndef EE_REPLICATIONSERVICE_H
#define EE_REPLICATIONSERVICE_H

#include <eon/OnlineEntry.h>

#include <efd/ISystemService.h>
#include <efd/MessageService.h>
#include <egf/EntityManager.h>
#include <egf/Scheduler.h>

#include <eon/OnlineEntity.h>

#include <eon/EntityMessage.h>
#include <efd/StreamMessage.h>
#include <eon/ViewEventMessage.h>
#include <eon/DiscoveryRequest.h>
#include <egf/EntityChangeMessage.h>
#include <eon/eonSystemServiceIDs.h>

namespace efd
{
    class AssetLoadResponse;
}


namespace eon
{


/**
     \brief The implementation class that is the basis for a scheduler process.
 */
class EE_EONENTRY ReplicationService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ReplicationService, efd::kCLASSID_ReplicationService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// Constructor used to create an instance of a local cache
    ReplicationService();

    /**
        Add an entity to the local cache. This is a direct pass-through to EntityManager::AddEntity.
    */
    virtual bool AddEntity(ReplicationConsumerEntity* pEntity);

    /**
        Remove an entity from the cache and clean up all data related to the entity (in both
        the ReplicationService and potentially the Scheduler). This is the only safe way to remove
        a replica from the system.
    */
    virtual bool RemoveEntity(ReplicationConsumerEntity* pEntity);


    /// EntityManager methods that simply get passed on to the cache
    //@{
    inline ReplicatingEntity* FindEntity(const egf::EntityID& id) const;

    inline ReplicationProducerEntity* FindProducerEntity(const egf::EntityID& id) const;

    inline ReplicationConsumerEntity* FindConsumerEntity(const egf::EntityID& id) const;

    /**
        Like EntityManager::GetFirstEntityPos(), only it will only iterate reflected entities
    */
    inline egf::EntityManager::EntityMap::const_iterator GetFirstEntityPos() const;

    /**
        Like EntityManager::GetNextEntity(), only it will only iterate reflected entities
    */
    bool GetNextEntity(
        egf::EntityManager::EntityMap::const_iterator& io_iter,
        ReplicationConsumerEntity*& o_pEntity) const;
    //@}

    /**
        Begin Monitoring of a replication channel
        Owned entities can request that certain replication channels be monitored if they need to
        know about other entities using that channel.  To do so they call this method on the
        ReplicationService and in response the ReplicationService subscribes to Discover, Update,
        and Loss messages on the given category.  This ensures that other entities that might live
        in a remote simulator will be replicated locally.

        @note: Subscription calls are reference counted so you can call this method multiple times
        so long as an equal number of calls are eventually made to the
        UnsubscribeReplicationChannel method.

        @param channelToAdd the replication channel
    */
    void SubscribeReplicationChannel(efd::Category channelToAdd);

    /**
        End monitoring of a replication channel
        Owned entities can request that certain replication channels be monitored if they need to
        know about other entities using that channel.  When they no longer need to know about a
        channel or when that entity is being migrated or deleted it must call this method to
        remove the subscription to Discover, Update, and Loss messages.  Every call to the
        SubscribeReplicationChannel must eventually have a matching call to this method in order
        to maintain proper reference counts on the subscriptions.

        @param channelToRemove the replication channel
    */
    void UnsubscribeReplicationChannel(efd::Category channelToRemove);

    /**
        Set or clear the replication channels produced by the given entity.
        When an entity produces into a replication channel it must notify the ReplicationService.
        In response the ReplicationService will perform the proper subscription updates so that
        all connected processes can receive the published replication messages.  This also allows
        remote processes to request discovery messages using ProducerSend.  It will also send
        a Loss message to the old category and a Discover message to the new category.

        @param pEntity the Entity which is changing a replication channel
        @param groupIndex the index of the Property Group whose replication channel is being set.
        @param oldCat The previous replication channel, or kCAT_INVALID if not yet joined.
        @param newCat The new replication channel, or kCAT_INVALID if only leaving a channel.
    */
    void ChangeReplicationGroupCategory(
        ReplicationProducerEntity* pEntity,
        efd::UInt32 groupIndex,
        efd::Category oldCat,
        efd::Category newCat);

    /**
        Called by ReplicationProducerEntity::SetDirty to indicate that this entity needs to be
        considered for sending replication messages.
    */
    void SetDirty(ReplicationProducerEntity* pEntity, efd::UInt32 groupsMask);

    /**
        Clear the dirtiness of a specific group by index on the given entity.
    */
    void ClearDirty(ReplicationProducerEntity* pEntity, efd::UInt32 groupIndex);

protected:
    /// destructor
    virtual ~ReplicationService();

    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();
    inline const char* GetDisplayName() const;

    /**
        Check each replication group to see if it should send an update message.

        @param pEntity Pointer to entity we are generating an update for
        @param dirtyGroups The groups that are dirty on that entity
    */
    void UpdateDirtyReplicationGroups(ReplicationProducerEntity* pEntity, efd::UInt32 dirtyGroups);

    /// Helper for sending point-to-point discovery messages
    bool SendDiscoveryMessage(
        ReplicationProducerEntity* i_pEntity,
        efd::Category targetCategory,
        efd::Category updateGroupCategory);

    /// Helper for tracking what entities are using what replication categories
    void UpdateEntity(ReplicationConsumerEntity* pEntity, efd::Category updateCategory);

    /// Helper for changing the category on a replica during loss cases. This is sort of the
    /// opposite of the UpdateEntity method but also updates the entity itself as needed.
    void ChangeEntityReplicationCategory(ReplicationConsumerEntity* pEntityReal,
        efd::UInt32 groupIndex,
        efd::Category newCategory);

public:

    /// Handle Discovery of replicated Entities
    void HandleEntityDiscovery(const EntityMessage* pMessage, efd::Category targetChannel);

    /// Handle Updates of replicated Entities
    void HandleEntityUpdate(const EntityMessage* pMessage, efd::Category targetChannel);

    /// Handle Loss of replicated Entities
    void HandleEntityLoss(const EntityMessage* pMessage, efd::Category targetChannel);

    /**
         Message handler for ViewEvent messages.  This is used to enable the processing of view
         behavior invocation requests.

         @param pMessage pointer to the Entity Message class
    */
    void HandleViewBehaviorMsg(const eon::ViewEventMessage* pMessage, efd::Category);

    void HandleDiscoveryRequestMsg(const eon::DiscoveryRequest *pMsg, efd::Category targetChannel);

    void HandleOwnedEntityAdded(const egf::EntityChangeMessage* pMsg, efd::Category targetChannel);

    void HandleOwnedEntityUpdated(
        const egf::EntityChangeMessage* pMsg,
        efd::Category targetChannel);

    void HandleOwnedEntityRemoved(
        const egf::EntityChangeMessage* pMsg,
        efd::Category targetChannel);

    void HandleNetIDAssigned(
        const efd::AssignNetIDMessage* pAssignNetIDMessage,
        efd::Category targetChannel);

    /**
        Message handler for AssetLoadResponse messages. When we discover a new entity, we use
        the EntityManager::CreateEntity to factory the entity in the background. This handler
        is called once the factory completes.
    */
    void HandleAssetLoadResponse(
        const efd::AssetLoadResponse* pMsg,
        efd::Category targetChannel);

    /**
        Apply any pending discovery, update or loss messages to the specified entity.
        This is called after async entity creation is complete but before discovery is called.
        @param pReplicant The entity to apply updates to.
        @return True if the entity still exists after all messages have been applied.
    */
    bool ApplyReplicationMessages(ReplicationConsumerEntity* pReplicant);

public:
    // Helper function used by HandleViewBehaviorMsg.  Handles invoking a behavior on an entity
    // in the local cache.
    void QueueBehaviorForReplicatedEntity(
        egf::EntityID entityID,
        const egf::EventMessage* pEvent);

private:
    // A factory method that we plug into the FlatModelManager in client-server settings so that
    // our derived entity types are created.
    static egf::EntityPtr EntityFactory(
        const egf::FlatModel* i_pModel,
        egf::EntityID i_eid,
        bool i_master);

protected:

    // Process an entity loss message for a replicated entity.
    void EntityLossUpdateFromMessage(
        eon::ReplicationConsumerEntity* pEntityReal,
        const eon::EntityMessage* pMsg);

    /// Helper for calling MessageService::BeginCategoryProduction when needed
    void BeginCategoryProduction(efd::Category newCat, efd::QualityOfService qos);

    /// Helper for calling MessageService::EndCategoryProduction when needed
    void EndCategoryProduction(efd::Category oldCat);

    /// Cached reference to the EntityManager
    egf::EntityManagerPtr m_spEntityManager;

    /// The channel I listen to.  People can send this specific instance of the ReplicationService
    /// a message using this ID.
    efd::Category m_myPrivateCategory;

    /// cached pointer to the message service
    efd::MessageServicePtr m_spMessageService;

    /// ptr to our scheduler (to execute behaviors of our replications)
    egf::Scheduler* m_pScheduler;

    // message counts
    int m_discoveryMsg;
    int m_updateMsg;
    int m_lossMsg;

    /// Map of Category to refcount. Lets us keep track of which replication categories are
    /// currently subscribed
    efd::map<efd::Category, efd::UInt32> m_subscriptionMap;

    /// Map of Category to Refcount, lets us keep track of which replication channels we are
    /// producing into.
    efd::map<efd::Category, efd::UInt32> m_productionMap;

    typedef efd::RefCountedMemObj<efd::set<eon::ReplicationConsumerEntityPtr> > EntityList;
    typedef efd::SmartPointer<EntityList> EntityListPtr;

    typedef efd::map<efd::Category, EntityListPtr> CategoryToEntityListMap;

    CategoryToEntityListMap m_categoryToEntityListMap;

    /// Data type for the CategoryChangesMap
    struct CategoryChange
    {
        CategoryChange(efd::Category oldCat, efd::Category newCat);

        efd::Category m_old;
        efd::Category m_new;
    };
    /// Storage for category changes resulting from ChangeReplicationGroup calls
    typedef efd::map<efd::UInt32, CategoryChange> CategoryChangesMap;

    /**
        State for changes to replication producer entities including dirty groups and subscription
        changes.
    */
    class ReplicationAction
    {
    public:
        /// Constructor
        ReplicationAction();

        /// Called when the local owned entity changes replication groups after being added.
        /// Could happen in the same tick we were added or happen multiple times in a tick.
        void OnChangeCategory(efd::UInt32 group, efd::Category oldCat, efd::Category newCat);

        /// Called when the local owned entity is changed. In response we will check the various
        /// replication policies to determine when to update the dirty group.
        void OnDirty(efd::UInt32 groups);

        /// When an update message is sent for a given entity on a given replication group we
        /// clear the dirtiness by calling this.
        void ClearDirtyGroup(efd::UInt32 groupIndex);

        /// Clear all dirtiness for the entity.
        void ClearAllDirtyGroups();

        /// Resets all the replication category related data. Called during OnTick after we have
        /// figured out what discover and loss messages need to be sent.
        void ResetCategoryData();

        /// The per-entity dirtiness of each group. In addition there is per-property dirtiness
        /// that is stored in ReplicationProducerEntity.
        efd::UInt32 m_dirty;

        /// All of the category changes that have been made this tick for a given entity.
        CategoryChangesMap m_catChanges;
    };

    /// A map from entity pointers to replication actions. The key is a smart pointer because even
    /// if the original entity is deleted we need to hold onto it long enough to send loss messages
    typedef efd::map<eon::ReplicationProducerEntityPtr, ReplicationAction> DirtyReplicatorsMap;

    /// A map with an entry for every entity that is either dirty or has changed replication
    /// categories. These are all the entities that potentially need to send out replication
    /// related messages.
    DirtyReplicatorsMap m_entityChanges;

    /// For remote entity update messages that arrive while we are asynchronously creating the
    /// entity itself (potentially loading new flat models, etc) we need to queue the messages
    /// until async creation is completed.
    struct PendingCreateData
    {
        efd::SmartPointer<const eon::EntityMessage> m_spEntityMsg;
        efd::UInt32 m_replicationGroupIndex;
    };

    // Keep track of messages received while waiting for the entity creation to complete.
    typedef efd::map<egf::EntityID, efd::list<PendingCreateData> > PendingEntityToDataMap;

    /// A map for entity messages that are awaiting entity creation
    PendingEntityToDataMap m_pendingEntityCreates;
};

/// A smart pointer for the ReplicationService class
typedef efd::SmartPointer<ReplicationService> ReplicationServicePtr;

} // end namespace eon

#include <eon/ReplicationService.inl>

#endif // EE_REPLICATIONSERVICE_H
