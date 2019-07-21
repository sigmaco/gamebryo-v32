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
#ifndef EE_D3D11RENDERSTATEMANAGER_H
#define EE_D3D11RENDERSTATEMANAGER_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>
#include <ecrD3D11Renderer/D3D11Renderer.h>
#include <ecrD3D11Renderer/D3D11RenderStateGroup.h>
#include <efd/MemObject.h>

#include <NiAlphaProperty.h>
#include <NiStencilProperty.h>
#include <NiTexturingProperty.h>
#include <NiZBufferProperty.h>

struct _D3DX11_STATE_BLOCK_MASK;
typedef _D3DX11_STATE_BLOCK_MASK D3DX11_STATE_BLOCK_MASK;

namespace ecr
{

class D3D11DeviceState;

/**
    ecr::D3D11RenderStateManager manages the D3D11 render state structures.

    ecr::D3D11RenderStateManager handles the accumulation of individual render state changes 
    and the creation of D3D11 state objects. Refer to the discussion on 
    Render State Management in the ecrD3D11Renderer for more information.
*/

class EE_ECRD3D11RENDERER_ENTRY D3D11RenderStateManager : public efd::MemObject
{
public:
    /// @cond EMERGENT_INTERNAL

    /// @name Construction and Destruction
    //@{
    /**
        The constructor initializes a new ecr::D3D11RenderStateManager using the D3D11 device. 
        
        An application should never construct a new render state manager object, but should 
        obtain a pointer to the D3D11Renderer object's instance instead.
    */
    D3D11RenderStateManager(
        ID3D11Device* pDevice,
        D3D11DeviceState* pDeviceState);
    /// Destructor.
    virtual ~D3D11RenderStateManager();
    //@}

    /// Return the left/right swap flag.
    inline efd::Bool GetLeftRightSwap() const;
    /// Set the left/right swap flag, which helps determine the value of FrontCounterClockwise
    /// in the depth stencil state.
    inline void SetLeftRightSwap(efd::Bool bSwap);

    /// @endcond

    /** 
        Update the accumulated render states based on the properties in the NiPropertyState.
        
        Only the NiAlphaProperty, NiStencilProperty, NiWireframeProperty, and NiZBufferProperty 
        properties are used by the D3D11RenderStateManager to update render state, though 
        NiTexturingProperty settings can also be applied by an NiShader.
    */
    efd::Bool ApplyProperties(const NiPropertyState* pState);
    /// Update the accumulated render states based on the provided NiAlphaProperty.
    efd::Bool ApplyAlphaProperty(const NiAlphaProperty* pNew);
    /// Update the accumulated render states based on the provided NiStencilProperty.
    efd::Bool ApplyStencilProperty(const NiStencilProperty* pNew);
    /// Update the accumulated render states based on the provided NiWireframeProperty.
    efd::Bool ApplyWireframeProperty(const NiWireframeProperty* pNew);
    /// Update the accumulated render states based on the provided NiZBufferProperty.
    efd::Bool ApplyZBufferProperty(const NiZBufferProperty* pNew);

    /// Update the accumulated render states based on the D3D11RenderStateGroup.
    efd::Bool ApplyRenderStateGroup(const D3D11RenderStateGroup* pRSGroup);

    /// Flags that indicate which states in the D3D11_BLEND_DESC structures should be accumulated
    /// into the current render state.
    enum BlendStateValidFlags
    {
        /// AlphaToCoverageEnable
        BSVALID_ALPHATOCOVERAGEENABLE   = 1 <<  0,
        /// IndependentBlendEnable
        BSVALID_INDEPENDENTBLENDENABLE  = 1 <<  1,
        /// Indicates any of the states in the D3D11_RENDER_TARGET_BLEND_DESC for render target 0 
        /// are valid.
        BSVALID_RENDERTARGET_0          = 1 <<  2,
        /// Indicates any of the states in the D3D11_RENDER_TARGET_BLEND_DESC for render target 1 
        /// are valid.
        BSVALID_RENDERTARGET_1          = 1 <<  3,
        /// Indicates any of the states in the D3D11_RENDER_TARGET_BLEND_DESC for render target 2 
        /// are valid.
        BSVALID_RENDERTARGET_2          = 1 <<  4,
        /// Indicates any of the states in the D3D11_RENDER_TARGET_BLEND_DESC for render target 3 
        /// are valid.
        BSVALID_RENDERTARGET_3          = 1 <<  5,
        /// Indicates any of the states in the D3D11_RENDER_TARGET_BLEND_DESC for render target 4 
        /// are valid.
        BSVALID_RENDERTARGET_4          = 1 <<  6,
        /// Indicates any of the states in the D3D11_RENDER_TARGET_BLEND_DESC for render target 5 
        /// are valid.
        BSVALID_RENDERTARGET_5          = 1 <<  7,
        /// Indicates any of the states in the D3D11_RENDER_TARGET_BLEND_DESC for render target 6 
        /// are valid.
        BSVALID_RENDERTARGET_6          = 1 <<  8,
        /// Indicates any of the states in the D3D11_RENDER_TARGET_BLEND_DESC for render target 7
        /// are valid.
        BSVALID_RENDERTARGET_7          = 1 <<  9
    };

