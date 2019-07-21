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
#ifndef EE_UNIVERSALID_H
#define EE_UNIVERSALID_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/utf8string.h>
#include <efd/BitUtils.h>


namespace efd
{
// Forward declaration
class Archive;

/**
    A class that encapsulates a unique ID.

    Universal IDs are 64-bit identifiers segmented into specific bit fields.  The ID is composed
    of several distinct fields which are hierarchically defined for several specific end uses.
    These fields are described below.

    System : 1 - 1==defined by Emergent, 0==not.  Half the namespace is available to end users.

    IsCategory : 1 - Must be 1 if it is valid to use this ID with subscribe, unsubscribe, or send.
    Category -  = 1
    Entity -    = 1
    EventID -   = 0

    IsWidelyUnique : 1 - Combined with IsCategory this uniquely distinguishes Category, Event,
        and Entity IDs
    Category -  = 0
    Entity -    = 1
    EventID -   = 1

    if this ID represents a CategoryId (IsCategory=1):
        Many-to-1 : 1 - 1==single subscriber, 0 ==multiple subscribers
        1-to-Many : 1 - 1==single producer, 0==multiple producers

        netid : 10 - optional portion set to the processes NetId.

    If this ID is widely unique across processes (IsWidelyUnique=1):
        netid : 10 - 0==temporary entity, cannot migrate or subscribe to events.
                    !0==what process originally created entity (might have since migrated)
      shardid : 10 - 0==temporary entity, cannot be persisted. !0==what shard created the entity

    If both a CategoryID and widely unique:
        1-to-Many : 1 - must be 0, many people can send me messages
        Many-to-1 : 1 - must be 1, only I subscribe to the private channel which is my entity ID

    netid : 10 - 0==temporary entity, cannot migrate or subscribe to events.
                !0==what process originally created entity (might have since migrated)

    shardid : 10 - 0==temporary entity, cannot be persisted. !0==what shard created the entity

    baseid : * - The remainder of the 64-bit namespace representing unique portion of the ID.
*/
class EE_EFD_ENTRY UniversalID
{
public:

    /// @name Construction and Destruction
    //@{

    /// Constructor
    inline UniversalID();

    /// Constructor taking a UInt64
    inline UniversalID(efd::UInt64 entityID);

    /// Copy Constructor
    inline UniversalID(const UniversalID& entityID);

    //@}

    /// Assignment operator taking a UInt64
    inline UniversalID& operator=(const efd::UInt64& other);

    /// Assignment operator taking an EntityID
    inline UniversalID& operator=(const UniversalID& other);

    /// Equality operator
    inline bool operator==(const UniversalID& other) const;

    /// Inequality operator
    inline bool operator!=(const UniversalID& other) const;

    /// Greater Than operator.  To support usage as the key in an efd::map.
    inline bool operator<(const UniversalID& rhs) const;

    /// Less Than operator.
    inline bool operator>(const UniversalID &lhs) const;

    /// Tests if the Id contains a valid (i.e. non-zero) value.
    inline bool IsValid() const;

    /// logical not operator.  Tests if the value is zero.
    inline bool operator!() const;

    /**
        Gets the numeric representation of this entity ID.

        @return A UInt64 representing the value of the entity ID
    */
    inline efd::UInt64 GetValue() const;


    /**
        Creates a "pretty" format string splitting out the different components of the ID.

        Handy for logging.

        @return The string
    */
    efd::utf8string ToString() const;


    /**
        Gets the numeric representation of the reserved bits in the ID

        @return Bool The value of the system bit.
    */
    inline efd::Bool GetSystem() const;

    /**
        Sets the numeric representation of the reserved bits in the ID.  The value will
        be ignored if it is outside of the valid range.

        @return bool true
    */
    inline efd::Bool SetSystem(efd::Bool i_system);


    /// NOTE: these are assigned specific and important values.  Both ChannelID and EntityID need
    ///     the second bit set high and both EventID and EntityID need the first bit high.
    enum IdType
    {
        kIDT_UnknownType = 0,
        kIDT_EventID     = 1,
        kIDT_ChannelID   = 2,
        kIDT_EntityID    = 3,
    };

    /**
        Gets the type bits from the ID.

        Only valid if GetSystem is true.

        @return IdType The value of the type bits.
    */
    IdType GetType() const;

    /**
        Sets the numeric representation of the type bits in the ID.

        The value will be ignored if it is outside of the valid range.

        @return bool true
    */
    efd::Bool SetType(IdType i_type);


    /// A hint suggested how the channel will be used.  This is only a hint and does not prevent
    /// other usage, but it can be used as a debugging aid to find potentially incorrect usage.
    enum ExpectedChannelUsage
    {
        ECU_Any            = 0, /// Many subscribers, many producers
        ECU_EventChannel   = 1, /// Many subscribers, one producer
        ECU_PrivateChannel = 2, /// One subscriber, many producers
        ECU_Point2Point    = 3, /// One subscriber, one producer
    };

