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
inline ecr::NIFFactoryResponse::NIFFactoryResponse()
    : efd::AssetLoadResponse()
{
}

//------------------------------------------------------------------------------------------------
inline ecr::NIFFactoryResponse::NIFFactoryResponse(
    const efd::utf8string& urn,
    const efd::Category& responseCategory,
    efd::AssetLoadResponse::AssetLoadResult result,
    const efd::utf8string& assetPath,
    bool isReload,
    NiStream* pStream)
    : efd::AssetLoadResponse(urn, responseCategory, result, assetPath, isReload)
    , m_pStream(pStream)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::NIFFactoryResponse::~NIFFactoryResponse()
{
    EE_DELETE m_pStream;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ecr::NIFFactoryResponse::GetObjectCount() const
{
    if (m_pStream)
        return m_pStream->GetObjectCount();

    return 0;
}

//------------------------------------------------------------------------------------------------
inline NiObject* ecr::NIFFactoryResponse::GetObjectAt(efd::UInt32 index) const
{
    return m_pStream->GetObjectAt(index);
}
