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
#ifndef EE_EGMANIMATIONBINDINGS_H
#define EE_EGMANIMATIONBINDINGS_H

#include "egmAnimationLibType.h"

#include <egf/EntityID.h>

#include <NiActorManager.h>

/**
    This namespace contains the scripting layer behavior API allowing scripts to hook into
    the Gamebryo Animation System.
 */
namespace egmAnimationBindings
{
    /// Sequence ID constant that represents an invalid sequence.
    const NiActorManager::SequenceID kInvalidSequence = NiActorManager::INVALID_SEQUENCE_ID;

    /// Frequency constant used to specify that the sequence's frequency itself should be used.
    const efd::Float32 kSequenceDataFreq = NiActorManager::SEQUENCE_DATA_FREQUENCY;

    /// Sequence ID constant used for specifying that a sequence should not be synchronized.
    const efd::UInt32 kSequenceNone = NiKFMTool::SYNC_SEQUENCE_ID_NONE;

    enum TransitionState
    {
        /// Not transitioning
        NoTransition = NiActorManager::NO_TRANSITION,

        /// In a blending transition.
        Blending = NiActorManager::BLENDING,

        /// In a morphing transition.
        Morphing = NiActorManager::MORPHING,

        /// In a cross-fading transition.
        CrossFading = NiActorManager::CROSSFADING,
    };

    /// @name Actor Information
    //@{
    /**
        Returns the name for a given sequence ID in a given entity.
        @param entityID The entity to query.
        @param sequenceID The sequenceID to get a name for.
        @return The name of the sequence.  Returns NULL if not found.
    */
    EE_EGMANIMATION_ENTRY const char* GetAnimationNameFromId(
        egf::EntityID entityID,
        NiActorManager::SequenceID sequenceID);

    /**
        Returns the ID for a given sequence.
        @param entityID The entity whose actor is being queried.
        @param animName The name of the sequence.
        @return The ID for the sequence with that name.  Returns kInvalidSequence if not found.
    */
    EE_EGMANIMATION_ENTRY NiActorManager::SequenceID GetAnimationIdFromName(
        egf::EntityID entityID,
        const char* animName);

    /**
        Returns the sequence name of the entity's currently playing animation.
        @param entityID The entity to query.
        @return The name of the current animation. Returns NULL if none.
    */
    EE_EGMANIMATION_ENTRY const char* GetCurrentAnimationName(egf::EntityID entityID);

    /**
        Returns the sequence ID of the entity's currently playing animation.
        @param entityID The entity to query.
        @return ID of the current animation.  Returns kInvalidSequence if no animation is playing.
    */
    EE_EGMANIMATION_ENTRY NiActorManager::SequenceID GetCurrentAnimationId(
        egf::EntityID entityID);

    /**
        Returns the name of the sequence that the entity is currently transitioning to.
        @param entityID The entity to query.
        @return Name of the next animation.  Returns NULL if not transitioning.
    */
    EE_EGMANIMATION_ENTRY const char* GetNextAnimationName(egf::EntityID entityID);

    /**
        Returns the ID of the sequence that the entity is currently transitioning to.
        @param entityID The entity to query.
        @return ID of the next animation.  Returns kInvalidSequence is not currently transitioning.
    */
    EE_EGMANIMATION_ENTRY NiActorManager::SequenceID GetNextAnimationId(egf::EntityID entityID);

    /**
        Returns the name of the sequence that the entity will try to transition to next.
        @param entityID The entity to query.
        @return The name of the target sequence.  If none, returns NULL.
    */
    EE_EGMANIMATION_ENTRY const char* GetTargetAnimationName(egf::EntityID entityID);

    /**
        Returns the ID of the sequence that the entity will try to transition to next.
        @param entityID The entity to query.
        @return The ID of the target sequence.  If none, kInvalidSequence is returned.
    */
    EE_EGMANIMATION_ENTRY NiActorManager::SequenceID GetTargetAnimationId(egf::EntityID entityID);

    /**
        Returns the transition state for a given entity.
        @param entityID The entity to query.
        @return Current transition state.
    */
    EE_EGMANIMATION_ENTRY TransitionState GetTransitionState(egf::EntityID entityID);

    /// @name Actor Manipulation
    //@{
    /**
        Changes the target animation of an entity to a sequence (given by name.)
        @param entityID The entity to manipulate.
        @param sequenceName The name of the sequence to set as the new target.
    */
    EE_EGMANIMATION_ENTRY void SetTargetAnimationByName(
        egf::EntityID entityID,
        const char* sequenceName);

    /**
        Changes the target animation of an entity to a sequence (given by ID.)
        @param entityID The entity to manipulate.
        @param sequenceID The ID to set as the new target sequence.
    */
    EE_EGMANIMATION_ENTRY void SetTargetAnimationById(
        egf::EntityID entityID,
        NiActorManager::SequenceID sequenceID);

