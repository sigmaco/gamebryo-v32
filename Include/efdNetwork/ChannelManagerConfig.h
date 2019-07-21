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
#ifndef EE_CHANNELMANAGERCONFIG_H
#define EE_CHANNELMANAGERCONFIG_H

#include "efd/ConnectionID.h"

namespace efd
{

/// Struct for holding ChannelManager configuration information.
class ChannelManagerConfig : public efd::MemObject
{
    EE_DECLARE_CONCRETE_REFCOUNT;
public:

    /// @name Construction and Destruction
    //@{
    inline ChannelManagerConfig();

    inline ChannelManagerConfig(
        efd::UInt32 index,
        const efd::utf8string& hostname,
        efd::UInt16 port,
        efd::QualityOfService qualityOfService);

    inline ChannelManagerConfig(const ChannelManagerConfig& rhs);
    //@}

    /// Assignment operator.
    inline ChannelManagerConfig& operator=(const ChannelManagerConfig& rhs);

    /// The index of this config entry.
    efd::UInt32 m_index;

    /// The hostname of the ChannelManager in this config entry.
    efd::utf8string m_hostname;

    /// The port of the ChannelManager in this config entry.
    efd::UInt16 m_port;

    /// The QualityOfService used for this connection to the ChannelManager in this config entry.
    efd::QualityOfService m_qualityOfService;

    /// The ConnectionID of a connection to a ChannelManager if established.
    efd::ConnectionID m_connectionID;

    /// The current status of this connection.
    efd::UInt32 m_connectionStatus;

    /// An index of the tick of the last attempted connection to this ChannelManager.
    efd::UInt32 m_lastAttempt;

    /// The index of the tick that the next connection attempt should be made to this 
    /// ChannelManager.
    efd::UInt32 m_nextAttempt;

    /// If true this connection should cause the app to fail if the port specified in the config is
    /// already in use.
    bool m_failInUse;
};
typedef efd::SmartPointer< ChannelManagerConfig > ChannelManagerConfigPtr;

typedef efd::RefCountedMemObj< efd::list< ChannelManagerConfigPtr > > ChannelManagerConfigList;

} //end namespace efd

#include <efdNetwork/ChannelManagerConfig.inl>

#endif //EE_CHANNELMANAGERCONFIG_H
