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
#ifndef NIPSSIMULATORGENERALSTEP_H
#define NIPSSIMULATORGENERALSTEP_H

#include "NiPSSimulatorStep.h"
#include <NiPSSimulatorGeneralKernel.h>
#include <NiSPStream.h>
#include "NiPSKernelDefinitions.h"

/**
    Encapsulates a Floodgate kernel that updates particle size, colors,
    and rotations.

    Size keys may be specified for this step. Additional properties control
    the time scaling and looping behavior of the size animations. Note that
    the size computed here is multiplied by the initial size of the particle,
    set in the emitter. This enables random particle sizes to still be scaled
    over the particle life.

    A grow time and a shrink time can be specified for this step. These
    control durations of time during which particles will grow from size 0.0
    to their specified size and will shrink from their radius to 0.0. The
    grow and shrink generation values specify which particle generation to use
    for the growing and shrinking action. The most common case is for the grow
    generation to be 0 and the shrink generation to be the highest generation
    supported by the particle system (so that particles will grow when born
    and shrink when dying). Grow and shrink is applied in addition to the
    animated size, so particles will grow and shrink regardless of their animated
    size.

    Color keys can be specified that define color animation over the lifetime
    of each particle.

    Rotation keys may be given to provide an additional rotation
    angle that is added to the particle's initial rotation value. The value derived
    from the keys is added to the rotation angle that is computed from the rotation
    speed for the particle. This allows the for random variation in the rotations
    through random variation in the rotation speed parameter. Furthermore,
    rotation keys are not typically used on mesh-based particles because a distinct
    set of rotation keys on the NiPSSimulatorMeshAlignStep object uses quaternions
    to animate 3D rotation of the mesh scene graph.

    All key-framed values are linearly interpolated (slerped in the case of
    rotations). It is valid to provide only a single key, in which case the
    given value will be treated as a constant over the life of the particle.
    The same set of keys is used for particles of all generations. If you
    would like different keys, then spawn dead particles into a different
    particle system.

    This step uses the NiPSSimulatorGeneralKernel Floodgate kernel. The kernel
    is only executed if one of the following conditions is met:

    - The grow time is greater than 0.0.
    - The shrink time is greater than 0.0.
    - There are size keys.
    - The particle system has colors and color keys have been specified.
    - The particle system has rotations.
*/
class NIPARTICLE_ENTRY NiPSSimulatorGeneralStep : public NiPSSimulatorStep
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;
    NiDeclareClone(NiPSSimulatorGeneralStep);
    NiDeclareStream;
    NiDeclareViewerStrings;

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /**
        Constructor.
    */
    NiPSSimulatorGeneralStep();

    /// Virtual destructor.
    virtual ~NiPSSimulatorGeneralStep();
    //@}

    /// @name Base Class Overrides
    //@{
    /// Returns the Floodgate kernel associated with the step, which will
    /// be of type NiPSSimulatorGeneralKernel.
    virtual NiSPKernel* GetKernel();

    /// Returns the largest stride value of all the input streams in the step.
    virtual NiUInt16 GetLargestInputStride();

    /**
        Prepares the input stream with the specified semantic for execution.

        The following semantics are recognized:
        NiPSCommonSemantics::PARTICLECOLOR,
        NiPSCommonSemantics::PARTICLEFLAGS,
        NiPSCommonSemantics::PARTICLEAGE,
        NiPSCommonSemantics::PARTICLELIFESPAN,
        NiPSCommonSemantics::PARTICLEROTANGLE and
        NiPSCommonSemantics::PARTICLEROTSPEED. Other semantics will assert
        in Debug builds.
    */
    virtual void PrepareInputStream(
        NiPSParticleSystem* pkParticleSystem,
        const NiFixedString& kSemantic,
        NiSPStream* pkStream);

    /**
        Prepares the output stream with the specified semantic for execution.

        The following semantics are recognized:
        NiPSCommonSemantics::PARTICLESIZE, NiPSCommonSemantics::PARTICLECOLOR,
        NiPSCommonSemantics::PARTICLEROTANGLE. Other semantics will assert
        in Debug builds.
    */
    virtual void PrepareOutputStream(
        NiPSParticleSystem* pkParticleSystem,
        const NiFixedString& kSemantic,
        NiSPStream* pkStream);

    /**
        Creates a task and add several input and output streams, including
        the fixed inputs.
    */
    virtual NiSPTaskPtr Attach(NiPSParticleSystem* pkParticleSystem);

    /**
        Sets all pointers to data streams to NULL.
    */
    virtual void Detach(NiPSParticleSystem* pkParticleSystem);

    /**
        Update function called each frame.

        This function sets the block count on all streams. The function
        returns true if any of the following are true: the particles have
        non-zero grow time, the particles have non-zero fade time, the
        particles have animated size keys, the particles have colors and
        there are color keys, or the particles have rotations. If none are
        true, then the function returns false.
    */
    virtual bool Update(NiPSParticleSystem* pkParticleSystem, float fTime);
    //@}

    /// Initialize the size, color and rotation for a new particle.
    ///
    /// Called in cases where the particle will be updated or drawn without a simulation step.
    virtual void InitializeNewParticle(NiPSParticleSystem* pkParticleSystem, NiUInt32 uiIndex);

    /**
        Gets the size keys that have been assigned to the step.

        @param ucNumSizeKeys Returns the size of the returned size key array.
        @return A pointer to an array of size keys.
    */
    inline NiPSKernelFloatKey* GetSizeKeys(NiUInt8& ucNumSizeKeys) const;

    /**
        Copies the input array of size keys, allocating aligned memory
        internally and copying the data.

        It is valid to specify NULL for pkSizeKeys, but ucNumSizeKeys must
        also be zero. If pkSizeKeys is not NULL, ucNumSizeKeys must be
        greater than zero.

        Is it valid to provide a single key representing a constant size.

        @note This function does not take ownership of pkSizeKeys. The
            calling code is responsible for memory management of that data.

        @param pkSizeKeys A pointer to the array of size keys to copy.
        @param ucNumKeys The number of keys in the pkSizeKeys array.
    */
    void CopySizeKeys(const NiPSKernelFloatKey* pkSizeKeys, const NiUInt8 ucNumKeys);

    /// Get the size key looping behavior.
    inline NiPSLoopBehavior GetSizeLoopBehavior() const;

    /// Set the size key looping behavior.
    void SetSizeLoopBehavior(const NiPSLoopBehavior eBehavior);

    /**
        Gets the color keys that have been assigned to the step.

        @param ucNumColorKeys Returns the size of the returned key array.
        @return A pointer to an array of color keys.
    */
    inline NiPSKernelColorKey* GetColorKeys(NiUInt8& ucNumColorKeys) const;

    /**
        Copies the input array of color keys, allocating aligned memory
        internally and copying the data.

        It is valid to specify NULL for pkColorKeys, but ucNumColorKeys must
        also be zero. If pkColorKeys is not NULL, ucNumColorKeys must be
        greater than zero.

        Is it valid to provide a single key representing a constant color.

        @note This function does not take ownership of pkColorKeys. The
            calling code is responsible for memory management of that data.

        @param pkColorKeys A pointer to the array of color keys to copy.
        @param ucNumKeys The number of keys in the pkColorKeys array.
    */
    void CopyColorKeys(const NiPSKernelColorKey* pkColorKeys, const NiUInt8 ucNumKeys);

    /// Get the color key looping behavior.
    inline NiPSLoopBehavior GetColorLoopBehavior() const;

    /// Set the color key looping behavior.
    ///
    /// The loop behavior is always clamping when only one key is given.
    inline void SetColorLoopBehavior(const NiPSLoopBehavior eBehavior);

    /**
        Get the rotation keys that have been assigned to the step.

        @param ucNumRotationsKeys Returns the size of the returned rotation key array.
        @return A pointer to an array of rotation keys.
    */
    inline NiPSKernelFloatKey* GetRotationKeys(NiUInt8& ucNumRotationsKeys) const;

    /**
        Copies the input array of rotation keys, allocating aligned memory
        internally and copying the data.

        It is valid to specify NULL for pkRotationKeys, but ucNumRotationKeys
        must also be zero. If pkRotationKeys is not NULL, ucNumRotationKeys must be
        greater than zero.

        Is it valid to provide a single key representing a constant rotation value.

        @note This function does not take ownership of pkRotationKeys. The
            calling code is responsible for memory management of that data.

        @param pkRotationKeys A pointer to the array of rotation keys to copy.
        @param ucNumKeys The number of keys in the pkRotationKeys array.
    */
    void CopyRotationKeys(const NiPSKernelFloatKey* pkRotationKeys, const NiUInt8 ucNumKeys);

    /// Get the rotation key looping behavior.
    inline NiPSLoopBehavior GetRotationLoopBehavior() const;

    /// Set the rotation key looping behavior.
    ///
    /// The loop behavior is always clamping when only one key is given.
    inline void SetRotationLoopBehavior(const NiPSLoopBehavior eBehavior);

    //@{
    /**
        Accesses the grow time for particles, in seconds.

        The grow time for a particle is the amount of time over which its size
        is ramped from 0.0 to 1.0. The particle size is multiplied by the
        particle radius to compute the final size for the particle.
    */
    inline float GetGrowTime() const;
    inline void SetGrowTime(float fGrowTime);
    //@}

    //@{
    /**
        Accesses the shrink time for particles, in seconds.

        The shrink time for a particle is the amount of time over which its
        size is ramped from 1.0 to 0.0. The particle size is multiplied by the
        particle radius to compute the final size for the particle.
    */
    inline float GetShrinkTime() const;
    inline void SetShrinkTime(float fShrinkTime);
    //@}

    /**
        Accesses the grow generation for particles.

        The grow generation specifies the particle generation to which the
        grow effect should be applied. This is usually generation 0, so that
        newly created particles will grow.
       */
    inline NiUInt16 GetGrowGeneration() const;
    inline void SetGrowGeneration(NiUInt16 usGrowGeneration);
    //@}

    /**
        Accesses the shrink generation for particles.

        The shrink generation specifies the particle generation to which the
        shrink effect should be applied. This is usually the highest supported
        generation for the particle system, so that particles will shrink
        immediately before getting killed.
    */
    inline NiUInt16 GetShrinkGeneration() const;
    inline void SetShrinkGeneration(NiUInt16 usShrinkGeneration);
    //@}

