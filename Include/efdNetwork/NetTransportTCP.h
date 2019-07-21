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
#ifndef EE_NETTRANSPORTTCP_H
#define EE_NETTRANSPORTTCP_H

#include <efd/ISystemService.h>
#include <efd/NetMessage.h>
#include <efd/OrderedMap.h>

#include <efdNetwork/efdNetworkLibType.h>
#include <efdNetwork/INetTransport.h>
#include <efdNetwork/IConnection.h>

namespace efd
{

class EnvelopeMessage;

/**
    A Transport class for sending reliable ordered TCP messages.
 */
class EE_EFDNETWORK_ENTRY NetTransportTCP : public INetTransport
{
public:
    EE_DECLARE_CONCRETE_REFCOUNT;

public:

    /// @name Construction and Destruction
    //@{
    NetTransportTCP(MessageFactory* pMessageFactory, QualityOfService qos);
    /// Virtual destructor
    virtual ~NetTransportTCP();
    //@}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool Send(EnvelopeMessage* pMessage, ConnectionIDSet* pListenerSet);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool Send(EnvelopeMessage* pMessage, const ConnectionID& cid);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::AsyncResult OnTick();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::AsyncResult OnInit();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::AsyncResult OnShutdown();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::QualityOfService GetTransportType() { return m_qos;}

    /**
        Creates a socket and starts listening on the specified port.
        @param portListen The port to listen of incoming connections on.
        @param pCallback Callback pointer.
        @return : returns true if the connection succeeded.
    */
    virtual efd::ConnectionID Listen(efd::UInt16 portListen, INetCallback* pCallback);

    /**
        Creates a new connection outgoing connection and listens for incoming messages.

        @param strServerAddress The server address to connect to
        @param portServer The server port to connect to
        @param pCallback Callback pointer.
    */
    virtual ConnectionID Connect(
        const efd::utf8string& strServerAddress,
        efd::UInt16 portServer,
        INetCallback* pCallback);

    /**
        Sends a message to the specified port and ip address originating from an already
        established connection.  Only valid for unreliable connectionless qualities of service.
        @param sourceConnectionID The connection/socket to use to send the message
        @param pEnvelopeMessage The outgoing message
        @param strServerAddress The server address to connect to
        @param portServer The server port to connect to
    */
    virtual bool SendTo(
        const ConnectionID& sourceConnectionID,
        EnvelopeMessage* pEnvelopeMessage,
        const efd::utf8string& strServerAddress,
        efd::UInt16 portServer);

    /**
         Loops through all the available transports and pulls off any messages
         that have been received.  Calls ReceiveMessage for each message received.
    */
    virtual void ReceiveMessages();

    /**
         Sends any queued messages.
    */
    virtual void SendMessages();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::UInt32 QueryOutgoingQueueSize();

    /**
        Called when a message is received. Actually delivers the message to the NetService.
        If any packet mangling or extra enveloping needs to happen at the transport layer,
        this is the method to override.
    */
    virtual void ReceiveMessage(INetCallback* pMessageCallback, EnvelopeMessage* pEnvelopeMessage);

    /**
        Send the message using the TCP Transport.
        @param pMessage The outgoing message
    */
    virtual bool Send(EnvelopeMessage *pMessage);

    /**
        Close a connection by ConnectionID.  It actually marks the connection
        so that it will be closed later when it is safe.
        @param cid The connectionID of the connection to close.
    */
    virtual void CloseConnection(const ConnectionID& cid);

    /**
        Get transport data by connection ID
        @param cid ID of the transport data (connection) get
    */
    virtual IConnection* GetTransportData(const ConnectionID& cid);


    /**
        Set the callback to use when the transport receives a message.
    */
    virtual void SetMessageCallback(INetCallback* pMessageCallback)
    {
        m_pMessageCallback = pMessageCallback;
    }

    /**
        Remove the specified callback from all connections.
    */
    virtual void RemoveCallback(
        INetCallback* pCallbackToRemove,
        INetCallback* pReplacementCallback);

    /**
        Check for any remaining connections that need to be closed and closes them.
    */
    virtual void CloseAllConnections();

    /**
        Used to check the last result of a send was for this transport.
        It is mainly used to keep track of whether a failure notice has been
        sent to the client.

        @return True if the last send was successful.
    */
    virtual bool GetLastResult() {return m_lastResult;}

