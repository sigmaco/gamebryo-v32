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
inline NiSPWorkflowManager* ecr::SceneGraphService::GetWorkflowManager() const
{
    return m_spWorkflowManager;
}

//------------------------------------------------------------------------------------------------
inline NiTexturePalette* ecr::SceneGraphService::GetTexturePalette() const
{
    return m_spSceneGraphCache->GetTexturePalette();
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphCache* ecr::SceneGraphService::GetSceneGraphCache() const
{
    return m_spSceneGraphCache;
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::SetDataPath(const char* path)
{
    m_strDataPath = path;
}

//------------------------------------------------------------------------------------------------
inline const NiFixedString& ecr::SceneGraphService::GetDataPath() const
{
    return m_strDataPath;
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphService::SceneGraphData* ecr::SceneGraphService::GetEntityData(
    const egf::Entity* pEntity) const
{
    // Already known? If so, return.
    efd::map<egf::Entity*, SceneGraphDataPtr>::const_iterator iter = 
        m_entityData.find(const_cast<egf::Entity*>(pEntity));

    if (iter != m_entityData.end())
        return iter->second;

    return NULL;
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::AddToUpdate(SceneGraphData* pData)
{
    if (pData->m_updateIndex == SceneGraphData::kInvalidUpdateIndex)
    {
        pData->m_updateIndex = static_cast<efd::UInt32>(m_toUpdate.size());
        m_toUpdate.push_back(pData);
    }
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::RemoveFromUpdate(SceneGraphData* pData)
{
    if (pData->m_updateIndex != SceneGraphData::kInvalidUpdateIndex)
    {
        SceneGraphData* pBackData = m_toUpdate.back();
        pBackData->m_updateIndex = pData->m_updateIndex;
        m_toUpdate[pBackData->m_updateIndex] = pBackData;
        m_toUpdate.pop_back();

        pData->m_updateIndex = SceneGraphData::kInvalidUpdateIndex;
    }
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::AddToUpdateOnce(SceneGraphData* pData)
{
    if (m_toUpdateOnce.find(pData) == m_toUpdateOnce.end())
        m_toUpdateOnce.push_back(pData);
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::RemoveFromUpdateOnce(SceneGraphData* pData)
{
    efd::vector<SceneGraphData*>::iterator updateOnceIter = m_toUpdateOnce.find(pData);
    if (updateOnceIter != m_toUpdateOnce.end())
    {
        m_toUpdateOnce.erase(updateOnceIter);
    }
}

inline void ecr::SceneGraphService::SwapUpdateOrder(SceneGraphData* pData1, SceneGraphData* pData2)
{
    efd::UInt32 index1 = pData1->m_updateIndex;
    if (index1 == SceneGraphData::kInvalidUpdateIndex)
        return;

    efd::UInt32 index2 = pData2->m_updateIndex;
    if (index2 == SceneGraphData::kInvalidUpdateIndex)
        return;
        
    m_toUpdate[index1] = pData2;
    pData2->m_updateIndex = index1;
    
    m_toUpdate[index2] = pData1;
    pData1->m_updateIndex = index2;
}

//------------------------------------------------------------------------------------------------
inline NiAVObject* ecr::SceneGraphService::SceneGraphData::GetSceneGraph()
{
    if (m_objects.size() > 0)
        return NiDynamicCast(NiAVObject, m_objects[0]);

    return NULL;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecr::SceneGraphService::SceneGraphData::IsEntity() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)IS_ENTITY);
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::SceneGraphData::SetIsEntity(const efd::Bool bIsEntity)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags, (efd::UInt16)IS_ENTITY, bIsEntity);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecr::SceneGraphService::SceneGraphData::IsDynamic() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)IS_DYNAMIC);
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::SceneGraphData::SetIsDynamic(const efd::Bool bIsDynamic)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags, (efd::UInt16)IS_DYNAMIC, bIsDynamic);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecr::SceneGraphService::SceneGraphData::IsAssetShared() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)IS_ASSET_SHARED);
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::SceneGraphData::SetIsAssetShared(
    const efd::Bool bIsAssetShared)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags, (efd::UInt16)IS_ASSET_SHARED, bIsAssetShared);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecr::SceneGraphService::SceneGraphData::IsRendered() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)IS_RENDERED);
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::SceneGraphData::SetIsRendered(const efd::Bool bIsRendered)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags, (efd::UInt16)IS_RENDERED, bIsRendered);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecr::SceneGraphService::SceneGraphData::IsAssetExternal() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)IS_ASSET_EXTERNAL);
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::SceneGraphData::SetIsAssetExternal(
    const efd::Bool bIsAssetExternal)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags,
        (efd::UInt16)IS_ASSET_EXTERNAL, bIsAssetExternal);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecr::SceneGraphService::SceneGraphData::IsRenderable() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)IS_RENDERABLE);
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::SceneGraphData::SetIsRenderable(const efd::Bool bIsRenderable)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags, (efd::UInt16)IS_RENDERABLE, bIsRenderable);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecr::SceneGraphService::SceneGraphData::IsWaitingToSendEvent() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)IS_WAITING_TO_SEND_EVENT);
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::SceneGraphData::SetIsWaitingToSendEvent(
    const efd::Bool waiting)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags,
        (efd::UInt16)IS_WAITING_TO_SEND_EVENT, waiting);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecr::SceneGraphService::SceneGraphData::IsInWorld() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)IS_IN_WORLD);
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::SceneGraphData::SetIsInWorld(const efd::Bool inWorld)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags,
        (efd::UInt16)IS_IN_WORLD, inWorld);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecr::SceneGraphService::SceneGraphData::DoPoseUpdate() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)DO_POSE_UPDATE);
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphService::SceneGraphData::SetDoPoseUpdate(const efd::Bool updatePose)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags,
        (efd::UInt16)DO_POSE_UPDATE, updatePose);
}

//------------------------------------------------------------------------------------------------
inline NiAVObject* ecr::SceneGraphService::AttachedSceneGraphData::GetSceneGraph()
{
    if (m_objects.size() > 0)
        return NiDynamicCast(NiAVObject, m_objects[0]);

    return NULL;
}

//------------------------------------------------------------------------------------------------


