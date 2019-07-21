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
inline const efd::utf8string& ecr::AttachNifData::GetAttachPoint() const
{
    return m_attachPoint;
}

//------------------------------------------------------------------------------------------------
inline void ecr::AttachNifData::SetAttachPoint(const efd::utf8string& attachPoint)
{
    m_attachPoint = attachPoint;
}

//------------------------------------------------------------------------------------------------
inline efd::AssetID ecr::AttachNifData::GetNifAsset() const
{
    return m_nifAsset;
}

//------------------------------------------------------------------------------------------------
inline void ecr::AttachNifData::SetNifAsset(const efd::AssetID& nifAsset)
{
    m_nifAsset = nifAsset;
}

//------------------------------------------------------------------------------------------------
inline efd::Point3 ecr::AttachNifData::GetTranslation() const
{
    return m_translation;
}

//------------------------------------------------------------------------------------------------
inline void ecr::AttachNifData::SetTranslation(const efd::Point3& translation)
{
    m_translation = translation;
}

//------------------------------------------------------------------------------------------------
inline efd::Point3 ecr::AttachNifData::GetRotation() const
{
    return m_rotation;
}

//------------------------------------------------------------------------------------------------
inline void ecr::AttachNifData::SetRotation(const efd::Point3& rotation)
{
    m_rotation = rotation;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 ecr::AttachNifData::GetScale() const
{
    return m_scale;
}

//------------------------------------------------------------------------------------------------
inline void ecr::AttachNifData::SetScale(const efd::Float32 scale)
{
    m_scale = scale;
}

//------------------------------------------------------------------------------------------------
inline efd::ClassID ecr::AttachNifData::GetPropertyType() const
{
    return CLASS_ID;
}

//------------------------------------------------------------------------------------------------
inline bool ecr::AttachNifData::operator==(const ecr::AttachNifData& other) const
{
    if (this == &other) return true;
    return other.m_attachPoint == m_attachPoint &&
           other.m_nifAsset == m_nifAsset &&
           other.m_translation == m_translation &&
           other.m_rotation == m_rotation &&
           other.m_scale == m_scale;
}

//------------------------------------------------------------------------------------------------
inline bool ecr::AttachNifData::operator!=(const ecr::AttachNifData& other) const
{
    if (this == &other) return false;
    return other.m_attachPoint != m_attachPoint ||
        other.m_nifAsset != m_nifAsset ||
        other.m_translation != m_translation ||
        other.m_rotation != m_rotation ||
        other.m_scale != m_scale;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<ecr::AttachNifData>::FromString(
    const efd::utf8string& value, ecr::AttachNifData& result)
{
    return result.FromString(value);
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<ecr::AttachNifData>::ToString(
    const ecr::AttachNifData& value, efd::utf8string& result)
{
    result = value.ToString();

    return !result.empty();
}

//------------------------------------------------------------------------------------------------
inline const char* efd::ParseHelper<ecr::AttachNifData>::GetNameOfType()
{
    return "ecr::AttachNifData";
}

//------------------------------------------------------------------------------------------------

