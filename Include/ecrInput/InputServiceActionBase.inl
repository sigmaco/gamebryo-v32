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
inline ecrInput::InputServiceActionBase::InputServiceActionBase() :
    m_flags(0),
    m_appData(0),
    m_deviceID(0),
    m_modifiers(0)

{
}
//--------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceActionBase::InputServiceActionBase(
    efd::UInt32 actionFlags,
    efd::UInt32 appData,
    efd::UInt32 deviceID,
    efd::UInt32 deviceModifiers) :
    m_flags(actionFlags),
    m_appData(appData),
    m_deviceID(deviceID),
    m_modifiers(deviceModifiers)
{
}
//--------------------------------------------------------------------------------------------------
// Data accessors
//--------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrInput::InputServiceActionBase::GetFlags() const
{
    return m_flags;
}
//--------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrInput::InputServiceActionBase::GetAppData() const
{
    return m_appData;
}
//--------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrInput::InputServiceActionBase::GetDeviceID() const
{
    return m_deviceID;
}
//--------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrInput::InputServiceActionBase::GetModifiers() const
{
    return m_modifiers;
}
//--------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrInput::InputServiceActionBase::GetHash() const
{
    // High 16 bits are flags (8 bit), device id (4 bit) and semantics device
    // type (4 bits). Low 16 bits are action-specific - semantics, type, etc.
    efd::UInt32 uiHash = (m_flags & 0xff) << 16;

    uiHash ^= m_deviceID << 24;

    return uiHash;
}
//--------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceActionBase::SetFlags(efd::UInt32 flags)
{
    m_flags = flags;
}
//--------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceActionBase::SetAppData(efd::UInt32 appData)
{
    m_appData = appData;
}
//--------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceActionBase::SetDeviceID(efd::UInt32 deviceID)
{
    m_deviceID = deviceID;
}
//--------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceActionBase::SetModifiers(efd::UInt32 modifiers)
{
    m_modifiers = modifiers;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceActionBase::CheckKeyboardModifiers(
    NiInputSystemPtr spInput) const
{
    NiInputKeyboard* pkKeyboard = spInput->GetKeyboard();

    if (!pkKeyboard)
        return false;

    if (m_modifiers != pkKeyboard->GetModifiers())
        return false;

    return true;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceActionBase::CheckMouseModifiers(
    NiInputSystemPtr spInput) const
{
    NiInputMouse* pkMouse = spInput->GetMouse();

    if (!pkMouse)
        return false;

    if (m_modifiers != pkMouse->GetModifiers())
        return false;

    return true;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool ecrInput::InputServiceActionBase::CheckGamePadModifiers(
    NiInputSystemPtr spInput,
    efd::UInt32 deviceID) const
{
    NiInputGamePad* pkGamePad = spInput->GetGamePad(deviceID);

    if (!pkGamePad)
        return false;

    if (m_modifiers != pkGamePad->GetModifiers())
        return false;


    return true;
}
//--------------------------------------------------------------------------------------------------
inline efd::Float32 ecrInput::InputServiceActionBase::ConvertAxisValue(efd::SInt32 value)
{
    return (efd::Float32)value / (efd::Float32)(EE_NIS_AXIS_RANGE);
}
//--------------------------------------------------------------------------------------------------
inline efd::Float32 ecrInput::InputServiceActionBase::ConvertABtnValue(efd::SInt32 value)
{
    return (efd::Float32)value / (efd::Float32)(EE_NIS_MAX_MAGNITUDE);
}
//--------------------------------------------------------------------------------------------------