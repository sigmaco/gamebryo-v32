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
#ifndef EE_IFRAMEEVENT_H
#define EE_IFRAMEEVENT_H

#include <efd/efdLibType.h>
#include <efd/IBase.h>
#include <efd/utf8string.h>
#include <efd/SystemFrameworkEnums.h>
#include <efd/efdSystemServiceIDs.h>


namespace efd
{


/**
    A frame event is an event that occurs once per frame while your application is running for
    which various responders can perform work in a specific order. Services interested in the event
    can register to be notified each time the event occurs. Frame events work in conjunction with
    system services and are invoked interspersed with the registered services during the OnTick
    phase of each frame. As such, the events themselves use the same priority system that controls
    the ticking of services, but in addition each handler for the event is also registered with a
    specific priority and the handlers are invoked in priority order. In fact, frame events are very
    similar to sending a local message but with the addition of being able to control the handler
    invocation order using priority. The other difference between a local message and a frame event
    is that the handler methods for frame event are invoked through a specific interface function
    that is defined by the event itself. Objects handling a specific frame event must derive from
    an interface specific to the event they wish to handle and override a method which is also
    specific to that event. There is no "IMessage"-like payload associated with a frame event.

    Frame events are typically added to the ServiceManager during the OnInit phase of an owning
    system service and are removed during the OnShutdown phase of the same service. Well-known
    frame events can then be used by other services to implement functionality related to the event.
    Any service that utilizes a frame event should also register a service dependency on the owning
    system service during their OnPreInit call.

    A service can also register itself as a handler for it's own frame event as a method of
    effectively receiving multiple "OnTick"-like function calls each frame at different priorities.

    @note If a frame event has the exact same priority as a system service, the system service will
    receive its OnTick call before the frame event is executed.

    @note  Once added to the ServiceManager, it assumes ownership of the frame event object and
    will delete the object when it is removed.
*/
class EE_EFD_ENTRY IFrameEvent : public efd::MemObject
{
    EE_DECLARE_CONCRETE_REFCOUNT;

protected:
    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    inline IFrameEvent(const efd::utf8string& frameEventName, efd::SInt32 defaultPriority = 0);

    /// Destructor
    inline virtual ~IFrameEvent();
    //@}

public:
    /**
        This method is called by the efd::ServiceManager in response to requests to add a handler
        to a frame event. This method should not be called directly, instead you should call
        ServiceManager::AddFrameEventHandler.

        @param pHandler The handler object, which must implement the interface specific to this
            frame event.
        @param priority The priority at which to register the handler.
        @return True if the handler was added, false otherwise.
    */
    virtual bool AddHandler(efd::IBase* pHandler, efd::SInt32 priority) = 0;

    /**
        This method will be called once per frame for each active frame event. In turn it will
        invoke all registered handlers for the event in priority order. This method will be called
        interspersed with the various system service OnTick methods as controlled by the priority
        with which the frame event is registered with the service manager.
    */
    virtual void DoEvent() = 0;

    /**
        This method is called by the efd::ServiceManager in response to requests to remove a handler
        from a frame event. This method should not be called directly, instead you should call
        ServiceManager::RemoveFrameEventHandler.

        @param pHandler The handler object, which must implement the interface specific to this
            frame event.
        @return True if the handler was removed, false otherwise.
    */
    virtual bool RemoveHandler(efd::IBase* pHandler) = 0;

    /**
        Return the number of handlers for this frame event.
    */
    virtual efd::UInt32 CountHandlers() const = 0;

    /**
        Get the default priority for this frame event. The priority determines the order in which
        IFrameEvent::DoEvent and ISystemService::OnTick is called for all IFrameEvent and
        ISystemService objects registered with the ServiceManager. Higher numerical values are
        called before lower values. The priority can be overridden when the frame event is
        registered with the ServiceManager, but if it is not overridden than this default priority
        will be used.
    */
    inline efd::SInt32 GetDefaultPriority() const;

    /**
        Returns the name of this frame event. Each frame event must have a unique name and handlers
        are added to a frame event by referencing this name.

        @return The name of this frame event
    */
    inline const efd::utf8string& GetName() const;

    /**
        Determine if this frame event is active. Only active frame events are invoked each frame.
        Frame events can be deactivated without unregistering them in order to preserve the
        registered handlers.
    */
    inline bool IsActive() const;

