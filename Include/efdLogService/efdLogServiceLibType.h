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
#ifndef EE_EFDLOGSERVICELIBTYPE_H
#define EE_EFDLOGSERVICELIBTYPE_H

// Need to know what platform we are building on
#include <efd/OS.h>

//Define the proper symbol export macros if we building in a Windows based
//environment.
#if defined(WIN32) || defined(_XENON)
    #ifdef EE_EFDLOGSERVICE_EXPORT
        //Defined if we are building the library.
        #define EE_EFD_LOGSERVICE_ENTRY __declspec (dllexport)

        #pragma warning(disable:4251) // drw ignore use of un-exported stuff in exported stuff.

    #elif defined(_WINDLL) || defined (USEDLL)
        //If we are including as part of a client (we are a library)
        #define EE_EFD_LOGSERVICE_ENTRY __declspec (dllimport)
    #else
        //If we are defining for a static build (NOT a .dll)
        #define EE_EFD_LOGSERVICE_ENTRY
    #endif
#else
    // if we are compiling for a non-windows build
    #define EE_EFD_LOGSERVICE_ENTRY
#endif

#endif
