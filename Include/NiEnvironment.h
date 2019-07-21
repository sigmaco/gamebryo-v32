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

#ifndef NIENVIRONMENT_H
#define NIENVIRONMENT_H

#include <NiNode.h>
#include <NiDirectionalLight.h>

#include "NiFogProperty.h"
#include "NiAtmosphere.h"
#include "NiSkyDome.h"
#include "NiCubeMapRenderStep.h"

/**
    The NiEnvionment class is used to encapsulate all the settings related to
    specifying an environment that a scene belongs in. The framework that is 
    provided by the NiEnvironment library will allow sky, fog, clouds, and 
    general scene lighting parameters to be specified in one place, whilst 
    allowing that configuration to be easily modified, animated, saved/loaded,
    and captured. 
*/
class NIENVIRONMENT_ENTRY NiEnvironment : public NiNode
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:

    /**
        Constructor.
    */
    NiEnvironment();

    /**
        Destructor.
    */
    ~NiEnvironment();

    /**
        Create a new atmosphere object for the environment to use in atmospheric
        coloring calculations. The created object is automatically assigned to
        this environment object. 

        @return The created atmosphere object (ready for configuration).
    */
    NiAtmosphere* CreateAtmosphere();

    /**
        Sets the atmosphere object used by the objects in this Environment.

        @param pkAtmosphere The atmosphere object to associate with the 
            environment
    */
    void SetAtmosphere(NiAtmosphere* pkAtmosphere);

    /**
        Gets the atmosphere object being used by this environment.
    */
    NiAtmosphere* GetAtmosphere();

    /**
        Creates a new SkyDome object and sets it as the sky 
        object for this environment. A NiSkyDome is a procedurally generated
        hemisphere mesh. It has useful configuration parameters that allow
        the distribution of the vertices to be adjusted.

        @return The created NISkyDome ready for configuration.
    */
    NiSkyDome* CreateSkyDome();

    /**
        Set the sky object to use when rendering the environment. This object
        represents the geometry object that the sky will be rendered upon. 
        (This could be a skybox, or a skydome etc). 

        @param pkSky The sky object to render the sky with. 
    */
    void SetSky(NiSky* pkSky);

    /**
        Get the sky object that is used to render the sky.
    */
    NiSky* GetSky();

    /**
        Create a directonal light for use as the sun. The created sun will be 
        automatically applied to this environment object.
    */
    NiDirectionalLight* CreateSun();

    /**
        Assign a specific directonal light to be used as a sun by this 
        environment object. Generally this light will also need to be applied 
        to the root node of the scene. This light is used by the atmosphere 
        shaders to calculate where the sun is in the sky. It also allows 
        any animation of the sun to be automated through the Environment object.
    */
    void SetSun(NiDirectionalLight* pkSun);

    /**
        Get the directional light that is being used as the sun by this 
        environment object.
    */
    NiDirectionalLight* GetSun();

    /**
        Create a new fog property to be used by the environment system. This
        object will automatically be assigned to this object.
    */
    NiFogProperty* CreateFogProperty();
    
    /**
        Set the fog property to use when rendering the environment. Generally
        this fog property should also be assigned to the entire scene.
    */
    void SetFogProperty(NiFogProperty* pkFogProperty);
    
    /**
        Get the fog property in use by this environment.
    */
    NiFogProperty* GetFogProperty();

    /**
        Create a render click capable of rendering the entire sky/environment
        using the given camera. The created render click will generally need
        to be rendered before the main scene render click, so that the sky
        is rendered behind the scene. The main significance of this render
        click is that it automatically ignores the position of the camera in 
        space, and will automatically adjust the fog color, and renderer 
        background color if those settings have been selected.

        @param pkCamera The main scene camera. The directon of this camera 
            will be used to render the sky.
    */
    NiRenderClick* CreateSkyRenderClick(NiCamera* pkCamera);

    /**
        Create a render step capable of rendering the entire environment 
        to a cube map. This cubemap may then be used by the scene as a skybox
        with high performance. The cubemap may also be extracted to disk to 
        allow use in other tools to generate a scene. 

        @param pkDestinationCubeMap The cube map to render the environment to.
        @param pkRenderer The renderer to use when rendering the map.
    */
    NiCubeMapRenderStep* CreateSkyBoxCubeMapRenderStep(
        NiRenderedCubeMap* pkDestinationCubeMap, NiRenderer* pkRenderer);

    /**
        Set the color of the fog being used by this environment. 
    */
    void SetFogColor(NiColorA kColor);
    
    /**
        Set the value of the flag controlling the automatic calculation of 
        the fog color for the environment (and even the entire scene) using
        the atmospheric color of the horizon in the camera's direction.
        This flag is only used by a render click that has been created using 
        CreateSkyRenderClick.
    */
    void SetAutoCalcFogColor(bool bEnable);
    
    /**
        Get the value of the flag controlling the automatic calculation of 
        the fog color for the environment.
    */
    bool GetAutoCalcFogColor();
    
    /**
        Set the value of the flag controlling the automatic setting of the
        renderer background color. This flag is only used by a render click
        that has been created using CreateSkyRenderClick.
    */
    void SetAutoSetBackgroundColor(bool bEnable);

    /**
        Get the value of the flag controlling the automatic setting of the
        renderer background color.
    */
    bool GetAutoSetBackgroundColor();

    /**
        Sets the angle of the sun on the horizontal plane (angle between the sun and 
        (0,0,1))
    */
    inline void SetSunElevationAngle(float fAngle);

    /**
        Gets the angle of the sun on the horizontal plane (angle between the sun and 
        (0,0,1))
    */
    inline float GetSunElevationAngle();

    /**
        Sets the angle of the sun on the vertical plane (angle between the sun and 
        (0,1,0))
    */
    inline void SetSunAzimuthAngle(float fAngle);

    /**
        Gets the angle of the sun on the vertical plane (angle between the sun and 
        (0,1,0))
    */
    inline float GetSunAzimuthAngle(); 

    /**
        Sets whether the sun should be using the angles for rotation
    */
    inline void SetUseSunAngles(bool bUseAngles);
    
    /**
        Gets whether the sun should be using the angles for rotation
    */
    inline bool GetUseSunAngles();


    /// @cond EMERGENT_INTERNAL
    /** 
        Overide the update function of nodes so that those are called
        appropriately when updating environment.

        @see NiNode
    */
    void DoUpdate(NiUpdateProcess& kUpdate);
    virtual void UpdateDownwardPass(NiUpdateProcess& kUpdate);
    virtual void UpdateSelectedDownwardPass(NiUpdateProcess& kUpdate);
    virtual void UpdateRigidDownwardPass(NiUpdateProcess& kUpdate);
    /// @endcond

