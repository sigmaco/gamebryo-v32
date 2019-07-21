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
inline const efd::FixedString& D3D11RenderStateGroup::Sampler::GetName() const
{
    return m_samplerName;
}

//------------------------------------------------------------------------------------------------
inline const D3D11_SAMPLER_DESC& D3D11RenderStateGroup::Sampler::GetSamplerDesc() const
{
    return m_samplerDesc;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11RenderStateGroup::Sampler::GetSamplerValidFlags() const
{
    return m_samplerValidFlags;
}

//--------------------------------------------------------------------------------------------------
inline const D3D11RenderStateGroup::Sampler* D3D11RenderStateGroup::GetFirstSampler() const
{
    return m_pSamplers;
}

//------------------------------------------------------------------------------------------------
inline const D3D11RenderStateGroup::Sampler* D3D11RenderStateGroup::GetNextSampler(
    const D3D11RenderStateGroup::Sampler* pSampler) const
{
    EE_ASSERT(pSampler);
    return pSampler->m_pNext;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11RenderStateGroup::GetResetCount() const
{
    return m_resetCount;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
