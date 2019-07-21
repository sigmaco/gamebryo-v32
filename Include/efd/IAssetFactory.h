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
#ifndef EE_IASSETFACTORY_H
#define EE_IASSETFACTORY_H

#include <efd/efdLibType.h>

#include <efd/Category.h>
#include <efd/IBase.h>
#include <efd/SmartPointer.h>

#include <efd/efdClassIDs.h>

namespace efd
{

// forward decl
class AssetLoadRequest;
class AssetLoadResponse;
class AssetLocatorResponse;
class AssetFactoryManager;

/*
    If you change anything in this code, please check for corresponding changes to the
    Programmer's Guide documentation for adding a new asset type.
*/

/**
    The interface from which all Asset Factories are derived. Asset factories are used with the
    egf::AssetManager service.
*/
class EE_EFD_ENTRY IAssetFactory : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(IAssetFactory, efd::kCLASSID_IAssetFactory, efd::IBase);
    /// @endcond

public:
    enum LoadStatus
    {
        /// The load has complete processing, and the response is available. The response may
        /// contain an error condition, but it is ready to send.
        LOAD_COMPLETE = 1,

        /// The load is partially complete but did enough work to preclude another loader from
        /// running in the same tick.
        LOAD_RUNNING = 2,

        /// The load is blocked on something and did no work.
        LOAD_BLOCKED = 3,
    };

    enum ThreadSafetyDescription
    {
        /// The loader may only execute in the foreground thread
        LOADER_FG_ONLY = 1,

        /// The loader may only execute in the background thread
        LOADER_BG_ONLY = 2,

        /// The loader may execute in the foreground or the background, simultaneously.
        LOADER_FG_AND_BG = 3,
    };

    /**
        The function to implement loading an asset from media.

        All derived classes must implement this function to load an asset from disk into a newly
        created AssetLoadResponse message. In typical usage, the AssetLoadResponse message is
        likely to be a derived class that includes asset-specific data handling. This function may
        be invoked in either of the threads allowed by the the GetThreadSafety() method.

        The message that is returned should be allocated using EE_NEW. Upon return the message is
        owned by the system and application level code must not delete it.

        A message should be returned even on error, with the error code in the message set
        appropriately.

        Loads are asynchronous. The return value to LoadAsset indicates that current state of the
        request. LOAD_RUNNING indicates the load is in progress and has not yet completed.
        LOAD_COMPLETE indicates the load has completed and the response is properly allocated
        and set. LOAD_FAILED indicates the load failed and the response is properly allocated
        and set.

        @param pFactoryManager The asset factory making the request. Any asset locates done by the
            loader must go through this manager.
        @param pRequest An instance of a load request. This is owned by the caller.
        @param o_spResponse reference-to-SmartPointer to the response. This is allocated by the
            loader. Ownership transfers to the caller through the smart pointer reference.
    */
    virtual LoadStatus LoadAsset(
        AssetFactoryManager* pFactoryManager,
        const AssetLoadRequest* pRequest,
        SmartPointer<AssetLoadResponse>& o_spResponse) = 0;

    /**
        Return the thread safety description for this loader.

        Any given loader may be thread safe in a variety of ways, or in no way at all.
        The implementation must return the appropriate ThreadSafetyDescription. If in doubt,
        use LOADER_FG_ONLY and the loader will only be invoked in the foreground thread.
    */
    virtual ThreadSafetyDescription GetThreadSafety() const = 0;

    /**
        The function to implement to received asset locate responses.

        A factory may need to locate other assets as it tries to create the requested asset.
        It can call AssetFactoryManager::AssetLocate function to locate these assets. The
        AssetFactoryManager will forward the AssetLocatorResponse message to this function.

        @param pResponse AssetLocatorResponse instance sent by the AssetLocatorService.
        @param targetCategory Category the response is sent to.
    */
    virtual void HandleAssetLocate(
        const efd::AssetLocatorResponse* pResponse,
        efd::Category targetCategory);

    /**
        Implement this function to receive a shutdown command in the background.

        A factory may need to clean up internal state before destruction. Implement this function
        to clean up these resources in the background thread.

        The default implementation does nothing.
    */
    virtual void Shutdown();
};

/// Type for a smart pointer to the IAssetFactory class.
typedef efd::SmartPointer<IAssetFactory> IAssetFactoryPtr;

} // end namespace efd

#include <efd/IAssetFactory.inl>

#endif // EE_IASSETFACTORY_H
