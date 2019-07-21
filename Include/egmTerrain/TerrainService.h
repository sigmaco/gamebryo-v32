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
#ifndef EE_TERRAINSERVICE_H
#define EE_TERRAINSERVICE_H

#include "egmTerrainLibType.h"

#include <egf/EntityID.h>
#include <efd/FixedString.h>
#include <efd/ISystemService.h>
#include <efd/StreamMessage.h>

#include <ecr/SceneGraphService.h>
#include <ecr/ecrSystemServiceIDs.h>
#include "TerrainChangedMessage.h"

#include <NiTerrain.h>

// Forward declarations
namespace egf
{
    class EntityManager;
}

namespace efd
{
    class MessageService;
}

class NiTerrain;

namespace egmTerrain
{

/**
    The Terrain service provides an interface and a set of script built-ins for interfacing with
    the Gamebryo Terrain system. The service allows seamless integration of entities, scripts,
    and behaviors with Gamebryo's Terrain system without the need for extensive custom code.
*/
class EE_EGMTERRAIN_ENTRY TerrainService :
    public efd::ISystemService,
    public efd::AssetChangeHandler
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(TerrainService, efd::kCLASSID_TerrainService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

    /// @name Construction and Destruction
    //@{
protected:
    /// Virtual Destructor
    virtual ~TerrainService();

public:
    /// Default Constructor
    TerrainService();
    //@}

    /**
        TerrainPickPolicy is an extension of NiPick that can be used to pick against terrain.
    */
    class EE_EGMTERRAIN_ENTRY TerrainPickPolicy : public NiPick::PickObjectPolicy
    {
    public:
        /// @name Construction and Destruction
        //@{
        
        /** 
            Constructor
            @param pTerrainService The terrain service to use for picking.
        */
        TerrainPickPolicy(TerrainService* pTerrainService);
        //@}

        /**
            Overridden pick routine for Terrain.
        */
        virtual bool FindIntersections(
            const NiPoint3& origin,
            const NiPoint3& dir,
            NiPick& pick,
            NiRenderObject* pRenderObj);

    protected:
        /// The terrain service to use for picking.
        TerrainService* m_pTerrainService;
    };

    /**
        This class is an implementation of NiTerrainAssetResolverBase that allows NiTerrain
        objects to resolve their assets through the AssetLocatorService. 
    */
    class EE_EGMTERRAIN_ENTRY AssetResolver : public NiTerrainAssetResolverBase, 
        public IBase
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(AssetResolver, efd::kCLASSID_TerrainServiceAssetResolver, efd::IBase);

    protected: 
        /// @see efd::IBase
        void DeleteThis() const;
    public:
        /// @see efd::IBase
        void IncRefCount() const;
        /// @see efd::IBase
        void DecRefCount() const;
        /// @see efd::IBase
        efd::UInt32 GetRefCount() const;

        /// @endcond

    public:
        /**
            Constructor

            @param pServiceManager The service manager that contains the message service and the
                asset locator service. 
        */
        AssetResolver(efd::ServiceManager* pServiceManager);

        /// Destructor
        virtual ~AssetResolver();

        /**
            Initialize function to be called during the initialization of the host service 
            (TerrainService). 
        */
        void Initialize();

        /**
            Shutdown function to be called during the shutdown of the host service (TerrainService). 
        */
        void Shutdown();

        /**
            Handle an asset locater response message.
            @param pMessage The asset locater response message.
            @param targetChannel Channel the message was sent on.
        */
        virtual void HandleAssetLocatorResponse(const efd::AssetLocatorResponse* pMessage, 
            efd::Category targetChannel);

    protected:
        /// @see NiTerrainAssetResolverBase
        virtual void InternalResolveReference(NiTerrainAssetReference* pkReference);

        /// The message service to listen to for asset messages
        efd::MessageService* m_pMessageService;
        /// The asset locator service to query for asset locations
        efd::AssetLocatorService* m_pAssetLocatorService;
        /// The category used by the class to listen to requests on
        efd::Category m_locaterCategory;

        /// Typedef to store a list of references that have asked for a specific URN
        typedef efd::list<NiTerrainAssetReference*> ContextList;
        /// Typedef to manage a map of URN's to the list of references that are querying them
        typedef efd::map<efd::utf8string, ContextList> ContextsMap;
        /// The context map of URN's to the references that are querying them
        ContextsMap m_pendingQueries;
    };

