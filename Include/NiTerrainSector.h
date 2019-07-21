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
#ifndef NITERRAINSECTOR_H
#define NITERRAINSECTOR_H

#include "NiTerrainLibType.h"

#include "NiTerrainSectorData.h"

#include "NiRay.h"
#include "NiTerrainCell.h"
#include "NiTerrainCellLeaf.h"
#include "NiTerrainCellNode.h"
#include "NiTerrainUtils.h"
#include "NiIndex.h"
#include "NiTerrainResourceManager.h"
#include "NiTerrainDeformationBuffer.h"

#include <NiPoint4.h>
#include <NiRWLock.h>

class NiTerrain;
class NiTerrainDataSnapshot;

NiSmartPointer(NiTerrainSector);

/**
    The Terrain Sector is a manager class for a collection of terrain cells,
    contained within a quadtree.

    An NiTerrainSector object keeps track of data streams, surface
    masks and the quad-tree of cells themselves.

    This class should not be interacted with directly by the end application
    for anything other than attaching dynamic effects, lights, shadowing etc.
 */
class NITERRAIN_ENTRY NiTerrainSector : public NiNode
{
    friend class NiTerrainStreamingTask;
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:
    /// Type to identify a single sector on a terrain
    typedef NiUInt32 SectorID;

    /// Type to identify a single cell on a terrain
    struct CellID
    {
        /// Constructor to simplify the creation
        CellID(SectorID kSectorId, efd::UInt32 uiCellId);
        /// Define the less than operator for use in maps
        bool operator<(const CellID& other) const;
        /// SectorID of the sector the cell belongs to
        SectorID m_kSectorId;
        /// Cell ID of the cell within the given sector
        efd::UInt32 m_uiCellId;
    };
    
    /// A class to encapsulate a height map for the sector
    class HeightMap: public NiRefObject
    {
    public:

        struct LockType
        {
            enum VALUE
            {
                /// Read lock type
                READ,
                /// Write lock type
                WRITE
            };
        };

        /**
            Create a new height map to take control over the given buffer

            @param uiWidth the width of the heightmap
            @param uiHeight the Height of the heightmap
            @param pkBuffer the buffer to use with this heightmap
        */
        inline HeightMap(NiUInt32 uiWidth, NiUInt32 uiHeight, NiUInt16* pkBuffer);
        
        /**
            Destructor
        */
        inline ~HeightMap();
        
        /**
            Lock the height map for read (Non blocking for other reads) or write (Blocking lock)

            @param eLockType defines whether to lock the buffer for read or write
            @return A pointer to the first element of the heightmap
        */
        inline NiUInt16* Lock(LockType::VALUE eLockType);
        
        /**
            Unlock the height map

            @param eLockType defines whether to lock the buffer for read or write
        */
        inline void Unlock(LockType::VALUE eLockType);
        
        /**
            Get the width of the height map in pixels
            @return the width of the heightmap
        */
        inline NiUInt32 GetWidth();
        
        /**
            Get the height of the height map in pixels
            @return the height of the heightmap
        */
        inline NiUInt32 GetHeight();

    private:
        /// The Width and height of the buffer
        NiUInt32 m_uiDimensions;
        /// The buffer the height map is stored in
        NiUInt16* m_pusBuffer;
        /// The lock used to control access to the buffer
        NiRWLock m_kLock;
    };
    /// Smartpointer to the HeightMap class
    typedef NiPointer<HeightMap> HeightMapPtr;

    /**
        Default constructor.

        @param bIsDeformable Defines whether the sector is deformable or not.
            Thismust be true if the terrain will be modified at runtime.        
    */
    NiTerrainSector(bool bIsDeformable = false);

    /// Destructor
    virtual ~NiTerrainSector();

    /**
        Gets the Terrain object that this sector belongs to.
    */
    inline NiTerrain* GetTerrain();

    /**
        Gets the Terrain object that this sector belongs to.
    */
    inline const NiTerrain* GetTerrain() const;

    /**
        Sets the Terrain object that this sector belongs to.
    */
    void SetTerrain(NiTerrain* pkTerrain);

    /**
        Get the sector ID of this sector within it's parent terrain
        @return This sector's ID
    */
    inline SectorID GetSectorID();

    /**
        Adds all visible blocks to the visible set defined in the given
        culling process. Frustum culling and quadtree based LOD culling are
        performed in this function, according to the camera provided by the
        culling process.

        @param kCuller The culling process to use during culling.
        @return True if this sector drew anything.
    */
    bool ProcessLOD(NiCullingProcess &kCuller);

    /**
        After calculating the LOD, this function should be called to allow
        appropriate stitching to occur between blocks of different LODs
    */
    void ProcessBorders();

    /// @cond EMERGENT_INTERNAL
    /**
        Controls the way a sector's visible set is built when using the NiNode system
        @param kCuller The culling process to use during culling.
    */
    virtual void OnVisible(NiCullingProcess &kCuller);
    /// @endcond

