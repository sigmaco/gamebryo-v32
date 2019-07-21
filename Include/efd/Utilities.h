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
#ifndef EE_UTILITIES_H
#define EE_UTILITIES_H

#include <efd/OS.h>
#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/StringUtilities.h>

namespace efd
{
/// @name General utility functions from Utilities.h

//@{

/// Gets the value of the specified environment variable
EE_EFD_ENTRY void GetEnvironmentVariable(size_t* pstDestLength, efd::Char* pcDest,
    size_t stDestSize, const efd::Char* pcSrc);

/// wrapper for a right bitwise rotation
EE_EFD_ENTRY efd::UInt32 Rotr(efd::UInt32 x, efd::SInt32 n);

/// wrapper for sleep
inline void Sleep(efd::UInt32 milliseconds);

/// encapsulation of sleep(0)
inline void YieldThread();

/// method to get the current thread identifier
inline unsigned long GetCurrentThreadId();

//--------------------------------------------------------------------------------------------------
// Cache Control Functions
//--------------------------------------------------------------------------------------------------
inline void Prefetch128(void* pvBase);

//--------------------------------------------------------------------------------------------------
// Routines that can potentially avoid branches on certain platforms
/// Non-branching selection on >=
inline efd::Float32 SelectGE(efd::Float32 condition,
    efd::Float32 resultIfGreaterThanEqualZero, efd::Float32 resultIfLessThanZero);
/// Non-branching selection on >=
inline efd::Float32 SelectGE(efd::SInt32 condition,
    efd::Float32 resultIfGreaterThanEqualZero, efd::Float32 resultIfLessThanZero);
/// Non-branching selection on boolean true/false
inline efd::SInt32 Select(bool condition, efd::SInt32 resultIfTrue,
    efd::SInt32 resultIfFalse);
/// Non-branching selection on boolean true/false
inline efd::Float32 Select(bool condition, efd::Float32 resultIfTrue,
    efd::Float32 resultIfFalse);
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
// Safe casting routines from 32-bit enum values to unsigned values.
//--------------------------------------------------------------------------------------------------

inline efd::UInt8 Int32ToUInt8(efd::SInt32 value);
inline efd::UInt16 Int32ToUInt16(efd::SInt32 value);
inline efd::UInt32 Int32ToUInt32(efd::SInt32 value);
inline efd::SInt8 Int32ToInt8(efd::SInt32 value);
inline efd::SInt16 Int32ToInt16(efd::SInt32 value);

//--------------------------------------------------------------------------------------------------

/**
    GetPerformanceCounter has a different number of cycles per second
    on different platforms and even different processors.  Use
    SystemDesc::GetSystemDesc().GetPerformanceCounterHz()
    to get the conversion divisor.
*/
EE_EFD_ENTRY efd::UInt32 GetPerformanceCounter();

//--------------------------------------------------------------------------------------------------
// Routines that query the system
//--------------------------------------------------------------------------------------------------

/// Wrapper around _getcwd/getcwd
inline efd::Char* Getcwd(efd::Char* buffer, size_t maxlen);

/// wrapper around getpid
inline efd::UInt64 GetPid();

/// wrapper around MakeDir
EE_EFD_ENTRY efd::UInt32 MakeDir(const efd::Char* path);

//--------------------------------------------------------------------------------------------------
// Routines for setting up environment for test apps
//--------------------------------------------------------------------------------------------------

/// Initialize a testing environment (turn off error dialogs, etc...)
EE_EFD_ENTRY void InitTestEnvironment();

//--------------------------------------------------------------------------------------------------

//@}

} // end namespace efd

// Include the platform specific inline functions
#include EE_PLATFORM_SPECIFIC_INCLUDE(efd,Utilities,inl)

#endif // EE_UTILITIES_H
