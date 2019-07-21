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
inline NiTerrainResourceManager::NiTerrainResourceManager(NiTerrain* pkOwner):
    m_pkTerrain(pkOwner),
    m_uiActiveObjects(0)
{
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainResourceManager::GetNumActiveObjects()
{
    m_kMutex.Lock();
    NiUInt32 uiActiveObjects = m_uiActiveObjects;
    m_kMutex.Unlock();

    return uiActiveObjects;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrain* NiTerrainResourceManager::GetTerrain()
{
    EE_ASSERT(m_pkTerrain);
    return m_pkTerrain;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainResourceManager::SetListener(Listener* pkListener)
{
    m_spListener = pkListener;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainResourceManager::RegisterResource(NiRefObject* pkObject)
{
    if (pkObject)
    {
        m_kMutex.Lock();

        // Notify the listener
        NotifyRegister(pkObject);

        // Adjust active object count
        m_uiActiveObjects++;

        // Make sure this object hangs around until release
        pkObject->IncRefCount();

        m_kMutex.Unlock();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainResourceManager::DeregisterResource(NiRefObject* pkObject)
{
    m_kMutex.Lock();

    // Notify the listener
    NotifyDeregister(pkObject);

    // Make sure that this object is still with us!
    EE_ASSERT(pkObject->GetRefCount() > 0);

    // Decrease the reference count
    pkObject->DecRefCount();

    // Check for underflow
    EE_ASSERT(m_uiActiveObjects > 0);
    // Adjust active object count
    m_uiActiveObjects--;

    m_kMutex.Unlock();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainResourceManager::NotifyAllocTexture(TextureType::Value ePurpose, 
    const NiTexture* pkTexture)
{
    if (m_spListener)
        m_spListener->ReportAllocTexture(ePurpose, pkTexture);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainResourceManager::NotifyReleaseTexture(TextureType::Value ePurpose,
    const NiTexture* pkTexture)
{
    if (m_spListener)
        m_spListener->ReportReleaseTexture(ePurpose, pkTexture);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainResourceManager::NotifyAllocStream(StreamType::Value ePurpose, 
    const NiDataStream* pkStream, efd::UInt32 uiLODLevel)
{
    if (m_spListener)
        m_spListener->ReportAllocStream(ePurpose, pkStream, uiLODLevel);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainResourceManager::NotifyReleaseStream(StreamType::Value ePurpose, 
    const NiDataStream* pkStream)
{
    if (m_spListener)
        m_spListener->ReportReleaseStream(ePurpose, pkStream);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainResourceManager::NotifyAllocBuffer(efd::UInt32 uiBufferSize, void* pvBuffer)
{
    if (m_spListener)
        m_spListener->ReportAllocBuffer(uiBufferSize, pvBuffer);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainResourceManager::NotifyReleaseBuffer(void* pvBuffer)
{
    if (m_spListener)
        m_spListener->ReportReleaseBuffer(pvBuffer);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainResourceManager::NotifyRegister(const NiRefObject* pkObject)
{
    if (m_spListener)
        m_spListener->ReportRegister(pkObject);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainResourceManager::NotifyDeregister(const NiRefObject* pkObject)
{
    if (m_spListener)
        m_spListener->ReportDeregister(pkObject);
}

//--------------------------------------------------------------------------------------------------
template<typename T> inline 
T* NiTerrainResourceManager::CreateBuffer(efd::UInt32 uiCount)
{
    return (T*)CreateBuffer(uiCount * sizeof(T));
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainStandardResourceManager::BufferData::BufferData(efd::UInt32 uiSize):
    m_pkNextFree(NULL),
    m_pkMoreRecentlyUsed(NULL),
    m_pkLessRecentlyUsed(NULL),
    m_uiSize(uiSize)
{
    // Allocate the buffer
    m_pucBuffer = EE_ALLOC(efd::UInt8, uiSize + sizeof(InlineBufferData));

    // Set the inline buffer data
    InlineBufferData* pkInline = (InlineBufferData*)m_pucBuffer;
    pkInline->m_pkBufferData = this;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainStandardResourceManager::BufferData::~BufferData()
{
    EE_FREE(m_pucBuffer);
}

//--------------------------------------------------------------------------------------------------
inline void* NiTerrainStandardResourceManager::BufferData::GetBuffer()
{
    return m_pucBuffer + sizeof(InlineBufferData);
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 NiTerrainStandardResourceManager::BufferData::GetSize()
{
    return m_uiSize;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainStandardResourceManager::BufferData* 
    NiTerrainStandardResourceManager::BufferData::GetMoreRecentlyUsed()
{
    return m_pkMoreRecentlyUsed;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainStandardResourceManager::BufferData* 
    NiTerrainStandardResourceManager::BufferData::GetLessRecentlyUsed()
{
    return m_pkLessRecentlyUsed;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStandardResourceManager::BufferData::SetMoreRecentlyUsed(BufferData* pkNext)
{
    EE_ASSERT(m_pkMoreRecentlyUsed == NULL);
    m_pkMoreRecentlyUsed = pkNext;
    pkNext->m_pkLessRecentlyUsed = this;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStandardResourceManager::BufferData::BeginUsing()
{
    // Remove this buffer from the recently used list
    if (m_pkLessRecentlyUsed)
    {
        m_pkLessRecentlyUsed->m_pkMoreRecentlyUsed = m_pkMoreRecentlyUsed;
    }
    if (m_pkMoreRecentlyUsed)
    {
        m_pkMoreRecentlyUsed->m_pkLessRecentlyUsed = m_pkLessRecentlyUsed;
    }
    m_pkLessRecentlyUsed = NULL;
    m_pkMoreRecentlyUsed = NULL;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainStandardResourceManager::BufferData* 
    NiTerrainStandardResourceManager::BufferData::GetNextFree()
{   
    return m_pkNextFree;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStandardResourceManager::BufferData::SetNextFree(BufferData* pkNext)
{
    m_pkNextFree = pkNext;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainStandardResourceManager::BufferData* 
    NiTerrainStandardResourceManager::BufferData::FetchBufferData(void* pvBuffer)
{
    // Find the inline buffer data
    efd::UInt8* pucBuffer = (efd::UInt8*)pvBuffer;
    pucBuffer -= sizeof(InlineBufferData);
    InlineBufferData* pkInline = (InlineBufferData*)pucBuffer;

    // Find the buffer data object
    EE_ASSERT(pkInline->m_pkBufferData->GetBuffer() == pvBuffer);
    return pkInline->m_pkBufferData; 
}

//--------------------------------------------------------------------------------------------------