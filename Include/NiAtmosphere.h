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

#ifndef NIATMOSPHERE_H
#define NIATMOSPHERE_H

#include <NiNode.h>
#include <NiMesh.h>
#include <NiFloatsExtraData.h>
#include <NiFloatExtraData.h>
#include <NiIntegerExtraData.h>
#include <NiColor.h>
#include <NiDirectionalLight.h>

/**
    This class stores all the information and constants relevant to Atmospheric Scattering. As
    well as the raw values, it also pre-calculates shader constants and stores relevant extra
    data objects to attach to any mesh that requires NiSkyMaterial support.
*/
class NIENVIRONMENT_ENTRY NiAtmosphere : public NiNode
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:

    /// @name Constructor
    //@{
    NiAtmosphere();
    //@}

    /// Destructor
    ~NiAtmosphere();    

    /// @name Atmosphere Configuration Management
    //@{

    /// Load the default configuration for the atmospheric constants
    void LoadDefaultConfiguration();
    
    /**
        Set the phase constant used in mie and rayleigh scattering. 
        @param fG phase constant.
    */
    void SetPhaseConstant(float fG);

    /**
        Set the sun size multiplier to make the sun larger or smaller.
        changing the sun intensity can also be used to make the sun larger
        @param fSize sun size multiplier.
    */
    void SetSunSize(float fSize);

    /**
        Set the sun intensity, higher values create a brighter sky
        @param fIntensity the sun intensity.
    */
    void SetSunIntensity(float fIntensity);

    /**
        Set the rayleigh constant for the scattering calculations.
        Rayleigh scattering is responsible for the color of the sky and 
        sunset colors.
        @param fRayleigh the rayleigh scattering constant
    */
    
    void SetRayleighConstant(float fRayleigh);

    /**
        Set the mie constant for the scattering calculations.
        Mie scattering is responsible for the sun's glow in the sky and
        the dusty color of the sky due to haze.
        @param fMie the mie scattering constant
    */
    void SetMieConstant(float fMie);

    /**
        Set the R,G, and B wavelengths for the sky calculations.
        values are in micrometers.
        @param fR Red wavelength in micrometers
        @param fG Green wavelength in micrometers
        @param fB Blue wavelength in micrometers
    */
    void SetRGBWavelengths(float fR, float fG, float fB);

    /**
        Set the RED wavelength for the sky calculations.
        value is in micrometers.
        @param fWaveLength Red wavelength in micrometers
    */
    void SetRedWavelength(float fWaveLength);

    /**
        Set the GREEN wavelength for the sky calculations.
        value is in micrometers.
        @param fWaveLength Red wavelength in micrometers
    */
    void SetGreenWavelength(float fWaveLength);

    /**
        Set the BLUE wavelength for the sky calculations.
        value is in micrometers.
        @param fWaveLength Red wavelength in micrometers
    */
    void SetBlueWavelength(float fWaveLength);

    /**
        Set the HDR exposure constant to adjust the brightness of the sky
        @param fExposure exposure value, by default it is 2.0f.
    */
    void SetHDRExposure(float fExposure);

    /// Get the phase constant in use
    float GetPhaseConstant();

    /// Get the sun size multipler value
    float GetSunSize();

    /// Get the sun intensity value
    float GetSunIntensity();

    /// Get the rayleigh constant value
    float GetRayleighConstant();

    /// Get the mie constant value
    float GetMieConstant();

    /// Get the RGB wavelengths used in the calculations
    const NiPoint3& GetRGBWavelengths();

    /// Get the HDR exposure constant
    float GetHDRExposure();
    //@}

    /// @name Shader constant management
    //@{

    /**
        Attach the atmospheric extra data to the appropriate object.
        This is useful as many object can have the same extra data applied,
        and the atmosphere object will take care of any updates to that
        data that may be required.
    */
    void AttachExtraData(NiAVObject* pkObject);

    /// Detach any atmospheric extra data applied to the object.
    void DetachExtraData(NiAVObject* pkObject);
    //@}

    /// @name CPU Calculation Management
    //@{
    /**
        Calculate the sky color in a particular direction according to
        a sun direction. This is useful for calculation of fog values to
        match the horizon, or for offline skydome calculations. 
    */
    NiColor GetSkyColorInDirection(const NiPoint3& kDirection, 
        const NiPoint3& kSunDirection, bool bIncludeMieScattering);
    //@}

    /// @cond EMERGENT_INTERNAL
    //@{
    /** 
        Overide the update functionality of nodes so that atmospheric constants
        are updated appropriately when required.

        @see NiNode
    */
    void DoUpdate(NiUpdateProcess& kUpdate);
    virtual void UpdateDownwardPass(NiUpdateProcess& kUpdate);
    virtual void UpdateSelectedDownwardPass(NiUpdateProcess& kUpdate);
    virtual void UpdateRigidDownwardPass(NiUpdateProcess& kUpdate);
    //@}
    /// @endcond
    
