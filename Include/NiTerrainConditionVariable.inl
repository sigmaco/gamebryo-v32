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
inline NiTerrainConditionVariable::NiTerrainConditionVariable(efd::CriticalSection& kMonitor):
    m_kMonitor(kMonitor)
{
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainConditionVariable::~NiTerrainConditionVariable()
{
    // At this point in time there should not be any threads waiting on this condition variable. 
    EE_ASSERT(m_kWaiters.size() == 0);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainConditionVariable::Wait()
{
    EE_ASSERT(m_kMonitor.GetOwningThreadID() == efd::GetCurrentThreadId());
    
    // Add this thread to the list of waiters:
    efd::Semaphore* pkThreadSemaphore = GetThreadSemaphore();
    m_kWaiters.push(pkThreadSemaphore);

    // Release the monitor (we must make sure we unlock enough times)
    efd::UInt32 uiLockCount = m_kMonitor.GetCurrentLockCount();
    for (efd::UInt32 uiCount = 0; uiCount < uiLockCount; ++uiCount) 
        m_kMonitor.Unlock();

    // Wait
    EE_ASSERT(pkThreadSemaphore->GetCount() >= 0);
    pkThreadSemaphore->Wait();

    // Reaquire the monitor
    for (efd::UInt32 uiCount = 0; uiCount < uiLockCount; ++uiCount) 
        m_kMonitor.Lock();
    EE_ASSERT(m_kMonitor.GetOwningThreadID() == efd::GetCurrentThreadId());
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainConditionVariable::Signal()
{
    EE_ASSERT(m_kMonitor.GetOwningThreadID() == efd::GetCurrentThreadId());
    // Release the first thread if there is one.
    if (m_kWaiters.size())
    {
        efd::Semaphore* pkThreadSemaphore = m_kWaiters.front();
        m_kWaiters.pop();
        pkThreadSemaphore->Signal();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainConditionVariable::Broadcast()
{
    EE_ASSERT(m_kMonitor.GetOwningThreadID() == efd::GetCurrentThreadId());
    // Release all the threads that are waiting
    while(m_kWaiters.size())
    {
        efd::Semaphore* pkThreadSemaphore = m_kWaiters.front();
        m_kWaiters.pop();
        pkThreadSemaphore->Signal();
    }
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
template<class T>
inline NiTerrainPollableValue<T>::NiTerrainPollableValue(efd::CriticalSection& kMonitor,
    const T& kValue):
    m_kValue(kValue),    
    m_kCV(kMonitor)
{
}

//--------------------------------------------------------------------------------------------------
template<class T>
inline void NiTerrainPollableValue<T>::SetValue(const T& kValue)
{
    if (m_kValue != kValue)
    {
        m_kValue = kValue;
        m_kCV.Broadcast();
    }
}

//--------------------------------------------------------------------------------------------------
template<class T>
inline const T& NiTerrainPollableValue<T>::GetValue() const
{
    return m_kValue;
}
//--------------------------------------------------------------------------------------------------
template<class T>
inline void NiTerrainPollableValue<T>::WaitEqual(const T& kValue)
{
    while (m_kValue != kValue)
    {
        m_kCV.Wait();
    }
}
//--------------------------------------------------------------------------------------------------
