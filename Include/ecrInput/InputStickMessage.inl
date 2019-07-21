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
inline ecrInput::InputStickMessage::InputStickMessage()
: m_x(0.0f)
, m_y(0.0f)
, m_z(0.0f)
{
}

//------------------------------------------------------------------------------------------------
inline ecrInput::InputStickMessage::InputStickMessage(
    const efd::utf8string& eventName,
    efd::UInt32 appData,
    efd::Float32 magnitude,
    efd::Float32 x,
    efd::Float32 y,
    efd::Float32 z,
    void* userData)
: ecrInput::InputActionMessage(eventName, appData, magnitude, userData)
, m_x(x)
, m_y(y)
, m_z(z)
{
}

//------------------------------------------------------------------------------------------------
// Data accessors
//------------------------------------------------------------------------------------------------
inline efd::Float32 ecrInput::InputStickMessage::GetX() const
{
    return m_x;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 ecrInput::InputStickMessage::GetY() const
{
    return m_y;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 ecrInput::InputStickMessage::GetZ() const
{
    return m_z;
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::InputStickMessage::SetX(efd::Float32 x)
{
    m_x = x;
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::InputStickMessage::SetY(efd::Float32 y)
{
    m_y = y;
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::InputStickMessage::SetZ(efd::Float32 z)
{
    m_z = z;
}

//------------------------------------------------------------------------------------------------
