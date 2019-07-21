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
inline ConnectionID::ConnectionID()
    : m_id(0ull)
    , m_qos(efd::QOS_INVALID)
{}

//------------------------------------------------------------------------------------------------
inline ConnectionID::ConnectionID(efd::QualityOfService i_qos,
    efd::UInt64 i_id)
    : m_id(i_id)
    , m_qos(i_qos)
{}

//------------------------------------------------------------------------------------------------
inline ConnectionID::ConnectionID(efd::QualityOfService i_qos,
    efd::UInt32 i_ip,
    efd::UInt16 i_localPort,
    efd::UInt16 i_remotePort)
    : m_qos(i_qos)
{
    m_ipInfo.ip = i_ip;
    m_ipInfo.localPort = i_localPort;
    m_ipInfo.remotePort = i_remotePort;
}

//------------------------------------------------------------------------------------------------
inline bool ConnectionID::operator==(const ConnectionID& rhs) const
{
    return m_id == rhs.m_id && m_qos == rhs.m_qos;
}

//------------------------------------------------------------------------------------------------
inline bool ConnectionID::operator!=(const ConnectionID& rhs) const
{
    return m_id != rhs.m_id || m_qos != rhs.m_qos;
}

//------------------------------------------------------------------------------------------------
inline bool ConnectionID::operator>(const ConnectionID& rhs) const
{
    return (m_id > rhs.m_id) || (m_id == rhs.m_id && m_qos > rhs.m_qos);
}

//------------------------------------------------------------------------------------------------
inline bool ConnectionID::operator<(const ConnectionID& rhs) const
{
    return m_id < rhs.m_id || (m_id == rhs.m_id && m_qos < rhs.m_qos);
}

//------------------------------------------------------------------------------------------------
inline bool ConnectionID::IsValid() const
{
    return m_id != 0ULL;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt64 ConnectionID::GetValue() const
{
    return m_id;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ConnectionID::GetIP() const
{
    return m_ipInfo.ip;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt16 ConnectionID::GetLocalPort() const
{
    return m_ipInfo.localPort;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt16 ConnectionID::GetRemotePort() const
{
    return m_ipInfo.remotePort;
}

//------------------------------------------------------------------------------------------------
inline efd::QualityOfService ConnectionID::GetQualityOfService() const
{
    return m_qos;
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
