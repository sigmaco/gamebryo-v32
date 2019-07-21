// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2007 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef EE_PROPSERVICE_H
#define EE_PROPSERVICE_H

#include "ecrPhysXLibType.h"

#include <efd/ISystemService.h>
#include <efd/UniversalTypes.h>
#include <efd/MessageService.h>
#include <efd/ServiceManager.h>

#include <egf/EntityManager.h>

#include <egf/Entity.h>
#include <egfPhysX/SceneService.h>
#include <egfPhysX/SceneMessage.h>
#include <egfPhysX/EntityActorData.h>

#include <ecr/CoreRuntimeMessages.h>
#include <ecr/SceneGraphService.h>

#include <NiPhysXScene.h>

namespace ecrPhysX
{

/**
    The Prop Service interfaces between the Core Runtime NiPhysX system and the
    GameFramework entity system.

    Its primary purpose is to support the loading and simulation of PhysX
    assets streamed in Nif files.

    An entity may have one or more NiPhysXProps associated with it; currently
    the only path for creating such associations is by loading them from a NIF
    file. Multiple props are typically used by the Gamebryo toolchain to
    compartmentalize rigid bodies, cloth, and particles/fluids.
*/
class EE_ECRPHYSX_ENTRY PropService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        PropService,
        efd::kCLASSID_PhysXPropService,
        efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /// Default constructor; sets member initial values and default service priority.
    PropService(bool runSynchronously = false);

    /**
        Provide a NiSPWorkflowManager to be used by NiPhysXScene objects.

        The workflow manager that is provided is used for all subsequently created NiPhysXScene objects.
        It is recommended that this be called during OnPreInit or OnInit, using the object returned
        by ecr::SceneGraphService::GetWorkflowManager.
    */
    void SetWorkflowManager(NiSPWorkflowManager* pManager);

    /**
        Set the value of AsynchronousSimulation to be used by NiPhysXScene objects.

        The value provided is used for all subsequently created NiPhysXScene objects. It is
        recommended that this be called before or during OnPreInit. All PhysX related services
        should use the same value for this flag.
    */
    void SetAsynchronousSimulation(efd::Bool bIsAsynchronous);

    /// Make a call to UpdateSources for all sources in this prop.
    /// For more information see the NiPhysXProp class reference.
    virtual void UpdateSources(efd::Bool bForce);

    /// A version of UpdateSources that defaults to a non-forced update. This method simply calls
    /// the virtual method with a 'false' parameter. This method is called once per frame as a
    /// frame event.
    inline void UpdateSources();

    /// Make a call to UpdateDestinations for all destinations in this prop.
    /// For more information see the NiPhysXProp class reference.
    virtual void UpdateDestinations(efd::Bool bForce);

    /// A version of UpdateDestinations that defaults to a non-forced update. This method simply
    /// calls the virtual method with a 'false' parameter. This method is called once per frame as
    /// a frame event.
    inline void UpdateDestinations();

    /// Handler for changes to the entity via rapid iteration.
    /// May use PendPropData() to queue PropData for processing in OnTick().
    void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /// Handler for entities being removed from the scheduler.  We only update trigger related
    /// data when the entity is removed.  Everything else related to the prop will be handled
    /// when HandleSceneGraphRemovedMessage()is called.
    void HandleEntityRemovedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /// Handler for adding scene graphs when Nifs are loaded.
    void HandleSceneGraphAddedMessage(
        const ecr::SceneGraphMessage* pMessage,
        efd::Category targetChannel);

    /// Handler for removing scene graphs.
    void HandleSceneGraphRemovedMessage(
        const ecr::SceneGraphMessage* pMessage,
        efd::Category targetChannel);

