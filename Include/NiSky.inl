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
inline NiAtmosphere* NiSky::GetAtmosphere()
{
    return m_spAtmosphere;
}

//---------------------------------------------------------------------------
inline NiDirectionalLight* NiSky::GetSun()
{
    return m_pkSun;
}

//---------------------------------------------------------------------------
inline void NiSky::SetAtmosphericCalcMode(
    AtmosphericCalcMode::Value eCalcMode)
{
    m_eAtmosphericCalcMode = eCalcMode;
    m_bBlendStagesChanged = true;
    NiRenderObject::RecursiveSetMaterialNeedsUpdate(this, true);
}

//---------------------------------------------------------------------------
inline NiSky::AtmosphericCalcMode::Value NiSky::GetAtmosphericCalcMode()
{
    return m_eAtmosphericCalcMode;
}

//---------------------------------------------------------------------------
inline void NiSky::MarkBlendStagesChanged()
{
    m_bBlendStagesChanged = true;
}

//---------------------------------------------------------------------------
