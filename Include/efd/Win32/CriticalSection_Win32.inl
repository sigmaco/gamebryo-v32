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
//-------------------------------------------------------------------------------------------------
#if defined(EE_MULTITHREADED)
inline CriticalSection::CriticalSection(const char*) :
    m_threadOwner(0), m_lockCount(0)
{
    InitializeCriticalSection(&m_criticalSection);
}
#else
inline CriticalSection::CriticalSection(const char*)
{
}
#endif // #if defined(EE_MULTITHREADED)
//-------------------------------------------------------------------------------------------------
inline CriticalSection::~CriticalSection()
{
#if defined(EE_MULTITHREADED)
    DeleteCriticalSection(&m_criticalSection);
#endif // #if defined(EE_MULTITHREADED)
}
//-------------------------------------------------------------------------------------------------
inline void CriticalSection::Lock()
{
#if defined(EE_MULTITHREADED)
    EnterCriticalSection(&m_criticalSection);
    m_threadOwner = GetCurrentThreadId();
    m_lockCount++;
#endif // #if defined(EE_MULTITHREADED)
}
//-------------------------------------------------------------------------------------------------
inline void CriticalSection::Unlock()
{
#if defined(EE_MULTITHREADED)
    EE_ASSERT(m_lockCount > 0);
    EE_ASSERT(m_threadOwner == GetCurrentThreadId());
    m_lockCount--;
    if (m_lockCount == 0)
        m_threadOwner = 0;
    LeaveCriticalSection(&m_criticalSection);
#endif // #if defined(EE_MULTITHREADED)
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 CriticalSection::GetOwningThreadID() const
{
#if defined(EE_MULTITHREADED)
    return m_threadOwner;
#else
    return 0;
#endif // #if defined(EE_MULTITHREADED)
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 CriticalSection::GetCurrentLockCount() const
{
#if defined(EE_MULTITHREADED)
    return m_lockCount;
#else
    return 0;
#endif // #if defined(EE_MULTITHREADED)
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Fast Critical Section Methods
//-------------------------------------------------------------------------------------------------
inline FastCriticalSection::FastCriticalSection(const char*)
{
#if defined(EE_MULTITHREADED)

#if defined(EE_EFD_CONFIG_DEBUG)
    m_locked = false;
#endif

    InitializeCriticalSection(&m_criticalSection);

#endif // #if defined(EE_MULTITHREADED)
}
//-------------------------------------------------------------------------------------------------
inline FastCriticalSection::~FastCriticalSection()
{
#if defined(EE_MULTITHREADED)
    DeleteCriticalSection(&m_criticalSection);
#endif // #if defined(EE_MULTITHREADED)
}
//-------------------------------------------------------------------------------------------------
inline void FastCriticalSection::Lock()
{
#if defined(EE_MULTITHREADED)
    EnterCriticalSection(&m_criticalSection);
#if defined(EE_EFD_CONFIG_DEBUG)
    EE_ASSERT(m_locked == false);
    m_locked = true;
#endif
#endif // #if defined(EE_MULTITHREADED)
}
//-------------------------------------------------------------------------------------------------
inline void FastCriticalSection::Unlock()
{
#if defined(EE_MULTITHREADED)
#if defined(EE_EFD_CONFIG_DEBUG)
    m_locked = false;
#endif
    LeaveCriticalSection(&m_criticalSection);
#endif // #if defined(EE_MULTITHREADED)
}
//-------------------------------------------------------------------------------------------------

}; // namespace efd
