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

#ifndef NITERRAINSTREAMINGMANAGER_H
#define NITERRAINSTREAMINGMANAGER_H

#include "NiTerrainTaskProcessor.h"
#include "NiTerrainStreamingTask.h"

NiSmartPointer(NiTerrainStreamingManager);

/**
    This class represents the workhorse of the terrain streaming mechanism. It manages a list 
    of jobs to have executing for each sector and handles how a thread pool of workers are divided
    up to process the pending jobs.
*/
class NITERRAIN_ENTRY NiTerrainStreamingManager : public NiRefObject
{
public:
    /** 
        A listener class used to collect error information about the streaming process and
        provide a possible hook for metrics.
    */  
    class NITERRAIN_ENTRY Listener
    {
    public:
        /// Quick reference to a TaskType object
        typedef NiTerrainStreamingTask::TaskType TaskType;
        /// Quick reference to a Status object
        typedef NiTerrainStreamingTask::Status Status;
        /// Quick reference to a SectorID object
        typedef NiTerrainSector::SectorID SectorID;
        /// Quick reference to a TaskID object
        typedef efd::UInt64 TaskID;

        /// Virtual destructor
        virtual ~Listener();

        /**
            Reference counting incrementation
        */
        virtual void IncRefCount() = 0;

        /**
            Reference counting decrementation
        */
        virtual void DecRefCount() = 0;

        /**
            This function is called whenever a streaming task is started
            
            @param kTaskID The task ID used to link reporting calls together.
            @param kSectorID The unique ID of the sector being manipulated in this task
            @param eTaskType The type of task being executed on the sector
        */
        virtual void ReportStartTask(TaskID kTaskID, SectorID kSectorID, TaskType::VALUE eTaskType);

        /**
            This function is called whenever a streaming task's status is updated.
            Different status values relate to different stages in the streaming process and
            are different for each task type.

            @param kTaskID The task ID used to link reporting calls together.
            @param eTaskType The type of task being executed on the sector
            @param eStatus The new status of the task
        */
        virtual void ReportTaskStatus(TaskID kTaskID, TaskType::VALUE eTaskType, 
            Status::VALUE eStatus);

        /**
            This function is called whenever a streaming task is completed. The 
            error code returned allows errors in the streaming process to be reported.

            @param kTaskID The task ID used to link reporting calls together.
            @param eTaskType The type of task being executed on the sector
            @param uiErrorCode The final errorcode reported by the streaming process
        */
        virtual void ReportFinishTask(TaskID kTaskID, TaskType::VALUE eTaskType, 
            efd::UInt32 uiErrorCode);
    };
    /// Defines a smartpointer for the Listener class
    typedef efd::SmartPointer<Listener> ListenerPtr;

    /// Constructor
    NiTerrainStreamingManager();
    ///Destructor
    ~NiTerrainStreamingManager();

    /**
        Request that the streaming manager rebuild the geometry of a portion of the given sector. 
        The region given is in heightmap pixels, and is an inclusive range. 
        This function will block until the rebuild has been completed.

        @param pkSector the sector to rebuild
        @param kChangedRegion the region of the heightmap that needs rebuilding
        @return true if the task was successfully submitted
    */
    bool RequestRebuildSector(NiTerrainSector* pkSector, NiRect<NiInt32> kChangedRegion);

    /**
        Request that a sector be paged in or out of memory from disk. 

        @param pkSector the sector to page
        @param iTargetLOD the LOD that the sector should be loaded to (-1 is unloaded and removed)
        @param bWaitForCompletion if true, this function will block until the task is completed
        @return true if the task was successfully submitted
    */
    bool RequestPageSector(NiTerrainSector* pkSector, NiInt32 iTargetLOD, 
        bool bWaitForCompletion = false); 

    /**
        Request that a sector be given blank geometry

        @param pkSector the sector to create
        @param bWaitForCompletion if true, this function will block until the task is completed
        @return true if the task was successfully submitted
    */
    bool RequestCreateBlankSector(NiTerrainSector* pkSector, bool bWaitForCompletion = false);

    /**
        Performs any lock/unlock operations or sector removal tasks that may be pending. All these
        tasks must be called from the renderer/update thread. This function is the entry point
        for that thread to execute the tasks waiting on it.

        NOTE: If the max tasks = 0 then all tasks are executed
    */
    void PerformRendererThreadTasks(efd::UInt32 uiMaxNumTasksToProcess = 0);

    /**
        Attempts to cancel any tasks, then runs until all queued tasks have been completed. This
        is a blocking function, returning only when all tasks have been completed.
    */
    void Abort();

    /**
        Waits for all tasks that have been submitted to the loading manager to be completed.
    */
    void WaitForAllTasksCompleted();

    /**
        Returns true if the specified sector is currently in the process of streaming
    */
    bool PollSectorStreamingStatus(NiTerrainSector* pkSector);

    /**
        Returns true if any streaming tasks are currently executing
    */
    bool PollStreamingStatus();

    /**
        Sets a listener object that will receive events on the progress of tasks
        @return The original listener object
    */
    ListenerPtr SetListener(Listener* pkListener);

    /**
        Returns the current streaming listener object that receives task progress events
    */
    Listener* GetListener();

