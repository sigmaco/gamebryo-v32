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
#ifndef EE_LOOPEDTHREADPROCEDURE_H
#define EE_LOOPEDTHREADPROCEDURE_H

#include <efd/efdLibType.h>
#include <efd/ThreadFunctor.h>

namespace efd
{

/**
    efd::LoopedThreadProcedure defines the function and associated data that will run in an
    efd::LoopedThread. While not abstract, applications should not create instances of this
    class but should instead define some useful subclass that overrides LoopedProcedure.
*/
class EE_EFD_ENTRY LoopedThreadProcedure : public ThreadFunctor
{
public:
    /**
        This function describes a single iteration of a loop.

        This function is the one that classes derived from LoopedThreadProcedure should override.
        It returns false if the Thread should terminate or true if the Thread should be kept alive
        so that this function may be called again.  LoopedThread may also be externally signaled
        through its Shutdown() function to stop looping.

        @note The thread will never be terminated in the middle of a LoopedProcedure function
        call.  It will always wait until the loop completes.

        @param pArg Pointer to a thread.
        @return True if the thread should continue looping; false otherwise.
    */
    virtual bool LoopedProcedure(efd::Thread* pArg);

    /// Enumerate the possible return values of this ThreadFunctor.
    enum ReturnCode
    {
        /// Indicates the thread was terminated by LoopedThread::Shutdown().
        THREAD_TERMINATED,

        /// Indicates the thread was terminated by the LoopedProcedure.
        PROC_TERMINATED
    };

private:
    /**
        This function is called by the Thread framework to handle iterations of the
        LoopedProcedure.
        @param pArg something
        @return The value is one from LoopedThreadProcedure::ReturnCode.
    */
    virtual efd::UInt32 Execute(efd::Thread* pArg);
};

}   // End namespace efd.

#endif
