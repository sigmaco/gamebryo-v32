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
#ifndef EE_ENTITYMANAGER_H
#define EE_ENTITYMANAGER_H

#include <efd/AssetFactoryManager.h>
#include <efd/AssetLocatorRequest.h>
#include <efd/MessageService.h>
#include <egf/egfLibType.h>
#include <egf/egfSystemServiceIDs.h>
#include <egf/Entity.h>
#include <egf/EntityChangeMessage.h>
#include <egf/EntityID.h>
#include <egf/EntityFactory.h>

namespace egf
{
class EntityFactoryResponse;
class FlatModelFactory;
class EntityPreloadResponse;


/**
    A hash functor for EntityID objects. This allows egf::EntityID to be used in efd::hash_map
    containers.
*/
struct EntityIDHashFunctor
{
    inline size_t operator()(const EntityID key) const;
};

/**
    A cache of all active entities that belong to the local scheduler. Every entity that is
    owned by the local scheduler is placed in the EntityManager. This central ISystemService
    is available throughout the application via the ServiceManager to access these local entities.

    The EntityManager maintains a list of Entities with dirty properties. This dirty list is used
    to generate update messages. This informs  listeners of property changes.
 */
class EE_EGF_ENTRY EntityManager : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EntityManager, efd::kCLASSID_EntityManager, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

protected:
    /// @name Construction and Destruction
    //@{
    /// virtual, non-public destructor.
    virtual ~EntityManager();

public:
    /// Constructor used to create an instance of the EntityManager.
    EntityManager();
    //@}

    // For rapid iteration cases FMM needs to be able to forcefully remove entities in ways that
    // are normally not desired, so it can access the EntityManager::RemoveEntity method:
    friend class FlatModelManager;

public:
    /**
        This typedef creates a pointer map specific to holding
        entities mapped by their Entity IDs.
    */
    typedef efd::hash_map<EntityID, EntityPtr, EntityIDHashFunctor> EntityMap;

    /**
        Asynchronously create a new entity. The provided model name is used to factory a
        FlatModel instance used to construct a new Entity. The specified flat model will be loaded
        if required. Once all of the Entity's initialization related lifecycle events complete, the
        EntityFactoryResponse message is forwarded to the provided callback category. An optional
        ParameterList can be included to pass information to the OnCreate lifecycle event and
        another optional ParameterList can be used to set initial property values prior to OnCreate.

        @note The entity is automatically added to the EntityManager.

        @note You can control whether or not the created entity automatically enters the world
        following the completion of its initial lifecycle behaviors by adding a boolean parameter
        named "AutoEnterWorld" to the pCreationArgs parameter list.

        @param modelName name of the Flat model used to instantiate the entity.
        @param callback optional callback category. An EntityFactoryResponse will be forwarded
            to this category. Do not use kCAT_LocalMessage for this callback category. Doing so
            will result in entity creation failures.
        @param pCreationArgs An optional ParameterList passed as arguments to OnCreate.
        @param pInitialProps An optional ParameterList containing initial property values. These
            values will be applied as soon as the entity is allocated and before the OnCreate
            behavior is invoked.
        @param entityId optional EntityID to assign to the new entity, or kENTITY_INVALID to
            generate a new one. Generally you should never specify the EntityID value unless you
            are recreating a previously existing entity (for example, loading from a save file).
        @param isMaster Typical entities for use in behavior scheduling must be "master" entities.
            Certain test cases and replicated entities in a client-server setting will use
            non-master entities. Generally you should always leave this as true.
        @return EntityID the EntityID assigned to the upcoming created entity, or kENTITY_INVALID
            if the creation failed.
    */
    egf::EntityID CreateEntity(
        const efd::utf8string& modelName,
        const efd::Category& callback = efd::kCAT_INVALID,
        efd::ParameterList* pCreationArgs = 0,
        efd::ParameterList* pInitialProps = 0,
        egf::EntityID entityId = kENTITY_INVALID,
        bool isMaster = true);

