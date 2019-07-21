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
template <typename T>
inline LockFreeQueue<T>::LockFreeQueue(size_t initialSize)
: m_linearPool(initialSize+1)
{
    // The head points to the front of the list, while the tail and divider point to the sentinel
    // node
    m_pHead = m_linearPool.GetAt(0);
    m_pDivider = m_linearPool.GetAt(initialSize);
    m_pTail = m_pDivider;

    // String the nodes together
    for (size_t ui = 0; ui < initialSize; ++ui)
    {
        m_linearPool.GetAt(ui)->m_pNext = m_linearPool.GetAt(ui + 1);
    }
    m_pTail->m_pNext = NULL;
}

//------------------------------------------------------------------------------------------------
template <typename T>
inline LockFreeQueue<T>::~LockFreeQueue()
{
    size_t extraAllocatedCount = 0;

    // Delete any nodes in the list that were not part of the initial pool allocation
    while (m_pHead != NULL)
    {
        Node* pNodeToDelete = m_pHead;
        m_pHead = m_pHead->m_pNext;

        extraAllocatedCount += m_linearPool.ReleaseNode(pNodeToDelete);
    }

#if defined(EE_EFD_CONFIG_DEBUG) && defined(EE_LOG)
    // If there were additional nodes allocated, print out a warning that the initial reservation
    // was too small
    if (extraAllocatedCount > 0)
    {
        EE_LOG(efd::kFoundation,
            efd::ILogger::kLVL2,
            ("Warning: Additional allocations were required for the LockFreeQueue %p. %u nodes "
            "were used, but only %u were initially allocated.\n",
            this, m_linearPool.GetSize()-1+extraAllocatedCount, m_linearPool.GetSize()-1));
    }
#endif
}

//------------------------------------------------------------------------------------------------
template <typename T>
inline void LockFreeQueue<T>::Produce(const T& value)
{
    Node* newNode;

    // If available, get a node from the free portion of the list (before the divider)
    if (m_pHead != m_pDivider)
    {
        newNode = m_pHead;
        m_pHead = newNode->m_pNext;
    }
    else
    {
        // There are no unconsumed nodes (other than the sentinel), create a new node
        newNode = EE_NEW Node();
    }

    // Add the value to a fresh node
    newNode->m_value = value;
    newNode->m_pNext = NULL;

    // Chain it beyond the current tail
    m_pTail->m_pNext = newNode;

    // Publish that a value was produced (advance the tail pointer)
    Atomic::SetValue(&m_pTail, m_pTail->m_pNext);
}

//------------------------------------------------------------------------------------------------
template <typename T>
inline bool LockFreeQueue<T>::Consume(T& result)
{
    if (m_pDivider != m_pTail)
    {
        // Copy the value from the queue
        result = m_pDivider->m_pNext->m_value;

        // Zero the value field so that it won't cause any lingering resources
        m_pDivider->m_pNext->m_value = T();

        // Publish that a value was consumed (advance the divider)
        Atomic::SetValue(&m_pDivider, m_pDivider->m_pNext);

        return true;
    }
    else
    {
        // The divider points to the tail, so the queue is empty
        return false;
    }
}

//------------------------------------------------------------------------------------------------

} // namespace efd
