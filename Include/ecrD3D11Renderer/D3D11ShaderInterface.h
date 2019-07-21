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
#ifndef EE_D3D11SHADERINTERFACE_H
#define EE_D3D11SHADERINTERFACE_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <NiShader.h>

struct _D3DX11_STATE_BLOCK_MASK;
typedef _D3DX11_STATE_BLOCK_MASK D3DX11_STATE_BLOCK_MASK;

namespace ecr
{

/**
    D3D11ShaderInterface is the interface for D3D11-specific NiShader-derived objects.

    It is a pure interface class, and the lowest level at which an application can derive their 
    own shaders from.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ShaderInterface : public NiShader
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /// Constructor
    D3D11ShaderInterface();
    /// Destructor
    virtual ~D3D11ShaderInterface();
    //@}

    /// Virtual function called when the renderer data is being destroyed, to give the shader a 
    /// chance to release any data/objects that are tied to the device at this point.
    virtual void DestroyRendererData() = 0;
    /// Virtual function called when the renderer data is being reconstruted, to give the shader a 
    /// chance to recreate any data/objects that are tied to the device at this point.
    virtual void RecreateRendererData() = 0;

    /// Return a mask indicating which render states this shader will set.
    virtual const D3DX11_STATE_BLOCK_MASK* GetStateBlockMask(
        const NiRenderCallContext& callContext) const;

    /// @cond EMERGENT_INTERNAL

    /// Add a reference to an NiVertexDeclarationCache, which D3D11 cast to 
    /// D3D11MeshMaterialBinding
    virtual void ReferenceVertexDeclarationCache(
        NiVertexDeclarationCache vdCache) const;
    /// Release a reference to an NiVertexDeclarationCache, which D3D11 cast to 
    /// D3D11MeshMaterialBinding
    virtual void ReleaseVertexDeclarationCache(
        NiVertexDeclarationCache vdCache) const;

    /// @endcond

protected:
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11ShaderInterface
/// class.
typedef efd::SmartPointer<D3D11ShaderInterface> D3D11ShaderInterfacePtr;

}   // End namespace ecr.

#endif // EE_D3D11SHADERINTERFACE_H
