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
inline void NiTerrainSectorSelectorDefault::SetFirstSectorIndex(NiIndex kFirstSector)
{
    m_kFirstSectorIndex = kFirstSector;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorSelectorDefault::SetFirstSectorIndex(NiUInt32 uiMinSectorX, 
    NiUInt32 uiMinSectorY)
{
    m_kFirstSectorIndex.x = uiMinSectorX;
    m_kFirstSectorIndex.y = uiMinSectorY;
}

//--------------------------------------------------------------------------------------------------
inline NiIndex NiTerrainSectorSelectorDefault::GetFirstSectorIndex()
{
    return m_kFirstSectorIndex;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorSelectorDefault::SetTerrainExtent(NiIndex kTerrainExtent)
{
    m_kTerrainExtent = kTerrainExtent;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorSelectorDefault::SetTerrainExtent(
    NiUInt32 uiNumSectorX, 
    NiUInt32 uiNumSectorY)
{
    m_kTerrainExtent.x = uiNumSectorX;
    m_kTerrainExtent.y = uiNumSectorY;
}

//--------------------------------------------------------------------------------------------------
inline NiIndex NiTerrainSectorSelectorDefault::GetTerrainExtent()
{
    return m_kTerrainExtent;
}

//--------------------------------------------------------------------------------------------------