protected:

    /**
        Callback function for use by a CubeMapRenderStep to set the renderer
        background color to the one used by the Environment it is rendering. 

        @param pkCurrentStep A NiCubeMapRenderStep object
        @param pvCallbackData A NiEnvironment object
    */
    static bool CallbackBakeRenderStep(NiRenderStep* pkCurrentStep,
        void* pvCallbackData);

    /// The sunlight color
    NiColorA m_kSunColor;

    /// The atmosphere object with all the configuration information.
    NiAtmospherePtr m_spAtmosphere;

    /// The Sky geometry object to render the sky with.
    NiSkyPtr m_spSky;

    /// The light that represents the sun.
    NiDirectionalLightPtr m_spSun;

    /// The environmental fog property to use across an entire scene. 
    NiFogPropertyPtr m_spFogProperty;

    /// The entire sky including cloud objects begins at this node.
    NiNodePtr m_spSkyRoot;

    /// angle defining the sun's position on the horizontal plane
    float m_fSunAzimuthAngle;

    /// Angle defining the sun's position on the vertical plane
    float m_fSunElevationAngle;

    /// Flag to coordinate the fog color with the atmospheric horizon color.
    bool m_bAutoCalcFogColor;

    /// Flag to coordinate setting the background color to the fog color.
    bool m_bAutoSetBackgroundColor;

    /// Flag defining whether to use the sun rotation angles or not
    bool m_bUseSunAnglesRotation;

    /// Flag used to ensure sun position is updated
    bool m_bSunSettingsChanged;
};

NiSmartPointer(NiEnvironment);

#include "NiEnvironment.inl"

#endif