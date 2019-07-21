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
#ifndef NIINITOPTIONS_H
#define NIINITOPTIONS_H

#include "NiSystemLibType.h"
#include "NiUniversalTypes.h"

#include <efd/InitOptions.h>

class NISYSTEM_ENTRY NiInitOptions : public efd::InitOptions
{
public:
    NiInitOptions();
    ~NiInitOptions();

#if !defined (EE_PLATFORM_PS3)
    /// Sets a callback method for Floodgate to use when determining the number
    /// of worker threads to create.
    void SetFloodgateDefineWorkerThreadCountFunc(void* pfnCallback);

    /// Gets a callback method for Floodgate to use when determining the number
    /// of worker threads to create.
    const void* GetFloodgateDefineWorkerThreadCountFunc();

    /// Sets a callback method for Floodgate to use when determining the
    /// thread affinity of the dispatcher thread.
    void SetDispatchThreadAffinityFunc(void* pfnCallback);

    /// Gets a callback method for Floodgate to use when determining the
    /// processor affinity of the dispatcher thread.
    const void* GetDispatchThreadAffinityFunc();

    /// Sets a callback method for Floodgate to use when determining the
    /// processor affinity of the worker threads.
    void SetWorkerThreadAffinityFunc(void* pfnCallback);

    /// Gets a callback method for Floodgate to use when determining the
    /// processor affinity of the worker threads.
    const void* GetWorkerThreadAffinityFunc();

    /**
        Sets whether or not Floodgate should operate with a parallel execution
        model. Floodgate will operate with a parallel execution model by
        default. In general parallel execution should only turned on when
        operating on a single core machine.
    */
    void SetFloodgateParallelExecution(bool bParallelExecution);

    /// Returns whether or not Floodgate is using a parallel execution model.
    bool GetParallelExecution();
#endif

#if defined (EE_PLATFORM_PS3)
    /// Gets the number of job workloads for Floodgate to reserve on the SPURS instance
    unsigned int GetJobWorkloadCount() const;

    /// Sets the number of job workloads for Floodgate to reserve on the SPURS instance
    void SetJobWorkloadCount(NiUInt32 uiJobWorkloadCount);

    // *** begin Emergent internal use only ***

    /// Gets the number of task workloads to reserve on the SPURS instance
    unsigned int GetTaskWorkloadCount() const;

    /// Sets the number of task workloads to reserve on the SPURS instance
    void SetTaskWorkloadCount(NiUInt32 uiTaskWorkloadCount);

    // *** end Emergent internal use only ***
#endif

private:

#if !defined(EE_PLATFORM_PS3)
    void* m_pfnDefineWorkerThreadCountFunc;
    void* m_pfnAssignDispatcherThreadAffinityFunc;
    void* m_pfnAssignWorkerThreadAffinityFunc;
    bool m_bParallelExecution;
#endif

#if defined(EE_PLATFORM_PS3)
    NiUInt32 m_uiJobWorkloadCount;
    NiUInt32 m_uiTaskWorkloadCount;
#endif
};

#endif // #ifndef NIINITOPTIONS_H
