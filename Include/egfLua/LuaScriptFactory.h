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
#ifndef EE_LUASCRIPTFACTORY_H
#define EE_LUASCRIPTFACTORY_H

#include <efd/AssetLoadResponse.h>
#include <egf/IScriptFactory.h>
#include <egf/egfClassIDs.h>
#include <egfLua/egfLuaLibType.h>

// forward declaration
namespace efd
{
    class AssetFactoryManager;
    class AssetLoadRequest;
    class AssetLocatorResponse;
}

namespace egf
{
// forward declaration
class ScriptFactoryRequest;
class ScriptFactoryResponse;

/**
    A factory for Lua behavior script files. The LuaScriptFactory loads a Lua script from disk,
    calculates dependencies, and then loads the script file content and its dependencies into
    memory. Script load requests are made using a ScriptFactoryRequest message. The resulting
    file content is returned using a ScriptFactoryResponse message.

    The LuaScriptFactory loads dependent script data based on the 'require' and 'dofile'
    keywords. It performs a depth-first search of these dependencies to ensure scripts are
    loaded in the correct order: from least dependent to most dependent.

    Callers to LuaScriptFactory::LoadAsset are responsible for looking up and setting the
    asset path to the underlying Lua script file in the ScriptFactoryRequest.

    The LuaScriptFactory is not typically called directly. Instead, it responds to a request from
    the AssetFactoryManager to load a particular asset. The AssetFactoryManager is responsible
    for locating the fully qualified path using the provided URN and setting this value in
    the ScriptFactoryRequest object.

    The caller is responsible for allocating and deallocating the ScriptFactoryRequest.

    The LuaScriptFactory allocates the response, it is the callers responsibility to
    deallocate it.

    The LuaScriptFactory does not add the resulting Lua script files to the
    Lua runtime system. The caller is responsible for doing so if required.

    A Lua script load goes through several stages:
    <ol>
    <li>Load the Lua script file.</li>
    <li>Calculate dependencies for the current script.</li>
    <li>Locates these dependencies.</li>
    <li>For each dependency, calculate its dependencies and load them.</li>
    <li>Once all dependencies are loaded, the load is complete and response is ready.</li>
    </ol>

    Failure to load a dependent module file results in an elr_PartialSuccess result status.
    A module can fail to load for several reasons that may not be fatal. For example, the module
    is loaded from a shared library, the module is statically bound at initialization,
    the module was pre-loaded from a static memory buffer, etc. The LuaScriptFactory
    does not have access to the main thread Lua runtime to check for these conditions.

    @note The WorldFactory is available in the background thread only.
*/
class EE_EGF_LUA_ENTRY LuaScriptFactory : public egf::IScriptFactory
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(LuaScriptFactory, efd::kCLASSID_LuaScriptFactory, egf::IScriptFactory);
    EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT;
    /// @endcond

public:

    /// @name Construction and Destruction
    //@{

    /**
        Construct a new LuaScriptFactory.

        @param pFactoryManager The factory manager associated with this factory. Used to locate
            dependent scripts.
    */
    LuaScriptFactory(efd::AssetFactoryManager* pFactoryManager);

    /// Destructor
    ~LuaScriptFactory();

    //@}

    /// @name IAssetFactory interface
    //@{

    /**
        Load a Lua script and any dependent scripts.

        @param manager AssetFactoryManager that owns this factory.
        @param pRequest The request message for this factory.
        @param pResponse The response to this load request, allocated by this factory.
        @return IAssetFactory::LoadStatus the status of this load request.
    */
    efd::IAssetFactory::LoadStatus LoadAsset(
        efd::AssetFactoryManager * manager,
        const efd::AssetLoadRequest* pRequest,
        efd::AssetLoadResponsePtr& pResponse);

    /// Cleanup open resources
    void Shutdown();

    /// Return the thread safety description for this loader.
    efd::IAssetFactory::ThreadSafetyDescription GetThreadSafety() const;

    //@}

    /// @name IScriptFactory interface
    //@{

    egf::BehaviorTypes GetScriptType() const;

    //@}


    /// @cond EMERGENT_INTERNAL

    /**
        Handler for AssetLocator responses. The LuaScriptFactory requests the locations for all
        scripts needed by the requested script. When we get a response, load the resulting scripts
        and add them to the ScriptFactoryResponse.

        @param response Response from the AssetFactoryManager to an AssetLocate request.
        @param targetCategory category sent to the AssetLocatorService. Not Used.
    */
    virtual void HandleAssetLocate(
        const efd::AssetLocatorResponse* pResponse,
        efd::Category targetCategory);

    /// @endcond

private:
    // Don't let the compiler generate these. We don't provide a deep-copy function
    // so any compiler-generated versions of these functions would be incorrect.
    LuaScriptFactory& operator=(const LuaScriptFactory&);
    LuaScriptFactory(const LuaScriptFactory&);

    // script name and URL.
    struct ScriptInfo
    {
        efd::utf8string m_name;
        efd::utf8string m_url;
        efd::utf8string m_data;
    };

    typedef efd::list<efd::utf8string> URNList;
    typedef efd::list<ScriptInfo> ScriptInfoList;

    // Pending factory response data. The script load goes through several stages;
    // this structure is used to track this data during the load life time.
    class LuaScriptFactoryResponseData : public efd::IAssetResponseData
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(
            LuaScriptFactoryResponseData,
            efd::kCLASSID_LuaScriptFactoryData,
            efd::IAssetResponseData)
        EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT;
        /// @endcond

    public:
        enum State
        {
            LOAD_NOT_STARTED,
            LOCATE_DEPENDENT_SCRIPTS,
            SCRIPTS_LOADED,
            COMPLETE
        };

        // constructor
        LuaScriptFactoryResponseData();

        // Current state of the script load.
        State m_state;

        // Script file asset locates that need to be sent.
        URNList m_locatesToSend;

        // Pending Lua script file asset locate requests.
        URNList m_pendingScriptLocates;

        // List of scripts we've loaded.
        ScriptInfoList m_loadedScripts;

        // Indicates we're waiting on an asset locate.
        bool m_waitingOnLocate;
    };
    typedef efd::SmartPointer<LuaScriptFactoryResponseData> ScriptFactoryResponseDataPtr;

    // helper function to get ready to load a script from disk.
    IAssetFactory::LoadStatus PrepareToLoadScript(
        efd::AssetFactoryManager* pAssetManager,
        const egf::ScriptFactoryRequest* pCurrentRequest);

    efd::AssetLoadResponse::AssetLoadResult LoadScriptData(ScriptInfo& scriptInfo);

    // Calculate dependent scripts required by the requested script.
    void CalculateDependencies(
        const ScriptInfo& scriptInfo,
        efd::list<efd::utf8string>& deps);

    // Add all the loaded scripts to the load response message.
    void AddScriptsToResponse(
        efd::AssetFactoryManager* pManager,
        LuaScriptFactoryResponseData* pResponse);

    // Helper for finding a dependency. Given a line and a dependency string, return the dependency.
    efd::utf8string FindDepend(
        const efd::utf8string& line,
        const efd::utf8string& findString);

    void FindDependencies(
        const ScriptInfo& scriptInfo,
        LuaScriptFactoryResponseData* pResponse);

    // our private category used by the AssetFactoryManager to respond to lookup requests.
    efd::Category m_privateCategory;
};

/// A SmartPointer for the LuaScriptFactory class
typedef efd::SmartPointer<LuaScriptFactory> LuaScriptFactoryPtr;

} // end namespace egf

#endif // EE_LUASCRIPTFACTORY_H
