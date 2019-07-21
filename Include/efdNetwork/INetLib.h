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
#ifndef EE_INETLIB_H
#define EE_INETLIB_H

#include <efd/NetEnums.h>
#include <efd/SystemFrameworkEnums.h>
#include <efd/INetCallback.h>
#include <efd/NetMessage.h>

#include <efdNetwork/NetCategory.h>
#include <efdNetwork/efdNetworkLibType.h>
#include <efd/GenericFactory.h>


namespace efd
{
class INetLib;
/// GenericFactory used to register and create INetLib instances
typedef GenericFactory< SmartPointer<INetLib>, efd::utf8string > NetLibFactory;

/// Typedef for the factory method loaded from efdNetLib*.dll
typedef void (*RegisterNetLibType)();

/// Typedef for the shutdown method loaded from efdNetLib*.dll
typedef void (*ShutdownNetLibType)();
/**
    /brief Abstract interface class for network layer used by NetService and ChannelManagerService.

    INetLib is the low level network abstraction that allows direct connections between INetLib
    instances.  INetLib is not intended to be used directly by applications.  INetLib is the
    expected integration point for third party network integrations.

*/
class EE_EFDNETWORK_ENTRY INetLib
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_ABSTRACT_REFCOUNT

    /// @endcond

public:
    /// Constructor.
    INetLib();
    /// Virtual destructor.
    virtual ~INetLib();

    /// Set the MessageFactory to be used by this instance.
    virtual void SetMessageFactory(MessageFactory* pMessageFactory);

    /**
        Send Message to all subscribers including subscribers in the current process (anyone in
        the current process that has subscribed to a message).

        Iterate local consumer data structure and calls callback for each also sends to all remote
        consumers of that category.

        @param pMessageToSend Message to send.
        @param destCategory Category to which to send message.
        @param defaultQOS QOS to send message on if category is not associated with a QOS by
            BeginCategoryProduction.
    */
    virtual void Send(
        IMessage* pMessageToSend,
        const Category& destCategory,
        efd::QualityOfService defaultQOS = QOS_INVALID) = 0;

    /**
        Send Message to subscribers in remote processes only.

        Gets NetSet from RemoteConsumer data struct, and calls NetSet::Send() to send to a group
        of connections via NetRoute.

        @param pMessageToSend Message to send.
        @param destCategory Category to which to send message.
        @param defaultQOS QOS to send message on if category is not associated with a QOS by
            BeginCategoryProduction.
    */
    virtual void SendRemote(
        IMessage* pMessageToSend,
        const Category& destCategory,
        efd::QualityOfService defaultQOS = QOS_INVALID) = 0;

    /**
        Send Message on a specific connection identified by cid.

        Send only to the CID provided.

        @param pMessageToSend Message to send.
        @param destCategory Category to which to send message.
        @param cid Connection ID.
    */
    virtual void SendRemote(
        IMessage* pMessageToSend,
        const Category& destCategory,
        const ConnectionID& cid) = 0;

    /**
        Sends a message to the specified hostname and port originating from an already
        established connection.  Only valid for unreliable connectionless qualities of service.
        @param pMessageToSend Message to send.
        @param destCategory Category to which to send message.
        @param sourceConnectionID The connection/socket to use to send the message
        @param strServerAddress The server address to connect to
        @param portServer The server port to connect to
    */
    virtual void SendTo(
        IMessage* pMessageToSend,
        const Category& destCategory,
        const ConnectionID& sourceConnectionID,
        const efd::utf8string& strServerAddress,
        efd::UInt16 portServer) = 0;

    /**
        Forward an envelope message without looking at/inflating contents.

        Does not modify sender NetID; forwards via NetRoute.

        @param pEnvelopeMessage Message to send.
        @param defaultQOS Quality of service to send message on if category is not associated
            with a QOS by BeginCategoryProduction.
    */
    virtual void Forward(
        EnvelopeMessage* pEnvelopeMessage,
        efd::QualityOfService defaultQOS = QOS_INVALID) = 0;

    /**
        Forward an envelope message without looking at/inflating contents do not modify sender
        NetID forwards only to the CID provided.

        @param pEnvelopeMessage Message to send.
        @param cid Connection ID.
    */
    virtual void Forward(
        EnvelopeMessage* pEnvelopeMessage,
        const ConnectionID& cid) = 0;

    /**
        Send Message to all remote listeners regardless of subscription sends to all remote
        listeners via NetRoute's Sendall.

        @param pMessageToSend Message to send.
        @param destCategory Category to which to send message.
    */
    virtual void SendAllRemote(IMessage* pMessageToSend,const Category& destCategory) = 0;

