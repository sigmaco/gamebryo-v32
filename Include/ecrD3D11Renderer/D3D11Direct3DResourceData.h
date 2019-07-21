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
#ifndef EE_D3D11DIRECT3DRESOURCEDATA_H
#define EE_D3D11DIRECT3DRESOURCEDATA_H

#include <ecrD3D11Renderer/D3D11TextureData.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

class NiRenderer;

namespace ecr
{

class D3D11Direct3DResource;

/**
    D3D11TextureData-derived class that manages a D3D11 resource provided by the application. 
    
    This allows applications to create D3D11 resources in ways unexpected by Gamebryo but still
    allow Gamebryo to interact with them as it does with other resources.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11Direct3DResourceData : public D3D11TextureData
{
public:
    /// @cond EMERGENT_INTERNAL

    /// @name Construction and Destruction
    //@{
    /// Destructor.
    virtual ~D3D11Direct3DResourceData();
    //@}

    /**
        Creates the renderer data for the ecr::D3D11Direct3DResourceData. 
        
        Applications should not call this function, and instead use 
        ecr::D3D11Renderer::CreateNiTextureFromD3D11Resource.
    */ 
    static D3D11Direct3DResourceData* Create(
        D3D11Direct3DResource* pTexture, 
        ID3D11Resource* pD3D11Texture,
        ID3D11ShaderResourceView* pResourceView);

    /// @endcond

protected:
    /// Hidden Constructor.
    D3D11Direct3DResourceData(D3D11Direct3DResource* pTexture);
};

}   // End namespace ecr.

#endif // EE_D3D11DIRECT3DRESOURCEDATA_H
