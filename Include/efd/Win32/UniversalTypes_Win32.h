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
#ifndef EE_UNIVERSALTYPES_WIN32_H
#define EE_UNIVERSALTYPES_WIN32_H

#include <efd/Win32/RTLib_Win32.h>

/** @file UniversalTypes_Win32.h
    Define our Universal types in terms of platform specific types
*/

namespace efd
{
/// @name UniversalTypes
/// Define our Universal types in terms of platform specific types. 
/// The following types have been defined for Win32 in UniversalTypes_Win32.h.
//@{

typedef bool                Bool;

typedef char                Char;
typedef unsigned short      WChar;

typedef __int8              SInt8;
typedef unsigned __int8     UInt8;

#define EE_SINT8_MAX        (127)
#define EE_UINT8_MAX        (255)

typedef __int16             SInt16;
typedef unsigned __int16    UInt16;

#define EE_SINT16_MAX       (32767)
#define EE_UINT16_MAX       (65535)

typedef __int32             SInt32;
typedef unsigned __int32    UInt32;

#define EE_SINT32_MAX       (2147483647)
#define EE_UINT32_MAX       (4294967295)

typedef __int64             SInt64;
typedef unsigned __int64    UInt64;

#define EE_SINT64_MAX       (9223372036854775807ll)
#define EE_UINT64_MAX       (18446744073709551615ull)

typedef float               Float32;
typedef double              Float64;

#if !defined(SWIG)

typedef HWND WindowRef;
typedef HWND StatusWindowRef;
typedef HDC ContextRef;
typedef HGLRC OglRenderContextRef;
typedef HINSTANCE InstanceRef;
typedef HACCEL AcceleratorRef;
typedef HMODULE ModuleRef;

typedef struct
{
    HWND hWnd;
    UINT uiMsg;
    WPARAM wParam;
    LPARAM lParam;
} EventRecord, *EventRecordPtr;

typedef LPCREATESTRUCT CreateStructRef;
typedef HMENU MenuRef;

#endif

//@}
}

#endif
