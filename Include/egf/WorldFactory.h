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
#ifndef EE_WORLDFACTORY_H
#define EE_WORLDFACTORY_H

#include <efd/BaseAssetFactory.h>
#include <egf/egfClassIDs.h>
#include <efd/CriticalSection.h>
#include <egf/FlatModelFactoryRequest.h>
#include <efd/Category.h>
#include <egf/WorldFactoryResponse.h>
#include <egf/egfLibType.h>
#include <efd/AssetFactoryManager.h>
#include <egf/FlatModelFactory.h>
#include <efd/MessageService.h>

// forward declarations
namespace efd
{
class AssetLoadRequest;
class AssetLoadResponse;
class AssetLocatorResponse;
}

namespace egf
{
// forward declarations
class WorldFactoryRequest;
class FlatModelFactoryResponse;

/**
    An IAssetFactory that takes a WorldFactoryRequest and attempts to load the xblock file
    from disk, locates all the flat models needed for this world, and instantiates each flat model.
    The result of this request is returned using a WorldFactoryResponse. All mix in models are
    also added to the response. If Lua scripting is available the WorldFactory will also include
    all required behavior scripts in the response message.

    Callers to WorldFactory::LoadAsset are responsible for looking up and setting the
    asset path to the underlying flat model file in the WorldFactoryRequest.

    The WorldFactory is not typically called directly. Instead, it responds to a request from
    the AssetFactoryManager to load a particular asset. The AssetFactoryManager is responsible
    for locating the fully qualified path using the provided URN and setting this value in
    the WorldFactoryRequest object.

    The caller is responsible for allocating and deallocating the WorldFactoryRequest.

    The WorldFactory allocates the response, it is the callers responsibility to deallocate it.

    The WorldFactory does not add the resulting FlatModel instances to the FlatModelManager.
    The caller is responsible for doing so if required.

    A World load goes through several stages:
    <ol>
    <li>Load and parse the block file.</li>
    <li>Locate dependent flat models.</li>
    <li>Request loads for all dependent flat models.</li>
    <li>Wait for flat model factories to complete.</li>
    <li>Load completed and response is ready.</li>
    </ol>

    Failure to load a flat model specified in the block file results in a failure, which is
    indicated in the WorldFactoryResponse message sent back to the requester.

    @note The WorldFactory is available in the background thread only.
 */
class EE_EGF_ENTRY WorldFactory : public efd::BaseAssetFactory
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(WorldFactory, efd::kCLASSID_WorldFactory, efd::BaseAssetFactory);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    ///{ @name Construction and Destruction

    /**
        Construct a new WorldFactory. The WorldFactory uses an egf::FlatModelLoader to load
        required flat models.

        @param pFactoryManager efd::AssetFactoryManager responsible for this factory.
        @param pFmLoader FlatModelFactory used to load flat model files.
    */
    WorldFactory(efd::AssetFactoryManager* pFactoryManager, egf::FlatModelFactory* pFmLoader);

    /**
        Cleanup any open resources.
    */
    ~WorldFactory();

    //@}

    /**
        Attempt to load a block file. If the factory is processing a URN and a new request
        arrives for that same URN, the factory will not attempt to load them simultaneously.
        Instead, LoadAsset returns IAssetFactory::LOAD_BLOCKED to indicate the request was
        blocked. The caller can make the same request again later.

        @see efd::IAssetFactory::LoadStatus for further details.

        @param pFactoryManager The AssetFactoryManager instance invoking this function.
        @param pRequest WorldFactoryRequest instance.
        @param ppResponse WorldFactoryResponse allocated by this factory.
        @return IAssetFactory::LoadStatus status of this load request.
    */
    IAssetFactory::LoadStatus LoadAsset(
        efd::AssetFactoryManager* pFactoryManager,
        const efd::AssetLoadRequest* pRequest,
        efd::AssetLoadResponsePtr& ppResponse);

    /// Thread status description.
    ///
    /// This loader is thread safe for foreground or background use.
    IAssetFactory::ThreadSafetyDescription GetThreadSafety() const;