    /**
        Add a created entity to this locale cache. I.E. After creating an Entity
        using the EntityFactory (recreate from DB, or create new Entity, or stream
        migrated Entity), add it to this EntityManager so can be referenced by scheduler.

        @param pEntity pointer to created entity.
        @param pParameterList optional ParameterList passed to OnCreate.
        @return bool return true if entity added successfully, false if error.
    */
    virtual bool AddEntity(Entity* pEntity, efd::ParameterList* pParameterList = 0);

protected:
    /**
        Remove the Entity from the EntityManager. This method should not be called directly
        except by OnEntityEndLifecycle(lifecycle_OnDestroy), call DestroyEntity instead.

        @param pEntity pointer to entity requested for removal.
        @return bool return true if entity removed successfully, false if error.
    */
    virtual bool RemoveEntity(Entity* pEntity);

public:
    /**
        Ask the specified Entity to Destroy itself. Valid created entities can not be removed from
        the EntityManager except by being destroyed. If temporary removal of the entity is needed,
        consider using Entity::ExitWorld instead.

        @param pEntity Pointer to the entity to be destroyed.
        @return True if entity destruction was begun, false if error.
    */
    virtual bool DestroyEntity(Entity* pEntity);
    /**
        Ask the specified Entity to Destroy itself. Valid created entities can not be removed from
        the EntityManager except by being destroyed. If temporary removal of the entity is needed,
        consider using Entity::ExitWorld instead.

        @param id The EntityID of the entity to be destroyed.
        @return True if entity destruction was begun, false if error.
    */
    virtual bool DestroyEntity(const EntityID& id);

    /**
        Find an entity given its EntityID.

        @param id reference to an EntityID class instance.
        @return Entity pointer to a locally owned entity or NULL if not found.
    */
    Entity* LookupEntity(const EntityID &id) const;

     /**
        Find an entity given its data file id.  Only entities that are loaded from block files
        will have a DataID set.  The DataID is the identifier that tools use to uniquely label
        all entities. If a block is loaded multiple times this will only the first matching entity
        that is found. No guarantees are made as to which entity will be the first one found.

        @param id reference to an ID128 class instance.
        @return Entity pointer to entity or NULL if not found.
    */
    Entity* LookupEntityByDataFileID(const efd::ID128& id) const;

    /**
        Find all entities with the given data file id. Only entities that are loaded from world
        files will have a DataID set.  The DataID is the identifier that tools use to uniquely
        label all entities.

        @param[in] id reference to an ID128 class instance.
        @param[out] o_results All the entities that were found
        @return The number of entities found.
    */
    efd::UInt32 LookupEntityByDataFileID(const efd::ID128 &id, efd::set<Entity*>& o_results) const;

    /**
        Return number of entities in cached by the EntityManager.

        @return UInt32 number of entities in the cache.
    */
    inline efd::UInt32 GetCount() const;

    /**
        Adds the given entity to the dirty list. This is called automatically by Entity when any
        properties are changed.  Eventually results in an update message being sent (messages
        are sent once per entity per tick).

        @param pEntity pointer to the entity that needs to be added to the dirty list.
    */
    void AddDirty(Entity* pEntity);

    /**
        Removes the given entity from the dirty list.

        @param pEntity pointer to the entity that needs to be removed from the dirty list.
    */
    void ClearDirty(Entity* pEntity);

    /**
        Returns an iterator that can be passed to GetNextEntity in order to enumerate all the
        entities owned by the EntityManager.  The iterator should not be used other than to
        pass it to GetNextEntity.

        @return EntityMap::const_iterator : An iterator for all entities.
    */
    EntityMap::const_iterator GetFirstEntityPos() const;

    /**
        Returns the next entity from the map of entities kept by the EntityManager based on the
        iterator passed in and then moves the iterator to the next item.

        @note: The iterator should not be used directly.

        Repeated calls to GetNextEntity() with the returned iterator will traverse the entire
        entity map.

        @param[in,out] io_pos A reference to an iterator used to index through the map.
            @note that this reference is updated upon each call.
        @param[out] o_pEntity a pointer used to contain the entity or NULL if there are no
            more entities to iterator over.
        @return bool true if there was another entity to return.  When this is true the output
            parameter o_pEntity should point to a valid entity, otherwise the output parameter
            should be set to NULL.
    */
    bool GetNextEntity(EntityMap::const_iterator& io_pos, Entity*& o_pEntity) const;

    /// Typedef for an entity filter function used by a filtered iterator.
    typedef bool (*FilterFunction)(const Entity* i_pEntity, void* i_pParam);

    EntityFactory* m_pEntityFactory;


