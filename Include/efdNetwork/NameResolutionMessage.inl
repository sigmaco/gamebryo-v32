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
inline efd::UInt32 NameResolutionMessage::GetServiceClassID() const
{
    return m_classID;
}

//------------------------------------------------------------------------------------------------
inline void NameResolutionMessage::SetServiceClassID(efd::UInt32 classID)
{
    m_classID = classID;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& NameResolutionMessage::GetName() const
{
    return m_name;
}

//------------------------------------------------------------------------------------------------
inline void NameResolutionMessage::SetName(const efd::utf8string& name)
{
    m_name = name;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& NameResolutionMessage::GetHostname() const
{
    return m_hostname;
}

//------------------------------------------------------------------------------------------------
inline void NameResolutionMessage::SetHostname(const efd::utf8string& hostname)
{
    m_hostname = hostname;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt16 NameResolutionMessage::GetPort() const
{
    return m_port;
}

//------------------------------------------------------------------------------------------------
inline void NameResolutionMessage::SetPort(efd::UInt16 port)
{
    m_port = port;
}

//------------------------------------------------------------------------------------------------
inline efd::Category NameResolutionMessage::GetResponseCategory() const
{
    return m_responseCategory;
}

//------------------------------------------------------------------------------------------------
inline void NameResolutionMessage::SetResponseCategory(efd::Category responseCategory)
{
    m_responseCategory = responseCategory;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 NameResolutionMessage::GetResponseIP() const
{
    return m_responseIP;
}

//------------------------------------------------------------------------------------------------
inline void NameResolutionMessage::SetResponseIP(efd::UInt32 ip)
{
    m_responseIP = ip;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt16 NameResolutionMessage::GetResponsePort() const
{
    return m_responsePort;
}

//------------------------------------------------------------------------------------------------
inline void NameResolutionMessage::SetResponsePort(efd::UInt16 port)
{
    m_responsePort = port;
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType NameResolutionMessage::GetTimestamp() const
{
    return m_timestamp;
}

//------------------------------------------------------------------------------------------------
inline void NameResolutionMessage::SetTimestamp(efd::TimeType timestamp)
{
    m_timestamp = timestamp;
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType NameResolutionMessage::GetRequestTimeout() const
{
    return m_request_timeout;
}

//------------------------------------------------------------------------------------------------
inline void NameResolutionMessage::SetRequestTimeout(efd::TimeType tmo)
{
    m_request_timeout = tmo;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& NameResolutionMessage::GetExtraInfo() const
{
    return m_extraInfo;
}

//------------------------------------------------------------------------------------------------
inline void NameResolutionMessage::SetExtraInfo(const efd::utf8string& extraInfo)
{
    m_extraInfo = extraInfo;
}

//------------------------------------------------------------------------------------------------
inline bool NameResolutionMessagePtrLess::operator()(
    const NameResolutionMessagePtr& a,
    const NameResolutionMessagePtr& b) const
{
    return (*a < *b);
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
