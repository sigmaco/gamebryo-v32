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
#ifndef NISTATICDATAMANAGER_H
#define NISTATICDATAMANAGER_H

#include "NiSystemLibType.h"
#include "NiSDMMacros.h"
#include "NiInitOptions.h"

#include <efd/StaticDataManager.h>
#define NI_NUM_LIBRARIES efd::EE_NUM_LIBRARIES

//--------------------------------------------------------------------------------------------------
class NISYSTEM_ENTRY NiStaticDataManager
{
public:
    static void Init(const NiInitOptions* pkOptions = NULL, bool kEEInit = true);
    static void Shutdown(bool kEEShutdown = true);
    static const NiInitOptions* GetInitOptions();

    static void AddLibrary(
        const char* libraryName,
        efd::StaticDataManager::InitFunction pInit,
        efd::StaticDataManager::ShutdownFunction pShutdown,
        const char* dependencies);
    static void RemoveLibrary(const char* libraryName);
    static void ProcessAccumulatedLibraries();
    static bool IsInitialized();
private:
    static bool ms_bAutoCreatedInitOptions;
    static const NiInitOptions* ms_pkInitOptions;

    static bool ms_initialized;
};

#define NiInit NiStaticDataManager::Init
#define NiShutdown NiStaticDataManager::Shutdown

#endif // #ifndef NISTATICDATAMANAGER_H
