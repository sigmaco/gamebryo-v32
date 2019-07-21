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
#ifndef NIPSSIMULATORKERNELHELPERS_H
#define NIPSSIMULATORKERNELHELPERS_H

#include "NiParticleLibType.h"
#include "NiPSKernelDefinitions.h"
#include <NiUniversalTypes.h>
#include <NiPoint3.h>
#include <NiColor.h>

/**
    Contains static helper functions used for various particle simulation
    tasks.

    The NiPSSimulatorGeneralKernel and NiPSSimulatorFinalKernel Floodgate
    kernels call the static helper functions contained in this class to
    implement various aspects of the particle simulation.

    Due to the implementation of Floodgate kernels on different platforms, it
    is necessary that all output (non-const) parameters to these functions get
    set to some value. It is not valid to simply not set an output value, as
    garbage memory could result on some platforms.
*/
class NIPARTICLE_ENTRY NiPSSimulatorKernelHelpers
{
public:
    /**
        Updates a particle's new position based on its current position, its
        velocity, and the time delta since the last update.

        @param kOPosition The computed new position of the particle.
        @param kIPosition The current position of the particle.
        @param kIVelocity The velocity of the particle.
        @param fILastUpdate The last time at which the particle was updated.
        @param fCurrentTime The current simulation time.
    */
    static inline void UpdateParticlePosition(
        NiPoint3& kOPosition,
        const NiPoint3& kIPosition,
        const NiPoint3& kIVelocity,
        const float fILastUpdate,
        const float fCurrentTime);

    /**
        Calculates the size parameter for a particle based on its grow/shrink
        settings and animation keys.

        The size value for a particle ranges from 0.0 to 1.0 and is multiplied
        by the particle initial size to calculate the final particle size.

        Size keys are linearly interpolated.

        @param fOSize The computed particle size. Will be between 0.0 and 1.0.
        @param usIGeneration The generation of the particle.
        @param fIAge The age of the particle.
        @param fILifeSpan The life span of the particle.
        @param fGrowTime The time in seconds during which the particle size
            will be ramped from 0.0 to 1.0.
        @param fShrinkTime The time in seconds during which the particle size
            will be ramped from 1.0 to 0.0.
        @param usGrowGeneration The generation during which the particle will
            grow. If the particle's generation is different from this value,
            no grow computation will be applied.
        @param usShrinkGeneration The generation during which the particle
            will shrink. If the particle's generation is different from this
            value, no shrink computation will be applied.
        @param ucNumKeys The number of size animation keys.
        @param pkKeys An array of size keys that specify size
            animation over the lifetime of the particle.
        @param eLoopBehavior The desired looping behavior.
    */
    static inline void UpdateParticleSize(
        float& fOSize,
        const NiUInt16 usIGeneration,
        const float fIAge,
        const float fILifeSpan,
        const float fGrowTime,
        const float fShrinkTime,
        const NiUInt16 usGrowGeneration,
        const NiUInt16 usShrinkGeneration,
        const NiUInt8 ucNumKeys,
        const NiPSKernelFloatKey* pkKeys,
        const NiPSLoopBehavior eLoopBehavior);

    /**
        Performs color animation for a particle.

        A color key array is used to determine the color of a particle
        throughout its life time. Color keys are linearly interpolated. If
        no keys are present, the existing color is copied to the output.

        @param kOColor The computed color for the particle.
        @param kIColor The current color for the particle.
        @param fIAge The age of the particle.
        @param fILifeSpan The life span of the particle.
        @param ucNumKeys The number of color animation keys.
        @param pkKeys An array of color keys that specify color
            animation over the lifetime of the particle.
        @param eLoopBehavior The desired looping behavior.
        @param ucBGRA Support for BGRA format.
    */
    static inline void UpdateParticleColor(
        NiRGBA& kOColor,
        const NiRGBA& kIColor,
        const float fIAge,
        const float fILifeSpan,
        const NiUInt8 ucNumKeys,
        const NiPSKernelColorKey* pkKeys,
        const NiPSLoopBehavior eLoopBehavior,
        const NiUInt8 ucBGRA);

    /**
        Updates the rotation angle for a particle based on its rotation speed.

        @param fORotAngle The computed rotation angle for the particle.
        @param fIRotAngle The initial rotation angle for the particle.
        @param fIRotSpeed The rotation speed for the particle.
        @param fIAge The age of the particle.
        @param fILifeSpan The life span of the particle.
        @param ucNumKeys The number of rotation animation keys.
        @param pkKeys An array of rotation keys that specify rotation
            animation over the lifetime of the particle.
        @param eLoopBehavior The desired looping behavior.
    */
    static inline void UpdateParticleRotation(
        float& fORotAngle,
        const float fIRotAngle,
        const float fIRotSpeed,
        const float fIAge,
        const float fILifeSpan,
        const NiUInt8 ucNumKeys,
        const NiPSKernelFloatKey* pkKeys,
        const NiPSLoopBehavior eLoopBehavior);

