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
#ifndef EE_TRANSFORMGIZMO_H
#define EE_TRANSFORMGIZMO_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "IGizmo.h"

#include <efd/Point3.h>
#include <efd/MessageService.h>

#include <egf/Entity.h>
#include <egf/EntityManager.h>

#include <ecr/RenderService.h>
#include <ecr/PickService.h>

#include "ToolSceneService.h"

#include "TransformGizmoAdapter.h"

namespace egmToolServices
{

class SelectionService;
class GizmoService;
class ToolCameraService;
class ToolSnapService;

/**
    Transform gizmo. 
*/
class EE_EGMTOOLSERVICES_ENTRY TransformGizmo : public IGizmo
{
public:
    TransformGizmo(efd::ServiceManager* pServiceManager, TransformGizmoAdapter* pAdapter);
    virtual ~TransformGizmo();

    /// @name IGizmo Members
    //@{
    virtual void Connect(Ni3DRenderView* pGizmoView);
    virtual void Disconnect(Ni3DRenderView* pGizmoView);

    virtual bool OnTick(efd::TimeType timeElapsed, ecr::RenderSurface* pSurface);

    virtual efd::Bool OnMouseScroll(
        ecr::RenderSurface* pSurface,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dScroll,
        efd::Bool bIsClosest);

    virtual efd::Bool OnMouseMove(
        ecr::RenderSurface* pSurface,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dx,
        efd::SInt32 dy,
        efd::Bool bIsClosest) = 0;

    virtual efd::Bool OnMouseDown(
        ecr::RenderSurface* pSurface,
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::Bool bIsClosest) = 0;

    virtual efd::Bool OnMouseUp(
        ecr::RenderSurface* pSurface,
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::Bool bIsClosest) = 0;

    virtual void BeginTransform();
    virtual void EndTransform(bool cancel);

    virtual bool HitTest(
        ecr::RenderSurface* pSurface,
        const efd::Point3& rayOrigin,
        const efd::Point3& rayDirection,
        float& outHitDistance) = 0;

    virtual GizmoAdapter* GetAdapter() const;

    virtual void TransformToView(ecr::RenderSurface* pSurface);
    //@}

    virtual bool IsActive();

protected:

    virtual bool MatchSurface(
        const efd::Point3& rayOrigin,
        const efd::Point3& rayDirection,
        efd::Point3& intersection,
        efd::Point3& rotation);

    efd::MessageService* m_pMessageService;
    ecr::PickService* m_pPickService;
    ecr::RenderService* m_pRenderService;
    ToolSceneGraphService* m_pSceneGraphService;
    ToolCameraService* m_pCameraService;
    GizmoService* m_pGizmoService;

    TransformGizmoAdapterPtr m_spTransformAdapter;

    NiAVObjectPtr m_spGizmo;

    float m_fDefaultDistance;

    bool m_isTransforming;
    bool m_usingSpecial;
    bool m_isActive;
};

typedef efd::SmartPointer<TransformGizmo> TransformGizmoPtr;

}; // namepsace

#endif // EE_TRANSFORMGIZMO_H
