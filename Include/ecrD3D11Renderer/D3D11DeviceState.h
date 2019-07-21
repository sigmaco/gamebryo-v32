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
#ifndef EE_D3D11DEVICESTATE_H
#define EE_D3D11DEVICESTATE_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>

#include <ecrD3D11Renderer/D3D11Headers.h>
#include <efd/UniversalTypes.h>
#include <efd/MemObject.h>

#include <NiGPUProgram.h>

namespace ecr
{

/**
    Manager responsible for maintaining references to D3D11 state objects that are set on a 
    device context.

    D3D11DeviceState shadows the state on a device context to prevent redundant state changes, 
    and it also ensures that state objects on the device are not unintentionally released 
    while they are still set on the context.

    It is not necessary for applications that want to set state on the device directly to use 
    the D3D11DeviceState, but they may. If they do not, then the application will need to 
    manually ensure that state object are not accidentally released while on the device. 
    In addition, the application may choose to clear the state objects from the 
    D3D11DeviceState for states that the application will set manually so Gamebryo will not
    inadvertantly retain these no-longer-used state objects and prevent them from being be 
    released. If applications do update device state without going through D3D11DeviceState, 
    they may need to call InvalidateDeviceState afterwards in order to let Gamebryo know that 
    the device state that it is maintaining is no longer up to date.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11DeviceState : public efd::MemObject
{
public:
    /// @cond EMERGENT_INTERNAL

    /// @name Construction and Destruction
    //@{
    /**
        The constructor initializes a new ecr::D3D11DeviceState using the D3D11 device context. 
        
        An application should never construct a new device state object, but should 
        obtain a pointer to the D3D11Renderer object's instance instead.
    */
    D3D11DeviceState(
        ID3D11DeviceContext* pDeviceContext, 
        efd::Bool isHSDSSupported, 
        efd::Bool isGSSupported, 
        efd::Bool isCSSupported,
        efd::Bool isCSDownLevel);

    /// Destructor
    virtual ~D3D11DeviceState();
    //@}

    /// @endcond

