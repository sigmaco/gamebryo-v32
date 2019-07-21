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

//------------------------------------------------------------------------------------------------
inline NiShadowMap::NiShadowMap() :
    m_uFlags(0),
    m_usMaxAnisotropy(1)
{
}

//------------------------------------------------------------------------------------------------
inline NiShadowMap::~NiShadowMap()
{
}

//------------------------------------------------------------------------------------------------
inline void NiShadowMap::_SDMInit()
{
    ms_akMapName[NiStandardMaterial::LIGHT_DIR] = "DirShadow";
    ms_akMapName[NiStandardMaterial::LIGHT_POINT] = "PointShadow";
    ms_akMapName[NiStandardMaterial::LIGHT_SPOT] = "SpotShadow";
}

//------------------------------------------------------------------------------------------------
inline void NiShadowMap::_SDMShutdown()
{
    ms_akMapName[NiStandardMaterial::LIGHT_DIR] = NULL;
    ms_akMapName[NiStandardMaterial::LIGHT_POINT] = NULL;
    ms_akMapName[NiStandardMaterial::LIGHT_SPOT] = NULL;
}

//------------------------------------------------------------------------------------------------
inline const NiFixedString& NiShadowMap::GetMapNameFromType(
    NiStandardMaterial::LightType eType)
{
    return ms_akMapName[eType];
}

//------------------------------------------------------------------------------------------------
inline bool NiShadowMap::GetLightTypeFromName(
    const NiFixedString& kName, unsigned int& uiID)
{
    if (kName == ms_akMapName[NiStandardMaterial::LIGHT_SPOT])
    {
        uiID = NiStandardMaterial::LIGHT_SPOT;
        return true;
    }

    if (kName == ms_akMapName[NiStandardMaterial::LIGHT_POINT])
    {
        uiID = NiStandardMaterial::LIGHT_POINT;
        return true;
    }

    if (kName == ms_akMapName[NiStandardMaterial::LIGHT_DIR])
    {
        uiID = NiStandardMaterial::LIGHT_DIR;
        return true;
    }

    return false;
}

//------------------------------------------------------------------------------------------------
inline const float* NiShadowMap::GetWorldToShadowMap() const
{
    EE_ASSERT(m_spRenderClick->GetRenderViews().GetSize() > 0);
    EE_ASSERT(NiIsKindOf(Ni3DRenderView,
        m_spRenderClick->GetRenderViews().GetHead()));

    Ni3DRenderView* pkShadowView =
        (Ni3DRenderView*)(m_spRenderClick->GetRenderViews().GetHead().data());
    EE_ASSERT(pkShadowView->GetCamera());

    return pkShadowView->GetCamera()->GetWorldToCameraMatrix();
}

//------------------------------------------------------------------------------------------------
inline NiRenderedTexture* NiShadowMap::GetTexture() const
{
    return m_spTexture;
}

//------------------------------------------------------------------------------------------------
inline NiShadowRenderClick* NiShadowMap::GetRenderClick() const
{
    return m_spRenderClick;
}

//------------------------------------------------------------------------------------------------
inline NiTexturingProperty::ClampMode NiShadowMap::GetClampMode() const
{
    return (NiTexturingProperty::ClampMode) GetField(CLAMPMODE_MASK,
        CLAMPMODE_POS);
}

//------------------------------------------------------------------------------------------------
inline void NiShadowMap::SetClampMode(
    NiTexturingProperty::ClampMode eClampMode)
{
    SetField(NiInt32ToUInt16(eClampMode), CLAMPMODE_MASK, CLAMPMODE_POS);
}

//------------------------------------------------------------------------------------------------
inline NiTexturingProperty::FilterMode NiShadowMap::GetFilterMode() const
{
    return (NiTexturingProperty::FilterMode) GetField(FILTERMODE_MASK,
        FILTERMODE_POS);
}

//------------------------------------------------------------------------------------------------
inline void NiShadowMap::SetFilterMode(
    NiTexturingProperty::FilterMode eFilterMode)
{
    SetField(NiInt32ToUInt16(eFilterMode), FILTERMODE_MASK, FILTERMODE_POS);
}

//------------------------------------------------------------------------------------------------
inline unsigned short NiShadowMap::GetMaxAnisotropy() const
{
    return m_usMaxAnisotropy;
}

//------------------------------------------------------------------------------------------------
inline void NiShadowMap::SetMaxAnisotropy(unsigned short usMaxAnisotropyValue)
{
    m_usMaxAnisotropy = usMaxAnisotropyValue;
}

//------------------------------------------------------------------------------------------------
inline NiShadowMap::TextureType NiShadowMap::GetTextureType()
{
    return (TextureType) GetField(TEXTURETYPE_MASK, TEXTURETYPE_POS);
}

//------------------------------------------------------------------------------------------------
inline void NiShadowMap::SetTextureType(TextureType eTextureType)
{
    SetField(NiInt32ToUInt16(eTextureType), TEXTURETYPE_MASK, TEXTURETYPE_POS);
}

//------------------------------------------------------------------------------------------------
inline void NiShadowMap::ClearFlags()
{
    m_uFlags = 0;
}

//------------------------------------------------------------------------------------------------
