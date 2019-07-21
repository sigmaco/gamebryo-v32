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
#ifndef EE_MEMMANAGER_H
#define EE_MEMMANAGER_H

#include <efd/efdLibType.h>
#include <efd/RTLib.h>
#include <efd/OS.h>
#include <efd/IAllocator.h>

namespace efd
{
/**
    MemManager is a platform-independent wrapper that is designed to provide
    an entry point for user-defined memory management. The MemManager contains
    an IAllocator instance and forwards all alloc/dealloc/realloc requests
    through that instance. The IAllocator is specified through the
    InitializeMemoryManager function. In static libs, this function can be
    declared by the application code. "DefaultInitializeMemoryManager.h"
    contains the default implementation of this function and should only be
    included if default behavior is desired. Dynamic libraries
    must use the default implementation. The Get method will create the singleton,
    allowing for static/pre-main allocations to occur.
*/
class EE_EFD_ENTRY MemManager
{
public:
    /// Singleton access. The first call will create the manager.
    static MemManager& Get();

    /// Return true if the MemManager is initialized.
    static inline bool IsInitialized();

    /// @see IAllocator::Allocate
    inline void* Allocate(
        size_t stSize,
        size_t stAlignment,
        MemHint kHint,
        MemEventType eEventType,
        const char *pcSourceFile = EE_MEM_FILE_DEFAULT,
        int iSourceLine = EE_MEM_LINE_DEFAULT,
        const char* pcFunction = EE_MEM_FUNCTION_DEFAULT);

    /// @see IAllocator::Reallocate
    inline void* Reallocate(
        void* pvMem,
        size_t stSize,
        size_t stAlignment,
        MemHint kHint,
        MemEventType eEventType,
        size_t stSizeCurrent = EE_MEM_DEALLOC_SIZE_DEFAULT,
        const char *pcSourceFile = EE_MEM_FILE_DEFAULT,
        int iSourceLine = EE_MEM_LINE_DEFAULT,
        const char* pcFunction = EE_MEM_FUNCTION_DEFAULT);

    /// @see IAllocator::Deallocate
    inline void Deallocate(
        void* pvMem,
        MemEventType eEventType,
        size_t stSizeinBytes= EE_MEM_DEALLOC_SIZE_DEFAULT);


    /// @see IAllocator::TrackAllocate
    inline bool TrackAllocate(
        const void* const pvMemory,
        size_t stSizeInBytes,
        MemHint kHint,
        MemEventType eEventType,
        const char *pcSourceFile = EE_MEM_FILE_DEFAULT,
        int iSourceLine = EE_MEM_LINE_DEFAULT,
        const char* pcFunction = EE_MEM_FUNCTION_DEFAULT);

    /// @see IAllocator::TrackDeallocate
    inline bool TrackDeallocate(
        const void* const pvMemory,
        MemEventType eEventType);

    /// @see IAllocator::SetMarker
    bool SetMarker(const char* pcMarkerType, const char* pcClassifier,
        const char* pcString);

    /// Static init
    static void _SDMInit();

    /// Static shutdown
    static void _SDMShutdown();

    /// Per-thread static init
    static void _SDMPerThreadInit();

    /// Per-thread static shutdown
    static void _SDMPerThreadShutdown();

    /// @see IAllocator::VerifyAddress
    static bool VerifyAddress(const void* pvMemory);

    /// Utility functions to "toString" an event type enumeration
    static const char* MemEventTypeToString(MemEventType eEventType);

    /// Returns the allocator in use
    static IAllocator* GetAllocator();
protected:
    // The only method allowed to construct a MemManager object is MemManager::Get
    MemManager();
    ~MemManager();

    static void CreateMemoryLogHandler();

    inline MemManager(const MemManager&) {};

    static MemManager* ms_pkMemManager;

    IAllocator* m_pkAllocator;
    bool m_bMemLogHandlerCreated;
};

/// @name GlobalMemoryAllocator from MemManager.h
//@{

/**
    Recall that MemManager is a platform-independent wrapper that is designed to provide an entry
    point for user-defined memory management.  The MemManager contains an IAllocator instance and
    forwards all alloc/dealloc/realloc requests through that instance.  The IAllocator to be used
    is specified by calling the CreateGlobalMemoryAllocator() function.

    Note: This method is *not* implemented inside of the efd library in statically linked builds.
    It must be implemented for an application to link successfully.  A default implementation is
    provided in the file efd/DefaultInitializeMemoryManager.h, which can be included in the
    application if there isn't a custom allocator otherwise provided.

    Dynamically linked builds include the default allocator; to change this behavior, the code in
    MemManager.cpp can be modified.

    If you have linker problems indicating that efd::CreateGlobalMemoryAllocator is not found,
    then you need to either invoke EE_USE_DEFAULT_ALLOCATOR or provide a custom implementation.

    @return Pointer to an IAllocator instance.
*/
EE_EFD_ENTRY efd::IAllocator* CreateGlobalMemoryAllocator();

//@}

} // namespace efd

#include <efd/MemManager.inl>

#endif // #ifndef EE_MEMMANAGER_H
