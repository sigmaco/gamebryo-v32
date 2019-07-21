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
inline NiPhysXMaterialMetaData::NiPhysXMaterialMetaData() :
    m_fRestitution(0.0f),
    m_fStaticFriction(0.0f),
    m_fDynamicFriction(0.0f)
{

}

//--------------------------------------------------------------------------------------------------
inline NiPhysXMaterialMetaData::NiPhysXMaterialMetaData(float fRestitution, float fSFriction, 
    float fDFriction) :
    m_fRestitution(fRestitution),
    m_fStaticFriction(fSFriction),
    m_fDynamicFriction(fDFriction)
{

}

//--------------------------------------------------------------------------------------------------
inline NiPhysXMaterialMetaData::~NiPhysXMaterialMetaData()
{

}

//--------------------------------------------------------------------------------------------------
inline void NiPhysXMaterialMetaData::SetRestitution(float fRestitution)
{
    m_fRestitution = fRestitution;
}

//--------------------------------------------------------------------------------------------------
inline float NiPhysXMaterialMetaData::GetRestitution() const
{
    return m_fRestitution;
}

//--------------------------------------------------------------------------------------------------
inline void NiPhysXMaterialMetaData::SetStaticFriction(float fFriction)
{
    m_fStaticFriction = fFriction;
}

//--------------------------------------------------------------------------------------------------
inline float NiPhysXMaterialMetaData::GetStaticFriction() const
{
    return m_fStaticFriction;
}

//--------------------------------------------------------------------------------------------------
inline void NiPhysXMaterialMetaData::SetDynamicFriction(float fFriction)
{
    m_fDynamicFriction = fFriction;
}

//--------------------------------------------------------------------------------------------------
inline float NiPhysXMaterialMetaData::GetDynamicFriction() const
{
    return m_fDynamicFriction;
}

//--------------------------------------------------------------------------------------------------
inline NiPhysXMaterialMetaData& NiPhysXMaterialMetaData::operator=(
    const NiPhysXMaterialMetaData& kData)
{
    this->m_fDynamicFriction = kData.m_fDynamicFriction;
    this->m_fRestitution = kData.m_fRestitution;
    this->m_fStaticFriction = kData.m_fStaticFriction;

    return *this;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSectorPhysXSampleData::NiTerrainSectorPhysXSampleData() :
    m_usMatIndex1(0),
    m_usMatIndex2(0),
    m_bTesselation(false)
{
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSectorPhysXSampleData::NiTerrainSectorPhysXSampleData(NiUInt16 usMat1, 
    NiUInt16 usMat2, bool bTess) :
    m_usMatIndex1(usMat1),
    m_usMatIndex2(usMat2),
    m_bTesselation(bTess)
{
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSectorPhysXSampleData::~NiTerrainSectorPhysXSampleData()
{

}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorPhysXSampleData::SetMaterialIndex1(NiUInt16 usMatIndex) 
{
    m_usMatIndex1 = usMatIndex;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiTerrainSectorPhysXSampleData::GetMaterialIndex1() const
{
    return m_usMatIndex1;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorPhysXSampleData::SetMaterialIndex2(NiUInt16 usMatIndex)
{
    m_usMatIndex2 = usMatIndex;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiTerrainSectorPhysXSampleData::GetMaterialIndex2() const
{
    return m_usMatIndex2;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorPhysXSampleData::SetTesselation(bool bTess)
{
    m_bTesselation = bTess;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainSectorPhysXSampleData::GetTesselation() const
{
    return m_bTesselation;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSectorPhysXSampleData& NiTerrainSectorPhysXSampleData::operator=(
    const NiTerrainSectorPhysXSampleData& kData)
{
    this->m_bTesselation = kData.m_bTesselation;
    this->m_usMatIndex1 = kData.m_usMatIndex1;
    this->m_usMatIndex2 = kData.m_usMatIndex2;

    return *this;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSectorPhysXData::NiTerrainSectorPhysXData(NiUInt32 uiWidth, NiUInt32 uiHeight) :
    m_uiWidth(uiWidth),
    m_uiHeight(uiHeight),
    m_uiNumSamples(uiHeight * uiWidth)
{
    m_pkSamples = EE_ALLOC(NiTerrainSectorPhysXSampleData, m_uiNumSamples);
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSectorPhysXData::~NiTerrainSectorPhysXData()
{
    EE_FREE(m_pkSamples);
    m_pkSamples = NULL;
}

//--------------------------------------------------------------------------------------------------
