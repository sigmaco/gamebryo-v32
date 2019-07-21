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
#ifndef EE_GAMESTATEBUILTINS_H
#define EE_GAMESTATEBUILTINS_H

#include "GameStateService.h"
#include "egmSampleLibType.h"


namespace egmSample
{

// Predefined states.  You can define your own as well, but you need to either
// hardcode them into your Lua scripts or add them here and rebuild Spark.
const efd::UInt32 InvalidState   = egmSample::InvalidStateID;
const efd::UInt32 LoadingState   = egmSample::LoadingStateID;
const efd::UInt32 PlayingState   = egmSample::PlayingStateID;
const efd::UInt32 PausedState    = egmSample::PausedStateID;
const efd::UInt32 GameOverState = egmSample::GameOverStateID;
const efd::UInt32 VictoryState  = egmSample::VictoryStateID;
const efd::UInt32 DefeatState  = egmSample::DefeatStateID;

/**
    Sets the game state machine's current state by GameStateID.

    @param newState the GameStateID of the state to switch to
    @return whether the given state argument was recognized as a valid state
            and the transition was made successfully.
*/
EE_EGMSAMPLE_ENTRY efd::Bool ChangeState(efd::UInt32 newState);

/**
    Sets the game state machine's current state by name.

    @param newState the name of the state to switch to
    @return whether the given state argument was recognized as a valid state
            and the transition was made successfully.
*/
EE_EGMSAMPLE_ENTRY efd::Bool ChangeState(const efd::utf8string& newState);

/**
    Returns the current game state
*/
EE_EGMSAMPLE_ENTRY efd::UInt32 CurrentState();

/**
    Return the name of the requested state
*/
EE_EGMSAMPLE_ENTRY efd::utf8string GetStateName(efd::UInt32 id);

} // end namespace egmSample

#endif // EE_GAMESTATEBUILTINS_H
