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
#ifndef EE_ACTORMESSAGES_H
#define EE_ACTORMESSAGES_H

#include <efd/IDs.h>
#include <efd/IMessage.h>
#include <egf/IProperty.h>
#include <egf/Entity.h>
#include <NiNode.h>

#include "egmAnimationLibType.h"
#include <ecr/ecrMessageIDs.h>

namespace egmAnimation
{

/// This message is sent by the AnimationService when an actor has been loaded.
class EE_EGMANIMATION_ENTRY ActorAddedMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ActorAddedMessage, efd::kMSGID_ActorAdded, efd::IMessage);
    /// @endcond

public:

    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    inline ActorAddedMessage();

    /// Virtual destructor.
    inline virtual ~ActorAddedMessage();
    //@}

    /// Factory method to construct this class.
    static efd::IBasePtr FactoryMethod();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

    /// The entity that contains the added actor.
    egf::EntityPtr m_pEntity;
};
typedef efd::SmartPointer<ActorAddedMessage> ActorAddedMessagePtr;


/// This message is sent by the AnimationService when an actor has been unloaded.
class EE_EGMANIMATION_ENTRY ActorRemovedMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ActorRemovedMessage, efd::kMSGID_ActorRemoved, efd::IMessage);
    /// @endcond

public:

    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    inline ActorRemovedMessage();

    /// Virtual destructor.
    inline virtual ~ActorRemovedMessage();
    //@}

    /// Factory method to construct this class.
    static efd::IBasePtr FactoryMethod();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

    /// The entity that contains the removed actor.
    egf::EntityPtr m_pEntity;
};
typedef efd::SmartPointer<ActorRemovedMessage> ActorRemovedMessagePtr;

} // end namespace egmAnimation

#include "ActorMessages.inl"

#endif // EE_ACTORMESSAGES_H