    /**
        Gets the bits from the ID.

        Only valid if GetSystem is true and GetType is either ChannelID or EntityID.

        @return ChannelUsage The value of the usage bits.
    */
    ExpectedChannelUsage GetUsage() const;

    /**
        Sets the usage bits.

        @return bool true if the input is valid
    */
    efd::Bool SetUsage(ExpectedChannelUsage i_type);


    /**
        Gets the numeric representation of the shard bits in the ID.

        Only valid if GetSystem is true and GetType is either EventID or EntityID.

        @return UInt32 the value of the Shard ID that created this ID
    */
    efd::UInt32 GetShardID() const;

    /**
        Sets the numeric representation of the shard bits in the ID.

        The value will be ignored if it is outside the valid range.  You must set the System and
        Type values before you set the ShardID as the location of the ShardID bits varies.

        @return bool true if the input value is in range, false otherwise
    */
    efd::Bool SetShardID(efd::UInt32);


    /**
        Gets the numeric representation of the NetID bits in the ID.

        Only valid if GetSystem is true and GetType is either ChannelID, EventID or EntityID.

        @return UInt32 the value of the Net ID that created this ID
    */
    efd::UInt32 GetNetID() const;

    /**
        Sets the numeric representation of the NetID bits in the ID.

        The value will be ignored if it is outside of the valid range.  You must set the System
        and Type values before you set the NetID as the location of the NetID bits varies.

        @return bool true if the input value is in range, false otherwise
    */
    efd::Bool SetNetID(efd::UInt32 i_netID);


    /**
        Gets the numeric representation of the base bits in the ID.

        The number of bits fetched depends on the System and Type values.

        @return UInt64 the value of the base ID without the extra info baked in
    */
    efd::UInt64 GetBaseID() const;

    /**
        Sets the numeric representation of the base bits in the ID.

        The value will be ignored if it is outside of the valid range.

        @return bool true if the input value is in range, false otherwise
    */
    efd::Bool SetBaseID(efd::UInt64 i_base);

    /// Serialization
    void Serialize(efd::Archive& ar);

protected:
    static const efd::UInt32 kTotalUIDBits = 64;
    static const efd::UInt32 kNumSystemBits = 1;
    static const efd::UInt32 kNumTypeBits = 2;
    static const efd::UInt32 kNumUsageBits = 2;
    static const efd::UInt32 kNumShardBits = 10;
    static const efd::UInt32 kNumServerNetBits = 12;
    static const efd::UInt32 kNumNetBits = 32;

    static const efd::UInt32 kNumChannelBaseBits = (kTotalUIDBits - kNumNetBits - kNumUsageBits -
        kNumTypeBits - kNumSystemBits);
    static const efd::UInt32 kNumEntityBaseBits = (kTotalUIDBits - kNumServerNetBits -
        kNumShardBits - kNumUsageBits - kNumTypeBits - kNumSystemBits);
    static const efd::UInt32 kNumEventBaseBits = (kTotalUIDBits - kNumNetBits - kNumShardBits -
        kNumTypeBits - kNumSystemBits);
    static const efd::UInt32 kNumUserDefinedBaseBits = (kTotalUIDBits - kNumSystemBits);
    static const efd::UInt32 kNumUnknownTypeBaseBits = (kTotalUIDBits - kNumTypeBits -
        kNumSystemBits);

    // structs are platform specific and so are defined in platform specific header files instead
    // of here.  As the structs are members of this class, the platform specific header file is
    // included here instead of at the top of the file.
    #if defined (EE_PLATFORM_WIN32)
    #include <efd/Win32/UniversalID_Win32.h>
    #elif defined (EE_PLATFORM_XBOX360)
    #include <efd/XBox360/UniversalID_XBox360.h>
    #elif defined (EE_PLATFORM_PS3)
    #include <efd/PS3/UniversalID_PS3.h>
    #elif defined (EE_PLATFORM_LINUX)
    #include <efd/Linux/UniversalID_Linux.h>
    #endif

// Swig does not compile with EE_COMPILETIME_ASSERT.
#if !defined(SWIG)
    EE_COMPILETIME_ASSERT(sizeof(ChannelID) == sizeof(efd::UInt64));
    EE_COMPILETIME_ASSERT(sizeof(EntityID) == sizeof(efd::UInt64));
    EE_COMPILETIME_ASSERT(sizeof(EventID) == sizeof(efd::UInt64));
    EE_COMPILETIME_ASSERT(sizeof(UserDefinedID) == sizeof(efd::UInt64));
    EE_COMPILETIME_ASSERT(sizeof(UnknownTypeID) == sizeof(efd::UInt64));
    EE_COMPILETIME_ASSERT(sizeof(InternalMasks) == sizeof(efd::UInt64));
#endif //SWIG
};

} // end namespace efd


//--------------------------------------------------------------------------------------------------
// inline file
#include <efd/UniversalID.inl>

#endif // EE_UNIVERSALID_H
