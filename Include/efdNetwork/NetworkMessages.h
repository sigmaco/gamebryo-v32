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
// Emergent Game Technologies, Calabasas, California 91302
// http://www.emergent.net

#pragma once
#ifndef NETWORKMESSAGES_H
#define NETWORKMESSAGES_H

#include <efd/StreamMessage.h>
#include <efd/Category.h>
#include <efd/ConnectionID.h>
#include <efd/efdMessageIDs.h>
#include <efdNetwork/efdNetworkLibType.h>

namespace efd
{
/**
    Messages used to notify the client of the network status.
    Used with MessageWrapper and kMSGID_NetworkBufferOK, kMSGID_NetworkBuffer1X,
    kMSGID_NetworkBuffer2X, kMSGID_NetworkBuffer3X, kMSGID_NetworkFailure.
*/
class EE_EFDNETWORK_ENTRY NetworkStatus : public efd::StreamMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(NetworkStatus, efd::kCLASSID_NetworkStatus, efd::StreamMessage);
    /// @endcond

public:
    /// Network status message constructor
    NetworkStatus();

    /// Network status message destructor
    virtual ~NetworkStatus();

    /**
        Set the information for this network status message by quality of service.
        @param cid The ID of the connection returning a status message.
        @param netId The net ID of the connection returning the status message.
    */
    void Set(
        const efd::ConnectionID& cid,
        const efd::UInt32 netId);

    /**
        Set the information for this network status message by quality of service.
        @param qos The quality of service of the connection returning a status message.
        @param netId The net ID of the connection returning the status message.
    */
    void Set(
        const efd::QualityOfService qos,
        const efd::UInt32 netId);

    /**
        Retrieves the quality of service that is reporting the network status.
        @return The quality of service.
    */
    efd::QualityOfService GetQOS() const;

    /**
        Retrieves the connection ID that is reporting the network status.
        @return The connection ID.
    */
    efd::ConnectionID GetConnectionID() const;

    /**
        Retrieves the network ID of the connection that is reporting the network status.
        @return The network ID.
    */
    efd::UInt32 GetNetID() const;

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

protected:
    /// Quality of service for the connection reporting the network status message.
    efd::QualityOfService m_qos;
    /// ID of the connection reporting the network status message.
    efd::ConnectionID m_cid;
    /// Network ID for the connection reporting the network status message.
    efd::UInt32 m_netId;
};
typedef efd::SmartPointer<NetworkStatus> NetworkStatusPtr;

} // end namespace efd

#include <efdNetwork/NetworkMessages.inl>

#endif // NETWORKMESSAGES_H
