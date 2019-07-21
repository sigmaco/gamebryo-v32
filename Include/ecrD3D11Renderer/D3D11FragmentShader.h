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
#ifndef D3D11FRAGMENTSHADER_H
#define D3D11FRAGMENTSHADER_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11ShaderCore.h>

#include <NiMaterialDescriptor.h>
#include <NiFragmentShaderInstanceDescriptor.h>
#include <NiTexturingProperty.h>

namespace ecr
{

/**
    ecr::D3D11FragmentShader is a special shader class that NiFragmentMaterial-derived classes, 
    including NiStandardMaterial, create in order to provide shaders with custom-built 
    pixel and vertex shaders. 
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11FragmentShader : public D3D11ShaderCore
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    /**
        Constructor. 
        
        Creates a new D3D11FragmentShader instance that will be built from the given 
        NiMaterialDescriptor. The constructor will not actually analyze the material 
        descriptor at all, but it will save it so that the material will know which 
        material descriptor was used to construct the shader.
    */
    D3D11FragmentShader(NiMaterialDescriptor* pDesc);
    /// Destructor
    virtual ~D3D11FragmentShader();
    //@}

    /// Initializes the shader and indicates that all bone matrices will be transposed,
    /// 3-row world space matrices.
    virtual efd::Bool Initialize();

    /// Prepares the shader resources from textures found in NiTexturingProperty.
    virtual efd::UInt32 UpdatePipeline(const NiRenderCallContext& callContext);

    /// Returns true, indicating this class can be configured by an NiFragmentMaterial
    virtual efd::Bool IsGenericallyConfigurable();

    /**
        Add an additional render pass to the shader. 
        
        @param passID Outputs the position of the new pass in the shader.
        @return True if the function succeeds, false otherwise.
    */
    virtual efd::Bool AppendRenderPass(efd::UInt32& passID);

    /**
        Overrides the alpha blending mode of a pass. 
        
        @param passID The ID of the pass to affect.
        @param alphaBlend Whether alpha blending should be enabled. 
        @param usePreviousSrcBlendMode Indicates whether the pass should inherit the source blend 
            mode from the previous pass.
        @param srcBlendMode The new source blend mode to use, if usePreviousSrcBlendMode is false.
        @param usePreviousDestBlendMode Indicates whether the pass should inherit the dest blend 
            mode from the previous pass.
        @param destBlendMode The new dest blend mode to use, if usePreviousDestBlendMode is false.
        @return True if the function succeeds, false otherwise.
    */
    virtual efd::Bool SetAlphaOverride(
        efd::UInt32 passID,
        efd::Bool alphaBlend,
        efd::Bool usePreviousSrcBlendMode,
        NiAlphaProperty::AlphaFunction srcBlendMode,
        efd::Bool usePreviousDestBlendMode,
        NiAlphaProperty::AlphaFunction destBlendMode);

    /**
        Sets the specified NiGPUProgram on a pass.
        
        @param passID The ID of the pass to affect.
        @param pProgram The NiGPUProgram to set
        @param shaderType Outputs the NiGPUProgram::ProgramType for pProgram.
        @return True if the function succeeds, false otherwise. 
    */
    virtual efd::Bool SetGPUProgram(
        efd::UInt32 passID,
        NiGPUProgram* pProgram,
        NiGPUProgram::ProgramType& shaderType);
    /**
        Creates a new NiShaderConstantMap for a pass.
        
        @param passID The ID of the pass to affect.
        @param shaderType Type of shader program that the new shader constant map will be used for.
        @param mapIndex Unused.
        @return The newly created NiShaderConstantMap, or NULL on failure. 
    */
    virtual NiShaderConstantMap* CreateShaderConstantMap(
        efd::UInt32 passID,
        NiGPUProgram::ProgramType shaderType,
        efd::UInt32 mapIndex = 0);

    /**
        Adds a texture sampler to a pass.
        
        @param passID The ID of the pass to affect.
        @param samplerID Unused.
        @param semantic Indicates which map from NiTexturingProperty to use. Valid values include 
            the standard maps from that class, such as "Base", "Dark", and "Normal".
        @param variableName Identifies the name of the sampler and texture variables that will
            make use of this texture.
        @param instance For "Shader" and "Decal" maps, this indicates which map of that type to use.
        @return True if the function succeeds, false otherwise. 
    */
    virtual efd::Bool AppendTextureSampler(
        efd::UInt32 passID,
        efd::UInt32& samplerID,
        const NiFixedString& semantic,
        const NiFixedString& variableName,
        efd::UInt32 instance = 0);

    /// Returns the NiMaterialDescriptor that was used to construct the shader.
    virtual const NiShader::NiShaderInstanceDescriptor* GetShaderInstanceDesc() const;

protected:
    NiFragmentShaderInstanceDescriptor m_descriptor;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11FragmentShader
/// class.
typedef efd::SmartPointer<D3D11FragmentShader> D3D11FragmentShaderPtr;

}   // End namespace ecr.


#endif // EE_D3D11FRAGMENTSHADER_H
