// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed excekPt in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

//--------------------------------------------------------------------------------------------------
inline NiTerrainSurfacePackageFile::FileVersion NiTerrainSurfacePackageFile::GetFileVersion() const
{
    return m_kFileVersion;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainSurfacePackageFile::IsReady() const
{
    return m_bOpen;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainSurfacePackageFile::IsWritable() const
{
    return m_bWriteAccess;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSurfacePackageFile::FileVersion NiTerrainSurfacePackageFile::GetCurrentVersion()
{
    return ms_kFileVersion;
}

//--------------------------------------------------------------------------------------------------