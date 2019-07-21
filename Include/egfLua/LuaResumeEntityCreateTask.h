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
#ifndef LUA_RESUME_ENTITY_CREATE_TASK_H
#define LUA_RESUME_ENTITY_CREATE_TASK_H

#include <egfLua/LuaResumeCoroutineTask.h>

namespace egf
{

class LuaResumeEntityCreateTask : public LuaResumeCoroutineTask
{
public:
    LuaResumeEntityCreateTask(PendingBehavior* what);

    virtual void SetEntityFactoryResponse(const EntityFactoryResponse* pResponse);

    virtual void DoTask(egf::Scheduler*);

    virtual int PrepareResumeArguments();

protected:
    egf::EntityID m_entityID;
};

typedef efd::SmartPointer<LuaResumeEntityCreateTask> LuaResumeEntityCreateTaskPtr;

}

#endif // LUA_RESUME_ENTITY_CREATE_TASK_H