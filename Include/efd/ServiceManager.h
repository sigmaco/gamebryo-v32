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
#ifndef EE_SERVICEMANAGER_H
#define EE_SERVICEMANAGER_H

#include <efd/ISystemService.h>
#include <efd/IBase.h>
#include <efd/CriticalSection.h>
#include <efd/utf8string.h>
#include <efd/StdContainers.h>
#include <efd/TimeType.h>
#include <efd/efdClassIDs.h>
#include <efd/IMessage.h>
#include <efd/IServiceDetailRegister.h>
#include <efd/IFrameEvent.h>

namespace efd
{

/**
    A cache of ISystemService instances that are managed to control preinit, initialization,
    ticking, and shutdown. The ServiceManager is a central repository for ISystemService instances.
    It maintains a prioritized list of ISystemServices.
 */
class EE_EFD_ENTRY ServiceManager
    : public efd::IBase
    , protected efd::IAliasRegistrar
    , protected efd::IDependencyRegistrar
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ServiceManager, efd::kCLASSID_ServiceManager, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /**
        The combination of the ServiceManager state and the service's current state determines
        which ISystemService method will be called.  The ServiceManager maintains the state of
        each service.
    */
    enum ServiceState
    {
        /// An invalid state
        kSysServState_Invalid,
        /// Service was just registered and OnPreInit will be called on the next tick.
        kSysServState_PreInit,
        /// Service just ran OnPreInit this tick and is waiting to call OnInit next tick.
        kSysServState_WaitingToInitialize,
        /// Service will have OnInit called each tick until it completes or fails.
        kSysServState_Initializing,
        /// Service just returned complete from OnInit and is waiting to call OnTick next tick.
        kSysServState_WaitingToRun,
        /// Service will have OnTick called each tick until it completes or the thread is shutdown.
        kSysServState_Running,
        /// Service was still ticking when Shutdown occurred. Continue to call OnTick each tick
        /// while waiting for this service's's turn to be OnShutdown.
        kSysServState_WaitingToShutdown,
        /// Service returned Complete from OnTick, don't call OnTick any more until this service is
        /// ready to have OnShutdown called during thread shutdown.
        kSysServState_WaitingForThreadShutdown,
        /// Service is shutting down and OnShutdown will be called each tick (unless we're waiting
        /// for another service that depends on this service to complete shutdown).
        kSysServState_ShuttingDown,
        /// Service has completed OnShutdown or was unregistered before OnPreInit was ever called.
        kSysServState_Complete,
    };

public:

    /// @name Construction and Destruction
    //@{
    ServiceManager();
    virtual ~ServiceManager();
    //@}

    /// @name ISystemService management
    //@{

    /// This value can be passed to RegisterSystemService or RegisterAlternateSystemService to
    /// indicate that the default system service priority should be used.
    static const SInt32 kUseDefaultPriotity = EE_SINT32_MAX;

    /**
        RegisterSystemService is used to register a service to be executed inside the
        ServiceManager.

        You may register a system service at any time. If you register a service during the
        processing of the current service list then the actual registration will be delayed
        until the end of that processing. Once registered the service will enter the
        "Initializing" state. Once each service is initialized that service will enter the
        "Running" state.

        @note It is an error to register the same system service twice. To use multiple instances
            of the same service you must use RegisterAlternateSystemService for all but one
            instance (or for all instances if desired).

        @param pService A pointer to the service to register. This service will have the
            OnServiceRegistered method called in order to provide the service IDs and dependencies.
        @param iPriority An optional parameter that can override the default priority for the
            registered service. If the value kUseDefaultPriotity is passed then GetDefaultPriority
            will be called on the service in order to determine it's priority. The priority
            determines the order in which OnTick will be called on all registered services; lower
            numerical values are ticked after higher numerical values.

        @return AsyncResult Success if the service was immediately registered, pending if
            registration was queued, and failure if the request is invalid. The most common reason
            for failure would be a conflicting service ID.
    */
    virtual AsyncResult RegisterSystemService(
        ISystemService* pService,
        SInt32 iPriority = kUseDefaultPriotity);

