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

namespace egfPhysX
{
//--------------------------------------------------------------------------------------------------
inline const efd::utf8string& SceneMessage::GetSceneName() const
{
    return m_sceneName;
}
//--------------------------------------------------------------------------------------------------
inline void SceneMessage::SetSceneName(const efd::utf8string& sceneName)
{
    m_sceneName = sceneName;
}
//--------------------------------------------------------------------------------------------------
inline NxScene* SceneMessage::GetScene() const
{
    return m_pScene;
}
//--------------------------------------------------------------------------------------------------
inline void SceneMessage::SetScene(NxScene* pScene)
{
    m_pScene = pScene;
}
////--------------------------------------------------------------------------------------------------
//inline const egf::EntityPtr SceneMessage::GetEntity() const
//{
//    return m_spEntity;
//}
////--------------------------------------------------------------------------------------------------
//inline void SceneMessage::SetEntity(egf::EntityPtr spEntity)
//{
//    m_spEntity = spEntity;
//}
//--------------------------------------------------------------------------------------------------
inline efd::IBasePtr SceneMessage::FactoryMethod()
{
    return EE_NEW SceneMessage();
}
//--------------------------------------------------------------------------------------------------
inline const efd::utf8string& SimulationMessage::GetSceneName() const
{
    return m_sceneName;
}
//--------------------------------------------------------------------------------------------------
inline void SimulationMessage::SetSceneName(const efd::utf8string& sceneName)
{
    m_sceneName = sceneName;
}
//--------------------------------------------------------------------------------------------------
inline const efd::TimeType& SimulationMessage::GetTime() const
{
    return m_time;
}
//--------------------------------------------------------------------------------------------------
inline void SimulationMessage::SetTime(const efd::TimeType& time)
{
    m_time = time;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool SimulationMessage::GetBlockOnFetch() const
{
    return m_blockOnFetch;
}
//--------------------------------------------------------------------------------------------------
inline void SimulationMessage::SetBlockOnFetch(efd::Bool blockOnFetch)
{
    m_blockOnFetch = blockOnFetch;
}
//--------------------------------------------------------------------------------------------------
}; // namespace egfPhysX
