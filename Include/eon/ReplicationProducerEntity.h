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
#ifndef EE_REPLICATIONPRODUCERENTITY_H
#define EE_REPLICATIONPRODUCERENTITY_H

#include <eon/ReplicatingEntity.h>
#include <eon/EntityMessage.h>
#include <eon/IReplicationGroupPolicy.h>

namespace eon
{

// Forward declarations:
class ReplicationService;

/**
    An owned entity that can generate replication updates in response to it's properties changing.
    This class is used for online applications that use the ReplicationService and the
    OnlineEntityManager.
*/
class EE_EONENTRY ReplicationProducerEntity : public ReplicatingEntity
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(
        ReplicationProducerEntity,
        efd::kCLASSID_ReplicationProducerEntity,
        ReplicatingEntity);

    /// @endcond

protected:
    // Only the factory method registered by the ReplicationService is allowed to create
    // this type of entity:
    friend class ReplicationService;

    /// Constructor
    ReplicationProducerEntity(const egf::FlatModel* i_pTemplate, egf::EntityID i_eid);

    /// Destructor
    ~ReplicationProducerEntity();

public:
    /**
        Sets the pointer to our active Replication Service.  The ReplicationService itself
        will call this method as needed.  This replication service will be used to send
        replication updates for Producer entities and will help with channel subscriptions
        and view behavior events for Consumer entities.

        This override will also generate initial discovery request messages in the event that
        any SetReplicationCategory calls where made prior to setting the ReplicationService.

        @param pRS pointer to a ReplicationService instance
    */
    virtual void SetReplicationService(class eon::ReplicationService* pRS);

    /**
        Set the category to which replication messages for the given group should be sent.
        If necessary, a Loss message will be sent to the previous replication channel and a
        Discovery message will be sent to the new category.  This method can be called at any
        time including before a newly created entity has been registered with the Scheduler.
    */
    bool SetReplicationCategory(efd::UInt32 groupIndex, efd::Category cat);

    /**
        Output this entity to a data stream.  Only the entity ID, flat model ID, plus the
        non-const properties of the entity which match the groupIndex are actually streamed.
        All const model values, plus property data that has not changed from the model will
        NOT be streamed out.

        @param i_groupIndex Which replication group is being used
        @param i_qos The QualityOfService to send the update message on
        @param i_pServiceManager a pointer to the ServiceManager.
        @param o_spEntityMessage A reference to a SmartPointer where the correct type of message
            will be allocated and populated.
        @param clearReplicationDirty If true dirtiness of this entity will be cleared after
            generating the discovery message.
    */
    efd::Category GenerateDiscovery(
        efd::UInt32 i_groupIndex,
        efd::QualityOfService& i_qos,
        efd::ServiceManager* i_pServiceManager,
        EntityMessagePtr& o_spEntityMessage,
        bool clearReplicationDirty);

    /**
        \brief Output this entity and dirty properties to a data stream.

        Only the entity ID, flat model ID, plus the DIRTY non-const parts of the entity are
        actually streamed.  All const model values, plus property data that IS NOT DIRTY will
        NOT be streamed out.
        @note: this is a version of the stream used for updating entities (as opposed to
        sending discovery with full embodiment)

        @param groupIndex Which replication group is being used
        @param qos The QualityOfService to send the update message on
        @param pServiceManager a pointer to the ServiceManager.
        @param spEntityMessage A reference to a SmartPointer where the correct type of message
            will be allocated and populated.
    */
    efd::Category GenerateUpdate(
        efd::UInt32 groupIndex,
        efd::QualityOfService& qos,
        efd::ServiceManager* pServiceManager,
        EntityMessagePtr& spEntityMessage);

    /**
        Output this entity ID to a data stream.  Only the entity ID
        is sent (no model or properties)!
        @note: this is a version of the entity stream used for the "loss"
        message (only need entity ID)

        @param groupIndex Which replication group is being used
        @param qos The QualityOfService to send the update message on
        @param pServiceManager a pointer to the ServiceManager.
        @param spEntityMessage A reference to a SmartPointer where the correct type of message
            will be allocated and populated.
        @param newCategory The new replication group category.
    */
    efd::Category GenerateLoss(
        efd::UInt32 groupIndex,
        efd::QualityOfService& qos,
        efd::ServiceManager* pServiceManager,
        EntityMessagePtr& spEntityMessage,
        efd::Category newCategory);

