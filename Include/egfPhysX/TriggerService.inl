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
inline egfPhysX::EntityActorData*
    egfPhysX::TriggerService::GetEntityActorData(const egf::EntityID& entityID) const
{
    efd::map<egf::EntityID, EntityActorDataPtr>::const_iterator iter =
        m_entitiesToActorData.find(entityID);
    if (iter == m_entitiesToActorData.end())
    {
        // We do not know about this entity.
        return NULL;
    }

    return iter->second;
}

//------------------------------------------------------------------------------------------------
inline void egfPhysX::TriggerService::AddToPendingList(EntityActorDataPtr spData)
{
    EntityActorList::iterator iter = m_pendingActorList.find(spData);
    if (iter == m_pendingActorList.end())
    {
        m_pendingActorList.push_back(spData);
    }
}

//------------------------------------------------------------------------------------------------
inline egfPhysX::TriggerService::TriggerCallbackHandler::TriggerData&
    egfPhysX::TriggerService::TriggerCallbackHandler::TriggerData::operator=(
    const egfPhysX::TriggerService::TriggerCallbackHandler::TriggerData& other)
{
    m_spTriggerActorData = other.m_spTriggerActorData;
    m_spOtherActorData = other.m_spOtherActorData;
    m_status = other.m_status;
    m_otherShapeFlagsMatchStatus = other.m_otherShapeFlagsMatchStatus;
    return *this;
}

//------------------------------------------------------------------------------------------------
inline bool
    egfPhysX::TriggerService::TriggerCallbackHandler::TriggerData::ShapeFlagsMatchStatus(
    const NxTriggerFlag& status, const NxShape& shape)
{
    if ((status & NX_TRIGGER_ON_ENTER) && shape.getFlag(NX_TRIGGER_ON_ENTER))
        return true;
    if ((status & NX_TRIGGER_ON_LEAVE) && shape.getFlag(NX_TRIGGER_ON_LEAVE))
        return true;
    if ((status & NX_TRIGGER_ON_STAY) && shape.getFlag(NX_TRIGGER_ON_STAY))
        return true;

    return false;
}

//------------------------------------------------------------------------------------------------
