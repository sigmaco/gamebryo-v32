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

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
OrderedMap<KEY, VALUE>::NodeType::NodeType(const KEY& i_key, const VALUE& i_value)
    : first(i_key)
    , second(i_value)
{
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
typename OrderedMap<KEY, VALUE>::iterator OrderedMap<KEY, VALUE>::begin()
{
    return m_list.begin();
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
typename OrderedMap<KEY, VALUE>::iterator OrderedMap<KEY, VALUE>::end()
{
    return m_list.end();
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
bool OrderedMap<KEY, VALUE>::push_back(const KEY& i_key, const VALUE& i_value)
{
    typename OMMap::iterator iter = m_map.find(i_key);
    if (iter != m_map.end())
    {
        return false;
    }

    NodeType* pNode = EE_NEW NodeType(i_key, i_value);
    m_list.push_back(pNode);
    m_map[i_key] = pNode;

    return true;
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
typename OrderedMap<KEY, VALUE>::NodeType* OrderedMap<KEY, VALUE>::find(const KEY& i_key)
{
    typename OMMap::iterator iter = m_map.find(i_key);
    if (iter == m_map.end())
    {
        return NULL;
    }
    return iter->second;
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
const typename OrderedMap<KEY, VALUE>::NodeType*
OrderedMap<KEY, VALUE>::find(const KEY& i_key) const
{
    typename OMMap::iterator iter = m_map.find(i_key);
    if (iter == m_map.end())
    {
        return NULL;
    }
    return iter->second;
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
bool OrderedMap<KEY, VALUE>::erase(const KEY& i_key)
{
    typename OMMap::iterator iter = m_map.find(i_key);
    if (iter == m_map.end())
    {
        return false;
    }

    NodeType* p = iter->second;
    m_list.remove(iter->second);
    m_map.erase(iter);
    EE_DELETE p;

    return true;
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
typename OrderedMap<KEY, VALUE>::iterator
OrderedMap<KEY, VALUE>::erase(typename OrderedMap<KEY, VALUE>::iterator it)
{
    if (it != m_list.end())
    {
        NodeType* p = *it;
        EE_ASSERT(p == find(p->first));
        m_map.erase(p->first);
        EE_DELETE p;
        return m_list.erase(it);
    }
    return it;
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
bool OrderedMap<KEY, VALUE>::erase(const NodeType* i_pNode)
{
    typename OMMap::iterator iter = m_map.find(i_pNode->first);
    if (iter == m_map.end())
    {
        return false;
    }

    NodeType* p = iter->second;
    EE_ASSERT(p == i_pNode);
    m_list.remove(iter->second);
    m_map.erase(iter);
    EE_DELETE p;

    return true;
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
void OrderedMap<KEY, VALUE>::clear()
{
    for (typename OMList::iterator listIt = m_list.begin();
        listIt != m_list.end();
        ++listIt)
    {
        NodeType* p = *listIt;
        EE_DELETE p;
    }

    m_list.clear();
    m_map.clear();
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
const typename OrderedMap<KEY, VALUE>::NodeType* OrderedMap<KEY, VALUE>::front() const
{
    if (m_list.empty())
    {
        return NULL;
    }
    const NodeType* p = m_list.front();
    return p;
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
typename OrderedMap<KEY, VALUE>::NodeType* OrderedMap<KEY, VALUE>::front()
{
    if (m_list.empty())
    {
        return NULL;
    }
    NodeType* p = m_list.front();
    return p;
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
bool OrderedMap<KEY, VALUE>::empty() const
{
    return m_list.empty();
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
efd::UInt32 OrderedMap<KEY, VALUE>::size() const
{
    EE_ASSERT(m_list.size() == m_map.size());
    return m_map.size();
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
bool OrderedMap<KEY, VALUE>::pop_front()
{
    if (m_list.empty())
    {
        return false;
    }

    NodeType* p = m_list.front();
    m_map.erase(p->first);
    m_list.pop_front();
    EE_DELETE p;

    return true;
}

//------------------------------------------------------------------------------------------------
template< typename KEY, typename VALUE >
bool OrderedMap<KEY, VALUE>::pop_front(KEY& o_key, VALUE& o_value)
{
    if (m_list.empty())
    {
        return false;
    }

    NodeType* p = m_list.front();
    o_key = p->first;
    o_value = p->second;
    m_map.erase(p->first);
    m_list.pop_front();
    EE_DELETE p;

    return true;
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
