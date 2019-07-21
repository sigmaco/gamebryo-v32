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
#ifndef EE_INPUTSERVICEACTIONBASE_H
#define EE_INPUTSERVICEACTIONBASE_H

#include <efd/IMessage.h>
#include <efd/TinyXML.h>

#include <NiInputSystem.h>
#include "ecrInputLibType.h"

#define EE_NIS_MAX_MAGNITUDE 255
#define EE_NIS_AXIS_RANGE 127


namespace ecrInput
{

// Forward declaration:
class InputService;

/// Type used to store string mappings for various flag-style attributes
typedef efd::map<efd::utf8string, efd::UInt32> FlagMap;

/// Helper used when reading actionmap files to convert strings into enum values.  The value is
/// expected to match exactly one entry in the FlagMap.
EE_ECRINPUT_ENTRY efd::Bool ReadEnumFromAttribute(
    efd::TiXmlElement* i_pElement,
    const char* i_attrib,
    const FlagMap& i_map,
    efd::UInt32& o_value);

/// Helper used when writing actionmap files to convert flag values into string.  The value is
/// expected to match exactly one entry in the FlagMap.
EE_ECRINPUT_ENTRY void WriteEnumToAttribute(
    efd::TiXmlElement* pElement,
    const char* attrib,
    const FlagMap& map,
    efd::UInt32 value);

/// Helper used when reading actionmap files to convert strings into flag values.  Multiple
/// flags can be combined using the '|' character.
EE_ECRINPUT_ENTRY efd::Bool ReadFlagsFromAttribute(
    efd::TiXmlElement* i_pElement,
    const char* i_attrib,
    const FlagMap& i_map,
    efd::UInt32& o_flags);

/// Helper used when writing actionmap files to convert flag values into string.  Multiple
/// flags can be combined using the '|' character.
EE_ECRINPUT_ENTRY void WriteFlagsToAttribute(
    efd::TiXmlElement* pElement,
    const char* attrib,
    const FlagMap& map,
    efd::UInt32 flags);


/**
    This class is abstract; it defines the interface for Input Service actions.

    The main purpose of this class is to define an interface for actions and to provide common
    functionality such as checking action device types and assigning device ids, modifiers and
    action flags.
*/
class EE_ECRINPUT_ENTRY InputServiceActionBase : public efd::MemObject
{
public:
    /// @name Construction and Destruction.
    //@{
    /// Default constructor.
    inline InputServiceActionBase();

    /**
        Initializing constructor.

        @param actionFlags Flags that define when the action is triggered, is it a device
            specific action, and whether and how it checks modifiers and range. These flags
            must be an ORed combination of ecrInput::InputService::ActionFlags.
        @param appData User-defined data.
        @param deviceID The device on which this action occurs. Typically, deviceID is
            always 0 for keyboard and mouse, and may be 0 to NiInputSystem::MAX_GAMEPADS for
            GamePads.
        @param deviceModifiers The modifiers that must be matched for the action to execute.
            These should be an ORed combination of modifiers specific to the device type,
            taken from one of NiInputKeyboard::Modifiers or NiInputMouse::Modifiers (there are
            no modifiers for GamePad input).
    */
    inline InputServiceActionBase(
        efd::UInt32 actionFlags,
        efd::UInt32 appData = 0,
        efd::UInt32 deviceID = 0,
        efd::UInt32 deviceModifiers = 0);

    /// Virtual destructor.
    virtual ~InputServiceActionBase();
    //@}

    /// @cond EMERGENT_INTERNAL

    /// Checks state of monitored physical device(s), checks modifiers and range if needed.
    /// If action is triggered, it returns true and fills in magnitude and coordinates.
    virtual efd::Bool ProcessInput(
        InputService* pInput,
        efd::UInt32& appData,
        efd::Float32& magnitude,
        efd::Float32& x,
        efd::Float32& y,
        efd::Float32& z) = 0;

