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
template< typename T >
T* ServiceManager::GetSystemServiceAs(SSID idSysSer) const
{
    ISystemService* pService = GetSystemService(idSysSer);
    T* pResult = EE_DYNAMIC_CAST(T, pService);
    return pResult;
}

//------------------------------------------------------------------------------------------------
template< typename T >
T* ServiceManager::GetSystemServiceAs() const
{
    ISystemService* pService = GetSystemService(T::CLASS_ID);
    T* pResult = EE_DYNAMIC_CAST(T, pService);
    return pResult;
}

//------------------------------------------------------------------------------------------------
inline bool ServiceManager::IsInitialized() const
{
    return m_threadState > kSysServState_Initializing;
}

//------------------------------------------------------------------------------------------------
inline ServiceManager::ServiceState ServiceManager::GetCurrentState() const
{
    return m_threadState;
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType ServiceManager::GetServiceManagerTime() const
{
    return m_clock.GetCurrentTime();
}

//------------------------------------------------------------------------------------------------
inline void ServiceManager::SetPeriodicLogServiceTiming(efd::Bool bEnableLogging)
{
    m_bLogPeriodicServiceTiming = bEnableLogging;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ServiceManager::GetPeriodicPeriodicLogServiceTiming() const
{
    return m_bLogPeriodicServiceTiming;
}

//------------------------------------------------------------------------------------------------
inline void ServiceManager::SetLogTimingDumpInterval(efd::TimeType kTimingDumpInterval)
{
    m_kTimingDumpInterval = kTimingDumpInterval;
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType ServiceManager::GetLogTimingDumpInterval() const
{
    return m_kTimingDumpInterval;
}

//------------------------------------------------------------------------------------------------
inline void ServiceManager::SetMaxAcceptableTickTime(efd::TimeType kMaxAcceptableTickTime)
{
    m_kMaxAcceptableTickTime = kMaxAcceptableTickTime;
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType ServiceManager::GetMaxAcceptableTickTime() const
{
    return m_kMaxAcceptableTickTime;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ServiceManager::GetSleepTime() const
{
    return m_sleepTime;
}

//------------------------------------------------------------------------------------------------
inline void ServiceManager::SetSleepTime(efd::UInt32 sleeptime)
{
    m_sleepTime = sleeptime;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ServiceManager::GetDeactivatedSleepTime() const
{
    return m_deactivatedSleepTime;
}

//------------------------------------------------------------------------------------------------
inline void ServiceManager::SetDeactivatedSleepTime(efd::UInt32 sleeptime)
{
    m_deactivatedSleepTime = sleeptime;
}

//------------------------------------------------------------------------------------------------
inline void ServiceManager::UseDeactivatedSleepTime(bool deactivated)
{
    m_useDeactivatedSleepTime = deactivated;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ServiceManager::IsRunning() const
{
    return m_inRunOnce;
}

//------------------------------------------------------------------------------------------------
// ServiceManager::DependencyData
//------------------------------------------------------------------------------------------------
inline ServiceManager::DependencyData::DependencyData(SSID id, SInt32 flags)
    : m_service(id)
    , m_flags(flags)
{
}

//------------------------------------------------------------------------------------------------
// ServiceManager::ServiceInfo
//------------------------------------------------------------------------------------------------
inline ServiceManager::ServiceInfo::ServiceInfo()
    : m_idSysSer(INVALID_SSID)
    , m_state(kSysServState_Invalid)
    , m_priority(2000)
    , m_spSysSer()
{
    ResetTiming();
}

//------------------------------------------------------------------------------------------------
inline ServiceManager::ServiceInfo::ServiceInfo(const ServiceInfo &sysSer)
    : m_idSysSer(sysSer.m_idSysSer)
    , m_state(sysSer.m_state)
    , m_priority(sysSer.m_priority)
    , m_spSysSer(sysSer.m_spSysSer)
{
    ResetTiming();
}

//------------------------------------------------------------------------------------------------
inline ServiceManager::ServiceInfo::~ServiceInfo()
{
    // Ensure the smart pointer gets freed
    m_spSysSer = NULL;
}

//------------------------------------------------------------------------------------------------
inline bool ServiceManager::ServiceInfo::operator == (const ServiceInfo &sysSer)
{
    // Since only one service may be registered with a particular SSID
    // we can test for equal on only it
    return m_idSysSer == sysSer.m_idSysSer;
}

//------------------------------------------------------------------------------------------------
inline bool ServiceManager::ServiceInfo::operator != (const ServiceInfo &sysSer)
{
    // Since only one service may be registered with a particular SSID
    // we can test for equal on only it
    return m_idSysSer != sysSer.m_idSysSer;
}

//------------------------------------------------------------------------------------------------
inline bool ServiceManager::ServiceInfo::IsType(SSID id) const
{
    if (id == m_idSysSer) return true;
    for (UInt32 i = 0; i < m_aliases.size(); ++i)
    {
        if (id == m_aliases[i]) return true;
    }
    return false;
}

//------------------------------------------------------------------------------------------------
inline void ServiceManager::ServiceInfo::ResetTiming()
{
    m_totalTimeSpent = 0.0;
    m_totalTicks = 0;
    for (unsigned int i=0; i < kTickHistorySize; ++i)
    {
        m_recentTickTimes[i] = 0.0;
    }
    m_insertPoint = kTickHistorySize-1;
}

//------------------------------------------------------------------------------------------------
inline void ServiceManager::ServiceInfo::StoreLastTickTime(efd::TimeType time)
{
    m_totalTimeSpent += time;
    ++m_totalTicks;

    ++m_insertPoint;
    if (m_insertPoint >= kTickHistorySize)
        m_insertPoint = 0;

    m_recentTickTimes[m_insertPoint] = time;
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType ServiceManager::ServiceInfo::GetLastTickTime() const
{
    return 1000.0 * m_recentTickTimes[m_insertPoint];
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType ServiceManager::ServiceInfo::ComputeLifetimeAverageSPF() const
{
    return 1000.0 * m_totalTimeSpent / m_totalTicks;
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType ServiceManager::ServiceInfo::ComputeRecentAverageSPF() const
{
    efd::TimeType recentTime = 0;
    for (unsigned int i=0; i < kTickHistorySize; ++i)
    {
        recentTime += m_recentTickTimes[i];
    }
    return 1000.0 * recentTime / kTickHistorySize;
}


//------------------------------------------------------------------------------------------------
// ServiceManager::ServiceSorter
//------------------------------------------------------------------------------------------------
inline ServiceManager::ServiceSorter::ServiceSorter(ServiceInfo* pServiceInfo)
    : m_pService(pServiceInfo)
    , m_time(pServiceInfo->ComputeLifetimeAverageSPF())
{
}

//------------------------------------------------------------------------------------------------
inline bool ServiceManager::ServiceSorter::operator<(const ServiceSorter& rhs) const
{
    return m_time < rhs.m_time;
}

//------------------------------------------------------------------------------------------------
} // end namespace efd

