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

#ifndef NITERRAINSTREAMINGLISTENERLIST_H
#define NITERRAINSTREAMINGLISTENERLIST_H

#include "NiTerrainStreamingManager.h"
#include <NiRefObject.h>

/**
    A basic streaming listener class to implement a list of streaming listeners. Attach
    this class to the Streaming manager and attach any number of streaming listeners to this 
    class to allow many classes to listen to streaming events at once.
*/
class NITERRAIN_ENTRY NiTerrainStreamingListenerList : public NiTerrainStreamingManager::Listener,
    public NiRefObject
{
public:
    /// Defines a list of streaming listeners
    typedef efd::list< efd::SmartPointer<NiTerrainStreamingManager::Listener> > ListenerList;

    /// Default constructor
    NiTerrainStreamingListenerList();

    /// Virtual destructor
    virtual ~NiTerrainStreamingListenerList();

    /// Adds a listener to the event distribution list
    void AddListener(NiTerrainStreamingManager::Listener* pkListener);

    /// Removes a listener from the event distribution list
    void RemoveListener(NiTerrainStreamingManager::Listener* pkListener);

    /// Removes all listeners from the event distribution list
    void RemoveAllListeners();

    /// @name Listener implementation
    //@{
    virtual void IncRefCount();
    virtual void DecRefCount();
    virtual void ReportStartTask(TaskID kTaskID, SectorID kSectorID, TaskType::VALUE eTaskType);
    virtual void ReportTaskStatus(TaskID kTaskID, TaskType::VALUE eTaskType, 
        Status::VALUE eStatus);
    virtual void ReportFinishTask(TaskID kTaskID, TaskType::VALUE eTaskType, 
        efd::UInt32 uiErrorCode);
    //@}

private:

    /// Critical section to protect the list in this class
    efd::CriticalSection m_kMutex;

    /// The list of listeners.
    ListenerList m_kListenerList;
};

#endif // NITERRAINSTREAMINGLISTENERLIST_H