    /**
        A class for storing entity iteration data.  Created by calling GetFilteredIterator
        and used with GetNextEntity in order to iterate those entities that match the provided
        filter method.
    */
    class FilteredIterator
    {
        friend class EntityManager;

    public:
        /// @name Construction and Destruction
        //@{
        /// Constructor
        inline FilteredIterator(const FilteredIterator& other);
        //@}

        /// Assignment operator taking a FilteredIterator
        inline FilteredIterator& operator=(const FilteredIterator& other);

    protected:
        /// Constructor
        inline FilteredIterator(
            EntityMap::const_iterator iter,
            FilterFunction i_pfn,
            void* i_pParam);

        // Members
        EntityMap::const_iterator m_iter;
        FilterFunction m_pfnFilter;
        void* m_pParam;
    };

    /**
        Returns an iterator that can be passed to GetNextEntity in order to enumerate all the
        entities owned by the EntityManager that match the provided filter function.  The
        iterator should not be used other than to pass it to GetNextEntity.  The filter function
        receives a void pointer which it can use to pass arbitrary context data.

        @param i_pfn A function that is called once for every entity.  Only entities for which
            this function returns true will be returned by GetNextEntity.
        @param i_pParam an arbitrary parameter that is passed to the filter function on every
            call.
        @return FilteredIterator An iterator that also remembers the provided arguments.
    */
    FilteredIterator GetFilteredIterator(
        FilterFunction i_pfn,
        void* i_pParam = NULL) const;

    /**
        Returns the next entity from the map of entities kept by the EntityManager based on the
        iterator passed in and then moves the iterator to the next item.

        @note: The iterator should not be used directly.

        Repeated calls to GetNextEntity() with the returned iterator will traverse the entire
        entity map.

        @param[in,out] io_pos a reference to an iterator used to index through the map.
        @note that this reference is updated upon each call.
        @param[out] o_pEntity a pointer used to contain the entity or NULL if there are no
            more entities to iterator over.
        @return bool true if there was another entity to return.  When this is true the output
            parameter o_pEntity should point to a valid entity, otherwise the output parameter
            should be set to NULL.
    */
    bool GetNextEntity(FilteredIterator& io_pos, Entity*& o_pEntity) const;

    /**
        A callback used by Entity::BeginLifecycle to notify the EntityManager of the entities
        current state.  This base class implementation does nothing in response.

        @param pEntity Pointer to the entity which is starting a lifecycle
        @param lifecycle The entity lifecycle that is beginning
    */
    virtual void OnEntityBeginLifecycle(Entity* pEntity, efd::UInt32 lifecycle);

    /**
        A callback used by Entity::EndLifecycle to notify the EntityManager of the entities
        current state.  This implementation is responsible for notifications concerning the
        lifecycle's used by the base Entity class.

        @param pEntity Pointer to the entity which is finishing a lifecycle
        @param lifecycle The entity lifecycle that is ending
    */
    virtual void OnEntityEndLifecycle(Entity* pEntity, efd::UInt32 lifecycle);

    /**
        Registers a service for entity preloading. When calling PreloadEntityAssets, all registered
        services receive an EntityPreloadRequest message containing the entity in question. All
        such services must respond with an EntityPreloadResponse message before the entity is
        considered "preloaded" and its OnAssetsLoaded behavior invoked, even if the service does
        not know how to preload such an entity.

        Services that wish to participate will receive preload requests on the category returned by
        GetEntityPreloadCategory, and will send preload responses on the category they registered
        with.
        
        The RegisterPreloadService method should be called after OnPreInit has been invoked on
        the entity manager. We recommend that services make this call during their OnInit methods
        and register a service dependency on the EntityManager class.

        Note that preloads already in progress are not affected by the registration of new
        services.

        @param completionCallback Category to receive EntityPreloadResponse messages.
    */
    void RegisterPreloadService(efd::Category completionCallback);

    /**
        Unregisters a service from entity preloading.

        Note that unregistering a service while preloads are in progress may lead to undefined
        behavior.

        @param completionCallback Category no longer to receive EntityPreloadResponse messages.
    */
    void UnregisterPreloadService(efd::Category completionCallback);

    /**
        Instructs registered services to begin preloading entity assets. Once all services have
        completed preloading, the entity's OnAssetsLoaded behavior will run.

        @param pEntity Entity to preload.
    */
    void PreloadEntityAssets(Entity* pEntity);

