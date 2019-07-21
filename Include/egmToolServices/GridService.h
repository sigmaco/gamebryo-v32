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
#ifndef EE_GRIDSERVICE_H
#define EE_GRIDSERVICE_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <efd/ISystemService.h>
#include <NiColor.h>
#include <NiMesh.h>

#include <ecr/RenderService.h>
#include <ecr/ecrSystemServiceIDs.h>

#include "ToolSceneService.h"

namespace egmToolServices
{

/**
    The GridService is responsible for constructing and managing grid meshes
    used to help visualize scale in scenes.
*/
class EE_EGMTOOLSERVICES_ENTRY GridService : public efd::ISystemService,
                                             public ecr::IRenderServiceDelegate
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS2(
        GridService,
        efd::kCLASSID_GridService,
        efd::ISystemService,
        ecr::IRenderServiceDelegate);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:
    GridService();

    /**
    */
    virtual const char* GetDisplayName() const;

    /**
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();

    void DeleteGrid();

    void SetDisplayGrid(bool flag);
    void SetMinorLineColor(const NiColor& color);
    void SetMajorLineColor(const NiColor& color);
    void SetMinorLineSpacing(float spacing);
    void SetMajorLineSpacing(float spacing);
    void SetExtents(float extents);

    bool GetDisplayGrid();

    void ToggleDisplayGrid();

    inline float GetVerticalInterval();
    inline void SetVerticalInterval(float interval);
    inline bool GetUseVerticalInterval();
    inline void SetUseVerticalInterval(bool useInterval);

    NiPoint3 PickOnGrid(const NiPoint3& rayOrigin, const NiPoint3& rayDirection);

    // IRenderServiceDelegate Members
    virtual void OnSurfacePreDraw(ecr::RenderService* pService, ecr::RenderSurface* pSurface);

    virtual void RequestRebuildGrid();

protected:
    virtual ~GridService();

    class GridSection
    {
    public:
        GridSection() : MajorLines(NULL), MinorLines(NULL)
        {
        }

        NiMeshPtr MajorLines;
        NiMeshPtr MinorLines;
        ecr::SceneGraphService::SceneGraphHandle MajorLinesHandle;
        ecr::SceneGraphService::SceneGraphHandle MinorLinesHandle;
    };

    void ConstructStaticGrid();
    void RebuildGrid();
    GridSection* CreateGridSection();

    ecr::RenderService* m_pRenderService;
    ToolSceneGraphServicePtr m_spSceneGraphService;

    NiMeshPtr m_spMajorLines;
    NiMeshPtr m_spMinorLines;
    ecr::SceneGraphService::SceneGraphHandle m_majorLinesHandle;
    ecr::SceneGraphService::SceneGraphHandle m_minorLinesHandle;

    efd::vector<GridSection*> m_gridSections;

    bool m_displayGrid;

    NiColor m_minorLineColor;
    NiColor m_majorLineColor;

    float m_minorLineSpacing;
    float m_majorLineSpacing;

    float m_extents;

    bool m_useVerticalInterval;
    float m_verticalInterval;

    bool m_rebuildGridRequested;
};

typedef efd::SmartPointer<GridService> GridServicePtr;

} // namespace

#include "GridService.inl"

#endif // EE_GRIDSERVICE_H
