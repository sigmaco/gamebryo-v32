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

#ifndef NIPSSIMULATORMESHALIGNKERNELSTRUCT_H
#define NIPSSIMULATORMESHALIGNKERNELSTRUCT_H

#include <NiParticleLibType.h>
#include <NiTransform.h>
#include <NiPSKernelDefinitions.h>

/// A structure containing data required by the NiPSSimulatorMeshAlignKernel[FV][FV]
/// Floodgate kernels.
struct NiPSSimulatorMeshAlignKernelStruct
{
    /**
        Fixed normal direction vector.

        For a VF kernel or a VV kernel it is not defined.
    */
    NiPoint3 m_kNormal;

    /**
        Fixed up direction vector.

        For a FV kernel or a VV kernel it is not defined.
    */
    NiPoint3 m_kUp;

    /// The transformation to apply to normal directions.
    ///
    /// Not used for FV or FF kernels. The transformation is pre-applied in that case.
    NiTransform m_kNormalTransform;

    /// The transformation to apply to up directions.
    ///
    /// Not used for VF or FF kernels. The transformation is pre-applied in that case.
    NiTransform m_kUpTransform;

    /// If true, use position for per-particle normal input, otherwise use velocity.
    bool m_bNormalUsePosition;

    /// If true, use position for per-particle up input, otherwise use velocity.
    bool m_bUpUsePosition;

    /// The number of rotation animation keys.
    NiUInt8 m_ucNumRotationKeys;

    /// The number of rotation animation keys.
    NiPSLoopBehavior m_eRotationLoopBehavior;

    /** The amount of scaling increases as the speed increases.

        If negative, the particle will shrink as the speed increases.
    */
    float m_fScaleAmount;

    /** The scale when the speed is zero.

        This value must not be the same as the limit. If the Scale Amount is positive, this value
        must be less than the limit.
        If the Scale Amount is negative, it must be greater than the limit.
    */
    float m_fScaleRest;

    /** The maximum value for scale (or the minimum if the scale amount is negative).

        The scale will approach this value as the speed goes to infinity.
    */
    float m_fScaleLimit;
};

#endif  // #ifndef NIPSSIMULATORMESHALIGNKERNELSTRUCT_H
