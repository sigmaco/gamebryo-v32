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
#ifndef EE_NOTIFICATIONSERVICE_H
#define EE_NOTIFICATIONSERVICE_H

#include <egf/egfLibType.h>
#include <egf/Entity.h>
#include <efd/ISystemService.h>
#include <efd/MessageHandlerBase.h>
#include <egf/EventMessage.h>
#include <efd/Category.h>
#include <efd/StreamMessage.h>
#include <efd/ServiceDiscoveryMessage.h>
#include <efd/MessageService.h>
#include <egf/EntityManager.h>
#include <egf/Scheduler.h>
#include <egf/FlatModelManager.h>
#include <egf/EntityChangeMessage.h>
#include <egf/egfClassIDs.h>

namespace egf
{

/**
    The message class used to send notifications.
*/
class EE_EGF_ENTRY NotificationMessage : public efd::DirectedMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(NotificationMessage, efd::kCLASSID_NotificationMessage, IMessage);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /// Default NotificationMessage Constructor
    NotificationMessage();

    /// virtual Destructor
    virtual ~NotificationMessage();
    //@}

    /**
        Method to convert this class to or from a stream.

        @param[in] ar Archive for storing this class contents.
    */
    virtual void Serialize(efd::Archive& ar);

    /**
        Retrieves the type of notification this message represents.

        @return The type of notification.
    */
    virtual efd::ClassID GetNotificationType() const
    {
        return GetClassID();
    }

    /**
        Retrieves the set of entities included in the notification.

        @return Set of entity IDs.
    */
    virtual const efd::set<egf::EntityID>& GetEntities() const
    {
        return m_entitySet;
    }

    /**
        Sets the set of entities to be included in the notification.

        @param [in] entitySet Set of entity IDs.
    */
    virtual void SetEntities(const efd::set<egf::Entity*>& entitySet);

protected:
    /// The set of entity IDs included in the notification.
    efd::set<egf::EntityID> m_entitySet;
};

/// A smart pointer (reference counting, self deleting pointer) for the NotificationMessage class.
typedef efd::SmartPointer<NotificationMessage> NotificationMessagePtr;



/**
    The notification service is responsible for monitoring changes to entities and notifying
    other entities and services about those changes.  It can send notifications by message, or
    entity behavior invocation.
*/
class EE_EGF_ENTRY NotificationService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(NotificationService, efd::kCLASSID_NotificationService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// The base class for all notification wrappers.  It handles the common task of gather the
    /// set of entities contained in the notification.
    class NotifyWrapper : public efd::IBase
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(NotifyWrapper, efd::kCLASSID_NotifyWrapper, efd::IBase);
        /// @endcond
    protected:
        /// @name Construction and Destruction
        //@{
        /**
            Protected default constructor to prevent direct use of this class.
            Only the derived versions of this calls should ever be created.
        */
        NotifyWrapper() {}
    public:
        /// Virtual destructor.
        virtual ~NotifyWrapper() {}
        //@}

        /**
            Sends the notification.

            @param [in] notificationType The type of notification being sent.
        */
        virtual void SendNotification(efd::ClassID notificationType) = 0;

        /**
            Adds a notice for the specified entity to be set when the service receives it tick.

            @param [in] pEntity The entity that was affected.
        */
        virtual void AddNotice(egf::Entity* pEntity);
    public:
        /// The list of entities that this wrapper is supposed to send a notification about.
        efd::set<egf::Entity*> m_entitySet;
    };

