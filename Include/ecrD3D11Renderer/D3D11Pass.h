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
#ifndef EE_D3D11PASS_H
#define EE_D3D11PASS_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11ComputeShader.h>
#include <ecrD3D11Renderer/D3D11DomainShader.h>
#include <ecrD3D11Renderer/D3D11GeometryShader.h>
#include <ecrD3D11Renderer/D3D11HullShader.h>
#include <ecrD3D11Renderer/D3D11PixelShader.h>
#include <ecrD3D11Renderer/D3D11RenderStateGroup.h>
#include <ecrD3D11Renderer/D3D11ShaderProgramData.h>
#include <ecrD3D11Renderer/D3D11ShaderConstantMap.h>
#include <ecrD3D11Renderer/D3D11VertexShader.h>

#include <NiRefObject.h>
#include <NiStreamOutSettings.h>
#include <NiTextureStage.h>
#include <NiTexturingProperty.h>

namespace ecr
{

class D3D11ShaderCore;

class D3D11Pass;
/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11Pass
/// class.
typedef efd::SmartPointer<D3D11Pass> D3D11PassPtr;

/**
    Description of a constant buffer that a shader program will use.

    After a shader program is compiled and used to create a D3D11 shader object, the renderer 
    creates a list of ConstantBufferDesc objects that the shader requires. These descriptions
    are linked to the NiShaderConstantMap objects that are responsible for updating the buffers, 
    and contain the information that allows the NiShaderConstantMapEntry objects to know where in 
    the constant buffer they need to write their data to. ConstantBufferDesc objects are also used
    to let the D3D11Pass know when multiple shader programs will be making use of the same
    constant buffer. 

    The list of ConstantBufferDesc objects on a pass also provides a list of constant buffers
    that need to be updated before the pass can be rendered.

    This class has no virtual functions to keep its size as small as possible.
*/
class EE_ECRD3D11RENDERER_ENTRY ConstantBufferDesc : public efd::MemObject
{
public:
    /// @name Construction and Destruction
    //@{
    /// Create a new ConstantBufferDesc with the given number of variables.
    ConstantBufferDesc(efd::UInt32 variableCount);
    /// Destructor.
    ~ConstantBufferDesc();
    //@}

    /// Name of the constant buffer variable.
    efd::FixedString m_bufferName;

    /// Array of names of each variable in the constant buffer.
    efd::FixedString* m_nameArray;
    /// Array of starting offsets of each variable in the constant buffer.
    efd::UInt32* m_startOffsetArray;
    /// Array of sizes of each variable in the constant buffer.
    efd::UInt32* m_sizeArray;
    /// Array of type information for each variable in the constant buffer.
    D3D11_SHADER_TYPE_DESC* m_typeArray;

    /// Number of variables in the constant buffer.
    const efd::UInt32 m_variableCount;

    /// Index for the constant map in the D3D11Pass that will manage this constant buffer.
    efd::UInt32 m_constantMapIndex;

    /// Bitfield of shader program types in the D3D11Pass that expect to use this constant buffer.
    efd::UInt32 m_shaderTypes;

    /// ConstantBufferDesc objects are stored in a linked list.
    ConstantBufferDesc* m_pNext;
private:
    /// Assignment operator to fix a build warning - do not use.
    ConstantBufferDesc& operator= (const ConstantBufferDesc& other);

};

/**
    ecr::D3D11Pass represents a single rendering pass for a D3D11ShaderCore.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11Pass : public NiRefObject
{
public:
    /// @name Construction and Destruction
    //@{
    /// Destructor
    virtual ~D3D11Pass();
    //@}

    /**
        Creates a new D3D11pass object.

        @param spNewPass Outputs a smart pointer to the new pass object.
        @return True if the function succeeds, false otherwise.
    */
     static efd::Bool CreateNewPass(D3D11PassPtr& spNewPass);

    /// Return the name of the pass.
    inline const efd::Char* GetName() const;
    /// Set the name of the pass.
    inline void SetName(efd::Char* pName);

