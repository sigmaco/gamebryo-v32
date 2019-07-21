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
#ifndef NITERRAIN_H
#define NITERRAIN_H

#include <NiRefObject.h>
#include <NiSmartPointer.h>
#include <NiFlags.h>
#include <efd/ecrLogIDs.h>

#include "NiTerrainLibType.h"
#include "NiRay.h"
#include "NiTerrainResourceManager.h"
#include "NiTerrainSector.h"
#include "NiTerrainSectorSelector.h"
#include "NiTerrainStreamingManager.h"
#include "NiTerrainDeformationBuffer.h"
#include "NiTerrainDecalManager.h"
#include "NiTerrainAssetReference.h"
#include "NiTerrainSurfaceLibrary.h"

class NiTerrainConfiguration;
class NiTerrainDataSnapshot;
class NiTerrainFile;

/**
    The terrain class is the main entry point to the NiTerrain library. As a NiNode, it can be 
    attached to a scene and can hold NiTerrainSector as children. The terrain does not hold any
    geometry as this is left to the NiTerrainSector that are attached to it.
 */
class NITERRAIN_ENTRY NiTerrain : public NiNode
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:
    enum ErrorCodes
    {
        /// Terrain file loading errors
        /// Defined path does not exist
        EC_INVALID_ARCHIVE_PATH                 = 1 << 1,
        /// An error code indicating an invalid terrain file
        EC_TERRAIN_FILE_INVALID                 = 1 << 2,
        /// An error code indicating the file is of an old format
        EC_TERRAIN_FILE_OUTOFDATE               = 1 << 3,
        /// An error code indicating the file was missing data
        EC_TERRAIN_MISSING_DATA                 = 1 << 4,

        /// Sector file loading errors
        /// Failed to load from a sector file
        EC_SECTOR_INVALID_FILE                  = 1 << 5,
        /// File format is not of the latest supported version
        EC_SECTOR_OUTOFDATE                     = 1 << 6,
        /// Sector size and size defined in the file do not correspond to the terrain 
        EC_SECTOR_INVALID_SECTOR_SIZE           = 1 << 7,
        /// failed to create the streams
        EC_SECTOR_STREAM_CREATION_ERROR         = 1 << 8,
        /// File has missing data
        EC_SECTOR_MISSING_DATA                  = 1 << 9,
        /// The file was loaded successfully
        EC_SECTOR_LOADED                        = 1 << 10,
        /// The file was loaded successfully
        EC_SECTOR_UNLOADED                      = 1 << 11,
        /// The file was saved successfully
        EC_SECTOR_SAVED                         = 1 << 12,
        /// The file is read only
        EC_SECTOR_IS_READ_ONLY                  = 1 << 13,
        /// The streaming task on a sector was cancelled
        EC_SECTOR_STREAMING_CANCELLED           = 1 << 14,
        /// Saving of custom data failed
        EC_SECTOR_SAVE_CUSTOM_DATA_FAILED       = 1 << 15,
        /// Loading of custom data failed
        EC_SECTOR_LOAD_CUSTOM_DATA_FAILED       = 1 << 16,

        /// Surface errors
        /// An error code indicating an invalid surface package was specified
        EC_SURFACE_INVALID_PACKAGE              = 1 << 17,
        /// An error code indicating an empty surface package was specified
        EC_SURFACE_EMPTY_PACKAGENAME            = 1 << 18,
        /// An error code indicating a surface failed to load
        EC_SURFACE_FAILED_LOADSURFACE           = 1 << 19,

        /// Low detail texture rendering error codes
        /// An error code indicating the low resolution texture failed to be rendered
        EC_LRT_RENDERING_FAILED                 = 1 << 20,
        /// Insufficient video memory to render low detail texture
        EC_LRT_INSUFICIENT_VRAM                 = 1 << 21,
        /// Required data is not loaded to render the low detail texture 
        EC_LRT_SCENE_CREATION_FAILED            = 1 << 22,
        /// Low detail texture creation failed
        EC_LRT_TEXTURE_CREATION_FAILED          = 1 << 23,
        /// Low detail texture render click creation failed
        EC_LRT_CLICK_CREATION_FAILED            = 1 << 24
    };

    ///@name Expose ResourceManager type enumerations
    //@{
    /// Texture type enumeration
    typedef NiTerrainResourceManager::TextureType TextureType;
    /// Stream type enumeration
    typedef NiTerrainResourceManager::StreamType StreamType;
    //@}

    /**
        This class is used to store callbacks for reading and writing files to do with 
        the storage of the terrain data. These callbacks can be changed to force terrain to
        be stored in different formats.
    */
    class NITERRAIN_ENTRY StoragePolicy
    {
    public:
        /// Open sector file callback type
        typedef NiTerrainSectorFile* (*OpenSectorCallback)(const char* kTerrainArchive, 
            NiInt32 iSectorX, NiInt32 iSectorY, bool bWriteAccess);
        /// Open terrain file callback type
        typedef NiTerrainFile* (*OpenTerrainCallback)(const char* kSectorFile, bool bWriteAccess);

        /// Constructor (Loads default callbacks)
        StoragePolicy();

        /// The function to call in order to open a sector file for read
        OpenSectorCallback m_kOpenSectorRead;
        /// The function to call in order to open a sector file for write
        OpenSectorCallback m_kOpenSectorWrite;
        /// The function to call in order to open a terrain file for read
        OpenTerrainCallback m_kOpenTerrainRead;
        /// The function to call in order to open a terrain file for write
        OpenTerrainCallback m_kOpenTerrainWrite;

        /// Request that an asset be resolved
        void ResolveAssetReference(NiTerrainAssetReference* pkReference);

        /// Set the asset resolver
        void SetAssetResolver(NiTerrainAssetResolverBase* pkResolver);
        /// Get the asset resolver
        NiTerrainAssetResolverBase* GetAssetResolver();

    private:
        /// Storage for the asset resolver object used to resolve AssetID's into paths
        NiTerrainAssetResolverBasePtr m_spAssetResolver;
    };

    /**
        This class is used to define how to handle custom data attached to or related to the 
        terrain. This data may even be stored within a custom file format to make it's existance
        seamless with the terrain library. A custom data policy for PhysX is implemented in the 
        PhysX libraries to enable PhysX support on terrain.
    */
    class NITERRAIN_ENTRY CustomDataPolicy: public NiRefObject
    {
    public:

        /// Returns the custom policy's required data tags
        virtual efd::UInt32 GetLoadPrecacheFields();
        /// Begin loading custom data for a particular sector. Called by the update thread.
        virtual bool BeginLoadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD, 
            NiTerrainSectorFile* pkFile);
        /// Load custom data for a particular sector.
        virtual bool LoadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD, 
            NiTerrainSectorFile* pkFile);
        /// Finish loading custom data for a particular sector. Called by the update thread.
        virtual bool EndLoadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD, 
            NiTerrainSectorFile* pkFile);
        /// Begin unloading custom data for a particular sector. Called by the update thread.
        virtual bool BeginUnloadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD);
        /// Unload custom data for a particular sector.
        virtual bool UnloadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD);
        /// Finish unloading custom data for a particular sector. Called by the update thread.
        virtual bool EndUnloadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD);
        /// Save custom data for a particular sector.
        virtual bool SaveCustomData(NiTerrainSector* pkSector, NiTerrainSectorFile* pkFile);
    };

    /**
        This class is used to provide a base class for custom visitor objects to be passed in when 
        querying metadata.
    */
    class NITERRAIN_ENTRY MetaDataVisitor
    {
    public:
        /// Virtual destructor
        virtual ~MetaDataVisitor();

        /**
            Visitor function. This function is called for every surface encountered on the terrain
            by the visitor and the corresponding weight of that surface at that point. 
        */
        virtual void Visit(const NiSurface* kSurface, const NiMetaData& kData, float fWeight) = 0;
    };

    /// @name Constructor and Destructor
    //@{

    /**
        Default constructor. If a null meta data store is given, then the
        default static meta data store singleton is used.
    */
    NiTerrain();

    /// Destructor
    virtual ~NiTerrain(void);

    /**
        Destroy the data stored within this object to allow the SDM etc to be shutdown whilst this
        object still exists. Once this function is called, all calls to this NiTerrain object are
        invalid and should be avoided. The only function that should be called upon this object
        once it's data has been destroyed is the NiRefObject interface and its destructor.
    */
    void DestroyData();
    //@}

    /// @cond EMERGENT_INTERNAL
    // Sector management

    /**
        Detach a sector from this terrain.
        @param pkSector sector to detach from this terrain
    */
    void RemoveSector(NiTerrainSector* pkSector);

    /**
        Attach a sector to this terrain component.
        @param pkSector sector component to attach to this terrain component
    */
    void AddSector(NiTerrainSector* pkSector);

    /**
        Get the sector at a specified index.
        @param iSectorX X coordinate of the sector to return
        @param iSectorY Y coordinate of the sector to return
        @return the sector at the given coordinates
    */
    NiTerrainSector* GetSector(NiInt16 iSectorX, NiInt16 iSectorY) ;

    /**
        Get the sector at a specified index.
        @param iSectorX X coordinate of the sector to return
        @param iSectorY Y coordinate of the sector to return
        @return the sector at the given coordinates
    */
    const NiTerrainSector* GetSector(NiInt16 iSectorX, NiInt16 iSectorY) const;

    /**
        Create a sector with the specified index.
        @param iSectorX X coordinate of the sector to create
        @param iSectorY Y coordinate of the sector to create
        @return the sector created at the given coordinates
    */
    NiTerrainSector* CreateSector(NiInt16 iSectorX, NiInt16 iSectorY);

    /**
        Update the list of sectors with this list, any sectors not already
        a part of the terrain will be created and any removed will be unloaded
        from memory
        @param kSectorList the list of sector to update our sectors with
    */
    void UseSectorList(const NiTPrimitiveSet<NiUInt32>& kSectorList);

    /**
        @return the number of attached sector components that currently have
        data loaded in memory.
    */
    NiUInt32 GetNumLoadedSectors() const;
    /// @endcond

    /**
        This function will return true if during the last update a deformation
        or translation/scaling/rotation of the terrain occurred. This
        function is useful in determining when to update any water objects
        associated with this terrain.
    */
    inline bool HasShapeChangedLastUpdate();
    
    /**
        This function will return true if during the last update a deformation
        or translation/scaling/rotation of the terrain occurred. This
        function is useful in determining when to update any water objects
        associated with this terrain.
    */
    inline void SetShapeChangedLastUpdate(bool bChanged);

    /**
        Generate the absolute path to the surfaces used for this terrain
        based upon the terrain path given.
        
        @param kTerrainPath the terrain path
        @return the absolute path to use
    */
    const NiFixedString CreateSurfacePath(
        const NiFixedString& kTerrainPath);

    /**
        Trigger a save of all attached sectors data to disk, in the directory
        and format currently specified by this component.

        @param pcFileName The archive directory to save to. If this value is
            0 then the currently set archive directory will be used.
        @param puiErrorCode Pointer to the OR'd mask of error codes from the
            operation. Error codes are enumerated in NiTerrainSector.
        @return whether saving was successful or not
    */
    bool Save(const char* pcFileName = 0, NiUInt32* puiErrorCode = 0);

    /**
        Trigger a load of all attached sectors data from disk, according to
        to the format currently specified.3

        @param pcFileName The archive directory to load from. If this value is
            0 then the currently set archive directory will be used.
        @param puiErrorCode Pointer to the OR'd mask of error codes from the
            operation. Error codes are enumerated in NiTerrainSector.
        @return whether loading was successful or not
    */
    bool Load(const char* pcFileName = 0, NiUInt32* puiErrorCode = 0);

    /**
        Adds a load or unload task to the paging manager as required so that the given is loaded in
        the background to the specified LOD.

        @param sIndexX the x index of the sector we want to load
        @param sIndexY the y index of the sector we want to load
        @param iLOD the LOD that should be loaded for this sector
        @returns true if this page request was successfully added to the loading managers queue,
            false if it could not be added (for example, the sector is already being paged)
    */
    bool PageSector(NiInt16 sIndexX, NiInt16 sIndexY, NiInt32 iLOD);

    /**
        Creates a new task in the loading manager to create a new sector at the given index with a
        blank height map. The task will be executed as normal in the background, if enabled. This 
        function assumes that no sector has been paged in at this index.

        @param sIndexX the x coordinate of the sector to create a task for
        @param sIndexY the y coordinate of the sector to create a task for
        @param bWaitForCompletion whether we should wait for the end of the task
        @returns false if a task could not be added to the loading manager, or a sector already
            exists at the given index.
    */
    bool CreateBlankSector(NiInt16 sIndexX, NiInt16 sIndexY, bool bWaitForCompletion = false);

    /**
        Request that the terrain rebuild the geometry on all it's loaded sectors. This function
        should be called after setting the min and max heights and other functions that
        affect the geometry of a terrain.
        @return whether rebuilding was successful or not
    */
    bool RebuildGeometry();

    /**
        Check to see if the specified sector exists on the disk.
        This function is to be used in figuring out if a sector exists before
        requesting that sector to load. Loading a sector that does not exist 
        on disk will result in a blank sector being created at that position.

        @param iSectorX X coordinate of the sector to check
        @param iSectorY Y coordinate of the sector to check
        @return returns true if the sector was found. false otherwise
    */
    bool IsSectorOnDisk(NiInt16 iSectorX, NiInt16 iSectorY);

    /**
        Loads the layer material masks for the sector specified by the given sector coordinates.

        @param sXIndex X index of the sector to load.
        @param sYIndex Y index of the sector to load.
        @param puiErrorCode Optional pointer to an OR'd mask of error codes from the operation.
        @return whether this was successful or not
    */
    bool LoadSectorMaterialMasks(NiInt16 sXIndex, NiInt16 sYIndex, NiUInt32* puiErrorCode = 0);

    /**
        The path containing all the sector folders to be used by this terrain.
        An update must be executed on the terrain for changes to this value
        to be reflected in the sectors.

        @note during runtime, changing the storage filename could cause a
        large amount of loading to occur on the next update. It is recommended
        set the storage filename once upon initialization of the terrain.
    **/
    inline const NiFixedString& GetArchivePath() const;

    /**
        The path containing all the sector folders to be used by this terrain.
        An update must be executed on the terrain for changes to this value
        to be reflected in the sectors.

        @note during runtime, changing the storage filename could cause a
        large amount of loading to occur on the next update. It is recommended
        set the storage filename once upon initialization of the terrain.
    **/
    inline void SetArchivePath(const NiFixedString& kArchive);

    //@{
    /**
        The factor used to adjust the LOD viewable at different distances.
        Values above 1 adjust the LOD ranges geometrically, increasing distant
        and foreground detail equally. Values below 1 linearly shift the
        LOD ranges closer to the camera, until only lower levels of detail
        can be seen.
    */    
    inline void SetLODScale(float fScale);
    inline float GetLODScale() const;
    inline float GetLODShift() const;
    //@}

    /**
        Use these functions to control the method used to perform LOD
        transitions on the terrain. The following modes are supported:
         LOD_MODE_2D - Uses the camera's X and Y position to determine
          the level of detail to display. Z is ignored.
         LOD_MODE_25D - Uses the camera's X and Y position as in 2D mode,
          but a maximum level of detail is placed on the terrain
          according to the camera's Z height.
         LOD_MODE_3D - Uses the camera's XYZ position to determine the
          level of detail to display. This mode may cause cracks and popping
          to appear on terrains that have quite steep regions.
    */
    inline NiUInt32 GetLODMode() const;

    /**
        Use these functions to control the method used to perform LOD
        transitions on the terrain. The following modes are supported:
         LOD_MODE_2D - Uses the camera's X and Y position to determine
          the level of detail to display. Z is ignored.
         LOD_MODE_25D - Uses the camera's X and Y position as in 2D mode,
          but a maximum level of detail is placed on the terrain
          according to the camera's Z height.
         LOD_MODE_3D - Uses the camera's XYZ position to determine the
          level of detail to display. This mode may cause cracks and popping
          to appear on terrains that have quite steep regions.
    */
    inline bool SetLODMode(NiUInt32 uiLODMode);

    /**
        The size of each quadtree block in the terrain in quads. The width
        of the block in vertices will be (BlockSize + 1).

        @note a each block shares vertices with neighboring blocks.
    */
    inline NiUInt32 GetCellSize() const;

    /**
        The size of each quadtree block in the terrain in quads. The width
        of the block in vertices will be (BlockSize + 1).

        @note a each block shares vertices with neighboring blocks.
    */
    inline bool SetCellSize(NiUInt32 uiCellSize);

    /**
        The number of levels of detail to allow per sector NOT including
        the highest level of detail. i.e. a setting of 0 effectively makes
        the terrain a simple heightfield.
    */
    inline NiUInt32 GetNumLOD() const;

    /**
        The number of levels of detail to allow per sector NOT including
        the highest level of detail. i.e. a setting of 0 effectively makes
        the terrain a simple heightfield.
    */
    inline bool SetNumLOD(NiUInt32 uiNumLOD);

    /**
        The minimum and maximum heights of the terrain. These values are used to
        interpret the height map of the terrain during loading and saving.
        A call to RebuildGeometry must be made after changing these values.
    */
    inline void SetMaxHeight(float fHeight);

    /**
        The minimum and maximum heights of the terrain. These values are used to
        interpret the height map of the terrain during loading and saving.
        A call to RebuildGeometry must be made after changing these values.
    */
    inline float GetMaxHeight() const;
    
    /**
        The minimum and maximum heights of the terrain. These values are used to
        interpret the height map of the terrain during loading and saving.
        A call to RebuildGeometry must be made after changing these values.
    */
    inline void SetMinHeight(float fHeight);

    /**
        The minimum and maximum heights of the terrain. These values are used to
        interpret the height map of the terrain during loading and saving.
        A call to RebuildGeometry must be made after changing these values.
    */
    inline float GetMinHeight() const;

    /**
        The distance between each vertex of the terrain. (Allows X-Y scaling without the Z).
    */
    inline void SetVertexSpacing(float fSpacing);

    /**
        The distance between each vertex of the terrain. 
    */
    inline float GetVertexSpacing() const;

    /**
        Transform a terrain's heightmap value into a terrain space height
    */
    inline float CalcTerrainSpaceHeight(efd::UInt16 heightMapValue);

    /**
        Transform a terrain's heightmap value into a world space height
    */
    inline float CalcWorldSpaceHeight(efd::UInt16 heightMapValue);

    /**
        Get function for the sector mask size.
    */
    efd::UInt32 GetMaskSize() const;

    /**
        Set function for the sector mask size.
    */
    bool SetMaskSize(efd::UInt32 uiMaskSize);

    /**
        Get function for the sector low detail texture size.
    */
    NiUInt32 GetLowDetailTextureSize() const;

    /**
        Set function for the sector low detail texture size.
    */
    bool SetLowDetailTextureSize(NiUInt32 uiMaskSize);

    /**
        Get function for the low detail specular power
    */
    float GetLowDetailSpecularPower() const;

    /**
        Set function for the low detail specular power
    */
    bool SetLowDetailSpecularPower(float fPower);

    /**
        Getfunction for the low detail specular intensity
    */
    float GetLowDetailSpecularIntensity() const;

    /**
        Set function for the low detail specular intensity
    */
    bool SetLowDetailSpecularIntensity(float fIntensity);

    /**
        The size of a sector in vertices based upon the block size and 
        NumLOD settings. The calculated sector size is calculated using
        the following formula: BlockSize * (2 ^ NumLOD) + 1.

        @return the size of a sector
    */
    NiUInt32 GetCalcSectorSize() const;   

    /**
        Function that returns a map of all the sectors currently loaded.

        @returns sectors currently loaded
    */
    const NiTMap<NiUInt32, NiTerrainSector*>& GetLoadedSectors() const;

    /**
        Sets the number of cells that can be rendered in one frame during a 
        low detail texture update.

        @param uiNumCells Number of cells to be rendered
    */
    void SetRenderedCellsPerFrame(NiUInt32 uiNumCells);

    /**
        Gets the number of cells that can be rendered in one frame during a 
        low detail texture update.

        @return the number of cells to be rendered
    */
    NiUInt32 GetRenderedCellsPerFrame();

    /**
        Get the NiRenderStep used to update the Low detail textures on 
        all of the sectors. The first call to this function will create
        the renderstep, all other calls will simply return the previously 
        created one. This function may be called to allow terrains that are
        often modified to be updated using the frame rendering system.

        @return the low detail render step
    */
    NiRenderStep* GetLowDetailRenderStep();

    /**
        Calling this function forces the low detail textures of the terrain's 
        sectors to be updated immediately. This may involve rendering to a 
        number of offscreen textures during this call. This method is provided
        as an alternative to using the frame rendering system, and allows
        the textures to be explicitly told to update.

        @param puiErrorCode returned code to give extra information upon failure
        @return true if successful
    */
    bool RenderLowDetailTextures(NiUInt32* puiErrorCode = 0);

    /**
        Call this function to mark the entire terrain for re-rendering to the low detail diffuse 
        texture during the next call to RenderLowDetailTextures.
    */
    void InvalidateLowDetailTexture();

    /// @name Data Painting
    //@{

    /**
        Initialize a deformation buffer for the selected world space region

        @param kWorldSpaceRegion affected worldspace region
        @param pkBuffer the surface mask buffer to initialize
        @return true if successful
    */
    bool InitializeDeformationBuffer(const NiRect<efd::SInt32>& kWorldSpaceRegion, 
        SurfaceMaskBuffer* pkBuffer);

    /**
        Initialize a deformation buffer for the selected world space region

        @param kWorldSpaceRegion affected worldspace region
        @param pkBuffer the height map buffer to initialize
        @return true if successful
    */
    bool InitializeDeformationBuffer(const NiRect<efd::SInt32>& kWorldSpaceRegion, 
        HeightMapBuffer* pkBuffer);

    /**
        Get the mask that a surface uses based on the given heightmap region. 
        This function will populate the given buffer with the relevant information for that mask. 
        The top-left coordinate used is given by the top-left sectorID and the heightmap region 
        coordinate. The bottom-right coordinate is specified in the same way. 
        NOTE: The returned buffer will contain the official region of the returned mask as it may
        differ from the region given. 

        @param pkSurface The surface that the mask is for.
        @param kTerrainSpaceRegion The coordinates of the top-left and bottom-right pixels in 
            heightmap space.
        @param pkMaskBuffer The buffer that contains the mask data to apply to the terrain.
        @param pkMaskSumBuffer the buffer that conatins the mask's sum data to use on the terrain
        @param pkSnapshot the terrain's cells current data buffers
        @return true if successful
    */
    bool GetSurfaceMask(
        const NiSurface* pkSurface, 
        NiRect<efd::SInt32> kTerrainSpaceRegion,
        SurfaceMaskBuffer* pkMaskBuffer, 
        SurfaceMaskBuffer* pkMaskSumBuffer = NULL,
        NiTerrainDataSnapshot* pkSnapshot = NULL);

    /**
        Get the mask that a surface uses based on the given heightmap region. 
        This function will populate the given buffer with the relevant information for that mask. 
        The top-left coordinate used is given by the top-left sectorID and the heightmap region 
        coordinate. The bottom-right coordinate is specified in the same way. 
        NOTE: The returned buffer will contain the official region of the returned mask as it may
        differ from the region given. 

        @param uiSurfaceIndex The surface index that the mask is for.
        @param kTerrainSpaceRegion The coordinates of the top-left and bottom-right pixels in 
            heightmap space.
        @param pkMaskBuffer The buffer that contains the mask data to apply to the terrain.
        @param pkMaskSumBuffer the buffer that conatins the mask's sum data to use on the terrain
        @param pkSnapshot the terrain's cells current data buffers
        @return true if successful
    */
    bool GetSurfaceMask(efd::SInt32 uiSurfaceIndex, 
        NiRect<efd::SInt32> kTerrainSpaceRegion,
        SurfaceMaskBuffer* pkMaskBuffer, 
        SurfaceMaskBuffer* pkMaskSumBuffer = NULL,
        NiTerrainDataSnapshot* pkSnapshot = NULL);

    /**
        Set the mask that a surface uses within a specific region
        
        @param pkSurface The surface to set the mask of.
        @param pkBuffer The buffer that contains the mask data to apply to the terrain.
        @param pkMaskSumBuffer the buffer that conatins the mask's sum data to use on the terrain
        @return true if successful
    */
    bool SetSurfaceMask(const NiSurface* pkSurface, SurfaceMaskBuffer* pkBuffer, 
        SurfaceMaskBuffer* pkMaskSumBuffer);

    /**
        Set the mask that a surface uses within a specific region
        
        @param uiSurfaceIndex The surface index to set the mask of.
        @param pkBuffer The buffer that contains the mask data to apply to the terrain.
        @param pkMaskSumBuffer the buffer that conatins the mask's sum data to use on the terrain
        @return true if successful
    */
    bool SetSurfaceMask(efd::SInt32 uiSurfaceIndex, SurfaceMaskBuffer* pkBuffer, 
        SurfaceMaskBuffer* pkMaskSumBuffer);

    /**
        Add the specified surface to the cells in the given region. 

        @param uiSurfaceIndex the Index to add the surface at
        @param kAffectedSectorRange the Range on the affected sector
        @param kMaskRegion the affected mask region
        @return true if successful
    */
    bool AddSurface(efd::UInt32 uiSurfaceIndex, NiRect<efd::SInt32> kAffectedSectorRange, 
        NiRect<efd::SInt32> kMaskRegion);

    /**
        Get the heightmap from a particular region of the terrain and return it in a buffer.
        The heightmap region specified is in terrain space and is an inclusive range.

        @param kTerrainSpaceRegion the inclusive region of the heightmap to fetch.
        @param pkBuffer a pointer to the buffer to fill with the requested data
        @param pkSnapshot the terrain's cells current data buffers
        @return true if the operation was successful

    */
    bool GetHeightMap(NiRect<efd::SInt32> kTerrainSpaceRegion, HeightMapBuffer* pkBuffer,
        NiTerrainDataSnapshot* pkSnapshot = NULL);

    /**
        Set the heightmap of a particular region of the terrain based on the contents of the 
        specified buffer. The buffer must have been initialized first by a call to GetHeightMap. 
        NOTE: This function will only succeed if the terrain is in tool mode.

        @param pkBuffer The buffer containing the new data.
        @return true if the operation was successful
    */
    bool SetHeightMap(HeightMapBuffer* pkBuffer);

    /**
        Restore a snapshot of the terrain's data immediately. The snapshot is generally built
        up over a series of GetHeightmap and GetSurfaceMask calls in connection with later set 
        operations. This function thus allows an 'undo' of any actions performed.
        NOTE: This function will only succeed if the terrain is in tool mode.
        @param pkSnapshot the snapshot to retore
    */
    void RestoreDataSnapshot(NiTerrainDataSnapshot* pkSnapshot);

    //@}

    /// @name Raycasting collision
    //@{
    /**
        Find the closest point of collision on the terrain with the given ray.
        The collision information is placed within the ray itself. This includes
        collision point, collision normal and collided cell.

        @param kRay Ray with which to find the collision point. This is as well
            a return parameter and information about the collision point will
            be added in the ray. The ray should hold information about its
            origin and its direction.
        @param uiDetailLOD Maximum detail level in which to search for an
            intersection.
        @return true if collided false otherwise
    */
    bool Collide(NiRay& kRay, NiUInt32 uiDetailLOD = NiTerrainUtils::ms_uiMAX_LOD) const;

    /**
        Test for a collision. No actual collision points are found as this
        function only tests to see if a collision exists.

        @param kRay Ray with which to find the collision point. The ray
            should hold information about its origin and its direction.
        @param uiDetailLOD Maximum detail level in which to search for an
            intersection.
        @return true if collision was detected
    */
    bool Test(NiRay& kRay, 
        NiUInt32 uiDetailLOD = NiTerrainUtils::ms_uiMAX_LOD) const;
    //@}

    /// @name Decals
    //@{

    /**
        Creates a decal on the terrain according to the information given.
        Note that if only a texture and a position are given, the decal
        will be created with default values.

        @param pkDecalTexture NiTexture to apply on the decal.
        @param kPosition Position in world coordinates around which to center
            the decal. The decal will be aligned and projected to the surface
            of the terrain.
        @param uiSize Side length of the decal. The decal will always be square
            so this represents both the X and Y components
        @param uiRatio The scale of the decal texture itself within the decal.
            A larger ratio value will result in a smaller texture within the
            decal.
        @param fTimeOfDeath accum application time at which the decal will be
            destroyed
        @param fDecayLength Time, in seconds, before fTimeOfDeath that the
            decal will start to become transparent
        @param fDepthBiasOffset Small offset to apply to the decal such that
            it does not cause depth buffer fighting artifacts.
        @return A pointer to the created decal object. Care should be taken,
            as this pointer will become invalid once the decal has expired.
    */
    NiTerrainDecal* CreateDecal(NiTexture* pkDecalTexture,
        NiPoint3 kPosition, NiUInt32 uiSize = 2,
        NiUInt32 uiRatio = 1, float fTimeOfDeath = 0.0f,
        float fDecayLength = -1.0f, float fDepthBiasOffset = 0.005f);

    /**
        Add a decal object to the terrain's decal manager
        @param pkDecal the decal to add to the manager
    */
    void AddDecal(NiTerrainDecal* pkDecal);
   
    /**
        Remove a decal object from the terrain
        @param pkDecal pointer to the decal to remove
    */
    void RemoveDecal(NiTerrainDecal* pkDecal);

    //@}

    /// @name Metadata and surface querying
    //@{

    /**
        Collide the given ray with the terrain, at the given detail level
        to find the alpha of the given surface at that point. Collision
        world location is placed in the ray

        @param kRay ray to collide with the terrain
        @param pkSurface Surface we want the alpha value of
        @param ucOpacity Discovered alpha value.
        @param uiDetailLevel Detail level
        @param bIncludeLowerDetail Checks lower detail levels for mask values
            as well.
        @return returns true if successful false otherwise
    */
    bool GetSurfaceOpacity(NiRay& kRay, const NiSurface* pkSurface, NiUInt8& ucOpacity, 
        NiUInt32 uiDetailLevel = NiTerrainUtils::ms_uiMAX_LOD, bool bIncludeLowerDetail = true) 
        const;

    /**
        Gets all the meta-data from the terrain where the point at which the
        meta-data is retrieved is computed by intersecting with the terrain
        along the specified ray. Note, the meta-data associated with materials
        that are not impacting the terrain at the computed intersection (the
        layer mask has a zero weight) are not returned.
        @param kRay Ray with which to intersect the terrain.
        @param kMetaData Map of terrain materials to the meta-data associated
            with that material.
        @return True if successful, false otherwise.
    */
    bool GetMetaData(NiRay& kRay, efd::map<efd::utf8string, NiMetaData>& kMetaData) 
        const;

    /**
        Gets all the meta-data from the terrain at the specified intersection
        point. Note, the meta-data associated with materials that are not
        impacting the terrain at the computed intersection (the layer mask has
        a zero weight) are not returned.
        @param kIntersectionPt Intersection point with which to retrieve
            meta data.
        @param pkLeaf Terrain leaf at which the intersection occurred. This is
            usually retrieved from the ray after a collision has occurred.
        @param kMetaData Map of terrain materials to the meta-data associated
            with that material.
    */
    void GetMetaData(const NiPoint3& kIntersectionPt, const NiTerrainCell *pkLeaf, 
        efd::map<efd::utf8string, NiMetaData>& kMetaData) const;

    /**
        Calls a visitor functor for each meta-data object on a surface with a
        non-zero opacity at the specified intersection point.
        @param kIntersectionPt Intersection point with which to retrieve
            meta-data.
        @param pkLeaf Terrain leaf at which the intersection occurred. This is
            usually retrieved from the ray after a collision has occurred.
        @param pkVisitor Visitor functor that will be called for each meta-data
            object found on a surface with non-zero opacity at the intersection pt.
    */
    void QueryMetaData(const NiPoint3& kIntersectionPt, const NiTerrainCellLeaf *pkLeaf,
        MetaDataVisitor* pkVisitor) const;

    /**
        Gets all the meta-data from the terrain at the intersection point
        between the given ray and the terrain. Also returns a blended meta-data
        for all the meta data values at this point.
        @param kRay Ray with which to intersect the terrain.
        @param kMetaData Map of terrain materials to the meta-data associated
            with that material.
        @param kBlendedMetaData the resulting blended meta data values
        @return True if successful, false otherwise.
    */
    bool GetBlendedMetaData(NiRay& kRay, efd::map<efd::utf8string, NiMetaData>& kMetaData, 
        NiMetaData& kBlendedMetaData) const;

    /**
        Gets all the meta-data from the terrain at the given point.
        Also returns a blended meta-data for all the meta data values at
        this point.
        @param kIntersectionPt Intersection point with which to retrieve
            meta data.
        @param pkLeaf Terrain leaf at which the intersection occurred. This is
            usually retrieved from the ray after a collision has occurred.
        @param kMetaData Map of terrain materials to the meta-data associated
            with that material.
        @param kBlendedMetaData the resulting blended meta data values
        @return True if successful, false otherwise.
    */
    void GetBlendedMetaData(const NiPoint3& kIntersectionPt, const NiTerrainCell *pkLeaf, 
        efd::map<efd::utf8string, NiMetaData>& kMetaData, NiMetaData& kBlendedMetaData) const;

    //@}


    ///@name Surface Management Functions
    //@{
    /**
        Get the density of the material mask pixels per vertex.
        @return The resulting density
    */
    float GetSurfaceMaskDensity();
    
    /**
        Add a surface to the terrain surface index to allow that surface
        to be painted on a sector of this terrain. 

        @param pkSurface the surface to allow painting with
        @return the index that surface is added to
    */
    NiInt32 AddSurface(const NiSurface* pkSurface);

    /**
        Insert a surface to the specified terrain index. The index must be empty in order
        to successfully insert the surface. 
        @param pkSurface the surface that should be inserted
        @param uiSurfaceIndex the index where to insert the surface
        @return true is insertion was succesful
    */
    bool InsertSurface(const NiSurface* pkSurface, NiInt32 uiSurfaceIndex);

    /**
        Remove a surface from the terrain surface index. This will result
        in the surface being removed from all sectors.

        @param pkSurface the surface to allow painting with
        @return The index where the surface was found. -1 if surface is null
    */
    NiInt32 RemoveSurface(const NiSurface* pkSurface);

    /**
        Remove all surfaces on a terrain. This will reset the terrain
        surface index as well.
    */
    void RemoveAllSurfaces();

    /**
        This event is fired whenever a material package reference has been resolved by the 
        relevant asset resolver.
    */
    void OnSurfacePackageUpdated(NiSurfacePackage* pkPackage, const efd::utf8string& kAssetID);

    /**
        Check if pkPackage's iteration matches the surface references used by this terrain
        object. If this function returns true, then the terrain should be resaved from the tools.
    */
    bool CheckPackageIteration(NiSurfacePackage* pkPackage) const;

    /**
        Fetch the data required to resolve a surface and the pointer that needs to be
        modified in order to set the surface. 

        @param uiSurfaceIndex the index we want to get surface data at
        @param kPackageID OUT The package ID found for the index
        @param kSurfaceID OUT The surface ID found for the index
        @return True is successful false ortherwise
    */
    inline bool GetSurfaceEntry(NiUInt32 uiSurfaceIndex, NiFixedString& kPackageID, 
        NiFixedString& kSurfaceID);

    /**
        Update the surface entry at the given position

        @param uiSurfaceIndex the index we want to get surface data at
        @param kPackageID the new package ID
        @param kSurfaceID the new surface ID
		@param uiPackageIteration the iteration of the package to reference
    */
    inline void UpdateSurfaceEntry(NiUInt32 uiSurfaceIndex, NiFixedString kPackageID, 
        NiFixedString kSurfaceID, efd::UInt32 uiPackageIteration);

    /**
        Resolve a single surface's entry into an actual surface object
        @param uiSurfaceIndex the index to resolve the surface at
        @param pkSurface the surface to resolve
    */
    inline void ResolveSurface(NiUInt32 uiSurfaceIndex, NiSurface* pkSurface);

    /**
        Get the number of unresolved surfaces on the terrain
        @return the number of unresolved surfaces
    */
    inline efd::UInt32 GetNumUnresolvedSurfaces();

    /**
        Notify the terrain that a specific surface package has just loaded. This will cause terrain
        to look through the package for any surfaces it requires and compile them.
        @param kAssetID the Asset ID of the package that was just loaded.
        @param pkPackage The package that was just laoded.
    */
    void NotifySurfacePackageLoaded(const efd::utf8string& kAssetID, NiSurfacePackage* pkPackage);

    /**
        Notify the terrain that a specific surface has changed in some way. Must be called after
        changing any of the properties of a surface that is used by this terrain.

        @param pkSurface the Surface that was changed
    */
    void NotifySurfaceChanged(const NiSurface* pkSurface);

    /**
        Fetch the surface that is represented by the given index.

        @param uiIndex the index used to represent the surface.
        @return A pointer to the surface
    */
    inline const NiSurface* GetSurfaceAt(NiUInt32 uiIndex);

    /**
        Get the index of a specific surface that the terrain uses to 
        reference that surface. 
    
        @param pkSurface the surface to find the index of.
        @return the index of the given surface
    */
    inline NiInt32 GetSurfaceIndex(const NiSurface* pkSurface);

    /**
        Get the index of a specific surface by it's name and package ID.
        @param kPackageID the Id of the package we want the index of
        @param kSurfaceID the id Of the surface we want the index of
        @return the index of the surface
    */
    inline NiInt32 GetSurfaceIndex(NiFixedString kPackageID, NiFixedString kSurfaceID);

    /**
        Get the number of surfaces that this terrain has registered for use.
        @return the number of surfaces
    */
    inline NiUInt32 GetNumSurfaces();
    //@}
    

    // Don't show documentation for these functions
    /// @cond EMERGENT_INTERNAL
    static void _SDMInit();
    static void _SDMShutdown();
    // @endcond

    ///@name NiNode overloads
    //@{
    /**
        Modify the default behaviour of NiNode so that all bounding information
        is retrieved from the base level of detail.

        @see NiNode
    */
    virtual void UpdateDownwardPass(NiUpdateProcess& kUpdate);

    /**
        Modify the default behaviour of NiNode so that all bounding information
        is retrieved from the base level of detail.

        @see NiNode
    */
    virtual void UpdateSelectedDownwardPass(NiUpdateProcess& kUpdate);

    /**
        Modify the default behaviour of NiNode so that all bounding information
        is retrieved from the base level of detail.

        @see NiNode
    */
    virtual void UpdateRigidDownwardPass(NiUpdateProcess& kUpdate);

    /**
        Modify the default behaviour of NiNode so that all bounding information
        is retrieved from the base level of detail.

        @see NiNode
    */
    inline void EnforceValidBound();    

    /**
        Modify the default behavior of NiNode so we can keep data on the
        effect and property states
    */
    virtual void UpdateEffectsDownward(NiDynamicEffectState* pkParentState);

    /**
        Modify the default behavior of NiNode so we can keep data on the
        effect and property states
    */
    virtual void UpdatePropertiesDownward(NiPropertyState* pkParentState);
    
    /**
        Controls the way a sector's visible set is built when using the
        NiNode system.

        @see NiNode
    */
    virtual void OnVisible(NiCullingProcess& kCuller);
    //@}

    /**
        Trigger an update of internal data, if required. All data loading,
        preparation and cache updates are performed within this function.
        If any deformation has occurred on the terrain, Update MUST be called
        before any attempt to render. Note this function does not propagate
        the update to children and is only public to allow NiTerrainComponent
        access to it.
    */
    void DoUpdate(NiUpdateProcess& kUpdate, bool bUpdateWorldData = false);

    /**
        Perform streaming update operations including queuing sectors to be loaded/unloaded
        according to the policy defined by the assigned sector selector object
    */
    void UpdateStreaming();
    
    /**
        Get the default platform configuration to use for any terrains 
        created. The configuration will determine how the terrain's data is
        stored in memory and allows configuration of the terrain for different
        platforms.
    */
    static const NiTerrainConfiguration GetDefaultConfiguration();

    /**
        Set the default platform configuration to use for any terrains 
        created. The configuration will determine how the terrain's data is
        stored in memory and allows configuration of the terrain for different
        platforms.
    */
    static void SetDefaultConfiguration(NiTerrainConfiguration kConfig);

    /// Returns a copy of the current terrain configuration
    const NiTerrainConfiguration GetConfiguration() const;

    /// Returns whether or not the terrain engine is in tool mode
    static bool InToolMode();

    /// Sets whether or not the terrain engine is in tool mode
    static void SetInToolMode(bool bInToolMode);

    /**
        Set the allocator used to allocate all the objects involved in
        terrain management. Allocators may only be set/changed whilst no
        objects are active in the current allocator. The default allocator
        is the NiTerrainStandardAllocator.
    */
    void SetResourceManager(NiTerrainResourceManager* pkManager);

    /**
        Get the allocator used to allocate all the objects involved in
        terrain management. Allocators may only be set/changed whilst no
        objects are active in the current allocator. The default allocator
        is the NiTerrainStandardAllocator.
    */
    NiTerrainResourceManager* GetResourceManager();

    /// @cond EMERGENT_INTERNAL
    /**
        Gets a pointer to this terrains decal manager instance. This should not be called 
        directly, all loading and unloading should take place via the sector selector.

        @internal
    */
    NiTerrainDecalManager* GetDecalManager();

    /**
        This is an internal callback function used by the low detail render 
        step. It is called before the renderstep is rendered, and is
        responsible for configuring the appropriate clicks to render the 
        required portion of the low detail texture.
    */
    static bool Callback_UpdateLowDetailRenderStep(NiRenderStep* pkCurrentStep, 
        void* pvCallbackData);

    /**
        This is an internal callback function used by the low detail render 
        step. It is called after the render step has executed to force ending
        the use of the render target group. This allows the render call to be
        called standalone from the Frame rendering system.
    */
    static bool Callback_EndUsingRenderTargetGroup(NiRenderStep* pkCurrentStep, 
        void* pvCallbackData);

    /**
        Creates the required data to store painting information.
        @return true if successful
    */
    bool CreatePaintingData();

    /**
        This is an internal function to allow sectors to attach their
        low detail scenes to the terrain's thus creating an overall low
        detail scene across the scope of the terrain.
        @return A pointer to the node where to attach the low detail data
    */
    NiNode* GetLowDetailScene();

    /// Register for notification of a DX9 device reset
    void SubscribeToDXDeviceResetNotification();

    /// Unregister from DX9 device reset notifications
    void UnsubscribeToDXDeviceResetNotification();

    /// Handle a DX9 device reset by regenerating the blend mask textures
    static bool HandleDXDeviceReset(bool bBeforeReset, void* pvVoid);

    /**
        Set the debug rendering mode to use on this terrain. This can be 
        used to display different properties of the terrain through special
        shaders applied to the terrain. All cells on the terrain will be flagged to be re-rendered
        to the low detail textures.

        @param eMode the debug mode to use
        @param bUpdateLowDetailNow render the low detail textures again now?
    */
    void SetDebugMode(NiTerrainCellShaderData::DebugMode eMode, bool bUpdateLowDetailNow = false);
    
    /**
        Get the debug rendering mode to use on this terrain. This can be 
        used to display different properties of the terrain through special
        shaders applied to the terrain. All cells on the terrain will be flagged to be re-rendered
        to the low detail textures.
    */
    NiTerrainCellShaderData::DebugMode GetDebugMode() const;

    /**
        Fetch the cached property state for the terrain. This state is used
        to update cells as they are loaded without requiring a traversal up
        the scene graph. 
        @return the cached property state
    */
    NiPropertyState* GetCachedPropertyState();

    /**
        Fetch the cached effect state for the terrain. This state is used
        to update cells as they are loaded without requiring a traversal up
        the scene graph.
        @return the cached effect state
    */
    NiDynamicEffectState* GetCachedEffectState();

    /**
        Gets a pointer to this terrains loading managers instance. This should not be called 
        directly, all loading and unloading should take place via the sector selector.

        @internal
    */
    NiTerrainStreamingManager* GetStreamingManager();
    /// @endcond

    /**
        Get the material to use on all terrain objects.
        @return the Material currently in use
    */
    inline NiMaterial* GetMaterial();

    /**
        Set the surface library object that is used to managed all the surfaces that this
        terrain references. Multiple terrains may share a common library, allowing the
        data to be shared across them all.

        @param pkLibrary The library to manage this terrain's surfaces
    */
    void SetSurfaceLibrary(NiTerrainSurfaceLibrary* pkLibrary);

    /**
        Get the surface library object that is used to managed all the surfaces that this
        terrain references. 
    */
    NiTerrainSurfaceLibrary* GetSurfaceLibrary();

    /**
        Set the sector selector object that is used to select which sectors will be loaded
        and unloaded. 
    */
    void SetSectorSelector(NiTerrainSectorSelector* pkSelector);

    /**
        Get the sector selector object that is used to select which sectors will be loaded
        and unloaded. 
    */
    NiTerrainSectorSelector* GetSectorSelector();
    
    /**
        Get the storage policy to use for this terrain object
    */
    const StoragePolicy& GetStoragePolicy();

    /**
        Set the storage policy to use for this terrain object
    */
    void SetStoragePolicy(const StoragePolicy& kPolicy);

    /**
        Get the custom data policy that this terrain uses
    */
    CustomDataPolicy* GetCustomDataPolicy();

    /**
        Set the custom data policy that this terrain uses
    */
    void SetCustomDataPolicy(CustomDataPolicy* pkPolicy);

    /**
        Opens a particular sector's storage file(s) for read or write
    */
    NiTerrainSectorFile* OpenSectorFile(NiInt32 iSectorX, NiInt32 iSectorY, bool bWrite, 
        const char* pucArchive = NULL);

    /**
        Opens the terrain's storage file for read or write
    */
    NiTerrainFile* OpenTerrainFile(bool bWrite, const char* pucArchive = NULL);

    /// @cond EMERGENT_INTERNAL
    /**
        Locks the surface data to stop different threads from reading and writing at 
        the same time
    */
    void LockSurface(bool bLockWrite = false);

    /**
        Unlocks the surface data to stop different threads from reading and writing at 
        the same time
    */
    void UnlockSurface(bool bLockWrite = false);
    /// @endcond

