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
#ifndef EE_CREATIONGIZMO_H
#define EE_CREATIONGIZMO_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "IGizmo.h"
#include "TransformGizmo.h"
#include "CreationGizmoAdapter.h"

#include <egf/Entity.h>

namespace egmToolServices
{
class GridService;

/**
    Creation gizmo. 
*/
class EE_EGMTOOLSERVICES_ENTRY CreationGizmo : public TransformGizmo
{
public:
    CreationGizmo(efd::ServiceManager* pServiceManager, CreationGizmoAdapter* pAdapter);
    virtual ~CreationGizmo();

    /// @name IGizmo Members
    //@{
    virtual efd::Bool OnTick(efd::TimeType timeElapsed, ecr::RenderSurface* pSurface);

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

    virtual efd::Bool HitTest(
        ecr::RenderSurface* pSurface,
        const efd::Point3& rayOrigin,
        const efd::Point3& rayDirection,
        float& outHitDistance);
    
    virtual void BeginTransform();
    virtual void EndTransform(bool cancel);
    //@}

    /// @name TransformGizmo Members
    //@{
    virtual efd::Bool IsActive();
    //@}

protected:

    /**
        Values that represent CreationStage.
    */
    enum CreationStage
    {
        STAGE_NONE,
        STAGE_LOCKED,
        STAGE_CREATING
    };

    void TranslateTarget(ecr::RenderSurface* pSurface, int x, int y);
    void RotateTarget(ecr::RenderSurface* pSurface, int x, int y);

    float GetRadians(ecr::RenderSurface* pSurface, const efd::Point3& origin,
                     const efd::Point3& direction);

    void SetupRotation(ecr::RenderSurface* pSurface, int x, int y);

    bool RotateLinear(ecr::RenderSurface* pSurface);

    GridService* m_pGridService;

    efd::Point3 m_startingPoint;
    efd::Point3 m_startingRotation;
    efd::Point3 m_endingRotation;

    efd::Float32 m_fStartingRadians;
    efd::Float32 m_fCurrentRadians;
    efd::Point3 m_rotationLine;

    efd::SInt32 m_mouseDownX;
    efd::SInt32 m_mouseDownY;

    efd::Bool m_bMouseMoved;

    CreationStage m_stage;

    CreationGizmoAdapterPtr m_spCreationAdapter;
};

typedef efd::SmartPointer<CreationGizmo> CreationGizmoPtr;

}; // namespace

#endif // EE_CREATIONGIZMO_H
