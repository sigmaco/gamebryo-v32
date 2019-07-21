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
#ifndef NIPSRADIALFIELDFORCE_H
#define NIPSRADIALFIELDFORCE_H

#include "NiPSFieldForce.h"

/**
    Updates particle velocity to simulate the effects of point gravity.

    The field object and direction define the location and orientation of the
    gravity field. The magnitude defines the acceleration in particle space.
    The attenuation and max distance define the area and influence of the
    gravity field.
*/
class NIPARTICLE_ENTRY NiPSRadialFieldForce : public NiPSFieldForce
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;
    NiDeclareClone(NiPSRadialFieldForce);
    NiDeclareStream;
    NiDeclareViewerStrings;

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /**
        Main constructor.

        @param kName The name of the force.
        @param pkFieldObj The object in the scene graph whose world-space
            transformations will be used to represent the position and
            orientation of the field.
        @param fMagnitude The magnitude of the force.
        @param fAttenuation How the magnitude of the force diminishes with
            distance from the field object.
        @param bUseMaxDistance Whether or not to use a maximum distance from
            the field object after which the force has no effect.
        @param fMaxDistance The maximum distance from the field object at
            which the force has any effect. This distance is only used if
            bUseMaxDistance is true.
        @param fRadialFactor How the radial field's effect diminishes with
            attenuation.
    */
    NiPSRadialFieldForce(
        const NiFixedString& kName,
        NiAVObject* pkFieldObj,
        float fMagnitude,
        float fAttenuation,
        bool bUseMaxDistance,
        float fMaxDistance,
        float fRadialFactor);
    //@}

    /// @name Base Class Overrides
    //@{
    virtual size_t GetDataSize() const;
    virtual void* GetData() const;
    virtual bool Update(NiPSParticleSystem* pkParticleSystem, float fTime);
    //@}
    ///

    //@{
    /**
        Accesses how the radial field's effect diminishes with attenuation.

        A value of 1.0 causes the effect of the radial field to drop quickly
        to zero when a particle approaches the max distance from the field.

        A value of 0.0 causes the effect of the radial field to gradually
        approach (but never reach) zero as a particle approaches the max
        distance from the field.
    */
    inline float GetRadialFactor() const;
    inline void SetRadialFactor(float fRadialFactor);
    //@}

protected:
    /// @name Construction and Destruction
    //@{
    /// Protected default constructor for cloning and streaming only.
    NiPSRadialFieldForce();
    //@}

    /// A structure containing the data used by this class.
    NiPSForceDefinitions::RadialFieldData m_kInputData;
};

NiSmartPointer(NiPSRadialFieldForce);

#include "NiPSRadialFieldForce.inl"

#endif  // #ifndef NIPSRADIALFIELDFORCE_H
