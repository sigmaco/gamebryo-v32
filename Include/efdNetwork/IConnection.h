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
#ifndef EE_ICONNECTION_H
#define EE_ICONNECTION_H

#include <efd/INetCallback.h>
#include <efd/MemObject.h>
#include <efd/ConnectionID.h>
#include <efd/NetEnums.h>
#include <efd/NetMessage.h>
#include <efdNetwork/efdNetworkLibType.h>

namespace efd
{
// Forward declarations
class EnvelopeMessage;
class IConnection;

// A SmartPointer for the IConnection interface
typedef efd::SmartPointer<IConnection> IConnectionPtr;

/**
    Interface class for the network transport data.

    It is used to hold the connection data for the transports so it can be
    shared among transports as required.
*/
class EE_EFDNETWORK_ENTRY IConnection : public efd::MemObject
{
    EE_DECLARE_ABSTRACT_REFCOUNT;
public:

    /// Virtual destructor
    virtual ~IConnection();

    /// Retrieves the QualityOfService associated with this object
    virtual efd::QualityOfService GetTransportType() = 0;

    /// Retrieves the remote ConnectionID that this connection object receives messages from and
    /// sends messages to.  If this connection is a listening connection or a many to one
    /// connection (such as UDP) then GetRemoteConnectionID will return the listening ConnectionID.
    virtual ConnectionID GetRemoteConnectionID() const=0;

    /**
        Actually sends the message across the network.
        @param pMessage The envelope message to send.
        @param cid connection id to send to.
        @return : True if the message was sent.
    */
    virtual bool Send(EnvelopeMessage* pMessage, const ConnectionID& cid) = 0;

    /**
        Closes the connection associated with this object.
    */
    virtual void Close() = 0;

    /**
        Set a callback object to receive connection oriented events:
        kMSGID_ConnectionConnectedMsg
        kMSGID_ConnectionFailedToConnectMsg
        kMSGID_ConnectionDisconnectedMsg
        kMSGID_ConnectionAcceptedMsg
        kMSGID_ConnectionFailedToAcceptMsg
    */
    virtual void SetConnectionCallback(INetCallback* pConnectionCallback) = 0;

    /// Retrieve the object set to receive connection oriented events
    virtual INetCallback* GetConnectionCallback() = 0;

    /// Set a callback to receive data events:
    /// kMSGID_ConnectionDataReceivedMsg
    virtual void SetMessageCallback(INetCallback* pMessageCallback) = 0;

    /// Retrieve the object set to receive data events
    virtual INetCallback* GetMessageCallback() = 0;

    /// Remove a callback object that no longer wishes to receive events.
    /// @param pCallbackToRemove callback object to remove
    /// @param pReplacementCallback callback object to register instead, may be NULL
    virtual void RemoveCallback(
        INetCallback* pCallbackToRemove,
        INetCallback* pReplacementCallback) = 0;

    /**
        Attempt to complete a connection asynchronously.
    */
    virtual efd::SInt32 CompleteConnection() = 0;

    /**
        Factories the appropriate connection notification message based on the status of the
        connection.
    */
    virtual NetMessagePtr GetStatusMessage() = 0;

    /// Returns true if the Connection is connected and valid.
    virtual bool IsValid() = 0;

    /**
        Receive a message from the underlying network and populate pEnvelopeMessage
        with the contents of the received message.
    */
    virtual efd::SInt32 ReceiveMessage(
        EnvelopeMessagePtr& spEnvelopeMessage,
        ConnectionID& remoteConnectionID) = 0;

    /**
        Send any queued messages.
    */
    virtual efd::SInt32 SendMessages() = 0;

    /**
        Query the size of the outgoing queue in this connection.
        @return The size of the outgoing queue in this connection.
    */
    virtual efd::UInt32 QueryOutgoingQueueSize() = 0;

    /**
        Check for an incoming connection.
        @return a SmartPointer to the IConnection for the newly established connection
    */
    virtual IConnectionPtr Accept() = 0;

    /**
        returns true if this is a listening connection
    */
    virtual bool IsListening() = 0;

    /**
        returns true if this is an incoming connection
    */
    virtual bool IsIncomingConnection() = 0;

    /**
      Returns the LightSpeed-specific error code associated with the last 
      failure that occurred in this connection object. 
    
      @return efd::UInt32 The error code.
    */
    virtual efd::SInt32 GetLastError() = 0;

    /**
      Returns a string describing the last failure that occurred in this 
      Connection object. 
    
      @return efd::utf8string The description 
    */
    virtual efd::utf8string GetLastErrorString() = 0;

    /**
      Returns the last error generated in the platform-specific networking code. 
      For Berkeley sockets and related (e.g Winsock), this calls GetLastError.
      
      @return efd::UInt32 The error code.
    */
    virtual efd::UInt32 GetLastSystemError() = 0;

    /**
      Returns a string describing the last error in the platform-specific 
      networking code.  
    
      @return efd::utf8string The error description.
    */
    virtual efd::utf8string GetLastSystemErrorString() = 0;

    /**
        Used to configure this IConnection instance. A derived class can read any configuration
        information needed out of the passed in ISection. The default implementation does nothing.

        @param pSection The config section from which to read settings
    */
    virtual void Configure(ISection* pSection);

};

} // end namespace efd

#endif // EE_ICONNECTION_H

