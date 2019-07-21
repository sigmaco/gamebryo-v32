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
inline void NiRendererSettings::ReadUInt(
    const char* pcFileName,
    const char* pcName,
    unsigned int& uiVal)
{
    uiVal = GetPrivateProfileInt(ms_pcSectionName, pcName, uiVal, pcFileName);
}

//--------------------------------------------------------------------------------------------------
inline void NiRendererSettings::ReadBool(
    const char* pcFileName,
    const char* pcName,
    bool& bVal)
{
    int iVal;
    iVal = GetPrivateProfileInt(ms_pcSectionName, pcName, bVal, pcFileName);
    bVal = iVal ? true : false;
}

//--------------------------------------------------------------------------------------------------
inline void NiRendererSettings::WriteUInt(
    const char* pcFileName,
    const char* pcName,
    unsigned int uiVal)
{
    char pcVal[64];
    NiSprintf(pcVal, 64, "%i", uiVal);
    WritePrivateProfileString(ms_pcSectionName, pcName, pcVal, pcFileName);
}

//--------------------------------------------------------------------------------------------------
inline void NiRendererSettings::WriteBool(
    const char* pcFileName,
    const char* pcName,
    bool bVal)
{
    char pcVal[64];
    NiSprintf(pcVal, 64, "%i", bVal);
    WritePrivateProfileString(ms_pcSectionName, pcName, pcVal, pcFileName);
}

//--------------------------------------------------------------------------------------------------
