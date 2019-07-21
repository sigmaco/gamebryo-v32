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
#ifndef EE_SWIGPROPHANDLER_H
#define EE_SWIGPROPHANDLER_H

#include <egfLua/ILuaPropertyHandler.h>

namespace egf
{

/**
    An implementation of ILuaPropertyHandler that uses a Swig generated C++ class wrapper to
    implement the accessors. This can be used with SchedulerLua::RegisterPropertyHandler to
    implement BehaviorAPI.GetProperty and BehaviorAPI.SetProperty for types bound by Swig.

    The methods and types used by this template are defined as local statics in the generated
    Swig wrapper file. As a result, to use this class you must inject code into the generated
    Swig wrapper to create and register the correct instance.  For example, you could place the
    following code into your Swig .i file:

    @code
    // Include the file that binds the custom type
    %include "CustomType.h"

    // Add some code to the Swig wrapper to define a function to register an ILuaPropertyHandler
    // for the Swig-bound class.
    %{
    #include <egfLua/SchedulerLua.h>
    #include <egfLua/SwigPropHandler.h>

    SWIGEXPORT bool RegisterSwigPropertyHandlerForCustomType(egf::SchedulerLua* pSchedulerLua)
    {
        return pSchedulerLua->RegisterPropertyHandler(
            efd::kCLASSID_CustomType,
            EE_NEW egf::SwigPropHandler<CustomType, swig_type_info>(SWIGTYPE_p_CustomType));
    }
    %}
    @endcode

    When using the sample above then you would need to call the generated function at some point
    prior to the first BehaviorAPI.GetProperty or BehaviorAPI.SetProperty call for your type.

    The SwigTypeInfo template parameter must always be set to "swig_type_info". This is passed as a
    parameter only because "swig_type_info" is defined locally in the generated SWIG wrapper. This
    allows us to use the type in this header file without worrying about type matching.
*/
template<typename T, typename SwigTypeInfo>
class SwigPropHandler : public egf::ILuaPropertyHandler
{
public:
    SwigPropHandler(SwigTypeInfo* pSwigTypeInfo)
        : m_pSwigTypeInfo(pSwigTypeInfo)
    {
    }

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

        T* pBoundType = 0;
        if (!SWIG_IsOK(SWIG_ConvertPtr(L, pos, (void**)&pBoundType, m_pSwigTypeInfo, 0)))
        {
            lua_error(L);
            return egf::PropertyResult_TypeMismatch;
        }

        return SetPropertyHelper(i_pEntity, i_pid, i_key, *pBoundType);
    }

    virtual int GetParameter(
        efd::ParameterList* pParamList,
        efd::UInt32 paramIndex,
        lua_State* L)
    {
        T* pData = EE_EXTERNAL_NEW T();
        if (efd::pr_OK == pParamList->GetParameter(paramIndex, *pData))
        {
            SWIG_NewPointerObj(L, pData, m_pSwigTypeInfo, 1);
            return 1;
        }
        return 0;
    }

    virtual bool SetParameter(
        efd::ParameterList* pParamList,
        const efd::utf8string& name,
        lua_State* L,
        int pos)
    {
        EE_ASSERT(L != 0);

        T* pBoundType = 0;
        if (!SWIG_IsOK(SWIG_ConvertPtr(L, pos, (void**)&pBoundType, m_pSwigTypeInfo, 0)))
        {
            return false;
        }

        efd::SInt32 result;
        if (name.empty())
        {
            result = pParamList->AddParameter(*pBoundType);
        }
        else
        {
            result = pParamList->AddParameter(name, *pBoundType);
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

        egf::PropertyResult result;
        T* pData = EE_EXTERNAL_NEW T();

        if (useDefaultValue)
        {
            result = GetDefaultPropertyHelper(i_pEntity, i_pid, i_key, *pData);
        }
        else
        {
            result = GetPropertyHelper(i_pEntity, i_pid, i_key, *pData);
        }

        if (result == egf::PropertyResult_OK)
        {
            SWIG_NewPointerObj(L, pData, m_pSwigTypeInfo, 1);
            ++o_count;
        }
        else
        {
            EE_EXTERNAL_DELETE pData;
        }

        return result;
    }
    
    SwigTypeInfo* m_pSwigTypeInfo;
};

} // end namespace egf

#endif // EE_SWIGPROPHANDLER_H
