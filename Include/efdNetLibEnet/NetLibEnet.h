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
#ifndef EE_NETLIBENET_H
#define EE_NETLIBENET_H

#include <efdNetwork/NetLib.h>
#include <efdNetLibEnet/efdNetLibEnetLibType.h>

namespace efd
{

/**
    Modification of NetLib to only use NetTransportEnet and assert if any
    unsupported quality of service is used.
*/
class EE_EFDNETLIBENET_ENTRY NetLibEnet : public efd::NetLib
{
public:
    /// Constructor.
    NetLibEnet();
    /// Virtual destructor.
    virtual ~NetLibEnet();

    /// Transport factory
    static INetTransportPtr CreateTransport(
        MessageFactory* pMessageFactory,
        QualityOfService qualityOfService);

protected:
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RegisterTransport(efd::QualityOfService qualityOfService);
};

typedef efd::SmartPointer<NetLibEnet> NetLibEnetPtr;

} // end namespace efd

#endif //EE_NETLIBENET_H
