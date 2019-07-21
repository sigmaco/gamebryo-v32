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
#ifndef EE_STATICDATAMANAGER_H
#define EE_STATICDATAMANAGER_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/SDMMacros.h>
#include <efd/InitOptions.h>

namespace efd
{

/// The maximum number of libraries that can have SDM functions registered
/// with the manager.
const efd::UInt32 EE_NUM_LIBRARIES = 32;

/**
    The StaticDataManager manages creation and cleanup of all dynamically allocated non-local
    static objects in the system. The foundation avoids allocating memory from the heap
    pre-main where possible. Therefore, the StaticDataManager allows callbacks to be registered
    with the system during C++ static initialization time which are then called once the system
    is initialized.
*/
class EE_EFD_ENTRY StaticDataManager
{
public:
    /// Callback function signature of the Init function.
    typedef void (*InitFunction)(void);

    /// Callback function signature of the Shutdown function.
    typedef void (*ShutdownFunction)(void);

    /**
        This function is called by the SDM constructor of each library. It is used to register the
        given library name with the given the Init and Shutdown functions. The dependencies
        string should contain a space-separated list of library names with SDM functions that must
        be initialized before this library is initialized. The efd library should not appear in
        this list. For example, the string for NiMesh is "NiFloodgate NiMain".
        routine.
        @param libraryName  The name of the library being registered
        @param pInit        A pointer to the init method.
        @param pShutdown    A pointer to the shutdown method.
        @param pPerThreadInit Callback function for init.
        @param pPerThreadShutdown Callback function for shutdown.
        @param dependencies A space-separated list of libraries that this library depends on
    */
    static void AddLibrary(
        const char* libraryName,
        InitFunction pInit,
        ShutdownFunction pShutdown,
        InitFunction pPerThreadInit,
        ShutdownFunction pPerThreadShutdown,
        const char* dependencies);

    /**
        This function exists to prevent libraries from being shut down after they are unloaded.
        With DLL's, this function is called by the DLL_PROCESS_DETACH case of DllMain for that
        library. It is not called by statically linked Gamebryo libraries, because there is no
        way to "unload" a statically linked library.

        @param libraryName The name of the library that was previously registered.
    */
    static void RemoveLibrary(const char* libraryName);

    /**
        This function is called by EE_INIT. The method initializes components
        in the following manor:
        @par First, it explicitly calls UtilitiesSDM::Init. Second, this method
            will call all Init functions that have been registered in the order
            that they are added.
        @note Since Init functions are registered during C++ static init time,
            the order is not deterministic. Therefore, static data should not
            depend on other static data across modules.
    */
    static void Init(const InitOptions* pOptions = NULL);

    /**
        This function is called by EE_SHUTDOWN. It calls the Shutdown function
        for all registered libraries in the following manor:
        @par First it explicitly calls UtilitiesSDM::Shutdown, and second, the
            Shutdown method of all remaining libraries that have been
            registered is invoked.
    */
    static void Shutdown();

    /**
        This function is called by EE_INIT on the main thread, or by efd::Thread
        on all other Emergent threads, and should be called explicitly if a custom
        threading solution is used.  It initializes thread-local mechanisms such
        as per-thread allocation pools.
    */
    static void PerThreadInit();

    /**
        This function is called by EE_SHUTDOWN on the main thread, or by efd::Thread
        on all other Emergent threads, and should be called explicitly if a custom
        threading solution is used.  It cleans up thread-local mechanisms such
        as per-thread allocation pools.
    */
    static void PerThreadShutdown();

    /**
        This function is called by the DLL_PROCESS_ATTACH section of DllMain for each library,
        as well as by StaticDataManager::Init. It causes the StaticDataManager to initialize
        all libraries, using each library's registered Init function, that have been added
        (via AddLibrary) but have not yet been initialized. The function is not called
        directly by statically linked libraries - it is called via EE_INIT.

        This function does nothing if Init has not been called. The first time this function is
        called after Init (typically from Init itself), the libraries are dependency sorted
        before processing. Subsequence calls will check that all the dependencies of newly
        added libraries have already been initialized, but will not process dependencies for
        those new libraries.
    */
    static void ProcessAccumulatedLibraries();


    /**
        Gets a pointer to the initialization options that were passed to the static data manager
        when it was created using EE_INIT.
        @return A pointer to the system's initialization options.
    */
    static const InitOptions* GetInitOptions();

    /**
        The static data manager is initialized during Init() and uninitialized during Shutdown().
        @return True if the static data manager is currently initialized
    */
    static bool IsInitialized();

private:
    struct LibraryNode
    {
        /// The name of the library.
        const char* m_pcName;

        /// A white-space separated list of library names on which this
        /// library depends.
        const char* m_pcDependsOn;

        /// The initialization function.
        InitFunction m_pfnInitFunction;

        /// The per-thread initialization function.
        InitFunction m_pfnPerThreadInitFunction;

        /// The shutdown function.
        ShutdownFunction m_pfnShutdownFunction;

        /// The per-thread shutdown function.
        ShutdownFunction m_pfnPerThreadShutdownFunction;

        /// Edges in the graph that is used to find an initialization order.
        UInt8* m_puiDependencies;
        UInt8 m_uiNumDependencies;
        UInt8 m_uiMaxDependencies;

        /// The index into the array of all libraries
        UInt8 m_uiIndex;
    };

    /// Returns true if the library at the given index has other libraries
    /// that depend on it.
    static bool HasDependents(const UInt8 uiLibIndex);

    /// Returns true if all of the dependencies of the given library
    /// have been initialized.
    static bool DependenciesInitialized(const UInt8 uiLibIndex);

    /// Computes an ordering that has all dependents initialized after their
    /// dependencies.
    static bool ComputeProcessOrder();

    /// Builds up, for a single node, the dependency graph for computing
    /// the process order.
    static bool ConstructDependencyGraph(const UInt8 uiLibIndex,
        UInt8* auiUnvisited, UInt8& uiNumUnvisited,
        UInt8* auiDependencyFree, UInt8& uiNumDependencyFree);

    /// Adds a single dependency.
    static void AddDependency(const UInt8 uiLibIndex,
        const UInt8 uiDependentIndex);

    /// Removes all the dependencies on the given index. Used in computing
    /// the processing order.
    static void RemoveDependencies(const UInt8 uiLibIndex,
        UInt8* auiUnvisited, UInt8& uiNumUnvisited,
        UInt8* auiDependencyFree, UInt8& uiNumDependencyFree);

    static LibraryNode ms_akLibraries[EE_NUM_LIBRARIES];
    static UInt8 ms_auiProcessOrder[EE_NUM_LIBRARIES];
    static UInt8 ms_uiNumLibraries;
    static UInt8 ms_uiNumInitializedLibraries;
    static bool ms_autoCreatedInitOptions;
    static bool ms_initialized;
    static const InitOptions* ms_pInitOptions;
};

#define EE_INIT efd::StaticDataManager::Init
#define EE_SHUTDOWN efd::StaticDataManager::Shutdown

#include <efd/StaticDataManager.inl>

}

#endif
