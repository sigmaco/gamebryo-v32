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
#ifndef NITDEFAULTALLOCATOR_H
#define NITDEFAULTALLOCATOR_H
#include <NiMemObject.h>

// To help prevent warning C4786 which is caused by template name expansion,
// here we define our name to be less lengthy.
#define NiTDefaultAllocator DFALL

// NiTDefaultAllocator is used for non-pooling allocations
template <class T> class NiTDefaultAllocator
{
public:
    inline void* Allocate()
    {
        AllocNode* pkNode = NiNew AllocNode;
        pkNode->m_element = 0;
        return (void*) pkNode;
    }
    inline void Deallocate (void* p)
    {
        NiDelete (AllocNode*)p;
    }
protected:
    // list is doubly-linked
    class AllocNode : public NiMemObject
    {
        public:
            AllocNode* m_pkNext;
            void* m_pkData;
            T m_element;
    };
public:
    enum Constants
    {
        SizeOfAllocNode = sizeof(AllocNode)
    };
};

#endif