protected:

    class NotifyByMessage : public NotifyWrapper
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(NotifyByMessage, efd::kCLASSID_NotificationByMessage, NotifyWrapper);
        EE_DECLARE_CONCRETE_REFCOUNT;
        /// @endcond
    public:
        /// @name Construction and Destruction
        //@{
        /**
            NotifyByMessage constructor.

            @param [in] sendCat The category to send the notifications on.
            @param [in] pMessageService Pointer to the message service to use to send the messages.
        */
        NotifyByMessage(
            const efd::Category& sendCat,
            efd::MessageService* pMessageService);

        /// Virtual destructor.
        virtual ~NotifyByMessage();
        //@}

        /**
            Gets the category that the message is to be sent on.

            @return The sent to category.
        */
        efd::Category& GetCategory() {return m_sendCat;}

        /**
            Sends the notification by sending a message to the registered category.

            @param [in] notificationType The type of notification being sent.
        */
        virtual void SendNotification(efd::ClassID notificationType);

    protected:
        /// Smart pointer to local message service.
        efd::MessageServicePtr m_spMessageService;
        /// The category to send the notification on.
        efd::Category m_sendCat;
    };

    class NotifyByBehavior : public NotifyWrapper
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(NotifyByBehavior, efd::kCLASSID_NotificationByBehavior, NotifyWrapper);
        EE_DECLARE_CONCRETE_REFCOUNT;
        /// @endcond
    public:
        /// @name Construction and Destruction
        //@{
        /**
            NotifyByBehavior constructor.

            @param [in] sendToEntity The entity ID to invoke the behavior on.
            @param [in] sendToBehavior The behavior to call to notify the entity of the change.
            @param [in] pMessageService Pointer to the message service to use to send the messages.
        */
        NotifyByBehavior(
            const egf::EntityID& sendToEntity,
            const egf::BehaviorID sendToBehavior,
            efd::MessageService* pMessageService);

        /// Virtual destructor.
        virtual ~NotifyByBehavior();
        //@}

        /**
            Gets the registered entity ID.

            @return The entity ID.
        */
        egf::EntityID& GetEntity() {return m_sendToEntity;}

        /**
            Gets the registered behavior ID.

            @return The behavior ID.
        */
        egf::BehaviorID GetBehavior() {return m_sendToBehavior;}

        /**
            Sends the notification by invoking the registered behavior on the registered entity.

            @param [in] notificationType The type of notification being sent.
        */
        virtual void SendNotification(efd::ClassID notificationType);

    protected:
        /// Smart pointer to local message service.
        efd::MessageServicePtr m_spMessageService;
        /// The entity ID to invoke the behavior on.
        egf::EntityID m_sendToEntity;
        /// The behavior to call to notify the entity of the change.
        egf::BehaviorID m_sendToBehavior;
    };

