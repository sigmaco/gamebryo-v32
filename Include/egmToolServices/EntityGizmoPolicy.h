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
#ifndef EE_ENTITYGIZMOPOLICY_H
#define EE_ENTITYGIZMOPOLICY_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <ecr/RenderService.h>

#include <egmToolServices\GizmoPolicy.h>

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY EntityGizmoPolicy : public GizmoPolicy
{
    EE_DECLARE_CLASS1(EntityGizmoPolicy, kCLASSID_EntityGizmoPolicy, GizmoPolicy);
    EE_DECLARE_CONCRETE_REFCOUNT;

public:
    EntityGizmoPolicy(efd::ServiceManager* pServiceManager);
    virtual ~EntityGizmoPolicy() { }

    /**
    Executes the added action.
    
    @param pGizmoService The gizmo service.
    */
    virtual void OnAdded(GizmoService* pGizmoService);

    /**
    Executes the tick action.
    
    @param pGizmoService The gizmo service.
    @param timeElapsed The time elapsed.
    @param pSurface The surface.
    */
    virtual void OnTick(GizmoService* pGizmoService, efd::TimeType timeElapsed, ecr::RenderSurface* pSurface);

    /**
    Executes the removed action. 
    
    @param pGizmoService The gizmo service.
    */
    virtual void OnRemoved(GizmoService* pGizmoService);

    /**
    Activates the policy. 
    
    @param pGizmoService The gizmo service.
    */
    virtual void Activate(GizmoService* pGizmoService);

    /**
    Deactivates the policy
    
    @param pGizmoService The gizmo service.
    */
    virtual void Deactivate(GizmoService* pGizmoService);

    /**
    Query if this policy understands a subject type.  This controls if the policy will be
    activated or not.
    
    @param pGizmoService The gizmo service.
    @param subjectName Name of the subject.
    
    @return true if the policy covers the subject, otherwise false.
    */
    virtual efd::Bool IsSubjectCovered(
        GizmoService* pGizmoService,
        const efd::utf8string& subjectName);

    /**
    Sets an active gizmo.  This will be called by the gizmo service when the active gizmo type is
    changed or this gizmo policy becomes is activated because a subject becomes active that this
    policy covers.
    
    @param pGizmoService The gizmo service.
    @param gizmoName Name of the gizmo.
    
    @return true if it succeeds, false if it fails.
    */
    virtual efd::Bool SetActiveGizmo(
        GizmoService* pGizmoService,
        const efd::utf8string& gizmoName);

    //void OnSelectionChanged(
    //    const efd::IMessage* pSelectionChanged,
    //    efd::Category targetChannel);

protected:
    IGizmo* m_pActiveGizmo;

    // Services
    //-------------------------------------------------------------------------
    efd::ServiceManager* m_pServiceManager;

    ecr::RenderService* m_pRenderService;
    efd::MessageService* m_pMessageService;
    egf::EntityManager* m_pEntityManager;
    ToolSceneGraphService* m_pSceneGraphService;
    GizmoService* m_pGizmoService;
    SelectionService* m_pSelectionService;
};

typedef efd::SmartPointer<EntityGizmoPolicy> EntityGizmoPolicyPtr;

}; // egmToolServices namespace

#endif // EE_ENTITYGIZMOPOLICY_H