private:

    /// @name Atmosphere Shader Management
    //@{

    /// Create and initialise the extra data objects to attach to objects
    void InitialiseExtraData();
    
    /**
        Update the shader constants that are not normally changed from 
        frame to frame
    */
    void UpdateShaderConstants();

    /**
        Update the shader constants that are expected to change from frame to
        frame.
    */
    void UpdateShaderVariables();   
    //@}

    /// @name Scattering Calculations
    //@{

    /// Calculate HDR exposure for a color using the CPU
    NiColor CalculateToneMapping(const NiColor& kInput);

    /// Calculate the color of the sky based on scattering values
    NiColor CalculateSkyColor(const NiPoint3& kRayleighScattering,
        const NiPoint3& kMieScattering, const NiPoint3& kDirection, 
        const NiPoint3& kSunDirection);

    /// Calculate scattering values for the calculation of the sky color
    void CalculateScattering(const NiPoint3& kDirection, 
        const NiPoint3& kSunDirection, NiPoint3& kRayleighScattering, 
        NiPoint3& kMieScattering);
    
    /// Calculate the distance to the edge of the atmosphere in a 
    /// certain direction
    float CalculateDistanceToEdgeOfAtmosphere(float fCosTheta, float fRA, 
        float fRA2, float fRE, float fRE2);

    /// Internal scale function defined by Sean O'neil in GPU Gems 2
    float InternalScaleFunction(float fCos, float fScaleDepth);
    //@}

protected:

    /// @name Atmosphere Configuration values
    //@{

    /// The sun size multipler (adjusts the directionality of the mie 
    /// scattering)
    float m_fSunSizeMultiplier;

    /// The Rayleigh scattering constant (beta rayleigh)
    float m_fRayleighConstant;

    /// The Mie scattering constant (beta mie)
    float m_fMieConstant;

    /// The intensity of the sun
    float m_fSunIntensity;

    /// The exposure constant to calculate HDR tone mapping on the sky
    float m_fHDRExposure;

    /// The radius of the planet
    float m_fPlanetRadius;

    /// The radius of the atmosphere
    float m_fAtmosphereRadius;
    
    /// The position in the sky at which the atmosphere is of average density 
    /// (between 0 and 1)
    float m_fScaleDepth;

    /// The R,G and B wavelengths to use, in micrometers
    NiPoint3 m_kRGBWavelengths;

    /// The phase constant to use. Adjustment will change the 
    /// directionality of the scattering
    float m_fPhaseConstant;

    /// The up vector to use, probably UNIT_Z
    NiPoint3 m_kUpVector;

    /// The number of iterations to perform in the sky shader
    NiUInt32 m_uiNumSamples;
    //@}

    /// @name Atmospheric Extra data values
    //@{

    /// Shader constant to specify the scattering constants
    NiFloatsExtraDataPtr m_spAtmosphericScatteringConstants;

    /// Shader constant to describe the RGB wavelengths with pre calculations
    NiFloatsExtraDataPtr m_spRGBInvWavelength4;

    /// Shader constant to specify the up vector of the scene
    NiFloatsExtraDataPtr m_spUpVector;

    /// Shader constant to describe the dimensions of the planet
    NiFloatsExtraDataPtr m_spPlanetDimensions;

    /// Shader constant to describe the atmspheric density
    NiFloatsExtraDataPtr m_spScaleDepth;

    /// Shader constant to store the data that may be updated every frame
    NiFloatsExtraDataPtr m_spFrameData;

    /// Shader constant to control the amount of HDR exposure on the sky
    NiFloatExtraDataPtr m_spHDRExposure;

    /// Shader constant to control division of the iteration
    NiFloatExtraDataPtr m_spNumSamplesFloat;

    /// Shader constant to control the number of samples iteration
    NiIntegerExtraDataPtr m_spNumSamplesInt;
    //@}

    /// @name Runtime values
    //@{

    /// Flag used to ensure atmospheric shader constants are updated
    bool m_bAtmosphereSettingsChanged;
    //@}
};

NiSmartPointer(NiAtmosphere);

#include "NiAtmosphere.inl"

#endif