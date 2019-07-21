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
inline efd::Category egmAnimation::KFMCache::GetReloadCategory() const
{
    return m_assetReloadResponseCategory;
}

//------------------------------------------------------------------------------------------------
inline egmAnimation::KFMCache::AssetStatus egmAnimation::KFMCache::GetStatus(
    KFMCacheHandle handle) const
{
    return handle->m_status;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& egmAnimation::KFMCache::GetPhysicalID(KFMCacheHandle handle) const
{
    return handle->m_physicalID;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& egmAnimation::KFMCache::GetFilePath(KFMCacheHandle handle) const
{
    return handle->m_filePath;
}

//------------------------------------------------------------------------------------------------
inline NiActorManager* egmAnimation::KFMCache::GetActorManager(KFMCacheHandle handle) const
{
    if (handle == KFMCache::k_invalidHandle)
        return NULL;

    return handle->m_spActorManager;
}
