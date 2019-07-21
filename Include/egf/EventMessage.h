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
#ifndef EE_EVENTMESSAGE_H
#define EE_EVENTMESSAGE_H

#include <efd/UniversalTypes.h>
#include <efd/utf8string.h>
#include <efd/ParameterList.h>
#include <efdNetwork/NetCategory.h>
#include <egf/egfLibType.h>
#include <efd/IMessage.h>
#include <egf/EntityID.h>
#include <egf/EntityTypes.h>
#include <egf/EventID.h>
#include <egf/egfMessageIDs.h>
#include <egf/egfClassIDs.h>


namespace egf
{

/// Define the base class for entity-based messages
class EE_EGF_ENTRY EventMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EventMessage, efd::kCLASSID_EventMessage, efd::IMessage);
    /// @endcond

public:

    /**
        Default constructor
    */
    EventMessage();

    /**
        Constructor

        @param msgClassID The type of message being created
        @param senderID The sender of the event
        @param eventID The ID of the event that for return value events
        @param behaviorID The behavior to execute
        @param mixinModelID A base model that defines the behavior to run.  The target must mix-in this model.
        @param invokeModelID The exact model to invoke the behavior from, or 0 to call the most derived.
        @param delay Time to delay execution of the event
        @param pParams The parameters for the behavior event
        @param needResponse True if the caller needs a return value event
                           message to be sent after the behavior completes
    */
    EventMessage(efd::ClassID msgClassID,
                  egf::EntityID senderID,
                  egf::EventID eventID,
                  egf::BehaviorID behaviorID,
                  egf::FlatModelID mixinModelID,
                  egf::FlatModelID invokeModelID,
                  efd::TimeType delay = 0,
                  efd::ParameterList* pParams = NULL,
                  bool needResponse = false);


