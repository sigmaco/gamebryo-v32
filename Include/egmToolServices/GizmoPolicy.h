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
#ifndef EE_GIZMOPOLICY_H
#define EE_GIZMOPOLICY_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY GizmoPolicy : public efd::IBase
{
    EE_DECLARE_CLASS1(GizmoPolicy, kCLASSID_GizmoPolicy, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;

public:
    virtual ~GizmoPolicy() { }

    /**
    Executes the added action.
    
    @param pGizmoService The gizmo service.
    */
    virtual void OnAdded(GizmoService* pGizmoService) = 0;

    /**
    Executes the tick action.
    
    @param pGizmoService The gizmo service.
    @param timeElapsed The time elapsed.
    @param pSurface The surface.
    */
    virtual void OnTick(GizmoService* pGizmoService, efd::TimeType timeElapsed, ecr::RenderSurface* pSurface) = 0;

    /**
    Executes the removed action. 
    
    @param pGizmoService The gizmo service.
    */
    virtual void OnRemoved(GizmoService* pGizmoService) = 0;

    /**
    Activates the policy. 
    
    @param pGizmoService The gizmo service.
    */
    virtual void Activate(GizmoService* pGizmoService) = 0;

    /**
    Deactivates the policy
    
    @param pGizmoService The gizmo service.
    */
    virtual void Deactivate(GizmoService* pGizmoService) = 0;

    /**
    Query if this policy understands a subject type.  This controls if the policy will be
    activated or not.
    
    @param pGizmoService The gizmo service.
    @param subjectName Name of the subject.
    
    @return true if the policy covers the subject, otherwise false.
    */
    virtual efd::Bool IsSubjectCovered(
        GizmoService* pGizmoService,
        const efd::utf8string& subjectName) = 0;

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
        const efd::utf8string& gizmoName) = 0;

    /**
    Adds a gizmo.
    
    @param gizmoName Name of the gizmo.
    @param pGizmo The gizmo.
    */
    virtual void AddGizmo(const efd::utf8string& gizmoName, IGizmo* pGizmo);

    /**
    Removes the gizmo described by gizmoName. 
    
    @param gizmoName Name of the gizmo.
    */
    virtual void RemoveGizmo(const efd::utf8string& gizmoName);

protected:

    typedef efd::map<efd::utf8string, IGizmoPtr> GizmoMap;
    GizmoMap m_gizmoMap;
};

typedef efd::SmartPointer<GizmoPolicy> GizmoPolicyPtr;

}; // egmToolServices namespace

#endif // EE_GIZMOPOLICY_H
