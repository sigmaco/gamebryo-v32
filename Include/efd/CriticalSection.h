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
// Emergent Game Technologies! Calabasas! CA 91302
// http://www.emergent.net

#pragma once
#ifndef EE_CRITICALSECTION_H
#define EE_CRITICALSECTION_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>

#if defined (EE_PLATFORM_LINUX)
#include <pthread.h>
#endif

#if defined(EE_PLATFORM_PS3) && !defined(__SPU__)
#include <sys/synchronization.h>
#include <sys/ppu_thread.h>
#include <cell/sync/mutex.h>
#endif

#define EE_MULTITHREADED
namespace efd
{
/**
    A platform-independent wrapper class to handle critical sections for threading. When entering
    the critical section the Lock method should be called. When exiting, the Unlock method. The
    critical section will automatically release upon destruction.

    This CriticalSection implementation is recursive. The same thread can requests a critical
    section lock multiple times without deadlock. These requests are tracked and the critical
    section released only when an equal number of unlock calls is made from the thread.
*/
class EE_EFD_ENTRY CriticalSection
{
public:
    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    CriticalSection(const char* pcDebugName = NULL);

    /// Destructor.
    ~CriticalSection();

    //@}

    /// Locks the critical section. This prevents other threads from entering the protected
    /// code block. Each call to Lock increments to lock count.
    inline void Lock();

    /// Decrement the lock count and unlocks the critical section when it falls to zero.
    inline void Unlock();

    /**
        Gets the ID of the thread that last locked the critical section.

        @return The ID of the last thread to lock the critical section or
            0 if the critical section is not locked.
    */
    inline efd::UInt32 GetOwningThreadID() const;

    /**
        Gets the current count of calls to Lock by the same thread. The
        critical section will not be unlocked until Unlock has been called
        this many times.

        @return The number of times the critical section has been locked by the same thread.
    */
    inline efd::UInt32 GetCurrentLockCount() const;


#if defined(EE_PLATFORM_PS3) && !defined(__SPU__)
    /// @cond EMERGENT_INTERNAL

    // Access to the system mutex id for use in conjunction with NiRWLock
    sys_lwmutex_t& GetSysMutex();

    /// @endcond
#endif

protected:
#if defined (EE_MULTITHREADED)
#if defined (EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
    CRITICAL_SECTION m_criticalSection;

    /// The ID of the last thread to lock the critical section.
    unsigned long m_threadOwner;

#elif defined (EE_PLATFORM_PS3) && !defined(__SPU__)
    sys_lwmutex_t m_criticalSection;
    sys_ppu_thread_t m_threadOwner;
#elif defined (EE_PLATFORM_LINUX)
    pthread_mutex_t m_criticalSection;
    pthread_t m_threadOwner;
#endif // #ifdef for platforms

    /// The count of how many times the critical section has been locked by
    /// the same thread.
    efd::UInt32 m_lockCount;

#endif // #if defined (EE_MULTITHREADED)
};

/**
    A platform-independent wrapper class to handle critical sections for
    threading. On some platforms this may be faster than efd::CriticalSection.
    This implementation does not track Lock requests and therefore should not be
    used recursively.
*/
class EE_EFD_ENTRY FastCriticalSection
{
public:
    /// Default constructor.
    FastCriticalSection(const char* pcDebugName = NULL);

    /// Destructor.
    ~FastCriticalSection();

    /// Locks the critical section.
    inline void Lock();

    /// Unlocks the critical section.
    inline void Unlock();

protected:
#if defined (EE_MULTITHREADED)
#if defined (EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
    CRITICAL_SECTION m_criticalSection;
#elif defined (EE_PLATFORM_PS3) && !defined(__SPU__)
    CellSyncMutex m_mutex;
    size_t m_mutexLockCount;
#elif defined (EE_PLATFORM_LINUX)
    pthread_mutex_t m_criticalSection;
#endif // #ifdef for platforms

#if defined (EE_EFD_CONFIG_DEBUG)
    bool m_locked;
#endif

#endif // #if defined (EE_MULTITHREADED)
};

} // end namespace efd

#if defined(EE_PLATFORM_WIN32)
#include <efd/Win32/CriticalSection_Win32.inl>
#elif defined(EE_PLATFORM_PS3)
#include <efd/PS3/CriticalSection_PS3.inl>
#elif defined(EE_PLATFORM_XBOX360)
#include <efd/XBox360/CriticalSection_Xbox360.inl>
#elif defined(EE_PLATFORM_LINUX)
#include <efd/Linux/CriticalSection_Linux.inl>
#else
#error Platform Undefined!
#endif

#endif // #ifndef EE_CRITICALSECTION_H
