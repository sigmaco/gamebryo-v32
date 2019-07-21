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
#ifndef NIMEMORYDEFINES_H
#define NIMEMORYDEFINES_H

#include "NiMemHint.h"
#include <efd/MemoryDefines.h>





//--------------------------------------------------------------------------------------------------
// Determine whether or not to store the File, Line, Function data.
//--------------------------------------------------------------------------------------------------
// Uncomment this #if block in order to turn on memory debugging in
// debug builds.

// Use memory debugging only in NiMemory builds
#if defined(EE_MEMORY_DEBUGGER)
    #define NI_MEMORY_DEBUGGER

#endif

// If the following error is triggered, an outdated project or makefile is defining
// the NI_USE_MEMORY_MANAGEMENT preprocessor symbol, which has been replaced by
// EE_USE_MEMORY_MANAGEMENT.
#if NI_USE_MEMORY_MANAGEMENT && !defined(EE_USE_MEMORY_MANAGEMENT)
    #error NI_USE_MEMORY_MANAGEMENT has been replaced by EE_USE_MEMORY_MANAGEMENT
#endif


#define NI_IS_POWER_OF_TWO(x)   (((x)&(x-1)) == 0)

//--------------------------------------------------------------------------------------------------
// NiMemEventType.
//
// Determine the overall allocation type. When an object is allocated with
// an allocation routine, it should be deallocated with its corresponding
// deallocation routine.
//--------------------------------------------------------------------------------------------------

// Bridge from NiMemEventType to efd::MemEventType
#define NiMemEventType efd::MemEventType

#define NI_UNKNOWN           efd::EE_MET_UNKNOWN
#define NI_OPER_NEW          efd::EE_MET_NEW
#define NI_OPER_NEW_ARRAY    efd::EE_MET_NEW_ARRAY
#define NI_OPER_DELETE       efd::EE_MET_DELETE
#define NI_OPER_DELETE_ARRAY efd::EE_MET_DELETE_ARRAY
#define NI_MALLOC            efd::EE_MET_MALLOC
#define NI_REALLOC           efd::EE_MET_REALLOC
#define NI_ALIGNEDMALLOC     efd::EE_MET_ALIGNEDMALLOC
#define NI_ALIGNEDREALLOC    efd::EE_MET_ALIGNEDREALLOC
#define NI_FREE              efd::EE_MET_FREE
#define NI_ALIGNEDFREE       efd::EE_MET_ALIGNEDFREE
#define NI_EXTERNALALLOC     efd::EE_MET_EXTERNALALLOC
#define NI_EXTERNALFREE      efd::EE_MET_EXTERNALFREE

//--------------------------------------------------------------------------------------------------
// Allocation macros and functions.
//
// NiNew and NiDelete are ONLY used for NiMemObject-derived classes.
// This lets Gamebryo store the file, line, function information depending
// on the build target.
//
// NiAlloc/NiMalloc/NiCalloc/NiRealloc and NiFree should be used for
// any non-NiMemObject object or intrinsic type. Note that they do not call
// global new or delete, nor will they call constructors or destructors.
//--------------------------------------------------------------------------------------------------

#define NI_MEM_FILE_DEFAULT         EE_MEM_FILE_DEFAULT
#define NI_MEM_LINE_DEFAULT         EE_MEM_LINE_DEFAULT
#define NI_MEM_FUNCTION_DEFAULT     EE_MEM_FUNCTION_DEFAULT
#define NI_MEM_DEALLOC_SIZE_DEFAULT EE_MEM_DEALLOC_SIZE_DEFAULT
#define NI_MEM_MARKER_BEGIN         EE_MEM_MARKER_BEGIN
#define NI_MEM_MARKER_END           EE_MEM_MARKER_END

#define NI_MEM_ALIGNMENT_DEFAULT    EE_MEM_ALIGNMENT_DEFAULT

// Build-independent memory management routines
#define _NiFree efd::_Free
#define _NiAlignedFree efd::_AlignedFree

#define _NiMalloc efd::_Malloc
#define _NiAlignedMalloc efd::_AlignedMalloc
#define _NiRealloc efd::_Realloc
#define _NiAlignedRealloc efd::_AlignedRealloc

#define NiVerifyAddress EE_VERIFY_ADDRESS
#define _NiTrackAlloc efd::_TrackAlloc
#define _NiTrackFree efd::_TrackFree
#define _NiMemMarker efd::_MemMarker

#define NiNew EE_NEW
#define NiNew2 EE_NEW2
#define NiDelete EE_DELETE

#define NiAlloc EE_ALLOC
#define NiAlloc2 EE_ALLOC2

#define NiAlignedAlloc EE_ALIGNED_ALLOC
#define NiAlignedAlloc2 EE_ALIGNED_ALLOC2

#define NiMalloc EE_MALLOC
#define NiMalloc2 EE_MALLOC2

#define NiAlignedMalloc EE_ALIGNED_MALLOC
#define NiAlignedMalloc2 EE_ALIGNED_MALLOC2

#define NiRealloc EE_REALLOC
#define NiRealloc2 EE_REALLOC2

#define NiAlignedRealloc EE_ALIGNED_REALLOC
#define NiAlignedRealloc2 EE_ALIGNED_REALLOC2

#define NiFree EE_FREE
#define NiAlignedFree EE_ALIGNED_FREE

#define NiFreeKnownSize EE_FREE_KNOWN_SIZE
#define NiAlignedFreeKnownSize EE_ALIGNED_FREE_KNOWN_SIZE

#define NiTrackAlloc EE_TRACK_ALLOC
#define NiTrackAlloc2 EE_TRACK_ALLOC2
#define NiTrackFree EE_TRACK_FREE
#define NiMemMarker EE_MEM_MARKER

#define NiExternalNew     EE_EXTERNAL_NEW
#define NiExternalDelete  EE_EXTERNAL_DELETE
#define NiExternalAlloc   EE_EXTERNAL_ALLOC
#define NiExternalMalloc  EE_EXTERNAL_MALLOC
#define NiExternalRealloc EE_EXTERNAL_REALLOC
#define NiExternalFree    EE_EXTERNAL_FREE
#define NiExternalCalloc  EE_EXTERNAL_CALLOC

#define NiExternalAlignedMalloc  EE_EXTERNAL_ALIGNED_MALLOC
#define NiExternalAlignedRealloc EE_EXTERNAL_ALIGNED_REALLOC
#define NiExternalAlignedFree    EE_EXTERNAL_ALIGNED_FREE
#define NiAlignOf EE_ALIGN_OF

#define NiStackAlloc EE_STACK_ALLOC
#define NiStackFree EE_STACK_FREE

#define _NiLogMemAssert efd::_LogMemAssert

#define NIMEMASSERT EE_MEMASSERT
#define NIMEMASSERTUNIT EE_MEMASSERT_UNIT

// Platform-specific allocation routines
#if defined(_XENON)
    #define _NiPhysicalAlloc efd::_PhysicalAlloc
    #define _NiPhysicalFree efd::_PhysicalFree

    #define NiPhysicalAlloc EE_PHYSICAL_ALLOC
    #define NiPhysicalFree  EE_PHYSICAL_FREE
#endif // _XENON

#endif // NIMEMORYDEFINES_H
