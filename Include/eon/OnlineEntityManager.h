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
#ifndef EE_ONLINEENTITYMANAGER_H
#define EE_ONLINEENTITYMANAGER_H

#include <egf/EntityManager.h>
#include <eon/eonSystemServiceIDs.h>
#include <eon/OnlineEntry.h>


namespace eon
{
/**
    A cache of all active entities that belong to the local scheduler. Every entity that is
    owned by the local scheduler is placed in the EntityManager. This central ISystemService
    is available throughout the application via the ServiceManager to access these local entities.

    The EntityManager maintains a list of Entities with dirty properties. This dirty list is used
    to generate update messages. This informs listeners of property changes.
*/
class EE_EONENTRY OnlineEntityManager : public egf::EntityManager
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(OnlineEntityManager, efd::kCLASSID_OnlineEntityManager, egf::EntityManager);
    /// @endcond
public:
    /// Constructor used to create an instance of the EntityManager.
     OnlineEntityManager();
    //@}

protected:
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void OnServiceRegistered(efd::IAliasRegistrar* pAliasRegistrar);
    virtual const char* GetDisplayName() const;
    virtual bool AddEntity(egf::Entity* pEntity, efd::ParameterList* pDataStream);

    /**
        An override of EntityManager::OnEntityEndLifecycle which knows how to deal with lifecycles
        specific to the OnlineEntity and other derived entity classes.

        @param pEntity Pointer to the entity which is finishing a lifecycle
        @param lifecycle The entity lifecycle that is ending
    */
    virtual void OnEntityEndLifecycle(egf::Entity* pEntity, efd::UInt32 lifecycle);

    /// This override sends a different message for replicated entities and otherwise differs
    /// to the base implementation.  Replicated entities will send a ReplicatedEntityAddedMessage
    /// message.
    virtual void SendEntityCreationNotification(egf::Entity* pEntity);

    /// This override sends a different message for replicated entities and otherwise differs
    /// to the base implementation.  Replicated entities will send a ReplicatedEntityUpdatedMessage
    /// message.
    virtual void SendEntityUpdateNotification(egf::Entity* pEntity);

    /// This override sends a different message for replicated entities and otherwise differs
    /// to the base implementation.  Replicated entities will send a ReplicatedEntityRemovedMessage
    /// message.
    virtual void SendEntityRemovalNotification(egf::Entity* pEntity);

    /**
        Overridden to destroy replica entities in the correct way.

        @param pEntity pointer to entity requested for removal.
        @return bool return true if entity removed successfully, false if error.
    */
    virtual bool DestroyEntity(egf::Entity* pEntity);

    /// Cached message sent immediately when replicated entities are added
    egf::EntityChangeMessagePtr m_spReplicatedEntityAddedMsg;
    /// Cached message sent immediately when replicated entities are updated
    egf::EntityChangeMessagePtr m_spReplicatedEntityUpdatedMsg;
    /// Cached message sent immediately when replicated entities are removed
    egf::EntityChangeMessagePtr m_spReplicatedEntityRemovedMsg;

};

/// A smart pointer (for the OnlineEntityManager class.
typedef efd::SmartPointer<OnlineEntityManager> OnlineEntityManagerPtr;


} // end namespace eon

#endif // EE_ONLINEENTITYMANAGER_H
