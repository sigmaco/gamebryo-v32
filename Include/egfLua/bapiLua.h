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
#ifndef EE_BAPILUA_H
#define EE_BAPILUA_H

#include <egf/BehaviorAPI.h>
#include <efd/ParseHelper.h>
#include <egfLua/LuaDataStream.h>
#include <efd/AssetID.h>
#include <efd/Quaternion.h>
#include <egf/egfLogIDs.h>
#include <egf/Entity.h>

#include <egfLua/SWIGLuaRuntime.h>
#include <egfLua/EntityProxyLua.h>
#include <egf/ScriptContext.h>
#include <egf/EntityManager.h>
#include <egfLua/EntityProxyLua.h>

struct lua_State;

// Make sure 64-bit integer support is enabled when building Lua wrappers.
#if !defined(LUA_USELONGLONG) || !defined(LNUM_DOUBLE) || !defined(LNUM_INT64)
EE_COMPILETIME_ASSERT(false);
#endif


namespace bapiLua
{

typedef efd::Bool (IsTypeFunction)(lua_State*, int);

// Print an error message about bad type conversion in lua and cause current behavior to fail
// with lua file and line number.  To cause the failure we simply return false which triggers
// a SWIG_fail call in the binding layer and that in turn calls lua_error which will use the
// string we are pushing here as the error string.
template<typename T>
bool LuaTypecheck(lua_State* L, int pos, const char* strTypeName);


/**
    The following templates are used to convert to/from C++ data types to Lua data types.
 */
template<typename T>
struct LuaTraits
{
};

/// Lua trait handler for type efd::Bool
template<>
struct LuaTraits<efd::Bool>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // in many places we pass 0 or 1 as a bool, so allow integers as well
        return lua_isboolean(L, pos) || lua_isinteger(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get a Bool value from the Lua stack and return it.

        @param L The Lua runtime state.
        @param pos position on the stack.
        @param o_rval converted bool value from the lua stack.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::Bool& o_rval)
    {
        if (!LuaTypecheck<efd::Bool>(L, pos, "efd::Bool")) return false;

        if (lua_isinteger(L, pos))
        {
            o_rval = (lua_tointeger(L, pos) != 0);
        }
        else
        {
            o_rval = (lua_toboolean(L, pos) != 0);
        }
        return true;
    }

    /**
        Push a Bool value on to the top of Lua stack.

        @param L The Lua runtime state.
        @param i_data Bool value to push on the stack.
        @return 1, the number of items pushed on the Lua stack.
    */
    static int ToLuaObject(lua_State* L, efd::Bool i_data)
    {
        lua_pushboolean(L, i_data);
        return 1;
    }
};


