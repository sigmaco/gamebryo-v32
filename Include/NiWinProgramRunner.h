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

#ifndef NIWINPROGRAMRUNNER_H
#define NIWINPROGRAMRUNNER_H

#include "NiProgramRunner.h"
#include "NiProgramLauncherLibType.h"

/**
    This class is used to launch Windows applications on the local PC.
 */
class NIPROGRAMLAUNCHER_ENTRY NiWinProgramRunner : public NiProgramRunner
{
public:
    /// Virtual destructor
    /// @note Destroying the runner object does not terminate the program that was launched
    ///     by it.
    virtual ~NiWinProgramRunner();

    /**
        Launch windows exe on the specified target machine.

        @note At this time, the NiWinProgramRunner only supports the local workstation, not
            remote PCs.

        @param pcTargetName The name of target where the executable is to be launched. This can
            be queried from the NiProgramLauncher singleton or a NiWinProgramRunnerFactory object
        @param pcExecutableFilename The path and filename to the exe file on the local
            workstation
        @return True if the executable was successfully launched. Check output window if the
            launch failed for error messages.
    */
    virtual bool Start(const char* pcTargetName, const char* pcExecutableFilename);

protected:
    // This object can only be created by a NiWinProgramRunnerFactory
    NiWinProgramRunner();

    friend class NiWinProgramRunnerFactory;

    PROCESS_INFORMATION m_kProcessInformation;
};

#endif // NIWINPROGRAMRUNNER_H
