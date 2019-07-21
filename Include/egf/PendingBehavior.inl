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


//------------------------------------------------------------------------------------------------
inline egf::Entity* egf::PendingBehavior::GetScriptEntity() const
{
    EE_ASSERT(m_spExecutingEntity);
    return m_spExecutingEntity;
}

//------------------------------------------------------------------------------------------------
inline const egf::BehaviorDescriptor* egf::PendingBehavior::GetBehaviorDescriptor() const
{
    EE_ASSERT(!m_behaviors.empty());
    return m_behaviors.front();
}

//------------------------------------------------------------------------------------------------
inline efd::ParameterList* egf::PendingBehavior::GetArgumentList() const
{
    return m_spArgs.data();
}

//------------------------------------------------------------------------------------------------
inline egf::EntityID egf::PendingBehavior::GetReturnEntityID() const
{
    return m_returnID;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 egf::PendingBehavior::GetLifecycleToken() const
{
    return m_lifeCycleAdvanceOnCompletion;
}

//------------------------------------------------------------------------------------------------
inline void egf::PendingBehavior::SetLifecycleToken(efd::UInt32 lifecycle)
{
    m_lifeCycleAdvanceOnCompletion = lifecycle;
}

//------------------------------------------------------------------------------------------------
inline bool egf::PendingBehavior::Started() const
{
    return m_started;
}

//------------------------------------------------------------------------------------------------
inline bool egf::PendingBehavior::IsImmediate() const
{
    return m_immediate;
}

//------------------------------------------------------------------------------------------------
inline bool egf::PendingBehavior::IsBlocked() const
{
    return m_blockedSleep || m_blockedReply || m_blockedDebug || m_blockedEnityCreation;
}

//------------------------------------------------------------------------------------------------
inline bool egf::PendingBehavior::CanBlock() const
{
    return m_canBlock;
}

//------------------------------------------------------------------------------------------------
inline bool egf::PendingBehavior::IsBlockedForReply() const
{
    return m_blockedReply;
}

//------------------------------------------------------------------------------------------------
inline bool egf::PendingBehavior::IsBlockedForSleep() const
{
    return m_blockedSleep;
}

//------------------------------------------------------------------------------------------------
inline bool egf::PendingBehavior::IsBlockedForDebug() const
{
    return m_blockedDebug;
}

//------------------------------------------------------------------------------------------------
inline bool egf::PendingBehavior::IsBlockedForEntityCreation() const
{
    return m_blockedEnityCreation;
}

//------------------------------------------------------------------------------------------------
// Timing methods
//------------------------------------------------------------------------------------------------
#if defined(EE_USE_BEHAVIOR_TIMING_METRICS)

//------------------------------------------------------------------------------------------------
inline void egf::StartBehaviorTimer(egf::PendingBehavior* ppb)
{
    efd::TimeType now = efd::GetCurrentTimeInSec();
    ppb->m_startTime = now;
    ppb->m_eventTime = now;
    ppb->m_accumulatedTime = 0.0;
}

//------------------------------------------------------------------------------------------------
inline void egf::RestartBehaviorTimer(egf::PendingBehavior* ppb)
{
    efd::TimeType now = efd::GetCurrentTimeInSec();
    ppb->m_eventTime = now;
}

//------------------------------------------------------------------------------------------------
inline void egf::StopBehaviorTimer(egf::PendingBehavior* ppb)
{
    // Only stop if we were started in the first place:
    if (ppb->m_startTime != 0.0)
    {
        efd::TimeType now = efd::GetCurrentTimeInSec();
        efd::TimeType delta = now - ppb->m_eventTime;
        ppb->m_accumulatedTime += delta;
    }
}

#else

//------------------------------------------------------------------------------------------------
inline void egf::StartBehaviorTimer(egf::PendingBehavior*) {}
inline void egf::RestartBehaviorTimer(egf::PendingBehavior*) {}
inline void egf::StopBehaviorTimer(egf::PendingBehavior*) {}

#endif // defined(EE_USE_BEHAVIOR_TIMING_METRICS)