    /// Handler for changes in the egfPhysX::SceneService.
    void HandleSceneAddedMessage(
        const egfPhysX::SceneMessage* pMessage,
        efd::Category targetChannel);
    /// Handler for changes in the egfPhysX::SceneService - called when the scene
    /// will be removed but is still accessible in SceneService's data structures.
    void HandleSceneRemovingMessage(
        const egfPhysX::SceneMessage* pMessage,
        efd::Category targetChannel);
    /// Handler for changes in the egfPhysX::SceneService - called after the scene
    /// is no longer accessible via SceneService's data structures.
    void HandleSceneRemovedMessage(
        const egfPhysX::SceneMessage* pMessage,
        efd::Category targetChannel);

    /// Handlers for simulation messages from the scene service
    //@{
    void HandleStartingSimulationMessage(
        const egfPhysX::SimulationMessage* pMessage,
        efd::Category targetChannel);
    void HandleFinishingSimulationMessage(
        const egfPhysX::SimulationMessage* pMessage,
        efd::Category targetChannel);
    void HandleSimulationTimeUpdateMessage(
        const egfPhysX::SimulationMessage* pMessage,
        efd::Category targetChannel);
    //@}

    /// @name Built-ins

    //@{

    /// Support for built-ins querying status of debug geometry.
    ///
    /// Returns false if we can't find a scene of the given name.
    inline efd::Bool GetDebugRender(const efd::utf8string& sceneName);

    /**
        Support for built-ins turning debug geometry on or off.

        Visualization scale is set to the scale of the first PhysX scene activated,
        which may cause problems when multiple PhysX scenes at different scales are
        being visualized.
    */
    void SetDebugRender(const efd::utf8string& sceneName, efd::Bool bActive);

    /// Support for built-ins purging debug geometry.
    void ClearDebugGeometry(const efd::utf8string& sceneName);

    /// Support for built-ins applying forces.
    //@{
    /// Apply a given force vector to all actors in an entity.
    void ApplyForce(const egf::EntityID& eid, efd::Point3 force);

    /// Apply a given force vector at a particular point.
    void ApplyForceAtPos(const egf::EntityID& eid, efd::Point3 force, efd::Point3 pos);
    //@}

    /// Support for built-ins applying torques.
    //@{
    /// Apply a given torque vector to all actors in an entity.
    void ApplyTorque(const egf::EntityID& eid, efd::Point3 torque);
    //@}

    /// Resets the PhysX scene called sceneName to the specified stateID.
    ///
    /// Return true if the scene is found.  Otherwise return false.
    efd::Bool ResetState(const efd::utf8string& sceneName, efd::UInt32 stateID);

    //@}

    /// Returns how many NiPhysXProps are associated with this entity.
    inline efd::UInt32 GetNumProps (const egf::EntityID& eid);

    /// Gets the NiPhysXProp associated with this entity ID at the given index.
    inline NiPhysXProp* GetPropAt (const egf::EntityID& eid, efd::UInt32 index);

    /// Gets the NiPhysXScene with the given name.
    inline NiPhysXScene* GetScene(const efd::utf8string& sceneName);

    /// Gets the NiPhysXScene that the given prop is currently instantiated
    /// in, or NULL if the prop is not in any scene at this time.
    inline NiPhysXScene* GetPropCurrentScene(const egf::EntityID& eid);


protected:
    /// Destructor. Most memory should be released during OnShutdown() so this has minimal
    /// responsibilities.
    virtual ~PropService();

    /// Return the name of the service, in this case "PropService".
    virtual const char* GetDisplayName() const;

    /// Registers dependencies and caches pointers to other services.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /// Sets up two frame events for use by the PropService.
    virtual efd::AsyncResult OnInit();

    /// Update the service for the current frame.
    virtual efd::AsyncResult OnTick();

    /// Tear down the service.
    virtual efd::AsyncResult OnShutdown();

    /**
        Simple state machine to ensure that ProcessPendingRemovals() handles
        scene graphs correctly if multiple events occur during a single frame.
        Initialize to SET_SCENE_GRAPH when we first get SceneGraphAdded.
        When we get a scene graph removed, transition to REMOVE_SCENE_GRAPH.
        Transition to REPLACE_SCENE_GRAPH if we get a SceneGraphAdded message
        while in REMOVE.
    */
    enum
    {
        PROP_SET_SCENE_GRAPH = 0x00,
        PROP_REMOVE_SCENE_GRAPH = 0x01,
        PROP_REPLACE_SCENE_GRAPH = 0x02
    };