public:
    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    NotificationService();

    /// Virtual destructor.
    virtual ~NotificationService();
    //@}

    /// @name Overridden Service Handlers
    //@{

    /// OnPreInit caches pointers ot other services and subscribes to messages on the local
    /// channel.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /// OnTick sends out any notifications gathered since the last tick.
    virtual efd::AsyncResult OnTick();

    /// OnShutdown unsubscribes to messages.
    virtual efd::AsyncResult OnShutdown();

    /// Return the name of the service, in this case "NotificationService".
    const char* GetDisplayName() const;

    //@}

    /// @name Notification Addition
    //@{
    /**
        Adds a notification message based on the model of the entity and optionally the
        property group that must change.

        @param [in] notifyDiscover Flag if a notification should be sent for discoveries.
        @param [in] notifyUpdate Flag if a notification should be sent for updates.
        @param [in] notifyRemoval Flag if a notification should be sent for removals.
        @param [in] sendTo The category to send the notification message to.
        @param [in] modelID Optional flat model ID to send notifications for (0 for all).
    */
    virtual bool AddNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const efd::Category& sendTo,
        const egf::FlatModelID modelID = 0);

    /**
        Adds a notification message for a specific entity and optionally the
        property group that must change.

        May be called during PreInit or Init.

        @param [in] notifyDiscover Flag if a notification should be sent for discoveries.
        @param [in] notifyUpdate Flag if a notification should be sent for updates.
        @param [in] notifyRemoval Flag if a notification should be sent for removals.
        @param [in] sendTo The category to send the message to.
        @param [in] entityID The entity ID to send notifications for.
    */
    virtual bool AddNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const efd::Category& sendTo,
        const egf::EntityID& entityID);

    /**
        Adds a notification behavior invocation based on the model of the entity and optionally the
        property group that must change.

        @param [in] notifyDiscover Flag if a notification should be sent for discoveries.
        @param [in] notifyUpdate Flag if a notification should be sent for updates.
        @param [in] notifyRemoval Flag if a notification should be sent for removals.
        @param [in] sendToEntity The entity ID to invoke the behavior on.
        @param [in] sendToBehavior The behavior ID to invoke.
        @param [in] modelID Optional flat model ID to send notifications for (0 for all).
    */
    virtual bool AddNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const egf::EntityID& sendToEntity,
        const egf::BehaviorID sendToBehavior,
        const egf::FlatModelID modelID = 0);

    /**
        Adds a notification behavior invocation for a specific entity and optionally the
        property group that must change.

        @param [in] notifyDiscover Flag if a notification should be sent for discoveries.
        @param [in] notifyUpdate Flag if a notification should be sent for updates.
        @param [in] notifyRemoval Flag if a notification should be sent for removals.
        @param [in] sendToEntity The entity ID to invoke the behavior on.
        @param [in] sendToBehavior The behavior ID to invoke.
        @param [in] entityID The entity ID to send notifications for.
    */
    virtual bool AddNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const egf::EntityID& sendToEntity,
        const egf::BehaviorID sendToBehavior,
        const egf::EntityID& entityID);

    /**
        Adds a notification behavior invocation based on the model of the entity and optionally the
        property group that must change.

        @param [in] notifyDiscover Flag if a notification should be sent for discoveries.
        @param [in] notifyUpdate Flag if a notification should be sent for updates.
        @param [in] notifyRemoval Flag if a notification should be sent for removals.
        @param [in] sendToEntity The entity ID to invoke the behavior on.
        @param [in] sendToBehavior The behavior name to invoke.
        @param [in] modelID Optional flat model ID to send notifications for (0 for all).
    */
    virtual bool AddNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const egf::EntityID& sendToEntity,
        const efd::utf8string& sendToBehavior,
        const egf::FlatModelID modelID = 0);

    /**
        Adds a notification behavior invocation for a specific entity and optionally the
        property group that must change.

        @param [in] notifyDiscover Flag if a notification should be sent for discoveries.
        @param [in] notifyUpdate Flag if a notification should be sent for updates.
        @param [in] notifyRemoval Flag if a notification should be sent for removals.
        @param [in] sendToEntity The entity ID to invoke the behavior on.
        @param [in] sendToBehavior The behavior name to invoke.
        @param [in] entityID The entity ID to send notifications for.
    */
    virtual bool AddNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const egf::EntityID& sendToEntity,
        const efd::utf8string& sendToBehavior,
        const egf::EntityID& entityID);
    //@}

    /// @name Notification Removal
    //@{

    /// Removes all the callback notifications that are registered.
    virtual void RemoveAllNotifications();
    /**
        Removes a notification message based on the model of the entity and optionally the
        property group that must change.

        May be called during PreInit or Init.

        @param [in] notifyDiscover Flag if a notification should be removed for discoveries.
        @param [in] notifyUpdate Flag if a notification should be removed for updates.
        @param [in] notifyRemoval Flag if a notification should be removed for removals.
        @param [in] sendTo The category to send the message to.
        @param [in] modelID Optional flat model ID to send notifications for (0 for all).
    */
    virtual bool RemoveNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const efd::Category& sendTo,
        const egf::FlatModelID modelID = 0);

    /**
        Removes a notification message for a specific entity and optionally the
        property group that must change.

        @param [in] notifyDiscover Flag if a notification should be removed for discoveries.
        @param [in] notifyUpdate Flag if a notification should be removed for updates.
        @param [in] notifyRemoval Flag if a notification should be removed for removals.
        @param [in] sendTo The category to send the message to.
        @param [in] entityID The entity ID to send notifications for.
    */
    virtual bool RemoveNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const efd::Category& sendTo,
        const egf::EntityID& entityID);

    /**
        Removes a notification behavior invocation based on the model of the entity and optionally the
        property group that must change.

        @param [in] notifyDiscover Flag if a notification should be removed for discoveries.
        @param [in] notifyUpdate Flag if a notification should be removed for updates.
        @param [in] notifyRemoval Flag if a notification should be removed for removals.
        @param [in] sendToEntity The entity ID to invoke the behavior on.
        @param [in] sendToBehavior The behavior ID to invoke.
        @param [in] modelID Optional flat model ID to send notifications for (0 for all).
    */
    virtual bool RemoveNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const egf::EntityID& sendToEntity,
        const egf::BehaviorID sendToBehavior,
        const egf::FlatModelID modelID = 0);
    /**
        Removes a notification behavior invocation for a specific entity and optionally the
        property group that must change.

        @param [in] notifyDiscover Flag if a notification should be removed for discoveries.
        @param [in] notifyUpdate Flag if a notification should be removed for updates.
        @param [in] notifyRemoval Flag if a notification should be removed for removals.
        @param [in] sendToEntity The entity ID to invoke the behavior on.
        @param [in] sendToBehavior The behavior ID to invoke.
        @param [in] entityID The entity ID to send notifications for.
    */
    virtual bool RemoveNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const egf::EntityID& sendToEntity,
        const egf::BehaviorID sendToBehavior,
        const egf::EntityID& entityID);

    /**
        Removes a notification behavior invocation based on the model of the entity and optionally the
        property group that must change.

        @param [in] notifyDiscover Flag if a notification should be removed for discoveries.
        @param [in] notifyUpdate Flag if a notification should be removed for updates.
        @param [in] notifyRemoval Flag if a notification should be removed for removals.
        @param [in] sendToEntity The entity ID to invoke the behavior on.
        @param [in] sendToBehavior The behavior name to invoke.
        @param [in] modelID Optional flat model ID to send notifications for (0 for all).
    */
    virtual bool RemoveNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const egf::EntityID& sendToEntity,
        const efd::utf8string& sendToBehavior,
        const egf::FlatModelID modelID = 0);

    /**
        Removes a notification behavior invocation for a specific entity and optionally the
        property group that must change.

        @param [in] notifyDiscover Flag if a notification should be removed for discoveries.
        @param [in] notifyUpdate Flag if a notification should be removed for updates.
        @param [in] notifyRemoval Flag if a notification should be removed for removals.
        @param [in] sendToEntity The entity ID to invoke the behavior on.
        @param [in] sendToBehavior The behavior name to invoke.
        @param [in] entityID The entity ID to send notifications for.
    */
    virtual bool RemoveNotification(
        bool notifyDiscover,
        bool notifyUpdate,
        bool notifyRemoval,
        const egf::EntityID& sendToEntity,
        const efd::utf8string& sendToBehavior,
        const egf::EntityID& entityID);
    //@}

