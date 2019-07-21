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
#ifndef EE_SCALEGIZMO_H
#define EE_SCALEGIZMO_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "IGizmo.h"
#include "TransformGizmo.h"

#include <egf/Entity.h>

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY ScaleGizmo : public TransformGizmo
{
public:
    ScaleGizmo(efd::ServiceManager* pServiceManager, TransformGizmoAdapter* pAdapter);
    virtual ~ScaleGizmo();

    /// @name Overriden functionality
    /// @see IGizmo
    //@{
    virtual bool OnTick(efd::TimeType timeElapsed, ecr::RenderSurface* pSurface);

    virtual efd::Bool OnMouseMove(
        ecr::RenderSurface* pSurface,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dx,
        efd::SInt32 dy,
        efd::Bool bIsClosest);

    virtual efd::Bool OnMouseDown(
        ecr::RenderSurface* pSurface,
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::Bool bIsClosest);

    virtual efd::Bool OnMouseUp(
        ecr::RenderSurface* pSurface,
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::Bool bIsClosest);

    virtual void BeginTransform();
    virtual void EndTransform(bool cancel);

    virtual bool HitTest(
        ecr::RenderSurface* pSurface,
        const efd::Point3& rayOrigin,
        const efd::Point3& rayDirection,
        float& outHitDistance);
    //@}

protected:

    float GetDistance(ecr::RenderSurface* pSurface, const float fX, const float fY);

    bool m_mouseMoved;
    int m_mouseX;
    int m_mouseY;

    float m_startDistance;

    efd::Point3 m_center;
};

typedef efd::SmartPointer<ScaleGizmo> ScaleGizmoPtr;

} // namespace

#endif // EE_SCALEGIZMO_H
