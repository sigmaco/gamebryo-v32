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
inline NiString NiTerrainSectorFileDeveloper::GenerateSectorPathPrefix()
{
    NiString kSectorPrefix;
    kSectorPrefix.Format("%s%sSector_%d_%d.", (const char*)m_kTerrainArchive, ms_pcFolder,
        m_iSectorX, m_iSectorY);
    return kSectorPrefix;
}

//--------------------------------------------------------------------------------------------------
inline NiString NiTerrainSectorFileDeveloper::GenerateHeightsFilename()
{
    return GenerateSectorPathPrefix() + NiString(ms_pcHeightsFile);
}

//--------------------------------------------------------------------------------------------------
inline NiString NiTerrainSectorFileDeveloper::GenerateNormalsFilename()
{
    return GenerateSectorPathPrefix() + NiString(ms_pcNormalsFile);
}

//--------------------------------------------------------------------------------------------------
inline NiString NiTerrainSectorFileDeveloper::GenerateTangentsFilename()
{
    return GenerateSectorPathPrefix() + NiString(ms_pcTangentsFile);
}

//--------------------------------------------------------------------------------------------------
inline NiString NiTerrainSectorFileDeveloper::GenerateLowDetailNormalMapFilename()
{
    return GenerateSectorPathPrefix() + NiString(ms_pcLowDetailNormalMapFile);
}

//--------------------------------------------------------------------------------------------------
inline NiString NiTerrainSectorFileDeveloper::GenerateLowDetailDiffuseMapFilename()
{
    return GenerateSectorPathPrefix() + NiString(ms_pcLowDetailDiffuseMapFile);
}

//--------------------------------------------------------------------------------------------------
inline NiString NiTerrainSectorFileDeveloper::GenerateSectorDataFilename()
{
    return GenerateSectorPathPrefix() + NiString(ms_pcSectorDataFile);
}

//--------------------------------------------------------------------------------------------------
inline NiString NiTerrainSectorFileDeveloper::GenerateBoundsFilename()
{
    return GenerateSectorPathPrefix() + NiString(ms_pcBoundsFile);
}

//--------------------------------------------------------------------------------------------------
inline NiString NiTerrainSectorFileDeveloper::GenerateSurfaceIndexFilename()
{
    return GenerateSectorPathPrefix() + NiString(ms_pcSurfaceIndexFile);
}

//--------------------------------------------------------------------------------------------------
inline NiString NiTerrainSectorFileDeveloper::GenerateBlendMaskFilename()
{
    return GenerateSectorPathPrefix() + NiString(ms_pcBlendMaskFile);
}

//--------------------------------------------------------------------------------------------------