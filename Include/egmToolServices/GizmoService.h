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
#ifndef EE_GIZMOSERVICE_H
#define EE_GIZMOSERVICE_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <efd/MessageHandlerBase.h>
#include <efd/ISystemService.h>

#include <Ni3DRenderView.h>
#include <NiCullingProcess.h>
#include <NiVisibleArray.h>
#include <NiViewRenderClick.h>

#include <ecr/RenderService.h>
#include <ecr/ecrSystemServiceIDs.h>

#include "ToolServicesMessages.h"

#include "CreationGizmo.h"

#include "IGizmo.h"
#include "IInteractionDelegate.h"

#include "GizmoPolicy.h"

namespace efd
{
    class MessageService;
}

namespace ecr
{
    class RenderService;
}

class NiViewRenderClick;

namespace egmToolServices
{

class SelectionService;
class ToolCameraService;

/**
    This service manages the gizmos used to position, orient, and otherwise graphically modify
    objects.
*/
class EE_EGMTOOLSERVICES_ENTRY GizmoService : public efd::ISystemService,
                                              public ecr::IRenderServiceDelegate,
                                              public IInteractionDelegate
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS3(
        GizmoService,
        efd::kCLASSID_GizmoService,
        efd::ISystemService,
        ecr::IRenderServiceDelegate,
        IInteractionDelegate);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    enum RelativeSpace
    {
        RSPACE_WORLD = 0,
        RSPACE_LOCAL,
        RSPACE_SCREEN
    };

    enum PlacementMode
    {
        PMODE_FREE_PLACEMENT = 0,
        PMODE_SNAP_TO_SURFACE,
        PMODE_ALIGN_TO_SURFACE
    };

    static const float ms_parallelThreshold;
    static const float ms_invParallelThreshold;

public:
    GizmoService();

    // IRenderServiceDelegate Members
    //=========================================================================

    /**
        Called by the RenderService when the RenderSurface is created.
        @param pService Pointer to the RenderService.
        @param pSurface Pointer to the newly created render surface.
    */
    virtual void OnSurfaceAdded(
        ecr::RenderService* pService,
        ecr::RenderSurface* pSurface);

    /**
        Called by the RenderService when the RenderSurface is about to be destroyed.
        @param pService Pointer to the RenderService.
        @param pSurface Pointer to the render surface that is about to be destroyed.
    */
    virtual void OnSurfaceRemoved(
        ecr::RenderService* pService,
        ecr::RenderSurface* pSurface);

    virtual void OnSurfacePreDraw(
        ecr::RenderService* pService,
        ecr::RenderSurface* pSurface);

    //=========================================================================

    Ni3DRenderView* GetGizmoView();

    template< typename T >
    inline T* GetPolicy() const;

    template< typename T >
    void AddGizmoPolicy(GizmoPolicy* pGizmoPolicy);
    void AddGizmoPolicy(GizmoPolicy* pGizmoPolicy);

    template< typename T >
    void RemoveGizmoPolicy(GizmoPolicy* pGizmoPolicy);
    void RemoveGizmoPolicy(GizmoPolicy* pGizmoPolicy);

    const efd::utf8string& GetActivePolicySubject();

    /**
    Sets an active policy subject and clears the active policy stack.
    
    @param subjectName Name of the subject.
    */
    void SetActivePolicySubject(const efd::utf8string& subjectName);

    /**
    Pushes an active policy subject. 
    
    @param subjectName Name of the subject.
    */
    void PushActivePolicySubject(const efd::utf8string& subjectName);

    /**
    Pops an active policy subject. 
    */
    void PopActivePolicySubject();

    void AddSurface(ecr::RenderSurfacePtr spSurface);
    void RemoveSurface(ecr::RenderSurfacePtr spSurface);

    const efd::utf8string& GetActiveGizmo();

    void SetActiveGizmo(const efd::utf8string& gizmoName);

    /**
    Pushes an active gizmo. 
    
    @param gizmoName Name of the gizmo.
    */
    void PushActiveGizmo(const efd::utf8string& gizmoName);

    /**
    Pops an active gizmo. 
    */
    void PopActiveGizmo();

    //=========================================================================

    void AddGizmo(IGizmo* pGizmo);
    void RemoveGizmo(IGizmo* pGizmo);

    // IInteractionDelegate Members
    //=========================================================================

    virtual efd::SInt32 GetInteractionPriority();

    virtual bool OnMouseScroll(
        efd::Bool handled,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dScroll);

    virtual bool OnMouseMove(
        efd::Bool handled,
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dx,
        efd::SInt32 dy);

