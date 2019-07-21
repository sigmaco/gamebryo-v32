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
#ifndef EE_ASSETFACTORYMANAGER_H
#define EE_ASSETFACTORYMANAGER_H

#include <efd/efdLibType.h>
#include <efd/efdSystemServiceIDs.h>

#include <efd/ISystemService.h>

#include <efd/IAssetFactory.h>

#include <efd/AssetLoadRequest.h>
#include <efd/AssetLoadResponse.h>
#include <efd/Thread.h>
#include <efd/LockFreeQueue.h>
#include <efd/CriticalSection.h>
#include <efd/ProcessorAffinity.h>

#include <efd/AssetLocatorService.h>
#include <efd/MessageService.h>

namespace efd
{
// Forward declaration
class AssetLoaderThreadFunctor;


/**
    The AssetFactoryManager is a system service that handles the loading of assets.
 */
class EE_EFD_ENTRY AssetFactoryManager : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        AssetFactoryManager,
        efd::kCLASSID_AssetFactoryManager,
        efd::ISystemService);
    EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT;
    /// @endcond

    /// @name Construction and Destruction
    //@{
protected:
    /// Destructor.
    virtual ~AssetFactoryManager();

public:
    /**
        Constructor used to create an instance of the AssetFactoryManager.

        When the pForeInstance argument is NULL, this instance is presumed to be the one running
        in the main thread. In such cases another thread is started to perform background
        loading. There can be at most one foreground instance. The constructor will assert
        if called more than once.

        @param requestQueueSize The size of the queue used to send messages to the other thread.
            This size is the maximum number of load requests that may be made, without a context
            switch, by the foreground thread during a single tick of the background service. The
            system will still function if more messages are queued, but more slowly.
        @param sleepInterval The period the background thread will sleep when no data is loaded
            on a tick, in milliseconds.
        @param pForeInstance The instance of this service in the other, master, thread.
            This must be NULL for the first instance created, typically the instance in the main
            thread. When NULL, the service creates a background loading thread and another
            instance of itself in that thread.
    */
    AssetFactoryManager(
        const size_t requestQueueSize = 16,
        const efd::UInt32 sleepInterval = 8,
        AssetFactoryManager* pForeInstance = NULL);
    //@}

    /// @name Asset Factory Registration
    ///
    /// All asset factory registration functions are thread safe.
    //@{
    /**
        Register an asset factory that will response to request on the given category. The
        AssetFactory is now owned by the AssetFactoryManager. Callers should not attempt
        to delete the factory once it is registered.

        @note This method can be called during OnPreInit or OnInit of any system service. It is
            recommended that asset factory instances be registered during OnPreInit of an owning
            system service.
        @note Any service that registers an IAssetFactory must also add a dependency on the
            AssetFactorManager during OnPreInit. The AssetFactoryManager cannot shutdown while
            there are outstanding factories.

        @param responseCategory The category under which to register the factory. Messages
            sent to the AssetFactoryManager contain a response category that is used to match the
            message to the registered loader of the same category. Response messages are then
            sent on the same category. The category should be unique among factories.
        @param pAssetFactory A pointer to an instance of a class that implements the
            efd::IAssetFactory interface.

        @return False if a factory is already registered at the given category. Otherwise true.
    */
    bool RegisterAssetFactory(const Category responseCategory, IAssetFactory* pAssetFactory);

    /**
        Unregister the asset factory for the given category. The factory is now available
        for cleanup. The AssetFactoryManager will call IAssetFactory::Shutdown on this
        factory during shutdown.

        To avoid memory leaks all asset factories that are registered must be unregistered
        before the application terminates.

        @note This method can be called during OnPreInit or OnInit of any system service. It is
            recommended that any service which registered a asset factory call this method during
            the OnShutdown of the owning service.

        @param responseCategory The response category to unregister.

        @return The asset factory pointer registered to category, or NULL if no factory was
            registered.
    */
    IAssetFactory* UnregisterAssetFactory(const Category responseCategory);

    /**
        Obtain a pointer to the asset factory registered for a given response category.

        @note This method can be called during OnPreInit or OnInit of any system service.
    */
    IAssetFactory* GetAssetFactory(const Category responseCategory);

    //@}


    /// @name Messaging Helpers
    //@{

    /// The category to use for all messages sent to the Asset Factory Manager service.
    inline static Category MessageCategory();

    //@}


    /// @name Asset Location Functions
    //@{

    /**
        Locate an asset required by a factory. A factory may need to located required assets
        needed to construct the asset. The LocateAsset function performs the asset location
        in the foreground thread and later posts the response to the provided waiting factory.

        The factory must implement the HandleAssetLocate function. This function is called
        by the AssetFactoryManager background thread when a locate response is received.

        If called on the foreground instance of the service, the request is passed directly
        to the efd::AssetLocatorService instance.

        @param urn URN of the asset(s) to locate.
        @param targetCategory category expecting an AssetLocatorResponse.
    */
    void AssetLocate(const efd::utf8string& urn, efd::Category targetCategory);

    /**
        Associate an asset locator request category with the factory that is expecting a response.
        An IAssetFactory may request the location of assets for use in the background thread.
        To deliver the AssetLocatorResponse message to the intended target, the category
        used by the factory must be registered using this method.

        @note This method can be called during OnPreInit or OnInit of any system service. Classes
            derived from efd::IAssetFactory will typically register themselves by calling this
            method during their constructors.

        @param factory IAssetFactory that expects locator response messages.
        @param targetCategory the target category the factory will used for these messages.
    */
    void RegisterAssetLocateHandler(
        efd::Category targetCategory,
        efd::IAssetFactory* factory);

    //@}

    /// @name Thread Information
    //@{

    /// Return true when this instance is in the foreground.
    inline bool IsFgInstance() const;

    /// Set the interval that the background thread will sleep, per tick, when no data is loaded.
    ///
    /// Value is in milliseconds for passing to efd::Sleep.
    void SetSleepInterval(const efd::UInt32 sleepInterval);

    /// Get the interval, in milliseconds, that the background thread will sleep on a tick when
    /// no data is loaded.
    inline efd::UInt32 GetSleepInterval() const;

    /// Set the maximum number of messages from the background to process in a single foreground
    /// tick.
    void SetBackgroundMessageCapPerTick(efd::UInt32 maxMessageCountPerTick);

    /// Gets the maximum number of messages from the background to process in a single foreground
    /// tick.
    efd::UInt32 GetBackgroundMessageCapPerTick() const;

    /**
        Set the processor affinity for the background thread.

        This function must be called on the foreground instance to have any effect.
        The new affinity is applied the next time the OS schedules the thread. The default is
        efd::ProcessorAffinity(ProcessorAffinity::PROCESSOR_1,
        (efd::UInt32)ProcessorAffinity::PROCESSOR_DONT_CARE) for Win32,
        efd::ProcessorAffinity(ProcessorAffinity::PROCESSOR_XENON_CORE_2_THREAD_0,
        (efd::UInt32)ProcessorAffinity::PROCESSOR_DONT_CARE) for Xbox360,
        and efd::ProcessorAffinity(ProcessorAffinity::PROCESSOR_DONT_CARE,
        (efd::UInt32)ProcessorAffinity::PROCESSOR_DONT_CARE) for PS3.

        The return value is false if the system could not set the affinity as requested. It is
        true when the system set the affinity as requested.
    */
    inline bool SetBgThreadAffinity(const efd::ProcessorAffinity& affinity);

    /**
        Get the processor affinity for the background thread.

        This function must be called on the foreground instance to get a valid return value.
    */
    inline const efd::ProcessorAffinity GetBgThreadAffinity();

    /**
        Set the thead priority for the background thread.

        This function must be called on the foreground instance to have any effect. See
        efd::Thread::SetPriority for more details. The default is efd::Thread::NORMAL.

        The return value is false if the system could not set the priority as requested. It is
        true when the system set the priority as requested.
    */
    inline bool SetBgThreadPriority(const efd::Thread::Priority priority);

    /**
        Get the priority for the background thread.

        This function must be called on the foreground instance to get a valid return value.
        See efd::Thread::GetPriority for more details.
    */
    inline efd::Thread::Priority GetBgThreadPriority() const;

    //@}

    /// @name Callback Registration.
    //@{

    /**
        Register a callback category used to forward load response messages. Any AssetLoadResponse
        message created by factory with the given class ID will be forwarded to the provided
        category. This can be useful if you want to know when a particular asset type is factoried.

        @note Receiving the factory response does not imply the asset is ready for use, only
            that the process of factoring the asset completed. The original requester may need to
            perform additional work before the asset is commonly available.

        @param factoryClassID ClassID of the factory creating the response messages.
        @param callback Callback category to receive response messages.
    */
    void RegisterAssetCallback(efd::ClassID factoryClassID, const efd::Category& callback);

    /**
        Unregister for callback notifications.

        @param factoryClassID ClassID of the factory creating the response messages.
        @param callback Callback category to unregister.
    */
    void UnregisterAssetCallback(efd::ClassID factoryClassID, const efd::Category& callback);

    //@}

    /// @cond EMERGENT_INTERNAL

    // Handler for AssetLoadRequest messages
    void AssetLoadRequestHandler(const AssetLoadRequest* pMessage, Category targetChannel);

    // Handler for AssetLocatorResponse messages
    void AssetLocatorResponseHandler(const AssetLocatorResponse* pMessage, Category targetChannel);

    // A class for asset factory data
    class AssetFactoryInfo : public MemObject
    {
    public:
        AssetFactoryInfo(IAssetFactory* pAssetFactory, const Category& reponseCategory);

        IAssetFactoryPtr m_spAssetFactory;
        Category m_responseCategory;
    };

    /// @endcond EMERGENT_INTERNAL

