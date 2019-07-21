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
#ifndef LUABEHAVIORDEBUGGER_H
#define LUABEHAVIORDEBUGGER_H

// LuaBehaviorDebugger is compiled out of Shipping configurations
#ifndef EE_CONFIG_SHIPPING

#include <efd/MessageHandlerBase.h>
#include <egf/ScheduledTask.h>
#include <egf/egfClassIDs.h>
#include <egfLua/bapiLua.h>
#include <egf/IDebuggerCallback.h>

struct lua_Debug;
struct lua_State;

namespace efd
{
    class MessageService;
    class StreamMessage;
}

namespace egf
{
class Scheduler;

/**
    This singleton implements the engine-side logic of a remote behavior debugger for Lua scripted
    behaviors.  It uses a language-independent communication protocol, receiving tool requests and
    sending responses via the MessageService.  The Lua Debug API is used to hook the execution of
    behavior scripts and allow interactive debugging.
*/
class EE_EGF_LUA_ENTRY LuaBehaviorDebugger
    : public efd::IBase
    , public egf::IDebuggerCallback
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(LuaBehaviorDebugger, efd::kCLASSID_LuaBehaviorDebugger, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

public:

    /// @name Construction and Destruction
    //@{
    /// default constructor.
    LuaBehaviorDebugger();

    /// virtual destructor allows for subclasses.
    virtual ~LuaBehaviorDebugger();
    //@}

    /**
        Accessor method for the debugger object.

        @return Pointer to the debugger.
    */
    static LuaBehaviorDebugger* Instance();

    /**
        Initialization routine to enable interactive debugger messaging.

        @param pServiceMgr The ServiceManager for this process.
        @return True on successful startup.
    */
    bool Initialize(efd::ServiceManager* pServiceMgr);

    /**
        Shuts the behavior debugger down (unregisters from it's messages)
    */
    void Shutdown();

    /**
        Entry point for the Lua debug hook for function call events.
    */
    void OnCall();

    /**
        Entry point for the Lua debug hook for function return events.
    */
    void OnReturn();

    /**
        Entry point for the Lua debug hook for execution line events.

        @param pLuaState The active Lua state object.
        @param pLuaDebug The active Lua debug object.
    */
    void OnLine(lua_State* pLuaState, lua_Debug* pLuaDebug);

    /**
        Determine if an active debugging session is in progress.

        @return True if a debugging session is in progress.
    */
    bool ActiveSession();

    /**
        Determine if breakpoints are enabled.

        @return True if breakpoints are enabled.
    */
    bool BreakAllowed();

    /**
        Sets or clears Lua debug hooks to allow interactive script debugging.

        @param enable True to set Lua debug hooks, False to clear them.
        @param pLuaState Lua state for the coroutine being debugged.
    */
    void UpdateDebugHooks(bool enable, lua_State* pLuaState);

    /**
        Cancels a pending step request when a behavior finishes or sleeps.
    */
    void StopStepping();

    /**
        Attempts to break into execution.
    */
    void ForceBreak();

    /**
        Function type for a userdata interpreter.

        This function attempts to create a human-readable string suitable for display in the
        debugger from the userdata value at position pos. Returns true if this interpreter
        generated a user-friendly string. Returns false if the value at pos is not a userdata
        value, or this interpreter is unable to construct a string for the userdata.

        The interpreter function is responsible for verify the value at pos is userdata and
        this userdata is of the appropriate type.

        @param L lua_State to examine.
        @param pos Position on the Lua stack.
        @param value Resulting user-friendly string.
        @return true if the conversion was successful, false otherwise.
    */
    typedef bool (UserDataInterpreter)(lua_State* L, int pos, efd::utf8string& value);

    /**
        Registers a Userdata interpreter that can generate a human-readable string for
        userdata values of 'type'.

        @param type Typename supported by this interpreter.
        @param interpreter pointer to the UserDataInterpreter function for this type.
    */
    void RegisterUserDataInterpreter(const char* type, UserDataInterpreter* interpreter);

    /**
        Handle incoming script commands coming in from the message service.

        @param pMessage The message delivered from the MessageService.
        @param targetChannel The category the message was delivered to.
    */
    void HandleScriptDebuggerCommand(
        const efd::StreamMessage* pMessage,
        efd::Category targetChannel);

    /**
        Handle the message that is sent before the world gets reset.

        @param pMessage The message delivered from the MessageService.
        @param targetChannel The category the message was delivered to.
    */
    void HandleWorldResetBegin(
        const efd::IMessage* pMessage,
        efd::Category targetChannel);

    /**
        Handle the message that is sent after the world has been reset.

        @param pMessage The message delivered from the MessageService.
        @param targetChannel The category the message was delivered to.
    */
    void HandleWorldResetEnd(
        const efd::IMessage* pMessage,
        efd::Category targetChannel);

    /// @cond EMERGENT_INTERNAL

    //@{
    static void _SDMInit();
    static void _SDMShutdown();
    //@}

    /// @endcond
private:
    void ResetState();

    bool PropertyHasHandler(const Entity* pEntity, const efd::utf8string& propertyName);

    bool AtBreak(
        const char* pFile,
        efd::UInt32 line,
        lua_State* pLuaState,
        lua_Debug* pLuaDebug);

    bool EvaluateCondition(
        const efd::utf8string& condition,
        lua_State* pLuaState,
        lua_Debug* pLuaDebug);

    void ExecuteStatement(
        lua_State* pLuaState,
        lua_Debug* pLuaDebug);

    void SendCallStack(lua_State* pLuaState);

    void SendLocals(lua_State* pLuaState, lua_Debug* pLuaDebug);

    void SendWatches(lua_State* pLuaState, lua_Debug* pLuaDebug);
    void SendAutoEntityProperties(lua_State* pLuaState, lua_Debug* pLuaDebug);
    void SendWatchEntityProperties(lua_State* pLuaState, lua_Debug* pLuaDebug);
    void SendEntityProperties(lua_State* pLuaState, lua_Debug* pLuaDebug, Entity* pEntity,
        efd::utf8string& response);

    void InterpretLuaData(
        lua_State* i_pLuaState,
        efd::utf8string& o_type,
        efd::utf8string& o_value,
        efd::UInt32 i_depth = 0);

    void InterpretEntityData(
        lua_State* pLuaState,
        const Entity* pEntity,
        const efd::utf8string& propertyName,
        const efd::utf8string& key,
        efd::utf8string& type,
        efd::utf8string& value);

    /// Tell the scheduler that we want a debugger callback in which we will resume the current
    /// behavior.
    void ResumeExecution();

    /// The debugger callback that we register with the scheduler when we want to resume the
    /// current behavior.
    void DoDebuggerCallback();

    /// Get the name of the file at the current execution unit.
    efd::utf8string GetSourcePath(const char* luaDebugSource);

    /// Mapping of userdata 'type' to UserDataInterpreter.
    typedef efd::map<efd::utf8string, UserDataInterpreter*> UserDataInterpreters;
    UserDataInterpreters m_userDataInterpreters;

    enum ExecutionMode
    {
        EXECMODE_GO,
        EXECMODE_STEP_INTO,
        EXECMODE_STEP_OVER,
        EXECMODE_STEP_OUT,
        EXECMODE_RUN_TO,
        EXECMODE_BREAK,
        EXECMODE_EXECUTE
    };

    // True when the remote debugger is attached
    bool m_activeSession;

    // True when the Lua debug hook is allowed to break
    bool m_breakAllowed;

    // Pending command
    ExecutionMode m_executionMode;

    // State of execution
    bool m_atBreak;
    efd::SInt32 m_stackLevel;
    efd::SInt32 m_targetStackLevel;

    // True while the world is being reset.
    bool m_worldResetting;

    // True while the world is being reset _if_ a debugging session was in progress before.
    bool m_restartSessionAfterWorldReset;

    // Breakpoints indexed by file, then line
    efd::map< efd::utf8string, efd::map<efd::UInt32, efd::utf8string> > m_breakpoints;

    // Watch expressions to evaluate at each break
    efd::vector<efd::utf8string> m_watches;

    // Entity ID for the watched entity
    efd::UInt64 m_watchEntityID;

    // Target for RunToCursor
    efd::utf8string m_runToFile;
    efd::UInt32 m_runToLine;

    // Target for Execute
    efd::utf8string m_executeStatement;

    // Sender of the execute request
    efd::utf8string m_executeSender;

    // Ignore first line on resume
    efd::utf8string m_breakFile;

    efd::ServiceManager* m_pServiceManager;
    efd::MessageService* m_pMessageService;
    egf::Scheduler* m_pScheduler;

    // The task that is being debugged
    ScheduledTaskPtr m_spTaskBeingDebugged;

    static efd::SmartPointer<LuaBehaviorDebugger> ms_spInstance;

    /// Handlers for various built-in userdata types.
    template<typename T>
    struct TemplatedInterpreter
    {
        static bool Interpret(lua_State* L, int pos, efd::utf8string& value)
        {
            if (bapiLua::LuaTraits<T>::IsType(L, pos))
            {
                // Matching type. Have Lua convert it into a string.
                lua_pushvalue(L, -1);
                if (!luaL_callmeta(L, -1, "__tostring"))
                {
                    lua_pop(L, -1);
                    return false;
                }

                const char* v = lua_tostring(L, -1);
                value = v ? v : efd::utf8string::NullString();

                lua_pop(L, 2);
                return true;
            }
            return false;
        }
    };

};

typedef efd::SmartPointer<LuaBehaviorDebugger> LuaBehaviorDebuggerPtr;

} // namespace egf

#include "LuaBehaviorDebugger.inl"

#endif // EE_CONFIG_SHIPPING

#endif // LUABEHAVIORDEBUGGER_H
