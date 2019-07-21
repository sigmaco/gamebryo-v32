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
inline void NetMessage::SetSenderConnection(const ConnectionID& cid)
{
    EE_ASSERT(cid.m_qos != QOS_INVALID);
    m_senderConnection = cid;
}

//--------------------------------------------------------------------------------------------------
inline const ConnectionID& NetMessage::GetSenderConnection() const
{
    return m_senderConnection;
}

//--------------------------------------------------------------------------------------------------
inline void NetMessage::SetSenderNetID(efd::UInt32 senderNetID)
{
    m_senderNetID = senderNetID;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 NetMessage::GetSenderNetID() const
{
    return m_senderNetID;
}

//--------------------------------------------------------------------------------------------------
inline void EnvelopeMessage::SetChild(IMessage *pMessage)
{
    m_spMessage = pMessage;
    m_contentsClassID = pMessage->GetClassID();
    m_childIdentity = pMessage->GetUniqueIdentifier();
    SetDebugFlags(GetDebugFlags() | pMessage->GetDebugFlags());
}

//--------------------------------------------------------------------------------------------------
inline bool EnvelopeMessage::IsInflated() const
{
    return (m_spMessage == NULL);
}

//--------------------------------------------------------------------------------------------------
inline void EnvelopeMessage::SetContentsType(efd::ClassID type)
{
    m_contentsClassID = type;
}

//--------------------------------------------------------------------------------------------------
inline efd::QualityOfService EnvelopeMessage::GetQualityOfService() const
{
    return m_qos;
}

//--------------------------------------------------------------------------------------------------
inline void EnvelopeMessage::SetQualityOfService(efd::QualityOfService qos)
{
    m_qos = qos;
}

//--------------------------------------------------------------------------------------------------
inline void RequestNetIDMessage::SetPrivateResponseChannel(
    efd::Category privateResponseChannel)
{
    m_privateResponseChannel = privateResponseChannel;
}

//--------------------------------------------------------------------------------------------------
inline efd::Category RequestNetIDMessage::GetPrivateResponseChannel() const
{
    return m_privateResponseChannel;
}

//--------------------------------------------------------------------------------------------------
inline void AssignNetIDMessage::SetAssignedNetID(efd::UInt32 assignedNetID)
{
    m_assignedNetID = assignedNetID;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 AssignNetIDMessage::GetAssignedNetID() const
{
    return m_assignedNetID;
}

//--------------------------------------------------------------------------------------------------
inline void AnnounceNetIDMessage::SetAnnouncedConnectionID(
    efd::ConnectionID announcedConnectionID)
{
    m_announcedConnectionID = announcedConnectionID;
}

//--------------------------------------------------------------------------------------------------
inline efd::ConnectionID AnnounceNetIDMessage::GetAnnouncedConnectionID() const
{
    return m_announcedConnectionID;
}

} // end namespace efd

