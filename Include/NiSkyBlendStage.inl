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
inline NiSkyMaterial::ColorMap::Value NiSkyBlendStage::GetColorMapType() 
    const
{
    return m_eColorMap;
}

//---------------------------------------------------------------------------
inline NiSkyMaterial::ModifierSource::Value 
NiSkyBlendStage::GetModifierSource() const
{
    return m_eModifierSource;
}

//---------------------------------------------------------------------------
inline NiSkyMaterial::BlendMethod::Value
NiSkyBlendStage::GetBlendMethod() const
{
    return m_eBlendMethod;
}

//---------------------------------------------------------------------------
inline float NiSkyBlendStage::GetBlendConstant() const
{
    return m_fBlendConstant;
}

//---------------------------------------------------------------------------
inline bool NiSkyBlendStage::GetEnabled() const
{
    return m_bEnabled;
}

//---------------------------------------------------------------------------
inline bool NiSkyBlendStage::HasPropertyChanged() const
{
    return m_bHasSettingChanged;
}

//---------------------------------------------------------------------------
inline void NiSkyBlendStage::MarkPropertyChanged(bool bChanged)
{
    m_bHasSettingChanged = bChanged;
}

//---------------------------------------------------------------------------
inline void NiSkyBlendStage::SetModifierSource(
    NiSkyMaterial::ModifierSource::Value eSource)
{
    m_eModifierSource = eSource;
}

//---------------------------------------------------------------------------
inline void NiSkyBlendStage::SetBlendMethod(
    NiSkyMaterial::BlendMethod::Value eMethod)
{
    m_eBlendMethod = eMethod;
}

//---------------------------------------------------------------------------
inline void NiSkyBlendStage::SetBlendConstant(float fMultiplier)
{
    m_fBlendConstant = fMultiplier;
    MarkPropertyChanged(true);
}

//---------------------------------------------------------------------------
inline float NiSkyBlendStage::GetBlendBiasExponent() const
{
    return m_fBlendBiasExponent;
}

//---------------------------------------------------------------------------
inline float NiSkyBlendStage::GetBlendHorizonBias() const
{
    return m_fBlendHorizonBias;
}

//---------------------------------------------------------------------------
inline void NiSkyBlendStage::SetBlendBiasExponent(float fBiasExponent)
{
    m_fBlendBiasExponent = fBiasExponent;
    MarkPropertyChanged(true);
}

//---------------------------------------------------------------------------
inline void NiSkyBlendStage::SetBlendHorizonBias(float fHorizonBias)
{
    m_fBlendHorizonBias = fHorizonBias;
    MarkPropertyChanged(true);
}

//---------------------------------------------------------------------------
inline void NiSkyBlendStage::SetEnabled(bool bEnabled)
{
    m_bEnabled = bEnabled;
}

//---------------------------------------------------------------------------
inline const NiColorA& NiSkyGradientBlendStage::GetZenithColor() const
{
    return m_kZenithColor;
}

//---------------------------------------------------------------------------
inline const NiColorA& NiSkyGradientBlendStage::GetHorizonColor() const
{
    return m_kHorizonColor;
}

//---------------------------------------------------------------------------
inline float NiSkyGradientBlendStage::GetGradientHorizonBias() const
{
    return m_fGradientHorizonBias;
}

//---------------------------------------------------------------------------
inline float NiSkyGradientBlendStage::GetGradientBiasExponent() const
{
    return m_fGradientBiasExponent;
}

//---------------------------------------------------------------------------
inline void NiSkyGradientBlendStage::SetZenithColor(NiColorA kZenithColor)
{
    m_kZenithColor = kZenithColor;
    MarkPropertyChanged(true);
}

//---------------------------------------------------------------------------
inline void NiSkyGradientBlendStage::SetHorizonColor(NiColorA kHorizonColor)
{
    m_kHorizonColor = kHorizonColor;
    MarkPropertyChanged(true);
}

//---------------------------------------------------------------------------
inline void NiSkyGradientBlendStage::SetGradientHorizonBias(float fHorizonBias)
{
    m_fGradientHorizonBias = fHorizonBias;
    MarkPropertyChanged(true);
}

//---------------------------------------------------------------------------
inline void NiSkyGradientBlendStage::SetGradientBiasExponent(float fBiasExponent)
{
    m_fGradientBiasExponent = fBiasExponent;
    MarkPropertyChanged(true);
}

//---------------------------------------------------------------------------
inline void NiSkySkyboxBlendStage::SetTexture(NiTexture* pkTexture)
{
    m_spTexture = pkTexture;
    MarkPropertyChanged(true);
}

//---------------------------------------------------------------------------
inline NiTexture* NiSkySkyboxBlendStage::GetTexture() const
{
    return m_spTexture;
}

//---------------------------------------------------------------------------
inline bool NiSkySkyboxBlendStage::IsOriented()
{
    return m_eColorMap == NiSkyMaterial::ColorMap::ORIENTED_SKYBOX;
}

//---------------------------------------------------------------------------
inline void NiSkySkyboxBlendStage::SetOriented(bool bOrient)
{
    if (bOrient)
    {
        m_eColorMap = NiSkyMaterial::ColorMap::ORIENTED_SKYBOX;
    }
    else
    {
        m_eColorMap = NiSkyMaterial::ColorMap::SKYBOX;
    }
    MarkPropertyChanged(true);
}

//---------------------------------------------------------------------------
inline void NiSkySkyboxBlendStage::SetOrientation(
    const NiMatrix3& kOrientation)
{
    m_kOrientation = kOrientation;
    MarkPropertyChanged(true);
}

//---------------------------------------------------------------------------
inline const NiMatrix3& NiSkySkyboxBlendStage::GetOrientation() const
{
    return m_kOrientation;
}

//---------------------------------------------------------------------------
