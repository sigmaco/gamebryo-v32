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
#ifndef EE_UNIVERSALTYPES_H
#define EE_UNIVERSALTYPES_H

#include <efd/OS.h>

#if defined(EE_PLATFORM_WIN32)
#include <efd/Win32/UniversalTypes_Win32.h>
#elif defined(EE_PLATFORM_LINUX)
#include <efd/Linux/UniversalTypes_Linux.h>
#elif defined(EE_PLATFORM_XBOX360)
#include <efd/XBox360/UniversalTypes_XBox360.h>
#elif defined(EE_PLATFORM_PS3)
#include <efd/PS3/UniversalTypes_PS3.h>
#else
    #ifndef SWIG // we don't use this file in swig
    #error Platform undefined.
    #endif
#endif

#endif //EE_UNIVERSALTYPES_H
