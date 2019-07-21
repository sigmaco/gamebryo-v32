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
#ifndef LUA_WAKE_SLEEPER_TASK_H
#define LUA_WAKE_SLEEPER_TASK_H

#include <egfLua/LuaResumeCoroutineTask.h>
#include <efd/TimeType.h>

namespace egf
{

/**
    Lua ScheduledTask implementations for blocked behaviors
*/
class LuaWakeSleeperTask : public LuaResumeCoroutineTask
{
public:
    LuaWakeSleeperTask(efd::TimeType when, PendingBehavior* what);

    virtual void DoTask(egf::Scheduler*);
};

typedef efd::SmartPointer<LuaWakeSleeperTask> LuaWakeSleeperTaskPtr;

} // namespace egf

#endif // LUA_WAKE_SLEEPER_TASK_H
