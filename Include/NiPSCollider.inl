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

#include "NiPSSpawner.h"

//--------------------------------------------------------------------------------------------------
inline NiPSColliderDefinitions::ColliderType NiPSCollider::GetType() const
{
    return m_eType;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSCollider::GetBounce() const
{
    EE_ASSERT(m_pkInputData);
    return m_pkInputData->m_fBounce;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSCollider::SetBounce(float fBounce)
{
    EE_ASSERT(m_pkInputData);
    m_pkInputData->m_fBounce = fBounce;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSCollider::GetSpawnOnCollide() const
{
    EE_ASSERT(m_pkInputData);
    return m_pkInputData->m_bSpawnOnCollide;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSCollider::SetSpawnOnCollide(bool bSpawnOnCollide)
{
    EE_ASSERT(m_pkInputData);
    m_pkInputData->m_bSpawnOnCollide = bSpawnOnCollide;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSCollider::GetDieOnCollide() const
{
    EE_ASSERT(m_pkInputData);
    return m_pkInputData->m_bDieOnCollide;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSCollider::SetDieOnCollide(bool bDieOnCollide)
{
    EE_ASSERT(m_pkInputData);
    m_pkInputData->m_bDieOnCollide = bDieOnCollide;
}

//--------------------------------------------------------------------------------------------------
inline NiPSSpawner* NiPSCollider::GetSpawner() const
{
    return m_pkSpawner;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSCollider::SetSpawner(NiPSSpawner* pkSpawner)
{
    m_pkSpawner = pkSpawner;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSCollider::GetActive() const
{
    return m_bActive;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSCollider::SetActive(bool bActive)
{
    m_bActive = bActive;
}

//--------------------------------------------------------------------------------------------------
