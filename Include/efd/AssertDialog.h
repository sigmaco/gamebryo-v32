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
#ifndef EE_ASSERTDIALOG_H
#define EE_ASSERTDIALOG_H

#include <efd/UniversalTypes.h>
#include <efd/efdLibType.h>

namespace efd
{
/**
    Function to display a dialog when an assert fails.

    @param pFile The source file where the assert message was generated
    @param line The source line where the assert message was generated
    @param pFunction The function where the assert message was generated
    @param pPred The predicate of the assert that failed
    @param pMsg The optional formatted assert message
    @param pStack Optional If EE_USE_ASSERT_STACKTRACE was defined at compile time, a stack
        backtrace is passed in.  Otherwise this will be NULL.
    @param isAVerify Boolean to denote if this is a Verify dialog (true for Verify)
*/
EE_EFD_ENTRY efd::SInt8 DisplayAssertDialog(
    const char* pFile,
    efd::SInt32 line,
    const char* pFunction,
    const char* pPred,
    const char* pMsg,
    const char* pStack,
    efd::Bool isAVerify);
}

#endif // EE_ASSERTDIALOG_H

