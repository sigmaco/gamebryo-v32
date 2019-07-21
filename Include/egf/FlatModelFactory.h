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
#ifndef EE_FLATMODELFACTORY_H
#define EE_FLATMODELFACTORY_H

#include <egf/egfLibType.h>
#include <egf/egfClassIDs.h>
#include <efd/Category.h>
#include <efd/CriticalSection.h>
#include <efd/AssetFactoryManager.h>
#include <egf/FlatModelManager.h>
#include <egf/IScriptFactory.h>
#include <egf/ScriptFactoryRequest.h>

// forward decl
namespace efd
{
    class AssetLocatorResponse;
    class MessageService;
    class AssetFactoryRequest;
    class AssetFactoryResponse;
}

namespace egf
{
// forward decl
class FlatModelFactoryRequest;
class FlatModelFactoryResponse;

/**
    An IAssetFactory that takes a FlatModelFactoryRequest and attempts to load the flat model
    from disk and create a FlatModel instance. The result of this request is returned using
    an FlatModelFactoryResponse. All mix in models and behavior scripts are also added to the
    response.

    Callers to FlatModelFactory::LoadAsset are responsible for looking up and setting the
    asset path to the underlying flat model file in the FlatModelFactoryRequest.

    The FlatModelFactory is not typically called directly. Instead, it responds to a request
    from the AssetFactoryManager to load a particular asset. The AssetFactoryManager is
    responsible for locating the fully qualified path using the provided URN and setting this
    value in the FlatModelFactoryRequest object.

    For mix in models and behavior scripts, the FlatModelFactory uses the AssetFactoryManager to
    locate the underlying assets.

    The caller is responsible for allocating and deallocating the FlatModelFactoryRequest.

    The FlatModelFactory allocates the response, it is the callers responsibility to deallocate it.

    The FlatModelFactory does not add the resulting flat model(s) to the FlatModelManager or Lua
    scripts to SchedulerLua. The caller is responsible for doing so if required.

    A FlatModel load goes through several stages:
    <ol>
    <li>Load and parse the flat model file.</li>
    <li>Locate mix in flat models needed by the requested model.</li>
    <li>Identify and locate any Lua behavior scripts needed by the model or its mix in models.</li>
    <li>Request loads for all dependent flat models.</li>
    <li>Request loads for any required Lua behavior scripts.</li>
    <li>Wait for flat model loads to complete.</li>
    <li>Wait for all Lua script loads to complete.</li>
    <li>Load completed and response is ready.</li>
    </ol>

    If any mix in model fails to load, the request fails and an AssetLoadResult::ALR_ParseError is
    returned in the response message. Failure to load a Lua behavior script will not result in
    failure.

    @note The FlatModelFactory is available in the background thread only.
*/
class EE_EGF_ENTRY FlatModelFactory : public efd::BaseAssetFactory
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(FlatModelFactory, efd::kCLASSID_FlatModelFactory, efd::BaseAssetFactory);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// @name Constructors and Destructors
    //@{

    /**
        Construct a new FlatModelFactory. The FlatModelFactory needs access to the
        FlatModelManager to factory properties and lookup mix in models.
        The AssetFactoryManager is used to lookup any mix in flat models.
        The loader will load these mix in models and add them to the response.

        @param pFactoryManager The efd::AssetFactoryManager responsible for this factory.
        @param pFmm An egf::FlatModelManager reference using during FlatModel instantiation.
        @param scriptFactory Optional factory for loading dependent scripts. If present,
        the FlatModelFactory will attempt to load any related scripts using this factory.
        The resulting data is added to the FlatModelFactoryResponse message.
    */
    FlatModelFactory(
        efd::AssetFactoryManager* pFactoryManager,
        egf::FlatModelManager* pFmm,
        egf::IScriptFactory* scriptFactory = 0);

    /// Cleanup any open resources.
    ~FlatModelFactory();

    //@}

    /**
        Attempt to load a flat model file. If the factory is processing a URN and a new request
        arrives for that same URN, the factory will not attempt to load them simultaneously.
        Instead, LoadAsset returns IAssetFactory::LOAD_BLOCKED to indicate the request was
        blocked. The caller can make the same request again later.

        @see efd::IAssetFactory::LoadStatus for further details.

        @param pFactoryManager The AssetFactoryManager instance invoking this function.
        @param pRequest FlatModelFactoryRequest
        @param ppResponse FlatModelFactoryResponse message allocated by this factory.
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
        Handler for AssetLocator requests. The FlatModelFactory requests the locations for all
        mix in models. When we get a response, load the resulting flat model files and add them to
        the FlatModelFactoryResponse.

        @param response Response from the AssetFactoryManager to an AssetLocate request.
        @param targetCategory category for the response (not used).
    */
    void HandleAssetLocate(
        const efd::AssetLocatorResponse* response,
        efd::Category targetCategory);

    /// @endcond


private:
    // Give the EntityFactory and WorldFactory access to our member variables.
    friend class EntityFactory;
    friend class WorldFactory;

    // Don't let the compiler generate these. We don't provide a deep-copy function
    // so any compiler-generated versions of these functions would be incorrect.
    FlatModelFactory& operator=(const FlatModelFactory&);
    FlatModelFactory(const FlatModelFactory&);

    // Helper function to process a request we haven't seen before.
    IAssetFactory::LoadStatus ProcessNewRequest(
        efd::AssetFactoryManager* pFactoryManager,
        const efd::AssetLoadRequest* request);

    // Services needed to load flat model files.
    egf::FlatModelManagerPtr m_spFMM;

    // Script factory used to load dependent scripts.
    egf::IScriptFactoryPtr m_spScriptFactory;

    // our private category to receive asset locate response messages.
    efd::Category m_privateCategory;

    // Internal helper class to hold response data while waiting to locate assets.
    class ResponseData : public efd::IAssetResponseData
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(
            ResponseData,
            efd::kCLASSID_FlatModelFactoryData,
            efd::IAssetResponseData);
        EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT;
        /// @endcond

    public:
        // AssetFactoryManager for the original request.
        efd::AssetFactoryManager* m_pAFM;

        // Set of urn values for pending asset locator requests
        efd::set<efd::utf8string> m_pendingLocateRequests;

        // Pending script load requests, indexed by URN.
        efd::map<efd::utf8string, egf::ScriptFactoryRequestPtr> m_pendingScriptLoads;
    };
    typedef efd::SmartPointer<ResponseData> ResponseDataPtr;

    void HandleFlatModelLocate(
        const efd::AssetLocatorResponse* pResponse,
        ResponseDataPtr pendingResponse);

    void HandleScriptLocate(
        const efd::AssetLoadRequest* pRequest,
        const efd::AssetLocatorResponse* pResponse,
        ResponseDataPtr pendingResponse);

    void CheckScriptLoads(ResponseData* pPendingResponse);

    /**
        Find behaviors associated with this flat model. If this is a top level request,
        also locate and load flat models required for 'extends' and 'reverse extends' behavior
        invocations.
    */
    void FindBehaviors(
        ResponseDataPtr pendingResponseData,
        const egf::FlatModel* pFlatModel,
        bool isTopLevelRequest);
};

/// A SmartPointer for the egf::FlatModelFactory class
typedef efd::SmartPointer<egf::FlatModelFactory> FlatModelFactoryPtr;

} // end namespace egf

#endif // EE_FLATMODELFACTORY_H
