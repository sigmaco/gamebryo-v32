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
#ifndef NITERRAINSECTORDATA_H
#define NITERRAINSECTORDATA_H

#include <NiMemoryDefines.h>
#include <NiMeshLib.h>

#include "NiTerrainLibType.h"
#include "NiDynamicStreamCache.h"
#include "NiTerrainMaterial.h"
#include "NiTerrainConfiguration.h"

class NiTerrainCell;
class NiSurface;

/**
    This class is responsible for keeping a record of data and variables that
    are consistent across all leaves in the quad hierarchy; such as cell size,
    renderer data, shared data streams etc.

    It should be regarded as internal only and not be used by an
    application directly.
*/

/// @cond EMERGENT_INTERNAL
class NITERRAIN_ENTRY NiTerrainSectorData : public NiMemObject
{
public:

    /// The number of regions that exist in the index streams, one region per
    /// stitching state
    enum
    {
        /// Specifies the number of index regions in the index stream to 9.
        NUM_INDEX_REGIONS = 9,
    };


    /// The types of LOD that the terrain system can provide. As described in
    /// the function "SetLODMode"
    enum
    {
        LOD_MODE_2D = 0,
        LOD_MODE_25D,
        LOD_MODE_3D,
        NUM_LOD_MODES,

        LOD_MORPH_ENABLE = 0x08
    };

public:

    /// Default constructor.
    NiTerrainSectorData();

    /// Destructor
    ~NiTerrainSectorData();

    /// Cell size in both theoretical and vertex space
    /// Side length of a block in this sector, in voxels
    NiUInt32 GetCellSize() const;

    /// Side length of a block in this sector, in vertices
    NiUInt32 GetCellWidthInVerts() const;

    /// Side length of this sector, in voxels (at maximum detail - level N)
    NiUInt32 GetSectorSize() const;

    /**
        Set the side length of each cell in this sector, in voxels. Calling
        this function will also implicitly update the side length in vertices,
        and the sector side length members.
    */
    void SetCellSize(NiUInt32 uiSize);

    /// Side length of this sector, in vertices (at maximum detail - level N)
    NiUInt32 GetSectorWidthInVerts() const;

    /// Number of lower levels of detail, below the maximum (level N)
    NiUInt32 GetNumLOD() const;

    /**
        Number of lower levels of detail, below the maximum (level N). Calling
        this function will also update the side length of the sector and the
        total block count.
    */
    void SetNumLOD(NiUInt32 uisNumLOD);

    /// The number of cells that exist in total, throughout the entire
    /// quadtree in this sector.
    //NiUInt32 GetNumCells() const;

    /// The level of the highest LOD level that has been completely loaded
    //@{
    NiInt32 GetHighestLoadedLOD() const;
    void SetHighestLoadedLOD(NiInt32 iHighestLoadedLOD);
    //@}

    /**
        The LOD Scale is different to the camera LOD, in that camera LOD is a
        general detail level that is applied to the whole world (generally
        in a games settings), but the LOD Scale is a separate adjustment
        specific to a terrain. Both the camera LOD and the LOD scale are
        taken into account.

        @param fScale The scale factor for the LOD. Higher is better detail.
        Must be at least 2.0f * NiSqrt(2.0f)
    */
    //@{
    float GetLODScale() const;
    float GetLODShift() const;
    void SetLODScale(float fScale, float fShift);
    //@}

    /**
        Use these functions to control the method used to perform LOD
        ransitions on the terrain. The following modes are supported:
         LOD_MODE_2D - Uses the camera's X and Y position to determine
          the level of detail to display. Z is ignored.
         LOD_MODE_25D - Uses the camera's X and Y position as in 2D mode,
          but a maximum level of detail is placed on the terrain
          according to the camera's Z height.
         LOD_MODE_3D - Uses the camera's XYZ position to determine the
          level of detail to display. This mode may cause cracks and popping
          to appear on terrains that have quite steep regions.
    */
    //@{
    NiUInt32 GetLODMode() const;
    bool SetLODMode(NiUInt32 uiLODMode);
    //@}

    /**
        Force the sector to cull up to a maximum of the specified LOD level
    */
    //@{
    NiUInt32 GetHighestVisibleLOD() const;
    void SetHighestVisibleLOD(NiUInt32 uiMaximumLOD);
    //@}

    /**
        Force the sector to cull at least the specified LOD
    */
    //@{
    NiUInt32 GetLowestVisibleLOD() const;
    void SetLowestVisibleLOD(NiUInt32 uiMinimumLOD);
    //@}

    /// World transformation of the sector
    //@{
    const NiTransform& GetWorldTransform() const;
    void SetWorldTransform(const NiTransform& kWorldTransform);
    //@}

    /**
        @name Static Data Streams
        Static data streams used by blocks in an unmodified state.
    */
    //@{
    NiDataStream* GetStaticIndexStream() const;
    void SetStaticIndexStream(NiDataStream* pkStream);
    NiDataStream* GetStaticPositionStream(NiUInt32 uiDetailLevel) const;
    void SetStaticVertexStream(NiUInt32 uiDetailLevel, NiDataStream* pkStream);
    NiDataStream* GetStaticNormalTangentStream(NiUInt32 uiDetailLevel) const;
    void SetStaticNormalTangentStream(NiUInt32 uiDetailLevel, NiDataStream* pkStream);
    NiDataStream* GetStaticUVStream() const;
    void SetStaticUVStream(NiDataStream* pkStream);
    //@}

    /// Dynamic stream cache that is used to allocate dynamic streams to any
    /// deformed blocks. This will only exist if the sector is deformable, or
    /// in tool mode.
    //@{
    NiDynamicStreamCache* GetDynamicStreamCache() const;
    void SetDynamicStreamCache(NiDynamicStreamCache* pkCache);
    //@}

