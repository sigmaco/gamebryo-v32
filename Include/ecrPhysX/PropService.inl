// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2007 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ecrPhysX::PropService::GetNumProps(const egf::EntityID& eid)
{
    ecrPhysX::PropService::PropData* pPropData = NULL;
    m_props.find(eid, pPropData);
    if (!pPropData)
        return 0;
    return (efd::UInt32)pPropData->m_pProps.size();
}

//------------------------------------------------------------------------------------------------
inline NiPhysXProp* ecrPhysX::PropService::GetPropAt(const egf::EntityID& eid,
                                                     efd::UInt32 index)
{
    ecrPhysX::PropService::PropData* pPropData = NULL;
    m_props.find(eid, pPropData);
    if (!pPropData ||
        (index >= pPropData->m_pProps.size()))
        return NULL;
    return pPropData->m_pProps[index];
}

//------------------------------------------------------------------------------------------------
inline NiPhysXScene* ecrPhysX::PropService::GetScene(const efd::utf8string& sceneName)
{
    SceneData* pSceneData = NULL;
    m_sceneNames.find(sceneName, pSceneData);
    if (!pSceneData)
        return NULL;
    return pSceneData->m_spScene;
}

//------------------------------------------------------------------------------------------------
inline NiPhysXScene* ecrPhysX::PropService::GetPropCurrentScene(const egf::EntityID& eid)
{
    ecrPhysX::PropService::PropData* pPropData = NULL;
    m_props.find(eid, pPropData);
    if (!pPropData)
        return NULL;
    return GetScene(pPropData->m_currentSceneName);
}

//------------------------------------------------------------------------------------------------
inline ecrPhysX::PropService::SceneData* ecrPhysX::PropService::GetSceneData(
    const efd::utf8string& sceneName,
    efd::Bool createData)
{
    // Make sure we return something invalid if the lookup fails
    SceneData* pSceneData = NULL;
    m_sceneNames.find(sceneName, pSceneData);
    if (createData && !pSceneData)
    {
        // SceneData is initialized with an entity ID of kENTITY_INVALID with the expectation
        // that the entity ID will be supplied when HandleSceneAddedMessage is called and the
        // NxScene is actually added.
        pSceneData = EE_NEW SceneData(sceneName);
        // Add the scene to name mapping
        m_sceneNames[sceneName] = pSceneData;
    }
    return pSceneData;
}

//------------------------------------------------------------------------------------------------
inline void ecrPhysX::PropService::UpdateSources()
{
    UpdateSources(false);
}

//------------------------------------------------------------------------------------------------
inline void ecrPhysX::PropService::UpdateDestinations()
{
    UpdateDestinations(false);
}
