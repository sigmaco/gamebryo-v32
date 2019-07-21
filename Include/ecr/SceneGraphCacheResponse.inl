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
inline ecr::SceneGraphCacheResponse::SceneGraphCacheResponse()
    : AssetCacheResponse()
    , m_pRequestData(NULL)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphCacheResponse::SceneGraphCacheResponse(
    const efd::utf8string& identifier,
    const efd::Category& responseCategory,
    SceneGraphCache::ISceneGraphCacheRequestData* pRequestData,
    const efd::AssetCacheResponse::AssetCacheResult result,
    const efd::AssetCacheResponse::AssetCacheType type)
    : AssetCacheResponse(identifier, responseCategory, result, type)
    , m_pRequestData(pRequestData)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphCacheResponse::~SceneGraphCacheResponse()
{
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& ecr::SceneGraphCacheResponse::GetIdentifier() const
{
    return GetURN();
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphCache::ISceneGraphCacheRequestData*
    ecr::SceneGraphCacheResponse::GetRequestData() const
{
    return m_pRequestData;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ecr::SceneGraphCacheResponse::GetHandleCount() const
{
    return (efd::UInt32)m_handles.size();
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphCache::SceneGraphCacheHandle
    ecr::SceneGraphCacheResponse::GetHandle(const efd::UInt32 index) const
{
    return m_handles[index];
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphCacheResponse::AddHandle(
    const SceneGraphCache::SceneGraphCacheHandle handle)
{
    m_handles.push_back(handle);
}

