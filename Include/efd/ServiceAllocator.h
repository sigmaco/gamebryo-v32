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
#ifndef EE_EFD_SERVICE_ALLOCATOR_H
#define EE_EFD_SERVICE_ALLOCATOR_H

#include <efd/ServiceManager.h>
#include <efd/efdLibType.h>

namespace efd
{

/// Define bit flags to modify service allocations in the CreateFoundationServices function
enum FoundationServiceAllocatorFlags
{
    /// Pass to Create to prevent creation of the efd::EnumManager and efd::Logger
    fsaf_NO_LOGGING = 0x1
};

/**
    Create the common Foundation services needed by most applications. If you use a fairly
    standard configuration you can simply call this method to create, configure and
    register the services.

    This function always creates the following services: efd::ConfigManager,
    efd::MessageService, efd::AssetLocatorService and efd::AssetFactoryManager.

    In addition, unless logging is disabled by passing the fsaf_NO_LOGGING flag the
    efd::EnumManager service is created and EnumManager::LoadConfigOptions is called. If their
    is a Logger singleton it will also initialized by calling ILogger::ReadConfig. As such it is
    recommended that before you call CreateFoundationServices you create a logger and register it
    by calling efd::LoggerSingleton::Initialize and then add the default ILogDestination by calling
    ILogger::AddDest.

    @param pServiceManager The ServiceManager to which the services are registered
    @param argcInit The number of command line arguments, which is passed to the constructor
        of the efd::ConfigManager. Pass zero on platforms without a command line.
    @param argvInit The command line arguments, which are passed to the constructor of the
        efd::ConfigManager. Pass NULL on platforms without a command line.
    @param flags Flags from the ServiceAllocatorFlags enum to change default behavior
*/
EE_EFD_ENTRY bool CreateFoundationServices(
    efd::ServiceManager* pServiceManager,
    int argcInit,
    char** argvInit,
    efd::UInt32 flags = 0);

} // end namespace efd

#endif // EE_EFD_SERVICE_ALLOCATOR_H
