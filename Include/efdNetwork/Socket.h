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
#ifndef EE_SOCKET_H
#define EE_SOCKET_H

/** @file Socket.h
Platform neutral wrapper for a socket. Internal use only.
*/

#include <efd/INetCallback.h>

#include <efdNetwork/Net.h>
#include <efdNetwork/SocketErrors.h>

#include <efd/utf8string.h>
#include <efd/SmartPointer.h>
#include <efd/Serialize.h>
#include <efdNetwork/efdNetworkLibType.h>
#include <efdNetwork/INetLib.h>
#include <efd/Metrics.h>


namespace efd
{

// so far we only consider the TCP socket, UDP will be added in later release
//const int MAX_RECV_LEN = 1048576;
const int MAX_RECV_LEN = 8096;
const int MAX_MSG_LEN = 1024;

#if defined(EE_PLATFORM_PS3)
#define MAX_DATAGRAM_SIZE 9216
#elif defined(EE_PLATFORM_XBOX360)
#define MAX_DATAGRAM_SIZE 1264
#elif defined(EE_PLATFORM_WIN32)
#define MAX_DATAGRAM_SIZE 1500
#endif

#define MAX_STREAM_SIZE 1500

/**
Abstract representation of a socket connection.
*/
class EE_EFDNETWORK_ENTRY Socket : public efd::MemObject
{
    EE_DECLARE_ABSTRACT_REFCOUNT;
public:

    /// @name Construction and Destruction
    //@{

    /// given a port number, create a socket.
    Socket(efd::UInt16 listenPort, QualityOfService qos, INetCallback* pCallback);

    /**
    Constructor. used for creating instances dedicated to client communication.
    @param socketId socket id of the socket created by call to accept
    @param localAddr sockaddr_in for the local end of the socket
    @param remoteAddr sockaddr_in for the remote end of the socket
    @param qos Quality of service.
    @param pCallback Callback to use to response to caller.
    */
    Socket(
        SOCKET socketId,
        struct sockaddr_in& localAddr,
        struct sockaddr_in& remoteAddr,
        QualityOfService qos,
        INetCallback* pCallback);

    virtual ~Socket();

    //@}

    /**
        Sends a message to a connected host.
        @param buffer message to send
        @return: number of bytes sent or error
    */
    virtual efd::SInt32 Send(const efd::SmartBuffer& buffer) = 0;

    /**
        Sends a message to a datagram socket.
        @param buffer message to send
        @param destinationConnectionID Destination connection ID.
        @return: number of bytes sent or error
    */
    virtual efd::SInt32 SendTo(
        const efd::SmartBuffer& buffer,
        efd::ConnectionID destinationConnectionID) = 0;

    /**
        receive messages and stores the message in a buffer.

        @param o_buffer The buffer to fill in with the received data

        @return int The number of bytes in the stream, 0 if no data available
            on a non blocking call, -1 if a socket error occurred
    */
    virtual efd::SInt32 Receive(efd::SmartBuffer& o_buffer) = 0;

    /**
        Receive a message from a datagram socket

        @param o_buffer The buffer to fill in with the received data
        @param senderConnectionID The ConnectionID of the sender of the data

        @return int The number of bytes in the stream, 0 if no data available
        on a non blocking call, -1 if a socket error occurred
    */
    virtual efd::SInt32 ReceiveFrom(
        efd::SmartBuffer& o_buffer,
        efd::ConnectionID& senderConnectionID) = 0;

    /**
        Binds the socket to an address and port number
        a server call.  Returns true if the bind succeeded, false if it failed.
    */
    virtual bool Bind();

    /**
        Accepts a connecting client.  The address of the connected client is stored in the
        returned Socket. Call this on the server side of the connection.
    */
    virtual Socket* Accept();

    /// Listens to connecting clients, a server call
    virtual void Listen(efd::UInt32 numPorts = 5);

