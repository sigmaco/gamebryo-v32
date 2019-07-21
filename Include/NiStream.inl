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
// Inline load/save routines for native data.
//--------------------------------------------------------------------------------------------------

#include <NiBinaryLoadSave.h>

template <class T>
void NiStreamLoadBinary(NiStream& kStream, T& value)
{
    efd::BinaryStreamLoad(kStream.Istr(), &value, 1);
}

//--------------------------------------------------------------------------------------------------
template <class T>
void NiStreamLoadBinary(NiStream& kStream, T* pValue, unsigned int uiNumEls)
{
    efd::BinaryStreamLoad(kStream.Istr(), pValue, uiNumEls);
}

//--------------------------------------------------------------------------------------------------
template <class T>
void NiStreamLoadBinary(NiStream& kStream, T* pValue, unsigned int uiNumEls,
    unsigned int* pauiComponentSizes, unsigned int uiNumComponents)
{
    efd::BinaryStreamLoad(kStream.Istr(), pValue, uiNumEls, pauiComponentSizes, uiNumComponents);
}

//--------------------------------------------------------------------------------------------------
template <class T>
void NiStreamLoadEnum(NiStream& kStream, T& value)
{
    efd::BinaryStreamLoadEnum(kStream.Istr(), &value);
}

//--------------------------------------------------------------------------------------------------
template <class T>
void NiStreamSaveBinary(NiStream& kStream, const T& value)
{
    efd::BinaryStreamSave(kStream.Ostr(), &value, 1);
}

//--------------------------------------------------------------------------------------------------
template <class T>
void NiStreamSaveBinary(NiStream& kStream, const T* pValue,
    unsigned int uiNumEls)
{
    efd::BinaryStreamSave(kStream.Ostr(), pValue, uiNumEls);
}

//--------------------------------------------------------------------------------------------------
inline void NiStreamSaveBinary(NiStream& kStream, const void* pValue,
    unsigned int uiNumEls, unsigned int* pauiComponentSizes,
    unsigned int uiNumComponents)
{
    efd::BinaryStreamSave(kStream.Ostr(), pValue, uiNumEls, pauiComponentSizes, uiNumComponents);
}

//--------------------------------------------------------------------------------------------------
template <class T>
void NiStreamSaveEnum(NiStream& kStream, const T& value)
{
    efd::BinaryStreamSaveEnum(kStream.Ostr(), value);
}

