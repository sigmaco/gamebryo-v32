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
//  NiTAbstractPoolAllocator inline functions
//--------------------------------------------------------------------------------------------------

#include "NiTAbstractPoolAllocatorFuncStorage.h"
#include <NiMemoryDefines.h>
#include <NiDebug.h>

template <class T> inline
void NiTAbstractPoolAllocator<T>::EnsureFreeMem()
{
    NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Lock();

    if (!ms_pkFreeMem)
        CreateFreeMem();

    NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Unlock();
}

//--------------------------------------------------------------------------------------------------
template <class T> inline
void NiTAbstractPoolAllocator<T>::CreateFreeMem()
{
    EE_ASSERT(ms_pkFreeMem == 0);
    EE_ASSERT(ms_uiBlockSize >= 2);

    AllocNode* pkFreeMem =
        NiNew typename NiTAbstractPoolAllocator<T>::AllocNode[ms_uiBlockSize];

    // Handle end point
    typename NiTAbstractPoolAllocator<T>::AllocNode* pkCurr =
        pkFreeMem + ms_uiBlockSize - 1;
    pkCurr->m_pkNext = 0;

    unsigned int i = 1;

    do
    {
        pkCurr = pkFreeMem + i;
        pkCurr->m_pkNext = pkCurr + 1;
    } while (i++ < ms_uiBlockSize - 2);

    if (ms_pkBlockHeader)
    {
        // add block to head of list
        pkFreeMem->m_pkNext = ms_pkBlockHeader;
        ms_pkBlockHeader = pkFreeMem;
    }
    else
    {
        ms_pkBlockHeader = pkFreeMem;
        ms_pkBlockHeader->m_pkNext = 0;
    }

    pkFreeMem = pkFreeMem + 1;
    ms_pkFreeMem = pkFreeMem;
}

//--------------------------------------------------------------------------------------------------
#if EE_USE_PER_THREAD_ALLOCATOR_POOLS
template <class T> inline
void NiTAbstractPoolAllocator<T>::GetFreeMemFromChain()
{
    if (!ms_pkFreeChainList)
    {
        CreateFreeMem();
    }
    else
    {
        NiTAbstractPoolAllocator<T>::ms_pkFreeMem = ms_pkFreeChainList->m_pkData;
        FreeChain* pFreeList = ms_pkFreeChainList;
        ms_pkFreeChainList = ms_pkFreeChainList->m_pkNext;
        NiDelete pFreeList;
    }
}
#endif // EE_USE_PER_THREAD_ALLOCATOR_POOLS

//--------------------------------------------------------------------------------------------------
template <class T> inline
void NiTAbstractPoolAllocator<T>::_SDMShutdown()
{
    typename NiTAbstractPoolAllocator<T>::AllocNode* pkCurr = ms_pkBlockHeader;

    while (pkCurr)
    {
        typename NiTAbstractPoolAllocator<T>::AllocNode* pkNext =
            pkCurr->m_pkNext;
        NiDelete [] pkCurr;
        pkCurr = pkNext;
    }

#if EE_USE_PER_THREAD_ALLOCATOR_POOLS

    FreeChain* pkDel = ms_pkFreeChainList;
    while (pkDel)
    {
        FreeChain* pkNext = pkDel->m_pkNext;
        NiDelete pkDel;
        pkDel = pkNext;
    }

    ms_pkFreeChainList = NULL;

    if (m_sbIsPerThreadShutdown)
    {
        m_sbIsPerThreadShutdown = false;
        NiTAbstractPoolAllocatorFuncStorage::RemovePerThreadShutdown(
            NiTAbstractPoolAllocator<T>::_SDMPerTheadShutdown);
    }
#endif // EE_USE_PER_THREAD_ALLOCATOR_POOLS

    ms_pkBlockHeader = NULL;
    ms_pkFreeMem = NULL;
}

//--------------------------------------------------------------------------------------------------
#if EE_USE_PER_THREAD_ALLOCATOR_POOLS
template <class T> inline
void NiTAbstractPoolAllocator<T>::_SDMPerTheadShutdown()
{
    NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Lock();

    typename NiTAbstractPoolAllocator<T>::AllocNode* pkBlockRoot =
        NiTAbstractPoolAllocator<T>::ms_pkFreeMem;

    if (pkBlockRoot != NULL)
    {
        // AllocNode pointer used to reference the start of a chain of a alloc nodes. This
        // references the starting location for new FreeChain objects.
        typename NiTAbstractPoolAllocator<T>::AllocNode* pkCurr = pkBlockRoot;

        // Iterate through all the alloc nodes in the local free list. After
        // ms_uiBlockSize worth of alloc nodes have been traversed pass off the
        // ms_uiBlockSize worth of traversed nodes to the global free chain (ms_pkFreeChainList)
        // by creating a new FreeChain object. Additionally all remaining nodes will also 
        // be cleaned up and added to the ms_pkFreeChainList via a new FreeChain object.
        unsigned int uiCounter = 0;
        while (pkCurr)
        {
            // Have we either reach the end of the freelist or traversed ms_uiBlockSize
            // worth of alloc nodes?
            if (pkCurr->m_pkNext == NULL || (uiCounter >= ms_uiBlockSize - 1) )
            {
                if (ms_pkFreeChainList)
                {
                    // The free chain list already contains node(s). Create a new
                    // FreeChain object and push it to the head of the free chain list.
                    FreeChain* pkNewChain = NiNew FreeChain;
                    pkNewChain->m_pkData = pkBlockRoot;
                    pkNewChain->m_pkNext = 0;

                    FreeChain* pTmpChain = ms_pkFreeChainList;
                    ms_pkFreeChainList = pkNewChain;
                    ms_pkFreeChainList->m_pkNext = pTmpChain;
                }
                else
                {
                    // The free chain list is currently empty. Create a new FreeChain
                    // object and add is as the head of the free chain list.
                    ms_pkFreeChainList = NiNew FreeChain;
                    ms_pkFreeChainList->m_pkData = pkBlockRoot;
                    ms_pkFreeChainList->m_pkNext = 0;
                }

                // Update the block root to point to the next node. This effectively points
                // to the starting location of the next set of alloc nodes to be added to the 
                // free chain list.
                pkBlockRoot = pkCurr->m_pkNext;

                // Update pkCurr to point to the next alloc node and disconnect pkCurr from
                // point to the next node in the list. This disconnection is required since
                // pkCurr currently points to the tail of a newly created FreeChain.
                pkCurr->m_pkNext = 0;
                pkCurr = pkBlockRoot;

                // Reset the counter.
                uiCounter = 0;
            }
            else
            {
                pkCurr = pkCurr->m_pkNext;
            }

            uiCounter++;
        }

        ms_pkFreeMem = NULL;
    }

    NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Unlock();
}
#endif // EE_USE_PER_THREAD_ALLOCATOR_POOLS

//--------------------------------------------------------------------------------------------------
template <class T> inline
void NiTAbstractPoolAllocator<T>::SetBlockSize(unsigned int uiBlockSize)
{
    EE_ASSERT(uiBlockSize >= 2);

    NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Lock();
    ms_uiBlockSize = uiBlockSize;
    NiTAbstractPoolAllocator<T>::ms_kCriticalSection.Unlock();
}
