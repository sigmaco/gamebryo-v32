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
inline void NiCurve3::SetDegree(NiUInt32 uiDegree)
{
    m_uiDegree = uiDegree;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiCurve3::GetNumControlPoints() const
{
    return m_uiNumControlPoints;
}

//--------------------------------------------------------------------------------------------------
inline NiPoint3 NiCurve3::GetControlPoint(NiUInt32 uiIndex) const
{
    EE_ASSERT(uiIndex < m_uiNumControlPoints);
    return m_pkControlPoints[uiIndex];
}

//--------------------------------------------------------------------------------------------------
inline NiPoint3* NiCurve3::GetControlPoints() const
{
    return m_pkControlPoints;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiCurve3::GetNumKnots() const
{
    return m_uiNumKnots;
}

//--------------------------------------------------------------------------------------------------
inline float NiCurve3::GetKnot(NiUInt32 uiIndex) const
{
    EE_ASSERT(uiIndex < m_uiNumKnots);
    return m_pfKnots[uiIndex];
}

//--------------------------------------------------------------------------------------------------
inline float* NiCurve3::GetKnots() const
{
    return m_pfKnots;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiCurve3::GetNumSpans(void) const
{
    return m_uiNumControlPoints - m_uiDegree;
}



