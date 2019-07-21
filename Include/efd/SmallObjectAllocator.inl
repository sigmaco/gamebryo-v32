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

namespace efd
{

//--------------------------------------------------------------------------------------------------
// Creates an allocator for small objects given chunk size and maximum 'small' object size.
template <class TheAllocator>
SmallObjectAllocator<TheAllocator>::SmallObjectAllocator(size_t stChunkSize)
    : m_stChunkSize(stChunkSize)
{
    for (size_t st = 1; st <= EE_MAX_SMALL_OBJECT_SIZE; st++)
    {
        m_kPool[st-1].Init(&m_kAllocator, st, stChunkSize);
    }
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
SmallObjectAllocator<TheAllocator>::SmallObjectAllocator(const SmallObjectAllocator&)
{
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
SmallObjectAllocator<TheAllocator>& SmallObjectAllocator<TheAllocator>::operator=(
    const SmallObjectAllocator&)
{
    return *(this);
}

//--------------------------------------------------------------------------------------------------
// Allocates 'numBytes' memory.  Uses an internal pool of FixedSizeAllocator objects for small
// objects.
template <class TheAllocator>
void* SmallObjectAllocator<TheAllocator>::Allocate(size_t stNumBytes)
{
    EE_MEMASSERT(stNumBytes != 0);
    EE_MEMASSERT(stNumBytes <= EE_MAX_SMALL_OBJECT_SIZE);
    EE_MEMASSERT(m_kPool[stNumBytes-1].BlockSize() == stNumBytes);

    FixedSizeAllocator::PerThreadSmallBlockCache* pkCache = NULL;

#if EE_USE_PER_THREAD_ALLOCATOR_POOLS
    if (ms_usePerThreadCaches && (stNumBytes >= sizeof(void*)))
    {
        pkCache = ms_pPerThreadCacheHead;
        // check case when PerThreadInit is not launched yet (main thread for example).
        if (pkCache)
            pkCache = pkCache + (stNumBytes - 1);
    }
#endif
    return m_kPool[stNumBytes-1].Allocate(pkCache);
}

//--------------------------------------------------------------------------------------------------
// Deallocates memory previously allocated with Allocate().  Behavior is undefined if you pass in
// any other kind of pointer.
template <class TheAllocator>
void SmallObjectAllocator<TheAllocator>::Deallocate(void* p, size_t stNumBytes)
{
    EE_MEMASSERT(stNumBytes != 0);
    EE_MEMASSERT(stNumBytes <= EE_MAX_SMALL_OBJECT_SIZE);
    EE_MEMASSERT(m_kPool[stNumBytes-1].BlockSize() == stNumBytes);

    FixedSizeAllocator::PerThreadSmallBlockCache* pkCache = NULL;

#if EE_USE_PER_THREAD_ALLOCATOR_POOLS
    if (ms_usePerThreadCaches && (stNumBytes >= sizeof(void*)))
    {
        pkCache = ms_pPerThreadCacheHead;
        // check case when PerThreadShutdown was launched already (main thread for example).
        if (pkCache)
            pkCache = pkCache + (stNumBytes - 1);
    }
#endif

    return m_kPool[stNumBytes-1].Deallocate(p, pkCache);
}

//--------------------------------------------------------------------------------------------------
// Returns the FixedSizeAllocator for the given input byte size.
template <class TheAllocator>
FixedSizeAllocator* SmallObjectAllocator<TheAllocator>::GetFixedAllocatorForSize(
    size_t stNumBytes)
{
    EE_MEMASSERT(stNumBytes != 0);
    EE_MEMASSERT(stNumBytes <= EE_MAX_SMALL_OBJECT_SIZE);
    EE_MEMASSERT(m_kPool[stNumBytes-1].BlockSize() == stNumBytes);
    return &m_kPool[stNumBytes-1];
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
size_t SmallObjectAllocator<TheAllocator>::GetSizeFromAddress(void* pMemory)
{
    size_t stSize;
    char* pcMemory = (char*) pMemory;
    char* pcSize = (char*)&stSize;

#if defined(EE_ARCH_32)
    EE_COMPILETIME_ASSERT(sizeof(size_t) == 4);
    pcSize[0] = pcMemory[0];
    pcSize[1] = pcMemory[1];
    pcSize[2] = pcMemory[2];
    pcSize[3] = pcMemory[3];
#elif defined(EE_ARCH_64)
    EE_COMPILETIME_ASSERT(sizeof(size_t) == 8);
    pcSize[0] = pcMemory[0];
    pcSize[1] = pcMemory[1];
    pcSize[2] = pcMemory[2];
    pcSize[3] = pcMemory[3];
    pcSize[4] = pcMemory[4];
    pcSize[5] = pcMemory[5];
    pcSize[6] = pcMemory[6];
    pcSize[7] = pcMemory[7];
#else
    #error "Unknown architecture"
#endif

    return stSize;
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
void SmallObjectAllocator<TheAllocator>::SetSizeToAddress(void* pMemory, size_t stSize)
{
    char* pcMemory = (char*) pMemory;
    char* pcSize = (char*)&stSize;

#if defined(EE_ARCH_32)
    EE_COMPILETIME_ASSERT(sizeof(size_t) == 4);
    pcMemory[0] = pcSize[0];
    pcMemory[1] = pcSize[1];
    pcMemory[2] = pcSize[2];
    pcMemory[3] = pcSize[3];
#elif defined(EE_ARCH_64)
    EE_COMPILETIME_ASSERT(sizeof(size_t) == 8);
    pcMemory[0] = pcSize[0];
    pcMemory[1] = pcSize[1];
    pcMemory[2] = pcSize[2];
    pcMemory[3] = pcSize[3];
    pcMemory[4] = pcSize[4];
    pcMemory[5] = pcSize[5];
    pcMemory[6] = pcSize[6];
    pcMemory[7] = pcSize[7];
#else
    EE_DEBUG_BREAK();
#endif
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
// Implementation of IAllocator.

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
void* SmallObjectAllocator<TheAllocator>::Allocate(size_t& stSizeInBytes, size_t& stAlignment,
    MemHint kHint, MemEventType eEventType, const char* pcFile, int iLine, const char* pcFunction)
{
    EE_MEMASSERT(EE_IS_POWER_OF_TWO(stAlignment));

    bool bPrependSize = false;
    void* pvMemory = NULL;

    if (stAlignment == EE_MEM_ALIGNMENT_DEFAULT &&
        (kHint.CompilerProvidesSizeOnDeallocate() == false) &&
        eEventType != EE_MET_ALIGNEDMALLOC &&
        eEventType != EE_MET_ALIGNEDREALLOC)
    {
        stSizeInBytes += EE_MEM_ALIGNMENT_DEFAULT;
        bPrependSize = true;
    }

    bool bCanUseSmallObjectAllocator = (eEventType != EE_MET_ALIGNEDMALLOC) &&
        (eEventType != EE_MET_ALIGNEDREALLOC) &&
        (stSizeInBytes <= EE_MAX_SMALL_OBJECT_SIZE) &&
        (stAlignment == EE_MEM_ALIGNMENT_DEFAULT);

    if (bCanUseSmallObjectAllocator)
    {
        pvMemory = Allocate(stSizeInBytes);
    }
    else
    {
        pvMemory = m_kAllocator.Allocate(
            stSizeInBytes,
            stAlignment,
            kHint,
            eEventType,
            pcFile,
            iLine,
            pcFunction);
    }

    if (pvMemory && bPrependSize)
    {
        EE_MEMASSERT(EE_MEM_ALIGNMENT_DEFAULT >= sizeof(size_t));
        SetSizeToAddress(pvMemory, stSizeInBytes);
        pvMemory = ((char*)pvMemory) + EE_MEM_ALIGNMENT_DEFAULT;
    }

    return pvMemory;
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
void SmallObjectAllocator<TheAllocator>::Deallocate(void* pvMemory, MemEventType eEventType,
    size_t stSizeInBytes)
{
    if (pvMemory == NULL)
        return;

    if (eEventType != EE_MET_ALIGNEDFREE && eEventType != EE_MET_ALIGNEDREALLOC &&
        EE_MEM_DEALLOC_SIZE_DEFAULT == stSizeInBytes)
    {
        pvMemory = ((char*)pvMemory) - EE_MEM_ALIGNMENT_DEFAULT;
        EE_MEMASSERT(EE_MEM_ALIGNMENT_DEFAULT >= sizeof(size_t));
        //stSizeInBytes = *((size_t*) pvMemory);
        stSizeInBytes = GetSizeFromAddress(pvMemory);
    }

    if (stSizeInBytes <= EE_MAX_SMALL_OBJECT_SIZE)
    {
        Deallocate(pvMemory, stSizeInBytes);
    }
    else
    {
        m_kAllocator.Deallocate(pvMemory, eEventType, stSizeInBytes);
    }
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
void* SmallObjectAllocator<TheAllocator>::Reallocate(void* pvMemory, size_t& stSizeInBytes,
    size_t& stAlignment, MemHint kHint, MemEventType eEventType, size_t stSizeCurrent,
    const char* pcFile, int iLine, const char* pcFunction)
{
    EE_MEMASSERT(EE_IS_POWER_OF_TWO(stAlignment));

    // The deallocation case should have been caught before in the allocation functions.
    EE_MEMASSERT(stSizeInBytes != 0);

    // Determine the current size for the address.
    if (eEventType != EE_MET_ALIGNEDFREE && eEventType != EE_MET_ALIGNEDREALLOC &&
        EE_MEM_DEALLOC_SIZE_DEFAULT == stSizeCurrent &&
        (kHint.CompilerProvidesSizeOnDeallocate() == false))
    {
        pvMemory = ((char*)pvMemory) - EE_MEM_ALIGNMENT_DEFAULT;
        EE_MEMASSERT(EE_MEM_ALIGNMENT_DEFAULT >= sizeof(size_t));
        stSizeCurrent = GetSizeFromAddress(pvMemory);
    }

    // Pad the allocation for the new current size.
    bool bPrependSize = false;
    if (stAlignment == EE_MEM_ALIGNMENT_DEFAULT &&
        (kHint.CompilerProvidesSizeOnDeallocate() == false) &&
        eEventType != EE_MET_ALIGNEDMALLOC && eEventType != EE_MET_ALIGNEDREALLOC)
    {
        stSizeInBytes += EE_MEM_ALIGNMENT_DEFAULT;
        bPrependSize = true;
    }

    if (stSizeCurrent != EE_MEM_DEALLOC_SIZE_DEFAULT &&
        stSizeInBytes <= stSizeCurrent && bPrependSize)
    {
        stSizeInBytes = stSizeCurrent;
        pvMemory = ((char*)pvMemory) + EE_MEM_ALIGNMENT_DEFAULT;
        return pvMemory;
    }

    void* pvNewMemory = NULL;

    if (eEventType != EE_MET_ALIGNEDMALLOC && eEventType != EE_MET_ALIGNEDREALLOC &&
        (stSizeCurrent <= EE_MAX_SMALL_OBJECT_SIZE || stSizeInBytes <= EE_MAX_SMALL_OBJECT_SIZE))
    {
        EE_MEMASSERT(stAlignment ==  EE_MEM_ALIGNMENT_DEFAULT);
        EE_MEMASSERT(stSizeCurrent != EE_MEM_DEALLOC_SIZE_DEFAULT);

        // Since the small object allocator does not support reallocation, we must manually
        // reallocate.

        // Remove any header information that we have added in this call.
        stSizeInBytes -= EE_MEM_ALIGNMENT_DEFAULT;

        // Allow the allocation call to do its job, which should mean that the size will be
        // embedded immediately before the address that we receive.
        pvNewMemory = Allocate(stSizeInBytes, stAlignment, kHint, eEventType, pcFile, iLine,
            pcFunction);
        bPrependSize = false;

        if (stSizeCurrent != EE_MEM_DEALLOC_SIZE_DEFAULT)
        {
            char* pvMemoryToCopy = ((char*)pvMemory) + EE_MEM_ALIGNMENT_DEFAULT;
            size_t stSizeToCopy = stSizeCurrent - EE_MEM_ALIGNMENT_DEFAULT;

            efd::Memcpy(pvNewMemory, stSizeInBytes, pvMemoryToCopy, stSizeToCopy);
            Deallocate(pvMemory, eEventType, stSizeCurrent);
        }
    }
    else
    {
        pvNewMemory = m_kAllocator.Reallocate(pvMemory, stSizeInBytes, stAlignment, kHint,
            eEventType, stSizeCurrent, pcFile, iLine, pcFunction);
    }

    if (pvNewMemory && bPrependSize)
    {
        EE_MEMASSERT(EE_MEM_ALIGNMENT_DEFAULT >= sizeof(size_t));
        SetSizeToAddress(pvNewMemory, stSizeInBytes);
        pvNewMemory = ((char*)pvNewMemory) + EE_MEM_ALIGNMENT_DEFAULT;
    }

    return pvNewMemory;
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
bool SmallObjectAllocator<TheAllocator>::TrackAllocate(const void* const pvMemory,
    size_t stSizeInBytes, MemHint kHint, MemEventType eEventType, const char* pcFile, int iLine,
    const char* pcFunction)
{
    return m_kAllocator.TrackAllocate(pvMemory, stSizeInBytes, kHint, eEventType, pcFile, iLine,
        pcFunction);
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
void SmallObjectAllocator<TheAllocator>::CreateMemoryLogHandler()
{
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
bool SmallObjectAllocator<TheAllocator>::TrackDeallocate(const void* const pvMemory,
    MemEventType eEventType)
{
    return m_kAllocator.TrackDeallocate(pvMemory, eEventType);
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
bool SmallObjectAllocator<TheAllocator>::SetMarker(const char* pcMarkerType,
    const char* pcClassifier, const char* pcString)
{
    return m_kAllocator.SetMarker(pcMarkerType, pcClassifier, pcString);
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
void SmallObjectAllocator<TheAllocator>::Initialize()
{
    m_kAllocator.Initialize();
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
void SmallObjectAllocator<TheAllocator>::Shutdown()
{
    m_kAllocator.Shutdown();
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
bool SmallObjectAllocator<TheAllocator>::VerifyAddress(const void* pvMemory)
{
    return m_kAllocator.VerifyAddress(pvMemory);
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
void SmallObjectAllocator<TheAllocator>::PerThreadInit()
{
#if EE_USE_PER_THREAD_ALLOCATOR_POOLS
    // Allocate a table of caches one for each pool size
    // This table is unique to the thread, so accesses don't need to be synchronized
    size_t stSizeInBytes =
        sizeof(FixedSizeAllocator::PerThreadSmallBlockCache) * EE_MAX_SMALL_OBJECT_SIZE;

    size_t stSizeInByteAligment = sizeof(FixedSizeAllocator::PerThreadSmallBlockCache);

    void* pvMemory = m_kAllocator.Allocate(
        stSizeInBytes,
        stSizeInByteAligment,  // alignment
        MemHint::USAGE_POOL,
        EE_MET_ALIGNEDMALLOC,
        __FILE__,
        __LINE__,
        __FUNCTION__);

    FixedSizeAllocator::PerThreadSmallBlockCache* pkCaches =
        static_cast<FixedSizeAllocator::PerThreadSmallBlockCache*>(pvMemory);

    // The entry per small object pool is a head pointer and a length of chain
    // (count of allocations in the cache; the remaining pointers are inside)
    for (size_t st = 0; st < EE_MAX_SMALL_OBJECT_SIZE; ++st)
    {
        pkCaches[st].ppHeadBlock = NULL;
        pkCaches[st].stSize = 0;
    }

    // Record the cache tables it in the thread local store for this thread
    ms_pPerThreadCacheHead = pkCaches;
    ms_usePerThreadCaches = true;
#endif // EE_USE_PER_THREAD_ALLOCATOR_POOLS
}

//--------------------------------------------------------------------------------------------------
template <class TheAllocator>
void SmallObjectAllocator<TheAllocator>::PerThreadShutdown()
{
#if EE_USE_PER_THREAD_ALLOCATOR_POOLS
    if (ms_usePerThreadCaches)
    {
        // Release all elements in the cache
        FixedSizeAllocator::PerThreadSmallBlockCache* pkCache = ms_pPerThreadCacheHead;
        if (pkCache != NULL)
        {
            for (size_t st = 0; st < EE_MAX_SMALL_OBJECT_SIZE; ++st)
            {
                m_kPool[st].ReleaseAllElementsInCache(&pkCache[st]);
            }
            m_kAllocator.Deallocate(pkCache, EE_MET_ALIGNEDFREE, 0);
        }
        ms_pPerThreadCacheHead = NULL;
    }
#endif // EE_USE_PER_THREAD_ALLOCATOR_POOLS
}

//--------------------------------------------------------------------------------------------------

}   // End namespace efd.
