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
#ifndef NIPSKERNELDEFINITIONS_H
#define NIPSKERNELDEFINITIONS_H

#include <NiColor.h>
#include <NiQuaternion.h>
#include <NiDebug.h>

/// A float key structure for use in particle system Floodgate kernels.
struct NiPSKernelFloatKey
{
    /// The key value.
    float m_fValue;

    /// The key time.
    float m_fTime;
};

/// A quaternion key structure for use in particle system Floodgate kernels.
struct NiPSKernelQuaternionKey
{
    /// The key orientation.
    NiQuaternion m_kValue;

    /// The key time.
    float m_fTime;
};

/// A color key structure for use in particle system Floodgate kernels.
struct NiPSKernelColorKey
{
    /// The key color.
    NiRGBA m_kColor;

    /// The key time.
    float m_fTime;
};

/// An enumeration for per-particle animation looping.
enum NiPSLoopBehavior {
    /// Key times map such that the first key occurs at the birth of the particle,
    /// and times later than the last key get the last key value.
    PSKERNELLOOP_CLAMP_BIRTH = 0,

    /// Key times map such that the last key occurs at the death of the particle, and times
    /// before the initial key time get the value of the initial key.
    PSKERNELLOOP_CLAMP_DEATH = 1,

    /// Scale the animation to fit the particle lifetime, so that the
    /// first key is age zero, and the last key comes at the particle
    /// death.
    PSKERNELLOOP_AGESCALE = 2,

    /// The time is converted to one within the time range represented
    /// by the keys, as if the key sequence loops forever in the past
    /// and future.
    PSKERNELLOOP_LOOP = 3,

    /// The time is reflection looped, as if the keys played forward then
    /// backward the forward then backward etc for all time.
    PSKERNELLOOP_REFLECT = 4
};

/// An epsilon to be used when comparing floating point variables in Floodgate kernels.
const float NIPSKERNEL_EPSILON = 0.0001f;

/// A float sufficiently large enough to be considered infinite in FloodGate kernels.
const float NIPSKERNEL_INFINITE = 10e6f;

/// The boundary to which data buffers used in Floodgate kernels should be aligned.
const size_t NIPSKERNEL_ALIGNMENT =
#ifdef _PS3
    128;
#else   // #ifdef _PS3
    16;
#endif  // #ifdef _PS3

#endif  // #ifndef NIPSKERNELDEFINITIONS_H
