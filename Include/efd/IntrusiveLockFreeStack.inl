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
// Implementation of efd::IntrusiveLockFreeStack
//------------------------------------------------------------------------------------------------
template <typename NodeType>
inline IntrusiveLockFreeStack<NodeType>::IntrusiveLockFreeStack()
{
    // Create a new list with a single empty node
    m_pHead = NULL;
}

//------------------------------------------------------------------------------------------------
template <typename NodeType>
inline IntrusiveLockFreeStack<NodeType>::~IntrusiveLockFreeStack()
{
    // Delete all of the nodes in the list
    while (m_pHead != NULL)
    {
        NodeType* pNodeToDelete = m_pHead;
        m_pHead = m_pHead->m_pNext;
        EE_DELETE pNodeToDelete;
    }
}

//------------------------------------------------------------------------------------------------
template <typename NodeType>
inline void IntrusiveLockFreeStack<NodeType>::Push(NodeType* newNode)
{
    // Publish that a value was produced (add it to the head of the stack)
    // Keep trying { newNode->next = oldHead;  head = newNode; } until it succeeds
    do
    {
        newNode->m_pNext = m_pHead;
    } while (!Atomic::CompareAndSwap(&m_pHead, newNode->m_pNext, newNode));
}

//------------------------------------------------------------------------------------------------
template <typename NodeType>
inline bool IntrusiveLockFreeStack<NodeType>::Pop(NodeType*& outResult)
{
    NodeType* pCurrent = m_pHead;
    while (pCurrent != NULL)
    {
        // Attempt to pop the top of the stack (if the head is still what we think it was, pop it)
        if (Atomic::CompareAndSwap(&m_pHead, pCurrent, pCurrent->m_pNext))
        {
            outResult = pCurrent;
            outResult->m_pNext = NULL;
            return true;
        }
        pCurrent = m_pHead;
    }

    return false;
}

//------------------------------------------------------------------------------------------------

} // namespace efd
