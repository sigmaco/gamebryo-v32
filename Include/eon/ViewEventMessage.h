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
#ifndef EE_VIEWEVENTMESSAGE_H
#define EE_VIEWEVENTMESSAGE_H

#include <eon/OnlineEntry.h>
#include <egf/EventMessage.h>
#include <efd/MessageFactory.h>
#include <efd/NetMessage.h>
#include <eon/eonMessageIDs.h>

namespace eon
{

//------------------------------------------------------------------------------------------------
class EE_EONENTRY ViewEventMessage : public efd::EnvelopeMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ViewEventMessage, efd::kMSGID_ViewEvent, efd::EnvelopeMessage);
    /// @endcond

public:
    /// Constructor creates an empty envelope message that can be filled from a stream
    ViewEventMessage();

    // NOTE: this part is just brainstorming, will the target ever need to be anything other than
    // a single entity ID?  We are sending this to a channel with potentially many listeners.
    // These listeners include multiple replications of the same entity but also potentially
    // include many different entities.  So what sort of targeting cases are needed, if any?
    enum DeliveryType
    {
        kDT_Invalid,
        kDT_Entity,     //< To a specific entity
        kDT_Model,      //< To all entities of a given model type that use the arrival channel
        kDT_All,        //< To all entities that use the arrival channel
    };

    /**
        Constructor which creates an envelope message class containing the given payload message
        for sending to the specified category.

        @param pMessage The message to add to the envelope message
        @param cat The category the message will be sent on
    */
    ViewEventMessage(egf::EventMessage* pMessage, const efd::Category& cat);

    virtual void SetTargetEntity(egf::EntityID i_target);
    virtual void SetTargetModel(const efd::utf8string& i_target);
    virtual void SetTargetAll();

    virtual DeliveryType GetDeliveryType() const;

    virtual egf::EntityID GetTargetEntityID() const;

    /**
        Calls EnvelopeMessage::GetContents and casts results to egf::EventMessage*
        @see EnvelopeMessage::GetContents
    */
    virtual const egf::EventMessage* GetContents(efd::MessageFactory* pMessageFactory) const;

    /**
        Calls EnvelopeMessage::SetChild. Takes a egf::EventMessage* instead of IMessage*
        @see EnvelopeMessage::SetChild
    */
    virtual void SetChild(egf::EventMessage *pMessage);

    /**
        Method to convert this class to a stream

        @param ar Reference to a stream to write this class contents into
    */
    virtual void Serialize(efd::Archive& ar);

protected:
    efd::UInt32 m_deliveryType;
    egf::EntityID m_targetEntity;
    efd::utf8string m_targetModel;
};

/// A smart pointer (reference counting, self deleting pointer) for the ViewEventMessage class
typedef efd::SmartPointer<ViewEventMessage> ViewEventMessagePtr;


} // end namespace eon

#endif // EE_VIEWEVENTMESSAGE_H
