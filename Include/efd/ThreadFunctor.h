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
#ifndef EE_THREADFUNCTOR_H
#define EE_THREADFUNCTOR_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/MemObject.h>

namespace efd
{
    class Thread;

/**
    ThreadFunctor is an interface class that defines the interface between an efd::Thread and the
    function that thread invokes. This treats the inheriting class instance into a function
    object that can be invoked by efd::Thread.
 */
class EE_EFD_ENTRY ThreadFunctor : public MemObject
{
public:
    /// @name Construction and Destruction
    //@{
    ThreadFunctor();
    virtual ~ThreadFunctor();
    //@}

    /**
        Classes that inherit from ThreadFunctor implement this method which is then
        invoked by efd::Thread.

        @param pArg A pointer to the efd::Thread object that invoked this method.
        @return An arbitrary integer return value for the thread. efd::Thread will store this
        value as the return value from execution.
    */
    virtual efd::UInt32 Execute(efd::Thread* pArg)=0;
};

}

#endif // EE_THREADFUNCTOR_H