/// Lua trait handler for type efd::utf8string
template<>
struct LuaTraits<efd::utf8string>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // We treat nil as an empty string
        return lua_isstring(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get a utf8string from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result string at pos or empty string if pos doesn't contain a string.
        @return true if the conversion was successful.

        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::utf8string& o_result)
    {
        if (!LuaTypecheck<efd::utf8string>(L, pos, "efd::utf8string")) return false;

        // We deliberately treat 'nil' as an empty string, for anything else log an error
        if (lua_isnil(L, pos))
        {
            o_result.clear();
            return true;
        }

        EE_ASSERT(lua_isstring(L, pos));
        o_result = (const char*)lua_tostring(L, pos);
        return true;
    }

    /**
        Push a utf8string on to the Lua stack.

        @param L Lua runtime state.
        @param i_data string to push on the stack.
        @return 1, the number of objects pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::utf8string& i_data)
    {
        lua_pushstring(L, i_data.c_str());
        return 1;
    }
};


/// Lua trait handler for type efd::Char*
template<>
struct LuaTraits<efd::Char*>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        return lua_isstring(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get a const efd::Char* from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result const char* at pos, or null if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, const efd::Char*& o_result)
    {
        if (!LuaTypecheck<efd::Char*>(L, pos, "efd::Char*")) return false;

        if (lua_isnil(L, pos))
        {
            // do nothing, allow 'nil' to represent null pointer
            o_result = NULL;
            return true;
        }

        EE_ASSERT(lua_isstring(L, pos));
        o_result = lua_tostring(L, pos);
        return true;
    }

    /**
        Push a const efd::Char* on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value tp push on the stack.
        @return 1, the number of objects pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::Char* i_data)
    {
        lua_pushstring(L, i_data);
        return 1;
    }
};

/// Lua trait handler for type efd::WChar*
template<>
struct LuaTraits<efd::WChar*>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        return lua_isstring(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get a const efd::WChar* from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result const efd::WChar* at pos or null if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, const efd::WChar*& o_result)
    {
        if (!LuaTypecheck<efd::WChar*>(L, pos, "efd::WChar*")) return false;

        if (lua_isnil(L, pos))
        {
            // do nothing, allow 'nil' to represent null pointer
            o_result = NULL;
            return true;
        }

        // Lua stores 'strings' as byte arrays with a length, ignoring content (e.g.
        // embedded null values).
        EE_ASSERT(lua_isstring(L, pos));
        o_result = (efd::WChar *)lua_tostring(L, pos);
        return true;
    }

    /**
        Push a const efd::WChar* string on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::WChar* i_data)
    {
        size_t len = wcslen((const wchar_t*)i_data);
        lua_pushlstring(L, (const char*)i_data, len);
        return 1;
    }
};

// The PS3 compiler sees SInt8 and Char as distinct types, but all other compilers (including
// newer versions of GCC like we use on Linux) see them as identical.  This means we must have
// seperate definitions for PS3 but cannot have seperate definitions on other platforms.
#if defined(EE_PLATFORM_PS3)
/// Lua trait handler for PS3 type efd::Char
template<>
struct LuaTraits<efd::Char>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        return lua_isnumber(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get an efd::Char from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::Char at pos or null if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::Char& o_result)
    {
        if (!LuaTypecheck<efd::Char>(L, pos, "efd::Char")) return false;

        o_result = (efd::Char)lua_tointeger(L, pos);
        return true;
    }

    /**
        Push an efd::Char value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::Char i_data)
    {
        lua_pushinteger(L, i_data);
        return 1;
    }
};
#endif

/// Lua trait handler for type efd::SInt8
template<>
struct LuaTraits<efd::SInt8>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // We treat nil as zero
        return lua_isnumber(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get an efd::SInt8 from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::SInt8 at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::SInt8& o_result)
    {
        if (!LuaTypecheck<efd::SInt8>(L, pos, "efd::SInt8")) return false;

        o_result = (efd::SInt8)lua_tointeger(L, pos);
        return true;
    }

    /**
        Push an efd::SInt8 value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::SInt8 i_data)
    {
        lua_pushinteger(L, i_data);
        return 1;
    }
};

/// Lua trait handler for type efd::UInt8
template<>
struct LuaTraits<efd::UInt8>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // We treat nil as zero
        return lua_isnumber(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get an efd::UInt8 from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::UInt8 at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::UInt8& o_result)
    {
        if (!LuaTypecheck<efd::UInt8>(L, pos, "efd::UInt8")) return false;

        o_result = (efd::UInt8)lua_tointeger(L, pos);
        return true;
    }

    /**
        Push an efd::UInt8 value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::UInt8 i_data)
    {
        lua_pushinteger(L, i_data);
        return 1;
    }
};

/// Lua trait handler for type efd::SInt16
template<>
struct LuaTraits<efd::SInt16>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // We treat nil as zero
        return lua_isnumber(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get an efd::SInt16 from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::SInt16 at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::SInt16& o_result)
    {
        if (!LuaTypecheck<efd::SInt16>(L, pos, "efd::SInt16")) return false;

        o_result = (efd::SInt16)lua_tointeger(L, pos);
        return true;
    }

    /**
        Push an efd::SInt16 value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::SInt16 i_data)
    {
        lua_pushinteger(L, i_data);
        return 1;
    }
};

/// Lua trait handler for type efd::UInt16
template<>
struct LuaTraits<efd::UInt16>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // We treat nil as zero
        return lua_isnumber(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get an efd::UInt16 from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::UInt16 at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::UInt16& o_result)
    {
        if (!LuaTypecheck<efd::UInt16>(L, pos, "efd::UInt16")) return false;

        o_result = (efd::UInt16)lua_tointeger(L, pos);
        return true;
    }

    /**
        Push an efd::UInt16 value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::UInt16 i_data)
    {
        lua_pushinteger(L, i_data);
        return 1;
    }
};

/// Lua trait handler for type efd::SInt32
template<>
struct LuaTraits<efd::SInt32>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // We treat nil as zero
        return lua_isnumber(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get an efd::SInt32 from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::SInt32 at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::SInt32& o_result)
    {
        if (!LuaTypecheck<efd::SInt32>(L, pos, "efd::SInt32")) return false;

        o_result = (efd::SInt32)lua_tointeger(L, pos);
        return true;
    }

    /**
        Push an efd::SInt32 value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::SInt32 i_data)
    {
        lua_pushinteger(L, i_data);
        return 1;
    }
};

/// Lua trait handler for type efd::UInt32
template<>
struct LuaTraits<efd::UInt32>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // We treat nil as zero
        return lua_isnumber(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get an efd::UInt32 from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::UInt32 at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::UInt32& o_result)
    {
        if (!LuaTypecheck<efd::UInt32>(L, pos, "efd::UInt32")) return false;

        o_result = (efd::UInt32)lua_tointeger(L, pos);
        return true;
    }

    /**
        Push an efd::UInt32 value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::UInt32 i_data)
    {
        lua_pushinteger(L, i_data);
        return 1;
    }
};

/// Lua trait handler for type efd::SInt64
template<>
struct LuaTraits<efd::SInt64>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // We treat nil as zero
        return lua_isnumber(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get an efd::SInt64 from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::SInt64 at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::SInt64& o_result)
    {
        if (!LuaTypecheck<efd::SInt64>(L, pos, "efd::SInt64")) return false;

        o_result = (efd::SInt64)lua_tointeger(L, pos);
        return true;
    }

    /**
        Push an efd::SInt64 value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::SInt64 i_data)
    {
        lua_pushinteger(L, i_data);
        return 1;
    }
};

/// Lua trait handler for type efd::UInt64
template<>
struct LuaTraits<efd::UInt64>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // We treat nil as zero. Also - special handling so we can accept EntityID instances.
        return lua_isnumber(L, pos) || lua_isnil(L, pos)  || egf::lua_checkEntityProxy(L, pos);

    }

    /**
        Get an efd::UInt64 from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::UInt64 at pos or null if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::UInt64& o_result)
    {
        o_result = 0;

        if (!LuaTypecheck<efd::UInt64>(L, pos, "efd::UInt64")) return false;

        if (lua_isinteger(L, pos))
        {
            o_result = (efd::UInt64)lua_tointeger(L, pos);
            return true;
        }
        else if (lua_isnil(L, pos))
        {
            return true;
        }

        egfLua::EntityProxy* tmp = egf::lua_toEntityProxy(L, pos);
        if (tmp)
        {
            if (tmp->m_pEntity)
            {
                o_result = tmp->m_pEntity->GetEntityIDValue();
            }
            return true;
        }

        return false;
    }

    /**
        Push an efd::UInt64 value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::UInt64 i_data)
    {
        lua_pushinteger(L, i_data);
        return 1;
    }
};

/// Lua trait handler for type efd::UniversalID
template<>
struct LuaTraits<efd::UniversalID>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        return bapiLua::LuaTraits<efd::UInt64>::IsType(L, pos);
    }

    /**
        Get an efd::UniversalID from the Lua stack. This value is represented as
        an efd::UInt64 in lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::UniversalID at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::UniversalID& o_result)
    {
        if (!LuaTypecheck<efd::UniversalID>(L, pos, "efd::UniveralID")) return false;

        efd::UInt64 result;
        if (bapiLua::LuaTraits<efd::UInt64>::FromLuaObject(L, pos, result))
        {
            o_result = result;
            return true;
        }
        return false;
    }

    /**
        Push an efd::UniversalID value on to the Lua stack. This value is represented as
        an efd::UInt64 in lua.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::UniversalID& i_data)
    {
        lua_pushinteger(L, i_data.GetValue());
        return 1;
    }
};

/// Lua trait handler for type efd::Category
template<>
struct LuaTraits<efd::Category>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        return bapiLua::LuaTraits<efd::UInt64>::IsType(L, pos);
    }

    /**
        Get an efd::Category from the Lua stack. This value is represented as
        an efd::UInt64 in lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::Category at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::Category& o_result)
    {
        if (!LuaTypecheck<efd::Category>(L, pos, "efd::Category")) return false;

        efd::UInt64 result;
        if (bapiLua::LuaTraits<efd::UInt64>::FromLuaObject(L, pos, result))
        {
            o_result = result;
            return true;
        }
        return false;
    }

    /**
        Push an efd::Category value on to the Lua stack. This value is represented as
        an efd::UInt64 in lua.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::Category& i_data)
    {
        lua_pushinteger(L, i_data.GetValue());
        return 1;
    }
};

/// Lua trait handler for type efd::EntityID
template<>
struct LuaTraits<egf::EntityID>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        return bapiLua::LuaTraits<efd::UInt64>::IsType(L, pos) || egf::lua_checkEntityProxy(L, pos);
    }

    /**
        Get an egf::EntityID from the Lua stack. This value is represented as
        an efd::UInt64 value or an egfLua::EntityProxy object in Lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result egf::EntityID at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, egf::EntityID& o_result)
    {
        if (!LuaTypecheck<egf::EntityID>(L, pos, "egf::EntityID")) return false;

        efd::UInt64 result;

        egfLua::EntityProxy* tmp = egf::lua_toEntityProxy(L, pos);
        if (tmp)
        {
            o_result = tmp->ID;
            return true;
        }
        else if (bapiLua::LuaTraits<efd::UInt64>::FromLuaObject(L, pos, result))
        {
            o_result = result;
            return true;
        }

        return false;
    }

    /**
        Push an efd::EntityID value on to the Lua stack. This value is represented as
        an egfLua::EntityProxy in lua.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, const egf::EntityID& i_data)
    {
        egf::EntityManager* pEntityMgr =
            egf::g_bapiContext.GetSystemServiceAs<egf::EntityManager>();
        if (!pEntityMgr)
        {
            lua_pushnil(L);
            return 1;
        }

        egfLua::EntityProxy* pResult = 0;

        egf::Entity* pEntity = pEntityMgr->LookupEntity(i_data);

        // If this is a EntityRef, the referenced entity may have been deleted.
        // We still want to create a reference in this situation.
        if (!pEntity)
        {
            pResult = EE_EXTERNAL_NEW egfLua::EntityProxy(i_data.GetValue());
        }
        else
        {
            pResult = EE_EXTERNAL_NEW egfLua::EntityProxy(pEntity);
        }

        swig_type_info* pTypeInfo = egfLua::EntityProxy::GetStaticEntityProxySWIGTypeInfo(L);

        // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
        EE_ASSERT(pTypeInfo);

        SWIG_Lua_NewPointerObj(L, pResult, pTypeInfo, 1);

        // Bind the entity's individual properties to this proxy.
        pResult->Bind(L);

        return 1;
    }
};

/// Lua trait handler for type efd::EventID
template<>
struct LuaTraits<egf::EventID>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        return bapiLua::LuaTraits<efd::UInt64>::IsType(L, pos);
    }

    /**
        Get an egf::EventID from the Lua stack. This value is represented as
        an efd::UInt64 in lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result egf::EventID at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, egf::EventID& o_result)
    {
        if (!LuaTypecheck<egf::EventID>(L, pos, "egf::EventID")) return false;

        efd::UInt64 result;
        if (bapiLua::LuaTraits<efd::UInt64>::FromLuaObject(L, pos, result))
        {
            o_result = result;
            return true;
        }
        return false;
    }

    /**
        Push an egf::EventID value on to the Lua stack. This value is represented as
        an efd::UInt64 in lua.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, const egf::EventID& i_data)
    {
        lua_pushinteger(L, i_data.GetValue());
        return 1;
    }
};

/// Lua trait handler for type efd::Float32
template<>
struct LuaTraits<efd::Float32>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // we treat nil as zero
        return lua_isnumber(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get an efd::Float32 from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::Float32 at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::Float32& o_result)
    {
        if (!LuaTypecheck<efd::Float32>(L, pos, "efd::Float32")) return false;

        o_result = (efd::Float32)lua_tonumber(L, pos);
        return true;
    }

    /**
        Push an efd::Float32 value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::Float32 i_data)
    {
        lua_pushnumber(L, i_data);
        return 1;
    }
};

/// Lua trait handler for type efd::Float64
template<>
struct LuaTraits<efd::Float64>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        // we treat nil as zero
        return lua_isnumber(L, pos) || lua_isnil(L, pos);
    }

    /**
        Get an efd::Float64 from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::Float64 at pos or 0 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::Float64& o_result)
    {
        if (!LuaTypecheck<efd::Float64>(L, pos, "efd::Float64")) return false;

        o_result = (efd::Float64)lua_tonumber(L, pos);
        return true;
    }

    /**
        Push an efd::Float64 value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::Float64 i_data)
    {
        lua_pushnumber(L, i_data);
        return 1;
    }
};

/// Lua trait handler for type efd::ParameterList*
template<>
struct LuaTraits<efd::ParameterList*>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        return egf::lua_checkParameterList(L, pos);
    }

    /**
        Get an efd::ParameterList* user data value from the Lua stack.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::ParameterList* at pos or null if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::ParameterList*& o_result)
    {
        if (!LuaTypecheck<efd::ParameterList*>(L, pos, "efd::ParameterList*")) return false;

        o_result = egf::lua_toParameterList(L, pos);
        return true;
    }

    /**
        Push an efd::ParameterList user data value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects push on the stack.
    */
    static int ToLuaObject(lua_State* L, efd::ParameterList* i_data)
    {
        return egf::lua_pushParameterList(L, i_data);
    }
};