    /**
        Activates a layered sequence on an entity.  See NiActorManager documentation for
        more information about these arguments.

        @param entityID Actor that owns the sequence.
        @param sequenceID Sequence ID to activate.
        @param autoDeactivate Whether to deactivate the sequence when it is complete.
        @param priority Sequence priority.
        @param weight Sequence weight.
        @param easeInTime Duration to ease this sequence in.
        @param easeOutTime Duration to ease this sequence out (if auto-deactivating.)
        @param timeSyncID Sequence to synchronize with.  kInvalidSequence means no synchronization.
        @param freq Frequency to play this animation at.
        @param startFrame Frame to begin playing this animation at.
        @param additiveBlend Whether this sequence is blended additively.
        @param additiveRefFrame The base frame to generate additive deltas from.
        @return True if the sequence activated successfully.
    */
    EE_EGMANIMATION_ENTRY efd::Bool ActivateLayeredSequenceById(
        egf::EntityID entityID,
        NiActorManager::SequenceID sequenceID,
        efd::Bool autoDeactivate,
        efd::SInt32 priority = 0,
        efd::Float32 weight = 1.0f,
        efd::Float32 easeInTime = 0.0f,
        efd::Float32 easeOutTime = 0.0f,
        NiActorManager::SequenceID timeSyncID = kSequenceNone,
        efd::Float32 freq = kSequenceDataFreq,
        efd::Float32 startFrame = 0.0f,
        efd::Bool additiveBlend = false,
        efd::Float32 additiveRefFrame = 0.0f);

    /**
        Activates a layered sequence on an entity.  See NiActorManager documentation for
        more information about these arguments.

        @param entityID Actor that owns the sequence.
        @param name Sequence name to activate.
        @param autoDeactivate Whether to deactivate the sequence when it is complete.
        @param priority Sequence priority.
        @param weight Sequence weight.
        @param easeInTime Duration to ease this sequence in.
        @param easeOutTime Duration to ease this sequence out (if auto-deactivating.)
        @param timeSyncID Sequence to synchronize with.  kInvalidSequence means no synchronization.
        @param freq Frequency to play this animation at.
        @param startFrame Frame to begin playing this animation at.
        @param additiveBlend Whether this sequence is blended additively.
        @param additiveRefFrame The base frame to generate additive deltas from.
        @return True if the sequence activated successfully.
    */
    EE_EGMANIMATION_ENTRY efd::Bool ActivateLayeredSequence(
        egf::EntityID entityID,
        const char* name,
        efd::Bool autoDeactivate,
        efd::SInt32 priority = 0,
        efd::Float32 weight = 1.0f,
        efd::Float32 easeInTime = 0.0f,
        efd::Float32 easeOutTime = 0.0f,
        NiActorManager::SequenceID timeSyncID = kSequenceNone,
        efd::Float32 freq = kSequenceDataFreq,
        efd::Float32 startFrame = 0.0f,
        efd::Bool additiveBlend = false,
        efd::Float32 additiveRefFrame = 0.0f);

    /**
        Deactivates a layered sequence on an entity.

        @param entityID The actor.
        @param sequenceID Sequence ID to deactivate.
        @param easeOutTime Duration to ease the sequence out.
        @return True if the sequence was succesfully deactivated.
    */
    EE_EGMANIMATION_ENTRY efd::Bool DeactivateLayeredSequenceById(
        egf::EntityID entityID,
        NiActorManager::SequenceID sequenceID,
        efd::Float32 easeOutTime = 0.0f);

    /**
        Deactivates a layered sequence on an entity.

        @param entityID The actor.
        @param name Sequence name to deactivate.
        @param easeOutTime Duration to ease the sequence out.
        @return True if the sequence was succesfully deactivated.
    */
    EE_EGMANIMATION_ENTRY efd::Bool DeactivateLayeredSequence(
        egf::EntityID entityID,
        const char* name,
        efd::Float32 easeOutTime = 0.0f);

    /**
        Registers a text key callback behavior function.  The data stream
        elements passed to the behavior are, in order:
         - sequence ID (UInt32)
         - text key (String)
         - current time (Float32)
         - event time (Float32)

        @param entityID The actor.
        @param behaviorName The behavior to call when this text key is encountered.
        @param textKey The text key to match against (Default is all text keys.)
        @param seqName The sequence name to match text keys in (Default is all sequences.)
        @return True if the registration succeeded.
    */
    EE_EGMANIMATION_ENTRY efd::Bool ListenForTextKeyEvents(
        egf::EntityID entityID,
        const char* behaviorName,
        const char* textKey = NULL,
        const char* seqName = NULL);

    /**
        Clear all text key callbacks.

        @param entityID The actor.
        @return True if successful.
    */
    EE_EGMANIMATION_ENTRY efd::Bool ClearRegisteredTextKeys(egf::EntityID entityID);
    //@}

