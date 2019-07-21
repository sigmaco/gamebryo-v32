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
#ifndef LUA_RESUME_WAITER_TASK_H
#define LUA_RESUME_WAITER_TASK_H

#include <egfLua/LuaResumeCoroutineTask.h>

namespace egf
{

class LuaResumeWaiterTask : public LuaResumeCoroutineTask
{
public:
    LuaResumeWaiterTask(PendingBehavior* what);

    virtual bool SetResult(egf::Scheduler*, const egf::EventMessage* pMessage);

    virtual void DoTask(egf::Scheduler*);

    virtual int PrepareResumeArguments();

protected:
    /// The argument ParameterList from the response message that wakes me up
    efd::ParameterListPtr m_spReturnValue;
};

typedef efd::SmartPointer<LuaResumeWaiterTask> LuaResumeWaiterTaskPtr;

}

#endif // LUA_RESUME_WAITER_TASK_H
