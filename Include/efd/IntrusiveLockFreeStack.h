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
#ifndef EE_INTRUSIVELOCKFREESTACK_H
#define EE_INTRUSIVELOCKFREESTACK_H

#include <efd/AtomicOperations.h>
#include <efd/MemObject.h>

namespace efd
{

/**
    This is an implementation of an intrusive single-producer, single-consumer lock-free stack.

    When a node is pushed into the stack, the stack takes ownership for the node.
    When a node is popped from the stack, the stack gives ownership to the caller.

    This class does no memory allocations or deletions unless nodes are left in it at destruction
    time.

    The NodeType template parameter is required to have a public member "NodeType* m_pNext" which
    will be used as part of the stack data structure for the duration of it's stay in the stack.
    There are no other requirements on NodeType.
  */
template <typename NodeType>
class IntrusiveLockFreeStack : public MemObject
{
public:
    /**
        Constructs a single-reader, single-writer lock-free stack.

        The producer and consumer threads must be different.

        Single-reader: Only one thread (the consumer thread) may be issuing calls to
                       Pop at any given time.
        Single-writer: Only one thread (the producer thread) may be issuing calls to
                       Push at any given time.

        The producer and consumer threads can/should be different.  A single thread may act as
        both producer and consumer only if there are no other threads producing or consuming at
        that time (the key is that there should never be multiple producers or multiple consumers).

        These requirements are not internally enforced (if ignored, the container will become
        inconsistent).  For example, it is up to the caller to ensure that only one thread is
        acting as a producer at any given moment.

        Requirements on NodeType:
         - T must have a public member NodeType* m_pNext.
    */
    inline IntrusiveLockFreeStack();

    /**
        Destructs a lock-free stack.

        The caller is responsible for ensuring that there are no threads currently pushing to
        or popping from the stack.
    */
    inline ~IntrusiveLockFreeStack();

    /**
        Pushes a node on to the stack.  The caller gives up ownership of the node's memory.
    */
    inline void Push(NodeType* newNode);

    /**
        Pops a node from the stack if the stack is not empty.  The caller takes ownership of the
        node's memory.

        @param outValue The node removed from the stack.  Only valid if the method returns True
        @return bool True if a node was consumed (outResult is valid).  False if the stack was empty.
    */
    inline bool Pop(NodeType*& outValue);

private:
    /*
    Implementation notes:
      - No need to worry about the 'ABA' problem, since only one thread can produce and only one
        thread can consume, and they are different threads.  The address of the popped node cannot
        be reused by the producer until the consumer frees it, which must happen after it's left the
        stack entirely.
      - Producer owns m_pHead->m_pNext.
      - Both producer and consumer share the ability to update m_pHead.
    */

    // Head of the linked list, shared by producer and consumer
    NodeType* volatile m_pHead;
};

} // namespace efd

#include <efd/IntrusiveLockFreeStack.inl>

#endif
