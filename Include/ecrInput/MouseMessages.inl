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
// MouseMessage functions
//------------------------------------------------------------------------------------------------
inline ecrInput::MouseMessage::MouseMessage() :
    m_x(0),
    m_y(0)
{
}

//------------------------------------------------------------------------------------------------
inline efd::SInt32 ecrInput::MouseMessage::GetX() const
{
    return m_x;
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::MouseMessage::SetX(efd::SInt32 x)
{
    m_x = x;
}

//------------------------------------------------------------------------------------------------
inline efd::SInt32 ecrInput::MouseMessage::GetY() const
{
    return m_y;
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::MouseMessage::SetY(efd::SInt32 y)
{
    m_y = y;
}

//------------------------------------------------------------------------------------------------
// MouseMoveMessage functions
//------------------------------------------------------------------------------------------------
inline efd::SInt32 ecrInput::MouseMoveMessage::GetXDelta() const
{
    return m_xDelta;
}

//------------------------------------------------------------------------------------------------
inline efd::SInt32 ecrInput::MouseMoveMessage::GetYDelta() const
{
    return m_yDelta;
}

//------------------------------------------------------------------------------------------------
inline efd::SInt32 ecrInput::MouseMoveMessage::GetZDelta() const
{
    return m_zDelta;
}

//------------------------------------------------------------------------------------------------
// MouseDownMessage functions
//------------------------------------------------------------------------------------------------
inline ecrInput::MouseDownMessage::MouseButton ecrInput::MouseDownMessage::GetButton() const
{
    return m_button;
}

//------------------------------------------------------------------------------------------------
// MouseUpMessage functions
//------------------------------------------------------------------------------------------------
inline ecrInput::MouseUpMessage::MouseButton ecrInput::MouseUpMessage::GetButton() const
{
    return m_button;
}

//------------------------------------------------------------------------------------------------
