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

#pragma once
#ifndef EE_CORERUNTIMEMESSAGES_H
#define EE_CORERUNTIMEMESSAGES_H

#include "ecrLibType.h"

#include <efd/IMessage.h>
#include <egf/IProperty.h>
#include <egf/Entity.h>
#include <NiNode.h>

#include <ecr/ecrMessageIDs.h>
#include <ecr/RenderService.h>
#include <ecr/SceneGraphService.h>

namespace ecr
{

/**
    The SceneGraphMessage class is a generic message class that holds an entity and a scene graph
    handle.

    Messages indicating specific events are derived from this message.

    Only one of the entity or handle members will be valid, the other will have the invalid
    value (NULL or SceneGraphService::kInvalidHandle).
*/
class EE_ECR_ENTRY SceneGraphMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SceneGraphMessage, efd::kMSGID_SceneGraph, efd::IMessage);
    /// @endcond

public:
    /// Default constructor sets the entity and the handle to the invalid values.
    inline SceneGraphMessage();

    /// Constructor sets the entity to the given value and the handle to the invalid value.
    inline SceneGraphMessage(egf::Entity* pEntity);

    /// Constructor sets the handle to the given value and the entity to the invalid value.
    inline SceneGraphMessage(const ecr::SceneGraphService::SceneGraphHandle handle);

    /// Destructor.
    inline virtual ~SceneGraphMessage();

    /// The factory for creating messages.
    static efd::IBasePtr FactoryMethod();

    /// Push the message contents to a data stream.
    virtual void Serialize(efd::Archive& ar);

    /// Get the entity pointer.
    ///
    /// The return value will be NULL if not valid.
    inline virtual egf::Entity* GetEntity() const;

    /// Set the entity pointer.
    inline virtual void SetEntity(egf::Entity* pEntity);

    /// Get the scene graph handle.
    ///
    /// The return value will be SceneGraphService::kInvalidHandle if not valid.
    inline virtual ecr::SceneGraphService::SceneGraphHandle GetHandle() const;

    /// Set the scene graph handle.
    inline virtual void SetHandle(const ecr::SceneGraphService::SceneGraphHandle handle);

protected:
    egf::Entity* m_pEntity;
    ecr::SceneGraphService::SceneGraphHandle m_handle;
};


/**
    The SceneGraphAddedMessage message is sent by the SceneGraphService service when a new scene
    graph has been loaded and is available for use.

    Other services should subscribe to this message if they need to take action when a new scene
    graph is available. For example, the Light Service looks for SceneGraphAddedMessage messages
    to add lighting to the newly added scene graph.

    All functionality is inherited from the base class except the class ID accessor.
*/
class EE_ECR_ENTRY SceneGraphAddedMessage : public SceneGraphMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SceneGraphAddedMessage, efd::kMSGID_SceneGraphAdded, ecr::SceneGraphMessage);
    /// @endcond
public:
    /// Default constructor sets the entity and the handle to the invalid values.
    inline SceneGraphAddedMessage();

    /// Constructor sets the entity to the given value and the handle to the invalid value.
    inline SceneGraphAddedMessage(egf::Entity* pEntity);

    /// Constructor sets the handle to the given value and the entity to the invalid value.
    inline SceneGraphAddedMessage(const ecr::SceneGraphService::SceneGraphHandle handle);
};
typedef efd::SmartPointer<SceneGraphAddedMessage> SceneGraphAddedMessagePtr;


/**
    The SceneGraphRemovedMessage message is sent by the SceneGraphService service when a scene
    graph is removed form the system.

    Other services should subscribe to this message if they need to take action when a scene
    graph is removed. For example, the Light Service looks for SceneGraphRemovedMessage messages
    to remove the scene graph from the affected entities list for lights.

    All functionality is inherited from the base class except the class ID accessor.
*/
class EE_ECR_ENTRY SceneGraphRemovedMessage : public SceneGraphMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SceneGraphRemovedMessage, efd::kMSGID_SceneGraphRemoved,
        ecr::SceneGraphMessage);
    /// @endcond

public:
    /// Default constructor sets the entity and the handle to the invalid values.
    inline SceneGraphRemovedMessage();

    /// Constructor sets the entity to the given value and the handle to the invalid value.
    inline SceneGraphRemovedMessage(egf::Entity* pEntity);

    /// Constructor sets the handle to the given value and the entity to the invalid value.
    inline SceneGraphRemovedMessage(const ecr::SceneGraphService::SceneGraphHandle handle);

};
typedef efd::SmartPointer<SceneGraphRemovedMessage> SceneGraphRemovedMessagePtr;


