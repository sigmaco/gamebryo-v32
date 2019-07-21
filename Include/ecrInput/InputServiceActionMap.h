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
#ifndef EE_INPUTSERVICEACTIONMAP_H
#define EE_INPUTSERVICEACTIONMAP_H

#include <efd/IMessage.h>
#include <efd/MessageService.h>
#include "InputServiceEvent.h"


namespace ecrInput
{

// Forward declaration:
class InputService;


/**
    An action map encapsulates a collection of named events.

    An action map is internally a collection of events of type ecrInput::InputServiceEvent.
    Events are stored in a map<name, pointer>
    container. When an action map is active, it receives ProcessInput() calls from InputService
    each tick and calls the same method on all contained events. Depending on the
    flags for a given event, and the set of actions that have been triggered by input, a message
    may be sent for the event, with a message category as stored in the event.

    The same action may appear in multiple events. When events are processed to see if they
    have fired, the events with the ACTION_COMBO flag set are checked first. Any event that
    seems to be part of a combo will not be considered for ACTION_AND or default (OR) events.
    However, the same event may be considered for multiple ACTION_COMBO events in one tick.

    A combo event fires when all of the actions in the event occur, in the order they appear
    in the event, with no more that the timeout time passing between each successive action.
    The actions may occur over multiple ticks of the service. If the timeout condition fails
    partway through an action, all of the actions that contributed to the combo up to the time
    it fails are considered as activated on the current tick for other events using the same
    action.

    An action map defines methods for adding, removing and querying events. There are two ways to
    add an event: add an existing event class (suitable for custom events) or specify event
    parameters only. In the latter case, the action map creates the event instance, sets up its
    parameters, and adds it to the event map. See ecrInput::InputService::AddAction,
    ecrInput::InputService::AddDPad and ecrInput::InputService::AddStick.
*/
class EE_ECRINPUT_ENTRY InputServiceActionMap : public efd::MemObject
{
public:
    typedef efd::map<efd::utf8string, InputServiceEvent*> InputServiceEventMap;
    typedef InputServiceEventMap::const_iterator Iterator;

    /// @name Construction and Destruction.
    //@{
    /**
        Constructor.
        @param name Name of this action map.
        @param pMessageService Pointer to the message service.

    */
    inline InputServiceActionMap(
        const efd::utf8string& name,
        efd::MessageService* pMessageService);

    /// Virtual Destructor.
    virtual ~InputServiceActionMap();
    //@}

    /// Calls ProcessInput on all contained events.
    ///
    /// The ecrInput::InputService OnTick method calls this function. Applications must not.
    efd::Bool ProcessInput(InputService* pInput, efd::Float32 currentTime);

    /// Returns the name of this action map.
    inline const efd::utf8string& GetName() const;

    /// Sets the name of this action map.
    inline void SetName(const efd::utf8string& name);

    /**
        Create an event and add it to the action map. If the named event already exists, it is
        replaced by this one.
        @param name Name of the event. This should be unique.
        @param msgCat ID of message, sent by this event.
        @param flags Event flags. An ORed combination of ecrInput::InputService::EventFlags.
        @param timeout Sets maximum time between actions for combos. Default timeout is 1 second.
        @return Returns a pointer to event or NULL in case of error\n
    */
    inline InputServiceEvent* AddEvent(
        const efd::utf8string& name,
        const efd::Category& msgCat,
        efd::UInt32 flags,
        efd::Float32 timeout = 1.0f);

    /// Add an event to the action map with the specified name. If the named event already
    /// exists, it is replaced by the new one.
    inline void AddEvent(const efd::utf8string& name, InputServiceEvent* pEvent);

    /// Returns a pointer to the event with given name or NULL if it cannot be found.
    inline InputServiceEvent* FindEvent(const efd::utf8string& name) const;

    /// Returns the number of events in this action map.
    inline efd::UInt32 GetEventCount() const;

    /// Returns an iterator for the first event in the action map.
    inline InputServiceActionMap::Iterator GetFirstEvent() const;

    /**
        Queries the name and pointer of a given event and advances the iterator to the next
        element.

        Returns true on success and false if there are no more events.
    */
    inline efd::Bool GetNextEvent(
        InputServiceActionMap::Iterator& itor,
        efd::utf8string& name,
        InputServiceEvent*& pEvent) const;

    /// Removes the event with the name.
    ///
    /// Returns true on success.
    inline efd::Bool RemoveEvent(const efd::utf8string& name);

    /// Clears the action map.
    ///
    /// All events are removed and destroyed.
    inline void DeleteAllEvents();

    /// @cond EMERGENT_INTERNAL

    /// Set the message service for this action map.
    inline void SetMessageService(efd::MessageService* messageService);

    /// Save action map contents into XML.
    efd::Bool SaveXml(efd::TiXmlElement* pElement);

    /// Load action map contents from XML.
    efd::Bool LoadXml(efd::TiXmlElement* pElement);

    /// @endcond

protected:
    /// Name of the current action map
    efd::utf8string m_name;

    /// The message service needed to notify when an action map is produced.
    efd::MessageService* m_pMessageService;

    /// All of the events that compose this action map
    InputServiceEventMap m_events;
};

} // end namespace ecrInput

#include "InputServiceActionMap.inl"

#endif // EE_INPUTSERVICEACTIONMAP_H
