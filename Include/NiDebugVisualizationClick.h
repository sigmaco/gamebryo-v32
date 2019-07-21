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

#ifndef NIDEBUGGEOMETRYCLICK_H
#define NIDEBUGGEOMETRYCLICK_H

#include <NiRenderClick.h>
#include <NiImmediateModeAdapter.h>

NiSmartPointer(NiCamera);
NiSmartPointer(NiLight);
NiSmartPointer(NiAVObject);

/**
    This class implements a simple debug geometry visualizer that can be easily integrated
    into the Frame Rendering System to display additional information about a scene.

    Here is an example of how to use this code in an NiApplication derived application:
    @code
    // Create the debug click
    m_spDebugGeometryClick = NiNew NiDebugVisualizationClick();
    m_spDebugGeometryClick->SetName("Debug visualization click.");
    m_spDebugGeometryClick->SetCamera(m_spCamera);
    m_spDebugGeometryClick->SetClearAllBuffers(false);
    m_spDebugGeometryClick->ClearScene();

    // Create a render step to hold the click and append it to the frame
    NiDefaultClickRenderStep* pkDebugStep = NiNew NiDefaultClickRenderStep;
    pkDebugStep->SetName("Debug visualization step.");
    pkDebugStep->AppendRenderClick(m_spDebugGeometryClick);
    EE_ASSERT(m_spFrame);
    m_spFrame->AppendRenderStep(pkDebugStep);

    // Process the scene to build up a list of things to visualize
    m_spDebugGeometryClick->ProcessScene(m_spScene, NiDebugVisualizationClick::ALL_MASK);
    @endcode

*/
class NIMESH_ENTRY NiDebugVisualizationClick : public NiRenderClick
{
    NiDeclareRTTI;
    NiDeclareFlags(unsigned char);
public:
    /// Visualization mode flags.  These may be combined.
    enum Flags
    {
        /// Display point lights
        POINT_LIGHT_MASK       = 0x01,

        /// Display directional lights
        DIRECTIONAL_LIGHT_MASK = 0x02,

        /// Display spot lights
        SPOT_LIGHT_MASK        = 0x04,

        /// Display all lights (combination of light flags)
        LIGHT_MASK             = 0x07,

        /// Display cameras
        CAMERA_MASK            = 0x08,

        /// Display bounding spheres for nodes
        BOUNDS_MASK            = 0x10,

        /// Display bones
        BONE_MASK             = 0x20,

        /// Display nodes
        NODE_MASK             = 0x40,

        /// Display hierarchy connections
        CONNECTION_MASK       = 0x80,

        /// Display all information (combination of other flags)
        ALL_MASK               = 0xFF
    };

    NiDebugVisualizationClick(NiUInt8 uiMask = ALL_MASK);

    /**
        Used to check whether point lights will be visualized when this
        click is rendered.

        @return True if point light visualizations will be rendered, false if
        they will not.
    */
    bool GetViewPointLights() const;
    /**
        Used to set whether point lights will be visualized when this
        click is rendered.

        @param bNewValue True if point light visualizations should be rendered,
        false if they will not.
    */
    void SetViewPointLights(bool bNewValue);

    /**
        Used to check whether directional lights will be visualized when
        this click is rendered.

        @return True if directional light visualizations will be rendered,
        false if they will not.
    */
    bool GetViewDirectionalLights() const;
    /**
        Used to set whether directional lights will be visualized when this
        click is rendered.

        @param bNewValue True if directional light visualizations should be
        rendered, false if they will not.
    */
    void SetViewDirectionalLights(bool bNewValue);

    /**
        Used to check whether spot lights will be visualized when this
        click is rendered.

        @return True if spot light visualizations will be rendered, false if
        they will not.
    */
    bool GetViewSpotLights() const;
    /**
        Used to set whether spot lights will be visualized when this click is
        rendered.

        @param bNewValue True if spot light visualizations should be rendered,
        false if they will not.
    */
    void SetViewSpotLights(bool bNewValue);

    /**
        Used to check whether cameras will be visualized when this click
        is rendered.

        @return True if camera visualizations will be rendered, false if they
        will not.
    */
    bool GetViewCameras() const;
    /**
        Used to set whether cameras will be visualized when this click is
        rendered.

        @param bNewValue True if camera visualizations should be rendered,
        false if they will not.
    */
    void SetViewCameras(bool bNewValue);

    /**
        Used to check whether bounding spheres will be visualized when this
        click is rendered.

        @return True if bounding sphere visualizations will be rendered, false
        if they will not.
    */
    bool GetViewBounds() const;
    /**
        Used to set whether bounding spheres will be visualized when this click
        is rendered.

        @param bNewValue True if bounding sphere visualizations should be rendered,
        false if they will not.
    */
    void SetViewBounds(bool bNewValue);

