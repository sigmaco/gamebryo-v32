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

#include <NiShadowGenerator.h>

//---------------------------------------------------------------------------
inline void NiSkyDome::SetDomeRadius(float fRadius)
{
    m_fDomeRadius = fRadius;
    m_bGeometrySettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiSkyDome::SetDomeDetail(float fDetail)
{
    m_fDomeDetail = fDetail;
    m_bGeometrySettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiSkyDome::SetDomeDetailAxisBias(float fBias)
{
    m_fDomeDetailAxisBias = fBias;
    m_bGeometrySettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiSkyDome::SetDomeDetailHorizonBias(float fBias)
{
    m_fDomeDetailHorizonBias = fBias;
    m_bGeometrySettingsChanged = true;
}

//---------------------------------------------------------------------------
inline float NiSkyDome::GetDomeRadius()
{
	return m_fDomeRadius;
}

//---------------------------------------------------------------------------
inline float NiSkyDome::GetDomeDetail()
{
	return m_fDomeDetail;
}

//---------------------------------------------------------------------------
inline float NiSkyDome::GetDomeDetailAxisBias()
{
	return m_fDomeDetailAxisBias;
}

//---------------------------------------------------------------------------
inline float NiSkyDome::GetDomeDetailHorizonBias()
{
	return m_fDomeDetailHorizonBias;
}

//---------------------------------------------------------------------------
