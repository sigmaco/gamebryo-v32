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
#ifndef EE_D3D112DBUFFERDATA_H
#define EE_D3D112DBUFFERDATA_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

#include <Ni2DBuffer.h>

class NiDepthStencilBuffer;

namespace ecr
{

//------------------------------------------------------------------------------------------------
/**
    Abstract base class representing a 2D buffer that can be used as a render or depth stencil 
    target.
    
    Instances of this class or its derivations are basically equivalent to an ID3D11Texture2D with
    an appropriate resource view. Applications should not need to create or manipulate objects of 
    this type directly.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D112DBufferData : public Ni2DBuffer::RendererData
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRootRTTI(D3D112DBufferData);

    /// @endcond
public:
    /// Destructor
    virtual ~D3D112DBufferData();

    /// @cond EMERGENT_INTERNAL

    /// Returns whether the currently derived class is capable or presenting the current render 
    /// target
    virtual efd::Bool CanDisplayFrame();
    
    /**
        Displays the frame.

        @param syncInterval Number of vertical syncs to wait on before presenting. 0 indicates no
            wait, 1 indicates wait for the next vsync, and so on.
        @param presentTest Indicates whether or not to pass DXGI_PRESENT_TEST to the Present call.
        @return Return value from IDXGISwapChain::Present.
    */
    virtual HRESULT DisplayFrame(
        efd::UInt32 syncInterval,
        efd::Bool presentTest = false);

    /// Returns the D3D11 texture that this object manages.
    ID3D11Texture2D* GetTexture2D() const;

    /// @endcond

protected:
    /// Hidden constructor
    inline D3D112DBufferData();

    ID3D11Texture2D* m_pTexture;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D112DBufferData
/// class.
typedef efd::SmartPointer<D3D112DBufferData> D3D112DBufferDataPtr;

//------------------------------------------------------------------------------------------------
/**
    A class to represents a 2D buffer that can be used as a render target. 
    
    Gamebryo creates instances of this class internally to represent rendered textures, 
    but applications can also create instances if they have an ID3D11Texture2D that 
    they want to use as a render target.    
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11RenderTargetBufferData : public D3D112DBufferData
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// Destructor
    virtual ~D3D11RenderTargetBufferData();

    /**
        Creates a D3D11RenderTargetBufferDataObject for the provided texture.

        @note This function requires that a Ni2DBuffer* reference is passed in. Since D3D11 
            requires that you create a texture prior to creating the Ni2DBuffer, the Ni2DBuffer 
            and its renderer data are populated by the Create call. Note that if pBuffer is NULL, 
            a new Ni2DBuffer will be created. If this new Ni2DBuffer it is not stored in a smart 
            pointer when the function returns, it will be leaked by the application.
        @param pD3DTexture D3D11 texture to create the buffer data for. This texture must have been
            created with the D3D11_BIND_RENDER_TARGET bind flag.
        @param pBuffer Ni2DBuffer pointer that will be filled with a new Ni2DBuffer responsible
            for managing the new render target buffer data object. If pBuffer is NULL, then the 
            caller needs to store the result in a smart pointer to prevent a leak. If pBuffer is 
            not NULL, then the contents of pBuffer may be overwritten by this function.
        @param pRTViewDesc Optional pointer to a D3D11_RENDER_TARGET_VIEW_DESC that will be used
            to create an ID3D11RenderTargetView for the render target. If NULL is passed in, then
            a default render target view will be created that references all the subresources of 
            the highest mip level.
        @return The resulting D3D11RenderTargetBufferData.
    */
    static D3D11RenderTargetBufferData* Create(
        ID3D11Texture2D* pD3DTexture,
        Ni2DBuffer*& pBuffer,
        D3D11_RENDER_TARGET_VIEW_DESC* pRTViewDesc = NULL);

    /// Returns the render target view.
    inline ID3D11RenderTargetView* GetRenderTargetView() const;

    /// Returns the render target resource.
    inline ID3D11Texture2D* GetRenderTargetBuffer() const;

protected:
    /// Hidden constructor
    D3D11RenderTargetBufferData();

    ID3D11RenderTargetView* m_pRenderTargetView;
};

