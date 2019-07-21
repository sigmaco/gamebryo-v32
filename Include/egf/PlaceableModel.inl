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
inline egf::Entity* egf::PlaceableModel::GetOwningEntity() const
{
    return m_pOwningEntity;
}

//------------------------------------------------------------------------------------------------
inline efd::Point3 egf::PlaceableModel::GetPosition() const
{
    return m_position;
}

//------------------------------------------------------------------------------------------------
inline void egf::PlaceableModel::SetPosition(const efd::Point3& position)
{
    if (m_position != position)
    {
        m_position = position;

        InvokeCallbacks(
            egf::kFlatModelID_StandardModelLibrary_Placeable,
            m_pOwningEntity,
            kPropertyID_StandardModelLibrary_Position,
            this,
            0,
            0);
    }
}

//------------------------------------------------------------------------------------------------
inline efd::Point3 egf::PlaceableModel::GetRotation() const
{
    return m_rotation;
}

//------------------------------------------------------------------------------------------------
inline void egf::PlaceableModel::SetRotation(const efd::Point3& rotation)
{
    if (m_rotation != rotation)
    {
        m_rotation = rotation;

        InvokeCallbacks(
            egf::kFlatModelID_StandardModelLibrary_Placeable,
            m_pOwningEntity,
            kPropertyID_StandardModelLibrary_Rotation,
            this,
            0,
            0);
    }
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 egf::PlaceableModel::GetScale() const
{
    return m_scale;
}

//------------------------------------------------------------------------------------------------
inline void egf::PlaceableModel::SetScale(const efd::Float32& scale)
{
    if (m_scale != scale)
    {
        m_scale = scale;

        InvokeCallbacks(
            egf::kFlatModelID_StandardModelLibrary_Placeable,
            m_pOwningEntity,
            kPropertyID_StandardModelLibrary_Scale,
            this,
            0,
            0);
    }
}

//------------------------------------------------------------------------------------------------
inline void egf::PlaceableModel::AddCallback(egf::IPropertyCallback* pCallback)
{
    PlaceableModel temp;
    temp.AddPropertyCallback(pCallback);
}

//------------------------------------------------------------------------------------------------
inline void egf::PlaceableModel::RemoveCallback(egf::IPropertyCallback* pCallback)
{
    PlaceableModel temp;
    temp.RemovePropertyCallback(pCallback);
}