    /// Render state objects
    //@{
    /// Sets the ID3D11BlendState, blend factor, and sample mask on the D3D11DeviceState and the 
    /// device context.
    void OMSetBlendState(
        ID3D11BlendState* pBlendState,
        const efd::Float32 blendFactor[4], 
        efd::UInt32 sampleMask);
    /// Retrieves the ID3D11BlendState, blend factor, and sample mask currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    void OMGetBlendState(
        ID3D11BlendState** pBlendState,
        efd::Float32 blendFactor[4], 
        efd::UInt32* pSampleMask) const;
    /// Remove the currently set ID3D11BlendState from the D3D11DeviceState and from the 
    /// device context.
    void OMClearBlendState();

    /// Sets the ID3D11DepthStencilState and stencil reference on the D3D11DeviceState and the 
    /// device context.
    void OMSetDepthStencilState(
        ID3D11DepthStencilState* pDepthStencilState,
        efd::UInt32 stencilRef);
    /// Retrieves the ID3D11DepthStencilState and stencil reference currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    void OMGetDepthStencilState(
        ID3D11DepthStencilState** pDepthStencilState,
        efd::UInt32* pStencilRef) const;
    /// Remove the currently set ID3D11DepthStencilState from the D3D11DeviceState and from the 
    /// device context.
    void OMClearDepthStencilState();

    /// Sets the ID3D11RasterizerState on the D3D11DeviceState and the device context.
    void RSSetState(ID3D11RasterizerState* pRasterizerState);
    /// Retrieves the ID3D11RasterizerState currently set on the D3D11DeviceState, which may 
    /// not match the state set on the device context itself.
    void RSGetState(ID3D11RasterizerState** pRasterizerState) const;
    /// Remove the currently set ID3D11RasterizerState from the D3D11DeviceState and from the 
    /// device context.
    void RSClearState();
    //@}

    /// Samplers
    //@{
    /// Sets the vertex shader samplers on the D3D11DeviceState and the device context.
    void VSSetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState*const* pSamplers);
    /// Retrieves the vertex shader samplers currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void VSGetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState** pSamplers) const;
    /// Remove the currently set vertex shader samplers from the D3D11DeviceState and from the 
    /// device context.
    void VSClearSamplers();

    /// Sets the hull shader samplers on the D3D11DeviceState and the device context.
    void HSSetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState*const* pSamplers);
    /// Retrieves the hull shader samplers currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void HSGetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState** pSamplers) const;
    /// Remove the currently set hull shader samplers from the D3D11DeviceState and from the 
    /// device context.
    void HSClearSamplers();

    /// Sets the domain shader samplers on the D3D11DeviceState and the device context.
    void DSSetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState*const* pSamplers);
    /// Retrieves the domain shader samplers currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void DSGetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState** pSamplers) const;
    /// Remove the currently set domain shader samplers from the D3D11DeviceState and from the 
    /// device context.
    void DSClearSamplers();

    /// Sets the geometry shader samplers on the D3D11DeviceState and the device context.
    void GSSetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState*const* pSamplers);
    /// Retrieves the geometry shader samplers currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void GSGetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState** pSamplers) const;
    /// Remove the currently set geometry shader samplers from the D3D11DeviceState and from the 
    /// device context.
    void GSClearSamplers();

    /// Sets the pixel shader samplers on the D3D11DeviceState and the device context.
    void PSSetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState*const* pSamplers);
    /// Retrieves the pixel shader samplers currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void PSGetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState** pSamplers) const;
    /// Remove the currently set pixel shader samplers from the D3D11DeviceState and from the 
    /// device context.
    void PSClearSamplers();

    /// Sets the compute shader samplers on the D3D11DeviceState and the device context.
    void CSSetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState*const* pSamplers);
    /// Retrieves the compute shader samplers currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void CSGetSamplers(
        efd::UInt32 startSlot, 
        efd::UInt32 numSamplers,
        ID3D11SamplerState** pSamplers) const;
    /// Remove the currently set compute shader samplers from the D3D11DeviceState and from the 
    /// device context.
    void CSClearSamplers();
    //@}

    /// Shader resources/textures
    //@{
    /// Sets the vertex shader resources on the D3D11DeviceState and the device context.
    void VSSetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView*const* pResourceViews);
    /// Retrieves the vertex shader resources currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void VSGetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView** pResourceViews) const;
    /// Remove the currently set vertex shader resources from the D3D11DeviceState and from the 
    /// device context.
    void VSClearShaderResources();

    /// Sets the hull shader resources on the D3D11DeviceState and the device context.
    void HSSetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView*const* pResourceViews);
    /// Retrieves the hull shader resources currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void HSGetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView** pResourceViews) const;
    /// Remove the currently set hull shader resources from the D3D11DeviceState and from the 
    /// device context.
    void HSClearShaderResources();

    /// Sets the domain shader resources on the D3D11DeviceState and the device context.
    void DSSetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView*const* pResourceViews);
    /// Retrieves the domain shader resources currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void DSGetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView** pResourceViews) const;
    /// Remove the currently set domain shader resources from the D3D11DeviceState and from the 
    /// device context.
    void DSClearShaderResources();

    /// Sets the geometry shader resources on the D3D11DeviceState and the device context.
    void GSSetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView*const* pResourceViews);
    /// Retrieves the geometry shader resources currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void GSGetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView** pResourceViews) const;
    /// Remove the currently set geometry shader resources from the D3D11DeviceState and from the 
    /// device context.
    void GSClearShaderResources();

    /// Sets the pixel shader resources on the D3D11DeviceState and the device context.
    void PSSetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView*const* pResourceViews);
    /// Retrieves the pixel shader resources currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void PSGetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView** pResourceViews) const;
    /// Remove the currently set pixel shader resources from the D3D11DeviceState and from the 
    /// device context.
    void PSClearShaderResources();

    /// Sets the compute shader resources on the D3D11DeviceState and the device context.
    void CSSetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView*const* pResourceViews);
    /// Retrieves the compute shader resources currently set on the D3D11DeviceState, which may not 
    /// match the state set on the device context itself.
    void CSGetShaderResources(
        efd::UInt32 startSlot,
        efd::UInt32 numViews,
        ID3D11ShaderResourceView** pResourceViews) const;
    /// Remove the currently set compute shader resources from the D3D11DeviceState and from the 
    /// device context.
    void CSClearShaderResources();
    //@}

    /// Shader constant buffers
    //@{
    /// Sets the vertex shader constant buffers on the D3D11DeviceState and the device context.
    void VSSetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer*const* pConstantBuffers);
    /// Retrieves the vertex shader constant buffers currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    void VSGetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer** pConstantBuffers) const;
    /// Remove the currently set vertex shader constant buffers from the D3D11DeviceState and from 
    /// the device context.
    void VSClearConstantBuffers();

    /// Sets the hull shader constant buffers on the D3D11DeviceState and the device context.
    void HSSetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer*const* pConstantBuffers);
    /// Retrieves the hull shader constant buffers currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    void HSGetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer** pConstantBuffers) const;
    /// Remove the currently set hull shader constant buffers from the D3D11DeviceState and from 
    /// the device context.
    void HSClearConstantBuffers();

    /// Sets the domain shader constant buffers on the D3D11DeviceState and the device context.
    void DSSetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer*const* pConstantBuffers);
    /// Retrieves the domain shader constant buffers currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    void DSGetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer** pConstantBuffers) const;
    /// Remove the currently set domain shader constant buffers from the D3D11DeviceState and from 
    /// the device context.
    void DSClearConstantBuffers();

    /// Sets the geometry shader constant buffers on the D3D11DeviceState and the device context.
    void GSSetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer*const* pConstantBuffers);
    /// Retrieves the geometry shader constant buffers currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    void GSGetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer** pConstantBuffers) const;
    /// Remove the currently set geometry shader constant buffers from the D3D11DeviceState and from 
    /// the device context.
    void GSClearConstantBuffers();

    /// Sets the pixel shader constant buffers on the D3D11DeviceState and the device context.
    void PSSetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer*const* pConstantBuffers);
    /// Retrieves the pixel shader constant buffers currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    void PSGetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer** pConstantBuffers) const;
    /// Remove the currently set pixel shader constant buffers from the D3D11DeviceState and from 
    /// the device context.
    void PSClearConstantBuffers();

    /// Sets the compute shader constant buffers on the D3D11DeviceState and the device context.
    void CSSetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer*const* pConstantBuffers);
    /// Retrieves the compute shader constant buffers currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    void CSGetConstantBuffers(
        efd::UInt32 startSlot,
        efd::UInt32 numBuffers, 
        ID3D11Buffer** pConstantBuffers) const;
    /// Remove the currently set compute shader constant buffers from the D3D11DeviceState and from 
    /// the device context.
    void CSClearConstantBuffers();
    //@}

    /// Shader programs
    //@{
    /// Sets the vertex shader program on the D3D11DeviceState and the device context.
    void VSSetShader(
        ID3D11VertexShader* pVertexShader,
        ID3D11ClassInstance*const* pClassInstances = NULL,
        efd::UInt32 numClassInstances = 0);
    /// Retrieves the vertex shader program and ID3D11ClassInstance array currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline void VSGetShader(
        ID3D11VertexShader** pVertexShader,
        ID3D11ClassInstance** pClassInstances,
        efd::UInt32* pNumClassInstances) const;
    /// Retrieves the vertex shader program currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    inline ID3D11VertexShader* VSGetShader() const;
    /// Retrieve the array of vertex shader ID3D11ClassInstance objects currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline ID3D11ClassInstance*const* VSGetShaderClassInstances() const;
    /// Retrieve the number of entries in the vertex shader ID3D11ClassInstance array currently set 
    /// on the D3D11DeviceState, which may not match the state set on the device context itself.
    inline efd::UInt32 VSGetShaderClassInstanceCount() const;
    /// Remove the currently set vertex shader and ID3D11ClassInstance array from the 
    /// D3D11DeviceState and from the device context.
    void VSClearShader();

    /// Sets the hull shader program on the D3D11DeviceState and the device context.
    void HSSetShader(
        ID3D11HullShader* pPixelShader,
        ID3D11ClassInstance*const* pClassInstances = NULL,
        efd::UInt32 numClassInstances = 0);
    /// Retrieves the hull shader program and ID3D11ClassInstance array currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline void HSGetShader(
        ID3D11HullShader** pPixelShader,
        ID3D11ClassInstance** pClassInstances,
        efd::UInt32* pNumClassInstances) const;
    /// Retrieves the hull shader program currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    inline ID3D11HullShader* HSGetShader() const;
    /// Retrieve the array of hull shader ID3D11ClassInstance objects currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline ID3D11ClassInstance*const* HSGetShaderClassInstances() const;
    /// Retrieve the number of entries in the hull shader ID3D11ClassInstance array currently set 
    /// on the D3D11DeviceState, which may not match the state set on the device context itself.
    inline efd::UInt32 HSGetShaderClassInstanceCount() const;
    /// Remove the currently set hull shader and ID3D11ClassInstance array from the 
    /// D3D11DeviceState and from the device context.
    void HSClearShader();

    /// Sets the domain shader program on the D3D11DeviceState and the device context.
    void DSSetShader(
        ID3D11DomainShader* pPixelShader,
        ID3D11ClassInstance*const* pClassInstances = NULL,
        efd::UInt32 numClassInstances = 0);
    /// Retrieves the domain shader program and ID3D11ClassInstance array currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline void DSGetShader(
        ID3D11DomainShader** pPixelShader,
        ID3D11ClassInstance** pClassInstances,
        efd::UInt32* pNumClassInstances) const;
    /// Retrieves the domain shader program currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    inline ID3D11DomainShader* DSGetShader() const;
    /// Retrieve the array of domain shader ID3D11ClassInstance objects currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline ID3D11ClassInstance*const* DSGetShaderClassInstances() const;
    /// Retrieve the number of entries in the domain shader ID3D11ClassInstance array currently set 
    /// on the D3D11DeviceState, which may not match the state set on the device context itself.
    inline efd::UInt32 DSGetShaderClassInstanceCount() const;
    /// Remove the currently set domain shader and ID3D11ClassInstance array from the 
    /// D3D11DeviceState and from the device context.
    void DSClearShader();

    /// Sets the geometry shader program on the D3D11DeviceState and the device context.
    void GSSetShader(
        ID3D11GeometryShader* pGeometryShader,
        ID3D11ClassInstance*const* pClassInstances = NULL,
        efd::UInt32 numClassInstances = 0);
    /// Retrieves the geometry shader program and ID3D11ClassInstance array currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline void GSGetShader(
        ID3D11GeometryShader** pGeometryShader,
        ID3D11ClassInstance** pClassInstances,
        efd::UInt32* pNumClassInstances) const;
    /// Retrieves the geometry shader program currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    inline ID3D11GeometryShader* GSGetShader() const;
    /// Retrieve the array of geometry shader ID3D11ClassInstance objects currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline ID3D11ClassInstance*const* GSGetShaderClassInstances() const;
    /// Retrieve the number of entries in the geometry shader ID3D11ClassInstance array currently 
    /// set on the D3D11DeviceState, which may not match the state set on the device context itself.
    inline efd::UInt32 GSGetShaderClassInstanceCount() const;
    /// Remove the currently set geometry shader and ID3D11ClassInstance array from the 
    /// D3D11DeviceState and from the device context.
    void GSClearShader();

    /// Sets the pixel shader program on the D3D11DeviceState and the device context.
    void PSSetShader(
        ID3D11PixelShader* pPixelShader,
        ID3D11ClassInstance*const* pClassInstances = NULL,
        efd::UInt32 numClassInstances = 0);
    /// Retrieves the pixel shader program and ID3D11ClassInstance array currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline void PSGetShader(
        ID3D11PixelShader** pPixelShader,
        ID3D11ClassInstance** pClassInstances,
        efd::UInt32* pNumClassInstances) const;
    /// Retrieves the pixel shader program currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    inline ID3D11PixelShader* PSGetShader() const;
    /// Retrieve the array of pixel shader ID3D11ClassInstance objects currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline ID3D11ClassInstance*const* PSGetShaderClassInstances() const;
    /// Retrieve the number of entries in the pixel shader ID3D11ClassInstance array currently set 
    /// on the D3D11DeviceState, which may not match the state set on the device context itself.
    inline efd::UInt32 PSGetShaderClassInstanceCount() const;
    /// Remove the currently set pixel shader and ID3D11ClassInstance array from the 
    /// D3D11DeviceState and from the device context.
    void PSClearShader();

    /// Sets the compute shader program on the D3D11DeviceState and the device context.
    void CSSetShader(
        ID3D11ComputeShader* pPixelShader,
        ID3D11ClassInstance*const* pClassInstances = NULL,
        efd::UInt32 numClassInstances = 0);
    /// Retrieves the compute shader program and ID3D11ClassInstance array currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline void CSGetShader(
        ID3D11ComputeShader** pPixelShader,
        ID3D11ClassInstance** pClassInstances,
        efd::UInt32* pNumClassInstances) const;
    /// Retrieves the compute shader program currently set on the D3D11DeviceState, which 
    /// may not match the state set on the device context itself.
    inline ID3D11ComputeShader* CSGetShader() const;
    /// Retrieve the array of compute shader ID3D11ClassInstance objects currently set on the 
    /// D3D11DeviceState, which may not match the state set on the device context itself.
    inline ID3D11ClassInstance*const* CSGetShaderClassInstances() const;
    /// Retrieve the number of entries in the compute shader ID3D11ClassInstance array currently set 
    /// on the D3D11DeviceState, which may not match the state set on the device context itself.
    inline efd::UInt32 CSGetShaderClassInstanceCount() const;
    /// Remove the currently set compute shader and ID3D11ClassInstance array from the 
    /// D3D11DeviceState and from the device context.
    void CSClearShader();

    /// Sets the compute shader unordered access views on the D3D11DeviceState and the 
    /// device context.
    void CSSetUnorderedAccessViews(
        efd::UInt32 startSlot,
        efd::UInt32 numUAVs, 
        ID3D11UnorderedAccessView*const* pUAVs,
        const efd::UInt32* pUAVInitialCounts);
    /// Retrieves the compute shader unordered access views currently set on the D3D11DeviceState, 
    /// which may not match the state set on the device context itself.
    void CSGetUnorderedAccessViews(
        efd::UInt32 startSlot,
        efd::UInt32 numUAVs, 
        ID3D11UnorderedAccessView** pUAVs) const;
    /// Remove the currently set compute shader unordered access views from the D3D11DeviceState 
    /// and from the device context.
    void CSClearUnorderedAccessViews();

    /// Invalidate the entire device state stored on the D3D11DeviceState. This may cause resources
    /// set on the device context to be released, if the D3D11DeviceState kept the only reference.
    void InvalidateDeviceState();