    /**
        RegisterAlternateSystemService is used to register a service under an alternate ClassID
        rather than it's usual ClassID. The service will be registered to be executed inside the
        ServiceManager just as normal, but no aliases will be accepted for the service and the
        service can only be retrieved via GetSystemService using the specified alternate ClassID.
        This is useful for situations where you want to use multiple instances of the same service.

        You may register a system service at any time. If you register a service during the
        processing of the current service list then the actual registration will be delayed
        until the end of that processing. Once registered the service will enter the
        "Initializing" state. Once each service is initialized that service will enter the
        "Running" state.

        @note It is an error to register the same system service twice.

        @param pService A pointer to the service to register
        @param idSysSer The ID under which to register the system service. This must be unique
            among all other registered services and service aliases.
        @param iPriority An optional parameter that can override the default priority for the
            registered service. If the value kUseDefaultPriotity is passed then GetDefaultPriority
            will be called on the service in order to determine it's priority. The priority
            determines the order in which OnTick will be called on all registered services; lower
            numerical values are ticked after higher numerical values.

        @return AsyncResult Success if the service was immediately registered, pending if
            registration was queued, and failure if the request is invalid.
    */
    virtual AsyncResult RegisterAlternateSystemService(
        ISystemService* pService,
        SSID idSysSer,
        SInt32 iPriority = kUseDefaultPriotity);

    /**
        UnregisterSystemService is used to unregister an existing system service by pointer.

        A service may be unregistered at any time.  Unregistering a service places the service
        into the shutdown state.  Once a service completes shutdown it will be removed from the
        ServiceManager completely.

        @param pSysSer A pointer to the service to unregister
    */
    virtual void UnregisterSystemService(ISystemService *pSysSer);


    /**
        UnregisterSystemService is used to unregister an existing system service by ID. For classes
        registered via RegisterSystemService the ID can be the main ClassID or any alias registered
        during OnServiceRegistered. For classes registered via RegisterAlternateSystemService the
        ID must be the same ID that was passing in while registering the service.

        A service may be unregistered at any time. Unregistering a service places the service
        into the shutdown state. Once a service completes shutdown it will be removed from the
        ServiceManager completely.

        @param idSysSer The ID of the service to unregister
    */
    virtual void UnregisterSystemService(SSID idSysSer);


    /**
        GetSystemService is used to find a system service by ID. For classes registered via
        RegisterSystemService the ID can be the main ClassID or any alias registered during
        OnServiceRegistered. For classes registered via RegisterAlternateSystemService the ID must
        be the same ID that was passing in while registering the service. Only services that have
        entered the "Initializing" state and not completed the "Shutdown" state can be retrieved.

        @note This method is not thread safe. It should only be called from thread that is
        executing the Run method or in a services tick call.

        @param idSysSer The ID of the service to find.

        @return ISystemService Pointer to the system service if found, otherwise it returns NULL.
    */
    virtual ISystemService* GetSystemService(SSID idSysSer) const;

    /**
        Helper template that can cast the system service return by GetSystemService into the
        appropriate type represented by T.
        @see GetSystemService
        @param idSysSer The ID of the service to find.
    */
    template< typename T >
    T* GetSystemServiceAs(SSID idSysSer) const;

    /**
        Helper template that can cast the system service return by GetSystemService into the
        appropriate type represented by T. The CLASS_ID member of the templated class is used as
        the ID value for the call to GetSystemService; as a result this version can only be used
        for classes registered via RegisterSystemService. If the specified class is a base class
        then the final class must also have properly registered an alias when OnServiceRegistered
        was called during registration.
        @see GetSystemService
    */
    template< typename T >
    T* GetSystemServiceAs() const;

    /// Search for a system with the given display name. The first service in priority order that
    /// matches the name will be returned. Service names are not guaranteed to be unique. This is
    /// not an optimized lookup.
    ISystemService* GetSystemServiceByName(const char* displayName) const;

    /**
        The state of each service is maintained by the ServiceManager, not by the services
        themselves. To check the state of a service you call this method.  If needed, services may
        implement their own concept of state, this is just the "initialized verse running verse
        shutting down" state and should not be overloaded for other purposes.

        @param idSysSer The ID of the service to check

        @return ServiceState Current state of the service or kSysServState_Invalid if the service
            was not found.
    */
    ServiceState CheckSystemServiceState(SSID idSysSer) const;

    /**
        Determines the priority at which a system service is operating.

        @param idSysSer The ID of the service to find.
        @return The priority of the system service, which may differ from the services default
            priority if it was overridden during RegisterSystemService. If the given service is not
            found then zero is returned, but as this is also a valid service priority you may wish
            to verify the existence of the service separately.
    */
    SInt32 CheckSystemServicePriority(SSID idSysSer) const;

    //@}
    /// @name ServiceManager control methods
    //@{

    /**
        Run is used to start ticking each of the registered services until the Shutdown method
        is called.  This is the main loop of a ServiceManager controlled application.  It first
        performs initialization, then runs until shutdown is requested, and then controls the
        shutdown process.  Applications that call Run should not call OnInit, RunOnce, or
        Shutdown directly as the Run function will perform those tasks.
    */
    virtual void Run();

    /**
        RunOnce is used to tick each of the registered services once. This is useful for
        integrating the ServiceManager with other application ServiceManagers.  Using Run() is the
        recommended approach. You must first call InitializeServices() before calling this method.
    */
    virtual void RunOnce();

