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
inline NiTerrain* NiTerrainSector::GetTerrain()
{
    return m_pkTerrain;
}

//--------------------------------------------------------------------------------------------------
inline const NiTerrain* NiTerrainSector::GetTerrain() const
{
    return m_pkTerrain;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSector::SectorID NiTerrainSector::GetSectorID()
{
    NiTerrainSector::SectorID uiResult;
    efd::SInt16 usSectorX;
    efd::SInt16 usSectorY;
    GetSectorIndex(usSectorX, usSectorY);
    GenerateSectorID(usSectorX, usSectorY, uiResult);
    return uiResult;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainSector::HasShapeChangedLastUpdate()
{
    return m_bHasShapeChangedLastUpdate;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainSector::HasPagingData() const
{
    return m_pkSectorPagingData != NULL;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::SetShapeChangedLastUpdate(bool bChanged)
{
    m_bHasShapeChangedLastUpdate = bChanged;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::GetVertexAt(
    const NiTerrainPositionRandomAccessIterator& kIterator,
    NiPoint3& kVertex, 
    const NiIndex& kIndex, NiUInt32 uiLevel) const
{
    // Assign the level if not specified:
    if (uiLevel == NiTerrainUtils::ms_uiMAX_LOD)
    {
        uiLevel = m_pkSectorData->GetNumLOD();
    }

    // Only check first existant level in debug
#ifdef NIDEBUG
    // What level does this point first exist at?
    NiUInt32 uiShallowestLevel = 0;
    NiUInt32 uiDivisor = 1 << m_pkSectorData->GetNumLOD();

    for (; uiDivisor > 0; uiDivisor /= 2)
    {
        if (kIndex.x % uiDivisor && kIndex.y % uiDivisor)
            uiShallowestLevel++;
    }
    EE_ASSERT(uiLevel >= uiShallowestLevel);
#endif

    // Get the block that this index belongs to. A vertex on an edge of a block
    // only 'belongs' to a single block, but is regarded as extended data to
    // any neighboring blocks
    NiTerrainCell* pkCell = GetCellContaining(kIndex, uiLevel);
    pkCell->GetVertexAtSector(kIterator, kVertex, kIndex);    
}

//--------------------------------------------------------------------------------------------------
template <typename T>
inline void NiTerrainSector::AddTri(NiUInt32 x0, NiUInt32 y0,
    NiUInt32 x1, NiUInt32 y1, NiUInt32 x2, NiUInt32 y2,
    NiTStridedRandomAccessIterator<T>& kIterator)
{
    kIterator[0] = (T)(x0 + y0 * m_pkSectorData->GetCellWidthInVerts());
    kIterator[1] = (T)(x1 + y1 * m_pkSectorData->GetCellWidthInVerts());
    kIterator[2] = (T)(x2 + y2 * m_pkSectorData->GetCellWidthInVerts());
    kIterator += 3;
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainSector::GetHeightAt(
    const NiTerrainPositionRandomAccessIterator& kIterator,
    const NiIndex& kIndex, NiUInt32 uiLevel) const
{
    NiPoint3 kPosition;
    GetVertexAt(kIterator, kPosition, kIndex, uiLevel);
    return kPosition.z;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::GetSectorIndex(
    NiInt16& sXIndex, NiInt16& sYIndex) const
{
    sXIndex = m_pkSectorData->GetSectorIndexX();
    sYIndex = m_pkSectorData->GetSectorIndexY();
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainCell* NiTerrainSector::GetCellContaining(
    const NiIndex& kIndex, NiUInt32 uiDetailLevel) const
{
    // Side length in level 0 verts
    NiUInt32 uiSideLength= m_pkSectorData->GetCellSize() <<
        (m_pkSectorData->GetNumLOD() - uiDetailLevel);
    NiUInt32 uiWidthInBlocks = 1 << uiDetailLevel;

    // Find out which block the index is in, at given detail level
    NiIndex kBlockIndex = kIndex / uiSideLength;

    // Deal with extended data on the right hand side of the sector
    if (kIndex.x == m_pkSectorData->GetSectorSize())
        --kBlockIndex.x;
    if (kIndex.y == m_pkSectorData->GetSectorSize())
        --kBlockIndex.y;

    // Width of this detail level, in blocks
    return m_kCellArray[GetCellOffset(uiDetailLevel) + 
        kBlockIndex.x + (kBlockIndex.y * uiWidthInBlocks)];
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainSector::GetSurfaceOpacity(
    const NiSurface* pkSurface, const NiPoint3& kWorldLocation,
    NiUInt8& ucValue, NiUInt32 uiDetailLevel,
    bool bSearchLowerDetail) const
{
    return NiTerrainUtils::GetSurfaceOpacity(
        pkSurface, kWorldLocation, ucValue, uiDetailLevel, bSearchLowerDetail,
        m_pkQuadCell);
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainCell* NiTerrainSector::GetCell(NiUInt32 uiCellID) const
{
    EE_ASSERT(uiCellID < m_kCellArray.GetSize());
    return m_kCellArray[uiCellID];
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainCell* NiTerrainSector::GetCellByRegion(NiUInt32 uiCellID) 
    const
{
    EE_ASSERT(uiCellID < m_kCellRegionArray.GetSize());
    return m_kCellRegionArray[uiCellID];
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSector::GetCellOffset(NiUInt32 uiDetailLevel) const
{
    EE_ASSERT(uiDetailLevel <= m_pkSectorData->GetNumLOD() + 1);
    return m_puiCellOffsets[uiDetailLevel];
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSector::GetNumCells() const
{
    return GetCellOffset(m_pkSectorData->GetNumLOD() + 1);
}

//--------------------------------------------------------------------------------------------------
inline const NiTerrainSectorData* NiTerrainSector::GetSectorData() const
{
    return m_pkSectorData;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::SetMinMaxVisibleLOD(NiUInt32 uiMinLOD, NiUInt32 uiMaxLOD)
{
    EE_ASSERT(uiMaxLOD >= uiMinLOD);
    m_pkSectorData->SetLowestVisibleLOD(uiMinLOD);
    m_pkSectorData->SetHighestVisibleLOD(uiMaxLOD);
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSectorData* NiTerrainSector::GetSectorData() 
{
    return m_pkSectorData;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSector::GetLowDetailTextureSize() const
{
    return m_uiLowDetailTextureSize;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::SetLowDetailTextureSize(NiUInt32 uiSize)
{
    m_uiLowDetailTextureSize = uiSize;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainSector::IsReadyToPaint()
{
    return m_pkPaintingData != NULL;
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainSector::GetLODScale() const
{
    return m_pkSectorData->GetLODScale();
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainSector::GetLODShift() const
{
    return m_pkSectorData->GetLODShift();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSector::GetLODMode() const
{
    return m_pkSectorData->GetLODMode();
}

//--------------------------------------------------------------------------------------------------
inline const NiTerrainConfiguration& NiTerrainSector::GetConfiguration() const
{
    return m_pkSectorData->GetConfiguration();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::CreatePagingData()
{
    if (!m_pkSectorPagingData)
        m_pkSectorPagingData = NiNew NiTerrainSectorPagingData();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::SyncWithPaging()
{
    if (m_pkSectorPagingData)
        m_pkSectorPagingData->SyncWithPaging();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::PauseUpdateThread()
{
    if (m_pkSectorPagingData)
        m_pkSectorPagingData->PauseUpdateThread();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::ResumeUpdateThread()
{
    if (m_pkSectorPagingData)
        m_pkSectorPagingData->ResumeUpdateThread();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::LockSectorPaging()
{
    if (m_pkSectorPagingData)
        m_pkSectorPagingData->LockSectorPaging();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::UnlockSectorPaging()
{
    if (m_pkSectorPagingData)
        m_pkSectorPagingData->UnlockSectorPaging();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::LockSectorUpdating()
{
    if (m_pkSectorPagingData)
        m_pkSectorPagingData->LockSectorUpdating();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::UnlockSectorUpdating()
{
    if (m_pkSectorPagingData)
        m_pkSectorPagingData->UnlockSectorUpdating();
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSector::HeightMap* NiTerrainSector::GetHeightMap()
{
    return m_spHeightMap;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::SetHeightMap(NiTerrainSector::HeightMap* pkHeightMap)
{
    m_spHeightMap = pkHeightMap;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSector::HeightMap::HeightMap(NiUInt32 uiWidth, NiUInt32 uiHeight, 
    NiUInt16* pusBuffer)
{
    EE_ASSERT(uiWidth == uiHeight);
    EE_UNUSED_ARG(uiHeight);
    m_uiDimensions = uiWidth;
    m_pusBuffer = pusBuffer;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSector::HeightMap::~HeightMap()
{
    if (m_pusBuffer)
        EE_FREE(m_pusBuffer);
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16* NiTerrainSector::HeightMap::Lock(LockType::VALUE eLockType)
{
    if (eLockType == LockType::WRITE)
        m_kLock.LockWrite();
    else
        m_kLock.LockRead();

    return m_pusBuffer;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSector::HeightMap::Unlock(LockType::VALUE eLockType)
{
    if (eLockType == LockType::WRITE)
        m_kLock.UnlockWrite();
    else
        m_kLock.UnlockRead();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSector::HeightMap::GetWidth()
{
    return m_uiDimensions;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSector::HeightMap::GetHeight()
{
    return m_uiDimensions;
}

//--------------------------------------------------------------------------------------------------