    /// @name Sequence Manipulation
    //@{
    /**
        Sets the frequency of an entity's sequence (given by ID.)

        @param entityID The actor.
        @param sequenceId The sequence to change.
        @param frequency The new frequency.
        @return True if set succeeded.
    */
    EE_EGMANIMATION_ENTRY efd::Bool SetSequenceFrequencyById(
        egf::EntityID entityID,
        NiActorManager::SequenceID sequenceId,
        efd::Float32 frequency);

    /**
        Gets the frequency of an entity's sequence (given by ID.)

        @param entityID The actor.
        @param sequenceId The sequence to query.
        @param frequency The queried frequency.
        @return True if get succeeded.
    */
    EE_EGMANIMATION_ENTRY efd::Bool GetSequenceFrequencyById(
        egf::EntityID entityID,
        NiActorManager::SequenceID sequenceId,
        efd::Float32& frequency);

    /**
        Sets the frequency of an entity's sequence (given by name.)

        @param entityID The Actor.
        @param sequenceName The sequence to change.
        @param frequency The new frequency.
        @return True if set succeeded.
    */
    EE_EGMANIMATION_ENTRY efd::Bool SetSequenceFrequency(
        egf::EntityID entityID,
        const char* sequenceName,
        efd::Float32 frequency);

    /**
        Gets the frequency of an entity's sequence (given by ID.)

        @param entityID The actor.
        @param sequenceName The name of the sequence to query.
        @param frequency The queried frequency.
        @return True if get succeeded.
    */
    EE_EGMANIMATION_ENTRY efd::Bool GetSequenceFrequency(
        egf::EntityID entityID,
        const char* sequenceName,
        efd::Float32& frequency);

    /**
        Gets the duration of an entity's sequence (given by ID.)

        @param entityID The actor.
        @param sequenceId The ID of the sequence to query.
        @param duration The queried duration.
        @return True if get succeeded.
    */
    EE_EGMANIMATION_ENTRY efd::Bool GetSequenceDurationById(
        egf::EntityID entityID,
        NiActorManager::SequenceID sequenceId,
        efd::Float32& duration);

    /**
        Returns the duration of an entity's sequence (given by name.)

        @param entityID The actor.
        @param sequenceName The name of the sequence to query.
        @param duration The queried duration.
        @return True if get succeeded.
    */
    EE_EGMANIMATION_ENTRY efd::Bool GetSequenceDuration(
        egf::EntityID entityID,
        const char* sequenceName,
        efd::Float32& duration);

    /**
        Sets the weight of an entity's sequence (given by ID.)

        @param entityID The actor.
        @param sequenceId The ID of the sequence to change.
        @param weight The new weight.
        @return True if set succeeded.
    */
    EE_EGMANIMATION_ENTRY efd::Bool SetSequenceWeightById(
        egf::EntityID entityID,
        NiActorManager::SequenceID sequenceId,
        efd::Float32 weight);

    /**
        Gets the weight of an entity's sequence (given by ID.)

        @param entityID The actor.
        @param sequenceId The ID of the sequence to query.
        @param weight The queried weight.
        @return True if get succeeded.
    */
    EE_EGMANIMATION_ENTRY efd::Bool GetSequenceWeightById(
        egf::EntityID entityID,
        NiActorManager::SequenceID sequenceId,
        efd::Float32& weight);

    /**
        Sets the weight of an entity's sequence (given by name.)

        @param entityID The actor.
        @param sequenceName The name of the sequence to change.
        @param weight The new weight.
        @return True if set succeeded.
    */
    EE_EGMANIMATION_ENTRY efd::Bool SetSequenceWeight(
        egf::EntityID entityID,
        const char* sequenceName,
        efd::Float32 weight);

    /**
        Gets the weight of an entity's sequence (given by name.)

        @param entityID The actor.
        @param sequenceName The name of the sequence to query.
        @param weight The queried weight.
        @return True if get succeeded.
    */
    EE_EGMANIMATION_ENTRY efd::Bool GetSequenceWeight(
        egf::EntityID entityID,
        const char* sequenceName,
        efd::Float32& weight);
    //@}

    /**
        Returns all active sequences for a given entity.

        @param entityID The actor.
        @return List of active sequence names.
    */
    EE_EGMANIMATION_ENTRY efd::list<efd::utf8string> GetActiveSequences(egf::EntityID entityID);

    /**
        Queries whether this entity's actor is paused.

        @param entityID The actor.
        @return True if this actor is paused, false if not or the entity has no actor.
    */
    EE_EGMANIMATION_ENTRY efd::Bool IsPaused(egf::EntityID entityID);

    /**
        Sets the pause state on an entity's actor.

        Does nothing if the entity has no actor.
        
        @param entityID The actor.
        @param isPaused The new pause state.
    */
    EE_EGMANIMATION_ENTRY void SetPaused(egf::EntityID entityID, efd::Bool isPaused);

} // namespace

#endif
