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
#ifndef EE_CONTROLBUILTINS_H
#define EE_CONTROLBUILTINS_H

#include <ecrInput/InputService.h>
#include "ecrInputLibType.h"

namespace ecrInput
{
const efd::UInt32 InvalidCallbackID = 0;

const efd::UInt32 CallbackNormal = ecrInput::InputService::CALLBACK_NORMAL;
const efd::UInt32 CallbackImmediate = ecrInput::InputService::CALLBACK_IMMEDIATE;

EE_ECRINPUT_ENTRY efd::UInt32 ListenForInputActionEvent(
    egf::EntityID entityID,
    efd::utf8string inputEventName,
    efd::utf8string behaviorName,
    efd::UInt32 callbackType = CallbackNormal);

EE_ECRINPUT_ENTRY efd::UInt32 ListenForInputStickEvent(
    egf::EntityID entityID,
    efd::utf8string inputEventName,
    efd::utf8string behaviorName,
    efd::UInt32 callbackType = CallbackNormal);

EE_ECRINPUT_ENTRY void ClearRegisteredInputEvents(egf::EntityID entityID);

EE_ECRINPUT_ENTRY void ClearRegisteredInputEvent(efd::UInt32 callbackID);

} // end namespace ecrInput

#endif // EE_CONTROLBUILTINS_H
