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

#ifndef NISKYBLENDSTAGE_H
#define NISKYBLENDSTAGE_H

#include "NiEnvironmentLibType.h"
#include "NiSkyMaterial.h"
#include "NiTexture.h"

class NiTimeOfDay;

/**
    Base class for the blend stages. Protected constructor, to prevent direct
    instantiation and force derivation.
*/
class NIENVIRONMENT_ENTRY NiSkyBlendStage : public NiRefObject
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRootRTTI(NiSkyBlendStage);
    /// @endcond

protected:

    /**
        Constructor that takes the type of the blend stage.
    */
    NiSkyBlendStage(NiSkyMaterial::ColorMap::Value eColorMap);

public:

    /**
        Get what type of blend stage this is. The returned value
        represents the color generation mode that this stage will use in the 
        shader.
        @see NiSkyMaterial
    */
    inline NiSkyMaterial::ColorMap::Value GetColorMapType() const;

    /**
        Get the current modifier source for this blend stage. This value is
        relevant when configuring how the stage blends with previous stages.
        @see NiSkyMaterial
    */
    inline NiSkyMaterial::ModifierSource::Value GetModifierSource() const;

    /**
        Get the blend method used by this blend stage. 
        @see NiSkyMaterial
    */
    inline NiSkyMaterial::BlendMethod::Value GetBlendMethod() const;

    /**
        Set the modifier source to use on this blend stage. 
        @see NiSkyMaterial
    */
    inline void SetModifierSource(NiSkyMaterial::ModifierSource::Value eSource);

    /**
        Set the blend method to use on this blend stage.
        @see NiSkyMaterial
    */
    inline void SetBlendMethod(NiSkyMaterial::BlendMethod::Value eMethod);

    /**
        Set the value of the blend modifier constant for this stage.
        @see NiSkyMaterial
    */
    inline void SetBlendConstant(float fConstant);

    /**
        Get the value of the blend modifier constant for this stage.
        @see NiSkyMaterial
    */
    inline float GetBlendConstant() const;

    /**
        Have any of the properties on this stage been modified?
    */
    inline bool HasPropertyChanged() const;

    /**
        Mark the blend stage as having a property changed. If a property has
        changed, sending true to this function will force the blend stage's
        configuration to be pushed to the object using it during the next update

        @param bChanged true if an update should be forced, false to prevent an
            update.
    */
    inline void MarkPropertyChanged(bool bChanged);

    /**
        Set the horizon bias value for this blend stage's modifier. 
        @see NiSkyMaterial
    */
    inline void SetBlendHorizonBias(float fHorizonBias);
    
    /**
        Set the bias exponent for this blend stage's modifier. 
        @see NiSkyMaterial
    */
    inline void SetBlendBiasExponent(float fBiasExponent);

    /**
        Get the value of the horizon bias for this blend stage's modifier.
        @see NiSkyMaterial
    */
    inline float GetBlendHorizonBias() const;
    
    /**
        Get the value of the bias exponent for this blend stage's modifier.
        @see NiSkyMaterial
    */
    inline float GetBlendBiasExponent() const;

    /**
        Set whether or not this blend stage is enabled or not. A value of false
        will cause this blend stage to have no effect inside the shader.
        @see NiSkyMaterial
    */
    inline void SetEnabled(bool bEnabled);

    /**
        Is this stage enabled.
    */
    inline bool GetEnabled() const;

    /**
        Configure the given object with the appropriate data for the 
        NiSkyMaterial to make use of this blend stage.

        @param pkObject The object to be rendered with NiSkyMaterial
        @param uiStage The id of this stage within the shader
        @param pkMaterial The instance of the sky material
    */
    virtual void ConfigureObject(NiAVObject* pkObject, 
        NiUInt32 uiStage, NiSkyMaterial* pkMaterial);

    /**
        Bind this stage's specific properties to a NiTimeOfDay animator 
        instance.

        @param uiStage The id of this stage within the shader
        @param pkTimeOfDay The instance of NiTimeOfDay to add this property to.
    */
    virtual void BindProperties(NiUInt32 uiStage, NiTimeOfDay* pkTimeOfDay);

    /**
        Removes the stage's specific properties from the time of day object

        @param uiStage The id of this stage within the shader
        @param pkTimeOfDay The instance of NiTimeOfDay to remove properties from.
    */
    virtual void RemoveProperties(NiUInt32 uiStage, NiTimeOfDay* pkTimeOfDay);

protected:

    /// The enumeration to select the color map that this stage uses
    NiSkyMaterial::ColorMap::Value m_eColorMap;

    /// Generate the TimeOfDay property track name for a specific property
    NiFixedString CreatePropertyName(const NiFixedString& kCategory, 
        const NiFixedString& kName, NiUInt32 uiStage);

private:

    /// Enumeration to select the method used to calculate the blending 
    /// modifier
    NiSkyMaterial::ModifierSource::Value m_eModifierSource;

    /// Enumeration to select the method to use when blending this
    /// stage with the previous stages
    NiSkyMaterial::BlendMethod::Value m_eBlendMethod;

    /// The multiplier value to use in the calculations of this stage
    float m_fBlendConstant;

    /// The horizon bias for stage blending
    float m_fBlendHorizonBias;

    /// The horizon bias exponent for stage blending
    float m_fBlendBiasExponent;

    /// Flag controlling the status of this blend stage
    bool m_bEnabled;

    /// Flag to check if any settings have changed recently
    bool m_bHasSettingChanged;
};

