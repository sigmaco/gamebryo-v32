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
#ifndef NIENVIRONMENTLIBTYPE_H
#define NIENVIRONMENTLIBTYPE_H

#ifndef __SPU__

    #if defined(NIENVIRONMENT_EXPORT)
        // building DLL library uses this
        #define NIENVIRONMENT_ENTRY __declspec(dllexport)
    #elif defined(NIENVIRONMENT_IMPORT)
        // something importing a DLL uses this
        #define NIENVIRONMENT_ENTRY __declspec(dllimport)
    #else
        // static library project uses this
        #define NIENVIRONMENT_ENTRY
    #endif
#else
#define NIENVIRONMENT_ENTRY 
#endif // __SPU__

#endif