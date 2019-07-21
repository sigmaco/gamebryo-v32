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
#ifndef EE_INETSERVICE_H
#define EE_INETSERVICE_H

#include <efd/IBase.h>
#include <efd/ISystemService.h>
#include <efd/CriticalSection.h>
#include <efd/INetListener.h>
#include <efd/StreamMessage.h>
#include <efd/INetCallback.h>
#include <efd/NetEnums.h>

namespace efd
{
class EnvelopeMessage;
class INetTransport;
class INetLib;
class MessageService;

class EE_EFD_ENTRY INetService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(INetService, efd::kCLASSID_INetService, efd::ISystemService);
    EE_DECLARE_ABSTRACT_REFCOUNT;
    /// @endcond

public:

    /**
        Subscribe tells NetService that the INetCallback specified by pCallback is interested in
        receiving messages on the Category cat.

        Messages delivered to this Category will be delivered to the INetCallback specified.

        @param cat Category to subscribe to
        @param pCallback pointer to callback class to handle messages
    */
    virtual void Subscribe(const Category &cat, INetCallback* pCallback) = 0;


    /**
        Unsubscribe tells NetService that the INetCallback specified by pCallback is no longer
        interested in receiving messages on the Category cat.

        Messages delivered to the Category specified will no longer be  delivered to the
        INetCallback specified.

        @param cat Category to subscribe to
        @param pCallback pointer to callback class to handle messages
    */
    virtual void Unsubscribe(const Category &cat, INetCallback* pCallback) = 0;

    /**
        Unsubscribe the specified callback from all Categories.
        Used in cases where the callback object pCallback is going to be deleted,
        or is otherwise no longer interested in receiving any more callbacks
        @param pCallback pointer to callback object to Unsubscribe
    */
    virtual void Unsubscribe(INetCallback* pCallback) = 0;

    /**
        Send an IMessage to every process except this one (in other words, send to every remote
        process). Only those processes subscribed to the given category will be notified.

        @param pMessage Pointer to message for delivery
        @param cat Category to send with
        @param defaultQOS quality of service to send message on
    */
    virtual void SendRemote(
        IMessage* pMessage,
        const Category &cat,
        efd::QualityOfService defaultQOS = QOS_INVALID) = 0;

    /**
        Send an IMessage to the remote process specified by the ConnectionID. The message will be
        sent using quality of service assigned to that connection.

        @note This function ignores subscription data and sends directly to the connection.

        @param pMessage Pointer to message for delivery
        @param cat Category to send with
        @param cid the ConnectionID to send message to
    */
    virtual void SendRemote(IMessage* pMessage, const Category &cat, const ConnectionID& cid)=0;

    /**
        Send a message to producers of specified category. In other words, send the message to
        any process in which someone called BeginCategoryProduction on this category and with an
        INetCallback pointer.

        @param pMessage Pointer to message for delivery
        @param categoryProduced send message to anyone who produces this category
        @param qualityOfService The quality of service.
    */
    virtual void ProducerSendRemote(
        IMessage* pMessage,
        const Category& categoryProduced,
        QualityOfService qualityOfService)=0;

    /// @name Accessors for NetID
    //@{
    virtual efd::UInt32 GetNetID() const=0;
    virtual void SetNetID(efd::UInt32 netID)=0;
    //@}

    /**
        BeginCategoryProduction assigns a quality of service to a category and notifies the
        CategoryManager of the intention of this NetService to produce messages destined for the
        specified category.

        @param cat The category specified "match" category
        @param qualityOfService Quality of service for this category
        @param pCallback The callback that will receive producer messages for this category
    */
    virtual bool BeginCategoryProduction(
        const Category& cat,
        QualityOfService qualityOfService,
        INetCallback* pCallback) = 0;

    /**
        EndCategoryProduction notifies the CategoryManager of the intention of this NetService to
        no longer produce messages destined for the specified category

        @param cat The category specified "match" category
        @param pCallback The callback that will no longer receive producer messages for this
            category
    */
    virtual bool EndCategoryProduction(const Category& cat, INetCallback* pCallback) = 0;

    /**
        Gets the status of the connection to the ChannelManager. If there is no concept of a
        "primary" or main connection (what we call the Channel Manager Connection in the default
        NetService implementation) then the exact meaning of this is left to the INetService
        implementation. It is recommended that the status be used as an aggregated state describing
        whether any connections exist in a connected state.
    */
    virtual ConnectionStatus GetConnectionStatus() = 0;

    /**
        Set the MessageService this NetService will use. The message service implements the
        MessageFactory which must be used to allocate incoming messages. There may be multiple
        MessageService/INetService pairs running simultaneously in the same service manager so it
        important to use the passed in message service rather than assuming that a call to
        ServiceManager::GetSystemServiceAs<MessageService> will return the correct one.
    */
    virtual void SetMessageService(MessageService* pMessageService) = 0;

    /**
        Return the ConnectionID of our connection to the the ChannelManager for the given quality
        of service. This is used by the MessageService to detect whether a given message was
        actually sent by this process and then bounced back by the ChannelManager due to a local
        subscription.

        @todo Move this bounced message handling into NetService. The need for this feature is an
        implementation detail of the NetService/ChannelManager implementation so this method should
        not exist on the INetService interface.
    */
    virtual efd::ConnectionID GetChannelManagerConnectionID(QualityOfService qualityOfService) = 0;

    /**
        Make sure the specified Category is associated with the specified QualityOfService. This
        is used by the MessageService when messages are received remotely to ensure that the local
        INetService knows about the remote category to QoS mapping. For locally produced categories
        we should already know this information since it would have either been passed to SendRemote
        or BeginCategoryProduction. This method lets us verify that remote producers are consistent
        with local producers.

        @todo Move this functionality from MessageService into NetService so that this method can
        be removed from INetService. This should be a NetService implementation detail.
    */
    virtual void CheckPendingSubscriptions(Category catIDToCheck, QualityOfService qos)=0;
};

/// A SmartPointer for the INetService interface
typedef efd::SmartPointer<INetService> INetServicePtr;

} // end namespace efd

#endif // EE_INETSERVICE_H
