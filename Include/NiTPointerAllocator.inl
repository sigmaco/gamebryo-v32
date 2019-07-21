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
//--------------------------------------------------------------------------------------------------
//  NiTPointerAllocator inline functions

//--------------------------------------------------------------------------------------------------
template <class T> inline
void* NiTPointerAllocator<T>::Allocate()
{
#if !EE_USE_PER_THREAD_ALLOCATOR_POOLS
    NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Lock();
#endif // EE_USE_PER_THREAD_ALLOCATOR_POOLS

#ifdef NIDEBUG
    unsigned int uiAllocated = NiTAbstractPoolAllocator<T>::ms_uiAllocated;
    unsigned int uiMaxAllocated = NiTAbstractPoolAllocator<T>::ms_uiMaxAllocated;

    NiTAbstractPoolAllocator<T>::ms_uiAllocated = ++uiAllocated;

    if (uiAllocated > uiMaxAllocated)
    {
        NiTAbstractPoolAllocator<T>::ms_uiMaxAllocated = uiAllocated;
    }
#endif

    if (!NiTAbstractPoolAllocator<T>::ms_pkFreeMem)
    {
#if EE_USE_PER_THREAD_ALLOCATOR_POOLS
        NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Lock();
        NiTPointerAllocator<T>::GetFreeMemFromChain();

        bool bRegisterPerThreadShutdown = false;
        if (!NiTAbstractPoolAllocator<T>::m_sbIsPerThreadShutdown)
        {
            NiTAbstractPoolAllocator<T>::m_sbIsPerThreadShutdown = true;
            bRegisterPerThreadShutdown = true;
        }
        NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Unlock();

        if (bRegisterPerThreadShutdown)
        {
            // Note this must be done AFTER the ms_kCriticalSection lock to prevent
            // dead lock with the NiTAbstractPoolAllocatorFuncStorage lock
            NiTAbstractPoolAllocatorFuncStorage::AddPerThreadShutdown(
                NiTAbstractPoolAllocator<T>::_SDMPerTheadShutdown);
        }
#else
        NiTPointerAllocator<T>::CreateFreeMem();
#endif // EE_USE_PER_THREAD_ALLOCATOR_POOLS
    }

    typename NiTAbstractPoolAllocator<T>::AllocNode* pTmp =
        NiTAbstractPoolAllocator<T>::ms_pkFreeMem;

    typename NiTAbstractPoolAllocator<T>::AllocNode* pkFreeMem =
        NiTAbstractPoolAllocator<T>::ms_pkFreeMem;
    NiTAbstractPoolAllocator<T>::ms_pkFreeMem = pkFreeMem->m_pkNext;

    pTmp->m_element = 0;
    pTmp->m_pkNext = 0;
    pTmp->m_pkData = 0;

#if !EE_USE_PER_THREAD_ALLOCATOR_POOLS
    NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Unlock();
#endif // EE_USE_PER_THREAD_ALLOCATOR_POOLS

    return pTmp;
}

//--------------------------------------------------------------------------------------------------
template <class T> inline
void NiTPointerAllocator<T>::Deallocate(void* pkDel)
{
#if !EE_USE_PER_THREAD_ALLOCATOR_POOLS
    NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Lock();
#endif

#ifdef NIDEBUG
    unsigned int uiAllocated = NiTAbstractPoolAllocator<T>::ms_uiAllocated;
    NiTAbstractPoolAllocator<T>::ms_uiAllocated = --uiAllocated;
#endif

    // Node being freed - Just set the freepointer
    // here and the next to the previous free
    // In debug, memset(0).
    typename NiTAbstractPoolAllocator<T>::AllocNode* pDel =
        (typename NiTAbstractPoolAllocator<T>::AllocNode*)pkDel;

    pDel->m_pkData = 0;
    pDel->m_pkNext = NiTAbstractPoolAllocator<T>::ms_pkFreeMem;
    NiTAbstractPoolAllocator<T>::ms_pkFreeMem = pDel;

#if !EE_USE_PER_THREAD_ALLOCATOR_POOLS
    NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Unlock();
#endif
}

//--------------------------------------------------------------------------------------------------
