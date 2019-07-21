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
#ifndef EE_SCHEDULER_H
#define EE_SCHEDULER_H

#include <egf/egfLibType.h>
#include <egf/egfSystemServiceIDs.h>
#include <egf/ISchedulerScripting.h>
#include <egf/EntityManager.h>
#include <egf/SchedulerQueue.h>
#include <egf/GameTimeClock.h>
#include <egf/IDebuggerCallback.h>

#if defined(EE_PLATFORM_WIN32)
    #pragma warning(disable : 4251)
#endif

namespace efd
{
    class AssignNetIDMessage;
}

namespace egf
{
// forward decl
class EntityFactoryResponse;
class PendingBehavior;

typedef efd::RefCountedMemObj< efd::list< EntityID > > EntityIDList;
typedef efd::SmartPointer< EntityIDList > EntityIDListPtr;

typedef efd::list< EntityPtr > EntityList;
typedef efd::set< EntityPtr > EntitySet;

#define EGF_SCHEDULER_SECTION "Scheduler"


/**
    The implementation class that is the basis for a scheduler process.
    The Scheduler is a System Service that manages 'owned' entities. Each entity in the system
    is owned by one and only one Scheduler at a time. The Scheduler gets ticked once per
    framework tick. When the Scheduler is ticked, it feeds cycles to the behavior models of any
    Entities that need it (Executed Owned Entities). The Scheduler will call the behavior system
    once for each pending Entity behavior.
 */
class EE_EGF_ENTRY Scheduler : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(Scheduler, efd::kCLASSID_Scheduler, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

private:
    /// Destructor. Private to prevent subclasses.
    virtual ~Scheduler();

public:

    /// Global Scheduler configuration defines
    static const char *kSchedulerSection;
    static const char *kMaxThread;
    static const char *kShardID;

public:
    /// Default constructor
    Scheduler();

    /**
        Add a task to the global queue.  The ExecutionTime set on the task determines when
        this task will run.  Tasks are always executed during Scheduler::OnTick at or after
        their ExecutionTime has been reached. All times for scheduled tasks are in game time, not
        real time, which means they are delayed by pausing the scheduler and effected by any
        changes to the game time clock.

        @param pTask The task to execute
        @return True
    */
    bool QueueTask(ScheduledTask* pTask);

    /**
        Add a task to a waiting queue until a response is received at which time the task will
        be automatically moved into the global queue at "time_Now" and executed on the next
        tick following the response.

        @note The initial ExecutionTime set on pTask is ignored.  When this event is eventually
            added to the global queue it will always be queued using "time_Now".

        @note Only one task can be blocked on a given EventID.

        @param replyEvent The event this task is waiting for.
        @param pTask The task waiting to be executed
        @return True if the event was queued, false on error.
    */
    bool QueueTaskOnEvent(EventID replyEvent, ScheduledTask* pTask);

    /**
        Add a task to a waiting queue until an EntityFactoryResponse is received at which time the
        task will be automatically moved into the global queue at "time_Now" and executed on the
        next tick following the response.

        @note The initial ExecutionTime set on pTask is ignored.  When this event is eventually
            added to the global queue it will always be queued using "time_Now".

        @note Only one task can be blocked on a given EntityID.

        @param waitingFor The ID of the entity we're waiting for.
        @param pTask The task waiting to be executed
        @return True if the event was queued, false on error.
    */
    bool QueueTaskOnEntityCreation(EntityID waitingFor, ScheduledTask* pTask);

    /**
        Determine if an event has been queued but not yet executed.
        @param id The event to check
        @return True if the event is queued but not yet executed.
    */
    bool IsBehaviorPending(EventID id) const;

    /**
        Remove an event that has been queued but not yet executed.  ScheduledTask::AbortTask
        will be called on the event if it is found and removed.

        @param id The event to remove
        @return True if the event was removed.
    */
    bool RemovePendingBehavior(EventID id);

    /**
        Destroy an entity by invoking Entity::Destroy, which will
        check for a scripted OnDestroy behavior

        @param entityID The EntityID of the entity to destroy
        @return true if the entity was found and the destroy function called
    */
    bool DestroyEntity(egf::EntityID entityID);

    /**
        Destroy an entity by invoking Entity::Destroy, which will
        check for a scripted OnDestroy behavior

        @param pEntity The Entity* of the entity to destroy
        @return true if the entity was found and the destroy function called
    */
    bool DestroyEntity(egf::Entity* pEntity);

    /**
        Find an owned entity given its EntityID class.

        @param id reference to an EntityID class instance.
        @return Entity smart pointer to owned entity or NULL if not found.
    */
    Entity* LookupEntity(const EntityID &id) const;

     /**
        Find ANY entity (owned or replicated) given its EntityID class.

        @param id reference to an EntityID class instance.
        @return Entity smart pointer to owned entity or NULL if not found.
    */
    Entity* FindEntity(const EntityID &id) const;

     /**
        Find an entity given its data file id.  This method simple delegates to the EntityManager
        and exists only for legacy compatibility.

        @param id reference to an EntityID class instance.
        @return Entity pointer to an entity or NULL if not found.
    */
    inline Entity* LookupEntityByDataFileID(const efd::ID128& id) const;

    /**
        Lets an entity subscribe to Behavior messages from particular categories
        This will subscribe the scheduler to kMSGID_Event and kMSGID_EventCancel messages on
        behalf of the given entity.  The category should be either the entity's ID itself or
        else an event channel about which the entity is interested.  Optionally you may also
        request return messages (kMSGID_EventReturn) if the entity

        @param pEntity The pointer to the entity that wants to receive the message
        @param cat The "match" category bits
    */
    void SubscribeEntity(Entity* pEntity, const efd::Category& cat);

    /**
        Allows an entity to unsubscribe to Behavior messages from particular categories

        @param pEntity The pointer to the entity to stop receiving the messages
        @param cat The "match" category bits
    */
    void UnsubscribeEntity(Entity* pEntity, const efd::Category& cat);

    /**
        Returns the number of script language threads each entity can run.

        May be called during PreInit or Init.

        @return efd::UInt32 number of script language threads that each entity can have open
            simultaneously.
    */
    efd::SInt32 GetMaxThread() const;

    /**
        Retrieves the private category for the scheduler process

        @return The private efd::Category for the this scheduler
    */
    inline const efd::Category& GetSchedulerCat() const;

    /**
        Retrieves the private category for the scheduler process

        @return The global efd::Category used by all schedulers
    */
    inline efd::Category GetAllSchedulersCat();

    /**
        Retrieves the scheduler announce channel for all the schedulers.

        @return The global efd::Category used by all schedulers to announce that they are up and
            running.
    */
    inline efd::Category GetSchedulersAnnouceCat();

    /**
        Entities directly receive their own EventMessages and then pass them to this method for
        processing.

        @param[in] pEntity The Entity* to process
        @param[in] pEventMessage The EventMessage* to process
        @param[in] isViewEvent True if this is a view event. This effects error logging only.
    */
    void ProcessEventMessage(
        Entity* pEntity,
        const EventMessage* pEventMessage,
        bool isViewEvent = false);

    /**
        Register a scripting runtime with the scheduler.

        @note This method can be called as soon as the Scheduler is created. It is recommended that
            scripting runtime implementations be added either during system service creation or
            during OnPreInit of a system service.

        @param name the name of the scripting engine.
        @param behaviorType The type of behavior handled by this runtime.
        @param engine the scripting engine to register.
        @return true if the engine was added, false if it already exists.
    */
    efd::Bool RegisterScriptingRuntime(
        const efd::utf8string& name,
        efd::UInt32 behaviorType,
        ISchedulerScripting* engine);

    /**
       Get a pointer to a scripting runtime given that runtimes name. Returns null
       if the runtime is not available.

       @param name the name of the runtime
       @return An ISchedulerScripting pointer, or null if the runtime was not found.
    */
    ISchedulerScripting* GetScriptingRuntime(const efd::utf8string& name);

    /**
        Get a pointer to a scripting runtime given that runtimes behavior id. Returns null
        if the runtime is not available.

        @param behaviorType The type of behavior handled by the runtime.
        @return An ISchedulerScripting pointer, or null if the runtime was not found.
    */
    ISchedulerScripting* GetScriptingRuntime(efd::UInt32 behaviorType);

    /**
       Get the status of the given runtime.

       @param[in] name the string name of the runtime to check
       @return ISchedulerScripting::RuntimeStatus enum value
    */
    ISchedulerScripting::RuntimeStatus GetRuntimeStatus(const efd::utf8string& name);

    /**
        Get the status of the given runtime.

        @param[in] ID the ID of the runtime to check
        @return ISchedulerScripting::RuntimeStatus enum value
    */
    ISchedulerScripting::RuntimeStatus GetRuntimeStatus(efd::UInt32 ID);

    /**
        Determine if the provided behavior type is a scripted type or one of the fixed base
        types.  Any value which is not a well-known non-script type is considered to be a
        scripted type.

        @param[in] behaviorType either an egf::BehaviorTypes enumeration value or a custom script
            value as would be used in a RegisterScriptingRuntime call.
    */
    static bool IsScriptedBehaviorType(efd::UInt32 behaviorType);

    /**
        Execute a behavior for the specified Entity

        @param[in] pPendBehavior The PendingBehavior* to run
        @return bool true on success
    */
    bool DoScriptBehavior(egf::PendingBehavior* pPendBehavior);

    /**
        Request that the Scheduler and game time clock be paused or resumed. Pass true to request
        pausing and false to request resuming. The Scheduler accumulates all the requests to
        determine the final pause state. When paused the value of the game time clock will not
        increase.

        This method can only be called after Scheduler::OnPreInit has completed.

        @param[in] pause True to pause or false to unpause.
    */
    void PauseScheduler(bool pause);

    /**
        Reports whether the scheduler is paused, meaning that entities are not being ticked.

        This method can only be called after Scheduler::OnPreInit has completed.

        @return bool true if a match was found, false otherwise
    */
    inline bool IsPaused() const;

    /**
        Request that the scheduler begin with the game time clock paused. If this method succeeds
        you must resume the scheduler by calling PauseScheduler(false) before behaviors can be
        executed.

        @note This method should be called before Scheduler::OnPreInit is called in order to
            ensure that the clock is paused before it begins ticking.

        @note When this method fails you may wish to simply call PauseScheduler(true) in order to
            go ahead and pause the clock. This can be useful if attempting to pause the scheduler
            from the OnPreInit of another service. Depending on the service priorities the other
            service could have OnPreInit called before or after the scheduler but in either case
            the game time clock will not have been advanced yet. Consider the following example:

        @code
        // Example of ensuring the scheduler is paused from an OnPreInit method:
        efd::SyncResult SomeService::OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar)
        {
            m_pScheduler = m_pServiceManager->GetSystemServiceAs<egf::Scheduler>();
            if (!m_pScheduler->StartSchedulerPaused())
            {
                // Failure of StartSchedulerPaused tells us Scheduler::OnPreInit has run so we
                // can safely call PauseScheduler:
                m_pScheduler->PauseScheduler(true);
            }
            // Because we called this during OnPreInit we now know the scheduler is paused at the
            // initial game time. We will resume the scheduler later when we are ready
            ...
        }
        efd::AsyncResult SomeService::OnTick()
        {
            // For example, we may simply want to leave game time paused until intialization
            // is complete. Or perhaps you might wait until loading of a block begins. Remember
            // that no behaviors can run while paused and completion of a block load may require
            // execution of various lifecycle behavaiors such as OnCreate so you should unpause
            // no later than the elr_Loaded result (elr_Loading would be even better to avoid a
            // glut of lifecycle behaviors from building up).
            if (m_firstTick)
            {
                m_pScheduler->PauseScheduler(false);
                m_firstTick = false;
            }
            ...
        }
        @endcode

        @return True if this method was called prior to OnPreInit and will thus take effect, or
            false if the game time clock has already been initialized. When false is returned the
            game time clock will NOT be paused and should therefore not be resumed.
    */
    inline bool StartSchedulerPaused();

    /**
        Tells the scheduler to delete all entities on the next tick.  Any running or queued
        behaviors are discarded.  This should only be called for rapid iteration and not in
        production as behaviors will be lost.  Calls ClearEntities after next tick.
    */
    void DeleteAllEntities();

    /**
        Delete Entities from internal maps, send a message to the server to unload assets.
        Caution this happens immediately, if a delay is practical use DeleteAllEntities.
    */
    void CleanEntities();

    /**
        Read the current value of the game time clock.

        This method can only be called after Scheduler::OnPreInit has completed.
    */
    inline efd::TimeType GetGameTime() const;

    /**
        Returns the amount by which the game time clock advanced between the previous tick and
        this tick.  When the Scheduler is paused this amount will be zero.

        This method can only be called after Scheduler::OnPreInit has completed.
    */
    inline efd::TimeType GetLastGameTimeDelta() const;

    /**
        Specifies a callback function for script debugging logic, executed during the scheduler
        update.  Only one debugger callback can be registered at a time.

        May be called during PreInit or Init.

        @param callback script debugger callback to install
    */
    inline void SetDebuggerCallback(IDebuggerCallback* callback);

    /// @cond EMERGENT_INTERNAL

    /**
        Called when a new NetID is assigned to this process
    */
    void HandleNetIDAssigned(
        const efd::AssignNetIDMessage* pAssignNetIDMessage,
        efd::Category targetChannel);

    /**
        Handler for EntityFactoryResponse messages. A behavior can block waiting for an entity
        creation to complete by calling BehaviorAPI::CreateEntityAndWait. The scheduler listens
        for EntityFactoryResponse messages and resumes any tasks waiting for the resulting
        EntityId.

        @param pMsg EntityFactoryResponse message.
    */
    void HandleEntityFactoryResponse(const egf::EntityFactoryResponse* pMsg, efd::Category);
    /// @endcond

protected:

    /**
        Pointers to other services are cached and the local message channel is subscribed
        to.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);


    /**
        Script runtimes are configured. The configuration is read and processed. Messages
        are subscribed to and some additional internal processing takes place.
    */
    virtual efd::AsyncResult OnInit();

    /**
        Process the scheduled task queue and execute any current tasks for this tick. Primarily
        that implies running new behaviors and resuming paused behaviors that have become unblocked.
    */
    virtual efd::AsyncResult OnTick();

    /**
        Clear internal queues and otherwise shut down the scheduler.
    */
    virtual efd::AsyncResult OnShutdown();

    /// Return the service name, in this case "Scheduler".
    virtual const char* GetDisplayName() const;

    /// Run all tasks whose time has come.
    efd::UInt32 ProcessQueue();

    /// When a "return value" event arrives, this checks whether any tasks are blocked on this
    /// event.  If they are those tasks are added to the global queue at "time_Now".
    bool ProcessReturnEvent(const EventMessage* pMessage);

    /**
        Count of number of scripted behaviors that can be blocked at any given moment...  For
        example, the active uThreads using Stackless Python.
    */
    efd::SInt32 m_maxThread;

    /// Smart pointer to local message service
    efd::MessageServicePtr m_spMessageService;
    /// Smart pointer to the EntityManager
    EntityManagerPtr m_spEntityManager;

    /// shard ID for this scheduler instance
    efd::UInt32 m_shardID;
    /// scheduler ID for this instance
    efd::UInt32 m_schedulerID;
    /// private channel for this scheduler/framework
    efd::Category m_simOwnedCat;

    /// The global task queue
    SchedulerQueue m_globalQueue;

    /// A map of tasks blocked waiting for return events
    typedef efd::map< egf::EventID, ScheduledTask* > BlockedTasksMap;
    BlockedTasksMap m_blockedTasks;

    /// A map of tasks blocked waiting on EntityFactoryResponse messages.
    typedef efd::map< egf::EntityID, ScheduledTask* > BlockedCreationTaskMap;
    BlockedCreationTaskMap m_blockCreationTasks;

    bool m_bCleanEntitiesOnNextTick;

    /// this boolean keeps track of whether we are currently ticking the scheduler
    /// this is important if we need to queue an action or perform it instantly.
    bool m_bIsTicking;

    /// The simulator clock
    egf::GameTimeClock* m_pGameClock;
    /// Defaults to false, if set true the game clock will be paused when created.
    efd::UInt32 m_startPaused;

private:
    friend class EntityManager;

    /**
        Processes the delayed entity destruction list calling Entity::Destroy on each entry in
        m_destroyedEntitySet
    */
    void DestroyEntitiesInternal();

    /// Initialize python and lua scripting if available
    void InitScriptingRuntimes();

    /// Storage for Entities to destroy at the end of our next OnTick.  Destruction is delayed
    /// when it triggers from inside OnTick in order to avoid recurrsion.
    EntitySet m_destroyedEntitySet;

    IDebuggerCallback* m_debuggerCallback;

    /// scripting runtimes
    typedef efd::map<efd::utf8string, ISchedulerScriptingPtr> ScriptingRuntimeMap;
    ScriptingRuntimeMap m_scriptingRuntimes;

    /// scripting runtimes
    typedef efd::map<efd::UInt32, ISchedulerScriptingPtr> ScriptingRuntimeIDMap;
    ScriptingRuntimeIDMap m_scriptingRuntimesByID;

    // Statistics related to the entities/behaviors on this scheduler.
    //

    /// Helper for outputting the entity/behavior related statistics.
    void LogEntityBehaviorStats();

    /// The number of seconds between scheduler stats dumps.
    efd::TimeType m_statsDumpIntervalInSec;
    /// The GetServiceManagerTime() timestamp of when the scheduler started.
    efd::TimeType m_schedulerStartTime;
    /// The GetServiceManagerTime() timestamp of the last stats dump.
    efd::TimeType m_lastStatsDumpTime;

    /// The following variables get incremented at each tick and holds the counters since the last
    /// stats dump.
    efd::UInt32 m_numTicks;
    efd::UInt32 m_numEntities;
    efd::UInt32 m_numExecutingEntities;
    efd::UInt32 m_numBehaviorsExecuted;

    /// The following variables get incremented at each stats dump (the above counters get
    /// added) and holds the counters since the system startup.
    efd::UInt32 m_numTotalTicks;
    efd::UInt64 m_numTotalEntities;
    efd::UInt64 m_numTotalExecutingEntities;
    efd::UInt64 m_numTotalBehaviorsExecuted;
};

/**
    A smart pointer (reference counting, self deleting pointer) for the Scheduler class
*/
typedef efd::SmartPointer<Scheduler> SchedulerPtr;

} // end namespace egf

#include <egf/Scheduler.inl>

#endif // EE_SCHEDULER_H
