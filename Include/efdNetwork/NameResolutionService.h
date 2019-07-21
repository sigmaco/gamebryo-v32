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
#ifndef EE_NAMERESOLUTIONSERVICE_H
#define EE_NAMERESOLUTIONSERVICE_H

#include <efd/ISystemService.h>
#include <efd/INetCallback.h>
#include <efd/SmartPointer.h>
#include <efd/IMessage.h>
#include <efd/ConnectionID.h>
#include <efdNetwork/efdNetworkLibType.h>
#include <efdNetwork/NameResolutionMessage.h>
#include <efd/efdClassIDs.h>

namespace efd
{

class MessageService;
class INetService;
class INetLib;
class EnvelopeMessage;

/**
    \brief Resolves names to ip addresses and other information.

    Similar to ZeroConf, mDNS, SSDP, or SLP (rfc 2608 http://tools.ietf.org/html/rfc2608).  Works
    on a local network only.

    Every service maintains a cache of responses.  When the NameResolutionService is queried, it
    will send a response message immediately if it has information in the cache, but will also
    send out a new request if that information is too old.  A second response will be sent locally
    with updated information if a response to the external query comes back with different data
    than what is in the cache.

    One of the drawbacks of mDNS is that a daemon must be installed on each machine.  To get
    around this limitation, NameResolutionService attempts to bind to a well known port; if the
    binding fails, it assumes that there is a service running that will respond to requests.  On a
    regular interval, NameResolutionService attempts to rebind to the port in case the process
    that was using the port released it.

    ServiceAnnouncements and requests are broadcast; responses are unicast.

    NameResolutionService listens for incoming unicast response messages on a private port
    assigned by the OS.  This port is sent in the request message so that the
    NameResolutionService bound to the well known port knows where to target the response.  In
    practice, the port will most likely be the local port assigned when the request is sent.

    Requests will be assigned a request ID, but responses to those requests will be sent in the
    form of 1 or more local messages.  If no response can be given within a timeout, a message
    will be sent indicating that the timeout has been exceeded with no response.  Any cached
    values will be sent as local messages immediately with any remote responses arriving within
    the timeout that are not already in the cache being sent locally as they arrive.  A structure
    will be kept for each request to keep track of state, including request time and cached
    responses already sent.
*/

class EE_EFDNETWORK_ENTRY NameResolutionService : public ISystemService, efd::INetCallback
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(NameResolutionService, efd::kCLASSID_NameResolutionService, ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT
    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    NameResolutionService();

    /// Virtual destructor.
    virtual ~NameResolutionService();
    //@}

    const utf8string& GetInternetAddressAny() const;
    const utf8string& GetInternetAddressBroadcast() const;

    /// Timeout value for setting no timeout on lookup requests.
    const static efd::TimeType kNameLookup_NoTimeout;

    /**
        Services wishing to be able to be found can announce themselves using this function.

        Services can be looked up by either their classid or name.

        @note Assumes that the hostname is InternetAddressAny

        @param classID classID of the service being announced
        @param name Name of the service being announced
        @param extraInfo Additional information to report about this service. Not searched.
        @param port port number to use.
    */
    void AnnounceService(
        efd::UInt32 classID,
        const efd::utf8string& name,
        const efd::utf8string& extraInfo,
        efd::UInt16 port);

    /**
        Services wishing to be able to be found can announce themselves using this function.

        Services can be looked up by either their classid or name.

        @param classID classID of the service being announced
        @param name Name of the service being announced
        @param port port number to use
        @param hostname The host name
        @param extraInfo Additional information to report about this service. Not searched.
    */
    void AnnounceService(
        efd::UInt32 classID,
        const efd::utf8string& name,
        efd::UInt16 port,
        const efd::utf8string& hostname = "",
        const efd::utf8string& extraInfo = "");

    /**
        Cancel a service announcement when it is no longer desired to advertise.
        @param classID the classID of the announcement being cancelled
        @param name the name of the service announcement being cancelled
    */
    void CancelAnnounce(
        efd::UInt32 classID,
        efd::utf8string name);

    /**
        Look up a service by classID.

        @param classID classID of the service being announced.
        @param tmo Timeout value to keep sending requests.
        @return The Category that the responses to this request will be sent on.
    */
    efd::Category LookupService(efd::UInt32 classID,
        efd::TimeType tmo=5.0);

    /**
        Look up a service by name.

        @param name Name of the service being announced.
        @param tmo Timeout value to keep sending requests.
        @return The Category that the responses to this request will be sent on.
    */
    efd::Category LookupService(efd::utf8string name,
        efd::TimeType tmo=5.0);

    /**
        Look up a service by name and classID.

        @param name Name of the service being announced.
        @param classID classID of the service being announced.
        @param tmo Timeout value to keep sending requests.
        @return The Category that the responses to this request will be sent on.
    */
    efd::Category LookupService(efd::utf8string name,
        efd::UInt32 classID,
        efd::TimeType tmo=5.0);

    /**
        Cancel a service lookup before the timeout has expired.

        @param responseCategory Category that is assigned to the request.
    */
    void CancelLookup(efd::Category responseCategory);

    /**
        Clears any cached responses this instance has.
        @note Cached responses do not ever expire so this method must be called before making a new
        request to assure that stale responses are not returned.
    */
    void ClearCache();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void HandleNetMessage(const IMessage* pIncomingMessage,
        const ConnectionID& senderConnectionID);
    virtual SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual AsyncResult OnInit();
    virtual AsyncResult OnTick();
    virtual AsyncResult OnShutdown();
    virtual const char* GetDisplayName() const;

    virtual void SetAnnouncePort(efd::UInt16 announcePort);

protected:
    /// Hand out the next request id.
    efd::Category GenerateResponseCategory();

    /// Add a response to the cache.
    /// Also check if anyone local is interested in being notified about this service.
    void AddToCache(NameResolutionMessage* pNameResolutionMessage,
        const ConnectionID& senderConnectionID);

    /// Look up services in our cache and send responses to the connection that originated the
    /// request.
    void SendRemoteResponses(NameResolutionMessage* pNameResolutionMessage,
        ConnectionID senderConnectionID);

    void HandleDataMessage(EnvelopeMessage* pIncomingMessage,
        const ConnectionID& senderConnectionID);

    void SendLocalResponses(efd::utf8string name,
        efd::UInt32 classID,
        Category responseCategory);
    void SendRemoteRequest(efd::utf8string name,
        efd::UInt32 classID,
        Category responseCategory,
        efd::TimeType tmo);
    void SendRemoteRequestMessage(NameResolutionMessage* pNameResolutionMessage,
        bool newRequest);

    /// After sending out responses from the local cache, this message is sent out.
    /// This can be used to determine which responses were cached.  Any responses received after
    /// this message were a result of remote responses.
    void SendLocalResponsesDone(Category responseCategory);

    /// After the timeout for a request has expired, this message is sent out indicating that
    /// no more responses will be sent.
    /// At this point the recipient should unsubscribe from the private response category.
    void SendRemoteResponsesDone(Category responseCategory);

    efd::SmartPointer< efd::MessageService > m_spMessageService;
    efd::SmartPointer< efd::INetService > m_spNetService;
    efd::SmartPointer< efd::INetLib > m_spNetLib;

    /// The next request ID we are going to give out.
    static efd::UInt16 m_responseID;

    efd::ConnectionID m_listenCID;
    efd::ConnectionID m_pritaveListenCID;

    typedef efd::map< efd::Category, NameResolutionMessageSetPtr > RequestMap;
    RequestMap m_inFlightRequests;

    NameResolutionMessageSet m_cachedResponses;
    NameResolutionMessageSet m_authoritativeResponses;
    NameResolutionMessageList m_pendingRequests;
    NameResolutionMessageList m_outstandingRequests;
    NameResolutionMessageList m_pendingResponses;
    efd::utf8string m_netLibType;
    efd::UInt16 m_announcePort;

    utf8string m_inetAddrAny;
    utf8string m_inetAddrBroadcast;
};
typedef efd::SmartPointer<NameResolutionService> NameResolutionServicePtr;

}

#endif //EE_NAMERESOLUTIONSERVICE_H
