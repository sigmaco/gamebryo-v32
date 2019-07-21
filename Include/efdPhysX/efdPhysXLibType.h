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
#ifndef EE_EFDPHYSXLIBTYPE_H
#define EE_EFDPHYSXLIBTYPE_H

// Need to know what platform we are building on
#include <efd/OS.h>

//Define the proper symbol export macros if we building in a Windows based
//environment.
#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
    #ifdef EE_EFDPHYSX_EXPORT
        //Defined if we are building the library.
        #define EE_EFDPHYSX_ENTRY __declspec (dllexport)

        #pragma warning(disable:4251) // drw ignore use of un-exported stuff in exported stuff.

    #elif defined(_WINDLL) || defined (USEDLL) || defined(EE_EFDPHYSX_IMPORT)
        //If we are including as part of a client (we are a library)
        #define EE_EFDPHYSX_ENTRY __declspec (dllimport)
    #else
        //If we are defining for a static build (NOT a .dll)
        #define EE_EFDPHYSX_ENTRY
    #endif
#else
    // if we are compiling for a non-windows build
    #define EE_EFDPHYSX_ENTRY
#endif

#endif // EE_EFDPHYSXLIBTYPE_H