    /**
        Shutdown is used to request a shutdown of the ServiceManager.  By default the current main
        loop will complete and then the ServiceManager will go into the "shutting down" state.  If
        an immediate shutdown is requested then the main loop is aborted and we go directly to
        the shutting down state.

        @param i_Immediate If true, this shutdown is being requested due to a critical error
              and the stability of the process is in question.  Normal clean shutdown will
              be by-passed when passing this flag.
    */
    virtual void Shutdown(bool i_Immediate = false);

    /**
         GetShutdown is used to check to see if a shutdown has been requested by using the
         Shutdown() method.  Note that this becomes true the second the request is made even
         though we do not enter the "shutting down" state until the next main loop.

         @return bool True if a ServiceManager shutdown has been requested
    */
    bool GetShutdown();

    /**
        Determine if the pre-initialization phase of process startup has completed. When true this
        implies that the service manager has been ticked at least once.

        @return Becomes true once all initial OnPreInit calls have completed.
    */
    inline bool IsInitialized() const;

    /**
       Gets a value indicating if the service manager is currently performing a tick. In other
       words this determines whether the RunOnce method is currently executing.
    */
    inline efd::Bool IsRunning() const;

    /**
         Returns the state of the ServiceManager itself.  Be aware that individual services might
         be in a different state than the ServiceManager (for example, a service added while the
         ServiceManager is already running will be in the initializing state).  The only valid
         ServiceManager states are:
          - kSysServState_PreInit : ServiceManager is allocated but has not begun to run
          - kSysServState_Initializing : ServiceManager is in the process of calling OnInit on all
                system services and will continue to do so until they all complete initialization.
          - kSysServState_Running : ServiceManager is in the process of calling OnTick on all
                system and will continue to do so until a Shutdown request is received.
          - kSysServState_ShuttingDown : ServiceManager is in the process of calling OnShutdown on
                all system services and will continue to do so until they all complete the
                shutdown state.  Note that this state is entered on the next loop after a
                Shutdown() request is received and not immediately upon receiving that request.
          - kSysServState_Complete : ServiceManager main loop has completed.

         @return ServiceState Current state of the ServiceManager.
    */
    inline ServiceState GetCurrentState() const;

    //@}
    /// @name Frame Event methods
    //@{

    /**
        Register a frame event with the Service Manager. A frame event is a method of performing
        per-frame work by invoking an ordered list of handlers at a specific priority during the
        frame. Frame events run interspersed with ISystemService::OnTick calls and use the exact
        same priority system to control the overall order. If a service and a frame event have the
        same priority the service will receive OnTick before the frame event is invoked. Unlike
        system services, frame events are not state containing objects; they are more like message
        handlers for a locally sent message, but unlike message handlers the order in which various
        handlers is invoked is also controlled by an additional priority system. The handlers
        themselves are invoked using an interface and method that is specific to the frame event
        itself.

        The expected usage of this method is for an owning system service to allocate a frame event
        during or after its OnInit phase. This owning service will eventually unregister the event
        before the end of its OnShutdown phase. The service manager will hold a reference to the
        frame event and will release it once it has been unregistered. If desired, the owning
        service may continue to reference the frame event but it is recommend that the event be
        treated as protected data of the owning service (one reason for this is that frame events
        do not implement Foundation RTTI so they cannot safely be cast to other class types). Once
        a frame event is registered, various services including the owning service or any service
        that depends on the owning service can add handlers that will be invoked sequentially when
        the frame event is invoked.

        @param pEvent The frame event to register. It must have a unique name in order to register
            successfully.
        @param priority The priority at which this frame event will execute. If the special value
            efd::kUseDefaultPriotity is used, the priority will be determined by calling the
            efd::IFrameEvent::GetDefaultPriority method.
        @return True if the event was registered successfully. When a true value is returned the
            caller must eventually call UnregisterFrameEvent to remove the event.
    */
    virtual bool RegisterFrameEvent(IFrameEvent* pEvent, SInt32 priority = kUseDefaultPriotity);

