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
#ifndef EE_ALLOCATOR_H
#define EE_ALLOCATOR_H

#include <efd/efdLibType.h>
#include <efd/MemoryDefines.h>

namespace efd
{

/**
    This class defines the interface for all memory allocators. Derived classes
    may choose to implement object pooling, memory tracking behavior, or memory
    error debugging. Note that each allocator is responsible for its own
    thread-safety.
*/
class EE_EFD_ENTRY IAllocator
{
public:
    /// Virtual destructor
    inline virtual ~IAllocator() {}

   /**
        Allocate stSizeInBytes bytes of memory guaranteeing stAlignment
        alignment if possible for the returned address.

        @note that the size and alignment are passed-by-reference. This allows
        the allocator to adjust the values internally and pass the results back
        to the caller. This functionality is useful in the event of nesting
        allocators for memory tracking and debugging purposes. The additional
        arguments are used by memory tracking and debugging routines.

        MemHint indicates the intended usage for the memory being allocated which
        allows the allocator to optionally pick the most efficient memory type or
        location, as well as providing additional information to the memory tracker
        when enabled.

        The eEventType argument indicates what external method was used to allocate
        the data. This may provide additional information to a memory debugging
        system or may be used at runtime to determine allocator behavior.

        pcFile, iLine, and pcFunction are the file name, line number, and function
        name for the function calling Allocate.
    */
    virtual void* Allocate(
        size_t& stSizeInBytes,
        size_t& stAlignment,
        MemHint kHint,
        MemEventType eEventType,
        const char* pcFile,
        int iLine,
        const char* pcFunction) = 0;

    /**
        Free the memory at the specified address.

        In some situations, the deallocation routine may know how large it was
        when allocated. If so, the stSizeInBytes argument will be the size initially
        requested. If this size is unknown, the correct value for the argument is
        EE_MEM_DEALLOC_SIZE_DEFAULT.

        The eEventType argument indicates what external method was used to deallocate
        the data. This may provide additional information to a memory debugging system
        or may be used at runtime to determine allocator behavior.
    */
    virtual void Deallocate(
        void* pvMemory,
        MemEventType eEventType,
        size_t stSizeInBytes) = 0;

    /**
        Reallocate the memory at the specified address, guaranteeing
        stAlignment if possible for the returned address. Note that if
        stSizeInBytes is zero, this method functions like Deallocate. If
        pvMemory is NULL, this method functions exactly like Allocate. In some
        cases, the outer memory management system may know the size prior to
        deallocation or reallocation, in this case stSizeCurrent should match
        the size and the compiler provides size hint should be provided. If
        this size is unknown, the correct value for the argument is
        EE_MEM_DEALLOC_SIZE_DEFAULT.

        MemHint indicates the intended usage for the memory being allocated which
        allows the allocator to optionally pick the most efficient memory type or
        location, as well as providing additional information to the memory tracker
        when enabled.

        The eEventType argument indicates what external method was used to reallocate
        the date. This may provide additional information to a memory debugging
        system or may be used at runtime to determine allocator behavior.

        pcFile, iLine, and pcFunction are the file name, line number, and function
        name for the function calling Reallocate.
    */
    virtual void* Reallocate(
        void* pvMemory,
        size_t& stSizeInBytes,
        size_t& stAlignment,
        MemHint kHint,
        MemEventType eEventType,
        size_t stSizeCurrent,
        const char* pcFile,
        int iLine,
        const char* pcFunction) = 0;

    /// @name Functions to allow tracking of memory
    /// These functions should NOT touch the input addresses in any way.
    //@{
    virtual bool TrackAllocate(
        const void* const pvMemory,
        size_t stSizeInBytes,
        MemHint kHint,
        MemEventType eEventType,
        const char* pcFile,
        int iLine,
        const char* pcFunction) = 0;

    virtual bool TrackDeallocate(
        const void* const pvMemory,
        MemEventType eEventType) = 0;
    //@}


    /**
        Function to allow the marking of memory allocations.

        This is used by a memory tracker / debugger to identify specific
        allocations. pcMarkerType, pcClassifier, and pcString are all free form
        strings that uniquely identify the allocation.
    */
    virtual bool SetMarker(
        const char* pcMarkerType,
        const char* pcClassifier,
        const char* pcString) = 0;

    /// @name Initialization and cleanup
    //@{

    /// Initialize the allocator. Called prior to any allocations.
    virtual void Initialize() = 0;

    /// Shutdown the allocator. No allocations are allowed after shutdown.
    virtual void Shutdown() = 0;

    /// Initialize any per-thread aspects of the allocator.  Called once for each thread.
    inline virtual void PerThreadInit() {}

    /// Shutdown any per-thread aspects of the allocator.  Called once for each thread.
    inline virtual void PerThreadShutdown() {}
    //@}

    /// Verify the provided address is valid and return false if it is not.
    virtual bool VerifyAddress(const void* pvMemory) = 0;

    /**
        Function to allow the memory allocator an opportunity to create an
        IMemLogHandler for logging memory allocations. This method will be called on
        the allocator after the MemManager has been constructed.
    */
    virtual void CreateMemoryLogHandler() = 0;
};

} // end namespace efd

#endif
