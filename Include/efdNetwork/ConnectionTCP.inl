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
inline ConnectionTCP::MessageToSend::MessageToSend()
{
}

//--------------------------------------------------------------------------------------------------
inline ConnectionTCP::MessageToSend::MessageToSend(
    EnvelopeMessage* pMessageToSend,
    const SmartBuffer& dataToSend,
    const ConnectionID& destCid)
    : m_spMessageToSend(pMessageToSend)
    , m_dataToSend(dataToSend)
    , m_destCid(destCid)
{
}

//--------------------------------------------------------------------------------------------------
inline void ConnectionTCP::SetConnectionCallback(INetCallback* pConnectionCallback)
{
    m_pConnectionCallback = pConnectionCallback;
    m_spSocket->SetCallback(pConnectionCallback);
}

//--------------------------------------------------------------------------------------------------
inline INetCallback* ConnectionTCP::GetConnectionCallback()
{
    return m_pConnectionCallback;
}

//--------------------------------------------------------------------------------------------------
inline void ConnectionTCP::SetMessageCallback(INetCallback* pMessageCallback)
{
    m_pMessageCallback = pMessageCallback;
}

//--------------------------------------------------------------------------------------------------
inline INetCallback* ConnectionTCP::GetMessageCallback()
{
    return m_pMessageCallback;
}

//-------------------------------------------------------------------------------------------------
inline efd::SInt32 ConnectionTCP::SetLastError(efd::SInt32 errCode)
{
    m_lastErr = errCode;
    return m_lastErr;
}

//-------------------------------------------------------------------------------------------------
inline efd::SInt32 ConnectionTCP::GetLastError()
{
    return m_lastErr;
}

//-------------------------------------------------------------------------------------------------
inline efd::utf8string ConnectionTCP::GetLastErrorString()
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

        case EE_SOCKET_CONNECTION_NOT_FOUND:
            return "Connection not found";

        default:
            return "";
    }
}

//-------------------------------------------------------------------------------------------------
inline efd::UInt32 ConnectionTCP::GetLastSystemError()
{
    return m_spSocket->getError();
}

//-------------------------------------------------------------------------------------------------
inline efd::utf8string ConnectionTCP::GetLastSystemErrorString()
{
    return m_spSocket->getErrorMessage();
}

} //End namespace efd
