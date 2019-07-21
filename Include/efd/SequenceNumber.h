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
#ifndef EE_SEQUENCENUMBER_H
#define EE_SEQUENCENUMBER_H

#include <efd/Serialize.h>
#include <efd/TemplateHelpers.h>

namespace efd
{

/**
    Does a "wrap-around" comparison of two signed integer values.

    Zero is treated as a special "invalid" or "not set" value and is considered to be less than
    all non-zero values.

    @param lhs Left-hand side of comparison.
    @param rhs Right-hand side of comparison.
    @return -1 if lhs < rhs, 0 if lhs == rhs, and 1 if lhs > rhs.
 */
template<typename T> inline int SequenceCompare(T lhs, T rhs);

/**
    A sequence number is a number whose comparison function works such that the compared numbers
    "wrap around".

    In addition, zero is reserved as a special "unset" value.  Any non-zero number is
    both > and < zero.
 */
template<typename T = efd::SInt32> class SequenceNumber
{
public:
    /// @name Constructors.
    //@{
    inline SequenceNumber();
    inline SequenceNumber(const SequenceNumber& other);
    inline SequenceNumber(T other);
    //@}

    /// Access whether sequence number has been set.
    inline bool IsSet() const;

    /// Access sequence number value.
    inline T GetValue() const;

    /// @name Assignment operators.
    //@{
    inline void operator=(const SequenceNumber& other);
    inline void operator=(T other);
    //@}

    /// @name Comparison operators.
    //@{
    inline bool operator==(const SequenceNumber& other) const;
    inline bool operator!=(const SequenceNumber& other) const;
    inline bool operator>(const SequenceNumber& other) const;
    inline bool operator>=(const SequenceNumber& other) const;
    inline bool operator<(const SequenceNumber& other) const;
    inline bool operator<=(const SequenceNumber& other) const;
    //@}

    /// Sequence number increment operator.
    inline void operator++();

    /// Serialization
    inline void Serialize(efd::Archive& ar);

protected:
    /// Sequence number member data.
    T m_sequence;
};


/// @name Common types of sequence numbers
//@{
typedef SequenceNumber<efd::SInt8> SequenceNumber8;
typedef SequenceNumber<efd::SInt16> SequenceNumber16;
typedef SequenceNumber<efd::SInt32> SequenceNumber32;
typedef SequenceNumber<efd::SInt64> SequenceNumber64;
//@}

} // end namespace efd.

#include <efd/SequenceNumber.inl>

#endif  // EE_SEQUENCENUMBER_H
