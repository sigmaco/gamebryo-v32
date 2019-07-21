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
#ifndef EE_CONNECTIONENET_H
#define EE_CONNECTIONENET_H

#include <enet/enet.h>

#include <efdNetwork/IConnection.h>
#include <efdNetwork/SocketErrors.h>

struct _ENetHost;
struct _ENetPeer;

namespace efd
{
class EnvelopeMessage;

/**
    A wrapper for data sent via the NetTransportEnet transport.
*/
class ConnectionEnet : public IConnection
{
public:
    EE_DECLARE_CONCRETE_REFCOUNT;

    enum ConnectionState
    {
        EE_CONN_CONNECTION_FAILED = -1,
        EE_CONN_NOT_CONNECTED,
        EE_CONN_ACCEPTED,
        EE_CONN_SEND_VERSIONS,
        EE_CONN_RECEIVE_VERSIONS,
        EE_CONN_CONNECTED,
        EE_CONN_LISTENING
    };

    /// @name Construction and Destruction
    //@{
public:
    ConnectionEnet(
        MessageFactory* pMessageFactory,
        QualityOfService qos,
        _ENetHost* pENetHost,
        INetCallback* pMessageCallback,
        INetCallback* pConnectionCallback,
        bool incomingConnection,
        bool isListening);

    /// Virtual destructor
    virtual ~ConnectionEnet();
    //@}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::QualityOfService GetTransportType();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool IsValid();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SInt32 ReceiveMessage(
        EnvelopeMessagePtr& spEnvelopeMessage,
        ConnectionID& remoteConnectionID);

    /**
        Service any events on this connection
    */
    virtual efd::SInt32 ReceiveMessage(
        EnvelopeMessagePtr& spEnvelopeMessage,
        ConnectionID& senderConnectionID,
        SmartPointer<ConnectionEnet>& spNewConnection);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SInt32 SendMessages();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SInt32 CompleteConnection();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual ConnectionID GetRemoteConnectionID() const;

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool Send(EnvelopeMessage *pMessage, const ConnectionID& cid);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Close();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SetConnectionCallback(INetCallback* pConnectionCallback);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual INetCallback* GetConnectionCallback();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SetMessageCallback(INetCallback* pMessageCallback);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual INetCallback* GetMessageCallback();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveCallback(
        INetCallback* pCallbackToRemove,
        INetCallback* pReplacementCallback);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual NetMessagePtr GetStatusMessage();

    virtual efd::SInt32 ReceiveVersions(efd::EnvelopeMessage* pEnvelopeMessage);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual IConnectionPtr Accept();

    /**
        returns true if this is a listening connection
    */
    bool IsListening();

    /**
        returns true if this is an incoming connection
    */
    bool IsIncomingConnection();

    /**
        Factory a ConnectionEnet, use it to attempt to connect
        @param pMessageFactory Pointer to MessageFactory.
        @param qos Quality of Service.
        @param strServerAddress String version of server address.
        @param portServer Server port.
        @param pMessageCallback Callback object to deliver messages to.
        @param pConnectionCallback Callback object to report connection status events to.
    */
    static efd::SmartPointer< ConnectionEnet > Connect(
        MessageFactory* pMessageFactory,
        efd::QualityOfService qos,
        const efd::utf8string& strServerAddress,
        efd::UInt16 portServer,
        INetCallback* pMessageCallback,
        INetCallback* pConnectionCallback);

    /**
        Factory a ConnectionEnet, use it to attempt to listen
        @param pMessageFactory Pointer to MessageFactory.
        @param qos Quality of Service.
        @param portListen Port to listen on.
        @param pMessageCallback callback object to deliver messages to
        @param pConnectionCallback callback object to report connection status events to
    */
    static efd::SmartPointer< ConnectionEnet > Listen(
        MessageFactory* pMessageFactory,
        efd::QualityOfService qos,
        efd::UInt16 portListen,
        INetCallback* pMessageCallback,
        INetCallback* pConnectionCallback);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::UInt32 QueryOutgoingQueueSize();

