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
#ifndef EE_LUAPARAMETERLIST_H
#define EE_LUAPARAMETERLIST_H

#include <efd/ParameterList.h>
#include <egfLua/egfLuaLibType.h>

struct lua_State;

namespace egf
{
    /// @cond EMERGENT_INTERNAL

    /**
        Method to initialize the ParameterList Lua module which implements the ParameterList class.
        This method should be called after the lua_State is initialized to register the
        ParameterList module.

        @param L Lua runtime state.
        @return 1, the number of objects left on the Lua stack (one metatable).
    */
    EE_EGF_LUA_ENTRY int luaopen_ParameterList(lua_State *L);

    // The following functions are use internally and should not be called directly.

    /**
        Convert a Lua object from a given location on the stack into a efd::ParameterList object.

        @param L Lua runtime state.
        @param pos Position on the stack.
        @return A ParameterList pointer, or NULL if the specified Lua object was not a
            ParameterList.
    */
    EE_EGF_LUA_ENTRY efd::ParameterList* lua_toParameterList(lua_State* L, int pos);

    /**
        Create a Lua ParameterList object from the provided efd::ParameterList and push it onto the
        top of the Lua stack.

        @param L Lua runtime state.
        @param pStream The stream to push onto the stack, which can be NULL.
        @return 1, the number of objects pushed on the stack (one ParameterList instance)
    */
    EE_EGF_LUA_ENTRY int lua_pushParameterList(lua_State* L, efd::ParameterList* pStream);

    /**
        Check if the Lua object at the given stack location is a ParameterList instance.
        @note The special value nil is treated as a valid but NULL ParameterList.

        @param L Lua runtime state.
        @param pos The index on the Lua stack.
        @return True if the object at pos is a ParameterList, false otherwise.
    */
    EE_EGF_LUA_ENTRY bool lua_checkParameterList(lua_State* L, int pos);

    /**
        Attempt to interpret a userdata value as a ParameterList and generate a user-friendly
        string representation suitable for display in the Lua debugger.

        @param L lua_State to examine.
        @param p Position on the Lua stack.
        @param value Resulting user-friendly string.
        @return true if the conversion was successful, false otherwise.
    */
    EE_EGF_LUA_ENTRY bool InterpretLuaParameterList(lua_State* L, int p, efd::utf8string& value);

    /// @endcond

} // end namespace egf

#endif // EE_LUAPARAMETERLIST_H
