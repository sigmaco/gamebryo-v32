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
#ifndef EE_SCENESERVICE_H
#define EE_SCENESERVICE_H

#include "egfPhysXLibType.h"
#include <efd/MessageService.h>
#include <efdPhysX/PhysXSDKManager.h>
#include <egf/EntityManager.h>
#include <egf/EntityChangeMessage.h>
#include <egf/Entity.h>
#include <egf/egfSystemServiceIDs.h>
#include <egfPhysX/PhysXSceneModel.h>
#include <egfPhysX/PhysXSceneData.h>

namespace egfPhysX
{

/**
    The Scene Service provides functionality to handle the adding, removing, modifying and
    simulating of PhysX scenes
*/
class EE_EGFPHYSX_ENTRY SceneService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SceneService, efd::kCLASSID_SceneService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /// Constructor
    SceneService(bool runSynchronously = false);

    /// A static constant used to convey an invalid simulation time.
    static const efd::TimeType ms_kInvalidSimulationTime;

    /**
        @name Global Simulate and Fetch Functions

        These functions invoke simulate and fetchResults for all known scenes, and send messages
        so that services managing non-owned scenes know to simulate.
    */
    //@{

    /**
        Method to start PhysX simulations.

        @param forceSim Sets time to ensure simulation if SceneService handles simulation.
    */
    virtual void Simulate(const efd::Bool forceSim);
 
    /**
        Method to start PhysX simulations. This version of Simulate simple calls the virtual method
        version with a false parameter.
    */
    inline void Simulate();

    /**
        Method to fetch the results of the PhysX simulations.

        @param forceBlockOnFetch Forces block on results if SceneService handles simulation.
            This over-rides the setting in any individual scene data.
    */
    virtual void FetchResults(const efd::Bool forceBlockOnFetch);

    /**
        Method to fetch the results of the PhysX simulations. This version of FetchResults simple
        calls the virtual method version with a false parameter.
    */
    inline void FetchResults();

    //@}

    /**
        @name PhysX Scene Management

        The Scene Service handles scene management.  PhysX scenes are created outside of the
        service and added to the scene map. Each scene is given a name when it is added to the
        Scene Service.  It can then be accessed by that name.

        Name conflicts are resolved by not adding the scene. As everything related to scenes is
        managed by name, subsequent functions accessing a scene of the conflicting name will
        receive data from the original scene with the name.
    */
    // @{

    /**
        Get the scene data with the specified name.

        This may be used to access any scene properties. including the NxScene object.
    */
    inline PhysXSceneData* GetSceneData(const efd::utf8string& sceneName) const;

    /**
        Add the PhysX scene to the Scene Service.

        This scene will be accessed by using the specified name. If a scene already exists with
        the given name, the existing scene is removed under the assumption that the existing
        scene will subsequently be renamed and re-added.

        An application that adds a scene in this way is responsible for removing it from the
        Scene Service. It is also responsible for deleting the pSceneData after the scene
        has been removed from the service.

        The Scene Service sends a SceneAddedMessage message when a scene is added

        @return False if a scene with the given name existed and was removed; otherwise true.
    */
    virtual efd::Bool AddScene(const efd::utf8string& sceneName, PhysXSceneData* pSceneData);

    /**
        Remove the PhysX scene with the specified name from the list of scenes.

        The Scene Service sends a SceneRemovingMessage message when it knows a scene will be
        removed, but while it is still possible to interact with the scene via the service. A
        SceneRemovedMessage message is sent when the scene has been removed. Subsequent
        attempts to access the scene will fail.

        @return True if the scene was removed, false if a scene with the specified name was
            not found
    */
    virtual efd::Bool RemoveScene(const efd::utf8string& sceneName);

    /**
        Get the service's recommended processor affinity for creating PhysX scenes.

        May be called during PreInit or Init.
    */
    inline virtual efd::ProcessorAffinity GetProcessorAffinity() const;

    // @}

    /**
        @name PhysX Scene Data Access

        The following functions provide access to the PhysXSceneData object for the named scene or
        the given entity. See the egfPhysX::PhysXSceneData class for details on the meaning
        of each parameter.
    */

    // @{

    /**
        Get the ownership of the named scene.

        Return true if the scene is found. Otherwise, return false.
    */
    inline efd::Bool GetSceneOwned(const efd::utf8string& sceneName, efd::Bool& isOwned) const;

    /**
        Sets ownership of the named scene.

        Return true if the scene is found. Otherwise, return false.
    */
    inline efd::Bool SetSceneOwned(const efd::utf8string& sceneName, const efd::Bool isOwned);

    /// Sets the value of scale to be the scale factor of named scene.
    ///
    /// Return true if the scene is found.  Otherwise, return false.
    inline efd::Bool GetScaleFactor(const efd::utf8string& sceneName, efd::Float32& scale) const;

