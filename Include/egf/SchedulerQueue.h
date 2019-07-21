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

#pragma once
#ifndef EE_SchedulerQueue_h
#define EE_SchedulerQueue_h

#include <egf/egfLibType.h>
#include <egf/ScheduledTask.h>


namespace egf
{

    /**
        Data structure to store the scheduler queue.  It acts like a priority queue but can be
        iterated and supports fast lookup by event ID.  Internally this queue is currently
        implemented using a sorted list and a map of EventIDs.
    */
    class SchedulerQueue
    {
        // DT32316 This data structure is performance critical to the egf::Scheduler. A large scale
        // server might have hundreds of thousands of queued tasks outstanding. As such this class
        // would benefit greatly from optimization.
    public:
        /// Add a new task to the queue.  The task will be sorted by its execution time.  This
        /// will hold a reference to the task.
        /// @param pTask The task to add
        void push(ScheduledTask* pTask);

        /// Retrieve the top task from the queue.  The task will remain on the top of the queue.
        inline ScheduledTask* top() const;

        /// Remove the top task from the queue, freeing the reference held to it.
        void pop();

        /// Gets the size of the queue
        inline size_t size() const;

        /// Determines if the queue is empty
        inline bool empty() const;

        /// Finds a task in the queue by EventID.
        ScheduledTask* find(egf::EventID evid);

        /// Finds a task in the queue by EventID.
        const ScheduledTask* find(egf::EventID evid) const;

        /// Removes the task with the given EventID from the queue.
        bool erase(egf::EventID evid);

        /// Erase the task with the given EventID from the queue.
        /// @param[in] i_eventID
        /// @param[out] o_pTask The task that was removed
        /// @return True if an event was erased, false if the event was not found
        bool erase(egf::EventID i_eventID, ScheduledTaskPtr& o_pTask);

        /// Iterator type for iterating the queue
        typedef efd::list<ScheduledTask*>::iterator iterator;
        /// Const iterator type for iterating the queue
        typedef efd::list<ScheduledTask*>::const_iterator const_iterator;

        /// Retrieves an iterator for the first item in the queue.  Results are sorted by
        /// execution time.
        inline iterator begin();

        /// Retrieves a const iterator for the first item in the queue.  Results are sorted by
        /// execution time.
        inline const_iterator begin() const;

        /// Retrieves an iterator for the end of the queue.
        inline iterator end();

        /// Retrieves a const iterator for the end of the queue.
        inline const_iterator end() const;

    protected:
        efd::list<ScheduledTask*> m_priorityQueue;
        efd::map<egf::EventID, ScheduledTask*> m_eventMap;
    };


} // end namespace egf

#include <egf/SchedulerQueue.inl>

#endif // EE_SchedulerQueue_h
