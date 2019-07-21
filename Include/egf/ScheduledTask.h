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
#ifndef EE_SCHEDULEDTASK_H
#define EE_SCHEDULEDTASK_H

#include <efd/IBase.h>
#include <egf/egfLibType.h>
#include <egf/EventID.h>

#include <egf/egfClassIDs.h>
#include <efd/TimeType.h>

namespace egf
{
class EventMessage;
class Scheduler;
class EntityFactoryResponse;

/// Used to schedule a task to run on the next tick.  The time will be updated to the
/// current time when the task is queued into the Scheduler.  If there are already other
/// pending "now" tasks, "first" tasks or past-due tasks they will run first.
static const efd::TimeType time_Now = 0.0;

/// Used to schedule a task to run before any already pending "now" tasks.  The time will
/// be updated to zero when the task is queued into the Scheduler.  If there are already
/// other "first" tasks pending the new task will run after those tasks.
static const efd::TimeType time_First = -1.0;

/**
    A unit of work for the Scheduler.  All tasks are processed in order through a single
    queue in the Scheduler.
*/
class EE_EGF_ENTRY ScheduledTask : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ScheduledTask, efd::kCLASSID_ScheduledTask, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    inline ScheduledTask(egf::EventID eventID, efd::TimeType when = time_Now);

    /// Destructor.
    virtual ~ScheduledTask();
    //@}

    /**
        Called to perform the work associated with this task.  Override this method to perform
        whatever actions are required by your task.

        @param pScheduler The Scheduler handling this task
    */
    virtual void DoTask(egf::Scheduler* pScheduler) = 0;

    /**
        In the event your task is cancelled prior to execution this method is called.  Perform
        any required cleanup to handle this condition.

        The default implementation does nothing.

        @param pScheduler The Scheduler handling this task
    */
    virtual void AbortTask(egf::Scheduler* pScheduler);

    /**
        Set the resulting event message which unblocked a waiting task.  This is only
        called for tasks that were added to the wait queue via Scheduler::QueueTaskOnEvent.
        The EventMessage passed in is the message with the EventID that was passed to
        Scheduler::QueueTaskOnEvent.  If this method returns true then this task will be
        added to the schedulers global queue at time_Now for execution on the next tick
        of the scheduler.  If you return false from this method then the task will be
        aborted via the AbortTask method instead.

        The default implementation simply returns true.

        @param pScheduler The scheduler to set the resulting event message for.
        @param pMessage The EventMessage this task was waiting for.
        @return True if your task is now ready to be queued, false if your task should be
            aborted instead.
    */
    virtual bool SetResult(egf::Scheduler* pScheduler, const egf::EventMessage* pMessage);

    /**
        Set the EntityFactoryResponse message which unblocked a waiting task. This is only
        called for tasks that were added to the wait queue via Scheduler::QueueTaskOnEntityCreation.
        The EntityFactoryMessage passed in is the message with the EntityID passed to
        Scheduler::QueueTaskOnEntityCreation.

        @param pResponse expected response message from the AssetFactoryManager.
    */
    virtual void SetEntityFactoryResponse(const egf::EntityFactoryResponse* pResponse);


    /// Get the time at which this task should execute.
    /// @return The time at which this task should begin execution
    inline efd::TimeType GetExecuteTime() const;

    /// Set the time at which this task should execute.
    /// @note Changing the time after calling Scheduler::QueueTask has no effect.
    /// @param when The time at which this task should run.  You can also use one of the
    ///     special values time_Now and time_First.
    inline void SetExecuteTime(efd::TimeType when);

    /// Get the EventID for this behavior execution.  All behaviors have a unique EventID.
    inline egf::EventID GetEventID() const;

    /// LessThan operator for storing ScheduledTasks in sorted containers.  A task is less
    /// than another task if it has a later execution time.
    inline bool operator<(const ScheduledTask& rhs) const;

protected:
    /// The event ID for this task.  All behavior-related tasks must have an EventID set.
    egf::EventID m_eventID;

    /// The execution time for this task.
    efd::TimeType m_executionTime;
};

/// A SmartPointer for the ScheduledTask class
typedef efd::SmartPointer<ScheduledTask> ScheduledTaskPtr;

} // end namespace egf

#include <egf/ScheduledTask.inl>

#endif // EE_SCHEDULEDTASK_H
