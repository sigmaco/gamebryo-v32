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

#include "NiMetricsLayer.h"
#include <NiSystemDesc.h>

//--------------------------------------------------------------------------------------------------
// NiSystemClockTimer definition
//--------------------------------------------------------------------------------------------------
inline NiSystemClockTimer::NiSystemClockTimer() :
    m_fStart(0.0),
    m_fElapsed(0.0),
    m_bStopped(true)
{
}

//--------------------------------------------------------------------------------------------------
inline float NiSystemClockTimer::GetElapsed() const
{
    if (m_bStopped)
    {
        return m_fElapsed;
    }
    else
    {
        return CalculateElapsed();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiSystemClockTimer::Start()
{
    m_bStopped = false;
    m_fStart = NiGetCurrentTimeInSec();
}

//--------------------------------------------------------------------------------------------------
inline void NiSystemClockTimer::Stop()
{
    m_bStopped = true;
    m_fElapsed = CalculateElapsed();
}

//--------------------------------------------------------------------------------------------------
inline float NiSystemClockTimer::CalculateElapsed() const
{
    return NiGetCurrentTimeInSec() - m_fStart;
}

//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
// NiPerformanceCounterTimer definition
//--------------------------------------------------------------------------------------------------
inline NiPerformanceCounterTimer::NiPerformanceCounterTimer() :
    m_uiStart(0),
    m_fElapsed(0.0),
    m_bStopped(true)
{
}

//--------------------------------------------------------------------------------------------------
inline float NiPerformanceCounterTimer::GetElapsed() const
{
    if (m_bStopped)
    {
        return m_fElapsed;
    }
    else
    {
        return CalculateElapsed();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPerformanceCounterTimer::Start()
{
    m_bStopped = false;
    m_uiStart = NiGetPerformanceCounter();
}

//--------------------------------------------------------------------------------------------------
inline void NiPerformanceCounterTimer::Stop()
{
    m_bStopped = true;
    m_fElapsed = CalculateElapsed();
}

//--------------------------------------------------------------------------------------------------
inline float NiPerformanceCounterTimer::CalculateElapsed() const
{
    return (NiGetPerformanceCounter() - m_uiStart) /
        NiSystemDesc::GetSystemDesc().GetPerformanceCounterHz();
}

//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// NiMetricsTimer base class definition
//--------------------------------------------------------------------------------------------------
inline NiMetricsTimer::NiMetricsTimer(const char* pcName) :
    m_pcName(pcName),
    m_fElapsed(0.0f)
{
    EE_ASSERT(pcName);
}

//--------------------------------------------------------------------------------------------------
inline const char* NiMetricsTimer::GetName() const
{
    return m_pcName;
}

//--------------------------------------------------------------------------------------------------
inline float NiMetricsTimer::GetElapsed() const
{
    return m_fElapsed;
}

//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
// NiMetricsTimerTemp derived templated definition
//--------------------------------------------------------------------------------------------------
template<class T>
inline NiTMetricsTimer<T>::NiTMetricsTimer(const char* pcName) :
    NiMetricsTimer(pcName)
{

}

//--------------------------------------------------------------------------------------------------
template<class T>
inline NiTMetricsTimer<T>::~NiTMetricsTimer()
{

}

//--------------------------------------------------------------------------------------------------
template<class T>
inline void NiTMetricsTimer<T>::Start()
{
    m_kTimer.Start();
}

//--------------------------------------------------------------------------------------------------
template<class T>
inline void NiTMetricsTimer<T>::Stop()
{
    m_kTimer.Stop();
    m_fElapsed = m_kTimer.GetElapsed();
}

//--------------------------------------------------------------------------------------------------
