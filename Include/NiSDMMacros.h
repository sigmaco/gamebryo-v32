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
#ifndef NISDMMACROS_H
#define NISDMMACROS_H

#include <efd/SDMMacros.h>

#define NiDeclareSDM(libname, entrytag) \
    EE_DECLARE_SDM(libname, entrytag)

#define NiDeclareSDMWithTLS(libname, entrytag) \
    EE_DECLARE_SDM_WITH_TLS(libname, entrytag)

#define NiImplementSDMConstructor(libname, dependencies) \
    EE_IMPLEMENT_SDM_CONSTRUCTOR(libname, dependencies)

#define NiImplementSDMConstructorWithTLS(libname, dependencies) \
    EE_IMPLEMENT_SDM_CONSTRUCTOR_WITH_TLS(libname, dependencies)

#define NiImplementSDMInitCheck() EE_IMPLEMENT_SDM_INIT_CHECK()

#define NiImplementSDMShutdownCheck() EE_IMPLEMENT_SDM_SHUTDOWN_CHECK()

#define NiImplementDllMain(libname) \
    HMODULE gs_h##libname##Handle = 0; \
    BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID /*pReserved*/)\
    { \
        switch (reason) \
        { \
            case DLL_PROCESS_ATTACH: \
                gs_h##libname##Handle = module; \
                NiStaticDataManager::ProcessAccumulatedLibraries(); \
                break; \
            case DLL_PROCESS_DETACH: \
                gs_h##libname##Handle = 0; \
                NiStaticDataManager::RemoveLibrary(#libname); \
                break; \
        } \
        return TRUE; \
     }

#endif