    /**
        Find the world position from vertex data at the given index and detail
        level.

        This function is computationally expensive and should be avoided
        in critical paths.

        @note The given index must be in the sector scope, at detail level 0.
        If no vertex exists at the given index in the requested detail
        level, an assertion is thrown.

        @param kIterator The stream iterator to use
        @param[out] kVertex Discovered position, or undefined if no vertex
        exists at the requested index for this detail level
        @param kIndex Sector scope index of the vertex from which to retrieve
        the world position
        @param uiLevel Detail level from which to retrieve the vertex
    */
    inline void GetVertexAt(
        const NiTerrainPositionRandomAccessIterator& kIterator,
        NiPoint3& kVertex, const NiIndex& kIndex, 
        NiUInt32 uiLevel = NiTerrainUtils::ms_uiMAX_LOD) const;

    /**
        Get the height value of the vertex specified by the given sector
        scope index, at the specified detail level.

        If the given index is invalid at the specified detail level, an
        assertion is thrown and the height is undefined.

        @param kIterator The stream iterator to use
        @param kIndex Sector scope index of the vertex from which to retrieve
        the world position
        @param uiLevel Detail level from which to retrieve the vertex
        @return The height value we are looking for
    */
    inline float GetHeightAt(
        const NiTerrainPositionRandomAccessIterator& kIterator,
        const NiIndex& kIndex, 
        NiUInt32 uiLevel = NiTerrainUtils::ms_uiMAX_LOD) const;

    /**
        Find the X and Y position of the sector in the terrain list.

        @param[out] sXIndex the X position of the sector
        @param[out] sYIndex the Y position of the sector
    */
    inline void GetSectorIndex(NiInt16& sXIndex, NiInt16& sYIndex) const;

    /**
        Set the X and Y position of the sector in the terrain list.

        @param sXIndex the X position to set the sector at
        @param sYIndex the Y position to set the sector at
    */
    void SetSectorIndex(NiInt16 sXIndex, NiInt16 sYIndex);

    /**
        Get the sector that borders this sector according to the
        border description passed in. The border descriptions are
        identical to those used for NiTerrainDataLeafs.

        @param uiBorder the border we want the adjacent sector for
        @return The adjacent terrain sector
    */
    NiTerrainSector* GetAdjacentSector(NiUInt32 uiBorder) const;

    /**        
        @return true if this sector is currently using a 16 bit index buffer,
            false if using 32 bit.
    */
    NiBool GetUsingShortIndexBuffer();

    /**
        @return true if this sector is currently using a 16 bit index buffer,
            false if using 32 bit (const version).
    */
    NiBool GetUsingShortIndexBuffer() const;

    /**
        This function will return true if during the last update a deformation
        or translation/scaling/rotation of the terrain occurred. This
        function is useful in determining when to update any water objects
        associated with this terrain.

        @return true if the terrain has changed
    */
    inline bool HasShapeChangedLastUpdate();

    /**
        Function that returns true if the sector has a paging data and 
        therefore if the sector is using paging.

        @return true if the sector is paging
    */
    inline bool HasPagingData() const;

    /**
        Populate the surface mask buffer with the relevant mask data for the given surface index.

        @param uiSurfaceIndex the index of the surface to fetch the mask for
        @param[out] pkBuffer the buffer to populate with the information
        @param[out] pkMaskSumBuffer the buffer to populate with the sample sum information
        @param[out] pkSnapshot The cells current data buffers
        @return true
    */
    bool GetSurfaceMask(efd::UInt32 uiSurfaceIndex, SurfaceMaskBuffer* pkBuffer, 
        SurfaceMaskBuffer* pkMaskSumBuffer, NiTerrainDataSnapshot* pkSnapshot = NULL);

    /**
        Update the surface mask of a particular surface on the terrain

        @param uiSurfaceIndex the index of the surface to fetch the mask for
        @param pkMaskBuffer the buffer holding the information to populate the individual channel
            from
        @param pkMaskSumBuffer the buffer holding the information to populate the sample sum from
        @return false if we are not ready for painting
    */
    bool SetSurfaceMask(efd::UInt32 uiSurfaceIndex, SurfaceMaskBuffer* pkMaskBuffer,
        SurfaceMaskBuffer* pkMaskSumBuffer);

    /**
        Add the specified surface to the cells in the given region.

        @param uiSurfaceIndex the index of the surface to fetch the mask for
        @param kAffectedSectorRange sector scope region affected by the given surface
        @param kMaskRegion The mask region affected by the given surface
        @return true
    */
    bool AddSurface(efd::UInt32 uiSurfaceIndex, NiRect<efd::SInt32> kAffectedSectorRange, 
        NiRect<efd::SInt32> kMaskRegion);

    /**
        Flag this sector as having changed in the last update.
        @param bChanged whether the sector changed or not
    */
    inline void SetShapeChangedLastUpdate(bool bChanged);