    /**
        Updates the age of a particle, killing off the particle if its age
        exceeds its life time.

        When a particle is killed, the appropriate bits in its flags bitfield
        are set. If bSpawnOnDeath is specified, the appropriate bit will be
        set in the particle flags, along with the spawner ID specified by
        ucSpawnerID. Killed and spawned particles will be resolved when the
        simulation completes.

        @param fOAge The computed age of the particle.
        @param fOLastUpdateTime Holds the time of death if bSpawnOnDeath is
            true and the particle has died. Otherwise, the input last update
            time is simply passed through to this parameter.
        @param uiOFlags The updated particle flags bitfield.
        @param fIAge The current age of the particle.
        @param fILifeSpan The life span of the particle.
        @param fILastUpdateTime The last time at which the particle was
            updated.
        @param uiIFlags The current particle flags bitfield.
        @param fCurrentTime The current simulation time.
        @param bSpawnOnDeath Whether or not the spawn flag should be set for
            the particle if it has been killed.
        @param ucSpawnerID The spawner ID to use when spawing on death.
    */
    static inline void UpdateParticleAgeDeath(
        float& fOAge,
        float& fOLastUpdateTime,
        NiUInt32& uiOFlags,
        const float fIAge,
        const float fILifeSpan,
        const float fILastUpdateTime,
        const NiUInt32 uiIFlags,
        const float fCurrentTime,
        const bool bSpawnOnDeath,
        const NiUInt16 ucSpawnerID);

    /**
        Updates the transformation of a mesh particle and applies velocity-driven scaling
        when the alignment of the particle is given by a constant up and constant normal.

        @param fOScale The computed scale of the mesh particle.
        @param kIVelocity The velocity of the particle.
        @param fIRadius The radius of the particle.
        @param fISize The size of the particle.
        @param fScaleAmount The amount of scaling increases as the speed increases.
            If negative, the particle will shrink as the speed increases.
        @param fScaleRest The scale when the speed is zero. This value must not be the same as
            the limit. If the Scale Amount is positive, this value must be less than the limit.
            If the Scale Amount is negative, it must be greater than the limit.
        @param fScaleLimit The maximum value for scale (or the minimum if the scale amount is
            negative). The scale will approach this value as the speed goes to infinity.

        @note This function does not set the rotation - the calling code must do that.
    */
    static inline void UpdateMeshAlignmentFF(
        float& fOScale,
        const NiPoint3& kIVelocity,
        const float fIRadius,
        const float fISize,
        const float fScaleAmount = 0.0f,
        const float fScaleRest = 0.0f,
        const float fScaleLimit = 10e6f);

    /**
        Updates the transformation of a mesh particle and applies velocity-driven scaling
        when the alignment of the particle is given by a constant up and constant normal,
        and particles have per-particle rotations.

        @param kORotCol0 The first column of the computed rotation of the mesh particle.
        @param kORotCol1 The second column of the computed rotation of the mesh particle.
        @param kORotCol2 The third column of the computed rotation of the mesh particle.
        @param fOScale The computed scale of the mesh particle.
        @param kIBasis The matrix defining the desired fixed orientation for the particles.
        @param kIVelocity The velocity of the particle.
        @param fIRadius The radius of the particle.
        @param fISize The size of the particle.
        @param fIRotAngle The rotation angle of the particle.
        @param fIRotAxis The rotation axis of the particle.
        @param fIAge The age of the particle.
        @param fILifeSpan The life span of the particle.
        @param ucNumRotationKeys The number of rotation animation keys.
        @param pkKeys An array of rotation keys that specify rotation
            animation over the lifetime of the particle.
        @param eLoopBehavior The desired looping behavior.
        @param fScaleAmount The amount of scaling increases as the speed increases.
            If negative, the particle will shrink as the speed increases.
        @param fScaleRest The scale when the speed is zero. This value must not be the same as
            the limit. If the Scale Amount is positive, this value must be less than the limit.
            If the Scale Amount is negative, it must be greater than the limit.
        @param fScaleLimit The maximum value for scale (or the minimum if the scale amount is
            negative). The scale will approach this value as the speed goes to infinity.
    */
    static inline void UpdateMeshAlignmentFFR(
        NiPoint3& kORotCol0,
        NiPoint3& kORotCol1,
        NiPoint3& kORotCol2,
        float& fOScale,
        const NiMatrix3& kIBasis,
        const NiPoint3& kIVelocity,
        const float fIRadius,
        const float fISize,
        const float fIRotAngle,
        const NiPoint3& fIRotAxis,
        const float fIAge,
        const float fILifeSpan,
        const NiUInt8 ucNumRotationKeys,
        const NiPSKernelQuaternionKey* pkKeys,
        const NiPSLoopBehavior eLoopBehavior,
        const float fScaleAmount = 0.0f,
        const float fScaleRest = 0.0f,
        const float fScaleLimit = 10e6f);

