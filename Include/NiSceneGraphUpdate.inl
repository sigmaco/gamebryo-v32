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
inline bool NiSceneGraphUpdate::IsObjectStateDirty(const NiUInt32 uiState)
{
    return (uiState != OS_CLEAN);
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdate::IsReady() const
{
    return m_bIsReady;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdate::IsDirty() const
{
    return m_bIsDirty;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiSceneGraphUpdate::GetInstanceId() const
{
    return m_uiInstanceId;
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdate::SetInstanceId(const NiUInt32 uiInstanceId)
{
    m_uiInstanceId = uiInstanceId;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdate* NiSceneGraphUpdate::GetInstance()
{
    return ms_pkThis;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateObjectPtr NiSceneGraphUpdate::GetObject(
    const NiSceneGraphUpdateObjectId& kId) const
{
    NiSceneGraphUpdateObjectPtr spObject;
    m_kObjects.GetAt(kId, spObject);
    return spObject;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateObjectId NiSceneGraphUpdate::GetObjectId(const NiObject* pkObject) const
{
    NiSceneGraphUpdateObjectId kId = NiSceneGraphUpdateObjectId::NULL_OBJECT_ID;
    m_kNiObjects.GetAt(pkObject, kId);
    return kId;
}

//--------------------------------------------------------------------------------------------------
inline NiNode* NiSceneGraphUpdate::GetRootNode()
{
    NiSceneGraphUpdateObjectId kId = NiSceneGraphUpdateObjectId::NULL_OBJECT_ID;
    m_kRootNodes.GetAt(GetInstanceId(), kId);
    NiSceneGraphUpdateObject* pkObject = GetObject(kId);
    if (pkObject && pkObject->GetObject())
    {
        return NiDynamicCast(NiNode, pkObject->GetObject());
    }

    return NULL;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateObjectId NiSceneGraphUpdate::GetRootNodeId() const
{
    NiSceneGraphUpdateObjectId kId = NiSceneGraphUpdateObjectId::NULL_OBJECT_ID;
    m_kRootNodes.GetAt(m_uiInstanceId, kId);
    return kId;
}

//--------------------------------------------------------------------------------------------------
inline NiCamera* NiSceneGraphUpdate::GetActiveCamera()
{
    NiSceneGraphUpdateObjectId kId = NiSceneGraphUpdateObjectId::NULL_OBJECT_ID;
    m_kActiveCameras.GetAt(GetInstanceId(), kId);
    NiSceneGraphUpdateObject* pkObject = GetObject(kId);
    if (pkObject && pkObject->GetObject())
    {
        return NiDynamicCast(NiCamera, pkObject->GetObject());
    }

    return NULL;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateObjectId NiSceneGraphUpdate::GetActiveCameraId() const
{
    NiSceneGraphUpdateObjectId kId = NiSceneGraphUpdateObjectId::NULL_OBJECT_ID;
    m_kActiveCameras.GetAt(m_uiInstanceId, kId);
    return kId;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateSettings& NiSceneGraphUpdate::GetSettings()
{
    return m_kSettings;
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdate::SetSceneDirty()
{
    m_bIsDirty = true;
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdate::SetSceneClean()
{
    m_bIsDirty = false;
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdate::SetRootNode(const NiSceneGraphUpdateObjectId& kId)
{
    m_kRootNodes.SetAt(kId.GetInstanceId(), kId);
    if (m_pfnSceneReadyCallback)
    {
        m_pfnSceneReadyCallback(m_pkSceneReadyCallbackParam);
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdate::SetActiveCamera(const NiSceneGraphUpdateObjectId& kId)
{
    m_kActiveCameras.SetAt(kId.GetInstanceId(), kId);
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdate::SetSceneReadyCallback(
    NISCENEGRAPHUPDATE_SCENEREADYCALLBACK pfnSceneReadyCallback, void* pkParam)
{
    m_pfnSceneReadyCallback = pfnSceneReadyCallback;
    m_pkSceneReadyCallbackParam = pkParam;
}

//--------------------------------------------------------------------------------------------------