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
#ifndef NITHREADPROCEDURE_H
#define NITHREADPROCEDURE_H

#include <efd/Thread.h>
#include <efd/ThreadFunctor.h>

// Entirely inline, so doesn't need NISYSTEM_ENTRY
class NiThreadProcedure : public efd::ThreadFunctor
{
public:
    // This is the method that needs to be overridden to implement new thread behavior
    virtual unsigned int ThreadProcedure(efd::Thread*)
    {
        EE_FAIL("The thread procedure was not overridden.  You may have a "
            "signature mismatch in your derived class of ThreadProcedure");
        return 0;
    }

    // Execute is invoked by the thread, and simply calls into the
    // 'standard' ThreadProcedure override point
    virtual efd::UInt32 Execute(efd::Thread* pArg)
    {
        return ThreadProcedure(pArg);
    }
};

#endif  //#ifndef NITHREADPROCEDURE_H
