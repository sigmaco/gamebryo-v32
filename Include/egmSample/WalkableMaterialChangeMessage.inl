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

namespace egmSample
{

//------------------------------------------------------------------------------------------------
inline WalkableMaterialChangeMessage::WalkableMaterialChangeMessage()
    : m_pEntity(0)
    , m_newMaterial()
{
}

//------------------------------------------------------------------------------------------------
inline egf::Entity* WalkableMaterialChangeMessage::GetEntity()
{
    return m_pEntity;
}

//------------------------------------------------------------------------------------------------
inline void WalkableMaterialChangeMessage::SetEntity(egf::Entity* pEntity)
{
    m_pEntity = pEntity;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string WalkableMaterialChangeMessage::GetMaterial()
{
    return m_newMaterial;
}

//------------------------------------------------------------------------------------------------
inline void WalkableMaterialChangeMessage::SetMaterial(efd::utf8string material)
{
    m_newMaterial = material;
}

//------------------------------------------------------------------------------------------------
} // end namespace egmSample