/// Lua trait handler for type efd::Point2
template<>
struct LuaTraits<efd::Point2>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        if (lua_isuserdata(L, pos))
        {
            if (strcmp(SWIG_Lua_typename(L, pos), "efd::Point2 *") == 0) return true;
        }
        else if (lua_istable(L, pos))
        {
            if (lua_objlen(L, pos) == 2) return true;
        }

        return false;
    }

    /**
        Get an efd::Point2 from the Lua stack. This is represented as a table with two
        float values in Lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::Point2 at pos or default Point2 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::Point2& o_result)
    {
        if (!LuaTypecheck<efd::Point2>(L, pos, "efd::Point2 *")) return false;

        if (lua_isuserdata(L, pos))
        {
            swig_module_info *module = SWIG_GetModule(L);
            swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Point2 *");

            // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
            EE_ASSERT(typeInfo);

            efd::Point2* tmp = 0;
            if (SWIG_Lua_ConvertPtr(L, pos, (void**)&tmp, typeInfo, 1) == SWIG_OK && tmp)
            {
                o_result = *tmp;
                return true;
            }
        }
        else if (lua_istable(L, pos))
        {
            lua_rawgeti(L, pos, 1);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.x))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 2);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.y))
                return false;
            lua_pop(L, 1);

            return true;
        }

        return false;
    }

    /**
        Push a Lua table containing the values for a Point2 on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects (one table) pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::Point2& i_data)
    {
        efd::Point2* pResult = EE_NEW efd::Point2(i_data.x, i_data.y);

        swig_module_info *module = SWIG_GetModule(L);
        swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Point2 *");

        // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
        EE_ASSERT(typeInfo);

        SWIG_Lua_NewPointerObj(L, pResult, typeInfo, 1);

        return 1;
    }
};

/// Lua trait handler for type efd::Point3
template<>
struct LuaTraits<efd::Point3>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches. The only compatible
        type for Point3 is a lua table with 3 values or a Point3 userdata type.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        if (lua_isuserdata(L, pos))
        {
            if (strcmp(SWIG_Lua_typename(L, pos), "efd::Point3 *") == 0) return true;
        }
        else if (lua_istable(L, pos))
        {
            if (lua_objlen(L, pos) == 3) return true;
        }

        return false;
    }

    /**
        Get an efd::Point3 from the Lua stack. This is represented as a userdata object
        in Lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::Point3 at pos or the default point3 if the position doesn't
            contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::Point3& o_result)
    {
        if (!LuaTypecheck<efd::Point3>(L, pos, "efd::Point3 *")) return false;

        if (lua_isuserdata(L, pos))
        {
            swig_module_info *module = SWIG_GetModule(L);
            swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Point3 *");

            // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
            EE_ASSERT(typeInfo);

            efd::Point3* tmp = 0;
            if (SWIG_Lua_ConvertPtr(L, pos, (void**)&tmp, typeInfo, 1) == SWIG_OK && tmp)
            {
                o_result = *tmp;
                return true;
            }
        }
        else if (lua_istable(L, pos))
        {
            lua_rawgeti(L, pos, 1);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.x))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 2);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.y))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 3);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.z))
                return false;
            lua_pop(L, 1);

            return true;
        }

        return false;
    }

    /**
        Push a Lua userdata containing the values for a Point3 on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects (one table) pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::Point3& i_data)
    {
        efd::Point3* pResult = EE_NEW efd::Point3(i_data);

        swig_module_info *module = SWIG_GetModule(L);
        swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Point3 *");

        // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
        EE_ASSERT(typeInfo);

        SWIG_Lua_NewPointerObj(L, pResult, typeInfo, 1);

        return 1;
    }
};

/// Lua trait handler for type efd::Point4
template<>
struct LuaTraits<efd::Point4>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        if (lua_isuserdata(L, pos))
        {
            if (strcmp(SWIG_Lua_typename(L, pos), "efd::Point4 *") == 0) return true;
        }
        else if (lua_istable(L, pos))
        {
            if (lua_objlen(L, pos) == 4) return true;
        }

        return false;
    }

    /**
        Get an efd::Point4 from the Lua stack. This is represented as a table with 4 float values
        in Lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::Point4 at pos. Parameter is unchanged if the position doesn't contain
            a Point4 object.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::Point4& o_result)
    {
        if (!LuaTypecheck<efd::Point4>(L, pos, "efd::Point4 *")) return false;

        if (lua_isuserdata(L, pos))
        {
            swig_module_info *module = SWIG_GetModule(L);
            swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Point4 *");

            // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
            EE_ASSERT(typeInfo);

            efd::Point4* tmp = 0;
            if (SWIG_Lua_ConvertPtr(L, pos, (void**)&tmp, typeInfo, 1) == SWIG_OK && tmp)
            {
                o_result = *tmp;
                return true;
            }
        }
        else if (lua_istable(L, pos))
        {
            lua_rawgeti(L, pos, 1);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.m_afPt[0]))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 2);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.m_afPt[1]))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 3);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.m_afPt[2]))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 4);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.m_afPt[3]))
                return false;
            lua_pop(L, 1);

            return true;
        }

        return false;
    }

    /**
        Push a Lua table containing the values for a Point4 on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects (one table) pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::Point4& i_data)
    {
        efd::Point4* pResult = EE_EXTERNAL_NEW efd::Point4(i_data);

        swig_module_info *module = SWIG_GetModule(L);
        swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Point4 *");

        // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
        EE_ASSERT(typeInfo);

        SWIG_Lua_NewPointerObj(L, pResult, typeInfo, 1);

        return 1;
    }
};

/// Lua trait handler for type efd::Quaternion
template<>
struct LuaTraits<efd::Quaternion>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        if (lua_isuserdata(L, pos))
        {
            if (strcmp(SWIG_Lua_typename(L, pos), "efd::Quaternion *") == 0) return true;
        }
        else if (lua_istable(L, pos))
        {
            if (lua_objlen(L, pos) == 4) return true;
        }

        return false;
    }

    /**
        Get an efd::Quaternion from the Lua stack. This is represented as a table with 4
        float values in Lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::Quaternion at pos or default Quaternion if the position doesn't
            contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::Quaternion& o_result)
    {
        if (!LuaTypecheck<efd::Quaternion>(L, pos, "efd::Quaternion *")) return false;

        if (lua_isuserdata(L, pos))
        {
            swig_module_info *module = SWIG_GetModule(L);
            swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Quaternion *");

            // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
            EE_ASSERT(typeInfo);

            efd::Quaternion* tmp = 0;
            if (SWIG_Lua_ConvertPtr(L, pos, (void**)&tmp, typeInfo, 1) == SWIG_OK && tmp)
            {
                o_result = *tmp;
                return true;
            }
        }
        else if (lua_istable(L, pos))
        {
            lua_rawgeti(L, pos, 1);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.m_w))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 2);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.m_x))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 3);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.m_y))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 4);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.m_z))
                return false;
            lua_pop(L, 1);

            return true;
        }

        return false;
    }

    /**
        Push a Lua table containing the values for a Quaternion on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects (one table) pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::Quaternion& i_data)
    {
        efd::Quaternion* pResult = EE_NEW efd::Quaternion(i_data);

        swig_module_info *module = SWIG_GetModule(L);
        swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Quaternion *");

        // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
        EE_ASSERT(typeInfo);

        SWIG_Lua_NewPointerObj(L, pResult, typeInfo, 1);

        return 1;
    }
};

/// Lua trait handler for type efd::Color
template<>
struct LuaTraits<efd::Color>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        if (lua_isuserdata(L, pos))
        {
            if (strcmp(SWIG_Lua_typename(L, pos), "efd::Color *") == 0) return true;
        }
        else if (lua_istable(L, pos))
        {
            if (lua_objlen(L, pos) == 3) return true;
        }

        return false;
    }

    /**
        Get an efd::Color from the Lua stack. This is represented as a table with 3 float
        values in Lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::Color at pos or the default Color if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::Color& o_result)
    {
        if (!LuaTypecheck<efd::Color>(L, pos, "efd::Color *")) return false;

        if (lua_isuserdata(L, pos))
        {
            swig_module_info *module = SWIG_GetModule(L);
            swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Color *");

            // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
            EE_ASSERT(typeInfo);

            efd::Color* tmp = 0;
            if (SWIG_Lua_ConvertPtr(L, pos, (void**)&tmp, typeInfo, 1) == SWIG_OK && tmp)
            {
                o_result.r = tmp->r;
                o_result.g = tmp->g;
                o_result.b = tmp->b;
                return true;
            }
        }
        else if (lua_istable(L, pos))
        {
            lua_rawgeti(L, pos, 1);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.r))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 2);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.g))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 3);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.b))
                return false;
            lua_pop(L, 1);

            return true;
        }

        return false;
    }

    /**
        Push a Lua table containing the values for a Color on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects (one table) pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::Color& i_data)
    {
        efd::Color* pResult = EE_NEW efd::Color(i_data.r, i_data.g, i_data.b);

        swig_module_info *module = SWIG_GetModule(L);
        swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Color *");

        // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
        EE_ASSERT(typeInfo);

        SWIG_Lua_NewPointerObj(L, pResult, typeInfo, 1);

        return 1;
    }
};

/// Lua trait handler for type efd::ColorA
template<>
struct LuaTraits<efd::ColorA>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        if (lua_isuserdata(L, pos))
        {
            if (strcmp(SWIG_Lua_typename(L, pos), "efd::ColorA *") == 0) return true;
        }
        else if (lua_istable(L, pos))
        {
            if (lua_objlen(L, pos) == 4) return true;
        }

        return false;
    }

    /**
        Get an efd::ColorA from the Lua stack. This is represented as a table with 4 float
        values in Lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::ColorA at pos. The parameter is unchanged if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::ColorA& o_result)
    {
        if (!LuaTypecheck<efd::ColorA>(L, pos, "efd::ColorA *")) return false;

        if (lua_isuserdata(L, pos))
        {
            swig_module_info *module = SWIG_GetModule(L);
            swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::ColorA *");

            // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
            EE_ASSERT(typeInfo);

            efd::ColorA* tmp = 0;
            if (SWIG_Lua_ConvertPtr(L, pos, (void**)&tmp, typeInfo, 1) == SWIG_OK && tmp)
            {
                o_result.r = tmp->r;
                o_result.g = tmp->g;
                o_result.b = tmp->b;
                o_result.a = tmp->a;
                return true;
            }
        }
        else if (lua_istable(L, pos))
        {
            lua_rawgeti(L, pos, 1);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.r))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 2);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.g))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 3);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.b))
                return false;
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 4);
            if (!bapiLua::LuaTraits<efd::Float32>::FromLuaObject(L, -1, o_result.a))
                return false;
            lua_pop(L, 1);

            return true;
        }

        return false;
    }

    /**
        Push a Lua table containing the values for a ColoarA on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects (one table) pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::ColorA& i_data)
    {
        efd::ColorA* pResult = EE_NEW efd::ColorA(i_data.r, i_data.g, i_data.b, i_data.a);

        swig_module_info *module = SWIG_GetModule(L);
        swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::ColorA *");

        // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
        EE_ASSERT(typeInfo);

        SWIG_Lua_NewPointerObj(L, pResult, typeInfo, 1);

        return 1;
    }
};

/// Lua trait handler for type efd::ID128
template<>
struct LuaTraits<efd::ID128>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        return 0 != lua_isstring(L, pos);
    }

    /**
        Get an efd::ID128 from the Lua stack. This is represented as a string in Lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::ID128 at pos or the default ID128 if the position doesn't contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::ID128& o_result)
    {
        if (!LuaTypecheck<efd::ID128>(L, pos, "efd::ID128")) return false;

        const char *t = (const char*)lua_tostring(L, pos);
        if (efd::ParseHelper<efd::ID128>::FromString(t, o_result))
        {
            return true;
        }

        EE_LOG(efd::kLua, efd::ILogger::kERR0, ("Bad efd::ID128 format '%s'.", t));
        lua_pushfstring(L, "Bad efd::ID128 format '%s'.", t);
        return false;
    }

    /**
        Push a Lua string representing the ID128 value on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::ID128& i_data)
    {
        efd::utf8string str;
        EE_VERIFY(efd::ParseHelper<efd::ID128>::ToString(i_data, str));
        lua_pushstring(L, str.c_str());
        return 1;
    }
};

/// Lua trait handler for type efd::Matrix3
template<>
struct LuaTraits<efd::Matrix3>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        if (lua_isuserdata(L, pos))
        {
            if (strcmp(SWIG_Lua_typename(L, pos), "efd::Matrix3 *") == 0) return true;
        }
        else if (lua_istable(L, pos))
        {
            if (lua_objlen(L, pos) == 3) return true;
        }

        return false;
    }

    /**
        Get an efd::Matrix3 from the Lua stack. This is represented as either a Matrix3 object
        or a nested table with 3 rows of tables with 3 values in Lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::Matrix3 at pos or the default Matrix3 if the position doesn't
            contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::Matrix3& o_result)
    {
        if (!LuaTypecheck<efd::Matrix3>(L, pos, "efd::Matrix3")) return false;

        if (lua_isuserdata(L, pos))
        {
            swig_module_info *module = SWIG_GetModule(L);
            swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Matrix3 *");

            // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
            EE_ASSERT(typeInfo);

            efd::Matrix3* tmp = 0;
            if (SWIG_Lua_ConvertPtr(L, pos, (void**)&tmp, typeInfo, 1) == SWIG_OK && tmp)
            {
                o_result = *tmp;
                return true;
            }
        }
        // could be a table of point3s, or a table of 3 float values.
        else if (lua_istable(L, pos))
        {
            efd::Point3 row(0,0,0);

            lua_rawgeti(L, pos, 1);
            if (!LuaTraits<efd::Point3>::FromLuaObject(L, -1, row))
                return false;
            o_result.SetRow(0, row);
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 2);
            if (!LuaTraits<efd::Point3>::FromLuaObject(L, -1, row))
                return false;
            o_result.SetRow(1, row);
            lua_pop(L, 1);

            lua_rawgeti(L, pos, 3);
            if (!LuaTraits<efd::Point3>::FromLuaObject(L, -1, row))
                return false;
            o_result.SetRow(2, row);
            lua_pop(L, 1);
            return true;

            return true;
        }

        return false;
    }

    /**
        Push a table on to the Lua stack that contains 3 rows of point3 values.
        Each row is represented by another Lua table containing 3 values x, y, z.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects (one table) pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::Matrix3& i_data)
    {
        efd::Matrix3* pResult = EE_NEW efd::Matrix3(i_data);

        swig_module_info *module = SWIG_GetModule(L);
        swig_type_info *typeInfo = SWIG_TypeQueryModule(module, module, "efd::Matrix3 *");

        // If you hit this assert, the module wasn't loaded properly into the Lua runtime.
        EE_ASSERT(typeInfo);

        SWIG_Lua_NewPointerObj(L, pResult, typeInfo, 1);

        return 1;
    }
};

/// Lua trait handler for type efd::AssetID
template<>
struct LuaTraits<efd::AssetID>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        return 0 != lua_isstring(L, pos);
    }

    /**
        Get an efd::AssetID from the Lua stack. This is represented as a string in Lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd::AssetID at pos or the INVALID_ASSET_ID if the position doesn't
            contain one.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    // treats these like utf8strings until we need the other AssetID properties
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::AssetID& o_result)
    {
        if (!LuaTypecheck<efd::AssetID>(L, pos, "efd::AssetID")) return false;

        const char *t = (const char*)lua_tostring(L, pos);
        o_result = efd::AssetID(t);
        return true;
    }

    /**
        Push a string representing an AssetID on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::AssetID& i_data)
    {
        lua_pushstring(L, i_data.c_str());
        return 1;
    }
};

/// Lua trait handler for type efd::utf8char_t
template<>
struct LuaTraits<efd::utf8char_t>
{
    /**
        Determine if the specified object on the Lua stack matches our data type. Compatible
        types that can be converted to our type are considered matches.

        @param L Lua runtime state.
        @param pos position on the stack.
        @return True if the object is a compatible data type.
    */
    static efd::Bool IsType(lua_State* L, int pos)
    {
        return 0 != lua_isstring(L, pos);
    }

    /**
        Get an efd::utf8char_t from the Lua stack. This is represented as a string in Lua.

        @param L Lua runtime state.
        @param pos position on the stack.
        @param o_result efd:utf8char_t at pos.
        @return true if the conversion was successful.
        @note This does not pop the stack.
    */
    static efd::Bool FromLuaObject(lua_State* L, int pos, efd::utf8char_t& o_result)
    {
        if (!LuaTypecheck<efd::utf8char_t>(L, pos, "efd::utf8char_t")) return false;

        const char *t = (const char*)lua_tostring(L, pos);
        o_result = efd::utf8char_t::from_stream(t);
        return true;
    }

    /**
        Push a string representing an efd::utf8char_t on to the Lua stack.

        @param L Lua runtime state.
        @param i_data value to push on the stack.
        @return 1, the number of objects pushed on the stack.
    */
    static int ToLuaObject(lua_State* L, const efd::utf8char_t& i_data)
    {
        lua_pushstring(L, i_data.c_str());
        return 1;
    }
};


