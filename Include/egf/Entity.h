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
#ifndef EE_ENTITY_H
#define EE_ENTITY_H

#include <efd/UniversalTypes.h>
#include <egf/IProperty.h>
#include <egf/IBuiltinModel.h>
#include <egf/FlatModel.h>
#include <efd/utf8string.h>
#include <egf/EntityID.h>
#include <egf/IPropertyType.h>
#include <egf/PropertyDescriptor.h>
#include <egf/egfLibType.h>
#include <efd/RefCount.h>
#include <efd/MessageHandlerBase.h>
#include <egf/EventMessage.h>

#include <efdNetwork/NetCategory.h>
#include <efd/ParameterList.h>
#include <egf/BehaviorDescriptor.h>
#include <efd/SequenceNumber.h>
#include <efd/ID128.h>
#include <efd/BitUtils.h>
#include <egf/PendingBehavior.h>
#include <egf/SchedulerQueue.h>
#include <egf/egfClassIDs.h>


/// A helper for use inside the Entity class which helps map from property names to property ID
/// values.  This macro cannot be used outside of Entity class methods.
#ifdef EE_CONFIG_SHIPPING
#define EE_NAME2ID(name)  _Name2ID(name, "")
#else
#define EE_NAME2ID(name)  _Name2ID(name, __FUNCTION__)
#endif

namespace efd
{
    class ServiceManager;
}