public:
    /**
        Construct an event message with parameters

        @param senderID The sender of the event
        @param behaviorID The behavior to execute
        @param mixinModelID A base model that defines the behavior to run.  The target must
                mix-in this model.
        @param invokeModelID The exact model to invoke the behavior from, or 0 to call the
                most derived.
        @param delay Time to delay execution of the event
        @param pParams The parameters for the behavior event
        @param needResponse True if the caller needs a return value event message to be sent
                after the behavior completes
    */
    static EventMessage* CreateEvent(egf::EntityID senderID,
                                      egf::FlatModelID mixinModelID,
                                      egf::FlatModelID invokeModelID,
                                      egf::BehaviorID behaviorID,
                                      efd::TimeType delay = 0,
                                      efd::ParameterList* pParams = NULL,
                                      bool needResponse = false);

    /**
        Construct a return message with parameters

        @param senderID The sender of the return
        @param eventID The ID of the event that for return value events
        @param pReturnVals The return values for the callback behavior
    */
    static EventMessage* CreateReturn(
        egf::EntityID senderID,
        egf::EventID eventID,
        efd::ParameterList* pReturnVals = NULL);

    /**
        Construct an event cancel message with parameters

        @param senderID The sender of the cancel event
        @param eventID The ID of the event that will be cancelled
    */
    static EventMessage* CreateCancel(
        egf::EntityID senderID,
        egf::EventID eventID);

    /// @name IStreamable overrides
    //@{
    virtual void Serialize(efd::Archive& ar);
    //@}

    /**
        Retrieves the entity ID that sent this event

        @return EntityID The entity that sent this event
    */
    inline egf::EntityID GetSenderID() const
    {
        return m_senderID;
    }

    /**
        Sets the identifier of the entity that is sending this event

        @param entityID The entity that is sending this event
    */
    inline void SetSenderID(egf::EntityID entityID)
    {
        m_senderID = entityID;
    }

    /**
        Retrieves the model ID that must be mixed into the target entity for this event to be valid.

        @return EntityID The mixed in model ID
    */
    inline egf::FlatModelID GetMixinModelID() const
    {
        return m_mixinModelID;
    }

    /**
       Retrieves the model ID of the specific implementation to invoke.  Normally this is left as
       zero in order to use virtual invoking semantics which calls the most derived implementation.

       @return FlatModelID The implementing model, or 0 to use virtual behavior semantics.
    */
    inline egf::FlatModelID GetInvokeModelID() const
    {
        return m_invokeModelID;
    }

    /**
        Retrieves the behavior identifier to be executed during this event.

        @return BehaviorID The behavior to execute
    */
    inline egf::BehaviorID GetBehaviorID() const
    {
        return m_behaviorID;
    }

    /**
        Retrieves the parameters for the behavior

        @return ParameterList* List of parameters for the behavior
    */
    inline efd::ParameterList* GetParameters() const
    {
        return m_spParameterList.data();
    }

    /**
        Sets the behavior that should be executed when this event is received and processed.

        @param mixinModelID The target entity must mix-in this model type or else the behavior
              request is considered invalid.  This acts as type safety of the target model.
        @param invokeModelID Normally this ID is set to 0 which results in calling the most-
              derived implementation of the given behavior on the target entity.  This is similar
              to how C++ virtual methods operate.  Sometimes you need to call a specific
              implementation of the behavior, in those rare cases you set this model ID.
        @param behaviorID The behavior to execute
        @param spStrm List of parameters that the behavior requires
        @param needResponse True if the caller needs a return value event
                message to be sent after the behavior completes
    */
    virtual void SetBehavior(egf::FlatModelID mixinModelID,
                              egf::FlatModelID invokeModelID,
                              egf::BehaviorID behaviorID,
                              efd::ParameterListPtr spStrm,
                              bool needResponse = false);

    /**
        Gets the time to wait before executing this behavior event

        @return float Time in seconds to delay
    */
    inline efd::TimeType GetDelay() const
    {
        return m_delay;
    }

    /**
        Sets the time to wait before executing this behavior event

        @param delay Time in seconds to delay
    */
    inline void SetDelay(efd::TimeType delay)
    {
        m_delay = delay;
    }


    /**
        Retrieves the unique ID assigned to this event

        @return EventID The unique event ID
    */
    inline egf::EventID GetEventID() const
    {
        return m_eventID;
    }

    /**
        Informs the entity that executes the event that a response is required

        @return True is a response is required.
    */
    inline bool NeedResponse() const
    {
        return m_needResponse;
    }

    /**
        Sets the m_eventID member

        @param[in] eID The eventID to store
    */
    inline void SetEventID(egf::EventID eID)
    {
        m_eventID = eID;
    }

    /**
        Sets the m_behaviorID member

        @param[in] bID The behavior ID to store
    */
    inline void SeBehaviorID(egf::BehaviorID bID)
    {
        m_behaviorID = bID;
    }

    /**
        Sets the m_needResponse member

        @param[in] needresponse The boolean to store for m_needResponse
    */
    inline void SetNeedResponse(bool needresponse)
    {
        m_needResponse = needresponse;
    }

    /**
        Sets the ParameterList from the provided list. The data is copied into another parameter
        list which will share the memory buffer used for storage.

        @param[in] data The data stream to store
    */
    inline void SetParams(efd::ParameterList* data)
    {
        m_spParameterList = data;
    }

protected:
    egf::EventID m_eventID;
    egf::EntityID m_senderID;
    egf::BehaviorID m_behaviorID;

    /// The target entity must mix-in this model type in order for this event message to be valid.
    /// This is basically a type safety enforcement.
    egf::FlatModelID m_mixinModelID;

    /// Normal event messages act like virtual C++ methods, the most derived implementation is
    /// what gets called.  Occasionally, however, you need to call a specific implementation of
    /// a behavior.  In those cases you set the m_invokeModelID to the specific model who's
    /// behavior is to be invoked.
    egf::FlatModelID m_invokeModelID;

    /// Storage for the parameters
    efd::ParameterListPtr m_spParameterList;
    efd::TimeType m_delay;
    bool m_needResponse;
};

/**
    A smart pointer (reference counting, self deleting pointer) for the
    EventMessage class
*/
typedef efd::SmartPointer<EventMessage> EventMessagePtr;


} // end namespace egf


#endif // EE_EVENTMESSAGE_H