    /// Flags that indicate which states in the D3D11_RENDER_TARGET_BLEND_DESC structures should be 
    /// accumulated into the current render state.
    enum BlendStateRenderTargetValidFlags
    {
        /// BlendEnable
        BSRTVALID_BLENDENABLE             = 1 <<  0,
        /// SrcBlend
        BSRTVALID_SRCBLEND                = 1 <<  1,
        /// DestBlend
        BSRTVALID_DESTBLEND               = 1 <<  2,
        /// BlendOp
        BSRTVALID_BLENDOP                 = 1 <<  3,
        /// SrcBlendAlpha
        BSRTVALID_SRCBLENDALPHA           = 1 <<  4,
        /// DestBlendAlpha
        BSRTVALID_DESTBLENDALPHA          = 1 <<  5,
        /// BlendOpAlpha
        BSRTVALID_BLENDOPALPHA            = 1 <<  6,
        /// RenderTargetWriteMask
        BSRTVALID_RENDERTARGETWRITEMASK   = 1 <<  7,
    };

    /// Flags that indicate which states in the D3D11_DEPTH_STENCIL_DESC structures should be 
    /// accumulated into the current render state.
    enum DepthStencilStateValidFlags
    {
        /// DepthEnable
        DSSVALID_DEPTHENABLE                    = 1 <<  0,
        /// DepthWriteMask
        DSSVALID_DEPTHWRITEMASK                 = 1 <<  1,
        /// DepthFunc
        DSSVALID_DEPTHFUNC                      = 1 <<  2,
        /// StencilEnable
        DSSVALID_STENCILENABLE                  = 1 <<  3,
        /// StencilReadMask
        DSSVALID_STENCILREADMASK                = 1 <<  4,
        /// StencilWriteMask
        DSSVALID_STENCILWRITEMASK               = 1 <<  5,
        /// FrontFace.StencilFailOp
        DSSVALID_FRONTFACE_STENCILFAILOP        = 1 <<  6,
        /// FrontFace.StencilDepthFailOp
        DSSVALID_FRONTFACE_STENCILDEPTHFAILOP   = 1 <<  7,
        /// FrontFace.StencilPassOp
        DSSVALID_FRONTFACE_STENCILPASSOP        = 1 <<  8,
        /// FrontFace.StencilFunc
        DSSVALID_FRONTFACE_STENCILFUNC          = 1 <<  9,
        /// BackFace.StencilFailOp
        DSSVALID_BACKFACE_STENCILFAILOP         = 1 << 10,
        /// BackFace.StencilDepthFailOp
        DSSVALID_BACKFACE_STENCILDEPTHFAILOP    = 1 << 11,
        /// BackFace.StencilPassOp
        DSSVALID_BACKFACE_STENCILPASSOP         = 1 << 12,
        /// BackFace.StencilFunc
        DSSVALID_BACKFACE_STENCILFUNC           = 1 << 13
    };

    /// Flags that indicate which states in the D3D11_RASTERIZER_DESC structures should be 
    /// accumulated into the current render state.
    enum RasterizerStateValidFlags
    {
        /// FillMode
        RSVALID_FILLMODE                = 1 <<  0,
        /// CullMode
        RSVALID_CULLMODE                = 1 <<  1,
        /// FrontCounterClockwise
        RSVALID_FRONTCOUNTERCLOCKWISE   = 1 <<  2,
        /// DepthBias
        RSVALID_DEPTHBIAS               = 1 <<  3,
        /// DepthBiasClamp
        RSVALID_DEPTHBIASCLAMP          = 1 <<  4,
        /// SlopeScaledDepthBias
        RSVALID_SLOPESCALEDDEPTHBIAS    = 1 <<  5,
        /// DepthClipEnable
        RSVALID_DEPTHCLIPENABLE         = 1 <<  6,
        /// ScissorEnable
        RSVALID_SCISSORENABLE           = 1 <<  7,
        /// MultisampleEnable
        RSVALID_MULTISAMPLEENABLE       = 1 <<  8,
        /// AntialiasedLineEnable
        RSVALID_ANTIALIASEDLINEENABLE   = 1 <<  9
    };

