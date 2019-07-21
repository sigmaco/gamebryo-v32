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
#ifndef EE_D3D11COMPUTESHADER_H
#define EE_D3D11COMPUTESHADER_H

#include <ecrD3D11Renderer/D3D11ShaderProgram.h>

namespace ecr
{

/**
    Encapsulates a D3D11 compute shader.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ComputeShader : public D3D11ShaderProgram
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    /// Constructor for an uninitialized D3D11ComputeShader.
    D3D11ComputeShader();

    /// This constructor creates an initialized D3D11ComputeShader using the provided compute 
    /// shader and an ID3DBlob containing the shader's byte code.
    D3D11ComputeShader(ID3D11ComputeShader* pComputeShader, ID3DBlob* pShaderByteCode);

    /// Destructor
    virtual ~D3D11ComputeShader();
    //@}

    /// Returns the D3D11 compute shader
    inline ID3D11ComputeShader* GetComputeShader() const;

    /// Sets the D3D11 compute shader
    void SetComputeShader(ID3D11ComputeShader* pPixelShader);

    /// Releases the ID3D11ComputeShader reference
    virtual void DestroyRendererData();

    /// Recreates the ID3D11ComptueShader from shader byte code, if it exists.
    virtual void RecreateRendererData();

protected:
    ID3D11ComputeShader* m_pComputeShader;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11ComputeShader
/// class.
typedef efd::SmartPointer<D3D11ComputeShader> D3D11ComputeShaderPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11ComputeShader.inl>

#endif // EE_D3D11COMPUTESHADER_H