protected:

    /**
        This class is used to store data specifically required when the terrain 
        is supporting painting. 
        (i.e if the terrain is being used in a tool)
    */
    class RuntimePaintingData : public NiMemObject
    {
    public:
        /// Maximum number of cells to update with each render call
        NiUInt32 m_uiMaxLowDetailRenderedCellsPerFrame;
        
        /// Low detail texture render step
        NiDefaultClickRenderStepPtr m_spLowDetailRenderStep;

        /// A pointer to the low detail scene of every texture currently on the 
        /// terrain.
        NiNodePtr m_spLowDetailScene;
        
        /// Error code is different from 0 when rendering the LRT fails
        NiUInt32 uiErrorCode;
    };

    /**
        This class is used to store data about the surfaces used on this terrain  
    */
    struct SurfaceEntry: public NiMemObject
    {
        /// Constructor
        SurfaceEntry();

        /// An ID specifying which surface package the surface belongs to 
        /// (may be filename or an AssetID)
        NiTerrainAssetReference m_kPackageReference;
        /// The name of the surface inside the package
        NiFixedString m_kSurfaceName;
        /// An instance of the surface
        const NiSurface* m_pkSurface;
        /// The iteration of the package the terrain is using
        efd::UInt32 m_uiIteration;
    };

    /// A set of flags used to indicate various things
    enum FLAGS
    {
        PROP_STORAGE_FILENAME_CHANGED   = 0x01,
        PROP_SECTORS_CHANGED            = 0x02,
        PROP_NUMLOD_CHANGED             = 0x04,
        PROP_BLOCKSIZE_CHANGED          = 0x08,
        PROP_ENVMAP_CHANGED             = 0x10,
        SETTING_CHANGED                 = 0x20
    };

    /// Default configuration to use on new terrains
    static NiTerrainConfiguration ms_kDefaultConfiguration;
    /// Is the terrain engine in tool mode
    static bool ms_bInToolMode;

    // Bit flags to store property uniqueness
    NiDeclareFlags(NiUInt8);

    // Has the shape changed during the last update?
    bool m_bHasShapeChangedLastUpdate;

    // Has this object been destroyed
    bool m_bObjDestroyed;
    
    // Local 'working copy' of terrain details. Changes to these need to be
    // 'committed' to the terrain when changed.
    NiFixedString m_kArchivePath;
    NiUInt32 m_uiBlockSize;
    NiUInt32 m_uiNumLOD;
    NiUInt32 m_uiMaskSize;
    NiUInt32 m_uiLowDetailTextureSize;
    float m_fLODScale;
    float m_fLODShift;
    float m_fMinHeight;
    float m_fMaxHeight;
    float m_fVertexSpacing;
    NiUInt32 m_uiLODMode;

    /// Terrain resource manager used in all terrain allocations
    NiTerrainResourceManagerPtr m_spResourceManager;

    /// Performs all loading and unloading of terrain sectors
    NiTerrainStreamingManager m_kStreamingManager;

    /// Manages all the decals displaying on this terrain
    NiTerrainDecalManagerPtr m_spDecalManager;

    /// Manages all the surfaces that the terrain references
    NiTerrainSurfaceLibraryPtr m_spSurfaceLibrary;

    // Terrain material
    NiMaterialPtr m_spTerrainMaterial;

    // Member sector information
    NiTMap<NiUInt32, NiTerrainSector*> m_kSectors;
    
    // The array of surfaces
    typedef efd::map<efd::SInt32, SurfaceEntry*> SurfaceReferenceMap;
    SurfaceReferenceMap m_kSurfaces;

    /// Cached effect and property states
    NiPropertyStatePtr m_spTerrainPropertyState;
    NiDynamicEffectStatePtr m_spTerrainEffectState;
    
    /// The DX9 Renderer device reset callback index
    bool m_bRegisteredDXDeviceResetCallback;
    NiUInt32 m_uiDXDeviceResetCallbackIndex;

    /// Store a structure with all the information required for performing
    /// runtime painting on the terrain.
    RuntimePaintingData* m_pkPaintingData;

    /// An object to handle how terrain information is stored on disk
    StoragePolicy m_kStoragePolicy;

    /// An object to describe how to handle custom terrain data
    NiPointer<CustomDataPolicy> m_spCustomDataPolicy;

    /// A pointer to the object that handles what sectors should/shouldn't be loaded
    NiTerrainSectorSelectorPtr m_spSectorSelector;

    NiRWLock m_kSurfaceRWLock;

    /**
        Returns whether or not the settings have changed since the last update
    */
    bool HasSettingChanged() const;

    /**
        Update a single sector with the settings for this terrain
    */
    inline void UpdateSector(NiTerrainSector* pkSector);

    /**
        Initialize the terrain's basic values. Called by the constructor
        of the NiTerrain.
    **/
    void Initialize();

    /**
        Save the terrain's surface index from storage.
        @param pcArchive the path to use for saving
        @param puiErrorCode return code giving feedback on faillure
        @return whether saving was successful or not
    */
    bool SaveTerrainConfig(const char* pcArchive, NiUInt32* puiErrorCode);

    /**
        Load the terrain's surface index from storage.
        @param pcArchive the path to use for saving
        @param puiErrorCode return code giving feedback on faillure
        @return whether saving was successful or not
    */
    bool LoadTerrainConfig(const char* pcArchive, NiUInt32* puiErrorCode);

    /**
        Update a surface reference.
        This function is the only way surface entries should be updated, as
        it manages the surface library callbacks as well.
    */
    void ModifySurfaceEntry(efd::UInt32 uiSurfaceIndex, SurfaceEntry* pkEntry);

    /**
        Find the first spot in the surface reference map that is free
    */
    efd::SInt32 FindFirstEmptySurfaceReference();
};

NiSmartPointer(NiTerrain);

#include "NiTerrain.inl"

#endif // NITERRAIN_H
