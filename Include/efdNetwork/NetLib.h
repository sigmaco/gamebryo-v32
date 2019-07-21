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
#ifndef EE_NETLIBTCP_H
#define EE_NETLIBTCP_H

#include <efd/NetMessage.h>
#include <efd/NetEnums.h>
#include <efd/MemObject.h>
#include <efd/SystemFrameworkEnums.h>
#include <efd/INetCallback.h>
#include <efd/INetListener.h>
#include <efd/StreamMessage.h>

#include <efdNetwork/INetLib.h>
#include <efdNetwork/NetCategory.h>
#include <efdNetwork/efdNetworkLibType.h>

/// @name TCP only includes.
//@{
#include <efdNetwork/INetTransport.h>
//@}

namespace efd
{
class ISection;

/**
    Simple concrete implementation of INetLib
*/
class EE_EFDNETWORK_ENTRY NetLib : public efd::MemObject, public INetCallback, public INetLib
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CONCRETE_REFCOUNT
    /// @endcond

public:
    /// Local connection address (ID).
    static const ConnectionID ms_localConnectionAddress;

    /// Constructor.
    NetLib();
    /// Virtual destructor.
    virtual ~NetLib();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Send(
        IMessage* pMessageToSend,
        const Category& destCategory,
        efd::QualityOfService defaultQOS = QOS_INVALID);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendRemote(
        IMessage* pMessageToSend,
        const Category& destCategory,
        efd::QualityOfService defaultQOS = QOS_INVALID);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendRemote(
        IMessage* pMessageToSend,
        const Category& destCategory,
        const ConnectionID& cid);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendTo(
        IMessage* pMessageToSend,
        const Category& destCategory,
        const ConnectionID& sourceConnectionID,
        const efd::utf8string& strServerAddress,
        efd::UInt16 portServer);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Forward(
        EnvelopeMessage* pEnvelopeMessage,
        efd::QualityOfService defaultQOS = QOS_INVALID);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Forward(EnvelopeMessage* pEnvelopeMessage, const ConnectionID& cid);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendAllRemote(IMessage* pMessageToSend, const Category& destCategory);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void ForwardAllRemote(EnvelopeMessage* pEnvelopeMessage);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void AddLocalConsumer(
        const Category& destCategory,
        INetCallback* callback);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveLocalConsumer(
        const Category& destCategory,
        INetCallback* callback);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveLocalConsumer(INetCallback* pCallback);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveAllLocalConsumers();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void AddRemoteConsumer(
        const Category& destCategory,
        const ConnectionID& consumerPrivateCat);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveRemoteConsumer(
        const Category& destCategory,
        const ConnectionID& consumerPrivateCat);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveRemoteConsumer(const ConnectionID& cid);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveAllRemoteConsumers();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::Bool HasRemoteConsumers(const Category& destCategory);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void ProducerAssociate(
        const ConnectionID& producer,
        const Category& categoryProduced);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void ProducerDeassociate(
        const ConnectionID& producer,
        const Category& categoryProduced);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void ProducerSendRemote(
        IMessage* pMessageToSend,
        const Category& categoryProduced);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void ProducerForward(
        EnvelopeMessage* pMessageToSend,
        const Category& categoryProduced);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RegisterEventHandler(
        efd::UInt32 eventType,
        INetCallback* pCallback,
        const ConnectionID& cid,
        bool consume = true);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void UnregisterEventHandler(
        efd::UInt32 eventType,
        INetCallback* pCallback,
        const ConnectionID& cid);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual ConnectionID Connect(
        const efd::utf8string& ipaddress,
        efd::UInt16 port,
        efd::QualityOfService qualityOfService,
        INetCallback* callback = NULL);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::ConnectionID Listen(
        const efd::utf8string& ipaddress,
        efd::UInt16 port,
        efd::QualityOfService qualityOfService,
        INetCallback* callback = NULL);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::ConnectionID Listen(
        efd::UInt16 port,
        efd::QualityOfService qualityOfService,
        INetCallback* callback = NULL);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void CloseConnection(const ConnectionID& cid);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void MapCategoryToQualityOfService(
        const Category& destCategory,
        QualityOfService virtualQOS);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void BeginCategoryProduction(
        const Category& categoryToProduce,
        efd::QualityOfService qualityOfService);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void EndCategoryProduction(const Category& categoryToProduce);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::AsyncResult Tick();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::utf8string IPToString(efd::UInt32 ipAddress);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::UInt32 QueryOutgoingQueueSize(efd::ConnectionID cid = kCID_INVALID);

    /// Transport factory
    static INetTransportPtr CreateTransport(
        MessageFactory* pMessageFactory,
        QualityOfService qualityOfService);

protected:
    /**
        Returns a list of local consumers (listeners) for the specified category.

        @param destCategory Category to which to send message.
        @return Smart pointer to a list of listeners for the specified category.
    */
    virtual INetCallbackSetPtr GetLocalConsumers(const Category& destCategory);

public:

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void HandleNetMessage(
        const IMessage* pIncomingMessage,
        const ConnectionID& sender);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Shutdown();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveCallback(INetCallback* pCallback);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void CloseAllConnections();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::QualityOfService GetTransport(const Category& destCategory);

