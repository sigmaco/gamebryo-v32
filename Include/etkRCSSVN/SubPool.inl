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

namespace etk
{ 
//--------------------------------------------------------------------------------------------------
SubPool::SubPool(apr_pool_t* pPool)
{
    m_pPool = svn_pool_create(pPool);
    EE_ASSERT(m_pPool);
}
//--------------------------------------------------------------------------------------------------
SubPool::~SubPool()
{
    svn_pool_destroy(m_pPool);
}
//--------------------------------------------------------------------------------------------------
SubPool::operator apr_pool_t*()
{
    return m_pPool;
}
//--------------------------------------------------------------------------------------------------
} // namespace etk