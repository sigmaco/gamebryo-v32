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
#ifndef EE_LOOPEDTHREAD_H
#define EE_LOOPEDTHREAD_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/Thread.h>
#include <efd/LoopedThreadProcedure.h>
#include <efd/Semaphore.h>

namespace efd
{

/**
    LoopedThread is a class designed to facilitate the use of threads that need to be reused
    multiple times.

    A common use for this class would be to allow an application to have a multithreaded update or
    culling pass.  Instead of recreating threads each frame in such a case, an application could
    use this class to repeatedly perform a task.

    @note Like a Thread, a LoopedThread is created suspended and must be resumed before it can be
    used.

    @note Each DoLoop() should be paired with a WaitForLoopCompletion() call after it.  DoLoop()
    cannot be called repeatedly to run the loop multiple times without blocking.

    @note LoopedThreads may be destroyed by deleting them (via destructor).  They may also be
    explicitly stopped via Shutdown().  Both Shutdown() and the destructor will wait until the
    loop procedure has finished running and will not interrupt it.  Shutdown() and the destructor
    will block until the loop has terminated (which is not necessarily when the thread procedure
    has terminated (return condition set, status set, etc...)  Once a thread has stopped, DoLoop()
    silently does nothing.
*/
class EE_EFD_ENTRY LoopedThread : public Thread
{
public:
    /// Virtual destructor.
    virtual ~LoopedThread();

    /**
        Create a thread using a specified LoopedThreadProcedure and a stack size.

        There are no publicly defined constructors for this class.  Applications should create all
        threads through the static Create method to make sure the thread is properly initialized
        and managed.

        The thread does not take ownership of the LoopedThreadProcedure object so that a
        procedure may be shared across multiple worker threads.  Like Thread, all LoopedThreads
        are created in the SUSPENDED state and must be resumed before any loop iterations will
        run.

        @param pProcedure Pointer to a LoopedThreadProcedure.
        @param stackSize Stack size.
        @param pcThreadName Optional thread name.
        @return Pointer to a newly created LoopedThread.
    */
    static LoopedThread* Create(
        LoopedThreadProcedure* pProcedure,
        efd::UInt32 stackSize = USEDEF_STACK_SIZE,
        const char* pcThreadName = NULL);

    /**
        Block until a loop iteration has completed.

        This function is usually used after a call to DoLoop().  If the thread has not terminated,
        then once this function returns, it will be suspended until the next time DoLoop() is
        called.
    */
    bool WaitForLoopCompletion();

    /**
        Signal the thread to run a single iteration of its loop.

        Calls to this function cannot be stacked.  In other words, there should only be a single
        call to DoLoop() before a corresponding call to WaitForLoopCompletion().
    */
    void DoLoop();

    /**
        Use this function to signal the LoopedThread to terminate.

        This function will not shutdown a thread in the middle of a loop.  In such a case, it will
        block until the loop has finished and then allow the thread to terminate.
    */
    inline void Shutdown();

    /// @cond EMERGENT_INTERNAL

    // Synchronization functions used by efd::LoopedThreadProcedure().
    inline void WaitStart();
    inline void SignalStart();
    inline void WaitComplete();
    inline void SignalComplete();
    inline void SetLastLoop();
    inline bool GetLastLoop();

    /// @endcond

protected:
    // Constructor is protected, so use the Create() function.
    LoopedThread(
        LoopedThreadProcedure* pProcedure,
        efd::UInt32 stackSize = USEDEF_STACK_SIZE,
        const char* pcThreadName = NULL);

    // True if the thread will exit in less than a complete loop iteration.
    volatile bool m_lastLoop;

    // Complete is 1 if the loop is done; Complete is 0 if in a loop.
    Semaphore m_complete;

    // Start is 0 if the loop has started; Start is 1 if the loop can start.
    Semaphore m_start;
};

}   // End namespace efd.

#include <efd/LoopedThread.inl>

#endif
