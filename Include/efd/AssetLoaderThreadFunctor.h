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
#ifndef EE_ASSETLOADERTHREADFUNCTOR_H
#define EE_ASSETLOADERTHREADFUNCTOR_H

#include <efd/efdLibType.h>
#include <efd/ThreadFunctor.h>
#include <efd/AssetFactoryManager.h>


namespace efd
{

/**
    efd::AssetLoaderThreadFunctor is the main procedure that executes in the background thread
    for asset loading.

    This thread procedure creates an efd::AssetFactoryManager instance and then loops
    calling its OnTick method. It exits when signaled to do so by some external process.

    The foreground instance of the efd::AssetFactoryManager class is responsible for creating
    and managing the thread that uses this functor. Applications should never create their own.
*/
class EE_EFD_ENTRY AssetLoaderThreadFunctor
    : public ThreadFunctor
    , public AssetFactoryManager
{

public:
    /**
        Constructor.

        The constructor takes everything needed to set up the thread.
    */
    AssetLoaderThreadFunctor(
        const size_t requestQueueSize,
        AssetFactoryManager* pForeAssetFactoryManager);

    /// Virtual destructor
    virtual ~AssetLoaderThreadFunctor();

    /// Set the functor to shut down next time it ticks.
    ///
    /// The class that created the thread should be the only thing to call this.
    inline void Shutdown();

    /// Get the background AssetFactoryManager instance.
    inline AssetFactoryManager* GetAssetFactoryManager();

protected:
    /**
        This function is called by the Thread framework to perform work.
        @param pArg The thread executing this procedure.
        @return The return value for this function is always 0.
    */
    virtual efd::UInt32 Execute(efd::Thread* pArg);

    /**
        The function that actually performs the shutdown procedure
    */
    virtual void DoShutdown();

    // When true, the service manager should be shut down on the next loop iteration.
    //
    // The shutdown procedure MUST NOT make any call that requires the foreground to tick
    // its service manager or otherwise block, because the foreground thread is blocked on
    // this thread while waiting for shutdown to complete.
    volatile bool m_shutdown;
};

}   // End namespace efd.

#include <efd/AssetLoaderThreadFunctor.inl>

#endif // EE_ASSETLOADERTHREADFUNCTOR_H
