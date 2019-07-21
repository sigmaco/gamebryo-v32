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

#pragma once
#ifndef EE_INPUTSERVICEACTION_H
#define EE_INPUTSERVICEACTION_H

#include "InputServiceActionBase.h"


namespace ecrInput
{

/**
    This class processes a digital / analog button or single axis action.

    This action can be assigned to a digital button, analog button or single axis. Actions check
    for device modifiers if requested by flags; range is checked only for analog buttons or axes.

    The returned magnitude for digital buttons can be only 0 or 1. For analog buttons, magnitude
    is in the range [0..1]. For axes, the magnitude (value) can be in the range [-1..1].
    For mouse axes, the magnitude is the delta from the last position and it has no limits.
    If the action is not device-specific, all devices of same type are checked
    for this action.
*/
class EE_ECRINPUT_ENTRY InputServiceAction : public InputServiceActionBase
{
public:
    /// @name Construction and Destruction.
    //@{
    /// Default constructor.
    inline InputServiceAction();

    /**
        Initializing Constructor.
        @param semantic Semantic associated with this action, from NiAction::Semantic.
        @param actionFlags An ORed combination of ecrInput::InputService::ActionFlags.
        @param appData User-defined data.
        @param deviceID Device on which this action should be checked. Typically, deviceID is
            always 0 for keyboard and mouse, and may be 0 to NiInputSystem::MAX_GAMEPADS for
            GamePads.
        @param modifiers Action modifiers. These should be an ORed combination of modifiers
            specific to the device type, taken from one of NiInputKeyboard::Modifiers or
            NiInputMouse::Modifiers (there are no modifiers for GamePad input).
        @param minRange Minimum range of magnitude / axis value.
        @param maxRange Maximum range of magnitude / axis value.
    */
    inline InputServiceAction(
        efd::UInt32 semantic,
        efd::UInt32 actionFlags,
        efd::UInt32 appData = 0,
        efd::UInt32 deviceID = 0,
        efd::UInt32 modifiers = 0,
        efd::Float32 minRange = -1.0f,
        efd::Float32 maxRange = 1.0f);

    /// Destructor
    virtual ~InputServiceAction();
    //@}

    /// @cond EMERGENT_INTERNAL

    /**
        Checks state of monitored control on physical device(s), checks modifiers and range if
        needed. Returns true if action triggered and fills in magnitude and coordinates.
    */
    virtual efd::Bool ProcessInput(
        InputService* pInput,
        efd::UInt32& appData,
        efd::Float32& magnitude,
        efd::Float32& x,
        efd::Float32& y,
        efd::Float32& z);

    /// Returns a unique hash value for this action.
    virtual efd::UInt32 GetHash() const;

    /// Insert this class into the XML tree.  Returns true if successful.
    virtual efd::Bool SaveXml(efd::TiXmlElement* pElement);

    /// Load member data from the given XML tree.  Returns true if successful.
    virtual efd::Bool LoadXml(efd::TiXmlElement* pElement);

    /// @endcond

    /// @name Action data getters and setters.
    //@{
    /// Get action semantic.
    inline efd::UInt32 GetSemantic() const;

    // Set action semantic.
    inline void SetSemantic(efd::UInt32 semantic);

    /// Get minimum magnitude value.
    inline efd::Float32 GetMinRange() const;

    // Set minimum magnitude value.
    inline void SetMinRange(efd::Float32 minRange);

    /// Get maximum magnitude value.
    inline efd::Float32 GetMaxRange() const;

    /// Set maximum magnitude value.
    inline void SetMaxRange(efd::Float32 maxRange);

    /// Check if provided value is in range of this action.
    inline efd::Bool IsInRange(efd::Float32 value) const;
    //@}

    /// Load string semantic -> semantic value translation map.
    static void LoadTranslationMap();

    /// Unload string semantic -> semantic value translation map.
    static void UnloadTranslationMap();

protected:
    inline efd::Bool IsKeyboardAction() const;
    inline efd::Bool IsMouseAction() const;
    inline efd::Bool IsGamePadAction() const;
    inline efd::Bool IsButton() const;
    inline efd::Bool IsAxis() const;

    efd::Bool ProcessKeyboardAction(
        NiInputKeyboard* pKeyboard,
        efd::Float32& magnitude) const;
    efd::Bool ProcessMouseAction(
        NiInputMouse* pMouse,
        efd::Float32& magnitude) const;
    efd::Bool ProcessGamePadAction(
        NiInputGamePad* pGamePad,
        efd::Float32& magnitude) const;
    efd::Bool CheckDigitalAction(
        efd::Bool wasPressed,
        efd::Bool wasReleased,
        efd::Bool isDown,
        efd::Float32& magnitude) const;
    efd::Bool CheckAnalogAction(
        efd::Float32 magnitude,
        efd::Float32 lastMagnitude) const;

    efd::UInt32 m_semantic;
    efd::UInt32 m_control;
    efd::Float32 m_minRange;
    efd::Float32 m_maxRange;

    /// Translation map of string semantic names to their values.
    static efd::map<efd::utf8string, efd::UInt32> ms_semanticMap;
};

} // namespace

#include "InputServiceAction.inl"

#endif // EE_INPUTSERVICEACTION_H
