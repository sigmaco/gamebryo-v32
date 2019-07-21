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
#ifndef EE_ScriptContext_h
#define EE_ScriptContext_h

#include <egf/egfLibType.h>
#include <efd/ServiceManager.h>
#include <egf/Entity.h>
#include <efd/StdContainers.h>



namespace egf
{


/**
    A class containing context data that is needed during scripted behavior calls.

    There is a global instance of this class which contains all the state needed during Behavior
    execution.  This state is setup by the Scheduler and the ISchedulerScripting instances
    whenever a script behavior is invoked or resumed.  Whenever the behavior makes calls back
    into C++ built-in APIs this context data is used to identify what Entity instance is running
    the behavior and which ServiceManager is managing this process.
*/
class EE_EGF_ENTRY ScriptContext
{
public:
    /// Constructor
    ScriptContext();

    /**
        Determine whether a behavior is currently active.  Other methods of this class assume that
        they will only be called when the context is active and may assert if called at other
        times.  This method allows you to safely check whether it is currently valid to call other
        methods on the context.

        @return bool True if the context is actively running a behavior.
    */
    inline bool ContextIsActive() const;

    /**
        Access the entity which is currently executing a behavior.

        @return Pointer to the current script entity, or NULL if no script behavior is running.
    */
    inline egf::Entity* GetScriptEntity() const;

    /**
        Access the entity which is currently executing a behavior and cast it to the requested
        class.

        @return Pointer to the current script entity cast to the specified type, or NULL if
            no script behavior is running or if the script entity is not of type T.
    */
    template< typename T >
    T* GetScriptEntityAs() const;

    /**
        Get the service manager that owns the scheduler that owns the entity that is running
        the current behavior.

        @return Pointer to the current ServiceManager.
    */
    inline const efd::ServiceManager* GetServiceManager() const;

    /**
        Sets the current ServiceManager.
        This method should only be called by the scheduler.

        @param[in] pMgr The ServiceManager which owns the scheduler running the script
    */
    inline void SetServiceManager(const efd::ServiceManager* pMgr);

    /**
        A convenience method to call ServiceManager::GetSystemServiceAs in one step.

        @return Pointer to the requested service, or NULL if the service is not found.
    */
    template< typename T >
    T* GetSystemServiceAs() const;

    /**
        Gets the ParameterList containing the input arguments to the current behavior.
        This method should only be called by the scheduler or related behavior execution code.

        @return ParameterList containing the arguments to the current script
    */
    inline efd::ParameterList* GetArgumentList() const;

    /**
        Determines if the currently running behavior is allowed to block.  If the behavior is
        NonBlocking then it cannot call blocking methods such as Sleep or SendEventAndWait.
        Attempts to call a blocking method from a non-blocking context will assert in debug
        and could lead to undefined results in release.

        @return True if the current context prohibits making blocking calls.
    */
    inline efd::Bool GetNonBlocking() const;

    /**
        Determines if the current script context is the result of an immediate behavior execution.
        Immediate behaviors called from within normal behaviors do not put the context into
        immediate mode, only when the bottom behavior in the stack is immediate is the stack
        considered immediate.

        @return True if the context is operating in Immediate Mode.
    */
    bool IsImmediateMode() const;

    /**
        Push the behavior that is about to execute or resume to the top of the context stack.
        @param pBehavior The PendingBehavior representing the waiting or blocked behavior that
            is about to begin or resume execution.
        @return True
    */
    inline bool PushBehavior(PendingBehavior* pBehavior);

    /**
        Pop the given behavior off the top of the context stack.
        @param pBehavior The PendingBehavior that has either completed or yielded.  This must
            be the top entity of the stack and is used only for error checking.
        @return True if the given PendingBehavior was removed from the top of the stack.
    */
    inline bool PopBehavior(PendingBehavior* pBehavior);

    /**
        Get the top PendingBehavior from the context stack.  This represents the behavior that
        is currently executing and stores all the state associated with that behavior.  Built-in
        APIs meant to be called from script use this state to determine the current context.

        @note This method must only be called during the execution of a behavior.  Calling at
        any other time will cause an assert and return NULL.

        @return The currently executing behavior
    */
    inline PendingBehavior* GetCurrentBehavior() const;

    /**
        Get the bottom PendingBehavior from the context stack. For "extends" style behaviors this
        represents the behavior that started the current stack of behaviors. For reverse-extends
        behaviors this is simply the lowest priority leaf. For non-extends behaviors this will be
        the same as GetCurrentBehavior.

        @note This method must only be called during the execution of a behavior.  Calling at
        any other time will cause an assert and return NULL.

        @return The behavior that started the current behavior stack
    */
    inline PendingBehavior* GetBottomBehavior() const;

    /**
        Get a string containing the name of the current running behavior and the name of the
        model that defines it.  Used when formatting error messages to show the user which
        script is causing the message.
    */
    const efd::utf8string GetCurrentBehaviorContextString() const;

    /// @cond EMERGENT_INTERNAL

    //@{
    static void _SDMInit();
    static void _SDMShutdown();
    //@}

    /// @endcond

protected:
    efd::SmartPointer<const efd::ServiceManager> m_spManager;
    efd::stack<egf::PendingBehaviorPtr>* m_pBehaviorStack;
    bool m_bImmediateStack;
};


/// Global instance of the ScriptContext used by built-in behavior APIs
extern EE_EGF_ENTRY ScriptContext g_bapiContext;

} // end namespace egf

#include <egf/ScriptContext.inl>

#endif // EE_ScriptContext_h
