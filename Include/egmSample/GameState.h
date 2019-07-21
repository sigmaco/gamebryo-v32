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
#ifndef EE_GAMESTATE_H
#define EE_GAMESTATE_H

#include <efd/TimeType.h>
#include <efd/IBase.h>
#include "egfDemoSystemServiceIDs.h"
#include "egmSampleLibType.h"

// forward declarations
class NiRenderStep;
namespace ecr
{
class RenderService;
}

namespace egmSample
{
// forward declarations
class GameStateService;

/// Unique identifier for a game state instance
typedef efd::UInt32 GameStateID;

/// List of common game states.  You are free to extend this list
/// with states of your own, starting at FirstUserState.
enum GameStateIDList
{
    InvalidStateID  =  0,

    LoadingStateID  =  1,
    PlayingStateID  =  2,
    PausedStateID   =  3,
    GameOverStateID =  4,
    VictoryStateID  =  5,
    DefeatStateID   =  6,

    FirstUserStateID =100
};

/// Enum describing possible actions to take upon entry to the state.
///
/// These enum values are designed to be OR'd together and passed in to the
/// GameState constructor or SetActions() call.
enum GameStateActions
{
    /// Don't do anything
    NO_ACTIONS = 0x00,

    /// Pause the scheduler when the state is entered.
    /// Do not specify both PAUSE_SCHEDULER and UNPAUSE_SCHEDULER.
    PAUSE_SCHEDULER = 0x01,

    /// Unpause the scheduler when the state is entered
    /// Do not specify both PAUSE_SCHEDULER and UNPAUSE_SCHEDULER.
    UNPAUSE_SCHEDULER = 0x02,

    /// Show the main renderer
    /// Do not specify both SHOW_MAIN_RENDERER and HIDE_MAIN_RENDERER.
    SHOW_MAIN_RENDERER = 0x04,

    /// Hide the main renderer
    /// Do not specify both SHOW_MAIN_RENDERER and HIDE_MAIN_RENDERER.
    HIDE_MAIN_RENDERER = 0x08,

    /// Display the texture billboard
    DISPLAY_TEXTURE = 0x10,

