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
#ifndef EE_OS_WIN32_H
#define EE_OS_WIN32_H

// WIN32 system headers demote/disable some useful warnings, so push
// warning state here and pop it after the include
#pragma warning(push, 3)

#include <winsock2.h>
#include <windows.h>

#pragma warning(pop)


#define EE_UNUSED

/// A helper macro that declares the argument as unused. Useful when building at warning level-4
/// to indicate the unused argument is known and accepted.
#define EE_UNUSED_ARG(arg) ((void)(arg))

/// Attempt to force the compiler to inline the function.
#define EE_FORCEINLINE __forceinline

/// Attempt to force the compiler to never inline the function.
#define EE_NOINLINE __declspec(noinline)

#if (_MSC_VER >= 1400) //VC8.0
    #define EE_RESTRICT __restrict
#else
    #define EE_RESTRICT
#endif

#define EE_EMPTY_THROW throw()

// We call many CRT methods that MSVC has marked as deprecated
// DT22211 We should remove calls to deprecated methods so this isn't needed
#pragma warning(disable : 4996)

#endif
