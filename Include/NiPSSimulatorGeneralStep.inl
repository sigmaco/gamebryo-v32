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
inline NiPSKernelFloatKey* NiPSSimulatorGeneralStep::GetSizeKeys(NiUInt8& ucNumSizeKeys) const
{
    ucNumSizeKeys = m_kInputStruct.m_ucNumSizeKeys;
    return m_pkSizeKeys;
}

//--------------------------------------------------------------------------------------------------
inline NiPSLoopBehavior NiPSSimulatorGeneralStep::GetSizeLoopBehavior() const
{
    return m_kInputStruct.m_eSizeLoopBehavior;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSimulatorGeneralStep::SetSizeLoopBehavior(const NiPSLoopBehavior eBehavior)
{
    m_kInputStruct.m_eSizeLoopBehavior = eBehavior;
}

//--------------------------------------------------------------------------------------------------
inline NiPSKernelColorKey* NiPSSimulatorGeneralStep::GetColorKeys(NiUInt8& ucNumColorKeys) const
{
    ucNumColorKeys = m_kInputStruct.m_ucNumColorKeys;
    return m_pkColorKeys;
}

//--------------------------------------------------------------------------------------------------
inline NiPSLoopBehavior NiPSSimulatorGeneralStep::GetColorLoopBehavior() const
{
    return m_kInputStruct.m_eColorLoopBehavior;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSimulatorGeneralStep::SetColorLoopBehavior(const NiPSLoopBehavior eBehavior)
{
    m_kInputStruct.m_eColorLoopBehavior = eBehavior;
}

//--------------------------------------------------------------------------------------------------
inline NiPSKernelFloatKey* NiPSSimulatorGeneralStep::GetRotationKeys(NiUInt8& ucNumRotationKeys)
    const
{
    ucNumRotationKeys = m_kInputStruct.m_ucNumRotationKeys;
    return m_pkRotationKeys;
}

//--------------------------------------------------------------------------------------------------
inline NiPSLoopBehavior NiPSSimulatorGeneralStep::GetRotationLoopBehavior() const
{
    return m_kInputStruct.m_eRotationLoopBehavior;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSimulatorGeneralStep::SetRotationLoopBehavior(const NiPSLoopBehavior eBehavior)
{
    m_kInputStruct.m_eRotationLoopBehavior = eBehavior;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSimulatorGeneralStep::GetGrowTime() const
{
    return m_kInputStruct.m_fGrowTime;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSimulatorGeneralStep::SetGrowTime(float fGrowTime)
{
    m_kInputStruct.m_fGrowTime = fGrowTime;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSimulatorGeneralStep::GetShrinkTime() const
{
    return m_kInputStruct.m_fShrinkTime;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSimulatorGeneralStep::SetShrinkTime(float fShrinkTime)
{
    m_kInputStruct.m_fShrinkTime = fShrinkTime;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiPSSimulatorGeneralStep::GetGrowGeneration() const
{
    return m_kInputStruct.m_usGrowGeneration;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSimulatorGeneralStep::SetGrowGeneration(NiUInt16 usGrowGeneration)
{
    m_kInputStruct.m_usGrowGeneration = usGrowGeneration;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiPSSimulatorGeneralStep::GetShrinkGeneration() const
{
    return m_kInputStruct.m_usShrinkGeneration;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSimulatorGeneralStep::SetShrinkGeneration(NiUInt16 usShrinkGeneration)
{
    m_kInputStruct.m_usShrinkGeneration = usShrinkGeneration;
}

//--------------------------------------------------------------------------------------------------