    /// Returns a unique hash for this action.
    inline virtual efd::UInt32 GetHash() const;

    /// Insert this class into the XML tree.  Returns true if successful.
    virtual efd::Bool SaveXml(efd::TiXmlElement* pElement);

    /// Load member data from the given XML tree.  Returns true if successful.
    virtual efd::Bool LoadXml(efd::TiXmlElement* pElement);

    /// @endcond

    /// @name Action data getters and setters.
    //@{
    /// Get action flags.
    ///
    /// The return value is an ORed combination of flags from ecrInput::InputService::ActionFlags.
    inline efd::UInt32 GetFlags() const;

    /// Set action flags.
    ///
    /// The parameter is an ORed combination of flags from ecrInput::InputService::ActionFlags.
    inline void SetFlags(efd::UInt32 flags);

    // Get user-defined data.
    inline efd::UInt32 GetAppData() const;

    /// Set user-defined data.
    inline void SetAppData(efd::UInt32 appData);

    /**
        Get ID of the device on which the action is checked.

        This makes sense only if the ecrInput::InputService::ActionFlags::DEVICE_SPECIFIC flag is
        set. See NiInputSystem::DeviceIDPort, NiInputSystem::DeviceIDSlot and
        NiInputSystem::GetDeviceDescription for information on interpreting this value.
    */
    inline efd::UInt32 GetDeviceID() const;

    /**
        Set ID of the device on which the action is checked.

        This makes sense only if the ecrInput::InputService::ActionFlags::DEVICE_SPECIFIC flag is
        set. Typically, deviceID is always 0 for keyboard and mouse, and may be 0 to
        NiInputSystem::MAX_GAMEPADS for GamePads.
    */
    inline void SetDeviceID(efd::UInt32 deviceID);

    /**
        Get device modifiers.

        This makes sense only if the ecrInput::InputService::ActionFlags::USE_MODIFIERS flag is
        set. The return value is an ORed combination of
        NiInputKeyboard::Modifiers or NiInputMouse::Modifiers, depending on the device type.
    */
    inline efd::UInt32 GetModifiers() const;

    /**
        Set device modifiers.

        This makes sense only if the ecrInput::InputService::ActionFlags::USE_MODIFIERS flag is
        set. The parameter is an ORed combination of
        NiInputKeyboard::Modifiers or NiInputMouse::Modifiers, depending on the device type.
    */
    inline void SetModifiers(efd::UInt32 modifiers);
    //@}

    /// Load string -> value translation maps for actions and modifiers.
    static void LoadTranslationMap();

    /// Unload translation maps for actions and modifiers.
    static void UnloadTranslationMap();

protected:
    /// Compare modifiers of current action with keyboard state.
    inline efd::Bool CheckKeyboardModifiers(NiInputSystemPtr spInput) const;

    /// Compare modifiers of current action with mouse state.
    inline efd::Bool CheckMouseModifiers(NiInputSystemPtr spInput) const;

    /// Compare modifiers of current action with game pad state, using device with given ID.
    inline efd::Bool CheckGamePadModifiers(NiInputSystemPtr spInput, efd::UInt32 deviceID) const;

    /// Convert axis position from NiInput-returned int to float.
    inline efd::Float32 ConvertAxisValue(efd::SInt32 value);

    /// Convert analog button magnitude from NiInput-returned int to float.
    inline efd::Float32 ConvertABtnValue(efd::SInt32 value);

    efd::UInt32 m_flags;
    efd::UInt32 m_appData;
    efd::UInt32 m_deviceID;
    efd::UInt32 m_modifiers;

    /// Translation map of string flags to flag values.
    static FlagMap ms_actionFlagsMap;

    /// Translation map of string modifiers to modifier values.
    static FlagMap ms_modifierMap;
};

} // end namespace ecrInput

#include "InputServiceActionBase.inl"

#endif // EE_INPUTSERVICEACTIONBASE_H
