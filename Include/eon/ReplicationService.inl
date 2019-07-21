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

namespace eon
{

//-------------------------------------------------------------------------------------------------
const char* ReplicationService::GetDisplayName() const
{
    return "ReplicationService";
}

//-------------------------------------------------------------------------------------------------
ReplicatingEntity* ReplicationService::FindEntity(const egf::EntityID& id) const
{
    EE_ASSERT(m_spEntityManager);
    return EE_DYNAMIC_CAST(ReplicatingEntity, m_spEntityManager->LookupEntity(id));
}

//-------------------------------------------------------------------------------------------------
ReplicationProducerEntity* ReplicationService::FindProducerEntity(
    const egf::EntityID& id) const
{
    EE_ASSERT(m_spEntityManager);
    return EE_DYNAMIC_CAST(ReplicationProducerEntity, m_spEntityManager->LookupEntity(id));
}

//-------------------------------------------------------------------------------------------------
ReplicationConsumerEntity* ReplicationService::FindConsumerEntity(
    const egf::EntityID& id) const
{
    EE_ASSERT(m_spEntityManager);
    return EE_DYNAMIC_CAST(ReplicationConsumerEntity, m_spEntityManager->LookupEntity(id));
}

//-------------------------------------------------------------------------------------------------
egf::EntityManager::EntityMap::const_iterator ReplicationService::GetFirstEntityPos() const
{
    EE_ASSERT(m_spEntityManager);
    return m_spEntityManager->GetFirstEntityPos();
}

} // end namespace eon
