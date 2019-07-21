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
#ifndef EE_IRENDERSERVICEDELEGATE_H
#define EE_IRENDERSERVICEDELEGATE_H

#include "ecrLibType.h"
#include <efd/ClassInfo.h>
#include <ecr/ecrClassIDs.h>
#include <egf/Entity.h>
#include <NiAVObject.h>

namespace ecr
{

class RenderSurface;
class RenderService;

/**
    The IRenderServiceDelegate interface allows for a class to implement callback logic for
    common operations within the RenderService, such as RenderSurface creation and destruction.
*/
class EE_ECR_ENTRY IRenderServiceDelegate
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE(IRenderServiceDelegate, efd::kCLASSID_IRenderServiceDelegate);
    /// @endcond
public:

    /**
        Declaring a virtual destructor so that deletions can occur properly.
    */
    virtual ~IRenderServiceDelegate();

    /**
        Called by the RenderService when the RenderSurface is created.
        @param pService Pointer to the RenderService.
        @param pSurface Pointer to the newly created render surface.
    */
    virtual void OnSurfaceAdded(RenderService* pService, RenderSurface* pSurface);

    /**
        Called by the RenderService when the RenderSurface is re-created.
        @param pService Pointer to the RenderService.
        @param pSurface Pointer to the newly created render surface.
    */
    virtual void OnSurfaceRecreated(RenderService* pService, RenderSurface* pSurface);

    /**
        Called by the RenderService when the RenderSurface is about to be destroyed.
        @param pService Pointer to the RenderService.
        @param pSurface Pointer to the render surface that is about to be destroyed.
    */
    virtual void OnSurfaceRemoved(RenderService* pService, RenderSurface* pSurface);

    /**
        Called by the RenderService when the RenderSurface is about to be drawn.
        @param pService Pointer to the RenderService.
        @param pSurface Pointer to the render surface that is about to be drawn.
    */
    virtual void OnSurfacePreDraw(RenderService* pService, RenderSurface* pSurface);

    /**
        Called by the RenderService on a surface that has just been drawn.
        @param pService Pointer to the RenderService.
        @param pSurface Pointer to the render surface that was drawn.
    */
    virtual void OnSurfacePostDraw(RenderService* pService, RenderSurface* pSurface);

    /**
        Called by the RenderService on a surface that has just been drawn.
        @param pService Pointer to the RenderService.
        @param pActiveSurface Pointer to the render surface that is currently active.
        @param pPriorActiveSurface Pointer to the render surface that was active.
    */
    virtual void OnSurfaceActiveChanged(RenderService* pService, RenderSurface* pActiveSurface,
        RenderSurface* pPriorActiveSurface);

    /**
        Called by the RenderService when the RenderService is about to be destroyed.
        @param pService Pointer to the RenderService.
    */
    virtual void OnRenderServiceShutdown(RenderService* pService);

    /**
        Called by the RenderService when an entity is added.
        @param pService Pointer to the RenderService.
        @param pEntity The ID of the newly added entity.
        @param pAVObject The scene graph root of the entity.
    */
    virtual void OnRenderedEntityAdded(RenderService* pService, egf::Entity* pEntity, NiAVObject* pAVObject);

    /**
        Called by the RenderService when an entity is removed.
        @param pService Pointer to the RenderService.
        @param pEntity The ID of the entity that is about to be removed.
        @param pAVObject The scene graph root of the entity.
    */
    virtual void OnRenderedEntityRemoved(RenderService* pService, egf::Entity* pEntity, NiAVObject* pAVObject);
};

} // end namespace ecr


#endif // EE_IRENDERSERVICEDELEGATE_H
