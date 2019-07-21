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

#ifndef NISKYMATERIAL_H
#define NISKYMATERIAL_H


#include <NiFragmentMaterial.h>
#include <NiTexturingProperty.h>

#include "NiEnvironmentLibType.h"

class NiSkyMaterialVertexDescriptor;
class NiSkyMaterialPixelDescriptor;
class NiSkyMaterialDescriptor;

/**
     This is an NiFragmentMaterial based material used for rendering
     a sky dome. This material will automatically generate the required
     shader based on the specified extra data parameters.
 */
class NIENVIRONMENT_ENTRY NiSkyMaterial : public NiFragmentMaterial
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:
    
    /// Used for tracking the version of the environment material.
    enum
    {
        /// Specifies the vertex shader version.
        VERTEX_VERSION = 2,

        /// Specifies the pixel shader version.
        PIXEL_VERSION = 3,

        /// Specifies the geometry shader version.
        GEOMETRY_VERSION = 0,

        /// Specifies the maximum number of blend stages.
        NUM_BLEND_STAGES = 5,
    };


    ///@cond EMERGENT_INTERNAL

    /** 
        @name Global Extra Data Constants
        
        These strings are declared for the extra data constant parameters
        used by the material. Allowing material choices to be based 
        upon extra data present on the material. They are not used inside
        the actual shader only in the shader's creation.
    */
    //@{
    static const char* ED_ATMOSPHERICCALCMODE;
    static const char* ED_STAGECONFIGURATION;
    //@}

    /** 
        @name Global Shader Constants
        
        These strings are declared for the shader constant parameters
        used by the material. 
    */
    //@{
    static const char* SC_ATMOSPHERICSCATTERINGCONST;
    static const char* SC_RGBINVWAVELENGTH4;
    static const char* SC_HDREXPOSURE;
    static const char* SC_UPVECTOR;
    static const char* SC_PLANETDIMENSIONS;
    static const char* SC_SCALEDEPTH;
    static const char* SC_FRAMEDATA;
    static const char* SC_NUMSAMPLESINT;
    static const char* SC_NUMSAMPLESFLOAT;

    static const char* SC_STAGEMODIFIEREXPONENT;
    static const char* SC_STAGEMODIFIERHORIZONBIAS;
    static const char* SC_STAGEMODIFIERCONSTANT;
    static const char* SC_STAGEGRADIENTHORIZON;
    static const char* SC_STAGEGRADIENTZENITH;
    static const char* SC_STAGEGRADIENTEXPONENT;
    static const char* SC_STAGEGRADIENTHORIZONBIAS;
    static const char* SC_STAGESKYBOXORIENTATION;
    //@}

    ///@endcond

    /// Used for selecting the atmospheric scattering mode to use
    struct AtmosphericCalcMode
    {
        enum Value
        {
            /// Specifies no atmospheric scattering calculations to be done
            NONE = 0,

            /// Select the calculations to be performed per vertex in the 
            /// vertex shader (Fast and efficient)
            GPU_VS = 1,

            /// Select the calculations to be performed per pixel in the 
            /// pixel shader (Must be SM3 or more)
            GPU_PS = 2,

            /// Select the calculations to be performed on the CPU 
            /// per vert, least GPU intensive, but requires the calcs
            /// to be put into a vert stream and fed to the shader.
            /// NOTE: Currently unsupported
            CPU = 3,
        };
    };
    
    /// A structure to encapsulate the selection of a blend method
    /// of a blend stage. 
    struct BlendMethod
    {
        enum Value
        {
            /// Specifies a custom blending mode
            CUSTOM = 0,

            /// Specifies to Multiply
            MULTIPLY = 1,

            /// Specifies to Add
            ADD = 2,

            /// Specifies to interpolate using multiplier
            INTERPOLATE = 3,    
        };
    };

    /// A structure to encapsulate the selection of a blend stage
    /// modifier. 
    struct ModifierSource
    {
        enum Value
        {
            /// Specifies a custom blend modifier source
            CUSTOM = 0,

            /// Specifies to use the default values (fastest)
            DEFAULT = 1,

            /// Specifies to use the alpha of the image
            ALPHA = 2,

            /// Specifies to use a shader constant for the modifier
            CONSTANT = 3,

            /// Specifies to use shader constants and normal to blend
            HORIZONBIAS = 4,

            /// Specifies this entire blend stage is disabled
            DISABLED = 5,
        };
    };

    /// A structure to encapsulate the selection of a color map modifier. 
    struct ColorMap
    {
        enum Value
        {
            /// Specifies a custom color map source
            CUSTOM = 0,

            /// Specifies to use a cubemap texture
            SKYBOX = 1,

            /// Specifies to use a gradient color map
            GRADIENT = 2,

            /// Specifies to use the fog color to blend
            FOG = 3,

            /// Specifies to use a cubemap which has an up vector (ie, is 
            /// rotated in the pixel shader)
            ORIENTED_SKYBOX = 4,
        };
    };

    /**
        Destructor.
    */
    virtual ~NiSkyMaterial();

    /**
        Static method allowing for the creation of the sky material.
    */
    static NiSkyMaterial* Create();

    /**
        Inherited from NiFragmentMaterial. Creates the default fallback 
        functions.
    */
    virtual void AddDefaultFallbacks();

    /// @name Blend Stage Configuration
    //@{
    /**
        Configure a particular blend stage of the material by applying an
        extra data constant to the object. There are presently 5 blend
        stages, with each one configurable through 3 categories of selections
            ColorMap - Specifies how a color is chosen to be blended 
            BlendMethod - Specifies how to blend the colors
            ModifierSource - Specifies how to calculate a modifier value for 
                             the blend method.

         The color used to begin with is the outcome of the Atmospheric 
         scattering calculations. In the event that atmospheric scattering is
         not used, the initial color of the sky is black.

         Available blend methods include the following (each method's equation
         is described as well)
            ADD = InitialValue + ColorMap * Modifier
            MULTIPLY = InitialValue * ColorMap * Modifier
            INTERPOLATE = lerp(InitialValue, ColorMap, Modifier)

         @param pkObject the object to apply the blend stage to
         @param uiStageIndex the stage to set the configuration of
         @param uiColorMap The blending color choosing method to be used
         @param uiModifierSource The modifier calculation method to be used
         @param uiBlendMethod the color blending method to use
    */
    void SetBlendStageConfiguration(NiAVObject* pkObject, 
        NiUInt32 uiStageIndex, NiUInt32 uiColorMap, NiUInt32 uiModifierSource, 
        NiUInt32 uiBlendMethod) const;
    bool GetBlendStageConfiguration(const NiAVObject* pkObject, 
        NiUInt32 uiStageIndex, NiUInt32& uiColorMap, NiUInt32& uiModifierSource, 
        NiUInt32& uiBlendMethod) const;

    /**
        Disable a specific blend stage

        @param pkObject the object to apply the configuration to
        @param uiStageIndex the stage to disable
    */
    void DisableBlendStage(NiAVObject* pkObject, NiUInt32 uiStageIndex);

    /**
        Specify the method of calculating the atmospheric coloring of
        the sky by applying a special extra data constant value to
        the object. 
        @param pkObject the object to apply the calculation to
        @param uiCalcMode the method of calculating the scattering values
            either NONE, GPU_VS, or GPU_PS
    */
    void SetAtmosphericCalcMode(NiAVObject* pkObject, NiUInt32 uiCalcMode);

    /**
        Specify the parameters to the calculation of the horizon bias 
        modifier. 
        @param pkObject the object to apply the configuration to
        @param uiStageIndex the stage to set the configuration of
        @param fExponent the power to apply to the linear value
        @param fHorizonBias a value to interpolate between linear and the
            power value
    */
    void SetModifierHorizonBiasValues(NiAVObject* pkObject, 
        NiUInt32 uiStageIndex, float fExponent, float fHorizonBias);

    /**
        Set the modifier value to use in a particular blend stage.
        @param pkObject the object to apply the configuration to
        @param uiStageIndex the stage to set the configuration of
        @param fModifier the value to use in the blend calculation
    */
    void SetModifierValue(NiAVObject* pkObject, NiUInt32 uiStageIndex, 
        float fModifier);
    /**
        Specify the parameters to the calculation of the gradient color map.
        @param pkObject the object to apply the configuration to
        @param uiStageIndex the stage to set the configuration of
        @param fExponent the power to apply to the linear interpolator
        @param fHorizonBias a value to interpolate between linear and the
            power value for interpolation
        @param kHorizonColor the color close to the horizon
        @param kZenithColor the color close to the summit of the dome
    */
    void SetGradientValues(NiAVObject* pkObject, NiUInt32 uiStageIndex, 
        float fExponent, float fHorizonBias, const NiColorA& kHorizonColor, 
        const NiColorA& kZenithColor);

    /**
        Specify the orientation of the skybox used in a particular blend stage.
        @param pkObject the object to apply the configuration to
        @param uiStageIndex the stage to set the configuration of
        @param kOrientation the matrix representing the orientation of the 
            skybox
    */
    void SetOrientedSkyboxValues(NiAVObject* pkObject, NiUInt32 uiStageIndex,
        const NiMatrix3& kOrientation);
    //@}

