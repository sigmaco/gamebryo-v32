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
inline efd::Category efd::AssetFactoryManager::MessageCategory()
{
    return ms_privateCategory;
}

//------------------------------------------------------------------------------------------------
inline bool efd::AssetFactoryManager::IsFgInstance() const
{
    return m_pLoaderThreadFunctor != NULL;
}

//------------------------------------------------------------------------------------------------
inline bool efd::AssetFactoryManager::SetBgThreadAffinity(const efd::ProcessorAffinity& affinity)
{
    if (!IsFgInstance())
        return false;

    return m_pLoaderThread->SetThreadAffinity(affinity);
}

//------------------------------------------------------------------------------------------------
inline const efd::ProcessorAffinity efd::AssetFactoryManager::GetBgThreadAffinity()
{
    if (!IsFgInstance())
        return ProcessorAffinity();

    return m_pLoaderThread->GetThreadAffinity();
}

//------------------------------------------------------------------------------------------------
inline bool efd::AssetFactoryManager::SetBgThreadPriority(const efd::Thread::Priority priority)
{
    if (!IsFgInstance())
        return false;

    return m_pLoaderThread->SetPriority(priority);
}

//------------------------------------------------------------------------------------------------
inline efd::Thread::Priority efd::AssetFactoryManager::GetBgThreadPriority() const
{
    if (!IsFgInstance())
        return efd::Thread::NUM_PRIORITIES;

    return m_pLoaderThread->GetPriority();
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 efd::AssetFactoryManager::GetSleepInterval() const
{
    return m_sleepInterval;
}
