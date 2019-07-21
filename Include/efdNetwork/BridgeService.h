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
#ifndef EE_BRIDGESERVICE_H
#define EE_BRIDGESERVICE_H

#include <efd/ISystemService.h>
#include <efdNetwork/efdNetworkLibType.h>
#include <efdNetwork/INetLib.h>
#include <efdNetwork/NetService.h>

namespace efd
{

class BridgeProxy;

/**
    The BridgeService bridges two different types of NetLibs potentially talking different
    protocols or transports.
*/
class EE_EFDNETWORK_ENTRY BridgeService : public NetService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(BridgeService, kCLASSID_BridgeService, NetService);
    /// @endcond
public:

    /// Default Constructor
    BridgeService(
        const efd::utf8string& netLibType = efd::utf8string::NullString(),
        const efd::utf8string& inNetLibType = efd::utf8string::NullString());

    /// Virtual Destructor
    virtual ~BridgeService();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    void HandleNetMessage(const IMessage* pIncomingMessage,const ConnectionID& senderConnectionID);

    // Callback Method called by m_spInNetLib through wrapper object
    void HandleInNetMessage(
        const IMessage* pIncomingMessage,
        const ConnectionID& senderConnectionID);

    /// Accessor for m_inNetLibType
    const efd::utf8string& GetInNetLibType() {return m_inNetLibType;}

    /// Accessor for m_netLibType
    const efd::utf8string& GetNetLibType() {return m_netLibType;}

    /// constant used to hold config section name
    const static char* kConfigSection;

protected:
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::AsyncResult OnTick();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    const char* GetDisplayName() const;

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void NotifyMessageService();

    /// INetLib used to listen for incoming connections
    INetLibPtr m_spInNetLib;

    /// pointer to the proxy object that will call HandleInNetMessage
    BridgeProxy* m_pInBridgeProxy;

    /// queue of incoming messages, stored until outgoing connection has been established
    efd::list<EnvelopeMessagePtr> m_inMessageQueue;

    /// queue of outgoing messages, stored until incoming connection has been established
    efd::list<EnvelopeMessagePtr> m_outMessageQueue;

    /// true if incoming connection is established and ready to receive messages
    bool m_inReady;

    /// true if outgoing connection is established and ready to receive messages
    bool m_outReady;

    /// ConnectionID that of the listening socket for the incoming connection
    efd::ConnectionID m_inListenCID;

    //// port number to listen for incoming connections on
    efd::UInt16 m_inPort;

    /// INetLib type used for the incoming connection
    efd::utf8string m_inNetLibType;

    /// used to determine if we should read the netlib value out of the config, or use the
    /// override passed in to the constructor
    bool m_readInNetLibConfig;

};
typedef efd::SmartPointer<BridgeService> BridgeServicePtr;

} // namespace efd

#endif //EE_BRIDGESERVICE_H
