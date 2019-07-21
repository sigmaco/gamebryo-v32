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
#ifndef EE_SELECTIONSERVICE_H
#define EE_SELECTIONSERVICE_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <ecr/RenderService.h>
#include <ecr/SceneGraphService.h>
#include <ecr/PickService.h>
#include <ecr/CoreRuntimeMessages.h>
#include <ecr/ecrSystemServiceIDs.h>

#include <egf/Entity.h>

#include <Ni3DRenderView.h>
#include <NiAccumulatorProcessor.h>
#include <NiMeshScreenElements.h>
#include <NiAlphaSortProcessor.h>
#include <NiMesh2DRenderView.h>

#include "ToolServicesMessages.h"

#include "SelectionAdapter.h"

#include "IInteractionDelegate.h"

class NiSingleShaderMaterial;
class NiViewRenderClick;

namespace efd
{
    class MessageService;
    class StreamMessage;
}

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY SelectionService
    : public efd::ISystemService
    , public ecr::IRenderServiceDelegate
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS2(
        SelectionService,
        efd::kCLASSID_SelectionService,
        efd::ISystemService,
        ecr::IRenderServiceDelegate);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:
    /**
        The selection mode is the current policy being used when selection is changed.
    */
    enum SelectionMode
    {
        SELECTIONMODE_REPLACE = 0,
        SELECTIONMODE_ADD,
        SELECTIONMODE_SUBTRACT,
        SELECTIONMODE_INVERT,
    };

public:
    /**
        Constructs the selection service and performs any pre-init operations.
    */
    SelectionService();

    /**
    Gets the adapter.
    
    @return null if it fails, else the adapter.
    */
    template< typename T >
    inline T* GetAdapter() const;

    /**
    Gets an adapter. 
    
    @param pAdapter The adapter.
    
    @return true if it succeeds, false if it fails.
    */
    template< typename T >
    inline bool GetAdapter(T*& pAdapter) const;

    /**
    Adds an adapter. 
    
    @param pAdapter The adapter.
    */
    template< typename T >
    inline void AddAdapter(SelectionAdapter* pAdapter);

    /**
    Adds an adapter. 
    
    @param pAdapter The adapter.
    */
    inline void AddAdapter(SelectionAdapter* pAdapter);

    /**
    Removes the adapter described by pAdapter. 
    
    @param pAdapter The adapter.
    */
    template< typename T >
    inline void RemoveAdapter(SelectionAdapter* pAdapter);

    /**
    Removes the adapter described by pAdapter. 
    
    @param pAdapter The adapter.
    */
    inline void RemoveAdapter(SelectionAdapter* pAdapter);

    virtual Ni3DRenderView* GetSelectionView();

    virtual bool IsSelectingMultiple() const;
    virtual bool IsSelectingAlternative() const;

    virtual SelectionMode GetSelectionMode() const;

    virtual void Select(ecr::RenderSurface* pSurface, efd::SInt32 x, efd::SInt32 y);

    virtual void SetSelectionRectangle(int x0, int y0, int x1, int y1, int width, int height);
    virtual void ClearSelectionRectangle();
    virtual void AddSelectionRectangle();

    /**
        Handle an input action change event.
        @param pMsg The input message.
        @param targetChannel Channel the message was sent on.
     */
    virtual void HandleInputAction(
        const egmToolServices::InputActionMessage* pMsg,
        efd::Category targetChannel);

    /**
        Called by the RenderService when the RenderSurface is created.
        @param pService Pointer to the RenderService.
        @param pSurface Pointer to the newly created render surface.
    */
    virtual void OnSurfaceAdded(
        ecr::RenderService* pService,
        ecr::RenderSurface* pSurface);

    /**
        Overridden from IRenderServiceDelegate to apply the selection UI to the render view
        of the surface.
        @param pService The render service.
        @param pSurface The surface that was recreated.
    */
    virtual void OnSurfaceRecreated(
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

    /**
        Overridden from IRenderServiceDelegate to ensure that the selected object's render
        click matches the main scene's render click.
        @param pService The render service.
        @param pSurface The surface that was recreated.
    */
    virtual void OnSurfacePreDraw(
        ecr::RenderService* pService,
        ecr::RenderSurface* pSurface);

protected:
    /**
        Cleans up any remaining resources used by the selection service.
    */
    virtual ~SelectionService();

    virtual const char* GetDisplayName() const;
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnShutdown();

    class EE_EGMTOOLSERVICES_ENTRY NiSelectionViewRenderClick : public NiViewRenderClick
    {
    public:
        NiSelectionViewRenderClick(SelectionService* pSelectionService);

        virtual void PerformRendering(unsigned int uiFrameID);

    protected:
        SelectionService* m_pSelectionService;
    };

    void SetupScreenFillingRenderViews(ecr::RenderSurfacePtr spSurface);
    void CreateRenderedTextureTargets(ecr::RenderSurface* pSurface);

    efd::MessageService* m_pMessageService;
    ecr::PickServicePtr m_spPickService;
    ecr::RenderServicePtr m_spRenderService;
    ecr::SceneGraphServicePtr m_spSceneGraphService;

    NiVisibleArray m_visibleArray;

    NiCullingProcessPtr m_spCuller;
    Ni3DRenderViewPtr m_spSelectionRenderView;
    NiAlphaSortProcessorPtr m_spAlphaSortProcessor;

    NiMesh2DRenderViewPtr m_spSelectionView;
    NiMeshScreenElementsPtr m_spSelectionRect;
    efd::vector<NiMeshScreenElementsPtr> m_spSelectionLines;

    typedef efd::map<efd::ClassID, SelectionAdapterPtr> AdapterMap;
    AdapterMap m_adapters;

    SelectionAdapterPtr m_activeAdapter;

    efd::Bool m_mutliSelecting;
    efd::Bool m_alternativeSelecting;
};

#include "SelectionService.inl"

typedef efd::SmartPointer<SelectionService> SelectionServicePtr;

} // namespace

#endif // EE_SELECTIONSERVICE_H
