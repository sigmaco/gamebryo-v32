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

namespace ecr
{

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11RenderStateManager::GetLeftRightSwap() const
{
    return m_leftRightSwap;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::SetLeftRightSwap(efd::Bool swap)
{
    m_leftRightSwap = swap;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetBlendStateDesc(D3D11_BLEND_DESC& blendDesc) const
{
    memset(&blendDesc, 0, sizeof(blendDesc));
    blendDesc = m_currentBlendDesc;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::SetBlendFactor(const float blendFactor[4])
{
    m_currentBlendFactor[0] = blendFactor[0];
    m_currentBlendFactor[1] = blendFactor[1];
    m_currentBlendFactor[2] = blendFactor[2];
    m_currentBlendFactor[3] = blendFactor[3];
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetBlendFactor(float blendFactor[4]) const
{
    blendFactor[0] = m_currentBlendFactor[0];
    blendFactor[1] = m_currentBlendFactor[1];
    blendFactor[2] = m_currentBlendFactor[2];
    blendFactor[3] = m_currentBlendFactor[3];
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::SetSampleMask(efd::UInt32 sampleMask)
{
    m_currentSampleMask = sampleMask;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetSampleMask(efd::UInt32& sampleMask) const
{
    sampleMask = m_currentSampleMask;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetDepthStencilStateDesc(
    D3D11_DEPTH_STENCIL_DESC& depthStencilDesc) const
{
    memset(&depthStencilDesc, 0, sizeof(depthStencilDesc));
    depthStencilDesc = m_currentDepthStencilDesc;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::SetStencilRef(efd::UInt32 stencilRef)
{
    m_currentStencilRef = stencilRef;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetStencilRef(efd::UInt32& stencilRef) const
{
    stencilRef = m_currentStencilRef;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetRasterizerStateDesc(
    D3D11_RASTERIZER_DESC& rasterizerDesc) const
{
    memset(&rasterizerDesc, 0, sizeof(rasterizerDesc));
    rasterizerDesc = m_currentRasterizerDesc;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetSamplerDesc(
    NiGPUProgram::ProgramType shaderType, 
    efd::UInt32 sampler,
    D3D11_SAMPLER_DESC& samplerDesc) const
{
    memset(&samplerDesc, 0, sizeof(samplerDesc));
    if (sampler < D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT)
        samplerDesc = m_currentSamplerDescArray[(efd::UInt32)shaderType][sampler];
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::SetDefaultBlendStateDesc(const D3D11_BLEND_DESC& blendDesc)
{
    m_defaultBlendDesc = blendDesc;
    UpdateDefaultBlendStateObject();
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetDefaultBlendStateDesc(D3D11_BLEND_DESC& blendDesc) const
{
    memset(&blendDesc, 0, sizeof(blendDesc));
    blendDesc = m_defaultBlendDesc;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::SetDefaultBlendFactor(const float blendFactor[4])
{
    m_defaultBlendFactor[0] = blendFactor[0];
    m_defaultBlendFactor[1] = blendFactor[1];
    m_defaultBlendFactor[2] = blendFactor[2];
    m_defaultBlendFactor[3] = blendFactor[3];
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetDefaultBlendFactor(float blendFactor[4]) const
{
    blendFactor[0] = m_defaultBlendFactor[0];
    blendFactor[1] = m_defaultBlendFactor[1];
    blendFactor[2] = m_defaultBlendFactor[2];
    blendFactor[3] = m_defaultBlendFactor[3];
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::SetDefaultSampleMask(efd::UInt32 uiSampleMask)
{
    m_defaultSampleMask = uiSampleMask;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetDefaultSampleMask(efd::UInt32& uiSampleMask) const
{
    uiSampleMask = m_defaultSampleMask;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::SetDefaultDepthStencilStateDesc(
    const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc)
{
    m_defaultDepthStencilDesc = depthStencilDesc;
    UpdateDefaultDepthStencilStateObject();
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetDefaultDepthStencilStateDesc(
    D3D11_DEPTH_STENCIL_DESC& depthStencilDesc) const
{
    memset(&depthStencilDesc, 0, sizeof(depthStencilDesc));
    depthStencilDesc = m_defaultDepthStencilDesc;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::SetDefaultStencilRef(efd::UInt32 stenciRef)
{
    m_defaultStencilRef = stenciRef;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetDefaultStencilRef(efd::UInt32& stencilRef) const
{
    stencilRef = m_defaultStencilRef;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::SetDefaultRasterizerStateDesc(
    const D3D11_RASTERIZER_DESC& rasterizerDesc)
{
    m_defaultRasterizerDesc = rasterizerDesc;
    UpdateDefaultRasterizerStateObject();
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetDefaultRasterizerStateDesc(
    D3D11_RASTERIZER_DESC& rasterizerDesc) const
{
    memset(&rasterizerDesc, 0, sizeof(rasterizerDesc));
    rasterizerDesc = m_defaultRasterizerDesc;
}
//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::GetDefaultSamplerDesc(
    D3D11_SAMPLER_DESC& samplerDesc) const
{
    memset(&samplerDesc, 0, sizeof(samplerDesc));
    samplerDesc = m_defaultSamplerDesc;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::SetSamplerArray(
    NiGPUProgram::ProgramType programType,
    efd::UInt8 samplerCount,
    D3D11RenderStateGroup::Sampler** samplerArray)
{
    m_samplerCountArray[programType] = samplerCount;
    m_samplerArray[programType] = samplerArray;
}

//------------------------------------------------------------------------------------------------
inline void D3D11RenderStateManager::ClearSamplerArrays()
{
    memset(&m_samplerCountArray, 0, sizeof(m_samplerCountArray));
    memset(&m_samplerArray, 0, sizeof(m_samplerArray));
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
