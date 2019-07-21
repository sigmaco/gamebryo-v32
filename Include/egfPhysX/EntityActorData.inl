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


//--------------------------------------------------------------------------------------------------
inline const egf::EntityPtr egfPhysX::EntityActorData::GetEntity() const
{
    return m_spEntity;
}
//--------------------------------------------------------------------------------------------------
inline NxActor* egfPhysX::EntityActorData::GetActor() const
{
    return m_pActor;
}
//--------------------------------------------------------------------------------------------------
inline void egfPhysX::EntityActorData::SetActor(NxActor* pActor)
{
    // Clear this object from any existing actor's user data
    if (m_pActor)
        m_pActor->userData = 0;

    // If we are changing the actor, then we need to clean up the shape that it used.
    if (m_pUpdateShape)
    {
        EE_EXTERNAL_DELETE m_pUpdateShape;
        m_pUpdateShape = NULL;
    }

    if (pActor)
        pActor->userData = this;
    m_pActor = pActor;
}
//--------------------------------------------------------------------------------------------------
inline const efd::Float32& egfPhysX::EntityActorData::GetSceneScale() const
{
    return m_sceneScale;
}
//--------------------------------------------------------------------------------------------------
inline void egfPhysX::EntityActorData::SetSceneScale(const efd::Float32& scale)
{
    m_sceneScale = scale;
}
//--------------------------------------------------------------------------------------------------
inline const efd::utf8string& egfPhysX::EntityActorData::GetSceneName() const
{
    return m_sceneName;
}
//--------------------------------------------------------------------------------------------------
inline efd::TimeType egfPhysX::EntityActorData::GetNextStayEventTime() const
{
    return m_nextStayEventTime;
}
//--------------------------------------------------------------------------------------------------
inline void egfPhysX::EntityActorData::SetNextStayEventTime(const efd::TimeType nextTime)
{
    m_nextStayEventTime = nextTime;
}
//--------------------------------------------------------------------------------------------------
inline efd::Float32 egfPhysX::EntityActorData::GetStayEventInterval() const
{
    return m_repeatInterval;
}
//--------------------------------------------------------------------------------------------------
inline void egfPhysX::EntityActorData::SetStayEventInterval(const efd::Float32 stayInterval)
{
    m_repeatInterval = stayInterval;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::EntityActorData::IsTrigger() const
{
    return m_isTrigger;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::EntityActorData::SetTriggerOwnsActor(const bool isOwned)
{
    m_updateFlags =
        efd::BitUtils::SetBitsOnOrOff<efd::UInt16>(m_updateFlags, TRIGGER_OWNED, isOwned);
}
//--------------------------------------------------------------------------------------------------
inline bool egfPhysX::EntityActorData::GetTriggerOwnsActor() const
{
    return efd::BitUtils::AnyBitsAreSet<efd::UInt16>(m_updateFlags, TRIGGER_OWNED);
}
//--------------------------------------------------------------------------------------------------
inline void egfPhysX::EntityActorData::MarkForRelease()
{
    m_updateFlags = efd::BitUtils::SetBits<efd::UInt16>(m_updateFlags, UPDATE_RELEASE);
    if (m_pActor)
    {
        m_pActor->userData = NULL;
    }
}
//--------------------------------------------------------------------------------------------------
inline void egfPhysX::EntityActorData::ClearForRelease()
{
    m_updateFlags = efd::BitUtils::ClearBits<efd::UInt16>(m_updateFlags, UPDATE_RELEASE);
    if (m_pActor)
    {
        m_pActor->userData = this;
    }
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::EntityActorData::IsMarkedForRelease() const
{
    return efd::BitUtils::AnyBitsAreSet<efd::UInt16>(m_updateFlags, UPDATE_RELEASE);
}
//--------------------------------------------------------------------------------------------------
inline void egfPhysX::EntityActorData::MarkForRemoval()
{
    m_updateFlags = efd::BitUtils::SetBits<efd::UInt16>(m_updateFlags, UPDATE_REMOVED);
    if (m_pActor)
    {
        m_pActor->userData = NULL;
    }
}
//--------------------------------------------------------------------------------------------------
inline void egfPhysX::EntityActorData::ClearForRemoval()
{
    m_updateFlags = efd::BitUtils::ClearBits<efd::UInt16>(m_updateFlags, UPDATE_REMOVED);
    if (m_pActor)
    {
        m_pActor->userData = this;
    }
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::EntityActorData::IsMarkedForRemoval() const
{
    return efd::BitUtils::AnyBitsAreSet<efd::UInt16>(m_updateFlags, UPDATE_REMOVED);
}
//--------------------------------------------------------------------------------------------------
