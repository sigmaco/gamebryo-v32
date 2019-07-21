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

#pragma once
#ifndef NITABSTRACTPOOLALLOCATOR_H
#define NITABSTRACTPOOLALLOCATOR_H

#include <NiMemObject.h>
#include <NiCriticalSection.h>
#include <efd/ThreadLocal.h>

#define NiAllocatorShutdown(T) NiTAbstractPoolAllocator<T>::_SDMShutdown();
#define NiAllocatorPerThreadInit(T) NiTAbstractPoolAllocator<T>::_SDMPerTheadInit();
#define NiAllocatorPerThreadShutdown(T) NiTAbstractPoolAllocator<T>::_SDMPerTheadShutdown();

#ifdef NIDEBUG
    #if EE_USE_PER_THREAD_ALLOCATOR_POOLS
        #define NiAllocatorDeclareStatics(T, BLOCKSIZE) \
            template <> NiTAbstractPoolAllocator<T>::AllocNode* \
                NiTAbstractPoolAllocator<T>::ms_pkBlockHeader = NULL; \
            template <> EE_IMPLEMENT_STATIC_TLS_MEMBER(NiTAbstractPoolAllocator<T>::AllocNode*,\
                ms_pkFreeMem,NiTAbstractPoolAllocator<T>); \
            template <> NiTAbstractPoolAllocator<T>::FreeChain* \
                NiTAbstractPoolAllocator<T>::ms_pkFreeChainList = NULL; \
            template <> efd::CriticalSection \
                NiTAbstractPoolAllocator<T>::ms_kCriticalSection("NiTPool"); \
            template <> unsigned int \
                NiTAbstractPoolAllocator<T>::ms_uiBlockSize = BLOCKSIZE; \
            template <> EE_IMPLEMENT_STATIC_TLS_MEMBER(unsigned int,ms_uiAllocated,\
                NiTAbstractPoolAllocator<T>); \
            template <> EE_IMPLEMENT_STATIC_TLS_MEMBER(unsigned int,ms_uiMaxAllocated,\
                NiTAbstractPoolAllocator<T>); \
            template <> bool \
                NiTAbstractPoolAllocator<T>::m_sbIsPerThreadShutdown = false;
    #else // EE_USE_PER_THREAD_ALLOCATOR_POOLS
        #define NiAllocatorDeclareStatics(T, BLOCKSIZE) \
            template <> NiTAbstractPoolAllocator<T>::AllocNode* \
                NiTAbstractPoolAllocator<T>::ms_pkBlockHeader = NULL; \
            template <> NiTAbstractPoolAllocator<T>::AllocNode* \
                NiTAbstractPoolAllocator<T>::ms_pkFreeMem = NULL; \
            template <> efd::CriticalSection \
                NiTAbstractPoolAllocator<T>::ms_kCriticalSection("NiTPool"); \
            template <> unsigned int \
                NiTAbstractPoolAllocator<T>::ms_uiBlockSize = BLOCKSIZE; \
            template <> unsigned int \
                NiTAbstractPoolAllocator<T>::ms_uiAllocated = 0; \
            template <> unsigned int \
                NiTAbstractPoolAllocator<T>::ms_uiMaxAllocated = 0;
    #endif // EE_USE_PER_THREAD_ALLOCATOR_POOLS
