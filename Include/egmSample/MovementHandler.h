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
#ifndef EE_MOVEMENTHANDLER_H
#define EE_MOVEMENTHANDLER_H

#include "SamplesModelLibraryPropertyIDs.h"
#include "egfDemoSystemServiceIDs.h"
#include "egmSampleLibType.h"

#include <egf/Entity.h>
#include <egf/BuiltinModelHelper.h>
#include <NiActorManager.h>

namespace egmSample
{

class WalkableService; // Forward declaration


/**
    MovementHandler class - handles moving characters.

    This class is a built-in model that mixes in the Actor model from the StandardModelLibrary.
    The MovementHandler will move the actor according to the model's target mode.

      * TargetNone - does not move the actor
      * TargetDirection - moves the actor based on the direction provided
      * TargetPoint - moves the actor to a specified point
      * TargetEntity - moves the actor to the position of a specified entity

    The actor's idle, walking, and running animations must be specified as properties in the
    model.  In addition, there are properties for handling the animation rates of walking and
    running to allow the artist to adjust the animation speeds to match the movement speed
    provided.  The MovementHandler will automatically handle the state transitions between
    idle, walking, and running.

    The movement speed can be selected by setting the target movement type.

      * Idle - the actor will not change position even if the target is set
      * Walking - the actor will move at its walking speed as directed by the target mode
      * Running - the actor will move at its running speed as directed by the target mode
      * Invalid - the actor will not change position or rotation under any circumstance

    The MovementHandler is updated by the MovementService on every tick.  The change in
    position or rotation is based on the properties set, the scale of the actor, and the
    amount of time passed from the previous tick.

    The MovementHandler also uses the WalkableService to determine whether or not it can
    move to the targeted area.

    Note that the entity will always face in the direction that it is moving.
*/
class EE_EGMSAMPLE_ENTRY MovementHandler : public egf::IBuiltinModelImpl
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(MovementHandler, efd::kCLASSID_MovementHandler, egf::IBuiltinModelImpl);
    EE_DECLARE_CONCRETE_REFCOUNT;

    EE_DECLARE_BUILTINMODEL_PROPERTIES

    EE_BUILTINMODELPROPERTY(
        MovementHandler,
        egf::kPropertyID_SamplesModelLibrary_IdleSequence,
        efd::utf8string,
        MovementHandler,
        m_idleSequence)

    EE_BUILTINMODELPROPERTY(
        MovementHandler,
        egf::kPropertyID_SamplesModelLibrary_WalkSequence,
        efd::utf8string,
        MovementHandler,
        m_walkSequence)

    EE_BUILTINMODELPROPERTY(
        MovementHandler,
        egf::kPropertyID_SamplesModelLibrary_RunSequence,
        efd::utf8string,
        MovementHandler,
        m_runSequence)

    EE_BUILTINMODELPROPERTY(
        MovementHandler,
        egf::kPropertyID_SamplesModelLibrary_WalkTopSpeed,
        efd::Float32,
        MovementHandler,
        m_walkTopSpeed)

    EE_BUILTINMODELPROPERTY(
        MovementHandler,
        egf::kPropertyID_SamplesModelLibrary_RunTopSpeed,
        efd::Float32,
        MovementHandler,
        m_runTopSpeed)

    EE_BUILTINMODELPROPERTY(
        MovementHandler,
        egf::kPropertyID_SamplesModelLibrary_WalkPlaybackRate,
        efd::Float32,
        MovementHandler,
        m_walkPlaybackRate)

    EE_BUILTINMODELPROPERTY(
        MovementHandler,
        egf::kPropertyID_SamplesModelLibrary_RunPlaybackRate,
        efd::Float32,
        MovementHandler,
        m_runPlaybackRate)

    EE_BUILTINMODELPROPERTY(
        MovementHandler,
        egf::kPropertyID_SamplesModelLibrary_InitialOrientation,
        efd::Point3,
        MovementHandler,
        m_initialOrientation)

    EE_BUILTINMODELPROPERTY(
        MovementHandler,
        egf::kPropertyID_SamplesModelLibrary_TurnTopSpeed,
        efd::Float32,
        MovementHandler,
        m_turnTopSpeed)

    EE_END_BUILTINMODEL_PROPERTIES
    /// @endcond

public:

    /**
        @name World orientation vectors

        The MovementHandler assumes that the world up axis is in the positive Z
        direction {0,0,1} and that the world forward vector is facing the positive X
        direction {1,0,0}.

        The movement handler uses these vectors to convert between rotations and directions.
    */
    //@{
    static const efd::Point3 WORLD_UP_VECTOR;
    static const efd::Point3 WORLD_FORWARD_VECTOR;
    //@}

    /// Enum describing the available movement types.
    enum MovementType
    {
        Invalid = 100,        /// No movement type set
        Idle = 101,           /// Idling/not moving
        Walking = 102,        /// Walking
        Running = 103,        /// Running
        ExternalControl = 104 /// Actor's animations being set externally, hands off
    };