/**
    Get a list from the Lua stack and construct an efd::list from it.

    @param L Lua runtime state.
    @param pos position on the stack.
    @param o_result a populated list if one is found, or the empty list if not.
    @return true if the conversion was successful.
*/
template< typename T >
efd::Bool LuaList_ToEutList(lua_State* L, int pos, efd::list<T>& o_result)
{
    if (!lua_istable(L, pos))
    {
        efd::utf8string errMessage(efd::Formatted,
            "Type error in LuaList_ToEutList (arg %d), expected 'efd::list' got '%s'",
            pos,
            lua_typename(L, lua_type(L, pos)));
        EE_LOG(efd::kLua, efd::ILogger::kERR0, ("%s", errMessage.c_str()));
        lua_pushstring(L, errMessage.c_str());
        return false;
    }

    lua_pushnil(L);
    while (lua_next(L, pos))
    {
        // key at index -2, value at -1
        T value;
        if (!LuaTraits<T>::FromLuaObject(L, -1, value))
            return false;

        o_result.push_back(value);

        // remove the value, keep the key for the next iteration
        lua_pop(L, 1);
    }
    return true;
}

/**
    Push an efd::list onto the Lua stack. The list is created as a table populated
    with list values that is pushed onto the top of the stack.

    @param L Lua runtime state.
    @param i_list list to push on the stack.
    @return 1, the number of objects pushed on the Lua stack (one table).
*/
template< typename T >
int LuaList_FromEutList(lua_State* L, const efd::list<T>& i_list)
{
    // create a new table to hold our result
    lua_newtable(L);

    // insert all these items into the new table
    typename efd::list<T>::const_iterator it = i_list.begin();
    for (int i=1; it != i_list.end(); ++it, i++)
    {
        // push the index
        lua_pushnumber(L, i);

        // push the value
        LuaTraits<T>::ToLuaObject(L, *it);

        // set the table cell
        lua_rawset(L, -3);
    }

    return 1;
}

