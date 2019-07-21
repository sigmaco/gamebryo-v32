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
#ifndef EE_NETLISTENER_H
#define EE_NETLISTENER_H

#include <efd/INetListener.h>
#include <efdNetwork/efdNetworkLibType.h>

namespace efd
{

/**
    Implementation of the INetListener interface.
 */
class EE_EFDNETWORK_ENTRY NetListener : public INetListener
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(NetListener, efd::kCLASSID_NetListener, INetListener);
    EE_DECLARE_CONCRETE_REFCOUNT
    /// @endcond
public:

    /// @name Construction and Destruction
    //@{
    NetListener(const ConnectionID& remoteConnectionID, INetCallback* callback = NULL);

    ~NetListener();
    //@}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual const ConnectionID& GetRemoteConnectionID();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual INetCallback* GetCallback();

private:
    // private constructor, so users can't use default
    NetListener();

protected:
    // private category of the connection of this listener
    ConnectionID m_remoteConnectionID;

    /// callback associated with this listener
    INetCallback* m_pCallback;
};

/// A smart pointer (reference counting, self deleting pointer) for the NetListener class.
typedef efd::SmartPointer<NetListener> NetListenerPtr;

} //  namespace efd

#include <efdNetwork/NetListener.inl>

#endif //EE_NETLISTENER_H
