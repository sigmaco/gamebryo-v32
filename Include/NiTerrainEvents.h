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
#ifndef NITERRAINEVENTS_H
#define NITERRAINEVENTS_H

#include "NiTerrainLibType.h"
#include <NiRefObject.h>

/**
    A class used to define unique TypeID's for NiTerrainEventHandler objects. 
    This class allows delegate objects to be checked for matching types, and if they match,
    then their equality can be determined accurately.
*/
class NITERRAIN_ENTRY NiTerrainEventDelegateTypeID
{
public:
    /// Constructor
    NiTerrainEventDelegateTypeID();

    /// Equality operator
    bool operator==(const NiTerrainEventDelegateTypeID& kOther) const;

protected:
    /// The typeID value being stored in this object
    efd::UInt32 m_uiTypeID;

private:
    /// The static variable used to ensure that all instances of this object have a different typeID
    static efd::UInt32 ms_uiNextValue;
};

/**
    This class provides an interface through which Events can call any handlers that are attached
    to them, regardless of what the handler is designed to achieve. 

    Both the sender and EventArgs types are defined by the Event object using the handler. See
    the documentation for the NiTerrainEvent class for more information.
*/
template <class Sender, class EventArgs>
class NiTerrainEventHandlerBase : public NiMemObject
{
public:
   
    /// Constructor
    NiTerrainEventHandlerBase();
    /// Destructor
    virtual ~NiTerrainEventHandlerBase();
    /// Equality operator
    bool operator==(const NiTerrainEventHandlerBase<Sender, EventArgs>& kOtherHandler) const;

    /**
        This function is called whenever the owning NiTerrainEvent
        Virtual function implemented by sub classes.

        @param pkSender The object that is raising the event
        @param kEventArgs The details of the event
    */
    virtual void HandleEvent(Sender* pkSender, EventArgs kEventArgs) = 0;

    /**
        This function is called to determine if another event handler may
        be attached to this handler's owning event. This may be used to enforce 
        only a certain number of callbacks, or limiting the number of times a specific
        handler may be invoked
    */
    virtual bool CanAttachHandler(
        const NiTerrainEventHandlerBase<Sender, EventArgs>* kOtherHandler);

    /**
        This function is called to determine if this handler may be detached from the owning 
        event. This may be used to add reference counting to event handlers if necessary.
    */
    virtual bool CanDetachHandler();

protected:

    /**
        This function is called when attempting to compare two handlers of the same type.
        The kOtherHandler parameter is guaranteed to be the same type as the object
        it is being called on, as the HandlerType objects have already been compared. 
        Virtual function implemented by sub classes.

        @param kOtherHandler the other handler to compare this one to
        @return True if the two handlers are the same
    */
    virtual bool Equals(const NiTerrainEventHandlerBase<Sender, EventArgs>& kOtherHandler)
        const = 0;

    /**
        This function is called to retrieve a handler type object to allow handlers
        to be compared to eachother even when they are of different types.
        Virtual function implemented by sub classes.

        @return A NiTerrainEventDelegateTypeID object unique to this object's type.
    */
    virtual const NiTerrainEventDelegateTypeID& GetHandlerType() const = 0;
};

/**
    This class implements the NiTerrainEventHandlerBase class with the ability to callback
    to arbitrary member functions on target objects. When this handler is invoked the following 
    function call is made:

    pkTarget->kCallback(Sender* pkSender, EventArgs kEventArgs)

    This class will not compile if the callback function does not have the correct signature.
*/
template <class Sender, class EventArgs, class TargetType>
class NiTerrainEventHandlerDelegate : public NiTerrainEventHandlerBase<Sender, EventArgs>
{
public:
    /// The type of the base class
    typedef NiTerrainEventHandlerBase<Sender, EventArgs> BaseType;
    /// The type of the callback function on the referrer type
    typedef void (TargetType::*CallbackType)(Sender* pkSender, EventArgs kEventArgs);
    /// The type of object that this delegate is
    typedef NiTerrainEventHandlerDelegate<Sender, EventArgs, TargetType> DelegateType;

    /**
        Constructor

        @param pkTarget The target object to callback onto
        @param kCallback The function to callback on the target when the event is raised
    */
    NiTerrainEventHandlerDelegate(TargetType* pkTarget, CallbackType kCallback);

