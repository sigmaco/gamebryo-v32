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

namespace efd
{

//------------------------------------------------------------------------------------------------
#if defined(EE_EFD_EXPORT) || defined(EE_EFD_IMPORT)

// DLL builds
//------------------------------------------------------------------------------------------------
inline FLF::FLF(const char* pcFile, unsigned int uiLine,
    const char* pcFunc)
{
    Set(pcFile, uiLine, pcFunc);
}

//------------------------------------------------------------------------------------------------
inline void FLF::Set(const char* pcFile, unsigned int uiLine,
    const char* pcFunc)
{
    if (pcFile != NULL)
    {
        size_t stStrLen = strlen(pcFile);
        if (stStrLen >= EE_FLF_FILE_LENGTH)
        {
            pcFile = pcFile + stStrLen - (EE_FLF_FILE_LENGTH - 1);
        }

        efd::Strcpy(m_pcFile, EE_FLF_FILE_LENGTH, pcFile);
    }
    else
    {
        m_pcFile[0] = '\0';
    }

    m_uiLine = uiLine;

    if (pcFunc != NULL)
    {
        efd::Strncpy(m_pcFunc, EE_FLF_FILE_LENGTH, pcFunc, EE_TRUNCATE);
    }
    else
    {
        m_pcFunc[0] = '\0';
    }
}

//------------------------------------------------------------------------------------------------
inline void FLF::Reset()
{
    Set(FLF::UNKNOWN.m_pcFile,
        FLF::UNKNOWN.m_uiLine,
        FLF::UNKNOWN.m_pcFunc);
}

#else // Non-DLL builds

//------------------------------------------------------------------------------------------------
inline FLF::FLF(const char* pcFile, unsigned int uiLine,
    const char* pcFunc) :
    m_pcFile(pcFile), m_pcFunc(pcFunc), m_uiLine(uiLine)
{
}

//------------------------------------------------------------------------------------------------
inline void FLF::Set(const char* pcFile, unsigned int uiLine,
    const char* pcFunc)
{
    m_pcFile = pcFile;
    m_uiLine = uiLine;
    m_pcFunc = pcFunc;
}

//------------------------------------------------------------------------------------------------
inline void FLF::Reset()
{
    m_pcFile = FLF::UNKNOWN.m_pcFile;
    m_uiLine = FLF::UNKNOWN.m_uiLine;
    m_pcFunc = FLF::UNKNOWN.m_pcFunc;
}

#endif

//------------------------------------------------------------------------------------------------
inline FLF::FLF()
{
    Reset();
}

//------------------------------------------------------------------------------------------------
inline bool FLF::IsValid() const
{
    return (m_uiLine != 0);
}

//------------------------------------------------------------------------------------------------
inline const char* FLF::SourceFileStripper() const
{
    const char* pcSlash = strrchr(m_pcFile, '\\');
    if (pcSlash)
    {
        return pcSlash + 1;
    }
    pcSlash = strrchr(m_pcFile, '/');
    if (pcSlash)
    {
        return pcSlash + 1;
    }
    return m_pcFile;
}

//------------------------------------------------------------------------------------------------
inline const char* FLF::CreateTempFLFString()
{
    static char acString[90];

    memset(acString, 0, sizeof(acString));
    efd::Sprintf(acString, 90, "%s(%05d)::%s", SourceFileStripper(), m_uiLine, m_pcFunc);
    return acString;
}

//------------------------------------------------------------------------------------------------
inline void AllocUnit::Reset()
{
    m_stAllocationID = (size_t) -1;
    m_stAlignment = 0;
    m_ulAllocThreadId = 0;
    m_pvMem = NULL;
    m_stSizeRequested = 0;
    m_stSizeAllocated = 0;
    m_kFLF.Reset();
    m_eAllocType = EE_MET_UNKNOWN;
    m_kAllocHint = EE_MEMHINT_NONE;
    m_fAllocTime = -FLT_MAX;
    m_pkPrev = NULL;
    m_pkNext = NULL;
#if defined(EE_MEMTRACKER_STACKTRACE)
    m_stackSize = 0;
    memset(m_stack, 0, sizeof(m_stack));
#endif
#if defined(EE_MEMTRACKER_DETAILEDREPORTING)
    m_pfnDetails = NULL;
#endif
#if defined(EE_MEMTRACKER_SNAPSHOT)
    m_pShapshotNext = NULL;
    m_pShapshotPrev = NULL;
#endif

}

//------------------------------------------------------------------------------------------------
#if defined(EE_MEMTRACKER_DETAILEDREPORTING)
inline void AllocUnit::GetDetailedReport(char* o_buffer, unsigned int i_cchBuffer) const
{
    if (m_pfnDetails)
    {
        m_pfnDetails(m_pvMem, o_buffer, i_cchBuffer);
    }
    else
    {
        *o_buffer = '\0';
    }
}
#endif

//------------------------------------------------------------------------------------------------
inline bool MemTracker::GetAlwaysValidateAll() const
{
    return m_bAlwaysValidateAll;
}

//------------------------------------------------------------------------------------------------
inline void MemTracker::SetAlwaysValidateAll(bool bOn)
{
    m_bAlwaysValidateAll = bOn;
}

//------------------------------------------------------------------------------------------------
inline bool MemTracker::GetCheckForArrayOverruns() const
{
    return m_bCheckArrayOverruns;
}

//------------------------------------------------------------------------------------------------
inline unsigned int MemTracker::AddressToHashIndex(const void* pvAddress)
{
    // Use the address to locate the hash index. Note that we shift off the
    // lower four bits. This is because most allocated addresses will be on
    // four-, eight- or even sixteen-byte boundaries. If we didn't do this,
    // the hash index would not have very good coverage.

    // The size_t may be cast to an unsigned int as long as ms_uiHashSize
    // is less than the largest unsigned int.

    return (unsigned int)(reinterpret_cast<size_t>(pvAddress) >> 4) &
        (ms_uiHashSize - 1);
}

//------------------------------------------------------------------------------------------------
inline MemTracker* MemTracker::Get()
{
    return ms_pkTracker;
}

//------------------------------------------------------------------------------------------------
inline size_t MemTracker::GetCurrentAllocationID() const
{
    return m_stCurrentAllocID;
}

//------------------------------------------------------------------------------------------------
inline bool MemTracker::IsInsideBreakRange(const void* pvMem, size_t stSize)
{
    return ((((const char*)pvMem) + stSize) >= ms_pvBreakOnAllocRangeStart &&
        (pvMem <= ms_pvBreakOnAllocRangeEnd));
}

//------------------------------------------------------------------------------------------------
inline void MemTracker::SetWriteToLog(bool bOn)
{
    m_bWriteToLog = bOn;
}

//------------------------------------------------------------------------------------------------
inline bool MemTracker::CanAllocateNow()
{
    return m_insideOfMain || !m_assertOutsideOfMain;
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
