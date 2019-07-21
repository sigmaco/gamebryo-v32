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
inline NiUInt32 NiPSParticleSystem::GetMaxNumParticles() const
{
    return m_uiMaxNumParticles;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiPSParticleSystem::GetNumParticles() const
{
    return m_uiNumParticles;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSParticleSystem::GetLastTime() const
{
    return m_fLastTime;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSParticleSystem::HasLivingSpawner() const
{
    return (m_pfNextSpawnTimes != NULL);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSParticleSystem::HasColors() const
{
    return (m_pkColors != NULL);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSParticleSystem::HasRotations() const
{
    return (m_pfRotationAngles != NULL) && (m_pfRotationAngles != NULL);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSParticleSystem::HasRotationSpeeds() const
{
    return (m_pfRotationSpeeds != NULL);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSParticleSystem::HasRotationAxes() const
{
    return (m_pkRotationAxes != NULL);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSParticleSystem::HasAnimatedTextures() const
{
    return (m_pfVariance != NULL);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSParticleSystem::GetWorldSpace() const
{
    return m_bWorldSpace;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::SetWorldSpace(bool bWorldSpace)
{
    m_bWorldSpace = bWorldSpace;
}

//--------------------------------------------------------------------------------------------------
inline const NiTransform& NiPSParticleSystem::GetOriginalWorldTransform() const
{
    return m_kUnmodifiedWorld;
}

//--------------------------------------------------------------------------------------------------
inline NiPSSimulator* NiPSParticleSystem::GetSimulator() const
{
    return m_pkSimulator;
}

//--------------------------------------------------------------------------------------------------
inline NiPSBoundUpdater* NiPSParticleSystem::GetBoundUpdater() const
{
    return m_spBoundUpdater;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::SetBoundUpdater(
    NiPSBoundUpdater* pkBoundUpdater)
{
    m_spBoundUpdater = pkBoundUpdater;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiPSParticleSystem::GetEmitterCount() const
{
    return m_kEmitters.GetSize();
}

//--------------------------------------------------------------------------------------------------
inline NiPSEmitter* NiPSParticleSystem::GetEmitterAt(NiUInt32 uiIndex) const
{
    EE_ASSERT(uiIndex < m_kEmitters.GetSize());

    return m_kEmitters.GetAt(uiIndex);
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::AddEmitter(NiPSEmitter* pkEmitter)
{
    EE_ASSERT(pkEmitter);
    m_kEmitters.Add(pkEmitter);
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::RemoveEmitterAt(
    NiUInt32 uiIndex,
    bool bMaintainOrder)
{
    EE_ASSERT(uiIndex < m_kEmitters.GetSize());

    if (bMaintainOrder)
    {
        m_kEmitters.OrderedRemoveAt(uiIndex);
    }
    else
    {
        m_kEmitters.RemoveAt(uiIndex);
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::RemoveAllEmitters()
{
    m_kEmitters.RemoveAll();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiPSParticleSystem::GetSpawnerCount() const
{
    return m_kSpawners.GetSize();
}

//--------------------------------------------------------------------------------------------------
inline NiPSSpawner* NiPSParticleSystem::GetSpawnerAt(NiUInt32 uiIndex) const
{
    EE_ASSERT(uiIndex < m_kSpawners.GetSize());

    return m_kSpawners.GetAt(uiIndex);
}

//--------------------------------------------------------------------------------------------------
inline NiPSSpawner* NiPSParticleSystem::GetDeathSpawner() const
{
    return m_pkDeathSpawner;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::SetDeathSpawner(NiPSSpawner* pkDeathSpawner)
{
    m_pkDeathSpawner = pkDeathSpawner;
}

//--------------------------------------------------------------------------------------------------
inline NiPSSpawner* NiPSParticleSystem::GetLivingSpawner() const
{
    return m_pkLivingSpawner;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::SetLivingSpawner(NiPSSpawner* pkLivingSpawner)
{
    m_pkLivingSpawner = pkLivingSpawner;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::ForceSimulationToComplete()
{
    NiSyncArgs kSyncArgs;
    kSyncArgs.m_uiSubmitPoint = NiSyncArgs::SYNC_ANY;
    kSyncArgs.m_uiCompletePoint = NiSyncArgs::SYNC_ANY;
    CompleteModifiers(&kSyncArgs);
}

//--------------------------------------------------------------------------------------------------
inline NiPoint3* NiPSParticleSystem::GetPositions()
{
    return m_pkPositions;
}

//--------------------------------------------------------------------------------------------------
inline const NiPoint3* NiPSParticleSystem::GetPositions() const
{
    return m_pkPositions;
}

//--------------------------------------------------------------------------------------------------
inline NiPoint3* NiPSParticleSystem::GetVelocities()
{
    return m_pkVelocities;
}

//--------------------------------------------------------------------------------------------------
inline const NiPoint3* NiPSParticleSystem::GetVelocities() const
{
    return m_pkVelocities;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSParticleSystem::GetAges()
{
    return m_pfAges;
}

//--------------------------------------------------------------------------------------------------
inline const float* NiPSParticleSystem::GetAges() const
{
    return m_pfAges;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSParticleSystem::GetLifeSpans()
{
    return m_pfLifeSpans;
}

//--------------------------------------------------------------------------------------------------
inline const float* NiPSParticleSystem::GetLifeSpans() const
{
    return m_pfLifeSpans;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSParticleSystem::GetLastUpdateTimes()
{
    return m_pfLastUpdateTimes;
}

//--------------------------------------------------------------------------------------------------
inline const float* NiPSParticleSystem::GetLastUpdateTimes() const
{
    return m_pfLastUpdateTimes;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSParticleSystem::GetNextSpawnTimes()
{
    return m_pfNextSpawnTimes;
}

//--------------------------------------------------------------------------------------------------
inline const float* NiPSParticleSystem::GetNextSpawnTimes() const
{
    return m_pfNextSpawnTimes;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32* NiPSParticleSystem::GetFlags()
{
    return m_puiFlags;
}

//--------------------------------------------------------------------------------------------------
inline const NiUInt32* NiPSParticleSystem::GetFlags() const
{
    return m_puiFlags;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSParticleSystem::GetInitialSizes()
{
    return m_pfInitialSizes;
}

//--------------------------------------------------------------------------------------------------
inline const float* NiPSParticleSystem::GetInitialSizes() const
{
    return m_pfInitialSizes;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSParticleSystem::GetSizes()
{
    return m_pfSizes;
}

//--------------------------------------------------------------------------------------------------
inline const float* NiPSParticleSystem::GetSizes() const
{
    return m_pfSizes;
}

//--------------------------------------------------------------------------------------------------
inline NiRGBA* NiPSParticleSystem::GetColors()
{
    return m_pkColors;
}

//--------------------------------------------------------------------------------------------------
inline const NiRGBA* NiPSParticleSystem::GetColors() const
{
    return m_pkColors;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSParticleSystem::GetInitialRotationAngles()
{
    return m_pfInitialRotationAngles;
}

//--------------------------------------------------------------------------------------------------
inline const float* NiPSParticleSystem::GetInitialRotationAngles() const
{
    return m_pfInitialRotationAngles;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSParticleSystem::GetRotationAngles()
{
    return m_pfRotationAngles;
}

//--------------------------------------------------------------------------------------------------
inline const float* NiPSParticleSystem::GetRotationAngles() const
{
    return m_pfRotationAngles;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSParticleSystem::GetRotationSpeeds()
{
    return m_pfRotationSpeeds;
}

//--------------------------------------------------------------------------------------------------
inline const float* NiPSParticleSystem::GetRotationSpeeds() const
{
    return m_pfRotationSpeeds;
}

//--------------------------------------------------------------------------------------------------
inline NiPoint3* NiPSParticleSystem::GetRotationAxes()
{
    return m_pkRotationAxes;
}

//--------------------------------------------------------------------------------------------------
inline const NiPoint3* NiPSParticleSystem::GetRotationAxes() const
{
    return m_pkRotationAxes;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSParticleSystem::GetVariance()
{
    return m_pfVariance;
}

//--------------------------------------------------------------------------------------------------
inline const float* NiPSParticleSystem::GetVariance() const
{
    return m_pfVariance;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiPSParticleSystem::GetMaxValidSpawnerID() const
{
    return (NiUInt16) m_kActiveSpawners.GetSize();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiPSParticleSystem::GetSpawnerID(NiPSSpawner* pkSpawner)
{
    return (NiUInt16) m_kActiveSpawners.Add(pkSpawner);
}

//--------------------------------------------------------------------------------------------------
inline NiPSSpawner* NiPSParticleSystem::GetSpawnerFromID(NiUInt16 uiID) const
{
    return m_kActiveSpawners.GetAt(uiID);
}

//--------------------------------------------------------------------------------------------------
inline NiPSParticleSystem::AlignMethod NiPSParticleSystem::GetNormalMethod() const
{
    return m_eNormalMethod;
}

//--------------------------------------------------------------------------------------------------
inline NiPoint3 NiPSParticleSystem::GetNormalDirection() const
{
    return m_kNormalDirection;
}

//--------------------------------------------------------------------------------------------------
inline NiPSParticleSystem::AlignMethod NiPSParticleSystem::GetUpMethod() const
{
    return m_eUpMethod;
}

//--------------------------------------------------------------------------------------------------
inline NiPoint3 NiPSParticleSystem::GetUpDirection() const
{
    return m_kUpDirection;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::SetNormalMethod(const AlignMethod eMethod)
{
    m_eNormalMethod = eMethod;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::SetNormalMethod(const AlignMethod eMethod,
    const NiPoint3& kDirection)
{
    m_eNormalMethod = eMethod;
    m_kNormalDirection = kDirection;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::SetUpMethod(const AlignMethod eMethod)
{
    m_eUpMethod = eMethod;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::SetUpMethod(const AlignMethod eMethod, const NiPoint3& kDirection)
{
    m_eUpMethod = eMethod;
    m_kUpDirection = kDirection;
}

//--------------------------------------------------------------------------------------------------
inline NiPSKernelFloatKey* NiPSParticleSystem::GetSpawnRateKeys(NiUInt8& ucNumSpawnRateKeys) const
{
    ucNumSpawnRateKeys = m_ucNumSpawnRateKeys;
    return m_pkSpawnRateKeys;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSParticleSystem::GetPreRPIParticleSystem() const
{
    return m_bPreRPIParticleSystem;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSParticleSystem::SetPreRPIParticleSystem(const bool bValue)
{
    m_bPreRPIParticleSystem = bValue;
}
