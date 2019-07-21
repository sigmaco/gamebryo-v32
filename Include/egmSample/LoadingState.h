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
#ifndef EE_LOADINGSTATE_H
#define EE_LOADINGSTATE_H

#include <efd/IBase.h>
#include <efd/utf8string.h>
#include <ecr/CoreRuntimeMessages.h>
#include <egf/EntityLoaderService.h>

#include "LogoSplash.h"
#include "GameState.h"
#include "IFatalError.h"
#include "egmSampleLibType.h"

class NiDefaultClickRenderStep;
class NiViewRenderClick;

namespace egmSample
{

/// A GameState for loading entity block files.  Can display logo splash screens until the block
/// loading has completed.
class EE_EGMSAMPLE_ENTRY LoadingState : public GameState
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(LoadingState, efd::kCLASSID_LoadingState, GameState);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// Error information about problems that occurred while loading.
    class Error : public IFatalError
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(Error, efd::kCLASSID_LoadingState_Error, IFatalError);
        EE_DECLARE_CONCRETE_REFCOUNT;
        /// @endcond

    public:
        Error(const efd::utf8string& message);

        // Overridden virtual functions inherit base documentation and thus are not
        // documented here.
        virtual const efd::utf8string& GetMessage() const;

        efd::utf8string m_blockFile;

    private:
        efd::utf8string m_message;
    };

    LoadingState(GameStateService* pMasterService, egmSample::GameStateID nextState);
    ~LoadingState();

    /// Overridden virtual functions inherit base documentation and are not documented here.
    virtual void TransitionTo(efd::TimeType time, efd::UInt32 fromState);
    virtual efd::Bool TransitionFrom(efd::TimeType time, efd::UInt32 toState);
    virtual void OnTick(efd::TimeType time);
    virtual efd::Bool IsReadyForAutoTransition();
    virtual void OnShutdown();

    /**
        Attempt to skip remaining splash screens
    */
    void SkipRemaining();

    /**
        Adds a splash screen instance to the loading state.
        @param splash Splash screen to display.
    */
    void AddSplash(LogoSplashPtr splash);

    /**
        Queues a block file for loading.
        @param blockFile Name of block file to load.
        @param critical
    */
    void QueueBlockFile(const efd::AssetID& blockFile, efd::Bool critical);

    /**
        @return True if this is the first time the LoadingState has been active.
    */
    inline efd::Bool IsInitialTime() const;

    /**
        Message callback when block is finished loading.
        @param pWorldMessage Message being received from world message
        @param targetChannel Channel message was sent to.
    */
    virtual void HandleWorldLoadedMessage(
        const egf::EntityLoadResult* pWorldMessage,
        efd::Category targetChannel);

protected:
    /// Data structure for holding meta data about block load requests
    struct Loader
    {
        efd::AssetID m_blockFile;
        /// If true and the file fails to load then the whole load process fails.
        efd::Bool m_critical;
        /// Set true when the file has been sent to the entity loader.
        efd::Bool m_queued;
    };

    typedef efd::list<LogoSplashPtr> SplashScreens;
    typedef efd::list<Loader> BlockFiles;

    efd::Bool m_skipping;     ///< the user has asked to skip remaining splash screens.
    efd::Bool m_initialTime;  ///< this is the first time that this state has been active.
    LogoSplashPtr m_pCurrentSplash;         ///< Current splash screens
    LogoSplashPtr m_pLastSplash;            ///< Last splash screen to be displayed,
                                            ///< held until current one is ready.
    SplashScreens m_splashScreens;          ///< all splash screens that are not current.
    NiDefaultClickRenderStep* m_pRenderStep; ///< The render step owned by the state machine.
    NiViewRenderClickPtr m_spSplashClick;
    BlockFiles m_blockFiles;                ///< all block files to be loaded.

    /// Category on which I request Block Load callback messages
    efd::Category m_myCallbackCat;

    /**
      Tests to see if all loading is done so that it can proceed to the next state.
      @returns True if loading is completed.
    */
    virtual efd::Bool LoadingIsDone() const;

    // find the next available splash screen.
    LogoSplashPtr GetNextSplash();

    // Ask the entity loader to load the given block file.
    void LoadBlockFile(Loader& blockFile);

    /// Initialize ourselves
    void Init();

    /// Do cleanup work
    void Cleanup();
};

} // end namespace egmSample

#include "LoadingState.inl"

#endif // EE_LOADINGSTATE_H
