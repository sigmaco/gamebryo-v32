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
#ifndef NIPSSIMULATORGENERALKERNEL_H
#define NIPSSIMULATORGENERALKERNEL_H

#include <NiParticleLibType.h>
#include <NiPSKernelDefinitions.h>
#include <NiSPKernelMacros.h>
#include <NiUniversalTypes.h>

/// A structure containing data required by the NiPSSimulatorGeneralKernel
/// Floodgate kernel.
struct NiPSSimulatorGeneralKernelStruct
{
    /// The current simulation time.
    float m_fCurrentTime;

    /// Looping behavior for color
    NiPSLoopBehavior m_eColorLoopBehavior;

    /// Looping behavior for size
    NiPSLoopBehavior m_eSizeLoopBehavior;

    /// Looping behavior for rotation
    NiPSLoopBehavior m_eRotationLoopBehavior;

    /// Flag to know if we are using the BGRA color format
    NiUInt8 m_ucBGRA;

    /// The total number of size keys.
    NiUInt8 m_ucNumSizeKeys;

    /// The total number of color keys.
    NiUInt8 m_ucNumColorKeys;

    /// The total number of rotation keys.
    NiUInt8 m_ucNumRotationKeys;

    /// The amount of time in seconds that a particle should grow.
    float m_fGrowTime;

    /// The amount of time in seconds that a particle should shrink.
    float m_fShrinkTime;

    /// The generation at which a particle should grow.
    NiUInt16 m_usGrowGeneration;

    /// The generation at which a particle should shrink.
    NiUInt16 m_usShrinkGeneration;
};

/**
    Simulates particle size, color and rotation.

    This Floodgate kernel calls the static helper functions in
    NiPSSimulatorKernelHelpers to grow and shrink particles, to animate the
    color of particles, and to update particle rotation.
*/
NiSPDeclareKernelLib(NiPSSimulatorGeneralKernel, NIPARTICLE_ENTRY)

#endif  // #ifndef NIPSSIMULATORGENERALKERNEL_H
