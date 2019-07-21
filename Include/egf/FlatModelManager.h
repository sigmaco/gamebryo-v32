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
#ifndef EE_FLATMODELMANAGER_H
#define EE_FLATMODELMANAGER_H

#include <efd/UniversalTypes.h>
#include <efd/utf8string.h>
#include <efd/CriticalSection.h>
#include <egf/FlatModel.h>
#include <efd/GenericFactory.h>
#include <efd/ISystemService.h>
#include <egf/egfSystemServiceIDs.h>
#include <egf/IBuiltinModel.h>
#include <egf/Entity.h>

namespace efd
{
    class AssetLocatorResponse;
    class AssetLoadResponse;
}
namespace egf
{
    class FlatModelFactory;

/**
    The system service for loading and parsing Flat Model files.

    The Flat Model Manager provides services to keep track of the Flat Models
    that are available, and to find, load and parse them on demand.
*/
class EE_EGF_ENTRY FlatModelManager : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(FlatModelManager, efd::kCLASSID_FlatModelManager, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// Constructor
    FlatModelManager();

    /**
        Enumerated possible results for loading a flat model file.
    */
    enum LoadResult
    {
        OK,
        AlreadyLoaded,
        ModelFileNotFound,
        ParseError
    };

    /// @name Model methods
    //@{

    /**
        Creates a parser, adding each model to the data structures of this class.  You must
        specify the complete filename with any required path information.

        @param modelFile Full filename to load the model data from
        @param[out] o_pModel Output smart pointer to the Flat Model object
    */
    virtual LoadResult ParseModelFile(
        const efd::utf8string& modelFile,
        FlatModelPtr& o_pModel);

    /**
        Creates a parser, adding each model to the data structures of this class.  You pass
        just the model name and the correct path and file extension are added to form the
        full file name to load.

        @param modelName The model name to load
        @param[out] o_pModel Output smart pointer to the Flat Model object
    */
    virtual LoadResult ParseModel(
        const efd::utf8string& modelName,
        FlatModelPtr& o_pModel);

    /**
        Creates a parser to load a single model file.

        @param modelFile Full filename to load the model data from
        @return LoadResult value depending on the outcome. @see enum LoadResult
    */
    virtual LoadResult LoadModelFile(const efd::utf8string& modelFile);

    /**
        Creates a parser to load a single model file.  The correct path and file extension
        for the model is computed using the configuration settings.  If the model already
        exists

        @param modelName The name of the model to load
        @return LoadResult value depending on the outcome. @see enum LoadResult
    */
    virtual LoadResult LoadModel(const efd::utf8string& modelName);

    /**
        Finds a flat model that has already been added

        @param i_id The FlatModelID of the model to find
        @return A pointer to the flat model.
    */
    const FlatModel* FindModel(FlatModelID i_id) const;

    /**
        Finds a flat model that has already been added

        @param i_name The name of the model to find
        @return A pointer to the flat model.
    */
    const FlatModel* FindModel(const efd::utf8string& i_name) const;

    /**
        @deprecated Use PreloadModel if you need to load a model at runtime, or use FindModel if
        you need the FlatModel object for a previously loaded model.

        Finds a flat model.  If the model doesn't exist it will attempt to load it.

        This function is only needed by applications that do not utilize the AssetFactoryManager,
        which generally would include only unit tests, servers, or tools that do not include graphical
        rendering functionality. A game application should not call this function because it is
        synchronous and will block rendering.

        @param i_name The name of the model to find
        @return A pointer to the flat model.
    */
    virtual const FlatModel* FindOrLoadModel(const efd::utf8string& i_name);

    /**
        Lookup the name of a model given its ID

        @param i_id The FlatModelID of the model to find
        @param i_bCheckMixins True to also check mix-in models
        @return utf8string The name of the flat model.
    */
    const efd::utf8string& GetModelNameByID(FlatModelID i_id, bool i_bCheckMixins = true) const;

    /**
        Lookup the ID of a model given its name

        @param i_name The name of the model to find
        @param i_bCheckMixins True to also check mix-in models
        @return FlatModelID the ID of the flat model. kFlatModelID_INVALID if model is not found.
    */
    FlatModelID GetModelIDByName(const efd::utf8string& i_name, bool i_bCheckMixins = true) const;

    /**
        Register a "name->id" mapping for a model that is mixed in but might not be loaded.
        You can then lookup the ID using GetModelIDByName.

        This method may be called during PreInit or Init.

        @param i_name The name of the model
        @param i_id The id of the model
        @return bool True if the name and ID don't conflict.
    */
    bool RegisterMixin(const efd::utf8string& i_name, FlatModelID i_id);

    /**
        Preload a flat model independent of .xblock loading. This makes the model available
        for use even if the model is not loaded as part of an entity or world load. The provided
        callback will receive an AssetLoadResponse once the load completes. The act of
        preloading an model also calculates and load dependent mixin flat models and Lua
        behavior scripts.

        @param modelName Name of the model to preload.
        @param callback Category to forward the AssetLoadResponse message to.
    */
    void PreloadModel(
        const efd::utf8string& modelName,
        const efd::Category& callback = efd::kCAT_INVALID);

    /**
        Preload a set of flat model files bassed on the given URN. All flat model files that
        match the URN are preloaded. The caller can provide a callback category, which receives
        an AssetLoadResponse for each located flat model that was preloaded.

        @see PreloadModel for further details.

        @param urn URN of the flat models to preload.
        @param callback Category to forward the AssetLoadResponse messages to.
    */
    void PreloadModels(
        const efd::utf8string& urn,
        const efd::Category& callback = efd::kCAT_INVALID);

    //@}

    /// @name Property methods
    //@{

    /**
        Factories a new property.

        @param classID the ClassID of the property being created.
        @return An IProperty pointer of the newly created property.
    */
    IProperty* FactoryProperty(efd::ClassID classID);

    typedef efd::GenericFactory<IProperty*> PropertyFactory;

    /**
        Register a factory method for a property.

        May be called during PreInit or Init.

        @param classID The ClassID of the property to register.
        @param name The name of the property to register.
        @param pfn The method to call to factory the property
        @return True if there are no errors
    */
    bool RegisterPropertyFactory(
        const efd::utf8string& name,
        efd::ClassID classID,
        PropertyFactory::FactoryMethod pfn);

    /**
        Mappings between the property type names and the class ID of the implementation.
        The various IProperty implementations each have unique names that are used in various
        data files like Flat Models as the property type.  So, for example, we have the "UInt32"
        property type which matches the UInt32ScalarProperty class.  New types are adding by
        calling the RegisterPropertyFactory method.

        @param i_id Class Id of Type whose name is to be retrieved
    */
    const efd::utf8string& GetTypeNameByID(efd::ClassID i_id) const;

    /**
        Mappings between the property type names and the class ID of the implementation.
        The various IProperty implementations each have unique names that are used in various
        data files like Flat Models as the property type.  So, for example, we have the "UInt32"
        property type which matches the UInt32ScalarProperty class.  New types are adding by
        calling the RegisterPropertyFactory method.

        @param i_name Name of Type whose ID is to be retrieved
    */
    efd::ClassID GetTypeIDByName(const efd::utf8string& i_name) const;

    /**
        Map specific property names to their property IDs.  Every property created in all the
        data files for a given project will have unique IDs.  EMT assigns these IDs when the
        properties are created.

        @param i_id Class Id of Property whose name is to be retrieved
    */
    const efd::utf8string& GetPropertyNameByID(PropertyID i_id) const;

    /**
        Map specific property names to their property IDs.  Every property created in all the
        data files for a given project will have unique IDs.  EMT assigns these IDs when the
        properties are created.

        @param i_id Class Id of Property whose name is to be retrieved
        @param o_name The resulting name if found, unchanged otherwise.
        @return True if the property ID was valid.
    */
    bool GetPropertyNameByID(PropertyID i_id, efd::utf8string& o_name) const;

    /**
        Map specific property names to their property IDs.  Every property created in all the
        data files for a given project will have unique IDs.  EMT assigns these IDs when the
        properties are created.

        @param i_name Name of Property whose ID is to be retrieved
    */
    PropertyID GetPropertyIDByName(const efd::utf8string& i_name) const;

    //@}

    /// @name Built-in Model methods
    //@{

    /**
        Factories a new built-in model.

        @param i_strBuiltinName the name of the built-in model being created.
        @return IBuiltinModel* : An IBuiltinModel pointer of the newly created property.
    */
    IBuiltinModel* FactoryBuiltinModel(const efd::utf8string& i_strBuiltinName);

    /**
        Factories a new built-in model.

        @param i_builtinID the model ID of the built-in model being created.
        @return IBuiltinModel* : An IBuiltinModel pointer of the newly created property.
    */
    IBuiltinModel* FactoryBuiltinModel(FlatModelID i_builtinID);

    typedef efd::GenericFactory<IBuiltinModel*> BuiltinModelFactory;

    /**
        Register a factory method for a built-in model.

        May be called during PreInit or Init.

        @param i_strName The name of the built-in model to register.
        @param compID The ID of the built-in model.
        @param pfn The method to call to factory the built-in model.
        @param i_priority Set priority (future use)
        @return True if there are no errors
    */
    bool RegisterBuiltinModelFactory(
        const efd::utf8string& i_strName,
        FlatModelID compID,
        BuiltinModelFactory::FactoryMethod pfn,
        efd::SInt32 i_priority = 0);

    /**
        Map specific built-in model names to their built-in model IDs.

        @param i_id Model Id of the built-in model whose name is to be retrieved
    */
    const efd::utf8string& GetBuiltinModelNameByID(FlatModelID i_id) const;

    /**
        Map specific built-in model names to their built-in model IDs.

        @param i_name Name of the built-in model whose Model ID is to be retrieved
    */
    FlatModelID GetBuiltinModelIDByName(const efd::utf8string& i_name) const;

    //@}

    /// @name Behavior methods
    //@{

    /**
        Map specific behavior names to their behavior IDs.  Every behavior created in all the
        data files for a given project will have unique IDs.  EMT assigns these IDs when the
        behaviors are created.

        @param i_id Class Id of Behavior whose name is to be retrieved
    */
    const efd::utf8string& GetBehaviorNameByID(BehaviorID i_id) const;

    /**
        Map specific behavior names to their behavior IDs.  Every behavior created in all the
        data files for a given project will have unique IDs.  EMT assigns these IDs when the
        behaviors are created.

        @param i_name Name of Behavior whose ID is to be retrieved
    */
    BehaviorID GetBehaviorIDByName(const efd::utf8string& i_name) const;

    //@}

    /// @name Entity creation methods
    //@{

    /**
        Factories a new entity based on the given FlatModel. This method should be avoided when
        creating new entities outside of Game Framework classes. Instead
        egf::EntityManager::CreateEntity should be used to create new  entities.  The
        Entity::CreateBuiltinModels method will be called on this entity after it is
        allocated using the EntityFactoryMethod.

        @param i_strModelName The name of the flat model to use.  This convenience method
            will look up the FlatModel* and call the pointer method.
            of a particular flat model.
        @param i_eid The entity ID to assign this entity, or kENTITY_INVALID if you want a
            new ID to be generated and assigned to the entity.  Typically new entities are
            automatically assigned IDs when first created and you would only pass in a specific
            ID if you are recreating a previously existing entity, for example after reloading
            from a saved state.
        @param i_master Typical entities for use in behavior scheduling must be "master"
            entities.  Certain test cases and replicated entities in a client-server setting
            will use non-master entities.  Typically you should always leave this as true.
        @return EntityPtr A newly allocated entity.

        @deprecated Entity creation is asynchronous; factorying them directory is discouraged.
            Instead use egf::EntityManager::CreateEntity.
    */
    EntityPtr FactoryEntity(
            const efd::utf8string& i_strModelName,
            egf::EntityID i_eid = egf::kENTITY_INVALID,
            bool i_master = true);

    /**
        Factories a new entity based on the given FlatModel. This method should be avoided when
        creating new entities outside of Game Framework classes. Instead
        egf::EntityManager::CreateEntity should be used to create new  entities.  The
        Entity::CreateBuiltinModels method will be called on this entity after it is
        allocated using the EntityFactoryMethod.

        @param i_modelID The id of the flat model to use.  This convenience method will
            look up the FlatModel* and call the pointer method.
        @param i_eid The entity ID to assign this entity, or kENTITY_INVALID if you want a
            new ID to be generated and assigned to the entity.  Typically new entities are
            automatically assigned IDs when first created and you would only pass in a specific
            ID if you are recreating a previously existing entity, for example after reloading
            from a saved state.
        @param i_master Typical entities for use in behavior scheduling must be "master"
            entities.  Certain test cases and replicated entities in a client-server setting
            will use non-master entities.  Typically you should always leave this as true.
        @return EntityPtr A newly allocated entity.
    */
    EntityPtr FactoryEntity(
        FlatModelID i_modelID,
        egf::EntityID i_eid = egf::kENTITY_INVALID,
        bool i_master = true);

    /**
        Factories a new entity based on the given FlatModel. This method should be avoided when
        creating new entities outside of Game Framework classes. Instead
        egf::EntityManager::CreateEntity should be used to create new  entities.  The
        Entity::CreateBuiltinModels method will be called on this entity after it is
        allocated using the EntityFactoryMethod.

        @param i_pModel The model definition to use.  All entities are the instantiations
            of a particular flat model.
        @param i_eid The entity ID to assign this entity, or kENTITY_INVALID if you want a
            new ID to be generated and assigned to the entity.  Typically new entities are
            automatically assigned IDs when first created and you would only pass in a specific
            ID if you are recreating a previously existing entity, for example after reloading
            from a saved state.
        @param i_master Typical entities for use in behavior scheduling must be "master"
            entities.  Certain test cases and replicated entities in a client-server setting
            will use non-master entities.  Typically you should always leave this as true.
        @return EntityPtr A newly allocated entity.

    */
    EntityPtr FactoryEntity(
        const FlatModel* i_pModel,
        egf::EntityID i_eid = egf::kENTITY_INVALID,
        bool i_master = true);

    //@}

    /// @name Entity factory registration methods
    //@{

    /// Function signature for the Entity factory method.  This method should simply allocate
    /// the Entity, it does not need to perform any other initialization steps.  Once allocated
    /// the factory method will construct the entity by calling the virtual Construct method.
    typedef EntityPtr (*EntityFactoryMethod)(
            const FlatModel* i_pModel,
            egf::EntityID i_eid,
            bool i_master);

    /**
        Register the entity factory.

        There is a single entity factory used to allocate all entities.  The default factory
        will simply allocate.

        May be called during PreInit or Init.
    */
    bool RegisterEntityFactory(
        EntityFactoryMethod pfn,
        efd::SInt32 i_priority = 0);

    //@}


    /**
        Update a location for a model file. This is used when a change notify message
        from the Asset Server informs of a new model file at run-time.

        @param model The name of the model
        @param path The full path for the model file
    */
    void UpdateModelLocation(const efd::utf8string& model, efd::utf8string& path);

    /**
        Externally set a specific file system path to be used for locating model files.

        May be called during PreInit or Init.

        @param fullPath Full file system path containing model files
    */
    inline void SetModelPath(const efd::utf8string& fullPath);

    /// @name Accessors to return data that may be gathered from the config manager
    //@{
    const efd::utf8string& GetModelPath() const;
    const efd::utf8string& GetModelFileExt() const;
    //@}

    /// Adds a model to this class's data structures
    bool AddModel(FlatModelPtr model);

    /**
        ReloadModel will do a live update of an already loaded model.

        This includes updating any existing entities that are currently using that model.
        If the model in question is not already loaded then this method does nothing since
        the correct model should be loaded.

        @param modelName Name of the model to reload
    */
    bool ReloadModel(const efd::utf8string& modelName);

    /**
        Remove a model from the maps of loaded models. Any Entity instances currently using this
        model will continue to reference it but new FactoryEntity requests with this model will
        fail. The model can be reloaded by calling PreloadModel or EntityManager::CreateEntity.

        @note Should a rapid iteration request arrive changing this model it will no longer update
        any remaining entities using the removed model. As a result, it is recommended this API
        only be called if there are no entities of the given model type or if rapid iteration is
        not enabled.

        @param pModel Pointer to the model to remove.
    */
    bool RemoveModel(const FlatModel* pModel);

    /// Helper function to clean out and reset all model maps for rapid-iteration
    void CleanModelMaps();

    /// ReloadAllModels will do a live update of every model already loaded.
    bool ReloadAllModels(bool fromToolbench = true);

    /// ResetFlatModelRequest will clean out the model maps and location maps followed by
    /// a request for all "urn:emergent-flat-model".
    void ResetFlatModelRequest();

    /// Tells whether the flat model manager is available to accept a request.
    inline bool IsAvailable();

    /**
        Returns the official instance of egf::FlatModelFactory.

        We own one so that multiple factory instances don't overwrite each other's asset-loader
        message registrations.
    */
    egf::FlatModelFactory* GetFlatModelFactory() const;

protected:
    /// Destructor
    virtual ~FlatModelManager();

    /// @name ISystemService methods
    //@{
    /**
        Prepare for OnInit.

        Configuration options are read. The PlaceableModel built-in model is registered.
        Message categories are created and subscribed to.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        Complete initialization.

        The FlatModelmanager servcie waits for various loading and script services to
        complete initialization. If available, the AssetFactoryManager is given the
        FlatModelFactory for loading flat models and this method returns efd::AsyncResult_Complete.

        When no AssetFactoryManager is available, the service performs an asset locate request
        for all of the flat models known to the asset locator. In this case, OnInit does not return
        efd::AsyncResult_Complete until the flat model locate has completed. The scheduler is
        paused during this process.
    */
    virtual efd::AsyncResult OnInit();

    /// This method does nothing.
    virtual efd::AsyncResult OnTick();

    /// Clean up registered objects and message subscriptions.
    virtual efd::AsyncResult OnShutdown();

    /// Return the the name of the service, in this case "FlatModelManager".
    inline const char* GetDisplayName() const;
    //@}

    /// Helper to register all the primitive property types.
    void RegisterPrimitivePropFactories();

    /// Helper to register all the utility property types.
    void RegisterUtilityPropFactories();

    /// Helper to read all the ini settings from the ConfigManager
    void ReadConfigOptions();

    /// Reload a model based on changes to the original loaded model
    bool ReloadModel(FlatModel* pOriginalModel, bool fromToolbench);

    /// Get the path for a given model using the cached data from the asset manager
    efd::utf8string GetPathForModel(const efd::utf8string& modelName);

    // Compare the old and new flat model and update entities appropriately.
    bool ProcessReload(egf::FlatModel* pOriginalModel, egf::FlatModel* pNewModel);

    /// @name Rapid Iteration Support
    /// Methods for managing the entities that have been created.
    ///@{
    void DeleteEntities(efd::list<egf::EntityPtr>& i_entities);

    /// Adds a list of entities to the entity manager; for RI.
    void AddEntities(efd::list<egf::EntityPtr>& i_entities);

    /// Reinitialises a list of entities; for RI.
    void ReinitializeEntities(efd::list<egf::EntityPtr>& i_entities);

    /// Update the list of entities to the new model.
    void UpdateEntities(
        const efd::list<egf::EntityPtr>& i_entities,
        const egf::FlatModel* pOldModel,
        const egf::FlatModel* pNewModel);

    ///@}

    /**
        Registers the behavior name/ID for use in the model system.  Every behavior name is
        associated with a single unique ID for an entire project.

        @param[in] i_strName The name of the behavior to register.
        @param[in] i_behaviorID The ID to associate with the name.
        @return True if a mapping was added
    */
    bool RegisterBehaviorName(const efd::utf8string& i_strName, BehaviorID i_behaviorID);

    /// Forward a an AssetLoadResponse to any listeners during preload.
    void ForwardPreloadResponse(const efd::AssetLoadResponse* pMsg);

    /// @name map of all flat model names to their load paths
    //@{
    typedef efd::map<efd::utf8string, efd::utf8string> FlatModelLocationMap;
    //@}

    /// @name map of all flat models indexed by ID
    //@{
    typedef efd::map<FlatModelID, FlatModelPtr> FlatModelMapByID;
    //@}

    /// @name map of all flat models indexed by model name
    //@{
    typedef efd::map<efd::utf8string, FlatModelPtr> FlatModelMapByName;
    //@}

    /**
     @name JIT load model mapping
     When we JIT load models we do not load all the models they mix in but we still need
     to be able to do "model name"->"id" mappings on those models.  So we keep a separate
     mapping of just that info.
    */
    //@{
    typedef efd::map<FlatModelID, efd::utf8string> MixinNameByIdMap;
    typedef efd::map<efd::utf8string, FlatModelID> MixinIDByNameMap;
    //@}

    /**
     @name Property/name consistency mapping
     All models must use consistent names and IDs for the properties they contain.  To
     verify this restriction we maintain mappings for all property names and IDs used.
    */
    //@{
    typedef efd::map<const efd::utf8string, PropertyID> PropNameToIdMap;
    typedef efd::map<PropertyID, efd::utf8string> PropIdToNameMap;
    //@}

    /// @name map to convert string text names found in the XML file to the corresponding class ID.
    //@{
    typedef efd::map<efd::utf8string, efd::ClassID> PropTypeNameToIdMap;
    typedef efd::map<efd::ClassID, efd::utf8string> PropTypeIdToNameMap;
    //@}

    /// the property factory
    PropertyFactory m_propertyFactory;

    /// @name map to convert string text names found in the XML file to the corresponding class ID.
    //@{
    typedef efd::map<const efd::utf8string, FlatModelID> CompNameToIdMap;
    typedef efd::map<FlatModelID, efd::utf8string> CompIdToNameMap;
    //@}

    /// @name map to convert string text names found in the XML file to the corresponding class ID.
    //@{
    typedef efd::map<const efd::utf8string, BehaviorID> BehNameToIdMap;
    typedef efd::map<BehaviorID, efd::utf8string> BehIdToNameMap;
    //@}


    struct FlatModelMetadata
    {
        FlatModelLocationMap m_flatModelLocations;
        FlatModelMapByID m_flatModelsByID;
        FlatModelMapByName m_flatModelsByName;
        MixinNameByIdMap m_mixinNameById;
        MixinIDByNameMap m_mixinIdByName;
        PropNameToIdMap m_mapPropNameToId;
        PropIdToNameMap m_mapPropIdToName;
        PropTypeNameToIdMap m_mapPropTypeNameToId;
        PropTypeIdToNameMap m_mapPropTypeIdToName;
        CompNameToIdMap m_mapCompNameToId;
        CompIdToNameMap m_mapCompIdToName;
        BehNameToIdMap m_mapBehNameToId;
        BehIdToNameMap m_mapBehIdToName;
    };

    FlatModelMetadata m_metadata;
    mutable efd::CriticalSection m_metadataLock;

    /// the built-in model factory
    BuiltinModelFactory m_builtinModelFactory;

    // Lock to prevent multiple threads from factoring entities simultaneously.
    efd::CriticalSection m_factoryLock;

    efd::utf8string m_modelPath;
    efd::utf8string m_modelFileExt;

    bool m_asset_lookup_in_progress;
    bool m_asset_lookup_complete;
    /// Category used for my asset lookup responses
    efd::Category m_callback;

    /// Category used when preloading a set of flat models by URN.
    efd::Category m_preloadLookupCategory;

public:
    /// @cond EMERGENT_INTERNAL
    void HandleAssetLookupMsg(
        const efd::AssetLocatorResponse* pMessage,
        efd::Category targetChannel);

    void HandleAssetLoadMsg(
        const efd::AssetLoadResponse* pMessage,
        efd::Category targetChannel);
    /// @endcond

protected:
    // mapping of pending preload model URN to callback categories.
    typedef efd::map<efd::utf8string, efd::set<efd::Category> > PendingPreloadMap;
    PendingPreloadMap m_pendingPreloads;

    EntityFactoryMethod m_pfnEntityFactory;
    efd::SInt32 m_entityFactoryPriority;

    FlatModelFactory* m_pFlatModelFactory;

    bool m_loadedPrimTypes;
    bool m_loadedUtilTypes;
};


typedef efd::SmartPointer<FlatModelManager> FlatModelManagerPtr;


} // end namespace egf

#include <egf/FlatModelManager.inl>

#endif // EE_FLATMODELMANAGER_H
