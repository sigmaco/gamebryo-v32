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
#ifndef EE_SIMDEBUGGER_H
#define EE_SIMDEBUGGER_H

// SimDebugger is compiled out of Shipping configurations
#ifndef EE_CONFIG_SHIPPING

#include <efd/IBase.h>
#include <efd/TimeType.h>
#include <egf/egfClassIDs.h>
#include <egf/EntityID.h>

namespace egf
{

class DebugNoteBase;
class Entity;
class EntityManager;
class FlatModelManager;
class IProperty;
class Scheduler;

/**
    This singleton implements the engine-side logic of a remote simulation/entity debugger. It sends
    events to Toolbench, which presents a visualization and means of inspecting the internals of the
    running simulation. Toolbench can also send requests back to the SimDebugger to alter entities.

    This class can optionally be used as a base for game-specific extensions to the debugger.
*/
class EE_EGF_ENTRY SimDebugger : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(SimDebugger, efd::kCLASSID_SimDebugger, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

public:

    /// @name Construction and Destruction
    //@{
    /// default constructor.
    SimDebugger();

    /// virtual destructor allows for subclasses.
    virtual ~SimDebugger();
    //@}

    /**
        Accessor method for the debugger object.

        @return Pointer to the debugger.
    */
    static SimDebugger* Instance();

    /**
        Establishes the singleton instance of the debugger.

        @param pInstance The SimDebugger instance.
    */
    static void SetInstance(SimDebugger* pInstance);

    /**
        Frees the singleton debugger object.
    */
    static void Release();

    /**
        Initialization routine to setup debugger messaging with Toolbench.

        @param pServiceMgr The ServiceManager for this process.
    */
    virtual void Initialize(efd::ServiceManager* pServiceMgr);

    /**
        Begins synchronizing state with the Toolbench Sim Debugger.
    */
    virtual void StartSession();

    /**
        Informs Toolbench about an entity in the world and tracks it for ongoing property updates.

        @param pEntity The entity to monitor.
    */
    virtual void StartTrackingEntity(const egf::Entity* pEntity);

    /**
        Informs Toolbench that an entity has been removed from the world and unregisters for
        updates.

        @param pEntity The entity to stop monitoring.
    */
    virtual void StopTrackingEntity(const egf::Entity* pEntity);

    /**
        Informs Toolbench of an entity property change.

        @param pEntity The entity with the property change.
        @param propID The ID of the changed property.
        @param pProperty The changed property.
    */
    virtual void SendPropertyUpdate(
        egf::Entity* pEntity,
        egf::PropertyID propID,
        const egf::IProperty* pProperty);

    /**
        Periodically inspects registered entities and sends property updates to Toolbench.
    */
    virtual void OnTick();

    /**
        Shuts the debugger down, including messaging.
    */
    virtual void Shutdown();

    /**
        Handle incoming commands from Toolbench.

        @param pMessage The message delivered from the MessageService.
        @param targetChannel The category the message was delivered to.
    */
    virtual void HandleSimDebuggerCommand(
        const efd::StreamMessage* pMessage,
        efd::Category targetChannel);

    /**
        Sends a simulation event notification to Toolbench for recording and visualization.

        @param pMessage The event message to send.
    */
    void SendEvent(egf::DebugNoteBase* pMessage);

    /**
        Sends a simulation event notification to Toolbench for recording and visualization.

        @param eventName The name of the event to send.
        @param gameID The ID of an entity associated with the event.
    */
    void SendEvent(
        const efd::utf8string& eventName,
        egf::EntityID gameID = egf::kENTITY_INVALID);

    /**
        Sends a simulation event notification to Toolbench for recording and visualization.

        @param eventName The name of the event to send.
        @param params A string containing additional information about the event.
        @param gameID The ID of an entity associated with the event.
    */
    void SendEvent(
        const efd::utf8string& eventName,
        const efd::utf8string& params,
        egf::EntityID gameID = egf::kENTITY_INVALID);

protected:
    /// Flag indicating whether SimDebugger::Initialize has run.
    efd::Bool m_initialized;

    /// Cached pointer to the ServiceManager.
    efd::ServiceManager* m_pServiceManager;
    /// Cached pointer to the MessageService.
    efd::MessageService* m_pMessageService;
    /// Cached pointer to the FlatModelManager.
    egf::FlatModelManager* m_pFlatModelManager;
    /// Cached pointer to the EntityManager.
    egf::EntityManager* m_pEntityManager;
    /// Cached pointer to the Scheduler.
    egf::Scheduler* m_pScheduler;

    /// Flag indicating whether Toolbench has requested events from the running game.
    efd::Bool m_sessionActive;

    /// Game time at session start.
    efd::TimeType m_sessionStartTime;

    /// The set of flat models that have been reported to Toolbench.
    efd::set<egf::FlatModelID> m_flatModelsDefined;

    /// The distance squared an entity must move to trigger an update to Toolbench.
    efd::Float32 m_positionUpdateThresholdSquared;

    /// The angle an entity's facing must change to trigger an update to Toolbench.
    efd::Float32 m_rotationUpdateThreshold;

    /// A storage type for recording the last reported state for tracked Actor entities.
    struct ActorTrackingData
    {
        /// The last position sent to Toolbench for an entity.
        efd::Point3 m_lastReportedPosition;
        /// The last facing angle sent to Toolbench for an entity.
        efd::Float32 m_lastReportedFacing;
    };

    /// A type for storing information about tracked Actor entities.
    typedef efd::map<const egf::Entity*, ActorTrackingData> ActorDataMap;
    /// A database used to keep Toolbench updated about the state of Actor entities.
    efd::vector<ActorDataMap> m_actors;

    /// The next bucket of Actor entities to process during OnTick.
    efd::UInt32 m_nextActorBucket;

    /// A type for storing entity property update counts.
    typedef efd::map<egf::PropertyID, efd::UInt32> PropertyDataMap;
    /// A database to prevent common property updates from spamming messages.
    PropertyDataMap m_properties;

private:
    /// Sends a flat model definition to Toolbench.
    void DefineFlatModel(const egf::FlatModel* pFlatModel);

    /// The singleton debugger instance.
    static efd::SmartPointer<SimDebugger> ms_spInstance;
};

/// A smart pointer type for SimDebugger.
typedef efd::SmartPointer<SimDebugger> SimDebuggerPtr;

} // namespace egf

#include "SimDebugger.inl"

#endif // EE_CONFIG_SHIPPING

#endif