    /**
        Find the region in the index stream that corresponds to the given
        4-bit block stitching mask.

        @note Index stream regions are shared between both static and dynamic
        index streams.

        @param ucStitchingIndex Stitching index of the vertex index stream
        region to retrieve. Value must be less than or equal to 0xF.

        @return Index stream region corresponding to the given stitching index,
        or NULL if region not found or ucStitchingIndex is out of bounds.
    */
    NiDataStream::Region* GetIndexRegionByStitchIndex(NiUInt8 ucStitchingIndex) const;

    /**
        Retrieve the index stream region at the given position.

        @note Index stream regions are shared between both static and dynamic
        index streams.

        @return Region in static index stream at given position, or NULL if
        no region exists at that position.
    */
    NiDataStream::Region* GetIndexRegion(NiUInt8 ucPos) const;

    /**
        Set the index stream region for the given index. Ownership is not taken
        of the region, it must be deleted by the sector during shutdown.

        @param ucPos Region index to set. Valid values must be
            < ms_ucNumIndexRegions.
        @param pkIndexRegion Region with which to set at the specified
            position.
        @note Index stream regions are shared between both static and dynamic
            index streams.
    */
    void SetIndexRegion(NiUInt8 ucPos, NiDataStream::Region* pkIndexRegion);

    /**
    @name Rendering
    */
    //@{
    /// Culling Process to be used by this sector
    NiCullingProcess* GetCullingProcess() const;

    /// Camera to be used during LOD and rendering calculations:
    NiCamera* GetLODCamera() const;

    /// The LOD factor, squared, taken from the NiCamera contained in the last
    /// rendering context to be assigned to this sector
    float GetCameraLODSqr() const;

    /// The NiCamera frustum planes cached from the NiCamera contained in the
    /// last rendering context to be assigned to this sector
    const NiFrustumPlanes& GetFrustumPlanes() const;

    /// Set the culling process to be used by the blocks in this sector
    /// during rendering.
    void SetCullingProcess(NiCullingProcess* pkCuller);

    /// Set the Camera to use during LOD calculations:
    void SetLODCamera(NiCamera *pkCamera);

    /// Add the given block to the visible set
    void AddToVisible(const NiTerrainCell* pkBlock) const;

    //@}

    /// Defines whether or not this sector is deformable
    //@{
    bool GetDeformable() const;
    void SetDeformable(bool bDeformable);
    //@}

    NiInt16 GetSectorIndexX();
    void SetSectorIndexX(NiInt16 sXIndex);
    NiInt16 GetSectorIndexY();
    void SetSectorIndexY(NiInt16 sYIndex);

    inline const NiTerrainConfiguration& GetConfiguration() const;
    inline void SetConfiguration(NiTerrainConfiguration kConfiguration);

    /**
        Checks whether a particular level of detail has been loaded or not
        @param iLevel Level of detail we want to check
        @return true if the level is loaded
    */
    inline bool IsLODLoaded(NiInt32 iLevel = 0);

private:

    /// Always a power of 2 - length of a block in voxels
    NiUInt32 m_uiCellSize;

    /// Always equal to blockSize + 1. Length of a block in vertices
    NiUInt32 m_uiCellWidthInVerts;

    /// Always a power of 2 - size of the sector side, in voxels
    NiUInt32 m_uiSectorSize;

    /// Always equal to m_uiSectorSize + 1. Length of the sector in vertices
    NiUInt32 m_uiSectorWidthInVerts;

    /// Deformation
    bool m_bIsDeformable;

    /// Number of lower levels of detail that exist, in addition to the maximum
    NiUInt32 m_uiNumLOD;

    /// Sector Index
    //@{
    NiInt16 m_sSectorIndexX;
    NiInt16 m_sSectorIndexY;
    //@}

    /// The level of the highest LOD level that has been completely loaded
    NiInt32 m_iHighestLoadedLOD;

    /// The level of detail requested to be loaded:
    NiInt32 m_iTargetLoadedLOD;

    /// Static data streams that are used by non deformed blocks
    NiDataStreamPtr m_spStaticIndexStream;
    NiDataStreamPtr m_spStaticUVStream;
    NiTObjectArray<NiDataStreamPtr> m_kStaticVertexStreams;
    NiTObjectArray<NiDataStreamPtr> m_kStaticNormalTangentStreams;

    // Responsible for managing dynamic block data
    NiDynamicStreamCachePtr m_spDynamicStreamCache;

    /// Rendering info
    NiCullingProcess* m_pkCullingProcess;
    NiCamera* m_pkLODCamera;
    float m_fCameraLODSqr;
    float m_fTerrainLODscale;
    float m_fTerrainLODshift;
    NiUInt32 m_uiTerrainLODmode;
    NiUInt32 m_uiHighestVisibleLOD;
    NiUInt32 m_uiLowestVisibleLOD;

    // Index regions
    NiUInt8 m_aucIndexRegionsMap[16];
    NiTPrimitiveArray<NiDataStream::Region*> m_kIndexRegions;

    /// The transformation of the terrain in the world. A scale of 1.0 will
    /// lead to a vertex spacing of 100.0 units at max detail level
    NiTransform m_kWorldTransform;

    /// Frustum of the last camera to be set via SetRenderingContext()
    NiFrustumPlanes m_kFrustumPlanes;

    /// The configuration of the terrain
    NiTerrainConfiguration m_kTerrainConfiguration;

};
/// @endcond

#include "NiTerrainSectorData.inl"

#endif // NITERRAINSECTORDATA_H