    /**
        Receives notifications from registered services that an entity has finished preloading its
        assets. The entity's OnAssetsLoaded behavior will run once all registered services have sent
        their responses.
    */
    void HandleEntityPreloadResponse(
        const egf::EntityPreloadResponse* pMessage,
        efd::Category targetChannel);

    /**
        When creating entities asynchronously, this handler is called when the EntityFactory has
        finished loading the entity data.
    */
    void HandleEntityFactoryResponse(
        const egf::EntityFactoryResponse* pMessage,
        efd::Category targetChannel);

    /// Get the category used for Entity Load requests.
    ///
    /// May be called during PreInit or Init.
    efd::Category GetEntityLoadCategory() const;

    /// Returns the EntityFactory instance used by this service.
    ///
    /// Only available after Init.
    egf::EntityFactory* GetEntityFactory() const;

    /**
        Get the category used for Entity Preload requests.

        Preload services subscribe to this category for request messages and return their responses
        on the category they passed to RegisterPreloadService. This method may be called during
        PreInit or Init.
    */
    efd::Category GetEntityPreloadCategory() const;

    /**
        Set the default auto-enter world value for dynamically created entities. The default
        default is to automatically place dynamically created entities into the world.
        @note Entities created from block loading are controlled by the GetDefaultAutoEnterWorld
        method on the BlockLoadParameters class and not this setting.
    */
    void SetDefaultAutoEnterWorld(bool newValue);

private:
    /**
        A factory method that we plug into the FlatModelManager in client-server settings so that
        our derived entity types are created.  Arguments are passed into Entity constructor.

        @param[in] i_pModel Pointer to the model template for the entity.
        @param[in] i_eid The @ref EntityID "entity ID" to assign to the new entity.
        @param[in] i_master True if this entity should be the master copy.
    */
    static egf::EntityPtr EntityFactoryMethod(
        const egf::FlatModel* i_pModel,
        egf::EntityID i_eid,
        bool i_master);

protected:
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::AsyncResult OnInit();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::AsyncResult OnTick();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::AsyncResult OnShutdown();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual const char* GetDisplayName() const;

    /// Helper to send a notification about newly added entities.  Called once the entity
    /// completes the OnCreate behavior, or during AddEntity if there is no OnCreate behavior.
    virtual void SendEntityCreationNotification(Entity* pEntity);

    /// Helper to send a notification about entities that have just entered the world.
    /// Called once the OnEnterWorld behavior completes.
    virtual void SendEntityEnterWorldNotification(Entity* pEntity);

    /// Helper to send a notification about updated entities.  Called from UpdateDirtyEntities
    /// for each entity that has changed.
    virtual void SendEntityUpdateNotification(Entity* pEntity);

    /// Helper to send a notification about entities that have just exited the world.
    /// Called once the OnExitWorld behavior completes.
    virtual void SendEntityExitWorldNotification(Entity* pEntity);

    /// Helper to send a notification about removed entities.  Called from RemoveEntity.  This
    /// shouldn't be called until after the entity has completed its OnDestroy behavior.
    virtual void SendEntityRemovalNotification(Entity* pEntity);

    /// Helper, called once per tick
    void UpdateDirtyEntities();

    /// Helper called to finish entity setup.  Removes entity from the 'new' list and sends the
    /// initial creation notification.
    void FinishEntitySetup(Entity* pEntity);

    /// Helper function for determining if entity preloading was requested
    virtual efd::Bool IsEntityPreloadRequested(const egf::Entity* pEntity) const;

    /// Helper called to warn of stale preload requests
    void SendPreloadWarnings();

    /// Number of ticks we've seen in OnInit
    efd::UInt32 m_tickCount;

    /// Category used for my asset loading responses
    efd::Category m_entityLoadCategory;

    /// For sending dirty messages
    efd::MessageServicePtr m_spMessageService;

    /// The map for the newly created entities owned by this scheduler
    EntityMap m_NewEntityMap;

    /// The map for the fully created entities owned by this scheduler
    EntityMap m_EntityCacheMap;

    /// information about all dirty entities
    EntityMap m_entityDirtyMap;

