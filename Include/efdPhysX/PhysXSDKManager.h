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
#ifndef EE_PHYSXSDKMANAGER_H
#define EE_PHYSXSDKMANAGER_H

#include <efdPhysX/efdPhysXLibType.h>

#include <efd/CriticalSection.h>
#include <efd/IConfigManager.h>
#include <efd/ProcessorAffinity.h>
#include <efd/StdContainers.h>
#include <efd/UniversalTypes.h>
#include <efd/utf8string.h>

#include <efdPhysX/efdPhysXSDM.h>
#include <efdPhysX/PhysXAllocator.h>
#include <efdPhysX/PhysXTypes.h>
#include <efdPhysX/PhysXUserOutput.h>

#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4512) // assignment operator could not be generated
#pragma warning(disable: 4244) // conversion from 'type' to 'type', possible loss of data
#pragma warning(disable: 4245) // conversion from 'type' to 'type', signed/unsigned mismatch
#elif defined(EE_PLATFORM_PS3)
#pragma GCC system_header
#endif
#include <NxPhysics.h>
#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(pop)
#endif

namespace efdPhysX
{

/**
    PhysXSDKManager is a singleton class for managing global PhysX
    state: the PhysX SDK pointer and collision meshes.

    Applications cannot create an instance of this class - a single instance
    is created by the efdPhysX static data manager when the efdPhysX
    library is loaded (be sure to include efdPhysX/PhysXSDKManager.h in at least one file).
*/
class EE_EFDPHYSX_ENTRY PhysXSDKManager : public efd::MemObject
{
public:
    /// Obtain a pointer to the singleton manager.
    static PhysXSDKManager* GetManager();

    /// Determine if the SDK has already been initialized.
    inline efd::Bool IsInitialized() const;

    /**
        Initialize the PhysX SDK.

        This function must be called before any PhysX
        related calls. This function creates the PhysX SDK using the given
        allocator and user output stream. If not specified, an efdPhysX::PhysXAllocator
        object and an efdPhysX::PhysXUserOutput object are created and used. The SDK
        descriptor argument is passed directly to the PhysX SDK creation
        function. Its default is a constant initialized with the default
        constructor for the NxPhysicsSDKDesc class.

        Every call to Initialize must be matched with a call to Shutdown.
    */
    efd::Bool Initialize(NxUserAllocator* pAllocator = NULL,
        NxUserOutputStream* pOutputStream = NULL,
        const NxPhysicsSDKDesc& sdkDesc = PhysXTypes::ms_kDefaultPhysicsSDKDesc,
        NxSDKCreateError* errorCode = 0);

    /**
        Releases the PhysX SDK and other resources such as the mesh tables.

        Shutdown must not be called until all pointers into PhysX related
        things have been freed, including smart pointers, because destructors
        for some PhysX objects require the PhysX SDK. Note that if
        another thread has a handle on the SDK then it will not be released
        and any resources you may still have, such as scenes or meshes, will
        not be released.
    */
    void Shutdown();

    /**
        @name PhysX SDK Locking Functions

        The PhysX SDK object is not thread safe. These functions control
        access to any critical sections that touch the PhysX SDK, and have
        critical section semantics (see efd::CriticalSection). In a multi-threaded
        environment, an application should call WaitSDKLock() before any call
        into the PhysX SDK, and call ReleaseSDKLock() when done.
    */
    /// @{

    /// Wait on the lock controlling access to the PhysX SDK object.
    void WaitSDKLock();

    /// Release the lock on the PhysX SDK object.
    void ReleaseSDKLock();

    /// @}

    /**
        The SDK object that is created.

        Not valid until Initialize has been called, nor after Shutdown has
        been called.
    */
    NxPhysicsSDK* m_pPhysXSDK;

    /**
        Create a PhysX scene in a thread on a particular core.

        The PhysX SDK creates the simulation thread at the time createScene
        is called. This function assists in targetting that thread to another
        core if necessary. Behavior is platform specific ...

        Win32: createScene is called directly. Windows will move the thread
            across processors.

        PS3: createScene is called directly. The PS3 OS will move the thread
            to either of the hardware threads as needed.

        Xbox 360: The current thread of execution is moved to the ideal
            processor specified in affinity before createScene is called.
            This has the effect of running the thread on that processor. The
            current thread is restored to its original processor after
            createScene is called.
    */
    NxScene* CreateSceneOnDifferentCore(const NxSceneDesc& desc,
        const efd::ProcessorAffinity& affinity);

    /// Provide a string corresponding to the SDK creation error codes.
    static const char* GetSDKCreateErrorString(NxSDKCreateError* perrorCode);

    /** @name Configuration

        The PhysX SDK manager may be configured through the efd::ConfigManager service.
        Here we provide the set of options that are recognized. All options must be in the
        section named PhysX.SDK (efdPhysX::PhysXSDKManager::kConfigSection).
    */
    //@{
    /// Process PhysX SDK configuration parameters held by the given config manager. This method
    /// should be called during system service creation before creating any PhysX related services.
    void Configure(efd::IConfigManager* pConfigManager);

    /// The name of the config section in which PhysX SDK options are found.
    ///
    /// The value is "PhysX.SDK".
    efd::utf8string m_kConfigSection;

    /// The option name to use for the default sleep linear velocity squared, "DefaultSleepLinear".
    efd::utf8string m_kConfigDefaultSleepLinVel;

    /// The option name to use for the default sleep angular velocity squared,
    /// "DefaultSleepAngular".
    efd::utf8string m_kConfigDefaultSleepAngVel;

    /// The option name to use for the default sleep energy, "DefaultSleepEnergy".
    efd::utf8string m_kConfigDefaultSleepEnergy;

    /// The option name to use for the Visual Remote Debugger host, "VRDHost".
    efd::utf8string m_kConfigVRDHost;

    /// The option name to use for the Visual Remote Debugger port, "VRDPort".
    ///
    /// This option is only used if "VRDHost" is provided, and it defaults to 5425 if not provided.
    efd::utf8string m_kConfigVRDPort;

    /**
        The option name to use for the Visual Remote Debugger event mask, "VRDEventMask".

        This option is only used if "VRDHost" is provided, and it defaults to
        NX_DBG_EVENTMASK_EVERYTHING if not provided.
    */
    efd::utf8string m_kConfigVRDEventMask;

    //@}

protected:

    // Cannot create one of these directly - only through SDM
    PhysXSDKManager();

    // And only destructed through the SDM
    ~PhysXSDKManager();

    // Some platforms require specific initialization or shutdown. These
    // functions are implemented in platform specific files.
    efd::Bool PlatformSpecificPostSDKInit();
    void PlatformSpecificSDKShutdown();

    // Only non-NULL if the user did not provide their own versions to Initialize().
    PhysXUserOutput* m_pOutputStream;
    PhysXAllocator* m_pAllocator;

    // The one and only instance of this class
    static PhysXSDKManager* ms_pPhysXManager;

    // For managing the locks
    efd::CriticalSection m_sdkCritSect;

    friend class efdPhysXSDM;
};

/// Including efdPhysX/PhysXSDKManager.h catches this static variable invoking the SDM functions.
static efdPhysXSDM efdPhysXSDMObject;

} // namepsace efdPhysX

#include <efdPhysX/PhysXSDKManager.inl>

#endif  // #ifndef EE_PHYSXSDKMANAGER_H

