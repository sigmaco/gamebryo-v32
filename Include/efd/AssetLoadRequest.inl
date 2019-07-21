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
inline efd::AssetLoadRequest::AssetLoadRequest()
    : m_urn()
    , m_responseCategory(efd::kCAT_INVALID)
    , m_assetPath()
    , m_isBackground(true)
    , m_isPreemptive(false)
    , m_isReload(false)
{
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& efd::AssetLoadRequest::GetURN() const
{
    return m_urn;
}

//------------------------------------------------------------------------------------------------
inline const efd::Category& efd::AssetLoadRequest::GetResponseCategory() const
{
    return m_responseCategory;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& efd::AssetLoadRequest::GetAssetPath() const
{
    return m_assetPath;
}

//------------------------------------------------------------------------------------------------
inline bool efd::AssetLoadRequest::GetIsBackground() const
{
    return m_isBackground;
}

//------------------------------------------------------------------------------------------------
inline bool efd::AssetLoadRequest::GetIsPreemptive() const
{
    return m_isPreemptive;
}

//------------------------------------------------------------------------------------------------
inline void efd::AssetLoadRequest::SetURN(const efd::utf8string& urn)
{
    m_urn = urn;
    EE_ASSERT(AssetID(m_urn).IsValidURN());
}

//------------------------------------------------------------------------------------------------
inline void efd::AssetLoadRequest::SetResponseCategory(const efd::Category& responseCategory)
{
    m_responseCategory = responseCategory;
}

//------------------------------------------------------------------------------------------------
inline void efd::AssetLoadRequest::SetAssetPath(const efd::utf8string& assetPath)
{
    m_assetPath = assetPath;
    EE_ASSERT(m_assetPath.length() > 0);
}

//------------------------------------------------------------------------------------------------
inline void efd::AssetLoadRequest::SetIsBackground(const bool isBackground)
{
    m_isBackground = isBackground;
}

//------------------------------------------------------------------------------------------------
inline void efd::AssetLoadRequest::SetIsPreemptive(const bool isPreemptive)
{
    m_isPreemptive = isPreemptive;
}

//------------------------------------------------------------------------------------------------
inline bool efd::AssetLoadRequest::GetIsReload() const
{
    return m_isReload;
}

//------------------------------------------------------------------------------------------------
inline void efd::AssetLoadRequest::SetIsReload(bool isReload)
{
    m_isReload = isReload;
}

