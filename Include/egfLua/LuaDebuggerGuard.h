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
#ifndef LUADEBUGGERGUARD_H
#define LUADEBUGGERGUARD_H

#ifndef EE_CONFIG_SHIPPING

#include "egfLuaPCH.h"
#include <egfLua/LuaBehaviorDebugger.h>

namespace egf
{
//-------------------------------------------------------------------------------------------------
// Guard class to limit Lua debugger hook usage and prevent reentrant Lua debugging.
class LuaDebuggerGuard
{
public:

    /// @cond EMERGENT_INTERNAL

    LuaDebuggerGuard(egf::LuaBehaviorDebugger* pDebugger, bool enableDebugging,
        lua_State* pLuaState) :
        m_spDebugger(pDebugger),
        m_pLuaState(pLuaState),
        m_initialCondition(false)
    {
        if (m_spDebugger)
        {
            m_initialCondition = m_spDebugger->BreakAllowed();

            m_spDebugger->UpdateDebugHooks(enableDebugging, m_pLuaState);
        }
    }

    ~LuaDebuggerGuard()
    {
        if (m_spDebugger)
        {
            m_spDebugger->UpdateDebugHooks(m_initialCondition, m_pLuaState);

            // If turning debugging back off, cancel step request
            if (m_initialCondition == false)
                m_spDebugger->StopStepping();
        }
    }

    /// @endcond

private:
    egf::LuaBehaviorDebuggerPtr m_spDebugger;
    lua_State* m_pLuaState;
    bool m_initialCondition;
};

} // namespace egf

#endif // EE_CONFIG_SHIPPING

#endif // LUADEBUGGERGUARD_H
