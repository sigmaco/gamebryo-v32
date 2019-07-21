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

#ifndef NIWINPROGRAMRUNNERFACTORY_H
#define NIWINPROGRAMRUNNERFACTORY_H

#include "NiWinProgramRunner.h"
#include "NiProgramRunnerFactory.h"

/**
    This Windows-specific factory is used to create NiWinProgramRunner objects and query
    information about the platform.
 */
class NIPROGRAMLAUNCHER_ENTRY NiWinProgramRunnerFactory : public NiProgramRunnerFactory
{
public:
    /// Virtual destructor
    ~NiWinProgramRunnerFactory();

    /// Returns NiSystemDesc::NI_WIN32
    virtual NiSystemDesc::PlatformID GetPlatformID();

    /// Returns "PC"
    virtual const char* GetPlatformDisplayName();

    /// Returns "Win32"
    virtual const char* GetPlatformInternalName();

    /// Returns "exe"
    virtual const char* GetPlatformExecutableFileExt();

    /**
        Returns all available Windows machines that can be used to launch an executable

        NOTE: At this time, NiWinProgramRunnerFactory only supports the local PC (not remote PCs)

        @param kTargetNames Returns a list of machine names associated with the platform. The
            NI_PROGRAMRUNNER_LOCAL_TARGET_NAME constant represents the name of the local PC.
        @param pkErrorInfo Optional string used to return error messages
        @return False if an error was detected. Pass string in as pkErrorInfo for
            additional details.
    */
    virtual bool GetAvailableTargetNames(NiStringArray& kTargetNames,
        NiString* pkErrorInfo = NULL);

    /** Create an NiWinProgramRunner object that can be used to launch a Windows exe.

        It is the caller's responsibility to delete the object returned by this method.

        @return NULL if a program runner could not be created
    */
    virtual  NiProgramRunner* Create();
};

#endif // NIWINPROGRAMRUNNERFACTORY_H
