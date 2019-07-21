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
#ifndef EE_BAPIENTITY_H
#define EE_BAPIENTITY_H

#include <efd/StdContainers.h>
#include <egf/BehaviorAPI.h>
#include <egf/egfLibType.h>
#include <egf/EntityManager.h>


// NOTE: This is a SWIG parsed file.  All methods listed in this file will have script wrappers
// generated.
//
// A note on argument types:
//
// Given any type the SWIG generated bindings will make certain assumptions about whether the
// parameter is an input argument, and output argument, or an input-output argument.  Given
// a type T, it will be treated as follows:
//
//    |---------------|---------------|------------------------------------------------------
//    | typename:     | treated as:   | notes:
//    |---------------|---------------|------------------------------------------------------
//    | T             | Input         |
//    | const T&      | Input         |
//    | const T*      | Input         | Pointer must NOT be NULL
//    | T*            | Output        | Pointer must NOT be NULL
//    | T&            | Input-Output  |
//    |---------------|---------------|------------------------------------------------------
//
// The one exception to the argument type rules above is efd::ParameterList.  efd::ParameterList*
// is treated as a basic type for the purpose of these rules, not efd::ParameterList itself.  For
// example, this means that "efd::ParameterList*" is treated as a plain ParameterList Input argument
// and "efd::ParameterList*&" is treated as an in-out efd::ParameterList parameter.  One additional
// special case, for convenance "efd::ParameterList&" is also treated as an in-out parameter.

