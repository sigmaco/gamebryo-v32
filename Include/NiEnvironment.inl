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
inline void NiEnvironment::SetAutoCalcFogColor(bool bEnable)
{
    m_bAutoCalcFogColor = bEnable;
}

//---------------------------------------------------------------------------
inline bool NiEnvironment::GetAutoCalcFogColor()
{
    return m_bAutoCalcFogColor;
}

//---------------------------------------------------------------------------
inline void NiEnvironment::SetAutoSetBackgroundColor(bool bEnable)
{
    m_bAutoSetBackgroundColor = bEnable;
}

//---------------------------------------------------------------------------
inline bool NiEnvironment::GetAutoSetBackgroundColor()
{
    return m_bAutoSetBackgroundColor;
}

//--------------------------------------------------------------------------------------------------
inline void NiEnvironment::SetSunElevationAngle(float fAngle)
{
    fAngle = (fAngle - 180.0f) * NI_PI / 180.0f;
    m_fSunElevationAngle = NiClamp(fAngle, - NI_PI, NI_PI);
    m_bSunSettingsChanged = true;
}

//--------------------------------------------------------------------------------------------------
inline float NiEnvironment::GetSunElevationAngle()
{
    return m_fSunElevationAngle;
}

//--------------------------------------------------------------------------------------------------
inline void NiEnvironment::SetSunAzimuthAngle(float fAngle)
{
    fAngle = (fAngle - 180.0f) * NI_PI / 180.0f;
    m_fSunAzimuthAngle = NiClamp(fAngle, - NI_PI, NI_PI);
    m_bSunSettingsChanged = true;
}

//--------------------------------------------------------------------------------------------------
inline float NiEnvironment::GetSunAzimuthAngle()
{
    return m_fSunAzimuthAngle;
}

//--------------------------------------------------------------------------------------------------
inline void NiEnvironment::SetUseSunAngles(bool bUseAngles)
{
    m_bUseSunAnglesRotation = bUseAngles;
}

//--------------------------------------------------------------------------------------------------
inline bool NiEnvironment::GetUseSunAngles()
{
    return m_bUseSunAnglesRotation;
}

//--------------------------------------------------------------------------------------------------
inline void NiEnvironment::SetFogColor(NiColorA kColor)
{
    NiFogProperty* pkFog = GetFogProperty();
    EE_ASSERT(pkFog);
    NiColor kFogColor(kColor.r, kColor.g, kColor.b);
    pkFog->SetFogColor(kFogColor);
}

//---------------------------------------------------------------------------