    /**
        Retrieve the opacity (from 0 to 255) of the given surface on this
        sector at the local position derived from the specified world location.

        Only the X and Y components of the local position are taken into
        account. If no valid surface mask is found at the given location for
        the specified detail level and bIncludeLowerDetail is set to true, the
        function will search up the tree for the first valid mask to use.

        @param pkSurface Surface to find surface mask for.
        @param kWorldLocation World location, which will be converted to
            terrain space for checking X and Y against the terrain.
        @param[out] ucValue Opacity (0 to 255) of the found mask pixel, or 0 if
            no valid mask was found.
        @param uiDetailLevel Detail level to check for a mask.
        @param bSearchLowerDetail If true, search up the quadtree for a valid
            mask if none is found at the specified level.

        @return true if a valid mask pixel was found.
    */
    bool GetSurfaceOpacity(const NiSurface* pkSurface,
        const NiPoint3& kWorldLocation,
        NiUInt8& ucValue,
        NiUInt32 uiDetailLevel = NiTerrainUtils::ms_uiMAX_LOD,
        bool bSearchLowerDetail = true) const;

    /**
        Make sure that the sector is ready to be painted upon. This may
        involve creating a new renderable low detail texture.

        @param pkSurface pointer to the surface to be used for painting
        @param puiErrorCode Error code giving information on failure
        @return true
    */
    bool PrepareForPainting(const NiSurface* pkSurface, NiUInt32* puiErrorCode = 0);

    /**
        This will cause all blocks using the given surface to update any shader
        maps and constants derived from the surface.

        @param uiSurfaceIndex the surface index for the changed surface
    */
    void NotifySurfaceChanged(NiUInt32 uiSurfaceIndex);

    /**
        Remove the given surface from this terrain, also removing associated
        masks.

        All surfaces below the given surface will be moved up to fill the gap.

        @param uiSurfaceIndex the surface index to remove
    */
    void RemoveSurface(NiUInt32 uiSurfaceIndex);

    /**
        Adds a surface to the parent terrain's surface index.

        @param pkSurface the surface to add.
        @return the surface index we added the surface at
    */
    NiInt32 AddSurface(const NiSurface* pkSurface);

    /**
        Get the surface that corresponds to the supplied index. This 
        function queries the parent terrain for the relevant information.

        @param uiIndex the index of the surface to retrieve
        @return pointer to the surface found
    */
    const NiSurface* GetSurfaceAt(NiUInt32 uiIndex);
    
    /**
        Get the index that is used to represent the supplied surface on this
        sector. This function queries the parent terrain for the relevant 
        information.

        @param pkSurface the surface to fetch the index of
        @return the Index of the surface found
    */
    NiInt32 GetSurfaceIndex(const NiSurface* pkSurface);

    /**
        Removes all surfaces used by this sector.
    */
    void RemoveAllSurfaces();

    /// @cond EMERGENT_INTERNAL
    /**
        Tells the contained sector to save to the currently defined location.

        @param pcArchive The archive directory to save the sector to. Set to
            0 to use the currently stored archive directory.
        @param puiErrorCode A pointer to an integer to receive error flags.
        @return true if successful
    */
    bool Save(const char* pcArchive = 0, NiUInt32* puiErrorCode = 0);

    /**
        Creates a blend texture of a particular size.
        @param uiMaskSize the size of the blend mask
        @return the created texture
    */
    NiSourceTexture* CreateBlendTexture(NiUInt32 uiMaskSize = 0);

    /**
        Creates a task in the loading manager to load data from the specified file into this sector

        @param pcArchive The archive directory to load the sector from. Set to
            0 to use the currently stored archive directory.
        @param puiErrorCode A pointer to an integer to receive error flags.
        @return true if successful
    */
    bool Load(const char* pcArchive = 0, NiUInt32* puiErrorCode = 0);

    /// @endcond

    /**
        Get the height map that was used when generating this sector

        @return the height map for this sector
    */
    HeightMap* GetHeightMap();

    /**
        Set the height map to use when generating this sector

        @param pkHeightMap the new heightmap
    */
    void SetHeightMap(HeightMap* pkHeightMap);

    /**
        Notify the sector that it's height map has changed over a particular region.
        This function will not return until the geometry in the region has been rebuilt. 

        @param kRegion A rectangle using pixel coordinates of the pixels that have changed
    */
    void NotifyHeightMapRegionChanged(NiRect<NiInt32> kRegion);

    /**
        Copy the data from the heightmap out into the relevant region of the buffer. 

        @param[out] pkBuffer the Sector's heightmap
        @param[out] pkSnapshot the sector's cells current data buffers
    */
    void GetHeightMap(HeightMapBuffer* pkBuffer, NiTerrainDataSnapshot* pkSnapshot = NULL);

    /**
        Copy the data from the heightmap buffer into the relevant region of the heightmap and
        notify the streaming of the update. Returns the vert region of this sector that changed.

        @param pkBuffer the heightmap to copy data from
        @return the vertex region on this sector that changed
    */
    NiRect<efd::SInt32> SetHeightMap(HeightMapBuffer* pkBuffer);

    /**
        An entry point into the loading system which creates a terrain with a
        continuous 0.0 height.

        The size of the created terrain is defined from the current block
        size and LOD level settings defined in the sector data.

        @return true if successful
    */
    bool CreateBlankGeometry();
    
    /**
        Set the low detail texture size.
        
        The low detail texture will be recreated with this new size
 
        @note Texture size must be a power of 2

        @param uiSize the low detail texture's new size
    */
    inline void SetLowDetailTextureSize(NiUInt32 uiSize);

