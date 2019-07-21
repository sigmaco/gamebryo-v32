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
#ifndef EE_SCHEDULERLUA_H
#define EE_SCHEDULERLUA_H

#include <egfLua/egfLuaLibType.h>
#include <egf/ISchedulerScripting.h>
#include <efd/StdContainers.h>
#include <efd/DynamicModule.h>
#include <egfLua/LuaBehaviorDebugger.h>
#include <egf/egfClassIDs.h>
#include <efd/MessageService.h>
#include <efd/IConfigManager.h>
#include <efd/AssetFactoryManager.h>
#include <egfLua/ILuaPropertyHandler.h>

struct lua_State;

namespace efd
{
    class AssetLoadResponse;
    class AssetLocatorResponse;
}

namespace egf
{
    class EntityChangeMessage;
    class ILuaPropertyHandler;

/**
    Given a lua state, a module name, and a method name, push the method to the top
    of the Lua stack.

    @param L lua state.
    @param moduleName Name of the module.
    @param methodName name of the method.
    @return true if the function is now on the top of L stack, false if the method was
        not found.
 */
EE_EGF_LUA_ENTRY bool lua_getFunction(lua_State *L, const char* moduleName, const char* methodName);

/**
    Custom allocator used by Lua. This allocator forces Lua to use our internal allocator.
 */
EE_EGF_LUA_ENTRY void* LuaAllocator(void *ud, void *ptr, size_t osize, size_t nsize);

/**
   Get an EntityProxy for the entity with ID.
  
   Lua Stack In:
   [-1] EntityID as UInt64, or an EntityProxy userdata object.
  
   Lua Stack Out:
   [-1] EntityProxy userdata, or nil if the entity was not found.
  
    @param L lua state to use.
    @return 1, number of values pushed on the stack. Either EntityProxy userdata or nil.
*/
EE_EGF_LUA_ENTRY int lua_GetEntityProxyByID(lua_State *L);


/**
    A Lua specific implementation of SchedulerScripting. SchedulerLua owns the Lua runtime.
    It's responsible for initializing any Lua-behavior built-ins when InitForScripting is called.
    SchedulerLua is called when a Lua behavior is called by the Scheduler by calling one of
    DoTickScript or DoScriptBehavior.

    Built-in writers that bind to Lua need to add their initialization function to SchedulerLua
    before the Lua runtime is initialized. To accomplish this, add an appropriate entry to the
    config.ini for Dll builds, or call AddStaticBuiltinInitFunction in main for static builds.
 */
class EE_EGF_LUA_ENTRY SchedulerLua : public egf::ISchedulerScripting
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SchedulerLua, efd::kCLASSID_SchedulerLua, egf::ISchedulerScripting);
    /// @endcond

    /// @name Construction and Destruction
    //@{
protected:
    /// Virtual destructor
    virtual ~SchedulerLua();

public:
    /// Default constructor
    SchedulerLua();
    //@}

    /**
        Typedef for LuaScriptInitFunction pointers. When defining custom built-in functions, SWIG
        will generate a function used to initialize that built-in and register it with the Lua
        runtime. These functions have the following declaration:
    */
    typedef int (*LuaScriptInitFunction)(lua_State *);

    /**
        Register a Lua module initialization function. This method can be called as early as
        desired. Calls made prior to Scheduler::OnInit will be processed during Scheduler::OnInit
        and calls made after this point will be run immediately.

        @param i_pfn The Lua module initialization method
    */
    static bool AddStaticBuiltinInitFunction(LuaScriptInitFunction i_pfn);

    /// Get the list of registered static initialization functions.
    typedef efd::list<LuaScriptInitFunction> StaticBuiltinList;

    /// Helper function to get the current Lua stack as a list of utf8strings.
    static efd::list<efd::utf8string> DumpLuaStack(
        lua_State* L = ms_currentState, 
        const efd::utf8string& prefix = efd::utf8string::NullString());

    /// Get the Lua runtime state for the main Lua thread
    virtual lua_State* GetLuaState() const;

    /**
        Register an instance of ILuaPropertyHandler that can perform Get and Set property
        operations for the given storage class data type. This method can be called as soon as the
        SchedulerLua instance is created. It is recommended that property handlers be added during
        the OnPreInit phase of system service configuration.

        @param propDataType A class ID defining the storage type for the property. Note that this
            is the storage type as might be returned by Entity::GetDataStorageType and not the type
            of an egf::IProperty instance which would hold that data type.
        @param pHandler A property handler that knows how to read and write Lua objects to get and
            set entity properties.
        @return True if the handler was registered, or false if the class ID conflicts.
    */
    bool RegisterPropertyHandler(efd::ClassID propDataType, ILuaPropertyHandler* pHandler);

    /**
        Find a previously registered ILuaPropertyHandler instance.
    */
    inline ILuaPropertyHandler* GetPropertyHandler(efd::ClassID propDataType);

    /// Handler for AssetLookup Messages
    void HandleAssetLookupMsg(
        const efd::AssetLocatorResponse* pMessage,
        efd::Category targetChannel);

    /// Get the category used by this scripting engine.
    virtual efd::Category GetAssetLoadCategory() const;

