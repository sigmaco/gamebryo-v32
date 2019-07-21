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
#ifndef EE_INETTRANSPORT_H
#define EE_INETTRANSPORT_H

#include <efd/ISystemService.h>
#include <efd/StdContainers.h>
#include <efd/INetListener.h>
#include <efd/NetEnums.h>

#include <efdNetwork/efdNetworkLibType.h>
#include <efdNetwork/NetCategory.h>

namespace efd
{
class EnvelopeMessage;
class IConnection;

/**
    Interface class for the network transport used by NetLib
 */
class EE_EFDNETWORK_ENTRY INetTransport : public MemObject
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_ABSTRACT_REFCOUNT;
    /// @endcond

public:

    /// Virtual destructor
    virtual ~INetTransport(){}

    /**
        Accept a message for sending to our connection.
        @param pMessage The outgoing message
        @return : True if the message was sent
    */
    virtual bool Send(EnvelopeMessage *pMessage) = 0;

    /**
        Accept a message for sending to a specific connection.

        @param pMessage The envelope message to send.
        @param cid the id of the connection to send the message on
        @return : True if the message was sent
    */
    virtual bool Send(EnvelopeMessage *pMessage, const ConnectionID& cid) = 0;

    /**
        Creates a socket and starts listening on the specified port
        @param portListen The port to listen of incoming connections on
        @param pCallback incoming connections will send notifications to this callback
        @return : returns true if the connection succeeded.
    */
    virtual efd::ConnectionID Listen(efd::UInt16 portListen, INetCallback* pCallback) = 0;

    /**
        Creates a new connection outgoing connection and listens for incoming messages.

        @param strServerAddress The server address to connect to
        @param portServer The server port to connect to
        @param pCallback data that arrives on this connection will be sent to this callback

        @return NetTransportTCPData* : The transport data for the connection
    */
    virtual ConnectionID Connect(
        const efd::utf8string& strServerAddress,
        efd::UInt16 portServer,
        INetCallback* pCallback) = 0;

    /**
         Close a connection by ID
        @param cid ConnectionID of the connection to close.
    */
    virtual void CloseConnection(const ConnectionID& cid) = 0;

    /**
         Get transport data by ID
        @param cid ConnectionID of the transport data (connection) get
    */
    virtual IConnection* GetTransportData(const ConnectionID& cid) = 0;

    /**
        Accept a message for sending to our connection.
        @param pMessage The outgoing message
        @param pListenerSet The set of listeners for this message
        @return : True if the message was sent
    */
    virtual bool Send(EnvelopeMessage *pMessage, ConnectionIDSet* pListenerSet) = 0;

    /**
        Query the total size of all outgoing queues in this transport.
        @return The total size of all outgoing queues in this transport.
    */
    virtual efd::UInt32 QueryOutgoingQueueSize() = 0;

    /**
        Returns the transport type for this transport
    */
    virtual efd::QualityOfService GetTransportType() = 0;

    virtual void SetMessageCallback(INetCallback* pMessageCallback) = 0;

    /**
        Remove the specified callback from all connections
    */
    virtual void RemoveCallback(
        INetCallback* pCallbackToRemove,
        INetCallback* pReplacementCallback) = 0;

    /**
        Closes all outstanding connections
    */
    virtual void CloseAllConnections() = 0;

    /// Called once per frame.
    virtual efd::AsyncResult OnTick() = 0;

    /// Called once before OnTick is called
    virtual efd::AsyncResult OnInit() = 0;

    /// Called once before the network shuts down.
    virtual efd::AsyncResult OnShutdown() = 0;

    /**
        Used to check the last result of a send was for this transport.
        It is mainly used to keep track of whether a failure notice has been
        sent to the client.

        @return True if the last send was successful.
    */
    virtual bool GetLastResult() = 0;

    /**
        Used to save the last result of a send for this transport.
        It is mainly used to keep track of whether a failure notice has been
        sent to the client.

        @param result True if the last send was successful.
    */
    virtual void SetLastResult(bool result) = 0;

    /**
        Called when a connection function call returns an error. Forwards the
        error information to the category kCAT_NetErrorMessage, so interested
        parties can subscribe for notifications.

        @param cid The connection ID
        @param pConnection Pointer to the connection that reported the error
    */
    virtual void ReportError(const ConnectionID& cid, IConnection *pConnection) = 0;


    /**
        An override of ReportError that takes an INetCallback for cases where the IConnection is
        invalid.

        @param cid The connection ID
        @param pCallback The callback to forward the net message to
        @param error The EE_SOCKET_ERROR value
        @param errorString String representation of the error.
    */
    virtual void ReportError(
        const ConnectionID& cid,
        INetCallback* pCallback,
        SInt32 error,
        const utf8string& errorString) = 0;

    /**
        Used to configure this INetTransport instance. A derived class can read any configuration
        information needed out of the passed in ISection.

        @param pISection The section of configuration information to use to read configuration
            information out of.
    */
    virtual void Configure(ISection* pISection) = 0;

};

/// A SmartPointer for the INetTransport interface
typedef efd::SmartPointer<INetTransport> INetTransportPtr;

} // end namespace efd

#endif // EE_INETTRANSPORT_H
