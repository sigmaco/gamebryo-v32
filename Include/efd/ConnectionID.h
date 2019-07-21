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
#ifndef EE_CONNECTIONID_H
#define EE_CONNECTIONID_H

#include <efd/NetEnums.h>
#include <efd/Serialize.h>

namespace efd
{

/**
    A unique id for a connection. The ConnectionID is used throughout the networking layer to
    identify connection instances. This id encapsulates the connection IP address, the local
    port number, the remote port number, and the QualityOfService.
 */
class EE_EFD_ENTRY ConnectionID
{
public:

    /// @name Construction and Destruction
    //@{
    /// Construct the default ConnectionID with id 0.
    inline ConnectionID();

    /// Construct a new ConnectionID from the given identifier.
    inline ConnectionID(efd::QualityOfService i_qos, efd::UInt64 i_id);

    /// Construct a new ConnectionID from an IP address, local port number and remote port number.
    inline ConnectionID(
        efd::QualityOfService i_qos,
        efd::UInt32 i_ip,
        efd::UInt16 i_localPort,
        efd::UInt16 i_remotePort);
    //@}

    /// Return true of the rhs ConnectionID is equal to this ID.
    inline bool operator==(const ConnectionID& rhs) const;

    /// Return true if the rhs ConnectionID is not equal to this ID.
    inline bool operator!=(const ConnectionID& rhs) const;

    /// Return true if the rhs ConnectionID is numerically greater than this ID.
    inline bool operator>(const ConnectionID& rhs) const;

    /// Return true if the rhs ConnectionID is numerically less than this ID.
    inline bool operator<(const ConnectionID& rhs) const;

    /// returns true if this ConnectionID is valid
    inline bool IsValid() const;

    /// Get is ID as an unsigned int64.
    inline efd::UInt64 GetValue() const;

    /// Get the IP address portion of this ID as a unsigned int32.
    inline efd::UInt32 GetIP() const;

    /// Get the local port portion of this ID as an unsigned int16.
    inline efd::UInt16 GetLocalPort() const;

    /// Get the remote port portion of this ID as an unsigned int16.
    inline efd::UInt16 GetRemotePort() const;

    /// Get the remote port portion of this ID as an unsigned int16.
    inline efd::QualityOfService GetQualityOfService() const;

    /// Convert this ID into a displayable string.
    efd::utf8string ToString() const;

    /// Serialize to an Archive
    void Serialize(efd::Archive& ar);

    /// @cond EMERGENT_INTERNAL
    // Internal contents of the ConnectionID.

    struct IPFields
    {
        efd::UInt64 ip : 32;
        efd::UInt64 localPort : 16;
        efd::UInt64 remotePort : 16;
    };

    union
    {
        efd::UInt64 m_id;
        IPFields m_ipInfo;
    };

    efd::QualityOfService m_qos;

    EE_COMPILETIME_ASSERT(sizeof(IPFields) == sizeof(efd::UInt64));

    /// @endcond
};

typedef efd::RefCountedMemObj< efd::set< ConnectionID > > ConnectionIDSet;
typedef efd::SmartPointer< ConnectionIDSet > ConnectionIDSetPtr;

static const ConnectionID kCID_INVALID; // use default constructor

} // end namespace efd


// Inline definitions:
#include <efd/ConnectionID.inl>


#endif //EE_CONNECTIONID_H
