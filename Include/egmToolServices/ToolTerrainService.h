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
#ifndef EE_TOOLTERRAINSERVICE_H
#define EE_TOOLTERRAINSERVICE_H

#include <egmTerrain/TerrainService.h>
#include "TerrainEditGizmo.h"

namespace egmToolServices
{

class ToolTerrainService;

/**
    The tool terrain service implements the TerrainService and provides extra 
    functionalities that allow tools such as toolbench to create and edit a NiTerrain object and
    all other related object (Materials).
*/
class EE_EGMTOOLSERVICES_ENTRY ToolTerrainService : public egmTerrain::TerrainService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ToolTerrainService, efd::kCLASSID_TerrainService, egmTerrain::TerrainService);
    /// @endcond

public:

    /**
        Constructor for the terrain tool service. Sets up tool time data structures and ensures the
        run-time terrain engine is prepared for tool time editing.
    */
    ToolTerrainService();

    /**
        Creates a new material package and adds it to the terrain's service list of known material
        packages. Note, packages are not actually attached to the terrain entity until a surface 
        from a package is actually painted onto the terrain.
        @param packageName Name of the package.
        @param packageLocation File path in the asset web to save the package file.
        @return True if new package was successfully created, false otherwise.
    */
    virtual efd::Bool CreateNewMaterialPackage(
        const efd::utf8string& packageName, 
        const efd::utf8string& packageLocation);

    /**
        Saves the material package with the specified name.
        @param packageName Name of the material package to save. If a material package does not 
            exist with the specified name, a message is logged and the method is a no-op.
    */
    virtual efd::Bool SaveMaterialPackage(const efd::utf8string& packageName);

    /**
        Saves the specified material package.
        @param pPackage Package to save.
        @return True if the package was saved, false otherwise.
    */
    virtual efd::Bool SaveMaterialPackage(NiSurfacePackage* pPackage);

    /**
        Creates a new terrain material and adds it to the specified package. A package with the 
        specified name must have already been created.
        @param packageName Name of the material package.
        @param materialName Unique name to assign to the material.
        @return True if the material was created, false otherwise.
        @note Creating a new material does not assign it to the terrain entity. This occurs when a
            material is first painted onto the terrain or manually assigned to the terrain.
    */
    virtual efd::Bool CreateNewMaterial(
        const efd::utf8string& packageName, 
        const efd::utf8string& materialName);

    /**
        Changes the name of an existing material.
        @param packageName Name of the material package containing the material.
        @param oldMaterialName Old name of the material. This name is used to find the existing 
            material to rename.
        @param newMaterialName New name to give to the material.
        @return True if successful, false otherwise.
    */
    virtual efd::Bool ChangeMaterialName(
        const efd::utf8string& packageName, 
        const efd::utf8string& oldMaterialName,
        const efd::utf8string& newMaterialName);

    /**
        Removes an exiting terrain material from the existing package.
        @param packageName Name of the material package.
        @param materialName Name of the material to remove.
        @return True if the material was removed, false if either the material package was not 
            found or the material with the specified name could not be found.
    */
    virtual efd::Bool RemoveMaterial(
        const efd::utf8string& packageName, 
        const efd::utf8string& materialName);

    /**
        Checks whether a specific material can be deleted or not
    */
    efd::Bool CanDeleteMaterial(
        const efd::utf8string& packageNameUTF8, 
        const efd::utf8string& materialNameUTF8);

    /**
        Checks whether or not a material is used on the terrain.
    */
    efd::Bool IsMaterialUsed(const NiSurface* pSurface);

    /**
        Assigns the specified texture to the specified map slot on the terrain surface material.
        @param packageName Name of the material package owning the material.
        @param materialName Name of the material which which to assign the texture.
        @param tMapType Map slot with which to assign the texture.
        @param fullPath Full path to the texture file.
        @param assetId Asset id of the texture.
        @remarks The asset id is persisted when a terrain surface material is saved, not the 
            absolute path.
    */
    virtual efd::Bool AssignMaterialTexture(
        const efd::utf8string& packageName, 
        const efd::utf8string& materialName,
        NiSurface::SurfaceMapID tMapType,
        const efd::utf8string& fullPath,
        const efd::utf8string& assetId);

    /**
        Adds a new brush type overlay mesh to the service. Brush type overlays render a 
        representation of the brush type being painted on the terrain.
        @param brushTypeName Name of the brush type. Used as a key to find an overlay for a given 
            brush type.
        @param pOverlayObj Render-able object assigned to the terrain edit gizmo when a brush type 
            overlay is set to active.
    */
    virtual void AddBrushTypeOverlay(const efd::utf8string& brushTypeName, NiNode* pOverlayObj);

    /**
        Sets the gizmo mesh on the terrain edit gizmo to the overlay mesh of the brush type
        matching the specified name.
        @param brushTypeName Brush type name or key used to find the correct overlay mesh.
        @return True if the overlay mesh was set, false if an overlay mesh mapping to the specified
            brush type name could not be found.
    */
    virtual efd::Bool SetBrushTypeOverlayActive(const efd::utf8string& brushTypeName);

    /**
        Updates the inner and outer radius parameters on the standard brush type gizmo.
        @param innerRadius Radius in the range [0..1] of the inner radius.
        @param outerRadius Radius in the range [0..1] of the outer radius.
        @param brushSize Size of the brush in world units. This value is multiplied by the inner
            and outer radius to get the inner and outer radius in world units.
    */
    virtual void UpdateStandardBrushParams(
        efd::Float32 innerRadius,
        efd::Float32 outerRadius,
        efd::Float32 brushSize);

    /**
        Creates a terrain with the specified values.
        @param archivePath the root path of the terrain asset
        @param terrainSize Size of each sector of terrain.
        @param cellSize Size of each cell within a sector.
        @param materialMaskSize Size of the material mask applied on a per cell basis.
        @param lowDetailTextureSize Size of the low detail diffuse and normal map textures displayed
        on a distant terrain sector.
        @param minElevation Minimum height of the terrain.
        @param maxElevation Maximum height of the terrain.
        @param vertexSpacing Distance between vertices on the horizontal plane.
        @param[out] terrainAssetPath The calculated terrain's new asset path
    */
    virtual efd::Bool CreateTerrainAsset(
        efd::utf8string archivePath,
        efd::UInt32 terrainSize, 
        efd::UInt32 cellSize,
        efd::UInt32 materialMaskSize,
        efd::UInt32 lowDetailTextureSize, 
        efd::Float32 minElevation,
        efd::Float32 maxElevation,
        efd::Float32 vertexSpacing, 
        efd::utf8string& terrainAssetPath);

    /**
        Persists the current terrain entity.
        @param pEntity the terrain entity that needs to be saved.
        @param terrainPath The path to the terrain file.
        @return True if the data was saved successfully, false otherwise.
    */
    virtual efd::Bool SaveTerrain(egf::Entity* pEntity, const efd::utf8string& terrainPath);

    /**
        Adjusts the min/max elevation of the terrain and rebuilds the geometry based on the new
        values. 

        @param minElevation The minimum height the terrain is capable of being
        @param maxElevation The minimum height the terrain is capable of being
    */
    virtual void SetNewMinMaxElevation(efd::Float32 minElevation, efd::Float32 maxElevation);

    /**
        Creates a mesh composed of lines representing two circles, one for the inner radius of 
        the brush and one for the outer radius of the brush.
        @return An NiMesh representing the standard brush type.
    */
    virtual NiNode* CreateStandardOverlayMesh();

    /// Enables or disables the airbrush painting mode. When enabled, paint operations occur even 
    /// if the mouse is not moving and the left mouse button is held down.
    inline void EnableAirbrushMode(efd::Bool isEnabled);

    /**
        Controls whether the terrain gizmo should display inverted colors. Occurs when the painting
        direction changes (when ctrl key is pressed or released)
    */
    inline void InvertBrushColor(efd::Bool invert);

    /**
        Checks with the GizmoService whether the TerrainEditGizmo is active or not.
    */
    inline bool IsTerrainEditGizmoActive();

    /// @name Active surface management
    //@{

    /**
        Gets number of active surfaces. A surface is active if a brush is active that has a valid 
        surface mapped to it.
    */
    efd::UInt32 GetNumActiveSurfaces() const;

    /**
        Gets the active surface at the specified index.

        The list of active surfaces are used to control the highlighting of the painting guide.
    */
    NiSurface* GetActiveSurfaceAt(efd::UInt32 index);

    /// Add a surface to the list of active surfaces
    void AddActiveSurface(NiSurface* pSurfaceMaterial);

    /// Remove a surface from the list of active surfaces
    void RemoveActiveSurface(NiSurface* pSurfaceMaterial);
    
    /// Clear the list of active surfaces
    void ClearActiveSurfaces();

    //@}

    /// @name Terrain deformation
    //@{

    /**
        Apply the data stored in the heightmap buffer to the terrain.
    */
    virtual void ApplyToHeightMap(HeightMapBuffer* pHeightMap);

    /**
        Apply the data stored in the surface mask buffer to the terrain.
    */
    void ApplyMaterialMask(
        const efd::utf8string& surfaceName,
        const efd::utf8string& packageName,
        SurfaceMaskBuffer* pMaskBuffer,
        SurfaceMaskBuffer* pMaskSumBuffer);

    //@}
    
    /// Force the terrain to render it's low detail textures
    void ForceUpdateLowDetailTextures();

    /// Force the render contexts of the renderer service to re-draw themselves.
    void ForceUpdateRenderContexts();

    /// Set the debug flags to control the debug modes of the terrain shader.
    void SetDebugMode(efd::UInt32 debugMode);

    /// @name Terrain sector streaming
    //@{

    /**
        Request that the sector at the given index be unloaded. In the tool terrain
        service, this will also cause any changes to the sector to be saved to disk. 
    */
    virtual void UnloadSector(NiTerrain* pTerrain, efd::SInt16 sectorX, efd::SInt16 sectorY);

    /**
        Request that a sector be created at the given index
    */
    void CreateSector(NiTerrain* pTerrain, efd::SInt16 sectorX, efd::SInt16 sectorY);

    /**
        Check if the sector at the given index has been loaded to a certain level of detail
    */
    bool IsSectorLODLoaded(efd::SInt16 sectorX, efd::SInt16 sectorY, efd::SInt32 lod);

    /**
        Check to see if the sector at the given index is available on disk
    */
    bool IsSectorOnDisk(efd::SInt16 sectorX, efd::SInt16 sectorY);
    //@}
    
    /**
        Get the index of the sector that was last intersected by the terrain edit gizmo.
    */
    bool GetLastIntersectedSector(efd::SInt16& sectorX, efd::SInt16& sectorY);
        
    /// @name Tool callbacks to manipulate the terrain
    //@{

    /// @cond EMERGENT_INTERNAL
    /**
        Register a callback function to be called whenever a package has been loaded. 
        This function is used by the toolbench tools to allow the UI to know when 
        a new package has been loaded. 
    */
    typedef void (__stdcall *PackageLoadedCallbackType)(efd::utf8string packageName);
    void SetSurfacePackageLoadedCallback(PackageLoadedCallbackType callback);
    
    /**
        Register a callback function to be called before attempting to load a terrain asset.
        This callback function is expected to check the asset to see if it requires migration. 
        If it requires migration the callback will return true, and the service will send a
        migration message to trigger a migration from later. 

        The Toolbench TerrainService implements this callback mechanism.
    */
    typedef bool (__stdcall *CheckAssetMigrationCallbackType)(
        const efd::utf8string& assetID, 
        const efd::utf8string& fileName);
    void SetCheckAssetMigrationCallback(CheckAssetMigrationCallbackType callback);

    /**
        Register a callback function to be called when the tool terrain service detects that
        the terrain needs re-saving. 

        The Toolbench TerrainService implements this callback mechanism.
    */
    typedef void (__stdcall *TerrainDirtyCallbackType)();
    void SetTerrainDirtyCallback(TerrainDirtyCallbackType callback);

    /**
        Call this function to notify the service that the asset belonging to the given
        entity has been migrated, and is now ready to be loaded. 
    */
    void NotifyMigrationComplete(egf::Entity* pEntity);

    /**
        Call this function to notify the service that the given surface has changed recently.
        This will cause it to update on the terrains that reference it.
    */
    virtual void NotifySurfaceChanged(NiSurface* pSurface);

    /// @endcond
    //@}    

    /**
        Function that fills in information according to the data kept since the last 
        TerrainEditGizmo tick.

        @param[out] sectorID the sector index we collided with.
        @param[out] leafID the cell ID we collided with.
        @param[out] materialList a vector containing the names of all the surfaces
            on the leaf. Names are a concatenation following the format PackageName.SurfaceName
        @return Returns true if all the data was found and false otherwise
    */
    bool GetTerrainMaterialIntersectionData(
        efd::Point2& sectorID,
        efd::UInt32& leafID, 
        efd::vector<efd::utf8string>& materialList);

    /**
        Removes a given material from a give leaf.

        @param sectorID the index of the sector where the leaf can be found.
        @param leafID the index of the leaf we want to remove the material from.
        @param materialName the material name we want to remove. The name is a concatenation 
            following the format PackageName.SurfaceName
    */
    void RemoveMaterialFromLeaf(
        efd::Point2 sectorID,
        efd::UInt32 leafID,
        efd::utf8string materialName);

    /**
        Removes the given material from all terrains. This function first resolves what surface to
        remove using the package and material name parameters.

        @param packageNameUTF8 name of the package the material belongs too
        @param materialNameUTF8 name of the material to remove
    */
    bool RemoveMaterialFromTerrain(
        efd::utf8string packageNameUTF8, 
        efd::utf8string materialNameUTF8);

    /**
        Removes the given surface from all registered terrains.

        @param pSurface the surface to remove.
    */
    bool RemoveMaterialFromTerrain(const NiSurface* pSurface);

    /**
        Sets the flag to control whether the painting guide should be displayed or not.

        @param enable flag to display the painting guide.
    */
    void DisplayPaintingGuide(bool enable);

    /**
        Requests the painting guide to be rebuild from the loaded sectors.
    */
    void RequestPaintingGuideRebuild();

    /**
        Retrieves the appropriate material data for the leaf defined by leafID and belonging to 
            the given sectorIndex.

        @param sectorIndex the index of the sector the leaf belongs to
        @param leafID the ID of the leaf we want the material data for.
        @param materialNameUTF8 the name of the material we want data for
        @param pMaskBuffer Return parameter that holds the requested data can not be NULL)
        @param pSumBuffer Return parameter that holds the material mask sums
    */
    void GetSurfaceMaskData(
        efd::Point2 sectorIndex,
        efd::UInt32 leafID, 
        efd::utf8string materialNameUTF8,
        SurfaceMaskBuffer* pMaskBuffer, 
        SurfaceMaskBuffer* pSumBuffer);

    /**
        Sets the material data for the leaf defined by leafID and belonging to 
            the given sectorIndex.

        @param sectorIndex the index of the sector the leaf belongs to
        @param leafID the ID of the leaf we want to modify with the given data.
        @param materialNameUTF8 the name of the material we are setting the data to
        @param pBuffer Holds the material blending data
        @param pSumBuffer Holds the required sum data
    */
    void SetSurfaceMaskData(
        efd::Point2 sectorIndex,
        efd::UInt32 leafID, 
        efd::utf8string materialNameUTF8,
        SurfaceMaskBuffer* pBuffer, 
        SurfaceMaskBuffer* pSumBuffer);

    /**
        Accesses the Painting Guide and sets the texture to use.
    */
    bool SetPaintingGuideTexture(efd::utf8string fileName);

