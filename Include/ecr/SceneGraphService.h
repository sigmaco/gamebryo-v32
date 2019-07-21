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
#ifndef EE_SCENEGRAPHSERVICE_H
#define EE_SCENEGRAPHSERVICE_H

#include "ecrLibType.h"

#include <egf/EntityManager.h>
#include <egf/EntityID.h>
#include <efd/ISystemService.h>
#include <efd/MessageHandlerBase.h>
#include <efd/StreamMessage.h>
#include <efd/AssetFactoryManager.h>
#include <egf/EntityChangeMessage.h>
#include <egf/EntityLoaderMessages.h>
#include <egf/PlaceableModel.h>

#include <ecr/ecrSystemServiceIDs.h>
#include <ecr/AttachNifData.h>
#include <ecr/MeshModel.h>
#include <ecr/RenderableModel.h>
#include <ecr/SceneGraphCache.h>
#include <ecr/SceneGraphCacheResponse.h>

#include <NiNode.h>
#include <NiSPWorkflowManager.h>
#include <NiTexturePalette.h>
#include <NiBatchedUpdateProcess.h>

class NiUpdateProcess;

namespace ecr
{

class RenderService;

/**
    The scene graph service is responsible for managing all the Gamebryo scene graphs that
    are in the system.

    Scene graphs come from a variety of sources. Most of the scene graphs are loaded for entities
    that have the NifAsset property, for use as rendered geometry. Other services may also
    provide scene graphs that have been loaded (such as the Animation Service) or
    created in code (such as the Light Service). Functions are provided for such services to
    register the scene graph with this service.

    The scene graph service registers with entity lifetime messages so the scene graphs
    associated with entities are automatically loaded and prepared for rendering. It also registers
    for property update messages on entities, and applies relevant property changes to the scene
    graphs.

    The scene graph service requires that a efd::MessageService object be available at the
    time the SceneGraphService object is added to the ServiceManager. Hence, the Message Service
    must be registered before the Scene Graph Service.
*/
class EE_ECR_ENTRY SceneGraphService :
    public efd::ISystemService,
    public egf::IPropertyCallback
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SceneGraphService, efd::kCLASSID_SceneGraphService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:

    /// A type for referring to entity-less scene graphs.
    typedef efd::UInt32 SceneGraphHandle;

    /// Invalid scene graph handle.
    static const SceneGraphHandle kInvalidHandle;

    /**
        Constructor.

        The constructor prepares data structures for scene graph updating and texture sharing.

        @param pWorkflowManager The workflow manager used to coordinate Floodgate task submission.
            If NULL, the service creates its own workflow manager. In general,
            all services should use the same workflow manager if they are operating in the
            same thread, or one manager per-thread otherwise.
        @param pTexturePalette The texture palette is used to facilitate texture sharing.
            The service will create a default palette if one is not provided in this constructor.
            The palette is stored as a smart pointer, so applications must not explicitly
            delete it.
        @param toolMode If true, loaded scene graphs will have all data streams set with CPU
            read access, thus supporting picking on all models.
    */
    SceneGraphService(
        NiSPWorkflowManager* pWorkflowManager = NULL,
        NiTexturePalette* pTexturePalette = NULL,
        const efd::Bool toolMode = false);

    /**
        Destructor.

        Cleans up any scene graph data that wasn't destroyed as a part of the
        service shutting down.
    */
    virtual ~SceneGraphService();

    /// Get the workflow manager used by this service for updating scene graphs.
    ///
    /// This method may be called during PreInit.
    inline NiSPWorkflowManager* GetWorkflowManager() const;

    /**
        Get the texture palette used by this service.

        The returned value should be assigned to a smart pointer. This method may be called
        during PreInit.
    */
    inline NiTexturePalette* GetTexturePalette() const;

    /**
        Get the Scene Graph Cache used by this service.

        The cache is necessary to look up data related to SceneGraphCache::SceneGraphCacheHandle
        objects. This method may be called during PreInit.
    */
    inline SceneGraphCache* GetSceneGraphCache() const;

    /**
        Return the name of the service, in this case "SceneGraphService".
    */
    virtual const char* GetDisplayName() const;

    /**
        OnPreInit subscribes to messages and reads configuration options.

        It also registers the factories for several property types and built-in models
        that are used by the service.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        OnInit sets internal pointers to other services and registers for messages.
    */
    virtual efd::AsyncResult OnInit();

    /**
        This method will update all dynamic scene graphs currently being managed.

        Note, this does not imply the scene graphs are rendered.
    */
    virtual efd::AsyncResult OnTick();

    /**
        Shuts down the scene graph service.

        All in-memory scene graphs are destroyed.
    */
    virtual efd::AsyncResult OnShutdown();

    /**
        @name Entity Scene Graph Functions
    */
    //@{
    /**
        Create a new scene graph for the given entity from the asset with the specified asset ID.

        The urn in the asset ID is passed to the Asset Locator Service, if available, for
        resolution to a file name on disk. The urn is treated as an explicit file name when
        no asset locator is registered, in which case the function CreateSceneGraphFileName
        is called by this function.

        The scene graph may be loaded asynchronously. The caller of this function should look
        for an ecr::SceneGraphAdded message, which will be sent when the scene graph is
        loaded and available. No message will be sent if the scene graph fails to load.

        @param pEntity The Entity to which the new scene graph is assigned.
        @param assetID The asset ID for the asset.
        @param delayInWorld When true, the object will not be added to the renderer or updated,
            regardless of any properties on the entity, and must be explicitly activated for
            rendering using DisplayEntity.
        @param forceSharing If true, the scene graph will be shared instead of reloaded from disk
            regardless of whether or not the entity requested sharing.
        @param updatePose When true, the Scene Graph Service will manage pose updates
            for the entity. When the Placeable model notifies the service of a pose
            change it is applied to the scene graph. If false, Placeable callbacks will not
            be applied for this entity.
        @return True if the scene graph was successfully requested or created, otherwise false.
    */
    virtual efd::Bool CreateSceneGraphAssetID(
        egf::Entity* pEntity,
        const efd::AssetID& assetID,
        const efd::Bool delayInWorld = false,
        const efd::Bool forceSharing = false,
        const efd::Bool updatePose = true);

