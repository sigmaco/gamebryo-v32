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
#ifndef EE_D3D11SHADERPROGRAMDATA_H
#define EE_D3D11SHADERPROGRAMDATA_H

#include <ecrD3D11Renderer/D3D11ShaderProgram.h>
#include <ecrD3D11Renderer/D3D11RenderStateGroup.h>

namespace ecr
{

class UAVSlot;
class ConstantBufferDesc;

/**
    Container class that manages the various constant buffers, shader resources, samplers,
    unordered access views, and shader program required to successfully set up and execute
    a shader program on the device context.

    Instances of this class exist on a D3D11Pass object for each shader type, and they will be 
    populated during D3D11Pass::ExposeShaderParameters with the names and/or descriptions of the
    various resources that the shader program will require.

    This class is internal to the renderer, and should not be operated on by an application.
*/
class D3D11ShaderProgramData : public efd::MemObject
{
public:
    /// @cond EMERGENT_INTERNAL

    /// Return the shader program that this object will manage.
    inline D3D11ShaderProgram* GetShaderProgram() const;
    /// Set the shader program that this object will manage.
    inline void SetShaderProgram(D3D11ShaderProgram* pShaderProgram);

    /// Set the number of constant buffers that this object will manage.
    void SetShaderConstantBufferAllocatedSize(efd::UInt8 maxCount);
    /// Return the number of constant buffers that have had ConstantBufferDesc pointers assigned.
    inline efd::UInt8 GetShaderConstantBufferCount() const;
    /// Return the number of constant buffers that this object has allocated memory for.
    inline efd::UInt8 GetShaderConstantBufferAllocatedSize() const;

    /// Set the number of shader resources that this object will manage
    void SetShaderResourceAllocatedSize(efd::UInt8 maxCount);
    /// Return the number of shader resources that have had names assigned.
    inline efd::UInt8 GetShaderResourceCount() const;
    /// Return the number of shader resources that this object has allocated memory for.
    inline efd::UInt8 GetShaderResourceAllocatedSize() const;

    /// Set the number of samplers that this object will manage
    void SetSamplerAllocatedSize(efd::UInt8 maxCount);
    /// Return the number of samplers that have had names assigned.
    inline efd::UInt8 GetSamplerCount() const;
    /// Return the number of samplers that this object has allocated memory for.
    inline efd::UInt8 GetSamplerAllocatedSize() const;

    /// Set the number of unordered access views that this object will manage.
    void SetUAVAllocatedSize(efd::UInt8 maxCount);
    /// Return the number of unordered access views that have had UAVSlot pointers assigned.
    inline efd::UInt8 GetUAVCount() const;
    /// Return the number of unordered access views that this object has allocated memory for.
    inline efd::UInt8 GetUAVAllocatedSize() const;

    /// Add the ConstantBufferDesc for a constant buffer index on the shader.
    inline void SetShaderConstantBufferDesc(
        efd::UInt8 shaderIndex, 
        ConstantBufferDesc* pCBDesc);

    /// Return the ConstantBufferDesc for a constant buffer index on the shader, if it exists.
    inline efd::Bool GetShaderConstantBufferDesc(
        efd::UInt8 shaderIndex, 
        ConstantBufferDesc*& pCBDesc) const;

    /// Set the shader resource name for a resource index on the shader.
    inline void SetShaderResourceName(
        efd::UInt8 shaderIndex, 
        efd::FixedString& name);

    /// Return the shader resource name for a resource index on the shader, if it exists.
    inline efd::Bool GetShaderResourceName(
        efd::UInt8 shaderIndex,
        efd::FixedString& name) const;

    /// Set the index of a ResourceSource in a D3D11Pass for a resource index on the shader.
    inline void SetShaderResourceIndex(
        efd::UInt8 shaderIndex, 
        efd::UInt8 shaderResourceSourceIndex);

    /// Return the index of a ResourceSource in a D3D11Pass for a resource index on the shader, 
    /// if it exists.
    inline efd::Bool GetShaderResourceIndex(
        efd::UInt8 shaderIndex, 
        efd::UInt8& shaderResourceSourceIndex) const;

    /// Set the sampler name for a sampler index on the shader.
    inline void SetSamplerName(
        efd::UInt8 shaderIndex, 
        efd::FixedString& samplerName);

    /// Return the sampler name for a sampler index on the shader, if it exists.
    inline efd::Bool GetSamplerName(
        efd::UInt8 shaderIndex,
        efd::FixedString& samplerName) const;

    /// Return the D3D11RenderStateGroup::Sampler for a sampler index on the shader.
    inline efd::Bool GetSampler(
        efd::UInt8 shaderIndex, 
        D3D11RenderStateGroup::Sampler*& pSampler) const;

    /// Set the UAV name for a UAV index on the shader.
    inline void SetUAVName(
        efd::UInt8 shaderIndex, 
        efd::FixedString& name);

    /// Return the UAV name for a UAV index on the shader, if it exists.
    inline efd::Bool GetUAVName(
        efd::UInt8 shaderIndex,
        efd::FixedString& name) const;

    /// Return the UAVSlot for a UAV index on the shader.
    inline efd::Bool GetUAVSlot(
        efd::UInt8 shaderIndex, 
        UAVSlot*& pUAV) const;

    /// @endcond

protected:
    /// Hidden construtor - instances of this class are created only in an array inside 
    /// D3D11Pass objects.
    inline D3D11ShaderProgramData();
    /// Destructor
    inline ~D3D11ShaderProgramData();

    D3D11ShaderProgramPtr m_spShaderProgram;

    ConstantBufferDesc** m_shaderConstantBufferDescs;

    efd::FixedString* m_shaderResourceNames;
    efd::UInt8* m_shaderResourceIndices;

    efd::FixedString* m_shaderSamplerNames;
    D3D11RenderStateGroup::Sampler** m_shaderSamplers;

    // Bind/name lookups for UnorderedAccessViews
    efd::FixedString* m_shaderUAVNames;
    UAVSlot** m_shaderUAVs;

    efd::UInt8 m_shaderConstantBufferCount;
    efd::UInt8 m_shaderConstantBufferAllocatedSize;

    // Assumption: The shaderResource count and SRVName count will be identical
    efd::UInt8 m_shaderResourceCount;
    efd::UInt8 m_shaderResourceAllocatedSize;

    // Assumption: The SamplerName count and Sampler count will be identical
    efd::UInt8 m_shaderSamplerCount;
    efd::UInt8 m_shaderSamplerAllocatedSize;

    // Assumption: The UAVName count and UAVcount will be identical
    efd::UInt8 m_shaderUAVCount;
    efd::UInt8 m_shaderUAVAllocatedSize;

    friend class D3D11Pass;
};

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11ShaderProgramData.inl>

#endif // EE_D3D11SHADERPROGRAMDATA_H
