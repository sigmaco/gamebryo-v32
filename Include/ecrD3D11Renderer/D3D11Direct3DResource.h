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
#ifndef EE_D3D11DIRECT3DRESOURCE_H
#define EE_D3D11DIRECT3DRESOURCE_H

#include <ecrD3D11Renderer/D3D11TextureData.h>

class NiRenderer;

namespace ecr
{

/**
    NiTexture-derived class that can be created by the renderer to wrap a D3D11 resource 
    provided by the application. 
    
    This allows applications to create D3D11 resources in ways unexpected by Gamebryo but still
    allow Gamebryo to interact with them as it does with other resources.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11Direct3DResource : public NiTexture
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @cond EMERGENT_INTERNAL

    /**
        Create a new instance of an ecr::D3D11Direct3DResource. 
        
        Applications should not call this function, and instead use 
        ecr::D3D11Renderer::CreateNiTextureFromD3D11Resource.
    */ 
    static D3D11Direct3DResource* Create(NiRenderer* pkRenderer);

    /// @endcond

    /// Returns the width of the resource if it is a texture, or the number of elements for a 
    /// buffer.
    virtual efd::UInt32 GetWidth() const;
    /// Returns the height of the resource if it is a texture with 2 or more dimensions, or 
    /// 0 otherwise.
    virtual efd::UInt32 GetHeight() const;
    /// Returns the depth of the resource if it is a texture with 3 dimensions, or 0 otherwise.
    virtual efd::UInt32 GetDepth() const;
    /// Returns the number of elements in the resource if it is a texture array, or 1 otherwise.
    virtual efd::UInt32 GetArrayCount() const;

    /// @cond EMERGENT_INTERNAL

    /// Sets the resource width.
    inline void SetWidth(efd::UInt32 width);
    /// Sets the resource height.
    inline void SetHeight(efd::UInt32 height);
    /// Sets the resource depth.
    inline void SetDepth(efd::UInt32 depth);
    /// Sets the resource array count.
    inline void SetArrayCount(efd::UInt32 arrayCount);

    /// @endcond

protected:
    /// Hidden constructor.
    D3D11Direct3DResource();

    efd::UInt32 m_width;
    efd::UInt32 m_height;
    efd::UInt32 m_depth;
    efd::UInt32 m_arrayCount;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the
/// D3D11Direct3DResource class.
typedef efd::SmartPointer<D3D11Direct3DResource> D3D11Direct3DResourcePtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11Direct3DResource.inl>

#endif // EE_D3D11DIRECT3DRESOURCE_H
