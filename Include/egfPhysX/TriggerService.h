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
#ifndef EE_TRIGGERSERVICE_H
#define EE_TRIGGERSERVICE_H

#include "egfPhysXLibType.h"

#include <efd/MessageService.h>
#include <efdPhysX/PhysXSDKManager.h>
#include <egf/Scheduler.h>
#include <egfPhysX/SceneService.h>
#include <egfPhysX/EntityActorData.h>
#include <egf/EntityChangeMessage.h>

#include <NxBoxShapeDesc.h>
#include <NxCapsuleShapeDesc.h>
#include <NxSphereShapeDesc.h>
#include <NxUserContactReport.h>

// Forward declarations
class NxUserTriggerReport;

namespace egfPhysX
{
class SceneMessage;

/**
    An enum that describes the PhysX collision status.
*/
enum CollisionStatus
{
    /// An invalid status, value 0.
    COLLIDE_INVALID = 0,

    /// The trigger is due to an enter event, value 1.
    COLLIDE_ON_ENTER = 1,

    /// The trigger is due to a stay event, value 2.
    COLLIDE_ON_STAY = 2,

    /// The trigger is due to a leave event, value 3.
    COLLIDE_ON_LEAVE = 3
};

/**
    The Trigger Service provides functionality for generating trigger events using PhysX
    actors.
*/
class EE_EGFPHYSX_ENTRY TriggerService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        TriggerService,
        efd::kCLASSID_TriggerService,
        efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /**
        Constructor.

        @param runSynchronously This parameter should be set to true when PhysX simulation is
            synchronous, as set by the entity with the PhysXScene model that triggers are
            simulating in. Otherwise, it should be false. It is used to correctly set
            the priority for the service.
    */
    TriggerService(bool runSynchronously = false);

    /**
        @name Entity-Actor Mapping Functions

        A mapping is maintained between entities and the PhysX actor's they use. To find an
        actor for a given entity, use the functions from this class. To find an entity for a given
        actor, use the userData in the NxActor object (which is of type EntityActorData).
    */
    //@{

    /**
        Add an entity and its associated actor.

        The actor is presumed to already be in the scene. The actor's userData member will be
        over-written. Sub-class this class if you need more control of the userData.

        When takeOwnership is true the Trigger Service will be responsible for removing the
        actor when the entity is removed. Set this true only when the calling code will not be
        managing the actor.

        Returns true if the entity and its actor were added, false if the entity already has
        an actor.
    */
    virtual efd::Bool AddEntityActor(
        egf::EntityPtr spEntity,
        NxActor* pActor,
        efd::Float32 scale,
        const bool takeOwnership);

    /**
        Remove an entity and its associated actor from the simulation.

        A call to this function removes the entity from the currently active set, but will
        leave the actor in the simulation until the OnTick function is called.

        The actor is removed from the simulation only if the Trigger Service has ownership of
        this entity's data.

        Returns true if the entity was found and removed. False otherwise.
    */
    virtual efd::Bool RemoveEntityActor(const egf::EntityID& entityID);

    /**
        Get the actor data for an Entity.

        Returns the actor data or NULL if the entity has no actor. Do not free the pointer.
    */
    inline EntityActorData* GetEntityActorData(const egf::EntityID& entityID) const;
    //@}

    /**
        This message handler is called when a new entity is discovered.

        The service only takes action if the entity has the PhysXShape model. If so,
        properties for the PhysX actor are extracted and saved in the service. The actor is
        created in a scene if the entity also has a "SceneName" property naming a valid
        PhysX scene.

        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityDiscoverMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when properties of an entity change.

        Position and orientation information is propagated to the PhysX actors.
        Any property changes affecting the shape or trigger status are also handled.
        The changes are not applied immediately because the state of the PhysX
        simulation may not be modified during simulation. The changes are cached and
        applied during OnTick.

        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been removed from the
        scheduler. The actor for the entity is removed.

        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityRemovedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when a PhysX scene has been added to the SceneService.
        Check the lists for any objects that need to be added to the scene.

        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleSceneAddedMessage(
        const egfPhysX::SceneMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when a PhysX scene has been removed from the SceneService.

        Remove all actors from that scene and keep the object information on the pending queue in
        case a new scene with that name is added.

        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleSceneRemovingMessage(
        const egfPhysX::SceneMessage* pMessage,
        efd::Category targetChannel);

protected:
    /**
        Destructor.

        Deletes internal data.
    */
    virtual ~TriggerService();

    /// Returns the name of the service, in this case "TriggerService".
    virtual const char* GetDisplayName() const;

    /**
        PreInit locates services on which the Trigger Service depends and subscribes to messages.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        Perform per-tick work.

        In this method, behaviors are invoked for any trigger events that fired during the
        preceding frame. In addition, and pending actor creation or removal happens here.
        These actions are delayed until OnTick so that they do not overlap with active
        PhysX simulation.
    */
    virtual efd::AsyncResult OnTick();

