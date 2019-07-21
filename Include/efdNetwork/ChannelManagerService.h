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
#ifndef EE_CHANNELMANAGERSERVICE_H
#define EE_CHANNELMANAGERSERVICE_H

#include <efd/ISystemService.h>
#include <efd/MessageService.h>
#include <efd/StreamMessage.h>

#include <efdNetwork/INetLib.h>
#include <efdNetwork/efdNetworkLibType.h>

#include <efdNetwork/ChannelManagerConfig.h>

namespace efd
{
class EnvelopeMessage;
class EnumManager;
class NetService;

/**
    \brief ChannelManagerService receives messages from connected NetServices and routes those
    messages to all other connected NetServices based on Subscription to Categories.

    The Network System uses Category subscription to route messages between processes. All
    processes that wish to communicate must connect to a central ChannelManagerService.
    The ChannelManagerService can exist in a process separate from all clients (client/server)
    or in the same process as a client (peer to peer).

*/
class EE_EFDNETWORK_ENTRY ChannelManagerService : public ISystemService, public INetCallback
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ChannelManagerService, efd::kCLASSID_ChannelManager, ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT
    /// @endcond
public:

    /// @name Config strings used by this service
    //@{
    //! The default section name for retrieving configuration variables
    const static char* kConfigSection;
    //! hostname that ChannelManagerService listens on
    const static char* kHostname;
    //! port that ChannelManagerService listens on
    const static char* kPort;
    //! Should ChannelManagerService return failure from OnInit/OnTick if port is in use
    const static char* kFailInUse;
    //! Quality of Service that ChannelManagerService listens on and allowed values
    const static char* kQualityOfService;
    const static char* kQOS_Reliable;
    const static char* kQOS_Unreliable;
    const static char* kQOS_Connectionless;
    const static char* kQOS_Invalid;
    //! default numeric port if no configuration is provided
    const static efd::UInt16 defaultListenPort;
    //@}

public:
    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    ChannelManagerService(const efd::utf8string& netLibType = efd::utf8string::NullString());
    /// Constructor that takes a pre-constructed NetLib
    ChannelManagerService(INetLib* pNetLib);

    /// Virtual destructor.
    virtual ~ChannelManagerService();
    //@}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual AsyncResult OnInit();
    virtual AsyncResult OnTick();
    virtual AsyncResult OnShutdown();
    virtual const char* GetDisplayName() const;

     /**
         Receives messages from all connected NetServices.
         @param pEnvelopeMessage Message to handle
    */
    virtual void HandleMessage(const efd::EnvelopeMessage* pEnvelopeMessage);

    /**
        Handle a new incoming connection.
        @param acceptedConnectionID New ConnectionID to add
    */
    virtual void AddConnection(const efd::ConnectionID& acceptedConnectionID);

    /**
        Handle a disconnection.
        @param acceptedConnectionID Previously added ConnectionID to remove
    */
    virtual void RemoveConnection(const efd::ConnectionID& acceptedConnectionID);

    /**
    Uses the NameResolutionService to announce the ChannelManager on the network

    @param name A name used to identify this particular ChannelManager
    @param extraInfo Additional info about this process. Not used in lookup search.
    */
    virtual void AnnounceService(
        const efd::utf8string& name,
        const efd::utf8string& extraInfo);

    /**
    Uses the NameResolutionService to stop announcing the ChannelManager

    @param name A name used to identify this particular ChannelManager
    */
    virtual void CancelAnnounceService(const efd::utf8string& name);

    /**
        Returns a const pointer to the ChannelManagerConfigList. The pointer is
        const because you should not modify this data directly. Making changes to the
        config this way will not guarantee that indexes are unique or that they
        remain in ascending order. The preferred way to change the configuration at
        runtime is to construct channel manager config objects and add them using
        AddConfig (or use the helper function AddChannelManagerConnection), and
        remove them from the CM using RemoveConfig.
    */
    const ChannelManagerConfigList& GetConfigList() { return m_ConfigList; }

    /**
        Reads ChannelManager config section and returns a list of ChannelManagerConfig objects
        each describing a ChannelManager/QualityOfService to connect to.
        Allocates a new list that can be used to keep track of connection status.
    */
    static void ReadConfig(IConfigManager* i_pConfigManager, ChannelManagerConfigList& o_result);

    /**
      Start listening on a socket with the params assigned by the passed-in channel
      manager config.

      @param spConfig The config to use for the new listen socket.

      @return efd::UInt32 The index assigned to the socket. You can later use this
              index to remove the socket from the list.
    */
    efd::UInt32 AddConfig(ChannelManagerConfigPtr spConfig);

