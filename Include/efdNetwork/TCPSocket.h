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

#pragma once
#ifndef EE_TCPSOCKET_H
#define EE_TCPSOCKET_H

/** @file TCPSocket.h
    Platform neutral wrapper for a bsd TCP socket. Internal use only.
*/
#include <efd/OS.h>
#include <efd/UniversalTypes.h>
#include <efd/INetCallback.h>

#include <efdNetwork/Net.h>
#include <efdNetwork/SocketErrors.h>
#include <efdNetwork/Socket.h>

#include <efd/utf8string.h>
#include <efd/SmartPointer.h>
#include <efd/Serialize.h>
#include <efd/ConnectionID.h>
#include <efdNetwork/INetLib.h>
#include <efdNetwork/efdNetworkLibType.h>

namespace efd
{

/**
    An implementation of Socket that uses TCP as the transport mechanism.
 */
class EE_EFDNETWORK_ENTRY TCPSocket : public Socket
{
    EE_DECLARE_CONCRETE_REFCOUNT;
public:

    /**
       Constructor. used for creating instances dedicated to client
       communication.
       @param qos Quality of service.
       @param socketId socket id of the socket created by call to accept
       @param localAddr sockaddr_in for the local end of the socket
       @param remoteAddr sockaddr_in for the remote end of the socket
       @param pCallback Callback pointer.
    */
    TCPSocket(
        efd::QualityOfService qos,
        SOCKET socketId,
        struct sockaddr_in& localAddr,
        struct sockaddr_in& remoteAddr,
        INetCallback* pCallback);

    /**
       Used to create a new TCP socket given a local port to listen to.
    */
    TCPSocket(efd::QualityOfService qos, efd::UInt16 listenPort, INetCallback* pCallback);

    virtual ~TCPSocket();

    /**
        Sends a message to a connected host.
        @param buffer Message to send
        @return Number of bytes sent or error
    */
    efd::SInt32 Send(const efd::SmartBuffer& buffer);

#if defined(EE_PLATFORM_WIN32)

    /**
        Sends a raw buffer to a connected host.
        @param pData Data to send
        @param size Size of the data to send
        @return Number of bytes sent or error
    */
    efd::SInt32 Send(const efd::Char* pData, efd::SInt32 size);

    /**
        Sends a message to a datagram socket.
        @param pData Data to send
        @param size Size of the data to send
        @param serverNameOrAddr Hostname or ip address of peer to send to
        @param portServer Port to send to
        @return Number of bytes sent or error
    */
    efd::SInt32 SendTo(
        const efd::Char* pData,
        efd::SInt32 size,
        const efd::utf8string& serverNameOrAddr,
        efd::UInt16 portServer);

    /**
        Receive data and store in the supplied buffer.

        @param pData The buffer to receive data into
        @param size The size of the buffer

        @return The number of bytes received, 0 if no data available
        on a non blocking call, -1 if a socket error occurred
    */
    efd::SInt32 Receive(efd::Char* pData, efd::SInt32 size);

    /**
        Receive a message from a datagram socket
        @param pData The buffer to fill in with the received data
        @param size The size of the buffer
        @param hostOrderIPAddr hostname or ip address remote sender
        @param hostOrderRemotePort port of remote sender

        @return int : The number of bytes in the stream, 0 if no data available
        on a non blocking call, -1 if a socket error occurred
    */
    efd::SInt32 ReceiveFrom(
        efd::Char* pData,
        efd::SInt32 size,
        efd::UInt32& hostOrderIPAddr,
        efd::UInt16& hostOrderRemotePort);

#endif // defined(EE_PLATFORM_WIN32)

    /**
        Sends a message to a datagram socket.
        @param buff message to send
        @param destinationConnectionID Destination connection ID.
        @return: number of bytes sent or error
    */
    efd::SInt32 SendTo(const efd::SmartBuffer& buff, efd::ConnectionID destinationConnectionID);

    /**
        receive messages and stores the message in a buffer.

       @param o_buff The buffer to fill in with the received data

       @return int The number of bytes in the stream, 0 if no data available
                on a non blocking call, -1 if a socket error occurred
    */
    efd::SInt32 Receive(efd::SmartBuffer& o_buff);

    /**
        Receive a message from a datagram socket
        @param o_buff The buffer to fill in with the received data
        @param senderConnectionID The ConnectionID of the sender of the data

        @return int The number of bytes in the stream, 0 if no data available
        on a non blocking call, -1 if a socket error occurred
    */
    efd::SInt32 ReceiveFrom(efd::SmartBuffer& o_buff, efd::ConnectionID& senderConnectionID);

    /**
       Binds the socket to an address and port number
       a server call.  Returns true if the bind succeeded, false if it failed.
    */
    bool Bind();

    /**
        Listens to connecting clients, a server call
        @param backlog Maximum length of the queue of pending connections
    */
    void Listen(efd::UInt32 backlog = 5);

    /**
        Connect to a listening server
        @param serverNameOrAddr hostname or ip address of server to connect to
        @param portServer port to connect to
    */
    efd::SInt32 Connect(const efd::utf8string& serverNameOrAddr, efd::UInt16 portServer);

    /**
        Begin shutting down the socket endpoint
    */
    void Shutdown();

    /**
        Create a new TCPSocket instance
        @param newSocket Native socket descriptor for new instance
        @param clientAddress Address of remote endpoint
    */
    Socket* CreateSocket(SOCKET newSocket, struct sockaddr_in clientAddress);

private:

    /**
        For connection-oriented sockets this value contains the return value of the most
        recent connect() call.
    */
    efd::SInt32 m_lastConnectResult;

};
typedef efd::SmartPointer<TCPSocket> TCPSocketPtr;

} // end namespace efd

#endif // EE_TCPSOCKET_H

