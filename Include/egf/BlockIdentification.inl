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

namespace egf
{

//------------------------------------------------------------------------------------------------
inline BlockIdentification::BlockIdentification()
    : m_blockAsset()
    , m_instance(0)
{
}

//------------------------------------------------------------------------------------------------
inline BlockIdentification::BlockIdentification(const efd::AssetID& asset, efd::UInt32 instance)
    : m_blockAsset(asset)
    , m_instance(instance)
{
}

//------------------------------------------------------------------------------------------------
inline BlockIdentification::BlockIdentification(const efd::utf8string& asset, efd::UInt32 instance)
    : m_blockAsset(asset)
    , m_instance(instance)
{
}

//------------------------------------------------------------------------------------------------
inline BlockIdentification::BlockIdentification(const char* asset, efd::UInt32 instance)
    : m_blockAsset(asset)
    , m_instance(instance)
{
}

//------------------------------------------------------------------------------------------------
inline BlockIdentification::BlockIdentification(const BlockIdentification& other)
    : m_blockAsset(other.m_blockAsset)
    , m_instance(other.m_instance)
{
}

//------------------------------------------------------------------------------------------------
inline BlockIdentification::operator efd::AssetID()
{
    return m_blockAsset;
}

//------------------------------------------------------------------------------------------------
inline BlockIdentification::operator const efd::AssetID() const
{
    return m_blockAsset;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& BlockIdentification::GetURN() const
{
    return m_blockAsset.GetURN();
}

//------------------------------------------------------------------------------------------------
inline bool BlockIdentification::IsUUID() const
{

    return m_blockAsset.IsUUID();
}

//------------------------------------------------------------------------------------------------
inline bool BlockIdentification::operator < (const BlockIdentification& other) const
{
    if (m_blockAsset == other.m_blockAsset)
        return m_instance < other.m_instance;
    return m_blockAsset < other.m_blockAsset;
}

//------------------------------------------------------------------------------------------------
} // end namespace egf
