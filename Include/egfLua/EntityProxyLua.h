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
#ifndef EE_ENTITYPROXYLUA_H
#define EE_ENTITYPROXYLUA_H

#include <egf/EntityID.h>
#include <egfLua/egfLuaLibType.h>
#include <egf/IProperty.h>

// Forward decls
struct lua_State;
struct swig_module_info;
struct swig_type_info;

namespace efd
{
    class ParameterList;
}
namespace egf
{
    class PropertyDescriptor;
    class BehaviorDescriptor;
    class FlatModel;
    class Entity;
}

namespace egfLua
{
/**
    egfLua::Entity : A Lua proxy to a Game Framework egf::Entity instance.

    The egfLua::Entity is a proxy object that exposes specific entity attributes to the
    Lua runtime. The runtime will automatically create an instance of this proxy each time an
    Entity / EntityID is passed from C++ to Lua. 

    Each Entity's proxy is passed directly to each behavior as the 'self' parameter. 
    
	If you have a UInt64 value that represents an EntityID, you can obtain an Entity proxy
	object by calling Emergent:GetEntity(UInt64).  (BehaviorAPI.GetEntityById will also work.)

    Typemaps exist that will automatically convert a proxy instances to and from an EntityID,
    as needed, when making built-in API calls.

    The proxy defined the following Lua constants:
       - Entity.InvalidEntity -- Represents an invalid EntityID, used to determine whether a 
            specific proxy is valid. 

    The proxy defines the following Lua attributes:
       - ID  -- The EntityID as a UInt64 value.

    The proxy defines the following additional functions:
       - Clone -- Create another instance of this Proxy. This does not clone the underlying entity.
       - "==" -- Return true if this proxy represents the same entity as another proxy.
       - IsBound -- Returns true if this proxy is bound to a C++ entity. A proxy remains unbound
            until the Entity's OnCreate life cycle completes.
       - GetPrivateCatID  -- Get the private category ID for the entity.
       - ContainsProperty  -- Returns true if the Entity has the provided property.
       - ContainsPropertyWithKey -- Returns true if the Entity has a assocated array property
            with the provided key.
       - ContainsBehavior  -- Returns true if the Entity has the provided behavior.
       - ContainsMixin -- Returns true if the Entity has the provided Mixin model.
       - GetModelName -- Returns the name of the flat model used by this Entity.
       - GetPropertyNames -- Returns a table containing the names of all the Entity's properties.
       - ResetProperty - Reset an Entity property back to initial conditions.
       - EnterWorld -- Request the Entity enters the world.
       - ExitWorld -- Request the entity exits the world.
       - SendEvent -- Sends an event to the proxy entity
       - tostring -- Returns a pretty-printable string representing this Entity.
       - 

    In addition, each Entity's properties are exposed in Lua directly using __index and
    __newindex metamethods. This allows Entity properties to be read/written without having
    to make BehaviorAPI function calls. For example, if an entity has property 'Position'
    defined as a Point3 value, you can set/get it as follows:

    @code
        local position = self.Position    -- Entity['Position'] also works.
        print(tostring(position))         -- calls Point3's __tostring metamethod.

        local newPosition = Point3.Point3(1,2,3)
        self.Position = newPosition       -- Could also pass a table { 1, 2, 3 }
        print(tostring(entity.Position))  -- prints 'Point3(1, 2, 3)'
    @endcode

    Associative array properties are also bound using this proxy. Once again you can
    get/set/erase array entries without making BehaviorAPI function calls. For example, if
    an entity has a list property named 'Nicknames' defined as a list of strings, you can
    manipulate it as follows:

    @code
        local nicknames = self.Nicknames  -- 'table' with __index and __newindex methods.

        print(tostring(nicknames))        -- prints out something like 'Array Nicknames[10]'
        print(tostring(nicknames[0]))     -- prints the nickname a position 0.

        nicknames[0] = "Enlightened"      -- updates the array value at index 0.
        print(tostring(nicknames[0]))     -- prints 'Enlightened'

        local keys = nicknames:Keys()     -- Obtain all the keys for this associative array.

        for _, key in pairs(keys) do
            -- print out all the array values
            print("Nicknames["..key.."] = " .. tostring(nicknames[key]))
        end

        nicknames[0] = nil                -- Remove the key and value from index 0.
    @endcode
 */
class EE_EGF_LUA_ENTRY EntityProxy
{
public:
    /// @cond EMERGENT_INTERNAL

    EntityProxy();

    EntityProxy(efd::UInt64 id);

    EntityProxy(const EntityProxy& other);

    EntityProxy Clone() const;

    EntityProxy& operator=(const EntityProxy& rhs);

    bool operator==(const EntityProxy& rhs) const;

    /**
        Determine if this entity proxy is bound to an Entity pointer. If the EntityID for this
        proxy does not match a local entity at the time when the proxy is created then it will not
        be bound. Being unbound does not mean the proxy is invalid, this proxy might represent a
        valid remote entity or a valid local entity that is not fully created yet. However, many of
        the entity proxy methods only work on bound proxies.
    */
    bool IsBound() const;

    /**
        Get the category for sending behaviors to this entity. This will always match the value of
        the EntityID as returned by ID.
    */
    efd::Category GetPrivateCatID() const;

    /**
        Check if a given property exists on this entity.
        @note Only works on bound proxies, returns false if not bound.
        @param propName The name of the property to check
    */
    bool ContainsProperty(const char* propName) const;

