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
inline NiD3DCgVertexShader::NiD3DCgVertexShader(NiD3DRenderer* pkRenderer) :
    NiD3DVertexShader(pkRenderer),
    m_pcEntryPoint(NULL),
    m_pcShaderTarget(NULL),
    m_kCgProgram(NULL)
{ /* */ }

//--------------------------------------------------------------------------------------------------
inline const char* NiD3DCgVertexShader::GetEntryPoint() const
{
    return m_pcEntryPoint;
}

//--------------------------------------------------------------------------------------------------
inline void NiD3DCgVertexShader::SetEntryPoint(const char* pcEntryPoint)
{
    if (m_pcEntryPoint == pcEntryPoint)
        return;

    NiFree(m_pcEntryPoint);
    if (pcEntryPoint && pcEntryPoint[0] != '\0')
    {
        size_t uiLen = strlen(pcEntryPoint) + 1;
        char* pcNewEntryPoint = NiAlloc(char, uiLen);
        EE_ASSERT(pcNewEntryPoint);
        NiStrcpy(pcNewEntryPoint, uiLen, pcEntryPoint);
        m_pcEntryPoint = pcNewEntryPoint;
    }
    else
    {
        m_pcEntryPoint = NULL;
    }
}

//--------------------------------------------------------------------------------------------------
inline const char* NiD3DCgVertexShader::GetShaderTarget() const
{
    return m_pcShaderTarget;
}

//--------------------------------------------------------------------------------------------------
inline void NiD3DCgVertexShader::SetShaderTarget(const char* pcShaderTarget)
{
    if (m_pcShaderTarget == pcShaderTarget)
        return;

    NiFree(m_pcShaderTarget);
    if (pcShaderTarget && pcShaderTarget[0] != '\0')
    {
        size_t uiLen = strlen(pcShaderTarget) + 1;
        char* pcNewShaderTarget = NiAlloc(char, uiLen);
        EE_ASSERT(pcNewShaderTarget);
        NiStrcpy(pcNewShaderTarget, uiLen, pcShaderTarget);
        m_pcShaderTarget = pcNewShaderTarget;
    }
    else
    {
        pcShaderTarget = NULL;
    }
}

//--------------------------------------------------------------------------------------------------
inline CGprogram NiD3DCgVertexShader::GetCgProgram() const
{
    return m_kCgProgram;
}

//--------------------------------------------------------------------------------------------------
inline void NiD3DCgVertexShader::SetCgProgram(CGprogram kProgram)
{
    m_kCgProgram = kProgram;
}

//--------------------------------------------------------------------------------------------------
