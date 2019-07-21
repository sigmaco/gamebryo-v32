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

#ifndef NIPROGRAMLAUNCHER_H
#define NIPROGRAMLAUNCHER_H

#include "NiProgramLauncherLibType.h"

#include "NiSystemDesc.h"
#include "NiTArray.h"
#include "NiTPtrSet.h"
#include "NiString.h"

#include "NiProgramRunnerFactory.h"

class NiProgramRunner;

typedef NiTObjectArray<NiString> NiStringArray;

/**
    This singleton object is used to launch an executable on the local PC or console
    development kit.

    When the NiProgramLauncher singleton is initialized, it will attempt to load
    platform-specific launcher plug-ins. The available platforms and targets can then
    be queried and used to create a NiProgramRunner object.
*/
class NIPROGRAMLAUNCHER_ENTRY NiProgramLauncher : public NiMemObject
{
public:
    /// Accessor for the singleton object. This method will return NULL if the Initialize()
    /// method has not been called (or if the Shutdown() method has been called).
    static NiProgramLauncher* GetInstance();

    /** Create the singleton and query for available platforms
        @param pkErrorInfo Optional string object passed by the caller to hold any error messages
        generated during initialization
        @param pcPluginDirectory Optional path to a directory to find the console program
        launcher DLLs. If no directory is supplied the following directory will be used
        EMERGENT_PATH\\sdk\\Win32\\DLL.
    */
    static bool Initialize(NiString* pkErrorInfo = NULL, const char* pcPluginDirectory = NULL);

    /// Unload any program launcher DLLs and destroy the singleton. Executables running on
    /// PC or consoles will not be terminated.
    static void Shutdown();

    /**
        Returns the display names for platforms (for example, "PC", "Playstation 3", etc) where an
        executable can be launched.
        @param kPlatformNames An array used to return the name strings
    */
    void GetAvailablePlatformNames(NiStringArray& kPlatformNames) const;

    /**
        Returns the display names for targets (machine names) where an executable can be launched.

        @param pcPlatformName The name of the platform (returned by GetAvailablePlatformNames())
        @param kTargetNames An array used to return the machine name strings
        @param pkErrorInfo An optional string used to return an error message if the method fails
        @return True indicates no errors were encountered while querying the target names
    */
    bool GetAvailableTargetNames(const char* pcPlatformName, NiStringArray& kTargetNames,
        NiString* pkErrorInfo = NULL) const;

    /**
        Create an object that can be used to execute a program on a PC or console development kit.

        @param pcPlatformName The name of the platform that the executable will be launched on.
            This can be queried using the GetAvailablePlatformNames() method.
        @return An object that can be used launch executable or NULL if the method failed
    */
    NiProgramRunner* Create(const char* pcPlatformName);

    /**
        Returns pointer to a factory object that can be used to query information about the
        platform and create NiProgramRunner objects.

        This object is managed by the NiProgramLauncher singleton. Do not delete the object,
        it will be cleaned up at shutdown.

        @param pcPlatformName The name of the platform that the executable will be launched on.
            This can be queried using the GetAvailablePlatformNames() method.
        @return NULL if the platform is not supported (or the plug-in for the platform was not
            loaded)
    */
    NiProgramRunnerFactory* GetProcessFactory(const char* pcPlatformName) const;

    /// @cond EMERGENT_INTERNAL
    static void SetDllInstance(HINSTANCE hDllInstance);
    static HINSTANCE GetDllInstance();
    /// @endcond EMERGENT_INTERNAL

private:
    /// This is a singleton, do not allow it to be subclassed.
    NiProgramLauncher();
    ~NiProgramLauncher();

    bool AddPluginDirectory(const char* pcPath, bool bRecurse, NiString* pkErrorInfo = NULL);
    bool AddLibrary(NiString strPath);

    /// Create platform factory objects used to create platform runner objects
    bool CreateFactories(NiString* pkErrorInfo = NULL, const char* pcPluginDirectory = NULL);

    /// Using an array instead of a map since this will be a short list that can be quickly
    /// searched
    NiTObjectArray<NiProgramRunnerFactoryPtr> m_kPlatformFactoryArray;

    /// The current set of HMODULE handles to Ni*ProgramLauncher DLLs loaded by the manager
    NiTPtrSet<NiModuleRef, NiTExternalNewInterface<NiModuleRef>> m_kDLLHandles;

    /// Singleton instance of the class
    static NiProgramLauncher* ms_pkInstance;

    /// Windows instance for the DLL (used to access DLL resources)
    static HINSTANCE ms_hDllInstance;
};

#endif // NIPROGRAMLAUNCHER_H
