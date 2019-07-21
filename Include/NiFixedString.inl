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
inline void NiFixedString::LoadCStringAsFixedString(efd::BinaryStream& kStream,
    NiFixedString& kString)
{
    unsigned int uiLength;
    NiStreamLoadBinary(kStream, uiLength);
    if (uiLength >= 1024)
    {
        char* pcString = 0;
        pcString = NiAlloc(char, uiLength + 1);
        EE_ASSERT(pcString);

        kStream.Read(pcString, uiLength);
        pcString[uiLength] = 0;
        kString = pcString;

        NiFree(pcString);
    }
    else if (uiLength > 0)
    {
        char acString[1024];

        kStream.Read(acString, uiLength);
        acString[uiLength] = 0;
        kString = acString;
    }
    else
    {
        kString = 0;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiFixedString::SaveFixedStringAsCString(efd::BinaryStream& kStream,
    const NiFixedString& kString)
{
    kStream.WriteCString((const char*)kString);
}

//--------------------------------------------------------------------------------------------------
inline NiFixedString& NiFixedString::operator=(const char* pkString)
{
    if (m_handle != pkString)
    {
        efd::GlobalStringTable::GlobalStringHandle handle = m_handle;
        m_handle = efd::GlobalStringTable::AddString(pkString);
        efd::GlobalStringTable::DecRefCount(handle);
    }
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline bool operator==(const NiFixedString& s1,
    const NiFixedString& s2)
{
    return s1.m_handle == s2.m_handle;
}

//--------------------------------------------------------------------------------------------------
inline bool operator!=(const NiFixedString& s1,
    const NiFixedString& s2)
{
    return s1.m_handle != s2.m_handle;
}

//--------------------------------------------------------------------------------------------------
inline bool operator==(const NiFixedString& s1, const char* s2)
{
    return s1.Equals(s2);
}

//--------------------------------------------------------------------------------------------------
inline bool operator!=(const NiFixedString& s1, const char* s2)
{
    return !(s1.Equals(s2));
}

//--------------------------------------------------------------------------------------------------
inline bool operator==(const char* s1, const NiFixedString& s2)
{
    return s2.Equals(s1);
}

//--------------------------------------------------------------------------------------------------
inline bool operator!=(const char* s1, const NiFixedString& s2)
{
    return !(s2.Equals(s1));
}

//--------------------------------------------------------------------------------------------------
inline void NiStandardizeFilePath(NiFixedString& kString)
{
    const char* pcString = (const char*) kString;
    char acTempPath[NI_MAX_PATH];
    NiStrcpy(acTempPath, NI_MAX_PATH, pcString);
    efd::PathUtils::Standardize(acTempPath);
    kString = acTempPath;
}

//--------------------------------------------------------------------------------------------------
