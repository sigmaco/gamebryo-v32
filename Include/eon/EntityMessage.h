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
#ifndef ENTITYMESSAGE_H
#define ENTITYMESSAGE_H

#include <eon/OnlineEntry.h>
#include <efd/IMessage.h>
#include <egf/Entity.h>
#include <efd/StreamMessage.h>
#include <eon/eonMessageIDs.h>
#include <efd/SequenceNumber.h>

namespace eon
{

/**
    This message class is used to replicate entity state.
 */
class EE_EONENTRY EntityMessage : public efd::StreamMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EntityMessage, efd::kMSGID_EntityMessage, efd::StreamMessage);
    /// @endcond

public:

    /// Constructor
    EntityMessage();

    /// virtual Destructor
    virtual ~EntityMessage();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

    /**
        Retrieve the ID of the entity streamed into this message.
        @return EntityID the ID for the entity this message is about.
    */
    egf::EntityID GetEntityID() const;
    void SetEntityID(egf::EntityID eid);

    /// Accessors for the group index. Updates are per-replication group.
    //@{
    efd::UInt32 GetGroupIndex() const;
    void SetGroupIndex(efd::UInt32 groupIndex);
    //@}

    /// Accessors for the model name of this entity type
    //@{
    const efd::utf8string& GetModelName() const;
    void SetModelName(const efd::utf8string& modelName);
    //@}

    /// Accessors for the sequence number for this update. The sequence number prevents old
    /// messages from being applied. Messages can be old both due to using unordered qualities of
    /// service or due to updating the same property in multiple replication groups.
    //@{
    efd::SequenceNumber32 GetSequenceNumber() const;
    void SetSequenceNumber(efd::SequenceNumber32 sequenceNumber);
    //@}

    /// Accessors for the current replication category. This is the replication category being
    /// used by the entity for the given group at the time the message was sent. This can be
    /// different from the category this message arrived on in some cases. For example, late-joiner
    /// discoveries arrive on a different private channel and loss messages resulting from the
    /// producer changing categories arrive on the previously used category.
    //@{
    efd::Category GetCurrentCategory() const;
    void SetCurrentCategory(efd::Category cat);
    //@}

    /// Accessors for the owning process ID. This uniquely identifies the process that owns the
    /// entity in question.
    //@{
    efd::UInt32 GetOwningProcessID() const;
    void SetOwningProcessID(efd::UInt32 id);
    //@}

protected:
    egf::EntityID m_entityID;
    efd::utf8string m_modelName;
    efd::UInt32 m_groupIndex;
    efd::SequenceNumber32 m_sequenceNumber;
    efd::Category m_cat;
    efd::UInt32 m_owningProcess;
};

/// A smart pointer for the EntityMessage class
typedef efd::SmartPointer<EntityMessage> EntityMessagePtr;

} // end namespace eon

#endif // ENTITYMESSAGE_H
