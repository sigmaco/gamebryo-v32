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
#ifndef EE_PHYSXALLOCATOR_H
#define EE_PHYSXALLOCATOR_H

#include <efdPhysX/efdPhysXLibType.h>

#include <efd/MemObject.h>


#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4512) // assignment operator could not be generated
#pragma warning(disable: 4244) // conversion from 'type' to 'type', possible loss of data
#pragma warning(disable: 4245) // conversion from 'type' to 'type', signed/unsigned mismatch
#elif defined(EE_PLATFORM_PS3)
#pragma GCC system_header
#endif
#include <NxUserAllocator.h>
#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(pop)
#endif

#if defined(EE_PLATFORM_WIN32)
#pragma warning(push)
#pragma warning(disable: 4275) // DLL export warning due to PhysX
#endif

namespace efdPhysX
{

/**
    This class implements the PhysX's memory allocation interface by
    passing all memory calls through to the current Foundation allocator.

    If no other allocator is passed to efdPhysX::PhysXSDKManager::Initialize then an
    instance of this class is created and passed to the PhysX SDK
    initialization function. Users wishing to override this behavior should
    create their own class that implements NxUserAllocator and pass it to
    efdPhysX::PhysXSDKManager::Initialize.
*/
class EE_EFDPHYSX_ENTRY PhysXAllocator : public NxUserAllocator, public efd::MemObject
{

public:
    /// Allocate the given number of bytes.
    ///
    /// Implemented using EE_MALLOC.
    virtual void* malloc(size_t stSize);

    /// Allocate the given number of bytes, with type information.
    ///
    /// Implemented using EE_MALLOC, ignoring the type argument.
    virtual void* malloc(size_t stSize, NxMemoryType eType);

    /// Allocate the given number of bytes, with debug information.
    ///
    /// Uses EE_MALLOC, or _Malloc if EE_USE_MEMORY_MANAGEMENT is defined.
    virtual void* mallocDEBUG(size_t stSize, const char* pcFileName, int iLine);

    /// Allocate the given number of bytes, with even more debug information.
    ///
    /// Uses EE_MALLOC, or _Malloc if EE_USE_MEMORY_MANAGEMENT is defined.
    virtual void* mallocDEBUG(size_t stSize, const char* pcFileName, int iLine,
        const char* pcClassName, NxMemoryType eType);

    /// Reallocate the given buffer.
    ///
    /// Implemented using EE_REALLOC.
    virtual void* realloc(void* pvMemory, size_t stSize);

    /// Free the given buffer.
    ///
    /// Implemented using EE_FREE.
    virtual void free(void* pvMemory);
};

} // namespace

#if defined (WIN32)
#pragma warning(pop)
#endif

#endif // #ifndef EE_PHYSXALLOCATOR_H
