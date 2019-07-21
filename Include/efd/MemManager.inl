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

#include <efd/Asserts.h>

namespace efd
{

//--------------------------------------------------------------------------------------------------
inline bool MemManager::IsInitialized()
{
    Get();
    return ms_pkMemManager != 0;
}

//--------------------------------------------------------------------------------------------------
inline void* MemManager::Allocate(
    size_t stSizeInBytes,
    size_t stAlignment,
    MemHint kHint,
    MemEventType eEventType,
    const char *pcSourceFile,
    int iSourceLine,
    const char* pcFunction)
{
    EE_MEMASSERT(m_pkAllocator);

    void* pvMem = m_pkAllocator->Allocate(stSizeInBytes,
        stAlignment,
        kHint,
        eEventType,
        pcSourceFile,
        iSourceLine,
        pcFunction);

    return pvMem;
}

//--------------------------------------------------------------------------------------------------
inline void* MemManager::Reallocate(
    void* pvMem,
    size_t stSizeInBytes,
    size_t stAlignment,
    MemHint kHint,
    MemEventType eEventType,
    size_t stSizeCurrent,
    const char *pcSourceFile,
    int iSourceLine,
    const char* pcFunction)
{
    EE_MEMASSERT(m_pkAllocator);

    void* pvNewMem = m_pkAllocator->Reallocate(pvMem,
        stSizeInBytes,
        stAlignment,
        kHint,
        eEventType,
        stSizeCurrent,
        pcSourceFile,
        iSourceLine,
        pcFunction);

    return pvNewMem;
}

//--------------------------------------------------------------------------------------------------
inline void MemManager::Deallocate(void* pvMem, MemEventType eEventType,
    size_t stSizeinBytes)
{
    EE_MEMASSERT(m_pkAllocator);

    m_pkAllocator->Deallocate(pvMem, eEventType, stSizeinBytes);
}

//--------------------------------------------------------------------------------------------------
inline bool MemManager::TrackAllocate(
    const void* const pvMem,
    size_t stSizeInBytes,
    MemHint kHint,
    MemEventType eEventType,
    const char *pcSourceFile,
    int iSourceLine,
    const char* pcFunction)
{
    EE_MEMASSERT(m_pkAllocator);

    return m_pkAllocator->TrackAllocate(pvMem,
        stSizeInBytes,
        kHint,
        eEventType,
        pcSourceFile,
        iSourceLine,
        pcFunction);
}

//--------------------------------------------------------------------------------------------------
inline bool MemManager::TrackDeallocate(
    const void* const pvMem,
    MemEventType eEventType)
{
    EE_MEMASSERT(m_pkAllocator);

    return m_pkAllocator->TrackDeallocate(pvMem, eEventType);
}

//--------------------------------------------------------------------------------------------------
inline bool MemManager::SetMarker(const char* pcMarkerType,
    const char* pcClassifier, const char* pcString)
{
    EE_MEMASSERT(m_pkAllocator);

    return m_pkAllocator->SetMarker(pcMarkerType, pcClassifier,
        pcString);
}

//--------------------------------------------------------------------------------------------------
inline const char* MemManager::MemEventTypeToString(MemEventType eEventType)
{
    switch (eEventType)
    {
    case EE_MET_UNKNOWN:
        return "EE_MET_UNKNOWN";
    case EE_MET_NEW:
        return "EE_MET_NEW";
    case EE_MET_NEW_ARRAY:
        return "EE_MET_NEW_ARRAY";
    case EE_MET_DELETE:
        return "EE_MET_DELETE";
    case EE_MET_DELETE_ARRAY:
        return "EE_MET_DELETE_ARRAY";
    case EE_MET_MALLOC:
        return "EE_MET_MALLOC";
    case EE_MET_REALLOC:
        return "EE_MET_REALLOC";
    case EE_MET_ALIGNEDMALLOC:
        return "EE_MET_ALIGNEDMALLOC";
    case EE_MET_ALIGNEDREALLOC:
        return "EE_MET_ALIGNEDREALLOC";
    case EE_MET_FREE:
        return "EE_MET_FREE";
    case EE_MET_ALIGNEDFREE:
        return "EE_MET_ALIGNEDFREE";
    case EE_MET_EXTERNALALLOC:
        return "EE_MET_EXTERNALALLOC";
    case EE_MET_EXTERNALFREE:
        return "EE_MET_EXTERNALFREE";
    case EE_MET_MARKER:
        return "EE_MET_MARKER";
    default:
        EE_FAIL("Unknown MemEventType value!");
    };

    return NULL;
}

//--------------------------------------------------------------------------------------------------
inline IAllocator* MemManager::GetAllocator()
{
    IAllocator* pResult = Get().m_pkAllocator;
    EE_MEMASSERT(pResult);
    return pResult;
}

//--------------------------------------------------------------------------------------------------
} // end namespace efd
