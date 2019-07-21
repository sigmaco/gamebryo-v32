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
inline void ecrInput::InputService::SetInstanceRef(efd::InstanceRef instanceRef)
{
    m_instanceRef = instanceRef;
}
//------------------------------------------------------------------------------------------------
inline void ecrInput::InputService::SetWindowRef(efd::WindowRef winRef)
{
    m_windowRef = winRef;
}
//------------------------------------------------------------------------------------------------
inline void ecrInput::InputService::SetExclusiveKeyboard(efd::Bool exclusive)
{
    m_exclusiveKeyboard = exclusive;
}
//------------------------------------------------------------------------------------------------
inline void ecrInput::InputService::SetExclusiveMouse(efd::Bool exclusive)
{
    m_exclusiveMouse = exclusive;
}
//------------------------------------------------------------------------------------------------
inline NiInputSystem* ecrInput::InputService::GetInputSystem()
{
    return m_spInput;
}

//------------------------------------------------------------------------------------------------
// Event management
//------------------------------------------------------------------------------------------------
inline efd::Category ecrInput::InputService::GetEventMsgCategory(
    const efd::utf8string& eventName) const
{
    ecrInput::InputServiceEvent* pEvent = FindEvent(eventName);

    if (!pEvent)
        return efd::kCAT_INVALID;

    return pEvent->GetMsgCategory();
}
//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputService::GetEventFlags(
    const efd::utf8string& eventName,
    efd::UInt32& eventFlags) const
{
    ecrInput::InputServiceEvent* pEvent = FindEvent(eventName);

    if (!pEvent)
        return false;

    eventFlags = pEvent->GetFlags();

    return true;
}
//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputService::GetEventTimeout(
    const efd::utf8string& eventName,
    efd::Float32& timeout) const
{
    ecrInput::InputServiceEvent* pEvent = FindEvent(eventName);

    if (!pEvent)
        return false;

    timeout = pEvent->GetTimeout();

    return true;
}
//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputService::SetEventFlags(
    const efd::utf8string& eventName,
    efd::UInt32 eventFlags)
{
    ecrInput::InputServiceEvent* pEvent = FindEvent(eventName);

    if (!pEvent)
        return false;

    pEvent->SetFlags(eventFlags);

    return true;
}
//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputService::SetEventTimeout(
    const efd::utf8string& eventName,
    efd::Float32 timeout)
{
    ecrInput::InputServiceEvent* pEvent = FindEvent(eventName);

    if (!pEvent)
        return false;

    pEvent->SetTimeout(timeout);

    return true;
}
//------------------------------------------------------------------------------------------------
// Action maps management
//------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceActionMap* ecrInput::InputService::CreateActionMap(
    const efd::utf8string& actionMapName)
{
    if (actionMapName.empty() || GetActionMap(actionMapName))
        return NULL;

    ecrInput::InputServiceActionMap* pActionMap =
        EE_NEW ecrInput::InputServiceActionMap(actionMapName, m_pMessageService);

    m_actionMaps.push_back(pActionMap);

    return pActionMap;
}
//------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrInput::InputService::GetActionMapCount() const
{
    return (efd::UInt32)m_actionMaps.size();
}
//------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceActionMap* ecrInput::InputService::GetActionMapAt(
    efd::UInt32 mapIdx) const
{
    if (mapIdx >= m_actionMaps.size())
        return NULL;

    return m_actionMaps[mapIdx];
}
//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputService::GetActionMapName(
    efd::UInt32 mapIdx,
    efd::utf8string& mapName) const
{
    if (mapIdx >= m_actionMaps.size())
        return false;

    ecrInput::InputServiceActionMap* pActionMap = m_actionMaps[mapIdx];
    mapName = pActionMap->GetName();

    return true;
}
//------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceActionMap* ecrInput::InputService::GetActionMap(
    const efd::utf8string& mapName) const
{
    for (efd::UInt32 i = 0; i < m_actionMaps.size(); i++)
    {
        if (m_actionMaps[i]->GetName() == mapName)
            return m_actionMaps[i];
    }

    return NULL;
}
//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputService::GetActiveActionMapName(
    efd::utf8string& actionMapName) const
{
    if (m_actionMapStack.empty())
        return false;

    ecrInput::InputServiceActionMap* pActionMap = m_actionMapStack.top();
    actionMapName = pActionMap->GetName();

    return true;
}
//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputService::RemoveActionMapAt(efd::UInt32 mapIdx)
{
    if (mapIdx >= m_actionMaps.size())
        return NULL;

    EE_DELETE m_actionMaps[mapIdx];
    m_actionMaps.erase(m_actionMaps.begin() + mapIdx);

    return true;
}
//------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceActionMap* ecrInput::InputService::GetActiveActionMap() const
{
    if (m_actionMapStack.empty())
        return NULL;

    return m_actionMapStack.top();
}
//------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceActionMap* ecrInput::InputService::GetGlobalActionMap()
{
    return &m_globalActionMap;
}
//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputService::PushActionMap(const efd::utf8string& actionMapName)
{
    ecrInput::InputServiceActionMap* pActionMap = GetActionMap(actionMapName);

    if (!pActionMap)
        return false;

    m_actionMapStack.push(pActionMap);

    return true;
}
//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputService::PushActionMap(efd::UInt32 mapIdx)
{
    if (mapIdx >= m_actionMaps.size())
        return false;

    m_actionMapStack.push(m_actionMaps[mapIdx]);

    return true;
}
//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputService::PopActionMap()
{
    if (m_actionMapStack.empty())
        return false;

    m_actionMapStack.pop();

    return true;
}
//------------------------------------------------------------------------------------------------
inline efd::Category ecrInput::InputService::MessageCategory()
{
    return ms_inputServiceCategory;
}
//------------------------------------------------------------------------------------------------
