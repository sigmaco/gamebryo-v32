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

//------------------------------------------------------------------------------------------------
inline ScheduledTask::ScheduledTask(egf::EventID eventID, efd::TimeType when)
    : m_eventID(eventID)
    , m_executionTime(when)
{
}

//------------------------------------------------------------------------------------------------
inline ScheduledTask::~ScheduledTask()
{
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType ScheduledTask::GetExecuteTime() const
{
    return m_executionTime;
}

//------------------------------------------------------------------------------------------------
inline void ScheduledTask::SetExecuteTime(efd::TimeType when)
{
    m_executionTime = when;
}

//------------------------------------------------------------------------------------------------
inline egf::EventID ScheduledTask::GetEventID() const
{
    return m_eventID;
}

//------------------------------------------------------------------------------------------------
inline bool ScheduledTask::operator<(const ScheduledTask& rhs) const
{
    return m_executionTime >= rhs.m_executionTime;
}

//------------------------------------------------------------------------------------------------
} // end namespace egf