    /**
        OnShutdown clears all internal data and removes any PhysX objects that the service created.
    */
    virtual efd::AsyncResult OnShutdown();

    /**
        This class is used by the trigger callback system to match events based on what events
        of interest have been registered through the trigger service.
    */
    class TriggerCallbackHandler : public NxUserTriggerReport, public efd::MemObject
    {
    public:
        /**
            Constructor sets the handler to be disabled, and not process events.
            
            The handler will be re-enabled in PreInit and disabled again in Shutdown.
        */
        TriggerCallbackHandler();

        /**
            The callback function required by NxUserTriggerReport.
        */
        virtual void onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status);

        class TriggerData
        {
        public:
            TriggerData(
                EntityActorData* pTriggerData,
                EntityActorData* pOtherData,
                NxTriggerFlag status,
                const bool statusMatches);

            /// Helper function to compare NxTriggerFlag on a shape to status
            static inline bool ShapeFlagsMatchStatus(
                const NxTriggerFlag& status,
                const NxShape& shape);

            inline TriggerData& operator=(const TriggerData& shape);

            EntityActorDataPtr m_spTriggerActorData;
            EntityActorDataPtr m_spOtherActorData;
            NxTriggerFlag m_status;
            bool m_otherShapeFlagsMatchStatus;
        };

        /// Clean up list of pending callbacks when NxScene is going away
        void RemoveCallbacksForScene(const efd::utf8string& scene);

        /// List of events received
        efd::list<TriggerData> m_triggerEvents;

        /// List of scenes for which this object has been set as a trigger reporter, by name.
        efd::list<efd::utf8string> m_activeScenes;

        /// Whether or not to process trigger events
        bool m_enabled;
    };

    // List of entity actor objects
    typedef efd::list<EntityActorDataPtr> EntityActorList;

    // Functions to extract data from newly discovered entities.
    static efd::Bool GetEntityPose(
        egf::Entity* pEntity,
        NxMat34& pose,
        const efd::Float32& sceneScale);
    static efd::Bool GetEntityShapePose(
        egf::Entity* pEntity,
        NxMat34& pose,
        const efd::Float32& sceneScale);
    static efd::Bool GetEntityShapeType(egf::Entity* pEntity, efd::UInt8& shapeType);
    static efd::Bool GetEntityShapeBox(
        egf::Entity* pEntity,
        NxBoxShapeDesc& boxShapeDesc,
        const efd::Float32& sceneScale);
    static efd::Bool GetEntityShapeCapsule(
        egf::Entity* pEntity,
        NxCapsuleShapeDesc& capsuleShapeDesc,
        const efd::Float32& sceneScale);
    static efd::Bool GetEntityShapeSphere(
        egf::Entity* pEntity,
        NxSphereShapeDesc& sphereShapeDesc,
        const efd::Float32& sceneScale);
    static efd::Bool GetEntityShapeCommon(
        egf::Entity* pEntity,
        NxShapeDesc& shapeDesc,
        const efd::Float32& sceneScale);

    // Helper function to handle actors in the pending actor map.
    void HandlePendingActors(const efd::Bool doTick = true);

    // Helper function to handle trigger callbacks
    void HandleTriggerCallback(
        EntityActorData* pTriggerData,
        const EntityActorData* pOtherData,
        const efd::TimeType& time,
        const CollisionStatus& status);

    // Helper function to create an actor for the specified scene based on the entity provided
    virtual NxActor* CreateActor(
        egf::EntityPtr spEntity,
        NxScene* pScene,
        const efd::Float32& scale);

    // Helper funciton to release an actor. Returns true if the actor was released, false if
    // the simulation was active and prevented release.
    virtual bool ReleaseActor(EntityActorData* pActorData);

    // Helper function to add entity actor to pending list.  Only adds if not already in the list
    inline void AddToPendingList(EntityActorDataPtr spData);

    /// Cached system services used frequently by the animation service.
    efd::MessageServicePtr m_pMessageService;
    SceneServicePtr m_pSceneService;

    // Callback manager
    TriggerCallbackHandler* m_pTriggerCallbackHandler;

    typedef efd::map<egf::EntityID, EntityActorDataPtr> EntityActorDataMap;
    // Map of all known entities to their PhysX data.
    EntityActorDataMap m_entitiesToActorData;

    // Map of actors that need to be added or updated.
    EntityActorList m_pendingActorList;


    // PhysX objects
    enum {
        SHAPE_BOX = 0x00,
        SHAPE_CAPSULE = 0x01,
        SHAPE_SPHERE = 0x02,
        SHAPE_INVALID = 0x8F
    };
};

typedef efd::SmartPointer<TriggerService> TriggerServicePtr;

} // end namespace egfPhysX

EE_SPECIALIZE_ENUM(egfPhysX::CollisionStatus, efd::UInt16);

#include "TriggerService.inl"

#endif // EE_TRIGGERSERVICE_H
