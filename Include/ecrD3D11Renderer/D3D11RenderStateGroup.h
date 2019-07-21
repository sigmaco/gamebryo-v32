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
#ifndef EE_D3D11RENDERSTATEGROUP_H
#define EE_D3D11RENDERSTATEGROUP_H

#include <ecrD3D11Renderer/D3D11ShaderProgram.h>
#include <ecrD3D11Renderer/D3D11Headers.h>
#include <ecrD3D11Renderer/D3D11Renderer.h>

#include <NiRefObject.h>
#include <NiGPUProgram.h>

namespace ecr
{

/**
    ecr::D3D11RenderStateGroup stores and accumulate render states for a render pass.

    ecr::D3D11RenderStateGroup is a class that collects render state values that will be used 
    to create the ID3D11BlendState, ID3D11DepthStencilState, ID3D11RasterizerState, and 
    ID3D11SamplerState objects. The D3D11RenderStateGroup allows a shader or application to 
    accumulate render states individually before passing them to the D3D11RenderStateManager to 
    be turned into D3D11 state objects. Refer to Render State Management in D3D11 for further 
    discussion of how to handle render states.    
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11RenderStateGroup : public NiRefObject
{
public:
    /// @name Construction and Destruction
    //@{
    /// Constructor
    D3D11RenderStateGroup();
    /// Destructor
    virtual ~D3D11RenderStateGroup();
    //@}

    /// Set BlendState AlphaToCoverage render state in the render state group.
    void SetBSAlphaToCoverageEnable(efd::Bool alphaToCoverageEnable);
    /// Output the BlendState AlphaToCoverage render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetBSAlphaToCoverageEnable(efd::Bool& alphaToCoverageEnable) const;
    /// Remove the BlendState AlphaToCoverage render state from the render state group.
    void RemoveBSAlphaToCoverageEnable();

    /// Set BlendState IndependentBlendEnable render state in the render state group.
    void SetBSIndependentBlendEnable(efd::Bool independentBlendEnable);
    /// Output the BlendState IndependentBlendEnable render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetBSIndependentBlendEnable(efd::Bool& independentBlendEnable) const;
    /// Remove the BlendState IndependentBlendEnable render state from the render state group.
    void RemoveBSIndependentBlendEnable();

    /// Set BlendState BlendEnable render state for the given render target in the render 
    /// state group.
    void SetBSBlendEnable(efd::UInt32 renderTarget, efd::Bool blendEnable);
    /// Output the BlendState BlendEnable render state for the given render target in the 
    /// render state group, and return whether or not that render state has actually been set in 
    /// the render state group.
    efd::Bool GetBSBlendEnable(efd::UInt32 renderTarget, efd::Bool& blendEnable) const;
    /// Remove the BlendState BlendEnable render state for the given render target from the
    /// render state group.
    void RemoveBSBlendEnable(efd::UInt32 renderTarget);

    /// Set BlendState SrcBlend render state for the given render target in the render 
    /// state group.
    void SetBSSrcBlend(efd::UInt32 renderTarget, D3D11_BLEND blend);
    /// Output the BlendState SrcBlend render state for the given render target in the 
    /// render state group, and return whether or not that render state has actually been set in 
    /// the render state group.
    efd::Bool GetBSSrcBlend(efd::UInt32 renderTarget, D3D11_BLEND& blend) const;
    /// Remove the BlendState SrcBlend render state for the given render target from the
    /// render state group.
    void RemoveBSSrcBlend(efd::UInt32 renderTarget);

    /// Set BlendState DestBlend render state for the given render target in the render 
    /// state group.
    void SetBSDestBlend(efd::UInt32 renderTarget, D3D11_BLEND blend);
    /// Output the BlendState DestBlend render state for the given render target in the 
    /// render state group, and return whether or not that render state has actually been set in 
    /// the render state group.
    efd::Bool GetBSDestBlend(efd::UInt32 renderTarget, D3D11_BLEND& blend) const;
    /// Remove the BlendState DestBlend render state for the given render target from the
    /// render state group.
    void RemoveBSDestBlend(efd::UInt32 renderTarget);

    /// Set BlendState BlendOp render state for the given render target in the render 
    /// state group.
    void SetBSBlendOp(efd::UInt32 renderTarget, D3D11_BLEND_OP blendOp);
    /// Output the BlendState BlendOp render state for the given render target in the 
    /// render state group, and return whether or not that render state has actually been set in 
    /// the render state group.
    efd::Bool GetBSBlendOp(efd::UInt32 renderTarget, D3D11_BLEND_OP& blendOp) const;
    /// Remove the BlendState BlendOp render state for the given render target from the
    /// render state group.
    void RemoveBSBlendOp(efd::UInt32 renderTarget);

    /// Set BlendState SrcBlendAlpha render state for the given render target in the render 
    /// state group.
    void SetBSSrcBlendAlpha(efd::UInt32 renderTarget, D3D11_BLEND blend);
    /// Output the BlendState SrcBlendAlpha render state for the given render target in the 
    /// render state group, and return whether or not that render state has actually been set in 
    /// the render state group.
    efd::Bool GetBSSrcBlendAlpha(efd::UInt32 renderTarget, D3D11_BLEND& blend) const;
    /// Remove the BlendState SrcBlendAlpha render state for the given render target from the
    /// render state group.
    void RemoveBSSrcBlendAlpha(efd::UInt32 renderTarget);

    /// Set BlendState DestBlendAlpha render state for the given render target in the render 
    /// state group.
    void SetBSDestBlendAlpha(efd::UInt32 renderTarget, D3D11_BLEND blend);
    /// Output the BlendState DestBlendAlpha render state for the given render target in the 
    /// render state group, and return whether or not that render state has actually been set in 
    /// the render state group.
    efd::Bool GetBSDestBlendAlpha(efd::UInt32 renderTarget, D3D11_BLEND& blend) const;
    /// Remove the BlendState DestBlendAlpha render state for the given render target from the
    /// render state group.
    void RemoveBSDestBlendAlpha(efd::UInt32 renderTarget);

    /// Set BlendState BlendOpAlpha render state for the given render target in the render 
    /// state group.
    void SetBSBlendOpAlpha(efd::UInt32 renderTarget, D3D11_BLEND_OP blendOp);
    /// Output the BlendState BlendOpAlpha render state for the given render target in the 
    /// render state group, and return whether or not that render state has actually been set in 
    /// the render state group.
    efd::Bool GetBSBlendOpAlpha(efd::UInt32 renderTarget, D3D11_BLEND_OP& blendOp) const;
    /// Remove the BlendState BlendOpAlpha render state for the given render target from the
    /// render state group.
    void RemoveBSBlendOpAlpha(efd::UInt32 renderTarget);

    /// Set BlendState RenderTargetWriteMask render state for the given render target in the render 
    /// state group.
    void SetBSRenderTargetWriteMask(efd::UInt32 renderTarget, efd::UInt8 writeMask);
    /// Output the BlendState RenderTargetWriteMask render state for the given render target in the 
    /// render state group, and return whether or not that render state has actually been set in 
    /// the render state group.
    efd::Bool GetBSRenderTargetWriteMask(efd::UInt32 renderTarget, efd::UInt8& writeMask) const;
    /// Remove the BlendState RenderTargetWriteMask render state for the given render target from
    /// the render state group.
    void RemoveBSRenderTargetWriteMask(efd::UInt32 renderTarget);

    /// Set Blend Factor render state in the render state group.
    void SetBlendFactor(const efd::Float32 blendFactor[4]);
    /// Output the Blend Factor render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetBlendFactor(efd::Float32 blendFactor[4]) const;
    /// Remove the Blend Factor render state from the render state group.
    void RemoveBlendFactor();

    /// Set Sample Mask render state in the render state group.
    void SetSampleMask(efd::UInt32 sampleMask);
    /// Output the Sample Mask render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetSampleMask(efd::UInt32& sampleMask) const;
    /// Remove the Sample Mask render state from the render state group.
    void RemoveSampleMask();

    /// Set DepthStencilState DepthEnable render state in the render state group.
    void SetDSSDepthEnable(efd::Bool depthEnable);
    /// Output the DepthStencilState DepthEnable render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetDSSDepthEnable(efd::Bool& depthEnable) const;
    /// Remove the DepthStencilState DepthEnable render state from the render state group.
    void RemoveDSSDepthEnable();

    /// Set DepthStencilState DepthWriteMask render state in the render state group.
    void SetDSSDepthWriteMask(D3D11_DEPTH_WRITE_MASK depthWriteMask);
    /// Output the DepthStencilState DepthWriteMask render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetDSSDepthWriteMask(D3D11_DEPTH_WRITE_MASK& depthWriteMask) const;
    /// Remove the DepthStencilState DepthWriteMask render state from the render state group.
    void RemoveDSSDepthWriteMask();

    /// Set DepthStencilState DepthFunc render state in the render state group.
    void SetDSSDepthFunc(D3D11_COMPARISON_FUNC depthFunc);
    /// Output the DepthStencilState DepthFunc render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetDSSDepthFunc(D3D11_COMPARISON_FUNC& depthFunc) const;
    /// Remove the DepthStencilState DepthFunc render state from the render state group.
    void RemoveDSSDepthFunc();

    /// Set DepthStencilState StencilEnable render state in the render state group.
    void SetDSSStencilEnable(efd::Bool stencilEnable);
    /// Output the DepthStencilState StencilEnable render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetDSSStencilEnable(efd::Bool& stencilEnable) const;
    /// Remove the DepthStencilState StencilEnable render state from the render state group.
    void RemoveDSSStencilEnable();

    /// Set DepthStencilState StencilReadMask render state in the render state group.
    void SetDSSStencilReadMask(efd::UInt8 stencilReadMask);
    /// Output the DepthStencilState StencilReadMask render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetDSSStencilReadMask(efd::UInt8& stencilReadMask) const;
    /// Remove the DepthStencilState StencilReadMask render state from the render state group.
    void RemoveDSSStencilReadMask();

    /// Set DepthStencilState StencilWriteMask render state in the render state group.
    void SetDSSStencilWriteMask(efd::UInt8 stencilWriteMask);
    /// Output the DepthStencilState StencilWriteMask render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetDSSStencilWriteMask(efd::UInt8& stencilWriteMask) const;
    /// Remove the DepthStencilState StencilWriteMask render state from the render state group.
    void RemoveDSSStencilWriteMask();

    /// Set DepthStencilState StencilFailOp render state for front-facing triangles in the 
    /// render state group.
    void SetDSSFrontFaceStencilFailOp(D3D11_STENCIL_OP stencilOp);
    /// Output the DepthStencilState StencilFailOp render state for front-facing triangles in the 
    /// render state group, and return whether or not that render state has actually been set in 
    /// the render state group.
    efd::Bool GetDSSFrontFaceStencilFailOp(D3D11_STENCIL_OP& stencilOp) const;
    /// Remove the DepthStencilState StencilFailOp render state for front-facing triangles from the 
    /// render state group.
    void RemoveDSSFrontFaceStencilFailOp();

    /// Set DepthStencilState StencilDepthFailOp render state for front-facing triangles in the 
    /// render state group.
    void SetDSSFrontFaceStencilDepthFailOp(D3D11_STENCIL_OP stencilOp);
    /// Output the DepthStencilState StencilDepthFailOp render state for front-facing triangles in 
    /// the render state group, and return whether or not that render state has actually been set 
    /// in the render state group.
    efd::Bool GetDSSFrontFaceStencilDepthFailOp(D3D11_STENCIL_OP& stencilOp) const;
    /// Remove the DepthStencilState StencilDepthFailOp render state for front-facing triangles 
    /// from the render state group.
    void RemoveDSSFrontFaceStencilDepthFailOp();

    /// Set DepthStencilState StencilPassOp render state for front-facing triangles in the 
    /// render state group.
    void SetDSSFrontFaceStencilPassOp(D3D11_STENCIL_OP stencilOp);
    /// Output the DepthStencilState StencilPassOp render state for front-facing triangles in 
    /// the render state group, and return whether or not that render state has actually been set 
    /// in the render state group.
    efd::Bool GetDSSFrontFaceStencilPassOp(D3D11_STENCIL_OP& stencilOp) const;
    /// Remove the DepthStencilState StencilPassOp render state for front-facing triangles 
    /// from the render state group.
    void RemoveDSSFrontFaceStencilPassOp();

    /// Set DepthStencilState StencilFunc render state for front-facing triangles in the 
    /// render state group.
    void SetDSSFrontFaceStencilFunc(D3D11_COMPARISON_FUNC eStencilFunc);
    /// Output the DepthStencilState StencilFunc render state for front-facing triangles in 
    /// the render state group, and return whether or not that render state has actually been set 
    /// in the render state group.
    efd::Bool GetDSSFrontFaceStencilFunc(D3D11_COMPARISON_FUNC& eStencilFunc) const;
    /// Remove the DepthStencilState StencilFunc render state for front-facing triangles 
    /// from the render state group.
    void RemoveDSSFrontFaceStencilFunc();

    /// Set DepthStencilState StencilFailOp render state for back-facing triangles in the 
    /// render state group.
    void SetDSSBackFaceStencilFailOp(D3D11_STENCIL_OP stencilOp);
    /// Output the DepthStencilState StencilFailOp render state for back-facing triangles in 
    /// the render state group, and return whether or not that render state has actually been set 
    /// in the render state group.
    efd::Bool GetDSSBackFaceStencilFailOp(D3D11_STENCIL_OP& stencilOp) const;
    /// Remove the DepthStencilState StencilFailOp render state for back-facing triangles 
    /// from the render state group.
    void RemoveDSSBackFaceStencilFailOp();

    /// Set DepthStencilState eStencilDepthFailOp render state for back-facing triangles in the 
    /// render state group.
    void SetDSSBackFaceStencilDepthFailOp(D3D11_STENCIL_OP stencilOp);
    /// Output the DepthStencilState eStencilDepthFailOp render state for back-facing triangles in 
    /// the render state group, and return whether or not that render state has actually been set 
    /// in the render state group.
    efd::Bool GetDSSBackFaceStencilDepthFailOp(D3D11_STENCIL_OP& stencilOp) const;
    /// Remove the DepthStencilState eStencilDepthFailOp render state for back-facing triangles 
    /// from the render state group.
    void RemoveDSSBackFaceStencilDepthFailOp();

    /// Set DepthStencilState StencilPassOp render state for back-facing triangles in the 
    /// render state group.
    void SetDSSBackFaceStencilPassOp(D3D11_STENCIL_OP stencilOp);
    /// Output the DepthStencilState StencilPassOp render state for back-facing triangles in 
    /// the render state group, and return whether or not that render state has actually been set 
    /// in the render state group.
    efd::Bool GetDSSBackFaceStencilPassOp(D3D11_STENCIL_OP& stencilOp) const;
    /// Remove the DepthStencilState StencilPassOp render state for back-facing triangles 
    /// from the render state group.
    void RemoveDSSBackFaceStencilPassOp();

    /// Set DepthStencilState StencilFunc render state for back-facing triangles in the 
    /// render state group.
    void SetDSSBackFaceStencilFunc(D3D11_COMPARISON_FUNC eStencilFunc);
    /// Output the DepthStencilState StencilFunc render state for back-facing triangles in 
    /// the render state group, and return whether or not that render state has actually been set 
    /// in the render state group.
    efd::Bool GetDSSBackFaceStencilFunc(D3D11_COMPARISON_FUNC& eStencilFunc) const;
    /// Remove the DepthStencilState StencilFunc render state for back-facing triangles 
    /// from the render state group.
    void RemoveDSSBackFaceStencilFunc();

    /// Set Stencil Ref render state in the render state group.
    void SetStencilRef(efd::UInt32 stencilRef);
    /// Output the Stencil Ref render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetStencilRef(efd::UInt32& stencilRef) const;
    /// Remove the Stencil Ref render state from the render state group.
    void RemoveStencilRef();

    /// Set RasterizerState FillMode render state in the render state group.
    void SetRSFillMode(D3D11_FILL_MODE fillMode);
    /// Output the RasterizerState FillMode render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetRSFillMode(D3D11_FILL_MODE& fillMode) const;
    /// Remove the RasterizerState FillMode render state from the render state group.
    void RemoveRSFillMode();

    /// Set RasterizerState CullMode render state in the render state group.
    void SetRSCullMode(D3D11_CULL_MODE cullMode);
    /// Output the RasterizerState CullMode render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetRSCullMode(D3D11_CULL_MODE& cullMode) const;
    /// Remove the RasterizerState CullMode render state from the render state group.
    void RemoveRSCullMode();

    /// Set RasterizerState FrontCounterClockwise render state in the render state group.
    void SetRSFrontCounterClockwise(efd::Bool frontCounterClockwise);
    /// Output the RasterizerState FrontCounterClockwise render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetRSFrontCounterClockwise(efd::Bool& frontCounterClockwise) const;
    /// Remove the RasterizerState FrontCounterClockwise render state from the render state group.
    void RemoveRSFrontCounterClockwise();

    /// Set RasterizerState DepthBias render state in the render state group.
    void SetRSDepthBias(efd::SInt32 depthBias);
    /// Output the RasterizerState DepthBias render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetRSDepthBias(efd::SInt32& depthBias) const;
    /// Remove the RasterizerState DepthBias render state from the render state group.
    void RemoveRSDepthBias();

    /// Set RasterizerState DepthBiasClamp render state in the render state group.
    void SetRSDepthBiasClamp(efd::Float32 depthBiasClamp);
    /// Output the RasterizerState DepthBiasClamp render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetRSDepthBiasClamp(efd::Float32& depthBiasClamp) const;
    /// Remove the RasterizerState DepthBiasClamp render state from the render state group.
    void RemoveRSDepthBiasClamp();

    /// Set RasterizerState SlopeScaledDepthBias render state in the render state group.
    void SetRSSlopeScaledDepthBias(efd::Float32 slopeScaledDepthBias);
    /// Output the RasterizerState SlopeScaledDepthBias render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetRSSlopeScaledDepthBias(efd::Float32& slopeScaledDepthBias) const;
    /// Remove the RasterizerState SlopeScaledDepthBias render state from the render state group.
    void RemoveRSSlopeScaledDepthBias();

    /// Set RasterizerState DepthClipEnable render state in the render state group.
    void SetRSDepthClipEnable(efd::Bool depthClipEnable);
    /// Output the RasterizerState DepthClipEnable render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetRSDepthClipEnable(efd::Bool& depthClipEnable) const;
    /// Remove the RasterizerState DepthClipEnable render state from the render state group.
    void RemoveRSDepthClipEnable();

    /// Set RasterizerState ScissorEnable render state in the render state group.
    void SetRSScissorEnable(efd::Bool scissorEnable);
    /// Output the RasterizerState ScissorEnable render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetRSScissorEnable(efd::Bool& scissorEnable) const;
    /// Remove the RasterizerState ScissorEnable render state from the render state group.
    void RemoveRSScissorEnable();

    /// Set RasterizerState MultisampleEnable render state in the render state group.
    void SetRSMultisampleEnable(efd::Bool multisampleEnable);
    /// Output the RasterizerState MultisampleEnable render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetRSMultisampleEnable(efd::Bool& multisampleEnable) const;
    /// Remove the RasterizerState MultisampleEnable render state from the render state group.
    void RemoveRSMultisampleEnable();

    /// Set RasterizerState AntialiasedLineEnable render state in the render state group.
    void SetRSAntialiasedLineEnable(efd::Bool antialiasedLineEnable);
    /// Output the RasterizerState AntialiasedLineEnable render state in the render state group,
    /// and return whether or not that render state has actually been set in the render state group.
    efd::Bool GetRSAntialiasedLineEnable(efd::Bool& antialiasedLineEnable) const;
    /// Remove the RasterizerState AntialiasedLineEnable render state from the render state group.
    void RemoveRSAntialiasedLineEnable();

    /**
        Class that stores and accumulates render states for a sampler.

        Sampler render states are stored in individual Sampler objects rather than directly
        in the D3D11RenderStateGroup because shaders reference samplers by name, rather than
        by number. It is much more useful and efficient to accumulate the state for a named
        sampler than by which shader type and index that sampler will use.

        New samplers should only be constructed using D3D11RenderStateGroup::AddSampler.
    */
    class EE_ECRD3D11RENDERER_ENTRY Sampler : public efd::MemObject
    {
    public:
        /// Get the variable name of the sampler.
        inline const efd::FixedString& GetName() const;