    /// Flags that indicate which states in the D3D11_SAMPLER_DESC structures should be 
    /// accumulated into the current render state.
    enum SamplerValidFlags
    {
        /// Filter
        SVALID_FILTER          = 1 <<  0,
        /// AddressU
        SVALID_ADDRESSU        = 1 <<  1,
        /// AddressV
        SVALID_ADDRESSV        = 1 <<  2,
        /// AddressW
        SVALID_ADDRESSW        = 1 <<  3,
        /// MipLODBias
        SVALID_MIPLODBIAS      = 1 <<  4,
        /// MaxAnisotropy
        SVALID_MAXANISOTROPY   = 1 <<  5,
        /// ComparisonFunc
        SVALID_COMPARISONFUNC  = 1 <<  6,
        /// BorderColor
        SVALID_BORDERCOLOR     = 1 <<  7,
        /// MinLOD
        SVALID_MINLOD          = 1 <<  8,
        /// MaxLOD
        SVALID_MAXLOD          = 1 <<  9
    };

    /**
        Update the accumulated render states based on a blend state desc.

        Only those elements of the structure indicated by the valid flags will be accumulated
        to the current render state.

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
    /// Return the currently accumulated blend state desc.
    inline void GetBlendStateDesc(D3D11_BLEND_DESC& blendDesc) const;
    /// Set the current blend factor.
    inline void SetBlendFactor(const float blendFactor[4]);
    /// Return the current blend factor.
    inline void GetBlendFactor(float blendFactor[4]) const;
    /// Set the current sample mask.
    inline void SetSampleMask(efd::UInt32 sampleMask);
    /// Return the current sample mask.
    inline void GetSampleMask(efd::UInt32& sampleMask) const;

    /**
        Update the accumulated render states based on a depth stencil state desc.

        Only those elements of the structure indicated by the valid flags will be accumulated
        to the current render state.

        @param depthStencilDesc The depth stencil state desc to set.
        @param validFlags The set of flags from D3D11RenderStateManager::DepthStencilStateValidFlags that
            indicate which states in the depth stencil state desc are valid.
    */
    void SetDepthStencilStateDesc(
        const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc,
        efd::UInt32 validFlags);
    /// Return the currently accumulated depth stencil state desc.
    inline void GetDepthStencilStateDesc(D3D11_DEPTH_STENCIL_DESC& depthStencilDesc) const;
    /// Set the current stencil reference value.
    inline void SetStencilRef(efd::UInt32 stencilRef);
    /// Return the current stencil reference value.
    inline void GetStencilRef(efd::UInt32& stencilRef) const;

    /**
        Update the accumulated render states based on a rasterizer state desc.

        Only those elements of the structure indicated by the valid flags will be accumulated
        to the current render state.

        @param rasterizerDesc The rasterizer state desc to set.
        @param validFlags The set of flags from D3D11RenderStateManager::RasterizerStateValidFlags that
            indicate which states in the rasterizer state desc are valid.
    */
    void SetRasterizerStateDesc(
        const D3D11_RASTERIZER_DESC& rasterizerDesc,
        efd::UInt32 validFlags);
    /// Return the currently accumulated rasterizer state desc.
    inline void GetRasterizerStateDesc(D3D11_RASTERIZER_DESC& rasterizerDesc) const;

    /**
        Update the accumulated render states based on a sampler desc.

        Only those elements of the structure indicated by the valid flags will be accumulated
        to the current render state.

        @param shaderType Shader type for this sampler.
        @param sampler Sampler index for this sampler.
        @param samplerDesc The sampler desc to set.
        @param validFlags The set of flags from D3D11RenderStateManager::SamplerValidFlags that
            indicate which states in the sampler desc are valid.
    */
    void SetSamplerDesc(
        NiGPUProgram::ProgramType shaderType,
        efd::UInt32 sampler,
        const D3D11_SAMPLER_DESC& samplerDesc,
        efd::UInt32 validFlags);
    /// Return the currently accumulated sampler desc for the given shader type and sampler index.
    inline void GetSamplerDesc(
        NiGPUProgram::ProgramType shaderType,
        efd::UInt32 sampler,
        D3D11_SAMPLER_DESC& samplerDesc) const;

