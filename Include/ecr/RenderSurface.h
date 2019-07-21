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
#ifndef EE_RENDERSURFACE_H
#define EE_RENDERSURFACE_H

#include "ecrLibType.h"

#include <efd/ISystemService.h>

#include <NiCamera.h>
#include <NiRenderFrame.h>
#include <NiDefaultClickRenderStep.h>
#include <NiViewRenderClick.h>

namespace ecr
{

class RenderContext;
class RenderService;

/**
    This class wraps the concept of a render window or render surface.

    This is useful for things like tools that may want to render to several
    different windows or controls. Most client side game related
    applications would only have one of these that represents the primary
    surface.
*/
class EE_ECR_ENTRY RenderSurface : public NiRefObject
{
public:
    /**
        Destructor.

        @note The back buffer is not destroyed if this render surface refers to the primary
            back buffer. The renderer itself is responsible for this behavior.
    */
    virtual ~RenderSurface();

    /**
        @name Frame Rendering Interface
    */
    //@{
    /// Get a pointer to the render click used to draw the main scene.
    inline NiViewRenderClick* GetSceneRenderClick() const;

    /**
        Set the primary 'scene' render click.

        The existing click is replaced in the render step object's list of clicks, if present,
        and most of its properties are copied to the new click. Otherwise,
        the new render click is appended to the end of the render step obejct's list of clicks.
    */
    void SetMainRenderClick(NiViewRenderClick* pRenderClick);

    /**
        Gets the render target group with which the render surface is bound
        to.

        All rendering is done to this render target group.

        @return The render target group for the render surface.

        @note This render target group is the primary render target
            group in the render frame. There may be more render target
            groups in a frame depending on the render steps that have been
            added. However, this render target group always refers to the
            back-buffer of the render surface.
    */
    inline NiRenderTargetGroup* GetRenderTargetGroup();

    /**
        Gets the render frame for this render surface.

        The render frame is the primary component of the frame rendering system and controls
        the rendering of a frame.
    */
    inline NiRenderFrame* GetRenderFrame();

    /**
        Get the default NiRenderStep object for this surface.

        By default, a click render step is created and registered with the
        render frame on this surface. The render target group for the
        default render step is attached to this surface's back buffer.

        @return The default render step for this render surface.
    */
    NiRenderStep* GetRenderStep();
    //@}

    /**
        Gets the default camera used for rendering to this render surface.

        On construction of a new RenderSurface object, the default camera is a newly
        allocated camera with all default parameters (see the NiCamera class documentation).

        @return The default camera.
    */
    inline NiCamera* GetCamera();

    /**
        Set the default camera to be used for rendering to this render surface.

        @param pCamera The new camera to use when rendering to this render surface.
    */
    inline void SetCamera(NiCamera* pCamera);

    /**
        Gets the window handle for this render surface. Note, on some
        platforms this handle has no meaning.

        @return The window handle.
    */
    inline efd::WindowRef GetWindowRef();

    /// Gets the render context that this render surface is part of.
    inline RenderContext* GetContext();

    /// Performs the draw, calling Draw and Display on the Render Frame object.
    ///
    /// The currentTime parameter is unused.
    void Draw(efd::Float32 currentTime);

protected:

    /**
    Constructs the render surface entry. An NiRenderFrame for the
    render surface is created as well as a default render step. The
    render step is then automatically added to the render frame.

    @param windowHandle The window handle that the surface is bound to.
       Note, on certain platforms this parameter is meaningless.
    @param pService A pointer to the render service creating the surface.
    */
    RenderSurface(efd::WindowRef windowHandle, RenderService* pService);

    efd::WindowRef m_windowRef;

    NiRenderFramePtr m_spRenderFrame;
    NiRenderStepPtr m_spRenderStep;
    NiViewRenderClickPtr m_spSceneRenderClick;
    NiCameraPtr m_spCamera;
    RenderContext* m_pRenderContext;
    RenderService* m_pRenderService;

    friend class RenderContext;
    friend class RenderService;
};
typedef efd::SmartPointer<RenderSurface> RenderSurfacePtr;

}; // namespace

#include "RenderSurface.inl"

#endif // EE_RENDERSURFACE_H