    /**
        Set the scale of the named scene.

        Strange things will happen if you set this after OnInit is called.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool SetScaleFactor(const efd::utf8string& sceneName, const efd::Float32 scale);

    /**
        Sets handleSimulate for the named scene.

        If handleSimulate is false, the service only sends notification messages when starting
        and finishing simulations when Simulate and FetchResults are called.  Other application
        code is expected to handle the actual PhysX simulation.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool GetHandleSimulate(
        const efd::utf8string& sceneName,
        efd::Bool& handleSimulate) const;

    /**
        Set whether or not this service does the PhysX simulation work in addition to sending
        messages when starting and finishing simulation.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool SetHandleSimulate(
        const efd::utf8string& sceneName,
        const efd::Bool handleSimulate);

    /**
        Start simulation on the named scene with the specified start time.

        Return true if the scene with the specified name is found.  Otherwise, return false.
    */
    inline efd::Bool StartSimulating(
        const efd::utf8string& sceneName,
        const efd::TimeType& time = ms_kInvalidSimulationTime);

    /**
        Start simulation on the entity's scene with the specified start time.

        Return true if the entity mixes in the PhysX Scene model, false otherwise.
    */
    efd::Bool StartSimulating(
        const egf::Entity* pSceneEntity,
        const efd::TimeType& time = ms_kInvalidSimulationTime);

    /**
        Stop simulation on the named scene.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool StopSimulating(const efd::utf8string& sceneName);

    /**
        Stop simulation on the entity's scene.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool StopSimulating(const egf::Entity* pSceneEntity);

    /**
        Returns the last time used in simulation for the named scene.

        If the scene is not found, return kINVALID_SIMULATION_TIME
    */
    inline efd::TimeType GetCurrentPhysXTime(const efd::utf8string& sceneName);

    /**
        Returns the last time used in simulation for the entity's scene.

        If the scene is not found, return kINVALID_SIMULATION_TIME
    */
    inline efd::TimeType GetCurrentPhysXTime(const egf::Entity* pSceneEntity);

    /**
        Get the fixed step flag for the named scene.

        Sets isFixedStep to the value of the flag controlling fixed or variable simulation
        timing for the specified scene.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool GetDoFixedStep(const efd::utf8string& sceneName, efd::Bool& isFixedStep) const;

    /**
        Set the flag controlling fixed or variable simulation timing for the named scene.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool SetDoFixedStep(const efd::utf8string& sceneName, const efd::Bool isFixedStep);

    /**
        Get the time step for the names scene.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool GetTimestep(const efd::utf8string& sceneName, efd::Float32& step) const;

    /**
        Set the timestep used with fixed time stepping for the specified scene.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool SetTimestep(const efd::utf8string& sceneName, const efd::Float32 step);

    /**
        Get the maximum number of sub-steps that PhysX will be asked to take for the
        named scene.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool GetMaxSubSteps(const efd::utf8string& sceneName, efd::UInt32& maxSteps) const;

    /**
        Set the maximum number of steps that PhysX will be asked to take for the named scene.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool SetMaxSubSteps(const efd::utf8string& sceneName, const efd::UInt32 maxSteps);

    /**
        Gets the number of sub-steps per timestep for the named scene.

        Returns true if the scene is found. Otherwise, returns false.
    */
    inline efd::Bool GetNumSubSteps(
        const efd::utf8string& sceneName,
        efd::UInt32& numSubSteps) const;

    /**
        Sets the number of sub-steps per timestep for the named scene.

        Returns true if the scene is found. Otherwise, returns false.
    */
    inline efd::Bool SetNumSubSteps(
        const efd::utf8string& sceneName,
        const efd::UInt32 numSubSteps);

    /**
        Get the block on fetch status for the named scene.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool GetBlockOnFetch(
        const efd::utf8string& sceneName,
        efd::Bool& blockOnFetch) const;

    /**
        Set the blocking status of fetch results for the specified scene.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool SetBlockOnFetch(
        const efd::utf8string& sceneName,
        const efd::Bool blockOnFetch);

    /**
        Get the PhysX scene's gravity.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool GetGravity(const efd::utf8string& sceneName, efd::Point3& gravity) const;

    /**
        Set the PhysX scene's gravity.

        Return true if the scene is found.  Otherwise, return false.
    */
    inline efd::Bool SetGravity(const efd::utf8string& sceneName, const efd::Point3 gravity);

    /**
        Get the simulation active status for the named scene.

        The isActive parameter will be set true when the scene name is found and a Simulate
        call has been made on the scene with no matching successful FetchResults. The
        isActive parameter will be false if there has been no Simulate call since the last
        successful FetchResults. In general, it is only safe to perform operations on the
        PhysX SDK when the isActive parameter is returned as false.

        Return true if the scene is found.  Otherwise, return false and do not change isActive.
    */
    inline efd::Bool IsSimulationActive(
        const efd::utf8string& sceneName,
        efd::Bool& isActive) const;