    /**
        Sets the number of worker threads to use in processing streaming. 
        A value of 0 will remove all threaded functionality of the streaming system. 
    */
    void SetNumWorkers(efd::UInt32 uiNumWorkers);

private:
    /// Enumeration of all the types of task queues involved in loading
    struct TaskQueueType
    {
        enum VALUE
        {
            PRELOADING,
            LOADING,
            BUILDING_HEIGHTS,
            BUILDING_LIGHTING,
            BUILDING_MAPS,
            POPULATING,
            UNLOADING,
            REMOVAL,
            LOCK,
            UNLOCK,

            NUM_TASK_QUEUES
        };
    };

    /// Sector to Task map type definition
    typedef efd::map<NiTerrainSector*, NiTerrainStreamingTask*> SectorToTaskMap;

    /**
        Attempt to start executing a task.

        @param pkTask The task to start
        @param bWaitForCompletion if true, this function will block until the task is completed
        @return true if the task was successfully started
    */
    bool StartTask(NiTerrainStreamingTask* pkTask, bool bWaitForCompletion = false);

    /**
        Submit a task to a specific task queue.
        The task's status will be set to the new value and will be submitted to the relevant
        task queue for it's state. 

        @param pkTask the task to submit
        @param eStatus the status of the task
    */
    bool SubmitTask(NiTerrainStreamingTask* pkTask, NiTerrainStreamingTask::Status::VALUE eStatus);

    /**
        Attempt to cancel the specified task. The task will not be cancelled if it has already
        begun to be executed.

        @param pkTask The task to cancel
        @return true if the task was successfully cancelled
    */
    bool CancelTask(NiTerrainStreamingTask* pkTask);

    /**
        This function is called when a task has been completed

        @param pkTask The task that has been completed
    */
    void CompleteTask(NiTerrainStreamingTask* pkTask);

    /// Fire the start task event on the listener object
    void NotifyStartTask(NiTerrainStreamingTask* pkTask);
    /// Fire the task status change event on the listener object
    void NotifyTaskStatus(NiTerrainStreamingTask* pkTask);
    /// Fire the task finish event on the listener object
    void NotifyFinishTask(NiTerrainStreamingTask* pkTask);

    /**
        Perform a number of tasks from the given queue. The maximum number of tasks that
        can be executed is passed in as a reference and is decremented as tasks are executed.
    */
    void ExecuteQueueTasks(NiTerrainTaskQueue* pkQueue, efd::UInt32& uiMaxTasks);

    /**
        Wait for a specific task to be completed. If the renderer thread is used to wait on a task
        then it is forced to keep processing the streaming tasks itself.
    */
    void WaitForTaskToComplete(NiTerrainStreamingTask* pkTask);

    /**
        This function is used to select which queue contains the next task to be allocated to a 
        thread.

        @returns null if there are no further tasks to be executed
    */
    NiTerrainTaskQueue* AquireTaskQueue();

    /// Critical section to protect this monitor class
    efd::CriticalSection m_kMutex;
    /// Map of sectors to tasks - for querying if a sector has a task currently executing
    SectorToTaskMap m_kTaskedSectors;
    /// The task processor used to execute tasks
    NiTerrainTaskProcessor m_kTaskProcessor;
    /// The queues used to breakdown tasks into different states
    NiTerrainTaskQueue m_kTaskQueues[TaskQueueType::NUM_TASK_QUEUES];
    /// Pollable value used to wait for all threaded tasks to complete
    NiTerrainPollableValue<bool> m_kAllThreadedTasksCompleted;
    /// Listener object listening to callbacks
    NiPointer<Listener> m_spListener;
    /// The thread ID of the renderer/update thread
    efd::UInt64 m_uiUpdateThreadID;

    /**
        Callback for threads to call. It will return a pointer to a queue from which the
        thread will process it's next task. Returns NULL if there are no tasks to be executed.
    */
    static NiTerrainTaskQueue* Callback_AquireTaskQueue(void* pvArg);

    /// @{
    /// Callbacks used by the task queues
    static void Callback_ProcessPreloadTask(void* pvArg, NiTerrainStreamingTask* pkTask, 
        NiUInt32 uiWorkUnit);
    static void Callback_ProcessLoadingTask(void* pvArg, NiTerrainStreamingTask* pkTask, 
        NiUInt32 uiWorkUnit);
    static void Callback_ProcessBuildingHeightsTask(void* pvArg, NiTerrainStreamingTask* pkTask, 
        NiUInt32 uiWorkUnit);
    static void Callback_ProcessBuildingLightingTask(void* pvArg, NiTerrainStreamingTask* pkTask, 
        NiUInt32 uiWorkUnit);
    static void Callback_ProcessBuildingMapsTask(void* pvArg, NiTerrainStreamingTask* pkTask, 
        NiUInt32 uiWorkUnit);
    static void Callback_ProcessPopulatingTask(void* pvArg, NiTerrainStreamingTask* pkTask, 
        NiUInt32 uiWorkUnit);
    static void Callback_ProcessUnloadingTask(void* pvArg, NiTerrainStreamingTask* pkTask, 
        NiUInt32 uiWorkUnit);
    static void Callback_ProcessRemovalTask(void* pvArg, NiTerrainStreamingTask* pkTask, 
        NiUInt32 uiWorkUnit);
    static void Callback_ProcessLockTask(void* pvArg, NiTerrainStreamingTask* pkTask, 
        NiUInt32 uiWorkUnit);
    static void Callback_ProcessUnlockTask(void* pvArg, NiTerrainStreamingTask* pkTask, 
        NiUInt32 uiWorkUnit);
    /// @}
};

#endif
