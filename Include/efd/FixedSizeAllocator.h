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

//////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above
//     copyright notice appear in all copies and that both that copyright
//     notice and this permission notice appear in supporting documentation.
// The author or Addison-Welsey Longman make no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
//////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef EE_FIXEDSIZEALLOCATOR_H
#define EE_FIXEDSIZEALLOCATOR_H

#include <efd/RTLib.h>
#include <efd/CriticalSection.h>

namespace efd
{
#ifndef EE_DEFAULT_CHUNK_SIZE
#define EE_DEFAULT_CHUNK_SIZE 25600
#endif

class IAllocator;
/**
    The following class is used by SmallObjectAllocator internally for
    allocation management. This class allocates memory of a particular size
    from an internal pool of memory chunks. When no more chunks have open
    slots, a new Chunk will be allocated. Note that each FixedSizeAllocator has
    a critical section that manages its various chunks. This can improve memory
    performance in a multi-threaded environment.
*/
class EE_EFD_ENTRY FixedSizeAllocator
{
public:
    enum
    {
        CacheRefillCount = 8,
        MaxCacheCount = 32,
        CacheReleaseCount = 32,
    };

    /// @cond EMERGENT_INTERNAL
    struct PerThreadSmallBlockCache
    {
        void** ppHeadBlock;
        size_t stSize;
    };
    /// @endcond

private:

    /// @cond EMERGENT_INTERNAL

    /**
        This struct is used by FixedSizeAllocators to pre-allocate several
        instances of a single element size. It stores the pointer to the
        beginning of the memory block in m_pucData. The first free slot in the
        list is stored in m_ucFirstAvailableBlock. The number of free slots is
        stored in m_ucBlocksAvailable.
    */
    struct EE_EFD_ENTRY Chunk
    {
    public:
        /// Allocate a piece of memory large enough to hold ucBlocks of size stBlockSize.
        void Init(IAllocator* pkAllocator, size_t stBlockSize, unsigned char ucBlocks);

        /// Allocate a piece of data of the appropriate size from the Chunk.
        void* Allocate(size_t stBlockSize);

        /// Return a piece of memory to the current Chunk's free pool.
        void Deallocate(void* p, size_t stBlockSize);

        /// Reset the Chunk to its initial state of having all blocks free.
        void Reset(size_t stBlockSize, unsigned char ucBlocks);

        /// Free all memory associated with this Chunk.
        void Release(IAllocator* pkAllocator);

        /// Determine if ucNumBlocks is available for allocation from this Chunk.
        bool HasAvailable(unsigned char ucNumBlocks) const;

        /// Returns true if this Chunk contains the memory at p.
        bool HasBlock(unsigned char * p, size_t stChunkLength) const;

        /// Returns true if this Chunk is full.
        bool IsFilled(void) const;

        /// Start of the memory block owned by this Chunk.
        unsigned char* m_pucData;

        /// The first free memory slot in this Chunk.
        unsigned char m_ucFirstAvailableBlock;

        /// The number o free memory slots available.
        unsigned char m_ucBlocksAvailable;
    };

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    FixedSizeAllocator();
    ~FixedSizeAllocator();
    //@}

    /// Create a FixedSizeAllocator able to manage blocks of 'blockSize' size.
    void Init(IAllocator* pkAllocator, size_t stBlockSizem, size_t stOptimalChunkSize);

    /// Allocate a memory block
    void* Allocate(PerThreadSmallBlockCache* pkCache /*= NULL*/);

    /// Deallocate a memory block previously allocated with Allocate().
    /// (if that's not the case, the behavior is undefined)
    void Deallocate(void* p, PerThreadSmallBlockCache* pkCache /*= NULL*/);

    /// Releases all elements in a cache
    void ReleaseAllElementsInCache(PerThreadSmallBlockCache* pkCache);

    /// Returns the block size with which the FixedSizeAllocator was initialized.
    size_t BlockSize() const
    { return m_stBlockSize; }

    /// Comparison operator for sorting.
    bool operator<(size_t rhs) const
    { return BlockSize() < rhs; }

    /// Returns the number of chunks allocated.
    size_t GetNumChunks() const
    { return m_stNumChunks;}

private:
    void Push_Back(Chunk& kChunk);
    void Pop_Back();
    void Reserve(size_t stNewSize);

    // Internal functions
    void DoDeallocate(void* p);
    Chunk* VicinityFind(void* p);

    void* AllocateInternal();
    void DeallocateInternal(void* p);

    void FillCache(PerThreadSmallBlockCache* pkCache);
    void ReleaseCache(PerThreadSmallBlockCache* pkCache, size_t stReleaseCount = CacheReleaseCount);

    // Data
    IAllocator* m_pkAllocator;
    size_t m_stBlockSize;
    unsigned char m_ucNumBlocks;

    Chunk* m_pkChunks;
    size_t m_stNumChunks;
    size_t m_stMaxNumChunks;
    Chunk* m_pkAllocChunk;
    Chunk* m_pkDeallocChunk;
    Chunk* m_pkEmptyChunk;
    FastCriticalSection m_kCriticalSection;
};

} // end namespace efd

#endif // EE_FIXEDSIZEALLOCATOR_H
