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

//------------------------------------------------------------------------------------------------
inline size_t egf::EntityIDHashFunctor::operator()(const EntityID key) const
{
    efd::UInt64 v = key.GetValue();
    return (size_t)(v ^ (v >> 32));
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 egf::EntityManager::GetCount() const
{
    return (efd::UInt32)m_EntityCacheMap.size();
}

//------------------------------------------------------------------------------------------------
inline egf::EntityManager::FilteredIterator::FilteredIterator(
    const egf::EntityManager::FilteredIterator& other)
    : m_iter(other.m_iter)
    , m_pfnFilter(other.m_pfnFilter)
    , m_pParam(other.m_pParam)
{
}

//------------------------------------------------------------------------------------------------
inline egf::EntityManager::FilteredIterator& egf::EntityManager::FilteredIterator::operator=(
    const egf::EntityManager::FilteredIterator& other)
{
    m_iter = other.m_iter;
    m_pfnFilter = other.m_pfnFilter;
    m_pParam = other.m_pParam;
    return *this;
}

//------------------------------------------------------------------------------------------------
inline egf::EntityManager::FilteredIterator::FilteredIterator(
    egf::EntityManager::EntityMap::const_iterator iter,
    egf::EntityManager::FilterFunction i_pfn,
    void* i_pParam)
    : m_iter(iter)
    , m_pfnFilter(i_pfn)
    , m_pParam(i_pParam)
{
}

