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
#ifndef EE_DEFAULTINITIALIZEMEMORYMANAGER_H
#define EE_DEFAULTINITIALIZEMEMORYMANAGER_H

#include <efd/MemTracker.h>
#include <efd/StandardAllocator.h>
#include <efd/MemManager.h>
#include <efd/DefaultInitializeMemoryLogHandler.h>

namespace efd
{
    /**
        Default implementation of the CreateGlobalMemoryAllocator() function.

        To use the default implementation in a statically linked application, invoke the macro
        EE_USE_DEFAULT_ALLOCATOR in a source file linked into the application.

        This implementation is always used in dynamically linked versions
        (see MemManager.cpp for more details).

        @return Pointer to an IAllocator instance.
    */
    inline IAllocator* CreateDefaultGlobalMemoryAllocator(bool silentPremainAllocations = false);

} // end namespace efd


/**
    Include this macro in a source file to get the default memory allocator.  If you want
    to implement a custom Gamebryo allocator, implement a CreateGlobalMemoryAllocator method
    that returns the custom allocator.

    This macro also invokes:
      - EE_USE_DEFAULT_MEMORY_LOG_HANDLER
    saving separate invocations.
*/
#if defined(EE_EFD_IMPORT) || ((defined(_WINDLL) || defined(USEDLL)) && !defined(EE_EFD_EXPORT))
    // The macro does not create the allocator in DLL import builds since it is already
    // included via the DLL build of MemManager.cpp
    #define EE_USE_DEFAULT_ALLOCATOR
    #define EE_USE_DEPRECATED_PREMAIN_ALLOCATOR
#else
    #define EE_USE_DEFAULT_ALLOCATOR \
        EE_EFD_ENTRY efd::IAllocator* efd::CreateGlobalMemoryAllocator() \
        { \
            return efd::CreateDefaultGlobalMemoryAllocator(false); \
        } \
        EE_USE_DEFAULT_MEMORY_LOG_HANDLER

    #define EE_USE_DEPRECATED_PREMAIN_ALLOCATOR \
        EE_EFD_ENTRY efd::IAllocator* efd::CreateGlobalMemoryAllocator() \
        { \
            return efd::CreateDefaultGlobalMemoryAllocator(true); \
        } \
        EE_USE_DEFAULT_MEMORY_LOG_HANDLER
#endif

#include <efd/DefaultInitializeMemoryManager.inl>

#endif // #ifndef EE_DEFAULTINITIALIZEMEMORYMANAGER_H
