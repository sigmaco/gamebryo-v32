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
#ifndef EE_SDMMACROS_H
#define EE_SDMMACROS_H

#define EE_DECLARE_SDM(libname, entrytag) \
    class entrytag libname##SDM \
    { \
    public: \
        libname##SDM(); \
        static void Init(); \
        static void Shutdown(); \
    protected: \
        static bool ms_initialized; \
    };


#define EE_DECLARE_SDM_WITH_TLS(libname, entrytag) \
    class entrytag libname##SDM \
    { \
    public: \
        libname##SDM(); \
        static void Init(); \
        static void Shutdown(); \
        static void PerThreadInit(); \
        static void PerThreadShutdown(); \
    protected: \
        static bool ms_initialized; \
    };


#define EE_IMPLEMENT_SDM_CONSTRUCTOR(libname, dependencies) \
    bool libname##SDM::ms_initialized = false; \
    libname##SDM::libname##SDM() \
    { \
        static efd::SInt32 counter = 0; \
        if (counter++ == 0) \
        { \
            efd::StaticDataManager::AddLibrary(#libname, \
                libname##SDM::Init, \
                libname##SDM::Shutdown, \
                NULL, \
                NULL, \
                dependencies); \
        } \
    }

#define EE_IMPLEMENT_SDM_CONSTRUCTOR_WITH_TLS(libname, dependencies) \
    bool libname##SDM::ms_initialized = false; \
    libname##SDM::libname##SDM() \
    { \
        static efd::SInt32 counter = 0; \
        if (counter++ == 0) \
        { \
            efd::StaticDataManager::AddLibrary(#libname, \
                libname##SDM::Init, \
                libname##SDM::Shutdown, \
                libname##SDM::PerThreadInit, \
                libname##SDM::PerThreadShutdown, \
                dependencies); \
        } \
    }

#define EE_IMPLEMENT_SDM_INIT_CHECK() \
    if (!ms_initialized) \
    { \
        ms_initialized = true; \
    } \
    else \
    { \
        return; \
    }


#define EE_IMPLEMENT_SDM_SHUTDOWN_CHECK() \
    if (ms_initialized) \
    { \
        ms_initialized = false; \
    } \
    else \
    { \
        return; \
    }

#define EE_IMPLEMENT_DLLMAIN(libname) \
    HMODULE gs_h##libname##Handle = 0; \
    BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID /*pReserved*/)\
    { \
        switch (reason) \
        { \
            case DLL_PROCESS_ATTACH: \
                gs_h##libname##Handle = module; \
                efd::StaticDataManager::ProcessAccumulatedLibraries(); \
                break; \
            case DLL_PROCESS_DETACH: \
                gs_h##libname##Handle = 0; \
                efd::StaticDataManager::RemoveLibrary(#libname); \
                break; \
        } \
        return TRUE; \
     }

#endif
