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

//-------------------------------------------------------------------------------------------------
// Construction / destruction
//-------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceEvent::InputServiceEvent(
    const efd::Category& msgCat,
    efd::UInt32 flags,
    efd::Float32 timeout)
    : m_msgCategory(msgCat)
    , m_flags(flags)
    , m_currentAction(0)
    , m_timeout(timeout)
    , m_comboStartTime(0.0f)
    , m_lastActionTime(0.0f)
{
}

//-------------------------------------------------------------------------------------------------
// Manipulating actions
//-------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceEvent::AddAction(ecrInput::InputServiceActionBase* pAction)
{
    if (!pAction)
        return false;

    m_actions.push_back(pAction);

    return true;
}

//-------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrInput::InputServiceEvent::GetActionCount()
{
    return (efd::UInt32)m_actions.size();
}
//-------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceActionBase* ecrInput::InputServiceEvent::GetActionAt(
    efd::UInt32 idx)
{
    if (idx >= m_actions.size())
        return NULL;

    return m_actions[idx];
}
//-------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceEvent::RemoveActionAt(efd::UInt32 idx)
{
    if (idx >= m_actions.size())
        return false;

    EE_DELETE m_actions[idx];

    m_actions.erase(m_actions.begin() + idx);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceEvent::RemoveAllActions()
{
    for (efd::UInt32 i = 0; i < m_actions.size(); i++)
        EE_DELETE m_actions[i];

    m_actions.clear();
}
//-------------------------------------------------------------------------------------------------
// Data accessors
//-------------------------------------------------------------------------------------------------
inline efd::Category ecrInput::InputServiceEvent::GetMsgCategory() const
{
    return m_msgCategory;
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrInput::InputServiceEvent::GetFlags() const
{
    return m_flags;
}
//-------------------------------------------------------------------------------------------------
inline efd::Float32 ecrInput::InputServiceEvent::GetTimeout() const
{
    return m_timeout;
}
//-------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceEvent::SetMsgCategory(const efd::Category& msgCat)
{
    m_msgCategory = msgCat;
}
//-------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceEvent::SetFlags(efd::UInt32 flags)
{
    m_flags = flags;
}
//-------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceEvent::SetTimeout(efd::Float32 timeout)
{
    m_timeout = timeout;
}

//-------------------------------------------------------------------------------------------------