    /// Return the render state group for the pass.
    inline D3D11RenderStateGroup* GetRenderStateGroup() const;
    /// Set the render state group for the pass.
    inline void SetRenderStateGroup(D3D11RenderStateGroup* pRenderStateGroup);

    /// Return the number of shader constant maps for the pass.
    inline efd::UInt32 GetConstantMapCount() const;
    /// Return the shader constant map with the given index.
    inline D3D11ShaderConstantMap* GetConstantMap(efd::UInt32 index) const;
    /// Add a new shader constant map pass, and return the index of that map.
    inline efd::UInt32 AddConstantMap(D3D11ShaderConstantMap* pSCMVertex);
    /// Remove the shader constant map with the given index.
    inline void RemoveConstantMap(efd::UInt32 index);

    /// Return the vertex shader on the pass.
    inline D3D11VertexShader* GetVertexShader() const;
    /// Set the vertex shader on the pass.
    inline void SetVertexShader(D3D11VertexShader* pVertexShader);
    /// Return the name of the file that will be used to compile the vertex shader.
    inline const efd::Char* GetVertexShaderProgramFileName() const;
    /// Set the name of the file that will be used to compile the vertex shader.
    inline void SetVertexShaderProgramFileName(const efd::Char* pProgramFile);
    /// Return the entry point that will be used to compile the vertex shader.
    inline const efd::Char* GetVertexShaderProgramEntryPoint() const;
    /// Set the entry point that will be used to compile the vertex shader.
    inline void SetVertexShaderProgramEntryPoint(const efd::Char* pEntryPoint);
    /// Return the shader target that will be used to compile the vertex shader.
    inline const efd::Char* GetVertexShaderProgramShaderTarget() const;
    /// Set the shader target that will be used to compile the vertex shader.
    inline void SetVertexShaderProgramShaderTarget(const efd::Char* pShaderTarget);

    /// Return the hull shader on the pass.
    inline D3D11HullShader* GetHullShader() const;
    /// Set the hull shader on the pass.
    inline void SetHullShader(D3D11HullShader* pHullShader);
    /// Return the name of the file that will be used to compile the hull shader.
    inline const efd::Char* GetHullShaderProgramFileName() const;
    /// Set the name of the file that will be used to compile the hull shader.
    inline void SetHullShaderProgramFileName(const efd::Char* pProgramFile);
    /// Return the entry point that will be used to compile the hull shader.
    inline const efd::Char* GetHullShaderProgramEntryPoint() const;
    /// Set the entry point that will be used to compile the hull shader.
    inline void SetHullShaderProgramEntryPoint(const efd::Char* pEntryPoint);
    /// Return the shader target that will be used to compile the hull shader.
    inline const efd::Char* GetHullShaderProgramShaderTarget() const;
    /// Set the shader target that will be used to compile the hull shader.
    inline void SetHullShaderProgramShaderTarget(const efd::Char* pShaderTarget);

    /// Return the domain shader on the pass.
    inline D3D11DomainShader* GetDomainShader() const;
    /// Set the domain shader on the pass.
    inline void SetDomainShader(D3D11DomainShader* pDomainShader);
    /// Return the name of the file that will be used to compile the domain shader.
    inline const efd::Char* GetDomainShaderProgramFileName() const;
    /// Set the name of the file that will be used to compile the domain shader.
    inline void SetDomainShaderProgramFileName(const efd::Char* pProgramFile);
    /// Return the entry point that will be used to compile the domain shader.
    inline const efd::Char* GetDomainShaderProgramEntryPoint() const;
    /// Set the entry point that will be used to compile the domain shader.
    inline void SetDomainShaderProgramEntryPoint(const efd::Char* pEntryPoint);
    /// Return the shader target that will be used to compile the domain shader.
    inline const efd::Char* GetDomainShaderProgramShaderTarget() const;
    /// Set the shader target that will be used to compile the domain shader.
    inline void SetDomainShaderProgramShaderTarget(const efd::Char* pShaderTarget);