protected:
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool InitForScripting(Scheduler* pScheduler);
    virtual void PreloadModule(const char* moduleName, efd::Category callback = efd::kCAT_INVALID);
    virtual bool ReloadModule(const char* moduleName);
    virtual bool DoScriptBehavior(egf::PendingBehavior* pPendBehavior);
    virtual void Shutdown();

    /// Initialize the Lua scripting runtime.
    bool InitLua();

    /// Initialize LUA built ins and register them with the runtime.
    bool InitBuiltins();

    /// Reads the config.ini file for LUA path information. Add the Lua system path to
    /// the LUA_PATH.
    bool InitSystemPath();

    /// Reads the config.ini file for asset path information.
    bool InitCMUserPath();

    /// Process a reload request. When background loading, this is called from the
    /// AssetLoad handler. Otherwise it's called directly from ReloadModule.
    bool ProcessReload(const char* moduleName, const char* newScript);

    /**
        Append additional paths to the LUA_PATH for .lua and .lc files.

        @param[in] basePath const char* path to append.
        @return efd::utf8string the extended path.
    */
    efd::utf8string BuildLuaPathAddition(const char *basePath);

    /**
        Append additional paths to the LUA_PATH for .dll and .so files.

        @param[in] basePath const char* path to append.
        @return efd::utf8string the extended path.
    */
    efd::utf8string BuildLuaCPathAddition(const char * basePath);

    /// All the dynamic modules containing built-ins that we know about:
    efd::list<efd::DynamicModule> m_BuiltinModules;

    /**
         @name Static linked functions
         Some built-ins are coming from static libraries linked directly to the final
         executable and cannot be easily moved into DLLs.  We still need to allow these to be
         initialized so I'll just call some static functions.  Since these functions are static
         linked we don't need to hold onto the dynamic module handles
    */
    //@{
    static StaticBuiltinList ms_StaticBuiltinInitFunctions;
    //@}

private:
    /**
        Determine if the behavior should be run in the main lua thread or in a coroutine thread.
        We want to use a coroutine only for behaviors that can block, unless the Lua debugger is
        attached in which case we want to use coroutines for all behaviors except immediates
        which we simply cannot debug.
    */
    inline bool ShouldUseCoroutine(egf::PendingBehavior* pPendBehavior);

public:
    /**
        Append any paths found in the given configuration section at valueKey to the lua
        package.path and package.cpath global search paths.
    */
    bool AppendLuaPath(const efd::ISection* pLuaSection, const char* valueKey);


    /// Helper to add locations found in an AssetLocatorResponse to the LUA_PATH
    static void AddAssetLocations(lua_State* state, const efd::AssetLocatorResponse* pMessage);

    /**
        Handle AssetFactoryManager messages in response to ScriptFactory requests.

        @param pResponse response message.
        @param target Category the message was delivered to.
    */
    void HandleAssetLoadResponse(const efd::AssetLoadResponse* pResponse, efd::Category target);

    /**
        Similar to GetPropertyImpl but uses a ParameterList rather than an Entity to read the
        value. The Lua stack contains the parameter list followed by either an integer index or
        string name for the parameter to read from the list and the then uses the correct
        ILuaPropertyHandler instance to push the correct data onto the Lua stack.

        @param L the Lua state containing the stack to read arguments from and push results to.
    */
    int GetParameter(lua_State* L);


    /**
        Generate a Lua error message in the provided lua_State.
    */
    static void LuaError(
        const efd::utf8string& msg = efd::utf8string::NullString(), 
        lua_State* L = ms_currentState);

    /**
        Name of the global Emergent table in Lua. We use this table to store application-wide
        values.
    */
    static const char* ms_LuaGlobalTable;

    /**
        Name of the key in the Emergent global table that holds the egf::PropertyResult
        value for the previous property operation. This can be used when accessing Entity
        properties directly via .PropertyName or ["PropertyName"] semantics, where the
        Lua specification for __index and __newindex metamethods only supports
        single value returns.
    */
    static const char* ms_PropertyResult;

    /**
        Get the global 'Emergent' Lua table from the given Lua state.

        Lua stack in:
        {any}

        Lua stack out:
        {any}
        [-1] 'Emergent' global Lua table, or no value if not found.

        @param L lua_State to look for the table.
        @return true if the table was found, false otherwise.
    */
    static bool GetGlobalTable(lua_State* L);

    /**
        Obtain 'this' from the Emergent global table found in the provided lua_State.
    */
    static SchedulerLua* GetSchedulerLua(lua_State* L);

