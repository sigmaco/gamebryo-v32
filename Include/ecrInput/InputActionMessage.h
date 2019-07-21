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
#ifndef EE_INPUTACTIONMESSAGE_H
#define EE_INPUTACTIONMESSAGE_H

#include <efd/IMessage.h>

#include "ecrInputLibType.h"

#include <ecrInput/ecrInputMessageIDs.h>

namespace ecrInput
{

/**
    A message for representing user input containing application context and a magnitude.

    It may be used for reporting digital and analog button presses, axis position or
    movement. It may be suitable for reporting that a stick or d-pad is in range
    if actual coordinates are not needed.
*/

class EE_ECRINPUT_ENTRY InputActionMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(InputActionMessage, efd::kMSGID_CoreInputAction, efd::IMessage);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /// Default constructor. Initializes all data to zero.
    inline InputActionMessage();

    /// Initializing constructor.
    inline InputActionMessage(const efd::utf8string& eventName,
        efd::UInt32 appData,
        efd::Float32 magnitude,
        void* userData = NULL);
    //@}

    /// On demand class creation.
    static efd::IBasePtr FactoryMethod();

    /// Save message data to stream.
    virtual void Serialize(efd::Archive& ar);

    /// @name Message data getters and setters.
    //@{
    /// The name of the event that is firing.  This matches whatever name was used in the
    /// action map.
    inline const efd::utf8string& GetEventName() const;

    /// Event name setter.
    inline void SetEventName(const efd::utf8string& eventName);

    /// Actionmap-defined data getter.
    inline efd::UInt32 GetAppData() const;

    /// Actionmap-defined data setter.
    inline void SetAppData(efd::UInt32 appData);

    /// Magnitude getter.
    inline efd::Float32 GetMagnitude() const;

    /// Magnitude setter.
    inline void SetMagnitude(efd::Float32 magnitude);

    /// User-defined data getter.  This is whatever value was passed to the InputService
    /// ListenForInput*Event method.
    inline void* GetUserData() const;

    /// User-defined data setter.
    inline void SetUserData(void* userData);
    //@}

protected:
    efd::utf8string m_eventName;
    efd::UInt32 m_appData;
    efd::Float32 m_magnitude;
    void* m_userData;
};

typedef efd::SmartPointer<InputActionMessage> InputActionMessagePtr;

} // end namespace ecrInput

#include "InputActionMessage.inl"

#endif // EE_INPUTACTIONMESSAGE_H
