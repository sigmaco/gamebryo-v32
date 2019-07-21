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
#ifndef ECR_LUA_RUNTIME_INITIALIZER_H
#define ECR_LUA_RUNTIME_INITIALIZER_H

#include <ecr/ecrLua/ecrLuaLibType.h>
#include <ecr/AttachNifData.h>
#include <egfLua/ILuaPropertyHandler.h>
#include <egfLua/SWIGLuaRuntime.h>

// Forward decls
namespace egf
{
    class SchedulerLua;
}

namespace ecr
{
/**
    Initialize the ecr AttachedNifData Lua bindings by attaching them to the provided Lua runtime.

    @param L Lua state to register the Lua property handlers with.
*/
EE_ECR_LUA_ENTRY void lua_ecrInitializePropertyHandlers(lua_State* L);



/**
    Implementation of an egfLua/ILuaPropertyHandler for an ecr::AttachNifData object.
    This allows us to treat AttachedNifAsset properties as first-class objects in 
    Lua. The ecr::SceneGraphService should add an instance of this class to the 
    egfLua/SchedulerLua during initialization to make this property available to scripts.
 */
class EE_ECR_LUA_ENTRY AttachedNifAssetLuaPropHandler : public egf::ILuaPropertyHandler
{

public:

/**
    egf::LuaBehaviorDebugger UserDataInterpreter for this type. This enables toolbench to
    display the contents of this type in the Lua debugger locals panel.
*/
static bool IntepretLuaUserData(lua_State *l, int pos, efd::utf8string& value);


///
/// Get a property value for an entity.
///
virtual egf::PropertyResult GetProperty(
    egf::Entity* i_pEntity,
    egf::PropertyID i_pid,
    const efd::utf8string& i_key,
    lua_State *L,
    int& o_count);

///
/// Get the default property value for an entity.
///
virtual egf::PropertyResult GetDefaultProperty(
    egf::Entity* i_pEntity,
    egf::PropertyID i_pid,
    const efd::utf8string& i_key,
    lua_State *L,
    int& o_count);

///
/// Set the property value for an entity.
///
virtual egf::PropertyResult SetProperty(
    egf::Entity* i_pEntity,
    egf::PropertyID i_pid,
    const efd::utf8string& i_key,
    lua_State* L,
    int pos);

///
/// Get an instance of the ecr::AttachNifData from an efd::ParameterList.
///
virtual int GetParameter(
    efd::ParameterList* pParamList,
    efd::UInt32 paramIndex,
    lua_State* L);

///
/// Push an ecr::AttachNifData value into an efd::ParameterList.
///
virtual bool SetParameter(
    efd::ParameterList* pParamList,
    const efd::utf8string& name,
    lua_State* L,
    int pos);

    /// Default constructor. Instances of this class should only be created by calling
    /// the luaopen_ecr function defined in bapiCoreRuntime_*.cpp.
    AttachedNifAssetLuaPropHandler(swig_type_info* swigTypeInfo);

protected:

    ///
    /// Helper for getting an ecr::AttachNifData property value.
    ///
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
        ecr::AttachNifData* pData = EE_NEW ecr::AttachNifData();

        bool d = useDefaultValue;
        if (d)
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
            EE_DELETE pData;
        }

        return result;
    }

    swig_type_info* m_pSwigTypeInfo;

};

}

#endif // ECR_LUA_RUNTIME_INITIALIZER
