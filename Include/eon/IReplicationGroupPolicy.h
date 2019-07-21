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
#ifndef EE_IREPLICATIONGROUPPOLICY_H
#define EE_IREPLICATIONGROUPPOLICY_H

#include <efd/IBase.h>
#include <eon/OnlineEntry.h>
#include <eon/EntityMessage.h>
#include <eon/OnlineEnums.h>
#include <eon/eonClassIDs.h>


namespace efd
{
    class ServiceManager;
    class IConfigManager;
    class EnumManager;
}

namespace eon
{
// Forward declaration
class ReplicationProducerEntity;

/**
    IReplicationGroupPolicy defines the parameters for a replication group. There is one policy for
    each of the 32 replication groups.  The policies are controlled by configuration settings.
*/
class EE_EONENTRY IReplicationGroupPolicy : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_INTERFACE1(
        IReplicationGroupPolicy,
        efd::kCLASSID_IReplicationGroupPolicy,
        efd::IBase);
    /// @endcond

public:
    /// Static accessors
    /// There are up to 32 possible policy instances. These static accessors can be used to get the
    /// various instances. If you are using custom policy objects then register your objects
    /// before calling Init, otherwise the system will automatically create GroupUpdatePolicy
    /// objects whenever a group is requested.
    //@{
    /**
        Get the IReplicationGroupPolicy object for the specified group index.

        @param groupIndex Index of the property group to get the policy of
    */
    static inline IReplicationGroupPolicy* GetReplicationGroupPolicy(efd::UInt32 groupIndex);

    /**
        Set the IReplicationGroupPolicy object for the specified group index. If registering a
        custom IReplicationGroupPolicy implementation you should call this prior to calling Init,
        otherwise default GroupUpdatePolicy objects will be automatically created.

        @param groupIndex Index of the property group to set the policy of
        @param pGroupUpdatePolicy The policy to assign to the specified group index
    */
    static inline void SetReplicationGroupPolicy(
        efd::UInt32 groupIndex,
        IReplicationGroupPolicy* pGroupUpdatePolicy);

    /**
        Read any config data from the ConfigManager. Standard options will be automatically
        parsed and set with the standard Generic Policy Options methods. If a policy needs to
        parse additional options they should override ReadConfiguration.

        @param pIConfigManager The ConfgiManager pointer to read data from
        @param pEnumManager The enumeration manager to allow setting quality of service values by
            name.
    */
    static void Init(efd::IConfigManager* pIConfigManager, efd::EnumManager* pEnumManager);

    /**
        Called by the Init method when a configuration section is provided for the given policy.
        This is not called if no configuration section is present. When called, the quality of
        service, minimum update delta, and update all policy settings will have already been read
        and applied so there is no need to call the default implementation, which does nothing.
    */
    virtual void ReadConfiguration(const efd::ISection* pSection);

    //@}


    /// Generic Policy Options
    /// These are the basic policy options that all policy implementations are expected to support.
    /// These can be extended by sub-classes but all subclasses are expected to support these.
    //@{

    /**
        Get the QualityOfService for the specified property group
    */
    inline efd::QualityOfService GetQualityOfService() const;

    /**
        Set the QualityOfService for the specified property group. This should only be set during
        initial setup and should not be changed once replication has begun.

        @param qos The new Quality of Service
    */
    inline void SetQualityOfService(efd::QualityOfService qos);

    /**
        Get the minimum amount of time between updates. Updates should never be generated more
        often that this time interval even though GenerateUpdate may be called more frequently.
    */
    inline efd::TimeType GetMinUpdateDelta();

    /**
        Set the minimum amount of time between updates. When using the default policy this can be
        changed at run-time and should begin to take immediately.

        @param minDelta The minimum amount of time between updates.
    */
    inline void SetMinUpdateDelta(efd::TimeType minDelta);

    /**
        Get the policy option for updating all properties rather than only dirty properties. By
        default only the dirty properties are updated, when this option is set then it is requested
        that updates contain more than just the dirty properties. Exactly what that means is
        determined by the specific policy implementation. The default GroupUpdatePolicy
        implementation will send all non-default properties that are in the specified replication
        groups when this option is set. This policy option can be useful for small replication
        groups that are sent over unreliable categories. If you are using a reliable quality of
        service then it is recommended that this option be left off in order to reduce bandwidth.
    */
    inline bool GetUpdateAll() const;

