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
#ifndef EE_NETSERVICE_H
#define EE_NETSERVICE_H

#include <efd/IBase.h>
#include <efd/ISystemService.h>
#include <efd/MessageService.h>
#include <efd/CriticalSection.h>
#include <efd/INetListener.h>
#include <efd/StreamMessage.h>
#include <efd/INetCallback.h>
#include <efd/NetMessage.h>
#include <efd/INetService.h>

#include <efdNetwork/efdNetworkLibType.h>
#include <efdNetwork/INetLib.h>
#include <efdNetwork/NetCategory.h>
#include <efdNetwork/ChannelManagerConfig.h>
#include <efd/GenericFactory.h>

namespace efd
{
class EnvelopeMessage;
class INetTransport;
class ChannelManagerService;

/**
    \brief NetService connects to a ChannelManagerService.

    The NetService is the service that connects to and communicates with the
    ChannelManagerService. Each client process must have a NetService. When a process wants to
    express interest in aCategory it tells NetService to Subscribe to that Category. NetService
    notifies the ChannelManagerService it is connected to that it is interested in the Category.
    From then on whenever a message is sent from a NetService on that Category the
    ChannelManagerService routes the message to any process that has expressed interest.
*/
class EE_EFDNETWORK_ENTRY NetService
    : public INetService
    , public efd::INetCallback
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(NetService, efd::kCLASSID_NetService, INetService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond


    /// @name Construction and Destruction
    //@{
protected:
    /// Virtual destructor.
    virtual ~NetService();

public:
    /// Default constructor.
    NetService(efd::utf8string netLibType = "");
    /// Constructor that takes a pre-constructed NetLib
    NetService(INetLib* pNetLib);
    //@}

    /**
        Subscribe tells NetService that the INetCallback specified by
        pCallback is interested in receiving messages on the Category cat.
        Messages delivered to this Category will be delivered to the INetCallback specified.
        @param cat Category to subscribe to
        @param pCallback pointer to callback class to handle messages
    */
    virtual void Subscribe(const Category& cat, INetCallback* pCallback);


    /**
        Unsubscribe tells NetService that the INetCallback specified by pCallback is no longer
        interested in receiving messages on the Category cat. Messages delivered to the Category
        specified will no longer be  delivered to the INetCallback specified.

        @param cat Category to subscribe to
        @param pCallback pointer to callback class to handle messages
    */
    virtual void Unsubscribe(const Category& cat, INetCallback* pCallback);

    /**
        Unsubscribe the specified callback from all Categories.
        Used in cases where the callback object pCallback is going to be deleted, or is otherwise
        no longer interested in receiving any more callbacks

        @param pCallback pointer to callback object to Unsubscribe
    */
    virtual void Unsubscribe(INetCallback* pCallback);

    /**
        Send an IMessage to every process except this one (Send to every remote process)

        @param pMessage Pointer to message for delivery
        @param cat Category to send with
        @param defaultQOS quality of service to send message on
    */
    virtual void SendRemote(
        IMessage* pMessage,
        const Category &cat,
        efd::QualityOfService defaultQOS = QOS_INVALID);

    /**
        Send an IMessage the remote process specified by cid.
        @note: This function ignores subscription data and sends directly to the connection.

        @param pMessage Pointer to message for delivery
        @param cat Category to send with
        @param cid the ConnectionID to send message to
    */
    virtual void SendRemote(IMessage* pMessage, const Category &cat, const ConnectionID& cid);

    /**
        Send a message to producers of specified category

        @param pMessage Pointer to message for delivery
        @param categoryProduced send message to anyone who produces this category
        @param defaultQOS Quality of service.
    */
    virtual void ProducerSendRemote(
        IMessage* pMessage,
        const Category& categoryProduced,
        QualityOfService defaultQOS = QOS_INVALID);

    /// @name Accessors for NetID
    //@{
    virtual efd::UInt32 GetNetID() const;
    virtual void SetNetID(efd::UInt32 netID);
    //@}

    /**
        BeginCategoryProduction assigns a quality of service to a category
        and notifies the CategoryManager of the intention of this NetService to
        produce messages destined for the specified category
        @param cat The category specified "match" category
        @param qualityOfService Quality of service for this category
        @param pCallback the callback that will receive producer messages for this category
    */
    virtual bool BeginCategoryProduction(
        const Category& cat,
        QualityOfService qualityOfService,
        INetCallback* pCallback);

    /**
        EndCategoryProduction notifies the CategoryManager of the intention of
        this NetService to no longer produce messages destined for the specified
        category
        @param cat The category specified "match" category
        @param pCallback the callback that will no longer receive producer messages for this
            category
    */
    virtual bool EndCategoryProduction(const Category& cat, INetCallback* pCallback);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void HandleNetMessage(
        const IMessage* pIncomingMessage,
        const ConnectionID& senderConnectionID);

    /// Return the connection private category of the ChannelManager
    virtual efd::ConnectionID GetChannelManagerConnectionID(QualityOfService qualityOfService);

    /// Return the NetID of the ChannelManager we are connected to
    virtual efd::UInt32 GetChannelManagerNetID();

    /**
        Sets the desired ip and port of the ChannelManager based on whatever default settings
        are specified in the Config.ini.

        @note Applications with ProgramType ProgType_Server will automatically connect to the
        ChannelManager using this method, so they should not need to call this.
    */
    virtual void ConnectToDefaultChannelManager();

    /**
        Sets the desired ip and port of the ChannelManager

        @note: Applications with ProgramType ProgType_Server will automatically connect to the
        ChannelManager using ConnectToDefaultChannelManager, so they should not need to call this.
    */
    virtual efd::ConnectionID ConnectToChannelManager(
        QualityOfService qualityOfService,
        const efd::utf8string& cmIPAddress,
        efd::UInt16 cmPort);

    /// Tell NetService to disconnect from the ChannelManager it is currently connected to.
    virtual void DisconnectFromChannelManager();

    /**
        Tell the NetService whether or not to automatically reconnect when the channel manager
        connection is unexpectedly dropped. The default is to auto-reconnect to ChannelManager.

        @param autoReconnect true if auto reconnection is desired
    */
    virtual void AutoReconnectToChannelManager(bool autoReconnect);

    /**
        Tell NetService to auto-connect or not. Default is to not auto-connect
        to ChannelManager
        @param autoConnect true if auto-connection is desired
    */
    virtual void AutoConnectToChannelManager(bool autoConnect);

    /**
        Tell NetService to assign client NetID until connected or not.
        Default is to assign the client NetID.
        Note: the client NetID will only be assigned until a connection to a ChannelManager is
        established. You can subscribe to the AssignNetIDMessage message on Category
        MessageService::GetServicePublicCategory(INetService::CLASS_ID) if you want to be notified
        when the NetID changes.

        @param assignClientNetID true if assignment of client NetID is desired
    */
    virtual void AssignClientNetID(bool assignClientNetID);

    /// Accessor for contained INetLib*
    virtual INetLib* GetNetLib();

    /**
        Used to send Connection and Disconnection notifications.
        @param pMessageService pointer to the MessageService instance to use to send the update
        @param cid ConnectionID of the connection that has just connected or disconnected
        @param netID Network ID.
    */
    template< efd::UInt32 MessageID >
    static void SendConnectionUpdate(
        efd::MessageService* pMessageService,
        const ConnectionID& cid,
        UInt32 netID);

    /**
        Resends all subscription messages to specified connection
        @param cid id of the connection to send subscription messages to
    */
    virtual void Resubscribe(const ConnectionID& cid);

    /// Return internal ConnectionStatus
    virtual ConnectionStatus GetConnectionStatus();

    /// Set the MessageService this NetService will use.  Will no longer be necessary once full
    /// virtual processes are implemented
    virtual void SetMessageService(MessageService* pMessageService);

    /**
        Create our INetLib object based on the string passed in
    */
    virtual void CreateNetLib(efd::utf8string netLibType);

    /**
        Set the pointer to the ChannelManager in this process
    */
    virtual void SetChannelManager(ChannelManagerService* pChannelManagerService);

    /**
        Make sure the specified Category is associated with the specified QualityOfService
    */
    virtual void CheckPendingSubscriptions(Category catIDToCheck, QualityOfService qos);

    /// @name Config strings used by this service
    //@{
    const static char* kConfigSection;
    const static char* kNetLibType;
    const static char* kNetLib;
    const static char* kWaitBeforeReconnect;
    const static char* kAutoConnect;
    const static char* kAutoReconnect;
    const static char* kAssignDefaultNetID;
    const static char* kWaitTicksOnShutdown;
    //@}

    /// Set the ConnectionID of the ChannelManager we are currently connected to.
    virtual void SetChannelManagerConnectionID(const efd::ConnectionID& cmConnectionID);

    /// @name ChannelManager configuration accessors.
    //@{
    /**
        Returns a const pointer to the ChannelManagerConfigList. The pointer is
        const because you should not modify this data directly. Making changes to the
        config this way will not guarantee that indexes are unique or that they
        remain in ascending order. The preferred way to change the configuration at
        runtime is to construct channel manager config objects and add them using
        AddConfig (or use the helper function AddChannelManagerConnection), and
        remove them from the CM using RemoveConfig.
    */
    inline const ChannelManagerConfigList& GetConfigList();

    /**
        Add configuration to connect to a ChannelManager.

        @param spConfig The config to use for the new listen socket.

        @return efd::UInt32 The index assigned to the socket. You can later use this
        index to remove the socket from the list.
    */
    efd::UInt32 AddConfig(ChannelManagerConfigPtr spConfig);

    /**
        Removes the config with the index value passed in, disconnecting the corresponding
        connection (if connected).

        @param index The index value of the config entry to remove. Note that this is
        not necessarily the same as the position in the list; it is
        actually the index value assigned to the config entry object.

        @return bool Returns true if the entry was found and removed.
    */
    bool RemoveConfig(efd::UInt32 index);

    /**
        Removes the config pointed to by the iterator passed in, disconnecting the corresponding
        connection (if connected).

        @param it The iterator pointing to the entry to remove.
    */
    void RemoveConfig(ChannelManagerConfigList::iterator it);

    /**
        Shortcut function for adding a new channel manager connection. Creates the
        config from the params passed in, and adds the config to the
        list of configs.

        @param hostname The name of the host to start listening on.
        @param port The port number to listen on.
        @param qos The quality of service to use for the connection.

        @return efd::UInt32 The index of the config added to the list.
    */
    efd::UInt32 AddChannelManagerConnection(
        efd::utf8string hostname,
        efd::UInt16 port,
        efd::QualityOfService qos);

    /**
        A convenience function for generating a unique index value. We keep the config
        list sorted ascending by index, so we can create a new unique index by simply
        taking the last one and incrementing it.

        @return efd::UInt32 The new index value.
    */
    efd::UInt32 GetNextIndexValue();

    //@}

protected:

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void OnServiceRegistered(IAliasRegistrar* pAliasRegistrar);
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();
    const char* GetDisplayName() const;

    /// Set the status of the connection associated with the specified Quality of Service
    void SetConnectionStatus(QualityOfService qos, ConnectionStatus status);

    /// Called by OnPreInit to let MessageService know that NetService is ready to handle
    /// subscriptions
    virtual void NotifyMessageService();

    /// Iterate any pending subscriptions to check to see if Categories now being produced can be
    /// mapped to Qualities of Service
    virtual void CheckPendingSubscriptions(Category catIDToCheck);

    /// Check all pending subscriptions
    virtual void CheckPendingSubscriptions();

    /// Tell NetService to disconnect from all ChannelManagers of a specific QualityOfService
    virtual void DisconnectFromChannelManager(QualityOfService qualityOfService);

    /// Unsubscribe all callbacks from everything.
    virtual void UnsubscribeAll();

    /**
        This method handles system messages received by the NetService.  Examples of system
        messages are SubscribeExternal and UnsubscribeExternal messages used to set up
        communication between two connected processes.

        @param pMessage The system message to handle
    */
    virtual void HandleSystemMessage(EnvelopeMessage* pMessage);

protected:
    /**
        The pointer to the local message service in this framework.
        Used to send messages from the Net Service to the Local Message Service
    */
    MessageServicePtr m_spMessageService;

    /// keeps track of which NetID/QOS maps to which ConnectionID
    NetIDQosPairToConnectionIDMap m_NetIDQosLookupMap;
    /// list of configurations of ChannelManagers to connect to
    ChannelManagerConfigList m_ConfigList;

    /// @cond EMERGENT_INTERNAL
    class PendingSubscription
    {
    public:
        PendingSubscription(efd::UInt32 netID, efd::UInt32 subscriptionType)
            : m_netID(netID)
            , m_subscriptionType(subscriptionType){}
        efd::UInt32 m_netID;
        efd::UInt32 m_subscriptionType;
    };

    typedef efd::list< PendingSubscription > PendingSubscriptionList;
    typedef efd::map< Category, PendingSubscriptionList > CategoryToPendingSubscriptionListMap;
    CategoryToPendingSubscriptionListMap m_pendingSubscriptions;
    /// @endcond

    /// The NetLib this NetServiceService instance uses to perform communication.
    efd::SmartPointer< INetLib > m_spNetLib;

    /// port of the ChannelManager we connect to.
    efd::UInt16 m_channelManagerListenPort;

    /// ip address of the ChannelManager we connect to.
    efd::utf8string m_channelManagerIP;

    /// NetID of the ChannelManager
    efd::UInt32 m_channelManagerNetID;

    /// True if we should automatically re-connect to our Channel Manager if the connection is lost.
    bool m_autoReconnectToChannelManager;

    /// The current status of our connection.
    ConnectionStatus m_connectionStatus;

    /// Time in the future when we should attempt to reconnect to our Channel Manager.
    efd::TimeType m_reconnectTime;

    /// Amount of time we should wait between re-connect attempts.
    efd::TimeType m_reconnectWaitTime;

    /// A string indicating what kind of NetLib should be factoried and used by this instance.
    efd::utf8string m_netLibType;

    /// True if we should read NetLib configuration information out of Config Manager.
    bool m_readNetLibConfig;

    /// @cond EMERGENT_INTERNAL
    typedef EE_STL_NAMESPACE::pair<efd::Category, INetCallback*> CategoryCallback;
    typedef efd::map<CategoryCallback, NonAtomicRefCount> CategoryRefcount;
    CategoryRefcount m_subscriberRefcount;
    CategoryRefcount m_producersRefcount;
    /// @endcond

    /// A pointer to the ChannelManagerService in the same process as this NetService instance.
    /// Used for direct in process communication instead of less efficient socket based
    /// communication.
    ChannelManagerService* m_pChannelManagerService;

    /// True if we should assign the NetID kNetID_Client in OnPreInit
    bool m_assignClientNetID;

    /// Number of ticks we should wait to attempt to send any messages in our outgoing message
    /// queues.
    efd::UInt32 m_waitTicksOnShutdown;
};

/// A SmartPointer for the NetService class
typedef efd::SmartPointer<NetService> NetServicePtr;

} // end namespace efd

#include <efdNetwork/NetService.inl>

#endif // EE_NETSERVICE_H