protected:
    ID3D11DeviceContext* m_pDeviceContext;

    ID3D11BlendState* m_pBlendState;
    ID3D11DepthStencilState* m_pDepthStencilState;
    ID3D11RasterizerState* m_pRasterizerState;
    ID3D11SamplerState* m_samplerArray[NiGPUProgram::PROGRAM_MAX]
        [D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];

    efd::Float32 m_blendFactor[4];
    efd::UInt32 m_sampleMask;
    efd::UInt32 m_stencilRef;

    ID3D11ShaderResourceView* m_resourceArray[NiGPUProgram::PROGRAM_MAX]
        [D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];

    ID3D11Buffer* m_bufferArray[NiGPUProgram::PROGRAM_MAX]
        [D3D11_COMMONSHADER_CONSTANT_BUFFER_REGISTER_COUNT];

    ID3D11ClassInstance* m_classInstanceArray[NiGPUProgram::PROGRAM_MAX]
        [D3D11_SHADER_MAX_INTERFACES];

    ID3D11UnorderedAccessView* m_csUnorderedAccessViews[D3D11_PS_CS_UAV_REGISTER_COUNT];

    efd::UInt32 m_classInstanceCount[NiGPUProgram::PROGRAM_MAX];

    ID3D11VertexShader* m_pVertexShader;
    ID3D11HullShader* m_pHullShader;
    ID3D11DomainShader* m_pDomainShader;
    ID3D11GeometryShader* m_pGeometryShader;
    ID3D11PixelShader* m_pPixelShader;
    ID3D11ComputeShader* m_pComputeShader;

    efd::Bool m_blendStateUnchanged;
    efd::Bool m_depthStencilStateUnchanged;

    const efd::Bool m_isHSDSSupported;
    const efd::Bool m_isGSSupported;
    const efd::Bool m_isCSSupported;
    const efd::Bool m_isCSDownLevel;

private:
    /// Assignment operator to fix a build warning - do not use.
    D3D11DeviceState& operator= (const D3D11DeviceState& other);
};

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11DeviceState.inl>

#endif // EE_D3D11DEVICESTATE_H
