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
#ifndef NISHADERLIBRARYINTERFACE_H
#define NISHADERLIBRARYINTERFACE_H

// DLL Library interface function
#if defined(_USRDLL)
#if defined(NIMAIN_EXPORT)
// DLL library project uses this
#define NISHADERLIBRARY_ENTRY __declspec(dllimport)
#else
#if defined(NIMAIN_IMPORT)
// client of DLL uses this
#define NISHADERLIBRARY_ENTRY __declspec(dllexport)
#else
// static library project uses this
#define NISHADERLIBRARY_ENTRY
#endif
#endif

typedef bool (*NISLI_LOADLIBRARY)(NiRenderer*, int,
    const char*[], bool, NiShaderLibrary** ppkLibrary);
typedef unsigned int (*NISLI_RUNPARSER)(const char*, bool);
typedef unsigned int (*NISLI_GETCOMPILERVERSIONFUNCTION)(void);

extern "C"
{
    NISHADERLIBRARY_ENTRY bool LoadShaderLibrary(
        NiRenderer* pkRenderer, int iDirectoryCount,
        const char* pszDirectories[], bool bRecurseSubFolders,
        NiShaderLibrary** ppkLibrary);
    NISHADERLIBRARY_ENTRY unsigned int RunShaderParser(
        const char* pszDirectory, bool bRecurseSubFolders);
    NISHADERLIBRARY_ENTRY unsigned int GetCompilerVersion(void);
};
#endif  //#if defined(_USRDLL)

#endif  //NISHADERLIBRARYINTERFACE_H
