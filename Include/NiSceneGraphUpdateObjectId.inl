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

#include "NiDebug.h"

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateObjectId::NiSceneGraphUpdateObjectId()
{
    m_usInstanceId = 0;
    m_usObjectId = 0;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateObjectId::NiSceneGraphUpdateObjectId(const NiSceneGraphUpdateObjectId& kId)
{
    this->m_usInstanceId = kId.m_usInstanceId;
    this->m_usObjectId = kId.m_usObjectId;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateObjectId::NiSceneGraphUpdateObjectId(const NiUInt32 uiId)
{
    // This class is cast to a NiUInt32 for serialization and unserialization. If this assert is
    // false then the class has been modified and is no longer 32 bits, which will break
    // streaming and its use in NiTMaps as a key.
    EE_ASSERT(sizeof(NiSceneGraphUpdateObjectId) == sizeof(NiUInt32));

    // Decode NiUInt32 into object ID parts
    m_usInstanceId = static_cast<NiUInt16>(uiId>>16 & 0xffff);
    m_usObjectId = static_cast<NiUInt16>(uiId & 0xffff);
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateObjectId::NiSceneGraphUpdateObjectId(const NiUInt16 usInstanceId,
    const NiUInt16 usObjectId)
{
    m_usInstanceId = usInstanceId;
    m_usObjectId = usObjectId;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateObjectId::~NiSceneGraphUpdateObjectId()
{
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiSceneGraphUpdateObjectId::GetInstanceId() const
{
    return m_usInstanceId;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt16 NiSceneGraphUpdateObjectId::GetObjectId() const
{
    return m_usObjectId;
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdateObjectId::SetInstanceId(const NiUInt16 usInstanceId)
{
   m_usInstanceId = usInstanceId;
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdateObjectId::SetObjectId(const NiUInt16 usObjectId)
{
    m_usObjectId = usObjectId;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateObjectId::operator NiUInt32() const
{
    // Encode object ID parts into NiUInt32
    NiUInt32 uiId = m_usInstanceId;
    uiId = uiId<<16;
    uiId |= m_usObjectId;

    return uiId;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateObjectId& NiSceneGraphUpdateObjectId::operator =(
    const NiSceneGraphUpdateObjectId& kOtherId)
{
    m_usInstanceId = kOtherId.m_usInstanceId;
    m_usObjectId = kOtherId.m_usObjectId;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdateObjectId::operator ==(
    const NiSceneGraphUpdateObjectId& kOtherId) const
{
    if (this == &kOtherId)
    {
        return true;
    }
    else
    {
        return (this->m_usObjectId == kOtherId.m_usObjectId
            && this->m_usInstanceId == kOtherId.m_usInstanceId);
    }
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdateObjectId::operator !=(
    const NiSceneGraphUpdateObjectId& kOtherId) const
{
    return !(*this == kOtherId);
}

//--------------------------------------------------------------------------------------------------