    /// All data needed to handle management of an NiPhysXProp.
    struct PropData : public efd::MemObject
    {
        PropData(egf::Entity* pEntity);

        /// Stores pProp, then triggers an update
        void AddProp(NiPhysXProp* pProp);
        void ClearProps(void);

        /// Sets transform on scale on the NiPhysXProp
        /// from values cached in this data structure.
        void UpdateProp();

        efd::vector<NiPhysXProp*> m_pProps;
        efd::UInt8 m_sceneGraphState;
        /// Smart pointer to the scene graph to make sure our
        /// destination isn't deleted before we are.
        NiAVObjectPtr m_spSceneGraphObject;

        /// Values used to set parameters on the prop
        /// @{
        efd::Point3 m_initialTranslation;
        efd::Point3 m_initialEulerAngles;
        /// @}

        /// Values used when adding the prop to a scene
        /// @{
        efd::UInt32 m_state;
        /// @}

        /// ID of the entity this prop belongs to
        egf::EntityID m_entityID;

        /// Name of the scene this prop is currently in
        efd::utf8string m_currentSceneName;

        /// Name of the scene this prop should be added to
        efd::utf8string m_newSceneName;

        egfPhysX::EntityActorDataPtr m_spTriggerEntityActor;
    };

    /// A list of PropData pointers
    typedef efd::list<PropData*> PropList;

    /**
        Simple state machine to ensure that the Gamebryo-PhysX interface
        is ticked in the correct order, regardless of when during the
        frame a scene is enabled. If the scene becomes eligible for
        processing after UpdateSources(), it won't be processed until
        the next frame's UpdateSources() so that we can ensure the data
        is not corrupt.
    */
    enum
    {
        SCENE_UPDATE_SOURCES = 0x01,
        SCENE_SIMULATE = 0x02,
        SCENE_UPDATE_DESTINATIONS = 0x03
    };

    /// All data needed to handle the management of an NiPhysXScene.
    /// Note that this responsibility is shared with egfPhysX::SceneService,
    /// which monitors NxScenes but not NiPhysXScenes.
    struct SceneData : public efd::MemObject
    {
        SceneData(const efd::utf8string& sceneName);
        ~SceneData();

        /// Update the parameters on the SceneData object and pass those
        /// values to the NiPhysXScene
        void UpdateScene(const egfPhysX::PhysXSceneData* pSrcSceneData);

        NiPhysXScenePtr m_spScene;
        efd::UInt8 m_simulationState;

        /// Scene graph containing PhysX debug geometry, if any.
        /// Since we only access it when turning debug on/off and on shutdown,
        /// we don't also cache the NiNode* or other special data.
        ecr::SceneGraphService::SceneGraphHandle m_debugHandle;

        /// Name of this scene
        efd::utf8string m_sceneName;

        /// Props that had a create or update message arrive and need to be processed
        /// next time the scene is not mid-simulation.
        PropList m_pPropsPending;

        /// Props to be removed from the scene that are mid-simulation at the removal
        /// event.
        PropList m_pPropsPendingRemoval;

        /// Props that currently exist in the scene
        PropList m_pActiveProps;

        efd::Bool m_isSceneDirty;
    };

    /// Send messages
    //@{
    void SendPropAddedMessage(egf::EntityID entityID);
    void SendPropRemovingMessage(egf::EntityID entityID);
    //@}

    /// @name Handles to system services
    //@{
    efd::MessageService* m_pMessageService;
    egfPhysX::SceneService* m_pSceneService;
    ecr::SceneGraphService* m_pSceneGraphService;
    egf::EntityManager* m_pEntityManager;
    //@}

