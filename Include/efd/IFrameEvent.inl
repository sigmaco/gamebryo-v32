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


namespace efd
{

//------------------------------------------------------------------------------------------------
// IFrameEvent
//------------------------------------------------------------------------------------------------
inline IFrameEvent::IFrameEvent(const efd::utf8string& frameEventName, efd::SInt32 defaultPriority)
    : m_eventPriority(defaultPriority)
    , m_active(true)
    , m_name(frameEventName)
{
}

//------------------------------------------------------------------------------------------------
inline IFrameEvent::~IFrameEvent()
{
}

//------------------------------------------------------------------------------------------------
inline efd::SInt32 IFrameEvent::GetDefaultPriority() const
{
    return m_eventPriority;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& IFrameEvent::GetName() const
{
    return m_name;
}

//------------------------------------------------------------------------------------------------
inline bool IFrameEvent::IsActive() const
{
    return m_active;
}

//------------------------------------------------------------------------------------------------
inline void IFrameEvent::SetActive(bool active)
{
    m_active = active;
}

//------------------------------------------------------------------------------------------------
// FrameEventBase
//------------------------------------------------------------------------------------------------
template <typename HandlerInterface>
FrameEventBase<HandlerInterface>::FrameEventBase(
    const efd::utf8string& frameEventName,
    efd::SInt32 priority)
    : efd::IFrameEvent(frameEventName, priority)
{
}

//------------------------------------------------------------------------------------------------
template <typename HandlerInterface>
bool FrameEventBase<HandlerInterface>::AddHandler(efd::IBase* pBase, efd::SInt32 priority)
{
    HandlerInterface* pHandler = EE_DYNAMIC_CAST(HandlerInterface, pBase);
    EE_ASSERT(pHandler);
    if (!pHandler)
    {
        return false;
    }

    for (typename HandlerList::iterator iter = m_handlers.begin();
        iter != m_handlers.end();
        ++iter)
    {
        HandlerData& hd = *iter;
        if (priority > hd.m_priority)
        {
            m_handlers.insert(iter, HandlerData(pHandler, priority));
            return true;
        }
    }

    m_handlers.push_back(HandlerData(pHandler, priority));
    return true;
}

//------------------------------------------------------------------------------------------------
template <typename HandlerInterface>
bool FrameEventBase<HandlerInterface>::RemoveHandler(efd::IBase* pBase)
{
    HandlerInterface* pHandler = EE_DYNAMIC_CAST(HandlerInterface, pBase);
    EE_ASSERT(pHandler);
    if (!pHandler)
    {
        return false;
    }

    for (typename HandlerList::iterator iter = m_handlers.begin();
        iter != m_handlers.end();
        ++iter)
    {
        HandlerData& hd = *iter;
        if (pHandler == hd.m_handler)
        {
            m_handlers.erase(iter);
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------------------------
template<typename HandlerInterface>
efd::UInt32 FrameEventBase<HandlerInterface>::CountHandlers() const
{
    return m_handlers.size();
}

//------------------------------------------------------------------------------------------------
template<typename HandlerInterface>
FrameEventBase<HandlerInterface>::HandlerData::HandlerData(
    HandlerInterface* pHandler,
    efd::SInt32 priority)
    : m_priority(priority)
    , m_handler(pHandler)
{
}

//------------------------------------------------------------------------------------------------
// FrameEvent
//------------------------------------------------------------------------------------------------
template<typename HandlerInterface, void (HandlerInterface::*HandlerFunction)() >
FrameEvent<HandlerInterface, HandlerFunction>::FrameEvent(
    const efd::utf8string& frameEventName,
    efd::SInt32 priority)
    : FrameEventBase<HandlerInterface>(frameEventName, priority)
{
}

//------------------------------------------------------------------------------------------------
template<typename HandlerInterface, void (HandlerInterface::*HandlerFunction)() >
void FrameEvent<HandlerInterface, HandlerFunction>::DoEvent()
{
    // NOTE: GCC is not a very smart compiler, without the "this->" it is unable to realize that
    // m_handlers is a class member of this class.
    typename FrameEventBase<HandlerInterface>::HandlerList& handlers = this->m_handlers;
    for (typename FrameEventBase<HandlerInterface>::HandlerList::iterator iter = handlers.begin();
        iter != handlers.end();
        ++iter)
    {
        typename FrameEventBase<HandlerInterface>::HandlerData& hd = *iter;
        HandlerInterface* pHandler = hd.m_handler;
        (pHandler->*HandlerFunction)();
    }
}


//------------------------------------------------------------------------------------------------
// FrameEventWithOwner
//------------------------------------------------------------------------------------------------
template<
    typename OwningService,
    typename HandlerInterface,
    void (HandlerInterface::*HandlerFunction)(OwningService*) >
FrameEventWithOwner<OwningService, HandlerInterface, HandlerFunction>::FrameEventWithOwner(
    OwningService* pOwner,
    const efd::utf8string& frameEventName,
    efd::SInt32 priority)
    : FrameEventBase<HandlerInterface>(frameEventName, priority)
    , m_pFrameEventOwner(pOwner)
{
}

//------------------------------------------------------------------------------------------------
template<
    typename OwningService,
    typename HandlerInterface,
    void (HandlerInterface::*HandlerFunction)(OwningService*) >
void FrameEventWithOwner<OwningService, HandlerInterface, HandlerFunction>::DoEvent()
{
    // NOTE: GCC is not a very smart compiler, without the "this->" it is unable to realize that
    // m_handlers is a class member of this class.
    typename FrameEventBase<HandlerInterface>::HandlerList& handlers = this->m_handlers;
    for (typename FrameEventBase<HandlerInterface>::HandlerList::iterator iter = handlers.begin();
        iter != handlers.end();
        ++iter)
    {
        typename FrameEventBase<HandlerInterface>::HandlerData& hd = *iter;
        HandlerInterface* pHandler = hd.m_handler;
        (pHandler->*HandlerFunction)(m_pFrameEventOwner);
    }
}

//------------------------------------------------------------------------------------------------
// FrameEventWithSubclass
//------------------------------------------------------------------------------------------------
template<
    typename FinalType,
    typename HandlerInterface,
    void (HandlerInterface::*HandlerFunction)(FinalType*) >
FrameEventWithSubclass<FinalType, HandlerInterface, HandlerFunction>::FrameEventWithSubclass(
    const efd::utf8string& frameEventName,
    efd::SInt32 priority)
    : FrameEventBase<HandlerInterface>(frameEventName, priority)
{
}

//------------------------------------------------------------------------------------------------
template<
    typename FinalType,
    typename HandlerInterface,
    void (HandlerInterface::*HandlerFunction)(FinalType*) >
void FrameEventWithSubclass<FinalType, HandlerInterface, HandlerFunction>::DoEvent()
{
    // NOTE: GCC is not a very smart compiler, without the "this->" it is unable to realize that
    // m_handlers is a class member of this class.
    typename FrameEventBase<HandlerInterface>::HandlerList& handlers = this->m_handlers;
    for (typename FrameEventBase<HandlerInterface>::HandlerList::iterator iter = handlers.begin();
        iter != handlers.end();
        ++iter)
    {
        typename FrameEventBase<HandlerInterface>::HandlerData& hd = *iter;
        HandlerInterface* pHandler = hd.m_handler;
        (pHandler->*HandlerFunction)(static_cast<FinalType*>(this));
    }
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
