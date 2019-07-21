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

//--------------------------------------------------------------------------------------------------
inline const NiTerrainSector* NiTerrainCell::GetContainingSector() const
{
    return m_pkContainingSector;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSector* NiTerrainCell::GetContainingSector()
{
    return m_pkContainingSector;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainCell::GetLevel() const
{
    return m_uiLevel;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::SetLevel(NiUInt32 uiLevel)
{
    m_uiLevel = uiLevel;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainCell::GetNumSubDivisions() const
{
    return m_pkSectorData->GetNumLOD() - GetLevel();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainCell::GetCellSize() const
{
    return m_pkSectorData->GetCellSize();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainCell::GetWidthInVerts() const
{
    return m_pkSectorData->GetCellWidthInVerts();
}

//--------------------------------------------------------------------------------------------------
inline const NiBound& NiTerrainCell::GetLocalBound() const
{
    return m_kBound;
}

//--------------------------------------------------------------------------------------------------
inline const NiBoxBV& NiTerrainCell::GetLocalBoxBound() const
{
    return m_kBoxBound;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::GetBottomLeftIndex(NiIndex& kIndex) const
{   
    kIndex = m_kDataBottomLeftIndex;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::SetBottomLeftIndex(const NiIndex& kIndex)
{
    m_kDataBottomLeftIndex = kIndex;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainCell::GetCellID() const
{
    return m_uiCellID;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::SetCellID(NiUInt32 uiCellID)
{
    m_uiCellID = uiCellID;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainCell::GetRegionID() const
{
    return m_uiRegionID;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::SetRegionID(NiUInt32 uiRegionID)
{
    m_uiRegionID = uiRegionID;

    if (m_uiRegionID == 0 && !m_pkParentCell && !m_pkDrawnPool)
    {
        // We are the tree root, so we are responsible for the drawn flag pool
        m_pkDrawnPool = NiNew NiUCharPool();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::SetBoundVolumeBox(const NiBoxBV& kBox)
{
    m_kBoxBound = kBox;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt8 NiTerrainCell::GetStitchingIndex() const
{
    return m_ucStitchingIndex;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::SetWorldScale(float fScale)
{
    NiNode::SetWorldScale(fScale);
    UpdateMorphConstants();
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainCell* NiTerrainCell::GetParent()
{
    return m_pkParentCell;
}

//--------------------------------------------------------------------------------------------------
inline const NiTerrainCell* NiTerrainCell::GetParent() const
{
    return m_pkParentCell;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::SetParent(NiTerrainCell* pkCell)
{
    m_pkParentCell = pkCell;
   
    if (m_uiRegionID != 0)
    {
        // Inherit the drawn flag pool from our parent
        m_pkDrawnPool = m_pkParentCell->m_pkDrawnPool;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::GetVertexAt(
    const NiTerrainPositionRandomAccessIterator& kIterator,
    NiPoint3& kVertex, const NiIndex& kLocal) const
{
    EE_ASSERT(kLocal.x <= GetWidthInVerts());
    EE_ASSERT(kLocal.y <= GetWidthInVerts());

    kIterator.GetHighDetail(kLocal.x + kLocal.y * GetWidthInVerts(),
        kVertex);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::GetVertexAtSector(
    const NiTerrainPositionRandomAccessIterator& kIterator,
    NiPoint3& kVertex, const NiIndex& kSector) const
{
    NiIndex kLocal;
#ifdef NIDEBUG
    SectorIndexToLocal(kSector, kLocal);
#else
    SectorIndexToLocalFast(kSector, kLocal);
#endif

    GetVertexAt(kIterator, kVertex, kLocal);
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainCell::GetHeightAt(
    const NiTerrainPositionRandomAccessIterator& kIterator,
    const NiIndex& kLocal) const
{
    EE_ASSERT(kLocal.x < GetWidthInVerts());
    EE_ASSERT(kLocal.y < GetWidthInVerts());
    
    return kIterator.GetComponent(
        kLocal.x + kLocal.y * GetWidthInVerts(), 
        NiTerrainPositionRandomAccessIterator::Z);
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainCell::GetHeightAtSector(
    const NiTerrainPositionRandomAccessIterator& kIterator,
    const NiIndex& kSector) const
{
    NiIndex kLocal;

#ifdef NIDEBUG
    SectorIndexToLocal(kSector, kLocal);
#else
    SectorIndexToLocalFast(kSector, kLocal);
#endif

    return GetHeightAt(kIterator, kLocal);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::GetNormalAt(
    const NiTerrainNormalRandomAccessIterator& kIterator,
    NiPoint3& kNormal, const NiIndex& kLocal) const
{
    EE_ASSERT(kLocal.x <= GetWidthInVerts());
    EE_ASSERT(kLocal.y <= GetWidthInVerts());

    kIterator.GetHighDetail(kLocal.x + kLocal.y * GetWidthInVerts(),
        kNormal);
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainCell* NiTerrainCell::GetAdjacent(NiUInt32 uiBorder)
{
    return DoGetAdjacent(uiBorder);
}

//--------------------------------------------------------------------------------------------------
inline const NiTerrainCell* NiTerrainCell::GetAdjacent(
    NiUInt32 uiBorder) const
{
    return DoGetAdjacent(uiBorder);
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainCell* NiTerrainCell::GetAdjacentFast(NiUInt32 uiBorder)
{
    return DoGetAdjacentFast(uiBorder);
}

//--------------------------------------------------------------------------------------------------
inline const NiTerrainCell* NiTerrainCell::GetAdjacentFast(
    NiUInt32 uiBorder) const
{
    return DoGetAdjacentFast(uiBorder);
}

//--------------------------------------------------------------------------------------------------
inline const NiIndex NiTerrainCell::SectorIndexFromLocal(
    const NiIndex& kLocal) const
{
    return NiIndex(
        m_kDataBottomLeftIndex.x + (kLocal.x << GetNumSubDivisions()),
        m_kDataBottomLeftIndex.y + (kLocal.y << GetNumSubDivisions()));
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::SectorIndexToLocalFast(const NiIndex& kSector, 
    NiIndex& kLocal) const
{
    kLocal = kSector - m_kDataBottomLeftIndex;
    kLocal.x >>= GetNumSubDivisions();
    kLocal.y >>= GetNumSubDivisions();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::UpdateMorphConstants()
{
    const float fSquareRoot2 = NiSqrt(2.0f);
    NiUInt32 uiNumDivisions = GetNumSubDivisions();

    m_fMaxDistanceSqr = NiMax(0.0f, (float)(m_pkSectorData->GetCellSize()) * 
        (float)(1 << uiNumDivisions) * m_pkSectorData->GetLODScale() * fSquareRoot2 + 
        m_pkSectorData->GetLODShift());
    m_fMaxDistanceSqr = NiSqr(m_fMaxDistanceSqr);

    // Reset the morphing data in the shader. This is in theory not required
    // any more, since we are using a transformed camera in the shader now.
    float fCellWorldWidth = float(m_pkSectorData->GetCellSize() << uiNumDivisions);
    float fMorphDistance = fSquareRoot2 * (fCellWorldWidth * 0.5f);
    float fThresholdDistance = NiSqrt(m_fMaxDistanceSqr) - fMorphDistance;

    m_kShaderData.m_fMorphThreshold = fThresholdDistance;
    m_kShaderData.m_fMorphDistance = fMorphDistance;
    m_kShaderData.m_uiMorphMode = m_pkSectorData->GetLODMode();
    m_kShaderData.UpdateShaderData(m_spMesh);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::ResetCullingResults()
{
    m_pkDrawnPool->Reset();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::MarkCellLoaded()
{
    // The cell was just loaded so we need to mark the properties and 
    // effect update flag
    SetUpdateFlag(true, UPDATE_CELL_JUST_LOADED);
    if (!RequiresUpdate())
        RequestUpdate();
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainCell::HasDynamicVertexStreams()
{
    return m_pkCustomPositionStream != 0 && m_pkCustomNormalTangentStream != 0;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainCell::HasDynamicUVStream()
{
    return m_pkCustomUVStream != 0;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainCell::HasDynamicIndexStream()
{
    return m_pkCustomIndexStream != 0;
}

//--------------------------------------------------------------------------------------------------
inline NiMesh& NiTerrainCell::GetMesh() const
{
    EE_ASSERT(m_spMesh);
    return *m_spMesh;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainCellShaderData& NiTerrainCell::GetShaderData()
{
    return m_kShaderData;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::AddToVisible()
{
    if (!m_pkSectorData->IsLODLoaded(NiInt32(m_uiLevel)))
    {
        return;
    }

    m_pkSectorData->AddToVisible(this);
    SetCullingResult(SELF_VISIBLE);

    // Update adjusted eye position
    m_kShaderData.m_kAdjustedEyePos = m_pkSectorData->GetLODCamera()->GetWorldLocation();
    m_kShaderData.UpdateShaderData(m_spMesh);
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainCell::IsVisible() const
{
    return (GetCullingResult() & VISIBLE_TREE_FLAG) == 0;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::SetCullingResult(NiUInt8 ucResult)
{
    m_pkDrawnPool->SetValue(m_uiDrawnPoolIndex, ucResult);
}

//--------------------------------------------------------------------------------------------------
inline NiUInt8 NiTerrainCell::GetCullingResult() const
{
    return m_pkDrawnPool->GetValue(m_uiDrawnPoolIndex);
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainCell::AddSurface(NiUInt32 uiSurfaceIndex, 
    NiUInt32 uiNewPriority)
{
    return DoAddSurface(uiSurfaceIndex, uiNewPriority);
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainCell::RemoveSurface(NiUInt32 uiSurfaceIndex)
{
    return DoRemoveSurface(uiSurfaceIndex);
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainCell::GetOppositeBorder(NiUInt32 uiBorder)
{
    NiUInt32 uiResult = BORDER_NONE;
    if (uiBorder & BORDER_LEFT)
        uiResult |= BORDER_RIGHT;
    else if (uiBorder & BORDER_RIGHT)
        uiResult |= BORDER_LEFT;
    if (uiBorder & BORDER_TOP)
        uiResult |= BORDER_BOTTOM;
    else if (uiBorder & BORDER_BOTTOM)
        uiResult |= BORDER_TOP;

    return uiResult;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainCell::SetUpdateFlag(bool bFlagValue, NiUInt32 uiFlagMask)
{
    if (bFlagValue)
    {
        m_uiUpdateFlags |= uiFlagMask;
    }
    else
    {
        m_uiUpdateFlags &= ~uiFlagMask;
    }
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainCell::GetUpdateFlag(NiUInt32 uiFlagMask) const
{
    return (m_uiUpdateFlags & uiFlagMask) != 0;
}

//--------------------------------------------------------------------------------------------------
