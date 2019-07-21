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

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSectorData::GetCellSize() const
{
    return m_uiCellSize;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSectorData::GetCellWidthInVerts() const
{
    return m_uiCellWidthInVerts;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSectorData::GetSectorSize() const
{
    return m_uiSectorSize;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSectorData::GetSectorWidthInVerts() const
{
    return m_uiSectorWidthInVerts;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetCellSize(NiUInt32 uiSize)
{
    EE_ASSERT(NiIsPowerOf2(uiSize));

    m_uiCellSize = uiSize;
    m_uiCellWidthInVerts = uiSize + 1;
    m_uiSectorSize = m_uiCellSize << m_uiNumLOD;
    m_uiSectorWidthInVerts = m_uiSectorSize + 1;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSectorData::GetNumLOD() const
{
    return m_uiNumLOD;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetNumLOD(NiUInt32 uiNumLOD)
{
    m_uiNumLOD = uiNumLOD;
    m_uiSectorSize = m_uiCellSize << m_uiNumLOD;
    m_uiSectorWidthInVerts = m_uiSectorSize + 1;

    // Number of blocks
    NiUInt32 uiNumBlocks = 0;
    for (NiUInt32 ui = 0; ui <= m_uiNumLOD; ++ui)
        uiNumBlocks += (1 << ui) * (1 << ui);

    // Resize the stream arrays:
    m_kStaticVertexStreams.SetSize(GetNumLOD() + 1);
    m_kStaticNormalTangentStreams.SetSize(GetNumLOD() + 1);
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSectorData::GetLODMode() const
{
    return m_uiTerrainLODmode;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainSectorData::SetLODMode(NiUInt32 uiLODMode)
{
    if ((uiLODMode & ~LOD_MORPH_ENABLE) < NUM_LOD_MODES)
    {
        m_uiTerrainLODmode = uiLODMode;
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSectorData::GetHighestVisibleLOD() const
{
    return m_uiHighestVisibleLOD;
}
//---------------------------------------------------------------------------
inline void NiTerrainSectorData::SetHighestVisibleLOD(NiUInt32 uiMaximumLOD)
{
    m_uiHighestVisibleLOD = uiMaximumLOD;
}
//---------------------------------------------------------------------------
inline NiUInt32 NiTerrainSectorData::GetLowestVisibleLOD() const
{
    return m_uiLowestVisibleLOD;
}
//---------------------------------------------------------------------------
inline void NiTerrainSectorData::SetLowestVisibleLOD(NiUInt32 uiMinimumLOD)
{
    m_uiLowestVisibleLOD = uiMinimumLOD;
}

//--------------------------------------------------------------------------------------------------
inline NiInt32 NiTerrainSectorData::GetHighestLoadedLOD() const
{
    return m_iHighestLoadedLOD;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetHighestLoadedLOD(
    NiInt32 iHighestLoadedLOD)
{
    m_iHighestLoadedLOD = iHighestLoadedLOD;
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainSectorData::GetLODShift() const
{
    return m_fTerrainLODshift;
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainSectorData::GetLODScale() const
{
    return m_fTerrainLODscale;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetLODScale(float fScale, float fShift)
{
    // Minimum scale represents the minimum diameter of the smallest
    // circle used to define the highest detail region.
    static const float fMinimumScale = 2.0f * NiSqrt(2.0);
    EE_ASSERT(fScale >= fMinimumScale);
    if (fScale < fMinimumScale)
        fScale = fMinimumScale;
    m_fTerrainLODscale = fScale;
    m_fTerrainLODshift = fShift;
}

//--------------------------------------------------------------------------------------------------
inline const NiTransform& NiTerrainSectorData::GetWorldTransform() const
{
    return m_kWorldTransform;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetWorldTransform(
    const NiTransform& kWorldTransform)
{
    m_kWorldTransform = kWorldTransform;
}

//--------------------------------------------------------------------------------------------------
inline NiDataStream* NiTerrainSectorData::GetStaticIndexStream() const
{
    return m_spStaticIndexStream;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetStaticIndexStream(NiDataStream* pkStream)
{
    m_spStaticIndexStream = pkStream;
}

//--------------------------------------------------------------------------------------------------
inline NiDataStream::Region* NiTerrainSectorData::GetIndexRegion(NiUInt8 ucPos)
    const
{
    if (ucPos >= m_kIndexRegions.GetSize())
        return 0;

    return m_kIndexRegions[ucPos];
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetIndexRegion(
    NiUInt8 ucPos, NiDataStream::Region* pkIndexRegion)
{
    EE_ASSERT(ucPos < NUM_INDEX_REGIONS);
    m_kIndexRegions.SetAt(ucPos, pkIndexRegion);
}

//--------------------------------------------------------------------------------------------------
inline NiDataStream::Region* NiTerrainSectorData::GetIndexRegionByStitchIndex(
    NiUInt8 ucStitchingIndex) const
{
    EE_ASSERT(ucStitchingIndex <= 0xF);
    EE_ASSERT(ucStitchingIndex == 0 || 
        m_aucIndexRegionsMap[ucStitchingIndex] != 0);
    return GetIndexRegion(m_aucIndexRegionsMap[ucStitchingIndex]);
}

//--------------------------------------------------------------------------------------------------
inline NiDataStream* NiTerrainSectorData::GetStaticPositionStream(
    NiUInt32 uiDetailLevel) const
{
    if (uiDetailLevel < m_kStaticVertexStreams.GetSize())
    {
        return m_kStaticVertexStreams[uiDetailLevel];
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetStaticVertexStream(
    NiUInt32 uiDetailLevel, NiDataStream* pkStream)
{
    m_kStaticVertexStreams.SetAt(uiDetailLevel, pkStream);
}

//--------------------------------------------------------------------------------------------------
inline NiDataStream* NiTerrainSectorData::GetStaticNormalTangentStream(
    NiUInt32 uiDetailLevel) const
{
    if (uiDetailLevel < m_kStaticNormalTangentStreams.GetSize())
    {
        return m_kStaticNormalTangentStreams[uiDetailLevel];
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetStaticNormalTangentStream(
    NiUInt32 uiDetailLevel, NiDataStream* pkStream)
{
    m_kStaticNormalTangentStreams.SetAt(uiDetailLevel, pkStream);
}

//--------------------------------------------------------------------------------------------------
inline NiDataStream* NiTerrainSectorData::GetStaticUVStream() const
{
    return m_spStaticUVStream;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetStaticUVStream(NiDataStream* pkStream)
{
    m_spStaticUVStream = pkStream;
}

//--------------------------------------------------------------------------------------------------
inline NiDynamicStreamCache* NiTerrainSectorData::GetDynamicStreamCache() const
{
    return m_spDynamicStreamCache;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetDynamicStreamCache(
    NiDynamicStreamCache* pkCache)
{
    m_spDynamicStreamCache = pkCache;
}

//--------------------------------------------------------------------------------------------------
inline NiCullingProcess* NiTerrainSectorData::GetCullingProcess() const
{
    return m_pkCullingProcess;
}

//--------------------------------------------------------------------------------------------------
inline NiCamera* NiTerrainSectorData::GetLODCamera() const
{
    return m_pkLODCamera;
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainSectorData::GetCameraLODSqr() const
{
    return m_fCameraLODSqr;
}

//--------------------------------------------------------------------------------------------------
inline const NiFrustumPlanes& NiTerrainSectorData::GetFrustumPlanes() const
{
    return m_kFrustumPlanes;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetCullingProcess(
    NiCullingProcess* pkCuller)
{
    m_pkCullingProcess = pkCuller;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetLODCamera(NiCamera* pkCamera)
{
    m_pkLODCamera = pkCamera;
    if (pkCamera)
    {
        m_fCameraLODSqr =NiSqr(pkCamera->GetLODAdjust());
        m_kFrustumPlanes.Set(*pkCamera);
    }
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainSectorData::GetDeformable() const
{
    return m_bIsDeformable;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetDeformable(bool bDeformable)
{
    m_bIsDeformable = bDeformable;
}

//--------------------------------------------------------------------------------------------------
inline NiInt16 NiTerrainSectorData::GetSectorIndexX()
{
    return m_sSectorIndexX;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetSectorIndexX(NiInt16 uiXIndex)
{
    m_sSectorIndexX = uiXIndex;
}

//--------------------------------------------------------------------------------------------------
inline NiInt16 NiTerrainSectorData::GetSectorIndexY()
{
    return m_sSectorIndexY;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetSectorIndexY(NiInt16 uiYIndex)
{
    m_sSectorIndexY = uiYIndex;
}

//--------------------------------------------------------------------------------------------------
inline const NiTerrainConfiguration& NiTerrainSectorData::GetConfiguration()
    const
{
    return m_kTerrainConfiguration;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorData::SetConfiguration(
    NiTerrainConfiguration kConfiguration)
{
    if (kConfiguration.ValidateConfiguration())
        m_kTerrainConfiguration = kConfiguration;
}
//---------------------------------------------------------------------------
inline bool NiTerrainSectorData::IsLODLoaded(NiInt32 iLevel)
{
    return m_iHighestLoadedLOD >= iLevel;
}

//--------------------------------------------------------------------------------------------------