    /**
        Create a scene graph direct from the file name.

        The scene graph may be loaded asynchronously. The caller of this function should look
        for an ecr::SceneGraphAdded message, which will be sent when the scene graph is
        loaded and available. No message will be sent if the scene graph fails to load.

        @param pEntity The Entity to which the new scene graph is assigned.
        @param fileName File location for the scene graph.
        @param prependDataPath The file name is used as is if this parameter is false. If true,
            the path returned by GetDataPath is prepended to the given file name.
        @param delayInWorld When true, the object will not be added to the renderer or updated,
            regardless of any properties on the entity, and must be explicitly activated for
            rendering using DisplayEntity.
        @param forceSharing If true, the scene graph will be shared instead of reloaded from disk
            regardless of whether or not the entity requested sharing.
        @param updatePose When true, the Scene Graph Service will manage pose updates
            for the entity. When the Placeable model notifies the service of a pose
            change it is applied to the scene graph. If false, Placeable callbacks will not
            be applied for this entity.
        @return True if the asset could be located and requested, otherwise false.
    */
    efd::Bool CreateSceneGraphFileName(
        egf::Entity* pEntity,
        const efd::utf8string& fileName,
        const efd::Bool prependDataPath,
        const efd::Bool delayInWorld = false,
        const efd::Bool forceSharing = false,
        const efd::Bool updatePose = true);

    /**
        Creates a new scene graph entry mapped to the specified entity id.

        The Scene Graph Service will manage Add/Remove messaging and rendering of the
        given objects.

        The scene graph added in this way does not have its asset data managed by the service,
        nor does the service process an property updates. The service only calls
        NiAVObject::Update on the scene graph when the callUpdate parameter is true.
        It is assumed that the above functionality is provided through another service or
        mechanism.

        An ecr::SceneGraphAdded message is sent when the scene graph is added.

        @param pEntity The Entity to which the scene graph is assigned.
        @param objects List of scene graph objects to map to the specified entity ID.
        @param callUpdate The service will only call NiAVObject::Update on the scene graph when
            this parameter is true.
        @param delayInWorld When true, the object will not be added to the renderer, regardless of
            any properties on the entity, and must be explicitly activated for rendering using
            DisplayEntity.
        @return True if successful, false otherwise.

        @note This method of entity-scenegraph registration is useful for other services that have
            ownership of the entity, but rely on the scene graph service for managing display
            of the underlying scene graph data.
    */
    virtual efd::Bool CreateExternalSceneGraph(
        egf::Entity* pEntity,
        efd::vector<NiObjectPtr>& objects,
        const efd::Bool callUpdate,
        const efd::Bool delayInWorld = false);

    /**
        Update properties on an entity that has been newly discovered, in case those properties
        have changed since the entity was created.

        This should be called by the Entity Enter World handler of any service that creates
        scene graphs from entities. Entity Update messages are not sent if properties change
        between the time the scene graph is created and the time the Entity Enter World is
        sent out. This method updates all properties that may have changed during this time.
    */
    virtual void UpdateDiscoveredEntity(egf::Entity* pEntity);

    /**
        Recreate the scene graph for a given entity from the specified location.

        Look for an ecr::SceneGraphRemovedMessage followed by an ecr::SceneGraphAddedMessage
        for the entity, on the kCAT_LocalMessage channel. These messages will not be sent when
        the scene graph in question (the original or the new one) is empty. Applications
        can rely on only receiving ecr::SceneGraphRemoved messages for scene graphs that
        also generated ecr::SceneGraphAdded messages.

        @param pEntity The Entity to which the new scene graph is assigned.
        @param sceneGraphAssetID Asset location for the scene graph file to load.
        @return True if the scene graph was successfully recreated, false if it needed to be
            loaded from disk.
    */
    virtual efd::Bool RecreateSceneGraph(
        egf::Entity* pEntity,
        const efd::AssetID& sceneGraphAssetID);

    /**
        Remove all scene graphs for a particular entity.

        @param pEntity The Entity to remove the scene graph from.
        @param forceRemoval Forces the removal of the entity's scene graph even if the scene graph
            entity is externally managed.
    */
    virtual void RemoveSceneGraph(egf::Entity* pEntity, efd::Bool forceRemoval = false);

    /**
        Reload the asset at the specified location.

        This function causes all of the entities using this asset to have their scene graph
        objects refreshed. This function assumes that the given asset location was
        previously returned by the asset locator or is otherwise the actual location from which to
        load the asset file.

        Look for an ecr::SceneGraphRemovedMessage followed by an ecr::SceneGraphAddedMessage
        for each entity or handle that uses the asset, on the kCAT_LocalMessage channel. These
        messages will not be sent when
        the scene graph in question (the original or the new one) is empty. Applications
        can rely on only receiving ecr::SceneGraphRemoved messages for scene graphs that
        also generated ecr::SceneGraphAdded messages.

        @param physicalID Asset urn.
        @param nifPath Location of the scene graph file to load.
        @return True if the scene graph was immediately reloaded, otherwise false.
    */
    virtual efd::Bool ReloadAsset(
        const efd::utf8string& physicalID,
        const efd::utf8string& nifPath);

    /**
        Sets the root path used to load scene graph data.

        This method may be called during PreInit.

        @note Only necessary if you will bypass asset manager services.
    */
    inline void SetDataPath(const char* path);

    /**
        Gets the root path used to load scene graph data.

        This method may be called during PreInit.

        @note Only necessary if you will bypass asset manager services.
    */
    inline const NiFixedString& GetDataPath() const;
    //@}

    /**
        @name Iterating Over Scene Graphs
    */
    //@{
    /// A functor class for iterating over all scene graphs with entities.
    EE_ECR_ENTRY class EntitySceneGraphFunctor
    {
    public:
        /**
            Derived classes must implement this operator.

            During scene graph iteration, the operator is called once for every entity
            that has a non-empty scene graph.

            The operator can prevent further iteration by setting the return value.

            @param pEntity The entity to which the scene graph objects belong.
            @param objects The scene graph objects for the entity.
            @return True if iteration should stop, or false if it should continue.
        */
        virtual efd::Bool operator()(
            const egf::Entity* pEntity,
            const efd::vector<NiObjectPtr>& objects) = 0;

        virtual ~EntitySceneGraphFunctor() { }
    };

    /// Iterate over all known entities and their scene graph objects.
    ///
    /// Returns true if the iteration was terminated early.
    efd::Bool ForEachEntitySceneGraph(EntitySceneGraphFunctor& functor);

