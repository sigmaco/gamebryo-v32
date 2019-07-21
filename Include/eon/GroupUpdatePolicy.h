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
#ifndef EE_GROUPUPDATEPOLICY_H
#define EE_GROUPUPDATEPOLICY_H

#include <eon/OnlineEntry.h>
#include <eon/IReplicationGroupPolicy.h>

namespace eon
{

class EE_EONENTRY GroupUpdatePolicy : public IReplicationGroupPolicy
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(GroupUpdatePolicy, efd::kCLASSID_GroupUpdatePolicy, IReplicationGroupPolicy);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /** 
        Constructor
    */
    GroupUpdatePolicy();

    ///Virtual Destructor
    virtual ~GroupUpdatePolicy();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void GenerateDiscovery(
        const efd::ServiceManager* pServiceManager,
        ReplicationProducerEntity* pEntity,
        efd::UInt32 groupIndex);
    virtual void GenerateUpdate(
        const efd::ServiceManager* pServiceManager,
        ReplicationProducerEntity* pEntity,
        efd::UInt32 groupIndex);
    virtual void GenerateLoss(
        const efd::ServiceManager* pServiceManager,
        ReplicationProducerEntity* pEntity,
        efd::UInt32 groupIndex,
        efd::Category oldCategory,
        efd::Category newCategory);
    virtual void GenerateP2PDiscovery(
        const efd::ServiceManager* pServiceManager,
        ReplicationProducerEntity* pEntity,
        efd::UInt32 groupIndex,
        efd::Category callbackChannel,
        efd::QualityOfService qos);

protected:
    class GroupUpdatePolicyData : public IReplicationGroupPolicyData
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(
            GroupUpdatePolicyData,
            efd::kCLASSID_GroupUpdatePolicyData,
            IReplicationGroupPolicyData);
        /// @endcond

    public:
        GroupUpdatePolicyData();
        efd::TimeType m_lastUpdate;
    };

    GroupUpdatePolicyData& GetPolicyData(
        ReplicationProducerEntity* pEntity,
        efd::UInt32 groupIndex);
};

} // end namespace eon

#endif // EE_GROUPUPDATEPOLICY_H
