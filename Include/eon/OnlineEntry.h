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
#ifndef EE_ONLINEENTRY_H
#define EE_ONLINEENTRY_H

// so we know the names our dll exports (if we compile for windows)
#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
    #ifdef EE_EON_EXPORT
        // if we are including as part of Scheduler.dll
        #define EE_EONENTRY __declspec (dllexport)
    #elif defined(_WINDLL) || defined (USEDLL)
        // if we are including as part of a client (we are a library)
        #define EE_EONENTRY __declspec (dllimport)
    #else
        // if we are defining for a static build (NOT a .dll)
        #define EE_EONENTRY
    #endif
#else
    // if we are compiling for a non-windows build
    #define EE_EONENTRY
#endif //EE_EON_EXPORT


#endif // EE_ONLINEENTRY_H