    /// Defines a smart pointer (reference counted) for the TerrainPickPolicy
    typedef efd::SmartPointer<TerrainPickPolicy> TerrainPickPolicyPtr;

    /**
        Return the current terrain.  Returns NULL if none.
    */
    inline NiTerrain* GetNiTerrain();

    /**
        Return the terrain entity.  Returns NULL if none.
    */
    inline egf::Entity* GetTerrainEntity();

    /**
        Given an entity ID, attempts to return the corresponding NiTerrain object. 
        If no NiTerrain is found, or the terrain hasn't yet been initialized,
        this function will return 0.
    */
    NiTerrain* GetTerrainForEntity(egf::EntityID entityID);

    /**
        Uses the given Entity's EntityID to retrive the corresponding NiTerrain object
    */
    NiTerrain* GetTerrainForEntity(egf::Entity* pEntity);

    /**
        Finds a material package with the specified file name.
        @param packageName Name of the material package.
        @return The material package with the specified name or NULL if a package of that
            name could not be found.
    */
    virtual NiSurfacePackage* FindMaterialPackage(const efd::utf8string& packageName);

    /**
        Finds a material package with the specified asset ID.
        @param packageAssetID Asset ID of the material package.
        @return The material package with the specified asset ID or NULL if a package of that
            ID could not be found.
    */
    virtual NiSurfacePackage* FindMaterialPackageAsset(const efd::utf8string& packageAssetID);

    /**
        Opens a material package from the specified location.
        @param packageAssetID Asset ID for the package file, if known.
        @param packageLocation File location for the package file, only used if the asset ID is
            not already known.
        @return The newly loaded material package if it has not already been loaded or NULL if the
            package failed to load. Note, if the material package has already been loaded,
            a pointer to the existing package is returned.
        @note Individual surfaces may not be loaded until all texture asset ids have been
            resolved which occurs asynchronously. Materials in a material package should only be
            compiled if they are marked as resolved via the IsResolved method.
    */
    NiSurfacePackage* OpenSurfacePackage(
        const efd::utf8string& packageAssetID,
        const efd::utf8string& packageLocation);

    /**
        Reload an already open material package

        @param pPackage The package to reload
    */
    void ReloadSurfacePackage(NiSurfacePackage* pPackage);

    /**
        Request that all surface packages in the asset web be loaded
    */
    void RequestLoadAllSurfacePackages();

    /**
        Helper method to look up the terrain surface package and surface based on the specified
        names.

        @param packageName Name of the surface package.
        @param surfaceName Name of the surface in the specified package.
        @param pPackage If a package with the specified name was found, stores a pointer to the
            package.
        @param pSurface If a surface of the specified name was found in the specified package,
            stores a pointer to the surface.
        @return True if both the package and surface were found, false otherwise.
    */
    efd::Bool GetPackageAndSurface(
        const efd::utf8string& packageName,
        const efd::utf8string& surfaceName,
        NiSurfacePackage*& pPackage,
        NiSurface*& pSurface);

    /**
        Pick against the terrain.
    */
    efd::Bool GetTerrainHeightAt(const efd::Point3& pt, float& height, efd::Point3& normal);

    /**
        Request to load a specific sector.
    */
    virtual void LoadSector(NiTerrain* pTerrain, efd::SInt16 sectorX, efd::SInt16 sectorY);

    /**
        Request to unload a specific sector.
    */
    virtual void UnloadSector(NiTerrain* pTerrain, efd::SInt16 sectorX, efd::SInt16 sectorY);

    /**
        Detect what sector the given filename represents.
    */
    static bool DetectSectorFromAsset(
        efd::utf8string assetPath,
        efd::SInt16& sectorX,
        efd::SInt16& sectorY);

