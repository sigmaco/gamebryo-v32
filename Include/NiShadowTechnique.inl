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

#include <NiShadowManager.h>

//--------------------------------------------------------------------------------------------------
inline const NiFixedString& NiShadowTechnique::GetName() const
{
    return m_kName;
}

//--------------------------------------------------------------------------------------------------
inline const NiFixedString& NiShadowTechnique::
    GetReadFragmentName(NiStandardMaterial::LightType eType) const
{
    return m_kReadFragmentName[eType];
}

//--------------------------------------------------------------------------------------------------
inline const NiFixedString& NiShadowTechnique::
    GetWriteFragmentName(NiStandardMaterial::LightType eType) const
{
    return m_kWriteFragmentName[eType];
}

//--------------------------------------------------------------------------------------------------
inline bool NiShadowTechnique::IsWriteBatchable()
{
    return m_bWriteBatchable;
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowTechnique::SetWriteBatchable(bool bBatchable)
{
    m_bWriteBatchable = bBatchable;
}

//--------------------------------------------------------------------------------------------------
inline unsigned short NiShadowTechnique::GetTechniqueID()
{
    return m_usTechniqueID;
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowTechnique::SetTechniqueID(unsigned short usID)
{
    m_usTechniqueID = usID;
}

//--------------------------------------------------------------------------------------------------
inline unsigned short NiShadowTechnique::GetActiveTechniqueSlot()
{
    return m_uiActiveTechniqueSlot;
}

//--------------------------------------------------------------------------------------------------
inline bool NiShadowTechnique::GetUseCubeMapForPointLight()
{
    return m_bUseCubeMapForPointLight;
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowTechnique::SetUseCubeMapForPointLight(bool bUseCubeMap)
{
    m_bUseCubeMapForPointLight = bUseCubeMap;
}

//--------------------------------------------------------------------------------------------------
inline NiTexture::FormatPrefs& NiShadowTechnique::GetTextureFormatPrefs(
    NiStandardMaterial::LightType eType)
{
    NIASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    return m_akFormatPrefs[eType];
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowTechnique::SetTextureFormatPrefs(
    NiStandardMaterial::LightType eType,
    NiTexture::FormatPrefs& pkPrefs)
{
    NIASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    m_akFormatPrefs[eType] = pkPrefs;
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowTechnique::AppendPostProcessRenderClicks(
    NiShadowMap*, NiShadowClickGenerator*)
{
    /* */
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowTechnique::PrepareShadowMap(NiShadowMap* /*pkShadowMap*/)
{
    /* */
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowTechnique::SetDefaultDepthBias(
    NiStandardMaterial::LightType eType, bool bRenderBackfaces,
    float fDepthBias)
{
    EE_ASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    int iIndex = NiSelect(bRenderBackfaces, eType,
        eType + NiStandardMaterial::LIGHT_MAX);
    m_afDefaultDepthBias[iIndex] = fDepthBias;
}

//--------------------------------------------------------------------------------------------------
inline float NiShadowTechnique::GetDefaultDepthBias(
    NiStandardMaterial::LightType eType, bool bRenderBackfaces)
{
    EE_ASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    int iIndex = NiSelect(bRenderBackfaces, eType,
        eType + NiStandardMaterial::LIGHT_MAX);
    return m_afDefaultDepthBias[iIndex];
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowTechnique::SetDepthFormat(
    NiStandardMaterial::LightType eType,
    const NiPixelFormat* pkDepthFormat)
{
    NIASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    m_apkDepthFormats[eType] = pkDepthFormat;
}

//--------------------------------------------------------------------------------------------------
inline const NiPixelFormat* NiShadowTechnique::GetDepthFormat(
    NiStandardMaterial::LightType eType) const
{
    NIASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    return m_apkDepthFormats[eType];
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowTechnique::SetFilterMode(
    NiStandardMaterial::LightType eType,
    NiTexturingProperty::FilterMode eFilterMode)
{
    NIASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    m_aeFilterModes[eType] = eFilterMode;
}

//--------------------------------------------------------------------------------------------------
inline NiTexturingProperty::FilterMode NiShadowTechnique::GetFilterMode(
    NiStandardMaterial::LightType eType) const
{
    NIASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    return m_aeFilterModes[eType];
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowTechnique::SetClampMode(
    NiStandardMaterial::LightType eType,
    NiTexturingProperty::ClampMode eClampMode)
{
    NIASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    m_aeClampModes[eType] = eClampMode;
}

//--------------------------------------------------------------------------------------------------
inline NiTexturingProperty::ClampMode NiShadowTechnique::GetClampMode(
    NiStandardMaterial::LightType eType) const
{
    NIASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    return m_aeClampModes[eType];
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowTechnique::SetGuardBandSize(unsigned int uiGuardBandSize)
{
    m_uiGuardBandSize = uiGuardBandSize;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiShadowTechnique::GetGuardBandSize() const
{
    return m_uiGuardBandSize;
}

//--------------------------------------------------------------------------------------------------
