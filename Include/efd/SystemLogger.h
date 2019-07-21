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
#ifndef EE_SYSTEMLOGGER_H
#define EE_SYSTEMLOGGER_H

#include <efd/Logger.h>
#include <efd/Helpers.h>
#include <efd/Category.h>
#include <efd/IMessage.h>
#include <efd/efdLibType.h>
#include <efd/efdClassIDs.h>

namespace efd
{

/**
    Convenience class to hold static creation function
 */
class EE_EFD_ENTRY SystemLogger
{
public:
    static efd::ILoggerPtr CreateSystemLogger();
};


} // end namespace efd

#endif // EE_SYSTEMLOGGER_H
