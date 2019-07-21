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
inline void D3D11ShaderConstantMap::SetName(const efd::FixedString& name)
{
    m_name = name;
}

//------------------------------------------------------------------------------------------------
inline const efd::FixedString& D3D11ShaderConstantMap::GetName() const
{
    return m_name;
}

//------------------------------------------------------------------------------------------------
inline D3D11DataStream* D3D11ShaderConstantMap::GetShaderConstantDataStream()  const
{
    return m_spShaderConstantDataStream;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderConstantMap::SetConstantBufferObsolete()
{
    m_constantBufferCurrent = false;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11ShaderConstantMap::IsConstantBufferCurrent() const
{
    return m_constantBufferCurrent;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderConstantMap::GetEntryCount()
{
    efd::UInt32 count = 0;
    for (efd::UInt32 ui = 0; ui < NiRenderer::PHASE_COUNT; ui++)
        count += m_phaseEntryArray[ui].GetEffectiveSize();

    return count;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderConstantMap::GetPhaseIndex(NiRenderer::RenderingPhase ePhase)
{
    switch (ePhase)
    {
    case(NiRenderer::PHASE_PER_SHADER):
        return 0;
    case(NiRenderer::PHASE_PER_LIGHTSTATE):
        return 1;
    case(NiRenderer::PHASE_PER_MESH):
        return 2;
    default:
        EE_ASSERT(!"Error: Unsupported Rendering Phase");
    };
    return 2;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
