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
#ifndef NITABSTRACTPOOLALLOCATORFUNCSTORAGE_H
#define NITABSTRACTPOOLALLOCATORFUNCSTORAGE_H

#include <NiCriticalSection.h>
#include <NiMemObject.h>
#include <NiMainLibType.h>

#if EE_USE_PER_THREAD_ALLOCATOR_POOLS

class NIMAIN_ENTRY NiTAbstractPoolAllocatorFuncStorage
{
public:
    typedef void (*PerThreadShutdownFunction)(void);

    static void AddPerThreadShutdown(PerThreadShutdownFunction pfnPerThreadShutdown);
    static void RemovePerThreadShutdown(PerThreadShutdownFunction pfnPerThreadShutdown);
    static void PerThreadShutdown();

    class AllocNode : public NiMemObject
    {
        public:
            AllocNode* m_pkNext;
            PerThreadShutdownFunction m_pfPerThreadShutdown;
    };

    static AllocNode* ms_pkBlockHeader;
    static efd::CriticalSection ms_kCriticalSection;
};

#endif // EE_USE_PER_THREAD_ALLOCATOR_POOLS
#endif // NITABSTRACTPOOLALLOCATORFUNCSTORAGE_H