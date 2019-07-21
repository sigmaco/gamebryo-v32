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
inline efd::QualityOfService IReplicationGroupPolicy::GetQualityOfService() const
{
    return m_messageQuality;
}

//-------------------------------------------------------------------------------------------------
inline void IReplicationGroupPolicy::SetQualityOfService(efd::QualityOfService qos)
{
    m_messageQuality = qos;
}

//------------------------------------------------------------------------------------------------
inline efd::TimeType IReplicationGroupPolicy::GetMinUpdateDelta()
{
    return m_minUpdateDelta;
}

//------------------------------------------------------------------------------------------------
inline void IReplicationGroupPolicy::SetMinUpdateDelta(efd::TimeType minDelta)
{
    m_minUpdateDelta = minDelta;
}

//------------------------------------------------------------------------------------------------
inline bool IReplicationGroupPolicy::GetUpdateAll() const
{
    return m_updateAll;
}

//------------------------------------------------------------------------------------------------
inline void IReplicationGroupPolicy::SetUpdateAll(bool updateAll)
{
    m_updateAll = updateAll;
}

//------------------------------------------------------------------------------------------------
inline bool IReplicationGroupPolicy::GetTreatUpdatesAsDiscovers() const
{
    return m_treatUpdatesAsDiscovers;
}

//------------------------------------------------------------------------------------------------
inline void IReplicationGroupPolicy::SetTreatUpdatesAsDiscovers(bool b)
{
    m_treatUpdatesAsDiscovers = b;
}

//-------------------------------------------------------------------------------------------------
inline IReplicationGroupPolicy* IReplicationGroupPolicy::GetReplicationGroupPolicy(
    efd::UInt32 groupIndex)
{
    EE_ASSERT(groupIndex < k_MAX_REPLICATION_GROUPS);
    return m_groups[groupIndex];
}

//-------------------------------------------------------------------------------------------------
inline void IReplicationGroupPolicy::SetReplicationGroupPolicy(
    efd::UInt32 groupIndex,
    IReplicationGroupPolicy* pGroupUpdatePolicy)
{
    EE_ASSERT(groupIndex < k_MAX_REPLICATION_GROUPS);
    m_groups[groupIndex] = pGroupUpdatePolicy;
}

//-------------------------------------------------------------------------------------------------
} // end namespace eon
