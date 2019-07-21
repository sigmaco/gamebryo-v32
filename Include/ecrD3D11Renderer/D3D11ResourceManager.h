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
#ifndef EE_D3D11RESOURCEMANAGER_H
#define EE_D3D11RESOURCEMANAGER_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

#include <efd/UniversalTypes.h>
#include <efd/MemObject.h>

namespace ecr
{

/**
    Wrapper class for creating D3D11 resources.

    This class wraps the D3D11 resource-creation functions. It is not necessary for applications
    to use this class to create resources.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ResourceManager : public efd::MemObject
{
public:
    /// @cond EMERGENT_INTERNAL

    /// @name Construction and Destruction
    //@{
    /**
        The constructor initializes a new ecr::D3D11ResourceManager using the D3D11 device. 

        An application should never construct a new resource manager object, but should 
        obtain a pointer to the D3D11Renderer object's instance instead.
    */
    D3D11ResourceManager(ID3D11Device* pDevice);
    /// Destructor
    virtual ~D3D11ResourceManager();
    //@}

    /// @endcond

    /** 
        Create a new ID3D11Buffer object.

        The parameters are used to create a D3D11_BUFFER_DESC object that is passed into 
        ID3D11Device::CreateBuffer along with the initial data.
    */
    ID3D11Buffer* CreateBuffer(
        efd::UInt32 bufferSize,
        efd::UInt32 bindFlags, 
        D3D11_USAGE usage,
        efd::UInt32 cpuAccessFlags, 
        efd::UInt32 miscFlags,
        efd::UInt32 structureByteStride,
        D3D11_SUBRESOURCE_DATA* pInitialData);
    /** 
        Create a new ID3D11Texture1D object.

        The parameters are used to create a D3D11_TEXTURE1D_DESC object that is passed into 
        ID3D11Device::CreateTexture1D along with the initial data.
    */
    ID3D11Texture1D* CreateTexture1D(
        efd::UInt32 width,
        efd::UInt32 mipLevels,
        efd::UInt32 arraySize, 
        DXGI_FORMAT format,
        D3D11_USAGE usage, 
        efd::UInt32 bindFlags,
        efd::UInt32 cpuAccessFlags, 
        efd::UInt32 miscFlags,
        D3D11_SUBRESOURCE_DATA* pInitialData = NULL);
    /** 
        Create a new ID3D11Texture2D object.

        The parameters are used to create a D3D11_TEXTURE2D_DESC object that is passed into 
        ID3D11Device::CreateTexture2D along with the initial data.
    */
    ID3D11Texture2D* CreateTexture2D(
        efd::UInt32 width,
        efd::UInt32 height, 
        efd::UInt32 mipLevels,
        efd::UInt32 arraySize, 
        DXGI_FORMAT format,
        efd::UInt32 msaaCount, 
        efd::UInt32 msaaQuality,
        D3D11_USAGE usage, 
        efd::UInt32 bindFlags,
        efd::UInt32 cpuAccessFlags, 
        efd::UInt32 miscFlags,
        D3D11_SUBRESOURCE_DATA* pInitialData = NULL);
    /** 
        Create a new ID3D11Texture3D object.

        The parameters are used to create a D3D11_TEXTURE3D_DESC object that is passed into 
        ID3D11Device::CreateTexture3D along with the initial data.
    */
    ID3D11Texture3D* CreateTexture3D(
        efd::UInt32 width,
        efd::UInt32 height, 
        efd::UInt32 depth, 
        efd::UInt32 mipLevels,
        DXGI_FORMAT format,
        D3D11_USAGE usage, 
        efd::UInt32 bindFlags,
        efd::UInt32 cpuAccessFlags, 
        efd::UInt32 miscFlags,
        D3D11_SUBRESOURCE_DATA* pInitialData = NULL);

protected:
    ID3D11Device* m_pDevice;
};

}   // End namespace ecr.

#endif // EE_D3D11RESOURCEMANAGER_H
