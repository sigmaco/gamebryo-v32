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
#ifndef EE_D3D11DOMAINSHADER_H
#define EE_D3D11DOMAINSHADER_H

#include <ecrD3D11Renderer/D3D11ShaderProgram.h>

namespace ecr
{

/**
    Encapsulates a D3D11 domain shader.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11DomainShader : public D3D11ShaderProgram
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    /// Constructor for an uninitialized D3D11DomainShader.
    D3D11DomainShader();

    /// This constructor creates an initialized D3D11DomainShader using the provided domain shader 
    /// and an ID3DBlob containing the shader's byte code.
    D3D11DomainShader(ID3D11DomainShader* pDomainShader, ID3DBlob* pShaderByteCode);

    /// Destructor
    virtual ~D3D11DomainShader();
    //@}

    /// Returns the D3D11 domain shader
    inline ID3D11DomainShader* GetDomainShader() const;

    /// Sets the D3D11 domain shader
    void SetDomainShader(ID3D11DomainShader* pPixelShader);

    /// Releases the ID3D11DomainShader reference
    virtual void DestroyRendererData();

    /// Recreates the ID3D11ComptueShader from shader byte code, if it exists.
    virtual void RecreateRendererData();

protected:
    ID3D11DomainShader* m_pDomainShader;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11DomainShader
/// class.
typedef efd::SmartPointer<D3D11DomainShader> D3D11DomainShaderPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11DomainShader.inl>

#endif // EE_D3D11DOMAINSHADER_H