    /// @see NiTerrainEventHandlerBase::HandleEvent
    virtual void HandleEvent(Sender* pkSender, EventArgs kEventArgs);

protected:
    /// @see NiTerrainEventHandlerBase::Equals
    virtual bool Equals(const BaseType& kOtherHandlerBase) const;

    /// @see NiTerrainEventHandlerBase::GetHandlerType
    virtual const NiTerrainEventDelegateTypeID& GetHandlerType() const;

    /// The target object to callback onto
    TargetType* m_pkTarget;
    /// The callback function to invoke on the target object
    CallbackType m_kTargetCallback;
    /// The typeID of this particular type of delegate
    static NiTerrainEventDelegateTypeID ms_kTypeID;
};

/**
    This class defines an event object that when "Raised" will callback to a set of arbitrary
    handler objects that have been registered upon it.
*/
template <class Sender, class EventArgs>
class NiTerrainEvent : public NiRefObject
{
public:
    /// The type of this event object
    typedef NiTerrainEvent<Sender, EventArgs> SelfType;
    /// The type of handlers this object requires
    typedef NiTerrainEventHandlerBase<Sender, EventArgs> HandlerType;

    /// Destructor
    ~NiTerrainEvent();

    /**
        Attach a handler to the event to be notified when the event is raised
        The event will take over ownership of the handler object that is passed in.

        @param pkHandler The handler object. 
    */
    bool AttachHandler(HandlerType* pkHandler);

    /**
        Detach a handler from the event. The passed in handler will be compared to the handlers
        attached to the event and if a matching one exists, one instance of it will be removed.

        @param pkHandler The handler object to look for and detach.
    */
    void DetachHandler(const HandlerType* pkHandler);

    /**
        Query the event to discover if a handler matching the passed in one has been registered
        on this event.

        @param pkHandler The handler object to look for
        @return A pointer to the existing handler if a matching instance exists on the event.
    */  
    HandlerType* FindHandler(const HandlerType* pkHandler) const;

    /**
        Remove all handlers from the event
    */
    void ClearHandlers();

    /**
        Raise the event and cause all attached handlers to be invoked with the given 
        parameter values.

        @param pkSender The object raising the event
        @param kEventArgs The event arguments
    */
    void Raise(Sender* pkSender, EventArgs kEventArgs);

    /**
        Override of the default assignment operator that does not copy event handler objects
        to the other object. This assignment operator essentially does nothing.
    */
    SelfType& operator=(const SelfType& kOther);
    
protected:
    /// A typedef to define a list of handler objects
    typedef efd::vector<HandlerType*> HandlerList;
    /// The list of handlers attached to this event
    HandlerList m_kHandlers;
};

/**
    This class defines a base class from which other classes may derive to allow subclasses
    to attach 'observers'. These observers may then listen to events that are raised by the subclass
*/
template <class ObservationType, class EventArgs = efd::UInt32>
class NiTerrainObservable
{
public:
    /**
        Attach an observer to this observable object. The observer will be notified through the
        registered member function whenever this class raises an event. The observer is invoked
        through the following function call:
        
        pkTarget->kCallback(ObservationType* pkSender, EventArgs kEventArgs)

        This function will not compile if the callback function does not have the correct
        signature.

        @param pkTarget The observer object to callback onto
        @param pkCallbackFunction The member function to call on the target object
    */
    template <class TargetType, typename CallbackType>
    void AttachObserver(TargetType* pkTarget, CallbackType pkCallbackFunction);

    /**
        Detach an observer from this observable object. 
        
        @param pkTarget The observer object to callback onto
        @param pkCallbackFunction The member function registered to call on the target object
    */
    template <class TargetType, typename CallbackType>
    void DetachObserver(TargetType* pkTarget, CallbackType pkCallbackFunction);

protected:

    /**
        Call this function to raise an event and sent the event arguments to all registered 
        observers.
    */
    void RaiseEvent(EventArgs kEventArgs);

private:
    /// A typedef defining the event type to use
    typedef NiTerrainEvent<ObservationType, EventArgs> EventType;
    /// The event hosted by this object
    EventType m_kNotifyChanged;
};

#include "NiTerrainEvents.inl"

#endif // NITERRAINEVENTS_H
