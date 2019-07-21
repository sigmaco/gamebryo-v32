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
#ifndef EE_ORBITCAMERAMODE_H
#define EE_ORBITCAMERAMODE_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "StandardCameraMode.h"

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY OrbitCameraMode : public StandardCameraMode
{
public:
    OrbitCameraMode(efd::ServiceManager* pServiceManager);
    virtual ~OrbitCameraMode();

    virtual efd::Bool OnMouseMove(
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dx,
        efd::SInt32 dy,
        ToolCamera* camera);

    virtual efd::Bool OnMouseDown(
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        ToolCamera* camera);

    virtual efd::Bool OnMouseUp(
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        ToolCamera* camera);
};

typedef efd::SmartPointer<OrbitCameraMode> OrbitCameraModePtr;

} // namespace

#endif // EE_ORBITCAMERAMODE_H