    // @}

    /**
        Get collision flag information based on scene name.

        Sets the value of isEnabled to the value of the collision flag for the specified
        groups.

        Return true if the scene is found and the groups are valid.  Otherwise, return false.
    */
    inline efd::Bool GetGroupCollisionFlag(
        const efd::utf8string& sceneName,
        efd::UInt16 group1,
        efd::UInt16 group2,
        efd::Bool& isEnabled);

    /**
        Get collision flag information based on scene entity.

        Sets the value of isEnabled to the value of the collision flag for the specified
        groups.

        Return true if the entity has a PhysX Scene model and the groups are valid.  Otherwise,
        return false.
    */
    inline efd::Bool GetGroupCollisionFlag(
        const egf::Entity* pSceneEntity,
        efd::UInt16 group1,
        efd::UInt16 group2,
        efd::Bool& isEnabled);

    /**
        Method to set the collision flag between two collision groups in a scene.

        Return true if the scene is found and the groups are valid.  Otherwise, return false.
    */
    inline efd::Bool SetGroupCollisionFlag(
        const efd::utf8string& sceneName,
        efd::UInt16 group1,
        efd::UInt16 group2,
        efd::Bool isEnabled);

    /**
        Method to set the collision flag between two collision groups in a scene.

        Return true if the entity has a PhysX Scene model and the groups are valid.  Otherwise,
        return false.
    */
    inline efd::Bool SetGroupCollisionFlag(
        const egf::Entity* sceneEntity,
        efd::UInt16 group1,
        efd::UInt16 group2,
        efd::Bool isEnabled);

    /// @cond EMERGENT_INTERNAL

    /// Method to allow other services to declare whether or not we are simulating.
    /// This will be used when other services are handling simulation.
    inline void SetSimulationActive(const efd::utf8string& sceneName, efd::Bool isActive);

    /**
        Returns the time to be used for calls to Simulate, FetchResults, UpdateSources, or
        UpdateDestinations.

        If the scene is not found or simulation is disabled, return kINVALID_SIMULATION_TIME.

        This method is used when other services are handling simulation.
    */
    inline efd::TimeType GetSimulationTime(const efd::utf8string& sceneName);

    /**
        Sets the last time used in simulation for the specified scene.

        This is used when other services are handling the simulation.

        Return true if the scene is found and value has been set.  Otherwise, return false
    */
    inline efd::Bool SetCurrentPhysXTime(const efd::utf8string& sceneName, efd::TimeType time);

    /// @endcond  EMERGENT_INTERNAL

protected:

    /// Destructor
    virtual ~SceneService();

    /// Return the name of the service, in this case "SceneService".
    virtual const char* GetDisplayName() const;

    /**
        Read configuration, cache service pointers and register a built-in model factory for the
        PhysXScene model.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        Creates frame events for Start and Finish Simulation.
    */
    virtual efd::AsyncResult OnInit();

    /**
        The OnTick method flushes all buffered changes to the PhysX scene.

        This service must be ticked when the simulation is not active. That is, between one tick
        of the Finish Simulation Service and before the next tick of the Start Simulation Service.
        Even then, scenes that did not complete simulation in the previous tick will not have
        buffered changes applied (the scene is still simulating, so it is illegal).
    */
    virtual efd::AsyncResult OnTick();

    /**
        Shutdown forces all scenes to complete and release.
    */
    virtual efd::AsyncResult OnShutdown();

    /// The processor affinity for creating new scenes.
    efd::ProcessorAffinity m_processorAffinity;

    /// Simulation time will be the same for all scenes as they go through the OnTick cycle
    efd::TimeType m_simulationTime;

    /// Map from names to the scene data.
    typedef efd::map<efd::utf8string, PhysXSceneData*> SceneMap;
    SceneMap m_scenes;

    /// The scenes that require updates due to changes while simulating.
    efd::list<PhysXSceneData*> m_sceneUpdates;

    /// @name Cached system services used frequently by the Scene Service.
    //@{
    efd::MessageServicePtr m_spMessageService;
    //@}

    /**
        Helper method to send the scene removing and scene removed messages
        @param sceneName The name of the scene to be removed.
        @param pData The scene data of the scene to be removed.
        @param removeFromMap determines whether or not the scene is removed from the scene map
    */
    void SendRemoveMessages(
        const efd::utf8string& sceneName,
        PhysXSceneData* pData,
        efd::Bool removeFromMap);

    /// Helper method to handle the public StartSimulation method calls.
    virtual void DoStartSimulating(
        const efd::utf8string& sceneName,
        PhysXSceneData* pSceneData,
        const efd::TimeType& time);

    bool m_runSynchronously;
};

/// A SmartPointer for the SceneService class
typedef efd::SmartPointer<SceneService> SceneServicePtr;

} // end namespace egfPhysX

#include <egfPhysX/SceneService.inl>

#endif // EE_SCENESERVICE_H