    virtual bool OnMouseDown(
        efd::Bool handled,
        ecrInput::MouseMessage::MouseButton eButton,
        efd::SInt32 x,
        efd::SInt32 y);

    virtual bool OnMouseUp(
        efd::Bool handled,
        ecrInput::MouseMessage::MouseButton eButton,
        efd::SInt32 x,
        efd::SInt32 y);

    // 
    //=========================================================================

    virtual efd::Bool HitTest(ecr::RenderSurface* pSurface, efd::SInt32 x, efd::SInt32 y);

    // 
    //=========================================================================

    void UpdateClosestGizmo(int x, int y, ecr::RenderSurface* pSurface);

    RelativeSpace GetRelativeSpace() const;
    void SetRelativeSpace(RelativeSpace space);

    bool TranslationPrecisionEnabled() const;
    void SetTranslationPrecisionEnabled(bool flag);

    double TranslationPrecision() const;
    void SetTranslationPrecision(double precision);

    bool ScalePrecisionEnabled() const;
    void SetScalePrecisionEnabled(bool flag);

    double ScalePrecision() const;
    void SetScalePrecision(double precision);

    bool TranslationSnapEnabled() const;
    void SetTranslationSnapEnabled(bool flag);

    double TranslationSnap() const;
    void SetTranslationSnap(double snap);

    bool RotationSnapEnabled() const;
    void SetRotationSnapEnabled(bool flag);

    double RotationSnap() const;
    void SetRotationSnap(double snap);

    bool ScaleSnapEnabled() const;
    void SetScaleSnapEnabled(bool flag);

    double ScaleSnap() const;
    void SetScaleSnap(double snap);

    PlacementMode GetPlacementMode() const;
    void SetPlacementMode(PlacementMode mode);

    void IsSpecialActive(bool value);
    bool IsSpecialActive() const;

    // 
    //=========================================================================

    static void FindAlignToSurfaceRotation(const efd::Point3& normal, efd::Point3& rotation);

    static inline void RoundToIncrement(efd::Point3& value, double increment);
    static inline void RoundToIncrement(float& value, double increment);

protected:

    virtual ~GizmoService();

    virtual const char* GetDisplayName() const;

    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();

    void InternalSetActivePolicySubject(
        const efd::utf8string& subjectName,
        efd::Bool clearStack);

    void InternalSetActiveGizmo(
        const efd::utf8string& gizmoName,
        efd::Bool clearStack);

    void DeactivateActivePolicies();
    efd::Bool ActivateGizmoPolicy(GizmoPolicy* pGizmoPolicy);

    bool HitTestActiveGizmo(ecr::RenderSurface* pSurface, const efd::Point3& rayStart,
        const efd::Point3& rayDir);

protected:

    efd::MessageService* m_pMessageService;
    ecr::RenderService* m_pRenderService;
    SelectionService* m_pSelectionService;
    ToolCameraService* m_pCameraService;

    NiVisibleArray m_visibleArray;
    Ni3DRenderViewPtr m_spGizmoRenderView;
    NiCullingProcessPtr m_spCuller;
    NiViewRenderClick* m_pGizmoRenderClick;

    efd::utf8string m_activeSubject;
    efd::stack<efd::utf8string> m_activeSubjectStack;

    efd::utf8string m_activeGizmoName;
    efd::stack<efd::utf8string> m_activeGizmoStack;

    typedef efd::map<efd::ClassID, GizmoPolicyPtr> GizmoPolicyMap;
    GizmoPolicyMap m_policies;

    typedef efd::vector<GizmoPolicyPtr> GizmoPolicyVector;
    GizmoPolicyVector m_activePolicies;

    typedef efd::vector<IGizmoPtr> Gizmos;
    Gizmos m_gizmos;

    IGizmo* m_pClosestGizmo;

    RelativeSpace m_currentSpace;
    PlacementMode m_placementMode;

    bool m_translationPrecisionEnabled;
    bool m_scalePrecisionEnabled;
    bool m_translationSnapEnabled;
    bool m_rotationSnapEnabled;
    bool m_scaleSnapEnabled;

    bool m_scaleToView;

    double m_translationPrecision;
    double m_scalePrecision;
    double m_translationSnap;
    double m_rotationSnap;
    double m_scaleSnap;

    efd::TimeType m_lastUpdateTime;

    bool m_isSpecialPrimed;
};

typedef efd::SmartPointer<GizmoService> GizmoServicePtr;

} // end namespace egmToolServices

#include "GizmoService.inl"

#endif // EE_GIZMOSERVICE_H
