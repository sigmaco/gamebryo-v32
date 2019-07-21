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
#ifndef EE_MEMOBJECT_H
#define EE_MEMOBJECT_H

#include <efd/efdLibType.h>
#include <efd/MemoryDefines.h>

namespace efd
{

/**
    MemObject implements interfaces overriding the global "new" and "delete" operators.  All
    derived classes will funnel their allocations/deallocations through the MemManager object.

    External code should never call "new" or "delete" on MemObjects directly.  Rather, they should
    use "EE_NEW" and "EE_DELETE".  This approach enables allocation tracking in builds defining
    the EE_MEMORY_DEBUGGER symbol.
*/
class EE_EFD_ENTRY MemObject
{

#if !defined(__SPU__)

#ifdef EE_MEMORY_DEBUGGER

    private:

        /*
            The memory debugger uses the file, line, and function routines.
            So new and new[] should be unavailable to the outer application.
        */
        static void* operator new(size_t stSize,
            MemHint kHint = EE_MEMHINT_NONE)
#if !defined(EE_MEMORY_ENABLE_EXCEPTIONS)
            EE_EMPTY_THROW
#endif
            ;

        static void* operator new[](size_t stSize,
            MemHint kHint = EE_MEMHINT_NONE)
#if !defined(EE_MEMORY_ENABLE_EXCEPTIONS)
            EE_EMPTY_THROW
#endif
            ;

    public:

        /**
            @name Overloaded Operator New Functions with MemoryHints
        */
        //@{
        /**
            Overloaded operator new functions to handle allocation and construction of new objects
            using a custom memory manager.

            @param stSize Size of the memory being allocated.
            @param kHint Indicates the intended usage for the memory being allocated, which
                enables the allocator to optionally pick the most efficient memory type or
                location, as well as providing additional information to the memory tracker when
                enabled.
            @param pcSourceFile File name for the function calling Allocate(), tracked for memory
                logging purposes.
            @param iSourceLine Line number for the function calling Allocate(), tracked for memory
                logging purposes.
            @param pcFunction Function name for the function calling Allocate(), tracked for
                memory logging purposes.
            @return Pointer to void (standard return value for new()).
        */
        static void *operator new(
            size_t stSize,
            MemHint kHint,
            const char *pcSourceFile,
            int iSourceLine,
            const char* pcFunction);
        static void *operator new[](
            size_t stSize,
            MemHint kHint,
            const char *pcSourceFile,
            int iSourceLine,
            const char* pcFunction);
        //@}

        /// @cond EMERGENT_INTERNAL

        /*
            @name Overloaded Operator Delete Functions for Exception Handling
            Required for exception handling in the compiler.
            These operators should not be used in practice.
        */
        //@{
        inline static void operator delete(
            void*,
            MemHint,
            const char*,
            int,
            const char*);
        inline static void operator delete[](
            void*,
            MemHint,
            const char*,
            int,
            const char*);
        //@}
        /// @endcond

#else   // EE_MEMORY_DEBUGGER

    public:
        /**
            @name Overloaded Operator New Functions with MemoryHints
        */
        //@{
        /**
            Overloaded operator new functions to handle allocation and construction of new objects
            using a custom memory manager.

            @param stSize Size of the memory being allocated.
            @param kHint Indicates the intended usage for the memory being allocated, which
                enables the allocator to optionally pick the most efficient memory type or
                location, as well as providing additional information to the memory tracker when
                enabled.
            @return Pointer to void (standard return value for new()).
        */
        static void* operator new(
            size_t stSize,
            MemHint kHint);
        static void* operator new[](
            size_t stSize,
            MemHint kHint);
        //@}

        /// @cond EMERGENT_INTERNAL

        /*
            @name Overloaded Operator Delete Functions for Exception Handling with MemHints
            Required for exception handling in the compiler.
            These operators should not be used in practice.
        */
        //@{
        inline static void operator delete(
            void *,
            MemHint);
        inline static void operator delete[](
            void *,
            MemHint);
        //@}
        /// @endcond

#endif  // EE_MEMORY_DEBUGGER

    public:
        /// @name Overloaded Operator Delete Functions
        /// These delete and delete[] operators must be implemented in EE_MEMORY_DEBUGGER and
        /// non-EE_MEMORY_DEBUGGER builds.
        //@{
        static void operator delete(
            void *pvMem,
            size_t stElementSize);
        static void operator delete[](
            void *pvMem,
            size_t stElementSize);
        //@}

        /// @name Overloaded Operator New Functions for In-Place Construction.
        /// Placement new and delete operators must be exposed as well to enable in-place 
        /// construction.
        //@{
        inline static void* operator new(
            size_t,
            void* p);
        inline static void* operator new[](
            size_t,
            void* p);
        inline static void operator delete(
            void *,
            void*);
        inline static void operator delete[](
            void *,
            void*);
        //@}

#endif  // !defined(__SPU__)

};

} //namespace efd

#include <efd/MemObject.inl>

#endif // EEMEMOBJECT_H
