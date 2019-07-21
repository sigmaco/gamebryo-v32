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

#ifndef NIPSSIMULATORMESHALIGNSTEP_H
#define NIPSSIMULATORMESHALIGNSTEP_H

#include "NiPSSimulatorStep.h"
#include <NiPSSimulatorMeshAlignKernelStruct.h>
#include <NiPSKernelDefinitions.h>
#include <NiSPStream.h>

class NiPSMeshParticleSystem;

/**
    Encapsulates a Floodgate kernel that updates mesh particle alignment and transforms.

    This step should be attached last in the NiPSSimulator mesh modifier for mesh particles.
    It may only be attached to a NiPSMeshParticleSystem.

    Rotation keys may be given, per generation, to provide an additional rotation
    that is added to the per-particle rotation computed by the NiPSSimulatorGeneralStep.
    The value derived from the keys is multiplied onto the rotation that is computed from
    the rotation speed and axis for the particle. This allows the for random variation in
    the rotations through random variation in the rotation speed parameter.

    All key-framed values are slerped. It is valid to provide only a single key, in which case the
    given value will be treated as a constant over the life of that particle generation.

    This step uses the NiPSSimulatorMeshAlignKernel Floodgate kernel. The kernel
    is always executed.
*/
class NIPARTICLE_ENTRY NiPSSimulatorMeshAlignStep : public NiPSSimulatorStep
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;
    NiDeclareClone(NiPSSimulatorMeshAlignStep);
    NiDeclareStream;
    NiDeclareViewerStrings;

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /**
        Constructor.

        @param fScaleAmount The amount of scaling increases as the speed increases.
            If negative, the particle will shrink as the speed increases.
        @param fScaleRest The scale when the speed is zero. This value must not be the same as
            the limit. If the Scale Amount is positive, this value must be less than the limit.
            If the Scale Amount is negative, it must be greater than the limit.
        @param fScaleLimit The maximum value for scale (or the minimum if the scale amount is
            negative). The scale will approach this value as the speed goes to infinity.
    */
    NiPSSimulatorMeshAlignStep(const float fScaleAmount = 0.0f, const float fScaleRest = 1.0f,
        const float fScaleLimit = 1e4f);

    /// Destructor.
    virtual ~NiPSSimulatorMeshAlignStep();
    //@}

    /// @name Base Class Overrides
    //@{
    /// Returns the Floodgate kernel associated with the step, which will
    /// be of type NiPSSimulatorFinalKernel.
    virtual NiSPKernel* GetKernel();

    /// Returns the largest stride value of all the input streams in the step.
    virtual NiUInt16 GetLargestInputStride();

    /**
        Prepares the input stream with the specified semantic for execution.

        The following semantics are recognized:
        NiPSCommonSemantics::PARTICLEPOSITION,
        NiPSCommonSemantics::PARTICLEVELOCITY,
        NiPSCommonSemantics::PARTICLERADIUS,
        NiPSCommonSemantics::PARTICLESIZE,
        NiPSCommonSemantics::PARTICLEROTANGLE,
        NiPSCommonSemantics::PARTICLEROTAXIS,
        NiPSCommonSemantics::PARTICLEAGE,
        NiPSCommonSemantics::PARTICLELIFESPAN,
        NiPSCommonSemantics::PARTICLEFLAGS. Other semantics will assert in
        Debug builds.
    */
    virtual void PrepareInputStream(
        NiPSParticleSystem* pkParticleSystem,
        const NiFixedString& kSemantic,
        NiSPStream* pkStream);

    /**
        Prepares the output stream with the specified semantic for execution.

        The following semantics are recognized:
        NiPSCommonSemantics::PARTICLEROTATION,
        NiPSCommonSemantics::PARTICLESCALE. Other semantics will assert in
        Debug builds.
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

        This function sets the block count on all streams and prepares any
        spawner data. Always returns true.
    */
    virtual bool Update(NiPSParticleSystem* pkParticleSystem, float fTime);
    //@}

    /// Initialize the orientation for a new particle
    virtual void InitializeNewParticle(NiPSMeshParticleSystem* pkParticleSystem, NiUInt32 uiIndex);

    /// @name Rotation Animation Keys
    //@{

    /**
        Get the rotation keys that have been assigned to the step.

        @param ucNumRotationsKeys Returns the size of the returned rotation key array.
        @return A pointer to an array of rotation keys.
    */
    NiPSKernelQuaternionKey* GetRotationKeys(NiUInt8& ucNumRotationsKeys) const;

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
    void CopyRotationKeys(
        const NiPSKernelQuaternionKey* pkRotationKeys, const NiUInt8 ucNumKeys);

    /// Get the rotation key looping behavior.
    NiPSLoopBehavior GetRotationLoopBehavior() const;

    /// Set the rotation key looping behavior.
    ///
    /// The loop behavior is always clamping when only one key is given.
    void SetRotationLoopBehavior(const NiPSLoopBehavior kBehavior);

    //@}

    /**
        @name Velocity-Derived Scaling Parameters

        These parameters control scaling of the mesh particles based on the particle speed.
        This scaling is applied as a multiplier to the particle size determined from the
        emitter and and size animation or grow-fade.

        When the speed is zero, the scale will be ScaleRest, which must be positive. The rate
        at which scale grows or shrinks with velocity is defined by ScaleAmount, which may be
        negative to have the particle shrink as it moves faster. The scale is limited to
        the value ScaleLimit as the speed increases to infinity. The ScaleLimit must be
        greater than ScaleRest if ScaleAmount is positive, or less than ScaleRest when ScaleLimit
        is negative.
    */
    //@{
    /// Get the scale amount.
    float GetScaleAmount() const;

    /// Set the scale amount.
    void SetScaleAmount(const float fAmount);

    /// Get the scale rest value.
    float GetScaleRest() const;

    /// Set the scale rest value.
    void SetScaleRest(const float fRest);

    /// Get the scale limit.
    float GetScaleLimit() const;

    /// Set the scale limit.
    void SetScaleLimit(const float fLimit);

    //@}