    /**
        Forward an EnvelopeMessage without looking at/inflating contents to all remotely connected
        processes.

        @param pEnvelopeMessage EnvelopeMessage to Forward to remote processes
    */
    virtual void ForwardAllRemote(EnvelopeMessage* pEnvelopeMessage) = 0;

    /**
        Query the size of the outgoing message queue of the specified connection.
        @param cid The ConnectionID of the connection to query. If kCID_INVALID is specified this
            function should return the total of all outgoing queue sizes for all connections.
        @return The size of the queried outgoing queue.
    */
    virtual efd::UInt32 QueryOutgoingQueueSize(efd::ConnectionID cid = kCID_INVALID) = 0;

    /**
        Register local callback for specified category and mask.

        @param destCategory Category to which to send message.
        @param callback Local callback.
    */
    virtual void AddLocalConsumer(
        const Category& destCategory,
        INetCallback* callback) = 0;

    /**
        Unregister local callback for specific category.

        @param destCategory Category to which to send message.
        @param callback Local callback.
    */
    virtual void RemoveLocalConsumer(
        const Category& destCategory,
        INetCallback* callback) = 0;

    /**
        Unregister local callback for all categories.

        @param pCallback Local callback.
    */
    virtual void RemoveLocalConsumer(INetCallback* pCallback) = 0;

    /**
        Remove all local consumers.

        No more callbacks will fire.
    */
    virtual void RemoveAllLocalConsumers() = 0;

    /**
        Looks up Connection of specified consumerPrivateCat and adds that connection to the
        NetRoutes route for that category.

        @param destCategory Category to which to send message.
        @param consumerPrivateCat Connection ID.
    */
    virtual void AddRemoteConsumer(
        const Category& destCategory,
        const ConnectionID& consumerPrivateCat) = 0;

    /**
        Unregister remote consumer from the netroute.

        @param destCategory Category to which to send message.
        @param consumerPrivateCat Connection ID.
    */
    virtual void RemoveRemoteConsumer(
        const Category& destCategory,
        const ConnectionID& consumerPrivateCat) = 0;

    /**
        Unregister remote consumer for all categories.

        Removes that cid from the netroute.

        @param cid Connection ID.
    */
    virtual void RemoveRemoteConsumer(const ConnectionID& cid) = 0;

    /**
        Remove all remote consumers.

        No more messages will be sent out; cleans up the NetRoute.
    */
    virtual void RemoveAllRemoteConsumers() = 0;

    /**
        Tests if there are any remote consumers for the given category.

        @param destCategory Category to test.

        Returns true if at least one remote consumer for the given category is found, otherwise
        returns false.
    */
    virtual efd::Bool HasRemoteConsumers(const Category& destCategory) = 0;

    /**
        Associate a producer with a specific destination category, this allows us to call producer
        forward, which will send a message to all producers on a cat.

        @param producer Connection ID for producer.
        @param categoryProduced Category produced.
    */
    virtual void ProducerAssociate(
        const ConnectionID& producer,
        const Category& categoryProduced) = 0;

    /**
        Disassociate a producer with a specific destination category, this allows us to call
        producer forward, which will send a message to all producers on a cat.

        @param producer Connection ID for producer.
        @param categoryProduced Category produced.
    */
    virtual void ProducerDeassociate(
        const ConnectionID& producer,
        const Category& categoryProduced) = 0;

    /**
        Sends a message to the producer of the specified category.

        @param pMessageToSend Message to send.
        @param categoryProduced Category produced.
    */
    virtual void ProducerSendRemote(
        IMessage* pMessageToSend,
        const Category& categoryProduced) = 0;

    /**
        Forwards a message to the producers of the specified category.

        @param pMessageToSend Message to send.
        @param categoryProduced Category produced.
    */
    virtual void ProducerForward(
        EnvelopeMessage* pMessageToSend,
        const Category& categoryProduced) = 0;

    /**
        Registers an event handler for events globally in INetLib.

        @param eventType Event type.
        @param pCallback Local callback.
        @param cid Connection ID.
        @param consume True mirrors Emergent's implementation, where one can either register a
            local consumer, or an event handler.  If an event handler is used, the old
            implementation is to consume that event.
    */
    virtual void RegisterEventHandler(
        efd::UInt32 eventType,
        INetCallback* pCallback,
        const ConnectionID& cid,
        bool consume = true) = 0;

    /**
        Unregisters an event handler.

        @param eventType Event type.
        @param pCallback Local callback.
        @param cid Connection ID.
    */
    virtual void UnregisterEventHandler(
        efd::UInt32 eventType,
        INetCallback* pCallback,
        const ConnectionID& cid) = 0;

