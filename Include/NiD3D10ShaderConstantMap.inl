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
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
inline void NiD3D10ShaderConstantMap::SetName(const NiFixedString& kName)
{
    m_kName = kName;
}

//--------------------------------------------------------------------------------------------------
inline const NiFixedString& NiD3D10ShaderConstantMap::GetName() const
{
    return m_kName;
}

//--------------------------------------------------------------------------------------------------
inline NiD3D10DataStream* NiD3D10ShaderConstantMap::
    GetShaderConstantDataStream()  const
{
    return m_spShaderConstantDataStream;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiD3D10ShaderConstantMap::
    GetShaderConstantBufferIndex() const
{
    return m_uiShaderConstantBufferIndex;
}

//--------------------------------------------------------------------------------------------------
inline void NiD3D10ShaderConstantMap::SetConstantBufferObsolete()
{
    m_bConstantBufferCurrent = false;
}

//--------------------------------------------------------------------------------------------------
inline bool NiD3D10ShaderConstantMap::IsConstantBufferCurrent() const
{
    return m_bConstantBufferCurrent;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiD3D10ShaderConstantMap::GetEntryCount()
{
    NiUInt32 uiCount = 0;
    for (NiUInt32 ui = 0; ui < NiRenderer::PHASE_COUNT; ui++)
        uiCount += m_aspPhaseEntries[ui].GetEffectiveSize();

    return uiCount;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiD3D10ShaderConstantMap::GetPhaseIndex(
    NiRenderer::RenderingPhase ePhase)
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
        EE_FAIL("Error: Unsupported Rendering Phase");
    };
    return 2;
}

//--------------------------------------------------------------------------------------------------