    /// Return the geometry shader on the pass.
    inline D3D11GeometryShader* GetGeometryShader() const;
    /// Set the geometry shader on the pass.
    inline void SetGeometryShader(D3D11GeometryShader* pGeometryShader);
    /// Return the name of the file that will be used to compile the geometry shader.
    inline const efd::Char* GetGeometryShaderProgramFileName() const;
    /// Set the name of the file that will be used to compile the geometry shader.
    inline void SetGeometryShaderProgramFileName(const efd::Char* pProgramFile);
    /// Return the entry point that will be used to compile the geometry shader.
    inline const efd::Char* GetGeometryShaderProgramEntryPoint() const;
    /// Set the entry point that will be used to compile the geometry shader.
    inline void SetGeometryShaderProgramEntryPoint(const efd::Char* pEntryPoint);
    /// Return the shader target that will be used to compile the geometry shader.
    inline const efd::Char* GetGeometryShaderProgramShaderTarget() const;
    /// Set the shader target that will be used to compile the geometry shader.
    inline void SetGeometryShaderProgramShaderTarget(const efd::Char* pShaderTarget);

    /// Return the pixel shader on the pass.
    inline D3D11PixelShader* GetPixelShader() const;
    /// Set the pixel shader on the pass.
    inline void SetPixelShader(D3D11PixelShader* pPixelShader);
    /// Return the name of the file that will be used to compile the pixel shader.
    inline const efd::Char* GetPixelShaderProgramFileName() const;
    /// Set the name of the file that will be used to compile the pixel shader.
    inline void SetPixelShaderProgramFileName(const efd::Char* pProgramFile);
    /// Return the entry point that will be used to compile the pixel shader.
    inline const efd::Char* GetPixelShaderProgramEntryPoint() const;
    /// Set the entry point that will be used to compile the pixel shader.
    inline void SetPixelShaderProgramEntryPoint(const efd::Char* pEntryPoint);
    /// Return the shader target that will be used to compile the pixel shader.
    inline const efd::Char* GetPixelShaderProgramShaderTarget() const;
    /// Set the shader target that will be used to compile the pixel shader.
    inline void SetPixelShaderProgramShaderTarget(const efd::Char* pShaderTarget);

    /// Return the compute shader on the pass.
    inline D3D11ComputeShader* GetComputeShader() const;
    /// Set the compute shader on the pass.
    inline void SetComputeShader(D3D11ComputeShader* pComputeShader);
    /// Return the name of the file that will be used to compile the compute shader.
    inline const efd::Char* GetComputeShaderProgramFileName() const;
    /// Set the name of the file that will be used to compile the compute shader.
    inline void SetComputeShaderProgramFileName(const efd::Char* pProgramFile);
    /// Return the entry point that will be used to compile the compute shader.
    inline const efd::Char* GetComputeShaderProgramEntryPoint() const;
    /// Set the entry point that will be used to compile the compute shader.
    inline void SetComputeShaderProgramEntryPoint(const efd::Char* pEntryPoint);
    /// Return the shader target that will be used to compile the compute shader.
    inline const efd::Char* GetComputeShaderProgramShaderTarget() const;
    /// Set the shader target that will be used to compile the compute shader.
    inline void SetComputeShaderProgramShaderTarget(const efd::Char* pShaderTarget);

    /**
        Query all the shader programs on the pass and set up all the structures necessary to 
        provide the data for the parameters that the shader programs expect.

        The structures this function will set up include ConstantBufferDesc objects for the 
        constant buffers, arrays of names for the shader resources and samplers, and UAVSlot 
        objects for unordered access views.

        This function is normally called when D3D11ShaderCore::Initialize iterates its pass array
        and calls the function on all its passes. If, for whatever reason, a pass is not included
        in that array when D3DShaderCore::Initialize is called on a derived shader class, then
        that derived shader needs to ensure the function is called on all its passes.
    */
    efd::Bool ExposeShaderParameters(D3D11ShaderCore* pShader);

