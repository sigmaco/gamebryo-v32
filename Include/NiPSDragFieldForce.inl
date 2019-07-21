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
inline bool NiPSDragFieldForce::GetUseDirection() const
{
    return m_kInputData.m_bUseDirection;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSDragFieldForce::SetUseDirection(bool bUseDirection)
{
    m_kInputData.m_bUseDirection = bUseDirection;
}

//--------------------------------------------------------------------------------------------------
inline const NiPoint3& NiPSDragFieldForce::GetDirection() const
{
    return m_kInputData.m_kDirection;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSDragFieldForce::SetDirection(const NiPoint3& kDirection)
{
    m_kInputData.m_kDirection = kDirection;
}

//--------------------------------------------------------------------------------------------------
