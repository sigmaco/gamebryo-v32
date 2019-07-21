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
inline NiCurve3* NiPSCurveEmitter::GetCurve() const
{
    return m_spCurve;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSCurveEmitter::SetCurve(NiCurve3* spCurve)
{
    m_spCurve = spCurve;
}

//--------------------------------------------------------------------------------------------------
inline NiNode* NiPSCurveEmitter::GetCurveParent() const
{
    return m_spCurveParent;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSCurveEmitter::SetCurveParent(NiNode* pkCurveParent)
{
    m_spCurveParent = pkCurveParent;
}

//--------------------------------------------------------------------------------------------------
inline NiAVObject* NiPSCurveEmitter::GetEmitterObj() const
{
    return m_pkEmitterObj;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSCurveEmitter::SetEmitterObj(NiAVObject* pkEmitterObj)
{
    m_pkEmitterObj = pkEmitterObj;
}

//--------------------------------------------------------------------------------------------------
