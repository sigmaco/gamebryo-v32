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
#ifndef EE_MEMORYDEFINES_H
#define EE_MEMORYDEFINES_H

#include <efd/OS.h>

#include <efd/efdLibType.h>
#include <efd/MemHint.h>

#if defined(EE_PLATFORM_PS3)
#include <stddef.h>
#include <alloca.h>
#else
#include <malloc.h>
#endif

// Provide EE_USE_MEMORY_MANAGEMENT in the configuration to enable
// memory debugging and tracking.  By default, it is enabled for Debug builds.
#if defined(EE_USE_MEMORY_MANAGEMENT) && !defined(__SPU__)
#define EE_MEMORY_DEBUGGER
#endif

// Provide EE_USE_MEMTRACKER_STACKTRACE in the configuration to collect stack traces for all
// memory allocations.  You must also provide EE_USE_MEMORY_MANAGEMENT for this to take effect.
// By default, it is disabled for all builds.
#if defined(EE_USE_MEMTRACKER_STACKTRACE) && defined(EE_MEMORY_DEBUGGER)
    #if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_LINUX)
        #define EE_MEMTRACKER_STACKTRACE
    #endif
#endif

// Define EE_USE_MEMTRACKER_SNAPSHOT to enable the MemTracker 'snapshot' APIs which can be used to
// analyze allocations made in specific portions of the code.
#if defined(EE_USE_MEMTRACKER_SNAPSHOT) && defined(EE_MEMORY_DEBUGGER)
    #define EE_MEMTRACKER_SNAPSHOT
#endif

// Define EE_USE_MEMTRACKER_DETAILEDREPORTING to enable registering display functions via
// EE_MEM_SETDETAILEDREPORT that can parse leaked objects into useful descriptions of what leaked.
#if defined(EE_USE_MEMTRACKER_DETAILEDREPORTING) && defined(EE_MEMORY_DEBUGGER)
    #define EE_MEMTRACKER_DETAILEDREPORTING
#endif

namespace efd
{

//------------------------------------------------------------------------------------------------
// Determine whether or not to store the File, Line, Function data.
//------------------------------------------------------------------------------------------------

///
///   Determine the overall allocation type. When an object is allocated with
///   an allocation routine, it should be deallocated with its corresponding
///   deallocation routine.
///
/// @name Memory Event Types from  MemoryDefines.h
//@{
enum MemEventType
{
    EE_MET_UNKNOWN = 0,             /*<! Unknown allocation/deallocation type.
                                         This type will cause assertions in
                                         the memory management interfaces. */
    EE_MET_NEW = 1,                 /*<! Allocated through EE_NEW.
                                       Should be deallocated with EE_DELETE */
    EE_MET_NEW_ARRAY = 2,           /*<! Allocated through EE_NEW[].
                                       Should be deallocated with EE_DELETE[] */
    EE_MET_DELETE = 3,              /*<! Deallocated with EE_DELETE. */

    EE_MET_DELETE_ARRAY = 4,        /*<! Deallocated with EE_DELETE[] */

