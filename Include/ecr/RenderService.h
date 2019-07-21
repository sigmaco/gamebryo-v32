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
#ifndef EE_RENDERSERVICE_H
#define EE_RENDERSERVICE_H

#include "ecrLibType.h"

#include <efd/ISystemService.h>
#include <ecr/ecrSystemServiceIDs.h>

#include <NiRenderer.h>
#include <NiRenderFrame.h>
#include <NiDefaultClickRenderStep.h>

#include <ecr/SceneGraphService.h>
#include <ecr/RenderContext.h>
#include <ecr/RenderSurface.h>
#include <ecr/IRenderServiceDelegate.h>

namespace ecr
{

// forward declaration
class IDefaultSurfaceCreator;


/**
    The RenderService service manages renderable objects and the renderer itself.

    A platform specific renderer is created at startup, based on parameters provided
    to the constructor or given after construction but before initialization.

    The render service maintains a set of RenderSurface objects, each describing a
    particular render window. Each surface may be associated with a particular
    Ni3DRenderView object that holds the scene graph objects to draw in that surface.
    Typical game applications will have only one surface, while tools may have several.

    Scene graph objects are given to the service to manage, typically by the
    SceneGraphService service. The render service then places the scene graph in the
    appropriate Ni3DRenderView object. Currently, all scene graphs are added to all
    views, but this will likely change in future to give applications control over
    which objects appear in which views.

    On each framework tick, all of the surfaces are updated, which causes them to draw.
*/
class EE_ECR_ENTRY RenderService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(RenderService, efd::kCLASSID_RenderService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:
    /**
        Constructs the render service with a known parent window handle.

        @note The renderer specific data is not allocated or created until the
            service's OnInit method is invoked.

        @param parentHandle Window handle to pass to renderer creation.
    */
    RenderService(NiWindowRef parentHandle = NULL);

    /// @name Default Context and Active Surface Control
    //@{
    /**
        Sets a surface creator for overriding the default creation of the render context and active
        surface that happens during OnInit.

        This method can be called any time after the RenderService is constructed and before it has
        been initialized via OnInit. It is recommended that it be called during OnPreInit of
        another system service.

        @param pCreator Interface for the creation method.
        @return True if this method was called before the creation of an active surface or false
            if there is already an active surface in which case the interface will not be used.
    */
    bool SetDefaultSurfaceCreator(IDefaultSurfaceCreator* pCreator);

    /**
        Sets the background color used when the default context is created during OnInit. If a
        IDefaultSurfaceCreator interface is provided via SetDefaultSurfaceCreator then this color
        is also passed to the creation method (which is free to ignore it).

        This method can be called any time after the RenderService is constructed and before it has
        been initialized via OnInit. It is recommended that it be called during OnPreInit of
        another system service.

        @param color The requested background color.
        @return True if this method was called before the creation of an active surface or false
            if there is already an active surface in which case the color will not be used.
    */
    bool SetDefaultSurfaceBackgroundColor(const efd::ColorA& color);
    //@}

    /// @name Render Surfaces
    //@{
    /// Create a new render surface for the given window.
    ///
    /// The result must be assigned to a smart pointer. This function is platform dependent.
    virtual RenderSurfacePtr CreateRenderSurface(NiWindowRef windowHandle = NULL);

    /// Destroy a render surface.
    ///
    /// This function is platform dependent.
    virtual bool DestroyRenderSurface(RenderSurface* pSurface);

    /// Recreate a render surface, typically in response to renderer recreation.
    ///
    /// This function is platform dependent.
    virtual bool RecreateRenderSurface(RenderSurface* pSurface);
    //@}

    /// @name Render Context Management
    //@{
    /// Get the number of render contexts.
    inline efd::UInt32 GetRenderContextCount() const;

    /// Get the render context at the given index.
    ///
    /// The index is not range checked.
    inline RenderContext* GetRenderContextAt(const efd::UInt32 index);

    /// Add a render context, returning the location of the new context for use with
    /// GetRenderContextAt.
    inline efd::UInt32 AddRenderContext(RenderContext* pContext);

    /// Remove the given render context, returning true if it was found.
    inline efd::Bool RemoveRenderContext(RenderContext* pContext);

    /**
        Remove the render context at the given index.

        The return value must be assigned to a smart pointer variable to
        prevent it from deletion upon removal. The context may be destroyed if it is not
        assigned at all or if assigned to a regular pointer.
    */
    inline RenderContextPtr RemoveRenderContextAt(const efd::UInt32 index);

    /// Find the render surface for the given window among all render surfaces known to
    /// the render contexts.
    RenderSurface* GetRenderSurface(efd::WindowRef window) const;
    //@}

    /**
        @name Active Render Surface

        The Render Service designates one surface as active. In case with only one surface that
        surface is always active. When multiple surfaces are presentit is the application's
        responsibility to designate a particular surface as active.

        The active surface is used by the CameraService class as the recipient of
        camera controlling and update events.
    */
    //@{
    /// Get the current active render surface.
    inline RenderSurface* GetActiveRenderSurface() const;

    /// Set the current active surface to that for the given window.
    void SetActiveRenderSurface(efd::WindowRef window);

    /// Set the current active surface.
    inline void SetActiveRenderSurface(RenderSurface* pSurface);
    //@}

    /// Gets the active render context based on the active render surface.
    inline RenderContext* GetActiveRenderContext() const;

    /// Invalidates the active render context.
    inline void InvalidateRenderContexts() const;

    /**
        @name Rendered Objects

        The RenderService is informed each time the SceneGraphService object creates a new
        scene graph for an entity that has rendering related properties, and each time the
        scene graph is removed.
    */
    //@{
    /// Called when an entity with rendering properties receives a new scene graph.
    virtual void AddRenderedEntity(egf::Entity* pEntity, NiAVObject* pAVObject);

    /// Called when an entity with rendering properties is about to have its scene graph removed.
    virtual void RemoveRenderedEntity(egf::Entity* pEntity, NiAVObject* pAVObject);

    /// Called when a new scene graph, with no entity, must be set up for rendering.
    virtual void AddRenderedObject(
        ecr::SceneGraphService::SceneGraphHandle handle, NiAVObject* pAVObject);

    /// Called when a new scene graph, with no entity, must be removed.
    virtual void RemoveRenderedObject(
        ecr::SceneGraphService::SceneGraphHandle handle, NiAVObject* pAVObject);
    //@}

    /**
        Returns a pointer to the underlying Gamebryo renderer object.

        The underlying type of the returned pointer is platform specific.
    */
    inline NiRenderer* GetRenderer() const;

    /**
        Set the parent handle.

        This is intended to be used when the parent handle is not yet known at RenderService
        creation, such as when the windowing system is initialized within the OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar) of
        another service.  In such cases this must be called before RenderService::OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar)
        is invoked.
    */
    inline void SetParentHandle(NiWindowRef parentHandle);

    /// Get the parent handle.
    inline NiWindowRef GetParentHandle();

    /// Add a render service delegate.
    inline void AddDelegate(IRenderServiceDelegate* pDelegate);

    /// Remove a render service delegate.
    inline void RemoveDelegate(IRenderServiceDelegate* pDelegate);

    /// Raise the surface added event, which invokes IRenderServiceDelegate::OnSurfaceAdded
    inline void RaiseSurfaceAdded(RenderSurface* pSurface);

    /// Raise the surface removed event, which invokes IRenderServiceDelegate::OnSurfaceRemoved
    inline void RaiseSurfaceRemoved(RenderSurface* pSurface);

    /// Raise the surface pre-draw event, which invokes IRenderServiceDelegate::OnSurfacePreDraw
    inline void RaisePreDrawEvent(RenderSurface* pSurface);

    /// Raise the surface post-draw event, which invokes IRenderServiceDelegate::OnSurfacePostDraw
    inline void RaisePostDrawEvent(RenderSurface* pSurface);

protected:

    /// Returns the service name, "RenderService".
    virtual const char* GetDisplayName() const;

    /// The OnPreInit function registers dependencies, reads configuration and sets up default data
    /// structures.
    ///
    /// This function is platform dependent.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /// The OnInit function calls the platform specific CreateRenderer() method and then creates
    /// a default active render surface.
    virtual efd::AsyncResult OnInit();

    /**
        The OnTick function calls Draw on all known RenderContext objects.
    */
    virtual efd::AsyncResult OnTick();

    /**
        Causes the renderer to be finalized and shut down.

        Any rendering specific resources are freed and the render device is destroyed.
        This function is platform dependent.
    */
    virtual efd::AsyncResult OnShutdown();

    typedef efd::list<IRenderServiceDelegate*> DelegateList;

    // Renderer Callbacks
    static bool OnDeviceLost(void* pvData);
    static bool OnDeviceReset(bool bBeforeReset, void* pvData);

    // Empty destructor.
    virtual ~RenderService();

    // Platform specific destruction.
    void InternalDestructor();

    // Used by multiple constructors to initialize members.
    void PrivateInit(const char* pcDefaultMaterialDirectory);

    // Attempts to create the renderer using specified configuration.
    virtual bool CreateRenderer();

    // The parent window associate with the renderer. Not valid on all platforms.
    NiWindowRef m_parentHandle;

    // The renderer doing the work for this service.
    NiRendererPtr m_spRenderer;

    // The set of available render contexts.
    efd::vector<RenderContextPtr> m_renderContexts;

    // The "active" surface, which is the one receiving events, or camera control, etc.
    RenderSurface* m_pActiveSurface;

    // Callback classes for render-service specific events
    DelegateList m_renderServiceDelegates;

    IDefaultSurfaceCreator* m_pDefaultSurfaceCreator;
    NiColorA m_defaultContextBackgroundColor;
};

typedef efd::SmartPointer<RenderService> RenderServicePtr;

} // end namespace ecr

#include "RenderService.inl"

#endif // EE_RENDERSERVICE_H