    /**
        Before rendering, ensure all ConstantBufferDesc objects refer to the appropriate
        NiShaderConstantMap, and all shader resources the shaders require are associated with
        ResourceSource objects.

        This function will not be called every frame; only when the renderer detects that the 
        resources need to be relinked, such as after removing an NiShaderConstantMap from the pass.
    */
    efd::Bool LinkUpShaderResources();

    /// Set all shader programs on the device context.
    virtual efd::UInt32 ApplyShaderPrograms(const NiRenderCallContext& callContext);

    /// Update constant buffers and set them on the device context.
    virtual efd::UInt32 ApplyShaderConstants(const NiRenderCallContext& callContext);

    /// Obtain shader resources and set them on the device context.
    virtual efd::UInt32 ApplyTextures();

    /// Obtain unordered access views and set them on the device context.
    virtual efd::UInt32 ApplyUAVs();

    /**
        Setup the pass for rendering the given object.

        This it the function that calls LinkUpShaderResources, UpdateSamplers, and UpdateUAVs
        if necessary. This function also updates the render states and calls ApplyTextures and
        ApplyUAVs.
    */ 
    virtual efd::UInt32 SetupRenderingPass(const D3D11ShaderCore* pShader);

    /// Performs any required functionality at the end of the pass. The base implementation does
    /// nothing.
    virtual efd::UInt32 PostProcessRenderingPass(efd::UInt32 pass = 0);

    /**
        Registers a shader resource on the pass as an NiTexture.

        When a shader program requires a shader resource, it will search the pass's list of
        registered shader resource sources by name. The resources source will then provide the
        resource itself to the shader. This function allows an application to directly provide 
        an NiTexture as the resource.

        @param resourceName Name of the shader resource.
        @param pResource NiTexture to associate with that name.
    */
    void SetShaderResourceAsDirectResource(
        const efd::FixedString& resourceName,
        NiTexture* pResource);
    /**
        Registers a shader resource on the pass as a map on an NiTexturingProperty.

        When a shader program requires a shader resource, it will search the pass's list of
        registered shader resource sources by name. The resources source will then provide the
        resource itself to the shader. This function has the shader get the resource from a
        specific map on the rendering NiMesh object's NiTexturingProperty.

        @param resourceName Name of the shader resource.
        @param gbMap NiTexturingProperty map to use, identified using 
            NiTextureStage::TSTextureFlags enumerations.
        @param instanceID Instance of the NiTexturingProperty map to use for Shader or Decal maps.
    */
    void SetShaderResourceAsGamebryoMap(
        const efd::FixedString& resourceName, 
        efd::UInt32 gbMap,
        efd::UInt16 instanceID);
    /**
        Registers a shader resource on the pass as a texture from an NiTextureEffect.

        When a shader program requires a shader resource, it will search the pass's list of
        registered shader resource sources by name. The resources source will then provide the
        resource itself to the shader. This function has the shader get the resource from a
        specific NiTexturingEffect applied to the rendering NiMesh object.

        @param resourceName Name of the shader resource.
        @param objectFlags Object ID to obtain texture from, identified using 
            NiTextureStage::TSObjTextureFlags enumerations.
    */
    void SetShaderResourceAsTextureObject(
        const efd::FixedString& resourceName, 
        efd::UInt16 objectFlags);

    /**
        Returns the NiTexture that is registered for a given shader resource.

        @param resourceName Name of the shader resource
        @return NiTexture registered with that name. If no resource source is registered with that 
            name, or if a source is registered in some other form, this function will return NULL.
    */
    NiTexture* GetShaderResourceAsDirectResource(
        const efd::FixedString& resourceName) const;
    /**
        Returns the NiTexturingProperty map that is registered for a given shader resource.

        @param resourceName Name of the shader resource
        @param gbMap Outputs the NiTexturingProperty map registered with that name, identified 
            using NiTextureStage::TSTextureFlags enumerations.
        @return True if the registered resource source with that name was found and it was in
            the correct form, and false otherwise.
    */
    efd::Bool GetShaderResourceAsGamebryoMap(
        const efd::FixedString& resourceName, 
        efd::UInt32& gbMap) const;
    /**
        Returns the NiTextureEffect object that is registered for a given shader resource.

        @param resourceName Name of the shader resource
        @param objectFlags Outputs the NiTextureEffect object registered with that name, identified 
            using NiTextureStage::TSObjTextureFlags enumerations.
        @return True if the registered resource source with that name was found and it was in
            the correct form, and false otherwise.
    */
    efd::Bool GetShaderResourceAsTextureObject(
        const efd::FixedString& resourceName, 
        efd::UInt16& objectFlags) const;

