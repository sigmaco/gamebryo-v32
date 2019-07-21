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

#ifndef NIPHYSXMANAGER_H
#define NIPHYSXMANAGER_H

#include "NiPhysXLibType.h"

#include <NiMain.h>
#include <NiSystem.h>

#include <efdPhysX/PhysXSDKManager.h>
#include <efdPhysX/PhysXTypes.h>

#include "NiPhysXTypes.h"

#if defined(WIN32) || defined(_XENON)
#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4512) // assignment operator could not be generated
#pragma warning(disable: 4244) // conversion from 'type' to 'type', possible loss of data
#pragma warning(disable: 4245) // conversion from 'type' to 'type', signed/unsigned mismatch
#elif defined(_PS3)
#pragma GCC system_header
#endif
#include <NxPhysics.h>
#if defined(WIN32) || defined(_XENON)
#pragma warning(pop)
#endif

/**
    NiPhysXManager is a singleton class for managing global Gamebryo-PhysX
    state: the PhysX SDK pointer and collision meshes.

    THIS CLASS HAS BEEN DEPRECATED. New applications should not use it.
    Rather, the efdPhysX::PhysXSDKManager class should be used.

    Applications cannot create an instance of this class - a single instance
    is created by the Gamebryo-PhysX static data manager when the NiPhysX
    library is loaded (be sure to include NiPhysX.h in at least one file).
*/
class NIPHYSX_ENTRY NiPhysXManager : public NiMemObject
{
public:
    /// Obtain a pointer to the singleton manager.
    static NiPhysXManager* GetPhysXManager();

    /**
        Initialize the PhysX SDK.

        DO NOT USE THIS FUNCTION. Use efdPhysX::PhysXSDKManager::Initialize.
    */
    bool Initialize(NxUserAllocator* pkAllocator = NULL,
        NxUserOutputStream* pkOutputStream = NULL,
        const NxPhysicsSDKDesc& kSDKDesc = efdPhysX::PhysXTypes::ms_kDefaultPhysicsSDKDesc,
        NxSDKCreateError* peErrorCode = 0);

    /**
        Releases the PhysX SDK and other resources such as the mesh tables.

        DO NOT USE THIS FUNCTION. Use efdPhysX::PhysXSDKManager::Shutdown.
    */
    void Shutdown();

    /**
        @name PhysX SDK Locking Functions

        DO NOT USE THESE FUNCTIONS. Use efdPhysX::PhysXSDKManager::WaitSDKLock or
        efdPhysX::PhysXSDKManager::ReleaseSDKLock.
    */
    /// @{

    /// Wait on the lock controlling access to the PhysX SDK object.
    void WaitSDKLock();

    /// Release the lock on the PhysX SDK object.
    void ReleaseSDKLock();

    /// @}

    /**
        The SDK object that is created.

        DO NOT USE THIS VARIABLE. Use efdPhysX::PhysXSDKManager::m_pPhysXSDK instead.

    */
    NxPhysicsSDK* m_pkPhysXSDK;

    /**
        Create a PhysX scene in a thread on a particular core.

        DO NOT USE THIS FUNCTION.
        Use efdPhysX::PhysXSDKManager::CreateSceneOnDifferentCore instead.
    */
    NxScene* CreateSceneOnDifferentCore(const NxSceneDesc& kDesc,
        const NiProcessorAffinity& kAffinity);

    /// Provide a string corresponding to the SDK creation error codes.
    static const char* GetSDKCreateErrorString(NxSDKCreateError* peErrorCode);

protected:

    // Cannot create one of these directly - only through SDM
    NiPhysXManager();

    // And only destructed through the SDM
    ~NiPhysXManager();

    // The one and only instance of this class
    static NiPhysXManager* ms_pPhysXManager;

    friend class NiPhysXSDM;
};

#include "NiPhysXManager.inl"

#endif  // #ifndef NIPHYSXMANAGER_H

