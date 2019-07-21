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
inline NetworkStatus::NetworkStatus()
    : m_cid(QOS_LOCAL,0,0,0)
    , m_netId(kNetID_Unassigned)
{
}

//--------------------------------------------------------------------------------------------------
inline void NetworkStatus::Set(
    const efd::ConnectionID& cid,
    const efd::UInt32 netId)
{
    m_cid = cid;
    m_netId = netId;
}
inline void NetworkStatus::Set(
    const efd::QualityOfService qos,
    const efd::UInt32 netId)
{
    m_qos = qos;
    m_netId = netId;
}

//--------------------------------------------------------------------------------------------------
inline efd::QualityOfService NetworkStatus::GetQOS() const
{
    return m_qos;
}

//--------------------------------------------------------------------------------------------------
inline efd::ConnectionID NetworkStatus::GetConnectionID() const
{
    return m_cid;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 NetworkStatus::GetNetID() const
{
    return m_netId;
}

} //end namespace efd

