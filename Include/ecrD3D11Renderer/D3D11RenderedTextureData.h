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
#ifndef EE_D3D11RENDEREDTEXTUREDATA_H
#define EE_D3D11RENDEREDTEXTUREDATA_H

#include <ecrD3D11Renderer/D3D11TextureData.h>

#include <Ni2DBuffer.h>

class NiRenderedTexture;

namespace ecr
{

/**
    ecr::D3D11RenderedTextureData manages the D3D11 resource and resource view representing a 
    rendered texture.

    Textures of all dimensions, including cube maps, can be represented with this class. Textures
    that are rendered to using multiple resource views can be managed by separate NiRenderedTexture
    objects that refer to the same D3D11 resource but have different resource views.
*/

class EE_ECRD3D11RENDERER_ENTRY D3D11RenderedTextureData : public D3D11TextureData
{
public:
    /// @name Construction and Destruction
    //@{
    /// Destructor.
    virtual ~D3D11RenderedTextureData();
    //@}

    /**
        Creates a new D3D11RenderedTextureData. 

        @param pTexture Texture to create the renderer-specific data for.
        @param msaaPref Multisample preferences for the texture.
    */
    static D3D11RenderedTextureData* Create(
        NiRenderedTexture* pTexture,
        Ni2DBuffer::MultiSamplePreference msaaPref);

protected:
    /// Hidden constructor
    D3D11RenderedTextureData(NiRenderedTexture* pTexture);

    /// Create the resource and the resource view.
    efd::Bool PrepareTexture(Ni2DBuffer::MultiSamplePreference msaaPref);

    efd::UInt16 m_numTextures;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the
/// D3D11RenderedTextureData class.
typedef efd::SmartPointer<D3D11RenderedTextureData> D3D11RenderedTextureDataPtr;

}   // End namespace ecr.

#endif // EE_D3D11RENDEREDTEXTUREDATA_H