    /// Automatically timeout and go to the next state.  Most of the other actions are performed
    /// only when the state transitions to being active.  This one is a little different - it is
    /// checked each tick while the state is active.  That means if you set or unset it while the
    /// state is active, the change takes effect immediately.
    AUTO_TIMEOUT = 0x20,
};

/**
    GameState base class. To create a new game state, instantiate or derive from this class
    and add an instance of it to the GameStateService. You can extend an existing GameState
    class by deriving from it and adding it to the state service using the ID of the
    original.

    The base GameState class supports automatically timing out and proceeding to a successor
    state; displaying a static billboard in front of or instead of the main render window;
    pausing or unpausing the scheduler; hiding or unhiding the main render window.

    Note that pausing the scheduler prevents all events from firing, meaning scripts invoked
    with SendEvent will not be invoked.  Animations will also be suspended.  You can still
    invoke behaviors to process input events, but you must mark those behaviors with the
    IMMEDIATE trait and specify an immediate call type to the SparkControl builtins.
*/
class EE_EGMSAMPLE_ENTRY GameState : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(GameState, efd::kCLASSID_GameState, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    static const efd::UInt32 kInvalidGameState;

    /**
        Primary constructor.  This has a lot of parameters, but most of them are optional.
        You could also use Setxxx() functions after allocating the class, but if you want
        to allocate and pass the class in one shot it's nice to have this functionality
        on the constructor.

        @param pMasterService Pointer to the owning service; makes getting context info easier

        @param thisID Unique integer ID for this service.  Any unique ID can be used; you can use
                a .enum file to define them, use the ClassID (if you're only making one
                instance of the class), etc.

        @param stateName Human-readable name of this state.  Should not be NULL.  Must be unique.

        @param actions Specify actions to be taken when the state is entered.  Values from the
                GameStateActions enum may be OR'd together here, except where they conflict.
                Conflicts are noted in the documentation for each action.

        @param timeout Timeout in seconds.  If AUTO_TIMEOUT is set in the "actions"
                then the state will automatically transition to the next state after
                the timeout period.

        @param nextStateID ID of the state to transition to after the timeout period.  Ignored
                if there is no timeout period.  If the nextStateID is kInvalidGameState and
                the timeout attempts to transition to it, the game will exit.

        @param displayTexture Texture to display as a sign onscreen.  NULL indicates no
                texture will be displayed.  If displayed, the texture will be centered on
                the screen.  This can be used to display "Game Over", "Paused", etc.
    */
    GameState(
        GameStateService* pMasterService,
        GameStateID thisID,
        const char *stateName,
        efd::UInt32 actions=NO_ACTIONS,
        efd::Float32 timeout=10.0f,
        GameStateID nextStateID=egmSample::InvalidStateID,
        const char *displayTexture=NULL);

    /// Destructor
    virtual ~GameState() {}

    /**
        Set the actions to perform on state entry.  Setting takes effect the next time
        this state is transitioned to.

        @param actions Specify actions to be taken when the state is entered.  Values from the
                GameStateActions enum may be OR'd together here, except where they conflict.
                Conflicts are noted in the documentation for each action.
    */
    inline void SetActions(efd::UInt32 actions);

    /**
        Return the current active action set.

        @return Current actions.
    */
    inline efd::UInt32 GetActions() const;

    /**
        Set a timeout for this state.  This is the same as passing the value into the constructor.
        This setting only has effect if the AUTO_TIMEOUT action is being used; the new timeout
        interval will be checked on the next tick for this game state.

        @param timeout Timeout in seconds.  0.0 indicates no timeout.  If there is a timeout
                then the state will automatically transition to the next state after
                that time period.
    */
    inline void SetTimeout(efd::TimeType timeout);

    /**
        Get the currently set timeout for this state.

        @return Current timeout.
    */
    inline efd::TimeType GetTimeout() const;

    /**
        Set a next state to transition to.  This is the same as passing the value into the
        constructor.  Setting takes effect the next time this state is transitioned to.

        @param nextStateID ID of the state to transition to after the timeout period.  Ignored
                if there is no timeout period.  If the nextStateID is InvalidState and
                the timeout attempts to transition to it, the game will exit.
    */
    inline void SetNextStateID(GameStateID nextStateID);

    /**
        Get the current next state to transition to.

        @return ID of the next state
    */
    inline GameStateID GetNextStateID() const;

    /**
        Set a texture to be displayed onscreen during this state.  Setting takes effect the
        next time this state is transitioned to.

        @param displayTexture Texture to display as a sign onscreen.  NULL indicates no
                texture will be displayed.  If displayed, the texture will be centered on
                the screen.  This can be used to display "Game Over", "Paused", etc.
    */
    void SetDisplayTexture(const char *displayTexture);

    /**
        Get the display texture.

        @return Display texture name.
    */
    const char *GetDisplayTexture() const;

    /**
        Set a name for this state.

        @param stateName Human-readable name of this state.  Should not be NULL.
    */
    inline void SetName(const char *stateName);

    /**
        OnInit is called once on every state during the GameStateService's ISystemService::OnInit
        call.  If a GameState is added to GameStateService after GameStateService::OnInit has
        already been called than OnInit will be called immediately from within the
        GameStateService::AddState method.
    */
    virtual void OnInit();

    /**
        TransitionTo is called when the state service is transitioning from another
        state to this state.
        @param time The current simulation time.
        @param fromState The GameStateID of the previous state. May be InvalidStateID.
    */
    virtual void TransitionTo(efd::TimeType time, egmSample::GameStateID fromState);

    /**
        OnTick is called once per from by the state service.
        @param time The current simulation time.
    */
    virtual void OnTick(efd::TimeType time);

    /**
        TransitionFrom is called when this state is the current state and the state
        service needs to make a new state the current state. The state can cancel the
        transition by returning false.
        @param time The current simulation time.
        @param toState The class ID of the next state.
        @return True to allow the transition, false to prevent it.
    */
    virtual efd::Bool TransitionFrom(efd::TimeType time, egmSample::GameStateID  toState);

    /**
        OnShutdown is called once on every state during the GameStateService's
        ISystemService::OnShutdown method.  This call is the last point in time at which it is safe
        to interact with other system services.  For example, any MessageService subscriptions
        should be released during this call.
    */
    virtual void OnShutdown();

    /**
        The name of the state. This typically remains the same if one state is derived from the
        other and is designed to be used as a replacement for the original. This is the name
        that is looked up when GameStateService.ChangeState("StateName") is called.
    */
    virtual const char* Name() const;

    /**
        The ID of the game state. Each game state is responsible for defining this function to
        return a unique state ID (often the ClassID of the class, if only one instance will be
        created.) If one class derives from another and is intended to serve as a
        drop-in replacement then it should return the parent's state ID.
    */
    virtual egmSample::GameStateID GetID() const;

    /**
        This virtual function returns true if it's ok to perform a timed transition out of this
        state.  It's used by loading states; set a small but nonzero duration, like 0.01 seconds,
        then implement this function to return false until the loading is done.  The base class
        version always returns true.

        @return true if ready for automatic transition
    */
    virtual efd::Bool IsReadyForAutoTransition();

    /// Helper function to access the owning state service as a derived class.
    template <class T> inline T* Context();
    template <class T> inline T* Context() const;
    inline GameStateService* Context();
    inline GameStateService* Context() const;

protected:
    GameStateService* m_pMasterService;

    efd::UInt32 m_actions;
    GameStateID m_thisID;
    GameStateID m_nextStateID;
    const char *m_pStateName;
    const char *m_pDisplayTexture;

    ecr::RenderService* m_pRenderService;

    NiRenderStep* GetRenderStep();

    efd::Bool m_bRenderStepIsActive;

    /// System time when state was entered
    efd::TimeType m_startTime;
    /// Duration to wait before advancing to the next state when AUTO_TIMEOUT is used.
    efd::TimeType m_timeout;

    /// True if a game state previously paused the scheduler.
    static efd::Bool ms_bPaused;

};

typedef efd::SmartPointer<GameState> GameStatePtr;
}

#include "GameState.inl"


#endif // EE_GAMESTATE_H
