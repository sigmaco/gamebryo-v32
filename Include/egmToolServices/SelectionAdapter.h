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
#ifndef EE_SELECTIONADAPTER_H
#define EE_SELECTIONADAPTER_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <efd/Point3.h>
#include <efd/Matrix3.h>

#include <NiAVObject.h>
#include <Ni3DRenderView.h>

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY SelectionAdapter : public efd::IBase
{
    EE_DECLARE_CLASS1(SelectionAdapter, kCLASSID_SelectionAdapter, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;

public:
    virtual ~SelectionAdapter() { }

    virtual void OnAdded() = 0;
    virtual void OnRemoved() = 0;

    /**
    Query if this object has selection. 
    
    @return true if selection, false if not.
    */
    virtual efd::Bool HasSelection() const = 0;

    /**
    Clears a selection. 
    */
    virtual void ClearSelection() = 0;

    /**
    Gets the selection bound. 
    
    @return The bound.
    */
    virtual NiBound GetBound() = 0;

    /**
    Gets the selection center. 
    
    @return The center.
    */
    virtual efd::Point3 GetCenter() = 0;

    /**
    Selects the entity closest to the camera using the ray determined by the specified parameters.
    
    @param pSurface The surface.
    @param x The x coordinate.
    @param y The y coordinate.
    @param origin The origin.
    @param direction The direction.
    
    @return true if it succeeds, false if it fails.
    */
    virtual efd::Bool Select(
        ecr::RenderSurface* pSurface,
        efd::SInt32 x,
        efd::SInt32 y,
        const efd::Point3& origin,
        const efd::Point3& direction) = 0;

    /**
    Select frustum.
    
    @param pCamera The camera.
    @param pCuller The culler.
    
    @return true if it succeeds, false if it fails.
    */
    virtual efd::Bool SelectFrustum(NiCamera* pCamera, NiMeshCullingProcess* pCuller) = 0;

    /**
    Renders a selection.
    
    @param pRenderService The render service.
    @param uiFrameID Identifier for the frame.
    */
    virtual void RenderSelection(
        ecr::RenderService* pRenderService,
        unsigned int uiFrameID) = 0;
};

typedef efd::SmartPointer<SelectionAdapter> SelectionAdapterPtr;

}; // egmToolServices namespace

#endif // EE_SELECTIONADAPTER_H
