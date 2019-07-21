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
#ifndef EE_D3D11HULLSHADER_H
#define EE_D3D11HULLSHADER_H

#include <ecrD3D11Renderer/D3D11ShaderProgram.h>

namespace ecr
{

/**
    Encapsulates a D3D11 hull shader.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11HullShader : public D3D11ShaderProgram
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    /// Constructor for an uninitialized D3D11HullShader.
    D3D11HullShader();

    /// This constructor creates an initialized D3D11HullShader using the provided hull shader 
    /// and an ID3DBlob containing the shader's byte code.
    D3D11HullShader(ID3D11HullShader* pHullShader, ID3DBlob* pShaderByteCode);

    /// Destructor
    virtual ~D3D11HullShader();
    //@}

    /// Returns the D3D11 hull shader
    inline ID3D11HullShader* GetHullShader() const;

    /// Sets the D3D11 hull shader
    void SetHullShader(ID3D11HullShader* pPixelShader);

    /// Releases the ID3D11HullShader reference
    virtual void DestroyRendererData();

    /// Recreates the ID3D11ComptueShader from shader byte code, if it exists.
    virtual void RecreateRendererData();

protected:
    ID3D11HullShader* m_pHullShader;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11HullShader
/// class.
typedef efd::SmartPointer<D3D11HullShader> D3D11HullShaderPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11HullShader.inl>

#endif // EE_D3D11HULLSHADER_H
