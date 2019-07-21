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

namespace egmSample
{

//--------------------------------------------------------------------------------------------------
efd::utf8string MovementHandler::GetIdleSequence() const
{
    return m_idleSequence;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetIdleSequence(const efd::utf8string& idleSequence)
{
    m_idleSequence = idleSequence;
    m_idleSequenceID = NiActorManager::INVALID_SEQUENCE_ID;
    InitializeAnimationData();
}

//--------------------------------------------------------------------------------------------------
efd::utf8string MovementHandler::GetWalkSequence() const
{
    return m_walkSequence;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetWalkSequence(const efd::utf8string& walkSequence)
{
    m_walkSequence = walkSequence;
    m_walkSequenceID = NiActorManager::INVALID_SEQUENCE_ID;
    InitializeAnimationData();
}

//--------------------------------------------------------------------------------------------------
efd::utf8string MovementHandler::GetRunSequence() const
{
    return m_runSequence;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetRunSequence(const efd::utf8string& runSequence)
{
    m_runSequence = runSequence;
    m_runSequenceID = NiActorManager::INVALID_SEQUENCE_ID;
    InitializeAnimationData();
}

//--------------------------------------------------------------------------------------------------
efd::Float32 MovementHandler::GetWalkTopSpeed() const
{
    return m_walkTopSpeed;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetWalkTopSpeed(const efd::Float32& walkTopSpeed)
{
    m_walkTopSpeed = walkTopSpeed;
}

//--------------------------------------------------------------------------------------------------
efd::Float32 MovementHandler::GetRunTopSpeed() const
{
    return m_runTopSpeed;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetRunTopSpeed(const efd::Float32& runTopSpeed)
{
    m_runTopSpeed = runTopSpeed;
}

//--------------------------------------------------------------------------------------------------
efd::Float32 MovementHandler::GetWalkPlaybackRate() const
{
    return m_walkPlaybackRate;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetWalkPlaybackRate(const efd::Float32& walkPlaybackRate)
{
    m_walkPlaybackRate = walkPlaybackRate;
}

//--------------------------------------------------------------------------------------------------
efd::Float32 MovementHandler::GetRunPlaybackRate() const
{
    return m_runPlaybackRate;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetRunPlaybackRate(const efd::Float32& runPlaybackRate)
{
    m_runPlaybackRate = runPlaybackRate;
}

//--------------------------------------------------------------------------------------------------
efd::Point3 MovementHandler::GetInitialOrientation() const
{
    return m_initialOrientation;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetInitialOrientation(const efd::Point3& initialOrientation)
{
    m_initialOrientation = initialOrientation;
}

//--------------------------------------------------------------------------------------------------
efd::Float32 MovementHandler::GetTurnTopSpeed() const
{
    return m_turnTopSpeed;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetTurnTopSpeed(const efd::Float32& turnTopSpeed)
{
    m_turnTopSpeed = turnTopSpeed;
}

//--------------------------------------------------------------------------------------------------
efd::Float32 MovementHandler::GetCurrentSpeed() const
{
    return m_currentSpeed;
}

//--------------------------------------------------------------------------------------------------
efd::Point3 MovementHandler::GetCurrentDirection() const
{
    return m_currentDirection;
}

//--------------------------------------------------------------------------------------------------
MovementHandler::MovementType MovementHandler::GetCurrentMovementType() const
{
    return m_currentMovementType;
}

//--------------------------------------------------------------------------------------------------
efd::Point3 MovementHandler::GetTargetPoint() const
{
    return m_targetPoint;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetTargetPoint(const efd::Point3& targetPoint)
{
    m_targetPoint = targetPoint;
    m_targetMode = TargetPoint;
}

//--------------------------------------------------------------------------------------------------
efd::Point3 MovementHandler::GetTargetDirection() const
{
    return m_targetDirection;
}

//--------------------------------------------------------------------------------------------------
efd::Point3 MovementHandler::GetTargetRotation() const
{
    return ConvertDirectionToRotation(m_targetDirection + m_initialOrientation);
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetTargetRotation(
    const efd::Point3& targetRotation,
    const efd::Point3& relativeRotation)
{
    SetTargetDirection(
        ConvertRotationToDirection(targetRotation - m_initialOrientation),
        relativeRotation);
}

//--------------------------------------------------------------------------------------------------
egf::Entity* MovementHandler::GetTargetEntity() const
{
    return m_spTargetEntity;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetTargetEntity(egf::Entity* pTargetEntity)
{
    m_spTargetEntity = pTargetEntity;
    m_targetMode = TargetEntity;
}

//--------------------------------------------------------------------------------------------------
MovementHandler::MovementType MovementHandler::GetTargetMovementType() const
{
    return m_targetMovementType;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::SetTargetMovementType(MovementHandler::MovementType movementType)
{
    m_targetMovementType = movementType;
}

//--------------------------------------------------------------------------------------------------
MovementHandler::TargetMode MovementHandler::GetTargetMode()
{
    return m_targetMode;
}

//--------------------------------------------------------------------------------------------------
void MovementHandler::ClearTargetMode()
{
    m_targetMode = TargetNone;
    if (m_targetMovementType != Invalid)
        SetupTransition(Idle);
}

//--------------------------------------------------------------------------------------------------
} // end namespace egmSample
