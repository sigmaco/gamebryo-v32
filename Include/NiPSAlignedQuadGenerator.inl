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
inline void NiPSAlignedQuadGenerator::NormalizeScaleAmountU()
{
    if (fabs(m_kGeneratorKernelStruct.m_fScaleLimitU - m_kGeneratorKernelStruct.m_fScaleRestU) <
        NIPSKERNEL_EPSILON)
    {
        m_kGeneratorKernelStruct.m_fScaleNormalizedU = 0.0f;
    }
    else
    {
        m_kGeneratorKernelStruct.m_fScaleNormalizedU = m_kGeneratorKernelStruct.m_fScaleAmountU /
            (m_kGeneratorKernelStruct.m_fScaleLimitU - m_kGeneratorKernelStruct.m_fScaleRestU);
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::NormalizeScaleAmountV()
{
    if (fabs(m_kGeneratorKernelStruct.m_fScaleLimitV - m_kGeneratorKernelStruct.m_fScaleRestV) <
        NIPSKERNEL_EPSILON)
    {
        m_kGeneratorKernelStruct.m_fScaleNormalizedV = 0.0f;
    }
    else
    {
        m_kGeneratorKernelStruct.m_fScaleNormalizedV = m_kGeneratorKernelStruct.m_fScaleAmountV /
            (m_kGeneratorKernelStruct.m_fScaleLimitV - m_kGeneratorKernelStruct.m_fScaleRestV);
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetScaleAmountU(const float fValue)
{
    if (!m_bAttached)
    {
        m_kGeneratorKernelStruct.m_fScaleAmountU = fValue;
        NormalizeScaleAmountU();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetScaleLimitU(const float fValue)
{
    if (!m_bAttached)
    {
        m_kGeneratorKernelStruct.m_fScaleLimitU = fValue;
        NormalizeScaleAmountU();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetScaleRestU(const float fValue)
{
    if (!m_bAttached)
    {
        m_kGeneratorKernelStruct.m_fScaleRestU = fValue;
        NormalizeScaleAmountU();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetScaleAmountV(const float fValue)
{
    if (!m_bAttached)
    {
        m_kGeneratorKernelStruct.m_fScaleAmountV = fValue;
        NormalizeScaleAmountV();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetScaleLimitV(const float fValue)
{
    if (!m_bAttached)
    {
        m_kGeneratorKernelStruct.m_fScaleLimitV = fValue;
        NormalizeScaleAmountV();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetScaleRestV(const float fValue)
{
    if (!m_bAttached)
    {
        m_kGeneratorKernelStruct.m_fScaleRestV = fValue;
        NormalizeScaleAmountV();
    }
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetScaleAmountU() const
{
    return m_kGeneratorKernelStruct.m_fScaleAmountU;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetScaleLimitU() const
{
    return m_kGeneratorKernelStruct.m_fScaleLimitU;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetScaleRestU() const
{
    return m_kGeneratorKernelStruct.m_fScaleRestU;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetScaleAmountV() const
{
    return m_kGeneratorKernelStruct.m_fScaleAmountV;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetScaleLimitV() const
{
    return m_kGeneratorKernelStruct.m_fScaleLimitV;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetScaleRestV() const
{
    return m_kGeneratorKernelStruct.m_fScaleRestV;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetUVScrolling(bool bValue)
{
    if (!m_bAttached)
    {
        m_kTextureKernelStruct.m_bUVScrolling = bValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetNumFramesAcross(const NiUInt16 uiValue)
{
    if (!m_bAttached)
    {
        m_kTextureKernelStruct.m_uiNumFramesAcross = uiValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetNumFramesDown(const NiUInt16 uiValue)
{
    if (!m_bAttached)
    {
        m_kTextureKernelStruct.m_uiNumFramesDown = uiValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetPingPong(const bool bValue)
{
    if (!m_bAttached)
    {
        m_kTextureKernelStruct.m_bPingPong = bValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetInitialFrame(const NiUInt16 uiValue)
{
    if (!m_bAttached)
    {
        m_kTextureKernelStruct.m_uiInitialFrame = uiValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetInitialFrameVar(const float fValue)
{
    if (!m_bAttached)
    {
        m_kTextureKernelStruct.m_fInitialFrameVar = fValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetNumFrames(const NiUInt16 uiValue)
{
    if (!m_bAttached)
    {
        m_kTextureKernelStruct.m_uiNumFrames = uiValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetNumFramesVar(const float fValue)
{
    if (!m_bAttached)
    {
        m_kTextureKernelStruct.m_fNumFramesVar = fValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetInitialTime(const float fValue)
{
    if (!m_bAttached)
    {
        m_kTextureKernelStruct.m_fInitialTime = fValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetFinalTime(const float fValue)
{
    if (!m_bAttached)
    {
        m_kTextureKernelStruct.m_fFinalTime = fValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSAlignedQuadGenerator::GetUVScrolling() const
{
    return m_kTextureKernelStruct.m_bUVScrolling;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiPSAlignedQuadGenerator::GetNumFramesAcross() const
{
    return m_kTextureKernelStruct.m_uiNumFramesAcross;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiPSAlignedQuadGenerator::GetNumFramesDown() const
{
    return m_kTextureKernelStruct.m_uiNumFramesDown;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSAlignedQuadGenerator::GetPingPong() const
{
    return m_kTextureKernelStruct.m_bPingPong;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiPSAlignedQuadGenerator::GetInitialFrame() const
{
    return m_kTextureKernelStruct.m_uiInitialFrame;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetInitialFrameVar() const
{
    return m_kTextureKernelStruct.m_fInitialFrameVar;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiPSAlignedQuadGenerator::GetNumFrames() const
{
    return m_kTextureKernelStruct.m_uiNumFrames;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetNumFramesVar() const
{
    return m_kTextureKernelStruct.m_fNumFramesVar;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetInitialTime() const
{
    return m_kTextureKernelStruct.m_fInitialTime;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetFinalTime() const
{
    return m_kTextureKernelStruct.m_fFinalTime;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetCenterU(const float fValue)
{
    if (!m_bAttached)
    {
        m_kGeneratorKernelStruct.m_fCenterU = fValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSAlignedQuadGenerator::SetCenterV(const float fValue)
{
    if (!m_bAttached)
    {
        m_kGeneratorKernelStruct.m_fCenterV = fValue;
    }
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetCenterU() const
{
    return m_kGeneratorKernelStruct.m_fCenterU;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSAlignedQuadGenerator::GetCenterV() const
{
    return m_kGeneratorKernelStruct.m_fCenterV;
}