    /// Track how many scenes currently have debug visualization enabled
    /// so we can toggle PhysX SDK functions at appropriate times.
    efd::UInt32 m_scenesInDebug;

    typedef efd::map<efd::utf8string, SceneData*> SceneNameMap;
    /// Map from scene name to scene entity id.
    // Owns scene data; manages creation & deletion.
    SceneNameMap m_sceneNames;

    typedef efd::map<egf::EntityID, PropData*> IDPropMap;
    /// Map from Entity ID value to prop data.
    /// Owns propData; manages creation & deletion.
    IDPropMap m_props;

    NiSPWorkflowManagerPtr m_spWorkflowManager;

    efd::Bool m_isAsynchronousSimulation;

    /**
        If we already have PropData for this Entity, return it.
        If not, try to extract from the Entity, add it to m_props,
        and return it.
        If no PhysXProp model is mixed in, return NULL.
    */
    PropData* GetPropData(egf::Entity* pEntity);

    /// Create the NiPhysX prop from a scene graph in the SceneGraphService and add it
    /// to the prop data.
    /// Return true if prop was added.  Otherwise, return false.
    virtual efd::Bool AddPhysXPropToPropData(egf::Entity* pEntity, PropData* pPropData);

    /// Search through a scene graph, returning the first NiPhysXProp found,
    /// or NULL if none.
    NiPhysXProp* FindNiProp(NiObject* pObj);

    /**
       Adds the prop to the NiPhysX scene.

       If the PropData has an NiPhysXProp object, the scene
       exists, the scene is not mid-simulation, and prop is successfully added to the
       NiPhysXScene object and the m_pActiveProps list, return true.  Otherwise, return false.
    */
    virtual efd::Bool AddPropToScene(PropData* pPropData, SceneData* pSceneData);

    /// Adds the propData to the specified list.  If the list is NULL, a new list is
    /// allocated
    void AppendPropData(PropData* pPropData, PropList& pPropList);

    /**
        Removes PropData from m_propsPerScene or m_propsPending.
        If it's in an NiPhysXScene (not mid-simulation), removes it from the scene.
        May not be called mid-simulation for a prop that is in the scene (in m_propsPerScene).
        @return whether or not the prop has been removed from the scene
    */
    virtual efd::Bool RemovePropFromScene(PropData* pPropData);

    /// Handle changes to scene properties and all the entries in the m_propsPendingRemoval and
    /// m_propsPending lists for the specified scene.  If the NiPhysXScene does not exist,
    /// handle only m_propsPendingRemoval.  If the scene is in mid-simulation, do nothing.
    void HandlePendingChanges(SceneData* pSceneData);

    /// Handle all props on the pending removal queue of the specified scene data
    void ProcessPendingRemovals(SceneData* pSceneData);

    /// Helper function to remove all the props from a scene in the prop service.  If deleteProps
    /// is true, then the props will be deleted.  Otherwise, the props will be queued in case
    /// they can be added to a scene with the same name later.
    void RemoveAllPropsFromScene(SceneData* pSceneData, efd::Bool deleteProps);

    /// Helper function will set all shapes in the prop to have the collision group specified by
    /// the prop entity.
    void SetCollisionGroup(NiPhysXProp* pProp, egf::Entity* pEntity);

    /// Helper function will set the userdata on all actors in the prop to the
    /// specified ActorData.  This allows the TriggerService to recognize those actors.
    void SetTriggerCallbackData(NiPhysXProp* pProp, egfPhysX::EntityActorData* pActorData);

    /**
        Convenience function to get the scene data object with the specified name.  If no object
        exists and the createData flag is true, then create a new object and return it.
    */
    inline SceneData* GetSceneData(const efd::utf8string& sceneName, efd::Bool createData = false);
};

typedef efd::SmartPointer<PropService> PropServicePtr;

}; // namespace ecrPhysX

#include <ecrPhysX/PropService.inl>

#endif // EE_PROPSERVICE_H