protected:
    /// The Floodgate kernel used by the step.
    NiPSSimulatorGeneralKernel m_kKernel;

    /// A structure containing input data for the Floodgate kernel.
    NiPSSimulatorGeneralKernelStruct m_kInputStruct;

    /// @name Input Floodgate Streams
    //@{
    NiTSPFixedInput<NiPSSimulatorGeneralKernelStruct> m_kInputStructIS;
    NiTSPFixedInput<NiPSKernelFloatKey> m_kSizeKeyIS;
    NiTSPFixedInput<NiPSKernelColorKey> m_kColorKeyIS;
    NiTSPFixedInput<NiPSKernelFloatKey> m_kRotationKeyIS;
    NiSPStream* m_pkColorIS;
    NiSPStream* m_pkFlagsIS;
    NiSPStream* m_pkAgeIS;
    NiSPStream* m_pkLifeSpanIS;
    NiSPStream* m_pkRotAngleIS;
    NiSPStream* m_pkRotSpeedIS;
    //@}

    /// @name Output Floodgate Streams
    //@{
    NiSPStream* m_pkSizeOS;
    NiSPStream* m_pkColorOS;
    NiSPStream* m_pkRotAngleOS;
    //@}

    /// A pointer to an array of size keys to use for particle size animation.
    NiPSKernelFloatKey* m_pkSizeKeys;

    /// A pointer to an array of color keys to use for particle color animation.
    NiPSKernelColorKey* m_pkColorKeys;

    /// A pointer to an array of rotation keys to use for particle rotation animation.
    NiPSKernelFloatKey* m_pkRotationKeys;
};

NiSmartPointer(NiPSSimulatorGeneralStep);

#include "NiPSSimulatorGeneralStep.inl"

#endif  // #ifndef NIPSSIMULATORGENERALSTEP_H