    /**
        Add a handler to an already registered frame event. The provided IBase must implement the
        specific interface and method used by the frame event, which should be documented along
        with the frame event itself. The handler will be invoked in priority order each time the
        frame event is triggered, which will be once per frame so as long as the frame event is
        active.

        The typical usage of this method is to add frame event handlers during the OnInit phase
        of a system service and to unregister those handlers during OnShutdown. If the handler
        needs to toggle itself on or off frequently it is more efficient to perform that operation
        within the handler than to frequently call the Add/RemoveFrameEventHandler methods.

        @note Services adding frame event handlers, either directly or through another object
        managed by the service, should register a dependency on the system service which owns the
        frame event (in other words, on the service that called RegisterFrameEvent).

        @note Services calling this method must call RemoveFrameEventHandler before the end of
        their OnShutdown method. If a non-service object is handling frame events it also must be
        removed prior to the UnregisterFrameEvent call for the frame event, which would typically
        occur during OnShutdown of the owning service.

        @note This method must never be called during the handler of the named frame event.

        @param name The name of a IFrameEvent instance you wish to handle
        @param pHandler The IBase pointer of an interface for handling that event. The specific
            interface that is used is determined by each specific frame event.
        @param priority The priority at which your handler should be invoked. Higher priority
            handlers are invoked before those with lower priority values.
    */
    virtual bool AddFrameEventHandler(const char* name, IBase* pHandler, SInt32 priority = 0);

    /**
        Remove a previously registered handler from a frame event.

        This would typically be called during the OnShutdown method of a system service which owns
        the handler.

        @note This method must never be called during the handler of the named frame event.

        @param name The name of an IFrameEvent instance you wish to stop handling
        @param pHandler The IBase pointer of an interface for handling that event. The specific
            interface that is used is determined by each specific frame event.
    */
    virtual bool RemoveFrameEventHandler(const char* name, IBase* pHandler);

    /**
        Unregister a frame event previously registered with RegisterFrameEvent.

        @param name The name of a IFrameEvent instance to remove
        @return True if the event was unregistered successfully.
    */
    virtual bool UnregisterFrameEvent(const char* name);

    /**
        Convince method to both register a frame event and also add a handler. This performs the
        same work as making two separate calls to RegisterFrameEvent and AddFrameEventHandler.

        @param pEvent The frame event to register. It must have a unique name in order to register
            successfully.
        @param pHandler The IBase pointer of an interface for handling that event. The specific
            interface that is used is determined by each specific frame event.
        @param eventPriority The priority at which this frame event will execute. If the special
            value efd::kUseDefaultPriotity is used, the priority will be determined by calling the
            efd::IFrameEvent::GetDefaultPriority method.
        @param handlerPriority The priority at which your handler should be invoked. Higher priority
            handlers are invoked before those with lower priority values.
        @return True if the event was registered successfully. When  a true value is returned the
            caller must eventually call RemoveHandlerAndUnregisterFrameEvent to remove the event.
    */
    bool RegisterFrameEventAndAddHandler(
        IFrameEvent* pEvent,
        IBase* pHandler,
        SInt32 eventPriority = kUseDefaultPriotity,
        SInt32 handlerPriority = 0);

    /**
        Convenience method to remove a handler and then unregister the frame event. This performs
        the same work as two separate calls to RemoveFrameEventHandler and UnregisterFrameEvent.

        @param name The name of a IFrameEvent instance you wish to unregister
        @param pHandler The IBase pointer of an interface for handling that event. The specific
            interface that is used is determined by each specific frame event.
        @return True if the event was unregistered successfully.
    */
    bool RemoveHandlerAndUnregisterFrameEvent(const char* name, IBase* pHandler);

    //@}
    /// @name Time and Clock management methods
    //@{

    /**
         The ServiceManagerTime is a "stepped real time" clock.  By stepped it means that it only
         increments once at the beginning of each "main loop" of the ServiceManager.  By real time
         it means that it advances at a rate of one second per real-world second.  The
         ServiceManager time will be synchronized between all servers and all clients.
    */
    inline efd::TimeType GetServiceManagerTime() const;


    /**
        Register a clock with the service manager. This clock will be updated every tick. The
        clock will be deleted when the ServiceManager is destroyed unless unregistered.

        @param clock the clock to be registered.
        @return bool returns whether or not the clock was properly registered. If
         a clock by that id already exists, the return value is false.
    */
    bool RegisterClock(IClock* clock);

    /**
        Remove a clock from the service manager. The clock is not deleted, it is assumed
        that the caller will delete the clock.

        @param clock the clock to be unregistered.
        @return bool returns whether or not the clock was found.
    */
    bool UnregisterClock(IClock* clock);

    /**
        Get the time for the specified clock.

        @param id The clock to query; this is the IClock::GetClockClassID value for a clock
            previously registered with the RegisterClock method.
        @return efd::TimeType with the current time of the clock. If no clock by that id
            exists, the return value is 0.0f.
    */
    TimeType GetTime(efd::ClassID id) const;

    /**
        Get the clock for the specified identifier.

        @param id the clock to query; this is the IClock::GetClockClassID value for a clock
            previously registered with the RegisterClock method.
        @return An efd::IClock pointer for the requested clock, if found (NULL otherwise).
    */
    IClock* GetClock(efd::ClassID id) const;

    //@}

    /// @name Logging and Performance monitoring utilities
    //@{

