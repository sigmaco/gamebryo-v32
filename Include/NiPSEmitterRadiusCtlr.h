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
#ifndef NIPSEMITTERRADIUSCTLR_H
#define NIPSEMITTERRADIUSCTLR_H

#include "NiPSEmitterFloatCtlr.h"

/// Animates the size value on an NiPSEmitter object.
class NIPARTICLE_ENTRY NiPSEmitterRadiusCtlr : public NiPSEmitterFloatCtlr
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;
    NiDeclareClone(NiPSEmitterRadiusCtlr);
    NiDeclareStream;
    NiDeclareViewerStrings;

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /**
        Main constructor.

        @param kEmitterName The name of the NiPSEmitter object that should be
            animated.
    */
    NiPSEmitterRadiusCtlr(const NiFixedString& kEmitterName);
    //@}

protected:
    /// @name Construction and Destruction
    //@{
    /// Protected default constructor for cloning and streaming only.
    NiPSEmitterRadiusCtlr();
    //@}

    /// @name Base Class Overrides
    //@{
    virtual void GetTargetFloatValue(float& fValue);
    virtual void SetTargetFloatValue(float fValue);
    //@}
};

NiSmartPointer(NiPSEmitterRadiusCtlr);

#endif  // #ifndef NIPSEMITTERRADIUSCTLR_H