    /**
      Removes the config with the index value passed in, shutting down the
      corresponding listener.

      @param index The index value of the config entry to remove. Note that this is
                   not necessarily the same as the position in the list; it is
                   actually the index value assigned to the config entry object.

      @return bool Returns true if the entry was found and removed.
    */
    bool RemoveConfig(efd::UInt32 index);

    /**
      Removes the config pointed to by the iterator passed in, shutting down the
      corresponding listener.

      @param it The iterator pointing to the entry to remove.
    */
    void RemoveConfig(ChannelManagerConfigList::iterator it);

    /**
      Shortcut function for adding a new channel manager listener. Creates the
      config from the params passed in, starts listening and adds the config to the
      list of configs.

      @param hostname The name of the host to start listening on.
      @param port The port number to listen on.
      @param qos The quality of service to use for the connection.

      @return efd::UInt32 The index of the config added to the list.
    */
    efd::UInt32 AddChannelManagerConnection(const efd::utf8string& hostname,
        efd::UInt16 port, efd::QualityOfService qos);

    /**
      A convenience function for generating a unique index value. We keep the config
      list sorted ascending by index, so we can create a new unique index by simply
      taking the last one and incrementing it.

      @return efd::UInt32 The new index value.
    */
    efd::UInt32 GetNextIndexValue();


    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void HandleNetMessage(
        const IMessage* pIncomingMessage,
        const ConnectionID& i_source);

    /// Returns the NetLib used by this service
    INetLib* GetNetLib();

    /// Add a local NetService in this process. If set ChannelManagerService will expect that the
    /// NetService has not connected over the network and will deliver any messages to it
    /// directly.
    virtual void AddNetService(NetService* pNetService);

    /// Returns the number of unbound configurations
    efd::UInt8 GetUnboundConfigurations() { return m_needListen; }

protected:
    /// Iterate any pending subscriptions to check to see if Categories now being produced can be
    /// mapped to Qualities of Service
    virtual void CheckPendingSubscriptions(Category catIDToCheck);

    /// Check all pending subscriptions
    virtual void CheckPendingSubscriptions();

    /// Make sure the specified Category is associated with the specified QualityOfService
    void CheckPendingSubscriptions(Category catIDToCheck, QualityOfService qos);

    /// Delivers a message to any NetServices that have registered to receive local delivery
    virtual void DeliverLocalNetMessage(
        const IMessage* pMessage,
        const ConnectionID& sourceCID);

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
        const ConnectionID& cid);

    /**
        Send Message to a specific QualityOfService.

        @param pMessageToSend Message to send.
        @param destCategory Category to which to send message.
        @param qos QualityOfService to send message on.
    */
    void SendRemote(
        IMessage* pMessageToSend,
        const Category& destCategory,
        QualityOfService qos);

    /**
        Convert a string read from config file to QualityOfService.  Returns QOS_INVALID if
        the string cannot be converted into a QualityOfService.
    */
    static efd::QualityOfService StringToQualityOfService(
        const efd::utf8string& stringName,
        EnumManager* pEnumManager);

    /**
        Convert a QualityOfService value to the string equivalent.
    */
    static efd::utf8string QualityOfServiceToString(efd::QualityOfService qos);

    /**
        Assigns a Server/Peer NetID.
    */
    efd::UInt32 AssignNetID();

    /**
        Assigns a Client NetID.
    */
    efd::UInt32 AssignClientNetID();

    /// The NetLib this ChannelManagerService instance uses to perform communication.
    efd::INetLibPtr m_spNetLib;

    /// The number of unbound configurations
    efd::UInt8 m_needListen;

    /// next Server/Peer NetID to be assigned
    efd::UInt32 m_curNetID;

    /// next Client NetID to be assigned
    efd::UInt32 m_curClientNetID;

    /// Pointer to the MessageService instance that should be used to send local notifications on.
    efd::MessageServicePtr m_spMessageService;

    /// A string indicating what kind of NetLib should be factoried and used by this instance.
    efd::utf8string m_netLibType;

    /// True if we should read NetLib configuration information out of Config Manager.
    bool m_readNetLibConfig;

    /// Keeps track of config and status information for quality of service connections
    ChannelManagerConfigList m_ConfigList;

    /// keeps track of which NetID/QOS maps to which ConnectionID
    NetIDQosPairToConnectionIDMap m_NetIDQosLookupMap;

    /// set of pointers to any NetServices contained in this process
    efd::set< NetService* > m_netServiceSet;

    /// map of ConnectionID to NetID, used to to notify of NetID disconnection
    efd::map< ConnectionID, UInt32 > m_connectionIdToNetIDMap;

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

};

typedef efd::SmartPointer<ChannelManagerService> ChannelManagerServicePtr;

} // end namespace efd

#endif // EE_CHANNELMANAGERSERVICE_H
