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
#ifndef EE_INPUTACTIONMAPSLOADED_H
#define EE_INPUTACTIONMAPSLOADED_H

#include <efd/IMessage.h>

#include "ecrInputLibType.h"

#include <ecrInput/ecrInputMessageIDs.h>

namespace ecrInput
{

/**
    A message for reporting that a request action map urn has been loaded.
*/

class EE_ECRINPUT_ENTRY InputActionMapsLoaded : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(InputActionMapsLoaded, efd::kMSGID_CoreInputActionMapsLoaded, efd::IMessage);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /// Default constructor. Initializes all data to zero.
    InputActionMapsLoaded();

    /// Initializing constructor.
    InputActionMapsLoaded(const efd::utf8string& urn, const bool success = true);
    //@}

    /// @name Message data getters and setters.
    //@{

    /// Get the urn for the original action map load request.
    efd::utf8string GetRequestedURN() const;

    /// Set the urn for the original action map load request.
    void SetRequestedURN(const efd::utf8string& urn);

    /// Get the success status.
    bool GetSuccess() const;

    /// Set the success status.
    void SetSuccess(const bool success);

    //@}

protected:
    efd::utf8string m_urn;
    bool m_success;
};

typedef efd::SmartPointer<InputActionMapsLoaded> InputActionMapsLoadedPtr;

}; // namespace

#endif // EE_INPUTACTIONMAPSLOADED_H
