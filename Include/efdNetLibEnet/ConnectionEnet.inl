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
inline bool ConnectionEnet::IsListening()
{
    return m_isListening;
}

//------------------------------------------------------------------------------------------------
inline bool ConnectionEnet::IsIncomingConnection()
{
    return m_isIncomingConnection;
}

//------------------------------------------------------------------------------------------------
inline ConnectionEnet::MessageToSend::MessageToSend()
{
}

//------------------------------------------------------------------------------------------------
inline ConnectionEnet::MessageToSend::MessageToSend(
    EnvelopeMessage* pMessageToSend,
    const efd::SmartBuffer& buffer,
    const ConnectionID& destCid)
    : m_spMessageToSend(pMessageToSend)
    , m_bufferToSend(buffer)
    , m_destCid(destCid)
{
}

//------------------------------------------------------------------------------------------------
inline efd::SInt32 ConnectionEnet::SetLastError(efd::SInt32 errCode)
{
    m_lastErr = errCode;
    return m_lastErr;
}


//------------------------------------------------------------------------------------------------
inline efd::SInt32 ConnectionEnet::SetLastSystemError(efd::SInt32 errCode)
{
    m_lastSysErr = errCode;
    return m_lastSysErr;
}


//------------------------------------------------------------------------------------------------
inline efd::SInt32 ConnectionEnet::GetLastError()
{
    return m_lastErr;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string ConnectionEnet::GetLastErrorString()
{
    switch (m_lastErr)
    {
    case EE_SOCKET_NO_DATA:
        return "No data";

    case EE_SOCKET_ERROR_UNKNOWN:
        return "Unknown socket error";

    case EE_SOCKET_SHUTDOWN:
        return "Socket shutting down";

    case EE_SOCKET_CONNECTION_CLOSED:
        return "Connection closed";

    case EE_SOCKET_MESSAGE_QUEUED:
        return "Message queued";

    case EE_SOCKET_QUEUE_ALMOST_FULL:
        return "Queue almost full";

    case EE_SOCKET_SEND_FAILED:
        return "Send failed";

    case EE_SOCKET_MESSAGE_NOT_SENT:
        return "Message not sent";

    case EE_SOCKET_CONNECTION_IN_PROGRESS:
        return "Connection in progress";

    case EE_SOCKET_CONNECTION_COMPLETE:
        return "Connection complete";

    case EE_SOCKET_CONNECTION_FAILED:
        return "Connection failed";

    case EE_SOCKET_CONNECTION_ACCEPTED:
        return "Connection accepted";

    case EE_SOCKET_END_OF_BUFFER:
        return "End of buffer";

    case EE_SOCKET_CONNECTION_TIMED_OUT:
        return "Connection timed out";

    default:
        return "";
    }
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ConnectionEnet::GetLastSystemError()
{
    return enet_get_errno();
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string ConnectionEnet::GetLastSystemErrorString()
{
    return enet_get_errmessage();
}

//------------------------------------------------------------------------------------------------
inline void ConnectionEnet::Configure(ISection*)
{
}

} // end namespace efd