public:
    /// @name Entity Change Handlers
    //@{
    /**
        This message handler is called when a new entity is discovered.  It then checks for
        any registered discovery notifications that match and schedules the notification to
        be sent on the next tick.

        @param [in] pMessage The message containing the discovery details.
        @param [in] targetChannel The channel the discovery message arrived on.
    */
    void HandleEntityDiscoverMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity is scheduled for removal.  It then checks for
        any registered removal notifications that match and schedules the notification to
        be sent on the next tick.

        @param [in] pMessage The message containing the removal details.
        @param [in] targetChannel The channel the removal message arrived on.
    */
    void HandleEntityRemovedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity is updated.  It then checks for
        any registered update notifications that match and schedules the notification to
        be sent on the next tick.

        @param [in] pMessage The message containing the update details.
        @param [in] targetChannel The channel the update message arrived on.
    */
    void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);
    //@}

protected:
    /// Class to hold the information for a notification to be delete
    class DeleteData
    {
    public:
        /// @name Construction and Destruction
        //@{
        /// Constructor
        DeleteData() {}
        /// Constructor with parameters
        DeleteData(
            efd::Category sendTo,
            egf::EntityID sendToEntity,
            egf::BehaviorID sendToBehavior)
            : m_sendTo(sendTo)
            , m_sendToEntity(sendToEntity)
            , m_sendToBehavior(sendToBehavior)
        {}
        /// Destructor
        ~DeleteData() {}
        //@}

        efd::Category m_sendTo;
        egf::EntityID m_sendToEntity;
        egf::BehaviorID m_sendToBehavior;
    };
    /// A smart pointer (reference counting, self deleting pointer) for the NotifyWrapper class.
    typedef efd::SmartPointer<NotifyWrapper> NotifyWrapperPtr;
    /// Set of notify wrappers typedef.
    typedef efd::set<NotifyWrapperPtr> CallbackSet;
    /// List of notify wrappers typedef.
    typedef efd::list<NotifyWrapperPtr> CallbackList;
    /// Class that contains the lists of callbacks for discoveries, updates, and removals.
    class CallbackLists : public efd::MemObject
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CONCRETE_REFCOUNT;
        /// @endcond
    public:
        /// @name Construction and Destruction
        //@{
        /// Constructor
        CallbackLists() {}
        /// Destructor
        ~CallbackLists() {}
        //@}

        /// List of discover callbacks.
        CallbackList m_discovers;
        /// List of update callbacks.
        CallbackList m_updates;
        /// List of removal callbacks.
        CallbackList m_removes;
    };

    /// Class that holds the maps for property and property group callbacks.
    class CallbackMaps : public efd::MemObject
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CONCRETE_REFCOUNT;
        /// @endcond
    public:
        /// @name Construction and Destruction
        //@{
        /// Constructor
        CallbackMaps() {}
        /// Destructor
        ~CallbackMaps() {}
        //@}

        /// List of the entity based callbacks.
        CallbackLists m_callbacks;
    };
    /// A smart pointer (reference counting, self deleting pointer) for the NotifyWrapper class.
    typedef efd::SmartPointer<CallbackMaps> CallbackMapsPtr;