    /// Shutdown function cleans up message subscriptions and smart pointers
    virtual void Shutdown();

    /// @cond EMERGENT_INTERNAL

    /**
        Handler for AssetLocator responses in the background thread.

        The WorldFactory requests the locations for all flat models needed by the world.
        When we get a response, load the resulting flat models and add them to the
        WorldFactoryResponse.

        @param response Response from the AssetFactoryManager to an AssetLocate request.
        @param targetCategory category sent to the AssetLocatorService. Not Used.
    */
    virtual void HandleAssetLocate(
        const efd::AssetLocatorResponse* pResponse,
        efd::Category targetCategory);

    /// @endcond

private:
    /// Don't let the compiler generate these. We don't provide a deep-copy function
    /// so any compiler-generated versions of these functions would be incorrect.
    //@{
    WorldFactory& operator=(const WorldFactory&);
    WorldFactory(const WorldFactory&);
    //@}

    // forward declaration
    class WorldFactoryData;

    /// helper function to load a world from disk.
    IAssetFactory::LoadStatus LoadWorld(
        efd::AssetFactoryManager* pFactoryManager,
        const egf::WorldFactoryRequest* pCurrentRequest,
        efd::AssetLoadResponsePtr& ppResponse);

    /// Helper function to request loading all FlatModel files associated with the World.
    efd::IAssetFactory::LoadStatus LoadFlatModels(
        efd::AssetFactoryManager* pFactoryManager,
        WorldFactoryData* pResponseData,
        bool isBackground,
        bool isPreemptive,
        bool isReload);

    /// Helper function to load an individual FlatModel file.
    efd::IAssetFactory::LoadStatus LoadFlatModel(
        efd::AssetFactoryManager* pFactoryManager,
        WorldFactoryData* pResponseData,
        egf::FlatModelFactoryRequest* pFlatModelRequest,
        egf::FlatModelFactoryResponsePtr& pFlatModelResponse);

    /// Check the status of pending flat model loads
    IAssetFactory::LoadStatus CheckFlatModelLoads(
        efd::AssetFactoryManager* pFactoryManager,
        WorldFactoryData* pResponseData);

    /// Classes needed to load flat model files.
    egf::FlatModelFactoryPtr m_spFMLoader;

    /// our private category used to respond to lookup requests.
    efd::Category m_privateCategory;

    /// mapping of Model name to fully qualified path.
    typedef efd::map<efd::utf8string, efd::utf8string> LocatedFlatModelMap;

    /// mapping of Model name to flat model load request.
    typedef efd::map<efd::utf8string, egf::FlatModelFactoryRequestPtr> FlatModelRequestMap;

    /// Pending factory response data. The world load goes through several stages;
    /// this structure is used to track this data during the load life time.
    class WorldFactoryData : public efd::IAssetResponseData
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(
            WorldFactoryData,
            efd::kCLASSID_WorldFactoryData,
            efd::IAssetResponseData);

        EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT;
        /// @endcond

    public:
        WorldFactoryData();

        enum State
        {
            LOAD_WORLD_FILE,
            LOCATE_FLAT_MODELS,
            LOAD_FLAT_MODELS,
            WAIT_FOR_FLAT_MODEL_LOADS,
            COMPLETE
        };

        // Current state of the world load.
        State m_state;

        // Map of urn values to asset names for pending asset locator requests
        efd::map<efd::utf8string, efd::utf8string> m_pendingLocateRequests;

        // The fully qualified path to located flat models, indexed by model name.
        LocatedFlatModelMap m_locatedFlatModels;

        FlatModelRequestMap m_pendingFlatModelLoads;
    };
    typedef efd::SmartPointer<WorldFactoryData> WorldFactoryResponseDataPtr;
};

/// A SmartPointer for the egf::WorldFactory class
typedef efd::SmartPointer<egf::WorldFactory> WorldFactoryPtr;

} // end namespace egf

#endif // EE_WORLDFACTORY_H