/**
    Get an efd::map from the Lua stack.

    @param L Lua runtime state.
    @param pos position on the stack.
    @param o_result populated map if one exists at pos, empty table if not.
    @return true if the conversion was successful.
*/
template< typename KEY, typename DATA >
efd::Bool LuaTable_ToEutMap(lua_State* L, int pos, efd::map<KEY,DATA>& o_result)
{
    if (!lua_istable(L, pos))
    {
        efd::utf8string errMessage(efd::Formatted,
            "Type error in LuaTable_ToEutMap (arg %d), expected 'efd::map' got '%s'",
            pos,
            lua_typename(L, lua_type(L, pos)));
        EE_LOG(efd::kLua, efd::ILogger::kERR0, ("%s", errMessage.c_str()));
        lua_pushstring(L, errMessage.c_str());
        return false;
    }

    lua_pushnil(L);
    while (lua_next(L, pos) != 0)
    {
        // value is at index -1, key is at index -2
        DATA value;
        KEY key;
        if (!LuaTraits<DATA>::FromLuaObject(L, -1, value) ||
            !LuaTraits<KEY>::FromLuaObject(L, -2, key))
        {
            return false;
        }

        // NOTE: this seemingly unnecessary typedef ensures this code works on both GCC and MSVC.
        typedef typename efd::map<KEY,DATA>::value_type value_type;
        o_result.insert(value_type(key, value));

        // remove the value but keep the key for the next iteration
        lua_pop(L, 1);
    }
    return true;
}

