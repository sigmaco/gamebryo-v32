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

//---------------------------------------------------------------------------
inline const NiFixedString& NiNoiseTexture::GetMapNameFromType(
    NiStandardMaterial::NoiseMapType eType)
{
    return ms_akMapFromTypeName[eType];
}
//---------------------------------------------------------------------------
inline bool NiNoiseTexture::GetTypeIDFromName(
    const NiFixedString& kName, unsigned int& uiID)
{
    if (kName == ms_akMapFromTypeName[
        NiStandardMaterial::NOISE_GREYSCALE])
    {
        uiID = NiStandardMaterial::NOISE_GREYSCALE;
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
inline NiNoiseTexture::NoiseType NiNoiseTexture::GetNoiseType() const
{
    return m_eNoiseType;
}
//---------------------------------------------------------------------------
inline void NiNoiseTexture::SetNoiseType(NoiseType eNoiseType)
{
    m_eNoiseType = eNoiseType;
}
//---------------------------------------------------------------------------