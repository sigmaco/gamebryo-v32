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

#ifndef NITERRAINTASKPROCESSOR_H
#define NITERRAINTASKPROCESSOR_H

#include <efd/MemObject.h>
#include <efd/Thread.h>
#include <efd/StdContainers.h>
#include <NiSmartPointer.h>
#include <NiString.h>
#include "NiTerrainLibType.h"
#include "NiTerrainConditionVariable.h"

class NiTerrainStreamingTask;

/**
    This class is used to manage the streaming task queues. Each instance of this class represents
    the queue for a particular action being executed on a streaming task.
*/
class NITERRAIN_ENTRY NiTerrainTaskQueue: public efd::MemObject
{
public:
    /// Task type exposure
    typedef NiTerrainStreamingTask TaskType;
    /// Task callback type
    typedef void (*ProcessCallbackType)(void* pvArg, TaskType* pkTask, efd::UInt32 uiWorkUnit);

    /// Constructor
    NiTerrainTaskQueue();
    /// Destructor
    ~NiTerrainTaskQueue();

    /**
        Submit a task to the queue to wait for a thread to process it. The task will be queried
        for the number of work units that are pending in it's current state, and these work units
        will then be queued for distribution to threads.
    */
    void SubmitTask(TaskType* pkNewTask);

    /**
        Configure this queue with what callback should be called to process each task
    */
    void SetTaskProcessingCallback(const ProcessCallbackType& kProcessTaskCallback, 
        void* pvCallbackArgument);
   
    /// Query the number of work units in this queue
    efd::UInt32 GetQueueSize();
    /// Query the number of unreserved work units
    efd::UInt32 GetNumUnreservedWorkUnits();
    /// Query the number of active work units
    efd::UInt32 GetActiveWorkUnitCount();
    /// Reserve a work unit from the queue for processing in the current thread
    bool ReserveWorkUnit();
    
    /**
        Execute the first work unit on the queue in the current thread. The ReserveWorkUnit
        function must have been called before calling this function and it must have returned true
        for this thread.
    */
    void ProcessWorkUnit();

private:

    /// structure to define a work unit
    struct WorkUnit
    {
        /// The ID of the work unit on the task
        efd::UInt32 m_uiWorkUnitID;
        /// The task that the work unit belongs to
        NiPointer<TaskType> m_spTask;
        /// A helper function to use when generating viewer strings
        void ToString(const char* pcPrefix, NiString& kString);
    };

    /// The custom argument to pass to the 'process callback'
    void* m_pvCallbackArgument;
    /// The callback function used to process a task's work unit
    ProcessCallbackType m_kProcessCallback;
    /// A mutex to protect the queue on this class
    efd::CriticalSection m_kMutex;
    /// The queue of work units
    efd::queue<WorkUnit> m_kWorkQueue;
    /// The total number of active work units (being processed)
    efd::UInt32 m_uiNumActiveWorkUnits;
    /// The total number of reserved work units (to be processed)
    efd::UInt32 m_uiNumReservedWorkUnits;
};

/**
    This class manages a set of worker threads to process the contents of NiTerrainTaskQueues.
    Whilst this class does not manage those queues, it abstracts the management of the threads
    from the rest of the system, allowing a smooth shift between threaded and unthreaded modes.
*/
class NITERRAIN_ENTRY NiTerrainTaskProcessor: public efd::MemObject
{
public:
    /// Callback type for the task queue aquisition
    typedef NiTerrainTaskQueue* (*AquireTaskQueueCallbackType)(void* pvArg);

    /// Constructor
    NiTerrainTaskProcessor();
    /// Destructor
    ~NiTerrainTaskProcessor();

    /**
        Configure the aquire task queue callback. This callback is used to select from which 
        queue a task will be executed from. The aquire callback must reserve the task before 
        returning or return NULL (no tasks to be executed).

        If the aquire callback does return NULL, the calling thread will be put to sleep until 
        it is notified of another task being added.
    */
    inline void SetAquireTaskQueueCallback(void* pvArg, AquireTaskQueueCallbackType kCallback);

    /**
        Notify the task processor that a task has been added to the queues that needs processing. 
        If there are worker threads sleeping then this function will wake one up. If there are
        no worker threads then this function will attempt to process the task immediately using
        the current thread.
    */
    inline void NotifyTaskAdded();

    /// Set the number of worker threads to use
    inline void SetNumWorkers(efd::UInt32 uiNumWorkers);
    /// Get the number of worker threads being used
    inline efd::UInt32 GetNumWorkers() const;
    
    /**
        Shutdown the task processor. This function will reduce the worker count to 0, and wait
        for all the worker threads to complete their execution before returning.
    */
    void Shutdown();

private:
    /// Thread functor for the general thread execution
    class ThreadFunction: public efd::ThreadFunctor
    {
    public:
        /// Constructor
        ThreadFunction(NiTerrainTaskProcessor* pkProcessor);
        /// Execution function
        efd::UInt32 Execute(efd::Thread* pArg);
    private:
        /// Pointer to the task processor in control of this thread
        NiTerrainTaskProcessor* m_pkProcessor;
    };

    /// Execute a single work unit by selecting a task queue
    void ExecuteNextWorkUnit();
    /// Add a worker thread to the thread pool
    inline void EnlistWorker();
    /// Retire a worker thread from the thread pool
    inline bool RetireWorker(efd::Thread* pkThread);

    /// Type for storing the threads
    typedef efd::vector<efd::Thread*> ThreadList;

    /// Custom callback argument
    void* m_pvCallbackArgument;
    /// Acquire callback to acquire a task queue
    AquireTaskQueueCallbackType m_kAquireCallback;
    /// The thread pool
    ThreadList m_kThreadPool;
    /// The lock to protect the thread pool and the condition variable
    efd::CriticalSection m_kLock;
    /// The function used by threads
    ThreadFunction* m_pkThreadFunction;
    /// The number of workers created
    efd::UInt32 m_uiNumWorkers;
    /// The number of active workers
    efd::UInt32 m_uiNumActiveWorkers;
    /// A condition variable to allow threads to sleep and wake when required
    NiTerrainConditionVariable m_kTaskNotified;
};

#include "NiTerrainTaskProcessor.inl"

#endif