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

#ifndef NIPHYSXPSFLUIDEMITTER_H
#define NIPHYSXPSFLUIDEMITTER_H

#include <NiColor.h>
#include <NiObject.h>

#include "NiPhysXFluidLibType.h"
#include <NiPSEmitter.h>

/**
    NiPhysXFluidEmitter is a particle system emitter intended for use with
    Gamebryo-PhysX fluid particle systems.

    One of these objects must be attached to every PhysX fluid particle system,
    and no other emitters should be attached. The class exists only to provide
    an implementation of the private function ComputeInitialPositionAndVelocity
    so that the class can be instantiated. It provides no functionality
    beyond the base class.
*/
class NIPHYSXFLUID_ENTRY NiPhysXPSFluidEmitter : public NiPSEmitter
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    NiDeclareStream;
    NiDeclareViewerStrings;
    /// @endcond

public:

    /// Constructor.
    ///
    /// The arguments are passed directly to the NiPSEmitter constructor.
    NiPhysXPSFluidEmitter(const NiFixedString& kName, float fSize = 1.0f,
        float fSizeVar = 0.0f);

    /// @cond EMERGENT_INTERNAL

    virtual bool StreamCanSkip();

    /// @endcond

protected:
    // For cloning and streaming only.
    NiPhysXPSFluidEmitter();

    // This function sets the position to the origin and the velocity to zero.
    virtual bool ComputeInitialPositionAndVelocity(
        NiPSParticleSystem* pkParticleSystem, 
        NiQuatTransform& kEmitterToPSys,
        NiPoint3& kPosition,
        NiPoint3& kVelocity);

    virtual NiAVObject* GetEmitterObj() const;

};

NiSmartPointer(NiPhysXPSFluidEmitter);

#endif  // #ifndef NIPHYSXPSFLUIDEMITTER_H
