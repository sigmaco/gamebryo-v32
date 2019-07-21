// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef NITERRAINCELL_H
#define NITERRAINCELL_H

#include <NiTArray.h>
#include <NiMesh.h>
#include <NiMain.h>
#include <NiBoxBV.h>

#include "NiTerrainLibType.h"
#include "NiTerrainSectorData.h"
#include "NiTerrainResourceManager.h"
#include "NiTextureRegion.h"
#include "NiRay.h"
#include "NiUCharPool.h"
#include "NiTerrainRandomAccessIterator.h"
#include "NiTextureRegion.h"
#include "NiTerrainCellShaderData.h"

class NiTerrainDecal;
class NiTerrainSector;

/**
    This abstract class represents a small portion of a terrain sector. This portion is 
    represented by a mesh and may be at any level of detail within the terrain. The two
    subclasses that are used to further define the terrain hierarchy are the NiTerrainCellNode and
    NiTerrainCellLeaf.
*/
class NITERRAIN_ENTRY NiTerrainCell : public NiNode
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:
    /// Used to distinguish the different texture types
    typedef NiTerrainResourceManager::TextureType TextureType;

    /// Used to distinguish the different stream types
    typedef NiTerrainResourceManager::StreamType StreamType;

    /// Used to distinguish the different borders of this cell.
    enum BORDERS 
    {
        /// Unspecified border.
        BORDER_NONE = 0,

        /// Borders the bottom.
        BORDER_BOTTOM = 1,

        /// Borders the right.
        BORDER_RIGHT = 2,

        /// Borders the top.
        BORDER_TOP = 4,

        /// Borders the left.
        BORDER_LEFT = 8
    };

    /**
        Constructor
        @param pkSector The sector the cell belongs to
        @param uiLevel the level of detail the cell is at
    */
    NiTerrainCell(NiTerrainSector* pkSector, NiUInt32 uiLevel);

    /**
        Destructor
    */
    virtual ~NiTerrainCell();

    /// @cond EMERGENT_INTERNAL
    static void _SDMInit();
    static void _SDMShutdown();
    /// @endcond

    /// @name Parent Sector
    //@{

    /// Retrieve a pointer to the sector that owns this quadtree cell (const
    /// version).
    inline const NiTerrainSector* GetContainingSector() const;

    /// Retrieve a pointer to the sector that owns this quadtree cell.
    inline NiTerrainSector* GetContainingSector();
    //@}

    /**
        Get the detail level of this tree node.
        
        From 0 at lowest detail, to n at the highest detail.
    */
    inline NiUInt32 GetLevel() const;

    /**
        Set the detail level of this tree node.
        
        From 0 at lowest detail, to n at the highest detail.
    */
    inline void SetLevel(NiUInt32 uiLevel);
    
    /**
        Get the number of LOD subdivisions below this block's level. This is 
        equivalent to Sector->GetNumLOD() - GetLevel() - 1.
    */
    inline NiUInt32 GetNumSubDivisions() const;

    /**
        Retrieve the SIZE of the cell. Size is always a power of 2.
    */
    inline NiUInt32 GetCellSize() const;

    /**
        Retrieve the WIDTH of the cell, in vertices.
        This value will be equal to (2^n) + 1 for some n.
    */
    inline NiUInt32 GetWidthInVerts() const;

    /**
        World Location bounding sphere.
    */
    inline const NiBound& GetLocalBound() const;

    /**
        World Location bounding box.
    */
    inline const NiBoxBV& GetLocalBoxBound() const;

    /**
        Get the bottom left index of this cell.
        
        The bottom left index corresponds to the sector scope index of the 
        vertex found at the bottom left of this cell.

        @param kIndex Sector scope index of the bottom left vertex found in 
            this cell.
    */
    inline void GetBottomLeftIndex(NiIndex& kIndex) const;

    /**
        Set the bottom left index of this cell.
        
        @param kIndex Sector scope index of the bottom left vertex found in 
            this cell.
    */
    inline void SetBottomLeftIndex(const NiIndex& kIndex);

    /**
        The Block ID of a cell is a unique key that is used to identify any 
        given cell, at any level. 

        A Block ID takes into account the level of the cell and the bottom 
            left index.
    */
    inline NiUInt32 GetCellID() const;
    
    /**
        Set the block ID for this cell.
    */
    inline void SetCellID(NiUInt32 uiRegionID);

    /**                   
        Get the region ID for this cell.
        
        The region ID also corresponds to the index of the 
        NiDataStream::Region within the sectors static position stream
        that belongs to this cell.
    */
    inline NiUInt32 GetRegionID() const;
    
    /**
        Set the region ID for this cell.
    */
    inline void SetRegionID(NiUInt32 uiRegionID);

    /**
        Reset the NiBound object according to the given center and radius, and
        store the given sum of positions.

        @param kCenter Center of bounding sphere
        @param fRadius Radius of bounding sphere
    */
    void SetBoundData(NiPoint3 kCenter, float fRadius);
    
    /**
        Reset the bounding box according to the given box.
    */
    inline void SetBoundVolumeBox(const NiBoxBV& kBox);

    /**
        Get the ID of the region in the index buffer to use for this cell. 
        
        Generally universal across standard and custom index buffers.
    */
    inline NiUInt8 GetStitchingIndex() const;

    /**
        This override of the base class function SetWorldScale is used to
        update the morphing data when scaling is done on the terrain
    */
    inline void SetWorldScale(float fScale);

    /**
        Retrieves the parent cell for this cell
    */
    inline NiTerrainCell* GetParent();

    /**
        Retrieves the parent cell for this cell
    */
    inline const NiTerrainCell* GetParent() const;

    /**
        Sets the parent cell for this cell
    */
    inline void SetParent(NiTerrainCell* pkCell);

    /**
        Retrieves an NiTerrainVertex object that is found within this block. 

        The given indices are in cell scope, meaning a value 
        from 0 to GetSize() (inclusive).

        @param kIterator the iterator to be used to retrieve the vertex
        @param kVertex Resulting vertex.
        @param kLocal CELL SCOPE index of the vertex within this leaf to 
            retrieve.
        @note You can derive the local X, Y position of a vertex from the index
            itself. It is recommended to do so as opposed to calling this 
            function where possible.
        @note Border vertices are conceptually shared between adjacent blocks, 
            but the data itself is duplicated.
    */
    inline void GetVertexAt(
        const NiTerrainPositionRandomAccessIterator& kIterator,
        NiPoint3& kVertex, const NiIndex& kLocal) const;

    /**
        Retrieves an NiTerrainVertex object that is found within the parent 
        sector.
        
        The given indices are in Sector scope, meaning a value from 0 to
        SectorSize (inclusive).

        @param kIterator the iterator to be used to retrieve the vertex
        @param kVertex Resulting vertex.
        @param kSector SECTOR SCOPE index of the vertex within this leaf to 
            retrieve.
        @note You can derive the local X, Y position of a vertex from the index
            itself. It is recommended to do so as opposed to calling this 
            function where possible.
    */
    inline void GetVertexAtSector(
        const NiTerrainPositionRandomAccessIterator& kIterator,
        NiPoint3& kVertex, const NiIndex& kSector) const;

    /**
        Return the height of the vertex at the given cell scope index.
        @param kIterator the iterator to be used to retrieve the vertex
        @param kLocal CELL SCOPE index of the vertex within this leaf to 
            retrieve.
    */
    inline float GetHeightAt(
        const NiTerrainPositionRandomAccessIterator& kIterator,
        const NiIndex& kLocal) const;
    
    /**
        Return the height of the vertex at the given sector scope index.
        @param kIterator the iterator to be used to retrieve the vertex
        @param kSector SECTOR SCOPE index of the vertex within this leaf to 
            retrieve.
    */
    inline float GetHeightAtSector(
        const NiTerrainPositionRandomAccessIterator& kIterator,
        const NiIndex& kSector) const;

    /**
        Return the normal of the vertex at the given cell scope index.
        @param kIterator the iterator to be used to retrieve the normal
        @param kNormal Resulting normal.
        @param kLocal CELL SCOPE index of the normal within this leaf to 
            retrieve.
    */
    inline void GetNormalAt(const NiTerrainNormalRandomAccessIterator& kIterator,
        NiPoint3& kNormal, const NiIndex& kLocal) const;    

    /**
        Attempts to find a cell adjacent to this cell, sharing the given 
        border.
        
        Diagonals can be represented by bitwise AND-ing together 
        two neighboring borders.

        @param uiBorder bitwise mask of NiTerrainCell::BORDERS enum
            dictating on which border to check for an adjacent cell.
        @return Adjacent cell if found, null if no adjacent cell exists on
            given border.
    */
    inline NiTerrainCell* GetAdjacent(NiUInt32 uiBorder);

    /**
        Attempts to find a cell adjacent to this cell, sharing the given 
        border (const version).
        @param uiBorder bitwise mask of NiTerrainCell::BORDERS enum
            dictating on which border to check for an adjacent cell.
        @return Adjacent cell if found, bad pointer if no adjacent cell exists 
            on given border
    */
    inline const NiTerrainCell* GetAdjacent(NiUInt32 uiBorder) const;

    /**
        Attempts to find a cell adjacent to this cell, sharing the given 
        border.
        
        Diagonals can be represented by bitwise AND-ing together 
        two neighboring borders. This is a fast method which always assumes
        that the adjacent exists.

        @param uiBorder bitwise mask of NiTerrainCell::BORDERS enum
            dictating on which border to check for an adjacent cell.
        @return Adjacent cell if found, bad pointer if no adjacent cell exists 
            on given border
    */
    inline NiTerrainCell* GetAdjacentFast(NiUInt32 uiBorder);

    /**
        Attempts to find a cell adjacent to this cell, sharing the given 
        border (fast, const version).

        @param uiBorder bitwise mask of NiTerrainCell::BORDERS enum
            dictating on which border to check for an adjacent cell.
        @return Adjacent cell if found, bad pointer if no adjacent cell exists 
            on given border
    */
    inline const NiTerrainCell* GetAdjacentFast(NiUInt32 uiBorder) const;

    /**
        Return the sector scope index, generated from a given cell scope index.

        @param kLocal Cell Scope index
        @return Sector scope index
    */
    inline const NiIndex SectorIndexFromLocal(const NiIndex& kLocal) const;

    /**
        Convert a given sector scope index to a cell scope index within 
        this cell. 
        
        @param kSector Sector scope index to convert.
        @param kLocal Resulting cell scope index.
        @return True if given sector scope index corresponds to a local index
    */
    bool SectorIndexToLocal(const NiIndex& kSector, NiIndex& kLocal) const;
    
    /**
        Convert a given sector scope index to a cell scope index within 
        this cell.
        
        This is an UNSAFE FUNCTION, it performs no bounds checking.
        
        @param kSector Sector scope index to convert.
        @param kLocal Resulting cell scope index.
    */
    inline void SectorIndexToLocalFast(const NiIndex& kSector, 
        NiIndex& kLocal) const;

    /// @name Update functionality
    //@{

    /**
        Request an update of the tree.
        
        If any vertices within this cell have changed their locations, 
        an update must be requested. This is a recursive function, and 
        will trigger an update request up to the root of the tree. 
        This function does not perform the actual update, just flags that 
        one is required. This function makes an assumption: if a parent 
        already has new data, then all of its parents also have new data.
    */
    void RequestUpdate();

    /**
        Returns true if this cell, or any cells below us require an update,
        otherwise false.
    */
    bool RequiresUpdate() const;

    /**
        Request that when the cell is next updated, the bounds (for just this cell) should be 
        recalculated. This does not call RequestUpdate(), this needs to be done by the calling
        function.
    */
    void RequestBoundsUpdate();

    /**
        Returns true if this cell has just been paged in, or rebuilt. This flag is true if the
        cell has not been updated since it was created.
    */
    bool IsJustLoaded() const;
    
    /**
        Apply any incremental changes that were made to this cell's bounds via
        the RecenterCountainingBounds function.
    */
    virtual void Update();
    virtual void UpdateEffectsDownward(NiDynamicEffectState* pkParentState);
    virtual void UpdatePropertiesDownward(NiPropertyState* pkParentState);

    /**
        This function forces an update of the bounding box/sphere that is used
        for this cell. 
    */
    virtual void UpdateBounds();

    /**
        This function updates the shader constant data for morphing. 
        This function is called whenever the scaling of the terrain is
        changed, and when the LOD scale is changed.
    */
    inline void UpdateMorphConstants();

    /**
        Set the 'Drawn' flags for all blocks in the quadtree to false.
        
        This function should only be called on the root node of the quadtree,
        as the drawn cache is shared by all cells in a tree
    */
    inline void ResetCullingResults();

    /**
        Recursively build the visible set of cells, adding it to the visible 
        set stored in the sector data's rendering context.
        
        This function also prepares the 'drawn' member variables to be used
        in ProcessBorders.

        @note To optimize, this function assumes that if any one child 
            exists, all other children will be present.
      
        @return True if this cell or any of its children are visible.
    */
    virtual bool ProcessLOD();

    /**
        Update the index buffer region used by this cell according to which
        borders need to be stitched.
        
        This is a recursive function, that will also process the borders of
        all block children.
    */
    virtual void ProcessBorders();  

    /**
        Sets the UPDATE_CELL_JUST_LOADED flag to true. This will mark the cell 
        as requiring to update its effects and properties 
    */
    inline void MarkCellLoaded();
    //@}

    ///@name Streams Functionality
    //@{

    /**
        Get the specified stream from the mesh of the cell.

        @param eStreamType the type of stream to retrieve
        @return the corresponding stream
    */
    NiDataStream* GetStream(StreamType::Value eStreamType);

    /**
        Return true if this cell has been assigned a dynamic vertex
        stream, false otherwise.
    */
    inline bool HasDynamicVertexStreams();

    /**
        Return true if this cell has been assigned a dynamic UV stream,
        false otherwise.
    */
    inline bool HasDynamicUVStream();

    /**
        Return true if this cell has been assigned a dynamic index stream,
        false otherwise.
    */
    inline bool HasDynamicIndexStream();

    /**
        Return the dynamic stream corresponding to the given stream type,
        or NULL if no dynamic stream exists for the given type.

        @param eStream the type of stream to retrieve
        @return the corresponding stream
    */
    NiDataStream* GetDynamicStream(StreamType::Value eStream);

    /**
        Assign a dynamic vertex stream to this block.
        
        This will take the place of the static stream for this block only.

        @param pkPositionStream The stream to use for positions
        @param pkNormalTangentStream the stream to use for normal and tangent data
        @return true if successful
    */
    bool SetDynamicVertexStreams(NiDataStream* pkPositionStream, 
        NiDataStream* pkNormalTangentStream);

    /**
        Assign a dynamic index stream to this block.
        
        This will take the place of the static stream for this block only.
        @param pkIndexStream the stream to use for index data
        @return true if successful
    */
    bool SetDynamicIndexStream(NiDataStream* pkIndexStream);

    /**
        Assign a dynamic texture coordinate stream to this block.
        
        This will take the place of the static stream for this block only.
        @param pkUVStream the stream to use for UV data
        @return true if successful
    */
    bool SetDynamicUVStream(NiDataStream* pkUVStream);

    /**
        Revert this cell to use a static vertex data streams if a
        dynamic streams were previously assigned.
        
        This function reverts the position, normal and tangent streams.
    */
    void RemoveDynamicVertexStreams();

    /**
        Revert this cell to use a static index data stream if a
        dynamic stream was previously assigned.
    */
    void RemoveDynamicIndexStream();

    /**
        Revert this cell to use a static texture coordinate data stream if a
        dynamic stream was previously assigned.
    */
    void RemoveDynamicUVStream();

    //@}
    
    /// @name Mesh Management
    //@{

    /**
        Creates the mesh for this cell using currently available data streams.

        The mesh will use any custom data streams it finds, but will fall back
        on the static streams found in the sector data.
    */
    void CreateMesh();

    /**
        Destroy the mesh associated with this cell, including surface blend
        textures and shader extra data.
        
        This function will not have any effect on associated dynamic streams,
        or delete any decals.
    */
    virtual void DestroyMesh();

    /**
        Return the NiMesh object currently attached to this cell.
        
        This function should only be called if a valid mesh exists in this
        block.

        @return the Mesh attached to the cell
    */
    inline NiMesh& GetMesh() const;

    /**
        Gets a reference to the shader data bound to the mesh.
        @return The shader data passed on to either the vertex shader or the pixel shader.
    */
    inline NiTerrainCellShaderData& GetShaderData();
    //@}

    /**
        Sets the offset and scale to be used by the cell for a texture region

        @param kOffset the offset for that texture
        @param fScale the scale to use on that texture
        @param eTexType the texture region to affect (can be the Blend mask for 
            a leaf or the low detail texture.
    */
    virtual void SetTextureRegion(NiPoint2 kOffset, float fScale, 
        NiTerrainCell::TextureType::Value eTexType);

    /**
        Sets the texture to use for a particular texture region

        @param pkTexture the texture the texture region will point to
        @param eTexType the texture region to affect (can be the Blend mask for 
            a leaf or the low detail texture.
    */
    virtual void SetTexture(NiTexture* pkTexture, 
        NiTerrainCell::TextureType::Value eTexType);

    /**
        Gets the texture to use for a particular texture region

        @param eTexType the texture region to affect (can be the Blend mask for 
            a leaf or the low detail texture.
        @return pkTexture the texture the texture region will point to
    */
    virtual NiTexture* GetTexture(NiTerrainCell::TextureType::Value eTexType);
    
    /**
        Calculate whether this cell should be drawn, according to the 
        camera position in the current rendering context. This function 
        takes both raw 3D distance from camera and morph radius weightings 
        into account. This function does not perform frustum culling.

        @return true if this block is a candidate for rendering
    */
    bool IsInRange();

    /**
        Add a surface to this cell.
        
        If the surface already exists, it will simply move that index to the
        given priority
        
        @param uiSurfaceIndex the index of the new surface
        @param uiNewPriority The position in the surface priority to insert.
        @return True if the addition was successful, false if the leaf is full.
    */
    bool AddSurface(NiUInt32 uiSurfaceIndex, NiUInt32 uiNewPriority = 0);
    
    /**
        Remove a surface from this cell.
        
        Optionally specify not to recalculate the best pixel spacing cache
        after the surface is removed, in which case it must be performed
        manually before any surface deformation occurs.
        
        @param uiSurfaceIndex the index of the surface to remove
        @return True if the surface was found.
    */
    bool RemoveSurface(NiUInt32 uiSurfaceIndex);

    /**
        Functions that gets the texture region associated with the given type.
        Possible types are BLEND_MASK (for the Cell leaf only) LOW_RES_MASK
        or ALL_MASK. If ALL_MASK is given as a parameter, the low detail 
        texture region will be returned.

        @param eType the texture region to affect (can be the Blend mask for 
            a leaf or the low detail texture.
        @return the requested texture region
    */
    virtual const NiTextureRegion& GetTextureRegion(
        NiTerrainCell::TextureType::Value eType) const;

    /**
        Functions that gets the texture region associated with the given type.
        Possible types are BLEND_MASK (for the Cell leaf only) LOW_RES_MASK
        or ALL_MASK. If ALL_MASK is given as a parameter, the low detail 
        texture region will be returned.

        @param eType the texture region to affect (can be the Blend mask for 
            a leaf or the low detail texture.
        @return the requested texture region
    */
    virtual NiTextureRegion& GetTextureRegion(
        NiTerrainCell::TextureType::Value eType);

    /**
        Function that allows getting pixel values from the 
        different texture regions. 

        @param eType the texture region to affect (can be the Blend mask for 
            a leaf or the low detail texture.
        @param kCoordinates define the coordinates in the local texture space
            that we want to read the value at
        @param uiComponent the channel of the texture we want the value for
        @return returns the value found
    */
    virtual NiUInt8 GetPixelAt(NiTerrainCell::TextureType::Value eType, 
        NiIndex kCoordinates, NiUInt32 uiComponent) const;

    /**
        Function that allows setting pixel values for the 
        different texture regions. 

        @param eType the texture region to affect (can be the Blend mask for 
            a leaf or the low detail texture.
        @param kCoordinates define the coordinates in the local texture space
            that we want to read the value at
        @param uiComponent the channel of the texture we want the value for
        @param ucNewValue out the new value we want to set
    */
    virtual void SetPixelAt(NiTerrainCell::TextureType::Value eType, 
        NiIndex kCoordinates, NiUInt32 uiComponent, NiUInt8 ucNewValue);

