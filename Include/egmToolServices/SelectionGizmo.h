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
#ifndef EE_SELECTIONGIZMO_H
#define EE_SELECTIONGIZMO_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "IGizmo.h"
#include "TransformGizmo.h"

namespace egmToolServices
{

/**
    Selection gizmo. 
*/
class EE_EGMTOOLSERVICES_ENTRY SelectionGizmo : public TransformGizmo
{
public:
    SelectionGizmo(efd::ServiceManager* pServiceManager, TransformGizmoAdapter* pAdapter);
    virtual ~SelectionGizmo();

    /// @name Overriden functionality
    /// @see IGizmo
    //@{
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

    virtual bool HitTest(
        ecr::RenderSurface* pSurface,
        const efd::Point3& rayOrigin,
        const efd::Point3& rayDirection,
        float& outHitDistance);
    //@}
};

typedef efd::SmartPointer<SelectionGizmo> SelectionGizmoPtr;

} // namespace

#endif // EE_SELECTIONGIZMO_H
