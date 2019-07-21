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
#ifndef EE_UNORDEREDACCESSRESOURCE_H
#define EE_UNORDEREDACCESSRESOURCE_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

#include <NiDataStream.h>
#include <NiTexture.h>

namespace ecr
{

/**
    Container for resources that will be provided to a compute shader as an unordered access view.

    Applications can create UnorderedAccessView objects to contain unordered access resources, and
    pass the objects to a UAVSlot object on a D3D11ShaderCore. The shader will then set those 
    resources on the device context when it runs the compute shader.
*/
class EE_ECRD3D11RENDERER_ENTRY UnorderedAccessResource : public NiRefObject
{
public:
    /// @name Construction and Destruction
    //@{
    /// Constructor.
    UnorderedAccessResource();
    /// Destructor.
    virtual ~UnorderedAccessResource();
    //@}

    /** 
        Provide an NiDataStream as the source to the UnorderedAccessResource. 
        
        An UnorderedAccessView will be created automatically.
    */
    inline void SetResourceAsNiDataStream(NiDataStream* pDataStream);
    /**
        Provide an NiTexture as the source to the UnorderedAccessResource 
        
        An UnorderedAccessView will be created automatically.
    */
    inline void SetResourceAsNiTexture(NiTexture* pTexture);

    /// Set flags to be used used when creating a UAV from NiDataStream or NiTexture.
    inline void SetUAVFlags(efd::UInt32 uavFlags);
    /// Return flags to be used used when creating a UAV from NiDataStream or NiTexture.
    inline efd::UInt32 GetUAVFlags() const;

    /// Recreate the UnorderedAccessView.
    void UpdateUnorderedAccessView();

    /// Set the D3D11 resource and unordered access view directly.
    inline void SetResourceAsD3D11Resource(
        ID3D11Resource* pResource, 
        ID3D11UnorderedAccessView* pUAV = NULL);

    /// Return the resource.
    inline ID3D11Resource* GetD3D11Resource() const;
    /// Return the unordered access view.
    inline ID3D11UnorderedAccessView* GetUnorderedAccessView() const;

protected:
    /// Set the resource and UAV.
    void SetResourceAndUAV(
        ID3D11Resource* pResource, 
        ID3D11UnorderedAccessView* pUAV);
    /// Release the resource and UAV.
    inline void ReleaseResourceAndUAV();

    NiDataStreamPtr m_spDataStream;
    NiTexturePtr m_spTexture;

    efd::UInt32 m_uavFlags;

    ID3D11Resource* m_pResource; 
    ID3D11UnorderedAccessView* m_pUAV;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the
/// UnorderedAccessResource class.
typedef efd::SmartPointer<UnorderedAccessResource> UnorderedAccessResourcePtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/UnorderedAccessResource.inl>

#endif // EE_UNORDEREDACCESSRESOURCE_H
