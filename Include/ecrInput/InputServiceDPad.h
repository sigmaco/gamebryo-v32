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
#ifndef EE_INPUTSERVICEDPAD_H
#define EE_INPUTSERVICEDPAD_H

#include "InputServiceActionBase.h"
#include "InputService.h"


namespace ecrInput
{

/**
    This class processes a directional pad action.

    This action can be assigned to game pad left or right D-Pad, emulated on keyboard using 3
    presets (arrow keys, numpad arrows, wsad) or can be formed from any 4 buttons specified as
    custom semantics. All 4 custom buttons must be on the same device. The D-Pad is always
    device-specific, so device id must be properly set. If requested by flags, the action
    will check the device modifiers.

    The returned magnitude is always 1.0. X and Y specify a point on unit circle and Z is always
    0.0.
*/
class EE_ECRINPUT_ENTRY InputServiceDPad : public InputServiceActionBase
{
public:
    /// @name Construction and Destruction.
    //@{
    /// Default Constructor.
    inline InputServiceDPad();

    /**
        Initializing Constructor.
        @param pad Pad type, from ecrInput::InputService::DPadType.
        @param flags An ORed combination of ecrInput::InputService::ActionFlags.
        @param appData User-specified data.
        @param deviceID Device on which this action should be checked. Typically, deviceID is
            always 0 for keyboard and mouse, and may be 0 to NiInputSystem::MAX_GAMEPADS for
            GamePads.
        @param modifiers Modifiers for this action. These should be an ORed combination of
            modifiers specific to the device type, taken from one of NiInputKeyboard::Modifiers or
            NiInputMouse::Modifiers (there are no modifiers for GamePad input).
        @param upSemantic Semantic of up button for custom D-Pad.
        @param downSemantic Semantic of down button for custom D-Pad.
        @param leftSemantic Semantic of left button for custom D-Pad.
        @param rightSemantic Semantic of right button for custom D-Pad.
    */
    inline InputServiceDPad(
        InputService::DPadType pad,
        efd::UInt32 flags,
        efd::UInt32 appData = 0,
        efd::UInt32 deviceID = 0,
        efd::UInt32 modifiers = 0,
        efd::UInt32 upSemantic = 0,
        efd::UInt32 downSemantic = 0,
        efd::UInt32 leftSemantic = 0,
        efd::UInt32 rightSemantic = 0);

    /// Virtual Destructor.
    virtual ~InputServiceDPad();
    //@}

    /// @cond EMERGENT_INTERNAL

    /// Processes input and checks modifiers and range. If an action
    /// was triggered, it returns true and fills in magnitude and coordinates.
    virtual efd::Bool ProcessInput(
        InputService* pInput,
        efd::UInt32& appData,
        efd::Float32& magnitude,
        efd::Float32& x,
        efd::Float32& y,
        efd::Float32& z);

    /// Returns a unqiue hash for this action.
    virtual efd::UInt32 GetHash() const;

    /// Save action to XML.
    virtual efd::Bool SaveXml(efd::TiXmlElement* pElement);

    /// Load action from XML.
    virtual efd::Bool LoadXml(efd::TiXmlElement* pElement);

    /// @endcond

    /// @name Action data getters and setters.
    //@{
    /// Returns the type of D-Pad.
    inline InputService::DPadType GetType() const;

    /// Sets the type of D-Pad.
    void SetType(InputService::DPadType pad);

    /// Returns the D-Pad custom semantics.
    inline void GetCustomSemantic(
        efd::UInt32& upSemantic,
        efd::UInt32& downSemantic,
        efd::UInt32& leftSemantic,
        efd::UInt32& rightSemantic) const;

    /// Sets the D-Pad custom semantics.
    inline void SetCustomSemantic(
        efd::UInt32 upSemantic,
        efd::UInt32 downSemantic,
        efd::UInt32 leftSemantic,
        efd::UInt32 rightSemantic);
    //@}

    static void LoadTranslationMap();
    static void UnloadTranslationMap();


protected:
    /// Returns true if this action is keyboard D-Pad.
    inline efd::Bool IsKeyboardDPad() const;

    /// Returns true if this action is game pad D-Pad.
    inline efd::Bool IsGamePadDPad() const;

    // D-Pad data
    efd::Float32 m_lastX;
    efd::Float32 m_lastY;

    // Data of a DPad
    InputService::DPadType m_padType;
    efd::UInt32 m_upSemantic;
    efd::UInt32 m_downSemantic;
    efd::UInt32 m_leftSemantic;
    efd::UInt32 m_rightSemantic;
    efd::UInt32 m_upControl;
    efd::UInt32 m_downControl;
    efd::UInt32 m_leftControl;
    efd::UInt32 m_rightControl;

    static FlagMap ms_padTypePad;
};

} // end namespace ecrInput

#include "InputServiceDPad.inl"

#endif // EE_INPUTSERVICEDPAD_H