    /**
        Set the "update all" policy. See GetUpdateAll for details on this policy. When using the
        default policy this can be changed at run-time and should begin to take effect immediately.

        @param updateAll A value indicating all property groups should be updated
    */
    inline void SetUpdateAll(bool updateAll);

    /**
        The the "treat updates as discovers" policy. When this policy is set all updates will be
        sent as if they are discovery requests. When used on an unreliable replication category
        this prevents loss of an initial discovery message from preventing the entity from ever
        being created. When using this policy the replica entity must be able to handle having only
        a partial state transfer as the updates will only contain dirty properties and out-of-order
        delivery or message loss can prevent some updates from being applied; you may wish to
        combine this policy with "update all" if the group also needs to ensure the properties are
        all updated together.
    */
    inline bool GetTreatUpdatesAsDiscovers() const;

    /**
        Set the "treat updates as discovers" policy. See GetTreatUpdatesAsDiscovers for details on
        this policy. When using the default policy this can be changed at run-time and should begin
        to take effect immediately.

        @param bSendDiscovers The "treat updates as discovers" policy value.
    */
    inline void SetTreatUpdatesAsDiscovers(bool bSendDiscovers);

    //@}


    /// Normal replication methods
    //@{

    /**
        Begin a cycle of replication updates. During the update cycle each dirty entity that uses
        the policy will make a call to generate either a discovery, an update, or a loss. The calls
        will be grouped by entity only, and not by replication category. Policies that wish to
        aggregate updates to a specific category may wish to prepare for a series of updates during
        this call.
        The default implementation does nothing.
    */
    virtual void BeginUpdate() {}

    /**
        End a cycle of replication updates. Policies that wish to aggregate updates can use this
        call to apply any cached data.
        The default implementation does nothing.
    */
    virtual void EndUpdate() {}

    /**
        Called when an entity should be discovered as result of setting a replication category.
        The typical response is to generate a MessageWrapper<EntityMessage,
        kMSGID_EntityDiscoveryMessage> message describing the entity being discovered and all 
        non-default property values for the group. The message should be sent to the category
        returned by pEntity->GetReplicationCategory(groupIndex) using the quality of service
        specified for the policy.

        @note The Replication Service can only handle EntityMessage results. If you construct a
            policy that sends other message types then you need to extend or replace the Replication
            Service to handle the new message type.

        @param pServiceManager The service manager for use in accessing any required services
        @param pEntity The producer entity for which to generate a discovery
        @param groupIndex The replication group that is being discovered
    */
    virtual void GenerateDiscovery(
        const efd::ServiceManager* pServiceManager,
        ReplicationProducerEntity* pEntity,
        efd::UInt32 groupIndex) = 0;

    /**
        Called when an entity is dirty and should be considered for updating. The typical response
        is to generate a MessageWrapper<EntityMessage, kMSGID_EntityUpdateMessage> message if
        enough time has passed since the last message was sent, or to do nothing if enough time has
        not passed. When generating an update the contents should include at least all dirty
        properties from the group and may optionally include additional property values based on
        specific poilicy needs.

        @note The Replication Service can only handle EntityMessage results. If you construct a
            policy that sends other message types then you need to extend or replace the Replication
            Service to handle the new message type.

        @param pServiceManager The service manager for use in accessing any required services
        @param pEntity The producer entity for which to generate an update
        @param groupIndex The replication group that is being updated
    */
    virtual void GenerateUpdate(
        const efd::ServiceManager* pServiceManager,
        ReplicationProducerEntity* pEntity,
        efd::UInt32 groupIndex) = 0;

    /**
        Called when an entity should be lost due to a category change. The typical response is
        to generate a MessageWrapper<EntityMessage, kMSGID_EntityLossMessage> message describing
        the entity being lost which should be sent to the oldCategory using the quality of service
        specified for the policy.

        @note The Replication Service can only handle EntityMessage results. If you construct a
            policy that sends other message types then you need to extend or replace the Replication
            Service to handle the new message type.

        @param pServiceManager The service manager for use in accessing any required services
        @param pEntity The producer entity for which to generate a loss
        @param groupIndex The replication group that is being lost
        @param oldCategory The category this entity is being lost from
        @param newCategory The new category this entity is joining, if any
    */
    virtual void GenerateLoss(
        const efd::ServiceManager* pServiceManager,
        ReplicationProducerEntity* pEntity,
        efd::UInt32 groupIndex,
        efd::Category oldCategory,
        efd::Category newCategory) = 0;