    /// @cond EMERGENT_INTERNAL

    /// @endcond

    /// @name Message handlers
    //@{

    /**
        This message handler is called when a new entity is discovered.
        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    virtual void HandleEntityDiscoverMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been removed from the
        EntityManager.
        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    virtual void HandleEntityRemovedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been updated in the
        EntityManager.
        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    virtual void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity is entering the world
        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
     */
    virtual void HandleEntityEnterWorldMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been removed from the
        world.
        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
     */
    virtual void HandleEntityExitWorldMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        Handle an asset locater response message.
        @param pMessage The asset locater response message.
        @param targetChannel Channel the message was sent on.
    */
    virtual void HandleAssetLocatorResponse(
        const efd::AssetLocatorResponse* pMessage,
        efd::Category targetChannel);

    /**
        Handle an asset preload request.

        @param pRequest The entity that is requesting preload.
        @param targetChannel Channel the message was sent on.
    */
    virtual void HandlePreloadRequest(
        const egf::EntityPreloadRequest* pRequest,
        efd::Category targetChannel);

    //@}

protected:
    /// @name Overridden virtual functions
    /// @see efd::ISystemService
    //@{
    virtual const char* GetDisplayName() const;
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();
    //@}

    // Types of assets managed by this service
    enum AssetType
    {
        AT_Terrain,
        AT_TerrainSector,
        AT_MaterialPackage,
        AT_SurfaceTexture,

        AT_NumAssetTypes
    };

    /**
        Specific terrain sector selector class used to control what sectors are loaded
        on a particular terrain. It uses another sector selector object to perform standard
        sector selection algorithms whilst providing a mechanism to specifically load/unload/lock
        sectors.
    */
    class EE_EGMTERRAIN_ENTRY SectorSelector: public NiTerrainSectorSelector
    {
        NiDeclareRTTI;
    public:
        /// Constructor
        SectorSelector(NiTerrain* pTerrain);
        SectorSelector(NiTerrain* pTerrain, NiTerrainSectorSelector* pOrigSelector);
        /// Destructor
        ~SectorSelector();

        virtual bool UpdateSectorSelection();

        /**
            Use this function to update the selector's information about what sectors are loaded.
            This function is used when creating sectors to notify the selector that it has been
            loaded completely.
        */
        virtual void NotifySectorLOD(efd::SInt16 sectorX, efd::SInt16 sectorY, efd::SInt32 lod);

        /**
            Use this function to request that a sector be loaded to a specific level of detail
            during the next update sequence.
        */
        virtual void RequestSectorLOD(efd::SInt16 sectorX, efd::SInt16 sectorY, efd::SInt32 lod);

        /**
            Use this function to prevent the default sector selector policy from affecting the
            given sector.
        */
        virtual void LockSectorLOD(efd::SInt16 sectorX, efd::SInt16 sectorY);

        /**
            Use this function to allow the default sector selector policy to affect the specified
            sector.
        */
        virtual void UnlockSectorLOD(efd::SInt16 sectorX, efd::SInt16 sectorY);

        /**
            Unlock all sectors on the terrain so the default selector can operate without
            restrictions.
        */
        virtual void UnlockAllSectors();

    private:

        /// The set of requests still pending to be applied
        efd::map<NiTerrainSector::SectorID, efd::SInt32> m_pendingRequests;

        /// The set of sectors that are no-longer modifiable by the normal sector selector
        efd::set<NiTerrainSector::SectorID> m_lockedSectors;

        /// The sector selector defining the general selection algorithm
        NiTerrainSectorSelectorPtr m_spSelector;
    };

    /**
        Clear out all the data that has been loaded for existing terrains.
        This function is called during shutdown of the service.
    */
    void ClearLoadedData();

    /**
        Implements the asset change handler to update terrain data when the assets change.
    */
    void HandleAssetChange(const efd::utf8string& assetId, const efd::utf8string& tag);

    /**
        Raise the terrain changed message and send it out
    */
    inline void RaiseTerrainChanged();

