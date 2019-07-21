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
#ifndef EE_TRANSFORMGIZMOADAPTER_H
#define EE_TRANSFORMGIZMOADAPTER_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "GizmoAdapter.h"

#include <efd/MessageService.h>
#include <egf/EntityManager.h>

namespace egmToolServices
{
/**
Transform gizmo adapter. 
*/
class EE_EGMTOOLSERVICES_ENTRY TransformGizmoAdapter : public GizmoAdapter
{
    EE_DECLARE_CLASS1(TransformGizmoAdapter, kCLASSID_TransformGizmoAdapter, GizmoAdapter);
    EE_DECLARE_CONCRETE_REFCOUNT;

public:
    TransformGizmoAdapter(efd::ServiceManager* pServiceManager);
    virtual ~TransformGizmoAdapter() { }

    /**
    Query if this object is visible. 
    
    @return true if visible, false if not.
    */
    virtual efd::Bool IsVisible() const = 0;

    /**
    Query if 'pObject' is selected.
    
    @param pObject The object.
    
    @return true if selected, false if not.
    */
    virtual efd::Bool IsSelected(NiAVObject* pObject) const = 0;

    virtual efd::Point3 GetOrigin() const = 0;
    virtual efd::Matrix3 GetRotation() const = 0;
    virtual efd::UInt32 GetTargets() const = 0;

    virtual efd::Bool SnapToPoints(efd::UInt32 targetIndex, efd::Point3 translationDelta) = 0;

    virtual efd::Bool CanTranslate(efd::UInt32 targetIndex) = 0;
    virtual efd::Point3 GetTranslationStart(efd::UInt32 targetIndex) const = 0;
    virtual void GetTranslation(efd::UInt32 targetIndex, efd::Point3& position) const = 0;
    virtual void SetTranslation(efd::UInt32 targetIndex, const efd::Point3& position) = 0;

    virtual efd::Bool CanRotate(efd::UInt32 targetIndex) = 0;
    virtual efd::Matrix3 GetRotationStart(efd::UInt32 targetIndex) const = 0;
    virtual void GetRotation(efd::UInt32 targetIndex, efd::Matrix3& rotation) const = 0;
    virtual void SetRotation(efd::UInt32 targetIndex, const efd::Matrix3& rotation) = 0;

    virtual efd::Bool CanScale(efd::UInt32 targetIndex) = 0;
    virtual efd::Float32 GetScaleStart(efd::UInt32 targetIndex) const = 0;
    virtual void GetScale(efd::UInt32 targetIndex, efd::Float32& scale) const = 0;
    virtual void SetScale(efd::UInt32 targetIndex, const efd::Float32& scale) = 0;

    virtual void OnTransformClone() = 0;

protected:
    efd::MessageService* m_pMessageService;
};

typedef efd::SmartPointer<TransformGizmoAdapter> TransformGizmoAdapterPtr;

}; // egmToolServices namespace

#endif // EE_TRANSFORMGIZMOADAPTER_H