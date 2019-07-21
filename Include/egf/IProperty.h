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
#ifndef EE_IPROPERTY_H
#define EE_IPROPERTY_H

#include <efd/UniversalTypes.h>
#include <efd/utf8string.h>
#include <egf/egfLibType.h>
#include <egf/EntityTypes.h>

namespace egf
{

/**
    An enum that describes the result of entity property operations.
*/
enum PropertyResult
{
    /// Success
    PropertyResult_OK,
    /// The property type does not match
    PropertyResult_TypeMismatch,
    /// A PropertyDescriptor has no default value when one is required
    PropertyResult_NoDefaultValue,
    /// The given property is not available
    PropertyResult_PropertyNotFound,
    /// A PropertyDescriptor already has a default value and cannot accept a new one
    PropertyResult_DefaultValueAlreadySet,
    /// The type of the property is not a known valid type
    PropertyResult_UnknownPropertyType,
    /// A property request was made on an entity with no FlatModel
    PropertyResult_ModelNotFound,
    /// Scalar method used with associative array property
    PropertyResult_PropertyNotScalar,
    /// Associative array method used with scalar property
    PropertyResult_PropertyNotAssociativeArray,
    /// Associative array property method used a key that is not valid
    PropertyResult_KeyNotFound,
    /// Attempted to write to a read-only property
    PropertyResult_ReadOnlyError,
    /// Attempted to write to a property on a replica entity
    PropertyResult_EntityNotOwned,
    /// An unknown error occurred
    PropertyResult_UnknownError,
    /// A property related method is operating on an entity ID for which no entity was found
    PropertyResult_EntityNotFound,
    /// An associative array key iterating method already returned all keys
    PropertyResult_NoMoreKeys,
    /// An error occurred serializing a property value, for example an invalid ParameterList could
    /// have been passed to Entity::ApplyProperties.
    PropertyResult_SerializationError,
};

#if !defined(SWIG)

/// Helper to map a @ref egf::PropertyResult enumeration into a string name
/// @param value The enumeration value to get the name
EE_EGF_ENTRY efd::utf8string TranslatePropertyResult(egf::PropertyResult value);


/**
    The interface that all property types and built-in models derive from.
*/
class EE_EGF_ENTRY IProperty : public efd::MemObject
{
public:

    /// Virtual destructor.
    inline virtual ~IProperty();

    /**
        Assigns the current value of this property to the data parameter.  If this is a built-in
        model, then data is set to the current value of the specified sub-property.

        No type safety is assumed at this level. Type safety is enforced at the Entity class where
        any call reaching these methods should be coming from. IProperties are never exposed
        through the Entity interface.

        The default implementation simply returns PropertyResult_PropertyNotScalar.

        @param propID The property ID to fetch data for.  This is useful for built-in models
            that have multiple sub-properties.
        @param data Pointer to where to assign the value of this property to
        @return A value from the EntityError enum indicating success/failure
    */
    virtual PropertyResult GetValue(PropertyID propID, void* data) const;

    /**
        Assigns the value of the data parameter to this property.  If this is a built-in model,
        then the value of the specified sub-property is set.

        No type safety is assumed at this level.  Type safety is enforced at the Entity class
        where any call reaching these methods should be coming from.  IProperties are never
        exposed through the Entity interface.

        The default implementation simply returns PropertyResult_PropertyNotScalar.

        @param propID The property ID to set the value of.  This is useful for built-in models
            that have multiple sub-properties.
        @param data Pointer to where to copy the data from
        @return A value from the EntityError enum indicating success/failure
    */
    virtual PropertyResult SetValue(PropertyID propID, const void* data);

    /**
        Assigns the current value of the specified key of this property to the data parameter.
        If this is a built-in model, then data is set to the current value of the specified
        key of the specified sub-property.

        No type safety is assumed at this level. Type safety is enforced at the Entity class where
        any call reaching these methods should be coming from. IProperties are never exposed
        through the Entity interface.

        The default implementation simply returns PropertyResult_PropertyNotAssociativeArray.

        @param propID The property ID to fetch data for.  This is useful for built-in models
            that have multiple sub-properties.
        @param key The key of the map to retrieve the value from
        @param data Pointer to where to assign the value of this property to
        @return A PropertyResult value indicating success/failure
    */
    virtual PropertyResult GetValue(
        PropertyID propID,
        const efd::utf8string& key,
        void* data) const;