    /**
        Get the low detail texture size.
        @return the low detail texture's size
    */
    inline NiUInt32 GetLowDetailTextureSize() const;
    

    /// @cond EMERGENT_INTERNAL
    //@{
    /**
        Calculates the normals and tangents for all leaves in the given array.
        Where applicable, the resulting data is placed in a blocks dynamic
        stream.

        @note If not in tool mode, valid write locks must exist for this
            sectors static data streams.
    */    
    void CalculateNormalsTangents(
        const NiTPrimitiveArray<NiTerrainCell*>& kCells);
    void CalculateNormalsTangentsPhase1(
        const NiTPrimitiveArray<NiTerrainCell*>& kCells);
    void CalculateNormalsTangentsPhase2(
        const NiTPrimitiveArray<NiTerrainCell*>& kCells);
    void CalculateNormalsTangentsPhase3(
        const NiTPrimitiveArray<NiTerrainCell*>& kCells);
    //@}

    /**
        Handle a device reset. For a sector this involves forcing a regeneration
        of all CPU generated textures so they may be uploaded again on the next
        render frame. (At this point, distribution masks are the only 
        resource that need regeneration). 
    */
    void HandleDXDeviceReset();

    //@{
    /**
        Use these values to adjust the level of detail viewable at different
        distances.

        @param fScale The scale factor for the LOD. Higher is better detail.
        Must be at least 2.0f * NiSqrt(2.0f)
    */
    void SetLODScale(float fScale, float fShift);
    inline float GetLODShift() const;
    inline float GetLODScale() const;
    //@}

    //@{
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
    bool SetLODMode(NiUInt32 uiLODMode);
    //@}

    /// @endcond

    /**
        Returns the highest valid cell index in the cell array (m_kCellArray). This will take into
        account the highest loaded LOD. If no loaded cells exist, this function returns -1.

        @param[out] uiIndex The heighest valid cell index
        @return true if successful
    */
    bool GetMaxLoadedCellIndex(NiUInt32& uiIndex) const;


    /**
        Define whether or not this sector can be deformed. Will initialize the
        dynamic stream cache if necessary.

        @param bIsDeformable whether the sector should be deformable or not
    */
    void SetIsDeformable(bool bIsDeformable);

    /**
        Find the cell that contains the given index at the specified 
        level.

        In border cases where an index may be found in multiple leaves,
        the cell with the smallest region ID takes precedence.

        @param kIndex the Index that is contained by the cell
        @param uiDetailLevel level the cell belongs to
        @return The cell we were looking for
    */
    inline NiTerrainCell* GetCellContaining(const NiIndex& kIndex,
        NiUInt32 uiDetailLevel) const;

    /**
        Retrieve a non-const pointer to a cell corresponding to the given 
        block ID (LOD Space indexing - Siblings are not stored sequentially)

        @param uiCellID the Id for the cell we are looking for
        @return the cell found
    */
    inline NiTerrainCell* GetCell(NiUInt32 uiCellID) const;

    /**
        Retrieve a non-const pointer to a cell corresponding to the given 
        region ID. (QuadTree Space indexing ie. First child = uiLeafID * 4 + 1)

        @param uiCellID the Id for the cell we are looking for
        @return the cell found
    */
    inline NiTerrainCell* GetCellByRegion(NiUInt32 uiCellID) const;

    /**
        Returns the offset in the internal cell array for a leaf at the given
        detail level.

        This value is used to generate the cell region ID.

        @param uiDetailLevel The level we want the offset for
        @return cell id offset
    */
    inline NiUInt32 GetCellOffset(NiUInt32 uiDetailLevel) const;

    /**
        Returns the maximium number of cells that this sector manages when all
        levels of detail are loaded

        @return the number of cells
    */
    inline NiUInt32 GetNumCells() const;

    /**
        Retrieve the sector settings object.

        @return the terrain sector data
    */
    inline const NiTerrainSectorData* GetSectorData() const;

    /**
        Retrieve the sector settings object.

        @return the terrain sector data
    */
    inline NiTerrainSectorData* GetSectorData();

    /**
        Define that the LOD of the cells added to the visible set must lie 
        between the given min and max LOD.

        @param uiMinLOD the minimum visible LOD
        @param uiMaxLOD the maximum visible LOD
    */
    inline void SetMinMaxVisibleLOD(NiUInt32 uiMinLOD, NiUInt32 uiMaxLOD);

    /**
        Change the dimensions of each block, and dictate how many
        levels of LOD exist.

        An attempt is made to preserve data, but some detail may be lost.

        @param uiBlockSize the new size for each block
        @param uiNumLOD the number of level of details
    */
    void SetFormat(NiUInt32 uiBlockSize, NiUInt32 uiNumLOD);

    /**
        Unload all supporting data that is not tied to a specific level of
        detail. This function must be called before changing any of the
        terrain's basic settings (ie. blocksize).
    */
    void DestroySupportingData();

