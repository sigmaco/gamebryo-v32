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
inline void NiPhysXBodyDesc::SetFromBodyDesc(const NxBodyDesc& kBodyDesc, const NxMat33& kXform)
{
    m_kBodyDesc = kBodyDesc;
    SetVelocities(kBodyDesc.linearVelocity, kBodyDesc.angularVelocity, false, 0, kXform);
}

//--------------------------------------------------------------------------------------------------
inline NxU32 NiPhysXBodyDesc::GetBodyFlags() const
{
    return m_kBodyDesc.flags;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiPhysXBodyDesc::AddState(NxActor* pkActor, const NxMat33& kXform)
{
    NiUInt32 uiIndex = m_uiNumVels;
    SetVelocities(
        pkActor->getLinearVelocity(),
        pkActor->getAngularVelocity(),
        pkActor->isSleeping(),
        uiIndex,
        kXform);
    return uiIndex;
}

//--------------------------------------------------------------------------------------------------
inline void NiPhysXBodyDesc::RestoreState(
    NxActor* pkActor,
    const NiUInt32 uiIndex,
    const NxMat33& kXform)
{
    EE_ASSERT(uiIndex < m_uiNumVels);
    if (pkActor->isDynamic() && !pkActor->readBodyFlag(NX_BF_KINEMATIC))
    {
        pkActor->setLinearVelocity(kXform * m_pkLinVels[uiIndex]);
        pkActor->setAngularVelocity(kXform * m_pkAngVels[uiIndex]);
        if (m_pkLinVels[uiIndex].isZero() && m_pkSleepSettings[uiIndex])
        {
            pkActor->putToSleep();
        }
    }
}

//--------------------------------------------------------------------------------------------------
inline bool NiPhysXBodyDesc::StreamCanSkip()
{
    return true;
}

//--------------------------------------------------------------------------------------------------
inline void NiPhysXBodyDesc::GetVelocities(
    NxVec3& kLinearVelocity,
    NxVec3& kAngularVelocity,
    bool& bIsSleeping,
    const NiUInt32 uiIndex) const
{
    kLinearVelocity = m_pkLinVels[uiIndex];
    kAngularVelocity = m_pkAngVels[uiIndex];
    bIsSleeping = m_pkSleepSettings[uiIndex];
}

//--------------------------------------------------------------------------------------------------
