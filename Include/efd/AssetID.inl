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

namespace efd
{

//------------------------------------------------------------------------------------------------
inline AssetID::AssetID()
    : m_urn("")
    , m_multiplicity(0)
    , m_cachingPolicy(AssetID::NEVER_CACHE)
{
}

//------------------------------------------------------------------------------------------------
inline AssetID::AssetID(
    const efd::utf8string& urn,
    efd::UInt8 multiplicity,
    AssetID::CachingPolicy cachingPolicy)
    : m_urn(urn)
    , m_multiplicity(multiplicity)
    , m_cachingPolicy(cachingPolicy)
{
}

//------------------------------------------------------------------------------------------------
inline AssetID::AssetID(
    const char* urn,
    efd::UInt8 multiplicity,
    AssetID::CachingPolicy cachingPolicy)
    : m_urn(urn)
    , m_multiplicity(multiplicity)
    , m_cachingPolicy(cachingPolicy)
{
}

//------------------------------------------------------------------------------------------------
inline AssetID::AssetID(const efd::AssetID& other)
{
    m_urn = other.m_urn;
    m_multiplicity = other.m_multiplicity;
    m_cachingPolicy = other.m_cachingPolicy;
}

//------------------------------------------------------------------------------------------------
inline AssetID::~AssetID()
{
    // noop
}

//------------------------------------------------------------------------------------------------
inline AssetID& AssetID::operator=(const efd::AssetID& other)
{
    m_urn = other.m_urn;
    m_multiplicity = other.m_multiplicity;
    m_cachingPolicy = other.m_cachingPolicy;
    return *this;
}

//------------------------------------------------------------------------------------------------
inline AssetID& AssetID::operator=(const efd::utf8string& urn)
{
    m_urn = urn;
    m_multiplicity = 0;
    m_cachingPolicy = NEVER_CACHE;
    return *this;
}

//------------------------------------------------------------------------------------------------
inline AssetID& AssetID::operator=(const char* urn)
{
    m_urn = urn;
    m_multiplicity = 0;
    m_cachingPolicy = NEVER_CACHE;
    return *this;
}

//------------------------------------------------------------------------------------------------
inline AssetID::operator const efd::utf8string&() const
{
    return m_urn;
}


//------------------------------------------------------------------------------------------------
inline const char* AssetID::c_str() const
{
    return m_urn.c_str();
}

//------------------------------------------------------------------------------------------------
inline bool AssetID::operator==(const AssetID& other) const
{
    // only compare URNs for now
    return m_urn == other.m_urn;
}

//------------------------------------------------------------------------------------------------
inline bool AssetID::operator!=(const AssetID& other) const
{
    // only compare URNs for now
    return m_urn != other.m_urn;
}

//------------------------------------------------------------------------------------------------
inline bool AssetID::operator<(const AssetID& other) const
{
    // only compare URNs for now
    return m_urn < other.m_urn;
}


//------------------------------------------------------------------------------------------------
inline bool AssetID::IsValidURN() const
{
    return m_urn.find_first_of("urn:") == 0;
}

//------------------------------------------------------------------------------------------------
inline void AssetID::SetURN(const efd::utf8string &val)
{
    m_urn = val;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& AssetID::GetURN() const
{
    return m_urn;
}

//------------------------------------------------------------------------------------------------
inline void AssetID::SetMultiplicity(efd::UInt8 val)
{
    m_multiplicity = val;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt8 AssetID::GetMultiplicity() const
{
    return m_multiplicity;
}

//------------------------------------------------------------------------------------------------
inline void AssetID::SetCachingPolicy(CachingPolicy val)
{
    m_cachingPolicy = val;
}

//------------------------------------------------------------------------------------------------
inline AssetID::CachingPolicy AssetID::GetCachingPolicy() const
{
    return m_cachingPolicy;
}

//------------------------------------------------------------------------------------------------
inline void AssetID::Serialize(efd::Archive& io_archive)
{
    // For historical legacy reasons we serialize just the URN.
    efd::Serializer::SerializeObject(m_urn, io_archive);
}

//------------------------------------------------------------------------------------------------
inline bool AssetID::IsUUID() const
{
    if (m_urn.find("urn:uuid:") != efd::utf8string::npos)
    {
        return true;
    }
    return false;
}

}  // namespace efd