protected:

    NiSkyMaterial(NiMaterialNodeLibrary* pkMaterialNodeLib,
        bool bAutoCreateCaches = true, const NiFixedString &kName=
        "NiSkyMaterial");

    virtual NiShader* CreateShader(NiMaterialDescriptor* pkDesc);

    virtual bool SetupPackingRequirements(NiShader* pkShader,
        NiMaterialDescriptor* pkMaterialDescriptor,
        RenderPassDescriptor* pkRenderPasses, NiUInt32 uiCount);

    virtual bool GenerateDescriptor(const NiRenderObject* pkGeometry, 
        const NiPropertyState* pkPropState, 
        const NiDynamicEffectState* pkEffects,
        NiMaterialDescriptor& kMaterialDesc);

    void SetStageConfiguration(NiSkyMaterialDescriptor* pkDesc,
        NiUInt32 uiStageIndex, NiUInt32 uiColorMap, NiUInt32 uiModifierSource, 
        NiUInt32 uiBlendMethod);

    virtual ReturnCode GenerateShaderDescArray(
        NiMaterialDescriptor* pkMaterialDescriptor,
        RenderPassDescriptor* pkRenderPasses, 
        NiUInt32 uiMaxCount,
        NiUInt32& uiCountAdded);

    virtual bool GenerateVertexShadeTree(Context& kContext, 
        NiGPUProgramDescriptor* pkDesc);

    virtual bool GenerateGeometryShadeTree(Context& kContext, 
        NiGPUProgramDescriptor* pkDesc);

    virtual bool GeneratePixelShadeTree(Context& kContext,
        NiGPUProgramDescriptor* pkDesc);
        
    virtual NiUInt32 VerifyShaderPrograms(NiGPUProgram* pkVertexShader,
        NiGPUProgram* pkGeometryShader, NiGPUProgram* pkPixelShader);

    void HandleDestroyDepthInformation(Context& kContext, 
        NiMaterialResource* pkVertProjPos, 
        NiMaterialResource*& pkVertProjPosOut);

    bool SetupTransformPipeline(Context& kContext,
        NiMaterialResource*& pkVertOutProjPos,
        NiSkyMaterialVertexDescriptor* pkVertDesc, 
        NiMaterialResource*& pkWorldPos, 
        NiMaterialResource*& pkWorldView);

    bool HandlePositionTransform(Context& kContext, 
        NiMaterialResource* pkOriginalPos, 
        NiMaterialResource* pkTransformMatrix, 
        NiMaterialResource*& pkTransformPos);

    bool HandleViewVector(Context& kContext, NiMaterialResource* pkWorldPos, 
        NiMaterialResource*& pkWorldView);

    bool HandleDirectionTransform(Context& kContext, 
        NiMaterialResource* pkOriginalDir, 
        NiMaterialResource* pkTransformMatrix, 
        NiMaterialResource*& pkTransformDir);

    bool SetupPixelInputs(Context& kContext, 
        NiSkyMaterialPixelDescriptor* pkPixelDesc, 
        NiMaterialResource*& pkWorldView, NiMaterialResource*& pkNormals);

    bool HandleVertexAtmosphericScattering(Context& kContext,
        NiSkyMaterialVertexDescriptor* pkVertDesc, 
        NiMaterialResource* pkWorldView);

    bool HandlePixelAtmosphericScattering(Context& kContext,
        NiSkyMaterialPixelDescriptor* pkPixelDesc,
        NiMaterialResource*& pkCurrentColor, NiMaterialResource* pkWorldView);

    bool SetupAtmosphericConstants(Context& kContext,
        NiMaterialResource** ppkHDRExposure = NULL,
        NiMaterialResource** ppkPhaseConstant = NULL,
        NiMaterialResource** ppkPhaseConstant2 = NULL,
        NiMaterialResource** ppkCameraHeight = NULL,
        NiMaterialResource** ppkCameraHeight2 = NULL,
        NiMaterialResource** ppkScale = NULL,
        NiMaterialResource** ppkScaleDepth = NULL,
        NiMaterialResource** ppkScaleOverScaleDepth = NULL,
        NiMaterialResource** ppkSunSizeMultiplier = NULL,
        NiMaterialResource** ppkOuterRadius = NULL,
        NiMaterialResource** ppkOuterRadius2 = NULL,
        NiMaterialResource** ppkInnerRadius = NULL,
        NiMaterialResource** ppkInnerRadius2 = NULL,
        NiMaterialResource** ppkKm4PI = NULL,
        NiMaterialResource** ppkKr4PI = NULL,
        NiMaterialResource** ppkKmESun = NULL,
        NiMaterialResource** ppkKrESun = NULL,
        NiMaterialResource** ppkRGBInvWavelength4 = NULL,
        NiMaterialResource** ppkUpVector = NULL,
        NiMaterialResource** ppkfNumSamples = NULL,
        NiMaterialResource** ppkiNumSamples = NULL);

    bool HandleAtmosphericScatteringCalculation(Context& kContext,
        NiMaterialResource* pkWorldView, NiMaterialResource* pkPhaseConstant, 
        NiMaterialResource* pkPhaseConstant2, 
        NiMaterialResource* pkCameraHeight, 
        NiMaterialResource* pkCameraHeight2, NiMaterialResource* pkScale, 
        NiMaterialResource* pkScaleDepth, 
        NiMaterialResource* pkScaleOverScaleDepth, 
        NiMaterialResource* pkSunSizeMultiplier, 
        NiMaterialResource* pkOuterRadius,
        NiMaterialResource* pkOuterRadius2, NiMaterialResource* pkInnerRadius, 
        NiMaterialResource* pkInnerRadius2, NiMaterialResource* pkKm4PI, 
        NiMaterialResource* pkKr4PI, NiMaterialResource* pkKmESun, 
        NiMaterialResource* pkKrESun, NiMaterialResource* pkRGBInvWavelength4, 
        NiMaterialResource* pkUpVector, NiMaterialResource* pkfNumSamples, 
        NiMaterialResource* pkiNumSamples, 
        NiMaterialResource*& pkRayleighScattering, 
        NiMaterialResource*& pkMieScattering);

    bool HandleAtmosphericColoring(Context& kContext, 
        NiMaterialResource* pkWorldView, 
        NiMaterialResource* pkRayleighScattering, 
        NiMaterialResource* pkMieScattering, 
        NiMaterialResource* pkPhaseConstant, 
        NiMaterialResource* pkPhaseConstant2, 
        NiMaterialResource* pkSunSizeMultiplier, 
        NiMaterialResource* pkHDRExposure, 
        NiMaterialResource*& pkOutputColor);

    bool HandleBlendStages(Context& kContext, 
        NiSkyMaterialPixelDescriptor* pkPixelDesc,
        NiMaterialResource*& pkCurrentColor, NiMaterialResource* pkNormal,
        NiMaterialResource* pkWorldView);

    NiMaterialResource* SetupSampleColorMap(Context& kContext,
        ColorMap::Value kColorMap, NiUInt32 uiStageIndex,
        NiSkyMaterialPixelDescriptor* pkPixelDesc, 
        NiMaterialResource*& pkCurrentColor, NiMaterialResource* pkNormal,
        NiMaterialResource* pkWorldView);

    virtual NiMaterialResource* HandleCustomColorMap(Context& kContext,
        NiUInt32 uiStageIndex, NiSkyMaterialPixelDescriptor* pkPixelDesc, 
        NiMaterialResource*& pkCurrentColor, NiMaterialResource* pkNormal,
        NiMaterialResource* pkWorldView);

    NiMaterialResource* SetupCalcModifier(Context& kContext,
        ModifierSource::Value kModifierSource, NiUInt32 uiStageIndex, 
        NiSkyMaterialPixelDescriptor* pkPixelDesc, 
        NiMaterialResource*& pkCurrentColor, NiMaterialResource* pkSampleColor,
        NiMaterialResource* pkNormal, NiMaterialResource* pkWorldView);

    virtual NiMaterialResource* HandleCustomModifier(Context& kContext,
        NiUInt32 uiStageIndex, NiSkyMaterialPixelDescriptor* pkPixelDesc, 
        NiMaterialResource*& pkCurrentColor, NiMaterialResource* pkSampleColor,
        NiMaterialResource* pkNormal, NiMaterialResource* pkWorldView);

    NiMaterialNode* SetupBlendMethod(NiFragmentMaterial::Context& kContext,
        BlendMethod::Value kBlendMode, NiUInt32 uiStageIndex,
        NiSkyMaterialPixelDescriptor* pkPixelDesc, 
        NiMaterialResource*& pkCurrentColor, NiMaterialResource* pkNormal, 
        NiMaterialResource* pkWorldView);

    virtual NiMaterialNode* HandleCustomBlendMethod(Context& kContext,
        NiUInt32 uiStageIndex, NiSkyMaterialPixelDescriptor* pkPixelDesc, 
        NiMaterialResource*& pkCurrentColor, NiMaterialResource* pkNormal,
        NiMaterialResource* pkWorldView);

    NiMaterialResource* HandleCalculateHorizonBias(Context& kContext,
        NiMaterialResource* pkNormal, NiMaterialResource* pkUpVector, 
        NiMaterialResource* pkExponent, NiMaterialResource* pkHorizonBias);

    NiFixedString GenerateConstantName(NiUInt32 uiStageIndex, 
        const NiFixedString& constantName) const;

    NiMaterialResource* AddTextureSampler(
        NiFragmentMaterial::Context& kContext,
        const NiFixedString& kSamplerName, NiUInt32 uiOccurance);

private:
    
    NiFixedString m_kMaterialDescriptorName;
    NiFixedString m_kVertexShaderDescriptorName;
    NiFixedString m_kPixelShaderDescriptorName;   

};

NiSmartPointer(NiSkyMaterial);

#endif
