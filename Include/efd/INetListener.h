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
#ifndef EE_INETLISTENER_H
#define EE_INETLISTENER_H

#include <efd/efdLibType.h>
#include <efd/ConnectionID.h>
#include <efd/efdClassIDs.h>

namespace efd
{
class INetCallback;

/// @cond EMERGENT_INTERNAL

/**
    A base interface for describing a low-level INetLib subscriber that listens for messages
    received on a specific Category. This includes both local and remote subscribers to that
    Category.

    This interface is used in the INetLib layer to route Category messages to interested
    subscribers via the INetCallback interface.

    In the majority of cases, the higher level MessageService-based IMessageTarget interface is
    more appropriate for handling data sent over the network. One potential use for subclasses
    of INetListener is to pre-process messages coming in over the wire, e.g. Encryption.
 */
class EE_EFD_ENTRY INetListener : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(INetListener, efd::kCLASSID_INetListener, efd::IBase);
    /// @endcond

public:
    /**
        Get the category this listener is listening on. It is valid for this to be kCID_INVALID.
        @return the category this listener is listening on.
    */
    virtual const ConnectionID& GetRemoteConnectionID()=0;

    /**
        Returns a pointer to the callback registered with this listener.
        It is valid for GetCallback to return NULL.
    */
    virtual INetCallback* GetCallback()=0;

};

/// A smart pointer (reference counting, self deleting pointer) for the INetListener class
typedef efd::SmartPointer<INetListener> INetListenerPtr;

/**
    Comparison operator for comparing two INetListener instances. We use this below when defining
    a Set of INetListener smart pointers.
 */
class INetListenerPtrLess
{
public:
    bool operator()(const INetListenerPtr& a, const INetListenerPtr& b)
    {
        return ((a->GetCallback() < b->GetCallback()) ||
               ((a->GetCallback() == b->GetCallback()) &&
                (a->GetRemoteConnectionID() < b->GetRemoteConnectionID())));
    }
};

/// A reference counted INetListener Set of smart pointer instances.
typedef efd::RefCountedMemObj< efd::set<INetListenerPtr,INetListenerPtrLess> > INetListenerSet;

/// A smart pointer to a reference counted INetListener smart pointer Set.
typedef efd::SmartPointer<INetListenerSet> INetListenerSetPtr;

/// A reference counted INetListener List of smart pointer instances.
typedef efd::RefCountedMemObj< efd::list< INetListenerPtr > > INetListenerList;

/// A smart pointer to a reference counted INetListener smart pointer List.
typedef efd::SmartPointer<INetListenerList> INetListenerListPtr;

/// @endcond

} //  namespace efd

#endif //EE_INETLISTENER_H