        /// Set Sampler Filter state in the sampler.
        void SetFilter(D3D11_FILTER filter);
        /// Output the Sampler Filter state in the sampler,
        /// and return whether or not that state has actually been set in the sampler.
        efd::Bool GetFilter(D3D11_FILTER& filter) const;
        /// Remove the Sampler Filter state from the sampler.
        void RemoveFilter();

        /// Set Sampler AddressU state in the sampler.
        void SetAddressU(D3D11_TEXTURE_ADDRESS_MODE addressU);
        /// Output the Sampler AddressU state in the sampler,
        /// and return whether or not that state has actually been set in the sampler.
        efd::Bool GetAddressU(D3D11_TEXTURE_ADDRESS_MODE& addressU) const;
        /// Remove the Sampler AddressU state from the sampler.
        void RemoveAddressU();

        /// Set Sampler AddressV state in the sampler.
        void SetAddressV(D3D11_TEXTURE_ADDRESS_MODE addressV);
        /// Output the Sampler AddressV state in the sampler,
        /// and return whether or not that state has actually been set in the sampler.
        efd::Bool GetAddressV(D3D11_TEXTURE_ADDRESS_MODE& addressV) const;
        /// Remove the Sampler AddressV state from the sampler.
        void RemoveAddressV();

        /// Set Sampler AddressW state in the sampler.
        void SetAddressW(D3D11_TEXTURE_ADDRESS_MODE addressW);
        /// Output the Sampler AddressW state in the sampler,
        /// and return whether or not that state has actually been set in the sampler.
        efd::Bool GetAddressW(D3D11_TEXTURE_ADDRESS_MODE& addressW) const;
        /// Remove the Sampler AddressW state from the sampler.
        void RemoveAddressW();

