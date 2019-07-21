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
#ifndef EE_IINTERACTIONDELEGATE_H
#define EE_IINTERACTIONDELEGATE_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <ecrInput/MouseMessages.h>

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY IInteractionDelegate
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE(IInteractionDelegate, kCLASSID_IInteractionDelegate);
    /// @endcond

public:

    virtual efd::SInt32 GetInteractionPriority() = 0;

    virtual bool OnMouseScroll(
        efd::Bool handled,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dScroll) = 0;

    virtual bool OnMouseMove(
        efd::Bool handled,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dx,
        efd::SInt32 dy) = 0;

    virtual bool OnMouseDown(
        efd::Bool handled,
        ecrInput::MouseMessage::MouseButton eButton,
        efd::SInt32 x,
        efd::SInt32 y) = 0;

    virtual bool OnMouseUp(
        efd::Bool handled,
        ecrInput::MouseMessage::MouseButton eButton,
        efd::SInt32 x,
        efd::SInt32 y) = 0;

    virtual bool OnPreMouseScroll(efd::SInt32 x, efd::SInt32 y, efd::SInt32 dScroll);

    virtual bool OnPreMouseMove(efd::SInt32 x, efd::SInt32 y, efd::SInt32 dx, efd::SInt32 dy);

    virtual bool OnPreMouseDown(
        ecrInput::MouseMessage::MouseButton eButton,
        efd::SInt32 x,
        efd::SInt32 y);

    virtual bool OnPreMouseUp(
        ecrInput::MouseMessage::MouseButton eButton,
        efd::SInt32 x,
        efd::SInt32 y);
};

} // egmToolServices namespace

#endif // EE_IINTERACTIONDELEGATE_H