    /// @name A map from guid to Entity.
    //@{
    typedef EE_STL_NAMESPACE::multimap<
        efd::ID128,
        EntityPtr,
        EE_STL_NAMESPACE::less<efd::ID128>,
        efd::CustomAllocator<EntityPtr> > DataIdToEntityMap;
    typedef EE_STL_NAMESPACE::pair<efd::ID128, EntityPtr> DataIdToEntityMapEntry;
    DataIdToEntityMap m_entityDataIDMap;
    //@}

    /// Cached message sent immediately when entities are added
    EntityChangeMessagePtr m_spOwnedEntityAddedMsg;
    /// Cached message sent immediately when entities enter the world
    EntityChangeMessagePtr m_spOwnedEntityEnterWorldMsg;
    /// Cached message sent immediately when entities are updated
    EntityChangeMessagePtr m_spOwnedEntityUpdatedMsg;
    /// Cached message sent immediately when entities exit the world
    EntityChangeMessagePtr m_spOwnedEntityExitWorldMsg;
    /// Cached message sent immediately when entities are removed
    EntityChangeMessagePtr m_spOwnedEntityRemovedMsg;

    /// Data awaiting a response from the AssetFactoryManager::LoadAsset call. This includes the
    /// callback category and ParameterList parameter passed to CreateEntity.
    struct PendingEntityCreationData
    {
        // Callback category provided in CreateEntity
        efd::Category m_category;

        // ParameterList provided in CreateEntity containing arguments for the OnCreate behavior.
        efd::ParameterListPtr m_pCreationArgs;

        // ParameterList provided in CreateEntity containing initial property values to set after
        // the entity is allocation and before it receives OnCreate.
        efd::ParameterListPtr m_pInitialPropertyValues;

        // EntityFactoryResponse message received from the AssetFactoryManager.
        efd::SmartPointer<const egf::EntityFactoryResponse> m_spFactoryResponse;
    };

    /// Map of EntityID to pending creation data. Used for asynchronous entity creation calls
    /// to know who to callback and the data stream to passed to OnCreate.
    typedef efd::map<egf::EntityID, PendingEntityCreationData> EntityIDPendingDataMap;
    EntityIDPendingDataMap m_entityIdToPendingDataMap;

    // AssetFactoryManager used to load Entities in the background.
    efd::AssetFactoryManagerPtr m_spAFM;

    /// Set of categories used in preloading entity assets.
    efd::set<efd::Category> m_preloadCategories;

    /// Typedef for a multimap of entities to categories.
    typedef EE_STL_NAMESPACE::multimap<egf::Entity*, efd::Category> PreloadMultimap;

    /// Multimap of entities and the preload services they are blocked on
    PreloadMultimap m_preloadingEntities;

    /// Typedef to make iterating over m_preloadingEntities significantly easier.
    typedef PreloadMultimap::iterator PreloadIterator;

    /// Number of ticks to wait before warning of a possible preloading problem
    efd::UInt32 m_preloadWarningThreshold;

    /// Context information for warning of possible preloading problems
    struct PreloadWarningData
    {
        // Tick on which we started preloading the entity
        efd::UInt32 m_tickStarted;

        // Whether we have already warned of the preload blockage.
        // This field is reset every time a preload service responds, so a developer reading the
        // log files can see how many services eventually complete.
        efd::Bool m_warningLogged;
    };

    /// PreloadingWarningData for all preloading entities
    efd::map<egf::Entity*, PreloadWarningData> m_preloadWarnings;

    /// Default value for the auto-enter-world setting on dynamically created entities.
    /// @note Entities created from block loading are controlled by the GetDefaultAutoEnterWorld
    /// method on the BlockLoadParameters class and not this setting.
    bool m_defaultAutoEnterWorld;

    /// Default parameter list passed to entities that don't otherwise have parameters. This passes
    /// the default value of the "auto enter world" parameter.
    efd::ParameterListPtr m_spDefaultOnCreateParams;

    /// Store which entities we are currently removing so that end lifecycle events dont attempt
    /// to remove them redundantly
    efd::list<egf::Entity*> m_entitiesRemovingList;

    /// Indicator of whether we have entered the shutting down phase
    bool m_shuttingDown;
};

/// A smart pointer (reference counting, self deleting pointer) for the EntityManager class.
typedef efd::SmartPointer<EntityManager> EntityManagerPtr;

} // end namespace egf

#include <egf/EntityManager.inl>

#endif // EE_ENTITYMANAGER_H
