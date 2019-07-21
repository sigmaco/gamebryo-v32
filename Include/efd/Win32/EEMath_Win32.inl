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

#include <efd/Asserts.h>

namespace efd
{

//------------------------------------------------------------------------------------------------
inline efd::Float32 Abs(efd::Float32 value)
{
    return efd::Float32(fabs(value));
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 ACos(efd::Float32 value)
{
    if (-1.0f < value)
    {
        if (value < 1.0f)
            return efd::Float32(acos(value));
        else
            return 0.0f;
    }
    else
    {
        return EE_PI;
    }
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 ASin(efd::Float32 value)
{
    if (-1.0f < value)
    {
        if (value < 1.0f)
            return efd::Float32(asin(value));
        else
            return EE_HALF_PI;
    }
    else
    {
        return -EE_HALF_PI;
    }
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 ATan(efd::Float32 value)
{
    return efd::Float32(atan(value));
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 ATan2(efd::Float32 numerator, efd::Float32 denominator)
{
    return efd::Float32(atan2(numerator, denominator));
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Cos(efd::Float32 radians)
{
    return efd::Float32(cos(radians));
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Exp(efd::Float32 value)
{
    return efd::Float32(exp(value));
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Floor(efd::Float32 value)
{
    return efd::Float32(floor(value));
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Fmod(efd::Float32 numerator, efd::Float32 denominator)
{
    return efd::Float32(fmod(numerator, denominator));
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Log(efd::Float32 value)
{
    return efd::Float32(log(value));
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Pow(efd::Float32 base, efd::Float32 exponent)
{
    return efd::Float32(pow(base, exponent));
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Sign(efd::Float32 value)
{
    return (value > 0.0f ? +1.0f : (value < 0.0f ? -1.0f : 0.0f));
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Sin(efd::Float32 radians)
{
    return efd::Float32(sin(radians));
}

//------------------------------------------------------------------------------------------------
inline void SinCos(efd::Float32 radians, efd::Float32& sin, efd::Float32& cos)
{
    efd::Float32 s, c;
    __asm fld radians
    __asm fsincos
    __asm fstp c
    __asm fstp s

    sin = s;
    cos = c;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Sqr(efd::Float32 value)
{
    return value*value;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Sqrt(efd::Float32 value)
{
    return efd::Float32(sqrt(value));
}

//------------------------------------------------------------------------------------------------
template<>
inline efd::Float32 Min(efd::Float32 a, efd::Float32 b)
{
    return (a < b) ? a : b;
}

//------------------------------------------------------------------------------------------------
template<>
inline efd::Float32 Max(efd::Float32 a, efd::Float32 b)
{
    return (a > b) ? a : b;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Clamp(efd::Float32 value, efd::Float32 min, efd::Float32 max)
{
    EE_ASSERT(min <= max);
    value = efd::Max(value, min);
    value = efd::Min(value, max);

    return value;
}

//------------------------------------------------------------------------------------------------
inline efd::SInt32 Clamp(efd::SInt32 value, efd::SInt32 min, efd::SInt32 max)
{
    EE_ASSERT(min <= max);
    value = efd::Max(value, min);
    value = efd::Min(value, max);

    return value;
}

//------------------------------------------------------------------------------------------------
inline bool IsPowerOf2(efd::UInt32 value)
{
    if (!value)
        return false;

    return (value & (value - 1)) == 0;
}

//------------------------------------------------------------------------------------------------
inline void Srand(efd::UInt32 seed)
{
    srand(seed);
}

//------------------------------------------------------------------------------------------------
inline efd::SInt32 Rand()
{
    return rand();
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 UnitRandom()
{
    return efd::Float32(efd::Rand())/efd::Float32(RAND_MAX);
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 SymmetricRandom()
{
    return -1.0f + 2.0f*efd::Float32(efd::Rand())/efd::Float32(RAND_MAX);
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 FastLog(efd::UInt32 num)
{
    efd::UInt32 logNum = 0;
    efd::UInt32 temp = num >> 1;
    while (temp & 0xffffffff)
    {
        temp >>= 1;
        ++logNum;
    }

    return logNum;
}

//------------------------------------------------------------------------------------------------
// Algorithm for fast inverse square root from Dave Eberly's WildMagic code.
// See http://www.wild-magic.com/Web/Documents/FastInverseSqrt.pdf for
// implementation discussion.
inline efd::Float32 FastInvSqrt(efd::Float32 value)
{
    efd::Float32 half = 0.5f*value;
    efd::SInt32 i  = *(efd::SInt32*) & value;

    i = 0x5f3759df - (i >> 1);
    value = *(efd::Float32*)&i;
    value = value*(1.5f - half*value*value);

    return value;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 FastSqrt(efd::Float32 value)
{
    return efd::FastInvSqrt(value) * value;
}

//------------------------------------------------------------------------------------------------
inline bool IsNAN(efd::Float32 value)
{
    return _isnan(value) != 0;
}

//------------------------------------------------------------------------------------------------
/// Returns a quiet NAN
inline efd::Float32 GetQNAN()
{
    union FloatIntUnion
    {
        efd::UInt32 ui;
        efd::Float32 f;
    };

    FloatIntUnion k;
    k.ui = 0xFFC00000;
    return k.f;
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