//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  NiStream inline functions
//--------------------------------------------------------------------------------------------------
inline NiStream::ConversionMap& NiStream::GetConversionMap()
{
    return m_kConversionMap;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiStream::GetObjectCount() const
{
    return m_kTopObjects.GetSize();
}

//--------------------------------------------------------------------------------------------------
inline NiObject* NiStream::GetObjectAt(unsigned int i) const
{
    return m_kTopObjects.GetAt(i);
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiStream::GetFileVersion() const
{
    return m_uiNifFileVersion;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiStream::GetFileUserDefinedVersion() const
{
    return m_uiNifFileUserDefinedVersion;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiStream::GetLastError() const
{
    return m_uiLastError;
}

//--------------------------------------------------------------------------------------------------
inline const char* NiStream::GetLastErrorMessage() const
{
    return m_acLastErrorMessage;
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::ResetLastErrorInfo()
{
    m_uiLastError = STREAM_OKAY;
    m_acLastErrorMessage[0] = 0;
}

//--------------------------------------------------------------------------------------------------
inline const char* NiStream::GetLastLoadedRTTI() const
{
    return m_acLastErrorMessage;
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::SaveLinkID(const NiObject* pkObject)
{
    unsigned int uiLinkID = GetLinkIDFromObject(pkObject);
    NiStreamSaveBinary(*this, uiLinkID);
}

//--------------------------------------------------------------------------------------------------
inline bool NiStream::BackgroundLoadGetExitStatus() const
{
    return m_bBackgroundLoadExitStatus;
}

//--------------------------------------------------------------------------------------------------
inline const NiProcessorAffinity& NiStream::GetAffinity() const
{
    return m_kAffinity;
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::SetAffinity(const NiProcessorAffinity& kAffinity)
{
    m_kAffinity = kAffinity;
}

//--------------------------------------------------------------------------------------------------
inline NiThread::Priority NiStream::GetPriority() const
{
    return m_ePriority;
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::SetPriority(const NiThread::Priority ePriority)
{
    m_ePriority = ePriority;
}

//--------------------------------------------------------------------------------------------------
inline efd::BinaryStream& NiStream::Istr()
{
    return *m_pkIstr;
}

//--------------------------------------------------------------------------------------------------
inline efd::BinaryStream& NiStream::Ostr()
{
    return *m_pkOstr;
}

//--------------------------------------------------------------------------------------------------
inline NiSearchPath* NiStream::GetSearchPath() const
{
    return m_pkSearchPath;
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::LockCleanupSection()
{
    ms_kCleanupCriticalSection.Lock();
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::UnlockCleanupSection()
{
    ms_kCleanupCriticalSection.Unlock();
}

//--------------------------------------------------------------------------------------------------
// Flag Conversion Functions
//--------------------------------------------------------------------------------------------------
inline unsigned short NiStream::GetLastNiAVObjectFlags() const
{
    return m_usNiAVObjectFlags;
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::SetLastNiAVObjectFlags(unsigned short usFlags)
{
    m_usNiAVObjectFlags = usFlags;
}

//--------------------------------------------------------------------------------------------------
inline unsigned short NiStream::GetLastNiTimeControllerFlags() const
{
    return m_usNiTimeControllerFlags;
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::SetLastNiTimeControllerFlags(unsigned short usFlags)
{
    m_usNiTimeControllerFlags = usFlags;
}

//--------------------------------------------------------------------------------------------------
inline unsigned short NiStream::GetLastNiPropertyFlags() const
{
    return m_usNiPropertyFlags;
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::SetLastNiPropertyFlags(unsigned short usFlags)
{
    m_usNiPropertyFlags = usFlags;
}

//--------------------------------------------------------------------------------------------------
// End flag conversion functions.
//--------------------------------------------------------------------------------------------------
inline unsigned int NiStream::GetVersion(unsigned int uiMajor,
    unsigned int uiMinor, unsigned int uiPatch, unsigned int uiInternal)
{
    EE_ASSERT(uiMajor < 256);
    EE_ASSERT(uiMinor < 256);
    EE_ASSERT(uiPatch < 256);
    EE_ASSERT(uiInternal < 256);

    return (uiMajor << 24) | (uiMinor << 16) | (uiPatch << 8) | uiInternal;
}

//--------------------------------------------------------------------------------------------------
inline bool NiStream::GetPrepareMeshModifiers()
{
    return m_bPrepareModifiers;
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::SetPrepareMeshModifiers(bool bEnable)
{
    m_bPrepareModifiers = bEnable;
}

//--------------------------------------------------------------------------------------------------
inline NiStream::StreamMetaDataObject::StreamMetaDataObject(
    unsigned int uiTag, unsigned int uiBufferSize,
    const NiUInt8* pucBuffer)
{
    m_uiTag = uiTag;
    m_uiBufferSize = uiBufferSize;
    m_pucBuffer = NULL;
    if (uiBufferSize != 0)
    {
        m_pucBuffer = NiAlloc(NiUInt8, uiBufferSize);
        NiMemcpy(m_pucBuffer, uiBufferSize, pucBuffer, uiBufferSize);
    }
}

//--------------------------------------------------------------------------------------------------
inline NiStream::StreamMetaDataObject::StreamMetaDataObject()
{
}

//--------------------------------------------------------------------------------------------------
inline NiStream::StreamMetaDataObject::~StreamMetaDataObject()
{
    NiFree(m_pucBuffer);
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::AddMetaDataBuffer(unsigned int uiTag,
    unsigned int uiBufferSize, const NiUInt8* pucBuffer)
{
    m_kMetaDataObjects.Add(NiNew NiStream::StreamMetaDataObject(uiTag,
        uiBufferSize, pucBuffer));
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiStream::GetMetaDataBufferCount() const
{
    return m_kMetaDataObjects.GetSize();
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiStream::GetMetaDataTag(
    unsigned int uiWhichBuffer) const
{
    return m_kMetaDataObjects.GetAt(uiWhichBuffer)->m_uiTag;
}

//--------------------------------------------------------------------------------------------------
inline const NiUInt8* NiStream::GetMetaDataBuffer(
    unsigned int uiWhichBuffer, unsigned int& uiBufferSize) const
{
    uiBufferSize = m_kMetaDataObjects.GetAt(uiWhichBuffer)->m_uiBufferSize;
    return m_kMetaDataObjects.GetAt(uiWhichBuffer)->m_pucBuffer;
}

//--------------------------------------------------------------------------------------------------
inline bool NiStream::GetLoadMetaData() const
{
    return m_bLoadMetaData;
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::SetLoadMetaData(bool bLoad)
{
    m_bLoadMetaData = bLoad;
}

//--------------------------------------------------------------------------------------------------
inline void NiStream::ClearMetaData()
{
    m_kMetaDataObjects.RemoveAll();
}

//--------------------------------------------------------------------------------------------------
