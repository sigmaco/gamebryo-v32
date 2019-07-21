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
#ifndef NIPHYSICSSHAREDDATA_H
#define NIPHYSICSSHAREDDATA_H

#include "NiStandardSharedDataLibType.h"
#include "NiSharedData.h"

/// A shared data object to contain scene physics simulation preferences
class NISTANDARDSHAREDDATA_ENTRY NiPhysicsSharedData : public NiSharedData
{
public:
    NiDeclareRTTI;

    /// Default constructor.
    NiPhysicsSharedData();

    /// Virtual destructor.
    virtual ~NiPhysicsSharedData();

    /** Get and set the scale factor of the source scene.
        
        This number represents how many meters per scene unit. For example, a scene modeled
        in centimeters would use a scaleFactor of 0.01.
    */
    efd::Float32 GetScaleFactor();
    void SetScaleFactor(efd::Float32 scaleFactor);

protected:
    /// The preferred scalefactor of the source scene
    efd::Float32 m_scaleFactor;
};

NiSmartPointer(NiPhysicsSharedData);

#endif  // #ifndef NIPHYSICSSHAREDDATA_H
