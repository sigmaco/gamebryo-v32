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
// Implementation of efd::LockFreeStack
//------------------------------------------------------------------------------------------------
template <typename T>
inline LockFreeStack<T>::LockFreeStack(size_t initialSize)
   : m_linearPool(initialSize)
{
    // Populate the freelist with the initial pool of nodes
    for (unsigned int ui = 0; ui < initialSize; ++ui)
    {
        m_freeList.Push(m_linearPool.GetAt(ui));
    }
}

//------------------------------------------------------------------------------------------------
template <typename T>
inline LockFreeStack<T>::~LockFreeStack()
{
    size_t extraAllocatedCount = 0;

    // Remove the nodes from the live stack and free list
    SingleLinkedNode* pNode;
    while (m_liveStack.Pop(pNode))
        extraAllocatedCount += m_linearPool.ReleaseNode(pNode);
    while (m_freeList.Pop(pNode))
        extraAllocatedCount += m_linearPool.ReleaseNode(pNode);

    (void)extraAllocatedCount;
#if defined(EE_EFD_CONFIG_DEBUG) && defined(EE_LOG)
    // If there were additional nodes allocated, print out a warning that the initial reservation
    // was too small
    if (extraAllocatedCount > 0)
    {
        EE_LOG(efd::kFoundation,
            efd::ILogger::kLVL2,
            ("Warning: Additional allocations were required for the LockFreeStack %p. "
            "%u nodes were used, but only %u were initially allocated.",
            this, extraAllocatedCount + m_linearPool.GetSize(), m_linearPool.GetSize()));
    }
#endif
}

//------------------------------------------------------------------------------------------------
template <typename T>
inline void LockFreeStack<T>::Push(const T& newValue)
{
    // Get a new node, either from the freelist or created fresh
    SingleLinkedNode* pNewNode;
    if (!m_freeList.Pop(pNewNode))
    {
        pNewNode = EE_NEW SingleLinkedNode();
    }
    pNewNode->m_value = newValue;

    // Add it to the live stack
    m_liveStack.Push(pNewNode);
}

//------------------------------------------------------------------------------------------------
template <typename T>
inline bool LockFreeStack<T>::Pop(T& outValue)
{
    SingleLinkedNode* pResult = NULL;
    if (m_liveStack.Pop(pResult))
    {
        // Get the value from the popped node
        outValue = pResult->m_value;

        // Recycle the node back to the freelist
        pResult->m_value = T();
        m_freeList.Push(pResult);

        return true;
    }

    return false;
}

//------------------------------------------------------------------------------------------------

} // namespace efd
