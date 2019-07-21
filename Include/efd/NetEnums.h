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
#ifndef EE_NETENUMS_H
#define EE_NETENUMS_H

#include <efd/UniversalTypes.h>

namespace efd
{
    typedef UInt32 QualityOfService;
}

#include <efd/efdNetFeatures.h>
#include <efd/efdQualityOfService.h>
#include <efd/efdVirtualQualityOfService.h>

namespace efd
{

/**
    Values used by the INetService::GetConnectionStatus method. Some INetService implementations
    may not use all of these values. 
*/
enum ConnectionStatus
{
    /// While waiting to connect, the system was told to cancel any connection attempt.
    kCS_Canceled = 0,

    /// Waiting to be told to connect.
    kCS_WaitConnect,

    /// An attempt to connect has failed to establish a connection
    kCS_Failed,

    /// A connection has been requested and is in the process of being established
    kCS_Connecting,

    /// Established an initial physical connection on which network commands can be reliably
    /// exchanged, but additional protocol level communication may be required for Category based
    /// message delivery to be available. In effect, at this point the local and remote INetService
    /// implementations can communicate using internal protocols but remote MessageService level
    /// communication is not possible yet.
    kCS_ReliableConnected,

    /// The connection is ready to notify the remote process of its NetID. Every process should have
    /// a unique NetID and connections should not be accepted that would violate this restriction.
    /// @note This status is an implementation detail of the default NetService implementation and
    ///     might not be used by other INetService implementations.
    kCS_AnnounceNetID,

    /// The connection is waiting for acknowledgment of the announced NetID.
    /// @note This status is an implementation detail of the default NetService implementation and
    ///     might not be used by other INetService implementations.
    kCS_WaitNetIDAck,

    /// The connection is fully established and ready for Category based message delivery.
    kCS_Connected,

    /// The connection was previously connected but has been disconnected
    kCS_Disconnected
};

} // end namespace efd

#endif //EE_NETENUMS_H