    /**
        Specifies if the ServiceManager should periodically log a detailed time break-down of
        the running services. By default the service manager will log this information. Note:
        Even if service time logging is disabled, the ServiceManager will still log if any
        services take longer than the specified max acceptable tick time.
    */
    inline void SetPeriodicLogServiceTiming(efd::Bool bEnableLogging);

    /// Determine if periodic log timings are enabled.
    /// @return true if periodic log timings are enabled.
    inline efd::Bool GetPeriodicPeriodicLogServiceTiming() const;

    /**
        Set how often we log a detailed time break-down of the running services. The
        ServiceManager defaults to a 20 second log interval.
    */
    inline void SetLogTimingDumpInterval(efd::TimeType kTimingDumpInterval);

    /// Get how often we log a detailed time break-down of the running services.
    inline efd::TimeType GetLogTimingDumpInterval() const;

    /**
        Set the maximum number of Milliseconds that we expect a single Tick to use.  If a tick
        takes longer then we will generate a slow-frame warning and log timing data. By default
        the ServiceManager uses a 5 millisecond max acceptable tick time.
    */
    inline void SetMaxAcceptableTickTime(efd::TimeType kMaxAcceptableTickTime);

    /// Get the maximum number of Milliseconds that we expect a single Tick to use.
    inline efd::TimeType GetMaxAcceptableTickTime() const;

    //@}
    /// @name Thread yeild behavior control
    //@{

    /**
        A special value which can be passed to ServiceManager::SetSleepTime to avoid sleeping at
        all.

        @note Skipping the sleep behaves very differently from using a sleep interval of zero.
        Sleeping for zero milliseconds will still yield the CPU which can limit the rate of your
        program.
    */
    static const efd::UInt32 kNoSleep = 0xFFFFFFFF;

    /**
        Gets the value for the milliseconds to sleep on every tick.
        @return Number of milliseconds to sleep
    */
    inline efd::UInt32 GetSleepTime() const;

    /**
        Sets the amount of time in milliseconds to sleep on every tick.  This limits the
        maximum frame rate of the application.  A value of ServiceManager::kNoSleep will result
        in skipping the sleep call completely.

        @param sleeptime Number of milliseconds to sleep on every tick
    */
    inline void SetSleepTime(efd::UInt32 sleeptime);

    /**
        Gets the value for the milliseconds to sleep on every tick if using DeactivatedSleepTime.
        @return Number of milliseconds to sleep
    */
    inline efd::UInt32 GetDeactivatedSleepTime() const;

    /**
        Sets the amount of time in milliseconds to sleep on every tick if using
        DeactivatedSleepTime.  This limits the maximum framerate of the application.  A value of
        ServiceManager::kNoSleep will result in skipping the sleep call completely.

        @param sleeptime Number of milliseconds to sleep on every tick when deactivated
    */
    inline void SetDeactivatedSleepTime(efd::UInt32 sleeptime);

    /**
        Instructs the ServiceManager to start or stop using DeactivatedSleepTime each frame, rather
        than the usual SleepTime.  This is called when the app should yield CPU to other processes
        on the same machine, such as rapid iteration tools.

        @param deactivated True if DeactivatedSleepTime should be used to sleep each frame
    */
    inline void UseDeactivatedSleepTime(bool deactivated);

    //@}
    /// @name ProgramType method
    //@{

    /**
        The ProgramType identifies the intent of the application running the ServiceManager.
        By assigning it here we make it available throughout the application.
    */
    enum ProgramType
    {
        kProgType_Invalid,
        kProgType_Client        = 0x00000001,
        kProgType_Server        = 0x00000002,
        kProgType_Tool          = 0x00000004,
    };

    /**
        Set the program type associated with this ServiceManager. You may set multiple program
        types by calling this API multiple times if your application fills multiple roles.
    */
    void SetProgramType(ProgramType i_pt, bool i_on = true);

    /**
        Return true if this program type is the same is i_pt.
        @note Be aware that multiple program types can be set.
    */
    bool IsProgramType(ProgramType i_pt);

    //@}

    /**
        Get the VirtualProcessID for this instance of ServiceManager. The VirtualProcessID is
        uniquely identifies this instance of the service manager.

        This function is not valid to be called before SetVirtualProcessID has been called.
    */
    efd::UInt32 GetVirtualProcessID() const;

    /**
        Set the VirtualProcessID for this instance of ServiceManager.
    */
    void SetVirtualProcessID(efd::UInt32 procID);

    /**
       Get the VirtualProcessName for this instance of ServiceManager.
       Will return an empty string before SetVirtualProcessName has been called.
    */
    const efd::utf8string GetVirtualProcessName() const;

    /**
       Set the VirtualProcessName for this instance of ServiceManager.
    */
    void SetVirtualProcessName(const efd::utf8string& procName);

