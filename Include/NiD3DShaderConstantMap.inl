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
// NiD3DShaderConstantMap inline functions
//--------------------------------------------------------------------------------------------------
inline bool NiD3DShaderConstantMap::GetModified()
{
    return m_bModified;
}

//--------------------------------------------------------------------------------------------------
inline void NiD3DShaderConstantMap::SetModified(bool bModified)
{
    m_bModified = bModified;
}

//--------------------------------------------------------------------------------------------------
inline NiD3DError NiD3DShaderConstantMap::GetLastError()
{
    return m_eLastError;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiD3DShaderConstantMap::GetEntryCount()
{
    NiUInt32 uiCount = 0;
    for (NiUInt32 ui = 0; ui < NiRenderer::PHASE_COUNT; ui++)
        uiCount += m_aspPhaseEntries[ui].GetEffectiveSize();

    return uiCount;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiD3DShaderConstantMap::GetPhaseIndex(
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
        return 2;
    };
}

//--------------------------------------------------------------------------------------------------
