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
inline ecr::SceneGraphMessage::SceneGraphMessage()
    : m_pEntity(NULL)
    , m_handle(ecr::SceneGraphService::kInvalidHandle)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphMessage::SceneGraphMessage(egf::Entity* pEntity)
    : m_pEntity(pEntity)
    , m_handle(ecr::SceneGraphService::kInvalidHandle)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphMessage::SceneGraphMessage(const
    ecr::SceneGraphService::SceneGraphHandle handle)
    : m_pEntity(NULL)
    , m_handle(handle)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphMessage::~SceneGraphMessage()
{
}

//------------------------------------------------------------------------------------------------
inline egf::Entity* ecr::SceneGraphMessage::GetEntity() const
{
    return m_pEntity;
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphMessage::SetEntity(egf::Entity* pEntity)
{
    m_pEntity = pEntity;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ecr::SceneGraphMessage::GetHandle() const
{
    return m_handle;
}

//------------------------------------------------------------------------------------------------
inline void ecr::SceneGraphMessage::SetHandle(const efd::UInt32 handle)
{
    m_handle = handle;
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphAddedMessage::SceneGraphAddedMessage()
    : ecr::SceneGraphMessage()
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphAddedMessage::SceneGraphAddedMessage(egf::Entity* pEntity)
    : ecr::SceneGraphMessage(pEntity)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphAddedMessage::SceneGraphAddedMessage(
    const ecr::SceneGraphService::SceneGraphHandle handle)
    : ecr::SceneGraphMessage(handle)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphRemovedMessage::SceneGraphRemovedMessage()
    : ecr::SceneGraphMessage()
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphRemovedMessage::SceneGraphRemovedMessage(egf::Entity* pEntity)
    : ecr::SceneGraphMessage(pEntity)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphRemovedMessage::SceneGraphRemovedMessage(
    const ecr::SceneGraphService::SceneGraphHandle handle)
    : ecr::SceneGraphMessage(handle)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphsUpdatedMessage::SceneGraphsUpdatedMessage()
{
}

//------------------------------------------------------------------------------------------------
inline ecr::SceneGraphsUpdatedMessage::~SceneGraphsUpdatedMessage()
{
}

//------------------------------------------------------------------------------------------------
inline ecr::AttachmentMessage::AttachmentMessage()
    : m_pEntity(NULL)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::AttachmentMessage::AttachmentMessage(egf::Entity* pEntity, const efd::utf8string& key)
    : m_pEntity(pEntity)
    , m_key(key)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::AttachmentMessage::~AttachmentMessage()
{
}

//------------------------------------------------------------------------------------------------
inline egf::Entity* ecr::AttachmentMessage::GetEntity() const
{
    return m_pEntity;
}

//------------------------------------------------------------------------------------------------
inline void ecr::AttachmentMessage::SetEntity(egf::Entity* pEntity)
{
    m_pEntity = pEntity;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string ecr::AttachmentMessage::GetKey() const
{
    return m_key;
}

//------------------------------------------------------------------------------------------------
inline void ecr::AttachmentMessage::SetKey(const efd::utf8string& key)
{
    m_key = key;
}

//------------------------------------------------------------------------------------------------
inline ecr::AttachmentMadeMessage::AttachmentMadeMessage() : AttachmentMessage()
{
}

//------------------------------------------------------------------------------------------------
inline ecr::AttachmentMadeMessage::AttachmentMadeMessage(egf::Entity* pEntity,
    const efd::utf8string& key)
    : AttachmentMessage(pEntity, key)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::AttachmentMadeMessage::~AttachmentMadeMessage()
{
}

//------------------------------------------------------------------------------------------------
inline ecr::AttachmentBrokenMessage::AttachmentBrokenMessage() : AttachmentMessage()
{
}

//------------------------------------------------------------------------------------------------
inline ecr::AttachmentBrokenMessage::AttachmentBrokenMessage(egf::Entity* pEntity,
    const efd::utf8string& key)
    : AttachmentMessage(pEntity, key)
{
}

//------------------------------------------------------------------------------------------------
inline ecr::AttachmentBrokenMessage::~AttachmentBrokenMessage()
{
}

//------------------------------------------------------------------------------------------------
