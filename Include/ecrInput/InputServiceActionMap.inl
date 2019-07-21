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
inline ecrInput::InputServiceActionMap::InputServiceActionMap(
    const efd::utf8string& name,
    efd::MessageService* pMessageService) :
    m_name(name),
    m_pMessageService(pMessageService)
{
}

//--------------------------------------------------------------------------------------------------
inline const efd::utf8string& ecrInput::InputServiceActionMap::GetName() const
{
    return m_name;
}

//--------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceActionMap::SetName(const efd::utf8string& name)
{
    m_name = name;
}

//--------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceEvent* ecrInput::InputServiceActionMap::AddEvent(
    const efd::utf8string& name,
    const efd::Category& msgCat,
    efd::UInt32 flags,
    efd::Float32 timeout)
{
    // Check for empty name
    if (name.empty())
        return NULL;

    ecrInput::InputServiceEvent* pEvent =
        EE_NEW ecrInput::InputServiceEvent(msgCat, flags, timeout);

    if (!pEvent)
        return NULL;

    AddEvent(name, pEvent);

    return pEvent;
}

//--------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceActionMap::AddEvent(
    const efd::utf8string& name,
    ecrInput::InputServiceEvent* pEvent)
{
    if (!pEvent)
        return;

    // If event with same name exists, remove it to prevent memory leaks
    RemoveEvent(name);

    m_events[name] = pEvent;
}

//--------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceEvent* ecrInput::InputServiceActionMap::FindEvent(
    const efd::utf8string& name) const
{
    efd::map<efd::utf8string, ecrInput::InputServiceEvent*>::const_iterator itor;
    itor = m_events.find(name);

    if (itor == m_events.end())
        return NULL;

    return (*itor).second;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrInput::InputServiceActionMap::GetEventCount() const
{
    return (efd::UInt32)m_events.size();
}

//--------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceActionMap::Iterator
    ecrInput::InputServiceActionMap::GetFirstEvent() const
{
    return m_events.begin();
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceActionMap::GetNextEvent(
    ecrInput::InputServiceActionMap::Iterator& itor,
    efd::utf8string& name,
    ecrInput::InputServiceEvent*& pEvent) const
{
    if (itor == m_events.end())
        return false;

    name = (*itor).first;
    pEvent = (*itor).second;
    ++itor;

    return true;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceActionMap::RemoveEvent(const efd::utf8string& name)
{
    efd::map<efd::utf8string, ecrInput::InputServiceEvent*>::iterator itor;
    itor = m_events.find(name);

    if (itor == m_events.end())
        return false;

    // Delete event instance
    EE_DELETE (*itor).second;

    m_events.erase(itor);

    return true;
}

//--------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceActionMap::DeleteAllEvents()
{
    efd::map<efd::utf8string, ecrInput::InputServiceEvent*>::iterator itor =
        m_events.begin();

    for (itor = m_events.begin(); itor != m_events.end(); ++itor)
    {
        EE_DELETE itor->second;
    }

    m_events.clear();
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceActionMap::SetMessageService(
    efd::MessageService* messageService)
{
    m_pMessageService = messageService;
}
//------------------------------------------------------------------------------------------------
