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
#ifndef EE_LOCKFREEQUEUE_H
#define EE_LOCKFREEQUEUE_H

#include <efd/AtomicOperations.h>
#include <efd/MemObject.h>
#include <efd/FixedNodePool.h>

namespace efd
{
/**
    This is an implementation of a single-reader, single-writer lock-free queue.

    Single-reader: Only one thread (the consumer thread) may be issuing calls to
                   Consume at any given time.
    Single-writer: Only one thread (the producer thread) may be issuing calls to
                   Produce or ReclaimSpace at any given time.

    The producer and consumer threads can/should be different.  A single thread may act as
    both producer and consumer only if there are no other threads producing or consuming at
    that time (the key is that there should never be multiple producers or multiple consumers).

    These requirements are not internally enforced (if ignored, the container will become
    inconsistent).  For example, it is up to the caller to ensure that only one thread is
    acting as a producer at any given moment.

    Requirements on T (the type of values stored in the queue):
     - T must have an accessible default constructor
       (i.e., T value = T(); must be a valid statement).
     - T must have an accessible assignment operator (which will be invoked when objects are
       produced into the queue, or consumed from the queue)
    These are naturally satisified by pointer and integral types.

    The constructor takes an initial size reservation parameter to prevent per-operation memory
    allocation, and as long as the working size of the queue is below the initial size, no
    operation on the queue will force a context switch.
  */

template <typename T>
class LockFreeQueue : public MemObject
{
public:
    /**
        Constructs a single-reader, single-writer lock-free queue.

        @param initialSize The number of nodes to preallocate.  If too many items are pushed in
        the queue, it will grow by dynamically allocating additional nodes, so it is a good idea
        to conservatively choose a large-enough initialSize.  As long as the working size of the
        queue is below the initial size, no operation on this queue will force a context switch.

        Since allocations could cause a temporary lock inside of the memory manager, a warning
        will be emitted by the destructor in debug builds if the initialSize parameter was too
        small.
    */
    inline LockFreeQueue(size_t initialSize = 0);

    /**
        Destructs a lock-free queue.

        The caller is responsible for ensuring that there are no threads currently producing to or
        consuming from the queue.
    */
    inline ~LockFreeQueue();

    /**
        Produces a value (pushes it into the queue for later use by the consumer thread).  This
        method also reclaims space used by already consumed nodes.

        This method may only be called from the producer thread.
    */
    inline void Produce(const T& value);

    /**
        Consumes a value (removes it from the queue).

        @param outResult The value removed from the queue.  Only valid if the method returns True
        @return bool True if a value was consumed, otherwise false if the queue was empty.
    */
    inline bool Consume(T& outResult);

private:
    /*
    The underlying implementation is a singly-linked-list with tracking of the head, tail, and a
    divider node, which points to the last consumed node (to keep this pointer valid, there will
    always be a dummy node present in the list, even if there were no nodes produced).

    The divider node allows the producer to work on one side, and the consumer on the other side.

    Nodes before the divider can be lazily freed by the producer (they have already been consumed),
    nodes after the divider are the active queue that the consumer consumes.  The divider always
    points to a 'dummy' node, with a valid next pointer that indicates the top of the queue.

    No need to worry about the 'ABA' problem, since only one thread can produce and only one
    thread can consume.  The producer cannot reuse an address in the midst of the consumer working,
    since only the consumer updates the divider, and the producer won't reuse it until it's on the
    production side of the divider.

    Producer owns:
      - The ability to update m_pHead and m_pTail
      - The contents of all nodes before the m_pDivider node
      - The next pointer of the tail node (m_pTail->m_pNext)

    Consumer owns:
      - The ability to update m_pDivider
      - The contents of all nodes after (and including) m_pDivider node
        except for m_pTail->m_pNext
    */
    struct Node : public MemObject
    {
        Node* m_pNext;
        T m_value;
    };

    // Head of the linked list, for producer only
    Node* m_pHead;

    // Divider point of the linked list (points to the most recently consumed node),
    // shared between producer and consumer
    Node* volatile m_pDivider;

    // Tail of the linked list, shared between producer and consumer
    Node* volatile m_pTail;

    // Linearly allocated pool of nodes, only used at init/shutdown,
    // never by producer or consumer
    FixedNodePool<Node> m_linearPool;
};

} // namespace efd

#include <efd/LockFreeQueue.inl>

#endif
