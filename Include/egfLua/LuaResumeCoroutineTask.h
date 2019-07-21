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
#ifndef EE_LuaResumeCoroutineTask_h
#define EE_LuaResumeCoroutineTask_h

#include <egf/PendingBehavior.h>
#include <egf/ScheduledTask.h>
#include <egfLua/egfLuaLibType.h>
#include <egf/egfClassIDs.h>

struct lua_State;

namespace egf
{
    class Scheduler;

    /**
        This task makes it easy to implement Lua tasks that yield the current coroutine.  Derive
        a task from this class and override the DoTask method to perform additional work.
    */
    class LuaResumeCoroutineTask : public egf::ScheduledTask
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(LuaResumeCoroutineTask,
                           efd::kCLASSID_LuaResumeCoroutineTask,
                           egf::ScheduledTask);
        /// @endcond
    public:
        /**
            Constructor
            @param when The time at which this task should execute.  This time will be used if
                you pass this task to Scheduler::QueueTask.  If you manually resume the Lua
                coroutine by directly calling DoTask then this time has no effect.
            @param what The PendingBehavior for a blocking Lua behavior that is being yielded.
        */
        LuaResumeCoroutineTask(efd::TimeType when, egf::PendingBehavior* what);

        /// This override of ScheduledTask::AbortTask will release any Lua references held by
        /// this task thus allowing them to be garbage collected.
        /// @see ScheduledTask::AbortTask
        virtual void AbortTask(egf::Scheduler*);

        /**
            Call this from within a Lua built-in method running in a coroutine.  It will cache
            information about the current coroutine and hold a reference that will prevent the
            coroutine from being garbage collected.  It will then yield the current coroutine
            by calling lua_yield.

            @note The result returned from this method must then be returned from the C++ Lua
            function which resulted in calling this method.  Failure to return this value will
            corrupt the Lua state.

            @param L The Lua state for the running coroutine
            @return The integer value that must be returned from the current Lua function.
                This value will be negative if we yielded successfully or zero on error.
        */
        int CacheAndYeildCoroutine(lua_State *L);

    protected:

        /**
            Method to resume a blocked coroutine.  Typically you would derive a new task from
            this class and call ResumeCoroutine at some point during the DoTask method.
        */
        void ResumeCoroutine();

        /**
            If you wish to return arguments during the resume call then you must override this
            method and push the arguments onto the m_luaThread stack.  You must return the
            number of arguments pushed onto the stack.  The default implementation simply
            returns zero.
            @return The number of arguments pushed onto the coroutine's stack
        */
        virtual int PrepareResumeArguments();

        // The behavior that is to be yielded and resumed.  Must a CanBlock Lua behavior.
        egf::PendingBehaviorPtr m_spBehavior;

        // The Lua thread that represents the current co-routine
        lua_State* m_luaThread;

        // An index to the Registry where we store the current co-routine.  This prevents the
        // Lua thread from being garbage collected by holding a reference to the thread.
        int m_coroutineReference;
    };

} // end namespace egf

#endif // EE_LuaResumeCoroutineTask_h
