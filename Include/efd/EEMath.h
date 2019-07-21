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
#ifndef EE_MATH_H
#define EE_MATH_H

#include <efd/UniversalTypes.h>
#include <efd/efdLibType.h>

namespace efd
{

/// @name Math functions from  EEMath.h
//@{

#ifndef __SPU__
const efd::Float32 EE_INFINITY = FLT_MAX;
const efd::Float32 EE_PI = 3.1415926535897932f;
const efd::Float32 EE_HALF_PI = 0.5f * EE_PI;
const efd::Float32 EE_TWO_PI = 2.0f * EE_PI;
const efd::Float32 EE_E = 2.7182818284590452f;

// Conversion macrose
const efd::Float32 EE_DEGREES_TO_RADIANS = EE_PI / 180.0f;
const efd::Float32 EE_RADIANS_TO_DEGREES = 180.0f / EE_PI;

#else
// SPU compiler does not like global static constant variables
#define EE_INFINITY     FLT_MAX
#define EE_PI           3.1415926535897932f
#define EE_HALF_PI      0.5f * EE_PI
#define EE_TWO_PI       2.0f * EE_PI
#define EE_E            2.7182818284590452f
#endif

/// Computes the absolute value of the 32-bit floating point argument.
efd::Float32 Abs(efd::Float32 value);

/// Computes the arc-cosine of the 32-bit floating point argument.
efd::Float32 ACos(efd::Float32 value);

/// Computes the arc-sin of the 32-bit floating point argument.
efd::Float32 ASin(efd::Float32 value);

/// Computes the arc-tangent of the 32-bit floating point argument.
efd::Float32 ATan(efd::Float32 value);

/// Computes the arc-tangent of numerator / denominator.
efd::Float32 ATan2(efd::Float32 numerator, efd::Float32 denominator);

/// Computes the cosine of the 32-bit floating point argument.
efd::Float32 Cos(efd::Float32 radians);

/// Computes the sine of the 32-bit floating point argument.
efd::Float32 Sin(efd::Float32 radians);

/// Computes the exponential of the 32-bit floating point argument.
efd::Float32 Exp(efd::Float32 value);

/// Calculates the floor of the floating point argument
/// (the greatest or "least negative / most positive" integer less than or
/// equal to the given argument).
efd::Float32 Floor(efd::Float32 value);

/// Calculates the floating-point remainder of numerator / denominator.
efd::Float32 Fmod(efd::Float32 numerator, efd::Float32 denominator);

/// Calculates the logarithm of the 32-bit floating point argument.
efd::Float32 Log(efd::Float32 value);

/// Calculates the result of raising base to the specified exponent.
efd::Float32 Pow(efd::Float32 base, efd::Float32 exponent);

/**
    Calculates the sign of the specified floating point argument.
    @return Positive one if the value is positive, negative one if the value
        is negative and zero if the value is zero.
*/
efd::Float32 Sign(efd::Float32 value);

/**
    Calculates both the sine and cosine of the radians argument. Many floating
    point processors have assembly instructions that can calculate both faster
    than each one individually.
    @param radians The angle in radians
    @param sin Contains the sine of the specified radians when this method
        returns.
    @param cos Contains the cosine of the specified radians when this method
        returns.
*/
void SinCos(efd::Float32 radians, efd::Float32& sin, efd::Float32& cos);

/// Calculates the product of the specified argument with itself.
efd::Float32 Sqr(efd::Float32 value);

/// Calculates the square root of the specified argument.
efd::Float32 Sqrt(efd::Float32 value);

/// Returns the smaller of the two values.
template<typename T> inline T Min(T a, T b) { return (a < b) ? a : b; }

/// Returns the largest of the two 32-bit integers.
template<typename T> inline T Max(T a, T b) { return (a > b) ? a : b; }

/// Clamps the specified 32-bit integer within the range [min,max].
efd::SInt32 Clamp(efd::SInt32 value, efd::SInt32 min, efd::SInt32 max);

/// Returns the smaller of the two specified arguments. Optimized on some platforms.
template<> inline efd::Float32 Min(efd::Float32 a, efd::Float32 b);

/// Returns the largest of the two specified arguments. Optimized on some platforms.
template<> inline efd::Float32 Max(efd::Float32 a, efd::Float32 b);

/// Clamps the specified value within the range [min,max].
efd::Float32 Clamp(efd::Float32 value, efd::Float32 min, efd::Float32 max);

/// Determines if the specified value is a power of two.
bool IsPowerOf2(efd::UInt32 value);

/**
    This macro calculates the linear interpolation between START and FINISH
    as parameterized by T.
    @note This function is a macro to allow multiple data-types to be mixed
        in both the parameters and the return value since this functionality
        can be useful at times.
*/
#define EE_LERP(T, START, FINISH) ((START) + ((T) * ((FINISH) - (START))))

/**
    The Srand function sets the starting point for generating a series of
    pseudo-random integers. Each value for seed causes the values retrieved by
    subsequent calls to efd::Rand to form a specific pseudo-random sequence.
    Multiple calls to Srand with the same seed will generate the same sequence.
    Calling efd::Rand before any call to efd::Srand generates the same sequence
    as calling efd::Srand with seed passed as 1.
    @param seed Value with which to seed the random number generator.
*/
void Srand(efd::UInt32 seed);

/**
    This function returns a pseudo-random integer in the range 0 to RAND_MAX.
    Use the efd::Srand function to seed the pseudo-random-number generator
    before calling efd::Rand.
*/
efd::SInt32 Rand();

/**
    This function returns a pseudo-random 32-bit floating point value in the
    range -1.0f to 1.0f. Use the efd::Srand function to seed the
    pseudo-random-number generator before calling efd::SymmetricRandom.
*/
efd::Float32 SymmetricRandom();

/**
    This function returns a pseudo-random float in the range 0.0f to 1.0f.
    Use the efd::Srand function to seed the pseudo-random-number generator
    before calling efd::UnitRandom.
*/
efd::Float32 UnitRandom();

/**
    Calculates the logarithm of the specified 32-bit unsigned integer argument.
*/
efd::UInt32 FastLog(efd::UInt32 num);

/// Calculates an approximated inverse square root value for improved
/// performance.

efd::Float32 FastInvSqrt(efd::Float32 value);

/// Calculates an approximated square root value for improved performance.
efd::Float32 FastSqrt(efd::Float32 value);

/// Calculates an approximated value for the arc-tangent of y / x.
EE_EFD_ENTRY efd::Float32 FastATan2(efd::Float32 y, efd::Float32 x);

/// Returns true if the value passed in is a NAN
inline bool IsNAN(efd::Float32 value);

/// Returns a quiet NAN
inline efd::Float32 GetQNAN();

//@}

} // end namespace efd

/// Include the platform specific inlines
#include EE_PLATFORM_SPECIFIC_INCLUDE(efd,EEMath,inl)

#endif