/**
    The SceneGraphsUpdatedMessage message is sent by the SceneGraphService service when the scene
    graphs have been updated (through the NiAVObject::Update method).

    Other services should subscribe to this message if they need to take action when the scene
    graphs have been updated. For example, the Light Service looks for SceneGraphsUpdatedMessage
    messages to track entities as they move between lights' areas of effect.

    After receiving one of these messages, the SceneGraphService Updated Entity Iteration
    functions may be used to iterate over the objects that were updated.
*/
class EE_ECR_ENTRY SceneGraphsUpdatedMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        SceneGraphsUpdatedMessage,
        efd::kMSGID_SceneGraphsUpdated,
        efd::IMessage);
    /// @endcond

public:
    /// Default constructor.
    inline SceneGraphsUpdatedMessage();

    /// Destructor.
    inline virtual ~SceneGraphsUpdatedMessage();

    /// The factory for creating messages.
    static efd::IBasePtr FactoryMethod();
};
typedef efd::SmartPointer<SceneGraphsUpdatedMessage> SceneGraphsUpdatedMessagePtr;


/**
    The AttachmentMessage class is a generic message class that holds an entity and an
    attachment key name.

    Messages indicating specific events are derived from this message.

    The attachment key will match one of the keys in the "AttachedObjects" associative property
    on the entity.
*/
class EE_ECR_ENTRY AttachmentMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AttachmentMessage, efd::kMSGID_Attachment, efd::IMessage);
    /// @endcond

public:
    /// Default constructor sets the entity and the key to invalid values.
    inline AttachmentMessage();

    /// Constructor sets the entity and key.
    inline AttachmentMessage(egf::Entity* pEntity, const efd::utf8string& key);

    /// Destructor.
    inline virtual ~AttachmentMessage();

    /// The factory for creating messages.
    static efd::IBasePtr FactoryMethod();

    /// Push the message contents to a data stream.
    virtual void Serialize(efd::Archive& ar);

    /// Get the entity pointer.
    ///
    /// The return value will be NULL if not valid.
    inline virtual egf::Entity* GetEntity() const;

    /// Set the entity pointer.
    inline virtual void SetEntity(egf::Entity* pEntity);

    /// Get the attachment key.
    inline virtual efd::utf8string GetKey() const;

    /// Set the scene graph handle.
    inline virtual void SetKey(const efd::utf8string& key);

protected:
    egf::Entity* m_pEntity;
    efd::utf8string m_key;
};
typedef efd::SmartPointer<AttachmentMessage> AttachmentMessagePtr;


/**
    The AttachmentMadeMessage class is sent when a new scene graph attachment is made.

    The entity to which something was attached is provided, along with the key for the
    specific attachment location.
*/
class EE_ECR_ENTRY AttachmentMadeMessage : public ecr::AttachmentMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AttachmentMadeMessage, efd::kMSGID_AttachmentMade, ecr::AttachmentMessage);
    /// @endcond

public:
    /// Default constructor sets the entity and the key to invalid values.
    inline AttachmentMadeMessage();

    /// Constructor sets the entity and key.
    inline AttachmentMadeMessage(egf::Entity* pEntity, const efd::utf8string& key);

    /// Destructor.
    inline virtual ~AttachmentMadeMessage();

    /// The factory for creating messages.
    static efd::IBasePtr FactoryMethod();
};
typedef efd::SmartPointer<AttachmentMadeMessage> AttachmentMadeMessagePtr;


/**
    The AttachmentMadeMessage class is sent when a new scene graph attachment is made.

    The entity to which something was attached is provided, along with the key for the
    specific attachment location.
*/
class EE_ECR_ENTRY AttachmentBrokenMessage : public ecr::AttachmentMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        AttachmentBrokenMessage,
        efd::kMSGID_AttachmentBroken,
        ecr::AttachmentMessage);
    /// @endcond

public:
    /// Default constructor sets the entity and the key to invalid values.
    inline AttachmentBrokenMessage();

    /// Constructor sets the entity and key.
    inline AttachmentBrokenMessage(egf::Entity* pEntity, const efd::utf8string& key);

    /// Destructor.
    inline virtual ~AttachmentBrokenMessage();

    /// The factory for creating messages.
    static efd::IBasePtr FactoryMethod();
};
typedef efd::SmartPointer<AttachmentBrokenMessage> AttachmentBrokenMessagePtr;

} // end namespace ecr

#include "CoreRuntimeMessages.inl"

#endif //EE_CORERUNTIMEMESSAGES_H
