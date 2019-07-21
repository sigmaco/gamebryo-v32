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
#ifndef EE_PendingBehavior_h
#define EE_PendingBehavior_h

#include <efd/UniversalTypes.h>
#include <efd/ParameterList.h>
#include <egf/BehaviorDescriptor.h>
#include <egf/ScheduledTask.h>
#include <egf/egfClassIDs.h>
#include <egf/Entity.h> // for smart ptr

/// Macro to enable additional behavior timing metrics.  Define to turn on detailed per-behavior
/// execution time tracking, or undefine for faster performance.
#undef EE_USE_BEHAVIOR_TIMING_METRICS

namespace egf
{

class Entity;

/**
    The implementation class for a pending behavior (event/method).

    This class holds pointers to a behavior and arguments to the actual call.  It is used to
    hold pending behaviors on the wait queue after they arrive in event or method messages.

*/
class EE_EGF_ENTRY PendingBehavior : public egf::ScheduledTask
{
    // DT32309 This class should be renamed to PendingEvent or perhaps even just Event.  An Event
    // can consist of multiple behaviors so the current name is misleading.

    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(PendingBehavior, efd::kCLASSID_PendingBehavior, egf::ScheduledTask);
    /// @endcond

    /// @name Construction and Destruction
    //@{
    /**
        Constructor used to build queue entry.

        @param[in] pEntity The entity on which the behavior is to run.
        @param[in] spArgs Stream of arguments for the behavior.
        @param[in] executeTime The time the behavior should execute.
        @param[in] eventID The event ID of the behavior.
        @param[in] returnID The entity ID to send the return value to.
        @param[in] immediate Is this event immediate
    */
    PendingBehavior(
        egf::Entity* pEntity,
        efd::ParameterListPtr spArgs,
        efd::TimeType executeTime,
        EventID eventID,
        EntityID returnID,
        bool immediate);

    /// Destructor
    ~PendingBehavior();
    //@}

public:

    /**
        Method to create a new PendingBehavior

        @param[in] pBehavior Pointer to the behavior to execute.
        @param[in] pEntity The entity on which the behavior is to run.
        @param[in] spArgs Stream of arguments for the behavior.
        @param[in] executeTime The time the behavior should execute.
        @param[in] eventID The event ID of the behavior.
        @param[in] returnID The entity ID to send the return value to.
        @param[in] immediate Is this event immediate
    */
    static efd::SmartPointer< PendingBehavior > Create(
        const BehaviorDescriptor* pBehavior,
        egf::Entity* pEntity,
        efd::ParameterListPtr spArgs,
        efd::TimeType executeTime,
        EventID eventID,
        EntityID returnID,
        bool immediate = false);

    /// Executes the pending behavior.
    virtual void DoTask(Scheduler*);

    /// Called if this task is aborted.  In turn calls FinishBehavior.
    virtual void AbortTask(Scheduler*);

    /// Get the Entity  that will run this behavior
    inline egf::Entity* GetScriptEntity() const;

    /// Get the Descriptor of the behavior that will run
    inline const BehaviorDescriptor* GetBehaviorDescriptor() const;

    /// Get the list of arguments for this behavior. Arguments can be fetched by index and
    /// optionally by name (names should be used when calling extends style behaviors).
    inline efd::ParameterList* GetArgumentList() const;

    /// Get the EntityID of the Entity that requested this behavior.  If this behavior is the
    /// result of a SendEvent call then this is the EntityID of the sender.  This ID is the
    /// destination for methods like SendReply.
    inline EntityID GetReturnEntityID() const;

    /// Get the lifecycle token.  This is a lifecycle identifier as would be passed to the
    /// Entity::_OnLifecycle and related methods.  If set, the completion of this behavior
    /// will trigger an Entity::EndLifecycle call.
    inline efd::UInt32 GetLifecycleToken() const;

    /// Set the lifecycle token.
    inline void SetLifecycleToken(efd::UInt32 lifecycle);

    /// Determine if execution has begun on this behavior.
    inline bool Started() const;

    /// Determines if the current behavior is being executed as an immediate behavior.  Note
    /// that immediate behaviors can also be run normally, so this is not the same as checking
    /// the immediate trait on the behavior descriptor.
    inline bool IsImmediate() const;

    /// Determine if this behavior is blocked for any reason.
    inline bool IsBlocked() const;

    /// Determine if this behavior is allowed to block.
    inline bool CanBlock() const;

    /// Check if this behavior is currently blocked waiting for a reply message
    inline bool IsBlockedForReply() const;

    /// Block this behavior for a reply message
    /// @return True if this behavior successfully blocked, false if this behavior is NoBlock
    bool BlockForReply();

    /// Unblock this behavior once the reply message arrives
    /// @return True if this behavior was blocked for reply.
    bool ResumeFromReply();