    /**
        Attempt to collide a Terrain space 2D ray with the sector, at the given
        detail level.

        Any collision data is stored in the ray itself.

        @param[out] kRay the ray to use for the collision. Resulting data will be set in this object
        @param uiDetailLOD the level of detail to collide with
        @return true if a collision occurred at the given detail level.
    */
    bool CollideWithRay2D(NiRay& kRay, NiUInt32 uiDetailLOD) const;

    /**
        Attempt to collide a Terrain space ray with the sector, at the given
        detail level.

        Any collision data is stored in the ray itself.

        @param[out] kRay the ray to use for the collision. Resulting data will be set in this object
        @param uiDetailLOD the level of detail to collide with
        @return true if a collision occurred at the given detail level.
    */
    bool CollideWithRay(NiRay& kRay, NiUInt32 uiDetailLOD = 0) const;

    /// @cond EMERGENT_INTERNAL
    /**
        Fetch the specified configuration to build terrain out of. 
        A configuration allows the terrain to run on different platforms
        with subsets of its features.

        @return the Terrain configuration
    */  
    inline const NiTerrainConfiguration& GetConfiguration() const;

    /**
        Fetch the resource manager to use in all terrain allocations.

        @return the terrain ressource manager
    */
    NiTerrainResourceManager* GetResourceManager();

    /** 
        Modify the default behavior of NiNode so that the critical sections 
        are respected 

        @see NiNode
    */
    virtual void UpdateEffectsDownward(NiDynamicEffectState* pkParentState);
    virtual void UpdatePropertiesDownward(NiPropertyState* pkParentState);
    /// @endcond

    /**
        Add a cell to the list of cells to be rendered during the next
        low detail texture render. Note this is a queue, so a number of 
        renders may have to occur before this cell is rendered.

        @param pkCell Pointer to the cell to queue for update
    */
    void QueueCellForLowDetailUpdate(NiTerrainCell* pkCell);

    /**
        Add all cells in the sector to the list of cells to be rendered during the next
        low detail texture render. 
    */
    void QueueAllCellsForLowDetailUpdate();

    /**
        Appends the latest render clicks that the terrain requires
        to be executed to the given render click step.

        @param[out] pkStep the step to add the render click to
        @param[out] iMaxNumCells the maximum number of cell updated
        @param[out] puiErrorCode Error code returned upon failure
        @return true if successful
    */
    bool AppendRenderClicks(NiDefaultClickRenderStep* pkStep, 
        NiInt32& iMaxNumCells, NiUInt32* puiErrorCode);

    /**
        Get the low detail scene used by this sector to render it's low detail
        textures. 
        
        @returns NULL if no painting data has been created for this sector
    */
    NiNode* GetLowDetailScene();

    /**
        This function should only be called by NiTerrain::PageSector since this 
        data should only be present on the sector if we are paging.
        It will create the paging data for the sector after a new sector was 
        created.
    */
    inline void CreatePagingData();

    /**
        Fetches the relevant texture from the root cell

        @param eTexType the texture type we want to retrieve
        @return the Texture that was found
    */
    NiTexture* GetTexture(NiTerrainCell::TextureType::Value eTexType);

    /**
        Generate a sectorID from a sector's coordinates

        @param sIndexX The sector's X coordinate
        @param sIndexY The sector's Y coordinate
        @param[out] kSectorID the generated sectorID
    */
    static void GenerateSectorID(NiInt16 sIndexX, NiInt16 sIndexY, SectorID& kSectorID);

    /**
        Extract the sector's coordinates from a sector ID

        @param kSectorID The sectorID to extract the data from
        @param[out] sIndexX The sector's X coordinate
        @param[out] sIndexY The sector's Y coordinate
        
    */
    static void GenerateSectorIndex(const SectorID& kSectorID, NiInt16& sIndexX, NiInt16& sIndexY);

    /**
        Set the mask usage information for a specific channel on a cell in the painting data. 
    */
    void SetLeafMaskUsage(efd::UInt32 uiCellID, efd::UInt32 uiChannel, efd::UInt32 uiUsage);

    /**
        Get the mask usage information for a specific channel on a cell in the painting data. 
    */
    efd::UInt32 GetLeafMaskUsage(efd::UInt32 uiCellID, efd::UInt32 uiChannel);

protected:

    /**
        An enumeration to specific the type of pixel painting mode to employ in a specific area
        of a leaf's blend mask. These enums are used in the SetSurfaceMask function.
    */
    struct PixelPaintMode 
    {
        /// These values are in descending priority. Lower values will overwrite higher ones
        enum VALUE
        {
            /// Do not modify the border pixels
            NONE = 0,
            /// Change the border pixels to match the previous line of this cell's pixels
            DUPLICATE_LOCAL = 1,
            /// Change the border pixels to match the adjacent cell
            NORMAL = 2,
        };
    };

    /**
        A class used to store painting information when a terrain is painted upon. It is separated
        from the rest of the class to allow applications without painting to avoid the memory 
        overhead of this class's contents.
    */
    class RuntimePaintingData : public NiMemObject
    {
    public:
        /// A structure used to record the number of pixels used by each surface on a leaf
        struct LeafMaskUsage
        {
            /// Store the number of pixels that are used by a surface on a leaf's mask
            efd::UInt32 m_uiSurfaceUsage[NiTerrainCellLeaf::MAX_NUM_SURFACES];
        };