    /**
        Updates the transformation of a mesh particle and applies velocity-driven scaling
        when the alignment of the particle is given by per-particle up and normal vectors.

        @param kORotCol0 The first column of the computed rotation of the mesh particle.
        @param kORotCol1 The second column of the computed rotation of the mesh particle.
        @param kORotCol2 The third column of the computed rotation of the mesh particle.
        @param fOScale The computed scale of the mesh particle.
        @param kINormal The (normalized) vector to use for the particle normal (x-axis).
        @param kIUp The target z-axis direction, which will projected to be perpendicular to the
            normal.
        @param kIVelocity The velocity of the particle.
        @param fIRadius The radius of the particle.
        @param fISize The size of the particle.
        @param fScaleAmount The amount of scaling increases as the speed increases.
            If negative, the particle will shrink as the speed increases.
        @param fScaleRest The scale when the speed is zero. This value must not be the same as
            the limit. If the Scale Amount is positive, this value must be less than the limit.
            If the Scale Amount is negative, it must be greater than the limit.
        @param fScaleLimit The maximum value for scale (or the minimum if the scale amount is
            negative). The scale will approach this value as the speed goes to infinity.
    */
    static inline void UpdateMeshAlignmentVV(
        NiPoint3& kORotCol0,
        NiPoint3& kORotCol1,
        NiPoint3& kORotCol2,
        float& fOScale,
        const NiPoint3& kINormal,
        const NiPoint3& kIUp,
        const NiPoint3& kIVelocity,
        const float fIRadius,
        const float fISize,
        const float fScaleAmount = 0.0f,
        const float fScaleRest = 0.0f,
        const float fScaleLimit = 10e6f);

    /**
        Updates the transformation of a mesh particle and applies velocity-driven scaling
        when the alignment of the particle is given by per-particle up and normal vectors,
        and particles have per-particle rotations.

        @param kORotCol0 The first column of the computed rotation of the mesh particle.
        @param kORotCol1 The second column of the computed rotation of the mesh particle.
        @param kORotCol2 The third column of the computed rotation of the mesh particle.
        @param fOScale The computed scale of the mesh particle.
        @param kINormal The (normalized) vector to use for the particle normal (x-axis).
        @param kIUp The target z-axis direction, which will projected to be perpendicular to the
            normal.
        @param kIVelocity The velocity of the particle.
        @param fIRadius The radius of the particle.
        @param fISize The size of the particle.
        @param fIRotAngle The rotation angle of the particle.
        @param fIRotAxis The rotation axis of the particle.
        @param fIAge The age of the particle.
        @param fILifeSpan The life span of the particle.
        @param ucNumRotationKeys The number of rotation animation keys.
        @param pkKeys An array of rotation keys that specify rotation
            animation over the lifetime of the particle.
        @param eLoopBehavior The desired looping behavior.
        @param fScaleAmount The amount of scaling increases as the speed increases.
            If negative, the particle will shrink as the speed increases.
        @param fScaleRest The scale when the speed is zero. This value must not be the same as
            the limit. If the Scale Amount is positive, this value must be less than the limit.
            If the Scale Amount is negative, it must be greater than the limit.
        @param fScaleLimit The maximum value for scale (or the minimum if the scale amount is
            negative). The scale will approach this value as the speed goes to infinity.
    */
    static inline void UpdateMeshAlignmentVVR(
        NiPoint3& kORotCol0,
        NiPoint3& kORotCol1,
        NiPoint3& kORotCol2,
        float& fOScale,
        const NiPoint3& kINormal,
        const NiPoint3& kIUp,
        const NiPoint3& kIVelocity,
        const float fIRadius,
        const float fISize,
        const float fIRotAngle,
        const NiPoint3& fIRotAxis,
        const float fIAge,
        const float fILifeSpan,
        const NiUInt8 ucNumRotationKeys,
        const NiPSKernelQuaternionKey* pkKeys,
        const NiPSLoopBehavior eLoopBehavior,
        const float fScaleAmount = 0.0f,
        const float fScaleRest = 0.0f,
        const float fScaleLimit = 10e6f);

    /**
        Calculate the effective particle animation time.

        @param fAge The age of the particle.
        @param fLife The lifetime of the particle.
        @param eLoop The desired looping behavior.
        @param fFirstKeyTime The first time among the keys.
        @param fLastKeyTime The last time among the keys.
        @return The time with which to sample the keys.
    */
    static inline float ComputeAnimationTime(
        const float fAge,
        const float fLife,
        const NiPSLoopBehavior eLoop,
        const float fFirstKeyTime,
        const float fLastKeyTime);
};

#include "NiPSSimulatorKernelHelpers.inl"

#endif  // #ifndef NIPSSIMULATORKERNELHELPERS_H
