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
#ifndef NIDEBUG_H
#define NIDEBUG_H

#include "NiSystemLibType.h"

#include <efd/Asserts.h>

//
// Note: This class has been deprecated and will be removed in a future release of Gamebryo
//
// The handler that was registered via ms_pfnNiAssertFailProc has changed signature to be of
// type efd::AssertHandler and is now registered via efd::AssertHelper::SetAssertHandler().
//

class NISYSTEM_ENTRY NiAssertFail
{
public:
    // This assertion routine will simply write out a debug string.
    // It will not trigger a breakpoint. This is useful for running
    // automated tests.
    static efd::SInt8 SimpleAssertFail(
        const char* pszFile,
        efd::SInt32 line,
        const char* pszFunction,
        const char* pszPred,
        const char* pszMsg,
        const char* pszStack,
        efd::Bool isAVerify);
};


#define NIASSERT          EE_ASSERT
#define NIVERIFY          EE_VERIFY
#define NIVERIFYEQUALS    EE_VERIFYEQUALS
#define NIVERIFYNOTEQUALS EE_VERIFY_NOT_EQUAL
#define NIDEBUGBREAK      EE_DEBUG_BREAK

// Causes a break in debugger, function always returns false
inline bool NiDebugBreakProc() { EE_DEBUG_BREAK(); return false; }

#endif // NIDEBUG_H