    /**
        Assigns the value of the data parameter to the specified key of this property.  If this
        is a built-in model, then the specified key of the specified sub-property is set.

        No type safety is assumed at this level. Type safety is enforced at the Entity class
        where any call reaching these methods should be coming from.  IProperties are never
        exposed through the Entity interface.

        The default implementation simply returns PropertyResult_PropertyNotAssociativeArray.

        @param propID The property ID to set the value of.  This is useful for built-in models
            that have sub-properties.
        @param key The key of the map to set the value of
        @param data Pointer to where to copy the data from
        @return A value from the PropertyResult enum indicating success/failure
    */
    virtual PropertyResult SetValue(
        PropertyID propID,
        const efd::utf8string& key,
        const void* data);

    /**
        Assigns a string representation of the current value of this property to the data parameter.
        If this is a built-in model, then data is set to the current value of the specified
        sub-property.

        @param propID The property ID to fetch data for. This is useful for built-in models that
            have multiple sub-properties.
        @param data String to hold the value of the property.
        @return A value from the PropertyResult enum indicating success/failure.
    */
    virtual PropertyResult GetValueAsString(
        PropertyID propID,
        efd::utf8string& data) const;

    /**
        Sets the value of this property by string.  This is to allow for the creation of properties
        from values stored in files on disk (flat models and block files).  This should not be used
        for normal property value manipulation.

        The default implementation simply returns PropertyResult_PropertyNotScalar.

        @param propID The property ID to set the value of.
        @param data A UTF8 string representation of the data
        @return A value from the PropertyResult enum indicating success/failure
    */
    virtual PropertyResult SetValueByString(PropertyID propID, const efd::utf8string& data);

    /**
        Assigns a string representation of the current value of the specified key of this property
        to the data parameter. If this is a built-in model, then data is set to the current value of
        the specified key of the specified sub-property.

        @param propID The property ID to fetch data for. This is useful for built-in models that
            have multiple sub-properties.
        @param key The key of the map to retrieve the value from.
        @param data String to hold the value of the property.
        @return A value from the PropertyResult enum indicating success/failure.
    */
    virtual PropertyResult GetValueAsString(
        PropertyID propID,
        const efd::utf8string& key,
        efd::utf8string& data) const;

    /**
        Same as SetValueByString, but takes an additional parameter, key, for setting the value of
        an associative array by string.

        The default implementation simply returns PropertyResult_PropertyNotAssociativeArray.

        @param propID The property ID to set the value of.
        @param key The key index of the value.
        @param data A UTF8 string representation of the data
        @return A value from the PropertyResult enum indicating success/failure
    */
    virtual PropertyResult SetValueByString(
        PropertyID propID,
        const efd::utf8string& key,
        const efd::utf8string& data);

    /**
        Get the number of elements in an associative property.

        The default implementation sets o_count to zero and returns
        PropertyResult_PropertyNotAssociativeArray.

        @return A value from the PropertyResult enum indicating success/failure
    */
    virtual PropertyResult GetPropertyCount(PropertyID i_propID, efd::UInt32& o_count) const;


    /**
        Get all the in use keys for an associative property.

        The default implementation clears o_keys and returns
        PropertyResult_PropertyNotAssociativeArray.

        @param[in] i_propID The property ID of an associative property to use
        @param[out] o_keys the keys that are in use
        @return A value from the PropertyResult enum indicating success/failure
    */
    virtual PropertyResult GetPropertyKeys(
        PropertyID i_propID,
        efd::list<efd::utf8string>& o_keys) const;

    /**
        Given a key value, find the next key value. Pass an empty string on the first call to this
        method to get the first key. When the iteration is done this will return PropertyResult_Done
        with an empty o_nextKey.

        The default implementation simply clears o_nextKey and returns
        PropertyResult_PropertyNotAssociativeArray. Overrides do not need to call the base version.

        @param[in] i_propID The property ID of an associative property to use
        @param[in] i_previousKey The previous key, or an empty string to find the first key
        @param[out] o_nextKey The next key, or an empty string if there are no more keys
        @return PropertyResult_KeyNotFound if i_previousKey is not a valid key.
            PropertyResult_NoMoreKeys if i_previousKey refers to the last key.
            PropertyResult_OK if the next key is successfully returned.
    */
    virtual PropertyResult GetNextPropertyKey(
        PropertyID i_propID,
        const efd::utf8string& i_previousKey,
        efd::utf8string& o_nextKey) const;