protected:
    /// @name ISystemService overrides
    /// @see efd::ISystemService
    //@{

    /**
        Registers a service alias for our egmTerrain::TerrainService base class.
    */
    void OnServiceRegistered(efd::IAliasRegistrar* pAliasRegistrar);

    /**
        Registers a dependency on GizmoZervice and returned  egmTerrain::TerrainService::PreInit.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        Calls the base terrain service initialization method and then registers the terrain edit 
        gizmo with the gizmo service.
    */
    virtual efd::AsyncResult OnInit();

    /**
        Updates the terrain painting guide, and may force the renderer contexts to be drawn
        or the terrain's low detail textures to be updated.
    */
    virtual efd::AsyncResult OnTick();

    /**
        Cleans out any tool specific memory and resources.
    */
    virtual efd::AsyncResult OnShutdown();

    //@}

    /**
        A streaming listener class to listen for sector load events. It will then trigger
        render of the scene again, and update the various tools. 
    */
    class EE_EGMTOOLSERVICES_ENTRY StreamingListener: public NiTerrainStreamingManager::Listener,
        public NiRefObject
    {
    public:
        /// Constructor
        StreamingListener(ToolTerrainService* pService, NiTerrain* pTerrain);

        /// Increment the reference count to this listener
        virtual void IncRefCount();
        /// Decrement the reference count to this listener
        virtual void DecRefCount();

        /// Listen to the completed streaming tasks
        virtual void ReportFinishTask(TaskID taskID, TaskType::VALUE taskType, 
            efd::UInt32 errorCode);

    private:
        /// The terrain service interested in the events
        ToolTerrainService* m_pService;

        /// The terrain the events are relevant to
        NiTerrain* m_pTerrain;
    };

    /// @name TerrainService overrides
    /// @see egmTerrain::TerrainService
    //@{

    /**
        Overridden to attach the tool service's streaming listener.
    */
    virtual void InitializeTerrain(NiTerrain* pTerrain, egf::Entity* pEntity = NULL);

    /**
        Overridden to force updating of the painting guide.
    */
    virtual void RemoveTerrainEntity(egf::Entity* pEntity, efd::Bool removeEntity = false);

    /**
        Overridden to force updating of the terrain gizmo.
    */
    virtual void UpdateTransformation(NiTerrain* pTerrain, egf::Entity* pEntity);

    /**
        Overridden to force updating of the painting guide.
    */
    virtual void AttachTerrainToEntity(NiTerrain* pTerrain, egf::Entity* pEntity);

    /**
        Overridden to implement detection of assets that require migration.
    */
    virtual efd::Bool LoadTerrainAsset(const efd::utf8string& assetID, 
        const efd::utf8string& fileName);

    /**
        Overridden to detect when a surface package has completed loading to trigger 
        a call to the registered surface package loaded callback.
    */
    virtual void NotifySurfacePackageLoaded(const efd::utf8string& assetID, 
        NiSurfacePackage* pPackage);

    /**
        Overridden to allow the document to be dirtied when an old terrain asset is
        detected.
    */
    virtual void NotifyTerrainOutOfDate(NiTerrain* pTerrain);

    //@}

    // Mesh overlay map
    typedef efd::map<efd::utf8string, NiNodePtr> OverlayMeshMap;
    OverlayMeshMap m_overlayMeshes;
    
    // List of active painting materials
    typedef efd::list<NiSurface*> SurfaceMaterialList;
    SurfaceMaterialList m_activeSurfaceMaterials;

    // Set up some constants which control the detail of the lines depicting the radii.
    const efd::UInt16 k_numInnerSegments;
    const efd::UInt16 k_numOuterSegments;
    const efd::UInt16 k_numBrushVertices;

    // Terrain edit gizmo variables
    efd::utf8string m_activeGizmoName;
    TerrainEditGizmoPtr m_spTerrainEditGizmo;

    // Callback functions for receiving events in the tool UI
    PackageLoadedCallbackType m_callbackPackageLoadedCallback;
    CheckAssetMigrationCallbackType m_callbackCheckAssetMigration;
    TerrainDirtyCallbackType m_callbackTerrainDirty;

    /// Flag to control re-rendering of low detail textures
    bool m_renderLowDetailTextures;
    /// Flag to control the re-rendering of the renderer contexts
    bool m_invalidateRenderContexts;

private:
    ToolTerrainService& operator=(const ToolTerrainService&) { return *this; }
};

}

#include "ToolTerrainService.inl"

#endif
