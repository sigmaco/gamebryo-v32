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
// NSBTextureStage inline functions
//------------------------------------------------------------------------------------------------
inline const char* NSBTextureStage::GetName()
{
    return m_pcName;
}

//------------------------------------------------------------------------------------------------
inline unsigned int NSBTextureStage::GetStage()
{
    return m_uiStage;
}

//------------------------------------------------------------------------------------------------
inline void NSBTextureStage::SetStage(unsigned int uiStage)
{
    m_uiStage = uiStage;
}

//------------------------------------------------------------------------------------------------
inline unsigned int NSBTextureStage::GetTextureFlags()
{
    return m_uiTextureFlags;
}

//------------------------------------------------------------------------------------------------
inline unsigned short NSBTextureStage::GetObjTextureFlags()
{
    return m_usObjTextureFlags;
}

//------------------------------------------------------------------------------------------------
inline void NSBTextureStage::SetNDLMap(unsigned int uiNDLMap)
{
    // Clear the DECAL and SHADER modes
    m_uiTextureFlags &= ~NiTextureStage::TSTF_MAP_MASK;

    // Set the given map flag
    m_uiTextureFlags |= uiNDLMap;
}

//------------------------------------------------------------------------------------------------
inline void NSBTextureStage::SetDecalMap(unsigned int uiDecal)
{
    // Clear the Map and Gamebryo sections
    m_uiTextureFlags &= ~(NiTextureStage::TSTF_MAP_MASK |
        NiTextureStage::TSTF_NDL_TYPEMASK);

    // Set decal mode and index
    m_uiTextureFlags |= (NiTextureStage::TSTF_MAP_DECAL | uiDecal);
}

//------------------------------------------------------------------------------------------------
inline void NSBTextureStage::SetShaderMap(unsigned int uiShaderMap)
{
    // Clear the Map and Gamebryo sections
    m_uiTextureFlags &= ~(NiTextureStage::TSTF_MAP_MASK |
        NiTextureStage::TSTF_NDL_TYPEMASK);

    // Set shader mode and index
    m_uiTextureFlags |= (NiTextureStage::TSTF_MAP_SHADER | uiShaderMap);
}

//------------------------------------------------------------------------------------------------
inline void NSBTextureStage::SetUseIndexFromMap(bool bUse)
{
    if (bUse)
        m_uiTextureFlags |= NiTextureStage::TSTF_MAP_USE_INDEX;
    else
        m_uiTextureFlags &= ~NiTextureStage::TSTF_MAP_USE_INDEX;
}

//------------------------------------------------------------------------------------------------
inline bool NSBTextureStage::GetUseTextureTransformation()
{
    return m_bTextureTransform;
}

//------------------------------------------------------------------------------------------------
inline float* NSBTextureStage::GetTextureTransformation()
{
    return m_afTextureTransform;
}

//------------------------------------------------------------------------------------------------
inline void NSBTextureStage::SetUseTextureTransformation(bool bUse)
{
    m_bTextureTransform = bUse;
}

//------------------------------------------------------------------------------------------------
inline void NSBTextureStage::SetTextureTransformation(float afTextureTransform[16])
{
    memcpy(m_afTextureTransform, afTextureTransform, sizeof(afTextureTransform));
}

//------------------------------------------------------------------------------------------------
inline unsigned int NSBTextureStage::GetTextureTransformFlags()
{
    return m_uiTextureTransformFlags;
}

//------------------------------------------------------------------------------------------------
inline void NSBTextureStage::SetTextureTransformFlags(unsigned int uiFlags)
{
    m_uiTextureTransformFlags = uiFlags;
}

//------------------------------------------------------------------------------------------------
inline const char* NSBTextureStage::GetGlobalName()
{
    return m_pcGlobalEntry;
}

//------------------------------------------------------------------------------------------------
inline void NSBTextureStage::SetGlobalName(const char* pcGlobalName)
{
    NSBUtility::SetString(m_pcGlobalEntry, 0, pcGlobalName);
}

//------------------------------------------------------------------------------------------------
inline void NSBTextureStage::SetObjTextureSettings(
    NiShaderAttributeDesc::ObjectType eObjectType,
    unsigned int uiObjectIndex)
{
    m_usObjTextureFlags = (unsigned short)(uiObjectIndex |
        (((unsigned int)eObjectType) << NiTextureStage::TSOTF_TYPE_SHIFT));
}

//------------------------------------------------------------------------------------------------
