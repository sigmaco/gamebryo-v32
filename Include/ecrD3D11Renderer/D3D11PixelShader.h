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
#ifndef EE_D3D11PIXELSHADER_H
#define EE_D3D11PIXELSHADER_H

#include <ecrD3D11Renderer/D3D11ShaderProgram.h>

namespace ecr
{

/**
    Encapsulates a D3D11 pixel shader.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11PixelShader : public D3D11ShaderProgram
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    /// Constructor for an uninitialized D3D11PixelShader.
    D3D11PixelShader();

    /// This constructor creates an initialized D3D11PixelShader using the provided pixel shader 
    /// and an ID3DBlob containing the shader's byte code.
    D3D11PixelShader(ID3D11PixelShader* pPixelShader, ID3DBlob* pShaderByteCode);

    /// Destructor
    virtual ~D3D11PixelShader();
    //@}

    /// Returns the D3D11 pixel shader
    inline ID3D11PixelShader* GetPixelShader() const;

    /// Sets the D3D11 pixel shader
    void SetPixelShader(ID3D11PixelShader* pPixelShader);

    /// Releases the ID3D11PixelShader reference
    virtual void DestroyRendererData();

    /// Recreates the ID3D11ComptueShader from shader byte code, if it exists.
    virtual void RecreateRendererData();

protected:
    ID3D11PixelShader* m_pPixelShader;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11PixelShader
/// class.
typedef efd::SmartPointer<D3D11PixelShader> D3D11PixelShaderPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11PixelShader.inl>

#endif // EE_D3D11PIXELSHADER_H
