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
#ifndef EE_STANDARDCAMERAMODE_H
#define EE_STANDARDCAMERAMODE_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "ICameraMode.h"

#include <egf/Entity.h>

namespace ecr
{
    class PickService;
    class RenderService;
}

namespace egmToolServices
{

class ToolSceneGraphService;
class ToolCameraService;
class SelectionService;

/**

*/
class EE_EGMTOOLSERVICES_ENTRY StandardCameraMode : public ICameraMode
{
public:
    /// @name Construction and Destruction.
    //@{
    /// Constructor.
    StandardCameraMode(efd::ServiceManager* pServiceManager);
    /// Virtual Destructor.
    virtual ~StandardCameraMode();
    //@}

    /// Use input from ToolCameraService to drive the camera.
    virtual efd::Bool OnTick(efd::TimeType timeElapsed, ToolCamera* pCamera);

    /// Zoom the camera.
    virtual efd::Bool OnMouseScroll(
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dScroll,
        ToolCamera* pCamera);

    /// If ToolCameraService is looking or panning, adjust camera.
    virtual efd::Bool OnMouseMove(
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dx,
        efd::SInt32 dy,
        ToolCamera* pCamera);

    /// Set orbit locations and set up panning speeds based on pick distances.
    virtual efd::Bool OnMouseDown(
        ecrInput::MouseMessage::MouseButton eButton,
        efd::SInt32 x,
        efd::SInt32 y,
        ToolCamera* pCamera);

    /// Do nothing.
    virtual efd::Bool OnMouseUp(
        ecrInput::MouseMessage::MouseButton eButton,
        efd::SInt32 x,
        efd::SInt32 y,
        ToolCamera* pCamera);

    /// Reset to default camera values.
    virtual void Reset(ToolCamera* camera);

protected:
    void SetupOrbit(efd::SInt32 x, efd::SInt32 y, ToolCamera* pCamera);

    efd::Bool GetPickDistance(efd::SInt32 x, efd::SInt32 y, efd::Float32& pickDistance);

    void AdjustOrthoDistance(ToolCamera* pCamera);

    efd::ServiceManager* m_pServiceManager;
    ecr::PickService* m_pPickService;
    ecr::RenderService* m_pRenderService;
    ToolSceneGraphService* m_pToolSceneService;
    ToolCameraService* m_pCameraService;
    SelectionService* m_pSelectionService;

    efd::Point3 m_upAxis;
    efd::Float32 m_scrollSpeed;
    efd::Float32 m_mouseLookScalar;
    efd::Float32 m_mousePanScalar;

    efd::Float32 m_orthoMovementScale;

    efd::Float32 m_panSpeedX;
    efd::Float32 m_panSpeedY;

    efd::Point3 m_cameraStart;

    efd::Point3 m_orbitCenter;
    efd::Float32 m_orbitStickDistance;
};

typedef efd::SmartPointer<StandardCameraMode> StandardCameraModePtr;

} // namespace

#endif // EE_STANDARDCAMERAMODE_H
