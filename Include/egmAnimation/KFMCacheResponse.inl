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
inline egmAnimation::KFMCacheResponse::KFMCacheResponse()
    : AssetCacheResponse()
    , m_pRequestData(NULL)
{
}

//------------------------------------------------------------------------------------------------
inline egmAnimation::KFMCacheResponse::KFMCacheResponse(
    const efd::utf8string& identifier,
    const efd::Category& responseCategory,
    KFMCache::IKFMCacheRequestData* pRequestData,
    const efd::AssetCacheResponse::AssetCacheResult result,
    const efd::AssetCacheResponse::AssetCacheType type)
    : AssetCacheResponse(identifier, responseCategory, result, type)
    , m_pRequestData(pRequestData)
{
}

//------------------------------------------------------------------------------------------------
inline egmAnimation::KFMCacheResponse::~KFMCacheResponse()
{
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& egmAnimation::KFMCacheResponse::GetIdentifier() const
{
    return GetURN();
}

//------------------------------------------------------------------------------------------------
inline egmAnimation::KFMCache::IKFMCacheRequestData*
    egmAnimation::KFMCacheResponse::GetRequestData() const
{
    return m_pRequestData;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 egmAnimation::KFMCacheResponse::GetHandleCount() const
{
    return (efd::UInt32)m_handles.size();
}

//------------------------------------------------------------------------------------------------
inline egmAnimation::KFMCache::KFMCacheHandle
    egmAnimation::KFMCacheResponse::GetHandle(const efd::UInt32 index) const
{
    return m_handles[index];
}

//------------------------------------------------------------------------------------------------
inline void egmAnimation::KFMCacheResponse::AddHandle(
    const KFMCache::KFMCacheHandle handle)
{
    m_handles.push_back(handle);
}

