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
#ifndef EE_ECRINPUTPCH_H
#define EE_ECRINPUTPCH_H

#if defined(EE_USE_PCH)

#pragma warning(disable: 4275)

#include <efd/ServiceManager.h>

#if defined (EE_PLATFORM_XBOX360)
    #include <NiXenonInputSystem.h>
#elif defined (EE_PLATFORM_WIN32)
    #include <NiDI8InputSystem.h>
#elif defined (EE_PLATFORM_PS3)
    #include <NiPS3InputSystem.h>
#elif defined (EE_PLATFORM_LINUX)
    #error Linux not supported by ecrInput!
#else
    #error Unknown platform!
#endif

#endif // EE_USE_PCH

#endif // EE_ECRINPUTPCH_H
