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

namespace egf
{

//------------------------------------------------------------------------------------------------
inline EntityID::EntityID()
: UniversalID()
{
    UID_SET_VALUE(EntityID, system, 1);
    UID_SET_VALUE(EntityID, type, kIDT_EntityID);
    UID_SET_VALUE(EntityID, usage, ECU_PrivateChannel);
}

//------------------------------------------------------------------------------------------------
inline EntityID::EntityID(efd::UInt64 entityID)
: UniversalID(entityID)
{
    EE_ASSERT(!IsValid() || GetSystem());
    EE_ASSERT(!IsValid() || kIDT_EntityID == GetType());
    EE_ASSERT(!IsValid() || ECU_PrivateChannel == GetUsage());
}

//------------------------------------------------------------------------------------------------
inline EntityID::EntityID(const EntityID& entityID)
: UniversalID(entityID)
{
    EE_ASSERT(!IsValid() || GetSystem());
    EE_ASSERT(!IsValid() || kIDT_EntityID == GetType());
    EE_ASSERT(!IsValid() || ECU_PrivateChannel == GetUsage());
}

//------------------------------------------------------------------------------------------------
inline EntityID::EntityID(const efd::Category& category)
: UniversalID(category.GetValue())
{
    EE_ASSERT(!IsValid() || GetSystem());
    EE_ASSERT(!IsValid() || kIDT_EntityID == GetType());
    EE_ASSERT(!IsValid() || ECU_PrivateChannel == GetUsage());
}

//------------------------------------------------------------------------------------------------
inline EntityID::EntityID(efd::UInt32 i_ShardID, efd::UInt32 i_netID, efd::UInt64 i_baseid)
: UniversalID()
{
    UID_SET_VALUE(EntityID, system, 1);
    UID_SET_VALUE(EntityID, type, kIDT_EntityID);
    UID_SET_VALUE(EntityID, usage, ECU_PrivateChannel);
    UID_SET_VALUE(EntityID, shard, i_ShardID);
    UID_SET_VALUE(EntityID, net, i_netID);
    UID_SET_VALUE(EntityID, base, i_baseid);
}

//------------------------------------------------------------------------------------------------
inline EntityID& EntityID::operator=(const efd::UInt64& other)
{
    UniversalID::operator=(other);
    EE_ASSERT(!IsValid() || GetSystem());
    EE_ASSERT(!IsValid() || kIDT_EntityID == GetType());
    EE_ASSERT(!IsValid() || ECU_PrivateChannel == GetUsage());
    return *this;
}

//------------------------------------------------------------------------------------------------
inline EntityID& EntityID::operator=(const EntityID& other)
{
    UniversalID::operator=(other);
    EE_ASSERT(!IsValid() || GetSystem());
    EE_ASSERT(!IsValid() || kIDT_EntityID == GetType());
    EE_ASSERT(!IsValid() || ECU_PrivateChannel == GetUsage());
    return *this;
}

//------------------------------------------------------------------------------------------------
inline bool EntityID::operator==(const EntityID& other) const
{
    return m_uid == other.m_uid;
}

//------------------------------------------------------------------------------------------------
inline bool EntityID::operator!=(const EntityID& other) const
{
    return m_uid != other.m_uid;
}

//------------------------------------------------------------------------------------------------
inline bool EntityID::operator<(const EntityID& rhs) const
{
    return m_uid < rhs.m_uid;
}

//------------------------------------------------------------------------------------------------
inline bool EntityID::operator>(const EntityID &lhs) const
{
    return m_uid > lhs.m_uid;
}

//------------------------------------------------------------------------------------------------
inline EntityID::operator efd::Category() const
{
    return efd::Category(GetValue());
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string EntityID::ToString() const
{
    efd::utf8string str(efd::Formatted, "<EntityID=(0x%016llX)>", m_uid);
    return str;
}

//------------------------------------------------------------------------------------------------
/* static */
inline efd::utf8string EntityID::IDToString(efd::UInt64 i_id)
{
    EntityID eid(i_id);
    return eid.ToString();
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 EntityID::GetShardID() const
{
    EE_ASSERT(!IsValid() || GetSystem());
    EE_ASSERT(!IsValid() || kIDT_EntityID == GetType());
    EE_ASSERT(!IsValid() || ECU_PrivateChannel == GetUsage());
    return UID_GET_VALUE(EntityID, shard);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool EntityID::SetShardID(efd::UInt32 i_shard)
{
    if (i_shard > efd::BitUtils::MakeBitMask<efd::UInt32, kNumShardBits, 0>())
    {
        EE_FAIL_MESSAGE((
            "ID Error: Shard value (%d) exceeds available space for shard ID bits (%d).",
            i_shard, kNumShardBits));
        return false;
    }

    UID_SET_VALUE(EntityID, shard, i_shard);
    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 EntityID::GetNetID() const
{
    EE_ASSERT(!IsValid() || GetSystem());
    EE_ASSERT(!IsValid() || kIDT_EntityID == GetType());
    EE_ASSERT(!IsValid() || ECU_PrivateChannel == GetUsage());
    return UID_GET_VALUE(EntityID, net);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool EntityID::SetNetID(efd::UInt32 i_netID)
{
    if (i_netID > efd::BitUtils::MakeBitMask<efd::UInt32, kNumNetBits, 0>())
    {
        EE_FAIL_MESSAGE((
            "EntityID Error: Net value (%d) exceeds available space for net ID bits (%d).",
            i_netID, kNumNetBits));
        return false;
    }

    UID_SET_VALUE(EntityID, net, i_netID);
    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt64 EntityID::GetBaseID() const
{
    EE_ASSERT(!IsValid() || GetSystem());
    EE_ASSERT(!IsValid() || kIDT_EntityID == GetType());
    EE_ASSERT(!IsValid() || ECU_PrivateChannel == GetUsage());
    return UID_GET_VALUE(EntityID, base);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool EntityID::SetBaseID(efd::UInt64 i_base)
{
    if (i_base > efd::BitUtils::MakeBitMask<efd::UInt64, kNumEntityBaseBits, 0>())
    {
        EE_FAIL_MESSAGE((
            "EntityID Error: Base value (0x%016llX) exceeds available space for base bits (%d).",
            i_base, kNumEntityBaseBits));
        return false;
    }

    UID_SET_VALUE(EntityID, base, i_base);
    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool EntityID::IsValidEntityID(efd::UInt64 id)
{
    // Check if an EntityID is valid before calling the construtor:
    // EntityID::EntityID(efd::UInt64 entityID)
    // This was done stricly to get rid of the asserts that are in the constructor.

    EntityID entityID;
    entityID.m_uid = id;
    return entityID.GetSystem() &&
        kIDT_EntityID == entityID.GetType() &&
        ECU_PrivateChannel == entityID.GetUsage();
}

//------------------------------------------------------------------------------------------------
inline void EntityID::Serialize(efd::Archive& io_archive)
{
    efd::Serializer::SerializeObject(m_uid, io_archive);
}

//------------------------------------------------------------------------------------------------
} // end namespace egf


//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<egf::EntityID>::FromString(
    const efd::utf8string& i_value,
    egf::EntityID& o_result)
{
    const efd::Char* pEnd;
    efd::UInt64 temp = efd::strtoull(i_value.c_str(), &pEnd);

    // If successful, the entire string will have been consumed and thus pEnd will point
    // to the trailing NULL terminator.
    if (*pEnd == '\0')
    {
        // Only assign once we know its valid, EntityID asserts on invalid assignments.
        o_result = temp;
        return true;
    }
    o_result = egf::kENTITY_INVALID;
    return false;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<egf::EntityID>::ToString(
    egf::EntityID i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("0x%016llX", i_value.GetValue());
    return true;
}

