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
#ifndef EE_INPUTSERVICEEVENT_H
#define EE_INPUTSERVICEEVENT_H

#include <efd/IMessage.h>
#include <efd/MessageService.h>
#include "ecrInputLibType.h"
#include "InputServiceActionBase.h"



namespace ecrInput
{

/**
    This class represents an event.

    An event contains one or more actions and sends messages
    if the actions are triggered in the way specified by event flags. The type of message sent
    can also be specified by the event flags.

    The magnitude field of an event message has a varied interpretation depending on the
    event flags. For ACTION_COMBO events, the magnitude is the time it took for all of the
    sequence to be activated. For ACTION_AND events, the magnitude is that of the last action
    in the event. For other events (OR), the magnitude is that of the first action that was
    found active. The coordinates in a message are those from the last action to activate in
    an ACTION_COMBO or ACTION_AND, or whichever action activated in the OR case.
*/
class EE_ECRINPUT_ENTRY InputServiceEvent : public efd::MemObject
{
public:
    /// @name Construction and Destruction.
    //@{
    /**
        Constructor.
        @param msgCat Category for these messages.
        @param flags Flags to use for triggering this event. An ORed combination of
            ecrInput::InputService::EventFlags.
        @param timeout Combo timeout.
    */
    inline InputServiceEvent(
        const efd::Category& msgCat,
        efd::UInt32 flags,
        efd::Float32 timeout = 1.0f);

    /// Virtual destructor.
    virtual ~InputServiceEvent();
    //@}

    /// Add an action to this event. Once added, this event owns the action pointer.
    inline efd::Bool AddAction(InputServiceActionBase* pAction);

    /// Returns the number of actions in this event.
    inline efd::UInt32 GetActionCount();

    /// Returns the action at the given index.
    inline InputServiceActionBase* GetActionAt(efd::UInt32 idx);

    /// Removes the action at the given index.
    inline efd::Bool RemoveActionAt(efd::UInt32 idx);

    /// Removes all actions.
    inline void RemoveAllActions();

    /// @cond EMERGENT_INTERNAL

    /// Input processing.  It calls ProcessInput on all actions and determines
    /// if a message needs to be sent.  Actions on the skip list are never
    /// triggered. Actions on the execute list always trigger regardless of input state.
    virtual efd::Bool ProcessInput(
        InputService* pInput,
        const efd::utf8string& eventName,
        efd::Float32 currentTime,
        efd::set<efd::UInt32>& skipList,
        efd::set<efd::UInt32>& execList);

    /// Save event parameters and all its actions to XML.
    efd::Bool SaveXml(efd::TiXmlElement* pElement);

    /// Load event parameters and saved actions from XML.
    efd::Bool LoadXml(efd::TiXmlElement* pElement);

    /// @endcond

    /// Returns the category of the message
    inline efd::Category GetMsgCategory() const;

    /// Sets the category of the message.
    inline void SetMsgCategory(const efd::Category& msgType);

    /// Returns the event flags.
    ///
    /// The return value is an ORed combination of ecrInput::InputService::EventFlags.
    inline efd::UInt32 GetFlags() const;

    /// Sets event flags.
    ///
    /// The parameter must be an ORed combination of ecrInput::InputService::EventFlags.
    inline void SetFlags(efd::UInt32 flags);

    /// Returns the timeout for combo events.
    inline efd::Float32 GetTimeout() const;

    /// Sets the timeout for combo events.
    inline void SetTimeout(efd::Float32 timeout);

    /// Load translation maps for event flags and action classes.
    static void LoadTranslationMap();

    /// Unload translation maps for event flags and action classes.
    static void UnloadTranslationMap();


protected:
    // Event data
    efd::Category m_msgCategory;
    efd::UInt32 m_flags;
    efd::UInt32 m_currentAction;
    efd::Float32 m_timeout;
    efd::Float32 m_comboStartTime;
    efd::Float32 m_lastActionTime;

    efd::vector<InputServiceActionBase*> m_actions;

    /// Translation map of flags string -> flags value.
    static FlagMap ms_eventFlagsMap;

    /// Translation map of action class string -> action class value.
    static FlagMap ms_actionClsIDMap;
};

} // end namespace ecrInput

#include "InputServiceEvent.inl"

#endif // EE_INPUTSERVICEEVENT_H
