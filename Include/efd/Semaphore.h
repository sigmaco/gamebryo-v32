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


#pragma once
#ifndef EE_SEMAPHORE_H
#define EE_SEMAPHORE_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/OS.h>
#include <efd/AtomicOperations.h>

namespace efd
{

/**
    A platform-independent wrapper class for a simple semaphore.

    @note Some platforms support the concept of a maximum count for a semaphore.  On platforms
    that do not, the maximum count is bounded only by the maximum of the storage type used by the
    OS.  Regardless, the Semaphore class does not enforce this count internally, but relies on the
    OS for such management, due to the synchronization overhead that such enforcement would incur.
*/
class EE_EFD_ENTRY Semaphore
{

public:
    /**
        Creates a Semaphore object with a count of 0.

        Semaphores created with this default constructor are non-signaled from creation, since the
        initial count is zero.  The maximum count is set to 1.
    */
    Semaphore();

    /**
        Creates a Semaphore object with a count equal to iCount.

        iCount should be a non-negative value.  The maximum count is set to iCount + 1.
        Semaphores created with this constructor will be signaled if the count is positive.

        @param count Initial count.  This value must be greater than or equal to 0.
    */
    Semaphore(efd::SInt32 count);

    /**
        Creates a Semaphore object with a count equal to iCount and the maximum count set to
        iMaxCount.

        iCount should be a non-negative value less than iMaxCount.  Semaphores created with this
        constructor will be signaled if the count is positive.

        @param count Initial count.  This value must be greater than or equal to 0 and less than
            or equal to maxCount.
        @param maxCount Maximum count.  This value must be greater than zero.
    */
    Semaphore(
        efd::SInt32 count,
        efd::SInt32 maxCount);

    /// Virtual destructor.
    virtual ~Semaphore();

    /**
        Get a count on the semaphore.

        It is possible for this value to be stale since the semaphore only alters the count after
        system level operations complete.  GetCount() is intended for debugging use only and
        should not be considered an accurate count for the purposes of thread synchronization.

        @return A signed 32-bit integer representing the current count.
    */
    inline efd::SInt32 GetCount();

    /**
        Get the maximum count of the semaphore, set during construction.

        @return A signed 32-bit integer representing the current maximum count.
    */
    inline efd::SInt32 GetMaxCount();

    /**
        Signal the semaphore and increase the count by 1.

        @return The count of the semaphore after the signal operation.
    */
    inline efd::SInt32 Signal();

    /**
        Wait on the semaphore.

        If the count is 0, the calling thread will be suspended until the semaphore is signaled.
        If the semaphore is in a signaled state, then the count will be reduced by 1 and returned.

        @return The count of the semaphore after the wait operation.
    */
    inline efd::SInt32 Wait();

protected:

#if !defined (EE_PLATFORM_PS3)
    /*
        Initial count.
        This value must be greater than or equal to 0 and less than or equal to maxCount.
    */
    volatile efd::SInt32 m_count;
#endif

    /*
        Maximum count.
        This value must be greater than zero.
    */
    efd::SInt32 m_maxCount;

    // Platform-specific semaphore member variable declaration.
#if defined (EE_PLATFORM_WIN32) || defined (EE_PLATFORM_XBOX360)
    HANDLE m_hSemaphore;
#elif defined(EE_PLATFORM_PS3)
    sys_semaphore_t m_hSemaphore;
#elif defined (EE_PLATFORM_LINUX)
    sem_t m_hSemaphore;
#endif

};

}   // End namespace efd.

// Include platform-specific header.
#if defined (EE_PLATFORM_WIN32)
#include <efd/Win32/Semaphore_Win32.inl>
#elif defined (EE_PLATFORM_LINUX)
#include <efd/Linux/Semaphore_Linux.inl>
#elif defined (EE_PLATFORM_PS3)
#include <efd/PS3/Semaphore_PS3.inl>
#elif defined (EE_PLATFORM_XBOX360)
#include <efd/XBox360/Semaphore_XBox360.inl>
#endif

#endif //EE_SEMAPHORE_H