protected:
        
    /// LOD
    enum DRAWN 
    {
        /// Cell was culled by the LOD
        LOD_CULLED = 0,

        /// Cell was culled by the frustum
        FRUSTUM_CULLED = 1,

        /// This cell was rendered by the LOD
        SELF_VISIBLE = 2,

        /// This cell's children were rendered by the LOD
        CHILDREN_VISIBLE = 3,

        /// A mask to detect visible trees 
        /// (either children or self are rendered)
        VISIBLE_TREE_FLAG = 0x02
    };

    /// Helper enumeration.
    enum
    {
        /// The number of children a cell can have
        NUM_CHILDREN = 4,
    };

    /// Lighting Status enumerations.
    enum
    {
        /// Lighting data is valid on this cell
        LIGHTING_BUILT = 0,

        /// Lighting data is not valid on this cell
        LIGHTING_OUTDATED = 1,

        /// Lighting data is in the process of being updated and is still 
        /// not valid yet.
        LIGHTING_IN_PROGRESS = 2
    };
    
    /// Update request flags.
    enum
    {
        /// Nothing requires updating on this cell.
        UPDATE_CELL_NOTHING = 0,

        /// A general update has been requested for this cell.
        UPDATE_CELL_REQUIRED = 1 << 0,

        /// The bounds require updating on this cell
        UPDATE_CELL_BOUNDS = 1 << 1,

        /// The morphing data requires updating
        UPDATE_CELL_MORPH_DATA = 1 << 2,

        /// The texture regions have changed
        UPDATE_CELL_TEXTURE_REGIONS = 1 << 3,

        /// Update cell's effects and properties according to parent
        UPDATE_CELL_JUST_LOADED = 1 << 4,

        /// The offset to use when beginning a new set 
        UPDATE_CELL_LAST_ENTRY = 1 << 5
    };

    /// Stream references (The index of the streamref for a streamtype on the mesh)
    enum STREAM_INDEX
    {
        /// Index stream
        INDEX = 0,
        /// Texture coordinate stream
        UV = 1,
        /// Position and morph height stream
        POSITION = 2,
        /// Normals and Tangents stream
        NORMAL_TANGENT = 3
    };

    /**
        Fetches the allocator

        @return A pointer to the Terrain ressource manager
    */
    NiTerrainResourceManager* GetResourceManager();

    /**
        Creates the required shader data.
        @return true if successful
    */
    virtual bool CreateShaderData();

    /**
        Updates the texturing property and shader constants to the correct
        values for rendering.
    */
    void UpdateShaderData();

    /**
        Retrieves the property and effect states from the terrain and
        applies them to the cell.
    */
    void UpdateJustLoaded();

    /**
        Retrieves parent region values and creates the texture region for 
        this cell.
    */
    void UpdateTextureRegions();

    /**
        Returns the texturing property set on this cell
        @return A pointer to the Texturing property set on this cell
    */
    NiTexturingProperty* GetTexturingProperty();
    
    /**
        Add this cell to the visible set contained in the sector data's
        rendering context
    */
    inline void AddToVisible();

    /**
        An efficient method to detect whether or not this cell was culled by
        the most recent call to ProcessLOD

        @return true if this cell was not added to the most recently 
            generated visible set.
    */
    inline bool IsVisible() const;

    /**
        Get/Set the latest result of culling on this cell.
    */
    //@{
    inline void SetCullingResult(NiUInt8 ucResult);
    inline NiUInt8 GetCullingResult() const;
    //@}

    /// @cond EMERGENT_INTERNAL
    /**
        Wrapper function that allows derived classes to call upon AddToVisible 
        from a NiTerrainCell object. 

        @param pkCell the Cell to be added
    */
    static void AddCellToVisible(NiTerrainCell* pkCell);
    
    /**
        Wrapper function that allows derived classes to call upon IsVisible 
        from a NiTerrainCell object. 

        @param pkCell the Cell to be checked
        @return true if the cell is visible
    */
    static bool IsCellVisible(NiTerrainCell* pkCell);    
    /// @endcond

    /** @name Level Of Detail */
    //@{  
    void SetStitchingIndex(NiUInt8 ucStitchingIndex);
    //@}
    
    /**
        Get the active configuration in use by the terrain containing this 
        block

        @return the Current terrain configuration
    */
    const NiTerrainConfiguration& GetConfiguration() const;

    //@{
    /**
        Retrieve the Adjacent cell according to the given border

        @param uiBorder The border to get the adjacent cell for
        @return the Adjacent cell.
    */
    NiTerrainCell* DoGetAdjacent(NiUInt32 uiBorder) const;
    NiTerrainCell* DoGetAdjacentFast(NiUInt32 uiBorder) const;
    //@}

    //@{
    /**
        Virtual implementations of the Surface adding function.
        
        @param uiSurfaceIndex The index of the surface to add
        @param uiNewPriority The priority the new surface should have
        @return true when successful
    */
    virtual bool DoAddSurface(NiUInt32 uiSurfaceIndex, NiUInt32 uiNewPriority) = 0;

    /**
        Virtual implementations of the Surface removing function.
        
        @param uiSurfaceIndex The index of the surface to remove
        @return true when successful
    */
    virtual bool DoRemoveSurface(NiUInt32 uiSurfaceIndex) = 0;
    //@}

    /**
        Invert the border directions specified 
        (BORDER_LEFT becomes BORDER_RIGHT) etc

        @param uiBorder the border to invert
        @return the resulting border
    */
    NiUInt32 GetOppositeBorder(NiUInt32 uiBorder);

    /// @{
    /**
        Manage update flags
    */
    inline void SetUpdateFlag(bool bFlagValue, NiUInt32 uiFlagMask);
    inline bool GetUpdateFlag(NiUInt32 uiFlagMask) const;
    /// @}

    /// Shader data specified on a per-cell basis.
    NiTerrainCellShaderData m_kShaderData;

    /// World Location bounding box
    NiBoxBV m_kBoxBound;

    /// World Location bounding sphere
    NiBound m_kBound;

    /// The bottom left index of this cell
    NiIndex m_kDataBottomLeftIndex;

    /// Storage for update flags
    NiUInt32 m_uiUpdateFlags;
    
    /// Determines the quad tree level.
    NiUInt32 m_uiLevel;

    /// The ID of our position region (in the appropriate LOD's stream)
    /// This ID is in QuadTree space, ie Siblings are stored sequentially
    NiUInt32 m_uiRegionID;

    /// The ID of the block and the position in the sectors cell array
    NiUInt32 m_uiCellID;

    /// The index of the value to modify to signal the state of this cell's culling operations
    NiUInt32 m_uiDrawnPoolIndex;

    /// The maximum distance in terrain space that this cell may be rendered from
    float m_fMaxDistanceSqr;
    
    /// The index stream to use on this cell for stitching
    NiUInt8 m_ucStitchingIndex;

    /// A pointer to the sector that contains this quad tree
    NiTerrainSector* m_pkContainingSector;

    /// A pointer to the sectors settings for ease of access
    NiTerrainSectorData* m_pkSectorData;

    NiUCharPool* m_pkDrawnPool;

    //@{
    /**
        Variables to store the custom streams for this particular cell
        Not-null if we are using a custom dynamic stream.
    */
    NiDataStream* m_pkCustomPositionStream;
    NiDataStream* m_pkCustomNormalTangentStream;
    NiDataStream* m_pkCustomIndexStream;
    NiDataStream* m_pkCustomUVStream;
    //@}
    
    /// The associated mesh
    NiMeshPtr m_spMesh;

    /// The parent cell
    NiTerrainCell* m_pkParentCell;

    /// The low detail texture region
    NiTextureRegion m_kLowDetailTextureRegion;

    /// The low detail normal texture
    NiTexturePtr m_spLowDetailNormalTexture;
};

NiSmartPointer(NiTerrainCell);

#include "NiTerrainCell.inl"

#endif