        /// A list of all the coverage structures for each cell
        efd::vector<LeafMaskUsage> m_kLeafMaskUsage;
        
        /// A list of all the cells that require re-rendering in the low detail
        /// texture. 
        NiTPointerList<NiTerrainCell*> m_kLowDetailRenderQueue;

        /// A scene for use when rendering low detail texture
        NiNodePtr m_spLowDetailScene;

        /// A camera used to render low detail scenes
        NiCameraPtr m_spLowDetailCamera;

        /// An extra data to manipulate how the terrain is rendered in the
        /// low detail scene
        NiIntegerExtraDataPtr m_spLowDetailRenderMode;

        /// A render click, used for updating the low detail diffuse texture
        NiViewRenderClickPtr m_spLowDetailDiffuseRenderClick;
    };

    /**
        This class should only be used with the NiTerrainPagingManager. 
        It should not be accessible to other classes 
    */
    class NiTerrainSectorPagingData : public NiMemObject
    {
    private:
        /// Threading utility variables
        bool m_bWaitingForUpdate;
        NiSemaphore m_kUpdatePaused;
        NiSemaphore m_kResumeUpdate;
        NiCriticalSection m_kSectorPages;
        NiCriticalSection m_kSectorUpdates;

    public:
        NiTerrainSectorPagingData();
        ~NiTerrainSectorPagingData();

        /**
            Function that waits for m_kUpdateApproval to be signaled
        */
        void PauseUpdateThread();
        
        /**
            Function that signals the m_kUpdateApproval semaphore and
            waits for the m_kOperationComplete semaphore.
        */        
        void SyncWithPaging();

        /**
            Function that signals m_kOperationComplete and marks the end
            of the synchronisation.
        */
        void ResumeUpdateThread();

        /**
            Lock the sector for paging operations to begin
        */
        void LockSectorPaging();

        /**
            Unlock the sector for the end of paging operations
        */
        void UnlockSectorPaging();

        /**
            Lock the sector for the initial update operation to begin
        */
        void LockSectorUpdating();

        /**
            Unlock the sector for the end of initial update operations
        */
        void UnlockSectorUpdating();
    };

    /**
        Check whether we need to perform an update synchronisation.
    */
    inline void SyncWithPaging();

    /**
        Starts a critical section if we have a TerrainSectorPagingData
    */
    inline void PauseUpdateThread();

    /**
        Ends a critical section
    */
    inline void ResumeUpdateThread();

    /**
        Lock the sector for paging operations to begin. Only performs the lock
        if the terrain is configured for paging.
    */
    inline void LockSectorPaging();

    /**
        Unlock the sector for the end of paging operations. Only performs the 
        operation if the terrain is configured for paging.
    */
    inline void UnlockSectorPaging();

    /**
        Lock the sector for initial update to begin. Only performs the lock
        if the terrain is configured for paging.
    */
    inline void LockSectorUpdating();

    /**
        Unlock the sector for the end of initial update operations. Only 
        performs the operation if the terrain is configured for paging.
    */
    inline void UnlockSectorUpdating();

    /// Enables recycling of dynamic streams when too many blocks have been 
    /// deformed
    bool m_bRecycleDynamicStreams;

    /// Used when constructing indices
    bool m_bUsingShortIndexBuffer;

    /// Used when loading surfaces;
    bool m_bSurfacesInFile;

    /// Are any block's lighting out of data
    bool m_bLightingOutdated;

    /// Flag to unsure the index and uv streams have only been created once
    bool m_bCalculateData;

    /// Sector specific paging data. Only exists if paging is used.
    NiTerrainSectorPagingData* m_pkSectorPagingData;

    /// Parent Terrain managing this sector
    NiTerrain* m_pkTerrain;

    /// Height map used for this sector
    HeightMapPtr m_spHeightMap;

    /// Sector Data keeps track of this sectors settings in such a way that
    /// quadtree nodes can also access it.
    NiTerrainSectorData* m_pkSectorData;

    /// Stores level offsets of blocks in the block array
    NiUInt32* m_puiCellOffsets; 

    /// A copy of the world space camera, that has been translated to terrain
    /// local space.
    NiCamera* m_pkLocalCamera;

    /// Data quad tree
    NiTerrainCell* m_pkQuadCell;

    // The low detail diffuse texture
    NiTexture* m_pkLowDetailDiffuseTexture;

    // The low detail normal texture
    NiTexture* m_pkLowDetailNormalTexture;

    /// Which blocks have which streams in the dynamic cache - used when we
    /// want to recycle blocks.
    NiTPointerList<NiTerrainCell*> m_kDynamicCellQueue;

    /// An array that contains pointers to all leaves loaded in the system.
    /// Level 0 blocks are first, followed by next LOD's
    /// (LOD Space Indexing -- Siblings are not stored sequentially)
    NiTPrimitiveArray<NiTerrainCell*> m_kCellArray;
  
