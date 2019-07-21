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
//-------------------------------------------------------------------------------------------------
inline SmartCriticalSection::SmartCriticalSection(CriticalSection& criticalSection)
    : m_criticalSection(criticalSection)
{
}
//-------------------------------------------------------------------------------------------------
inline SmartCriticalSection::~SmartCriticalSection()
{
    Unlock();
}
//-------------------------------------------------------------------------------------------------
inline void SmartCriticalSection::Lock()
{
    m_criticalSection.Lock();
}
//-------------------------------------------------------------------------------------------------
inline void SmartCriticalSection::Unlock()
{
    if (GetCurrentLockCount() &&
        GetOwningThreadID() == GetCurrentThreadId())
    {
        m_criticalSection.Unlock();
    }
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 SmartCriticalSection::GetOwningThreadID() const
{
    return m_criticalSection.GetOwningThreadID();
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 SmartCriticalSection::GetCurrentLockCount() const
{
    return m_criticalSection.GetCurrentLockCount();
}
inline SmartCriticalSection::SmartCriticalSection(const SmartCriticalSection& other)
    : m_criticalSection(other.m_criticalSection)
{
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

}; // namespace efd
