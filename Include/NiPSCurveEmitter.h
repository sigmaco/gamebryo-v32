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

#ifndef NIPSCURVEEMITTER_H
#define NIPSCURVEEMITTER_H

#include "NiPSEmitter.h"
#include <NiCurve3.h>
#include <NiDataStreamElement.h>
#include <NiDataStreamPrimitiveLock.h>
#include <NiNode.h>

/**
    Emits particles from a curve.

    The shape of the curve is used to compute the initial position and velocity of the particle.

*/
class NIPARTICLE_ENTRY NiPSCurveEmitter : public NiPSEmitter
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;
    NiDeclareClone(NiPSCurveEmitter);
    NiDeclareStream;
    NiDeclareViewerStrings;

    /// @endcond

public:

    /// @name Construction and Destruction
    //@{
    /**
        Main constructor.

        @param kName The name of the emitter.
        @param pkCurveParent A NiNode object that is the parent of the curve. This object is used
            to place the curve in the world.
        @param pkEmitterObj A NiAVObject object that is used to define the direction of the emitter
            in the world.
        @param pkCurve An NiCurve3 object to use as a curve emitter.
        @param fSpeed The speed assigned to new particles.
        @param fSpeedVar The speed variation for new particles. The resulting speed values assigned
            to new particles will be evenly distributed over the range [fSpeed - fSpeedVar/2,
            fSpeed + fSpeedVar/2].
        @param fSpeedFlipRatio The proportion of particles that have their velocity negated from
            the value defined by other parameters. The value must be in the range [0.0, 1.0].
        @param fDeclination The declination angle in radians from the positive z-axis for the
            velocity vector of newly created particles. The expected range of declination is from
            0.0, which will set the velocity vector to [0,0,1], to NI_PI, which will set the
            velocity vector to [0,0,-1].
        @param fDeclinationVar The declination variation in radians for new particles. The
            resulting declination values assigned to new particles will be evenly distributed over
            the range [fDeclination - fDeclinationVar, fDeclination + fDeclinationVar].
        @param fPlanarAngle The planar angle in radians about the z-axis from the positive x-axis
            that will serve as the plane in which the declination will occur. The expected range of
            the planar angle is [0, 2*NI_PI).
        @param fPlanarAngleVar The planar angle variation in radians for new particles. The
            resulting planar angle values assigned to new particles will be evenly distributed over
            the range [fPlanarAngle - fPlanarAngleVar, fPlanarAngle + fPlanarAngleVar].
        @param fSize The radius assigned to new particles.
        @param fSizeVar The radius variation for new particles. The resulting radius values
            assigned to new particles will be evenly distributed over the range [fSize - fSizeVar,
            fSize + fSizeVar]. If fSizeVar is larger than fSize, it is possible that the radius
            will be set to a negative value. In this case, the particle will be flipped, and the
            bounding volume may be computed incorrectly. Thus, it is recommended that fSizeVar be
            less than or equal to fSize.
        @param fLifeSpan The life span in seconds assigned to new particles.
        @param fLifeSpanVar The life span variation for new particles. The resulting life span
            values assigned to new particles will be evenly distributed over the range
            [fLifeSpan - fLifeSpanVar/2, fLifeSpan + fLifeSpanVar/2].
        @param fRotAngle The rotation angle in radians assigned to new particles.
        @param fRotAngleVar The rotation angle variation in radians for new particles. The
            resulting rotation angle values assigned to new particles will be evenly distributed
            over the range [fRotAngle - fRotAngleVar, fRotAngle + fRotAngleVar].
        @param fRotSpeed The rotation speed in radians per second assigned to new particles.
        @param fRotSpeedVar The rotation speed variation in radians per second for new particles.
            The resulting rotation speed values assigned to new particles will be evenly
            distributed over the range [fRotSpeed - fRotSpeedVar, fRotSpeed + fRotSpeedVar].
        @param bRandomRotSpeedSign Whether or not the rotation speed sign should be randomly
            flipped when being assigned to new particles.
        @param kRotAxis The rotation axis assigned to new particles. This value is only used if
            bRandomRotAxis is false.
        @param bRandomRotAxis Whether or not a random rotation axis will be assigned to new
            particles.
    */
    NiPSCurveEmitter(
        const NiFixedString& kName,
        NiNode* pkCurveParent = NULL,
        NiAVObject* pkEmitterObj = NULL,
        NiCurve3* pkCurve = NULL,
        float fSpeed = 1.0f,
        float fSpeedVar = 0.0f,
        float fSpeedFlipRatio = 0.0f,
        float fDeclination = 0.0f,
        float fDeclinationVar = 0.0f,
        float fPlanarAngle = 0.0f,
        float fPlanarAngleVar = 0.0f,
        float fSize = 1.0f,
        float fSizeVar = 0.0f,
        float fLifeSpan = 1.0f,
        float fLifeSpanVar = 0.0f,
        float fRotAngle = 0.0f,
        float fRotAngleVar = 0.0f,
        float fRotSpeed = 0.0f,
        float fRotSpeedVar = 0.0f,
        bool bRandomRotSpeedSign = false,
        const NiPoint3& kRotAxis = NiPoint3::UNIT_X,
        bool bRandomRotAxis = true);
    //@}

    //@{
    /// Accesses the curve from which particles will be emitted.
    inline NiCurve3* GetCurve() const;
    inline void SetCurve(NiCurve3* pkCurve);
    //@}

    //@{
    /// Accesses the curve parent used to position the curve in the world.
    inline NiNode* GetCurveParent() const;
    inline void SetCurveParent(NiNode* pkCurve);
    //@}

    //@{
    /// Accesses the object in the scene graph whose world-space transformation
    /// will be used to represent the orientation of the emitter.
    inline NiAVObject* GetEmitterObj() const;
    inline void SetEmitterObj(NiAVObject* pkEmitterObj);
    //@}

    /// @cond EMERGENT_INTERNAL

    /// @name Base Class Overrides
    //@{
    virtual void ProcessClone(NiCloningProcess& kCloning);
    //@}

    /// @endcond

protected:
    /// @name Construction and Destruction
    //@{
    /// Protected default constructor for cloning and streaming only.
    NiPSCurveEmitter();
    //@}

    /// @name Base Class Overrides
    //@{
    virtual bool ComputeInitialPositionAndVelocity(
        NiPSParticleSystem* pkParticleSystem,
        NiQuatTransform& kEmitterToPSys,
        NiPoint3& kPosition,
        NiPoint3& kVelocity);
    //@}

    /// The curve to use when emitting particles.
    NiCurve3Ptr m_spCurve;
    NiNodePtr m_spCurveParent;

    /// The object in the scene graph whose world-space transformation will
    /// be used to represent the orientation of the emitter.
    NiAVObject* m_pkEmitterObj;
};

NiSmartPointer(NiPSCurveEmitter);

#include "NiPSCurveEmitter.inl"

#endif  // #ifndef NIPSCURVEEMITTER_H
