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
#ifndef NIMATERIALTOOLKITLIBTYPE_H
#define NIMATERIALTOOLKITLIBTYPE_H

#ifdef NIMATERIALTOOLKIT_EXPORT
    // DLL library project uses this
    #define NIMATERIALTOOLKIT_ENTRY __declspec(dllexport)
#elif defined(NIMATERIALTOOLKIT_IMPORT)
    // client of DLL uses this
    #define NIMATERIALTOOLKIT_ENTRY __declspec(dllimport)
#else
#error NIMATERIALTOOLKIT_EXPORT or NIMATERIALTOOLKIT_IMPORT must be defined.
#endif

#endif  // #ifndef NIMATERIALTOOLKITLIBTYPE_H