    /**
        Connect to a listening server
        @param serverNameOrAddr hostname or ip address of server to connect to
        @param portServer port to connect to
    */
    virtual efd::SInt32 Connect(const efd::utf8string& serverNameOrAddr, efd::UInt16 portServer) = 0;

    virtual void Shutdown();

    /// Returns true if there is a message in the process of being sent.
    virtual bool SendPending();

    virtual Socket* CreateSocket(SOCKET newSocket, struct sockaddr_in clientAddress) = 0;

public:

    /// @name Socket options: 1=On, 0=Off
    //@{
    inline void setDebug(int);
    void setReuseAddr(int);
    virtual void setKeepAlive(int);
    void setLingerOnOff(bool);
    void setLingerSeconds(int);
    void setSocketBlocking(bool);
    void setSocketBroadcast(int);
    void setSocketNoDelay(int);
    //@}

    /// @name Set the size of the send and receive buffers.
    //@{
    void setSendBufSize(int);
    void setReceiveBufSize(int);
    //@}

    /// @name Get socket options settings. 1=On, 0=Off.
    //@{
    inline int getDebug();
    int getReuseAddr();
    virtual int getKeepAlive();
    int getSendBufSize();
    int getReceiveBufSize();
    bool getSocketBlocking() { return m_blocking; }
    int getLingerSeconds();
    bool getLingerOnOff();
    //@}

    /// Get the current socket identifier.
    SOCKET getSocketId() { return m_socketId; }

    /// Get the port of the local side of the socket connection.
    virtual unsigned short getLocalPort();

    /// Get the ip of the local side of the socket connection.
    virtual unsigned int getLocalIP();

    /// Get the port of the remote side of the socket connection.
    virtual unsigned short getRemotePort();

    /// Get the ip of the remote side of the socket connection.
    virtual unsigned int getRemoteIP();

    /// @name INetCallback methods
    //@{

    /// Set the INetCallback method to call when data is received in this socket.
    virtual void SetCallback(INetCallback* pCallback) { m_pCallback = pCallback; };

    /// Get the currently registered INetCallback instance.
    virtual INetCallback* GetCallback() { return m_pCallback; };
    //@}

    /// Get the unique connection ID for this TCP Socket.
    ConnectionID GetConnectionID()
    {
        return INetLib::GenerateConnectionID(
            m_qos,
            getRemoteIP(),
            getRemotePort(),
            getLocalPort());
    }

    inline efd::UInt32 getError();
    inline efd::utf8string getErrorMessage();
    inline efd::utf8string getErrorMessage(efd::UInt32 errorNum);

protected:

    /// default constructor
    Socket();

    SOCKET m_socketId;          // Socket file descriptor
    bool m_blocking;        // Blocking flag
    struct sockaddr_in m_localAddr;     // local Address/port
    struct sockaddr_in m_remoteAddr;    // Address of the remote side of the connection
    QualityOfService m_qos; // Used to determine the type of socket created, TCP, UDP, etc

    INetCallback* m_pCallback;
    efd::SInt32 m_SendOffset;
    efd::SInt32 m_ReceiveOffset;
    efd::SInt32 m_ReceiveSize;
    efd::SmartBuffer m_receiveBuffer;
    efd::UInt8* m_pSendBuffer;
    efd::UInt8* m_pReceiveBuffer;

};
typedef efd::SmartPointer<Socket> SocketPtr;

} // end namespace efd


#if defined(EE_PLATFORM_WIN32)
#include <efdNetwork/Win32/Socket_Win32.h>
#elif defined(EE_PLATFORM_LINUX)

#elif defined(EE_PLATFORM_XBOX360)
#include <efdNetwork/Xbox360/Socket_Xbox360.h>
#elif defined(EE_PLATFORM_PS3)
#include <efdNetwork/PS3/Socket_PS3.h>
#else
#error Unknown platform
#endif

#endif // EE_SOCKET_H