    EE_MET_MALLOC = 5,              /*<! Allocated through EE_MALLOC.
                                       Should be deallocated with EE_FREE */
    EE_MET_REALLOC = 6,             /*<! Allocated through EE_REALLOC.
                                       Should be deallocated with EE_FREE. */
    EE_MET_ALIGNEDMALLOC = 7,       /*<! Allocated through EE_ALIGNED_ALLOC.
                                       Should be deallocated with
                                       EE_ALIGNED_FREE */
    EE_MET_ALIGNEDREALLOC = 8,      /*<! Allocated through EE_ALIGNED_REALLOC.
                                       Should be deallocated with
                                       EE_ALIGNED_FREE */
    EE_MET_FREE = 9,                /*<! Deallocated with EE_FREE */
    EE_MET_ALIGNEDFREE = 10,        /*<! Deallocated with EE_ALIGNED_FREE */
    EE_MET_EXTERNALALLOC = 11,      /*<! Track external alloc, EE_TRACK_ALLOC */
    EE_MET_EXTERNALFREE = 12,       /*<! Track external dealloc, EE_TRACK_FREE */
    EE_MET_MARKER = 13              /*<! Memory event marker, EE_MEM_MARKER */
};
//@}

/// @name Allocation macros and functions from MemoryDefines.h.
//@{
/**
  EE_NEW and EE_DELETE are ONLY used for MemObject-derived classes.
  This lets Foundation store the file, line, function information depending
  on the build target.

  EE_ALLOC/EE_MALLOC/EE_REALLOC and EE_FREE should be used for
  any non-MemObject object or intrinsic type. Note that they do not call
  global new or delete, nor will they call constructors or destructors.
*/
#define EE_MEM_FILE_DEFAULT 0
#define EE_MEM_LINE_DEFAULT -1
#define EE_MEM_FUNCTION_DEFAULT 0
#define EE_MEM_DEALLOC_SIZE_DEFAULT (size_t)-1
#define EE_MEM_MARKER_BEGIN "BEGIN"
#define EE_MEM_MARKER_END "END"

#ifdef EE_PLATFORM_XBOX360
    #define EE_MEM_ALIGNMENT_DEFAULT  16
#elif defined(EE_PLATFORM_PS3)
    #define EE_MEM_ALIGNMENT_DEFAULT  16
#elif defined(EE_PLATFORM_LINUX)
    //GNU libc malloc() always returns 8-byte aligned memory addresses
    #define EE_MEM_ALIGNMENT_DEFAULT  8
#elif defined(EE_PLATFORM_WIN32)
    #define EE_MEM_ALIGNMENT_DEFAULT  16
#else
    #error No platform defined!
#endif

/// @name Build-independent memory management routines from MemoryDefines.h
//@{
EE_EFD_ENTRY void _Free(void* pvMemory, size_t stSizeInBytes = EE_MEM_DEALLOC_SIZE_DEFAULT);
EE_EFD_ENTRY void _AlignedFree(void* pvMemory, size_t stSizeInBytes = EE_MEM_DEALLOC_SIZE_DEFAULT);

#define EE_IS_POWER_OF_TWO(x)   (((x)&(x-1)) == 0)
//@}

/// @name Build-dependent memory management routines from MemoryDefines.h
//@{
#if defined(EE_MEMORY_DEBUGGER)
    EE_EFD_ENTRY void* _Malloc(size_t stSizeInBytes, MemHint kHint,
        const char* pcSourceFile, int iSourceLine, const char* pcFunction);

    EE_EFD_ENTRY void* _AlignedMalloc(size_t stSizeInBytes,
        size_t stAlignment, MemHint kHint, const char* pcSourceFile,
        int iSourceLine, const char* pcFunction);

    EE_EFD_ENTRY void* _Realloc(void *memblock, size_t stSizeInBytes,
        MemHint kHint, const char* pcSourceFile, int iSourceLine,
        const char* pcFunction);

    EE_EFD_ENTRY void* _AlignedRealloc(void *memblock,
        size_t stSizeInBytes, size_t stAlignment, MemHint kHint,
        const char* pcSourceFile, int iSourceLine, const char* pcFunction);

    EE_EFD_ENTRY bool _VerifyAddress(const void* pvMemory);

    EE_EFD_ENTRY bool _TrackAlloc(const void* pvMemory,
        size_t stSizeInBytes, MemHint kHint, const char* pcSourceFile,
        int iSourceLine, const char* pcFunction);

    EE_EFD_ENTRY bool _TrackFree(const void* pvMemory);

    EE_EFD_ENTRY bool _MemMarker(const char* pcMarkerType,
        const char* pcClassifier, const char* pcString);
    EE_EFD_ENTRY bool _MemMarker(const char* pcMarkerType,
        const char* pcClassifier, unsigned int uiValue);
    EE_EFD_ENTRY bool _MemMarker(const char* pcMarkerType,
        const char* pcClassifier, const void* const pvValue);

    #define EE_NEW new(EE_MEMHINT_NONE, __FILE__,__LINE__,__FUNCTION__)
    #define EE_NEW2(hint) new(hint,__FILE__,__LINE__,__FUNCTION__)
    #define EE_DELETE delete

