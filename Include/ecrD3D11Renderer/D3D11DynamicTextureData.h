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
#ifndef EE_D3D11DYNAMICTEXTUREDATA_H
#define EE_D3D11DYNAMICTEXTUREDATA_H

#include <ecrD3D11Renderer/D3D11TextureData.h>

class NiDynamicTexture;

namespace ecr
{

class D3D11Renderer;
/**
    Manages the D3D11 representation of a dynamic texture. 
    
    In general, an application will not have to manipulate objects of this class. Instead, 
    an application will perform operations via an NiDynamicTexture object. 
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11DynamicTextureData : public D3D11TextureData
{
public:
    /// @cond EMERGENT_INTERNAL

    /// @name Construction and Destruction
    //@{
    /// Destructor
    virtual ~D3D11DynamicTextureData();
    //@}

    /// Create the dynamic texture data for the NiDynamicTexture.
    static D3D11DynamicTextureData* Create(NiDynamicTexture* pTexture);

    /// @endcond

    /**
        Lock the texture and return a pointer to the memory.
        
        @param pitch Row pitch of the memory block.
        @return Pointer to memory block.
    */
    virtual void* Lock(efd::SInt32& pitch);

    /// Unlock the texture
    virtual bool UnLock() const;

    /// Returns whether or not the texture is locked.
    virtual bool IsLocked();

    /// @cond EMERGENT_INTERNAL

    /// Sets whether or not the texture is locked.
    virtual void SetLocked(efd::Bool isLocked);

    /// @endcond
protected:
    /// Hidden Constructor
    D3D11DynamicTextureData(NiDynamicTexture* pkTexture);

    /// Perform the lock of a 1D texture resource.
    void* Texture1DLock();
    /// Perform the lock of a 2D texture resource.
    void* Texture2DLock(efd::SInt32& pitch);
    /// Perform the lock of a 3D texture resource.
    void* Texture3DLock(efd::SInt32& rowPitch, efd::SInt32& depthPitch);

    /// Create the texture and return the pixel format used for the texture.
    const NiPixelFormat* CreateTexture(const NiDynamicTexture* pTexture);

    efd::Bool m_isTextureLocked;

    D3D11_MAP m_mapFlags;
    ID3D11Resource* m_pStagingTexture;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the
/// D3D11DynamicTextureData class.
typedef efd::SmartPointer<D3D11DynamicTextureData> D3D11DynamicTextureDataPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11DynamicTextureData.inl>

#endif // EE_D3D11DYNAMICTEXTUREDATA_H
