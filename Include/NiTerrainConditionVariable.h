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

#ifndef NITERRAINCONDITIONVARIABLE_H
#define NITERRAINCONDITIONVARIABLE_H

#include <efd/UniversalTypes.h>
#include <efd/StdContainers.h>
#include <efd/CriticalSection.h>
#include <efd/Semaphore.h>
#include <efd/StdContainers.h>
#include <efd/Utilities.h>
#include "NiTerrainLibType.h"

/**
    A class to implement a basic ConditionVariable on top of the efd::Semaphore and 
    efd::CriticalSection objects. Because it does not have access to OS level condition variable
    implementations it does not offer the best performance, though it does allow the semantics of
    ConditionVariables to be applied to a solution. 

    NOTE: No threads should be waiting on this condition variable when it is destroyed. 
*/
class NiTerrainConditionVariable
{
public:
    /**
        Condition variable constructor.
        The critical sector reference should be that of the monitor class that is using the
        condition variable. This monitor lock should be locked before making any calls to this
        condition variable.
    */
    NiTerrainConditionVariable(efd::CriticalSection& kMonitor);

    /// Destructor
    ~NiTerrainConditionVariable();

    /**
        Force the calling thread to pause until a 'signal' or a 'broadcast' is called on this
        object. The monitor lock must be locked before calling this function. All threads must be 
        signalled before destroying this object.
    */
    void Wait();

    /**
        Signal a single waiting thread to resume. If no threads are waiting then this function does
        nothing. The monitor lock must be locked before calling this function.
    */
    void Signal();
    
    /**
        Signal all waiting threads to resume. If no threads are waiting then this function does
        nothing. The monitor lock must be locked before calling this function.
    */
    void Broadcast();

    // Don't show documentation for these functions
    /// @cond EMERGENT_INTERNAL
    static void _SDMInit();
    static void _SDMShutdown();
    /// @endcond

private:
    // operator= not implemented because it is not valid 
    // This declaration is necessary due to the monitor reference stored in this class.
    NiTerrainConditionVariable& operator=(const NiTerrainConditionVariable&);

    /// The lock used by the encapsulating monitor class that this object belongs to
    efd::CriticalSection& m_kMonitor;
    /// A list of all the semaphores that waiting threads are waiting upon.
    efd::queue<efd::Semaphore*> m_kWaiters;

    /**
        Fetch a unique semaphore for the current thread. If one does not yet exist then one is 
        created. If one has already been created for this thread then it is returned. 
    */
    static efd::Semaphore* GetThreadSemaphore();
    
    /// The map of thread ID's to semaphores
    typedef efd::map<efd::UInt64, efd::Semaphore*> SemaphoreMap;
    static SemaphoreMap ms_kThreadSemaphores;
    /// A lock to protect the semaphore map
    static efd::CriticalSection ms_kCVSemaphores;
};

/**
    A class to abstract the process of pausing a thread until the value of a variable is observed.

    NOTE: It is possible for the value to be missed if SetValue is called twice before a waiting 
    thread has a chance to check the value. 
*/
template<class T> class NiTerrainPollableValue
{
public:
    /**
        Constructor of the value. It takes the initial value of the variable and a reference to
        the lock of the monitor class that owns this value. All locking rules for the 
        NiTerrainConditionVariable class apply to this object as well.
    */
    NiTerrainPollableValue(efd::CriticalSection& kMonitor, const T& kValue);
    
    /**
        Set the value of the variable to the given value. 
    */
    void SetValue(const T& kValue);
    
    /**
        Get the value of the variable.
    */
    const T& GetValue() const;

    /**
        Pause the calling thread until the variable's value is observed to equal the given value. 
        NOTE: It is possible for the value to be missed if SetValue is called twice before a waiting 
        thread has a chance to check the value. 
    */
    void WaitEqual(const T& kValue);

private:
    /// The variable to store the value of this object
    T m_kValue;
    /// The condition variable used to implement the waiting behaviour
    NiTerrainConditionVariable m_kCV;
};

#include "NiTerrainConditionVariable.inl"

#endif