    /// Enum describing the ways to specify how the entity determines where it moves
    enum TargetMode
    {
        TargetNone = 0,      /// No target mode
        TargetDirection = 1, /// Moving in a specific direction
        TargetPoint = 2,     /// Moving to a specified point
        TargetEntity = 3     /// Moving to a specified entity
    };

    /// Constructor
    MovementHandler();

    /// Destructor
    virtual ~MovementHandler();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::Bool Initialize(egf::Entity* pOwner, const egf::PropertyDescriptorList& defaults);
    virtual void OnAdded();
    virtual void OnEndLifecycle(efd::UInt32 lifecycle);
    virtual void OnRemoved();

    /**
        Updates the entity's position and rotation based on the MovementType and TargetMode

        @param timeDelta amount of game time passed since the last update call
    */
    virtual void Update(efd::TimeType timeDelta);

    /**
        @name Built-in model properties

        The following methods are getters and setters for properties specified by the model.
        Whenever the entity gets or sets those properties, these methods are called.
    */
    // @{

    /// Returns the name of the idle sequence
    inline efd::utf8string GetIdleSequence() const;
    /// Sets the name of the idle sequence
    /// @param idleSequence the name of the new sequence
    inline void SetIdleSequence(const efd::utf8string& idleSequence);

    /// Returns the name of the walk sequence
    inline efd::utf8string GetWalkSequence() const;
    /// Sets the name of the walk sequence
    /// @param walkSequence the name of the new sequence
    inline void SetWalkSequence(const efd::utf8string& walkSequence);

    /// Returns the name of the run sequence
    inline efd::utf8string GetRunSequence() const;
    /// Sets the name of the run sequence
    /// @param runSequence the name of the new sequence
    inline void SetRunSequence(const efd::utf8string& runSequence);

    /// Returns the speed the entity moves when walking
    inline efd::Float32 GetWalkTopSpeed() const;
    /// Sets the speed of the entity's walk
    /// @param walkTopSpeed walk speed in units per second
    inline void SetWalkTopSpeed(const efd::Float32& walkTopSpeed);

    /// Returns the speed the entity moves when running
    inline efd::Float32 GetRunTopSpeed() const;
    /// Sets the speed of the entity's run
    /// @param runTopSpeed run speed in units per second
    inline void SetRunTopSpeed(const efd::Float32& runTopSpeed);

    /// Returns the frequency for the walk animation sequence
    inline efd::Float32 GetWalkPlaybackRate() const;
    /// Sets the frequency of the walk animation sequence
    /// @param walkPlaybackRate the frequency for walk animation sequence
    inline void SetWalkPlaybackRate(const efd::Float32& walkPlaybackRate);

    /// Returns the frequency for the run animation sequence
    inline efd::Float32 GetRunPlaybackRate() const;
    /// Sets the frequency of the run animation sequence
    /// @param runPlaybackRate the frequency for run animation sequence
    inline void SetRunPlaybackRate(const efd::Float32& runPlaybackRate);

    /// Returns the rotation, in degrees, needed to make the entity face the
    /// WORLD_FORWARD_VECTOR with up being the WORLD_UP_VECTOR
    inline efd::Point3 GetInitialOrientation() const;
    /// Sets the rotation, in degrees, needed to make have the entity face the
    /// WORLD_FORWARD_VECTOR with up being the WORLD_UP_VECTOR
    /// @param initialOrientation orientation as a Euler angle measured in degrees
    inline void SetInitialOrientation(const efd::Point3& initialOrientation);

    /// Returns the maximum change in rotation measured in degrees per second
    inline efd::Float32 GetTurnTopSpeed() const;
    /// Sets the maximum change in rotation measured in degrees per second
    /// @param turnTopSpeed change in rotation in degrees per second
    inline void SetTurnTopSpeed(const efd::Float32& turnTopSpeed);
    /// @}

    /**
        @name Built-in behavior properties

        The following methods are made available to script via built-in behaviors
    */
    // @{

    /// Returns the speed, in units per second, that the entity is moving
    inline efd::Float32 GetCurrentSpeed() const;
    /// Returns the direction that the entity is facing
    inline efd::Point3 GetCurrentDirection() const;
    /// Returns the MovementType that the entity is using when moving
    inline MovementType GetCurrentMovementType() const;

    /// Returns the point towards which the entity is moving
    inline efd::Point3 GetTargetPoint() const;

    /**
        Sets the point to which the entity should go.  Note that the entity will hit the
        target point before stopping so it will likely not be exactly on that point by the
        time it stops.  This sets the target mode to TargetPoint.

        @param targetPoint point to which the entity will go
    */
    inline void SetTargetPoint(const efd::Point3& targetPoint);

    /// Returns the direction that the entity is moving
    inline efd::Point3 GetTargetDirection() const;