protected:
    /// The main Lua thread state
    static lua_State* ms_luaState;

    /// Lua thread state for the currently running behavior
    static lua_State* ms_currentState;

    typedef efd::map<efd::ClassID, ILuaPropertyHandlerPtr> PropHandlerMap;
    PropHandlerMap m_PropHandlers;

    // Only the intended methods should be calling the Get/SetPropertyImpl methods.
    friend EE_EGF_LUA_ENTRY int lua_GetProperty(lua_State *L);
    friend EE_EGF_LUA_ENTRY int lua_GetDefaultProperty(lua_State *L);
    friend EE_EGF_LUA_ENTRY int lua_SetProperty(lua_State* L);
    friend class LuaResumeCoroutineTask;

    /// Category used by the AssetFactoryManager to report LuaScriptFactoryResponse messages.
    efd::Category m_category;

    efd::SmartPointer<efd::MessageService> m_spMsgSvc;
    efd::SmartPointer<efd::ServiceManager> m_spSrvMgr;
    efd::SmartPointer<efd::IConfigManager> m_spConfigManager;
    efd::SmartPointer<efd::AssetFactoryManager> m_spAFM;

    /// Map of script names to callback categories used during module preload. Once a module
    /// has completed loading, the ScriptFactoryResponse message is forwarded to the category.
    typedef efd::map<efd::utf8string, efd::Category> PreloadCallbackMap;
    PreloadCallbackMap m_preloadCallbackMap;

    /**
        Helper for implementing lua_GetProperty and lua_GetDefaultProperty. Reads arguments from
        the Lua stack to determine what property to read and then uses the correct
        ILuaPropertyHandler instance to read the property.

        @param L the Lua state containing the stack to read arguments from and push results to.
        @param getDefault If true the default property value is fetched, otherwise the current
            value is fetched.
    */
    int GetPropertyImpl(lua_State* L, bool getDefault);
    /**
        Helper for implementing lua_SetProperty. Reads arguments from the Lua stack to determine
        what property to set and then uses the correct ILuaPropertyHandler instance to set the
        property.

        @param L the Lua state containing the stack to read arguments from and push results to.
    */
    int SetPropertyImpl(lua_State* L);

    /**
        Log the error message at the top of the luaState stack to the Lua error log.

        @param status int status value of the last Lua call made.
        @param pState the Lua state to look for error messages. Defaults to the main Lua thread state.
    */
    void LogLuaError(int status, lua_State* pState=ms_currentState);

    /**
        Load a script from the provided buffer. The buffer can be either text or bytecode.

        @param scriptData String containing the contents of the Lua script.
        @param scriptName the name of the script.
        @param reload True if the existing module should be unloaded before loading this script.
        @return true if the load succeeds, false otherwise.
    */
    bool LoadScriptFromBuffer(
        const char* scriptData,
        const char* scriptName,
        bool reload);

    /**
        Create a lua module named "scheduler" to which we add functions needed for the rapid
        iteration of lua scripts.
    */
    bool MakeSchedulerModule();

#ifndef EE_CONFIG_SHIPPING
    LuaBehaviorDebuggerPtr m_spDebugger;
#endif
};

/// A SmartPointer for the SchedulerLua class
typedef efd::SmartPointer<SchedulerLua> SchedulerLuaPtr;

} // end namespace egf

#include <egfLua/SchedulerLua.inl>

#endif // EE_SCHEDULERLUA_H
