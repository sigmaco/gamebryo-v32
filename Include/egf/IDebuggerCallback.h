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
#ifndef IDEBUGGERCALLBACK_H
#define IDEBUGGERCALLBACK_H

/// Class for the debugger callback method used by egf::Scheduler::SetDebuggerCallback
namespace egf
{

class IDebuggerCallback
{
public:
    /// Method called once per egf::Scheduler::OnTick when a debugger callback is registered via
    /// egf::Scheduler::SetDebuggerCallback.
    virtual void DoDebuggerCallback() = 0;

    virtual ~IDebuggerCallback(){}
};

}

#endif // IDEBUGGERCALLBACK_H
