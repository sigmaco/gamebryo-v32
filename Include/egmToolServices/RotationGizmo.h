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
#ifndef EE_ROTATIONGIZMO_H
#define EE_ROTATIONGIZMO_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "IGizmo.h"
#include "TransformGizmo.h"

#include <egf/Entity.h>

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY RotationGizmo : public TransformGizmo
{
public:
    RotationGizmo(efd::ServiceManager* pServiceManager, TransformGizmoAdapter* pAdapter);
    virtual ~RotationGizmo();

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

    enum RotateAxis
    {
        ROTATE_AXIS_NONE = 0,
        ROTATE_AXIS_X,
        ROTATE_AXIS_Y,
        ROTATE_AXIS_Z
    };

    void SetupRotation(ecr::RenderSurface* pSurface, int x, int y);
    float GetRadians(ecr::RenderSurface* pSurface, const NiPoint3& origin,
        const NiPoint3& direction);
    bool RotateLinear(ecr::RenderSurface* pSurface, const RotateAxis axis);
    void PickAxis(ecr::RenderSurface* pSurface, int x, int y);
    void HighLightAxis(const RotateAxis axis);

    // fixed strings for finding objects in the gizmo
    NiFixedString* m_pkXAxisName;
    NiFixedString* m_pkYAxisName;
    NiFixedString* m_pkZAxisName;
    NiFixedString* m_pkXLineName;
    NiFixedString* m_pkYLineName;
    NiFixedString* m_pkZLineName;

    // values that need to be stored between frames
    RotateAxis m_eCurrentAxis;

    float m_fStartingRadians;
    float m_fCurrentRadians;
    NiPoint3 m_pkRotationLine;

    efd::Point3 m_center;

    bool m_mouseMoved;
    int m_mouseX;
    int m_mouseY;
};

typedef efd::SmartPointer<RotationGizmo> RotationGizmoPtr;

} // namespace

#endif // EE_ROTATIONGIZMO_H
