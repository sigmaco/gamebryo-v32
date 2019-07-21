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
#ifndef EE_NET_H
#define EE_NET_H

/// @cond EMERGENT_INTERNAL

#if defined(EE_PLATFORM_WIN32)
#   include <efdNetwork/Win32/Net_Win32.h>
#elif defined(EE_PLATFORM_PS3)
#   include <efdNetwork/PS3/Net_PS3.h>
#elif defined(EE_PLATFORM_XBOX360)
#   include <efdNetwork/Xbox360/Net_Xbox360.h>
#elif defined(EE_PLATFORM_LINUX)
#   include <efdNetwork/Linux/Net_Linux.h>
#else
#   error Unknown platform
#endif // EE_PLATFORM_*

/// @endcond

#endif //EE_NET_H
