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
#ifndef EE_KEYBOARDMESSAGES_H
#define EE_KEYBOARDMESSAGES_H

#include <efd/IMessage.h>
#include <NiInputKeyboard.h>

#include "ecrInputLibType.h"

#include <ecrInput/ecrInputMessageIDs.h>

namespace ecrInput
{

/**
    Message for reporting key down events.

    Stores the key that has been pressed.

    Messages of this type are only sent when the ecrInput::InputService object is
    constructed with the sendSingleMessages parameter true (not the default).

    This class is not recommended for use outside of tools. Applications should only use it when
    working with Gamebryo tool services.
*/
class EE_ECRINPUT_ENTRY KeyDownMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(KeyDownMessage, efd::kMSGID_KeyDown, efd::IMessage);
    /// @endcond

public:
    /// @name Construction and Destruction.
    //@{
    /// Default Constructor.
    KeyDownMessage();

    /// Initializing Constructor.
    KeyDownMessage(NiInputKeyboard::KeyCode key);

    /// Virtual Destructor.
    virtual ~KeyDownMessage();
    //@}

    /// @cond EMERGENT_INTERNAL

    /// On demand class creation.
    static efd::IMessagePtr FactoryMethod();

    /// Save message data to the stream.
    virtual void Serialize(efd::Archive& ar);
    /// @endcond

    /// Get the key that has been pressed.
    inline NiInputKeyboard::KeyCode GetKey() const;

protected:
    NiInputKeyboard::KeyCode m_key;
};

typedef efd::SmartPointer<KeyDownMessage> KeyDownMessagePtr;


/**
    Message for reporting key up events.

    Stores the key that has been released.

    Messages of this type are only sent when the ecrInput::InputService object is
    constructed with the sendSingleMessages parameter true (not the default).

    This class is not recommended for use outside of tools. Applications should only use it when
    working with Gamebryo tool services.
*/
class EE_ECRINPUT_ENTRY KeyUpMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(KeyUpMessage, efd::kMSGID_KeyUp, efd::IMessage);
    /// @endcond

public:
    /// @name Construction and Destruction.
    //@{
    /// Default Constructor.
    KeyUpMessage();

    /// Initializing Constructor.
    KeyUpMessage(NiInputKeyboard::KeyCode key);

    /// Virtual Destructor.
    virtual ~KeyUpMessage();
    //@}

    /// @cond EMERGENT_INTERNAL

    /// On demand class creation.
    static efd::IMessagePtr FactoryMethod();

    /// Save message data to the stream.
    virtual void Serialize(efd::Archive& ar);

    /// @endcond

    /// Get the key that has been released.
    inline NiInputKeyboard::KeyCode GetKey() const;

protected:
    NiInputKeyboard::KeyCode m_key;
};

typedef efd::SmartPointer<KeyUpMessage> KeyUpMessagePtr;

} // end namespace ecrInput

EE_SPECIALIZE_ENUM(NiInputKeyboard::KeyCode, efd::UInt32);

#include "KeyboardMessages.inl"

#endif // EE_KEYBOARDMESSAGES_H
