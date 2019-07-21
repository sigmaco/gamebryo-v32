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
inline NiPSKernelQuaternionKey* NiPSSimulatorMeshAlignStep::GetRotationKeys(
    NiUInt8& ucNumRotationKeys) const
{
    ucNumRotationKeys = m_kKernelStruct.m_ucNumRotationKeys;
    return m_pkRotationKeys;
}

//--------------------------------------------------------------------------------------------------
inline NiPSLoopBehavior NiPSSimulatorMeshAlignStep::GetRotationLoopBehavior() const
{
    return m_kKernelStruct.m_eRotationLoopBehavior;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSimulatorMeshAlignStep::SetRotationLoopBehavior(const NiPSLoopBehavior eBehavior)
{
    m_kKernelStruct.m_eRotationLoopBehavior = eBehavior;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSimulatorMeshAlignStep::GetScaleAmount() const
{
    return m_kKernelStruct.m_fScaleAmount;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSimulatorMeshAlignStep::SetScaleAmount(const float fAmount)
{
    m_kKernelStruct.m_fScaleAmount = fAmount;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSimulatorMeshAlignStep::GetScaleRest() const
{
    return m_kKernelStruct.m_fScaleRest;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSimulatorMeshAlignStep::SetScaleRest(const float fRest)
{
    m_kKernelStruct.m_fScaleRest = fRest;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSimulatorMeshAlignStep::GetScaleLimit() const
{
    return m_kKernelStruct.m_fScaleLimit;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSimulatorMeshAlignStep::SetScaleLimit(const float fLimit)
{
    m_kKernelStruct.m_fScaleLimit = fLimit;
}

//--------------------------------------------------------------------------------------------------
