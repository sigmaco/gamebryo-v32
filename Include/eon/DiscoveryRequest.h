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
#ifndef EE_DISCOVERYREQUEST_H
#define EE_DISCOVERYREQUEST_H

#include <efd/UniversalTypes.h>
#include <efd/IMessage.h>
#include <efdNetwork/NetCategory.h>
#include <egf/EntityID.h>
#include <eon/OnlineEntry.h>
#include <eon/eonMessageIDs.h>


namespace eon
{

/**
    Used to request a full discovery of all entities.  Sent by the GWClientProxy when a client
    late-joins a channel.  Sent using ProducerSend to the channel being joined.
*/
class EE_EONENTRY DiscoveryRequest : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(DiscoveryRequest, efd::kMSGID_RequestDiscovery, efd::IMessage);
    /// @endcond

public:

    /// @name Construction and Destruction
    //@{

    /// Default Constructor (used by factory).
    DiscoveryRequest();

    /// Destructor.
    virtual ~DiscoveryRequest();
    //@}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

    /// @name Accessors for SenderID
    //@{
    virtual efd::Category GetSenderID() const;

    virtual void SetSenderID(efd::Category);
    //@}

protected:
    /// Storage for senders Category
    efd::Category m_senderID;
};

/**
    A smart pointer (reference counting, self deleting pointer) for the
    DiscoveryRequest class
 */
typedef efd::SmartPointer<DiscoveryRequest> DiscoveryRequestPtr;

} //  namespace eon


#endif // EE_DISCOVERYREQUEST_H
