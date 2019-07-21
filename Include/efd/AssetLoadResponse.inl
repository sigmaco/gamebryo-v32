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
inline efd::AssetLoadResponse::AssetLoadResponse()
    : m_urn("")
    , m_responseCategory(kCAT_INVALID)
    , m_result(ALR_UnknownError)
    , m_assetPath("")
    , m_isReload(false)
{
}

//------------------------------------------------------------------------------------------------
inline efd::AssetLoadResponse::AssetLoadResponse(
    const efd::utf8string& urn,
    const efd::Category& responseCategory,
    efd::AssetLoadResponse::AssetLoadResult result,
    const efd::utf8string& assetPath,
    bool isReload)
    : m_urn(urn)
    , m_responseCategory(responseCategory)
    , m_result(result)
    , m_assetPath(assetPath)
    , m_isReload(isReload)
{
}

//------------------------------------------------------------------------------------------------
inline efd::AssetLoadResponse::~AssetLoadResponse()
{
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& efd::AssetLoadResponse::GetURN() const
{
    return m_urn;
}

//------------------------------------------------------------------------------------------------
inline const efd::Category& efd::AssetLoadResponse::GetResponseCategory() const
{
    return m_responseCategory;
}

//------------------------------------------------------------------------------------------------
inline void efd::AssetLoadResponse::SetResponseCategory(const efd::Category& cat)
{
    m_responseCategory = cat;
}

//------------------------------------------------------------------------------------------------
inline void efd::AssetLoadResponse::SetResult(efd::AssetLoadResponse::AssetLoadResult result)
{
    m_result = result;
}

//------------------------------------------------------------------------------------------------
inline efd::AssetLoadResponse::AssetLoadResult efd::AssetLoadResponse::GetResult() const
{
    return m_result;
}

//------------------------------------------------------------------------------------------------
inline bool efd::AssetLoadResponse::GetIsReload() const
{
    return m_isReload;
}

//------------------------------------------------------------------------------------------------
inline void efd::AssetLoadResponse::SetIsReload(bool isReload)
{
    m_isReload = isReload;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& efd::AssetLoadResponse::GetAssetPath() const
{
    return m_assetPath;
}
