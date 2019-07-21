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

#pragma once
#ifndef EE_FIXEDNODEPOOL_H
#define EE_FIXEDNODEPOOL_H

#include <efd/MemObject.h>

namespace efd
{

/**
    This class represents a simple fixed-length buffer of nodes that cannot be resized.

    It does not internally track which nodes are free or used, but it is capable of determining
    if a given node is part of it's buffer, which allows it to be used as a useful component of
    other containers.  In this usage pattern, the outer container will create a fixed pool and
    initialize it's freelist with that pool.  If the freelist is exhausted and new allocations are
    created, then they will be individually deleted when ReleaseNode is called on them.
*/
template <typename NodeType>
class FixedNodePool
{
public:
    /// Create a fixed-size pool of nodes
    inline FixedNodePool(size_t size);

    /// Destroy the fixed-size pool, releasing the memory used by it
    inline ~FixedNodePool();

    /// Returns the indexed node
    inline NodeType* GetAt(unsigned int ui);

    /// Returns the size of the fixed pool.
    inline size_t GetSize();

    /**
        'Release' the node back to the pool.  If the node was not part of the fixed pool,
        it will be deleted.
        Returns 0 if the node belonged to the pool, and 1 if it was deleted.

        Note: The pool does not keep track of which nodes are free or used, that is up to the caller.
    */
    inline size_t ReleaseNode(NodeType* pNodeToDelete);

private:
    // Head of the linearly allocated pool of nodes
    NodeType* m_pNodeAlloc;

    // Number of nodes in the pool
    size_t m_initialSize;
};

} // end namespace efd

#include <efd/FixedNodePool.inl>

#endif