    /**
        Sets the direction that the entity will move.  The movement direction will be based
        on the relative rotation provided.  If the relative rotation is efd::Point3::ZERO,
        then the direction will be based on WORLD_UP_VECTOR and WORLD_FORWARD_VECTOR.  This
        sets the target mode to TargetDirection.

        @param targetDirection direction to make the entity move
        @param relativeRotation the rotation to use to establish targetDirection's origin
    */
    void SetTargetDirection(
        const efd::Point3& targetDirection,
        const efd::Point3& relativeRotation);

    /// Returns the rotation of the entity when it moves forward
    inline efd::Point3 GetTargetRotation() const;

    /**
        Sets the facing rotation of the entity.  The facing rotation will be based
        on the relative rotation provided.  This sets the target mode to TargetDirection.

        @param targetRotation facing rotation for the entity to move
        @param relativeRotation the rotation to use to establish targetRotation's origin
    */
    inline void SetTargetRotation(
        const efd::Point3& targetRotation,
        const efd::Point3& relativeRotation);

    /// Returns the entity the MovementHandler entity is following
    inline egf::Entity* GetTargetEntity() const;

    /// Sets the entity for the MovementHandler entity to follow.  This sets the target
    /// mode to TargetEntity.
    /// @param pTargetEntity entity to follow.
    inline void SetTargetEntity(egf::Entity* pTargetEntity);

    /// Returns the MovementType that the entity should use when moving
    inline MovementType GetTargetMovementType() const;

    /// Sets the MovementType that the entity should use when moving
    /// @param movementType movement type to use for the entity's movement
    inline void SetTargetMovementType(MovementType movementType);

    /// Returns the targeting mode used by the entity
    inline TargetMode GetTargetMode();

    /// Clears all targeting information and sets the TargetMode to None.  The
    /// entity will not move after the target mode is cleared and it comes to a stop.
    /// It will only move again if a new target mode is set.
    inline void ClearTargetMode();
    /// @}

    /**
        Gets all the animation data needed for the MovementHandler to function.  This
        includes getting the actor manager and sequence IDs for the named sequences.

        @return Returns true if the animation data is successfully initialized, false otherwise.
    */
    efd::Bool InitializeAnimationData();

    /**
        Resets all the animation data used by the MovementHandler.  This is usually used when
        the actor is removed from the scene.  InitializeAnimationData() will need to be called
        for the MovementHandler to work properly.
    */
    void ResetAnimationData();

    static egf::IBuiltinModel* Factory();

protected:

    // Model properties
    efd::utf8string m_idleSequence;
    efd::utf8string m_walkSequence;
    efd::utf8string m_runSequence;
    efd::Float32 m_walkTopSpeed;
    efd::Float32 m_runTopSpeed;
    efd::Float32 m_walkPlaybackRate;
    efd::Float32 m_runPlaybackRate;
    efd::Point3 m_initialOrientation;
    efd::Float32 m_turnTopSpeed;

    // Sequence IDs corresponding to the sequence names
    NiActorManager::SequenceID m_idleSequenceID;
    NiActorManager::SequenceID m_walkSequenceID;
    NiActorManager::SequenceID m_runSequenceID;

    // Current state properties
    efd::Point3 m_currentDirection;
    efd::Float32 m_currentSpeed;
    MovementType m_currentMovementType;

    // Target properties
    efd::Point3 m_targetPoint;
    efd::Point3 m_targetDirection;
    egf::EntityPtr m_spTargetEntity;
    MovementType m_targetMovementType;
    TargetMode m_targetMode;

    // Transition properties
    efd::Bool m_transition;
    efd::Float32 m_transitionTime;
    efd::Float32 m_totalTransitionTime;
    MovementType m_transitionMovementType;

    NiActorManagerPtr m_spActorManager;
    const efd::ServiceManager* m_pServiceManager;
    WalkableService* m_pWalkableService;

    /// Helper method used to compute the new facing direction of the entity.
    efd::Point3 ComputeNewDirection(efd::TimeType timeDelta);

    /// Helper method used to convert a rotation to a direction.
    /// @param rotation Euler angle in degrees
    /// @returns facing direction
    efd::Point3 ConvertRotationToDirection(efd::Point3 rotation) const;

    /// Helper method used to convert a direction to a rotation.
    /// @param direction direction the entity is facing
    /// @returns entity's rotation for that direction as an Euler angle in degrees
    efd::Point3 ConvertDirectionToRotation(efd::Point3 direction) const;

    /// Helper function to setup the transition animations to change the movement type
    /// @param type the movement type of the entity at the end of the transition.
    void SetupTransition(MovementType type);
};

typedef efd::SmartPointer<MovementHandler> MovementHandlerPtr;

} // end namespace egmSample

#include "MovementHandler.inl"

#endif // EE_MOVEMENTHANDLER_H
