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
template<class T> inline
NiTerrainSectorFile* NiTerrainSectorFileVersion5::Create(const char* pcTerrainArchive, 
    NiInt32 iSectorX, NiInt32 iSectorY, efd::File::OpenMode kAccessMode)
{
    NiString kFileName = GenerateSectorFileName(pcTerrainArchive, iSectorX, iSectorY);
    return EE_NEW T(kFileName, kAccessMode);
}
//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSectorFileVersion5::GetBlockID() const
{
    if (IsWritable())
    {
        return m_iCurrentBlockID + 1;
    }
    else
    {
        return m_iCurrentBlockID;
    }
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainSectorFileVersion5::GetBlockLevel() const
{
    return m_iCurrentBlockLevel;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorFileVersion5::SetHeightData(float* pfData,
    NiUInt32 uiDataLength)
{
    SetStreamData(
        STREAM_HEIGHT, sizeof(float), pfData, uiDataLength);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorFileVersion5::SetNormalData(float* pfData,
    NiUInt32 uiDataLength)
{
    SetStreamData(
        STREAM_NORMAL, sizeof(float), pfData, uiDataLength);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorFileVersion5::SetTangentData(float* pfData, NiUInt32
    uiDataLength)
{
    SetStreamData(
        STREAM_TANGENT, sizeof(float), pfData, uiDataLength);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorFileVersion5::SetMorphHeightData(float* pfData,
    NiUInt32 uiDataLength)
{
    SetStreamData(
        STREAM_MORPH_HEIGHT, sizeof(float), pfData, uiDataLength);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorFileVersion5::SetMorphNormalData(float* pfData,
    NiUInt32 uiDataLength)
{
    SetStreamData(
        STREAM_MORPH_NORMAL, sizeof(float), pfData, uiDataLength);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorFileVersion5::SetMorphTangentData(float* pfData,
    NiUInt32 uiDataLength)
{
    SetStreamData(
        STREAM_MORPH_TANGENT, sizeof(float), pfData, uiDataLength);
}

//---------------------------------------------------------------------------
inline void NiTerrainSectorFileVersion5::SetSurfaceIndexData(NiUInt32* puiData, 
    NiUInt32 uiDataLength)
{
    SetStreamData(
        STREAM_SURFACE_INDEX, sizeof(NiUInt32), puiData, uiDataLength);
}

//---------------------------------------------------------------------------
inline void NiTerrainSectorFileVersion5::SetBlendMaskData(NiUInt8* pucData, 
    NiUInt32 uiDataLength)
{
    SetStreamData(
        STREAM_BLEND_MASK, sizeof(NiUInt8), pucData, uiDataLength);
}

//---------------------------------------------------------------------------
inline void NiTerrainSectorFileVersion5::SetLowDetailDiffuseData(NiUInt8* pucData, 
    NiUInt32 uiDataLength)
{
    SetStreamData(
        STREAM_LOW_DETAIL_DIFFUSE_TEXTURE, sizeof(NiUInt8), pucData, 
        uiDataLength);
}

//---------------------------------------------------------------------------
inline void NiTerrainSectorFileVersion5::SetLowDetailNormalData(NiUInt8* pucData, 
    NiUInt32 uiDataLength)
{
    SetStreamData(
        STREAM_LOW_DETAIL_NORMAL_TEXTURE, sizeof(NiUInt8), pucData, 
        uiDataLength);
}

//---------------------------------------------------------------------------
inline float* NiTerrainSectorFileVersion5::GetHeightData(NiUInt32& uiDataLength)
{
    return (float*)GetStreamData(STREAM_HEIGHT, uiDataLength);
}

//--------------------------------------------------------------------------------------------------
inline float* NiTerrainSectorFileVersion5::GetNormalData(NiUInt32& uiDataLength)
{
    return (float*)GetStreamData(STREAM_NORMAL, uiDataLength);
}

//--------------------------------------------------------------------------------------------------
inline float* NiTerrainSectorFileVersion5::GetTangentData(NiUInt32& uiDataLength)
{
    return (float*)GetStreamData(STREAM_TANGENT, uiDataLength);
}

//--------------------------------------------------------------------------------------------------
inline float* NiTerrainSectorFileVersion5::GetMorphHeightData(NiUInt32& uiDataLength)
{
    return (float*)GetStreamData(STREAM_MORPH_HEIGHT, uiDataLength);
}

//--------------------------------------------------------------------------------------------------
inline float* NiTerrainSectorFileVersion5::GetMorphNormalData(NiUInt32& uiDataLength)
{
    return (float*)GetStreamData(STREAM_MORPH_NORMAL, uiDataLength);
}

//--------------------------------------------------------------------------------------------------
inline float* NiTerrainSectorFileVersion5::GetMorphTangentData(NiUInt32& uiDataLength)
{
    return (float*)GetStreamData(STREAM_MORPH_TANGENT, uiDataLength);
}

//---------------------------------------------------------------------------
inline NiUInt32* NiTerrainSectorFileVersion5::GetSurfaceIndexData(
    NiUInt32& uiDataLength)
{
    return (NiUInt32*)GetStreamData(STREAM_SURFACE_INDEX, uiDataLength);
}

//---------------------------------------------------------------------------
inline NiUInt8* NiTerrainSectorFileVersion5::GetBlendMaskData(NiUInt32& uiDataLength)
{
    return (NiUInt8*)GetStreamData(STREAM_BLEND_MASK, uiDataLength);
}

//---------------------------------------------------------------------------
inline NiUInt8* NiTerrainSectorFileVersion5::GetLowDetailDiffuseData(
    NiUInt32& uiDataLength)
{
    return (NiUInt8*)GetStreamData(STREAM_LOW_DETAIL_DIFFUSE_TEXTURE, 
        uiDataLength);
}

//---------------------------------------------------------------------------
inline NiUInt8* NiTerrainSectorFileVersion5::GetLowDetailNormalData(
    NiUInt32& uiDataLength)
{
    return (NiUInt8*)GetStreamData(STREAM_LOW_DETAIL_NORMAL_TEXTURE, 
        uiDataLength);
}

//---------------------------------------------------------------------------