        /// Set Sampler MipLODBias state in the sampler.
        void SetMipLODBias(efd::Float32 mipLODBias);
        /// Output the Sampler MipLODBias state in the sampler,
        /// and return whether or not that state has actually been set in the sampler.
        efd::Bool GetMipLODBias(efd::Float32& mipLODBias) const;
        /// Remove the Sampler MipLODBias state from the sampler.
        void RemoveMipLODBias();

        /// Set Sampler MaxAnisotropy state in the sampler.
        void SetMaxAnisotropy(efd::UInt32 maxAnisotropy);
        /// Output the Sampler MaxAnisotropy state in the sampler,
        /// and return whether or not that state has actually been set in the sampler.
        efd::Bool GetMaxAnisotropy(efd::UInt32& maxAnisotropy) const;
        /// Remove the Sampler MaxAnisotropy state from the sampler.
        void RemoveMaxAnisotropy();

        /// Set Sampler ComparisonFunc state in the sampler.
        void SetComparisonFunc(D3D11_COMPARISON_FUNC comparisonFunc);
        /// Output the Sampler ComparisonFunc state in the sampler,
        /// and return whether or not that state has actually been set in the sampler.
        efd::Bool GetComparisonFunc(D3D11_COMPARISON_FUNC& comparisonFunc) const;
        /// Remove the Sampler ComparisonFunc state from the sampler.
        void RemoveComparisonFunc();

