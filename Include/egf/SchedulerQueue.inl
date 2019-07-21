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


namespace egf
{

    /// Retreive the top task from the queue.  The task will remain on the top of the queue.
    /// @param pTask The task to add
    inline ScheduledTask* SchedulerQueue::top() const
    {
        EE_ASSERT(!m_priorityQueue.empty());
        return m_priorityQueue.front();
    }

    /// Gets the size of the queue
    inline size_t SchedulerQueue::size() const
    {
        return m_priorityQueue.size();
    }

    /// Determines if the queue is empty
    inline bool SchedulerQueue::empty() const
    {
        return m_priorityQueue.empty();
    }

    /// Retrieves an iterator for the first item in the queue.  Results are sorted by
    /// execution time.
    inline SchedulerQueue::iterator SchedulerQueue::begin()
    {
        return m_priorityQueue.begin();
    }

    /// Retrieves a const iterator for the first item in the queue.  Results are sorted by
    /// execution time.
    inline SchedulerQueue::const_iterator SchedulerQueue::begin() const
    {
        return m_priorityQueue.begin();
    }

    /// Retrieves an iterator for the end of the queue.
    inline SchedulerQueue::iterator SchedulerQueue::end()
    {
        return m_priorityQueue.end();
    }

    /// Retrieves a const iterator for the end of the queue.
    inline SchedulerQueue::const_iterator SchedulerQueue::end() const
    {
        return m_priorityQueue.end();
    }

} // end namespace egf

