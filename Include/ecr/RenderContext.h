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
#ifndef EE_RENDERCONTEXT_H
#define EE_RENDERCONTEXT_H

#include "ecrLibType.h"

#include <egf/Entity.h>

#include <NiRenderFrame.h>
#include <NiDefaultClickRenderStep.h>
#include <Ni3DRenderView.h>
#include <NiAccumulatorProcessor.h>
#include <NiAnimation.h>
#include <NiCullingProcess.h>
#include <NiVisibleArray.h>

#include "RenderSurface.h"
#include "SceneGraphService.h"

namespace ecr
{

// DT32476 The current arrangement of data in ecr::RenderContext and ecr::RenderSurface
// is messy and not cleanly delineated. It should be refactored to clarrify the meaning
// of each class.

// DT32477 We would like to add support for different sort processors. It is currently always
// a Shader Sort Processor. We would also like to add support for custom culling processes.
// Right now the source must be modified, or complex sub-classing performed.

/**
    A RenderContext object is used to group several render surfaces all rendering the same scene
    contents, but from potentially different cameras or with different rendering effects (e.g.,
    wireframe mode).

    Multiple contexts should be used when different surfaces must displays different sets of
    objects, or must use significantly different steps for rendering.  Each RenderContext holds a
    single Gamebryo NiRenderFrame object representing the entire process to use for rendering
    within the surfaces owned by the context.  In addition, callback mechanisms are provided to
    enable applications to make per-surface modifications to the rendering steps.
*/
class EE_ECR_ENTRY RenderContext : public efd::MemObject
{
    EE_DECLARE_CONCRETE_REFCOUNT;

public:
    /// Constructor.
    ///
    /// The RenderService object must be non-NULL.  If pRenderView is NULL, a default 3D render
    /// view will be used.
    RenderContext(RenderService* pRenderService,
        Ni3DRenderView* pRenderView = NULL);

    /// Destructor.
    ///
    /// Clears the list of render surfaces held by the context and deletes any rendering data.
    virtual ~RenderContext();

    /// Draw all surfaces in the context.
    ///
    /// Pre- and Post- Draw Events will be raised for each surface.
    virtual void Draw(efd::Float32 currentTime);

    /// Sets a value indicating if the render context should check if the frame has been
    /// invalidated before doing any drawing, and also controls if it should validate the frame
    /// when complete.
    inline efd::Bool GetValidateFrames();
    inline void SetValidateFrames(efd::Bool validate);

    /// Invalidates the frame so that the next tick should force a new draw.
    inline void Invalidate();

    /**
        @name Render Surfaces

        The render context object holds a vector of smart pointers to RenderSurface objects.  The
        Draw operation is applied to every surface using the NiRenderFrame object held within this
        object.
    */
    //@{
    /**
        Add a new render surface to the context.

        @param spSurface The surface to add to the current render context
        @param pCustomRenderListProcessor Optional render list processor that can be used to 
            specify rendering order of meshes
    */
    void AddRenderSurface(RenderSurfacePtr spSurface, 
        NiRenderListProcessor* pCustomRenderListProcessor = NULL);

    /**
        Removes a render surface from the render service.

        @param pSurface The surface to remove.
        @return True if successful, false otherwise.
    */
    void RemoveRenderSurface(RenderSurface* pSurface);

    /**
        Removes a render surface from the render service.

        @param window The window handle for the surface.  Note, on some platforms, this parameter
            has no meaning.
        @return True if successful, false otherwise.
    */
    void RemoveRenderSurface(efd::WindowRef window);

    /**
        Get the first render surface with a window matching the argument.
    */
    RenderSurface* GetRenderSurface(efd::WindowRef window) const;

    /**
        Get the render surface at the given index.
    */
    RenderSurface* GetRenderSurfaceAt(efd::UInt32 index) const;

    /**
        Get the number of render surfaces available.
    */
    inline efd::UInt32 GetRenderSurfaceCount() const;

    //@}

    /**
        @name Rendering Control Functions
    */
    //@{
    /// Set the background color.
    void SetBackgroundColor(const NiColorA& kColor);

    /// Return the culling process currently in use by the context.
    inline NiCullingProcess* GetCullingProcess();
    //@}

    /**
        @name Rendered Scene Functions
    */
    //@{
    /// Called when an entity with rendering properties receives a new scene graph.
    virtual void AddRenderedEntity(egf::Entity* pEntity, NiAVObject* pAVObject);

    /// Called when an entity with rendering properties is about to have its scene graph removed.
    virtual void RemoveRenderedEntity(egf::Entity* pEntity, NiAVObject* pAVObject);

    /// Called when an entity with rendering properties receives a new scene graph.
    virtual void AddRenderedObject(SceneGraphService::SceneGraphHandle handle,
        NiAVObject* pAVObject);

    /// Called when an entity with rendering properties is about to have its scene graph removed.
    virtual void RemoveRenderedObject(SceneGraphService::SceneGraphHandle handle,
        NiAVObject* pAVObject);
    //@}

protected:
    void RaiseSurfaceAdded(RenderSurface* pSurface);
    void RaiseSurfaceRemoved(RenderSurface* pSurface);
    void RaisePreDrawEvent(RenderSurface* pSurface);
    void RaisePostDrawEvent(RenderSurface* pSurface);

    RenderService* m_pRenderService;    // Not a smart pointer to avoid circular dependencies.

    efd::vector<RenderSurfacePtr> m_renderSurfaces;

    // Frame rendering objects.
    Ni3DRenderViewPtr m_spMainRenderView;
    NiRenderListProcessorPtr m_spRenderListProcessor;
    NiCullingProcessPtr m_spCuller;
    NiVisibleArray m_visibleArray;
    NiColorA m_backgroundColor;

    efd::Bool m_invalid;
    efd::Bool m_validate;
};

typedef efd::SmartPointer<RenderContext> RenderContextPtr;

}; // namespace

#include "RenderContext.inl"

#endif // EE_RENDERCONTEXT_H