    /// A functor class for iterating over all scene graphs with handles.
    EE_ECR_ENTRY class HandleSceneGraphFunctor
    {
    public:
        /**
            Derived classes must implement this operator.

            During scene graph iteration, the operator is called once for every handle
            that has a non-empty scene graph.

            The operator can prevent further iteration by setting the return value.

            @param handle The handle for the scene graph objects.
            @param objects The scene graph objects for the entity.
            @return True if iteration should stop, or false if it should continue.
        */
        virtual efd::Bool operator()(const SceneGraphHandle handle,
            const efd::vector<NiObjectPtr>& objects) = 0;

        virtual ~HandleSceneGraphFunctor() { }
    };

    /**
        Iterate over all known handles and their scene graph objects.

        Returns true if the iteration was terminated early.
    */
    efd::Bool ForEachHandleSceneGraph(HandleSceneGraphFunctor& functor);
    //@}

    /**
        @name Finding Scene Graphs and Entities
    */
    //@{
    /**
        Search through known scene graphs for the entity that owns the given object as its first
        object.

        This requires iterating, potentially, through all known scene graphs.
    */
    egf::Entity* GetEntityFromSceneGraph(const NiAVObject* pObject) const;

    /**
        Search through known scene graphs for the entity that has a primary scene graph that
        contains the given node.

        This requires iterating, potentially, through all known scene graphs.
    */
    egf::Entity* GetEntityFromSceneGraphNode(const NiAVObject* pObject) const;

    /**
        Search through known scene graphs for the entity that owns the given object as any one of
        its objects.

        This requires iterating, potentially, through all known scene graphs.
    */
    egf::Entity* GetEntityFromObject(const NiObject* pObject) const;

    /**
        Returns the scene graph path for the given entity.

        Returns the emoty string if the entity is unknown to the service or has no asset.
    */
    const efd::utf8string& GetSceneGraphPathFromEntity(const egf::Entity* pEntity) const;

    /**
        Return the first object for an entity, as an NiAVObject.

        The first object loaded from a NIF file is traditionally assumed to be a scene graph
        in Gamebryo. Hence, this function assumes that the first object associated with an entity
        is the NiAVObject scene graph. Applications that violate the assumption must take care
        in using this function.

        The function returns NULL when the scene graph for the entity failed to load or
        otherwise has no objects.
    */
    NiAVObject* GetSceneGraphFromEntity(const egf::Entity* pEntity) const;

    /// Get the number of objects associated with a given entity.
    efd::UInt32 GetObjectCountFromEntity(const egf::Entity* pEntity) const;

    /**
        Obtain a scene graph object for the given entity.

        If the entity is known to the service, the object at the given index is returned.
        NULL is returned if the entity is unknown or the index is out of range.
    */
    NiObject* GetObjectFromEntity(const egf::Entity* pEntity, efd::UInt32 objectIndex) const;

    /**
        @name Scene Graphs with No Entity

        Scene graphs without associated entities are managed through handles. Operations that
        create or register a scene graph return a handle, which is subsequently used to locate
        that scene graph within the service.
    */
    //@{
    /**
        Create a scene graph file direct from the name, with no associated entity.

        The fileName argument must be relative to the path that was given to the SetDataPath()
        method.

        @param fileName File location for the scene graph.
        @param isDynamic If true, the scene graph will be updated on each tick.
        @param isRendered If true, the object is sent to the RenderService for rendering.
        @param prependDataPath Determines whether or not the path to the data folder will be
            prepended to the file name
        @return A handle for the scene graph, or SceneGraphService::kInvalidHandle if the
            scene graph needed to be loaded from disk, in which case you should wait for an
            ecr::SceneGraphAddedMessage. No message will be sent if the scene graph fails to load.
    */
    SceneGraphHandle CreateSceneGraphFileName(
        const efd::utf8string& fileName,
        const efd::Bool isDynamic,
        const efd::Bool isRendered,
        const efd::Bool prependDataPath = true);

    /**
        Add a set of scene graph objects with no entity.

        The set of objects is not associated with any asset, and the scene graph objects
        cannot be shared (although the objects passed in may be clones of other objects).
        The isDynamic and isRendered flags determine whether the scene graph is to be updated
        on each tick and rendered on each tick.

        A unique handle to this scene graph is returned.
    */
    SceneGraphHandle AddSceneGraph(
        const efd::vector<NiObjectPtr>& objects,
        const efd::Bool isDynamic,
        const efd::Bool isRendered);

    /// Remove all scene graph information for the given handle.
    void RemoveSceneGraph(const SceneGraphHandle handle);

    /**
        Returns the SceneGraphData object.

        Returns NULL if the handle is invalid.
    */
    const efd::utf8string& GetSceneGraphPathFromHandle(const SceneGraphHandle handle);

    /**
        Return the first object for a handle, as an NiAVObject.

        The first object loaded from a NIF file is traditionally assumed to be a scene graph
        in Gamebryo. Hence, this function assumes that the first object associated with a handle
        is the NiAVObject scene graph. Applications that violate the assumption must take care
        in using this function.

        Returns NULL if the handle is invalid or the scene graph is empty.
    */
    NiAVObject* GetSceneGraphFromHandle(const SceneGraphHandle handle);

    /// Get the number of objects associated with a given handle.
    efd::UInt32 GetObjectCountFromHandle(const SceneGraphHandle handle);

    /**
        Obtain a scene graph object for a handle.

        If the handle is known to the service, the object at the given index is returned.
        NULL is returned if the handle is unknown.
    */
    NiObject* GetObjectFromHandle(const SceneGraphHandle handle, efd::UInt32 objectIndex);
    //@}

    /// @name Updated Scene Graph Iteration
    //@{
    /// Iterate over all recently updated entities and their scene graph objects.
    ///
    /// Returns true if the iteration was terminated early.
    efd::Bool ForEachUpdatedEntity(EntitySceneGraphFunctor& functor);

    /// Iterate over all recently updated handles and their scene graph objects.
    ///
    /// Returns true if the iteration was terminated early.
    efd::Bool ForEachUpdatedHandle(HandleSceneGraphFunctor& functor);
    //@}

    /**
        @name Asset Caching

        When an asset is cached, this service immediately loads it and will never unload it
        until it is removed from the cache.  When entities with shared scenegraphs request this
        asset, it will be cloned rather than loaded from disk, which can save having to repeatedly
        reload assets.

        Caching is a boolean state, not a reference count.  If an asset is repeatedly cached,
        it will still be uncached during the first RemoveFromCache or RemoveAllFromCache.
    */
    //@{

