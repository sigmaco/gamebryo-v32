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
#ifndef EE_SERVICEDISCOVERYMESSAGE_H
#define EE_SERVICEDISCOVERYMESSAGE_H

#include <efd/IMessage.h>
#include <efd/efdMessageIDs.h>
#include <efd/Category.h>


namespace efd
{

    /**
        A message to request discovery from all receiving system services. Send this message
        to a category that the service is know to subscribe to (for example, a global well
        known channel) and all receiving services that implement service discovery will respond
        with their ClassID and a private channel for communication to that service instance.
    */
    class EE_EFD_ENTRY ServiceDiscoveryRequest : public IMessage
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(ServiceDiscoveryRequest, kMSGID_ServiceDiscoveryRequest, IMessage);
        /// @endcond

    public:
        /// Default constructor.
        ServiceDiscoveryRequest();

        /**
            Create a service discovery request.  Send this to a category that one or more services
            are expected to be listening on and everyone who receives the message will reply with
            their service ClassID and a private channel that can be used to communicate with that
            particular instance of the service.

            @note: There is no way to tell if no services of that type exist since our message
                system can't tell you if message delivery fails due to no target subscribers.
                The best you can do is to wait for a while and assume that if no one has replied
                then no services of that type exist.

            @param i_userData Arbitrary data that will be returned in all response messages.
            @param i_callback The category to which responses should be sent. This should normally
                be a private category that the sender is already subscribed to.
        */
        ServiceDiscoveryRequest(efd::UInt32 i_userData, efd::Category i_callback);

        /// Get the sender provided context value
        efd::UInt32 GetContext() const
        {
            return m_context;
        }

        /// Get the sender specified response category to which any response messages will be sent.
        efd::Category GetCallbackChannel() const
        {
            return m_respondTo;
        }

        // Overridden IStreamable methods
        virtual void Serialize(efd::Archive& ar);

    protected:
        efd::UInt32 m_context;
        efd::Category m_respondTo;
    };

    /// A SmartPointer for the ServiceDiscoveryRequest class.
    typedef efd::SmartPointer<ServiceDiscoveryRequest> ServiceDiscoveryRequestPtr;



    /**
        Response to the ServiceDiscoveryRequest message which identifies the responder's
        private channel and service ID.
    */
    class EE_EFD_ENTRY ServiceDiscoveryResponse : public IMessage
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(ServiceDiscoveryResponse, kMSGID_ServiceDiscoveryResponse, IMessage);
        /// @endcond

    public:
        /// Default constructor.
        ServiceDiscoveryResponse();

        /**
            Constructor for responding to a ServiceDiscoveryRequest. A service which handles
            ServiceDiscoveryRequest messages should create a ServiceDiscoveryResponse message using
            this constructor by passing it information about the service itself along with data
            from the received message.

            @param i_discoveredService The system service ID of the responder
            @param i_context The context value transferred from the ServiceDiscoveryRequest message.
            @param i_discoveredChannel The private channel of the responder
        */
        ServiceDiscoveryResponse(efd::SSID i_discoveredService,
            efd::UInt32 i_context,
            efd::Category i_discoveredChannel);

        /// The system service ID of the responding service
        efd::SSID GetServiceType() const
        {
            return m_discoveredService;
        }

        /// The context as sent in the ServiceDiscoveryRequest message
        efd::UInt32 GetContext() const
        {
            return m_context;
        }

        /// A private category used by the responding service.
        efd::Category GetServicePrivateChannel() const
        {
            return m_servicePrivateChannel;
        }

        // Overridden IStreamable methods
        virtual void Serialize(efd::Archive& ar);

    protected:
        efd::SSID m_discoveredService;
        efd::UInt32 m_context;
        efd::Category m_servicePrivateChannel;
    };

    /// A SmartPointer for the ServiceDiscoveryResponse class.
    typedef efd::SmartPointer<ServiceDiscoveryResponse> ServiceDiscoveryResponsePtr;


} // end namespace efd

#endif // EE_SERVICEDISCOVERYMESSAGE_H
