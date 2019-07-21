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
#ifndef EE_PlatformService_h
#define EE_PlatformService_h

// This is a convenience header to include the appropriate platfrom-specific service

#if defined(EE_PLATFORM_WIN32)
#include <efd/Win32/Win32PlatformService.h>
#elif defined(EE_PLATFORM_PS3)
#include <efd/PS3/PS3PlatformService.h>
#elif defined(EE_PLATFORM_XBOX360)
    // XBox360 does not have a platform service
#endif

#endif // EE_PlatformService_h
