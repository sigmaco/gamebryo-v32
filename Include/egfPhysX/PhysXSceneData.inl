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
inline bool egfPhysX::PhysXSceneData::GetSimulating() const
{
    return m_simulate;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::PhysXSceneData::GetSimActive() const
{
    return m_inSimFetch;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetSimActive(const efd::Bool isActive)
{
    m_inSimFetch = isActive;
}

//--------------------------------------------------------------------------------------------------
inline efd::TimeType egfPhysX::PhysXSceneData::GetCurrentPhysXTime() const
{
    return m_lastFetchTime;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetCurrentPhysXTime(const efd::TimeType& time)
{
    m_lastFetchTime = time;
    if (!m_simulate)
        m_nextFetchTime = m_lastFetchTime;
}

//--------------------------------------------------------------------------------------------------
inline efd::TimeType egfPhysX::PhysXSceneData::GetLastDelta() const
{
    return m_nextFetchTime - m_lastFetchTime;
}

//--------------------------------------------------------------------------------------------------
inline efd::Float32 egfPhysX::PhysXSceneData::GetTimeStep() const
{
    return m_timeStep;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetTimeStep(const efd::Float32& timeStep)
{
    m_timeStep = timeStep;
}

//--------------------------------------------------------------------------------------------------
inline efd::Float32 egfPhysX::PhysXSceneData::GetScaleWorldToPhysX() const
{
    return m_scaleWorldToPhysX;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetScaleWorldToPhysX(const efd::Float32& scaleWorldToPhysX)
{
    m_scaleWorldToPhysX = scaleWorldToPhysX;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 egfPhysX::PhysXSceneData::GetMaxSubSteps() const
{
    return m_maxSteps;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetMaxSubSteps(const efd::UInt32& maxSubSteps)
{
    m_maxSteps = maxSubSteps;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 egfPhysX::PhysXSceneData::GetNumSubSteps() const
{
    return m_numSubSteps;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetNumSubSteps(const efd::UInt32& numSubSteps)
{
    m_numSubSteps = numSubSteps;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::PhysXSceneData::GetFixedTimeStep() const
{
    return m_fixedTimeStep;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetFixedTimeStep(const efd::Bool& fixedTimeStep)
{
    m_fixedTimeStep = fixedTimeStep;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::PhysXSceneData::GetBlockOnFetch() const
{
    return m_blockOnFetch;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetBlockOnFetch(const efd::Bool& block)
{
    m_blockOnFetch = block;
}
    
//--------------------------------------------------------------------------------------------------
inline efd::Point3 egfPhysX::PhysXSceneData::GetGravity() const
{
    return m_gravity;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetGravity(const efd::Point3& gravity)
{
    m_gravity = gravity;
    
    if (m_pScene)
    {
        if (m_inSimFetch)
        {
            m_gravityHasChanged = true;
        }
        else
        {
            NxVec3 vector(gravity.x, gravity.y, gravity.z);
            m_pScene->setGravity(vector);
        }
    }
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::PhysXSceneData::GetHandleSimulation() const
{
    return m_handleSimulation;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetHandleSimulation(const efd::Bool handleSimulation)
{
    m_handleSimulation = handleSimulation;
}

//--------------------------------------------------------------------------------------------------
inline NxScene* egfPhysX::PhysXSceneData::GetPhysXScene() const
{
    return m_pScene;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::PhysXSceneData::GetOwnScene() const
{
    return m_ownScene;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetOwnScene(const efd::Bool ownScene)
{
    m_ownScene = ownScene;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::PhysXSceneData::GetEntityOwned() const
{
    return m_haveEntity;
}

//--------------------------------------------------------------------------------------------------
inline egfPhysX::PhysXSceneData::CollisionGroupPair::CollisionGroupPair(
    efd::UInt16 group1,
    efd::UInt16 group2)
{
    // To reduce the number of pairs we have to consider, always put the smaller number in group1
    if (group1 > group2)
    {
        m_group1 = group2;
        m_group2 = group1;
    }
    else
    {
        m_group1 = group1;
        m_group2 = group2;
    }
}
//--------------------------------------------------------------------------------------------------
inline bool egfPhysX::PhysXSceneData::CollisionGroupPair::operator==(
    const egfPhysX::PhysXSceneData::CollisionGroupPair& rhs) const
{
    return ((m_group1 == rhs.m_group1) && (m_group2 == rhs.m_group2));
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool egfPhysX::PhysXSceneData::GetUseHardware() const
{
    return m_useHardware;
}

//--------------------------------------------------------------------------------------------------
inline void egfPhysX::PhysXSceneData::SetUseHardware(const efd::Bool& useHardware)
{
    m_useHardware = useHardware;
}