    /**
       Registers platform appropriate signal handlers for ctrl-C
       should be called after any scripting runtimes have been registered
    */
    virtual void RegisterSignalHandlers();

    /**
         Translates the message type ID or ClassID into a human readable string.
          (mostly for use in log messages so can relate to real IDs)

         @param typeID the type or class to be translated.
         @return efd::utf8string containing the string for the ID specified in human readable hex
            form.
    */
    static efd::utf8string IDToString(efd::ClassID typeID);

protected:

    /// @cond EMERGENT_INTERNAL

    struct DependencyData
    {
        /// Constructor
        inline DependencyData(SSID id, SInt32 flags);

        SSID m_service;
        SInt32 m_flags;
    };

    /**
        Create a class that encapsulates the SSID and the smart pointer for the service so that
        we can use a list and the memory and smart pointer will be handled automatically by the
        template list.
    */
    class ServiceInfo : public RefCount
    {
    public:
        /// Constructor
        inline ServiceInfo();

        /// Copy constructor
        inline ServiceInfo(const ServiceInfo &sysSer);

        /// Destructor
        inline ~ServiceInfo();

        inline bool operator == (const ServiceInfo &sysSer);
        inline bool operator != (const ServiceInfo &sysSer);

        inline bool IsType(SSID id) const;

        /// @name Service data
        //@{
        SSID m_idSysSer;
        ServiceState m_state;
        int m_priority;
        ISystemServicePtr m_spSysSer;
        efd::vector<SSID> m_aliases;
        efd::vector<DependencyData> m_dependencies;
        //@}

        /// @name Timing data
        //@{
        efd::TimeType m_totalTimeSpent;
        efd::UInt32 m_totalTicks;
        static const efd::UInt32 kTickHistorySize = 20;
        efd::TimeType m_recentTickTimes[kTickHistorySize];
        efd::UInt32 m_insertPoint;
        //@}

        /// @name Timing methods
        //@{
        /// Set all data to initial condition
        inline void ResetTiming();

        /// Store the time taken by the last tick
        inline void StoreLastTickTime(efd::TimeType time);

        /// Retrieve the time taken by the last tick
        inline efd::TimeType GetLastTickTime() const;

        /// Calculate the Lifetime Average Seconds Per Frame.  This is fairly cheap to compute.
        inline efd::TimeType ComputeLifetimeAverageSPF() const;

        /// Calculate the Recent Average Seconds Per Frame.  This is fairly expensive to compute.
        inline efd::TimeType ComputeRecentAverageSPF() const;
        //@}
    };

    // Helper class used in LogServiceTiming.  Defined here since local functions are apparently
    // not supported in gcc.  None the less this should be treated as a private function scoped to
    // the LogServiceTiming method.
    class ServiceSorter
    {
    public:
        /// Constructor
        inline ServiceSorter(ServiceInfo* service);

        /// Operator used to sort the ServiceInfo instances by lifetime average time per tick
        inline bool operator<(const ServiceSorter& rhs) const;

        ServiceInfo* m_pService;
        efd::TimeType m_time;
    };

    /// Helper class used for generating service dependency graphs. It's main purpose is simply to
    /// avoid copying the ServiceInfo structures while otherwise acting like one.
    class ServiceInfoProxy
    {
    public:
        /// Constructor
        ServiceInfoProxy(ServiceInfo* pSI = NULL);

        /// Access the ClassID from the ServiceInfo
        SSID GetClassID() const;

        /// @name comparison methods that compare by ClassID
        //@{
        bool operator<(const ServiceInfoProxy& rhs) const;
        bool operator==(const ServiceInfoProxy& rhs) const;
        bool operator!=(const ServiceInfoProxy& rhs) const;
        //@}

        ServiceInfo* m_pSI;
    };

    /// Helper function used for sorting service dependency graphs by service priority
    static bool PrioritySortFunction(
        const ServiceManager::ServiceInfoProxy& one,
        const ServiceManager::ServiceInfoProxy& two);

    /// Helper class for starting and stopping the performance timer on a given service.
    class RunningServiceTimer
    {
    public:
        RunningServiceTimer(ServiceManager& srvMgr, ServiceManager::ServiceInfo* pServiceInfo);
        ~RunningServiceTimer();

        RunningServiceTimer& operator=(const RunningServiceTimer& other);

        ServiceManager& m_srvMgr;
        ServiceManager::ServiceInfo* m_pServiceInfo;
        TimeType m_startTime;
    };

    /// @endcond

    /**
    */
    void RemoveAliases(ServiceInfo* serviceInfo);

    /**
        Helper method to generate a ServiceInfo for a registered service and either immediately
        register it or queue it for later registration.
    */
    AsyncResult RegisterSystemService(
        ISystemService *pSysSer,
        SSID idSysSer,
        int iPriority,
        bool allowAliases);