    /**
        Determines if the given associative property has the specified key.

        @param propID The property ID to remove the value from.
        @param key The key of the item to remove
        @return PropertyResult_OK if the specified property exists, is associative, and has the
            given key. Other PropertyResult values on failure.
    */
    virtual PropertyResult HasValue(PropertyID propID, const efd::utf8string& key) const;

    /**
        Removes a value from an associative property by key.

        The default implementation simply returns PropertyResult_PropertyNotAssociativeArray.

        @param propID The property ID to remove the value from.
        @param key The key of the item to remove
        @return A value from the PropertyResult enum indicating success/failure
    */
    virtual PropertyResult RemoveValue(PropertyID propID, const efd::utf8string& key);

    /**
        Get the type of this property implementation. Every IProperty implementation must have a
        unique property type ClassID.

        @return ClassID The property type of this property
    */
    virtual efd::ClassID GetPropertyType() const = 0;

    /**
        Get the type of the data stored in this property. Many IProperty implementations might store
        the same data type, perhaps with semantic restrictions applied to limit the valid range of
        the data. These implementations would all return the same data type class. Also associative
        properties return the data type stored in their maps. The value returned should be the same
        value that would be returned from efd::GetClassIDFromObject or efd::GetClassIDFromType as
        defined in <efd/ClassIDHelpers.h> for the data type stored inside the property. ClassID
        values for common primitive types are defined in <efd/efdPrimitiveTypeIDs.h> and these
        values are extended in various places.

        @param i_propID The property ID to determine the type of. Only used by multiple property
            providers such as IBuiltinModel.
        @return ClassID The type of the value stored in this property
    */
    virtual efd::ClassID GetDataType(PropertyID i_propID) const = 0;


    /**
        Clones this property, returning a pointer to the newly created instance.  This is used
        for Copy-on-Write, among other things.  The caller is responsible for deleting this
        property.

        @return A new IProperty pointer that is a copy of this one.
    */
    virtual IProperty* Clone() const = 0;


    /**
        Read or write a given property from an archive.

        @note The serialized format for associative properties must match the format obtained by
        calling efd::SR_StdMap<>::Serialize<efd::map<efd::utf8string, T> > where 'T' can be any
        property data type. This is required even for egf::IBuiltinModel implementations of
        associative properties. This restriction allows data transfer between ParameterList
        map-style parameters, egf::TPropertyAssoc based properties and egf::IBuiltinModel based
        associative properties.

        @param i_propID The id of the property being streamed. Only used by multiple property
            providers such as IBuiltinModel.
        @param ar The archive to read or write the class from
    */
    virtual void SerializeProperty(PropertyID i_propID, efd::Archive& ar) = 0;

    /**
        Convenience method to allow packing using a const IProperty. Do not attempt to override
        this method, only override the non-const version. This method simply calls the non-const
        version of the same method after verifying that the stream is packing and thus the
        operation should not modify the IProperty instance.

        @param i_propID The id of the property being streamed. Only used by multiple property
            providers such as IBuiltinModel.
        @param ar The archive to read or write the class from
    */
    inline void SerializeProperty(PropertyID i_propID, efd::Archive& ar) const;

    /**
        Read an instance of myself from the stream just like FromStream but without actually
        modifying my internal state.  In other words, seek the stream forward by my streamed
        size.

        @param i_propID The id of the property being streamed.  Only used by multiple property
            providers such as IBuiltinModel.
        @param ar The archive to read or write the class from
    */
    virtual void AdvanceStream(PropertyID i_propID, efd::Archive &ar) const = 0;

    /// Equality operator. This verifies that the other IProperty has the exact same implementation
    /// and also the same value. Two properties might store the same value but will still be
    /// considered different if they use separate IProperty implementations.
    virtual bool operator==(const IProperty& other) const = 0;
};

#endif // !defined(SWIG)

} // end namespace egf

#include <egf/IProperty.inl>

#endif // EE_IPROPERTY_H
