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
#ifndef EE_IFATAL_ERROR_H
#define EE_IFATAL_ERROR_H

#include <efd/IBase.h>
#include <efd/utf8string.h>
#include "egfDemoSystemServiceIDs.h"

namespace egmSample
{

/**
    IFatalError. A class used to pass information about a fatal error to the GameStateService.
    General usage would be to derive a class from it that could provide more information.
*/
struct IFatalError : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(IFatalError, efd::kCLASSID_IFatalError, efd::IBase);
    /// @endcond

    /**
        Get the message string describing the fatal error.
        @return The message associated with the error.
    */
    virtual const efd::utf8string& GetMessage() const = 0;
};

} // end namespace egmSample

#endif // EE_IFATAL_ERROR_H
