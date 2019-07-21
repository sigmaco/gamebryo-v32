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
// Emergent Game Technologies, Calabasas, California 91302
// http://www.emergent.net

#pragma once
#ifndef EE_WORLDRESETREQUEST_H
#define EE_WORLDRESETREQUEST_H

#include <efd/MessageHandlerBase.h>
#include <efd/IMessage.h>
#include <egf/egfLibType.h>
#include <egf/egfMessageIDs.h>

namespace egf
{
/// @name MessageWrappers from WorldResetRequest.h
//@{
typedef efd::MessageWrapper<efd::IMessage, efd::kMSGID_WorldResetRequest> WorldResetRequest;
//@}
typedef efd::SmartPointer<WorldResetRequest> WorldResetRequestPtr;

} //namespace egf

#endif // EE_WORLDRESETREQUEST_H
