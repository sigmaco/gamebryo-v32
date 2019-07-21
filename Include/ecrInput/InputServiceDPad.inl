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
// Constructors
//--------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceDPad::InputServiceDPad() :
    m_lastX(0),
    m_lastY(0),
    m_padType(ecrInput::InputService::INVALID_DPAD),
    m_upSemantic(0),
    m_downSemantic(0),
    m_leftSemantic(0),
    m_rightSemantic(0),
    m_upControl(0),
    m_downControl(0),
    m_leftControl(0),
    m_rightControl(0)
{
}
//--------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceDPad::InputServiceDPad(
    ecrInput::InputService::DPadType pad,
    efd::UInt32 flags,
    efd::UInt32 appData,
    efd::UInt32 deviceID,
    efd::UInt32 modifiers,
    efd::UInt32 upSemantic,
    efd::UInt32 downSemantic,
    efd::UInt32 leftSemantic,
    efd::UInt32 rightSemantic) :
    ecrInput::InputServiceActionBase(flags, appData, deviceID, modifiers),
    m_lastX(0),
    m_lastY(0)
{
    SetType(pad);
    if (pad == ecrInput::InputService::CUSTOM_DPAD)
    {
        SetCustomSemantic(upSemantic, downSemantic, leftSemantic, rightSemantic);
    }
}
//--------------------------------------------------------------------------------------------------
// Methods for checking type of an action
//--------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceDPad::IsKeyboardDPad() const
{
    if (m_padType == InputService::CUSTOM_DPAD)
    {
        // Check one of custom semantics
        if (m_upSemantic & NiAction::KEY_MASK)
            return true;

        return false;
    }

    if (m_padType == InputService::GP_DPAD_L || m_padType == InputService::GP_DPAD_R)
    {
        return false;
    }

    return true;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceDPad::IsGamePadDPad() const
{
    return !IsKeyboardDPad();
}
//--------------------------------------------------------------------------------------------------
// Data accessors - querying
//--------------------------------------------------------------------------------------------------
inline ecrInput::InputService::DPadType ecrInput::InputServiceDPad::GetType() const
{
    return m_padType;
}
//--------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceDPad::GetCustomSemantic(
    efd::UInt32& upSemantic,
    efd::UInt32& downSemantic,
    efd::UInt32& leftSemantic,
    efd::UInt32& rightSemantic) const
{
    upSemantic = m_upSemantic;
    downSemantic = m_downSemantic;
    leftSemantic = m_leftSemantic;
    rightSemantic = m_rightSemantic;
}
//--------------------------------------------------------------------------------------------------
// Data accessors - setting
//--------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceDPad::SetCustomSemantic(
    efd::UInt32 upSemantic,
    efd::UInt32 downSemantic,
    efd::UInt32 leftSemantic,
    efd::UInt32 rightSemantic)
{
    m_upSemantic = upSemantic;
    m_downSemantic = downSemantic;
    m_leftSemantic = leftSemantic;
    m_rightSemantic = rightSemantic;

    m_upControl = NiAction::SemanticToDeviceControl(m_upSemantic);
    m_downControl = NiAction::SemanticToDeviceControl(m_downSemantic);
    m_leftControl = NiAction::SemanticToDeviceControl(m_leftSemantic);
    m_rightControl = NiAction::SemanticToDeviceControl(m_rightSemantic);
}
//--------------------------------------------------------------------------------------------------