    /**
        Calls GenerateConnectionID with ip and port.

        Creates a Connection by calling Connection::Connect().  INetLib handles callback.  Adds
        private cat and connection to m_privCatToConn and m_privConnToCat so fast lookup can be
        done by either private category or Connection*.

        @param ipaddress IP address of the host to connect to in host byte order.
        @param port Port on remote host to which to connect in host byte order.
        @param qualityOfService Quality of service on which to send message.
        @param callback Local callback.
        @return ID of the Connection created.
    */
    virtual ConnectionID Connect(
        const efd::utf8string& ipaddress,
        efd::UInt16 port,
        efd::QualityOfService qualityOfService,
        INetCallback* callback = NULL) = 0;

    /**
        Creates a Connection and calls Connection::Listen.

        INetLib handles callback.  Adds private cat and connection to m_privCatToConn and
        m_privConnToCat so fast lookup can be done by either private category or Connection*.

        @param ipaddress IP address of the host to connect to in network byte order.
        @param port Port on remote host to which to connect in host byte order.
        @param qualityOfService Quality of service on which to send message.
        @param callback Local callback.
        @return True if listen completed successfully.
    */
    virtual efd::ConnectionID Listen(
        const efd::utf8string& ipaddress,
        efd::UInt16 port,
        efd::QualityOfService qualityOfService,
        INetCallback* callback = NULL) = 0;

    /**
        Creates a Connection and calls Connection::Listen.

        INetLib handles callback.  Adds private cat and connection to m_privCatToConn and
        m_privConnToCat so fast lookup can be done by either private category or Connection*.
        This version listens on all available interfaces (0.0.0.0).

        @param port Port on remote host to which to connect in host byte order.
        @param qualityOfService Quality of service on which to send message.
        @param callback Local callback.
        @return True if listen completed successfully.
    */
    virtual efd::ConnectionID Listen(
        efd::UInt16 port,
        efd::QualityOfService qualityOfService,
        INetCallback* callback = NULL) = 0;

    /**
        Closes the connection identified by connectionPrivateCat.

        This function will essentially delete that connection and all references to it.

        @param cid Connection ID.
    */
    virtual void CloseConnection(const ConnectionID& cid) = 0;

    /**
        Declare that the specified Category should be sent over the specified QualityOfService.
        @param destCategory Category that is being mapped.
        @param virtualQOS QualityOfService that the Category is being mapped to.
    */
    virtual void MapCategoryToQualityOfService(
        const Category& destCategory,
        QualityOfService virtualQOS) = 0;

    /**
        Declares that this INetLib will be producing the specified category.

        @param categoryToProduce Category to produce.
        @param qualityOfService Quality of service to use.
    */
    virtual void BeginCategoryProduction(
        const Category& categoryToProduce,
        efd::QualityOfService qualityOfService) = 0;

    /**
        Declares that this INetLib will no longer be producing the specified category.

        @param categoryToProduce Category to produce.
    */
    virtual void EndCategoryProduction(const Category& categoryToProduce) = 0;

    /**
        Run any per-frame or periodic processing INetLib needs, such as calling accept on pending
        incoming sockets.

        @return Asynchronous result.
    */
    virtual efd::AsyncResult Tick() = 0;

    /**
        Uses port and IP address (possibly CONNECTION_PROTOCOL as well) to generate a private
        category.

        @param qos Quality of service.
        @param ip 32-bit IP address of the remote host to which to connect.
        @param remotePort 16-bit port on remote host to which to connect.
        @param localPort 16-bit local port.
        @return Private connection ID.
    */
    inline static ConnectionID GenerateConnectionID(
        efd::QualityOfService qos,
        efd::UInt32 ip,
        efd::UInt16 remotePort,
        efd::UInt16 localPort = 0);

    /**
        Utility method to convert a 4 byte ipaddress into a string.
        @param ipAddress ip address in host order
    */
    virtual efd::utf8string IPToString(efd::UInt32 ipAddress) = 0;


    /**
        Callback that handles all incoming messages and queues them for later delivery.

        @param pIncomingMessage Incoming message.
        @param sender Sender of incoming message.
    */
    virtual void HandleNetMessage(
        const IMessage* pIncomingMessage,
        const ConnectionID& sender) = 0;

    /**
        Release resources.

        This function should be called manually before destroying the NetLIb object.
    */
    virtual void Shutdown() = 0;

    /**
        Remove all instances of a callback from all data structures.

        @param pCallback Callback function to be removed from all data structures.
    */
    virtual void RemoveCallback(INetCallback* pCallback) = 0;