    /// Remove all accumulated render states and reset their values to the defaults
    void ResetCurrentState();

    /// Set the default blend state desc values.
    inline void SetDefaultBlendStateDesc(const D3D11_BLEND_DESC& blendDesc);
    /// Return the default blend state desc values.
    inline void GetDefaultBlendStateDesc(D3D11_BLEND_DESC& blendDesc) const;
    /// Set the default blend factor.
    inline void SetDefaultBlendFactor(const float blendFactor[4]);
    /// Return the default blend factor.
    inline void GetDefaultBlendFactor(float blendFactor[4]) const;
    /// Set the default sample mask.
    inline void SetDefaultSampleMask(efd::UInt32 sampleMask);
    /// Return the default sample mask.
    inline void GetDefaultSampleMask(efd::UInt32& sampleMask) const;

    /// Set the default depth stencil state desc values.
    inline void SetDefaultDepthStencilStateDesc(
        const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc);
    /// Return the default depth stencil state desc values.
    inline void GetDefaultDepthStencilStateDesc(
        D3D11_DEPTH_STENCIL_DESC& depthStencilDesc) const;
    /// Set the default stencil reference value.
    inline void SetDefaultStencilRef(efd::UInt32 stenciRef);
    /// Return the default stencil reference value.
    inline void GetDefaultStencilRef(efd::UInt32& stencilRef) const;

    /// Set the default rasterizer state desc values.
    inline void SetDefaultRasterizerStateDesc(const D3D11_RASTERIZER_DESC& rasterizerDesc);
    /// Return the default rasterizer state desc values.
    inline void GetDefaultRasterizerStateDesc(D3D11_RASTERIZER_DESC& rasterizerDesc) const;

    /// Set the default sampler desc values, used for all samplers.
    void SetDefaultSamplerDesc(const D3D11_SAMPLER_DESC& samplerDesc);
    /// Return the default sampler state desc values, used for all samplers.
    void GetDefaultSamplerDesc(D3D11_SAMPLER_DESC& samplerDesc) const;

    /** 
        Apply currently accumulated render state to device context.

        The currently accumulated render states are used to create new state block objects
        which are set on the device context.

        @param pMask State block mask indicating which render state blocks to set.
    */
    void ApplyCurrentState(const D3DX11_STATE_BLOCK_MASK* pMask = NULL);

    /// Create blend state block object and set it on the device context.
    void ApplyCurrentBlendState();
    /// Create depth stencil state block object and set it on the device context.
    void ApplyCurrentDepthStencilState();
    /// Create rasterizer state block object and set it on the device context.
    void ApplyCurrentRasterizerState();
    /// Create sampler objects and set them on the device context.
    void ApplyCurrentSamplers(const D3DX11_STATE_BLOCK_MASK* pMask = NULL);

    /** 
        Create sampler objects for the given shader type and set them on the device context.

        @param shaderType Shader type of samplers to be set.
        @param samplerStart First index of samplers to set.
        @param samplerCount Number of samplers to set.
        @param pMask State block mask indicating which render state blocks to set.
    */
    void ApplyCurrentSamplers(
        NiGPUProgram::ProgramType shaderType,
        efd::UInt32 samplerStart, 
        efd::UInt32 samplerCount,
        const D3DX11_STATE_BLOCK_MASK* pMask = NULL);

    /** 
        Set an array of D3D11RenderStateGroup::Sampler objects.

        D3D11RenderStateGroup objects accumulate sampler states based on a sampler name, but
        the samplers must be set on the device context based on shader program type and index 
        value, which are determined by the shader programs themselves. Before applying samplers, 
        a shader must construct arrays of Sampler objects that correspond to the sampler
        indices that the shader programs exist. This function is how those arrays are passed in
        before the render state manager constructs the ID3D11SamplerState objects and set on the
        device context.
    */
    void SetSamplerArray(
        NiGPUProgram::ProgramType programType,
        efd::UInt8 samplerCount,
        D3D11RenderStateGroup::Sampler** samplerArray);
    /// Clear the array of D3D11RenderStateGroup::Sampler objects.
    void ClearSamplerArrays();