    /// Returns the number of shader resource names registered with the pass.
    inline efd::UInt8 GetShaderResourceCount() const;

    /// Set the Stream Out settings on the pass.
    inline void SetStreamOutSettings(const NiStreamOutSettings& streamOutSettings);
    /// Return the Stream Out settings on the pass.
    inline NiStreamOutSettings& GetStreamOutSettings();

    /// For a pass using compute shaders, set the thread group counts used to invoke the shader.
    inline void SetComputeThreadGroupCounts(
        efd::UInt32 threadGroupCountX, 
        efd::UInt32 threadGroupCountY, 
        efd::UInt32 threadGroupCountZ);
    /// Return the X thread group count used to invoke a compute shader.
    inline efd::UInt32 GetComputeThreadGroupCountX() const;
    /// Return the Y thread group count used to invoke a compute shader.
    inline efd::UInt32 GetComputeThreadGroupCountY() const;
    /// Return the Z thread group count used to invoke a compute shader.
    inline efd::UInt32 GetComputeThreadGroupCountZ() const;

    /// @cond EMERGENT_INTERNAL

    /// Return the input signature for the vertex shader.
    ID3DBlob* GetInputSignature() const;
    /// Set the input signature for the vertex shader.
    void SetInputSignature(ID3DBlob* inputSignature);

    /// Wrapper for D3D11ShaderCore::ObtainTexture to get the shader resource for a ResourceSource. 
    const efd::Bool ObtainAndCacheResource(
        efd::UInt8 shaderResourceID, 
        const NiRenderCallContext& callContext, 
        efd::FixedString& resourceName, 
        NiTexturingProperty::ClampMode& clampMode,
        NiTexturingProperty::FilterMode& filterMode,
        efd::UInt16& maxAnisotropy);

    /// @endcond

protected:
    /// Hidden Constructor
    D3D11Pass();

    /// Find a ResourceSource by name and return its index.
    efd::UInt32 FindShaderResourceSource(const efd::FixedString& resourceName) const;

    /// Update the shader constant maps.
    efd::UInt32 UpdateShaderConstants(const NiRenderCallContext& callContext);

    /// Update the list of the D3D11RenderStateGroup::Sampler objects that the shaders in the pass 
    /// will use based on the names of the samplers that the shaders expect.
    void UpdateSamplers();
    /// Update the list of the UAVSlot objects that the shaders in the pass will
    /// use based on the names of the UAVs that the shaders expect.
    void UpdateUAVs(const D3D11ShaderCore* pShader);

    enum
    {
        MAX_NAME_LENGTH = 16
    };

    efd::Char m_name[MAX_NAME_LENGTH];

    D3D11RenderStateGroupPtr m_spRenderStateGroup;

    NiTObjectArray<D3D11ShaderConstantMapPtr> m_shaderConstantMapArray;

    ID3DBlob* m_pInputSignature;

    efd::Char* m_pVertexShaderProgramFile;
    efd::Char* m_pVertexShaderEntryPoint;
    efd::Char* m_pVertexShaderTarget;

    efd::Char* m_pHullShaderProgramFile;
    efd::Char* m_pHullShaderEntryPoint;
    efd::Char* m_pHullShaderTarget;

    efd::Char* m_pDomainShaderProgramFile;
    efd::Char* m_pDomainShaderEntryPoint;
    efd::Char* m_pDomainShaderTarget;