#else // NIDEBUG
    #if EE_USE_PER_THREAD_ALLOCATOR_POOLS
        #define NiAllocatorDeclareStatics(T, BLOCKSIZE) \
            template <> NiTAbstractPoolAllocator<T>::AllocNode* \
                NiTAbstractPoolAllocator<T>::ms_pkBlockHeader = NULL; \
            template <> EE_IMPLEMENT_STATIC_TLS_MEMBER(NiTAbstractPoolAllocator<T>::AllocNode*,\
                ms_pkFreeMem,NiTAbstractPoolAllocator<T>); \
            template <> NiTAbstractPoolAllocator<T>::FreeChain* \
                NiTAbstractPoolAllocator<T>::ms_pkFreeChainList = NULL; \
            template <> efd::CriticalSection \
                NiTAbstractPoolAllocator<T>::ms_kCriticalSection = 0; \
            template <> unsigned int \
                NiTAbstractPoolAllocator<T>::ms_uiBlockSize = BLOCKSIZE; \
            template <> bool \
                NiTAbstractPoolAllocator<T>::m_sbIsPerThreadShutdown = false;
    #else // EE_USE_PER_THREAD_ALLOCATOR_POOLS
        #define NiAllocatorDeclareStatics(T, BLOCKSIZE) \
            template <> NiTAbstractPoolAllocator<T>::AllocNode* \
                NiTAbstractPoolAllocator<T>::ms_pkBlockHeader = NULL; \
            template <> NiTAbstractPoolAllocator<T>::AllocNode* \
                NiTAbstractPoolAllocator<T>::ms_pkFreeMem = NULL; \
            template <> efd::CriticalSection \
                NiTAbstractPoolAllocator<T>::ms_kCriticalSection = 0; \
            template <> unsigned int \
                NiTAbstractPoolAllocator<T>::ms_uiBlockSize = BLOCKSIZE;
    #endif // EE_USE_PER_THREAD_ALLOCATOR_POOLS
#endif // NIDEBUG

#define NiAllocatorSetBlockSize(T, BLOCKSIZE) \
    NiTAbstractPoolAllocator<T>::SetBlockSize(BLOCKSIZE);
#define NiAllocatorEnsureFreeMem(T) \
    NiTAbstractPoolAllocator<T>::EnsureFreeMem();

template <class T> class NiTAbstractPoolAllocator
{
public:

    // Virtuals are not used because they add additional memory for each
    // class derived. This class can be thought of as abstract with the
    // following commented classes as pure virtuals.
    // virtual void* Allocate() = 0;
    // virtual void Deallocate (void* p) = 0;

    static void _SDMShutdown();
    static void SetBlockSize(unsigned int uiBlockSize);
    static void EnsureFreeMem();
    static void CreateFreeMem();
protected:
    // list is doubly-linked
    class AllocNode : public NiMemObject
    {
    public:
        AllocNode* m_pkNext;
        void* m_pkData;
        T m_element;
    };

    static AllocNode* ms_pkBlockHeader;
    static unsigned int ms_uiBlockSize;

    static efd::CriticalSection ms_kCriticalSection;

#if EE_USE_PER_THREAD_ALLOCATOR_POOLS
    class FreeChain : public NiMemObject
    {
    public:
        FreeChain* m_pkNext;
        AllocNode* m_pkData;

        FreeChain()
        {
            m_pkNext = NULL;
            m_pkData = NULL;
        }
    };

    static void GetFreeMemFromChain();

    EE_DECLARE_STATIC_TLS_MEMBER(AllocNode*, ms_pkFreeMem);

    static FreeChain* ms_pkFreeChainList;
    static bool m_sbIsPerThreadShutdown;
    static void _SDMPerTheadShutdown();
#ifdef NIDEBUG
    EE_DECLARE_STATIC_TLS_MEMBER(unsigned int,ms_uiAllocated);
    EE_DECLARE_STATIC_TLS_MEMBER(unsigned int,ms_uiMaxAllocated);
#endif // NIDEBUG
#else
    static AllocNode* ms_pkFreeMem;
#ifdef NIDEBUG
    static unsigned int ms_uiAllocated;
    static unsigned int ms_uiMaxAllocated;
#endif // NIDEBUG
#endif
public:
    enum Constants
    {
        SizeOfAllocNode = sizeof(AllocNode)
    };
};

//--------------------------------------------------------------------------------------------------
// Inline include
#include "NiTAbstractPoolAllocator.inl"

//--------------------------------------------------------------------------------------------------

#endif
