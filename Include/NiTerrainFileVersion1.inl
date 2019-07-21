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
inline NiUInt32 NiTerrainFileVersion1::GetNumSurfaces() const
{
    return m_kSurfaceNameArray.GetSize();
}

//--------------------------------------------------------------------------------------------------
inline NiFixedString NiTerrainFileVersion1::GetSurfacePackage(NiUInt32 uiSurfaceIndex) 
    const
{
    return m_kSurfacePackageArray.GetAt(uiSurfaceIndex);
}

//--------------------------------------------------------------------------------------------------
inline NiFixedString NiTerrainFileVersion1::GetSurfaceName(NiUInt32 uiSurfaceIndex) 
    const
{
    return m_kSurfaceNameArray.GetAt(uiSurfaceIndex);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainFileVersion1::SetSurfacePackage(NiUInt32 uiSurfaceIndex, 
    NiFixedString kPackage)
{
    m_kSurfacePackageArray.SetAtGrow(uiSurfaceIndex, kPackage);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainFileVersion1::SetSurfaceName(NiUInt32 uiSurfaceIndex, 
    NiFixedString kName)
{
    m_kSurfaceNameArray.SetAtGrow(uiSurfaceIndex, kName);
}

//--------------------------------------------------------------------------------------------------