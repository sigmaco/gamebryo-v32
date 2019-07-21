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

#ifndef NITERRAINMATERIAL_H
#define NITERRAINMATERIAL_H

#include <NiFragmentMaterial.h>
#include <NiTexturingProperty.h>

#include "NiTerrainLibType.h"

#include "NiFragmentLighting.h"

class NiTerrainMaterialVertexDescriptor;
class NiTerrainMaterialPixelDescriptor;
class NiTerrainMaterialDescriptor;
class NiTerrainFragmentLighting;

/**
    This class implements the default terrain material. The terrain material
    currently supports up to 4 layers, in which each layer can have a base
    map, detail map, normal map, parallax map and specular map. The material generates a
    unique shader depending on how many layers are present on the terrain,
    what lights are affecting the terrain, fogging, etc.
*/
class NITERRAIN_ENTRY NiTerrainMaterial : public NiFragmentMaterial
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:

    /// The default color of the terrain when no blend masks or textures are applied
    static const NiColor ms_kDefaultColor;

    /// Used for tracking the version of the terrain material.
    enum
    {
        /// The number of DWORDs to use for material descriptor bit field.
        MATERIAL_DESCRIPTOR_INDEX_COUNT = 5,

        /// The number of DWORDs to use for pixel program descriptor bit field.
        PIXEL_PROGRAM_DESCRIPTOR_INDEX_COUNT = 5,

        /// The number of DWORDs to use for vertex program descriptor bit field.
        VERTEX_PROGRAM_DESCRIPTOR_INDEX_COUNT = 2,

        /// Specifies the vertex shader version.
        VERTEX_VERSION = 5,

        /// Specifies the pixel shader version.
        PIXEL_VERSION = 6,

        /// Specifies the geometry shader version.
        GEOMETRY_VERSION = 0,
    };

    /// Allows the terrain to have distance fog.
    enum Fog
    {
        /// Specifies no fog.
        FOG_NONE = 0,

        /// Specifies to use linear fog.
        FOG_LINEAR,

        /// Specifies squared fog
        FOG_SQUARED,

        /// The maximum specifications for fog.
        FOG_MAX
    };

    /// Defines useful constants.
    enum
    {
        /// Maximum number of surface layers per leaf cell.
        MAX_LAYERS_PER_CELL = 4,

        /// Control map for blending the different surfaces on a leaf.
        BLEND_MAP = 1,

        /// 4 channel texture map. RGB contains albedo, alpha channel may contain data depending on 
        /// the per platform packing.
        BASE_MAP = 2,

        /// 4 channel texture map. RGB contains the normal map, alpha channel may contain data 
        /// depending on the per platform packing.
        NORMAL_MAP = 3,

        /// 4 channel texture map. RGB contains the specular map, alpha channel may contain data 
        /// depending on the per platform packing.
        SPEC_MAP = 4,
    };

    /// Destructor
    virtual ~NiTerrainMaterial();

    /**
        Since normal and parallax maps are automatically disabled when running on
        SM2_x cards, this method exists to force the support of normal and
        parallax maps even if the current shader model is 2_x.
        @param bEnable Enables or disables normal and parallax maps.
    */
    void SetForceEnableNormalParallaxMaps(bool bEnable);

    /**
        Helper function for creating an instance of a terrain material. The
        function first looks up the material in Gamebryo's material database.
        If it is not found an instance of the NiTerrainMaterial is created.

        @note Since materials are basically singletons, the terrain material
        object is only created once.
    */
    static NiTerrainMaterial* Create();

    /**
        Inherited from NiFragmentMaterial. Creates the default fallback
        functions.
    */
    virtual void AddDefaultFallbacks();

    /**
        This method removes the parallax/normal maps from all the layers
        in the pixel shader. In addition, it disables passing tangents from
        the vertex shader to the pixel shader.
    */
    static bool DropNormalParallaxMap(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    /**
        Create a new pass for each pass with lighting. The lights are evenly
        divided from the original pass into the new passes. Note that this only
        affects per-pixel lights. These passes will be additively blended.
    */
    static bool SplitPerPixelLights(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);
        
    /**
        This technique will disable any shadow maps that use PSSM. Note that it
        will completely disable the shadowmap for any light using PSSM rather
        than reverting to a regular shadowmap.
    */
    static bool DropPSSMShadowMaps(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    /**
        Combination of DropPSSMShadowMaps and SplitPerPixelLights
    */
    static bool DropPSSMShadowMapsThenSplitPerPixelLights(
        NiMaterialDescriptor*, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    /**
        This technique will remove the shadow maps from the input passes.
    */
    static bool DropShadowMaps(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    /**
        This technique is a combination of DropShadowMaps and
        SplitPerPixelLights.
    */
    static bool DropShadowMapsThenSplitPerPixelLights(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    /**
        Create a new pass for each pass with lighting. The lights are evenly
        divided from the original pass into the new passes. Note that this only
        affects per-vertex lighting. These passes will be additively blended.
    */
    static bool SplitPerVertexLights(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    /**
        This technique is a combination of DropShadowMaps and SplitTextureMaps.
    */
    static bool DropShadowMapsThenSplitTextureMaps(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    /**
        This technique is a combination of DropParallaxMap and
        SplitPerPixelLights.
    */
    static bool DropNormalParallaxMapThenSplitLights(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    /**
        Combination of DropPSSMShadowMaps, DropParallaxMap and
        SplitPerPixelLights.
    */
    static bool DropPSSMShadowMapsThenNormalParallaxMapThenSplitLights(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    /**
        This technique is a combination of DropShadowMaps, DropParallaxMap,
        and SplitPerPixelLights.
    */
    static bool DropShadowMapsThenDropNormalParallaxMapThenSplitLights(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    /**
        Shader fallback to be used when all other fallbacks fail. This fall back
        will resort to using one of the replacement shaders that was inserted into
        the shader cache at cache creation time. These represent bare bones shaders
        that are exist to allow an object to be rendered.
    */
    static bool UseTerrainReplacementShader(
        NiMaterialDescriptor* pkMaterialDescriptor, ReturnCode eFailedRC,
        unsigned int uiFailedPass, RenderPassDescriptor* pkRenderPasses,
        unsigned int uiMaxCount, unsigned int& uiCount,
        unsigned int& uiFunctionData);

    /**
        Populates the shader cache with a set of fall back shaders. Replacement shaders 
        are 'fail safe' shaders that can be used when shader compilation can not be performed.
    */
    virtual void AddReplacementShaders();

protected:

    struct TerrainLightingData
    {
        enum 
        {
            MAX_LAYERS = NiTerrainMaterial::MAX_LAYERS_PER_CELL
        };
        
        TerrainLightingData();

        size_t m_uiSize;
        bool m_abLayerSpecularEnabled[MAX_LAYERS];
        NiMaterialResource* m_apkLayerSpecular[MAX_LAYERS];
        NiMaterialResource* m_pkLayerSpecularIntensities;
        NiMaterialResource* m_pkLayerSpecularPowers;
        NiMaterialResource* m_pkLayerMaskValues;
        NiMaterialResource* m_pkLowDetailSpecular;
    };

    /**
        This class implements special case specularity calculations for terrain.
    */
    class NiTerrainFragmentLighting : public NiFragmentLighting
    {
    public:
        NiTerrainFragmentLighting();

        virtual bool HandleLight(Context& kContext, NiUInt32 uiLight,
            LightType eType, NiUInt32 uiLightByType,
            NiMaterialResource* pkWorldPos,
            NiMaterialResource* pkWorldNorm, NiMaterialResource* pkViewVector,
            NiMaterialResource* pkSpecularPower,
            NiMaterialResource*& pkAmbientAccum,
            NiMaterialResource*& pkDiffuseAccum,
            NiMaterialResource*& pkSpecularAccum,
            bool bSpecular, NiMaterialResource* pkShadow, ExtraLightingData kExtraData = 0);
    };

    /// Constructor
    NiTerrainMaterial(NiMaterialNodeLibrary* pkMaterialNodeLib,
        bool bAutoCreateCaches = true, const NiFixedString &kName = "NiTerrainMaterial");
    
    // Inherited from NiFragmentMaterial. Returns the number of DWORDs to use
    // for the material descriptor bit field.
    virtual unsigned int GetMaterialDescriptorSize();

    // Inherited from NiFragmentMaterial. Returns the number of DWORDs to use
    // for the vertex program descriptor bit field.
    virtual unsigned int GetVertexProgramDescriptorSize();

    // Inherited from NiFragmentMaterial. Returns the number of DWORDs to use
    // for the geometry program descriptor bit field.
    virtual unsigned int GetGeometryProgramDescriptorSize();

    // Inherited from NiFragmentMaterial. Returns the number of DWORDs to use
    // for the pixel program descriptor bit field.
    virtual unsigned int GetPixelProgramDescriptorSize();

    /**
        Analyzes the specified render object (terrain blocks in this case),
        the properties attached to the geometry, and the dynamic effects
        attached to the geometry. This method then builds a descriptor object
        which is used to stitch together shader fragments to produce a shader.
    */
    virtual bool GenerateDescriptor(const NiRenderObject* pkGeometry,
        const NiPropertyState* pkPropState,
        const NiDynamicEffectState* pkEffects,
        NiMaterialDescriptor& kMaterialDesc);

    /// Configures the streams of data to be sent to the shader based upon the
    /// specified material descriptor.
    virtual bool SetupPackingRequirements(NiShader* pkShader,
        NiMaterialDescriptor* pkMaterialDescriptor,
        RenderPassDescriptor* pkRenderPasses, NiUInt32 uiCount);

    /**
        If no fall backs are required, a material descriptor encoding the
        information for a single pass are is generated.
    */
    virtual ReturnCode GenerateShaderDescArray(
        NiMaterialDescriptor* pkMaterialDescriptor,
        RenderPassDescriptor* pkRenderPasses, NiUInt32 uiMaxCount,
        NiUInt32& uiCountAdded);

    /**
        Constructs a shade tree for the vertex shader based on the
        specified descriptor object. The shade tree is then parsed and used
        to construct the final vertex shader.
    */
    virtual bool GenerateVertexShadeTree(Context& kContext,
        NiGPUProgramDescriptor* pkDesc);

    /**
        Constructs a shade tree for the pixel shader based on the
        specified descriptor object. The shade tree is then parsed and used
        to construct the final pixel shader.
    */
    virtual bool GeneratePixelShadeTree(Context& kContext,
        NiGPUProgramDescriptor* pkDesc);

    /**
        Entry point for constructing a shader based on the specified material
        descriptor.
    */
    virtual NiShader* CreateShader(NiMaterialDescriptor* pkDesc);

    /**
        This method takes the shader programs generated by the shader 
        generating functions and returns RC_SUCCESS if they were created 
        successfully.
    */
    virtual NiUInt32 VerifyShaderPrograms(NiGPUProgram* pkVertexShader,
        NiGPUProgram* pkGeometryShader, NiGPUProgram* pkPixelShader);

    /**
        Handles fetching of the required inputs to the vertex shader from
        the streams.
    */
    virtual bool HandleVertexInputs(Context& kContext,
        NiTerrainMaterialVertexDescriptor* pkVertexDesc,
        NiMaterialResource*& pkInputPosition, 
        NiMaterialResource*& pkInputNormal, 
        NiMaterialResource*& pkInputTangent);

    /**
        Handles the shader fragments that split the incoming packed positions,
        normals, and possibly tangents into source and target morph targets
        based on the current level of detail of a terrain block. It
        also handles the decompression of these values.
    */
    virtual void HandleInputDataSplits(Context& kContext, 
        NiTerrainMaterialVertexDescriptor* pkDesc, 
        NiMaterialResource* pkPosition, NiMaterialResource* pkRawNormal,
        NiMaterialResource* pkRawTangent,
        NiMaterialResource*& pkPosHigh, NiMaterialResource*& pkPosLow,
        NiMaterialResource*& pkNormal, NiMaterialResource*& pkTangent);

    /**
        Handle splitting a float4 value into two separate float2 values.
    */
    virtual void HandleSplitFloat4ToFloat2(Context& kContext,
        NiMaterialResource* pkFloat4, NiMaterialResource*& pkFirstHalf,
        NiMaterialResource*& pkSecondHalf);

    /**
        Handle decompressing a normal from the vertex streams
    */
    virtual void HandleDecompressNormal(Context& kContext,
        NiMaterialResource* pkCompressed, NiMaterialResource*& pkNormal);

    /**
        Handle decompressing a tangent from the vertex streams
    */
    virtual void HandleDecompressTangent(Context& kContext,
        NiMaterialResource* pkCompressed, NiMaterialResource*& pkTangent);

    /**
        Morph the values of all the streams to their final values that will be 
        used in all subsequent calculations.
    */
    virtual void HandleMorphStreams(Context& kContext, NiMaterialResource* pkMorphValue,
        NiMaterialResource* pkPosHigh, NiMaterialResource* pkPosLow, 
        NiMaterialResource*& pkFinalPos);

    /// Handles the application of standard lighting in the vertex shader
    bool HandleVertexLighting(Context& kContext, 
        NiTerrainMaterialVertexDescriptor* pkVertexDesc, 
        NiMaterialResource* pkWorldPosition, 
        NiMaterialResource* pkWorldNormal, 
        NiMaterialResource* pkWorldView);

    /// Handles the texture generation fragment
    void HandleGenerateTextureCoordinates(Context& kContext, 
        NiMaterialResource*& pkMaskUV, NiMaterialResource*& pkLayer0UV,
        NiMaterialResource*& pkLayer1UV, NiMaterialResource*& pkLayer2UV,
        NiMaterialResource*& pkLayer3UV, NiMaterialResource*& pkLowDetailDiffuseUV,
        NiMaterialResource*& pkLowDetailNormalUV);

    /// Calculate the total number of interpolators used for encoding
    efd::UInt32 CalculateNumEncodedInterpolators(bool bIncludeNormal, 
        bool bIncludePosition, bool bIncludeView, bool bIncludeNBT);

    /// Encode the data into the vertex stage interpolators
    efd::UInt32 HandleEncodeVertexInterpolators(Context& kContext, 
        NiTerrainMaterialVertexDescriptor* pkDesc, NiMaterialResource* pkMaskUV, 
        NiMaterialResource* pkLayer0UV, NiMaterialResource* pkLayer1UV, NiMaterialResource* pkLayer2UV,
        NiMaterialResource* pkLayer3UV, NiMaterialResource* pkLowDetailDiffuseUV,
        NiMaterialResource* pkLowDetailNormalUV, NiMaterialResource* pkWorldPosition, 
        NiMaterialResource* pkWorldNormal, NiMaterialResource* pkWorldBinormal, 
        NiMaterialResource* pkWorldTangent, NiMaterialResource* pkWorldView, 
        NiMaterialResource* pkMorphValue, NiMaterialResource*& pkTexCoord0, 
        NiMaterialResource*& pkTexCoord1, NiMaterialResource*& pkTexCoord2, 
        NiMaterialResource*& pkTexCoord3, NiMaterialResource*& pkTexCoord4, 
        NiMaterialResource*& pkTexCoord5, NiMaterialResource*& pkTexCoord6, 
        NiMaterialResource*& pkTexCoord7);

    /**
        Allows handling for final vertex outputs.
    */
    virtual bool HandleVertexOutputs(Context& kContext,
        NiTerrainMaterialVertexDescriptor* pkVertexDesc, 
        NiMaterialResource* pkProjectedPosition,
        NiMaterialResource* pkWorldPosition, NiMaterialResource* pkWorldNormal,
        NiMaterialResource* pkWorldBinormal, NiMaterialResource* pkWorldTangent, 
        NiMaterialResource* pkWorldView, NiMaterialResource* pkMorphValue,
        NiMaterialResource* pkFogValue);

    /**
        Overrides the output color in favor of outputting debugging values
    */
    virtual bool HandlePixelDebuging(Context& kContext,
        NiTerrainMaterialPixelDescriptor* pkPixelDesc,
        NiMaterialResource* pkFinalNormal, NiMaterialResource* pkParallaxOffset, 
        NiMaterialResource* pkMorphValue, NiMaterialResource* pkTotalMask,
        NiMaterialResource* pkGlossiness, NiMaterialResource*& pkFinalColor);

    /**
        Handles the final accumulation of color and outputs the result
        as the output color of the pixel shader.
    */
    virtual bool HandleFinalPixelOutputs(Context& kContext, 
        NiTerrainMaterialPixelDescriptor* pkPixelDesc,
        NiMaterialResource* pkDiffuseAccum,
        NiMaterialResource* pkSpecularAccum,
        NiMaterialResource* pkOpacityAccum, NiMaterialResource* pkGlossiness,
        NiMaterialResource* pkFinalNormal, NiMaterialResource* pkParallaxOffset, 
        NiMaterialResource* pkMorphValue, NiMaterialResource* pkTotalMask);

    /// Handles the shader fragments for computing a view vector for the 
    /// specified world position.
    /// @note The camera position is a shader constant automatically
    /// registered by this method.
    virtual void HandleCalculateWorldView(Context& kContext, 
        NiTerrainMaterialVertexDescriptor* pkDesc,
        NiMaterialResource* pkWorldPos, NiMaterialResource*& pkViewVector);

    /// Handles the shader fragments for doing per pixel fog.
    virtual void HandleCalculateFog(Context& kContext, Fog eFogType,
        NiMaterialResource* pkViewPos, NiMaterialResource*& pkFogValue);

    /// Handles the shader fragments for computing a morph value based on the
    /// distance from the camera. This is controlled by several additional
    /// shader constants that are registered by this method.
    virtual void HandleCalculateMorphValue(Context& kContext,
        NiTerrainMaterialVertexDescriptor* pkDesc,
        NiMaterialResource*& pkMorphValueOutput);

    /// Handles the shader fragments for morphing the vertex positions and
    /// applying the view projection transformation.
    virtual void SetupTransformPipeline(
        Context& kContext, NiTerrainMaterialVertexDescriptor* pkDesc,
        NiMaterialResource* pkModelPosition,
        NiMaterialResource* pkModelNormal,
        NiMaterialResource* pkModelTangent,
        NiMaterialResource*& pkWorldPos,
        NiMaterialResource*& pkProjPos,
        NiMaterialResource*& pkViewPos,
        NiMaterialResource*& pkWorldNormal,
        NiMaterialResource*& pkWorldBinormal,
        NiMaterialResource*& pkWorldTangent);

    /// Handles the shader fragments for morphing the normals and possibly
    /// tangents of the geometry and sending them on to the pixel shader.
    virtual void TransformNBTs(
        Context& kContext,
        NiTerrainMaterialVertexDescriptor* pkDesc,
        NiMaterialResource* pkNormal, NiMaterialResource* pkTangent,
        NiMaterialResource* pkWorldMatrix, NiMaterialResource*& pkWorldNormal,
        NiMaterialResource*& pkWorldBinormal, 
        NiMaterialResource*& pkWorldTangent);

    // Handles the shader fragment for sampling a base texture
    void HandleSampleLowDetailDiffuse(Context& kContext, 
        NiTerrainMaterialPixelDescriptor* pkPixelDesc, NiMaterialResource* pkUV, 
        NiMaterialResource*& pkLowDetailDiffuseColor, NiMaterialResource*& pkLowDetailSpecularColor, 
        NiMaterialResource*& pkLowDetailGlossiness);

    // Handles the shader fragment for sampling a base normal texture
    void HandleSampleLowDetailNormal(Context& kContext, 
        NiTerrainMaterialPixelDescriptor* pkPixelDesc, NiMaterialResource* pkUV, 
        NiMaterialResource*& pkLowDetailNormal);
    
    // Handles the shader fragment for blending between the surface layers 
    // and the low resolution textures
    virtual void HandleTextureMorphing(Context& kContext, 
        NiTerrainMaterialPixelDescriptor* pkPixelDesc, 
        NiMaterialResource* pkLowDetailDiffuseColor, 
        NiMaterialResource* pkBlendDiffuseAccum,
        NiMaterialResource* pkWorldNormal,        
        NiMaterialResource* pkLowDetailNormalValue,
        NiMaterialResource* pkBlendNormalAccum,
        NiMaterialResource* pkLowDetailSpecular,
        NiMaterialResource* pkLowDetailGlossiness,
        NiMaterialResource* pkBlendGlossiness,
        NiMaterialResource* pkMorphValue,
        NiMaterialResource*& pkDiffuseColor,
        NiMaterialResource*& pkNormal,
        NiMaterialResource*& pkGlossiness,
        TerrainLightingData* pkLightingData);

    /// Generates a texture sampler name based on the specified prefix and
    /// count value.
    inline virtual NiFixedString GenerateSamplerName(
        const NiFixedString& kBaseName, NiUInt32 uiIndex);

    /// Adds a new texture sampler to the shader context.
    inline virtual NiMaterialResource* AddTextureSampler(Context& kContext,
        const NiFixedString& kSamplerName, NiUInt32 uiOccurance);

    /// Handles the application of fog in the pixel shader
    virtual bool HandleApplyFog(Context& kContext,
        NiTerrainMaterialPixelDescriptor* pkPixDesc,
        NiMaterialResource* pkUnfoggedColor,
        NiMaterialResource*& pkFogOutput);

    /// Handles the setup of all pixel shader inputs from vertex shader
    virtual bool HandlePixelInputs(Context& kContext, NiTerrainMaterialPixelDescriptor* pkPixelDesc,
        NiMaterialResource*& pkMorphValue, NiMaterialResource*& pkMaskValues, 
        NiMaterialResource*& pkLayer0UV, NiMaterialResource*& pkLayer1UV, 
        NiMaterialResource*& pkLayer2UV, NiMaterialResource*& pkLayer3UV,
        NiMaterialResource*& pkLowResDiffuseUV, NiMaterialResource*& pkLowResNormalUV,
        NiMaterialResource*& pkWorldView, NiMaterialResource*& pkWorldViewTS, 
        NiMaterialResource*& pkWorldPos, NiMaterialResource*& pkNBTMatrix,
        NiMaterialResource*& pkWorldNormal);

    /// Handles the application of initial values to the pixel shader pipeline
    bool HandlePixelInitialValues(Context& kContext,
        NiTerrainMaterialPixelDescriptor* pkPixelDesc,
        NiMaterialResource*& pkMatDiffuse, NiMaterialResource*& pkMatSpecular,
        NiMaterialResource*& pkSpecularPower,
        NiMaterialResource*& pkGlossiness,
        NiMaterialResource*& pkMatAmbient, NiMaterialResource*& pkMatEmissive,
        NiMaterialResource*& pkTexDiffuseAccum,
        NiMaterialResource*& pkTexSpecularAccum,
        NiMaterialResource*& pkDiffuseAccum,
        NiMaterialResource*& pkSpecularAccum,
        NiMaterialResource*& pkOpacityAccum,
        NiMaterialResource*& pkLightDiffuseAccum,
        NiMaterialResource*& pkLightSpecularAccum,
        NiMaterialResource*& pkLightAmbientAccum);

    /// Handles detecting each layers capabilities and configuring the layer sampling fragment 
    /// appropriately.
    virtual bool HandleSurfaceLayers(Context& kContext, NiTerrainMaterialPixelDescriptor* pkPixelDesc, 
        NiMaterialResource*& pkMaskValues, NiMaterialResource* pkWorldViewTS, 
        NiMaterialResource* pkLayerUV[4], 
        NiMaterialResource* pkNBTMatrix, NiMaterialResource* pkWorldNormal, 
        TerrainLightingData* pkSurfaceLightingData, 
        NiMaterialResource*& pkFinalLayerColor, NiMaterialResource*& pkFinalLayerNormal, 
        NiMaterialResource*& pkFinalLayerSpecular, NiMaterialResource*& pkFinalLayerParallax,
        NiMaterialResource*& pkFinalLayerGlossiness, NiMaterialResource*& pkTotalMask);

    /// Handles the adjustment of the layer texture coordinates according to the surface
    /// parallax maps that are applied.
    virtual bool HandleParallaxMaps(Context& kContext, 
        NiTerrainMaterialPixelDescriptor* pkPixelDesc, NiMaterialResource* pkMaskValues, 
        NiMaterialResource** pkLayerUV, NiMaterialResource* pkWorldViewTS, 
        NiMaterialResource*& pkParallaxAccum);

    /// Handles the application of lighting in the pixel shader
    bool HandlePixelLighting(Context& kContext,
        NiTerrainMaterialPixelDescriptor* pkPixelDesc,
        NiMaterialResource* pkWorldPos,
        NiMaterialResource* pkWorldView, NiMaterialResource* pkSpecularPower, 
        NiMaterialResource*& pkNormalAccum, NiMaterialResource* pkMatEmissive, 
        NiMaterialResource* pkMatDiffuse, NiMaterialResource* pkMatAmbient, 
        NiMaterialResource* pkMatSpecular, 
        NiMaterialResource* pkLightSpecularAccum, 
        NiMaterialResource* pkLightDiffuseAccum, 
        NiMaterialResource* pkLightAmbientAccum,
        NiMaterialResource* pkGlossiness,
        NiMaterialResource* pkTexDiffuseAccum,
        NiMaterialResource* pkTexSpecularAccum,
        TerrainLightingData* pkSurfaceLightingData, 
        NiMaterialResource*& pkSpecularAccum,
        NiMaterialResource*& pkDiffuseAccum);

    /**
        Checks the passed in properties for any incompatible settings that
        the terrain material is not designed to handle.
    */
    virtual bool DetectIncompatibleObject(const NiRenderObject* pkGeometry, 
        const NiPropertyState* pkPropState, 
        const NiDynamicEffectState* pkEffects);

    /**
        Detects the format of the streams that are to be sent to the shader.
    */
    virtual bool DetectStreamFormat(const NiRenderObject* pkGeometry,
        bool& bNormalsAvailable, bool& bTangentsAvailable, 
        bool& bMorphData, bool& bCompressed, NiUInt32& uiNumTexCoords);

    /**
        Detects any extra data applied to the object that may be useful in
        generating the shader.
    */
    virtual bool DetectExtraData(const NiRenderObject* pkGeometry, NiUInt32& uiMorphMode);

    /**
        Detects the surface layers that are being used and their capabilities
    */
    bool DetectSurfaceLayerProperties(NiTerrainMaterialDescriptor* pkDesc,
        const NiTexturingProperty* pkTexProp);

    /**
        Detect any platform restrictions and adjust the descriptor to comply to the platform
    */
    virtual bool DetectPlatformRestrictions(NiTerrainMaterialDescriptor* pkDesc,
        const NiRenderObject* pkGeometry);

    /**
        Detect any debug configuration of the material that may have been 
        applied.
    */
    virtual bool DetectDebugConfiguration(NiTerrainMaterialDescriptor* pkDesc,
        const NiRenderObject* pkGeometry);

    /**
        Detect the render mode that the generated shader is expected to operate
        under. In future this may include baking steps, and even shadow
        generation.
    */
    virtual bool DetectRenderMode(NiTerrainMaterialDescriptor* pkDesc,
        const NiRenderObject* pkGeometry);

protected:

    NiFixedString m_kMaterialDescriptorName;
    NiFixedString m_kVertexShaderDescriptorName;
    NiFixedString m_kPixelShaderDescriptorName;
    NiTerrainFragmentLighting* m_pkLighting;
    NiFragmentOperations* m_pkOperations;
    bool m_bEnableNPOnSM2;
};

NiSmartPointer(NiTerrainMaterial);
#include "NiTerrainMaterial.inl"

#endif