    #define EE_ALLOC(T, count) ((T*)efd::_Malloc(sizeof(T)*(count), \
        EE_MEMHINT_NONE, __FILE__, __LINE__, __FUNCTION__))

    #define EE_ALLOC2(T, count, hint) ((T*)efd::_Malloc(sizeof(T)*(count), \
        hint, __FILE__, __LINE__, __FUNCTION__))

    #define EE_ALIGNED_ALLOC(T, count, alignment) ((T*)efd::_AlignedMalloc(\
        sizeof(T)*(count), alignment, EE_MEMHINT_NONE, __FILE__, __LINE__, __FUNCTION__))

    #define EE_ALIGNED_ALLOC2(T, count, alignment, hint) ((T*)efd::_AlignedMalloc(\
        sizeof(T)*(count), alignment, hint, \
        __FILE__, __LINE__, __FUNCTION__))


    #define EE_ALIGNED_MALLOC(size, alignment) (efd::_AlignedMalloc(\
        size, alignment, EE_MEMHINT_NONE, \
        __FILE__, __LINE__, __FUNCTION__))

    #define EE_ALIGNED_MALLOC2(size, alignment, hint) (efd::_AlignedMalloc(\
        size, alignment, hint, \
        __FILE__, __LINE__, __FUNCTION__))

    #define EE_MALLOC(size) (efd::_Malloc(size, EE_MEMHINT_NONE, \
        __FILE__, __LINE__, __FUNCTION__))

    #define EE_MALLOC2(size, hint) (efd::_Malloc(size, hint, \
        __FILE__, __LINE__, __FUNCTION__))

    #define EE_REALLOC(memblock, size) (efd::_Realloc(memblock, size, \
        EE_MEMHINT_NONE, __FILE__, __LINE__, __FUNCTION__))

    #define EE_REALLOC2(memblock, size, hint) (efd::_Realloc(memblock, size, \
        hint, __FILE__, __LINE__, __FUNCTION__))

    #define EE_ALIGNED_REALLOC(memblock, size, alignment) (efd::_AlignedRealloc(\
        memblock, size, alignment, EE_MEMHINT_NONE, __FILE__, __LINE__, __FUNCTION__))
    #define EE_ALIGNED_REALLOC2(memblock, size, alignment, hint) (efd::_AlignedRealloc(\
        memblock, size, alignment, hint, __FILE__, __LINE__, __FUNCTION__))

    #define EE_FREE(p) efd::_Free(p)
    #define EE_ALIGNED_FREE(p) efd::_AlignedFree(p)

    #define EE_FREE_KNOWN_SIZE(p, sizeInBytes) efd::_Free(p, sizeInBytes)
    #define EE_ALIGNED_FREE_KNOWN_SIZE(p, sizeInBytes) efd::_AlignedFree(p, sizeInBytes)

    #define EE_VERIFY_ADDRESS(x) efd::_VerifyAddress(x)

    #define EE_TRACK_ALLOC(pointer, sizeInBytes) (efd::_TrackAlloc(\
        pointer, sizeInBytes, EE_MEMHINT_NONE, __FILE__, __LINE__, __FUNCTION__))

    #define EE_TRACK_ALLOC2(pointer, sizeInBytes, hint) (efd::_TrackAlloc(\
        pointer, sizeInBytes, hint, __FILE__, __LINE__, __FUNCTION__))
    #define EE_TRACK_FREE(pointer)  (efd::_TrackFree(pointer))
    #define EE_MEM_MARKER(markerType, classifier, string) (efd::_MemMarker(\
        markerType, classifier, string))