    /// @name Conversion functions
    //@{
    /// Convert an NiAlphaProperty::AlphaFunction to a D3D11_BLEND enumeration.
    static D3D11_BLEND ConvertGbBlendToD3D11Blend(
        NiAlphaProperty::AlphaFunction alphaFunction);
    /// Convert an NiStencilProperty::TestFunc to a D3D11_COMPARISON_FUNC enumeration.
    static D3D11_COMPARISON_FUNC ConvertGbStencilFuncToD3D11Comparison(
        NiStencilProperty::TestFunc testFunction);
    /// Convert an NiStencilProperty::Action to a D3D11_STENCIL_OP enumeration.
    static D3D11_STENCIL_OP ConvertGbStencilActionToD3D11StencilOp(
        NiStencilProperty::Action action);
    /// Convert an NiZBufferProperty::TestFunction to a D3D11_COMPARISON_FUNC enumeration.
    static D3D11_COMPARISON_FUNC ConvertGbDepthFuncToD3D11Comparison(
        NiZBufferProperty::TestFunction testFunction);
    /// Convert an NiTexturingProperty::FilterMode to a D3D11_FILTER enumeration.
    static D3D11_FILTER ConvertGbFilterModeToD3D11Filter(
        NiTexturingProperty::FilterMode filterMode);
    /// Return whether an NiTexturingProperty::FilterMode enables mipmapping or not.
    static efd::Bool ConvertGbFilterModeToMipmapEnable(
        NiTexturingProperty::FilterMode filterMode);
    /// Convert an NiTexturingProperty::ClampMode to a D3D11_TEXTURE_ADDRESS_MODE enumeration.
    static D3D11_TEXTURE_ADDRESS_MODE ConvertGbClampModeToD3D11AddressU(
        NiTexturingProperty::ClampMode clampMode);
    /// Convert an NiTexturingProperty::ClampMode to a D3D11_TEXTURE_ADDRESS_MODE enumeration.
    static D3D11_TEXTURE_ADDRESS_MODE ConvertGbClampModeToD3D11AddressV(
        NiTexturingProperty::ClampMode clampMode);
    //@}
protected:
    /// Initialize Gamebryo's default render state values.
    void InitDefaultValues();

    /// Create a default blend state object based on the default values.
    void UpdateDefaultBlendStateObject();
    /// Create a default depth stencil state object based on the default values.
    void UpdateDefaultDepthStencilStateObject();
    /// Create a default rasterizer state object based on the default values.
    void UpdateDefaultRasterizerStateObject();
    /// Create a default sampler state object based on the default values.
    void UpdateDefaultSamplerObject();

    ID3D11Device* m_pDevice;
    D3D11DeviceState* m_pDeviceState;

    // Default render state values
    D3D11_BLEND_DESC m_defaultBlendDesc;
    D3D11_DEPTH_STENCIL_DESC m_defaultDepthStencilDesc;
    D3D11_RASTERIZER_DESC m_defaultRasterizerDesc;
    D3D11_SAMPLER_DESC m_defaultSamplerDesc;
    float m_defaultBlendFactor[4];
    efd::UInt32 m_defaultSampleMask;
    efd::UInt32 m_defaultStencilRef;

    // Render states currently under construction
    D3D11_BLEND_DESC m_currentBlendDesc;
    D3D11_DEPTH_STENCIL_DESC m_currentDepthStencilDesc;
    D3D11_RASTERIZER_DESC m_currentRasterizerDesc;
    D3D11_SAMPLER_DESC m_currentSamplerDescArray[NiGPUProgram::PROGRAM_MAX]
        [D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
    float m_currentBlendFactor[4];
    efd::UInt32 m_currentSampleMask;
    efd::UInt32 m_currentStencilRef;

    // Default state objects
    ID3D11BlendState* m_pDefaultBlendState;
    ID3D11DepthStencilState* m_pDefaultDepthStencilState;
    ID3D11RasterizerState* m_pDefaultRasterizerState;
    ID3D11SamplerState* m_pDefaultSamplerState;

    // Temporary sampler arrays
    efd::UInt8 m_samplerCountArray[NiGPUProgram::PROGRAM_MAX];
    D3D11RenderStateGroup::Sampler** m_samplerArray[NiGPUProgram::PROGRAM_MAX];

    // Gamebryo override value
    efd::Bool m_leftRightSwap;

    // Dirty flags
    efd::Bool m_blendStateDirty;
    efd::Bool m_depthStencilStateDirty;
    efd::Bool m_rasterizerStateDirty;
    efd::Bool m_samplersDirtyArray[NiGPUProgram::PROGRAM_MAX]
        [D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
};

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11RenderStateManager.inl>

#endif // EE_D3D11RENDERSTATEMANAGER_H