    /// An array that contains pointers to all leaves loaded in the system.
    /// Sorted by region ID (QuadTree Space Indexing)
    NiTPrimitiveArray<NiTerrainCell*> m_kCellRegionArray;

    /// A boolean that will allow to inform dependant entities (water) that
    /// the terrain has changed and they should be updated
    bool m_bHasShapeChangedLastUpdate;

    /// The selected size of the low detail texture
    NiUInt32 m_uiLowDetailTextureSize;

    /// Store a structure with all the information required for performing
    /// runtime painting on the terrain.
    RuntimePaintingData* m_pkPaintingData;
    
private:

    /*
        calling order:
        1. CreateStreams()
        2. BuildQuadTree()
        3. (populate the position stream with data)
        3a. (optional) SmoothLowerLOD()
        4. BuildData()     
        5. (run the game)
        6. DestroyMesh()
        7. DestroySupportingData()
    */

    /**
        Allocate memory for the data streams to be used to the quad mesh. If
        tool mode is enabled, no static streams are generated and the dynamic
        stream cache is created with an initial to allow for every block to be
        dynamic.

        If terrain deformation is not enabled, the dynamic stream cache is not
        created.

        @param uiMaxDetailLevel The number of levels of detail to account for
        @return true if successful
    */
    bool CreateStreams(NiUInt32 uiMaxDetailLevel = NiTerrainUtils::ms_uiMAX_LOD);

    /**
        Allocate memory for the data streams to be used to the quad mesh. If
        tool mode is enabled, no static streams are generated and the dynamic
        stream cache is created with an initial to allow for every block to be
        dynamic.

        If terrain deformation is not enabled, the dynamic stream cache is not
        created.

        @param uiMaxDetailLevel The number of levels of detail to account for
        @return true if successful
    */
    bool CreatePNTStream(NiUInt32 uiMaxDetailLevel = NiTerrainUtils::ms_uiMAX_LOD);

    /**
        Allocate memory for the data streams to be used to the quad mesh. If 
        tool mode is enabled, no static streams are generated and the dynamic
        stream cache is created with an initial to allow for every block to be 
        dynamic.

        If terrain deformation is not enabled, the dynamic stream cache is not
        created.
        @return true if successful
    */
    bool CreateUVStream();

    /**
        Allocate memory for the data streams to be used to the quad mesh. If 
        tool mode is enabled, no static streams are generated and the dynamic
        stream cache is created with an initial to allow for every block to be 
        dynamic.

        If terrain deformation is not enabled, the dynamic stream cache is not
        created.
        @return true if successful
    */
    bool CreateIndexStream();

    /**
        Allocates a dynamic stream cache to be used by a deformable terrain.

        @param uiCacheSize the Size of the created cache
        @return true if successful
    */
    bool CreateDeformationCache(NiUInt32 uiCacheSize);

    /**
        Generates normal, tangent, index and UV data from existing positional
        data for all leaves in the tree. This function will recognize that a
        block is currently using a dynamic stream and write to that where
        possible.

        @param uiMaxDetailLevel the LOD level we require to be completed up
            to. Will build the data for every block between the currently
            loaded LOD and this new supplied level of detail.

        @note This function assumes write locks exist for all streams that will
            be used.
    */
    void BuildData(NiUInt32 uiMaxDetailLevel = NiTerrainUtils::ms_uiMAX_LOD);

    /**
        This is a fast function to create bounding spheres for all the leaves.
    */
    void BuildBounds();

    /// @cond EMERGENT_INTERNAL
    //@{
    /**
        Override the normal bounds calculation to use the pre-cached bound info
        in the quadtree.
    */    
    virtual void UpdateNodeBound();
    virtual void UpdateWorldBound();
    //@}

    /**
        Modify the default behavior of NiNode so that all bounding information
        is retrieved from the base level of detail and the critical sections 
        are respected 

        @see NiNode
    */
    virtual void UpdateDownwardPass(NiUpdateProcess& kUpdate);
    virtual void UpdateSelectedDownwardPass(NiUpdateProcess& kUpdate);
    virtual void UpdateRigidDownwardPass(NiUpdateProcess& kUpdate);
    /// @endcond

    /**
        Generates default index data (for all 9 stitching states) into the
        stream associated with the given lock.

        @note The given lock MUST be a write lock.
    */
    void CalculateIndices();

    /**
        Template helper function used by CalculateIndices to add a single
        triangle to the given stream.

        @param x0
        @param y0
        @param x1
        @param y1
        @param x2
        @param y2
        @param kIterator Adds the triangle to the beginning of this
            iterator, which is then incremented by the size of the inserted
            triangle.

        @note The given iterator will be incremented by 3 within this function.
    */
    template <typename T>
    inline void AddTri(NiUInt32 x0, NiUInt32 y0, NiUInt32 x1, NiUInt32 y1, 
        NiUInt32 x2, NiUInt32 y2, 
        NiTStridedRandomAccessIterator<T>& kIterator);

    /**
        Generates default UV data into the stream associated with the given
        lock.

        @note The given lock MUST be a write lock.
    */
    void CalculateUV();