    //@}


    /// Point-to-point Discovery methods
    /// These methods handle the special case where a point-to-point discovery has been requested.
    /// Unlike the normal discovery process the results from a point-to-point discovery are sent
    /// to a specified category on a specified quality of service rather than using the values
    /// from the policy itself.
    //@{

    /**
        Begin a point-2-point discovery.
        The default implementation does nothing.
    */
    virtual void BeginP2PUpdate() {}

    /**
        End a point-2-point discovery. Policies that wish to aggregate updates can use this call to
        apply any cached data.
        The default implementation does nothing.
    */
    virtual void EndP2PUpdate() {}

    /**
        Called when an entity should be discovered as result of a late joiner subscribing to the
        replication channel. The typical response is to generate a MessageWrapper<EntityMessage,
        kMSGID_EntityDiscoveryMessage> message describing the entity being discovered and all 
        non-default property values for the group. The message should be sent to the specified
        category using the specified quality of service.

        @note The Replication Service can only handle EntityMessage results. If you construct a
            policy that sends other message types then you need to extend or replace the Replication
            Service to handle the new message type.

        @param pServiceManager The service manager for use in accessing any required services
        @param pEntity The producer entity for which to generate a discovery
        @param groupIndex The replication group that is being discovered
        @param callbackChannel The category to which any results should be sent
        @param qos The quality of service at which results should be sent
    */
    virtual void GenerateP2PDiscovery(
        const efd::ServiceManager* pServiceManager,
        ReplicationProducerEntity* pEntity,
        efd::UInt32 groupIndex,
        efd::Category callbackChannel,
        efd::QualityOfService qos) = 0;

    //@}


    /// @cond EMERGENT_INTERNAL

    /// Method for freeing static memory during EE_SHUTDOWN
    static void _SDMShutdown();
    /// @endcond

protected:
    /// Constructor
    IReplicationGroupPolicy();

    /// virtual Destructor
    virtual ~IReplicationGroupPolicy();

    /// The quality of service to which updates are sent
    efd::QualityOfService m_messageQuality;

    /// The "update all" policy value
    bool m_updateAll;

    /// The "treat updates as discovers" policy
    bool m_treatUpdatesAsDiscovers;

    /// The minimum amount of time between updates. Updates should never be generated more often
    /// that this time interval even though GenerateUpdate may be called more frequently.
    efd::TimeType m_minUpdateDelta;

    /// Static storage for all 32 replication group policies
    static efd::SmartPointer<IReplicationGroupPolicy> m_groups[k_MAX_REPLICATION_GROUPS];
};

/// A SmartPointer for the IReplicationGroupPolicy interface
typedef efd::SmartPointer<IReplicationGroupPolicy> IReplicationGroupPolicyPtr;


/**
    A class for use by IReplicationGroupPolicy instances for storing per-entity data. These objects
    can be stored in and retrieved from the entity instance itself. As there can be hundreds of
    replicating entities care should be taken to ensure instances of this class are as small as
    possible. The producer entity will own these objects and will delete them when the entity is
    destroyed. IReplicationGroupPolicy implementations should lazy create these objects as needed.
    It is not required that policy data be used, if a policy does not need any per-entity data
    then it should not use this class.
*/
class EE_EONENTRY IReplicationGroupPolicyData : public efd::MemObject
{
    /// @cond EMERGENT_INTERNAL

    // We use Foundation RTTI which gives us a vtable but we do not use reference counting in order
    // to minimize object size.
    EE_DECLARE_CLASS(IReplicationGroupPolicyData, efd::kCLASSID_IReplicationGroupPolicyData);
    /// @endcond

public:
    // virtual destructor
    virtual ~IReplicationGroupPolicyData();

protected:
    // Protected constructor. You must create a derived instance to use this class.
    IReplicationGroupPolicyData() {}
};

} // end namespace eon

#include <eon/IReplicationGroupPolicy.inl>

#endif // EE_IREPLICATIONGROUPPOLICY_H
