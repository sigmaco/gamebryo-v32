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
#ifndef EE_NETTRANSPORTENET_H
#define EE_NETTRANSPORTENET_H

#include <efdNetwork/NetTransportTCP.h>
#include <efdNetLibEnet/efdNetLibEnetLibType.h>

namespace efd
{

class EnvelopeMessage;

/**
A Transport class for sending messages over the reliable udp messages with enet.
*/
class EE_EFDNETLIBENET_ENTRY NetTransportEnet : public NetTransportTCP
{
public:

    /// @name Construction and Destruction
    //@{
    NetTransportEnet(MessageFactory* pMessageFactory, QualityOfService qos);
    /// Virtual destructor
    virtual ~NetTransportEnet();
    //@}

    virtual efd::ConnectionID Listen(efd::UInt16 portListen, INetCallback* pCallback);

    virtual ConnectionID Connect(
        const efd::utf8string& strServerAddress,
        efd::UInt16 portServer,
        INetCallback* pCallback);

    virtual void ReceiveMessages();

};

    /// A smart pointer (reference counting, self deleting pointer) for the NetTransportUSB class.
    typedef efd::SmartPointer<NetTransportEnet> NetTransportEnetPtr;


} // end namespace efd

#endif // EE_NETTRANSPORTENET_H
