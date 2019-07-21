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
inline efd::ProcessorAffinity egfPhysX::SceneService::GetProcessorAffinity() const
{
    return m_processorAffinity;
}

//--------------------------------------------------------------------------------------------------
inline egfPhysX::PhysXSceneData* egfPhysX::SceneService::GetSceneData(
    const efd::utf8string& sceneName) const
{
    SceneMap::const_iterator iter = m_scenes.find(sceneName);
    if (iter != m_scenes.end())
        return iter->second;
    return NULL;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::GetSceneOwned(
    const efd::utf8string& sceneName,
    efd::Bool& isOwned) const
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        isOwned = pSceneData->GetOwnScene();
        return true;
    }
    isOwned = false;
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetSceneOwned(
    const efd::utf8string& sceneName,
    const efd::Bool isOwned)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetOwnScene(isOwned);
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::GetScaleFactor(
    const efd::utf8string& sceneName,
    efd::Float32& scale) const
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        scale = pSceneData->GetScaleWorldToPhysX();
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetScaleFactor(
    const efd::utf8string& sceneName,
    const efd::Float32 scale)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetScaleWorldToPhysX(scale);
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::GetHandleSimulate(
    const efd::utf8string& sceneName,
    efd::Bool& handleSimulate) const
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        handleSimulate = pSceneData->GetHandleSimulation();
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetHandleSimulate(
    const efd::utf8string& sceneName,
    const efd::Bool handleSimulate)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetHandleSimulation(handleSimulate);
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::StartSimulating(
    const efd::utf8string& sceneName,
    const efd::TimeType& time)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        DoStartSimulating(sceneName, pSceneData, time);
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::StopSimulating(const efd::utf8string& sceneName)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->StopSimulating();
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::StopSimulating(const egf::Entity* pSceneEntity)
{
    PhysXSceneData* pSceneData = EE_DYNAMIC_CAST(
        PhysXSceneData, 
        pSceneEntity->FindBuiltinModel(egf::kFlatModelID_PhysXModelLibrary_PhysXScene));
    if (pSceneData)
    {
        pSceneData->StopSimulating();
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::TimeType egfPhysX::SceneService::GetCurrentPhysXTime(const efd::utf8string& sceneName)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        return pSceneData->GetCurrentPhysXTime();
    }
    return ms_kInvalidSimulationTime;
}
//--------------------------------------------------------------------------------------------------
inline efd::TimeType egfPhysX::SceneService::GetCurrentPhysXTime(const egf::Entity* pSceneEntity)
{
    PhysXSceneData* pSceneData = EE_DYNAMIC_CAST(
        PhysXSceneData, 
        pSceneEntity->FindBuiltinModel(egf::kFlatModelID_PhysXModelLibrary_PhysXScene));
    if (pSceneData)
    {
        return pSceneData->GetCurrentPhysXTime();
    }
    return ms_kInvalidSimulationTime;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::GetDoFixedStep(
    const efd::utf8string& sceneName,
    efd::Bool& isFixedStep) const
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        isFixedStep = pSceneData->GetFixedTimeStep();
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetDoFixedStep(
    const efd::utf8string& sceneName,
    const efd::Bool isFixedStep)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetFixedTimeStep(isFixedStep);
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::GetTimestep(
    const efd::utf8string& sceneName,
    efd::Float32& step) const
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        step = pSceneData->GetTimeStep();
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetTimestep(
    const efd::utf8string& sceneName,
    const efd::Float32 step)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetTimeStep(step);
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::GetMaxSubSteps(
    const efd::utf8string& sceneName,
    efd::UInt32& maxSteps) const
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        maxSteps = pSceneData->GetMaxSubSteps();
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetMaxSubSteps(
    const efd::utf8string& sceneName,
    const efd::UInt32 maxSteps)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetMaxSubSteps(maxSteps);
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::GetNumSubSteps(
    const efd::utf8string& sceneName,
    efd::UInt32& numSubSteps) const
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        numSubSteps = pSceneData->GetNumSubSteps();
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetNumSubSteps(
    const efd::utf8string& sceneName,
    const efd::UInt32 numSubSteps)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetNumSubSteps(numSubSteps);
        return true;
    }
    return false;
}//-----------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::GetBlockOnFetch(
    const efd::utf8string& sceneName,
    efd::Bool& blockOnFetch) const
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        blockOnFetch = pSceneData->GetBlockOnFetch();
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetBlockOnFetch(
    const efd::utf8string& sceneName,
    const efd::Bool blockOnFetch)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetBlockOnFetch(blockOnFetch);
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::GetGravity(
    const efd::utf8string& sceneName,
    efd::Point3& gravity) const
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        gravity = pSceneData->GetGravity();
        return true;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetGravity(
    const efd::utf8string& sceneName,
    const efd::Point3 gravity)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetGravity(gravity);
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::IsSimulationActive(
    const efd::utf8string& sceneName,
    efd::Bool& isActive) const
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        isActive = pSceneData->GetSimActive();
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline void egfPhysX::SceneService::SetSimulationActive(
    const efd::utf8string& sceneName,
    efd::Bool isActive)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetSimActive(isActive);
    }
}
//--------------------------------------------------------------------------------------------------
inline efd::TimeType egfPhysX::SceneService::GetSimulationTime(const efd::utf8string& sceneName)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        return m_simulationTime;
    }
    return ms_kInvalidSimulationTime;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetCurrentPhysXTime(
    const efd::utf8string& sceneName,
    efd::TimeType time)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetCurrentPhysXTime(time);

        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::GetGroupCollisionFlag(
    const efd::utf8string& sceneName,
    efd::UInt16 group1,
    efd::UInt16 group2,
    efd::Bool& isEnabled)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        return pSceneData->GetGroupCollisionFlag(group1, group2, isEnabled);
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::GetGroupCollisionFlag(
    const egf::Entity* pSceneEntity,
    efd::UInt16 group1,
    efd::UInt16 group2,
    efd::Bool& isEnabled)
{
    PhysXSceneData* pSceneData = EE_DYNAMIC_CAST(
        PhysXSceneData, 
        pSceneEntity->FindBuiltinModel(egf::kFlatModelID_PhysXModelLibrary_PhysXScene));
    if (pSceneData)
    {
        return pSceneData->GetGroupCollisionFlag(group1, group2, isEnabled);
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetGroupCollisionFlag(
    const efd::utf8string& sceneName,
    efd::UInt16 group1,
    efd::UInt16 group2,
    efd::Bool isEnabled)
{
    PhysXSceneData* pSceneData = GetSceneData(sceneName);
    if (pSceneData)
    {
        pSceneData->SetGroupCollisionFlag(group1, group2, isEnabled);
        return true;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::SceneService::SetGroupCollisionFlag(
    const egf::Entity* pSceneEntity,
    efd::UInt16 group1,
    efd::UInt16 group2,
    efd::Bool isEnabled)
{
    PhysXSceneData* pSceneData = EE_DYNAMIC_CAST(
        PhysXSceneData, 
        pSceneEntity->FindBuiltinModel(egf::kFlatModelID_PhysXModelLibrary_PhysXScene));
    if (pSceneData)
    {
        pSceneData->SetGroupCollisionFlag(group1, group2, isEnabled);
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
inline void egfPhysX::SceneService::Simulate()
{
    Simulate(false);
}

//------------------------------------------------------------------------------------------------
inline void egfPhysX::SceneService::FetchResults()
{
    FetchResults(false);
}

//------------------------------------------------------------------------------------------------