    /**
        Remove the terrain belonging to an entity from the service. If the flag is set,
        this function will also remove the entity from the service.
    */
    virtual void RemoveTerrainEntity(egf::Entity* pEntity, efd::Bool removeEntity = false);

    /**
        Update the transformation of a terrain based on the properties of the entity
    */
    virtual void UpdateTransformation(NiTerrain* pTerrain, egf::Entity* pEntity);

    /**
        Create a link between a terrain and an entity.
    */
    virtual void AttachTerrainToEntity(NiTerrain* pTerrain, egf::Entity* pEntity);

    /**
        Request that the asset for an entity be loaded.
    */
    efd::Bool RequestLoadTerrain(egf::Entity* pEntity, efd::utf8string& assetID);

    /**
        Load the terrain asset at the given location. Once it has completed, the asset will
        be matched up to the entity that requested it.
    */
    virtual efd::Bool LoadTerrainAsset(
        const efd::utf8string& assetID,
        const efd::utf8string& fileName);

    /**
        Attempt to load a terrain asset at the given asset path
    */
    NiTerrain* LoadTerrain(
        const efd::utf8string& archivePath,
        efd::UInt32* pErrorCode,
        egf::Entity* pEntity);

    /**
        Update all the terrain entities that the service is managing
    */
    void UpdateTerrainEntities();

    /**
        Update a specific terrain with the information from the entity
    */
    void UpdateTerrain(egf::Entity* pEntity, NiTerrain* pTerrain);

    /**
        Configure the shadowing system such that it will work for the given terrain entity
    */
    void ConfigureShadowsForTerrain(egf::Entity* pEntity);

    /**
        Create a terrain object.
        Overload this function to assign custom surface libraries, asset resolvers, storage 
        policies and platform configurations.
    */
    virtual NiTerrain* CreateTerrain();

    /**
        Initialize the given terrain.

        This is used to give terrain objects certain listeners, sector selectors, and
        other attributes such as custom data policies and resource managers. 
        This is done once the terrain has successfully loaded it's configuration
    */
    virtual void InitializeTerrain(NiTerrain* pTerrain, egf::Entity* pEntity = NULL);

    /**
        Request to load the surface package at the given URI
    */
    void RequestLoadSurfacePackage(efd::utf8string kURI);

    /**
        Request to load the textures for the surfaces contained inside the given package
    */
    void RequestLoadPackageSurfaces(NiSurfacePackage* pPackage);

    /**
        Attempt to update the loaded data for the given asset by reloading it from disk.
    */
    void RefreshAsset(
        AssetType eAssetType,
        const efd::utf8string& assetID,
        const efd::utf8string& assetPath);

    /**
        Checks we have a terrain for this entity and creates the external scene graph.
    */
    void AttachSceneGraph(egf::Entity* pEntity);

    /**
        Checks we have a terrain for this entity and removes the external scene graph.
    */
    void DetachSceneGraph(egf::Entity* pEntity);    

    /**
        Check all the preloading terrains to see if they have completed preloading their data.
        This function is called in the OnTick function.
    */
    void CheckPreloadStatus();

    /**
        Find the entity that requested the given asset
    */
    egf::Entity* FindEntityByAssetLLID(const efd::AssetID& assetID);

    /**
        Check to see if a given entity has begun preloading a terrain
    */
    bool IsEntityPreloading(egf::EntityID entityID);

    /**
        Load the list of initial sectors for the terrain on the given entity.
    */
    void LoadInitialSectors(efd::utf8string assetID, egf::Entity* pEntity, bool waitForCompletion);

    /**
        Fetch the set of terrains that the service is currently handling.
    */
    void FetchTerrainSet(efd::set<NiTerrain*>& terrains);

    /**
        Detect if a specific terrain has completed it's loading cycle.

        This includes all streaming has been completed, and all referenced packages resolved.
    */
    bool IsLoadComplete(NiTerrain* pTerrain);

    /**
        Skip preloading assets in the terrain service. This immediately responds to outstanding
        preload requests, and generates an appropriate error message if the flag is specified.
    */
    void SkipPreloadingAssets(bool bError = true);