    /// Close all connections.
    virtual void CloseAllConnections() = 0;

    /**
        Lookup which transport on which to send data for a specific category.

        A category can only be mapped to a single transport.

        @param destCategory Category to which to send message.
        @return Quality of service to use.
    */
    virtual efd::QualityOfService GetTransport(const Category& destCategory) = 0;

    //@{
    /// Access the network ID.
    inline void SetNetID(efd::UInt32 netID);
    inline efd::UInt32 GetNetID() const;
    //@}

    //@{
    /// Start, stop and poll the network.
    static efd::UInt32 StartNet();
    static void StopNet();
    static bool IsNetReady();
    //@}

    /// send subscribe messages for all subscribed categories to the specified connection
    virtual void SendAddLocalConsumerRequests(const ConnectionID& privateCategory) = 0;

    /**
        Tell all remote processes that a remote consumer should be subscribed to the specified
        category
    */
    virtual void SendAddLocalConsumerRequest(
        const Category& category) = 0;

    /**
        Tell remote processes specified by cid that a remote consumer should be subscribed to the
        specified category
    */
    virtual void SendAddLocalConsumerRequest(
        const Category& category,
        ConnectionID cid) = 0;

    /**
        Tell all remote processes that a remote consumer should no longer be subscribed to the
        specified category
    */
    virtual void SendRemoveLocalConsumerRequest(
        const Category& category) = 0;

    /**
        Tell remote processes specified by cid that a remote consumer should no longer be
        subscribed to the specified category
    */
    virtual void SendRemoveLocalConsumerRequest(
        const Category& category,
        ConnectionID cid) = 0;

    /**
        Declares that this INetLib will be producing the specified category.
        Sends a message notifying the Channel Manager of production.
    */
    virtual void SendBeginCategoryProduction(
        const Category& categoryToProduce,
        QualityOfService qualityOfService) = 0;

    /**
    * Declares that this INetLib will no longer be producing the specified category.
    * Sends a message notifying the Channel Manager of stopping of production.
    */
    virtual void SendEndCategoryProduction(
        const Category& categoryToProduce) = 0;

    /**
    * Send a messages to privateCategory for every category being produced
    */
    virtual void SendCategoryProductionMessages(const ConnectionID& cid) = 0;

    /**
        Return the connection private category of the ChannelManager.
    */
    virtual efd::ConnectionID GetChannelManagerConnectionID(QualityOfService qualityOfService);

    /**
    * Set the connection private category of the ChannelManager
    */
    virtual void SetChannelManagerConnectionID(const efd::ConnectionID& CMConnectionID);

    /**
        Send NetID announcement
    */
    virtual void SendNetIDAnnouncement(
        const ConnectionID& newConnectionID,
        const ConnectionID& destConnectionID);

    /**
        Used to configure this INetLib instance. A derived class can read any configuration
        information needed out of the passed in ISection.
        @param pISection The section of configuration information to use to read configuration
            information out of.
    */
    virtual void Configure(const ISection* pISection);

    /// Used to register the factory method for an INetLib
    template<typename T>
    static void RegisterNetLib(const efd::utf8string& netLibName);

    /**
        Create our INetLib object based on the string passed in

        @param netLibType The type of the net lib to be created.
        @param pMessageFactory The MessageFactory to be used by the newly created net lib instance.
        @param pSection A Pointer to the configuration section to allow NetTransport configuration.
        @return A smart pointer to the newly created net lib.
    */
    static SmartPointer<INetLib> CreateNetLib(
        const efd::utf8string& netLibType,
        MessageFactory* pMessageFactory,
        const efd::ISection* pSection);


    /// @cond EMERGENT_INTERNAL

    //@{
    static void _SDMShutdown();
    //@}

    /// @endcond

protected:
    efd::map< QualityOfService, ConnectionID > m_channelManagerQOSToIDMap;

    /// Unique identifier for this NetLib instance.
    efd::UInt32 m_netID;

    /// static used to keep track of the number of time INetLib has been initialized
    static efd::UInt32 ms_netInitCount;

    /// A factory that can be used to create messages of registered types
    MessageFactory* m_pMessageFactory;

    /// Used to register and factory INetLibs
    static NetLibFactory* ms_pNetLibFactory;
};

typedef efd::SmartPointer<INetLib> INetLibPtr;

typedef EE_STL_NAMESPACE::pair< efd::UInt32, QualityOfService > NetIDQosPair;
typedef efd::map< NetIDQosPair, efd::ConnectionID > NetIDQosPairToConnectionIDMap;

} // end namespace efd

#include <efdNetwork/INetLib.inl>

#endif //EE_INETLIB_H
