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

#ifndef NIPSALIGNEDQUADGENERATORKERNELSTRUCT_H
#define NIPSALIGNEDQUADGENERATORKERNELSTRUCT_H

#include <NiParticleLibType.h>
#include <NiTransform.h>

/// A structure containing data required by the
/// NiPSAlignedQuadGeneratorKernel[FV][FV] Floodgate kernels.
struct NiPSAlignedQuadGeneratorKernelStruct
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
    /// Not used for FV or FF kernels. The transformation is pre-applied in
    /// that case.
    NiTransform m_kNormalTransform;

    /// The transformation to apply to up directions.
    ///
    /// Not used for VF or FF kernels. The transformation is pre-applied in
    /// that case.
    NiTransform m_kUpTransform;

    /// If true, use position for per-particle normal input, otherwise use
    /// velocity.
    bool m_bNormalUsePosition;

    /// If true, use position for per-particle up input, otherwise use
    /// velocity.
    bool m_bUpUsePosition;

    /**
        A scale factor for the stretching of particles along the U direction.

        Stretching is applied based on velocity data. The ratio value is
        normalized to give results that are independent of the max stretch
        value.
    */
    float m_fScaleAmountU;

    /**
        The limit allowed for scale along the U direction.

        Stretching is only applied when data for the "up" direction is
        per-particle.
    */
    float m_fScaleLimitU;

    /**
        The scale in the U direction when the speed is zero.

        This value must not be the same as the max. If the ratio is positive,
        this value must be less than the limit. If the ratio is negative,
        it must be greater than the limit.
    */
    float m_fScaleRestU;

    /**
        A scale factor for the stretching of particles along the V direction.

        Stretching is applied based on velocity data. The ratio value is
        normalized to give results that are independent of the max stretch
        value.
    */
    float m_fScaleAmountV;

    /**
        The limit allowed for scale along the V direction.

        Stretching is only applied when data for the "up" direction is
        per-particle.
    */
    float m_fScaleLimitV;

    /**
        The scale in the V direction when the speed is zero.

        This value must not be the same as the max. If the ratio is positive,
        this value must be less than the limit. If the ratio is negative,
        it must be greater than the limit.
    */
    float m_fScaleRestV;

    /// A normalized version of the scale factor for U.
    ///
    /// This makes the scale factor effectively independent of the limit.
    float m_fScaleNormalizedU;

    /// A normalized version of the scale factor for V.
    ///
    /// This makes the scale factor effectively independent of the limit.
    float m_fScaleNormalizedV;

    /// A pivot point offset in the U direction.
    ///
    /// Particles will rotate about this point.
    float m_fCenterU;

    /// A pivot point offset in the V direction.
    ///
    /// Particles will rotate about this point.
    float m_fCenterV;
};

#endif  // #ifndef NIPSALIGNEDQUADGENERATORKERNELSTRUCT_H