#else
    EE_EFD_ENTRY void* _Malloc(size_t stSizeInBytes, MemHint kHint);

    EE_EFD_ENTRY void* _AlignedMalloc(size_t stSizeInBytes,
        size_t stAlignment, MemHint kHint);

    EE_EFD_ENTRY void* _Realloc(void *memblock, size_t stSizeInBytes, MemHint kHint);

    EE_EFD_ENTRY void* _AlignedRealloc(void* pvMemblock,
        size_t stSizeInBytes, size_t stAlignment, MemHint kHint);

    #define EE_VERIFY_ADDRESS(x) false

    #define EE_NEW new(efd::MemHint(efd::MemHint::NONE))
    #define EE_NEW2(hint) new(hint)
    #define EE_DELETE delete

    #define EE_ALLOC(T, count) \
        ((T*)efd::_Malloc(sizeof(T)*(count), EE_MEMHINT_NONE))

    #define EE_ALLOC2(T, count, hint) ((T*)efd::_Malloc(sizeof(T)*(count), hint))

    #define EE_ALIGNED_ALLOC(T, count, alignment) ((T*)efd::_AlignedMalloc(\
        sizeof(T)*(count), alignment, EE_MEMHINT_NONE))

    #define EE_ALIGNED_ALLOC2(T, count, alignment, hint) \
        ((T*)efd::_AlignedMalloc(sizeof(T)*(count), alignment, hint))

    #define EE_ALIGNED_MALLOC(size, alignment) (efd::_AlignedMalloc(size, \
        alignment, EE_MEMHINT_NONE))

    #define EE_ALIGNED_MALLOC2(size, alignment, hint) (efd::_AlignedMalloc(size, \
        alignment, hint))

    #define EE_MALLOC(size) (efd::_Malloc(size, EE_MEMHINT_NONE))

    #define EE_MALLOC2(size, hint) (efd::_Malloc(size, hint))

    #define EE_REALLOC(memblock, size) \
        (efd::_Realloc(memblock, size, EE_MEMHINT_NONE))

    #define EE_REALLOC2(memblock, size, hint) \
        (efd::_Realloc(memblock, size, hint))

    #define EE_ALIGNED_REALLOC(memblock, size, alignment) \
        (efd::_AlignedRealloc(memblock, size, alignment, EE_MEMHINT_NONE))

    #define EE_ALIGNED_REALLOC2(memblock, size, alignment, hint) \
        (efd::_AlignedRealloc(memblock, size, alignment, hint))

    #define EE_FREE(p) efd::_Free(p)
    #define EE_ALIGNED_FREE(p) efd::_AlignedFree(p)

    #define EE_FREE_KNOWN_SIZE(p, sizeInBytes) efd::_Free(p, sizeInBytes)
    #define EE_ALIGNED_FREE_KNOWN_SIZE(p, sizeInBytes) efd::_AlignedFree(p, sizeInBytes)

    #define EE_TRACK_ALLOC(p, sizeInBytes) false
    #define EE_TRACK_ALLOC2(p, sizeInBytes, hint) false

    #define EE_TRACK_FREE(p) false
    #define EE_MEM_MARKER(markerType, classifier, string) false

#endif // EE_MEMORY_DEBUGGER

//@}

// In many cases, external resources will need to be allocated.
// In this case, use the following macros:
#define EE_EXTERNAL_NEW new
#define EE_EXTERNAL_DELETE delete
#define EE_EXTERNAL_ALLOC(T, count) ((T*)malloc(sizeof(T)*(count)))
#define EE_EXTERNAL_MALLOC malloc
#define EE_EXTERNAL_REALLOC realloc
#define EE_EXTERNAL_FREE free
#define EE_EXTERNAL_CALLOC calloc

#if defined(EE_PLATFORM_PS3)
    #define EE_EXTERNAL_ALIGNED_MALLOC(size, alignment) memalign(alignment, size)
    #define EE_EXTERNAL_ALIGNED_REALLOC reallocalign
    #define EE_EXTERNAL_ALIGNED_FREE free
    #define EE_ALIGN_OF(T) __alignof__(T)
    #define EE_ALIGN_CLASS_BEGIN(T)
    #define EE_ALIGN_CLASS_END(T) __attribute__((aligned(T)))
    #define EE_STACK_ALLOC(T, count) (T*)alloca(sizeof(T)*(count))
    #define EE_STACK_FREE(x)