        /// Set Sampler BorderColor state in the sampler.
        void SetBorderColor(const efd::Float32 borderColor[4]);
        /// Output the Sampler BorderColor state in the sampler,
        /// and return whether or not that state has actually been set in the sampler.
        efd::Bool GetBorderColor(efd::Float32 borderColor[4]) const;
        /// Remove the Sampler BorderColor state from the sampler.
        void RemoveBorderColor();

        /// Set Sampler MinLOD state in the sampler.
        void SetMinLOD(efd::Float32 minLOD);
        /// Output the Sampler MinLOD state in the sampler,
        /// and return whether or not that state has actually been set in the sampler.
        efd::Bool GetMinLOD(efd::Float32& minLOD) const;
        /// Remove the Sampler MinLOD state from the sampler.
        void RemoveMinLOD();

        /// Set Sampler MaxLOD state in the sampler.
        void SetMaxLOD(efd::Float32 maxLOD);
        /// Output the Sampler MaxLOD state in the sampler,
        /// and return whether or not that state has actually been set in the sampler.
        efd::Bool GetMaxLOD(efd::Float32& maxLOD) const;
        /// Remove the Sampler MaxLOD state from the sampler.
        void RemoveMaxLOD();

        /// Return the accumulated D3D11_SAMPLER_DESC for this sampler.
        inline const D3D11_SAMPLER_DESC& GetSamplerDesc() const;
        /// Return a set of flags from D3D11RenderStateManager::SamplerValidFlags indicating which 
        /// states were actually set on this sampler.
        inline efd::UInt32 GetSamplerValidFlags() const;