protected:

    /// @name System Service Functions
    //@{

    /// Registers dependencies on the message service and asset locator.
    efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /// OnInit grabs a pointer to the message service, creates the message queues and creates
    /// the background thread.
    virtual efd::AsyncResult OnInit();

    /// OnTick pulls any AssetLoadResponse messages off the response queue and sends them out on
    /// the message service.
    virtual efd::AsyncResult OnTick();

    /// Shutdown removes all messages from the request queue and signals the background thread
    /// to terminate.
    virtual efd::AsyncResult OnShutdown();

    /// Return the name of the service, in this case "AssetFactoryManager".
    virtual const char* GetDisplayName() const;

    //@}

    enum LoadRequestStatus
    {
        /// Load is waiting for location
        LRS_LOCATING = 1,
        /// Load is pending, not started
        LRS_PENDING = 2,
        /// Load is in progress. Could be blocked or canceling.
        LRS_IN_PROGRESS = 3,
        /// Load is complete
        LRS_COMPLETED = 4,
        /// Load has canceled
        LRS_CANCELLED = 5
    };

    // Forward declaration.
    class LocatorRequestData;

    /// Class to hold info about pending load requests
    class LoadRequestData : public MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;

    protected:
        ~LoadRequestData();

    public:
        // The request message
        AssetLoadRequestConstPtr m_spRequest;

        // The response message
        AssetLoadResponsePtr m_spResponse;

        // The current state of this load
        LoadRequestStatus m_status;

        // The target thread
        bool m_isForBackground;

        // ClassID of the target factory.
        efd::ClassID m_factoryClassID;
    };
    typedef SmartPointer<LoadRequestData> LoadRequestDataPtr;
    typedef list<LoadRequestDataPtr> LoadRequestQueue;

    /// Class to hold info about pending locator requests
    class LocatorRequestData : public MemObject
    {
        EE_DECLARE_CONCRETE_REFCOUNT;
    protected:
        ~LocatorRequestData();

    public:
        /// The urn that the asset was requested with
        utf8string m_urn;

        // The request message
        IMessageConstPtr m_spSourceMessage;

        // A pointer to the load requests that allows us to update the
        // status of a load when the request is met. NULL if this request is not for a load.
        LoadRequestDataPtr m_spLoadRequestData;

        // The background thread category for the response message
        efd::Category m_responseCategory;
    };
    typedef SmartPointer<LocatorRequestData> LocatorRequestDataPtr;
    typedef list<LocatorRequestDataPtr> LocatorRequestList;

    // The construction code for a foreground instance
    void FgConstructor(const size_t requestQueueSize);

    // The construction code for a background instance.
    void BgConstructor(AssetFactoryManager* pForeInstance);

    // The OnTick code for a foreground instance
    virtual efd::AsyncResult FgTick();

    // The OnTick code for a background instance.
    virtual efd::AsyncResult BgTick();

    // Process preemptive loads. Returns true if we did some significant work.
    bool ProcessPreemptiveLoads();

    // Do some processing of pending loads. At most one pending load will be allowed to do some
    // significant work. Returns true if some work was done.
    bool ProcessPendingLoads();

    // Called by the foreground OnTick to get any pending messages from the background thread.
    void PullMessagesFromBackground();

    // Called by the foreground OnTick to move any pending messages to the background thread.
    void PushMessagesToBackground();

    // Called by the background OnTick to get any pending messages from the foreground thread.
    void PullMessagesFromForeground();

    // Called by the background OnTick to move any pending messages to the foreground thread.
    void PushMessagesToForeground();

    // Process responses to be sent. If in the background, puts the messages on the queue. If
    // foreground, it sends them on the message service.
    void SendResponseMessages(bool isBackground);

    // Return true if the asset requested by the message should be background loaded
    bool LoadsInBackground(const AssetLoadRequest* pMessage);

    // Obtain a pointer to the asset factory registered for a given response category.
    // This version doesn't lock.
    IAssetFactory* GetAssetFactoryInternal(const Category responseCategory);

    // Forward a response to any registered callback listeners.
    void ForwardToCallbackListeners(efd::ClassID factoryClassID, const AssetLoadResponse* pMsg);

    // Helper to shutdown factories from the background thread. Called only by the background
    // thread. The assumption is the foreground thread will add things to the list, and stop
    // using a factory for any new processing, while the background thread actually shuts down
    // the factory when it is known to not be in use in the background thread.
    void ShutdownFactories();

    // The background thread procedure. Only the foreground thread should ever touch this.
    AssetLoaderThreadFunctor* m_pLoaderThreadFunctor;

    // The background thread. Only the foreground thread should ever touch this.
    Thread* m_pLoaderThread;

    // The queue for sending messages to the other thread. This instance own this queue and
    // is responsible for allocating and cleaning it up.
    LockFreeQueue<IMessageConstPtr> m_sendQueue;

    // The queue for receiving messages from the other thread. This instance does not own
    // this queue.
    LockFreeQueue<IMessageConstPtr>* m_pReceiveQueue;

    // A category for locate requests initiated by the service itself
    Category m_assetLoadRequestCategory;

    // A list to keep track of any assets for which we will have requested a location.
    // This list contains all outstanding locations, including those for background
    // loaders.
    LocatorRequestList m_pendingLocatorRequests;

    // A list to keep track of any assets for which we a load request and the
    // load is still pending. This list is for assets that are not immediately loaded.
    // Both the foreground and background thread have an instance of this queue.
    //
    // The foreground thread has the following items on the queue:
    // * Any non-immediate load request that is pending an asset locate
    // * Any non-immediate load request that arrived later than one pending an asset locate
    // * Any foreground non-immediate load that is in progress
    // * Any foreground non-immediate load that was requested after a non-completed load
    //
    // The background thread has the following items on the queue
    // * Any non-immediate background load that is in progress
    // * Any non-immediate background load that arrived after one that is in progress
    LoadRequestQueue m_pendingLoadRequests;

    // A list to keep track of any assets for which have requested a preemptive load.
    // Both the foreground and background thread have an instance of this queue.
    //
    // The foreground thread has the following items on the queue:
    // * Any immediate load request that is pending an asset locate
    // * Any foreground immediate load that is in progress
    //
    // The background thread has the following items on the queue
    // * Any immediate background load that is in progress
    LoadRequestQueue m_preemptiveLoadRequests;

    // We keep pointers to the message service and the asset locator service
    MessageServicePtr m_spMessageService;
    AssetLocatorServicePtr m_spAssetLocatorService;

    // The map of factories is static so that both threads share. It is protected
    // by the ms_AssetFactoryCritSect lock. This map is allocated upon first use.
    typedef map<Category, AssetFactoryInfo*> AssetFactoryMap;
    static AssetFactoryMap* ms_pAssetFactoryMap;

    // Cleanup factory list. Items in this list are waiting for shutdown so they
    // can cleanup resources in the background thread. This list is shared by
    // both threads. It is protected by the ms_assetFactoryCritSect lock. This
    // list is allocated upon first use.
    typedef list<IAssetFactoryPtr> AssetFactoryList;
    static AssetFactoryList* ms_pFactoriesPendingShutdown;

    // The message category
    static Category ms_privateCategory;

    // Mapping of factory ClassID to callback category.
    typedef efd::map<efd::ClassID, efd::set<efd::Category> > CallbackCategoryMap;
    CallbackCategoryMap m_callbacks;

    // Critical section controlling access to the loader registration functions
    static CriticalSection ms_assetFactoryCritSect;

    // mapping between a category and the IAssetFactory instance that makes asset locator requests.
    // This map is used to find the factory that is waiting on an asset locator response so
    // we can forward the response to the correct factory.  Shared between the foreground
    // and background threads. Protected by the ms_locatorHandlersCritSect lock.
    // This map is allocated upon first use.
    typedef efd::map<efd::Category, efd::IAssetFactory*> AssetLocatorMap;
    static AssetLocatorMap* ms_pAssetLocatorMap;

    // Critical section controlling access to the locator response handler map
    static CriticalSection ms_locatorHandlersCritSect;

    // The time the background thread will sleep when no work is done.
    efd::UInt32 m_sleepInterval;

    // The maximum number of messages from the background to process in a single foreground tick.
    efd::UInt32 m_backgroundMessageCapPerTick;

    // Set true by the first foreground instance, and checked as an error condition by
    // other instances when asked to construct for the foreground.
    static volatile bool ms_isMasterSet;
};

/// A smart pointer for AssetFactoryManager instances.
typedef SmartPointer<AssetFactoryManager> AssetFactoryManagerPtr;

} // end namespace efd

#include <efd/AssetFactoryManager.inl>

#endif // EE_ASSETFACTORYMANAGER_H