    /// Wrapper for GetTransport that handles the case of an invalid category
    efd::QualityOfService SafeGetTransport(const Category& destCategory);

    /// Returns true is there are local listeners registered
    efd::Bool HaveLocalListeners();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendAddLocalConsumerRequests(const ConnectionID& privateCategory);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendAddLocalConsumerRequest(
        const Category& category);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendAddLocalConsumerRequest(
        const Category& category,
        ConnectionID cid);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendRemoveLocalConsumerRequest(
        const Category& category);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendRemoveLocalConsumerRequest(
        const Category& category,
        ConnectionID cid);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendBeginCategoryProduction(
        const Category& categoryToProduce,
        QualityOfService qualityOfService);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendEndCategoryProduction(const Category& categoryToProduce);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SendCategoryProductionMessages(const ConnectionID& cid);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Configure(ISection* pISection);

protected:
    /**
       Create a StreamMessage of the specified type for sending a create local consumer request
    */
    template<efd::UInt32 msgguid>
    StreamMessagePtr CreateLocalConsumerRequest(
        const Category& category);

    /**
       Create a StreamMessage of the specified type for sending a category production notification
    */
    template<efd::UInt32 msgguid>
    StreamMessagePtr CreateCategoryProductionMessage(
        const Category& category,
        QualityOfService qualityOfService);

    //------------------------------------------------------------------------
    // INetTransport related functions.

    virtual void RegisterTransport(INetTransport* pTrans, efd::QualityOfService qualityOfService);

    ///Register a transport for use by NetLib
    virtual void RegisterTransport(efd::QualityOfService qualityOfService);

    /// Unregister an existing transport (given the transport type)
    virtual void UnregisterTransport(efd::QualityOfService qualityOfService);

    /// Unregister an existing transport (given the pointer to the transport service)
    virtual void UnregisterTransport(INetTransport* pTrans);

    /// Retrieves the connection data for the specified process name
    virtual IConnection* GetTransportData(const ConnectionID& cid);

    /**
    * Checks to see if the given category (cat) matches any of the
    * subscribed remote listeners

    * Internal use for NetLib only
    */
    virtual ConnectionIDSetPtr GetRemoteConsumers(const Category& destCategory);

    // end: INetTransport related functions.
    //------------------------------------------------------------------------

    /**
    * Called from MessageReceivedCallback.  Message callbacks are not
    * triggered until DeliverQueuedMessages is called.  This makes sure
    * that all callbacks are triggered in sync with framework.
    */
    void QueueMessage(NetMessage *pMessage);

    /**
    * Delivers all queued messages.  Intended to be called from
    * NetService::OnTick or similar.
    */
    void DeliverQueuedMessages();

    /**
    * Iterates internal DataStructures to look for callback pointers still subscribed
    */
    void InternalRemoveCallback(INetCallback* pCallback);

    typedef efd::map< efd::Category, efd::INetCallbackSetPtr > CategoryToINetCallbackMap;
    CategoryToINetCallbackMap m_localListeners;

    typedef efd::RefCountedMemObj< efd::map< efd::Category, efd::ConnectionIDSetPtr > >
        CategoryToConnectionIDMap;
    typedef efd::SmartPointer< CategoryToConnectionIDMap > CategoryToConnectionIDMapPtr;
    CategoryToConnectionIDMap m_remoteListeners;

    typedef efd::RefCountedMemObj< efd::list<NetMessagePtr> > NetMessageList;
    typedef efd::SmartPointer< NetMessageList > NetMessageListPtr;
    NetMessageListPtr m_spMessageList;

    /**
    * This is the array of registered transports.  It holds the pointer to
    * the transport, indexed by the transport type.  It is used to determine
    * if a requested transport type is registered (or we generate an error),
    * and then to dispatch messages to the saved pointer.
    */
    typedef efd::map<efd::QualityOfService, INetTransportPtr> RegisteredTransportMap;
    RegisteredTransportMap m_transportMap;

    typedef efd::map<Category, efd::QualityOfService> CatToQualityOfServiceMap;
    CatToQualityOfServiceMap m_catToQualityOfServiceMap;


    typedef efd::map< Category, ConnectionIDSetPtr > ProducerMap;
    typedef efd::set< Category > CategorySet;

    /// Map of Category to connections producing that Category.
    ProducerMap m_producerMap;

    /// Set of all the Categories this NetLib instance produces.
    CategorySet m_categoryProductionSet;

    /// The previous message sent about the buffer status.
    ClassID m_bufferStatus;

    /// The configuration section used to configure this NetLib instance.
    ISection* m_pISection;
};

typedef efd::SmartPointer<NetLib> NetLibPtr;

} // end namespace efd

#endif //EE_NETLIBTCP_H