namespace egf
{

class Entity;
class Scheduler;
class EntityManager;
class ISchedulerScripting;
class PendingBehavior;
class EntityFactoryResponse;

/**
    A smart pointer (reference counting, self deleting pointer) for the
    Entity class.
*/
typedef efd::SmartPointer<Entity> EntityPtr;

/**
    The implementation class for an entity. An Entity is the smallest individual object in the
    virtual world. They are sometimes referred to as game objects.

    An Emergent Entity is composed of Properties, and Behaviors. A Property is a member variable of
    an Entity and has a data type, an initial/default value, and a current value. Properties also
    have Traits associated with them, which are used to control automated management of the
    Properties, such as whether they are Persisted, or can be accessed on a Client.

    An Emergent Entity system Behavior is a member function on an Entity. Behaviors also have
    Traits that restrict how they can be called. A Behavior can be implemented in one of many
    different scripting or compiled languages, and an Entity can be composed of any combination of
    these.
*/
class EE_EGF_ENTRY Entity : public efd::IBase
{
    friend class egf::Scheduler;
    friend class egf::EntityManager;
//    friend class egf::IBuiltinModel;
    friend class egf::FlatModelManager;

    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(Entity, efd::kCLASSID_Entity, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

protected:
    /// @name Construction and Destruction
    //@{
    /**
        Constructor used to create an entity from a flat model template.

        @param[in] i_pTemplate Pointer to the template for the entity.
        @param[in] i_eid The entity ID to assign to the new entity.
        @param[in] i_bCreateAsMasterCopy True if this entity should be the master copy.
    */
    Entity(const FlatModel* i_pTemplate, egf::EntityID i_eid, efd::Bool i_bCreateAsMasterCopy);

    /// Destructor.
    ~Entity();
    //@}


public:
    /// Container properties modified from the default.
    typedef efd::map<PropertyID, IProperty*> PropertyMap;

    /// Entity process flags
    enum EntityProcFlags
    {
        kInit = 0x0001,         ///< In process of init (so read-only properties may be set).
        kOwned = 0x0002,        ///< Owned by a scheduler.
        kActive = 0x0004,       ///< Has behaviors queued or running.
        kCreated = 0x0008,      ///< Has successfully finished creation.
        kInWorld = 0x0010,      ///< Is currently in the world.
        kRequestDestroy = 0x0020,   ///< Has this entity been requested to be destroyed.
        kDestroyComplete = 0x0040,   ///< Has completed an lifecycle_OnDestroy behavior.
        kRequestEnterWorld = 0x0080, ///< Has this entity been requested to enter the world.
        kEnterWorldInProgress = 0x0100, ///<Has the OnEnterWorld lifecycle started yet.
        kRequestExitWorld = 0x0200, ///< Has this entity been requested to exit the world.
        kExitWorldInProgress = 0x0400, ///<Has the OnExitWorld lifecycle started yet.
        kAssetsLoaded = 0x0800, ///< Have the assets for this entity finished loading.
        kEntitySetFishished = 0x1000, ///< Has the containing set of entities finished loading.
    };

    /// @name Member Gets and Sets
    //@{
    /**
        Get the entity ID class for this entity.

        @return Reference to the entity ID class.
    */
    inline const EntityID& GetEntityID() const;

    /**
        Get the entity ID value for this entity.  This should only be used for logging.

        @return Entity ID value.
    */
    inline efd::UInt64 GetEntityIDValue() const;

    /**
        Get a pointer to the flat model class for this entity.  All entities will always have a
        valid FlatModel pointer as this member is set by the entity factory and is not cleared
        until the entity is destroyed.

        @return Const pointer to the flat model.
    */
    inline const FlatModel* GetModel() const;

    /**
        Get the flat model ID for this entity.

        @return The flat model ID.
    */
    inline FlatModelID GetModelID() const;

    /**
        Get the model name for this entity.

        @return A const reference to the model name.
    */
    inline const efd::utf8string& GetModelName() const;

    /**
        Returns the data file ID used to identify this entity in the block file it was loaded from.
        If the entity was not loaded from a data file this ID will be zero. Data file IDs are
        guaranteed to be universally unique across all entities in all block files (but remember
        that the same block can potentially be loaded multiple times).

        @return An ID128 containing the data file ID for this entity, or 0 if none.
    */
    inline const efd::ID128& GetDataFileID() const;

    /**
        Sets the value of the block file data ID for this entity (if loaded from a block file).
        This method is called by the internal block loading code and should never be used by any
        other code.

        @param id The data ID used in the block file to identify this entity
    */
    inline void SetDataFileID(const efd::ID128& id);

    /**
        Returns the block instance ID used when the block file containing this entity was loaded.
        If the entity was not loaded from a block file this ID will be zero.

        @return The block instance ID if this entity was loaded from a block, or 0 for dynamically
            created entities.
    */
    inline efd::UInt32 GetBlockInstance() const;

    /**
        Sets the value of the block instance ID for this entity (if loaded from a block file).
        This method is called by the internal block loading code and should never be used by any
        other code.

        @param instance The instance ID used when loading the block file.
    */
    inline void SetBlockInstance(efd::UInt32 instance);

    /**
        Returns the iteration counter used to indicate revisions to the entity in a world
        file. If the entity was not loaded from a data file this count will be zero.

        @return UInt32 The iteration count for this entity, or 0 if none.
    */
    inline efd::UInt32 GetIterationCount() const;

    /**
        Sets the value of the block file iteration counter for this entity.  Only entities loaded
        from a block file set this value. It allows the entity to be compared to a previously
        loaded entity and changes detected. World Builder increments this number every time the
        entity is changed in the block file.

        @param iteration the numeric iteration
    */
    inline void SetIterationCount(const efd::UInt32 iteration);

    /**
        Convenience method to access the service manager which owns this entities EntityManager.

        @return Const pointer to the service manager.
    */
    const efd::ServiceManager* GetServiceManager() const;

    /**
        Gets a the pointer to the EntityManager that owns this entity

        @return Pointer to EntityManager instance that owns this entity.
    */
    inline egf::EntityManager* GetEntityManager() const;

    /**
        Get a pointer to the Scheduler, if set.

        @return Pointer to Scheduler, or NULL if not set.
    */
    inline egf::Scheduler* GetScheduler() const;

    //@}

    ///////////////////////////////////////////////////////////////////////////
    /// @name Property System Methods
    //@{
public:
    /**
        Type safely retrieves the current value from the specified property.  If
        this entity is not overridden, the default data is retrieved from the flat model.

        @param[in] propID The PropertyID to retrieve from.
        @param[out] data A reference to a variable of type T that the value of this
            property will be assigned to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult GetPropertyValue(
        PropertyID propID,
        T& data) const;

    /**
        Type safely retrieves the current value from the specified property.  If
        this entity is not overridden, the default data is retrieved from the flat model.

        @param[in] propName The name of the property to retrieve.
        @param[out] data A reference to a variable of type T that the value of this
            property will be assigned to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult GetPropertyValue(
        const efd::utf8string& propName,
        T& data) const;

    /**
        Type safely retrieves the current value from the specified property by key.  If
        this entity is not overridden, the default data is retrieved from the flat model.

        @param[in] propID The PropertyID to retrieve from.
        @param[in] key The key in the map to fetch data from an map property type.
        @param[out] data A reference to a variable of type T that the value of this
            property will be assigned to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult GetPropertyValue(
        PropertyID propID,
        const efd::utf8string& key,
        T& data) const;

    /**
        Type safely retrieves the current value from the specified property by key.  If
        this entity is not overridden, the default data is retrieved from the flat model.

        @param[in] propName The name of the property to retrieve.
        @param[in] key The key in the map to fetch data from an map property type.
        @param[out] data A reference to a variable of type T that the value of this
            property will be assigned to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult GetPropertyValue(
        const efd::utf8string& propName,
        const efd::utf8string& key,
        T& data) const;

    /**
        Retrieves a string representation of the current value from the specified property. If this
        property is not overridden, the default data is retrieved from the flat model.

        @param[in] propID The PropertyID to retrieve from.
        @param[out] data A string to hold the value of the property.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetValueAsString(
        PropertyID propID,
        efd::utf8string& data) const;

    /**
        Retrieves a string representation of the current value from the specified property by key.
        If this property is not overridden, the default data is retrieved from the flat model.

        @param[in] propID The PropertyID to retrieve from.
        @param[in] key The key in the map to fetch data from.
        @param[out] data A string to hold the value of the property.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetValueAsString(
        PropertyID propID,
        const efd::utf8string& key,
        efd::utf8string& data) const;

    /**
        Attempts to lookup the ID for the given property.  Will return zero if the property is
        not found.

        @param[in] i_propName The name of the property to retrieve.
        @return The PropertyID of the specified property, or zero if the property is not found.
    */
    inline PropertyID GetPropertyID(const efd::utf8string& i_propName) const;

    /**
        Type safely retrieves the default value from the specified property.

        @param[in] propID The PropertyID to retrieve from.
        @param[out] data A reference to a variable of type T that the value of this
            property will be assigned to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult GetDefaultPropertyValue(
        PropertyID propID,
        T& data) const;

    /**
        Type safely retrieves the default value from the specified property.

        @param[in] propName The name of the property to retrieve from.
        @param[out] data A reference to a variable of type T that the value of this
            property will be assigned to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult GetDefaultPropertyValue(
        const efd::utf8string& propName,
        T& data) const;

    /**
        Type safely retrieves the default value from the specified property by key.

        @param[in] propID The PropertyID to retrieve from.
        @param[in] key The key in the map to fetch data from an map property type.
        @param[out] data A reference to a variable of type T that the value of this
            property will be assigned to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult GetDefaultPropertyValue(
        PropertyID propID,
        const efd::utf8string& key,
        T& data) const;

    /**
        Type safely retrieves the default value from the specified property by key.

        @param[in] propName The name of the property to retrieve from.
        @param[in] key The key in the map to fetch data from an map property type.
        @param[out] data A reference to a variable of type T that the value of this
            property will be assigned to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult GetDefaultPropertyValue(
        const efd::utf8string& propName,
        const efd::utf8string& key,
        T& data) const;

    /**
        Count the number of entries in the given associative property.

        @param[in] i_propID The PropertyID to look up.
        @param[out] o_count On success, the number of values for the given associative array.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetPropertyCount(PropertyID i_propID, efd::UInt32& o_count) const;

    /**
        Count the number of entries in the given associative property.

        @param[in] i_strName The name of the Property to look up.
        @param[out] o_count On success, the number of values for the given associative array.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetPropertyCount(const efd::utf8string& i_strName,
        efd::UInt32& o_count) const;

    /**
        Retrieves the property keys from the specified associative property.

        @note This method is only valid for associative array property types.

        @param[in] i_propID The ID of the property to retrieve the keys from.
        @param[out] o_keys A reference to a list that will receive the key names.
        @return A result value indicating the success or failure of the method.
    */
    PropertyResult GetPropertyKeys(PropertyID i_propID,
        efd::list<efd::utf8string>& o_keys) const;

    /**
        Retrieves the property keys from the specified associative property.

        @note This method is only valid for associative array property types.

        @param[in] i_strName The name of the property to retrieve the keys from.
        @param[out] o_keys A reference to a list that will receive the key names.
        @return A result value indicating the success or failure of the method.
    */
    PropertyResult GetPropertyKeys(const efd::utf8string& i_strName,
        efd::list<efd::utf8string>& o_keys) const;

    /**
        Retrieves the next property key name from the specified property.

        @note This method is only valid for associative array property types.

        @param[in] i_propID The ID of the property to retrieve the keys from.
        @param[in] i_previousKey The name of the previous property key. The first key should
            be returned in o_nextKey when i_previousKey  is empty.
        @param[out] o_nextKey A reference to a list that will receive the key names. This will
            be the empty string when there are no more keys.
        @return A result value indicating the success or failure of the method.
    */
    PropertyResult GetNextPropertyKey(PropertyID i_propID,
        const efd::utf8string& i_previousKey,
        efd::utf8string& o_nextKey) const;

    /**
        Retrieves the next property key name from the specified property.

        @note This method is only valid for associative array property types.

        @param[in] i_strName The name of the property to retrieve the keys from.
        @param[in] i_previousKey The name of the previous property key. The first key should
            be returned in o_nextKey when i_previousKey  is empty.
        @param[out] o_nextKey A reference to a list that will receive the key names. This will
            be the empty string when there are no more keys.
        @return A result value indicating the success or failure of the method.
    */
    PropertyResult GetNextPropertyKey(const efd::utf8string& i_strName,
        const efd::utf8string& i_previousKey,
        efd::utf8string& o_nextKey) const;

    /**
        Determine the type of a property given its ID.

        @param[in] i_propID The PropertyID to look up.
        @param[out] o_result The type for the property.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetPropertyType(PropertyID i_propID, efd::ClassID& o_result) const;

    /**
        Determine the type of a property given its name.

        @param[in] i_strName The name of the Property to look up.
        @param[out] o_result The type for the property.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetPropertyType(const efd::utf8string& i_strName,
        efd::ClassID& o_result) const;

    /**
        Determine the type of the storage elements for a property given its ID.

        @param[in] i_propID The PropertyID to look up.
        @param[out] o_result The storage type for the property.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetDataStorageType(PropertyID i_propID, efd::ClassID& o_result) const;

    /**
        Determine the type of the storage elements for a property given its name.

        @param[in] i_strName The name of the Property to look up.
        @param[out] o_result The storage type for the property.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetDataStorageType(const efd::utf8string& i_strName,
        efd::ClassID& o_result) const;

    /**
        Type safely sets the value of this entity's specified property to the
        specified value.  If this entity has not overridden, this will cause a new property
        to be created and bound to the entity to store the contents of data.

        @param[in] propID The PropertyID to assign data to.
        @param[in] data A reference to a variable of type T that contains the value
            that the property should be set to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult SetPropertyValue(
        PropertyID propID,
        const T& data);

    /**
        Type safely sets the value of this entity's specified property to the
        specified value.  If this entity has not overridden, this will cause a new property
        to be created and bound to the entity to store the contents of data.

        @param[in] propName The name of the property to assign data to.
        @param[in] data A reference to a variable of type T that contains the value
            that the property should be set to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult SetPropertyValue(
        const efd::utf8string& propName,
        const T& data);

    /**
        Type safely sets the value, by key, of this entity's specified property to the
        specified value.  If this entity has not overridden, this will cause a new property
        to be created and bound to the entity to store the contents of data.

        @param[in] propID The PropertyID of an associative property to assign data to.
        @param[in] key The key within the property to set
        @param[in] data A reference to a variable of type T that contains the value
            that the property key should be set to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult SetPropertyValue(
        PropertyID propID,
        const efd::utf8string& key,
        const T& data);

    /**
        Type safely sets the value, by key, of this entity's specified property to the
        specified value.  If this entity has not overridden, this will cause a new property
        to be created and bound to the entity to store the contents of data.

        @param[in] propName The name of the associative property to assign data to.
        @param[in] key The key within the property to set
        @param[in] data A reference to a variable of type T that contains the value
            that the property should be set to.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult SetPropertyValue(
        const efd::utf8string& propName,
        const efd::utf8string& key,
        const T& data);


    /**
        Type safely sets the value of this entity's specified property to the
        specified string value.  If this entity has not overridden, this will cause a new
        property to be created and bound to the entity to store the contents of data.

        @param[in] propID The PropertyID to assign data to.
        @param[in] i_strValue A string that contains a text representation of the value
            that the property should be set to.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult SetPropertyValueByString(
        PropertyID propID,
        const efd::utf8string& i_strValue);

    /**
        Type safely sets the value of this entity's specified property to the
        specified string value.  If this entity has not overridden, this will cause a new
        property to be created and bound to the entity to store the contents of data.

        @param[in] i_strPropName The string name of the property to assign data to.
        @param[in] i_strValue A string that contains a text representation of the value
            that the property should be set to.
        @return A PropertyResult value indicating the operation's status.
    */
    inline PropertyResult SetPropertyValueByString(
        const efd::utf8string& i_strPropName,
        const efd::utf8string& i_strValue);

    /**
        Type safely sets the value, by key, of this entity's specified property to the
        specified string value.  If this entity has not overridden, this will cause a new
        property to be created and bound to the entity to store the contents of data.

        @param[in] propID The PropertyID to assign data to.
        @param[in] i_strKey The key for the data item to set in an Assoc property.
        @param[in] i_strValue A string that contains a text representation of the value
            that the property should be set to.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult SetPropertyValueByString(
        PropertyID propID,
        const efd::utf8string& i_strKey,
        const efd::utf8string& i_strValue);

    /**
        Type safely sets the value, by key, of this entity's specified property to the
        specified string value.  If this entity has not overridden, this will cause a new
        property to be created and bound to the entity to store the contents of data.

        @param[in] i_strPropName The name of the property to assign data to.
        @param[in] i_strKey The key for the data item to set in an Assoc property.
        @param[in] i_strValue A string that contains a text representation of the value
            that the property should be set to.
        @return A PropertyResult value indicating the operation's status.
    */
    inline PropertyResult SetPropertyValueByString(
        const efd::utf8string& i_strPropName,
        const efd::utf8string& i_strKey,
        const efd::utf8string& i_strValue);

    /**
        Checks whether the given property is valid for this entity.

        @param[in] i_propID The ID of the property to check.
        @return A PropertyResult value indicating the operation's status.
    */
    inline PropertyResult HasPropertyValue(PropertyID i_propID) const;

    /**
        Checks whether a property key with the given name exists for the given associative property.

        @param[in] i_propID The ID of the property to check.
        @param[in] i_strKey The key for the data item to check in an Assoc property.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult HasPropertyValue(
        PropertyID i_propID,
        const efd::utf8string& i_strKey) const;

    /**
        Checks whether the given property is valid for this entity.

        @param[in] i_strPropName The name of the property to check.
        @return A PropertyResult value indicating the operation's status.
    */
    inline PropertyResult HasPropertyValue(const efd::utf8string& i_strPropName) const;

    /**
        Checks whether a property key with the given name exists for the given associative property.

        @param[in] i_strPropName The name of the property to check.
        @param[in] i_strKey The key for the data item to check in an Assoc property.
        @return A PropertyResult value indicating the operation's status.
    */
    inline PropertyResult HasPropertyValue(
        const efd::utf8string& i_strPropName,
        const efd::utf8string& i_strKey) const;

    /**
        Checks if the specified property is locally dirty. Properties become locally dirty whenever
        a property value is set through SetPropertyValue or SetPropertyValueByString or reset using
        ResetProperty. The dirty flag is cleared by the egf::EntityManager during its OnTick once
        the local entity update notification message has been sent out.

        @param[in] propID : The ID of the property to check.
        @return True if the property is dirty.
    */
    inline efd::Bool IsDirty(PropertyID propID) const;

    /**
        Checks if the specified property is locally dirty. Properties become locally dirty whenever
        a property value is set through SetPropertyValue or SetPropertyValueByString or reset using
        ResetProperty. The dirty flag is cleared by the egf::EntityManager during its OnTick once
        the local entity update notification message has been sent out.

        @param[in] propName The name of the property to check.
        @return True if the property is dirty.
    */
    inline efd::Bool IsDirty(const efd::utf8string& propName) const;

    /**
        Return true if the property has an overridden (non-default) value.

        @param[in] pid the property to check.
        @return true if the property is overridden, false if not.
    */
    bool IsPropertyOverridden(PropertyID pid) const;

    /**
        Reset a property to the default value.  The default value is the value specified in the
        final flat model used to create this entity and does not reflect any overrides specified
        in the block file.

        @param[in] propID The ID of the property to reset.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult ResetProperty(PropertyID propID);

    /**
        Reset a property to the default value.  The default value is the value specified in the
        final flat model used to create this entity and does not reflect any overrides specified
        in the block file.

        @param[in] propName The name of the property to reset.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult ResetProperty(const efd::utf8string& propName);

    /**
        Reset all overridden properties to their default value.

        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult ResetAllProperties();

    /**
        Attempts to increment given property.

        @param[in] propID The PropertyID to increment.
        @param[out] data A reference to a variable of type T that the incremented
            value of the property should be assigned to.
        @param[in] increment_value The amount to increment by.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult IncrementPropertyValue(
        PropertyID propID,
        T& data,
        T increment_value = 1);

    /**
        Attempts to increment given property.

        @param[in] propName The name of the property to increment.
        @param[out] data A reference to a variable of type T that the incremented
            value of the property should be assigned to.
        @param[in] increment_value The amount to increment by.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult IncrementPropertyValue(
        const efd::utf8string& propName,
        T& data,
        T increment_value = 1);

    /**
        Attempts to decrement given property.

        @param[in] propID The PropertyID to decrement.
        @param[out] data A reference to a variable of type T that the decremented
            value of the property should be assigned to.
        @param[in] decrement_value The amount to decrement by.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult DecrementPropertyValue(
        PropertyID propID,
        T& data,
        T decrement_value = 1);

    /**
        Attempts to decrement given property.

        @param[in] propName The name of the property to decrement.
        @param[out] data A reference to a variable of type T that the decremented
            value of the property should be assigned to.
        @param[in] decrement_value The amount to decrement by.
        @return A PropertyResult value indicating the operation's status.
    */
    template<typename T>
    PropertyResult DecrementPropertyValue(
        const efd::utf8string& propName,
        T& data,
        T decrement_value = 1);

    /**
        Type safely removes a value, by key, from this entity's specified associative property.
        If this entity has not overridden the property from that of the flat model, a new
        property will be created and bound to the entity to store the changed data.

        @param[in] propID The property ID to remove the value from
        @param[in] key A reference to a variable of type T that contains the value
            that the property should be set to.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult RemovePropertyValue(
        PropertyID propID,
        const efd::utf8string& key);

    /**
        Type safely removes a value, by key, from this entity's specified associative property.
        If this entity has not overridden the property from that of the flat model, a new
        property will be created and bound to the entity to store the changed data.

        @param[in] propName The name of the property to remove the value from
        @param[in] key A reference to a variable of type T that contains the value
            that the property should be set to.
        @return A PropertyResult value indicating the operation's status.
    */
    inline PropertyResult RemovePropertyValue(
        const efd::utf8string& propName,
        const efd::utf8string& key);

    /**
        Transfer properties from a parameter list to the entity. The parameter names must match
        properties on the current entity and the parameter types must match the property types.
    */
    bool ApplyProperties(efd::ParameterList* pParameterList);

    /**
        Sets the specified property as being dirty as result of a direct manipulation of a built-in
        model. Do not call this when a built-in model property is changing due to normal
        IBuiltinModel API calls, only call this if the property value is being directly manipulated
        outside of a normal Entity property APIs.

        @param[in] propID The ID of the property.
        @param[in] prop Pointer to the builtin model that exposed the property.
    */
    void BuiltinPropertyChanged(PropertyID propID, IBuiltinModel* prop);

protected:

    /**
        Remove a property from the Entity.

        @param[in] propID The ID of the property to reset.
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult RemoveProperty(PropertyID propID);

    /**
        Checks if the given property should be read from and written to an IBuiltinModel or if
        it should use a normal IProperty.  Looks at the property traits and whether the entity
        is owned or replicated in order to make that decision.

        @param[in] pDesc Pointer to the descriptor of the property to check.
        @return True if we should lookup and use an IBuiltinModel for this property.
    */
    efd::Bool ShouldPropertyUseBuiltinModel(const PropertyDescriptor* pDesc) const;

    /**
        This will fetch the value from the property map if the value has been modified.  Otherwise
        it will access the default value from the descriptor.

        @param[in] pDesc Pointer to the descriptor of the property to check.
        @return Pointer to the property, might be either the current value or default value.
    */
    const IProperty* GetPropertyForReading(const PropertyDescriptor* pDesc) const;

    /**
        Tests whether the given property can be written to.  A property must not have the
        ReadOnly trait in order to be written.  In addition, it must either be owned or else
        have the Mutable trait.

        @param[in] pDesc Pointer to the descriptor of the property to check.
        @return PropertyResult_OK if the property can be written
            to.  Otherwise an error value describing why the property cannot be written to.
    */
    PropertyResult CheckWritability(const PropertyDescriptor* pDesc) const;

    /**
        This will fetch the value from the property map if the value has been modified.  Otherwise
        it will either clone the default value or lookup the owning built-in model depending on
        the type of property and then add the property to the property map.

        @param[in] pDesc Pointer to the descriptor of the property to check.
        @return Pointer to the writable property, NULL if read only.
    */
    IProperty* GetPropertyForWriting(const PropertyDescriptor* pDesc);

    /**
        Sets the specified property as being dirty.

        @param[in] propID The ID of the property.
        @param[in] prop Pointer to the property.
    */
    virtual void SetDirty(PropertyID propID, const IProperty* prop);

    /**
        Looks in this entity's FlatModel for a property with the given name and returns its ID.
        As a result this method can only convert properties that are used by this entity.  See
        FlatModelManager::GetPropertyNameByID for a more universal conversion method.

        @param[in] propName The name of the property.
        @param[in] pszMethod The name of the function that called _Name2ID, used for logging
        @return The ID of the property.
    */
    PropertyID _Name2ID(const efd::utf8string& propName, const char* pszMethod) const;

    /**
        Retrieves a descriptor for the specified property.

        @param[in] i_propID The ID of the property
        @param[out] o_ppd A reference to a const pointer to the descriptor
        @return PropertyResult_OK if the property descriptor was retrieved.  Otherwise an error
            value describing why it failed.
    */
    PropertyResult _GetPropDesc(PropertyID i_propID, const PropertyDescriptor*& o_ppd) const;

    /**
        Retrieves a descriptor for the specified property.

        @param[in] i_strPropName The name of the property
        @param[out] o_ppd A reference to a const pointer to the descriptor
        @return PropertyResult_OK if the property descriptor was retrieved.  Otherwise an error
            value describing why it failed.
    */
    PropertyResult _GetPropDesc(const efd::utf8string& i_strPropName,
        const PropertyDescriptor*& o_ppd) const;

    /**
        Releases the memory used by the specified property

        @param[in] propID The ID of the property
        @param[in] prop Pointer to the property
    */
    void FreeProperty(PropertyID propID, IProperty* prop);

    /**
        Similar to ResetProperty only it resets to the specified PropertyDescriptor value rather
        than our current default value. This is used during rapid iteration at a point where our
        model data still points to the old model but we are being updated to prepare for accepting
        a new model.

        @param[in] changedPropID The ID of the property that has changed during rapid iteration
        @param[in] newDesc A description of the new property which might differ by traits, type and
            default values from our current description for the property.
    */
    void RapidIterateResetProperty(PropertyID changedPropID, const PropertyDescriptor* newDesc);

    /**
        Called by FlatModelManager when a flat model has been rapidly iterated resulting in a change
        to a property. When called our model data still points to the old model but we are being
        updated to prepare for accepting a new model.

        @param[in] changedPropID The ID of the property that has changed during rapid iteration
        @param[in] newDesc A description of the new property which might differ by traits, type and
            default values from our current description for the property.
    */
    void RapidIterateDefaultPropertyValue(
        PropertyID changedPropID,
        const PropertyDescriptor* newDesc);

    /// The default map of properties.
    PropertyMap m_propertyMap;

    /// Container properties modified from the default.
    typedef efd::set<PropertyID> DirtyPropertySet;

    /// Set of dirty properties.
    DirtyPropertySet m_dirtyPropertySet;

    /**
        Validates that the type of the specified classID can safely hold the
        data found in the specified property.  Upon successful validation, the
        PropertyDescriptor argument will point the specified property's
        descriptor.  This is useful because it is generally required to use
        the descriptor later in the code block, resulting in at least one extra
        virtual call.

        @param[in] propID The ID of the property
        @param[in] classID The ClassID to check against
        @param[out] rpDescriptor Reference to a const pointer to the descriptor
        @return PropertyResult_OK if the classID can safely hold the data.  Otherwise an error
            value describing why it failed.
    */
    PropertyResult ValidateTypeSafety(
        PropertyID propID,
        efd::ClassID classID,
        const PropertyDescriptor*& rpDescriptor) const;

    /// @name Type-Unsafe Getters and Setters
    //@{
    /// The public template methods should be used instead of these type-unsafe methods.

    /**
        Retrieves the current value from the specified property without enforcing type checking.
        If this entity is not overridden, the default data is retrieved from the flat model.

        @note The public template methods should be used instead of these type-unsafe methods.

        @param[in] propID The PropertyID to retrieve from.
        @param[out] data A void pointer to hold the retrieved value.
        @param[in] classID The ClassID of the data type in the void pointer (data).
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetPropertyValueUnsafe(
        PropertyID propID,
        void* data,
        efd::ClassID classID) const;

    /**
        Retrieves the current value, by key, from the specified property without enforcing type
        checking.  If this entity is not overridden, the default data is retrieved from the flat
        model.

        @note The public template methods should be used instead of these type-unsafe methods.

        @param[in] propID The PropertyID to retrieve from.
        @param[in] key The key of the value to retrieve.
        @param[out] data A void pointer to hold the retrieved value.
        @param[in] classID The ClassID of the data type in the void pointer (data).
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetPropertyValueUnsafe(
        PropertyID propID,
        const efd::utf8string& key,
        void* data,
        efd::ClassID classID) const;

    /**
        Retrieves the default value from the specified property without enforcing type
        checking.

        @note The public template methods should be used instead of these type-unsafe methods.

        @param[in] propID The PropertyID to retrieve from.
        @param[out] data A void pointer to hold the retrieved value.
        @param[in] classID The ClassID of the data type in the void pointer (data).
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetDefaultPropertyValueUnsafe(
        PropertyID propID,
        void* data,
        efd::ClassID classID) const;

    /**
        Retrieves the default value, by key, from the specified property without enforcing type
        checking.

        @note The public template methods should be used instead of these type-unsafe methods.

        @param[in] propID The PropertyID to retrieve from.
        @param[in] key The key of the value to retrieve.
        @param[out] data A void pointer to hold the retrieved value.
        @param[in] classID The ClassID of the data type in the void pointer (data).
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult GetDefaultPropertyValueUnsafe(
        PropertyID propID,
        const efd::utf8string& key,
        void* data,
        efd::ClassID classID) const;

    /**
        Sets the value of this entity's specified property to the
        specified value without enforcing type checking.  If this entity has not overridden,
        this will cause a new property to be created and bound to the entity to store the
        contents of data.

        @note The public template methods should be used instead of these type-unsafe methods.

        @param[in] propID The PropertyID to assign data to.
        @param[in] data A reference to a variable of type T that contains the value
            that the property should be set to.
        @param[in] classID A classID that describes the type of the pointed to data
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult SetPropertyValueUnsafe(
        PropertyID propID,
        const void* data,
        efd::ClassID classID);

    /**
        Sets the value of this entity's specified property, by key, to the
        specified value without enforcing type checking.  If this entity has not overridden,
        this will cause a new property to be created and bound to the entity to store the
        contents of data.

        @note The public template methods should be used instead of these type-unsafe methods.

        @param[in] propID The PropertyID to assign data to.
        @param[in] key The key of the value to retrieve.
        @param[in] data A reference to a variable of type T that contains the value
            that the property should be set to.
        @param[in] classID A classID that describes the type of the pointed to data
        @return A PropertyResult value indicating the operation's status.
    */
    PropertyResult SetPropertyValueUnsafe(
        PropertyID propID,
        const efd::utf8string& key,
        const void* data,
        efd::ClassID classID);

    /**
        Clears the local dirty property map of all entries. This is called by the EntityManager
        after it has sent out the local change notification message. This should not be called at
        any other time as that could prevent update messages from being sent and those messages
        are relied upon by many services.
    */
    inline void ClearDirty();

    //
    // end Property System Methods
    //@}
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// @name Built-in Model System Methods
    //@{
    //
public:
    /**
        Finds a built-in model by name.

        @param[in] i_strComponentName The name of the built-in model to find.
        @return Pointer to the built-in model, NULL if not found.
    */
    IBuiltinModel* FindBuiltinModel(const efd::utf8string& i_strComponentName) const;

    /**
        Finds a built-in by ID.

        @param[in] i_builtinId The ID of the built-in model to find.
        @return Pointer to the built-in model, NULL if not found.
    */
    inline IBuiltinModel* FindBuiltinModel(FlatModelID i_builtinId) const;

    /**
        Finds a built-in by the class ID of the built-in model's C++ class.

        @param[in] i_classId The Class ID of the built-in model to find.
        @return Pointer to the built-in model, NULL if not found.
    */
    IBuiltinModel* FindBuiltinModelByClass(efd::ClassID i_classId) const;

    /**
        Creates all the built-in models specified in the flat model.
        Used at creation time to setup all the built-in models needed by the entity.
        Called by the FlatModelManager::FactoryEntity method.

        @param[in] i_pCompFactory Pointer to the flat model manager.
        @return True if all the built-in models were created successfully.
    */
    efd::Bool CreateBuiltinModels(class FlatModelManager* i_pCompFactory);

protected:
    /**
        Creates a new built-in model and adds it to the entity.

        @param[in] i_builtinId The ID of the built-in model.
        @param[in] i_pNewComp Pointer to the newly created built-in model.
        @return True if created, false if it already exists or could not be created.
    */
    efd::Bool AddBuiltinModel(FlatModelID i_builtinId, IBuiltinModel* i_pNewComp);

    /// Typedef for the built-in model map.
    typedef efd::map< FlatModelID, IBuiltinModelPtr > BuiltModelMap;

    /// Map of all the built-in models in this entity.
    BuiltModelMap m_BuiltinModels;

    //
    // end BuiltinModel System Methods
    //@}
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// @name Behavior System Methods
    //@{
    //
public:
    /**
        Immediately execute a behavior.  The behavior must have the Immediate trait, which also
        means the behavior cannot be a blocking behavior.

        @note A successful return result only indicates that a valid behavior was found and
        invoked.  It does not imply that the behavior itself was able to successfully run.

        @param[in] id  The ID of the behavior to execute.
        @param[in] mixinModelID  A model that must be mixed in for this behavior to be valid. Can
            be zero in which case no mix-in restriction is enforced.
        @param[in] pArgs Pointer to the streamed arguments for the behavior.  This pointer
            can be NULL if the behavior takes no arguments.
        @param[in] eventID  The ID of the event that triggered the behavior.
        @param[in] returnID  ID of the entity to send the return value to.
        @return True if behavior was successfully executed, false if an error occurred.
    */
    efd::Bool CallImmediateBehavior(
        BehaviorID id,
        FlatModelID mixinModelID = 0,
        efd::ParameterList* pArgs = NULL,
        EventID eventID = 0,
        EntityID returnID = 0);

    /**
        Immediately execute a behavior.  The behavior must have the Immediate trait, which also
        means the behavior cannot be a blocking behavior.

        @note A successful return result only indicates that a valid behavior was found and
        invoked.  It does not imply that the behavior itself was able to successfully run.

        @param[in] behaviorName The name of the behavior to execute.
        @param[in] mixinModelName A model that must be mixed in for this behavior to be valid. This
            can be an empty string in which case no mix-in restriction is enforced.
        @param[in] pArgs Pointer to the streamed arguments for the behavior.  This pointer
            can be NULL if the behavior takes no arguments.
        @param[in] eventID The ID of the event that triggered the behavior.
        @param[in] returnID ID of the entity to send the return value to.
        @return True if behavior was successfully invoked, false if an error occurred.
    */
    efd::Bool CallImmediateBehavior(
        const efd::utf8string& behaviorName,
        const efd::utf8string& mixinModelName = efd::utf8string::NullString(),
        efd::ParameterList* pArgs = NULL,
        EventID eventID = 0,
        EntityID returnID = 0);

    /**
        Add a behavior to the queue of those awaiting execution.

        @param[in] pMessage Pointer to the event message that is invoking the behavior.
        @return True if behavior added successfully,
            false if error (behavior not found in this entity's model).
    */
    efd::Bool AddPendingBehavior(const EventMessage* pMessage);

    /**
        Add a behavior to the queue of those awaiting execution.

        @param[in] behaviorName The name of the behavior to execute.
        @param[in] mixinModelName A model that must be mixed in for this behavior to be valid.
        @param[in] pArgs Pointer to the streamed arguments for the behavior.  This pointer
            can be NULL if the behavior takes no arguments.
        @param[in] executionTime The time, in seconds, at which the behavior should execute.
        @param[in] eventID The ID of the event that triggered the behavior.
        @param[in] returnID ID of the entity to send the return value to.
        @return True if behavior added successfully,
            false if error (behavior not found in this entity's model).
    */
    efd::Bool AddPendingBehavior(
        const efd::utf8string& behaviorName,
        const efd::utf8string& mixinModelName,
        efd::ParameterList* pArgs = NULL,
        efd::TimeType executionTime = 0.0,
        EventID eventID = 0,
        EntityID returnID = 0);

    /**
        Add a behavior to the queue of those awaiting execution.

        @param[in] id The ID of the behavior to execute.
        @param[in] mixinModelID A model that must be mixed in for this behavior to be valid.
        @param[in] pArgs Pointer to the streamed arguments for the behavior.  This pointer
            can be NULL if the behavior takes no arguments.
        @param[in] executionTime The time in seconds that the behavior should execute.
        @param[in] eventID The ID of the event that triggered the behavior.
        @param[in] returnID ID of the entity to send the return value to.
        @return True if behavior added successfully,
            false if error (behavior not found in this entity's model).
    */
    efd::Bool AddPendingBehavior(
        BehaviorID id,
        FlatModelID mixinModelID,
        efd::ParameterList* pArgs = NULL,
        efd::TimeType executionTime = 0.0,
        EventID eventID = 0,
        EntityID returnID = 0);

    /**
        Add a behavior to the queue of those awaiting execution.

        @param[in] spBehavior Const pointer of the behavior to execute.
        @param[in] mixinModelID A model that must be mixed in for this behavior to be valid.
        @param[in] pArgs Pointer to the streamed arguments for the behavior.  This pointer
            can be NULL if the behavior takes no arguments.
        @param[in] executionTime The time in seconds that the behavior should execute.
        @param[in] eventID The ID of the event that triggered the behavior.
        @param[in] returnID ID of the entity to send the return value to.
        @return True if behavior added successfully,
            false if error (behavior not found in this entity's model).
    */
    efd::Bool AddPendingBehavior(
        const BehaviorDescriptor* spBehavior,
        FlatModelID mixinModelID,
        efd::ParameterList* pArgs = NULL,
        efd::TimeType executionTime = 0.0,
        EventID eventID = 0,
        EntityID returnID = 0);

    /**
        Remove a behavior from the queue of those awaiting execution.

        @param[in] pMessage Pointer to the event message that is canceling the pending behavior.
        @return True if behavior removed/cancelled successfully,
            false if error (behavior not found).
    */
    efd::Bool RemovePendingBehavior(const EventMessage* pMessage);

    /**
        Remove a behavior to the queue of those awaiting execution.

        @param[in] eventID The ID of the behavior event that should be removed.
        @return True if behavior removed/cancelled successfully,
            false if error (behavior not found).
    */
    efd::Bool RemovePendingBehavior(EventID eventID);

    /**
        Method to test if a behavior exists on the pending queue.

        @param[in] id The event ID of the behavior to find.
        @return True if the behavior is pending.
    */
    efd::Bool IsBehaviorPending(EventID id) const;

    /**
        Determine if any behaviors are pending on this entity.

        @return Bool True if any behaviors are pending, false otherwise.
    */
    efd::Bool HasPendingBehaviors() const;

    /**
        Determine if any behaviors are executing on this entity.

        @return Bool True if any behaviors are pending, false otherwise.
    */
    efd::Bool HasExecutingBehaviors() const;

    /**
        Determine if any behaviors are pending or executing on this entity.

        @return Bool True if any behaviors are pending or executing, false otherwise.
    */
    efd::Bool HasActiveBehaviors() const;

    /**
        Whenever a behavior is about to begin on the entity this method is called.

        @param pBehavior The behavior that is about to execute.
        @return Return true to allow the behavior to run, or false to skip execution
    */
    bool StartBehavior(PendingBehavior* pBehavior);

    /**
        Whenever a behavior completes whether successfully or through an error this method is
        called to perform any required cleanup.

        @param pBehavior The behavior that has either completed, been cancelled or failed.
        @param success True if the behavior ran to completion, false if it was cancelled or failed.
    */
    void FinishEvent(PendingBehavior* pBehavior, bool success);

    /**
        Return the test of the flag bit for owned for this entity.

        @return True if entity is owned by a scheduler, false if it is a replication (not writable).
    */
    efd::Bool IsOwned() const;

    /**
        Return the test of the flag bit for creation for this entity.

        @return True if entity is has successfully completed creation.
    */
    efd::Bool IsCreated() const;

    /**
        Return the test of the flag bit for in-world for this entity.

        @return True if entity is currently in the world.
    */
    efd::Bool IsInWorld() const;

    /**
        Return the test of the flag bit for destroying for this entity.

        @return True if entity is in the process of being destroyed or has been destroyed.
    */
    efd::Bool IsDestroyInProgress() const;

    /**
        Test if it is valid to execute a given behavior on the entity.

        @param[in] i_bid The ID of the behavior to check if execution is valid.
        @return True if the given behavior is valid to execute on this entity.
    */
    efd::Bool IsBehaviorInvokeValid(BehaviorID i_bid);

    /**
        Test if it is valid to execute a given behavior on the entity.

        @param[in] bid The ID of the behavior to check if execution is valid.
        @param[in] psim A pointer to the simulator to ask if execution is valid.
        @param[in] expectSuccess If true, an error will be logged if this method returns false.
        @param[in] isViewEvent If true, failure due to the "view only" trait will not log an error.
        @return True if the given behavior is valid to execute on this entity.
    */
    efd::Bool IsBehaviorInvokeValid(
        BehaviorID bid,
        egf::Scheduler* psim,
        bool expectSuccess = false,
        bool isViewEvent = false);

    /**
        Test if it is valid to execute a given behavior on the entity.

        @param[in] pBehavior Pointer to the behavior to check if execution is valid.
        @param[in] psim A pointer to the simulator to ask if execution is valid.
        @param[in] expectSuccess If true, an error will be logged if this method returns false.
        @param[in] isViewEvent If true, failure due to the "view only" trait will not log an error.
        @return True if the given behavior is valid to execute on this entity.
    */
    efd::Bool IsBehaviorInvokeValid(
        const BehaviorDescriptor* pBehavior,
        egf::Scheduler* psim,
        bool expectSuccess = false,
        bool isViewEvent = false);

    /**
        Gets a the pointer to the Scheduler that controls behaviors for this entity.

        @return Pointer to scheduler instance for this entity.
    */
    inline egf::Scheduler* GetExecutor() const;

    /**
        Sets the pointer to our "owner" scheduler, the scheduler that is allowed to execute
        behaviors on this entity.

        @note This must only be called to set an executer to the same scheduler
            that this entity is stored in.

        @param[in] pSim Pointer to scheduler instance that owns this entity.
    */
    void SetExecutor(egf::Scheduler* pSim);

    /**
        Behavior invocation requests are delivered here.  In turn we simply pass them to the
        scheduler to be processed.

        @param[in] pMsg Pointer to the message that needs to be handled.
        @param[in] targetChannel Channel that the message arrived on.
    */
    virtual void HandleMessage(const EventMessage *pMsg, efd::Category targetChannel);

    /**
        Set the name of a behavior to invoke when the entity with the provided EntityId is created.

        @param[in] entityId EntityId for the entity we're waiting for.
        @param[in] behavior Name of the behavior to invoke when the entity arrives.
    */
    void SetEntityCreateCallbackBehavior(
        const egf::EntityID& entityId,
        const efd::utf8string& behavior);

    /**
        EntityFactoryResponse messages are delivered here. These are created in response to
        a BehaviorAPI::CreateEntity call. If the script registered a callback behavior during
        this call, this handler will send an event to ourselves.

        @param[in] pMsg EntityFactoryMessage instance to handle.
    */
    virtual void HandleEntityFactoryResponse(const egf::EntityFactoryResponse* pMsg, efd::Category);

protected:

    /**
        Insert a behavior directly on the queue.

        @param[in] pPend Pointer to the pending behavior event.
    */
    void InsertBehavior(PendingBehavior* pPend);

private:
    /**
        Sets the flag that this entity is owned by a scheduler (whether
        or not it is actively executing OnTick()s).  This flag set
        indicates that properties may be altered within behaviors
        executed by this scheduler.

        @param[in] ownFlag True if a scheduler owns this entity,
            false if the entity exists only as a replication.
    */
    void SetOwned(efd::Bool ownFlag);

    /**
        Apply supermodel invocation order policies and queue resulting behaviors.

        @param[in] pBehavior Pointer of the behavior to execute.
        @param[in] spArgs Pointer to the streamed arguments for the behavior.
        @param[in] executionTime The time, in seconds, at which the behavior should execute.
        @param[in] eventID The ID of the event that triggered the behavior.
        @param[in] returnID ID of the entity to send the return value to.
        @param[in] lifeCycleAdvanceOnCompletion When set, indicates this behavior advances the
            specified entity lifecycle on completion.
        @return True if one or more behaviors were queued
    */
    bool QueuePendingBehavior(
        const BehaviorDescriptor* pBehavior,
        efd::ParameterList* spArgs,
        efd::TimeType executionTime,
        EventID eventID,
        EntityID returnID,
        efd::UInt32 lifeCycleAdvanceOnCompletion = 0);

    //
    // end Behavior System Methods
    //@}
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// @name Messaging Methods
    //@{
    //
public:

    /**
        Creates a private category ID based on the entity ID specified.

        @param[in] entityID The entity ID for form category ID from.
        @return The private category ID.
    */
    static efd::Category MakePrivateCatID(const EntityID& entityID);

    /**
        Returns the private category for the entity.

        @return The private category for this entity.
    */
    efd::Category GetPrivateCatID() const;

    /**
        Sends an event message to invoke the specified behavior on any entity
        listening on the specified category.

        @param[in] categoryID The category to send the event message to.
        @param modelID The ID of a model that the target entity must mix-in in order for
            this event to be considered valid.  Acts as a sort of type safety. This is optional,
            pass 0 to avoid using a mix-in restriction on target entities.
        @param[in] invokeModelID The specific model that implements the behavior to invoke, or
            zero to automatically call the most derived implementation.  Typically you always
            want to pass zero for this parameter.
        @param[in] behaviorID The behavior ID to invoke.
        @param[in] callbackBehaviorID The behavior ID to invoke when the return
            value is received.
        @param[in] delay The time to delay before executing the behavior.
        @param[in] pParams The parameters required by the behavior.
        @return The ID of the event that was generated.
    */
    EventID SendEvent(
        efd::Category categoryID,
        FlatModelID modelID,
        FlatModelID invokeModelID,
        BehaviorID behaviorID,
        BehaviorID callbackBehaviorID = 0,
        efd::TimeType delay = 0.0f,
        efd::ParameterList* pParams = NULL);

    /**
        Sends an event message to invoke the specified behavior on any entity
        listening on the specified category.

        @note This version is just like SendEvent only it is for use by the scripting system.

        @param[in] idEntityOrChannel The entity or channel to send to.
        @param[in] strModel The name of a model that the target entity must mix-in in order for
            this event to be considered valid.  Acts as a sort of type safety. This is optional,
            pass NULL to avoid using a mix-in restriction on target entities.
        @param[in] strBehavior The name of the behavior to invoke which can contain a
            "Model:Method" style string.
        @param[in] pParams The parameters required by the behavior.
        @param[in] strCallback The name of the behavior to invoke when the return
            value is received or NULL for no callback.
        @param[in] delay The time to delay before executing the behavior.
        @return The ID of the event that was generated.
    */
    EventID SendEvent(
        efd::Category idEntityOrChannel,
        const char* strModel,
        const char* strBehavior,
        efd::ParameterList* pParams = NULL,
        const char* strCallback = NULL,
        efd::TimeType delay = 0.0f);

    /**
        Creates an Event Message to be sent.

        @param[in] entityID The replicated entity's ID.
        @param[in] strModel The model that must be mixed into all target entities. This is optional,
            pass NULL to avoid filtering the behavior by mix-in model.
        @param[in] strBehavior The behavior to invoke.
        @param[in] pParams The parameters required by the behavior.
        @param[in] strCallback The name of the behavior to invoke when the return value is
            received.  Pass NULL or an empty string for no callback.
        @param[in] delay The time to delay before executing the behavior.
        @param[in] needResponse True if the caller requires a return value message.
        @return Smart pointer to the message created.
    */
    EventMessagePtr CreateEventMessage(
        egf::EntityID entityID,
        const char* strModel,
        const char* strBehavior,
        efd::ParameterList* pParams,
        const char* strCallback, /* if empty, no callback */
        efd::TimeType delay,
        bool needResponse);

    /**
        Posts an event to this entity for processing.

        @param[in] pMessage The event message to process.
        @return True if the message was processed correctly.
    */
    efd::Bool PostEvent(const EventMessage* pMessage);

    /**
        Sends a return value event message to the entity that that invoked the behavior.

        @param[in] pBehavior The running behavior that is returning a value.
        @param[in] pRetVals The return value parameters, if any.
        @return True if it is sent.
    */
    efd::Bool SendReturnValue(egf::PendingBehavior* pBehavior, efd::ParameterList* pRetVals) const;

    //
    // end Messaging Methods
    //@}
    ///////////////////////////////////////////////////////////////////////////

    /**
        Called when the entity is added to the EntityManager.

        Passes the word on to any built-in models in the entity so that they can perform startup
        tasks.  Also kicks off the lifecycle_OnCreate lifecycle which, if a scheduler is present,
        will invoke the OnCreate behavior.

        @param pParameterList Optional ParameterList passed to OnCreate.
    */
    virtual void OnAdded(efd::ParameterList* pParameterList = 0);

    virtual void OnReinitialized();

    /**
        Called when assets have been loaded for a preload request, or immediately after OnAdded
        when preloading is not requested.

        Preload of assets is performed only for entities that mix-in the Preloadable model and
        have the PreloadAssets property set true. When the OnCreate lifecycle finishes all
        requested assets will be pre-loaded and once the preload is completed this method will
        be invoked. This method will be invoked immediately after the OnCreate lifecycle for
        entities that do not preload. In turn this method kicks off the OnAssetsLoaded lifecycle
        and, if a scheduler is present, its associated behavior.
    */
    virtual void OnAssetsLoaded();

    /**
        Called when all entities in an entity set have all completed their lifecycle_OnCreate.
        If the entity was loaded from a block then all entities in the block are a single set,
        the EntityLoaderService calls this method in that case.  For dynamically created entities
        each entity is it's own set and this method is called from EntityManager as soon as
        the OnCreate lifecycle completes.  This method then begins the OnEntitySetFinished
        lifecycle (and its associated behavior if a scheduler is present).
    */
    virtual void OnEntitySetFinished();

    /**
        Call this function to invoke the lifecycle_OnDestroy for an entity.  If a scheduler is
        present this will invoke the OnDestroy behavior.  In order to destroy the entity it may be
        neccessary to first remove the entity from the world, which will be done automatically if
        required.
    */
    virtual void Destroy();

    /**
        Called when the entity is removed from the EntityManager.  Passes the word on to any
        built-in models in the entity so that they can perform cleanup tasks.
    */
    virtual void OnRemoved();

    /**
        Call this function to invoke the lifecycle_OnEnterWorld for an entity. If a scheduler is
        present this will invoke the OnEnterWorld behavior.
    */
    virtual void EnterWorld();

    /**
        Call this function to invoke the lifecycle_OnExitWorld for an entity. If a scheduler is
        present this will invoke the OnExitWorld behavior.
    */
    virtual void ExitWorld();

    /// Lifecycle values for use in _OnLifecycleEvent and related methods.
    enum LifeCycles
    {
        /// Invalid lifecycle event
        lifecycle_Invalid,

        /// Called after Entity has been created
        lifecycle_OnCreate,

        /// Called after all assets the Entity requires are loaded
        lifecycle_OnAssetsLoaded,

        /// Called after all Entity objects in the same block file have had OnCreate called
        lifecycle_OnEntitySetFinished,

        /// Called after the Entity has been placed in the world
        lifecycle_OnEnterWorld,

        /// Called after the Entity has been removed from the world
        lifecycle_OnExitWorld,

        /// Called just before the Entity is destroyed
        lifecycle_OnDestroy,

        MAX_ENTITY_LIFECYCLE
    };

protected:

    /**
        Helper to invoke lifestyle event behaviors on myself.

        @param[in] lifecycle Lifecycle event to invoke.
        @param[in] spParameterList ParameterList passed to the Lifecycle event (optional).
        @return True if a behavior was queued for this lifecycle event.
    */
    bool _OnLifecycleEvent(efd::UInt32 lifecycle, efd::ParameterList* spParameterList = 0);

    /**
        Called when a lifecycle behavior is about to be invoked.
        @param[in] lifecycle Lifecycle event to invoke.
    */
    virtual void BeginLifecycle(efd::UInt32 lifecycle);

    /**
        Called as part of EndLifecycle behavior before
        @param[in] lifecycle Lifecycle event to invoke.
        @return Next lifecycle to run.
    */
    virtual LifeCycles ProcessEndLifecycle(efd::UInt32 lifecycle);

    /**
        Called when a lifecycle behavior has completed.
        @param[in] lifecycle Lifecycle event to invoke.
    */
    virtual void EndLifecycle(efd::UInt32 lifecycle);

    /// Returns the behavior name for a given lifecycle event
    virtual const char* GetLifecycleName(efd::UInt32 lifecycle);

    /**
        Sets the flag that this entity is being initialized or
        streamed in at initialization.  This allows read-only
        properties to be set.

        @param[in] initFlag True indicating entity is being initialized.
    */
    void SetInit(efd::Bool initFlag);

    /**
        Sets the pointer to our "manager" service.  This acts as our link back to the
        EntityManager and through that to ServiceManager and to other system services.
        This is set by the EntityManager itself when we are added and gets set to NULL
        when we are removed.

        @param[in] pMgr Pointer to entity manager instance that owns us.
    */
    inline void SetEntityManager(egf::EntityManager* pMgr);

    /**
        Sets the unique ID of the entity.

        @param[in] entityID Reference to entity ID class to set.
    */
    inline void SetID(const EntityID& entityID);

    /**
        Sets the pointer to the flat model for this entity.

        @param[in] flatModel Reference to flat model class.
    */
    inline void SetModel(const FlatModel* flatModel);

    /// Attempt to cancel every behavior in the active queue
    void CancelActiveBehaviors();

    /// A helper used by ApplyProperties that sets the value of a single property by serializing
    /// the new value from an archive. Performs existence and type checks before attempting the
    /// serialization.
    PropertyResult SetPropertyValueFromArchive(
        PropertyID propID,
        efd::ClassID typeOfDataInBuffer,
        efd::Archive& io_ar);

    /// Helper for generating memory leak reports
    static void LeakDump(void* pMem, char* o_buffer, unsigned int i_cchBuffer);

    /// The ID for this entity.
    EntityID m_entityID;

    /// Pointer to this entity's flat model.
    efd::SmartPointer<const FlatModel> m_pFlatModel;

    /// Keeps us linked back to our managing service and through that to the ServiceManager.
    /// Set when we are added to EntityManager, cleared after we are removed.
    egf::EntityManager* m_pEntityManager;

    /// Standard Pointer to our scheduler executor (if present) - Not a smart pointer to prevent
    /// it from holding a reference to the scheduler and preventing the scheduler from being freed.
    egf::Scheduler* m_pScheduler;

    /// a sorted queue of pending behaviors.  Used when behaviors are queued when we have no
    /// Scheduler or when we have too many outstanding behaviors.
    SchedulerQueue m_pendingBehaviorQueue;

    /// @name Used to keep track of all active behaviors to support cases like deletion of an
    /// active entity.
    //@{
    typedef efd::set< egf::EventID > ActiveBehaviorSet;
    ActiveBehaviorSet m_activeBehaviors;
    //@}

    /// The count of pending events in both the global queue and my backup local queue
    efd::SInt32 m_pendingBehaviorCount;

    /// The count of pending and executing behaviors for this entity.
    efd::SInt32 m_executingBehaviorCount;

    /// various flag bits used by the entity
    efd::UInt32  m_flagBits;

    /// the data file ID for this entity if loaded from a block file
    efd::ID128 m_dataFileID;

    /// the block instance ID for this entity if loaded from a block file
    efd::UInt32 m_blockInstance;

    /// the iteration counter for entity loaded from a block file
    efd::UInt32 m_iterationCount;

    /// Set of pending EntityIDs to behavior names to invoke when those entities are created.
    typedef efd::map<egf::EntityID, efd::utf8string> PendingEntityCreateBehaviorMap;
    PendingEntityCreateBehaviorMap m_pendingEntityCreateBehaviors;
};


} // end namespace egf

#include <egf/Entity.inl>

#endif // EE_ENTITY_H
