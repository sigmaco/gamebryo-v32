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
#ifndef EE_LOCKFREESTACK_H
#define EE_LOCKFREESTACK_H

#include <efd/AtomicOperations.h>
#include <efd/MemObject.h>
#include <efd/FixedNodePool.h>
#include <efd/IntrusiveLockFreeStack.h>

namespace efd
{

/**
    This is an implementation of a single-reader, single-writer lock-free stack.

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

    Requirements on T (the type of values stored in the stack):
     - T must have an accessible default constructor
       (i.e., T value = T(); must be a valid statement).
     - T must have an accessible assignment-operator (which will be invoked when objects are
       pushed into the stack, or popped from the stack)
    These are naturally satisified by pointer and integral types.

    The constructor takes an initial size reservation parameter to prevent per-operation memory
    allocation, and as long as the working size of the stack is below the initial size, no
    operation on the stack will force a context switch.
*/

template <typename T>
class LockFreeStack : public MemObject
{
public:
    /**
        Constructs a single-reader, single-writer lock-free stack.

        @param initialSize The number of nodes to preallocate.  If too many items are pushed in
        the stack, it will grow by dynamically allocating additional nodes, so it is a good idea
        to conservatively choose a large-enough initialSize.  As long as the working size of the
        stack is below the initial size, no operation on this stack will force a context switch.

        Since allocations could cause a temporary lock inside of the memory manager, a warning
        will be emitted by the destructor in debug builds if the initialSize parameter was too
        small.
    */
    inline LockFreeStack(size_t initialSize = 0);

    /**
        Destructs a lock-free stack.

        The caller is responsible for ensuring that there are no threads currently pushing to
        or popping from the stack.
    */
    inline ~LockFreeStack();

    /**
        Pushes a node on to the stack.
    */
    inline void Push(const T& newValue);

    /**
        Pops a value from the stack if the stack is not empty.

        @param outValue The value removed from the stack.  Only valid if the method returns True.
        @return bool True if a node was consumed (outValue is valid).  False if the stack was empty.
    */
    inline bool Pop(T& outValue);

private:
    struct SingleLinkedNode : public MemObject
    {
        SingleLinkedNode* m_pNext;
        T m_value;
    };

    /*
    Implementation notes:
      - This non-intrusive stack is implemented using a pair of intrusive stacks, each operating in one
        direction.  One is used as the actual communication stack, while the other is used as a free list
        of already popped nodes.
      - The free list is initially populated with a fixed number of nodes to avoid per-operation memory
        allocation/deallocation.
      - Let thread A be the producer (caller of Push on this class)
      - Let thread B be the consumer (caller of Pop)
    */

    // The live stack has producer=A, consumer=B
    IntrusiveLockFreeStack<SingleLinkedNode> m_liveStack;

    // The freelist has producer=B, consumer=A
    IntrusiveLockFreeStack<SingleLinkedNode> m_freeList;

    // Linearly allocated pool of nodes, only used at init/shutdown,
    // never by producer or consumer
    FixedNodePool<SingleLinkedNode> m_linearPool;
};

} // namespace efd

#include <efd/LockFreeStack.inl>

#endif
