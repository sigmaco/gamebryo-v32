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
#ifndef EE_MOVEMENTBINDINGS_H
#define EE_MOVEMENTBINDINGS_H

#include "MovementHandler.h"
#include "egmSampleLibType.h"

namespace egmSample
{

/**
    Enum describing the available movement types.  Movement types are used to allow
    the movement speed to be set.

    * Idle - the actor will not change position even if the target is set
    * Walking - the actor will move at its walking speed as directed by the target mode
    * Running - the actor will move at its running speed as directed by the target mode
    * Invalid - the actor will not change position or rotation under any circumstance

*/
enum MovementType
{
    Idle = egmSample::MovementHandler::Idle,
    Walking = egmSample::MovementHandler::Walking,
    Running = egmSample::MovementHandler::Running,
    Invalid = egmSample::MovementHandler::Invalid,
    ExternalControl = egmSample::MovementHandler::ExternalControl
};

/**
    Enum describing the ways to specify how the entity determines where it moves.
    The MovementHandler will move the actor according to the model's target mode.

    * TargetNone - does not move the actor
    * TargetDirection - moves the actor based on the direction provided
    * TargetPoint - moves the actor to a specified point
    * TargetEntity - moves the actor to the position of a specified entity
 */
enum TargetMode
{
    TargetNone = egmSample::MovementHandler::TargetNone,
    TargetDirection = egmSample::MovementHandler::TargetDirection,
    TargetPoint = egmSample::MovementHandler::TargetPoint,
    TargetEntity = egmSample::MovementHandler::TargetEntity
};

/// Returns the speed, in units per second, that the specified entity is moving
/// @param entityID ID of the entity
EE_EGMSAMPLE_ENTRY efd::Float32 GetCurrentSpeed(egf::EntityID entityID);

/// Returns the direction that the specified entity is facing
/// @param entityID ID of the entity
EE_EGMSAMPLE_ENTRY efd::Point3 GetCurrentDirection(egf::EntityID entityID);

/// Returns the MovementType that the specified entity is using when moving
/// @param entityID ID of the entity
EE_EGMSAMPLE_ENTRY MovementType GetCurrentMovementType(egf::EntityID entityID);

/// Returns the point towards which the specified entity is moving
/// @param entityID ID of the entity
EE_EGMSAMPLE_ENTRY efd::Point3 GetTargetPoint(egf::EntityID entityID);

/**
    Sets the point to which the specified entity should go.  Note that the entity will hit the
    target point before stopping so it will likely not be exactly on that point by the
    time it stops.  This sets the target mode to TargetPoint.

    @param entityID ID of the entity
    @param targetPoint point to which the entity will go
*/
EE_EGMSAMPLE_ENTRY efd::Bool SetTargetPoint(egf::EntityID entityID, efd::Point3 targetPoint);

/// Returns the direction that the specified entity is moving
/// @param entityID ID of the entity
EE_EGMSAMPLE_ENTRY efd::Point3 GetTargetDirection(egf::EntityID entityID);

/**
    Sets the direction that the specified entity will move.  The movement direction will be
    based on the relative rotation provided.  If the relative rotation is efd::Point3::ZERO,
    then the direction will be based on WORLD_UP_VECTOR and WORLD_FORWARD_VECTOR.  This
    sets the target mode to TargetDirection.

    @param entityID ID of the entity
    @param targetDirection direction to make the entity move
    @param relativeRotation the rotation to use to establish targetDirection's origin
*/
EE_EGMSAMPLE_ENTRY efd::Bool SetTargetDirection(
    egf::EntityID entityID,
    efd::Point3 targetDirection,
    efd::Point3 relativeRotation = efd::Point3::ZERO);

/// Returns the rotation of the specified entity when it moves forward
/// @param entityID ID of the entity
EE_EGMSAMPLE_ENTRY efd::Point3 GetTargetRotation(egf::EntityID entityID);

/**
 Sets the facing rotation of the specified entity.  The facing rotation will be based
 on the relative rotation provided.  This sets the target mode to TargetDirection.

 @param entityID ID of the entity
 @param targetRotation facing rotation for the entity to move
 @param relativeRotation the rotation to use to establish targetRotation's origin
 */
EE_EGMSAMPLE_ENTRY efd::Bool SetTargetRotation(
    egf::EntityID entityID,
    efd::Point3 targetRotation,
    efd::Point3 relativeRotation = efd::Point3::ZERO);

/// Returns the entity ID of the entity that the specified entity is following
/// @param entityID ID of the entity following the target entity
EE_EGMSAMPLE_ENTRY egf::EntityID GetTargetEntityID(egf::EntityID entityID);

/**
 Sets the entity ID for the specified entity to follow.  This sets the target
 mode to TargetEntity.
 @param entityID ID of the entity that will be following the target entity
 @param targetEntityID ID of the entity to follow.
 */
EE_EGMSAMPLE_ENTRY efd::Bool SetTargetEntityID(egf::EntityID entityID, egf::EntityID targetEntityID);

/// Returns the MovementType that the specified entity should use when moving
/// @param entityID ID of the entity
EE_EGMSAMPLE_ENTRY MovementType GetTargetMovementType(egf::EntityID entityID);

/// Sets the MovementType that the entity specified should use when moving
/// @param entityID ID of the entity
/// @param movementType movement type to use for the entity's movement
EE_EGMSAMPLE_ENTRY efd::Bool SetTargetMovementType(egf::EntityID entityID, MovementType state);

/// Returns the targeting mode used by the specified entity
/// @param entityID ID of the entity
EE_EGMSAMPLE_ENTRY TargetMode GetTargetMode(egf::EntityID entityID);

/**
    Clears all targeting information and sets the TargetMode to None for the specified entity.
    The entity will not move after the target mode is cleared and it comes to a stop.
    It will only move again if a new target mode is set.
    @param entityID ID of the entity
*/
EE_EGMSAMPLE_ENTRY void ClearTargetMode(egf::EntityID entityID);

} // end namespace egmSample

#endif // EE_MOVEMENTBINDINGS_H
