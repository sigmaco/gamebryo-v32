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

//--------------------------------------------------------------------------------------------------
inline NiTerrainTaskQueue::NiTerrainTaskQueue():
    m_kProcessCallback(0),
    m_uiNumActiveWorkUnits(0),
    m_uiNumReservedWorkUnits(0)
{

}

//--------------------------------------------------------------------------------------------------
inline NiTerrainTaskQueue::~NiTerrainTaskQueue()
{
    EE_ASSERT(m_kWorkQueue.size() == 0);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTaskQueue::SetTaskProcessingCallback(
    const ProcessCallbackType& kProcessTaskCallback, void* pvCallbackArgument)
{
    m_kMutex.Lock();
    EE_ASSERT(m_kWorkQueue.size() == 0);
    m_kProcessCallback = kProcessTaskCallback;
    m_pvCallbackArgument = pvCallbackArgument;
    m_kMutex.Unlock();
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 NiTerrainTaskQueue::GetQueueSize()
{
    m_kMutex.Lock();
    efd::UInt32 uiQueueSize = m_kWorkQueue.size();
    m_kMutex.Unlock();

    return uiQueueSize;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 NiTerrainTaskQueue::GetNumUnreservedWorkUnits()
{
    m_kMutex.Lock();
    efd::UInt32 uiNumTasks = m_kWorkQueue.size() - m_uiNumReservedWorkUnits;
    m_kMutex.Unlock();

    return uiNumTasks;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
inline NiTerrainTaskProcessor::NiTerrainTaskProcessor() :
    m_uiNumWorkers(0),
    m_uiNumActiveWorkers(0),
    m_kTaskNotified(m_kLock)
{
    m_pkThreadFunction = EE_NEW ThreadFunction(this);
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainTaskProcessor::~NiTerrainTaskProcessor()
{
    EE_DELETE m_pkThreadFunction;

    // Loop through all the threads ever created and destroy them
    ThreadList::iterator kIter;
    for (kIter = m_kThreadPool.begin(); kIter != m_kThreadPool.end(); ++kIter)
    {
        efd::Thread* pkThread = *kIter;
        while (pkThread->GetStatus() != efd::Thread::COMPLETE)
            efd::Sleep(10);

        EE_DELETE pkThread;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTaskProcessor::SetAquireTaskQueueCallback(void* pvArg, 
    AquireTaskQueueCallbackType kCallback)
{
    m_pvCallbackArgument = pvArg;
    m_kAquireCallback = kCallback;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTaskProcessor::NotifyTaskAdded()
{
    m_kLock.Lock();

    // Wake up any threads waiting for a task
    m_kTaskNotified.Signal();

    // We may need to execute this task immediately (threading disabled)
    if (m_uiNumActiveWorkers == 0)
        ExecuteNextWorkUnit();

    m_kLock.Unlock();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTaskProcessor::SetNumWorkers(efd::UInt32 uiNumWorkers)
{
    m_kLock.Lock();
    m_uiNumWorkers = uiNumWorkers;
    while (m_uiNumActiveWorkers < m_uiNumWorkers)
    {
        EnlistWorker();
    }

    m_kLock.Unlock();
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 NiTerrainTaskProcessor::GetNumWorkers() const
{
    return m_uiNumWorkers;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTaskProcessor::EnlistWorker()
{
    m_kLock.Lock();

    // Fetch a thread that is dormant
    efd::Thread* pkThread = NULL;
    if (m_kThreadPool.size() > m_uiNumActiveWorkers)
    {
        // Fetch an already available dormant thread
        pkThread = m_kThreadPool[m_uiNumActiveWorkers];
    }
    else
    {
        // Create a new thread
        pkThread = efd::Thread::Create(m_pkThreadFunction, efd::UInt32(
            efd::Thread::USEDEF_STACK_SIZE), "Terrain Worker Thread");
        m_kThreadPool.push_back(pkThread);
    }

    m_uiNumActiveWorkers++;
    m_kLock.Unlock();

    // Tell the thread to resume
    EE_VERIFY(pkThread->Resume() != -1);   
}
//--------------------------------------------------------------------------------------------------
inline bool NiTerrainTaskProcessor::RetireWorker(efd::Thread* pkThread)
{
    bool bRetire = false;
    m_kLock.Lock();
    if (m_uiNumActiveWorkers > m_uiNumWorkers)
    {
        // Retire this worker
        bRetire = true;
        m_uiNumActiveWorkers--;

        // Swap the last active one with this inactive one
        ThreadList::iterator kRemoveIndex = m_kThreadPool.find(pkThread);
        *kRemoveIndex = m_kThreadPool[m_uiNumActiveWorkers];
        m_kThreadPool[m_uiNumActiveWorkers] = pkThread;
    }
    m_kLock.Unlock();
    return bRetire;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainTaskProcessor::ThreadFunction::ThreadFunction(NiTerrainTaskProcessor* pkProcessor)
{
    m_pkProcessor = pkProcessor;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 NiTerrainTaskProcessor::ThreadFunction::Execute(efd::Thread* pkArg)
{
    EE_ASSERT(m_pkProcessor);

    while (!m_pkProcessor->RetireWorker(pkArg))
    {
        m_pkProcessor->ExecuteNextWorkUnit();
    }

    return 0;
}

//--------------------------------------------------------------------------------------------------