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
#ifndef EE_ILUAPROPERTYHANDLER_H
#define EE_ILUAPROPERTYHANDLER_H

#include <egf/EntityTypes.h>
#include <egf/IProperty.h>
#include <egf/Entity.h>


struct lua_State;

namespace efd
{
    class ParameterList;
}

namespace egf
{

/**
    Interface with methods for getting or setting a property from Lua. Instances of this
    interface are registered with SchedulerLua::RegisterPropertyHandler for each supported property
    data type. Then the lua_GetProperty and lua_SetProperty methods will find the right instance
    and use these methods to read or write the property to or from the Lua stack.
*/
class ILuaPropertyHandler : public efd::RefCount
{
public:
    /**
        Get the specified property from the entity and push the value onto the Lua stack.

        @param i_pEntity The entity on which to read the property
        @param i_pid The property to read
        @param i_key If the property to read is associative then this is the key that should be
            read. This will be an empty string if the property to read is scalar.
        @param L The lua state.
        @param o_count The number of Lua objects pushed into the stack as a result of your call.
            This will normally be 1 if the method is successful and 0 otherwise.
        @return The PropertyResult value as returned by Entity::Get*PropertyValue.
    */
    virtual PropertyResult GetProperty(
        Entity* i_pEntity,
        PropertyID i_pid,
        const efd::utf8string& i_key,
        lua_State *L,
        int& o_count) = 0;

    /**
        Get the default value of the specified property from the entity and push the value onto the
        Lua stack.

        @param i_pEntity The entity on which to read the property
        @param i_pid The property to read
        @param i_key If the property to read is associative then this is the key that should be
            read. This will be an empty string if the property to read is scalar.
        @param L The lua state.
        @param o_count The number of Lua objects pushed into the stack as a result of your call.
            This will normally be 1 if the method is successful and 0 otherwise.
        @return The PropertyResult value as returned by Entity::Get*PropertyValue.
    */
    virtual PropertyResult GetDefaultProperty(
        Entity* i_pEntity,
        PropertyID i_pid,
        const efd::utf8string& i_key,
        lua_State *L,
        int& o_count) = 0;

    /**
        Read the specified property from the entity and push the value onto the Lua stack.

        @param i_pEntity The entity on which to set the property
        @param i_pid The property to set
        @param i_key If the property to set is associative then this is the key that should be
            set. This will be an empty string if the property to set is scalar.
        @param L The lua state.
        @param pos The index on the Lua stack where the property value is location
        @return The PropertyResult value as returned by Entity::SetPropertyValue.
    */
    virtual PropertyResult SetProperty(
        Entity* i_pEntity,
        PropertyID i_pid,
        const efd::utf8string& i_key,
        lua_State* L,
        int pos) = 0;

    /**
        Used for getting a parameter out of a ParameterList. On success this should push the
        resulting object(s) into the Lua stack. On Error the Lua stack should not be altered as the
        calling function will handle returning an appropriate error value.

        @param pParamList the parameter list from which to fetch an argument
        @param paramIndex The index within the parameter list to be fetched
        @param L The lua state.
        @return The number of objects pushed onto to the stack, which should be zero if an error
            occured.
    */
    virtual int GetParameter(
        efd::ParameterList* pParamList,
        efd::UInt32 paramIndex,
        lua_State* L) = 0;

    /**
        Used for adding a parameter to a ParameterList. You can optionally pass in a name or use
        an empty string to add an unnamed parameter. The value for the parameter is read from the
        given position on the Lua stack.

        @param pParamList the parameter list to add the argument to
        @param name The name of the parameter, or empty string to add an unnamed parameter
        @param L The lua state.
        @param pos The index on the Lua stack where the parameter value is location
        @return True for success, false for failure.
    */
    virtual bool SetParameter(
        efd::ParameterList* pParamList,
        const efd::utf8string& name,
        lua_State* L,
        int pos) = 0;

protected:
    /**
        Convenience function for derived classes to access property values. All ILuaPropertyHandler
        derived classes will need to read some sort of property value from the entity, so this
        helper function does that work for the caller.

        @param i_pEntity The entity on which to read the property
        @param i_pid The property to read
        @param i_key If the property to read is associative then this is the key that should be
            read. This will be an empty string if the property to read is scalar.
        @param o_result The value of the property.
        @return The PropertyResult value as returned by Entity::GetPropertyValue.
    */
    template<typename T>
    inline egf::PropertyResult GetPropertyHelper(
        egf::Entity* i_pEntity,
        egf::PropertyID i_pid,
        const efd::utf8string& i_key,
        T& o_result);

    /**
        Convenience function for derived classes to access default property values. All
        ILuaPropertyHandler derived classes will need to read some sort of property value from the
        entity, so this helper function does that work for the caller.

        @param i_pEntity The entity on which to read the default property
        @param i_pid The property to read
        @param i_key If the property to read is associative then this is the key that should be
            read. This will be an empty string if the property to read is scalar.
        @param o_result The value of the property.
        @return The PropertyResult value as returned by Entity::GetDefaultPropertyValue.
    */
    template<typename T>
    inline egf::PropertyResult GetDefaultPropertyHelper(
        egf::Entity* i_pEntity,
        egf::PropertyID i_pid,
        const efd::utf8string& i_key,
        T& o_result);

    /**
        Convenience function for derived classes to set property values. All ILuaPropertyHandler
        derived classes will need to set some sort of property value on the entity, so this
        helper function does that work for the caller.

        @param i_pEntity The entity on which to set the property
        @param i_pid The property to set
        @param i_key If the property to set is associative then this is the key that should be
            set. This will be an empty string if the property to set is scalar.
        @param i_value The value to set
        @return The PropertyResult value as returned by Entity::SetPropertyValue.
    */
    template<typename T>
    inline egf::PropertyResult SetPropertyHelper(
        egf::Entity* i_pEntity,
        egf::PropertyID i_pid,
        const efd::utf8string& i_key,
        const T& i_value);
};

/// SmartPointer for the ILuaPropertyHandler class
typedef efd::SmartPointer<ILuaPropertyHandler> ILuaPropertyHandlerPtr;

} // end namespace egf

#include <egfLua/ILuaPropertyHandler.inl>

#endif // EE_ILUAPROPERTYHANDLER_H
