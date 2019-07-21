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
inline ecrInput::InputServiceAction::InputServiceAction() :
    m_semantic(0),
    m_control(0),
    m_minRange(0.0f),
    m_maxRange(1.0f)
{
}

//------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceAction::InputServiceAction(
    efd::UInt32 semantic,
    efd::UInt32 flags,
    efd::UInt32 appData,
    efd::UInt32 deviceID,
    efd::UInt32 modifiers,
    efd::Float32 minRange,
    efd::Float32 maxRange) :
    ecrInput::InputServiceActionBase(flags, appData, deviceID, modifiers),
    m_minRange(minRange),
    m_maxRange(maxRange)
{
    SetSemantic(semantic);
}

//------------------------------------------------------------------------------------------------
// Methods for checking type of an action
//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceAction::IsKeyboardAction() const
{
    return (m_semantic & NiAction::KEY_MASK) ? true : false;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceAction::IsMouseAction() const
{
    return (m_semantic & NiAction::MOUSE_MASK) ? true : false;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceAction::IsGamePadAction() const
{
    return (m_semantic & NiAction::GAMEPAD_MASK) ? true : false;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceAction::IsButton() const
{
    // Note: This code relies on the fact that NiAction::GP_BUTTON_LUP and
    // NiAction::MOUSE_BUTTON_LEFT are effectively masks for their respective ranges of
    // the enum space.  If either constant is changed, this code will break.
    // DT29853 Add proper masks to NiAction.h and use them instead.
    return ((m_semantic & NiAction::GP_BUTTON_LUP) == NiAction::GP_BUTTON_LUP) ||
        ((m_semantic & NiAction::MOUSE_BUTTON_LEFT) == NiAction::MOUSE_BUTTON_LEFT ||
        (m_semantic & NiAction::KEY_MASK));
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceAction::IsAxis() const
{
    return !IsButton();
}

//------------------------------------------------------------------------------------------------
// Data accessors - querying
//------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrInput::InputServiceAction::GetSemantic() const
{
    return m_semantic;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 ecrInput::InputServiceAction::GetMinRange() const
{
    return m_minRange;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 ecrInput::InputServiceAction::GetMaxRange() const
{
    return m_maxRange;
}

//------------------------------------------------------------------------------------------------
// Data accessors - setting
//------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceAction::SetSemantic(efd::UInt32 semantic)
{
    m_semantic = semantic;
    m_control = NiAction::SemanticToDeviceControl(semantic);
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceAction::SetMinRange(efd::Float32 minRange)
{
    m_minRange = minRange;
}

//------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceAction::SetMaxRange(efd::Float32 maxRange)
{
    m_maxRange = maxRange;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceAction::IsInRange(efd::Float32 value) const
{
    // Check if provided value is in range of this action.
    if (value >= m_minRange && value <= m_maxRange)
        return true;

    return false;
}

//------------------------------------------------------------------------------------------------
