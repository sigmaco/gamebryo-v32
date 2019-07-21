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

//-----------------------------------------------------------------------------------------------
inline efd::AssetCacheResponse::AssetCacheResponse()
    : m_urn("")
    , m_responseCategory(kCAT_INVALID)
    , m_result(ACR_UnknownError)
    , m_type(ACT_UnknownType)
{
}

//-----------------------------------------------------------------------------------------------
inline efd::AssetCacheResponse::AssetCacheResponse(
    const efd::utf8string& urn,
    const efd::Category& responseCategory,
    efd::AssetCacheResponse::AssetCacheResult result,
    efd::AssetCacheResponse::AssetCacheType type)
    : m_urn(urn)
    , m_responseCategory(responseCategory)
    , m_result(result)
    , m_type(type)
{
}

//-----------------------------------------------------------------------------------------------
inline efd::AssetCacheResponse::~AssetCacheResponse()
{
}

//-----------------------------------------------------------------------------------------------
inline const efd::utf8string& efd::AssetCacheResponse::GetURN() const
{
    return m_urn;
}

//-----------------------------------------------------------------------------------------------
inline const efd::Category& efd::AssetCacheResponse::GetResponseCategory() const
{
    return m_responseCategory;
}

//-----------------------------------------------------------------------------------------------
inline void efd::AssetCacheResponse::SetResponseCategory(const efd::Category& cat)
{
    m_responseCategory = cat;
}

//-----------------------------------------------------------------------------------------------
inline void efd::AssetCacheResponse::SetResult(efd::AssetCacheResponse::AssetCacheResult result)
{
    m_result = result;
}

//-----------------------------------------------------------------------------------------------
inline efd::AssetCacheResponse::AssetCacheResult efd::AssetCacheResponse::GetResult() const
{
    return m_result;
}

//-----------------------------------------------------------------------------------------------
inline efd::AssetCacheResponse::AssetCacheType efd::AssetCacheResponse::GetType() const
{
    return m_type;
}

//-----------------------------------------------------------------------------------------------
inline void efd::AssetCacheResponse::SetType(efd::AssetCacheResponse::AssetCacheType type)
{
    m_type = type;
}

//-----------------------------------------------------------------------------------------------
