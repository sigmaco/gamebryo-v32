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


// NOTE: all values in the following structure must be declared as "efd::UInt64" or
// else MSVC gets dreadfully confused and packs them all wrong.  GCC can handle mixing
// 64, 32, and boolean types into a single tightly packed bitfield but MSVC will align
// each differently sized type into separate fields (all bools in one 32 bit section, all
// ints into a separate 32 bit section, and all long longs into a separate 64 bit section).
// NOTE: the order of declaration is Least Significant to Most Significant.

/// Definition of a Channel Identifier.
struct ChannelID
{
    efd::UInt64 base      : kNumChannelBaseBits;
    efd::UInt64 net       : kNumNetBits;
    efd::UInt64 usage     : kNumUsageBits;
    efd::UInt64 type      : kNumTypeBits;
    efd::UInt64 system    : kNumSystemBits;
};

/// Definition of an Entity Identifier.
struct EntityID
{
    efd::UInt64 base      : kNumEntityBaseBits;
    efd::UInt64 net       : kNumServerNetBits;
    efd::UInt64 shard     : kNumShardBits;
    efd::UInt64 usage     : kNumUsageBits;
    efd::UInt64 type      : kNumTypeBits;
    efd::UInt64 system    : kNumSystemBits;
};

/// Definition of an Event identifier.
struct EventID
{
    efd::UInt64 base      : kNumEventBaseBits;
    efd::UInt64 net       : kNumNetBits;
    efd::UInt64 shard     : kNumShardBits;
    efd::UInt64 type      : kNumTypeBits;
    efd::UInt64 system    : kNumSystemBits;
};

/// A user defined identifier. This is a helper to assist in masking other identifiers.
struct UserDefinedID
{
    efd::UInt64 base      : kNumUserDefinedBaseBits;
    efd::UInt64 system    : kNumSystemBits;
};

/// An unknown type identifier. This is a helper to assist in masking other identifiers.
struct UnknownTypeID
{
    efd::UInt64 base      : kNumUnknownTypeBaseBits;
    efd::UInt64 type      : kNumTypeBits;
    efd::UInt64 system    : kNumSystemBits;
};

/// Special identifier masks to indicate the relationship between sender and receiver.
struct InternalMasks
{
    efd::UInt64               : (kTotalUIDBits - kNumUsageBits - kNumTypeBits - kNumSystemBits);
    efd::UInt64 isOneToMany   : 1;
    efd::UInt64 isManyToOne   : 1;
    efd::UInt64 isUnique      : 1;
    efd::UInt64 isCategory    : 1;
    efd::UInt64               : kNumSystemBits;
};

#define UID_GET_VALUE(type, member) (m_##type.member)
#define UID_SET_VALUE(type, member, value) m_##type.member = value

union
{
    // the actual ID
    efd::UInt64 m_uid;

    // We know all three sub-types we might actually be:
    ChannelID m_ChannelID;
    EntityID m_EntityID;
    EventID m_EventID;

    // We also know several helper types for fetching ranges of values
    UserDefinedID m_UserDefinedID;
    UnknownTypeID m_UnknownTypeID;
    InternalMasks m_InternalMasks;
};