    /**
        RegisterSystemService actually registers the service by adding it to the
        list of registered services and calling its init method.

        @param spSysSer A pointer to a system service structure containing the
                       information required to register a system service.
    */
    virtual AsyncResult RegisterSystemService(ServiceInfo* spSysSer);

    /**
        UnregisterSystemService actually unregisters the service by moving it into the shutting
        down state.

        @param spSysSer A pointer to a system service structure containing the
                       information required to find the service to unregister.
    */
    AsyncResult UnregisterSystemService(ServiceInfo* spSysSer);

    /**
        RegUnRegSystemServices loops through the list of services to register or unregister and
        performs the task.
    */
    virtual void UnregisterSystemServices();

    /**
        TickServices loops through the list of registered services and ticks
        each service in turn from the highest priority to the lowest priority.
    */
    virtual void TickServices();

    /**
        Returns the AsyncResult value that triggered ServiceManager shutdown
    */
    inline efd::AsyncResult GetRunResult() const;

    /// Call OnPreInit for any services added since the last tick. OnPreInit is called in the order
    /// the services were added.
    bool RunPreInitServices();
    /// Call OnInit for any services in the initializing state. OnInit is called in dependency
    /// order
    bool RunInitingServices();
    /// Call OnTick for any services in the running state. OnTick is called in priority order
    bool RunTickingServices();
    /// Call OnShutdown for any services in the shutting down state. OnShutdown is called in
    /// reverse priority order.
    bool RunShuttingDownServices();

    /// Move all services in to the shutting down state
    void CancelActiveServices();

    /**
        Helper for outputting service timing data to the logs.  Writes the following information
        for each registered service:

        * Name - name of the service
        * LifeTime Average Time (LTT): overall average time per tick for the life of the program
        * Recent Average Time (RAT): average time per tick for the last 20 ticks
        * Last Tick Time (LTT): time used on the most recent completed tick
        * Percent Time (%time): percent of total tick time for all services used by this service
        @note These are indicators of possible problems, but might be expected conditions for
            some services.  Indicators currently include:
            - Slow: this service took more than 10ms to tick
            - Hog: this service is more than 50% of total time
            - Spike: this tick took twice as long as average
    */
    void LogServiceTiming();

protected:
    /// @name IAliasRegistrar and IDependencyRegistrar methods
    //@{
    virtual bool AddIdentity(SSID idSysSer);
    virtual bool AddDependency(SSID idSysSer, efd::UInt32 flags);
    //@}

    /// Helper to apply all dependency data in order to determine the init and shutdow orders
    void ComputeDependencyOrder();

public:

    /**
        Get the last tick time of a service.
    */
    TimeType GetServiceLastTickTime(SSID idSysSer);

    /**
        Get the map of services SSIDs versus accumulated time in each
        The map is only valid if the ServiceTimeStatType includes SERVICETIME_ACCUMULATE
    */
    const efd::map<SSID, TimeType>& GetAccumulatedServiceTimes();

    /// Reset the map of services SSIDs versus accumulated time in each
    void ResetAccumulatedServiceTimes();

    /// Dump the accumulated service times to the log
    void DumpAccumulatedServiceTimes();

    /// Possible bit values used for SetServiceTimeStatTypes.
    enum ServiceTimeStatType
    {
        SERVICETIME_NONE = 0,
        SERVICETIME_LOG = 1<<0,
        SERVICETIME_ACCUMULATE = 1<<1,
        SERVICETIME_METRICS = 1<<2,
    };

    /**
        Set the types of logging we are doing for services.  Use a logical OR of the values in
        the ServiceTimeStatType enum.
        @note The SERVICETIME_METRICS bit will always be added whenever EE_ENABLE_METRICS_LOGGING is
            defined.
    */
    void SetServiceTimeStatTypes(efd::UInt32 types);

    /// Get the types of logging we are doing for service timing.
    efd::UInt32 GetServiceTimeStatTypes();

protected:
    /// The map of service SSIDs versus accumulated time spent
    efd::map<SSID, TimeType> m_mapAccumulatedServiceTimes;

    /// The section name for retrieving frame rate configuration variables
    const static char* kConfigFramerate;
    /// The key name for the sleep time value
    const static char* kSleepKey;
    /// The key name for the sleep time value when deactivated
    const static char* kDeactivatedSleepKey;

    /**
        Checks the configuration manager for frame rate settings for the ServiceManager.
    */
    void ConfigureFramerate();

private:

    /// @cond EMERGENT_INTERNAL

    /**
        A global shut-down signal. This can be switched to true from any thread and will cause
        all ServiceManager instances to shut down.
    */
    static bool ms_bGlobalShutdownRequested;

