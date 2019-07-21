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
#ifndef EE_TRANSPORTFACTORY_H
#define EE_TRANSPORTFACTORY_H

#include <efdNetwork/efdNetworkLibType.h>
#include <efdNetwork/INetTransport.h>

#include <efd/StdContainers.h>

namespace efd
{

//class MessageFactory;

/// Typedef for the signature the class method must have
typedef INetTransportPtr (TransportFactoryMethod)(
    MessageFactory* pMessageFactory,
    QualityOfService qualityOfService);

/**
*/
class EE_EFDNETWORK_ENTRY RegisterTransportFactory
{
public:
    /**
        Constructor
    */
    RegisterTransportFactory(TransportFactoryMethod pMethod, efd::QualityOfService qos);

    /// Destructor
    ~RegisterTransportFactory();

    /// Next object in linked list of transport factories registered statically.
    RegisterTransportFactory* m_nextTransportFactory;

    /// Collects all statically declared transport factories w/o using init-time allocation.
    static RegisterTransportFactory* ms_firstTransportFactory;

    /// a reference to the method to invoke to factory a transport.
    TransportFactoryMethod* m_pMethod;

    /// The QualityOfService this factory produces
    efd::QualityOfService m_qos;
};

/// Macro for declaring a factory function that can create a transport of the specified
/// QulaityOfService
#define EE_REGISTER_TRANSPORT_FACTORY(METHOD,QOS) \
    static RegisterTransportFactory \
    EE_MAKE_UNIQUE_NAME(RegisterTransportFactory)(METHOD, QOS);

/**
*/
class EE_EFDNETWORK_ENTRY TransportFactory : public MemObject
{
public:
    TransportFactory();
    virtual ~TransportFactory();

    INetTransportPtr CreateTransport(
        MessageFactory* pMessageFactory,
        QualityOfService qualityOfService);

    void RegisterTransports();

protected:
    RegisterTransportFactory* m_lastHeadTransportFactory;
    map< efd::QualityOfService, TransportFactoryMethod* > m_factoryMap;
};

} // end namespace efd

#endif // EE_TRANSPORTFACTORY_H