    /**
        This is the outgoing update sequence number. This number is incremented whenever a
        replication message is sent for this entity on any replication group. The number is used
        to ensure that old replication messages never override newer updates in the event that the
        replication messages arrive out of order. Messages can arrive out of order as a result of
        sending replication messages on an unordered quality of service or as result of using
        the same property in multiple replication groups.
    */
    efd::SequenceNumber32 GetSequenceNumber() const;

    /// Called during replication every time a replication message is sent out. This should not
    /// be called at any other time.
    void IncrementSequenceNumber();

    /**
        Get the IReplicationGroupPolicyData object for the specified group index for this entity.
        If there is no policy data set for the specified groupIndex this will return NULL.

        @param groupIndex Index of the property group to get the policy of.
        @return The IReplicationGroupPolicyData for the specified groupIndex.
    */
    IReplicationGroupPolicyData* GetReplicationGroupPolicyData(efd::UInt32 groupIndex);

    /**
        Set the IReplicationGroupPolicyData object for the specified group index of this entity.
        Once set the entity is responsible for deleting the policy data. You can delete previously
        set data by calling this method again with a NULL pPolicyData pointer.

        @param groupIndex Index of the property group to set the policy of
        @param pPolicyData The policy data to assign to the specified group index
    */
    void SetReplicationGroupPolicyData(
        efd::UInt32 groupIndex,
        IReplicationGroupPolicyData* pPolicyData);

    /**
        Write data describing the current entity into an EntityMessage instance.

        @param io_pEntityMessage Pointer to a message to be filled in
        @param i_groupIndex The replication group to describe
    */
    void WriteHeaderData(EntityMessage* io_pEntityMessage, efd::UInt32 i_groupIndex);

    /**
        Stream the values for all properties that replicate to the given group and have changed from
        the default value into the provided Archive. In the process, the dirtiness of those
        properties in the specified group is optionally cleared. The data is serialized in a format
        compatible with the ReplicationConsumerEntity::UpdatePropertiesFromStream method.

        @param[in,out] io_ar An Archive into which the properties are serialized
        @param[in] i_groupIndex The replication group to stream
        @param[in] i_clearReplicationDirty If true, dirtiness of the properties is cleared for the
            specified group when each property is streamed.
    */
    size_t StreamChangedProperties(
        efd::Archive& io_ar,
        efd::UInt32 i_groupIndex,
        bool i_clearReplicationDirty = true);

    /**
        Stream the values for all currently dirty properties that replicate to the given group into
        the provided data stream. In the process, the dirtiness of those properties in the specified
        group is optionally cleared. The data is streamed in a format compatible with the
        ReplicationConsumerEntity::UpdatePropertiesFromStream method.

        @param[in,out] io_ar An Archive into which the properties are serialized
        @param[in] i_groupIndex The replication group to stream
        @param[in] i_clearReplicationDirty If true, dirtiness of the properties is cleared for the
            specified group when each property is streamed.
    */
    size_t StreamDirtyProperties(
        efd::Archive& io_ar,
        efd::UInt32 i_groupIndex,
        bool i_clearReplicationDirty = true);

protected:
    /**
        Clears the replication dirtiness of all properties in the specified group.
        @param groupIndex The replication group index to clear dirtiness of.
    */
    virtual void ClearReplicationDirty(efd::UInt32 groupIndex);

    /**
        ReplicationProducerEntity overrides Entity::SetDirty to track per-property dirtiness for
        managing replication groups. This method is
    */
    virtual void SetDirty(egf::PropertyID propID, const egf::IProperty* prop);

    // Sequence number for the last update I sent.  This is only valid on master entities and
    // is not set on replications.
    efd::SequenceNumber32 m_lastUpdate;

    struct DirtyPropertyData
    {
        inline DirtyPropertyData(const egf::IProperty* pProp, efd::UInt32 dirtyMask);

        const egf::IProperty* m_pProp;
        efd::UInt32 m_dirtyMask;
    };
    typedef efd::map<egf::PropertyID, DirtyPropertyData> DirtyReplicationMap;
    DirtyReplicationMap m_dirtyPropertyMap;

    /// Storage for the run-time state for each in-use IReplicationGroupPolicy.
    typedef efd::map<efd::UInt32, IReplicationGroupPolicyData* > GroupUpdatePolicyData;
    GroupUpdatePolicyData m_groupPolicySettings;
};

/// SmartPointer for the ReplicationProducerEntity class
typedef efd::SmartPointer<ReplicationProducerEntity> ReplicationProducerEntityPtr;

} // end namespace eon

#include <eon/ReplicationProducerEntity.inl>

#endif // EE_REPLICATIONPRODUCERENTITY_H
