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

#ifndef NIPROGRAMRUNNER_H
#define NIPROGRAMRUNNER_H

#include "NiRTTI.h"
#include "NiRefObject.h"
#include "NiString.h"
#include "NiTSet.h"

#include "NiOutputWindow.H"
#include "NiProgramLauncherLibType.h"

NiSmartPointer(NiProgramRunner);

/**
    Interface that defines methods for launching an executable.

    This interface is implemented by a concrete class for each platform supported by the
    NiProgramLauncher library.
 */
class NIPROGRAMLAUNCHER_ENTRY NiProgramRunner : public NiRefObject
{
    NiDeclareRootRTTI(NiProgramRunner);

public:
    NiProgramRunner();
    virtual ~NiProgramRunner();

    /// Get string that will be used as command line arguments when an executable is launched.
    /// This string can be replaced or appended to change or add options. The command line
    /// should not include the executable name.
    NiString& GetCommandLine();

    /**
        This method either copies or configures paths required by the executable depending on
        the platform.

        The behavior of this method varies based on the platform type. Refer to
        the Ni[platform]ProgramRunner class definition for additional information.

        @param pcLocal Path on the local PC
        @param pcRemote Path or variable used by the console development kit (see
            console-specific class for additional details)
    */
    void AddFilePathMapping(const char* pcLocal, const char* pcRemote);

    /**
        Open or close a separate output window that displays text messages
        indicating progress or errors encountered while launching executable

        @param bEnabled True indicates the window should be displayed
    */
    void SetOutputWindow(bool bEnabled);

    /// Gets the display status of the output window
    /// @return True if the window is currently displayed
    bool GetOutputWindow();

    /**
        Allows caller to assign a title to the output window associated with this runner object
        @param pcTitle The string to be used as the window title
        @return False if the window could not be created
    */
    bool SetOutputWindowTitle(const char* pcTitle);

    /**
        Launch executable on the specified target machine

        The command line specified by GetCommandLine() will be passed to the executable at launch.
        The progress or failure to launch the executable will be displayed as text messages in
        in a separate output window (if enabled using SetOutputWindow()).

        @param pcTargetName The name of target where the executable is to be launched. This can
            be queried from the NiProgramLauncher singleton or a NiProgramFactory object
        @param pcExecutableFilename The path and filename to the executable on the local
            workstation
        @return True if the executable was successfully launched. Check output window if the
            launch failed for error messages.
    */
    virtual bool Start(const char* pcTargetName, const char* pcExecutableFilename) = 0;

    /**
        Show a message in the output window

        @param pcFormat Printf-like format specifier string
        @return The number of bytes displayed or -1 if the window is closed.
    */
    int DisplayMsg(const char* pcFormat, ...);

    /// @cond EMERGENT_INTERNAL
    static NiString GetEnvVariable(const char* pcName);
    static bool SplitFilePath(const char* pcFilePath, NiString& kPath, NiString& kFilename,
        char cPathSeparator = '\\');
    /// @endcond EMERGENT_INTERNAL

protected:

    NiTObjectSet<NiString> m_kLocalFilePathSet;
    NiTObjectSet<NiString> m_kRemoteFilePathSet;

    NiString m_kCommandLine;

    NiOutputWindow m_kOutputWindow;
};

#endif // NIPROGRAMRUNNER_H