    efd::Char* m_pGeometryShaderProgramFile;
    efd::Char* m_pGeometryShaderEntryPoint;
    efd::Char* m_pGeometryShaderTarget;

    efd::Char* m_pPixelShaderProgramFile;
    efd::Char* m_pPixelShaderEntryPoint;
    efd::Char* m_pPixelShaderTarget;

    efd::Char* m_pComputeShaderProgramFile;
    efd::Char* m_pComputeShaderEntryPoint;
    efd::Char* m_pComputeShaderTarget;

    /**
        Internal class that provides a ResourceSource to the shader.

        ResourceSource objects on the pass indicate where to get each shader resource that
        the various shaders in the pass will require. The possibile sources for the resources
        include NiTexturingProperty or NiTextureEffect on the mesh, or an NiTexture pointer 
        stored directly on the pass.
    */
    class ResourceSource : public efd::MemObject
    {
    public:
        inline ResourceSource();
        inline ResourceSource(ResourceSource& resourceSource);
        virtual ~ResourceSource();

        inline void SetName(const efd::FixedString& name);
        inline const efd::FixedString& GetName() const;

        enum ResourceSourceDimension
        {
            RESOURCE_SOURCE_INVALID,
            RESOURCE_SOURCE_TEXTURE_MAP_FLAGS,
            RESOURCE_SOURCE_OBJECT_FLAGS,
            RESOURCE_SOURCE_RESOURCE_POINTER
        };

        inline void SetGamebryoMapFlags(efd::UInt32 gamebryoMapFlags);
        inline void SetTextureObjectFlags(efd::UInt16 objectFlags);
        inline void SetDirectResource(NiTexture* pResource);

        inline void SetCachedResource(NiTexture* pResource);

        inline efd::UInt32 GetGamebryoMapFlags() const;
        inline efd::UInt16 GetTextureObjectFlags() const;
        inline NiTexture* GetDirectResource() const;

        inline NiTexture* GetCachedResource() const;

    protected:

        efd::FixedString m_resourceName;

        ResourceSourceDimension m_dimension;

        union 
        {
            efd::UInt32 m_gamebryoMapFlags;
            efd::UInt16 m_textureObjectFlags;
        };

        NiTexturePtr m_spResource;
    };

    /**
        Search for a ConstantBufferDesc on the pass. 

        The ConstantBufferDesc must match the provided name and the layout of the variables
        from the shader reflection. This allows different shaders on a pass to have constant buffer
        name collisions (like "$Globals") and still ensure that the same constant buffer doesn't
        have to be listed in two separate ConstantBufferDesc objects.
    */ 
    ConstantBufferDesc* FindConstantBufferDesc(
        const efd::FixedString& bufferName, 
        ID3D11ShaderReflection* pShaderReflection) const;
    /// Add a new ConstantBufferDesc to the pass using the name and the layout of variables
    /// found in the shader reflection.
    ConstantBufferDesc* AddConstantBufferDesc(
        const efd::FixedString& bufferName, 
        ID3D11ShaderReflection* pShaderReflection);

    ConstantBufferDesc* m_constantBufferDescs;

    NiTObjectSet<ResourceSource> m_shaderResources;

    D3D11ShaderProgramData m_shaders[NiGPUProgram::PROGRAM_MAX];

    /// Indicates whether the sampler arrays on the D3D11ShaderProgramData objects are valid
    efd::UInt32 m_renderStateGroupResetCount;

    /// Indicates whether the UAV arrays on the D3D11ShaderProgramData objects are valid
    efd::UInt32 m_unorderedAccessViewResetCount;

    /// Stream Out settings for the pass
    NiStreamOutSettings m_streamOutSettings;

    efd::UInt32 m_threadGroupCountX;
    efd::UInt32 m_threadGroupCountY;
    efd::UInt32 m_threadGroupCountZ;

    efd::Bool m_shaderResourcesLinked;
};

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11Pass.inl>

#endif // EE_D3D11PASS_H
