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
#ifndef EE_GIZMOADAPTER_H
#define EE_GIZMOADAPTER_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <efd/Point3.h>
#include <efd/Matrix3.h>

#include <NiAVObject.h>

namespace egmToolServices
{
/**
    Gizmo adapter. 
*/
class EE_EGMTOOLSERVICES_ENTRY GizmoAdapter : public efd::IBase
{
    EE_DECLARE_CLASS1(GizmoAdapter, kCLASSID_GizmoAdapter, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;

public:

    /**
        Default constructor. 
    */
    GizmoAdapter();

    /**
        Finalizer. 
    */
    virtual ~GizmoAdapter() { }

    /// @name Gizmo Events
    //@{
    /**
        Executes the added action. 
    */
    virtual void OnAdded();

    /**
        Executes the tick action. 
    */
    virtual void OnTick();

    /**
        Executes the removed action. 
    */
    virtual void OnRemoved();
    //@}

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

    /**
        Gets the origin. 
    
        @return The origin.
    */
    virtual efd::Point3 GetOrigin() const = 0;

    /**
        Gets the rotation. 
    
        @return The rotation.
    */
    virtual efd::Matrix3 GetRotation() const = 0;

    /**
        Begins a transform. 
    */
    virtual void BeginTransform();

    /**
        Ends a transform. 
    
        @param cancel true to cancel.
    */
    virtual void EndTransform(efd::Bool cancel);

protected:
    efd::Bool m_transforming;
};

typedef efd::SmartPointer<GizmoAdapter> GizmoAdapterPtr;

}; // namespace

#endif // EE_GIZMOADAPTER_H
