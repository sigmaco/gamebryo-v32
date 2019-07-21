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

#ifndef NIPROGRAMRUNNERFACTORY_H
#define NIPROGRAMRUNNERFACTORY_H

#include "NiProgramLauncherLibType.h"

#include "NiSystemDesc.h"
#include "NiTArray.h"
#include "NiString.h"

typedef NiTObjectArray<NiString> NiStringArray;

class NiProgramRunner;
NiSmartPointer(NiProgramRunnerFactory);

/**
    Interface that defines methods for querying platform information and creating runner
    objects that are used for launching an executable on the specified platform.
 */
class NIPROGRAMLAUNCHER_ENTRY NiProgramRunnerFactory : public NiRefObject
{
public:
    /// Returns the Gamebryo platform ID enum associated with the factory
    virtual NiSystemDesc::PlatformID GetPlatformID() = 0;

    /// Returns a long string suitable for use in a user interface to represent the platform
    virtual const char* GetPlatformDisplayName() = 0;

    /// Returns a short string used for naming directories and files related to the platform
    virtual const char* GetPlatformInternalName() = 0;

    /// Returns the platform's executable file extension (for example, "exe" for PC)
    virtual const char* GetPlatformExecutableFileExt() = 0;

    /**
        Returns all available targets for the platform

        @param kTargetNames Returns a list of machine names associated with the platform. The
            NI_PROGRAMRUNNER_LOCAL_TARGET_NAME constant represents the name of the local PC.
        @param pkErrorInfo Optional string used to return error messages
        @return False if an error was detected. Pass string in as pkErrorInfo for
            additional details.
    */
    virtual bool GetAvailableTargetNames(NiStringArray& kTargetNames,
        NiString* pkErrorInfo = NULL) = 0;

    /** Create an object used to launch an executable for the platform represented by this factory.

        It is the caller's responsibility to delete the object returned by this method.

        @return NULL if a program runner could not be created
    */
    virtual  NiProgramRunner* Create() = 0;
};

typedef NiProgramRunnerFactory* (*NiCreateProcessFactoryFunction)(void);

/// Constant that represents the string for local PC target name
#define NI_PROGRAMRUNNER_LOCAL_TARGET_NAME "[Local]"

#endif // NIPROGRAMRUNNERFACTORY_H
