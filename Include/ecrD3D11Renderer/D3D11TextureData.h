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
#ifndef EE_D3D11TEXTUREDATA_H
#define EE_D3D11TEXTUREDATA_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

#include <NiTexture.h>

namespace ecr
{

class D3D11RenderedTextureData;
class D3D11SourceTextureData;
class D3D11DynamicTextureData;

/**
    D3D11TextureData manages the D3D11 structures representing a shader resource and its 
    shader resource view.
*/

class EE_ECRD3D11RENDERER_ENTRY D3D11TextureData : public NiTexture::RendererData
{
public:
    /// @name Construction and Destruction
    //@{
    /// Constructor.
    D3D11TextureData(NiTexture* pTexture);
    /// Destructor.
    virtual ~D3D11TextureData();
    //@}

    /// Returns the number of mipmap levels in the texture.
    inline efd::UInt16 GetLevels() const;

    /// Returns whether this texture is an NiRenderedTexture.
    inline efd::Bool IsRenderedTexture() const;
    /// Returns whether this texture is an NiSourceTexture.
    inline efd::Bool IsSourceTexture() const;
    /// Returns whether this texture is an NiDynamicTexture.
    inline efd::Bool IsDynamicTexture() const;
    /// Returns whether this texture is a cube map.
    inline efd::Bool IsCubeMap() const;

    /// Returns whether this resource is an ID3D11Buffer.
    inline efd::Bool IsBuffer() const;
    /// Returns whether this resource is an ID3D11Texture1D.
    inline efd::Bool IsTexture1D() const;
    /// Returns whether this resource is an ID3D11Texture2D.
    inline efd::Bool IsTexture2D() const;
    /// Returns whether this resource is an ID3D11Texture3D.
    inline efd::Bool IsTexture3D() const;

    /// Returns the depth of this resource, if it is a 3D texture.
    inline efd::UInt32 GetDepth() const;
    /// Returns the array count of this resource, if it is a texture array.
    inline efd::UInt32 GetArrayCount() const;

    /// Release all texture data.
    static void ClearTextureData();

    /// Return the D3D11 shader resource view for this resource.
    inline ID3D11ShaderResourceView* GetResourceView() const;
    /// Return the D3D11 resource for this resource.
    inline ID3D11Resource* GetResource() const;

    /// Create a default shader resource view for a given D3D11 resource.
    static ID3D11ShaderResourceView* CreateDefaultResourceView(ID3D11Resource* pResource);

    /// Set the resource view for the resource.
    void SetResourceView(ID3D11ShaderResourceView* pkResourceView);

protected:
    /// Return the closest supported D3D11 pixel format for a given pixel format.
    const NiPixelFormat* FindMatchingPixelFormat(
        const NiPixelFormat& srcFmt, 
        const NiTexture::FormatPrefs& formatPrefs,
        D3D11_FORMAT_SUPPORT supportTest);

    /// Return the closest supported D3D11 pixel format for a set of texture prefs.
    const NiPixelFormat* FindMatchingPixelFormat(
        const NiTexture::FormatPrefs& formatPrefs,
        D3D11_FORMAT_SUPPORT supportTest);

    /// Initialize a texture data from the resource and shader resource view.
    efd::Bool InitializeFromD3D11Resource(
        ID3D11Resource* pD3D11Texture,
        ID3D11ShaderResourceView* pResourceView = NULL);

    efd::UInt16 m_levels;

    enum ResourceTypeFlags
    {
        RESOURCETYPE_SOURCE     = 1 << 0,
        RESOURCETYPE_RENDERED   = 1 << 1,
        RESOURCETYPE_DYNAMIC    = 1 << 2,
        RESOURCETYPE_CUBE       = 1 << 11,
        RESOURCETYPE_BUFFER     = 1 << 12,
        RESOURCETYPE_1D         = 1 << 13, // Supports texture arrays as well
        RESOURCETYPE_2D         = 1 << 14, // Supports texture arrays as well
        RESOURCETYPE_3D         = 1 << 15,
        RESOURCETYPE_DIMENSIONMASK = 0xF800
    };
    efd::UInt16 m_resourceType;
    efd::UInt32 m_depthOrArrayCount;

    ID3D11ShaderResourceView* m_pResourceView;
    ID3D11Resource* m_pD3D11Resource;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11TextureData
/// class.
typedef efd::SmartPointer<D3D11TextureData> D3D11TextureDataPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11TextureData.inl>

#endif // EE_D3D11TEXTUREDATA_H
