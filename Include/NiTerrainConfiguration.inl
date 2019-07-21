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


inline void NiTerrainConfiguration::EnableMorphingData(
    bool bMorphingDataEnabled)
{
    m_bMorphingDataEnabled = bMorphingDataEnabled;
    EE_ASSERT(ValidateConfiguration());
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainConfiguration::EnableTangentData(bool bTangentDataEnabled)
{
    m_bTangentDataEnabled = bTangentDataEnabled;
    EE_ASSERT(ValidateConfiguration());
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainConfiguration::EnableLightingDataCompression(
    bool bLightingDataCompressionEnabled)
{
    m_bLightingDataCompressionEnabled = bLightingDataCompressionEnabled;
    EE_ASSERT(ValidateConfiguration());
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainConfiguration::EnableLowDetailNormalMapping(
    bool bLowDetailNormalMappingEnabled)
{
    m_bLowDetailNormalMappingEnabled = bLowDetailNormalMappingEnabled;
    EE_ASSERT(ValidateConfiguration());
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainConfiguration::IsMorphingDataEnabled() const
{
    return m_bMorphingDataEnabled;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainConfiguration::IsTangentDataEnabled() const
{
    return m_bTangentDataEnabled;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainConfiguration::IsLightingDataCompressionEnabled() const
{
    return m_bLightingDataCompressionEnabled;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainConfiguration::IsLowDetailNormalMappingEnabled() const
{
    return m_bLowDetailNormalMappingEnabled;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainConfiguration::GetNumPositionComponents(bool bHighDetail) const
{
    EE_UNUSED_ARG(bHighDetail);

    if (!m_bMorphingDataEnabled)
        return 3;
    return 4;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainConfiguration::GetNumTangentComponents(bool bHighDetail) const
{
    if (!m_bTangentDataEnabled)
        return 0;

    if (m_bLowDetailNormalMappingEnabled && !bHighDetail)
        return 0;

    if (m_bLightingDataCompressionEnabled)
        return 2;

    if (!m_bLightingDataCompressionEnabled)
        return 3;

    EE_FAIL("Invalid Terrain Configuration queried");
    return 0;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainConfiguration::GetNumNormalComponents(bool bHighDetail) const
{
    EE_UNUSED_ARG(bHighDetail);

    if (m_bLightingDataCompressionEnabled)
        return 2;

    if (!m_bLightingDataCompressionEnabled)
        return 3;

    EE_FAIL("Invalid Terrain Configuration queried");
    return 0;
}