    /// A helper used for ctrl-C handling on some platforms
    static void HandleSignal(efd::SInt32 sig);

protected:
    ServiceState m_threadState;
    bool m_bShutdownRequested;

    efd::UInt32 m_programTypes;

    /// When GetServiceManagerTime exceeds this we know its time to perform a periodic dump of the
    /// service timing information to the logs.
    efd::TimeType m_nextTimingDump;

    typedef efd::list<efd::SmartPointer<ServiceInfo> > SystemServiceList;

    /// @name Service lists
    /// These lists track services that need to have various methods called on them. As each
    /// service completes its work and advances to the next state then services are removed from
    /// these lists. When new services are added or removed the lists are regenerated in the
    /// ComputeDependencyOrder method.
    //@{
    /// List of services that need to have OnPreInit called in whatever order services were added
    /// to the ServiceManager via RegisterService.
    SystemServiceList m_preInitList;
    /// List of services that need to have OnInit called in dependency order
    SystemServiceList m_initList;
    /// List of services that need to have OnTick called in priority order
    SystemServiceList m_tickList;
    /// List of services that need to have OnShutdown called in reverse dependency order
    SystemServiceList m_shutdownList;
    //@}

    /// List of all registered services sorted by service priority. This master list ensures that
    /// the ServiceInfo data is preserved even once the service enters the Complete state. It is
    /// sorted in priority order mainly for legacy reasons, but we use it's sort order when we
    /// regenerate the m_tickList in response to new services being added or removed.
    SystemServiceList m_servicePriorityList;

    /// List of services to be unregistered at the next appropriate opportunity
    SystemServiceList m_pendingUnregisterList;

    /// True if the service lists need to be generated on the next TickServices call. The
    /// m_preInitList and m_servicePriorityList are maintained directly when services are added
    /// and removed but all other lists (m_initList, m_tickList and m_shutdownList) are regenerated
    /// as needed. This flag indicates that the ComputeDependencyOrder needs to be called.
    bool m_dependenciesChanged;

    /// A map for faster lookups in GetSystemService, all system service IDs and aliases are in
    /// this map.
    typedef efd::map<SSID, efd::SmartPointer<ServiceInfo> > SystemServiceMap;
    SystemServiceMap m_SysSerMap;

    /// Used to remember the currently active service for IAliasRegistrar callbacks
    efd::SmartPointer<ServiceInfo> m_spCurrentService;
    /// Used to indicate whether the currently active service (m_spCurrentService) is allowed to
    /// have aliases during IAliasRegistrar callbacks. When a service is registered with an
    /// alternate SSID it cannot have aliases.
    bool m_aliasesAllowed;

    typedef efd::map<efd::ClassID, IClock*> ClockList;
    ClockList m_clocks;

    efd::StepHighPrecisionClock m_clock;

    efd::UInt32 m_sleepTime;
    efd::UInt32 m_deactivatedSleepTime;
    bool m_useDeactivatedSleepTime;

    /// This is how often we log a detailed time break-down of the running services.
    efd::TimeType m_kTimingDumpInterval;

    /**
        This is the maximum number of Milliseconds that we expect a single Tick to use.
        If a tick takes longer then we will generate a slow-frame warning and log timing data.
    */
    efd::TimeType m_kMaxAcceptableTickTime;

    efd::Bool m_bLogPeriodicServiceTiming;

    /// keeps track of if we are already in a RunOnce call
    bool m_inRunOnce;

    efd::UInt32 m_virtualProcessID;
    efd::utf8string m_virtualProcessName;

    /// The current service time statistics being generated - a logical OR of the
    /// values in the ServiceTimeStatType enum
    efd::UInt32 m_uiServiceTimeStatTypes;

    typedef efd::MessageWrapper< efd::IMessage, kMSGID_StartTick > StartTickMessage;
    efd::SmartPointer< StartTickMessage > m_spStartTickMsg;

    IFrameEvent* GetFrameEvent(const char* name);

    typedef EE_STL_NAMESPACE::pair<efd::SInt32, efd::SmartPointer<IFrameEvent> > FrameEventEntry;
    typedef EE_STL_NAMESPACE::multimap<
        efd::SInt32,
        efd::SmartPointer<IFrameEvent>,
        EE_STL_NAMESPACE::greater<efd::SInt32>,
        efd::CustomAllocator<FrameEventEntry> > FrameEvents;
    FrameEvents m_frameEvents;
    /// @endcond
};

/// A smart pointer for the ServiceManager class
typedef efd::SmartPointer<ServiceManager> ServiceManagerPtr;

} //  namespace efd

#include <efd/ServiceManager.inl>

#endif // EE_SERVICEMANAGER_H
