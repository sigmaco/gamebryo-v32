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

//--------------------------------------------------------------------------------------------------
inline ISystemService::ISystemService()
    : m_pServiceManager(NULL)
    , m_defaultPriority(2000)
{
}

//--------------------------------------------------------------------------------------------------
inline ISystemService::~ISystemService()
{
}

//--------------------------------------------------------------------------------------------------
inline ServiceManager* ISystemService::GetServiceManager()
{
    return m_pServiceManager;
}

//--------------------------------------------------------------------------------------------------
inline const ServiceManager* ISystemService::GetServiceManager() const
{
    return m_pServiceManager;
}

//--------------------------------------------------------------------------------------------------
inline int ISystemService::GetDefaultPriority() const
{
    return m_defaultPriority;
}

//--------------------------------------------------------------------------------------------------
inline void ISystemService::SetServiceManager(ServiceManager* pServiceManager)
{
    // Should only be called once, you can't have the same service in multiple frameworks
    EE_ASSERT(!m_pServiceManager || !pServiceManager || (pServiceManager == m_pServiceManager));
    m_pServiceManager = pServiceManager;
}

//--------------------------------------------------------------------------------------------------
} //  End namespace efd
