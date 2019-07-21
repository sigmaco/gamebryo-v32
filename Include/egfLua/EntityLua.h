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
#ifndef EE_EntityLua_h
#define EE_EntityLua_h

#if !defined(DISABLE_SCRIPTING) && defined(LUA_SCRIPTING)

#include <egfLua/egfLuaLibType.h>

namespace egf
{
///
///  The following built-in functions expose methods in the Lua runtime to interact with
///  egf::Entity instances. Specifically, you can get / set properties, dump a list of
///  properties, and set a conditional breakpoint on a specific entity from Lua using
///  these built-in functions. They're available in Lua from the BehaviorAPI namespace.
///
/// @name Built-in functions from EntityLua.h

//@{
/**
    This method returns the specified property for the specified Entity. Arguments to
    this call are passed on the Lua stack.

    @param L lua_State pointer
    @return The number of values pushed on to the Lua stack. The number varies by
     property type. See bapiLua.h for details of each type.

    @code
    BehaviorAPI::GetProperty(EntityID, PropertyID, key (optional))
    Args:
      Arg 1: Entity ID
      Arg 2: property ID or name (can be specified as either tPropertyID or string)
      Arg 3 (optional): key for looking up entries in a map property
    @endcode

    Arguments are popped from the stack, results are push on the stack.
*/
EE_EGF_LUA_ENTRY int lua_GetProperty(lua_State *L);

/**
    This method returns the default value of the specified property for specified entity.
    The default value is the value specified in the flat model and does not reflect any overrides
    specified in the block file.  Arguments to this call are passed on the Lua stack.

    @param L lua_State pointer
    @return The number of values pushed on to the Lua stack. The number varies by
    property type. See bapiLua.h for details of each type.

    @code
    BehaviorAPI::GetDefaultProperty(EntityID, propertyID, key(optional))
        Args:
            Arg 1: Entity ID
            Arg 2: property ID or name (can be specified as either tPropertyID or string)
            Arg 3 (optional): key for looking up entries in a map property
    @endcode

    Arguments are popped from the stack, results are push on the stack.
*/
EE_EGF_LUA_ENTRY int lua_GetDefaultProperty(lua_State *L);


/**
    This method sets the specified property for the specified entity. Arguments to this call
    are passed on the Lua stack.

    @param L lua_State pointer
    @return 1, the number of objects pushed on the Lua stack (one result value).

    @code
    BehaviorAPI::SetProperty(EntityID, propertyID, key (or nil), value)
        Args:
           Arg 1: Entity ID
           Arg 2: property ID or name (can be specified as either tPropertyID or string)
           Arg 3: key name for map properties (optional)
           Arg 4: new value
    @endcode

    Results are returned to the Lua stack.
*/
EE_EGF_LUA_ENTRY int lua_SetProperty(lua_State* L);


/**
    This method sends an event and blocks waiting for a response.

    @param L lua_State pointer.
    @return -1 if the wait succeeded, 0 if we were unable to wait either because the entity
              is non-blocking or if lua_yield failed.

    Arguments are passed on the Lua stack:
    @code
    BehaviorAPI::SendAndWaitForReply(EntityID, behavior, ParameterList*, delay)
        Args:
           Arg 1: EntityID for the target entity
           Arg 2: String containing the behavior name to call
           Arg 3: (optional) ParameterList* containing arguments to the behavior
           Arg 4: (optional) TimeType with the number of seconds to delay the event
    @endcode

    Returns a ParameterList containing the response data.  Results are returned to the Lua stack.
*/
EE_EGF_LUA_ENTRY int lua_SendAndWaitForReply(lua_State* L);

/**
    This method yields the current coroutine for a specified number of milliseconds. The sleep
    duration is measured in game time (not real time).  Only blocking behaviors can call this
    method.

    @param L lua_State pointer
    @return -1 if the yield succeeded, 0 if we were unable to wait either because the entity
    is non-blocking or if lua_yield failed.

    Arguments are passed on the Lua stack:
    @code
    BehaviorAPI::Sleep(timeInMilliseconds)
        Args:
           Arg 1: Time to sleep in milliseconds
    @endcode

    No lua results are returned.
*/
EE_EGF_LUA_ENTRY int lua_Sleep(lua_State* L);

/**
    This method dumps all property values to the log for the specified entity.

    @param L lua_State pointer
    @return 0 on success, 1 on failure.

    Arguments are on the Lua stack:
    @code
    BehaviorAPI::DumpProperties(EntityID)
        Args:
          Arg 1: Entity ID
    @endcode

    No lua results are returned.
*/
EE_EGF_LUA_ENTRY int lua_DumpProperties(lua_State* L);

/**
    This method acts like a coded conditional breakpoint.  If the passed expression is false, the
    behavior debugger will break into execution.  If no debugging session is active, the condition
    will just be logged.

    @param L lua_State pointer
    @return 0 always (unused)

    Arguments are on the Lua stack:
    @code
    BehaviorAPI::BreakIfFalse(<expression>)
        Args:
          Arg 1: boolean result of expression
    @endcode

    No lua results are returned.
*/
EE_EGF_LUA_ENTRY int lua_BreakIfFalse(lua_State* L);


/**
    Implementation of the BehaviorAPI.CreateEntityAndWait(modelName, createParams, initParams)
    built-in API method for the Lua scripting language.

    Creates a new entity and adds it to the local simulator. The process of creating a new entity
    is asynchronous. This call will block the current behavior until the Entity is ready or the
    creation fails. Returns the new Entity's EntityID identifier, or 0 if the Entity creation
    failed.

    Arguments (read from the Lua stack):
        - Arg 1: String containing the model name for the new entity.
        - Arg 2: optional ParameterList passed to the new entity's OnCreate behavior.
        - Arg 3: optional ParameterList containing initial property values.

    Return values (pushed onto the Lua Stack when the co-routine is resumed):
        - The EntityID of the new entity, or 0 if creation failed.

    @note Other options for creating an entity include BehaviorAPI.SpawnEntity, which requires the
    flat model to be preloaded, and BehaviorAPI.CreateEntity which is non-blocking but can send a
    callback behavior once all creation lifecycles complete on the new entity.

    @param L lua_State pointer
    @return -1 if the wait succeeded, 0 if we were unable to wait either because the entity
        is non-blocking or if lua_yield failed.
*/
EE_EGF_LUA_ENTRY int lua_CreateEntityAndWait(lua_State* L);

//@}

} // end namespace egf

#endif // !defined(DISABLE_SCRIPTING) && defined(LUA_SCRIPTING)

#endif // EE_EntityLua_h
