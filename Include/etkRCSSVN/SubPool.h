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
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#pragma once
#ifndef EE_SUBPOOL_H
#define EE_SUBPOOL_H

// Forward delcarations
struct apr_pool_t;

namespace etk
{ 
    class SubPool
    {
    public:
        inline SubPool(apr_pool_t* pPool);
        inline ~SubPool();

        inline operator apr_pool_t*();

    private:
        apr_pool_t* m_pPool;
    };
} // end namespace etk

#include "SubPool.inl"

#endif // EE_SUBPOOL_H
