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
#ifndef EE_MOUSEMESSAGES_H
#define EE_MOUSEMESSAGES_H

#include <efd/IMessage.h>

#include "ecrInputLibType.h"

#include <ecrInput/ecrInputMessageIDs.h>

namespace ecrInput
{

/**
    Abstract mouse message common across all mouse messages.

    Messages of this type are only sent when the ecrInput::InputService object is
    constructed with the sendSingleMessages parameter true (not the default).

    This class is not recommended for use outside of tools. Applications should only use it when
    working with Gamebryo tool services. Furthermore, the values returned by the GetX and GetY
    member functions are valid only inside a Gamebryo Toolbench plug-in or Toolbench core code,
    or in cases where application code explicitly sets the values. The (X, Y) values are not
    set by the Input Service.
*/
class EE_ECRINPUT_ENTRY MouseMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(MouseMessage, efd::kMSGID_MouseMove, efd::IMessage);
    /// @endcond

public:
    /// The mouse button generated this message.
    enum MouseButton
    {
        /// The left mouse button.
        MBUTTON_LEFT = 0,

        /// The right mouse button.
        MBUTTON_RIGHT,

        /// The middle mouse button.
        MBUTTON_MIDDLE
    };

    /// @name Construction and Destruction
    //@{
    /// Default Constructor.
    inline MouseMessage();
    //@}

    /// @name Message data getters and setters.
    //@{
    /**
        Get mouse X position.

        Valid only inside a Gamebryo Toolbench plug-in or when application
        level code has explicitly set the value.
    */
    inline efd::SInt32 GetX() const;

    /// Set mouse X position.
    inline void SetX(efd::SInt32 x);

    /**
        Get mouse Y position.

        Valid only inside a Gamebryo Toolbench plug-in or when application
        level code has explicitly set the value.
    */
    inline efd::SInt32 GetY() const;

    /// Set mouse Y position.
    inline void SetY(efd::SInt32 y);
    //@}

    /// @cond EMERGENT_INTERNAL

    /// Save message data to the stream.
    virtual void Serialize(efd::Archive& ar);

    /// @endcond

protected:
    efd::SInt32 m_x;
    efd::SInt32 m_y;
};


/**
    Message for reporting mouse move events.

    Stores the delta movement along each axis since the last message.

    Messages of this type are only sent when the ecrInput::InputService object is
    constructed with the sendSingleMessages parameter true (not the default).

    This class is not recommended for use outside of tools. Applications should only use it when
    working with Gamebryo tool services.
*/
class EE_ECRINPUT_ENTRY MouseMoveMessage : public MouseMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(MouseMoveMessage, efd::kMSGID_MouseMove, MouseMessage);
    /// @endcond

public:
    /// @name Construction and Destruction.
    //@{
    /// Default Constructor.
    MouseMoveMessage();

    /// Initializing Constructor.
    MouseMoveMessage(efd::SInt32 xDelta, efd::SInt32 yDelta, efd::SInt32 zDelta);

    /// Virtual Destructor.
    virtual ~MouseMoveMessage();
    //@}

    /// @cond EMERGENT_INTERNAL

    /// On demand class creation.
    static efd::IMessagePtr FactoryMethod();

    /// Save message data to the stream.
    virtual void Serialize(efd::Archive& ar);

    /// @endcond

    /// @name Message data getters and setters.
    //@{
    /// Return the change in position along the X axis.
    inline efd::SInt32 GetXDelta() const;

    /// Return the change in position along the Y axis.
    inline efd::SInt32 GetYDelta() const;

    /// Return the change in position along the Z axis.
    inline efd::SInt32 GetZDelta() const;
    //@}

protected:
    efd::SInt32 m_x;
    efd::SInt32 m_y;

    efd::SInt32 m_xDelta;
    efd::SInt32 m_yDelta;
    efd::SInt32 m_zDelta;
};
typedef efd::SmartPointer<MouseMoveMessage> MouseMoveMessagePtr;


/**
    Message for reporting mouse down events.

    Stores the mouse button that has been pressed.

    Messages of this type are only sent when the ecrInput::InputService object is
    constructed with the sendSingleMessages parameter true (not the default).

    This class is not recommended for use outside of tools. Applications should only use it when
    working with Gamebryo tool services.
*/
class EE_ECRINPUT_ENTRY MouseDownMessage : public MouseMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(MouseDownMessage, efd::kMSGID_MouseDown, MouseMessage);
    /// @endcond

public:
    /// @name Construction and Destruction.
    //@{
    MouseDownMessage();

    MouseDownMessage(MouseButton button);

    virtual ~MouseDownMessage();
    //@}

    /// @cond EMERGENT_INTERNAL

    /// On demand class creation.
    static efd::IMessagePtr FactoryMethod();

    /// Save message data to the stream.
    virtual void Serialize(efd::Archive& ar);

    /// @endcond

    /// Return the button that was pressed.
    inline MouseButton GetButton() const;

protected:
    MouseButton m_button;
};

typedef efd::SmartPointer<MouseDownMessage> MouseDownMessagePtr;


/**
    Message for reporting mouse up events.

    Stores the mouse button that has been released.

    Messages of this type are only sent when the ecrInput::InputService object is
    constructed with the sendSingleMessages parameter true (not the default).

    This class is not recommended for use outside of tools. Applications should only use it when
    working with Gamebryo tool services.
*/
class EE_ECRINPUT_ENTRY MouseUpMessage : public MouseMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(MouseUpMessage, efd::kMSGID_MouseUp, MouseMessage);
    /// @endcond

public:
    /// @name Construction and Destruction.
    //@{
    /// Default Constructor.
    MouseUpMessage();

    /// Initializing Constructor.
    MouseUpMessage(MouseButton button);

    /// Virtual Destructor.
    virtual ~MouseUpMessage();
    //@}

    /// @cond EMERGENT_INTERNAL

    /// On demand class creation.
    static efd::IMessagePtr FactoryMethod();

    /// Save message data to the stream.
    virtual void Serialize(efd::Archive& ar);

    /// @endcond

    /// Return the mouse button that was released.
    inline MouseButton GetButton() const;

protected:
    MouseButton m_button;
};

typedef efd::SmartPointer<MouseUpMessage> MouseUpMessagePtr;

} // end namespace ecrInput

EE_SPECIALIZE_ENUM(ecrInput::MouseMessage::MouseButton, efd::UInt8);

#include "MouseMessages.inl"

#endif // EE_MOUSEMESSAGES_H