/**
    Push an efd::map onto the Lua stack. This creates a new table at the top of the
    stack that contains the key/value pairs from the efd::map.

    @param L Lua runtime state.
    @param m efd::map to push on the stack.
    @return 1, the number of objects pushed on the stack (one table).
*/
template< typename KEY, typename DATA >
int LuaTable_FromEutMap(lua_State* L, const efd::map<KEY,DATA>& m)
{
    lua_newtable(L);
    for (typename efd::map<KEY,DATA>::const_iterator it = m.begin(); it != m.end(); ++it)
    {
        // push the key
        LuaTraits<KEY>::ToLuaObject(L, it->first);

        // push the value
        LuaTraits<DATA>::ToLuaObject(L, it->second);

        // set the table cell
        lua_rawset(L, -3);
    }
    return 1;
}

template<typename T>
bool LuaTypecheck(
    lua_State* L,
    int pos,
    const char* strTypeName)
{
    if (!bapiLua::LuaTraits<T>::IsType(L, pos))
    {
        efd::utf8string typeName("");
        if (lua_isuserdata(L, pos))
        {
            const char* t = SWIG_Lua_typename(L, pos);
            if (t) typeName = t;
            else typeName = lua_typename(L, lua_type(L, pos));
        }
        else
        {
            typeName = lua_typename(L, lua_type(L, pos));
        }

        // Try to convert bad param to string for better error feedback
        const char* pszValue = lua_tostring(L,pos);

        efd::utf8string errMessage(efd::Formatted,
            "Type error in %s (arg %d), expected '%s' got '%s' value '%s'",
            __FUNCTION__, pos, strTypeName, typeName.c_str(),
            pszValue ? pszValue : "<unknown>");
        lua_pushstring(L, errMessage.c_str());

        return false;
    }

    return true;
}

} // end namespace bapi

#endif // EE_BAPILUA_H