/// NiSkyBlendStage smart pointer declaration
NiSmartPointer(NiSkyBlendStage);

/**
    Blend stage derivation specific to gradient layer
*/
class NIENVIRONMENT_ENTRY NiSkyGradientBlendStage : public NiSkyBlendStage
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:

    /**
        Default constructor.
    */
    NiSkyGradientBlendStage();

    /**
        Overridden ConfigureObject function to handle the extra configuration
        necessary for this type of blend stage.
        @see NiSkyBlendStage
    */
    virtual void ConfigureObject(NiAVObject* pkObject, 
        NiUInt32 uiStage, NiSkyMaterial* pkMaterial);

    /**
        Overridden BindProperties function to handle the extra properties
        available on this type of blend stage
        @see NiSkyBlendStage
    */
    virtual void BindProperties(NiUInt32 uiStage, NiTimeOfDay* pkTimeOfDay);

    virtual void RemoveProperties(NiUInt32 uiStage, NiTimeOfDay* pkTimeOfDay);

    /**
        Set the value of the Zenith color of the gradient.

        @param kZenithColor The color to use.
    */
    inline void SetZenithColor(NiColorA kZenithColor);

    /**
        Set the value of the Horizon color of the gradient.

        @param kHorizonColor The color to use.
    */
    inline void SetHorizonColor(NiColorA kHorizonColor);

    /**
        Set the value of the horizon bias to use when calculating the 
        gradient.
        
        @see NiSkyMaterial
        @param fHorizonBias The value of the horizon bias
    */
    inline void SetGradientHorizonBias(float fHorizonBias);
    
    /**
        Set the value of the horizon bias exponent to use when calculating the 
        gradient.

        @see NiSkyMaterial
        @param fBiasExponent The value of the horizon bias exponent
    */
    inline void SetGradientBiasExponent(float fBiasExponent);

    /**
        Get the value of the Zenith color of the gradient.
    */
    inline const NiColorA& GetZenithColor() const;

    /**
        Get the value of the Horizon color of the gradient.
    */
    inline const NiColorA& GetHorizonColor() const;

    /**
        Get the value of the horizon bias that is used when calculating the
        gradient. 
        @see NiSkyMaterial
    */
    inline float GetGradientHorizonBias() const;

    /**
        Get the value of the horizon bias exponent that is used when 
        calculating the gradient. 
        @see NiSkyMaterial
    */
    inline float GetGradientBiasExponent() const;

private:
    /// The zenith color used in the gradient blends
    NiColorA m_kZenithColor;

    /// The horizon color used in gradient blends
    NiColorA m_kHorizonColor;

    /// The bias value towards the horizon for gradient blends
    float m_fGradientHorizonBias;

    /// The bias exponent for gradient blends
    float m_fGradientBiasExponent;
};

/**
    Blend stage derivation specific to fog layer
*/
class NIENVIRONMENT_ENTRY NiSkyFogBlendStage : public NiSkyBlendStage
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:

    /**
        Default constructor.
    */
    NiSkyFogBlendStage();

    /**
        Overridden ConfigureObject function to handle the extra configuration
        necessary for this type of blend stage.
        @see NiSkyBlendStage
    */
    virtual void ConfigureObject(NiAVObject* pkObject, 
        NiUInt32 uiStage, NiSkyMaterial* pkMaterial);
};

/**
    Blend stage derivation specific to cubemapped sky box layer
*/
class NIENVIRONMENT_ENTRY NiSkySkyboxBlendStage : public NiSkyBlendStage
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:

    /**
        Default constructor.
    */
    NiSkySkyboxBlendStage();

    /**
        Overridden ConfigureObject function to handle the extra configuration
        necessary for this type of blend stage.
        @see NiSkyBlendStage
    */
    virtual void ConfigureObject(NiAVObject* pkObject, 
        NiUInt32 uiStage, NiSkyMaterial* pkMaterial);

    /**
        Overridden BindProperties function to handle the extra properties
        available on this type of blend stage
        @see NiSkyBlendStage
    */
    virtual void BindProperties(NiUInt32 uiStage, NiTimeOfDay* pkTimeOfDay);

    virtual void RemoveProperties(NiUInt32 uiStage, NiTimeOfDay* pkTimeOfDay);

    /**
        Set the cubemap to use when rendering the skybox. NOTE: This texture
        must be a cube map texture.

        @param pkTexture The sky cubemap 
    */
    inline void SetTexture(NiTexture* pkTexture);

    /**
        Get the cubemap that will be used when rendering the skybox
    */
    inline NiTexture* GetTexture() const;

    /**
        Set whether or not to orientate this skybox using a matrix rotation. 

        @param bOrient True if a rotation is required.
    */
    inline void SetOriented(bool bOrient);

    /**
        Get whether or not this skybox is oriented using a matrix.
    */
    inline bool IsOriented();
    
    /**
        Set the value of the rotation matrix to use when rendering this skybox
        @param kOrientation The value of the rotation matrix
    */
    inline void SetOrientation(const NiMatrix3& kOrientation);

    /**
        Get the value of the orientation matrix that will be used when
        rendering the skybox.
    */
    inline const NiMatrix3& GetOrientation() const;

private:

    /// Orientation matrix to rotate the skybox.
    NiMatrix3 m_kOrientation;

    /// Skybox texture to use in this blend stage.
    NiTexturePtr m_spTexture;
};

#include "NiSkyBlendStage.inl"

#endif // NISKYBLENDSTAGE_H