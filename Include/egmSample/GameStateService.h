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
#ifndef EE_GAMESTATESERVICE_H
#define EE_GAMESTATESERVICE_H

#include <ecr/CoreRuntimeMessages.h>
#include <efd/ISystemService.h>

#include "egfDemoSystemServiceIDs.h"
#include "GameState.h"

// forward declarations
namespace egmSample
{
struct IFatalError;

/**
    Manages the high level state of the game.

    The game state service is responsible for managing the interaction between the
    different states of the game, such as loading, menu, playing, pause. In order
    to use it derive states from egmSample::GameState. It may also be desirable to
    derive from the GameStateService to add context data that can be shared among
    the different states. The derived class is also a good place to initialize the
    states, usually in the OnInit function, and to perform cleanup, usually in the
    OnShutdown function.
*/
class EE_EGMSAMPLE_ENTRY GameStateService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(GameStateService, efd::kCLASSID_GameStateService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:
    /**
        Constructor.

        @param dataPath Path to any texture files you will be using.  You can omit this
            if you are not using textures.
    */
    GameStateService(const efd::utf8string& dataPath = "");

    /**
        Adds a state, registered under its class ID.
        @param state New state to register.
    */
    template <class T>
    inline void AddState(T* state);

    /**
        Change to newState if the current state allows the transistion.
        @param newState GameStateID of the desired state.
    */
    efd::Bool ChangeState(egmSample::GameStateID newState);

    /**
        Lookup the class id of a state and return the state object that it corresponding.
        @param stateID GameStateID to lookup.
        @return the corresponding state pointer.
    */
    GameState* FindState(egmSample::GameStateID stateID);

    /**
        Lookup the name of a state and return the state object that it corresponding.
        @param name Name to look up.
        @return The corresponding state pointer.
    */
    GameState* FindState(const efd::utf8string& name);

    /**
        Returns the current state.
        @return The current state pointer.
    */
    inline GameState* GetState() const;

    /**
        Return the requested state, as the requested type (i.e. it's "real" type)
        @return The requested state.
    */
    template <class T>
    inline T* GetStateAs(egmSample::GameStateID stateID);

    /**
    Return the requested state, as the requested type (i.e. it's "real" type)
    @return The requested state.
    */
    template <class T>
    inline T* GetStateAs(const efd::utf8string& name);

    /**
        Turn off the main render screen and turn on the blanking render step.
        @return The blanking render step.
    */
    virtual NiRenderStep* DisableMainRender();

    /**
        Turn on the main render screen and turn off the blanking render step.
        @return The blanking render step.
    */
    virtual NiRenderStep* EnableMainRender();

    /**
        Register a fatal error from some game state. An instance of IFatalError will be
        passed and it can be used to retrieve more information. By default the message
        is deleted and the state will become invalid. The GameStateService is responsible
        for destroying the error object when it is done.
        @param error An instance of a class derived from IFatalError.
    */
    virtual void RegisterFatalError(const IFatalError* error);

    /**
        Return the game state data path (used for loading textures).
    */
    inline const efd::utf8string& GetDataPath() const;

    /**
        Change the path used for textures
    */
    inline void SetDataPath(const efd::utf8string& dataPath);

protected:
    /// Overridden virtual functions inherit base documentation and are not documented here.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();
    virtual const char* GetDisplayName() const;

    /**
        Checks to make sure we have a render surface before creating render step.
    */
    efd::Bool CheckForSurface();

    /**
        Creates a render step for blanking the screen.
    */
    void AddRenderStep();

    /**
        Removes the render step.
    */
    void RemoveRenderStep();

    typedef efd::map<egmSample::GameStateID, GameStatePtr> StatesByID;
    typedef efd::map<efd::utf8string, GameStatePtr> StatesByName;

    efd::MessageService* m_pMessageService;
    GameState* m_currentState;
    StatesByID m_statesByID;
    StatesByName m_statesByName;
    // Render step used to blank the screen when not rendering.
    NiDefaultClickRenderStep* m_pRenderStep;

    efd::utf8string m_dataPath;

    // A boolean to keep track of whether we have already initialized our states.
    efd::Bool m_bAlreadyRunning;

private:
    /**
      Adds a new state to the state service.
      @param state New GameState derived class to add.
      @param stateID ID of the new state.  Can be any unique numerical ID.
    */
    void AddState(GameStatePtr state, egmSample::GameStateID stateID);
};
typedef efd::SmartPointer<GameStateService> GameStateServicePtr;

} // end namespace egmSample

#include "GameStateService.inl"

#endif // EE_GAMESTATESERVICE_H