    protected:
        /// Hidden constructor.
        Sampler(efd::FixedString samplerName);
        /// Destructor.
        virtual ~Sampler();

        D3D11_SAMPLER_DESC m_samplerDesc;
        efd::FixedString m_samplerName;

        efd::UInt32 m_samplerValidFlags;

        Sampler* m_pNext;

        friend class D3D11RenderStateGroup;
    };

    /// Add a new Sampler object with the given name to track sampler states.
    Sampler* AddSampler(const efd::FixedString& samplerName);
    /// Return the Sampler object with the given name, or NULL if one does not exist.
    Sampler* GetSampler(const efd::FixedString& samplerName) const;
    /// Remove the Sampler object with the given name, and return whether or not a match was found
    /// on the render state group.
    efd::Bool RemoveSampler(const efd::FixedString& samplerName);
    /// Remove the given Sampler object, and return whether or not a match was found on the render 
    /// state group.
    efd::Bool RemoveSampler(Sampler* pSampler);

    /// Return the first Sampler object on the render state group.
    inline const Sampler* GetFirstSampler() const;
    /// Return the next Sampler object on the render state group.
    inline const Sampler* GetNextSampler(const Sampler* pSampler) const;

    /**
        Set a blend state desc on a render state group at once, rather than through individual
        states.

        The data in the provided blend state desc and valid flags will overwrite the data 
        currently stored in the render state group.

        @param blendDesc The blend state desc to set.
        @param validFlags The set of flags from D3D11RenderStateManager::BlendStateValidFlags that
            indicate which states in the blend state desc are valid.
        @param renderTargetValidFlags An array of flags from  
            D3D11RenderStateManager::BlendStateRenderTargetValidFlags that indicate which 
            render states are valid for each render target.
    */
    void SetBlendStateDesc(
        const D3D11_BLEND_DESC& blendDesc, 
        efd::UInt32 validFlags,
        efd::UInt8 renderTargetValidFlags[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]);
    /**
        Returns the currently set blend state desc on a render state group.

        @param blendDesc Outputs the blend state desc.
        @param validFlags Outputs the set of flags from D3D11RenderStateManager::BlendStateValidFlags that
            indicate which states in the blend state desc are valid.
        @param renderTargetValidFlags Outputs an array of flags from  
            D3D11RenderStateManager::BlendStateRenderTargetValidFlags that indicate which 
            render states are valid for each render target.
    */
    void GetBlendStateDesc(
        D3D11_BLEND_DESC& blendDesc, 
        efd::UInt32& validFlags,
        efd::UInt8 renderTargetValidFlags[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]) const;
    /**
        Set a depth stencil state desc on a render state group at once, rather than through 
        individual states.

        The data in the provided depth stencil state desc and valid flags will overwrite the data 
        currently stored in the render state group.

        @param depthStencilDesc The depth stencil state desc to set.
        @param validFlags The set of flags from D3D11RenderStateManager::DepthStencilStateValidFlags that
            indicate which states in the depth stencil state desc are valid.
    */
    void SetDepthStencilStateDesc(
        const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc, 
        efd::UInt32 validFlags);
    /**
        Returns the currently set depth stencil state desc.

        @param depthStencilDesc Outputs the depth stencil state desc.
        @param validFlags Outputs the set of flags from 
            D3D11RenderStateManager::DepthStencilStateValidFlags that indicate which states in the 
            depth stencil state desc are valid.
    */
    void GetDepthStencilStateDesc(
        D3D11_DEPTH_STENCIL_DESC& depthStencilDesc, 
        efd::UInt32& validFlags) const;
    /**
        Set a rasterizer state desc on a render state group at once, rather than through 
        individual states.

        The data in the provided rasterizer state desc and valid flags will overwrite the data 
        currently stored in the render state group.

        @param rasterizerDesc The rasterizer state desc to set.
        @param validFlags The set of flags from D3D11RenderStateManager::RasterizerStateValidFlags that
            indicate which states in the rasterizer state desc are valid.
    */
    void SetRasterizerStateDesc(
        const D3D11_RASTERIZER_DESC& rasterizerDesc, 
        efd::UInt32 validFlags);
    /**
        Returns the currently set rasterizer state desc.

        @param rasterizerDesc Outputs the rasterizer state desc.
        @param validFlags Outputs the set of flags from 
            D3D11RenderStateManager::RasterizerStateValidFlags that indicate which states in the 
            rasterizer state desc are valid.
    */
    void GetRasterizerStateDesc(
        D3D11_RASTERIZER_DESC& rasterizerDesc, 
        efd::UInt32& validFlags) const;
    /**
        Set a sampler desc on a sampler in a render state group at once, rather than through 
        individual states.

        The data in the provided sampler desc and valid flags will overwrite the data 
        currently stored in the sampler.

        @param samplerName The name of the sampler to affect.
        @param samplerDesc The sampler desc to set.
        @param samplerValidFlags The set of flags from D3D11RenderStateManager::SamplerValidFlags that
            indicate which states in the sampler desc are valid.
    */
    void SetSamplerDesc(
        efd::FixedString& samplerName,
        const D3D11_SAMPLER_DESC& samplerDesc, 
        efd::UInt32 samplerValidFlags);
    /**
        Returns the currently set sampler desc for a sampler.

        @param samplerName The name of the sampler to affect.
        @param samplerDesc Outputs the sampler desc.
        @param samplerValidFlags Outputs the set of flags from D3D11RenderStateManager::SamplerValidFlags that
            indicate which states in the sampler desc are valid.
    */
    void GetSamplerDesc(
        efd::FixedString& samplerName,
        D3D11_SAMPLER_DESC& samplerDesc,
        efd::UInt32& samplerValidFlags) const;

