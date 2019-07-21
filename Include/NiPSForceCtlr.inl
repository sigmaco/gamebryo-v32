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
inline const NiFixedString& NiPSForceCtlr::GetForceName() const
{
    return m_kForceName;
}

//--------------------------------------------------------------------------------------------------
inline NiPSForce* NiPSForceCtlr::GetForcePointer() const
{
    return m_pkForce;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSForceCtlr::SetForceName(const NiFixedString& kForceName)
{
    EE_ASSERT(kForceName.Exists());
    m_kForceName = kForceName;
}

//--------------------------------------------------------------------------------------------------
