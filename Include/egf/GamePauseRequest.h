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
#ifndef EE_GAMEPAUSEREQUEST_H
#define EE_GAMEPAUSEREQUEST_H

#include <efd/MessageHandlerBase.h>
#include <egf/egfLibType.h>
#include <egf/egfMessageIDs.h>

namespace egf
{
/// @name MessageWrappers from GamePauseRequest.h
//@{
typedef efd::MessageWrapper<efd::IMessage, efd::kMSGID_GamePauseRequest> GamePauseRequest;
//@}

typedef efd::SmartPointer<GamePauseRequest> GamePauseRequestPtr;

}

#endif // EE_GAMEPAUSEREQUEST_H
