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
#ifndef EE_ONLINEENTITYCHANGEMESSAGE_H
#define EE_ONLINEENTITYCHANGEMESSAGE_H

#include <egf/EntityChangeMessage.h>
#include <eon/eonMessageIDs.h>


namespace eon
{

    /// A message sent when a replicated entity is added to the OnlineEntityManager.  This message
    /// is sent instead of the egf::OwnedEntityAddedMessage sent for replicated entities.
    typedef efd::MessageWrapper<egf::EntityChangeMessage, efd::kMSGID_ReplicatedEntityAdded>
        ReplicatedEntityAddedMessage;

    /// A message sent when properties of a replicated entity are modified.  This message is sent
    /// instead of the egf::OwnedEntityUpdatedMessage for replicated entities.
    typedef efd::MessageWrapper<egf::EntityChangeMessage, efd::kMSGID_ReplicatedEntityUpdated>
        ReplicatedEntityUpdatedMessage;

    /// A message sent when a replicated entity is removed.  The message is already disassociated
    /// with the ReplicationService when this message is delivered.  This message is sent instead
    /// of the egf::OwnedEntityRemovedMessage for replicated entities.
    typedef efd::MessageWrapper<egf::EntityChangeMessage, efd::kMSGID_ReplicatedEntityRemoved>
        ReplicatedEntityRemovedMessage;

} // end namespace eon

#endif // EE_ONLINEENTITYCHANGEMESSAGE_H
