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
inline NiTexturePalette* ecr::SceneGraphCache::GetTexturePalette() const
{
    return m_spPalette;
}

//------------------------------------------------------------------------------------------------
inline efd::Category ecr::SceneGraphCache::GetReloadCategory() const
{
    return m_assetReloadResponseCategory;
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphCache::AssetStatus ecr::SceneGraphCache::GetStatus(
    SceneGraphCacheHandle handle) const
{
    return handle->m_status;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& ecr::SceneGraphCache::GetPhysicalID(
    SceneGraphCacheHandle handle) const
{
    return handle->m_physicalID;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& ecr::SceneGraphCache::GetFilePath(
    SceneGraphCacheHandle handle) const
{
    return handle->m_filePath;
}

//------------------------------------------------------------------------------------------------
efd::UInt32 ecr::SceneGraphCache::GetObjectCount(SceneGraphCacheHandle handle) const
{
    return (efd::UInt32)handle->m_objects.size();
}

//------------------------------------------------------------------------------------------------
NiObject* ecr::SceneGraphCache::GetObjectAt(
    SceneGraphCacheHandle handle,
    efd::UInt32 index) const
{
    return handle->m_objects[index];
}

