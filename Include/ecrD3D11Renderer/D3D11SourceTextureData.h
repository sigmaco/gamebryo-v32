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
#ifndef EE_D3D11SOURCETEXTUREDATA_H
#define EE_D3D11SOURCETEXTUREDATA_H

#include <ecrD3D11Renderer/D3D11TextureData.h>

class NiSourceTexture;

namespace ecr
{

class D3D11PersistentSrcTextureRendererData;

/**
    ecr::D3D11SourceTextureData manages the D3D11 resource and resource view representing a 
    static texture loaded from memory or a file.

    Textures of all dimensions, including cube maps, can be represented with this class. Textures
    that require multiple resource views can be managed by separate NiSourceTexture
    objects that refer to the same D3D11 resource but have different resource views.
*/

class EE_ECRD3D11RENDERER_ENTRY D3D11SourceTextureData : public D3D11TextureData
{
public:
    /// @name Construction and Destruction
    //@{
    /// Destructor
    virtual ~D3D11SourceTextureData();
    //@}

    /**
        Creates a new D3D11SourceTextureData. 

        @param pTexture Texture to create the renderer-specific data for.
    */
    static D3D11SourceTextureData* Create(NiSourceTexture* pTexture);

    /// Forces the D3D11 representation of the texture to update itself based on the source texture.
    virtual void Update();

    /// Set the number of mipmap levels to skip when loading the D3D11 representation of the 
    /// texture.
    static efd::Bool SetMipmapSkipLevel(efd::UInt16 skip);
    /// Return the number of mipmap levels to skip when loading the D3D11 representation of the 
    /// texture.
    static efd::UInt16 GetMipmapSkipLevel();

protected:
    /// Hidden constructor
    D3D11SourceTextureData(NiSourceTexture* pTexture);

    /// Load the texture from whatever source it is stored in.
    efd::Bool LoadTexture();

    /// Initialize the texture from an NiPixelData
    efd::Bool InitializeTexture(
        const NiPixelData* pPixels, 
        efd::Bool isCube,
        efd::Bool isStatic);
    /// Initialize the texture from an NiPersistantSrcTextureRendererData
    efd::Bool D3D11SourceTextureData::InitializeTexture(
        const D3D11PersistentSrcTextureRendererData* pData,
        efd::Bool isCube,
        efd::Bool isStatic);
    /// Update the texture with the new NiPixelData.
    efd::Bool UpdateTexture(const NiPixelData* pPixels);
    /// Update the texture with the new NiPalette.
    efd::Bool UpdatePalette(NiPalette* pNewPalette);
    /// Load the texture from file.
    efd::Bool LoadTextureFile(
        const efd::Char* pFilename, 
        const NiTexture::FormatPrefs& formatPrefs);

    efd::Bool m_replacementData;
    efd::Bool m_mipmap;

    efd::UInt32 m_sourceRevID;   // can be compared with source PixelData
    efd::UInt32 m_formattedSize;

    efd::UInt16 m_levelsSkipped;
    efd::UInt16 m_numTextures;   // Texture array/cube map support

    NiPalettePtr m_spPalette;
    efd::UInt32 m_paletteRevID;

    static efd::UInt16 ms_skipLevels;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the
/// D3D11SourceTextureData class.
typedef efd::SmartPointer<D3D11SourceTextureData> D3D11SourceTextureDataPtr;

}   // End namespace ecr.

#endif // EE_D3D11SOURCETEXTUREDATA_H
