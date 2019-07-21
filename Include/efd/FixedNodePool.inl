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
// Implementation of efd::FixedNodePool
//------------------------------------------------------------------------------------------------
template <typename NodeType>
inline FixedNodePool<NodeType>::FixedNodePool(size_t size)
{
    m_initialSize = size;

    if (size > 0)
        m_pNodeAlloc = EE_NEW NodeType[m_initialSize];
    else
        m_pNodeAlloc = NULL;
}

//------------------------------------------------------------------------------------------------
template <typename NodeType>
inline FixedNodePool<NodeType>::~FixedNodePool()
{
    if (m_pNodeAlloc)
    {
        // Free the initial reservation
        EE_DELETE [] m_pNodeAlloc;
    }
}

//------------------------------------------------------------------------------------------------
template <typename NodeType>
inline NodeType* FixedNodePool<NodeType>::GetAt(unsigned int ui)
{
    EE_ASSERT(ui < m_initialSize);
    return m_pNodeAlloc + ui;
}

//------------------------------------------------------------------------------------------------
template <typename NodeType>
inline size_t FixedNodePool<NodeType>::ReleaseNode(NodeType* pNodeToDelete)
{
    // Delete the node if it was not part of the initial pool allocation
    if ((pNodeToDelete >= m_pNodeAlloc) && (pNodeToDelete < m_pNodeAlloc + m_initialSize))
    {
        return 0;
    }
    else
    {
        EE_DELETE pNodeToDelete;

        return 1;
    }
}

//------------------------------------------------------------------------------------------------
template <typename NodeType>
inline size_t FixedNodePool<NodeType>::GetSize()
{
    return m_initialSize;
}

//------------------------------------------------------------------------------------------------

} // end namespace efd