    /**
        Check if a given associative property exists and has the given key set on this entity.
        @note Only works on bound proxies, returns false if not bound.
        @param propName The name of the associative property to check
        @param keyName The name of the key within the given property
    */
    bool ContainsPropertyWithKey(const char* propName, const char* keyName) const;

    /**
        Check if a given behavior exists on this entity.
        @note Only works on bound proxies, returns false if not bound.
        @param behaviorName The behavior to check for.
    */
    bool ContainsBehavior(const char* behaviorName) const;

    /**
        Tests if the given model is mixed into this entity.
        @note The final model is considered to be mixed into itself.
        @note Only works on bound proxies, returns false if not bound.
        @param mixinName The name of a model to check for
    */
    bool ContainsMixin(const char* mixinName) const;

    /**
        Get the name of the model used to create this entity. This will return NULL if the proxy
        is not bound.
    */
    const char* GetModelName() const;

    /**
        Populate a list with all of the property names that exist for this entity. If the proxy is
        not bound this will return an empty list.
        @param[out] o_names List populated with all property names for this entity
    */
    void GetPropertyNames(efd::list<efd::utf8string>& o_names) const;

    /**
        Reset the given property to it's default value. If the proxy is not bound this will return
        egf::PropertyResult_EntityNotFound.
        @param propName The name of a property to reset
        @return The result of calling Entity::ResetProperty.
    */
    egf::PropertyResult ResetProperty(const char* propName);

    /**
        Request that the entity enter the world.
        @note Only works on bound proxies.
        @return True if the proxy was bound and Entity::EnterWorld was called, false otherwise.
    */
    bool EnterWorld();

    /**
        Request that the entity exit the world.
        @note Only works on bound proxies.
        @return True if the proxy was bound and Entity::ExitWorld was called, false otherwise.
    */
    bool ExitWorld();

    /**
        A wrapper for calling BehaviorAPI.SendEvent to send an event to the entity being proxied.
        This can be called on unbound proxies as it only relies on the ID member being set.

        @param strBehavior The behavior to execute for this event
        @param args [Optional] The ParameterList of arguments to be included in the event message,
            or NULL if there are no arguments.
        @param strCallback [Optional] The behavior to launch for any reply message.
        @param delay [Optional] Game Time in seconds to wait before actually executing the event.
        @return True if a valid Event was generated and sent. A true result does not guarantee
            that the event will be successfully delivered or executed.
    */
    bool SendEvent(
        const char* strBehavior,
        efd::ParameterList* args = NULL,    /* if NULL, no arguments to the called behavior */
        const char* strCallback = NULL,     /* if NULL or empty, no callback */
        double delay = 0.0);

    /// Support for Lua tostring - pretty print an Entity value.
    const char* __str__() const;

    /**
        The EntityID for this entity.
    */
    efd::UInt64 ID;

#if !defined(SWIG)
    /**
        Attempt to interpret a userdata value as an EntityProxy and generate a user-friendly
        string representation suitable for display in the Lua debugger.

        @param L lua_State to examine.
        @param p Position on the Lua stack.
        @param value Resulting user-friendly string.
        @return true if the conversion was successful, false otherwise.
    */
    static bool InterpretLuaEntityProxy(lua_State* L, int p, efd::utf8string& value);

    /// Construct a proxy from and entity pointer.
    EntityProxy(egf::Entity* pEntity);

    /// Create a new EntityProxy object for pEntity and place it on the top of the stack.
    static bool CreateEntityProxy(lua_State* L, egf::Entity* pEntity);

    /**
        The following are used to provide metadata to this proxy to make the Lua-bound class more
        useful.

        Lua stack in:
        [-1] EntityProxy userdata object.
        
        Lua stack out:
        [-1] EntityProxy userdata object.
    */
    bool Bind(lua_State* L);

    /// Pointer to the entity being proxied, or NULL if that entity could not be bound.
    egf::Entity* m_pEntity;

    /// Cache the SWIG type info for the EntityProxy data type. This reduces the number of
    /// calls to SWIG_TypeEquiv by an order of magnitude.  This sets the global 
    /// egfLua::s_EntityProxySWIGTypeInfo, which is then available for other classes 
    /// and functions to also use.
    static swig_type_info* GetStaticEntityProxySWIGTypeInfo(lua_State* L);

#endif // !defined(SWIG)

    /// @endcond
};

/**
    InvalidEntity constant.
*/
const EntityProxy InvalidEntity;

} // end namespace egfLua



#if !defined(SWIG)

namespace egf
{
/*
    Convert a Lua object from a given location on the stack into a egfLua::EntityProxy object.

    @param L Lua runtime state.
    @param pos Position on the stack.
    @return A egfLua::EntityProxy pointer, or NULL if the specified Lua object is the wrong type.
*/
EE_EGF_LUA_ENTRY egfLua::EntityProxy* lua_toEntityProxy(lua_State* L, int pos);

/*
    Check if the Lua object at the given stack location is a egfLua::EntityProxy instance.

    @param L Lua runtime state.
    @param pos The index on the Lua stack.
    @return True if the object at pos is a egfLua::EntityProxy, false otherwise.

*/
EE_EGF_LUA_ENTRY bool lua_checkEntityProxy(lua_State* L, int pos);

} // end namespace egf

#endif // !defined(SWIG)


#endif // EE_ENTITYPROXYLUA_H
