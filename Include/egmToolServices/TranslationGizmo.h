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
#ifndef EE_TRANSLATIONGIZMO_H
#define EE_TRANSLATIONGIZMO_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "IGizmo.h"
#include "TransformGizmo.h"

#include <ecr/PickService.h>
#include <egf/Entity.h>

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY TranslationGizmo : public TransformGizmo
{
public:
    TranslationGizmo(efd::ServiceManager* pServiceManager, TransformGizmoAdapter* pAdapter);
    virtual ~TranslationGizmo();

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

    virtual void TransformToView(ecr::RenderSurface* pSurface);

    virtual bool HitTest(
        ecr::RenderSurface* pSurface,
        const efd::Point3& rayOrigin,
        const efd::Point3& rayDirection,
        float& outHitDistance);
    //@}

    static void SetUserOctantFacing(bool value) { m_userOctantFacing = value; }

protected:

    enum TranslateAxis
    {
        NONE = 0,
        AXIS_X,
        AXIS_Y,
        AXIS_Z,
        PLANE_XY,
        PLANE_XZ,
        PLANE_YZ
    };

    ecr::PickService::PickRecordPtr PickAxis(ecr::RenderSurface* pSurface, int x, int y);

    void HighLightAxis(const TranslateAxis eAxis, bool reverse_xy);
    void SetEmittance(NiAVObject* pObject, const NiColor& kColor);

    static bool m_userOctantFacing;

    // fixed strings for finding objects in the gizmo
    NiFixedString* m_pkXAxisName;
    NiFixedString* m_pkYAxisName;
    NiFixedString* m_pkZAxisName;
    NiFixedString* m_pkXYPlaneName;
    NiFixedString* m_pkXZPlaneName;
    NiFixedString* m_pkYZPlaneName;
    NiFixedString* m_pkXYPlanePanelName;
    NiFixedString* m_pkXZPlanePanelName;
    NiFixedString* m_pkYZPlanePanelName;
    NiFixedString* m_pkXArrowName;
    NiFixedString* m_pkYArrowName;
    NiFixedString* m_pkZArrowName;
    NiFixedString* m_pkXLineName;
    NiFixedString* m_pkYLineName;
    NiFixedString* m_pkZLineName;
    NiFixedString* m_pkXYLineName;
    NiFixedString* m_pkXZLineName;
    NiFixedString* m_pkYXLineName;
    NiFixedString* m_pkYZLineName;
    NiFixedString* m_pkZXLineName;
    NiFixedString* m_pkZYLineName;

    TranslateAxis m_eCurrentAxis;

    NiPoint3 m_gizmoStartPoint;
    NiPoint3 m_gizmoStartPick;

    bool m_mouseMoved;
    int m_mouseX;
    int m_mouseY;
};

typedef efd::SmartPointer<TranslationGizmo> TranslationGizmoPtr;

} // namespace

#endif // EE_TRANSLATIONGIZMO_H
