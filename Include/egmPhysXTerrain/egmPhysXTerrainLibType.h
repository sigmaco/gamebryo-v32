// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2007 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef EE_EGMPHYSXTERRAINLIBTYPE_H
#define EE_EGMPHYSXTERRAINLIBTYPE_H

// so we know the names our dll exports (if we compile for windows)
#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
    #ifdef EE_EGMPHYSXTERRAIN_EXPORT
        //Defined if we are building the library.
        #define EE_EGMPHYSXTERRAIN_ENTRY __declspec (dllexport)
    #elif defined(EE_EFD_NO_IMPORT)
        #define EE_EGMPHYSXTERRAIN_ENTRY
    #elif defined(_WINDLL) || defined (USEDLL) || defined(EE_EGMPHYSXTERRAIN_IMPORT)
        // if we are including as part of a client (we are a library)
        #define EE_EGMPHYSXTERRAIN_ENTRY __declspec (dllimport)
    #else
        // if we are defining for a static build (NOT a .dll)
        #define EE_EGMPHYSXTERRAIN_ENTRY
    #endif

    // 4275 - non dll-interface class used as base for dll-interface class.
    #pragma warning(disable:4275)

#else
    // if we are compiling for a non-windows build
    #define EE_EGMPHYSXTERRAIN_ENTRY
#endif

#endif // EE_EGMPHYSXTERRAINLIBTYPE_H
