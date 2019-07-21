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
#ifndef EE_THREAD_H
#define EE_THREAD_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/ProcessorAffinity.h>
#include <efd/ThreadFunctor.h>
#include <efd/MemObject.h>
#include <efd/Utilities.h>

#if defined (EE_PLATFORM_PS3) || defined (EE_PLATFORM_LINUX)
#include <pthread.h>
#endif

namespace efd
{

/**
    A platform-independent wrapper class to handle thread manipulation.
*/

class EE_EFD_ENTRY Thread : public MemObject
{
public:

    /// @name Enums
    //@{
    enum
    {
        USEDEF_STACK_SIZE  = 0xffffffff,
        #if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
            DEFAULT_STACK_SIZE = 0  // Let the OS pick the default stack size
        #elif defined (EE_PLATFORM_PS3)
            DEFAULT_STACK_SIZE = 0x4000 // 16KB
        #elif defined (EE_PLATFORM_LINUX)
            DEFAULT_STACK_SIZE = 0 // Let the OS pick the default stack size
        #endif
    };

    enum Priority
    {
        /**
        The thread is scheduled with the lowest priority so that it only runs
        when no other thread needs processor time.
        */
        IDLE = 0,               // Base priority level
        /**
        The lowest, non-idle priority available. This thread will only preempt idle threads.
        */
        LOWEST,                 // 2 points below normal
        /**
        The thread is scheduled at below normal priority to avoid interrupting regular tasks.
        */
        BELOW_NORMAL,           // 1 point below normal
        /**
        The thread is scheduled at normal priority and shares time with other common task threads.
        */
        NORMAL,
        /**
        The thread is scheduled above normal priority and will preempt normal priority threads
        to complete its task.
        */
        ABOVE_NORMAL,           // 1 point above normal
        /**
        The highest regular priority available. This thread will run with priority execution
        over any thread not marked as TIME_CRITICAL
        */
        HIGHEST,                // 2 points above normal
        /**
        This maps to the absolute highest system priority meaning that this thread will never
        be preempted unless there are other TIME_CRITICAL threads.
        */
        TIME_CRITICAL,          // Absolute highest OS priority available

        NUM_PRIORITIES
    };

    enum Status
    {
        /**
        The thread is currently active although not necessarily scheduled and executing.
        */
        RUNNING     = 0,
        /**
        The thread is suspended and not eligible for scheduling.
        */
        SUSPENDED,
        /**
        The thread has completed and exited with a return value.
        */
        COMPLETE
    };
    //@}

protected:
    Thread(ThreadFunctor* pProcedure,
        efd::UInt32 stackSize = USEDEF_STACK_SIZE,
        const char* pcThreadName = NULL);

public:

    /// @name Constructor and Virtual Destructor
    //@{
    /**
    There are no publicly defined constructors forThread.
    Applications should create all threads through the static
    Create method to make sure the thread is properly initialized and managed.
    */

    /**
    Virtual Destructor
    */
    virtual ~Thread();


    //@}

    /// @name Static Member Functions
    //@{

    /**
    Create a thread using a specified ThreadProcedure and stack size. The thread
    does not take ownership of the ThreadProcedure object so that a procedure can
    be shared across multiple worker threads. All threads are created in the SUSPENDED state.
    */
    static Thread* Create(ThreadFunctor* pProcedure,
        efd::UInt32 stackSize = USEDEF_STACK_SIZE,
        const char* pcThreadName = NULL);

    /**
    Get the Thread pointer for the current thread context. If the current thread context
    was not created using the Thread API, this value will be NULL.
    */
    static Thread* GetThread();

    //@}

    /// @name Supported Member Functions
    //@{

    /// Get a pointer to the thread procedure used by an Thread object.
    inline ThreadFunctor* GetProcedure() const;
    /**
    Set the priority of the thread. The priority enumeration is listed below.
    It is possible for this value to be stale since the class member's priority will
    only be set after the system level priority is set.
    */
    bool SetPriority(Priority newPriority);
    /**
    Get the priority of the thread. The priority enumeration is listed below.
    It is possible for this value to be stale since the class member's priority will
    only be set after the system level priority is set.
    */
    inline Priority GetPriority() const;

    /**
    Set the processor affinity for the thread using the ProcessorAffinity class.
    This setting will take place the next time the OS schedules the thread.
    */
    inline bool SetThreadAffinity(const ProcessorAffinity& affinity);
    /**
    Get the processor affinity for the thread using the ProcessorAffinity class.
    This setting will take place the next time the OS schedules the thread.
    */
    inline const ProcessorAffinity GetThreadAffinity();

    /**
    Get the current status of a thread. It is possible for this member to be stale
    since the class member's status will only be set after the system level routines return.
    */
    inline Status GetStatus() const;
    /// Get the return value of a completed thread.
    inline efd::UInt32 GetReturnValue() const;
    /// Get and set the name of the thread for debugging purposes.
    inline const efd::Char* GetName() const;

    /**
    Suspend or resume a thread. The system will return -1 if these calls fail.
    Successful completion will return an integer that depends on the operating system.
    Usually, this value is the thread's suspend count prior to the call. Thus, a return of
    0 indicates that a thread was running at the time of the call. Any positive, non-zero
    value indicates a suspended thread.
    */
    efd::SInt32 Suspend();
    /**
    Suspend or resume a thread. The system will return -1 if these calls fail. Successful
    completion will return an integer that depends on the operating system. Usually, this
    value is the thread's suspend count prior to the call. Thus, a return of 0 indicates
    that a thread was running at the time of the call. Any positive, non-zero value indicates
    a suspended thread.
    */
    efd::SInt32 Resume();
    /**
    Returns true if the thread was running and the system waited for termination. If the thread
    was not running, the function will return false. This may be because the thread has already
    completed execution.
    */
    bool WaitForCompletion();

    //@}


    //@cond EMERGENT_INTERNAL
    // *** begin Emergent internal use only ***
    inline void SetStackSize(efd::UInt32 stackSize);
    inline void SetProcedure(ThreadFunctor* pProcedure);
    // *** end Emergent internal use only ***
    //@endcond

protected:
    bool SystemCreateThread();
    bool SystemSetPriority(Priority newPriority);
    bool SystemSetAffinity(const ProcessorAffinity& affinity);
    int SystemSuspend();
    int SystemResume();
    bool SystemWaitForCompletion();

    ProcessorAffinity m_affinity;

    efd::UInt32 m_stackSize;

    ThreadFunctor* m_pProcedure;

    Priority m_priority;
    volatile Status m_status;
    volatile efd::UInt32 m_returnValue;

    // Note: Setting the name is now a protected method as the name should be passed in
    // via the Create method instead for proper operation on all platforms
    inline void SetName(const efd::Char* pcName);

#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
    static DWORD WINAPI ThreadProc(void* pArg);
    HANDLE m_hThread;
#elif defined(EE_PLATFORM_PS3)
    static void* ThreadProc(void* pArg);
    pthread_t m_threadID;
    pthread_mutex_t m_mutexID;
    volatile bool m_resumed;
#elif defined(EE_PLATFORM_LINUX)
    static void* ThreadProc(void* pArg);
    pthread_t m_threadID;
    pthread_mutex_t m_mutexID;
#endif

    // This is supplied primarily for debugging to allow for easily
    // identifying threads. In release builds, it will likely be compiled
    // out to nothing, so DO NOT write code that depends on it being
    // present.
    efd::Char* m_pName;
};

} // namespace efd

#include <efd/Thread.inl>

#endif