    /// Clear out all render states currently set on the render state group, and release all
    /// sampler objects.
    void ResetRenderStates();

    /// @cond EMERGENT_INTERNAL

    /// Returns the number of times Reset has been called.
    inline efd::UInt32 GetResetCount() const;

    /// @endcond

protected:
    /// Internal helper function to find a sampler and its predecessor.
    Sampler* FindSampler(
        const efd::FixedString& samplerName, 
        Sampler*& pSamplerBefore) const;

    D3D11_BLEND_DESC m_blendDesc;
    D3D11_DEPTH_STENCIL_DESC m_depthStencilDesc;
    D3D11_RASTERIZER_DESC m_rasterizerDesc;

    Sampler* m_pSamplers;

    efd::Float32 m_blendFactor[4];
    efd::UInt32 m_sampleMask;
    efd::UInt32 m_stencilRef;

    efd::UInt32 m_blendValidFlags;
    efd::UInt8 m_renderTargetValidFlags[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
    efd::UInt32 m_depthStencilValidFlags;
    efd::UInt32 m_rasterizerValidFlags;

    // Must track reset count so we know when the samplers are invalid
    efd::UInt32 m_resetCount;

    efd::Bool m_blendFactorValid;
    efd::Bool m_sampleMaskValid;
    efd::Bool m_stencilRefValid;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11RenderStateGroup
/// class.
typedef efd::SmartPointer<D3D11RenderStateGroup> D3D11RenderStateGroupPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11RenderStateGroup.inl>

#endif // EE_D3D11RENDERSTATEGROUP_H