    /**
        Load and cache any assets that match the provided asset ID.

        The assets may already be loaded from disk, in which case true is returned and the
        handles for the asset are returned. Otherwise, the caller must wait for a
        SceneGraphCacheResponse message on the given category with a list of handles to
        the cached objects. The identifier in that message will be the urn from the given
        assetID.

        @param assetID The ID for the asset you wish to cache.
        @param pRequestData Data that will be passed back to you in the response to this cache
            request, if one is sent.
        @param responseCategory The category to send the response on when the recreate is
            completed. The message will only be sent if this function returns false.
        @param handles A vector of handles to cached scene graphs that will be filled if
            the assets are already available (only when true is returned by this function).
            Information about the asset can be obtained by using the handle with functions
            in the ecr::SceneGraphCache returned by GetSceneGraphCache.
        @result True is the assets for the requested ID were already in the cache, or could be
           cached immediately. False if you must wait on a message indicating the result of the
           caching operation.
    */
    efd::Bool Cache(
        const efd::AssetID& assetID,
        SceneGraphCache::ISceneGraphCacheRequestData* pRequestData,
        const efd::Category responseCategory,
        efd::vector<SceneGraphCache::SceneGraphCacheHandle>& handles);

    /// Stop caching all assets.
    void RemoveAllFromCache();

    /**
        Manually cache a scene graph file direct from the name, with no associated entity.
        This asset will persist (and will be shared by any scene graphs that also use
        this file) until no other objects are using the cached data and
        UnCacheHandles is called.

        The fileName argument fileName must be an absolute path.

        The assets may already be loaded from disk, in which case true is returned and the
        handles for the asset are returned. Otherwise, the caller must wait for a
        SceneGraphCacheResponse message on the given category with a list of handles to
        the cached objects. The identifier in that message will be the given fileName.

        @param fileName File location for the scene graph.
        @param pRequestData Data that will be passed back to you in the response to this cache
            request, if one is sent.
        @param responseCategory The category to send the response on when the recreate is
            completed.
        @param handles A vector of handles to cached scene graphs that will be filled if
            the asset is already available (only when true is returned by this function).
            Information about the asset can be obtained by using the handle with functions
            in the ecr::SceneGraphCache returned by GetSceneGraphCache.
        @return True if the asset was already in the cache and is immediately available, false
            otherwise.
    */
    efd::Bool CacheSceneGraphFileName(
        const efd::utf8string& fileName,
        SceneGraphCache::ISceneGraphCacheRequestData* pRequestData,
        const efd::Category responseCategory,
        efd::vector<SceneGraphCache::SceneGraphCacheHandle>& handles);

    /**
        Un-cache scene graph files direct from the handle that was provided when the
        scene graph was cached.

        This must be called at some point if the asset is ever to leave the cache,
        but asset will only be removed from the cache when no other objects are using the
        cached data.

        @param handles The handles for the assets, as returned by CacheSceneGraphFileName or in
            the response to Cache.
    */
    void UnCacheHandles(
        efd::vector<SceneGraphCache::SceneGraphCacheHandle>& handles);
    //@}

    /// @name Attachment Management
    //@{
    /**
        Create the attached scene graphs for an entity that was not created via entity
        discovery.

        This function is intended for processing the attached scene of an entity that added its
        primary scene graph via the CreateSceneGraphFilename function (see
        egmAnimation::AnimationService for an example). The method looks for the attached
        objects property on the entity and creates any attached scene graphs.

        Once created, the attachments are updated automatically via entity update messages.
        An alternate to calling this function is to mark the AttachedObjects property as dirty
        and allow the update method to load the missing attachments. However, the alternate method
        introduces lag in loading the attached assets.
    */
    virtual void CreateAttachedSceneGraphs(egf::Entity* pEntity);

    /**
        Attach one scene graph to another.

        One scene graph may be attached to a particular node in another using this function.
        It is typically invoked during entity discovery when an entity is found with the
        "AttachedObjects" property and that property is a map of "AttachedNifAsset" type.

        The scene graph may not immediately be attached because it may need to be located and
        loaded. An ecr::AttachmentMadeMessage will be sent when the attachment is made.

        @param pEntity The entity with the scene graph to which we are attaching.
        @param slotName A name for this attachment location. The name must be one of the key
            names in the map of attachment points in the "AttachedObjects" property of the
            entity's model.
        @return True if the attachment is proceeding. False if a problem is found with the entity
            or attachment data.
    **/
    efd::Bool AttachSceneGraph(
        egf::Entity* pEntity,
        const efd::utf8string& slotName);

    /**
        Detach any scene graph attached at the named slot.

        An ecr::AttachmentBrokenMessage will be sent when the attachment is removed.

        @param pEntity The entity with the scene graph to which we are attaching.
        @param slotName A name for this attachment location. The name must be one of the key
            names in the map of attachment points in the "AttachedObjects" property of the
            entity's model.
        @return True if the detachment succeeded. False if a problem is found with the entity
            or attachment data. True is also returned if there was nothing attached.
    */
    efd::Bool DetachSceneGraph(
        egf::Entity* pEntity,
        const efd::utf8string& slotName);

    /**
        Return the scene graph attached at the named slot.

        @param pEntity The entity with the scene graph that has the attachment
        @param slotName The name for the attachment location.
        @return The attached scene graph if it exists.  NULL if there is none attached,
            the slot name was invalid, or the attached scene graph is empty.
    */
    NiAVObject* GetAttachedSceneGraph(
        egf::Entity* pEntity,
        const efd::utf8string& slotName) const;
    //@}

    /// @name Preloading
    //@{

    /**
        Preload all assets related to a given entity which uses a scene graph with the given
        filename.

        This function is intended for use by other services that handle models with scene graphs.
        The path must be an absolute path.

        Attached scene graphs are also loaded before the response is sent.

        The response category is the category that the EntityPreloadResponse should be sent on.
        If efd::kCAT_INVALID no response will be sent.
    */
    void Preload(
        egf::Entity* pEntity,
        const efd::utf8string& filePath,
        const efd::Category& responseCategory);

    //@}

    /// @name Placeable Property Update

    //@{