    /**
        Used to check whether nodes affecting a skinned mesh bones will be
        visualized as bones when this click is rendered.

        @return True if bone visualizations will be rendered, false if
        they will not.
    */
    bool GetViewBones() const;
    /**
        Used to set whether nodes affecting a skinned mesh bones will be
        visualized when this click is rendered.

        @param bNewValue True if bone visualizations should be rendered, false
        if they will not.
    */
    void SetViewBones(bool bNewValue);

    /**
        Used to check whether nodes will be visualized when this
        click is rendered.

        @return True if node visualizations will be rendered, false if they
        will not.
    */
    bool GetViewNodes() const;
    /**
        Used to set whether nodes will be visualized when this click is
        rendered.

        @param bNewValue True if node visualizations should be rendered, false
        if they will not.
    */
    void SetViewNodes(bool bNewValue);

    /**
        Used to check whether hierarchical connections between nodes will
        be visualized as colored lines when this click is rendered.

        @return True if hierarchical connection visualizations will be rendered,
        false if they will not.
    */
    bool GetViewConnections() const;
    /**
        Used to set whether nodes will be visualized when this click is
        rendered.

        @param bNewValue True if node visualizations should be rendered, false
        if they will not.
    */
    void SetViewConnections(bool bNewValue);

    /**
        Used to add a scene root node that will be searched for items to be
        visualized by a subsequent call to the ProcessScene function.  Note
        that the list of items to be visualized will not be updated until
        ProcessScene is called.

        @param pkRoot The root node of the scene to add to the list of scenes
        which will be searched for objects to visualize.
    */
    void AddRoot(NiAVObject* pkRoot);
    /**
        Used to remove a scene root node from the search for items to be
        visualized by a subsequent call to the ProcessScene function.  Note
        that the list of items to be visualized will not be updated until
        ProcessScene is called.

        @param pkRoot The root node of the scene to remove from the list of
        scenes which will be searched for objects to visualize.
    */
    void RemoveRoot(NiAVObject* pkRoot);
    /**
        Used to remove all scene root nodes from the search for items to be
        visualized by a subsequent call to the ProcessScene function.  Note
        that the list of items to be visualized will not be updated until
        ProcessScene is called.
    */
    void ClearRoots();
    /**
        Internally records a list of items to visualize by recursively parsing
        the scenes previously added with the AddRoot function.  If the scene
        changes, or if AddRoot, RemoveRoot, or ClearRoots are called, this
        function should be called again to apply the changes to the list of
        objects to visualize.
    */
    void ProcessScene();


    /// @name Camera control
    //@{

    /// Set the camera to use when rendering the debug visualization.
    void SetCamera(NiCamera* pkCamera);

    /// Get the camera that will be used to render the debug visualization.
    const NiCamera* GetCamera() const;

    // Extend the near and far planes to encompass the debug visualization geometry.
    void ExtendCameraNearAndFar(NiCamera* pkCamera) const;

    //@}

    /// @name Screen scale control
    //@{

    /**
        The camera and light debug visualizations all have a default scale set by
        NiImmediateModeMacro::GetScreenScaleFactor().  This can be further scaled
        up or down by specifying a screen scale multipler

        @param fScreenMultiplier  Multiplier value (1.0 = no adjustment)
      */
    void SetScreenMultiplier(float fScreenMultiplier);

    /// Get the current screen scale multiplier
    float GetScreenMultiplier() const;

    //@}

    // Implementation of NiRenderClick API
    virtual unsigned int GetNumObjectsDrawn() const;
    virtual float GetCullTime() const;
    virtual float GetRenderTime() const;
protected:
    virtual void PerformRendering(unsigned int uiFrameID);
    virtual void PerformProcessing(NiAVObject* pkObject);

    /**
    Empty one or more of the internal lists of debug visualization information.

    @param uiClearMask  A combination of one or more flags indicating which lists
                        should be cleared
    */
    void ClearScene(unsigned int uiClearMask = ALL_MASK);


    static void ExpandFrustumNearFar(
        NiCamera* pkCamera,
        NiFrustum& kFrust,
        const NiPoint3& kCenter,
        float fRadius);

    float m_fCullTime;
    float m_fRenderTime;
    unsigned int m_uiNumObjectsDrawn;

    float m_fScreenMultiplier;

    NiTObjectSet<NiCameraPtr> m_kCameras;
    NiTObjectSet<NiLightPtr> m_kLights;
    NiTObjectSet<NiAVObjectPtr> m_kBounds;

    NiImmediateModeAdapter m_kAdapter;
    NiUInt8 m_uiSettingsMask;
    NiTObjectSet<NiAVObjectPtr> m_kSceneRoots;
};

NiSmartPointer(NiDebugVisualizationClick);

#endif  // #ifndef NIDEBUGGEOMETRYCLICK_H
