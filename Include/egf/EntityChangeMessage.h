// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or nondisclosure agreement
// with Emergent Game Technologies and may not be copied or disclosed except in accordance with
// the terms of that agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef EE_ENTITYCHANGEMESSAGE_H
#define EE_ENTITYCHANGEMESSAGE_H

#include <efd/IMessage.h>
#include <egf/egfMessageIDs.h>
#include <egf/Entity.h>


namespace egf
{

/// A message for sending local notifications of changing entity state.
class EE_EGF_ENTRY EntityChangeMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EntityChangeMessage, efd::kMSGID_EntityChangeMessage, efd::IMessage);
    /// @endcond

public:
    /// Constructor
    inline EntityChangeMessage();

    /// Set the entity pointer
    /// @param pEntity The entity pointer
    inline void SetEntity(egf::Entity* pEntity);

    /// Get the entity pointer
    /// @return The entity pointer
    inline egf::Entity* GetEntity() const;

private:
    // See IStreamable::Serialize.
    virtual void Serialize(efd::Archive& ar);

protected:
    egf::EntityPtr m_spEntity;
};

/// A SmartPointer for the EntityChangeMessage class
typedef efd::SmartPointer<EntityChangeMessage> EntityChangeMessagePtr;

/// @name MessageWrappers from EntityChangeMessage.h
//@{

/// A message sent when an entity is added to the EntityManager.  Message is sent by the
/// EntityManager as soon as the new entity completed its OnCreate lifecycle.
typedef efd::MessageWrapper<EntityChangeMessage, efd::kMSGID_OwnedEntityAdded>
    OwnedEntityAddedMessage;

/// A message sent when an entity enters the world.
typedef efd::MessageWrapper<EntityChangeMessage, efd::kMSGID_OwnedEntityEnterWorld>
    OwnedEntityEnterWorldMessage;

/// A message sent when properties of an entity are modified.  Sent no more than once per
/// tick by the EntityManager service.
/// @note Making further property changes to the entity while handling this message is not
/// recommended as any properties changed during the handling of this message will not result
/// in a future update message.  This means the update might go unnoticed by other services.
typedef efd::MessageWrapper<EntityChangeMessage, efd::kMSGID_OwnedEntityUpdated>
    OwnedEntityUpdatedMessage;

/// A message sent when an entity exits the world.
typedef efd::MessageWrapper<EntityChangeMessage, efd::kMSGID_OwnedEntityExitWorld>
    OwnedEntityExitWorldMessage;

/// A message sent by the EntityManager when an entity is removed.  When handling this
/// message you can still access the entity, read its properties, and call immediate behaviors
/// but it is too late to schedule any behaviors on the entity.
typedef efd::MessageWrapper<EntityChangeMessage, efd::kMSGID_OwnedEntityRemoved>
    OwnedEntityRemovedMessage;
//@}

} // end namespace egf

#include <egf/EntityChangeMessage.inl>

#endif // EE_ENTITYCHANGEMESSAGE_H