    /**
        Enable Placeable built-in model property updates using the given scene egraph node.

        When enabled, the service will set the properties of the given Placeable model
        with the world transformation of the given scene graph node. Any scene graph node
        may be given provided that it belongs to a scene graph belonging to an entity
        that the service knows about. This enables one entity to receive transformation
        updates for another entity's scene graph.

        An entity should only enable Placeable reporting from its own scene graph when the
        entity has been registered as not requiring pose updates. The service will refuse to
        enable this Placeable update if the service is actively updating the pose itself.

        All Placeable feedback information is destroyed when a NIF file is rapidly iterated
        or otherwise changed. Placeable feedback for a node that is in an attachment is removed
        when the attachment is removed. The feedback must be re-enabled with the new
        scene graph or attachment.

        @param pPlaceable The Placeable mdoel to update.
        @param pSourceEntity The entity from which the placeable model is to receive feedback.
        @param pSourceNode The node from which to pull the world transform.
        @param pIgnoreCallback A Placeable model callback to ignore when setting this property.
            This will typically be the callback for the service that is calling this method.
        @param ignoreScale Scale is fed back to the Placeable model when this parameter is true;
            otherwise, scale on the given Placeable is not set.
        @return True on success, or false when the given node is not known to the service or
            the entity is receiving pose updates via the scene graph service and this request
            would cause conflicts.
    */
    bool EnablePlaceableFeedback(
        egf::PlaceableModel* pPlaceable,
        egf::Entity* pSourceEntity,
        NiAVObject* pSourceNode,
        egf::IPropertyCallback* pIgnoreCallback,
        bool ignoreScale = false);

    /**
        Disable Placeable model feedback.

        Returns false if the Placeable model and node requesting feedback is known to the service.
    */
    bool DisablePlaceableFeedback(
        egf::PlaceableModel* pPlaceable,
        egf::Entity* pSourceEntity,
        NiAVObject* pSourceNode);

    //@}

    /**
        Marks all NiRenderObjects associated with the SceneGraphService to update
        their material the next time they are rendered.

        This forces the material
        descriptor of NiFragmentMaterial based materials to be recomputed.
    */
    void ForceMaterialUpdate();

    /// @cond EMERGENT_INTERNAL

    /**
        This method is called by the Mesh built-in model to notify the service that
        an entity has been discovered that is of interest to the service.

        A corresponding RemoveEntityWithMeshModel call will be made when the entity is
        removed.
    */
    virtual void AddEntityWithMeshModel(egf::Entity* pEntity);

    /**
        This method is called by the Mesh built-in model to notify the service that
        an entity has been removed.

        A corresponding AddEntityWithMeshModel call will have been made when the entity was
        added.
    */
    virtual void RemoveEntityWithMeshModel(egf::Entity* pEntity);

    /**
        Callback for built-in model property changes.

        The SceneGraphService registers itxself to get property update callbacks
        from the PlaceableModel and the RenderableModel. This function is invoked to
        apply the property change.
    */
    virtual void OnPropertyUpdate(
        const egf::FlatModelID& modelID,
        egf::Entity* pEntity,
        const egf::PropertyID& propertyID,
        const egf::IProperty* pProperty,
        const efd::UInt32 tags);

    // This message handler is called when an entity hits its enter world life cycle.
    // The entity is set to be rendered and updated.
    void HandleEntityEnterWorldMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    // This message handler is called when an entity hits its exit world lifecycle.
    // The entity ceases to be updated or rendered.
    void HandleEntityExitWorldMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    // This message handler is called when properties of an entity change.
    // Scene graph related property values are propagated from the entity to
    // the corresponding scene graph node.
    void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    // Asset load request response
    void HandleCacheResponse(
        const ecr::SceneGraphCacheResponse* pResponse,
        efd::Category targetChannel);

    // Asset preload request
    void HandlePreloadRequest(
        const egf::EntityPreloadRequest* pRequest,
        efd::Category targetChannel);

    /// @endcond

protected:
    // Predeclaration for various classes.
    class AttachedSceneGraphData;
    class SceneGraphData;
    class AssetData;

    // Actions that might be taken on receipt of a ScenegraphCacheResponse message
    enum SceneGraphCacheRequestAction
    {
        SGCRA_Invalid,
        SGCRA_AssetLoadRequest,
        SGCRA_CacheSceneGraph
    };

    // Generic Scene Graph Cache request data for this service
    class SceneGraphCacheRequestData : public SceneGraphCache::ISceneGraphCacheRequestData
    {
        EE_DECLARE_CONCRETE_REFCOUNT;
    public:
        SceneGraphCacheRequestData();
        ~SceneGraphCacheRequestData();

        SceneGraphCacheRequestAction m_action; // Used to decide what function to call
        AssetData* m_pAssetData; // The asset data associated with this request.

         // Request data for an application-level cache request.
        SceneGraphCache::ISceneGraphCacheRequestData* m_pRequestData;

        efd::Category m_responseCategory; // The category to use when a response must be sent
    };
    typedef efd::SmartPointer<SceneGraphCacheRequestData> SceneGraphCacheRequestDataPtr;