    /**
        A private callback function that is triggered whenever the surface library updates a
        package.
    */
    void OnSurfacePackageUpdated(NiTerrainSurfaceLibrary* pLibrary, NiSurfacePackage* pPackage);
    
    /**
        Notify all loaded terrains that a surface package has just been loaded
    */
    virtual void NotifySurfacePackageLoaded(
        const efd::utf8string& assetID,
        NiSurfacePackage* pPackage);

    /**
        Notify the the service that a terrain is out of date
    */
    virtual void NotifyTerrainOutOfDate(NiTerrain* pTerrain);

    /**
        Creates a terrain with the specified values.
        @param terrainSize Size of each sector of terrain.
        @param cellSize Size of each cell within a sector.
        @param materialMaskSize Size of the material mask applied on a per cell basis.
        @param lowDetailTextureSize Size of the low detail diffuse and normal map textures displayed
            on a distant terrain sector.
        @param minElevation Minimum height of the terrain.
        @param maxElevation Maximum height of the terrain.
        @param vertexSpacing Distance between vertices on the horizontal plane.
    */
    virtual NiTerrain* CreateBlankTerrain(
        efd::UInt32 terrainSize,
        efd::UInt32 cellSize,
        efd::UInt32 materialMaskSize,
        efd::UInt32 lowDetailTextureSize,
        efd::Float32 minElevation,
        efd::Float32 maxElevation,
        efd::Float32 vertexSpacing);

    /**
        Instructs the asset locater service to locate the specified asset.

        @param eAssetType The type of asset to load
        @param assetURN Asset resource name to load.
        @return True if the request was made successfully, false otherwise.
    */
    virtual efd::Bool InsertAssetLocateRequest(
        AssetType eAssetType,
        const efd::utf8string& assetURN);
    virtual efd::Bool InsertAssetRefreshRequest(
        AssetType eAssetType,
        const efd::utf8string& assetURN);
   
    /// The asset resolver to use for NiTerrain objects
    NiPointer<AssetResolver> m_spAssetResolver;

    /// The surface library to be shared across all NiTerrain objects
    NiTerrainSurfaceLibraryPtr m_spSurfaceLibrary;

    /// List of all terrain entities that this service knows about
    typedef efd::list<egf::EntityPtr> EntityList;
    EntityList m_terrainEntities;

    /// Map connecting terrain entities to actual NiTerrain objects
    typedef efd::map<egf::EntityID, NiTerrainPtr> EntityToTerrainMap;
    EntityToTerrainMap m_entityToTerrainMap;

    /// Map connecting asset ID's to actual NiTerrain objects
    typedef efd::map<efd::utf8string, NiTerrainPtr> PreloadingTerrainMap;
    PreloadingTerrainMap m_preloadingTerrainMap;

    /// Map storing terrains to preload responses
    typedef efd::map<egf::EntityPreloadResponse*, efd::utf8string> PreloadResponseToAssetMap;
    PreloadResponseToAssetMap m_preloadResponseToAssetMap;

    /// Cached system services used frequently by the Terrain service.
    efd::MessageService* m_pMessageService;
    egf::EntityManager* m_pEntityManager;
    ecr::SceneGraphService* m_pSceneGraphService;

    /// @name Categories used for asset lookup responses
    //@{
    efd::Category m_loadCategory[AT_NumAssetTypes];
    efd::Category m_refreshCategory[AT_NumAssetTypes];
    efd::Category m_assetPreloadRequestCategory;
    efd::Category m_assetPreloadResponseCategory;
    //@}

    /// Static variable to store the tag names of the terrain assets
    efd::utf8string m_assetTags[AT_NumAssetTypes];

    /// Do we want to handle asset change events?
    efd::Bool m_handleAssetChanges;

    friend class TerrainPickPolicy;
};

/// Defines a smart pointer (reference counted) for the TerrainService
typedef efd::SmartPointer<TerrainService> TerrainServicePtr;

}; // namespace

#include "TerrainService.inl"

#endif