#elif defined (EE_PLATFORM_LINUX)
    #define EE_EXTERNAL_ALIGNED_MALLOC(size, alignment) memalign(alignment, size)
    #define EE_EXTERNAL_ALIGNED_REALLOC(pointer, size, alignment) realloc(pointer, size)
    #define EE_EXTERNAL_ALIGNED_FREE free
    #define EE_ALIGN_OF(T) __alignof__(T)
    #define EE_ALIGN_CLASS_BEGIN(T)
    #define EE_ALIGN_CLASS_END(T) __attribute__((aligned(T)))
    #define EE_STACK_ALLOC(T, count) (T*)alloca(sizeof(T)*(count))
    #define EE_STACK_FREE(x)
#elif defined(EE_PLATFORM_XBOX360) || defined(EE_PLATFORM_WIN32)
    #define EE_EXTERNAL_ALIGNED_MALLOC _aligned_malloc
    #define EE_EXTERNAL_ALIGNED_REALLOC _aligned_realloc
    #define EE_EXTERNAL_ALIGNED_FREE _aligned_free
    #define EE_ALIGN_OF(T) __alignof(T)
    #define EE_ALIGN_CLASS_BEGIN(T) __declspec(align(T))
    #define EE_ALIGN_CLASS_END(T)
    #define EE_STACK_ALLOC(T, count) (T*)_malloca(sizeof(T)*(count))
    #define EE_STACK_FREE _freea
#else
    #error Unsupported platform
#endif

#define EE_ALIGN_CLASS(T, CODE) EE_ALIGN_CLASS_BEGIN(T) CODE EE_ALIGN_CLASS_END(T)

//@}

class AllocUnit;


/**
    _LogMemAssert serves as a simplified assert handler for asserts inside
    MemManager and the allocators. This assert handler is purposely designed
    to do nothing more than simply output the assert location and assert.
    Since other assert handlers may allocate memory they can not be used by the
    MemManager. Doing so could result in infinite recursion.
*/
EE_EFD_ENTRY void _LogMemAssert(const char* pcCondition, const AllocUnit* pkUnit,
    const char* pcFile, int iLine, const char* pcFunction);

#if defined(EE_MEMORY_DEBUGGER)
    #define EE_MEMASSERT(value) {bool bValue = 0 != (value); \
        if (!bValue) {efd::_LogMemAssert(#value, 0, __FILE__, __LINE__, \
        __FUNCTION__);}}
    #define EE_MEMASSERT_UNIT(value, unit) {bool bValue = (bool)(value); \
        if (!bValue) {efd::_LogMemAssert(#value, pkUnit, __FILE__, __LINE__, \
        __FUNCTION__);}}
#else
    #define EE_MEMASSERT(value) ((void)0)
    #define EE_MEMASSERT_UNIT(value, unit) ((void)0)
#endif // #if defined(EE_MEMORY_DEBUGGER) && defined(EE_ASSERTS_ARE_ENABLED)

// Platform-specific allocation routines
#ifdef EE_PLATFORM_XBOX360
#ifdef EE_MEMORY_DEBUGGER
    EE_EFD_ENTRY void* _PhysicalAlloc(size_t stSizeInBytes,
        size_t stDesiredPhysicalAddress, size_t stAlignment,
        unsigned int uiFlags, const char* pcSourceFile, int iSourceLine,
        const char* pcFunction);
    EE_EFD_ENTRY void _PhysicalFree(void* p);
    #define EE_PHYSICAL_ALLOC(size, desiredAddress, alignment, flags) \
        (efd::_PhysicalAlloc(size, desiredAddress, alignment, flags, \
        __FILE__, __LINE__, __FUNCTION__))
    #define EE_PHYSICAL_FREE(p) (efd::_PhysicalFree(p))

#else
    EE_EFD_ENTRY void* _PhysicalAlloc(size_t stSizeInBytes,
        size_t stDesiredPhysicalAddress, size_t stAlignment,
        unsigned int uiFlags);
    EE_EFD_ENTRY void _PhysicalFree(void* p);
    #define EE_PHYSICAL_ALLOC(size, desiredAddress, alignment, flags) \
        (efd::_PhysicalAlloc(size, desiredAddress, alignment, flags))
    #define EE_PHYSICAL_FREE(p) (efd::_PhysicalFree(p))
#endif // EE_MEMORY_DEBUGGER
#endif // EE_PLATFORM_XBOX360

} //namespace efd
#endif // EEMEMORYDEFINES_H