namespace BehaviorAPI
{

/**
    Returns the EntityID of the entity currently executing a scripted behavior.

    @return EntityID The entity on which a behavior is currently executing.
*/
EE_EGF_ENTRY egf::EntityID GetExecutingEntityId();

/**
    Returns the EventID of the currently executing behavior.

    @return The event ID of the currently executing behavior.
*/
EE_EGF_ENTRY egf::EventID GetCurrentEventID();

/**
    Returns the EntityID of the entity which sent the currently running behavior.

    @return EntityID The entity on which a behavior is currently executing.
*/
EE_EGF_ENTRY egf::EntityID GetReturnEntityId();

/**
    A return value used by many behavior APIs.

    Many behavior API methods operate on a specific entity by passing in its EntityID.  This
    return type allows scripts to distinguish between the case where that entity cannot be found
    and other cases where it is a valid entity but the method fails for other reasons.  We bind
    these values into script as constants so script authors can directly use them.  For example:

    @code
    python:
        if BehaviorAPI.IsKindOf(BehaviorAPI.GetExecutingEntityId(), "SomeModel") == ec_Yes:
            # Some code here

    lua:
        if BehaviorAPI.IsKindOf(BehaviorAPI.GetExecutingEntityId(), "SomeModel") == ec_Yes then
            -- Some code here
        end
    @endcode
*/
enum EntityCheck
{
    ec_Yes,
    ec_No,
    ec_EntityNotFound
};

/**
    Tests if the entity "is-a" specific model type.

    This means that the entity either is that model type or mixes in that model type.

    @note This method differs from HasMixin in that it will return ec_Yes if modelName is equal to
        the result of GetModelName(entity) whereas HasMixin would return ec_No in that case.

    @param[in] entity EntityID of the Entity to be tested
    @param[in] modelName Name of the model to test
    @return EntityCheck enum value
*/
EE_EGF_ENTRY EntityCheck IsKindOf(egf::EntityID entity, const efd::utf8string& modelName);

/**
    Tests if the entity mixes in a particular model.

    @note For this method a model is not considered to be a mix-in of itself.  The IsKindOf
    method is equivalent to "HasMixin(id, foo) || GetModelName(id) == foo".

    @param[in] entity EntityID of the Entity to be tested
    @param[in] mixinModelName Name of the model to test
    @return EntityCheck enum value
*/
EE_EGF_ENTRY EntityCheck HasMixin(egf::EntityID entity, const efd::utf8string& mixinModelName);

/**
    Tests if the entity has a particular behavior.

    @param[in] entity EntityID of the Entity to be tested
    @param[in] behaviorName Name of the behavior to test
    @return EntityCheck enum value
*/
EE_EGF_ENTRY EntityCheck HasBehavior(egf::EntityID entity, const efd::utf8string& behaviorName);

/**
    Tests if the entity has a particular property.

    @param[in] entity EntityID of the Entity to be tested
    @param[in] propertyName Name of the property to test
    @return EntityCheck enum value
*/
EE_EGF_ENTRY EntityCheck HasProperty(egf::EntityID entity, const efd::utf8string& propertyName);

/**
Tests if an associative property has a particular key.

@param[in] entity EntityID of the Entity to be tested
@param[in] propertyName Name of the property to test
@param[in] propertyKey Key of the property to test
@return EntityCheck enum value
*/
EE_EGF_ENTRY EntityCheck HasPropertyKey(
    egf::EntityID entity,
    const efd::utf8string& propertyName,
    const efd::utf8string& propertyKey);

/**
    Get a list of all the models that are mixed into the given entity.

    @param[in] entity EntityID of the Entity to be tested
    @param[out] OutValue a list of mix-ins found in this Entity
    @return EntityCheck enum value
*/
EE_EGF_ENTRY EntityCheck FindMixins(egf::EntityID entity, efd::list<efd::utf8string>* OutValue);

/**
    Gets a list of mix-in names based on a filter string.

    Only those mix-in models with a name that contains the filter string will be returned.  The
    filter string is a simple substring, and does not support any wildcard matching.

    @param[in] entity EntityID of the Entity to be tested
    @param[in] filter Search criteria string
    @param[out] OutValue List of matching mix-ins found in this Entity
    @return EntityCheck enum value
*/
EE_EGF_ENTRY EntityCheck FindMatchingMixins(
    egf::EntityID entity,
    const efd::utf8string& filter,
    efd::list<efd::utf8string>* OutValue);

/**
    Gets a list of all behaviors for the given entity, including those that are mixed-in from
    another model - in other words, not just the behaviors this model overrides.

    @param[in] entity EntityID of the Entity to be tested
    @param[out] OutValue a list of behaviors found in this Entity
    @return EntityCheck enum value
*/
EE_EGF_ENTRY EntityCheck FindBehaviors(egf::EntityID entity, efd::list<efd::utf8string>* OutValue);

/**
    Gets a list of behavior names based on a filter string.

    Only those behaviors with a name that contains the filter string will be returned.  The filter
    string is a simple substring and does not support any wildcard matching.

    @param[in] entity EntityID of the Entity to be tested
    @param[in] filter Search criteria string
    @param[out] OutValue List of matching behaviors found in this Entity
    @return EntityCheck enum value
*/
EE_EGF_ENTRY EntityCheck FindMatchingBehaviors(
    egf::EntityID entity,
    const efd::utf8string& filter,
    efd::list<efd::utf8string>* OutValue);

/**
    Gets a list of Properties.

    @param[in] entity EntityID of the Entity to be tested
    @param[out] OutValue a list of properties found in this Entity
    @return EntityCheck enum value
*/
EE_EGF_ENTRY EntityCheck FindProperties(egf::EntityID entity, efd::list<efd::utf8string>* OutValue);

/**
    Gets a list of property names matching a filter string.

    Only those properties with a name that contains the filter string will be returned.  The
    filter string is a simple substring, and does not support any wildcard matching.

    @param[in] entity EntityID of the Entity to be tested
    @param[in] filter Search criteria string
    @param[out] OutValue List of matching properties found in this Entity
    @return EntityCheck enum value
*/
EE_EGF_ENTRY EntityCheck FindMatchingProperties(
    egf::EntityID entity,
    const efd::utf8string& filter,
    efd::list<efd::utf8string>* OutValue);

/**
    Returns a list of all in-use key names for a given map-style property.

    This should only be used when you know there will only be a small number of keys, to enumerate
    potentially large map-style properties it is recommended that GetNextPropertyKey be used.

    @param[in] entity EntityID of the Entity to be tested
    @param[in] propertyName : the name of a map-style property
    @param[out] OutValue List of property key names for the map in this Entity
    @return EntityCheck ec_Yes if the entity exists and has a map-style property with the
        given name.  ec_No if the entity exists but has no valid property.  ec_EntityNotFound
        if the entity cannot be found.
*/
EE_EGF_ENTRY EntityCheck FindPropertyKeys(
    egf::EntityID entity,
    const efd::utf8string& propertyName,
    efd::list<efd::utf8string>* OutValue);

/**
    GetNextPropertyKey allows the enumeration of key values in a map-style property.

    Use an empty string on the first call to return the first key, then use the previous key value
    in future calls to return the next key.  If no more keys exists, if the entity is not found,
    or if the entity has no map-style property with the given name then an empty string will be
    returned.

    @param[in] entity EntityID of the Entity to be tested
    @param[in] propertyName name of the map-style property
    @param[in] previousKey The previous key, or an empty string to find the first key.
    @return utf8string The name of the next key, or an empty string on errors or when finished.
*/
EE_EGF_ENTRY efd::utf8string GetNextPropertyKey(
    egf::EntityID entity,
    const efd::utf8string& propertyName,
    const efd::utf8string& previousKey);

/**
    Get the model name for an entity.

    All Entities are instantiations of a single final model, and all models have a unique name as
    specified in the Entity Modeling Tool data.

    @param[in] entity EntityID of the entity to get the model name from
    @return The model name, or an empty string if the entity is not found
*/
EE_EGF_ENTRY const efd::utf8string& GetModelName(egf::EntityID entity);

/**
    Get the originating model for a particular behavior.

    When models are mixed in but not overridden, the origin will be the model containing the
    implementation.  This information is typically only useful for debugging.

    @param[in] entity EntityID of the entity of interest
    @param[in] behaviorName Name of the behavior to get the source of
    @return The model name where the specified behavior is implemented
*/
EE_EGF_ENTRY const efd::utf8string& GetBehaviorSource(
    egf::EntityID entity,
    const efd::utf8string& behaviorName);

/**
    Get the originating model for a particular property.

    @param[in] entity EntityID of the entity of interest
    @param[in] propertyName Name of the property to get the source of
    @return The model name where the property was defined
*/
EE_EGF_ENTRY const efd::utf8string& GetPropertySource(
    egf::EntityID entity,
    const efd::utf8string& propertyName);

/**
    Reset a property to its default value by property name.

    The default value is the value specified in the flat model, and does not reflect any overrides
    specified in the block file or runtime changes to the property.  This works for both scalar
    and map-style properties; when resetting a map-style property, all keys not present in the
    default value will be removed, and any remaining keys will have their values returned to the
    default value.

    @param[in] entity EntityID of the entity of interest
    @param[in] propertyName Name of the property to get reset
    @return True if an override of the property existed and was reset, false otherwise.
*/
EE_EGF_ENTRY bool ResetProperty(
    egf::EntityID entity,
    const efd::utf8string& propertyName);

/**
    Removes a value, by key, from an associative array property.

    @param[in] entity Entity ID to of the entity of interest
    @param[in] propertyName Name of the property to remove a value from
    @param[in] key The key of the value to remove
    @return True if the entity, property, and key were found and the value was removed
*/
EE_EGF_ENTRY bool RemovePropertyValue(
    egf::EntityID entity,
    const efd::utf8string& propertyName,
    const efd::utf8string& key);


///////////////////////////////////////////////////////////////////////////////
// Entity discovery:

/**
    Get a list of all the EntityIDs.

    @note Calling this function would be extremely expensive for a typical application with a
        large number of entities.  You should typically use one of the more restrictive entity
        finding methods such as FindEntitiesByBaseModel or FindEntitiesByModel.  This method can
        be useful for debugging.

    @param[out] OutValue list of EntityIDs found
    @return this function always returns 1
*/
EE_EGF_ENTRY efd::UInt32 FindAllEntities(efd::list<egf::EntityID>* OutValue);

/**
    Get a list of all entities that use the specified model as their final model.

    Only entities of that exact type are returned.  Even presets of a model are considered to be
    different final models.

    @note This method differs from FindEntitiesByBaseModel which also includes entities that
        mix-in the specified model.

    @param[in] modelName Name of the model to search for
    @param[out] OutValue list of EntityIDs found
    @return this function always returns 1
*/
EE_EGF_ENTRY efd::UInt32 FindEntitiesByModel(
    const efd::utf8string& modelName,
    efd::list<egf::EntityID>* OutValue);

/**
    Get a list of all entities that either mix-in the specified model or use the specified model
    as their final model.

    @note This method differs from FindEntitiesByModel which only finds entities which use the
        specified model as their final model.

    @param[in] modelName Name of the model to search for
    @param[out] OutValue list of EntityIDs found
    @return this function always returns 1
*/
EE_EGF_ENTRY efd::UInt32 FindEntitiesByBaseModel(
    const efd::utf8string& modelName,
    efd::list<egf::EntityID>* OutValue);

/**
    Find the Entity instantiated using the given DataID.

    A unique DataID is automatically assigned to each entity in a block by the World Builder in
    Toolbench.  Only entities that are the result of loading a block file will have a DataID.  The
    DataID is a 128bit guid.
*/
EE_EGF_ENTRY egf::EntityID FindEntityByDataID(const efd::ID128& dataId);

/**
    This method finds all behaviors implemented on a given model.

    The requested model will be loaded, if needed.  Each behavior name is returned in the format
    "ModelName:BehaviorName", where the ModelName describes the source model in the mix-in
    hierarchy for the specified behavior.  So, for example, if the model "Final" mixes in a model
    called "Base", which implements a behavior called "DoSomething", you would get an entry called
    "Base:DoSomething".  If you want to invoke one of the resulting behaviors, you will normally
    want to strip off this model name and use just the behavior name, in order to invoke the most
    derived behavior.

    @param[in] modelName Name of the model to search
    @param[out] OutValue List of behaviors
    @return boolean true for success
*/
EE_EGF_ENTRY bool FindAllBehaviors(
    const efd::utf8string& modelName,
    efd::list<efd::utf8string>* OutValue);

///////////////////////////////////////////////////////////////////////////////
// Category discovery / management:

/**
    Subscribe this entity to receive behavior requests on the specified category.

    Multiple entities can subscribe to the same category.  Behaviors can be invoked on all
    entities subscribed to the category by using the specified category as the entityID parameter
    to SendEvent.

    @param[in] entityID EntityID of the active Entity
    @param[in] catID CategoryID to subscribe to
    @return bool false if the entity is unknown to the scheduler
*/
EE_EGF_ENTRY bool SubscribeToCategory(egf::EntityID entityID, efd::Category catID);

/**
    Unsubscribe this entity from behavior requests on the specified category.

    @param[in] entityID EntityID of the active Entity
    @param[in] catID CategoryID to unsubscribe
    @return bool false if the entity is unknown to the scheduler
*/
EE_EGF_ENTRY bool UnsubscribeToCategory(egf::EntityID entityID, efd::Category catID);


/**
    Begin the creation of a new entity and add it to the local simulator once created. The process
    of creating a new entity is asynchronous. This call will immediately return the future entity's
    ID but that entity may not exist yet so it is not generally valid to immediate use the
    resulting value in other built-in API calls.

    The caller can be notified when the entity is ready by providing the name of a callback
    behavior. This behavior will be called once the entity is fully available; it should
    expect a data stream with two values: the original EntityID returned by this function
    and a boolean indicating whether the creation was successful.

    @note You can control whether or not the created entity automatically enters the world
    following the completion of its initial lifecycle behaviors by adding a boolean parameter named
    "AutoEnterWorld" to the pCreationParams parameter list.

    @note Other options for creating an entity include BehaviorAPI.SpawnEntity, which requires the
    flat model to be preloaded, and BehaviorAPI.CreateEntityAndWait which blocks until all creation
    lifecycles complete on the new entity.

    @param[in] modelName Name of the flat model to create an instance of
    @param[in] pCreationParams An optional parameter list passed to OnCreate behavior.
    @param[in] callbackBehavior The optional name of a callback behavior that is invoked once
        the entity is created.
    @param[in] pInitialProperties An optional parameter list containing property values that are
        transfered to the created entity before it has OnCreate called.
    @return EntityID of the Entity that will be created.
*/
EE_EGF_ENTRY egf::EntityID CreateEntity(
    const efd::utf8string& modelName,
    efd::ParameterList* pCreationParams = 0,
    const efd::utf8string& callbackBehavior = efd::utf8string::NullString(),
    efd::ParameterList* pInitialProperties = 0);

/**
    Immediately create a new entity and add it to the local simulator. In order for this operation
    to work the flat model specified must have been previously loaded. The returned entity will be
    fully allocated with all properties initialized to the flat model default values but it will
    not yet have run it's OnCreate behavior. You may immediately begin setting properties on the
    resulting entity, but keep in mind that some of these properties could be overridden once the
    OnCreate behavior runs on the entity. For the same reason be careful immediately reading
    properties from the entity as the default values may be overridden. Finally, keep in mind that
    the loading of assets such the NIF, KFM or sound data will still be performed asynchronously so
    you cannot immediately pass the resulting entity to built-in API methods that require this data
    already be loaded.

    @note Flat models can be preloaded by calling egf::FlatModelManager::PreloadModel. If a block
    will load entities with behaviors that call SpawnEntity then the required models should be
    preloaded before the block is loaded.

    @note You can control whether or not the created entity automatically enters the world
    following the completion of its initial life cycle behaviors by adding a boolean parameter
    named "AutoEnterWorld" to the pCreationParams parameter list. However, any calls to EnterWorld
    or ExitWorld made immediately after SpawnEntity will override this setting.

    @note Other options for creating an entity include BehaviorAPI.CreateEntity and
    BehaviorAPI.CreateEntityAndWait. Those other options do not require pre-loading of the flat
    model.

    @note If a call is made to SpawnEntity for a flat model that is not already loaded the call to
    SpawnEntity will fail and no entity will be created. However SpawnEntity will attempt to cache
    the specified flat model for furture use when this happens. As a result, failure to precache
    the required flat models may only cause the first few spawn attempts to fail, which could go
    unnoticed depending on the application and entity in question. Be sure to check your log output
    for error messages related to entity spawning to ensure the proper data is being precached.

    @param[in] modelName Name of the flat model to create an instance of. This model must already
        be completely loaded prior to making this call.
    @param[in] pCreationParams An optional parameter list passed to OnCreate behavior.
    @return EntityID of the Entity that will be created, or 0 if the specified flat model is not
        already loaded.
*/
EE_EGF_ENTRY egf::EntityID SpawnEntity(
    const efd::utf8string& modelName,
    efd::ParameterList* pCreationParams = 0);

/**
    Request the destruction of an entity and invocation of an OnDestroy behavior, if it exists.
    Destroying an entity will invoke the OnDestroy behavior if present, and when that behavior
    completes (or if its not found), will then remove the entity.

    @param[in] id EntityID to destroy
    @return boolean true for success
*/
EE_EGF_ENTRY bool DestroyEntity(egf::EntityID id);

/**
    Request the specified entity enter the world. This will cause the OnEnterWorld behavior, if it
    exists to be called.

    @param[in] id EntityID to ask to enter the world
    @return boolean true for success
*/
EE_EGF_ENTRY bool EntityEnterWorld(egf::EntityID id);

/**
    Request the specified entity exit the world. This will cause the OnExitWorld behavior, if it
    exists to be called.

    @param[in] id EntityID to ask to exit the world
    @return boolean true for success
*/
EE_EGF_ENTRY bool EntityExitWorld(egf::EntityID id);

/**
    Check to see if the specified entity is in the world.

    @param[in] id EntityID to ask if it is in the world
    @return boolean true if entity exists and is in the world, false otherwise.
*/
EE_EGF_ENTRY bool IsEntityInWorld(egf::EntityID id);

/**
    Increments a UInt32 property.

    @param[in] id EntityID of the Entity the property belongs to
    @param[in] propName Name of the property to increment
    @return efd::UInt32 value is the incremented property value, a return value of 0 indicates
        a failure
*/
EE_EGF_ENTRY efd::UInt32 IncrementProperty(
    egf::EntityID id,
    const efd::utf8string& propName);

/**
    Decrements a UInt32 property by one and returns the new value.

    @param[in] id EntityID of the Entity the property belongs to
    @param[in] propName Name of the property to decrement
    @return efd::UInt32 value is the decremented property value, a return value of 0 may
        indicate a failure
*/
EE_EGF_ENTRY efd::UInt32 DecrementProperty(egf::EntityID id, const efd::utf8string& propName);

/**
    Changes a UInt32 property value, returning the old value.

    @param[in] id EntityID of the Entity the property belongs to
    @param[in] propName Name of the property to change
    @param[in] newValue New property value
    @return efd::UInt32 value equal to the old value of this property, a return of 0 may
        indicate a failure
*/
EE_EGF_ENTRY efd::UInt32 SwapProperty(
    egf::EntityID id,
    const efd::utf8string& propName,
    efd::UInt32 newValue);

} // end namespace BehaviorAPI

#endif // !defined(EE_BAPIENTITY_H)
