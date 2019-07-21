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

//---------------------------------------------------------------------------
inline void NiAtmosphere::SetPhaseConstant(float fG)
{
    m_fPhaseConstant = fG;
    m_bAtmosphereSettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiAtmosphere::SetSunSize(float fSize)
{
    m_fSunSizeMultiplier = fSize;
    m_bAtmosphereSettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiAtmosphere::SetSunIntensity(float fIntensity)
{
    m_fSunIntensity = fIntensity;
    m_bAtmosphereSettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiAtmosphere::SetHDRExposure(float fExposure)
{
    m_fHDRExposure = fExposure;
    m_bAtmosphereSettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiAtmosphere::SetRayleighConstant(float fRayleigh)
{
    m_fRayleighConstant = fRayleigh;
    m_bAtmosphereSettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiAtmosphere::SetMieConstant(float fMie)
{
    m_fMieConstant = fMie;
    m_bAtmosphereSettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiAtmosphere::SetRGBWavelengths(float fR, float fG, float fB)
{
    m_kRGBWavelengths.x = fR;
    m_kRGBWavelengths.y = fG;
    m_kRGBWavelengths.z = fB;
    m_bAtmosphereSettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiAtmosphere::SetRedWavelength(float fWaveLength)
{
    m_kRGBWavelengths.x = fWaveLength;
    m_bAtmosphereSettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiAtmosphere::SetGreenWavelength(float fWaveLength)
{
    m_kRGBWavelengths.y = fWaveLength;
    m_bAtmosphereSettingsChanged = true;
}

//---------------------------------------------------------------------------
inline void NiAtmosphere::SetBlueWavelength(float fWaveLength)
{
    m_kRGBWavelengths.z = fWaveLength;
    m_bAtmosphereSettingsChanged = true;
}

//---------------------------------------------------------------------------
inline float NiAtmosphere::GetPhaseConstant()
{
	return m_fPhaseConstant;
}

//---------------------------------------------------------------------------
inline float NiAtmosphere::GetSunSize()
{
	return m_fSunSizeMultiplier;
}

//---------------------------------------------------------------------------
inline float NiAtmosphere::GetSunIntensity()
{
	return m_fSunIntensity;
}

//---------------------------------------------------------------------------
inline float NiAtmosphere::GetRayleighConstant()
{
	return m_fRayleighConstant;
}

//---------------------------------------------------------------------------
inline float NiAtmosphere::GetMieConstant()
{
	return m_fMieConstant;
}

//---------------------------------------------------------------------------
inline const NiPoint3& NiAtmosphere::GetRGBWavelengths()
{
	return m_kRGBWavelengths;
}

//---------------------------------------------------------------------------
inline float NiAtmosphere::GetHDRExposure()
{
	return m_fHDRExposure;
}

//---------------------------------------------------------------------------