    /**
        Creates the internal quad data and mesh tree, pointing to relevant
        dynamic or static stream data. This new tree will replace any tree that
        already existed.

        @param uiMaxDetailLevel the LOD level we require to be completed up
            to. Will build the tree for every block between the currently
            loaded LOD and this new supplied level of detail.
    */
    void BuildQuadTree(NiUInt32 uiMaxDetailLevel = NiTerrainUtils::ms_uiMAX_LOD);

    /**
        Destroy the quad mesh tree, leaving the quad data tree intact.
    */
    void DestroyMesh();

    /**
        Trigger an update of internal data, if required. All data loading,
        preparation and cache updates are performed within this function.
        If any deformation has occurred on the terrain, DoUpdate MUST be called
        before any attempt to render.

        @param kUpdate The NiUpdateProcess used to update the sector.                 
    */
    void DoUpdate(NiUpdateProcess& kUpdate);

    /**
        Return true if the sector is ready to be painted upon.

        @return whether the sector is ready to be painted upon.
    */
    inline bool IsReadyToPaint();

    /**
        Create the appropriate textures and render clicks to provide an
        environment in which the terrain can be painted upon.

        @param[out] puiErrorCode Return code if painting data creation failed
        @return true if successful
    */
    bool CreatePaintingData(NiUInt32* puiErrorCode);

    /**
        Generate a list of the usage of each surface on a particular leaf for use
        when painting. 

        @param[out] kLeafUsage the generated list
    */
    void GenerateLeafMaskUsageData(efd::vector<RuntimePaintingData::LeafMaskUsage>& kLeafUsage);

    /**
        Update the painting environment to reflect the latest configuraition.
        This may involve recreating textures.

        @param[out] iMaxNumCells The number of updated cells
        @param[out] puiErrorCode Return code if painting data update failed
        @return true is successful
    */
    bool UpdatePaintingData(NiInt32& iMaxNumCells, NiUInt32* puiErrorCode);

    /**
        Create a scene for use during low detail rendering based on the 
        high detail cells.

        @param[out] puiErrorCode Return code if scene creation failed
        @return Pointer to the root of the created scene
    */
    NiNode* CreateSectorLowDetailScene(NiUInt32* puiErrorCode);

    /**
        Create the low detail render click suitable for rendering the cells on
        this sector.

        @param eTexType The type of texture used to render the low detail scene to
        @param pkScene the Scene's root node
        @param pkCamera the Scene's camera
        @param[out] puiErrorCode Return code if click creation failed
        @return pointer to the created renderclick
    */
    NiViewRenderClick* CreateLowDetailRenderClick(
        NiTerrainCell::TextureType::Value eTexType, NiNode* pkScene, 
        NiCamera* pkCamera, NiUInt32* puiErrorCode);
    
    /**
        Adjusts the render click so that it renders to the appropriate section
        of the texture that has changed since the last render. If no cells
        were in the queue, then the render click is disabled.

        @param pkPaintingData The data holding the cells to be updated
        @param[out] iMaxNumCells maximum number of cells to be rendered
        @return The number of cells updated
    */
    NiUInt32 UpdateLowDetailScene(RuntimePaintingData* pkPaintingData,
        NiInt32& iMaxNumCells);
    /**
        Causes the previous low detail texture to be rendered as the initial
        value of the texture. 

        Things that need doing:
        - Setup the new texture as a target for the click
        - Initialize with initial image or make it white

        @param pkTexture texture used as render target
        @param pkInitialTexture Initial texture value
        @param pkClick Render click to be used.
    */
    void InitializeRenderedTexture(NiRenderedTexture* pkTexture, 
        NiTexture* pkInitialTexture, NiRenderClick* pkClick);

    /**
        Create a low detail texture of a specified size. This texture
        will be a NiRenderedTexture for dynamic updates of the low detail
        appearance of the terrain. As such, there is no mipmapping supplied 
        with this texture. AssignLowDetailTexture is called by this function.

        @param eTexType The type of the texture to be created
        @param pkClick the render click to be used to render the texture
        @param uiMaskSize The size of the texture
        @param[out] puiErrorCode Return code if texture creation failed
        @return a pointer to the created texture
    */
    NiRenderedTexture* CreateLowDetailTexture(
        NiTerrainCell::TextureType::Value eTexType, NiRenderClick* pkClick, 
        NiUInt32 uiMaskSize, NiUInt32* puiErrorCode);

    /**
        Removes all extra render views from the render click that were used
        for initialization and makes sure the click never clears the render
        target again. This callback is only ever called once, as it removes
        itself from the click once executed.

        @param pkCurrentRenderClick render click to remove the views from
        @param pvCallbackData pointer to the call back data
        @return true if successful
    */
    static bool Callback_RemoveTextureInitialization(
        NiRenderClick* pkCurrentRenderClick, void* pvCallbackData);

    /**
        Sets the low detail textures and updates the relevant cells with the
        new information

        @param eTexType the type of the texture to set
        @param pkTexture Pointer to the texture to use
    */
    void SetTexture(NiTerrainCell::TextureType::Value eTexType, NiTexture* pkTexture);
};

#include "NiTerrainSector.inl"

#endif // NITERRAINSECTOR_H
