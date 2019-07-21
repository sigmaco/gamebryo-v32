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
#ifndef EE_SMALLOBJECTALLOCATOR_H
#define EE_SMALLOBJECTALLOCATOR_H

#ifndef EE_MAX_SMALL_OBJECT_SIZE
#define EE_MAX_SMALL_OBJECT_SIZE 256
#endif

#include <efd/RTLib.h>
#include <efd/FixedSizeAllocator.h>
#include <efd/MemoryDefines.h>
#include <efd/IAllocator.h>
#include <efd/StringUtilities.h>
#include <efd/ThreadLocal.h>

namespace efd
{

/**
    A platform-independent class to support pooling of small allocations.

    This allocator is based on the SmallObjectAlloctor described by Alexei Alexandrescu in Modern
    C++ Design.  The latest code for Loki (the codebase containing the SmallObjectAllocator) may
    be found at http://sourceforge.net/projects/loki-lib/.  The licensing information for this
    class may be found in the Third Party Code section of the documentation.  Also of importance
    is the fact that allocation thread safety responsibility is passed onto the FixedSizeAllocator
    objects.

    @note All sizes from 1 to EE_MAX_SMALL_OBJECT_SIZE will receive their own internal allocation
    pool.  This approach helps conserve memory, since this class is a small object allocator.  The
    current track of Alexandrescu's code enforces alignment restrictions that bloat the size for
    small object allocations.  Please see the alignment note which follows for more justification
    for this design decision.  Also note that the size of an allocation must be known at
    deallocation time.  Absence of this knowledge will currently make it impossible to delete the
    allocation.  Please see "Modern C++ Design" by Andrei Alexandrescu for strategies that enable
    the deallocator to know how large the allocation was without storing a size per instance.

    @note Allocations for a given size are only guaranteed to be aligned if the size of the
    request itself is aligned.  For example, all 8-byte allocations will be aligned to at least a
    4-byte boundary, since the beginning of a pool is aligned to EE_MEM_ALIGNMENT_DEFAULT.
    However, 7-byte allocations are not guaranteed to be aligned.  This scheme works in practice
    for classes, since the class size will be a multiple of the largest alignment requirement for
    the members of the class.

    The FixedSizeAllocator class is used by SmallObjectAllocator internally for allocation
    management.  FixedSizeAllocator allocates memory of a particular size from an internal pool of
    memory chunks.  When no more chunks have open slots, a new chunk will be allocated.  Note that
    each FixedSizeAllocator has a critical section that manages its various chunks.  This approach
    can improve memory performance in a multi-threaded environment.
*/
template <class TheAllocator>
class SmallObjectAllocator : public IAllocator
{
public:
    /**
        Creates a SmallObjectAllocator object with a set of pools up to EE_MAX_SMALL_OBJECT_SIZE.

        Each pool, once it receives a request for memory for the first time, will allocate space
        for 256 entries or however many entries can fit into EE_DEFAULT_CHUNK_SIZE, whichever is
        less.

        @param stChunkSize Chunk size (default is EE_DEFAULT_CHUNK_SIZE).
    */
    SmallObjectAllocator(size_t stChunkSize = EE_DEFAULT_CHUNK_SIZE);

    /// @name Methods defined by IAllocator.
    //@{
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void* Allocate(
        size_t& stSizeInBytes,
        size_t& stAlignment,
        MemHint kHint,
        MemEventType eEventType,
        const char* pcFile,
        int iLine,
        const char* pcFunction);

    virtual void Deallocate(
        void* pvMemory,
        MemEventType eEventType,
        size_t stSizeInBytes);

    virtual void* Reallocate(
        void* pvMemory,
        size_t& stSizeInBytes,
        size_t& stAlignment,
        MemHint kHint,
        MemEventType eEventType,
        size_t stSizeCurrent,
        const char* pcFile, int iLine,
        const char* pcFunction);

    virtual bool TrackAllocate(
        const void* const pvMemory,
        size_t stSizeInBytes,
        MemHint kHint,
        MemEventType eEventType,
        const char* pcFile,
        int iLine,
        const char* pcFunction);

    virtual bool TrackDeallocate(
        const void* const pvMemory,
        MemEventType eEventType);

    virtual bool SetMarker(
        const char* pcMarkerType,
        const char* pcClassifier,
        const char* pcString);

    virtual void Initialize();
    virtual void Shutdown();
    virtual void PerThreadInit();
    virtual void PerThreadShutdown();

    virtual bool VerifyAddress(const void* pvMemory);

    /**
        Empty function implemented to complete the IAllocator interface.

        The SmallObjectAllocator does not perform any memory logging.
    */
    void CreateMemoryLogHandler();
    //@}

    /**
        Returns the FixedSizeAllocator for the given input byte size.

        @param stNumBytes Input number of bytes to specify the FixedSizeAllocator.
        @return Pointer to FixedSizeAllocator.
    */
    FixedSizeAllocator* GetFixedAllocatorForSize(size_t stNumBytes);

private:
    SmallObjectAllocator(const SmallObjectAllocator&);

    // Assignment operator.
    SmallObjectAllocator& operator=(const SmallObjectAllocator&);

    /*
        Allocates 'numBytes' memory.
        Uses an internal pool of FixedSizeAllocator objects for small objects.
          stNumBytes : Number of bytes to allocate.
          return : Pointer to allocated memory.
    */
    void* Allocate(size_t stNumBytes);

    /*
        Deallocates memory previously allocated with Allocate().
        Behavior is undefined if you pass in any other kind of pointer.
          p : Pointer to memory to be deallocated.
          stSize : Memory size being deallocated.
    */
    void Deallocate(
        void* p,
        size_t stSize);

    /// Reads the size of a memory allocation from the given address.  Should only be
    /// used on addresses that were passed to SetSizeToAddress previously.
    size_t GetSizeFromAddress(void* pMemory);

    /// Stores a given size to a memory address.
    void SetSizeToAddress(void* pMemory, size_t stSize);

    // Release all elements in all caches for this thread
    void ReleaseAllElementsInCache();

    // Allocator for small objects.
    TheAllocator m_kAllocator;

    // Internal pool of FixedSizeAllocator objects for small objects.
    FixedSizeAllocator m_kPool[EE_MAX_SMALL_OBJECT_SIZE];

#if EE_USE_PER_THREAD_ALLOCATOR_POOLS
    static bool ms_usePerThreadCaches;
    EE_DECLARE_STATIC_TLS_MEMBER(FixedSizeAllocator::PerThreadSmallBlockCache*,
        ms_pPerThreadCacheHead);
#endif

    // Chunk size.
    size_t m_stChunkSize;
};

} // namespace efd

#if EE_USE_PER_THREAD_ALLOCATOR_POOLS
#define EE_IMPLEMENT_SMALL_OBJECT_ALLOCATOR(ClassName) \
    template<> \
    bool ClassName::ms_usePerThreadCaches = false; \
    template<> \
    EE_IMPLEMENT_STATIC_TLS_MEMBER(\
        efd::FixedSizeAllocator::PerThreadSmallBlockCache*,\
        ms_pPerThreadCacheHead, ClassName)
#else
#define EE_IMPLEMENT_SMALL_OBJECT_ALLOCATOR(ClassName)
#endif

#include <efd/SmallObjectAllocator.inl>

#endif // EE_SMALLOBJECTALLOCATOR_H