    /// Class to hold information about preload requests
    class EntityPreloadData : public efd::MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;
    public:
        SceneGraphData* m_pEntityData;
        efd::Category m_responseCategory;
        efd::UInt32 m_assetsNeeded;
        efd::UInt32 m_assetsFound;
    };
    typedef efd::SmartPointer<EntityPreloadData> EntityPreloadDataPtr;

    /// Structure to hold information about scene graph files and cloning
    EE_ECR_ENTRY class AssetData : public efd::MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;
    public:
        AssetData();
        virtual ~AssetData();

        enum AssetDataState {
            ADS_Loading,
            ADS_Reloading,
            ADS_Ready,
            ADS_Unloaded
        };

        /// Returns false if this entity is not being shared and can be removed.
        efd::Bool InUse() const;

        /**
            Remove the given entity from the preload list, if present

            Returns true if the entity was present in the preload list. Because of attachments
            the same entity may be present multiple times in the list. Only the first found
            incident is removed.
        */
        efd::Bool RemoveEntityFromPreload(egf::Entity* pEntity);

        /// The current state, initially locating, then loading etc.
        AssetDataState m_state;

        /// The identifier that the asset was requested with, only valid while loading
        efd::utf8string m_identifier;

        /// May be either a physical ID or a path on disk.
        efd::utf8string m_physicalID;

        SceneGraphCache::SceneGraphCacheHandle m_cacheHandle;

        /// The set of entities sharing this asset data.
        efd::vector<SceneGraphData*> m_entities;

        /// The set of attachments using this asset.
        efd::vector<AttachedSceneGraphData*> m_attachments;

        /// The set of handles sharing this asset data.
        efd::vector<SceneGraphData*> m_handles;

        /// The set of preload requests that we have not yet responded to.
        efd::vector<EntityPreloadDataPtr> m_preloads;

        /// This pointer is non-NULL if there is an outstanding load with cache data.
        /// It is needed to free the data if the asset is removed before the reload completes.
        SceneGraphCacheRequestDataPtr m_spLoadData;

        /// Was this asset explicitly cached?
        efd::Bool m_isCached;
    };
    typedef efd::SmartPointer<AssetData> AssetDataPtr;

    /// Structure to hold attached scene graph information
    EE_ECR_ENTRY class AttachedSceneGraphData : public efd::MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;
    public:
        AttachedSceneGraphData();
        virtual ~AttachedSceneGraphData();

        /// All attached scene graphs have a handle
        // SceneGraphHandle m_handle;

        /// The data for the entity we are attached to
        SceneGraphData* m_pEntityData;

        /// The key for the attachment
        efd::utf8string m_attachmentKey;

        /// The set of objects we have. Only the first object is attached (to the first object
        /// of the entity). The others are available for their services, if necessary.
        efd::vector<NiObjectPtr> m_objects;

        /// The asset data we belong to
        AssetDataPtr m_spAssetData;

        /// The attachment may have a scenegraph but not be attached to the entity yet.
        efd::Bool m_isAttached;

        /// Returns the scene graph, or NULL if no objects or a non-NiAVObject object
        inline NiAVObject* GetSceneGraph();
    };

    typedef efd::SmartPointer<AttachedSceneGraphData> AttachedSceneGraphDataPtr;

    class PlaceableFeedbackData : public efd::MemObject
    {
        public:
            egf::PlaceableModel* m_pPlaceable;
            NiAVObject* m_pNode;
            egf::IPropertyCallback* m_pIgnoreCallback;
            bool m_doScale;
    };

    /// Structure to hold entity scene graph information
    EE_ECR_ENTRY class SceneGraphData : public efd::MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;
    public:
        SceneGraphData();
        virtual ~SceneGraphData();

        // The scene graph objects.
        efd::vector<NiObjectPtr> m_objects;

        // Only NULL if the asset couldn't load. But check with the AssetData to see if the
        // asset is ready for use.
        AssetDataPtr m_spAssetData;

        // An index to use when this object is not updated.
        static const efd::UInt32 kInvalidUpdateIndex;

        // The index of this entity in the update vector.
        efd::UInt32 m_updateIndex;

        // We're either an entity or a handle.
        union {
            egf::Entity* m_pEntity;
            SceneGraphHandle m_handle;
        };

        // Map of attached objects, indexed on slot name.
        efd::map<efd::utf8string, AttachedSceneGraphDataPtr> m_attached;

        // Vector of enitities to whom we report transformation updates
        efd::vector<PlaceableFeedbackData> m_placeableFeedback;

        // Returns the scene graph, or NULL if no objects or a non-NiAVObject object
        inline NiAVObject* GetSceneGraph();

        // Returns true if the scene data is waiting on it's asset to be available.
        efd::Bool IsWaitingOnAsset() const;

        // Returns true if the asset is waiting on its attachments to be loaded.
        efd::Bool IsWaitingOnAttachments() const;

        inline efd::Bool IsEntity() const;
        inline void SetIsEntity(const efd::Bool bIsEntity);
        inline efd::Bool IsDynamic() const;
        inline void SetIsDynamic(const efd::Bool bIsDynamic);
        inline efd::Bool IsAssetShared() const;
        inline void SetIsAssetShared(const efd::Bool bIsAssetShared);
        inline efd::Bool IsRendered() const; // Is currently registered with the render service
        inline void SetIsRendered(const efd::Bool bIsRendered);
        inline efd::Bool IsRenderable() const; // Can be added to the render service
        inline void SetIsRenderable(const efd::Bool bIsRenderable);
        inline efd::Bool IsAssetExternal() const;
        inline void SetIsAssetExternal(const efd::Bool bIsAssetExternal);
        inline efd::Bool IsWaitingToSendEvent() const;
        inline void SetIsWaitingToSendEvent(const efd::Bool waiting);
        inline efd::Bool IsInWorld() const;
        inline void SetIsInWorld(const efd::Bool inWorld);
        inline efd::Bool DoPoseUpdate() const;
        inline void SetDoPoseUpdate(const efd::Bool updatePose);

    protected:
        enum FlagBits {
            IS_ENTITY = 0x01,
            IS_DYNAMIC = 0x02,
            IS_ASSET_SHARED = 0x04,
            IS_RENDERED = 0x08,
            IS_ASSET_EXTERNAL = 0x10,
            IS_RENDERABLE = 0x20,
            IS_WAITING_TO_SEND_EVENT = 0x40,
            IS_IN_WORLD = 0x80,
            DO_POSE_UPDATE = 0x100
        };

        efd::UInt16 m_flags;
    };

    typedef efd::SmartPointer<SceneGraphData> SceneGraphDataPtr;

    /// Look up the reflector service and register for entity discovery,
    /// entity property change, entity removal messages, entity added, and asset locator.
    virtual efd::Bool SubscribeToMessages();

    /**
        Updates any entities that are dynamic, like those with animations.  Also updates
        entities that are not usually dynamic that were added to the update once queue.
    
        @param advanceUpdateTime should we advance the current animation time during the update.
        @param performUpdate true to perform updates for dynamic entities.
        @param performUpdateOnce true to perform updates for items in the update once queue.
    */
    virtual void UpdateDynamicEntities(
        bool advanceUpdateTime = true,
        bool performUpdate = true,
        bool performUpdateOnce = true);

    /// Bring an entity into the world, which means adding it to the rendered set and
    /// adding it to the update list.
    virtual void EntityEnterWorld(SceneGraphData* pData);

    /// Take an entity out of the world, which means removing it from the rendered set and
    /// removing it from the update list.
    virtual void EntityExitWorld(SceneGraphData* pData);

    /// Update the Placeable model for the given data.
    virtual void PlaceableFeedback(PlaceableFeedbackData& data);

    /// Remove placeable feedback for attached nodes
    void RemoveAttachmentPlaceableFeedback(AttachedSceneGraphData* pSceneData);

    /// True if a scene graph contains another
    bool SceneGraphContains(NiAVObject* pSceneGraph, NiAVObject* pTarget);

    /// Add and Remove data from the update lists.
    inline void AddToUpdate(SceneGraphData* pData);
    inline void RemoveFromUpdate(SceneGraphData* pData);
    inline void AddToUpdateOnce(SceneGraphData* pData);
    inline void RemoveFromUpdateOnce(SceneGraphData* pData);
    inline void SwapUpdateOrder(SceneGraphData* pData1, SceneGraphData* pData2);

    /// Preload an asset
    void Preload(EntityPreloadData* pData, const efd::utf8string& assetURN);

    /// Preload the attachments for an asset
    void PreloadAttachedSceneGraphs(EntityPreloadData* pData);

    /// Mark a preload requested asset as found. Messages will go out and this data will be
    /// deleted in cases where it is the last requested asset to be found.
    void MarkPreloadsAsFound(AssetData* pAssetData);

    /// Create asset data for a given identifier. This will launch a request to load the asset.
    /// It also adds the asset to the physical ID and, if appropriate, request ID map.
    /// Asserts if the asset already exists. Returns NULL if the asset can be immediately loaded
    /// but has errors.
    AssetData* CreateAssetData(const efd::utf8string& identifier);

    /// Create asset data for a given identifier using a handle that has already been loaded.
    /// This is used when caching assets.
    AssetData* CreateAssetDataWithHandle(SceneGraphCache::SceneGraphCacheHandle handle);

    /// Merge an asset data object with an existing one because the redundant data has
    /// been found to have the same physical ID as the existing data. This function assumes
    /// that the redundant data is newly loaded and that all entities, attachments, etc using
    /// the data have not yet been set up with their scene graphs.
    void MergeAssetData(AssetData* pExistingData, AssetData* pRedundantData);

    /// Remove asset data if not in use
    void RemoveUnusedAssetData(AssetDataPtr spAssetData);

    /// Set up an AssetData object based on the handle from the Scene Graph Cache.
    /// This adds the scene graph to any entities and attachments and handles waiting on the
    /// asset. If a cache handle already exists, this is treated as a reload.
    AssetData*  SetAssetDataFromCache(
        AssetDataPtr spAssetData,
        SceneGraphCache::SceneGraphCacheHandle cacheHandle,
        bool usagePending);

    /// Set the scene graph objects for an entity or handle.
    /// This will cause messages to be sent out.
    void SetSceneGraph(AssetData* pAssetData, SceneGraphData* pSceneData);

    /// Unset the scene graph objects for an entity or handle.
    /// This will cause messages to be sent out.
    void UnsetSceneGraph(SceneGraphData* pSceneData);

    /// Set the scene graph objects for an attachment.
    /// This will cause messages to be sent out.
    void SetAttachedSceneGraph(AssetData* pAssetData, AttachedSceneGraphData* pSceneData);

    /// Unset the scene graph objects for an attachment.
    /// This will cause messages to be sent out.
    void UnsetAttachedSceneGraph(AttachedSceneGraphData* pSceneData);

    /// Invalidates an asset, which removes all traces of it
    virtual void OnAssetLoadFailure(AssetDataPtr spAssetData);

    /// Handle a message that is for an unsolicited scene graph refresh
    virtual void ProcessSceneGraphCacheReload(const ecr::SceneGraphCacheResponse* pMessage);

    /// Add the entity to the asset data. This is called on existing asset data when a new
    /// entity is added to the service.
    void AddEntityToAssetData(AssetData* pAssetData, SceneGraphData* pEntityData);

    /// Add the handle to the asset data. This is called on existing asset data when a new
    /// handle is added to the service.
    void AddHandleToAssetData(AssetData* pAssetData, SceneGraphData* pHandleData);

    /// Add the attachment to the asset data. This sets up the attachment if the asset is
    /// ready.
    void AddAttachmentToAssetData(
        AssetData* pAssetData,
        AttachedSceneGraphData* pAttachData);

    /// Remove all traces of the entity from its asset data. Should only by used when the
    /// entity is having its asset changed or the entity is being deleted.
    void RemoveEntityFromAssetData(SceneGraphData* pEntityData);

    /// Remove all traces of the handle from its asset data. Should only by used when the
    /// handle is having its asset changed or the handle is being deleted.
    void RemoveHandleFromAssetData(SceneGraphData* pHandleData);

    /// Remove all traces of the attachment from its asset data. Should only by used when the
    /// attachment is having its asset changed or the attachment is being deleted.
    void RemoveAttachmentFromAssetData(AttachedSceneGraphData* pAttachData);

    /// Replace the asset used by an entity or handle. The pNewAssetData may be NULL. If so it is
    /// created from the given name and the new pointer is returned.
    void ReplaceAsset(
        SceneGraphData* pSceneGraphData,
        AssetDataPtr& pNewAssetData,
        const efd::utf8string& newSceneGraphName);

    /// Called when a scene graph is added and non-AssetData-specific work must be done.
    /// This function actually send the messages and does the initial update of the scene graph.
    void ProcessFreshSceneGraph(SceneGraphData* pSceneData);

    /// Clone the asset into the given object vector
    void GetSharedObjects(
        SceneGraphCache::SceneGraphCacheHandle handle,
        efd::vector<NiObjectPtr>& objects);

    /// Deep copy the asset into the given object vector
    void GetNonSharedObjects(
        SceneGraphCache::SceneGraphCacheHandle handle,
        efd::vector<NiObjectPtr>& objects);

    /// Attach one scene graph to another. Return false if the attachment point could not
    /// be located or some other error. The entity scene graph has its properties, effects and
    /// scene graph updated.
    virtual efd::Bool AttachSceneGraph(
        NiAVObject* pEntitySceneGraph,
        NiAVObject* pAttachSceneGraph,
        const AttachNifData& attachData);

    /// Re-attach all the scene graphs in the case where the scene graph for the entity
    /// has changed.
    virtual void AttachAllSceneGraphs(SceneGraphData* pEntityData, NiAVObject* pAVObject);

    /// Detach all the scene graphs attached to this entity
    virtual void DetachAllSceneGraphs(SceneGraphData* pEntityData);

    /// Detach one scene graph from another. The entity scene graph has its properties, effects
    /// and scene graph updated.
    virtual void DetachSceneGraph(
        NiAVObject* pEntitySceneGraph,
        NiAVObject* pAttachSceneGraph);

    /// Remove all the data for attachments. Should only be called when the entity is removed
    /// or otherwise must have all trace of any attachments deleted.
    virtual void RemoveAllAttachmentData(SceneGraphData* pEntityData);

    /// Remove the data for an attachment. Should only be called when the attached objects
    /// property on the entity has changed to entirely eliminate the attachment slot.
    virtual void RemoveAttachmentData(
        SceneGraphData* pEntityData,
        const efd::utf8string& slotName);

    /// Update scene-graph relevant data from the entity properties, only if those properties
    /// are dirty.
    virtual void UpdateDirtyProperties(egf::Entity* pEntity);

    /// Update non-volatile properties - those that persist through asset changes.
    virtual void UpdateNonVolatileProperties(
        egf::Entity* pEntity,
        SceneGraphData* pSceneGraphData);

    /// Update scene graph properties that must be derived from entity properties
    /// alone. This includes the transformation and visibility information. Referred to as
    /// volatile because these properties are from built-ins that usual notify of
    /// changes with a callback.
    virtual void UpdateVolatileProperties(
        egf::Entity* pEntity,
        NiAVObject* pSceneGraph,
        bool initialUpdate = false);

    /// Update things derived from the AttachedObjects property.
    virtual void UpdateAttachedProperty(egf::Entity* pEntity);

    /// Handle attachment update
    virtual void UpdateAttachmentPropertyData(
        egf::Entity* pEntity,
        const efd::utf8string& slotName,
        AttachedSceneGraphData* pAttachData,
        const AttachNifData& attachData);

    /// @name Called when a scene graph is added or removed
    /// Useful to anyone that subclasses the SceneGraphService.
    //@{
    virtual void OnSceneGraphAdded(egf::Entity* pEntity, NiAVObject* pSceneGraph);
    virtual void OnSceneGraphRemoved(egf::Entity* pEntity, NiAVObject* pSceneGraph);
    virtual void OnSceneGraphAdded(SceneGraphHandle handle, NiAVObject* pSceneGraph);
    virtual void OnSceneGraphRemoved(SceneGraphHandle handle, NiAVObject* pSceneGraph);
    //@}

    /// Called once after all the dynamic scene graphs have been updated.
    virtual void OnSceneGraphsUpdated();

    /// @name Called when attachments are made or broken
    //@{
    virtual void OnAttachmentMade(egf::Entity* pEntity, const efd::utf8string& slotName);
    virtual void OnAttachmentBroken(egf::Entity* pEntity, const efd::utf8string& slotName);
    //@}

    /// @name SceneGraphHandle allocation
    //@{
    SceneGraphHandle AllocateHandle();
    void ReleaseHandle(const SceneGraphHandle handle);
    //@}

    /// Flag an asset as cached, or add it if not already present.
    void CacheHandles(efd::vector<SceneGraphCache::SceneGraphCacheHandle>& handles);

    /// Convenience accessor for the URN -> asset data map.
    /// Returns the asset data if we know the mapping from URN to physical ID and hence asset.
    /// This does not imply that the asset is currently loaded or even located.
    AssetData* FindAssetData(const efd::utf8string& identifier) const;

    /// Obtain scene graph data for the given entity. NULL is returned
    /// if the entity is not present.
    inline SceneGraphService::SceneGraphData* GetEntityData(const egf::Entity* pEntity) const;

    /// Create a new SceneGraphData entry and add it to the map of known entities.
    /// New data has the entity set, but no asset data, not rendered, etc; basically
    /// just a placeholder to remember we have the entity. NULL is returned if there is
    /// existing data. Properties are pulled from the entity in this method.
    SceneGraphData* CreateEntityData(egf::Entity* pEntity);

    /// Create a new SceneGraphData entry and add it to the map of known handles.
    SceneGraphData* CreateHandleData();

    /// Returns true if the model contains a mesh and has the NifAsset property.
    static bool HasNifAssetProperty(const egf::Entity* pEntity, efd::AssetID& sceneGraphAssetID);

    /// Cached services
    efd::MessageService* m_pMessageService;
    egf::EntityManager* m_pEntityManager;
    efd::SmartPointer<RenderService> m_spRenderService;

    /// Data path for direct loading of assets
    NiFixedString m_strDataPath;

    /// Mapping from known entities to their scene graph data
    efd::map<egf::Entity*, SceneGraphDataPtr> m_entityData;

    /// Mapping from attached scene graphs to their data
    efd::map<SceneGraphHandle, AttachedSceneGraphDataPtr> m_attachedData;

    /// Mapping from scene graph handles to their scene graph data
    efd::map<SceneGraphHandle, SceneGraphDataPtr> m_handleData;

    /// Map of physical IDs to asset data (which has a 1-1 mapping to cached scene graphs)
    efd::map<efd::utf8string, AssetDataPtr> m_assetsByPhysicalID;

    /// Map of all asset locator request URNs to the asset data representing it.
    efd::map<efd::utf8string, efd::utf8string> m_requestIDToPhysicalID;

    /// Vector of all assets to be updated
    efd::vector<SceneGraphData*> m_toUpdate;

    /// Vector of assets that need an update due to rapid iteration, but otherwise static
    efd::vector<SceneGraphData*> m_toUpdateOnce;

    /// Use a map to keep track of any assets that are loading but for which we do not yet have
    /// a physical ID. Key is the identifier for which the asset was requested.
    efd::map<efd::utf8string, AssetDataPtr> m_pendingAssetLoads;

    /// @name Dynamic categories used for asset lookup responses.
    //@{
    efd::Category m_assetPreloadRequestCategory;
    efd::Category m_assetPreloadResponseCategory;
    efd::Category m_assetRefreshCategory;
    efd::Category m_sceneGraphCacheCategory;
    //@}

    /// Scene Graph Cache to handle our asset caching
    SceneGraphCachePtr m_spSceneGraphCache;

    /// @name Update process and workflow manager used for updating all scene graphs.
    //@{
    NiUpdateProcess* m_pUpdateProcess;
    NiBatchedUpdateProcess* m_pBatchedUpdateProcess;
    NiSPWorkflowManagerPtr m_spWorkflowManager;
    //@}

    /// @name SceneGraphHandle management
    //@{
    efd::vector<SceneGraphHandle> m_unusedHandles;
    SceneGraphHandle m_nextUnusedHandle;
    //@}

    /// Tool mode
    efd::Bool m_toolMode;
};

typedef efd::SmartPointer<SceneGraphService> SceneGraphServicePtr;

} // end namespace egf

#include "SceneGraphService.inl"

#endif // EE_SCENEGRAPHSERVICE_H
