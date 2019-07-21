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
// Constructors
//------------------------------------------------------------------------------------------------
inline ecrInput::InputActionMessage::InputActionMessage()
: m_eventName()
, m_appData(0)
, m_magnitude(0.0f)
, m_userData(NULL)
{
}

//------------------------------------------------------------------------------------------------
inline ecrInput::InputActionMessage::InputActionMessage(
    const efd::utf8string& eventName,
    efd::UInt32 appData,
    efd::Float32 magnitude,
    void* userData)
: m_eventName(eventName)
, m_appData(appData)
, m_magnitude(magnitude)
, m_userData(userData)
{
}

//------------------------------------------------------------------------------------------------
// Data accessors
//------------------------------------------------------------------------------------------------
inline const efd::utf8string& ecrInput::InputActionMessage::GetEventName() const
{
    return m_eventName;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrInput::InputActionMessage::GetAppData() const
{
    return m_appData;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 ecrInput::InputActionMessage::GetMagnitude() const
{
    return m_magnitude;
}

//------------------------------------------------------------------------------------------------
inline void* ecrInput::InputActionMessage::GetUserData() const
{
    return m_userData;
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::InputActionMessage::SetEventName(const efd::utf8string& eventName)
{
    m_eventName = eventName;
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::InputActionMessage::SetAppData(efd::UInt32 appData)
{
    m_appData = appData;
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::InputActionMessage::SetMagnitude(efd::Float32 magnitude)
{
    m_magnitude = magnitude;
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::InputActionMessage::SetUserData(void* userData)
{
    m_userData = userData;
}

//------------------------------------------------------------------------------------------------