    /// Check if this behavior is currently blocked due to a sleep call
    inline bool IsBlockedForSleep() const;

    /// Block this behavior for sleep
    /// @return True if this behavior successfully blocked, false if this behavior is NoBlock
    bool BlockForSleep();

    /// Unblock this behavior after a sleep interval passes
    /// @return True if this behavior was blocked for sleep.
    bool ResumeFromSleep();

    /// Check if this behavior is blocked due to a debugger break point
    inline bool IsBlockedForDebug() const;

    /// Block this behavior for debugging
    /// @return True if this behavior successfully blocked, false if this behavior is Immediate
    bool BlockForDebug();

    /// Unblock this behavior after a debug break point resumes
    /// @return True if this behavior was blocked for sleep.
    bool ResumeFromDebug();

    /// Block this behavior for Entity Creation
    /// @return True if this behavior successfully blocked, false if this behavior is Immediate
    bool BlockForEntityCreation();

    /// Resume this behavior after Entity creation completes.
    /// @return True if this behavior was blocked for entity creation.
    bool ResumeFromEntityCreation();

    /// Check if this behavior is blocked waiting on an entity creation to complete.
    bool IsBlockedForEntityCreation() const;

    /// When a pending behavior completes for any reason this is called.  This method simply
    /// calls Entity::FinishBehavior passing itself.
    /// @param success True if this behavior finished by successfully completing.
    void FinishBehavior(bool success);

protected:
    /**
        Determine the behavior call list for a given behavior.  If the behavior is an extends
        or reverse extends behavior then you may have to call multiple behaviors, otherwise
        the resulting list will simply contain the single initial behavior that was passed in.

        @note In some cases the input behavior will not be in the resulting call list.  This
        happens in cases where the provided behavior is an automatically generated placeholder
        for multiple extends-style mixed in behaviors.  In all cases only those behaviors
        returned by this method should be passed to InvokeBehavior.

        @param[in] i_pBehavior The specific behavior which is to be called
        @return True if the output list was successfully generated.
    */
    bool GetBehaviorCallList(const BehaviorDescriptor* i_pBehavior);

    /// Helper to execute behaviors from the m_behaviors list.
    bool RunBehaviors();

    /// Helper for generating memory leak reports
    static void LeakDump(void* pMem, char* o_buffer, unsigned int i_cchBuffer);

    /// List of the behaviors to run for this event.
    efd::list<BehaviorDescriptorPtr> m_behaviors;

    /// Pointer to the Entity to run the behavior
    efd::SmartPointer<Entity> m_spExecutingEntity;

    /// Pointer to the behavior's arguments.
    efd::ParameterListPtr m_spArgs;

    /// Entity to send the return value to.
    EntityID m_returnID;

    /// If set, the behavior in question is an entity lifecycle behavior such as OnCreate
    /// or OnDestroy.  When the behavior completes special handling is required.
    efd::UInt32 m_lifeCycleAdvanceOnCompletion;

    /// True if execution has begun on this event.  Execution has begun as soon as
    /// Entity::StartBehavior returns true.
    efd::Bool m_started : 1;
    /// True if any of the behaviors forming this event might block
    efd::Bool m_canBlock : 1;
    /// True if this behavior is the result of an immediate invokation.
    efd::Bool m_immediate : 1;

    /// True if the behavior is blocked (waiting for sleep to resume execution).
    efd::Bool m_blockedSleep : 1;
    /// True if the behavior is blocked (waiting for message reply to resume execution).
    efd::Bool m_blockedReply : 1;
    /// True if the behavior is blocked (in the Lua debugger).
    efd::Bool m_blockedDebug : 1;
    /// True if the behavior is blocked (waiting for an entity creation to complete).
    efd::Bool m_blockedEnityCreation : 1;

#ifdef EE_USE_BEHAVIOR_TIMING_METRICS
public:
    /// @name Performance Data
    /// Data used to gather statistics for executing and blocked time
    //@{
    /// The time the behavior has been running so far.
    efd::TimeType m_accumulatedTime;
    /// The time the behavior initially started execution.
    efd::TimeType m_startTime;
    /// The time the behavior most recently began execution.
    efd::TimeType m_eventTime;
    //@}
#endif
};

/// A SmartPointer to the PendingBehavior class
typedef efd::SmartPointer<PendingBehavior> PendingBehaviorPtr;


/// @name Behavior Timing Methods
//@{
inline void StartBehaviorTimer(PendingBehavior*);
inline void RestartBehaviorTimer(PendingBehavior*);
inline void StopBehaviorTimer(PendingBehavior*);
//@}


} // end namespace egf

#include <egf/PendingBehavior.inl>

#endif // EE_PendingBehavior_h
