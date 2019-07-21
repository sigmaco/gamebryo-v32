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

#include <egf/egfBaseIDs.h>

namespace egf
{

//------------------------------------------------------------------------------------------------
inline Entity* Scheduler::LookupEntityByDataFileID(const efd::ID128& id) const
{
    return m_spEntityManager->LookupEntityByDataFileID(id);
}

//------------------------------------------------------------------------------------------------
inline const efd::Category& Scheduler::GetSchedulerCat() const
{
    return m_simOwnedCat;
}

//------------------------------------------------------------------------------------------------
inline efd::Category Scheduler::GetAllSchedulersCat()
{
    return m_spMessageService->GetServicePublicCategory(Scheduler::CLASS_ID);
}

//------------------------------------------------------------------------------------------------
inline efd::Category Scheduler::GetSchedulersAnnouceCat()
{
    return m_spMessageService->GetServicePublicCategory(efd::kBASEID_SchedulerAnnouce);
}

//------------------------------------------------------------------------------------------------
inline bool Scheduler::IsPaused() const
{
    return m_pGameClock->IsPaused();
}

//------------------------------------------------------------------------------------------------
inline bool Scheduler::StartSchedulerPaused()
{
    // This is a count to handle the possibility that multiple parties may wish to ensure the
    // scheduler starts paused. For every person requesting the scheduler start paused there should
    // be a person who will resume the scheduler so we may need to pause the clock multiple times.
    ++m_startPaused;
    return m_pGameClock ? false : true;
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType Scheduler::GetGameTime() const
{
    return m_pGameClock->GetCurrentTime();
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType Scheduler::GetLastGameTimeDelta() const
{
    return m_pGameClock->GetLastDelta();
}

//------------------------------------------------------------------------------------------------
inline void Scheduler::SetDebuggerCallback(egf::IDebuggerCallback* callback)
{
    m_debuggerCallback = callback;
}

} // end namespace egf