    /**
        Activate or deactivate this frame event. Only active frame events are invoked each frame.
        Frame events default to the active state.
    */
    inline void SetActive(bool active);

protected:
    efd::SInt32 m_eventPriority;
    bool m_active;
    efd::utf8string m_name;
};


/**
    FrameEventBase provides a base class for implementing common functionality that is needed by
    all IFrameEvent implementations. It is an abstract class and cannot be used directly. Rather
    you should derive from this class and implement the DoEvent method.

    @note Several default derivations are provided including:
        - FrameEvent: A default implementation where the handler methods take no parameters
        - FrameEventWithOwner: A frame event that holds a pointer which is passed to the handlers.
        - FrameEventWithData: A frame event that passes itself cast to a derived type to handlers.
*/
template<typename HandlerInterface>
class FrameEventBase : public IFrameEvent
{
protected:
    /// Constructor
    FrameEventBase(const efd::utf8string& frameEventName, efd::SInt32 priority = 0);

    // Overridden base class methods inherit parent documentation
    virtual bool AddHandler(efd::IBase* pHandler, efd::SInt32 priority);
    virtual bool RemoveHandler(efd::IBase* pHandler);
    virtual efd::UInt32 CountHandlers() const;

    /// Data for a single callback handler
    struct HandlerData
    {
        HandlerData(HandlerInterface* pHandler, efd::SInt32 priority);

        efd::SInt32 m_priority;
        efd::SmartPointer<HandlerInterface> m_handler;
    };

    /// Storage type for callback handler list
    typedef efd::vector<HandlerData> HandlerList;

    /// A list of handlers to invoke during DoEvent sorted in priority order
    HandlerList m_handlers;
};


/**
    A FrameEvent is the default IFrameEvent implementation where the handling interface function
    takes no parameters.
*/
template<typename HandlerInterface, void (HandlerInterface::*HandlerFunction)() >
class FrameEvent : public FrameEventBase<HandlerInterface>
{
public:
    /// Constructor
    FrameEvent(const efd::utf8string& frameEventName, efd::SInt32 priority = 0);

protected:
    // Overridden base class methods inherit parent documentation
    virtual void DoEvent();
};


/**
    A FrameEventWithOwner is an IFrameEvent implementation where the event handler functions
    accept a pointer to the owning object, typically an ISystemService derived class, as a
    parameter. The event is initialized with the owning object pointer.
*/
template<
    typename OwningService,
    typename HandlerInterface,
    void (HandlerInterface::*HandlerFunction)(OwningService*) >
class FrameEventWithOwner : public FrameEventBase<HandlerInterface>
{
public:
    /// Constructor
    FrameEventWithOwner(
        OwningService* pOwner,
        const efd::utf8string& frameEventName,
        efd::SInt32 priority = 0);

protected:
    // Overridden base class methods inherit parent documentation
    virtual void DoEvent();

    /// The owning object which is typically the ISystemService derived class that owns the frame
    /// event.
    OwningService* m_pFrameEventOwner;
};


/**
    A FrameEventWithSubclass is an IFrameEvent implementation where the frame event instance itself
    is passed to the event handler functions. The FinalType template argument must be a class that
    derives from FrameEventWithSubclass and is expected to implement additional data members or
    methods that will be available to the handler method. The FinalType instance is allocated and
    passed to ServiceManager::RegisterFrameEvent and then passes itself to each handler.

    @note Use this class carefully, it performs a static_cast to convert from FrameEventWithSubclass
    to the FinalType and such conversions are not always safe.

    @note In general frame event objects are not expected to maintain dynamic state, they are
    primarily just containers for the handler lists. If you need to maintain complex or dynamic
    state, consider placing that data into a system service and use the FrameEventWithOwner class
    instead.
*/
template<
    typename FinalType,
    typename HandlerInterface,
    void (HandlerInterface::*HandlerFunction)(FinalType*) >
class FrameEventWithSubclass : public FrameEventBase<HandlerInterface>
{
protected:
    /// Constructor
    FrameEventWithSubclass(const efd::utf8string& frameEventName, efd::SInt32 priority = 0);

    // Overridden base class methods inherit parent documentation
    virtual void DoEvent();
};

} // end namespace efd

#include <efd/IFrameEvent.inl>

#endif // EE_IFRAMEEVENT_H
