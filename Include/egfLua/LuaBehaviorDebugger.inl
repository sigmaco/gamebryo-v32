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

namespace egf
{

//-------------------------------------------------------------------------------------------------
inline LuaBehaviorDebugger* LuaBehaviorDebugger::Instance()
{
    EE_ASSERT(ms_spInstance != NULL);

    return ms_spInstance;
}

//-------------------------------------------------------------------------------------------------
inline void LuaBehaviorDebugger::OnCall()
{
    ++m_stackLevel;
}

//-------------------------------------------------------------------------------------------------
inline void LuaBehaviorDebugger::OnReturn()
{
    --m_stackLevel;
}

//-------------------------------------------------------------------------------------------------
inline bool LuaBehaviorDebugger::ActiveSession()
{
    return m_activeSession;
}

//-------------------------------------------------------------------------------------------------
inline bool LuaBehaviorDebugger::BreakAllowed()
{
    return m_breakAllowed;
}

//-------------------------------------------------------------------------------------------------
inline void LuaBehaviorDebugger::StopStepping()
{
    if (m_atBreak)
        return;

    // Handle stepping out of a behavior
    if (m_executionMode == EXECMODE_STEP_INTO ||
        m_executionMode == EXECMODE_STEP_OVER ||
        m_executionMode == EXECMODE_STEP_OUT)
    {
        m_executionMode = EXECMODE_GO;
    }

    m_stackLevel = 0;
}

//-------------------------------------------------------------------------------------------------
inline void LuaBehaviorDebugger::ForceBreak()
{
    m_executionMode = EXECMODE_BREAK;
}

//-----------------------------------------------------------------------------------------------
inline void LuaBehaviorDebugger::RegisterUserDataInterpreter(
    const char* type, 
    UserDataInterpreter* interpreter)
{
    m_userDataInterpreters[type] = interpreter;
}

} // namespace egf
