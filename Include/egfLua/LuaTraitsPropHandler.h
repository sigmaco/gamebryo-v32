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
#ifndef EE_LUATRAITSPROPHANDLER_H
#define EE_LUATRAITSPROPHANDLER_H

#include <egfLua/ILuaPropertyHandler.h>
#include <egfLua/bapiLua.h>

// including the most commonly used serializer methods here, failure to include the correct
// specialization of SerializeObject before using LuaTraitsPropHandler can lead to confusing
// compiler errors such as "error C2039: 'Serialize' : is not a member of 'YourTypeName'"
#include <efd/SerializeEfdHelpers.h>

namespace egf
{

/**
    An implementation of ILuaPropertyHandler that uses bapiLua::LuaTraits to implement the
    accessors.  This can be used with SchedulerLua::RegisterPropertyHandler.
 */
template<typename T>
class LuaTraitsPropHandler : public ILuaPropertyHandler
{
public:
    virtual egf::PropertyResult GetProperty(
        egf::Entity* i_pEntity,
        egf::PropertyID i_pid,
        const efd::utf8string& i_key,
        lua_State *L,
        int& o_count)
    {
        return GetPropHelper<false>(i_pEntity, i_pid, i_key, L, o_count);
    }

    virtual egf::PropertyResult GetDefaultProperty(
        egf::Entity* i_pEntity,
        egf::PropertyID i_pid,
        const efd::utf8string& i_key,
        lua_State *L,
        int& o_count)
    {
        return GetPropHelper<true>(i_pEntity, i_pid, i_key, L, o_count);
    }

    virtual egf::PropertyResult SetProperty(
        egf::Entity* i_pEntity,
        egf::PropertyID i_pid,
        const efd::utf8string& i_key,
        lua_State* L,
        int pos)
    {
        EE_ASSERT(L != 0);

        T val;
        if (!bapiLua::LuaTraits<T>::FromLuaObject(L, pos, val))
        {
            lua_error(L);
            return PropertyResult_TypeMismatch;
        }

        return SetPropertyHelper(i_pEntity, i_pid, i_key, val);
    }

    virtual int GetParameter(
        efd::ParameterList* pParamList,
        efd::UInt32 paramIndex,
        lua_State* L)
    {
        T val;
        if (efd::pr_OK == pParamList->GetParameter(paramIndex, val))
        {
            return bapiLua::LuaTraits<T>::ToLuaObject(L, val);
        }
        return 0;
    }

    virtual bool SetParameter(
        efd::ParameterList* pParamList,
        const efd::utf8string& name,
        lua_State* L,
        int pos)
    {
        T val;
        if (!bapiLua::LuaTraits<T>::FromLuaObject(L, pos, val))
        {
            return false;
        }

        efd::SInt32 result;
        if (name.empty())
        {
            result = pParamList->AddParameter(val);
        }
        else
        {
            result = pParamList->AddParameter(name, val);
        }
        return (-1 != result);
    }

protected:
    template<bool useDefaultValue>
    inline egf::PropertyResult GetPropHelper(
        egf::Entity* i_pEntity,
        egf::PropertyID i_pid,
        const efd::utf8string& i_key,
        lua_State *L,
        int& o_count)
    {
        EE_ASSERT(L != 0);
        o_count = 0;

        PropertyResult result;
        T resultVal;

        if (useDefaultValue)
        {
            result = GetDefaultPropertyHelper(i_pEntity, i_pid, i_key, resultVal);
        }
        else
        {
            result = GetPropertyHelper(i_pEntity, i_pid, i_key, resultVal);
        }

        if (result == PropertyResult_OK)
        {
            // Convert the value to a Lua object
            o_count = bapiLua::LuaTraits<T>::ToLuaObject(L, resultVal);
        }

        return result;
    }
};

} // end namespace egf

#endif // EE_LUATRAITSPROPHANDLER_H
