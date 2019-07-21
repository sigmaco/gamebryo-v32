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
#ifndef EE_IGIZMO_H
#define EE_IGIZMO_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <ecr/RenderSurface.h>
#include <ecrInput/MouseMessages.h>

#include "GizmoAdapter.h"

namespace egmToolServices
{
/**
    Gizmo. 
*/
class EE_EGMTOOLSERVICES_ENTRY IGizmo : public efd::IBase
{
    EE_DECLARE_CLASS1(IGizmo, kCLASSID_IGizmo, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;

public:

    /**
        Constructor.
    
        @param pAdapter The adapter.
    */
    IGizmo(GizmoAdapter* pAdapter = NULL);

    /**
        Finalizer. 
    */
    virtual ~IGizmo();

    /**
        Connects. 
    
        @param pGizmoView The Ni3DRenderView* to connect.
    */
    virtual void Connect(Ni3DRenderView* pGizmoView);

    /**
        Disconnects the given pGizmoView. 
    
        @param pGizmoView The Ni3DRenderView* to disconnect.
    */
    virtual void Disconnect(Ni3DRenderView* pGizmoView);

    /**
        Executes the tick action. 
    
        @param timeElapsed The time elapsed.
        @param pSurface The surface.
    
        @return true if it succeeds, false if it fails.
    */
    virtual efd::Bool OnTick(efd::TimeType timeElapsed, ecr::RenderSurface* pSurface);

    /**
        Executes the mouse scroll action. 
    
        @param pSurface The surface.
        @param x The x coordinate.
        @param y The y coordinate.
        @param dScroll The scroll.
        @param bIsClosest true if is closest.
    
        @return true if it succeeds, false if it fails.
    */
    virtual efd::Bool OnMouseScroll(
        ecr::RenderSurface* pSurface,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dScroll,
        efd::Bool bIsClosest) = 0;

    /**
        Executes the mouse move action. 
    
        @param pSurface The surface.
        @param x The x coordinate.
        @param y The y coordinate.
        @param dx The dx.
        @param dy The dy.
        @param bIsClosest true if is closest.
    
        @return true if it succeeds, false if it fails.
    */
    virtual efd::Bool OnMouseMove(
        ecr::RenderSurface* pSurface,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dx,
        efd::SInt32 dy,
        efd::Bool bIsClosest) = 0;

    /**
        Executes the mouse down action.
    
        @param pSurface The surface.
        @param button The button.
        @param x The x coordinate.
        @param y The y coordinate.
        @param bIsClosest true if is closest.
    
        @return true if it succeeds, false if it fails.
    */
    virtual efd::Bool OnMouseDown(
        ecr::RenderSurface* pSurface,
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::Bool bIsClosest) = 0;

    /**
        Executes the mouse up action.
    
        @param pSurface The surface.
        @param button The button.
        @param x The x coordinate.
        @param y The y coordinate.
        @param bIsClosest true if is closest.
    
        @return true if it succeeds, false if it fails.
    */
    virtual efd::Bool OnMouseUp(
        ecr::RenderSurface* pSurface,
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::Bool bIsClosest) = 0;

    /**
        Begins a transform. 
    */
    virtual void BeginTransform() = 0;

    /**
        Ends a transform. 
    
        @param cancel true to cancel.
    */
    virtual void EndTransform(efd::Bool cancel) = 0;

    /**
        Tests hit. 
    
        @param pSurface The surface.
        @param rayOrigin The ray origin.
        @param rayDirection The ray direction.
        @param outHitDistance The out hit distance.
    
        @return true if the test passes, false if the test fails.
    */
    virtual efd::Bool HitTest(
        ecr::RenderSurface* pSurface,
        const efd::Point3& rayOrigin,
        const efd::Point3& rayDirection,
        float& outHitDistance) = 0;

    /**
        Gets the adapter. 
    
        @return null if it fails, else the adapter.
    */
    virtual GizmoAdapter* GetAdapter() const;

    /**
        Transform to view. 
    
        @param pSurface The surface.
    */
    virtual void TransformToView(ecr::RenderSurface* pSurface);

protected:
    GizmoAdapterPtr m_spAdapter;
};

typedef efd::SmartPointer<IGizmo> IGizmoPtr;

} // namespace

#endif // EE_IGIZMO_H
