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
inline efd::Bool ecr::LightService::IsEntityLight(const egf::EntityID& entityID) const
{
    return m_entityLightMap.find(entityID) != m_entityLightMap.end();
}
//--------------------------------------------------------------------------------------------------
inline void ecr::LightService::EnableShadowing(bool bEnable)
{
    if (NiShadowManager::GetActive() != bEnable)
    {
        NiShadowManager::SetActive(bEnable);

        if (m_spSceneGraphService)
        {
            m_spSceneGraphService->ForceMaterialUpdate();
        }
    }
}
//--------------------------------------------------------------------------------------------------
inline void ecr::LightService::SetMaxAmbientLightsPerObject(efd::UInt8 uiLimit)
{
    m_uiMaxAmbientLightsPerObject = uiLimit;
}
//-------------------------------------------------------------------------------------------------
inline void ecr::LightService::SetUsePrecomputedLighting(efd::Bool bUsePrecomputedLighting)
{
    if (bUsePrecomputedLighting != m_bUsePrecomputedLighting)
    {
        m_bUsePrecomputedLighting = bUsePrecomputedLighting;
        RelightScene(false);
    }
}
//-------------------------------------------------------------------------------------------------
inline void ecr::LightService::SetMaxDirectionalLightsPerObject(efd::UInt8 uiLimit)
{
    m_uiMaxDirectionalLightsPerObject = uiLimit;
}
//--------------------------------------------------------------------------------------------------
inline void ecr::LightService::SetMaxPointLightsPerObject(efd::UInt8 uiLimit)
{
    m_uiMaxPointLightsPerObject = uiLimit;
}
//--------------------------------------------------------------------------------------------------
inline void ecr::LightService::SetMaxSpotLightsPerObject(efd::UInt8 uiLimit)
{
    m_uiMaxSpotLightsPerObject = uiLimit;
}
//--------------------------------------------------------------------------------------------------
inline efd::UInt8 ecr::LightService::GetMaxAmbientLightsPerObject() const
{
    return m_uiMaxAmbientLightsPerObject;
}
//-------------------------------------------------------------------------------------------------
inline efd::Bool ecr::LightService::GetUsePrecomputedLighting() const
{
    return m_bUsePrecomputedLighting;
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt8 ecr::LightService::GetMaxDirectionalLightsPerObject() const
{
    return m_uiMaxDirectionalLightsPerObject;
}
//--------------------------------------------------------------------------------------------------
inline efd::UInt8 ecr::LightService::GetMaxPointLightsPerObject() const
{
    return m_uiMaxPointLightsPerObject;
}
//--------------------------------------------------------------------------------------------------
inline efd::UInt8 ecr::LightService::GetMaxSpotLightsPerObject() const
{
    return m_uiMaxSpotLightsPerObject;
}
//--------------------------------------------------------------------------------------------------
inline void ecr::LightService::SwapLights(unsigned int i, unsigned int j)
{
    LightData* pTemp;

    pTemp = m_lightList[i];
    m_lightList[i] = m_lightList[j];
    m_lightList[j] = pTemp;
}
//--------------------------------------------------------------------------------------------------
inline void ecr::LightService::SwapReceivers(unsigned int i, unsigned int j)
{
    ReceiverData* pTemp;

    pTemp = m_receiverList[i];
    m_receiverList[i] = m_receiverList[j];
    m_receiverList[j] = pTemp;
}
//--------------------------------------------------------------------------------------------------
inline NiLight* ecr::LightService::GetLightFromEntity(egf::EntityID id)
{
    LightData* pTemp;

    if (m_entityLightMap.find(id, pTemp))
        return pTemp->m_spLight;
    else
        return 0;
}
//--------------------------------------------------------------------------------------------------
// ecr::LightService::ObjectData
//--------------------------------------------------------------------------------------------------
inline ecr::LightService::BaseObjectData::BaseObjectData()
{
}
//--------------------------------------------------------------------------------------------------
inline ecr::LightService::BaseObjectData::BaseObjectData(
    const NiPoint3& position,
    float radius,
    const egf::EntityID& entityID)
    : m_position(position)
    , m_projectedCenter(0.0f)
    , m_radius(radius)
    , m_entityID(entityID)
{
}
//--------------------------------------------------------------------------------------------------
inline bool ecr::LightService::LightPriority::operator < (const LightPriority& kIn) const
{
    return m_fPriority < kIn.m_fPriority;
}
//--------------------------------------------------------------------------------------------------
inline bool ecr::LightService::LightPriority::operator > (const LightPriority& kIn) const
{
    return m_fPriority > kIn.m_fPriority;
}
//--------------------------------------------------------------------------------------------------
inline bool ecr::LightService::BaseObjectData::operator == (const BaseObjectData& kIn) const
{
    return m_entityID == kIn.m_entityID;
}
//--------------------------------------------------------------------------------------------------
inline void ecr::LightService::BaseObjectData::DumpData()
{
    efd::utf8string msg;
    msg.sprintf("Object Data (x,y,z) = (%f,%f,%f) pc = %f r = %f pc-r = %f\n",
        m_position.x, m_position.y, m_position.z, m_projectedCenter, m_radius,
        m_projectedCenter - m_radius);

    EE_OUTPUT_DEBUG_STRING(msg.c_str());
}
//--------------------------------------------------------------------------------------------------
inline bool ecr::LightService::BaseObjectData::ObjectFurther(
    const BaseObjectData* lhs,
    const BaseObjectData* rhs)
{
    return lhs->m_projectedCenter - lhs->m_radius >
            rhs->m_projectedCenter - rhs->m_radius;
}
//--------------------------------------------------------------------------------------------------
inline ecr::LightService::ReceiverData*
    ecr::LightService::FindReceiverData(const egf::EntityID& entityID)
{
    efd::map<egf::EntityID, ReceiverData*>::iterator itor = m_entityReceiverMap.find(entityID);

    if (itor != m_entityReceiverMap.end())
    {
        return itor->second;
    }
    else
    {
        return NULL;
    }
}
//-------------------------------------------------------------------------------------------------
// ecr::LightService::LightData
//-------------------------------------------------------------------------------------------------
inline ecr::LightService::LightData::LightData()
{
}
//-------------------------------------------------------------------------------------------------
inline ecr::LightService::LightData::LightData(
    const NiPoint3& position, float radius, const egf::EntityID& entityID) : 
    BaseObjectData(position, radius, entityID),
    m_spLight(NULL)
{
}
//-------------------------------------------------------------------------------------------------
// ecr::LightService::ReceiverData
//-------------------------------------------------------------------------------------------------
inline ecr::LightService::ReceiverData::ReceiverData()
{
}
//-------------------------------------------------------------------------------------------------
inline ecr::LightService::ReceiverData::ReceiverData(
    const NiPoint3& position, float radius, const egf::EntityID& entityID) : 
    BaseObjectData(position, radius, entityID),
    m_spNode(NULL)
{
}
//-------------------------------------------------------------------------------------------------