//------------------------------------------------------------------------------------------------
/**
    A class to represents a swap chain that can be used for an on-screen window. 
    
    Gamebryo creates instances of this class internally to represent rendered swap chains, 
    but applications can also create instances if they have an IDXGISwapChain that 
    they want to use as a render target.    
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11SwapChainBufferData : public D3D11RenderTargetBufferData
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// Destructor
    virtual ~D3D11SwapChainBufferData();

    /// @cond EMERGENT_INTERNAL

    /// Returns whether the currently derived class is capable or presenting the current render 
    /// target
    virtual efd::Bool CanDisplayFrame();

    /**
        Displays the frame.

        @param syncInterval Number of vertical syncs to wait on before presenting. 0 indicates no
            wait, 1 indicates wait for the next vsync, and so on.
        @param presentTest Indicates whether or not to pass DXGI_PRESENT_TEST to the Present call.
        @return Return value from IDXGISwapChain::Present.
    */
    virtual HRESULT DisplayFrame(
        efd::UInt32 syncInterval,
        efd::Bool presentTest = false);

    /**
        Resizes the swap chain, usually in response to a window resize or resolution change.
        
        @param width The new width.
        @param height The new height.
        @return Whether or not the call to IDXGISwapChain::ResizeBuffers succeeded.
    */

    efd::Bool ResizeSwapChain(efd::UInt32 width, efd::UInt32 height);

    /// @endcond

    /**
        Creates a D3D11SwapChainBufferData for the provided swap chain.

        @note This function requires that a Ni2DBuffer* reference is passed in. Since D3D11 
            requires that you create a swap chain prior to creating the Ni2DBuffer, the Ni2DBuffer 
            and its renderer data are populated by the Create call. Note that if pBuffer is NULL, 
            a new Ni2DBuffer will be created. If this new Ni2DBuffer it is not stored in a smart 
            pointer when the function returns, it will be leaked by the application.
        @param pSwapChain DXGI swap chain to create the buffer data for. 
        @param pBuffer Ni2DBuffer pointer that will be filled with a new Ni2DBuffer responsible
            for managing the new swap chain buffer data. If pBuffer is NULL, then the caller
            needs to store the result in a smart pointer to prevent a leak. If pBuffer is not NULL, 
            then the contents of pBuffer may be overwritten by this function.
        @return The resulting D3D11SwapChainBufferData.
    */
    static D3D11SwapChainBufferData* Create(
        IDXGISwapChain* pSwapChain,
        Ni2DBuffer*& pBuffer);

    /// Returns the swap chain.
    IDXGISwapChain* GetSwapChain() const;

protected:
    /// Hidden constructor
    D3D11SwapChainBufferData();

    IDXGISwapChain* m_pSwapChain;
};

//------------------------------------------------------------------------------------------------
/**
    A class to represents a 2D buffer that can be used as a depth/stencil buffer. 
    
    Gamebryo creates instances of this class internally to represent depth/stencil buffers, 
    but applications can also create instances if they have an ID3D11Texture2D that 
    they want to use as a depth/stencil buffer.    
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11DepthStencilBufferData : public D3D112DBufferData
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    /// Destructor
    virtual ~D3D11DepthStencilBufferData();
    //@}

    /**
        Creates a D3D11DepthStencilBufferData for the provided texture.

        @note This function requires that a Ni2DBuffer* reference is passed in. Since D3D11 
            requires that you create a texture prior to creating the Ni2DBuffer, the Ni2DBuffer 
            and its renderer data are populated by the Create call. Note that if pBuffer is NULL, 
            a new Ni2DBuffer will be created. If this new Ni2DBuffer it is not stored in a smart 
            pointer when the function returns, it will be leaked by the application.
        @param pD3DTexture D3D11 texture to create the buffer data for. This texture must have been
            created with the D3D11_BIND_DEPTH_STENCIL bind flag.
        @param pBuffer Ni2DBuffer pointer that will be filled with a new Ni2DBuffer responsible
            for managing the new depth/stencil buffer data object. If pBuffer is NULL, then the 
            caller needs to store the result in a smart pointer to prevent a leak. If pBuffer is 
            not NULL, then the contents of pBuffer may be overwritten by this function.
        @param pDSViewDesc Optional pointer to a D3D11_DEPTH_STENCIL_VIEW_DESC that will be used
            to create an ID3D11DepthStencilView for the depth/stencil buffer. If NULL is passed in, 
            then a default render target view will be created that references all the subresources
            of the highest mip level.
        @return The resulting D3D11DepthStencilBufferData.
    */
    static D3D11DepthStencilBufferData* Create(
        ID3D11Texture2D* pD3DTexture, 
        NiDepthStencilBuffer*& pBuffer,
        D3D11_DEPTH_STENCIL_VIEW_DESC* pDSViewDesc = NULL);

    /// Returns the depth stencil view.
    ID3D11DepthStencilView* GetDepthStencilView() const;

    /// Returns the depth stencil resource.
    ID3D11Texture2D* GetDepthStencilBuffer() const;

protected:
    /// Hidden constructor
    D3D11DepthStencilBufferData();

    ID3D11DepthStencilView* m_pDepthStencilView;
};

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D112DBufferData.inl>

#endif // EE_D3D112DBUFFERDATA_H
