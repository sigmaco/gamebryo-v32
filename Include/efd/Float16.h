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
#ifndef EE_FLOAT16_H
#define EE_FLOAT16_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>

namespace efd
{

#define FLOAT16_MAX 65504.0f
#define FLOAT16_MIN 6.1035156e-5f

/**
    A platform-independent class designed to support 2 byte half-floats.
    The code is based off of ILM's half class and the licensing information
    for this class can be found in both the source and in the Third Party
    Code section of the Gamebryo documentation. The Float16  implementation
    uses 1 bit for sign, 5 bits for exponent, and 10 bits for the mantissa.
    The class is designed to operate similarly to the built-in C++ IEEE 754
    single-precision floating point type in terms of performing arithmetic
    expressions and inter-operations with floats and doubles.

    The Float16 class can represent positive and negative numbers whose
    magnitude is between roughly 6.1e-5 and 6.5e+4 with a relative error of
    9.8e-4. Numbers that are smaller than 6.1e-5 can be represented with an
    absolute error of 6.0e-8. Finally, all integers from -2048 to +2048 can
    be represented exactly.

*/

// Entirely inline. Does not need EE_EFD_ENTRY
class Float16
{
public:
    /// @name Constructors
    //@{

    /**
        The default constructor provides no initialization.
    */
    inline Float16();

    /// Copy constructor
    inline Float16(const Float16& f);

    /**
        Initializes the Float16 object with the value provided.
        Note that overflow is possible.
    */
    inline Float16(efd::Float32 f);

    //@}

    /// @name Member Functions
    //@{
    inline void Set(efd::Float32 f);

    inline efd::Float32 Get() const;

    inline UInt16 GetData() const;

    //@}
    /// @name Operators
    //@{

    //--------------------
    // Conversion to float
    //--------------------
    /// Conversion to standard 32 bit float
    inline operator float () const;

    //------------
    // Unary minus
    //------------
    /// The subtraction operator.
    inline Float16 operator - () const;

    //-----------
    // Assignment
    //-----------
    /// The supported assignment operations.
    inline Float16& operator = (Float16 f);
    /// The supported assignment operations.
    inline Float16& operator = (efd::Float32 f);

    /// The supported increment operations.
    inline Float16& operator += (Float16 f);
    /// The supported increment operations.
    inline Float16& operator += (efd::Float32 f);

    /// The supported decrement operations.
    inline Float16& operator -= (Float16 f);
    /// The supported decrement operations.
    inline Float16& operator -= (efd::Float32 f);

    /// The supported in-place scaling operations.
    inline Float16& operator *= (Float16 f);
    /// The supported in-place scaling operations.
    inline Float16& operator *= (efd::Float32 f);

    /// The supported in-place scalar division operations.
    inline Float16& operator /= (Float16 f);
    /// The supported in-place scalar division operations.
    inline Float16& operator /= (efd::Float32 f);

    //------------
    // Equality
    //------------
    /// The supported comparison operators.
    inline bool operator == (Float16 f) const;
    /// The supported comparison operators.
    inline bool operator == (efd::Float32 f) const;
    /// The supported comparison operators.
    inline bool operator == (const efd::Float64& d) const;

    /// The supported comparison operators.
    inline bool operator != (Float16 f) const;
    /// The supported comparison operators.
    inline bool operator != (efd::Float32 f) const;
    /// The supported comparison operators.
    inline bool operator != (const efd::Float64& d) const;
    //@}

private:
    efd::UInt16 m_uiData;
};

} // end namespace efd

#include <efd/Float16.inl>

#endif // EE_FLOAT16_H
