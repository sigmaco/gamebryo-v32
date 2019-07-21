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
#ifndef EE_ID128_H
#define EE_ID128_H

#include <efd/UniversalTypes.h>
#include <efd/RTLib.h>

namespace efd
{
class Archive;


/**
    Container class for a 128 bit ID.

    Providing only minimal functionality, this class originally came from
    the NiUniqueID class in the NiEntity library in Gamebryo.
*/
class EE_EFD_ENTRY ID128
{
public:
    /// Construct with zeroed value
    ID128();

    /// Construct by copying from an array of bytes
    ID128(const efd::UInt8* pCharID);

    /// Construct by specifying each byte
    ID128(
        efd::UInt8 b01,
        efd::UInt8 b02,
        efd::UInt8 b03,
        efd::UInt8 b04,
        efd::UInt8 b05,
        efd::UInt8 b06,
        efd::UInt8 b07,
        efd::UInt8 b08,
        efd::UInt8 b09,
        efd::UInt8 b10,
        efd::UInt8 b11,
        efd::UInt8 b12,
        efd::UInt8 b13,
        efd::UInt8 b14,
        efd::UInt8 b15,
        efd::UInt8 b16);

    /// Comparison ==
    bool operator==(const ID128& uniqueID) const;

    /// Comparison !=
    bool operator!=(const ID128& uniqueID) const;

    /// Comparison <
    bool operator<(const ID128& rhs) const;

    /// Comparison >
    bool operator>(const ID128& rhs) const;

    /// returns true if the value is non-zero
    bool IsValid() const;

    /**
        Generates a 128bit UUID using the algorithm (version 4, using pseudo-random numbers)
        specified in RFC4122.
    */
    static efd::ID128 GenUUID();

    /// Serialization
    void Serialize(efd::Archive& ar);

    efd::UInt8 m_value[16];
};

} // end namespace efd

#include <efd/ID128.inl>

#endif

