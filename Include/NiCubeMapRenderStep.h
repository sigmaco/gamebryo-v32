// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef NICUBEMAPRENDERSTEP_H
#define NICUBEMAPRENDERSTEP_H

#include "NiEnvironmentLibType.h"
#include <NiNode.h>
#include <NiRenderer.h>
#include <NiRenderStep.h>
#include <NiRenderedCubeMap.h>
#include <NiRenderTargetGroup.h>
#include <NiMeshCullingProcess.h>

/**
    This class implements a render step that is capable of rendering a scene from 6 different
    camera angles into the 6 camera faces of a supplied NiRenderedCubeMap object. It also
    supports functionality to pull the rendered faces back to system memory for export to files
    if necessary.
*/
class NIENVIRONMENT_ENTRY NiCubeMapRenderStep : public NiRenderStep
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    NiDeclareFlags(unsigned short);
    /// @endcond

public:

    /**
        Method for constructing a NiCubeMapRenderStep. The render step will
        render the scene from 6 different camera angles to the 6 camera faces
        of the supplied CubeMap. This rendering will take place from the 
        position of the reference object.

        @param pkMap The cube map to render to
        @param pkRenderer The renderer to use when rendering the scene
        @param pkScene The scene to render to the cubemap
        @param pkReference The object to have at the center of the scene
    */
    static NiCubeMapRenderStep* Create(NiRenderedCubeMap* pkMap, 
        NiRenderer* pkRenderer, NiNode* pkScene, NiAVObject* pkReference);
    
    /**
        Destructor.
    */
    ~NiCubeMapRenderStep();

    /**
        Get the number of faces updated per frame.
    */
    unsigned int GetCamerasPerUpdate();

    /**
        Set the number of faces updated per frame.
    */
    void SetCamerasPerUpdate(unsigned int uiNum);

    /**
        Set whether or not to swap left and right when rendering the cubemap.
        When rendering a reflection cubemap left and right should be swapped.
    */
    inline void SetSwapLeftRight(bool bSwapLeftRight);

    /**
        Get whether or not left and right will be swapped when rendering.
    */
    inline bool GetSwapLeftRight();

    /**
        Set the background color to clear to when rendering a face.
    */
    inline void SetBackgroundColor(const NiColorA& kColor);

    /**
        Get the background color to clear the cubemap to.
    */
    inline void GetBackgroundColor(NiColorA& kColor);

    /**
        Set whether or not the renderer's background color should be used.
    */
    inline void SetUseRendererBackgroundColor(bool bUseRendererBG);

    /**
        Get whether or not the renderer's background color should be used.
    */
    inline bool GetUseRendererBackgroundColor();

    /**
        Set whether or not the render step's background color should persist
        after execution.
    */
    inline void SetPersistBackgroundColorToRenderer(bool bPersist);
    
    /**
        Get whether or not the render step's background color should persist.
        after execution.
    */
    inline bool GetPersistBackgroundColorToRenderer();

    /**
        Generate a NiPixelData object from one of the faces of the rendered
        cube map. Useful for exporting a rendered image to disk.

        @param uiFaceID The face ID of the face to generate a NiPixelData for
    */
    NiPixelData* TakeScreenshot(NiRenderedCubeMap::FaceID uiFaceID);

    /**
        Function for setting the render target group that will
        contain the final output for this render step.
    */
    virtual bool SetOutputRenderTargetGroup(
        NiRenderTargetGroup* pkOutputRenderTargetGroup);

    /**
        Function for getting the render target group that will
        contain the final output for this render step.
    */
    virtual NiRenderTargetGroup* GetOutputRenderTargetGroup();

    /**
        Reports the number of objects drawn in the most recent frame
        @see NiRenderStep
    */
    virtual unsigned int GetNumObjectsDrawn() const;

    /**
        Reports the amount of time spent culling in the most recent frame
        @see NiRenderStep
    */
    virtual float GetCullTime() const;

    /**
        Reports the amount of time spent rendering the most recent frame
        @see NiRenderStep
    */
    virtual float GetRenderTime() const;

protected:

    /**
        Constructor
        @param pkScene The scene that will be rendered.
    */
    NiCubeMapRenderStep(NiNode* pkScene);

    /**
        Perform the rendering operations of the render step. 
        @see NiRenderStep
    */
    virtual void PerformRendering();

    /// A set of Enums for use in the object's bitfield
    enum 
    {
        /// If set, the render step will swap left/right when rendering
        SWAP_LEFT_RIGHT = 0x0001,

        /// If set, the render step will use the default bgcolor when rendering
        USE_RENDERER_BG_COLOR = 0x0002,

        /// If set, the render step will leave it's bgcolor set on the renderer even after 
        /// execution of the render step
        PERSIST_BG_COLOR = 0x0004
    };

    /// The scene to render to the cubemap
    NiNodePtr m_spScene;

    /// An object that represents the center of the cubemap from which to render
    NiAVObjectPtr m_spReference;

    /// The cube map that is being rendered
    NiRenderedCubeMapPtr m_spRenderedTexture;

    /// The background color to use when rendering
    NiColorA m_kBackgroundColor;
    
    /// The number of faces of the cube to render during each frame
    unsigned int m_uiCamerasPerUpdate;

    /// The ID of the last face of the cube to be rendered
    unsigned int m_uiLastUpdatedCamera;

    /// An array of render targets, one for each face of the cube map
    NiRenderTargetGroupPtr 
        m_aspRenderTargetGroups[NiRenderedCubeMap::FACE_NUM];
     
    /// The visible array used to store visible objects for rendering
    NiVisibleArray m_kVisible;

    /// The culling process used to cull objects during rendering
    NiMeshCullingProcess m_kCuller;

    /// The camera used to render the faces of the cube map
    NiCameraPtr m_spCamera;

    /// Renderer used to render the faces of the cube map
    NiRendererPtr m_spRenderer;

    ///@name Rendering statistics
    //@{

    /// Total number of objects drawn by the last execution of this render step
    unsigned int m_uiNumObjectsDrawn;

    /// Time spent culling objects by the last execution of this render step
    float m_fCullTime;

    /// Time spent rendering objects by the last execution of this render step
    float m_fRenderTime;
    //@}
};

NiSmartPointer(NiCubeMapRenderStep);

#include "NiCubeMapRenderStep.inl"

#endif // NICUBEMAPRENDERSTEP_H