protected:
    /**
        Adds notification callback wrappers to the map.

        @param [in] pDiscoverWrapper Pointer to the wrapper for discoveries.
        @param [in] pUpdateWrapper Pointer to the wrapper for updates.
        @param [in] pRemoveWrapper Pointer to the wrapper for removals.
        @param [in] pMap Map to store the notifications in.
    */
    virtual bool AddNotification(
        NotifyWrapper* pDiscoverWrapper,
        NotifyWrapper* pUpdateWrapper,
        NotifyWrapper* pRemoveWrapper,
        CallbackMaps* pMap);

    /**
        Adds notification callback wrappers to the model map.

        @param [in] pDiscoverWrapper Pointer to the wrapper for discoveries.
        @param [in] pUpdateWrapper Pointer to the wrapper for updates.
        @param [in] pRemoveWrapper Pointer to the wrapper for removals.
        @param [in] modelID Flat model ID to send notifications for.
    */
    virtual bool AddNotification(
        NotifyWrapper* pDiscoverWrapper,
        NotifyWrapper* pUpdateWrapper,
        NotifyWrapper* pRemoveWrapper,
        const egf::FlatModelID modelID);

    /**
        Adds notification callback wrappers to the model map.

        @param [in] pDiscoverWrapper Pointer to the wrapper for discoveries.
        @param [in] pUpdateWrapper Pointer to the wrapper for updates.
        @param [in] pRemoveWrapper Pointer to the wrapper for removals.
        @param [in] entityID Entity ID to send notifications for.
    */
    virtual bool AddNotification(
        NotifyWrapper* pDiscoverWrapper,
        NotifyWrapper* pUpdateWrapper,
        NotifyWrapper* pRemoveWrapper,
        const egf::EntityID& entityID);

    /**
        Removes notification callback wrappers to the map.

        @param [in] notifyType The type of notification to handle.
        @param [in] pData Pointer to the data to be deleted.
        @param [in] pMap Map to store the notifications in.
    */
    virtual bool RemoveNotification(
        efd::ClassID notifyType,
        DeleteData* pData,
        CallbackMaps* pMap);

    /**
        Removes notification callback wrappers to the model map.

        @param [in] notifyType The type of notification to handle.
        @param [in] pData Pointer to the data to be deleted.
        @param [in] modelID Flat model ID to send notifications for.
    */
    virtual bool RemoveNotification(
        efd::ClassID notifyType,
        DeleteData* pData,
        const egf::FlatModelID modelID);

    /**
        Removes notification callback wrappers to the model map.

        @param [in] notifyType The type of notification to handle.
        @param [in] pData Pointer to the data to be deleted.
        @param [in] entityID Entity ID to send notifications for.
    */
    virtual bool RemoveNotification(
        efd::ClassID notifyType,
        DeleteData* pData,
        const egf::EntityID& entityID);

    /**
        This message handler is called to process all the discoveries, updates, and removals after
        the proper callback map has been located.

        @param [in] notifyType The type of notification to handle.
        @param [in] targetChannel The channel the update message arrived on.
        @param [in] pMap The map that should be checked for notifications.
        @param [in] pEntity The entity that has changed.
    */
    virtual void HandleCallbackMapCheck(
        efd::ClassID notifyType,
        efd::Category targetChannel,
        CallbackMaps* pMap,
        Entity* pEntity);

    /**
        This message handler is called to process all the discoveries, updates, and removals.

        @param [in] notifyType The type of notification to handle.
        @param [in] pMessage The message containing the update details.
        @param [in] targetChannel The channel the update message arrived on.
    */
    virtual void HandleEntityMessage(
        efd::ClassID notifyType,
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

protected:
    /// Map for entity notifications that holds additional maps for further filtering.
    efd::map<egf::EntityID, CallbackMapsPtr> m_entityIDCBs;
    /// Map for model notifications that holds additional maps for further filtering.
    efd::map<egf::FlatModelID, CallbackMapsPtr> m_modelIDCBs;
    /// Set of discover notifications to send on the next tick.
    CallbackSet m_discoversToSend;
    /// Set of update notifications to send on the next tick.
    CallbackSet m_updatesToSend;
    /// Set of removal notifications to send on the next tick.
    CallbackSet m_removesToSend;

    /// Smart pointer to local message service.
    efd::MessageServicePtr m_spMessageService;
    /// Smart pointer to the flat model manager
    egf::FlatModelManagerPtr m_spFMM;
};

/**
    A smart pointer (reference counting, self deleting pointer) for the
    NotificationService class
*/
typedef efd::SmartPointer<NotificationService> NotificationServicePtr;

} // end namespace egf

#endif // EE_NOTIFICATIONSERVICE_H
