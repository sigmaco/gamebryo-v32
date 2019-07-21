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
#ifndef EE_ENTITYID_H
#define EE_ENTITYID_H

#include <efd/UniversalID.h>
#include <efdNetwork/NetCategory.h>
#include <egf/egfLibType.h>
#include <efd/ParseHelper.h>
#include <efd/Serialize.h>



namespace egf
{

/**
    A class that encapsulates a unique entity ID.
*/
class EntityID
    : protected efd::UniversalID
{
public:
    /// invalid entity id
    static const efd::UInt64 kENTITY_INVALID = 0ull;

    /// @name Construction
    //@{

    /// Constructor.
    inline EntityID();

    /// Constructor taking a UInt64.
    inline EntityID(efd::UInt64 entityID);

    /// Copy Constructor.
    inline EntityID(const EntityID& entityID);

    /// Entities are a special case of Category some we can turn certain categories into EntityIDs.
    /// This will assert if the category used is not actually an entity ID.
    inline EntityID(const efd::Category& entityID);

    /**
        Constructor to build an entity ID from its base parts.

        @param i_ShardID The numeric representation of the shard bits in the ID.
        @param i_netID The numeric representation of the NetID bits in the ID.
        @param i_baseid The numeric representation of the base bits in the ID.
    */
    inline EntityID(efd::UInt32 i_ShardID, efd::UInt32 i_netID, efd::UInt64 i_baseid);

    //@}

    /// Assignment operator taking a UInt64
    inline EntityID& operator=(const efd::UInt64& other);

    /// Assignment operator taking an EntityID
    inline EntityID& operator=(const EntityID& other);

    /// Any EntityID is really a special case of a Category so we support conversion.  This will
    /// assert if the category provided isn't actually an EntityID
    inline EntityID& operator=(const efd::Category& other);

    /// EntityIDs are a special kind of category ID, so we allow implicit casting to a Category
    inline operator efd::Category() const;

    /// @name UniversalID members and overrides
    //@{

    /// Some members of UniversalID are simply directly exposed:
    using efd::UniversalID::operator!;
    using efd::UniversalID::IsValid;
    using efd::UniversalID::GetValue;
    using efd::UniversalID::GetSystem;   // Can get this for verification, but can't set it
    using efd::UniversalID::GetType;     // Can get this for verification, but can't set it
    using efd::UniversalID::GetUsage;    // Can get this for verification, but can't set it
    using efd::UniversalID::Serialize;

    /// @note We don't want to be able to compare different types of IDs, we only share UniversalID
    /// so that we have a single place to put all the bit fields we use.
    inline bool operator==(const EntityID& rhs) const;
    inline bool operator!=(const EntityID& rhs) const;
    inline bool operator>(const EntityID& rhs) const;
    inline bool operator<(const EntityID& rhs) const;

    // Other members we override with Category specific implementations that still use the
    // bit fields defined in UniversalID

    /**
        Gets the numeric representation of the shard bits in the ID.

        @return efd::UInt32 The value of the Shard ID that created this ID
    */
    inline efd::UInt32 GetShardID() const;

    /**
        Sets the numeric representation of the shard bits in the ID.  The value will be ignored
        if it is outside of the valid range.

        @param i_shard The efd::UInt32 for the shardID
        @return true if the input value is in range, false otherwise
    */
    inline efd::Bool SetShardID(efd::UInt32 i_shard);

    /**
        Gets the numeric representation of the NetID bits in the ID.

        @return efd::UInt32 The value of the Net ID that created this ID.
    */
    inline efd::UInt32 GetNetID() const;

    /**
        Sets the numeric representation of the NetID bits in the ID.  The value will be ignored
        if it is outside of the valid range.

        @param[in] i_netID The netID to store.
        @return efd::Bool true if the input value is in range, false otherwise.
    */
    inline efd::Bool SetNetID(efd::UInt32 i_netID);


    /**
        Gets the numeric representation of the base bits in the ID.

        @return efd::UInt64 The value of the base ID without the extra info baked in.
    */
    inline efd::UInt64 GetBaseID() const;

    /**
        Sets the numeric representation of the base bits in the ID.  The value will
        be ignored if it is outside of the valid range.

        @param i_base The numeric representation of the base bits in the ID.
        @return efd::Bool true if the input value is in range, false otherwise.
    */
    inline efd::Bool SetBaseID(efd::UInt64 i_base);

    /**
        Creates a "pretty" format string splitting out the different components.
        of the entity ID.  Handy for logging.

        @return The string.
    */
    inline efd::utf8string ToString() const;
    //@}

    /// Serialize method for using EntityID with Archive or ParameterList
    inline void Serialize(efd::Archive& io_archive);

    /**
        Creates an EntityID from id, then calls EntityID::ToString().

        @param[in] id The id to convert to a string.
        @return efd::utf8string of the EntityID.
    */
    static inline efd::utf8string IDToString(efd::UInt64 id);


    /**
        Check if a given UInt64 is valid as an potential EntityID

        @param[in] id The id to check.
        @return bool of the EntityID.
    */
    static efd::Bool IsValidEntityID(efd::UInt64 id);
};

static const EntityID kENTITY_INVALID = EntityID::kENTITY_INVALID;

} // end namespace egf


//------------------------------------------------------------------------------------------------
namespace efd
{

template<>
struct ParseHelper<egf::EntityID>
{
    static bool FromString(const efd::utf8string& i_value, egf::EntityID& o_result);
    static bool ToString(egf::EntityID i_value, efd::utf8string& o_result);
    static const char* GetNameOfType() { return "egf::EntityID"; }
};

} // end namespace efd


//------------------------------------------------------------------------------------------------
// inline file
#include "EntityID.inl"


//------------------------------------------------------------------------------------------------
#endif ///EE_ENTITYID_H
