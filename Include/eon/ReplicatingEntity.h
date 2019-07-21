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
#ifndef EE_REPLICATINGENTITY_H
#define EE_REPLICATINGENTITY_H

#include <eon/OnlineEntry.h>
#include <egf/Entity.h>
#include <eon/eonClassIDs.h>

namespace eon
{

// Forward declarations:
class ReplicationService;
class OnlineEntityManager;

/// An entity that can replicate its state. Used as a common base for ReplicationProducerEntity
/// and ReplicationConsumerEntity. This adds data members common to all replicated entities.
class EE_EONENTRY ReplicatingEntity : public egf::Entity
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(ReplicatingEntity, efd::kCLASSID_ReplicatingEntity, egf::Entity);

    /// @endcond

protected:
    ReplicatingEntity(
        const egf::FlatModel* i_pTemplate,
        egf::EntityID i_eid,
        bool i_createAsMaster);

public:
    /**
        Sets the pointer to our active Replication Service.  The ReplicationService itself
        will call this method as needed.  This replication service will be used to send
        replication updates for Producer entities and will help with channel subscriptions
        and view behavior events for Consumer entities.

        @param pRS pointer to a ReplicationService instance
    */
    virtual void SetReplicationService(eon::ReplicationService* pRS);

    /**
        Returns the category to which the given property group is reflecting.

        @param groupIndex an index between 0 and 31 inclusive identifying a property group.
           What properties, if any, are in the group is defined in the flat model data.
    */
    efd::Category GetReplicationCategory(efd::UInt32 groupIndex) const;

    /**
        Determine if the given Category is being used to replicate any data too.  This means
        that the given category has been passed to SetReplicationCategory for some groupIndex.

        @param cat The category to check for
        @return True if the given category is used for any of our replication groups
    */
    bool UsesReplicationCategory(efd::Category cat) const;

    /**
        Sends a view event message to invoke the specified behavior on the specified
        replicated entity listening on the specified event channel

        @param eventChannel The category to send the event message to
        @param entityID The replicated entity's ID
        @param mixinModelID The model that must be mixed into the target entities.  Pass
        an ID of 0 to skip this type safety check.
        @param invokeModelID The specific model that implements the behavior to invoke, or
        zero to automatically call the most derived implementation.  Typically you always
        want to pass zero for this parameter.
        @param behaviorID The behavior ID to invoke.
        @param pParams The parameters required by the behavior.
        @param delay The time to delay before executing the behavior.

        @return True if the event message was successfully sent, false otherwise
    */
    bool SendViewEvent(
        efd::Category eventChannel,
        egf::EntityID entityID,
        egf::FlatModelID mixinModelID,
        egf::FlatModelID invokeModelID,
        egf::BehaviorID behaviorID,
        efd::ParameterList* pParams,
        efd::TimeType delay);

    /**
        Sends a view event message to invoke the specified behavior on the specified replicated
        entity listening on the specified event channel

        @param eventChannel The category to send the event message to
        @param entityID The replicated entity's ID
        @param strMixinModel A model that must be mixed into the target entities.  Pass a
            NULL pointer or empty string to skip this type safety check.
        @param strBehavior The behavior to invoke
        @param pParams The parameters required by the behavior
        @param delay The time to delay before executing the behavior

        @return True if the event message was successfully sent, false otherwise
    */
    bool SendViewEvent(
        efd::Category eventChannel,
        egf::EntityID entityID,
        const char* strMixinModel,
        const char* strBehavior,
        efd::ParameterList* pParams,
        efd::TimeType delay);


    /// Lifecycle values for use in _OnLifecycleEvent and related methods.
    enum RepLifeCycles
    {
        lifecycle_OnBeginMigration = Entity::MAX_ENTITY_LIFECYCLE+1,
        lifecycle_OnEndMigration,

        MAX_REP_LIFECYCLE
    };

protected:
    virtual const char* GetLifecycleName(efd::UInt32 lifecycle);

    eon::ReplicationService* m_pReplicationService;

    // Storage for the Replication Group to Channel mapping.  For owned entities this stores
    // the channel that should be used to send replication updates when properties change. For
    // replicated entities we use this to store the channel on which replication updates are
    // arriving.  In either case, UsesReplicationCategory can be used to test whether an entity
    // uses a particular channel for any replication group and GetReplicationCategory can be
    // used to get the value of a particular group.
    typedef efd::map< efd::UInt32, efd::Category > ReplicationCategoryData;
    ReplicationCategoryData m_replicationSettings;
};

/// A SmartPointer for the ReplicatingEntity class
typedef efd::SmartPointer< ReplicatingEntity > ReplicatingEntityPtr;

} // end namespace eon


#endif // EE_REPLICATINGENTITY_H