    /**
        Used to save the last result of a send for this transport.
        It is mainly used to keep track of whether a failure notice has been
        sent to the client.

        @param result True if the last send was successful.
    */
    virtual void SetLastResult(bool result) {m_lastResult = result;}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void ReportError(const ConnectionID& cid, IConnection *pConnection);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void ReportError(
        const ConnectionID& cid,
        INetCallback* pCallback,
        efd::SInt32 error,
        const utf8string& errorString);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Configure(ISection* pISection);

protected:

    /// @cond EMERGENT_INTERNAL

    /*!
    * Connections to service
    * This is the map of connection data, indexed by the process name string.
    * It holds pointers to connection data.
    */
    typedef efd::OrderedMap<ConnectionID, IConnectionPtr > ConnectionToTransportMap;

    typedef efd::list<ConnectionID> ConnectionIDList;
    typedef efd::list<IConnectionPtr> IConnectionList;
    typedef efd::set<IConnectionPtr> IConnectionSet;

    /// @endcond

protected:
    /**
        Check for any connections that have been marked to be closed and then closes them.

        @param sendNotification If true, send a connection close notification upon close.
    */
    virtual void CloseWaitingConnections(bool sendNotification = true);

    /**
        Checks to see if there is a client waiting to connect.  If there is it
        accepts and validates the connection.

        @return bool True if a new connection is established.
    */
    virtual bool AcceptClient();

    /**
        Attempts to complete all asynchronous connections initiated by
        Connect(const efd::utf8string&,efd::UInt16,INetCallback*)
    */
    void CheckPendingConnections();

    /**
        Attempts to complete an asynchronous connection initiated by
        Connect(const efd::utf8string&,efd::UInt16,INetCallback*)

        @param pConnection the connection to check the status of and complete if ready
        @return EE_SOCKET_CONNECTION_IN_PROGRESS The connection is still pening, try again later.
            EE_SOCKET_CONNECTION_FAILED: The connection failed, give up.
            EE_SOCKET_CONNECTION_COMPLETE: The connection completed successfully.
    */
    efd::SInt32 CompleteConnection(IConnection* pConnection);

    /**
        Add a socket for this transport to listen to for messages. The msg parameter is passed
        on the transport message callback if a connection is established.

        @param pConnection Pointer to the client data structure to use.

        @return bool True if successful.
    */
    virtual bool AddListener(IConnection* pConnection);

    /**
        Sends a local message to let other services know the current connection status.

        @param cid ID of the new connection that has been made.
        @param pCallback Callback pointer.
        @param pStatusMessage Message for status.
    */
    virtual void SendConnectionUpdate(
        const ConnectionID& cid,
        INetCallback* pCallback,
        NetMessage* pStatusMessage);

    /**
        Sends a local message to let other services know the connection has been closed.

        @param cid ID of the connection that closed
        @param pCallback Callback pointer.
    */
    virtual void SendConnectionClosed(const ConnectionID& cid, INetCallback* pCallback);

protected:

    /// True if the transport is not shutting down.
    /// This is being used to prevent shutdown crashes when a callback has already been deleted
    /// from the system.
    bool m_running;

    /**
        A list of ConnectionIDs that need closing.
    */
    ConnectionIDSet m_transportsToClose;

    /**
        A list of IConnectionIDs that are listening for incoming connections.
    */
    ConnectionToTransportMap m_listenList;

    /**
        A map of ConnectionID to IConnectionPtr.  Holds all currently established and verified
        connections.
    */
    ConnectionToTransportMap m_transports;

    /**
        Callback pointer that receives any incoming messages from any of our connections.
    */
    INetCallback* m_pMessageCallback;

    /**
        A list of pending connections to service and check for completion in OnTick.
    */
    ConnectionToTransportMap m_connectionsPending;

    /// The qos to report that this instance is
    QualityOfService m_qos;

    /// A factory that can be used to create messages of registered types
    MessageFactory* m_pMessageFactory;

    /// holds a map of incoming unreliable connections we are currently receiving data from
    ConnectionToTransportMap m_incomingConnections;

    /// The last send result
    bool m_lastResult;
    
    /// The maximum number of messages to receive in a single frame.
    efd::UInt32 m_maxReceiveMessages;

    /// The maximum number of bytes to receive in a single frame.
    efd::UInt32 m_maxReceiveBytes;

    /// The configuration section used to configure this NetLib instance.
    ISection* m_pISection;
};


/// A smart pointer (reference counting, self deleting pointer) for the NetTransportTCP class.
typedef efd::SmartPointer<NetTransportTCP> NetTransportTCPPtr;


} // end namespace efd

#endif // EE_NETTRANSPORTTCP_H
