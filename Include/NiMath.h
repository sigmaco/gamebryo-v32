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
#ifndef NIMATH_H
#define NIMATH_H

#include <efd/EEMath.h>

#ifndef __SPU__
const float NI_INFINITY = efd::EE_INFINITY;
const float NI_PI = efd::EE_PI;
const float NI_HALF_PI = efd::EE_HALF_PI;
const float NI_TWO_PI = efd::EE_TWO_PI;
const float NI_E = efd::EE_E;
#else
// SPU compiler does not like global static constant variables
#define NI_INFINITY EE_INFINITY
#define NI_PI       EE_PI
#define NI_HALF_PI  EE_HALF_PI
#define NI_TWO_PI   EE_TWO_PI
#define NI_E        EE_E
#endif

// 'float' wrappers for standard math functions
#define NiAbs(fValue) efd::Abs(fValue)
#define NiACos(fValue) efd::ACos(fValue)
#define NiASin(fValue) efd::ASin(fValue)
#define NiATan(fValue) efd::ATan(fValue)
#define NiATan2(fNumerator, fDenominator) efd::ATan2(fNumerator, fDenominator)
#define NiCos(fRadians) efd::Cos(fRadians)
#define NiExp(fValue) efd::Exp(fValue)
#define NiFloor(fValue) efd::Floor(fValue)
#define NiFmod(fNumerator, fDenominator) efd::Fmod(fNumerator, fDenominator)
#define NiLog(fValue) efd::Log(fValue)
#define NiPow(fBase, fExponent) efd::Pow(fBase, fExponent)
#define NiSign(fValue) efd::Sign(fValue)
#define NiSin(fRadians) efd::Sin(fRadians)
#define NiSinCos(fRadians, fSin, fCos) efd::SinCos(fRadians, fSin, fCos)
#define NiSqr(fValue) efd::Sqr(fValue)
#define NiSqrt(fValue) efd::Sqrt(fValue)

// min max clamp
#define NiMin(fA, fB) efd::Min(fA, fB)
#define NiMax(fA, fB) efd::Max(fA, fB)
#define NiClamp(fValue, fMin, fMax) efd::Clamp(fValue, fMin, fMax)

// utility functions
#define NiIsPowerOf2(uiI) efd::IsPowerOf2(uiI)
#define NiLerp(T, START, FINISH) ((START) + ((T) * ((FINISH) - (START))))

// random number generation
#define NiSrand(uiSeed) efd::Srand(uiSeed)
#define NiRand() efd::Rand() // r in [0,RAND_MAX]
#define NiSymmetricRandom() efd::SymmetricRandom()  // r in [-1,1]
#define NiUnitRandom() efd::UnitRandom()  // r in [0,1]

// fast functions
#define NiFastLog(uiNum) efd::FastLog(uiNum)
#define NiFastInvSqrt(fValue) efd::FastInvSqrt(fValue)
#define NiFastSqrt(fValue) efd::FastSqrt(fValue)

#define NiFastATan2(fY, fX) efd::FastATan2(fY, fX)

#endif // NIMATH_H
