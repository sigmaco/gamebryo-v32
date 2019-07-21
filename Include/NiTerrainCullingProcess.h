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

#ifndef NITERRAINCULLINGPROCESS_H
#define NITERRAINCULLINGPROCESS_H

#include "NiTerrainLibType.h"
#include "NiMeshCullingProcess.h"

class NITERRAIN_ENTRY NiTerrainCullingProcess : public NiMeshCullingProcess
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond

public:
    /**
        The default public constructor.
        @param pkVisibleSet Pointer to the visible set to use with this
            culling process. NULL may be passed if the application intends to
            provide a visible set to the call to Cull.
        @param pkWorkflowManager The workflow manager for this culling process.
            Applications may pass NULL in for the workflow manager. If so,
            NiTerrainCullingProcess will create one from the heap.
    **/
    NiTerrainCullingProcess(NiVisibleArray* pkVisibleSet,
        NiSPWorkflowManager* pkWorkflowManager);

    /**
        Defines the maximum level of detail that a terrain will be culled to
        through this culling process.
    */
    //@{
    void SetMaxTerrainLOD(NiUInt32 uiMaxLOD);
    NiUInt32 GetMaxTerrainLOD() const;
    //@}

    /**
        Force a culled terrain to add cells of at least the specified detail
        level, no lower. If the terrain does not contain any cells of the given
        detail level, the highest available detail level will be used.
    */
    //@{
    void SetMinTerrainLOD(NiUInt32 uiMinLOD);
    NiUInt32 GetMinTerrainLOD() const;
    //@}

    /**
        Enable/disable updating the geometry while performing a culling pass.
        Turning off 'geometry updating' can be useful when performing a culling pass,
        but you don't intend to render the results.
    */
    //@{
    void SetUpdateGeometry(bool bUpdateGeometry);
    bool GetUpdateGeometry() const;
    //@}

    /**
        Enable/disable rendering decals on the terrain. By default decal rendering
        is enabled. This is primarily used by the shadowing system to disable
        rendering of decals while rendering to a shadow map.
    */
    //@{
    void SetRenderDecals(bool bRenderDecals);
    bool GetRenderDecals() const;
    //@}

    /// Simple factory method for creating a NiTerrainCullingProcess. This method
    /// is registered as a NiShadowManager::CreateShadowCullingProcess call back.
    /// Note: Decal rendering will be disabled by default for the culling process
    /// returned by this method.
    static NiCullingProcess* CreateTerrainCullingProcess();

protected:

    NiUInt32 m_uiMaxLOD;
    NiUInt32 m_uiMinLOD;
    bool m_bUpdateGeometry;
    bool m_bRenderDecals;
};

#endif // NITERRAINCULLINGPROCESS_H