    /// @ {
    /**
        These functions implement the error-handling portion of the
        IConnection interface. @see IConnection.
    */
    efd::SInt32 GetLastError();
    efd::utf8string GetLastErrorString();
    efd::UInt32 GetLastSystemError();
    efd::utf8string GetLastSystemErrorString();
    /// @ }

    efd::SInt32 SetLastError(efd::SInt32 errCode);
    efd::SInt32 SetLastSystemError(efd::SInt32 errCode);


    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Configure(ISection* pISection);

protected:

    /// The version of the ConnectionEnet. Used to ensure compatibility at the transport layer.
    const efd::UInt32 m_numVersions;
    const efd::utf8string m_pVersionName;
    const efd::utf8string m_pVersionValue;

    /**
        Receive a buffer from the network
        @param[out] buffer buffer received
    */
    virtual efd::SInt32 ReceiveStream(efd::SmartBuffer& buffer);

    /// Returns true if the version has been checked for this data.
    virtual bool VersionChecked();

    /// Validate the data contained in the given stream is compatible with this data.
    virtual bool ValidateVersions(efd::Archive& ar);

    /**
        Sends a version packet to be validated at the receiving end.
        The version packet consists of an unsigned integer that specifies the number
        of strings to follow.  After it the first utf8string for the version name and
        then the first utf8string for the version value.  All the other version string
        pairs follow in succession.
    */
    virtual efd::SInt32 SendVersions();

    /**
        Attempts to receive versions.  If a version stream has been received, it is returned in
        the spStream parameter and a positive value is returned.  If no stream has yet been
        received, returns 0.  Returns a negative value if an error occurred.
    */
    virtual efd::SInt32 ReceiveVersions();

    /// @cond EMERGENT_INTERNAL

    class MessageToSend
    {
    public:
        MessageToSend();
        MessageToSend(
            EnvelopeMessage* pMessageToSend,
            const efd::SmartBuffer& buffer,
            const ConnectionID& destCid);
        EnvelopeMessagePtr m_spMessageToSend;
        efd::SmartBuffer m_bufferToSend;
        ConnectionID m_destCid;
    };

    virtual efd::SInt32 InternalSend(MessageToSend& messageToSend);

    // Bury the assignment operator
    ConnectionEnet& operator=(const ConnectionEnet& other);

    /// True if the transport has passed its version check
    bool m_versionsValid;

    /// True if versions have been successfully sent.
    bool m_versionsSent;

    /// True if the transport has received versions from remote
    bool m_versionsReceived;

    INetCallback* m_pMessageCallback;
    INetCallback* m_pConnectionCallback;

    typedef efd::list< MessageToSend > MessageList;
    MessageList m_messageQueue;

    /// Hold versions so that we can attempt to send versions over multiple ticks.
    SmartBuffer m_sendVersionBuffer;

    /// Keep track of the state of this connection.
    ConnectionState m_connectionState;

    /// True if this connection was created by Accept
    bool m_isIncomingConnection;

    /// The quality of service to report this connection as
    efd::QualityOfService m_qos;

    /// A factory that can be used to create messages of registered types
    MessageFactory* m_pMessageFactory;

    /// the ConnectionID of the other end of the connection.
    ConnectionID m_remoteConnectionID;

    /// True if this connection is listening for incoming connections
    bool m_isListening;

    // this end of the connection
    _ENetHost* m_pENetHost;

    // the other end of the connection
    _ENetPeer* m_pENetPeer;

    /// Last reported LightSpeed error code
    efd::UInt32 m_lastErr;

    /// Description for last reported error
    efd::utf8string m_lastErrString;

    /// Last reported enet error code
    efd::UInt32 m_lastSysErr;

    /// Description for last reported system error
    efd::utf8string m_lastSysErrString;

    /// @endcond
};

/// A smart pointer (reference counting, self deleting pointer) for the ConnectionEnet class.
typedef efd::SmartPointer<ConnectionEnet> ConnectionEnetPtr;

} // end namespace efd

#include <efdNetLibEnet/ConnectionEnet.inl>

#endif //EE_CONNECTIONENET_H
