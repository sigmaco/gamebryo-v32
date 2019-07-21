// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed excekPt in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs, class TargetType> 
NiTerrainEventDelegateTypeID 
    NiTerrainEventHandlerDelegate<Sender, EventArgs, TargetType>::ms_kTypeID;

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline NiTerrainEventHandlerBase<Sender, EventArgs>::NiTerrainEventHandlerBase()
{
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline NiTerrainEventHandlerBase<Sender, EventArgs>::~NiTerrainEventHandlerBase()
{
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline bool NiTerrainEventHandlerBase<Sender, EventArgs>::CanAttachHandler(
    const NiTerrainEventHandlerBase<Sender, EventArgs>* pkOtherHandler)
{
    EE_UNUSED_ARG(pkOtherHandler);

    return true;
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline bool NiTerrainEventHandlerBase<Sender, EventArgs>::CanDetachHandler()
{
    return true;
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline bool NiTerrainEventHandlerBase<Sender, EventArgs>::operator==(
    const NiTerrainEventHandlerBase<Sender, EventArgs>& kOtherHandler) const
{
    if (kOtherHandler.GetHandlerType() == GetHandlerType())
        return Equals(kOtherHandler);
    else
        return false;
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs, class TargetType>
inline NiTerrainEventHandlerDelegate<Sender, EventArgs, TargetType>::NiTerrainEventHandlerDelegate(
    TargetType* pkTarget, CallbackType kCallback)
    : m_pkTarget(pkTarget)
    , m_kTargetCallback(kCallback)
{
}
//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs, class TargetType>
inline void NiTerrainEventHandlerDelegate<Sender, EventArgs, TargetType>::HandleEvent(
    Sender* pkSender, EventArgs kEventArgs)
{
    if (m_pkTarget)
    {
        (m_pkTarget->*m_kTargetCallback)(pkSender, kEventArgs);
    }
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs, class TargetType>
inline bool NiTerrainEventHandlerDelegate<Sender, EventArgs, TargetType>::Equals(
    const NiTerrainEventHandlerBase<Sender, EventArgs>& kOtherHandlerBase) const
{
    const DelegateType& kOtherHandler = (const DelegateType&)kOtherHandlerBase;
    bool bResult = (
        m_pkTarget == kOtherHandler.m_pkTarget &&
        m_kTargetCallback == kOtherHandler.m_kTargetCallback);
    return bResult;
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs, class TargetType>
inline const NiTerrainEventDelegateTypeID& 
    NiTerrainEventHandlerDelegate<Sender, EventArgs, TargetType>::GetHandlerType() const
{
    return DelegateType::ms_kTypeID;
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline NiTerrainEvent<Sender, EventArgs>::~NiTerrainEvent()
{
    ClearHandlers();
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline bool NiTerrainEvent<Sender, EventArgs>::AttachHandler(HandlerType* pkHandler)
{
    bool bCanAttach = true;

    typename HandlerList::iterator kIter;
    for (kIter = m_kHandlers.begin(); kIter != m_kHandlers.end(); ++kIter)
    {
        HandlerType* pkExistingHandler = (*kIter);
        if (!pkExistingHandler->CanAttachHandler(pkHandler))
        {
            // Note: Do not simply 'break' here, we should
            // allow all handlers to know about the attachment event.
            bCanAttach = false;
        }
    }

    if (bCanAttach)
        m_kHandlers.push_back(pkHandler);

    return bCanAttach;
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline void NiTerrainEvent<Sender, EventArgs>::DetachHandler(const HandlerType* pkHandler)
{
    typename HandlerList::iterator kIter;
    for (kIter = m_kHandlers.begin(); kIter != m_kHandlers.end(); ++kIter)
    {
        HandlerType* pkExistingHandler = (*kIter);
        if (*pkExistingHandler == *pkHandler)
        {
            if (pkExistingHandler->CanDetachHandler())
            {
                NiDelete (*kIter); 
                m_kHandlers.erase(kIter);
                break;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline typename NiTerrainEvent<Sender, EventArgs>::HandlerType* 
    NiTerrainEvent<Sender, EventArgs>::FindHandler(const HandlerType* pkHandler) 
    const
{
    typename HandlerList::const_iterator kIter;
    for (kIter = m_kHandlers.begin(); kIter != m_kHandlers.end(); ++kIter)
    {
        if (*(*kIter) == *pkHandler)
        {
            return *kIter;
        }
    }
    return false;
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline void NiTerrainEvent<Sender, EventArgs>::ClearHandlers()
{
    typename HandlerList::iterator kIter;
    for (kIter = m_kHandlers.begin(); kIter != m_kHandlers.end(); ++kIter)
    {
        NiDelete (*kIter);
    }
    m_kHandlers.clear();
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline void NiTerrainEvent<Sender, EventArgs>::Raise(Sender* pkSender, EventArgs kEventArgs)
{
    typename HandlerList::iterator kIter;
    for (kIter = m_kHandlers.begin(); kIter != m_kHandlers.end(); ++kIter)
    {
        (*kIter)->HandleEvent(pkSender, kEventArgs);
    }
}

//-------------------------------------------------------------------------------------------------
template <class Sender, class EventArgs>
inline NiTerrainEvent<Sender, EventArgs>& NiTerrainEvent<Sender, EventArgs>::operator=(
    const SelfType& kOther)
{
    // Don't do anything - handlers aren't passed on
    EE_UNUSED_ARG(kOther);
    return *this;
}

//-------------------------------------------------------------------------------------------------
template <class ObservationType, class EventArgs>
template <class TargetType, typename CallbackType>
inline void NiTerrainObservable<ObservationType, EventArgs>::AttachObserver(TargetType* pkTarget, 
    CallbackType pkCallbackFunction)
{
    typename EventType::HandlerType* pkHandler = 
        NiNew NiTerrainEventHandlerDelegate<ObservationType, EventArgs, TargetType>(
            pkTarget, pkCallbackFunction);
    m_kNotifyChanged.AttachHandler(pkHandler);
}

//-------------------------------------------------------------------------------------------------
template <class ObservationType, class EventArgs>
template <class TargetType, typename CallbackType>
inline void NiTerrainObservable<ObservationType, EventArgs>::DetachObserver(TargetType* pkTarget, 
    CallbackType pkCallbackFunction)
{
    NiTerrainEventHandlerDelegate<ObservationType, EventArgs, TargetType> kDummyHandler(
        pkTarget, pkCallbackFunction);
    m_kNotifyChanged.DetachHandler(&kDummyHandler);
}

//-------------------------------------------------------------------------------------------------
template <class ObservationType, class EventArgs>
inline void NiTerrainObservable<ObservationType, EventArgs>::RaiseEvent(EventArgs kEventArgs)
{
    m_kNotifyChanged.Raise((ObservationType*)this, kEventArgs);
}

//-------------------------------------------------------------------------------------------------