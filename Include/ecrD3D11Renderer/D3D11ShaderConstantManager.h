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
#ifndef EE_D3D11SHADERCONSTANTMANAGER_H
#define EE_D3D11SHADERCONSTANTMANAGER_H


#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

#include <efd/UniversalTypes.h>
#include <efd/MemObject.h>

namespace ecr
{

class D3D11DeviceState;
class D3D11ShaderConstantMap;
class D3D11ShaderProgram;

/**
    ecr::D3D11ShaderConstantManager accumulates individual shader constant buffers so they can be 
    set on the device context all at once.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ShaderConstantManager : public efd::MemObject
{
public:
    /// @cond EMERGENT_INTERNAL

    /// @name Construction and Destruction
    //@{
    /**
        The constructor initializes a new ecr::D3D11ShaderConstantManager using the 
        D3D11DeviceState. 
        
        An application should never construct a new device shader constant manager object, but 
        should obtain a pointer to the D3D11Renderer object's instance instead.
    */
    D3D11ShaderConstantManager(D3D11DeviceState* pkDeviceState);
    /// Destructor
    virtual ~D3D11ShaderConstantManager();
    //@}

    /// @endcond

    /// Removes all currently accumulated shader constant buffers.
    inline void ResetConstantBuffers();

    /**
        Store a constant map's constant buffer so it will be set on the device context.
        
        @param programType Shader program type for the constant buffer.
        @param bufferIndex Index of the constant buffer.
        @param pConstantMap D3D11ShaderConstantMap that contains the constant buffer to be set.
    */
    void SetShaderConstantMap(
        NiGPUProgram::ProgramType programType,
        efd::UInt32 bufferIndex,
        D3D11ShaderConstantMap* pConstantMap);

    /**
        Store a set of constant buffers so they will be set on the device context.
        
        @param programType Shader program type for the constant buffer.
        @param startSlot Starting index of the constant buffer array.
        @param numBuffers Number of buffers in the array.
        @param pBuffers Array of buffers to be set.
    */
    void SetConstantBuffers(
        NiGPUProgram::ProgramType programType,
        efd::UInt32 startSlot, 
        efd::UInt32 numBuffers,
        ID3D11Buffer*const* pBuffers);
    /**
        Returns the constant buffers that are scheduled to be set on the device context.
        
        @param programType Shader program type for the constant buffer.
        @param startSlot Starting index of the constant buffer array to read back.
        @param numBuffers Number of buffers in the array to be read back.
        @param pBuffers Caller-provided array to contain the resulting array of buffers.
    */
    void GetConstantBuffers(
        NiGPUProgram::ProgramType programType,
        efd::UInt32 startSlot, 
        efd::UInt32 numBuffers,
        ID3D11Buffer** pBuffers) const;
    /// Removes all currently accumulated constant buffers for the given shader program type.
    void ClearConstantBuffers(NiGPUProgram::ProgramType programType);

    // Set accumulated constant buffers on the device context.
    void ApplyShaderConstants();

protected:
    D3D11DeviceState* m_pDeviceState;
    ID3D11Buffer* m_constantBufferArray[NiGPUProgram::PROGRAM_MAX]
        [D3D11_COMMONSHADER_CONSTANT_BUFFER_REGISTER_COUNT];
};

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11ShaderConstantManager.inl>

#endif // EE_D3D11SHADERCONSTANTMANAGER_H
