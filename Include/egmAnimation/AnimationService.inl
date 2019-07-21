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


namespace egmAnimation
{

//------------------------------------------------------------------------------------------------
inline KFMCache* AnimationService::GetKFMCache() const
{
    return m_spKFMCache;
}

//------------------------------------------------------------------------------------------------
inline efd::Category AnimationService::GetMessageCategory() const
{
    return m_actorMessageCategory;
}

//------------------------------------------------------------------------------------------------
inline NiActorManager* AnimationService::GetActorManager(const egf::EntityID& entityID)
{
    ActorEntry* pEntry = NULL;
    if (!ContainsEntity(entityID, pEntry))
        return NULL;

    return pEntry->m_spActorManager;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool AnimationService::ContainsEntity(
    const egf::EntityID& entityID,
    ActorEntry*& pActorEntry)
{
    ActorMap::iterator itor = m_entityData.find(entityID);
    if (itor != m_entityData.end())
    {
        pActorEntry = itor->second;
        return true;
    }

    return false;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool AnimationService::SetTargetAnimation(
    const egf::EntityID& entityID,
    NiActorManager::SequenceID sequenceID)
{
    ActorEntry* pEntry;
    if (!ContainsEntity(entityID, pEntry))
        return false;

    pEntry->m_currentSequenceID = sequenceID;

    NiActorManager* pActorManager = pEntry->m_spActorManager;
    if (!pActorManager)
        return false;

    return pActorManager->SetTargetAnimation(sequenceID);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool AnimationService::SetTargetAnimation(
    const egf::EntityID& entityID,
    const efd::utf8string& sequenceName)
{
    ActorEntry* pEntry;
    if (!ContainsEntity(entityID, pEntry))
        return false;

    AssetData* pAssetData = pEntry->m_spAssetData;
    if (!pAssetData)
        return false;

    NiActorManager::SequenceID sequenceID = pAssetData->GetSequenceID(sequenceName);
    if (sequenceID == NiActorManager::INVALID_SEQUENCE_ID)
        return false;

    pEntry->m_currentSequenceID = sequenceID;

    NiActorManager* pActorManager = pEntry->m_spActorManager;
    if (!pActorManager)
        return false;

    return pActorManager->SetTargetAnimation(sequenceID);
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string AnimationService::GetCurrentAnimation(const egf::EntityID& entityID)
{
    ActorEntry* pEntry;
    if (!ContainsEntity(entityID, pEntry))
        return efd::utf8string::NullString();

    AssetData* pAssetData = pEntry->m_spAssetData;
    if (!pAssetData)
        return efd::utf8string::NullString();

    if (!pEntry->m_spActorManager)
        return efd::utf8string::NullString();

    NiActorManager::SequenceID currId = pEntry->m_spActorManager->GetCurAnimation();
    if (currId == NiActorManager::INVALID_SEQUENCE_ID)
        return efd::utf8string::NullString();
    else
        return pAssetData->GetSequenceName(currId);
}

//------------------------------------------------------------------------------------------------
inline NiActorManager::SequenceID AnimationService::GetCurrentAnimationId(
    const egf::EntityID& entityID)
{
    NiActorManager* pActorManager = GetActorManager(entityID);
    if (!pActorManager)
        return NiActorManager::INVALID_SEQUENCE_ID;

    return pActorManager->GetCurAnimation();
}

//------------------------------------------------------------------------------------------------
inline NiActorManager::SequenceID AnimationService::GetNextAnimationId(
    const egf::EntityID& entityID)
{
    NiActorManager* pActorManager = GetActorManager(entityID);
    if (!pActorManager)
        return NiActorManager::INVALID_SEQUENCE_ID;

    return pActorManager->GetNextAnimation();
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string AnimationService::GetNextAnimation(const egf::EntityID& entityID)
{
    ActorEntry* pEntry;
    if (!ContainsEntity(entityID, pEntry))
        return efd::utf8string::NullString();

    AssetData* pAssetData = pEntry->m_spAssetData;
    if (!pAssetData)
        return efd::utf8string::NullString();

    if (!pEntry->m_spActorManager)
        return efd::utf8string::NullString();

    NiActorManager::SequenceID currId = pEntry->m_spActorManager->GetNextAnimation();
    if (currId == NiActorManager::INVALID_SEQUENCE_ID)
        return efd::utf8string::NullString();
    else
        return pAssetData->GetSequenceName(currId);
}

//------------------------------------------------------------------------------------------------
inline NiActorManager::SequenceID AnimationService::GetTargetAnimationId(
    const egf::EntityID& entityID)
{
    NiActorManager* pActorManager = GetActorManager(entityID);
    if (!pActorManager)
        return NiActorManager::INVALID_SEQUENCE_ID;

    return pActorManager->GetTargetAnimation();
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string AnimationService::GetTargetAnimation(const egf::EntityID& entityID)
{
    ActorEntry* pEntry;
    if (!ContainsEntity(entityID, pEntry))
        return efd::utf8string::NullString();

    AssetData* pAssetData = pEntry->m_spAssetData;
    if (!pAssetData)
        return efd::utf8string::NullString();

    if (!pEntry->m_spActorManager)
        return efd::utf8string::NullString();

    NiActorManager::SequenceID currId = pEntry->m_spActorManager->GetTargetAnimation();
    if (currId == NiActorManager::INVALID_SEQUENCE_ID)
        return efd::utf8string::NullString();
    else
        return pAssetData->GetSequenceName(currId);
}

//------------------------------------------------------------------------------------------------
inline NiActorManager::TransitionState AnimationService::GetTransitionState(
    const egf::EntityID& entityID)
{
    NiActorManager* pActorManager = GetActorManager(entityID);
    if (!pActorManager)
        return NiActorManager::NO_TRANSITION;

    return pActorManager->GetTransitionState();
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string AnimationService::GetAnimationNameFromId(
    const egf::EntityID& entityID,
    NiActorManager::SequenceID id)
{
    ActorEntry* pEntry;
    if (!ContainsEntity(entityID, pEntry) || id == NiActorManager::INVALID_SEQUENCE_ID)
        return efd::utf8string::NullString();

    if (!pEntry->m_spAssetData)
        return efd::utf8string::NullString();

    return pEntry->m_spAssetData->GetSequenceName(id);
}

//------------------------------------------------------------------------------------------------
inline NiActorManager::SequenceID AnimationService::GetAnimationIdFromName(
    const egf::EntityID& entityID, const efd::utf8string& name)
{
    ActorEntry* pEntry;
    if (!ContainsEntity(entityID, pEntry))
        return NiActorManager::INVALID_SEQUENCE_ID;

    if (!pEntry->m_spAssetData)
        return NiActorManager::INVALID_SEQUENCE_ID;

    return pEntry->m_spAssetData->GetSequenceID(name);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool AnimationService::ClearRegisteredTextKeys(const egf::EntityID& entityID)
{
    NiActorManager* pActorManager = GetActorManager(entityID);
    if (!pActorManager)
        return false;

    pActorManager->ClearAllRegisteredCallbacks();

    return true;
}

//------------------------------------------------------------------------------------------------
inline void AnimationService::GetActiveSequences(
    const egf::EntityID& entityID,
    efd::vector<efd::utf8string>& sequences)
{
    NiActorManager* pActorManager = GetActorManager(entityID);
    if (!pActorManager)
        return;

    NiControllerManager* pCtrlMgr = pActorManager->GetControllerManager();
    if (!pCtrlMgr)
        return;

    efd::UInt32 sequenceCount = pCtrlMgr->GetSequenceCount();
    for (efd::UInt32 ui = 0; ui < sequenceCount; ui++)
    {
        NiControllerSequence* pCurrSequence = pCtrlMgr->GetSequenceAt(ui);
        if (!pCurrSequence)
            continue;

        sequences.push_back((const char*)pCurrSequence->GetName());
    }
}

//------------------------------------------------------------------------------------------------
inline efd::Bool AnimationService::SetSequenceFrequencyById(
    const egf::EntityID entityID,
    NiActorManager::SequenceID sequenceID,
    efd::Float32 frequency)
{
    NiActorManager* pActorManager = GetActorManager(entityID);
    if (!pActorManager)
        return false;

    NiControllerSequence* pSequence = pActorManager->GetActiveSequence(sequenceID, true, true);
    if (pSequence == NULL)
        return false;

    pSequence->SetFrequency(frequency);

    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool AnimationService::GetSequenceFrequencyById(
    const egf::EntityID entityID,
    NiActorManager::SequenceID sequenceID,
    efd::Float32& frequency)
{
    NiActorManager* pActorManager = GetActorManager(entityID);
    if (!pActorManager)
        return false;

    NiControllerSequence* pSequence = pActorManager->GetActiveSequence(sequenceID, true, true);
    if (pSequence == NULL)
        return false;

    frequency = pSequence->GetFrequency();

    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool AnimationService::GetSequenceDurationById(
    const egf::EntityID entityID,
    NiActorManager::SequenceID sequenceID,
    efd::Float32& duration)
{
    NiActorManager* pActorManager = GetActorManager(entityID);
    if (!pActorManager)
        return false;

    NiSequenceData* pSequence = pActorManager->GetSequenceData(sequenceID);
    if (pSequence == NULL)
        return false;

    duration = pSequence->GetDuration();

    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool AnimationService::GetSequenceWeightById(
    const egf::EntityID entityID,
    NiActorManager::SequenceID sequenceID,
    efd::Float32& weight)
{
    NiActorManager* pActorManager = GetActorManager(entityID);
    if (!pActorManager)
        return false;

    NiControllerSequence* pSequence = pActorManager->GetActiveSequence(sequenceID, true, true);
    if (pSequence == NULL)
        return false;

    weight = pSequence->GetWeight();

    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool AnimationService::SetSequenceWeightById(
    const egf::EntityID entityID,
    NiActorManager::SequenceID sequenceID,
    efd::Float32 weight)
{
    NiActorManager* pActorManager = GetActorManager(entityID);
    if (!pActorManager)
        return false;

    NiControllerSequence* pSequence = pActorManager->GetActiveSequence(sequenceID, true, true);
    if (pSequence == NULL)
        return false;

    pSequence->SetWeight(weight);

    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool AnimationService::IsPaused(egf::EntityID entityID)
{
    ActorEntry* pEntry;
    if (!ContainsEntity(entityID, pEntry))
        return false;

    NiActorManager* pActorManager = pEntry->m_spActorManager;
    if (!pActorManager)
        return pEntry->m_currentPaused;

    return pActorManager->IsPaused();
}

//------------------------------------------------------------------------------------------------
inline void AnimationService::SetPaused(egf::EntityID entityID, efd::Bool isPaused)
{
    ActorEntry* pEntry;
    if (!ContainsEntity(entityID, pEntry))
        return;

    pEntry->m_currentPaused = isPaused;

    NiActorManager* pActorManager = pEntry->m_spActorManager;
    if (!pActorManager)
        return;

    pActorManager->SetPaused(isPaused);
}

//------------------------------------------------------------------------------------------------
inline void AnimationService::AddToUpdate(ActorEntry* pData)
{
    if (pData->m_updateIndex == ActorEntry::kInvalidUpdateIndex)
    {
        pData->m_updateIndex = static_cast<efd::UInt32>(m_toUpdate.size());
        m_toUpdate.push_back(pData);
    }
}

//------------------------------------------------------------------------------------------------
inline void AnimationService::RemoveFromUpdate(ActorEntry* pData)
{
    if (pData->m_updateIndex != ActorEntry::kInvalidUpdateIndex)
    {
        ActorEntry* pBackData = m_toUpdate.back();
        pBackData->m_updateIndex = pData->m_updateIndex;
        m_toUpdate[pBackData->m_updateIndex] = pBackData;
        m_toUpdate.pop_back();

        pData->m_updateIndex = ActorEntry::kInvalidUpdateIndex;
    }
}

//------------------------------------------------------------------------------------------------
inline AnimationService::ActorEntry::ActorEntry()
    : m_spActorManager(0)
    , m_spAssetData(0)
    , m_updateIndex(kInvalidUpdateIndex)
    , m_pEntity(NULL)
    , m_currentSequenceID(NiActorManager::INVALID_SEQUENCE_ID)
    , m_currentPaused(false)
    , m_flags(0)
{
}

//------------------------------------------------------------------------------------------------
inline efd::Bool AnimationService::ActorEntry::IsWaitingOnAsset() const
{
    return !m_spAssetData || m_spAssetData->m_state != AssetData::ADS_Ready;
}

//------------------------------------------------------------------------------------------------
inline const NiFixedString& AnimationService::TextKeyBehavior::GetBehavior()
{
    return m_behavior;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool egmAnimation::AnimationService::ActorEntry::IsAssetShared() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)IS_ASSET_SHARED);
}

//------------------------------------------------------------------------------------------------
inline void egmAnimation::AnimationService::ActorEntry::SetIsAssetShared(
    const efd::Bool bIsAssetShared)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags, (efd::UInt16)IS_ASSET_SHARED, bIsAssetShared);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool egmAnimation::AnimationService::ActorEntry::IsAccumulated() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)IS_ACCUMULATED);
}

//------------------------------------------------------------------------------------------------
inline void egmAnimation::AnimationService::ActorEntry::SetIsAccumulated(
    const efd::Bool bIsAccumulated)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags, (efd::UInt16)IS_ACCUMULATED, bIsAccumulated);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool egmAnimation::AnimationService::ActorEntry::IsInWorld() const
{
    return efd::BitUtils::AnyBitsAreSet(m_flags, (efd::UInt16)IS_IN_WORLD);
}

//------------------------------------------------------------------------------------------------
inline void egmAnimation::AnimationService::ActorEntry::SetIsInWorld(const efd::Bool inWorld)
{
    m_flags = efd::BitUtils::SetBitsOnOrOff(m_flags,
        (efd::UInt16)IS_IN_WORLD, inWorld);
}

//------------------------------------------------------------------------------------------------
inline NiActorManager::SequenceID AnimationService::AssetData::GetSequenceID(
    const efd::utf8string& sequenceName) const
{
    NiActorManager::SequenceID sequenceID = NiActorManager::INVALID_SEQUENCE_ID;
    m_sequenceIDs.find(sequenceName, sequenceID);

    return sequenceID;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string AnimationService::AssetData::GetSequenceName(
    const NiActorManager::SequenceID sequenceID) const
{
    efd::utf8string sequenceName;
    m_sequenceNames.find(sequenceID, sequenceName);

    return sequenceName;
}

} // namespace