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
inline const NiTerrainDataSnapshot::CellSnapshot::SurfaceMaskMap& 
NiTerrainDataSnapshot::CellSnapshot::GetSurfaceMasks() const
{
    return m_kSurfaceMasks;
}

//--------------------------------------------------------------------------------------------------
inline const NiTerrainDataSnapshot::CellMap& NiTerrainDataSnapshot::GetCellSnapshots() const
{
    return m_kCells;
}

//--------------------------------------------------------------------------------------------------
inline const NiTerrainDataSnapshot::CellStack& NiTerrainDataSnapshot::GetCellStack() const
{
    return m_kCellStack;
}

//--------------------------------------------------------------------------------------------------