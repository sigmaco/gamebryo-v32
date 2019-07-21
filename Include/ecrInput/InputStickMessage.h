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
#ifndef EE_INPUTSTICKMESSAGE_H
#define EE_INPUTSTICKMESSAGE_H

#include "InputActionMessage.h"

#include <ecrInput/ecrInputMessageIDs.h>
#include <ecr/ecrClassIDs.h>

namespace ecrInput
{

/**
    This class represents a message that contains a magnitude and 3 coordinates.

    It is used for reporting mouse moves (in this case it contains deltas by axes) or for reporting
    the position of D-Pads or sticks.
*/
class EE_ECRINPUT_ENTRY InputStickMessage : public InputActionMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(InputStickMessage, efd::kCLASSID_InputStickMessage, InputActionMessage);
    /// @endcond

public:
    /// @name Construction and Destruction.
    //@{
    /// Default constructor. Initializes all data to zero.
    inline InputStickMessage();

    /// Initializing constructor.
    /**
        Initializing constructor.
        @param eventName The name of the event.
        @param appData User-defined data.
        @param magnitude Magnitude of the event (0..1).
        @param x Delta along the X-axis.
        @param y Delta along the Y-axis.
        @param z Delta along the Z-axis.
        @param userData optional userData to attach to the message.
    */
    inline InputStickMessage(
        const efd::utf8string& eventName,
        efd::UInt32 appData,
        efd::Float32 magnitude,
        efd::Float32 x,
        efd::Float32 y,
        efd::Float32 z,
        void* userData = NULL);
    //@}

    /// On demand class creation.
    static efd::IBasePtr FactoryMethod();

    /// Save message data to a stream.
    virtual void Serialize(efd::Archive& ar);

    /// @name Message data getters and setters.
    //@{
    /// Get X magnitude.
    inline efd::Float32 GetX() const;

    /// Set X magnitude.
    inline void SetX(efd::Float32 x);

    /// Get Y magnitude.
    inline efd::Float32 GetY() const;

    /// Set Y magnitude.
    inline void SetY(efd::Float32 y);

    /// Get Z magnitude.
    inline efd::Float32 GetZ() const;

    /// Set Z magnitude.
    inline void SetZ(efd::Float32 z);
    //@}

protected:
    efd::Float32 m_x;
    efd::Float32 m_y;
    efd::Float32 m_z;
};

typedef efd::SmartPointer<InputStickMessage> InputStickMessagePtr;

} // namespace

#include "InputStickMessage.inl"

#endif // EE_INPUTSTICKMESSAGE_H
