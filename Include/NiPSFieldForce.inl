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
inline NiAVObject* NiPSFieldForce::GetFieldObj() const
{
    return m_pkFieldObj;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSFieldForce::SetFieldObj(NiAVObject* pkFieldObj)
{
    m_pkFieldObj = pkFieldObj;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSFieldForce::GetMagnitude() const
{
    EE_ASSERT(m_pkInputData);
    return m_pkInputData->m_fMagnitude;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSFieldForce::SetMagnitude(float fMagnitude)
{
    EE_ASSERT(m_pkInputData);
    m_pkInputData->m_fMagnitude = fMagnitude;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSFieldForce::GetAttenuation() const
{
    EE_ASSERT(m_pkInputData);
    return m_pkInputData->m_fAttenuation;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSFieldForce::SetAttenuation(float fAttenuation)
{
    EE_ASSERT(m_pkInputData);
    m_pkInputData->m_fAttenuation = fAttenuation;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSFieldForce::GetUseMaxDistance() const
{
    EE_ASSERT(m_pkInputData);
    return m_pkInputData->m_bUseMaxDistance;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSFieldForce::SetUseMaxDistance(bool bUseMaxDistance)
{
    EE_ASSERT(m_pkInputData);
    m_pkInputData->m_bUseMaxDistance = bUseMaxDistance;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSFieldForce::GetMaxDistance() const
{
    EE_ASSERT(m_pkInputData);
    return m_pkInputData->m_fMaxDistance;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSFieldForce::SetMaxDistance(float fMaxDistance)
{
    EE_ASSERT(m_pkInputData);
    m_pkInputData->m_fMaxDistance = fMaxDistance;
    m_pkInputData->m_fMaxDistanceSqr = fMaxDistance * fMaxDistance;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSFieldForce::ComputeFieldToPSys(
    const NiTransform& kPSys,
    NiTransform& kFieldToPSys)
{
    EE_ASSERT(m_pkFieldObj);

    // Compute the transform from field space to particle system space.
    NiTransform kField = m_pkFieldObj->GetWorldTransform();
    NiTransform kInvPSys;
    kPSys.Invert(kInvPSys);
    kFieldToPSys = kInvPSys * kField;
}

//--------------------------------------------------------------------------------------------------