protected:
    /// Fill the kernel structure with data for alignment
    void PopulateKernelStruct(NiPSParticleSystem* pkParticleSystem);

    /// The Floodgate kernel used by the step.
    NiSPKernel* m_pkKernel;

    /// A structure containing input data for the Floodgate kernel.
    NiPSSimulatorMeshAlignKernelStruct m_kKernelStruct;

    /// @name Input Floodgate Streams
    //@{
    NiTSPFixedInput<NiPSSimulatorMeshAlignKernelStruct> m_kInputStructIS;
    NiTSPFixedInput<NiPSKernelQuaternionKey> m_kRotationKeyIS;
    NiSPStream* m_pkPositionIS;
    NiSPStream* m_pkVelocityIS;
    NiSPStream* m_pkSizesIS;
    NiSPStream* m_pkRadiiIS;
    NiSPStream* m_pkRotAnglesIS;
    NiSPStream* m_pkRotAxesIS;
    NiSPStream* m_pkAgesIS;
    NiSPStream* m_pkLifeSpansIS;
    //@}

    /// @name Output Floodgate Streams
    //@{
    NiSPStream* m_pkRotationsOS;
    NiSPStream* m_pkScalesOS;
    //@}

    /// A pointer to an array of rotation keys to use for particle rotation animation.
    ///
    /// Key count and looping behavior is stored in the kernel struct.
    NiPSKernelQuaternionKey* m_pkRotationKeys;
};

NiSmartPointer(NiPSSimulatorMeshAlignStep);

#include "NiPSSimulatorMeshAlignStep.inl"

#endif  // #ifndef NIPSSIMULATORMESHALIGNSTEP_H
