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
ChannelManagerConfig::ChannelManagerConfig()
    : m_index(0)
    , m_port(0)
    , m_qualityOfService(efd::QOS_INVALID)
    , m_connectionStatus(0)
    , m_lastAttempt(0)
    , m_nextAttempt(0)
    , m_failInUse(false)
{
}

//------------------------------------------------------------------------------------------------
ChannelManagerConfig::ChannelManagerConfig(
    efd::UInt32 index,
    const efd::utf8string& hostname,
    efd::UInt16 port,
    efd::QualityOfService qualityOfService)
    : m_index(index)
    , m_hostname(hostname)
    , m_port(port)
    , m_qualityOfService(qualityOfService)
    , m_connectionStatus(0)
    , m_lastAttempt(0)
    , m_nextAttempt(0)
    , m_failInUse(false)
{
}

//------------------------------------------------------------------------------------------------
ChannelManagerConfig::ChannelManagerConfig(const ChannelManagerConfig& rhs)
    : m_index(rhs.m_index)
    , m_hostname(rhs.m_hostname)
    , m_port(rhs.m_port)
    , m_qualityOfService(rhs.m_qualityOfService)
    , m_connectionStatus(rhs.m_connectionStatus)
    , m_lastAttempt(rhs.m_lastAttempt)
    , m_nextAttempt(rhs.m_nextAttempt)
{
}

//------------------------------------------------------------------------------------------------
ChannelManagerConfig& ChannelManagerConfig::operator=(const ChannelManagerConfig& rhs)
{
    m_index = rhs.m_index;
    m_hostname = rhs.m_hostname;
    m_port = rhs.m_port;
    m_qualityOfService = rhs.m_qualityOfService;
    m_connectionStatus = rhs.m_connectionStatus;
    m_lastAttempt = rhs.m_lastAttempt;
    m_nextAttempt = rhs.m_nextAttempt;
    return *this;
}

} //namespace efd
