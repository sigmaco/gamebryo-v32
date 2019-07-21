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
#ifndef EE_SCENEDATA_H
#define EE_SCENEDATA_H

#include "egfPhysXLibType.h"

#include <efd/IBase.h>
#include <efd/Point3.h>
#include <efd/ProcessorAffinity.h>
#include <efd/TimeType.h>
#include <efd/utf8string.h>

#include <egf/egfClassIDs.h>

// Subdue compiler warnings from PhysX headers.
#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4512) // assignment operator could not be generated
#pragma warning(disable: 4244) // conversion from 'type' to 'type', possible loss of data
#pragma warning(disable: 4245) // conversion from 'type' to 'type', signed/unsigned mismatch
#elif defined(EE_PLATFORM_PS3)
#pragma GCC system_header
#endif
#include <NxScene.h>
#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(pop)
#endif


namespace egfPhysX
{

/**
    The PhysXSceneData class manages all the data necessary to configure and control an
    NxScene in the Game Framework.
    
    Entites that mix in PhysXScene use this data object, and the egfPhysX::SceneService
    caches pointers to the data for all scene graphs it knows of.
*/
class PhysXSceneData : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(PhysXSceneData, efd::kCLASSID_PhysXSceneData, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

public:

    /// Constructor sets all default properties.
    PhysXSceneData();
    
    /// Virtual destructor.
    virtual ~PhysXSceneData();

    /**
        @name PhysX Scene Functions
        
        The PhysXSceneData object is responsible for managing scenes that it owns, including
        creation and destruction.
    */
    
    //@{

    /// Get the PhysX Scene object that corresponds to this scene, or NULL if there is no scene.
    inline NxScene* GetPhysXScene() const;

    /**
        Query whether this model owns its corresponding PhysX scene.
    
        The scene may be owned by an NiPhysXScene from PhysX Core Services, in which case
        this function will return false.
    */
    inline efd::Bool GetOwnScene() const;

    /**
        Set the ownership status of the PhysX scene.
    
        Only owned scenes are deleted by this model.
    */
    inline void SetOwnScene(const efd::Bool ownScene);

    /**
        Create the PhysX scene from the stored properties.
        
        Returns true if the scene was successfully created, false otherwise.
    */
    bool CreateScene(const efd::ProcessorAffinity& affinity);

    /**
        Release the PhysX scene.
        
        This function may block until simulation on the scene can be completed.
        
        Returns true if the scene was successfully removed, false if removal failed or if
        the scene is not owned.
    */
    bool ReleaseScene();

    /**
        Flush queued changes to the PhysX object.
        
        Entity property changes may come in at any time, but results can only be written
        to the PhysX scene when it is not simulating. This method pushes any pending changes
        to the scene.
    */
    void FlushPendingChanges();
    
    //@}

    /**
        @name Simulation Functions

        The PhysXSceneData object has two levels of simulation management.  When GetHandleSimulate
        returns true, the object will completely manage all scene simulation, including making
        calls to NxScene::simulate and NxScene::fetchResults. If GetHandleSimulate returns
        false, the scene service will send messages indicating when simulation is starting and
        when simulation is finishing, and when simulation has finished, but the data will not
        actually handle the simulation.  In this case, the expectation is that another service
        will manage the simulation when it receives the start and end simulation messages.

        When GetHandleSimulate returns true, the PhysXSceneData object takes complete control
        over the timing of the physics compartment when simulating. Applications should not make
        any calls to NxScene::setTiming or NxCompartment::setTiming - they will be over-ridden
        by this object.

        Some of these functions control the time step used when calling simulate for this
        scene and the time steps that PhysX uses. These functions only have an impact if
        GetHandleSimulate returns true. If active, fixed stepping uses a multiple of the given
        time step (set through SetTimestep) sufficient to get to or surpass the current tick
        time, otherwise it uses the difference between the target time and the most recent time
        (which depends on how the service is ticked). The PhysX scene is set to use the same
        stepping mechanism, fixed or variable, as this object. The time step passed to
        NxCompartment::setTiming is controlled by SetTimeStep and SetNumSubSteps. The argument
        to SetMaxNumSteps is the same as would be passed as the maxIter argument to
        NxCompartment::setTiming.

        There are functions to control whether or not simulation takes place.  When the scene
        is created, simulation is disabled and StartSimulating() must be called to enable it.
        StopSimulating() will pause the simulation indefinitely.
    */

    // @{
    /**
        Query whether this object controls simulation of its corresponding the PhysX scene.
    
        Another service may be looking for messages to start and finish simulation on the
        scene, in which case this object should not handle simulation.
    */
    inline efd::Bool GetHandleSimulation() const;

    /**
        Set the simulation control status of the PhysX scene.
    
        This model only calls simulate/fetchResults on scenes for which it handles simulation.
    */
    inline void SetHandleSimulation(const efd::Bool handleSimulation);

    /**
        Start simulation on the scene with the specified start time.

        If time is less than 0, use the Current PhysX Time.

        NOTE: No simulation will occur before this method is called. The
        ActivateOnSetFinished property, if true, will cause this function to be called when
        the entity set has finished loading.
    */
    virtual void StartSimulating(const efd::TimeType& time);

    /**
        Stop simulating.
        
        Any currently active step will complete during the next Finish Simulation tick.
    */
    virtual void StopSimulating();
    
    /// Return true when StartSimulating has been with no matching StopSimulation.
    inline bool GetSimulating() const;

    /**
        Start a simulation step.
        
        The targetTime is manipulated according to the timing values described below,
        although if forceSim is called and the internal time is in the future the time
        will be set to force a step.
        
        The simulation only starts of the handle simulation flag is true and the scene
        exists and the time is in the future (unless forced). True is returned when the step
        is started, false otherwise.
    */
    virtual bool Simulate(const efd::TimeType& targetTime, const efd::Bool forceSim);

    /**
        Fetch the simulation results.
        
        The results are only fetched if the object handles simulation for this data, we are
        actively simulating, the PhysX scene exists, the target time is greater than our most
        recent simulation target time, or the passed forced flag is true or the internal forced
        flag is true.
        
        Returns true if simulation completed, false otherwise.
    */
    virtual bool FetchResults(
        const efd::TimeType& targetTime,
        const efd::Bool forceBlockOnFetch);

    /**
        Get the status of the simulation.

        True is returned when a Simulate call has been made on the scene with no matching
        successful FetchResults. False is returned if there has been no Simulate call since
        the last successful FetchResults. In general, it is only safe to perform operations
        on the PhysX SDK when this method returns false.
    */
    inline efd::Bool GetSimActive() const;

    /**
        Set the status of the simulation.
        
        This should be called by other services or systems that handle simulation on behalf of
        this model.
    */
    inline void SetSimActive(const efd::Bool isActive);

    /// Return the last fetch time.
    inline efd::TimeType GetCurrentPhysXTime() const;

    /// Set the last fetch time, which is equivalent to setting the current simulation time.
    inline void SetCurrentPhysXTime(const efd::TimeType& time);
    
    /// Get the most recent delta time.
    inline efd::TimeType GetLastDelta() const;

    /// Get the time step.
    inline efd::Float32 GetTimeStep() const;

    /**
        Set the time step.
        
        Default is 1.0 / 30.0.
    */
    inline void SetTimeStep(const efd::Float32& timeStep);

    /// Get the maximum number of simulation sub steps the scene will use.
    inline efd::UInt32 GetMaxSubSteps() const;

    /**
        Set the maximum number of simulation sub steps the scene will use.

        Default is 8.
    */
    inline void SetMaxSubSteps(const efd::UInt32& maxSubSteps);

    /**
        Get the number of PhysX steps per Framework time step.
        
        More sub-steps increases the resolution of the PhysX simulation, with the cost of
        greater simulation time.
    */
    inline efd::UInt32 GetNumSubSteps() const;

    /**
        Set the number of PhysX steps per Framework time step.

        Default value is 1.
    */
    inline void SetNumSubSteps(const efd::UInt32& numSubSteps);

    /// Get the fixed time step flag.
    inline efd::Bool GetFixedTimeStep() const;

    /**
        Set the fixed time step flag.
        
        Default is true.
    */
    inline void SetFixedTimeStep(const efd::Bool& fixedTimeStep);

    /// Get the block on fetch flag.
    inline efd::Bool GetBlockOnFetch() const;

    /**
        Set the block on fetch flag.

        Default is false.
    */
    inline void SetBlockOnFetch(const efd::Bool& block);
    
    // @}
    
    /// Get the current gravity value.
    inline efd::Point3 GetGravity() const;

    /**
        Set the current gravity value.

        The default is 0,0,-9.8;
    */
    inline void SetGravity(const efd::Point3& gravity);

    /**
        @name PhysX Coordinate System

        A scale factor relates the size of objects in the PhysX scene to those in the
        broader simulation. PhysX operates optimally at a particular ratio of force and
        mass to size, roughly corresponding to real-world physical quantities. Applications
        that have a world coordinate system designed for some other purpose may need to
        set the scale to place PhysX within its optimal range.

        Physics size is the scale factor times world (entity property) size. For example,
        an entity that is 100 units across in the rendered world with a scale factor of 0.01
        will be 1 unit across in the PhysX simulation.
        
        The default scale factor is 1.0.
    */
    // @{

    /// Get the value of the scale factor from world to PhysX coordinates.
    inline efd::Float32 GetScaleWorldToPhysX() const;

    /**
        Set the value of the scale factor from world to PhysX coordinates.
        
        This should not be changed after the scene has been created and actors have been added.
    */
    inline void SetScaleWorldToPhysX(const efd::Float32& scaleWorldToPhysX);

    // @}

    /// Query whether or not this data belongs to an entity.
    inline efd::Bool GetEntityOwned() const;

    /// Set whether or not this data belongs to an entity.
    inline void SetEntityOwned(const efd::Bool haveEntity);

    /// Get the name of the scene.
    virtual const efd::utf8string& GetSceneName() const;

    /// Set the name of the scene.
    virtual void SetSceneName(const efd::utf8string& newName);

    inline efd::Bool GetUseHardware() const;
    inline void SetUseHardware(const efd::Bool& useHardware);

    /**
        Get the collision flag between two collision groups in a scene.

        The result of the query is placed in isEnabled.
        
        Return true if the groups are valid. Otherwise, return false.
    */
    efd::Bool GetGroupCollisionFlag(
        efd::UInt16 group1,
        efd::UInt16 group2,
        efd::Bool& isEnabled);

    /**
        Set the collision flag between two collision groups in a scene.

        Return true if the PhysX scene exists and the groups are valid.  Otherwise,
        return false.
    */
    efd::Bool SetGroupCollisionFlag(
        efd::UInt16 group1,
        efd::UInt16 group2,
        efd::Bool isEnabled);


    /// @cond EMERGENT_INTERNAL

    /// Collision group information declared public to work around compiler bugs.
    class CollisionGroupPair : public efd::MemObject
    {
    public:
        inline CollisionGroupPair(efd::UInt16 group1, efd::UInt16 group2);

        inline bool operator==(const CollisionGroupPair& rhs) const;

        // PhysX only allows group ID's 0-31
        static const efd::UInt16 ms_kInvalidGroupID;

        efd::UInt16 m_group1;
        efd::UInt16 m_group2;
    };

    /// @endcond  EMERGENT_INTERNAL

protected:
    // The PhysX scene
    NxScene* m_pScene;

    // Properties for the model, or just data for non-entity scenes.
    efd::utf8string m_sceneName;
    efd::Float32 m_scaleWorldToPhysX;
    efd::Float32 m_timeStep;
    efd::UInt32 m_maxSteps;
    efd::UInt32 m_numSubSteps;
    efd::Point3 m_gravity;
    efd::Bool m_fixedTimeStep;
    efd::Bool m_blockOnFetch;
    efd::Bool m_useHardware;
    efd::Bool m_inSimFetch;

    // Simulation and scene control
    efd::Bool m_ownScene;
    efd::Bool m_handleSimulation;
    efd::Bool m_simulate;
    efd::TimeType m_lastFetchTime;
    efd::TimeType m_nextFetchTime;

    // Collision could be properties, but is handled through script API functions.
    efd::list<CollisionGroupPair> m_disabledCollisionGroups;

    // Flags controlling updating, indicating that a value needs to be pushed to the scene.
    // For collision groups, we keep explicit track of enabled groups, and enable them first.
    // Then we process the disabled list and disable all of those. This ensures that the final
    // status at the end of each FlushPendingChanges call is accurate.
    efd::list<CollisionGroupPair> m_enabledCollisionGroups;
    efd::Bool m_groupsHaveChanged;
    efd::Bool m_gravityHasChanged;
    efd::Bool m_nameHasChanged;
    
    // Flag to indicate that this model belongs to an entity. The Scene Service uses this data
    // structure to hold non-entity scenes in some cases.
    efd::Bool m_haveEntity;
};

}; // namespace egfPhysX

#include <egfPhysX/PhysXSceneData.inl>

#endif // EE_PHYSXSCENEDATA_H
