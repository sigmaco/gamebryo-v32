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
#ifndef EE_PROPERTYDESCRIPTOR_H
#define EE_PROPERTYDESCRIPTOR_H

#include <efd/UniversalTypes.h>
#include <efd/RefCount.h>
#include <egf/IProperty.h>
#include <egf/egfLibType.h>
#include <egf/EntityTypes.h>

namespace egf
{

/**
    A PropertyDescriptor provides information about the property, such as
    its name, ID, type, and default values.
*/
class EE_EGF_ENTRY PropertyDescriptor : public efd::RefCount
{

public:

    enum PropertyMetaType
    {
        PropertyMetaType_Unknown,
        PropertyMetaType_Scalar,
        PropertyMetaType_Assocative,
    };

    /// These constants can be used to access specific bits in the m_updateGroups bit array.
    static const efd::UInt32 MAX_REPLICATION_GROUP_INDEX = 30;
    static const efd::UInt32 PERSISTENCE_GROUP_INDEX    = 31;
    static const efd::UInt32 REPLICATION_GROUP_MASK      = 0x7FFF;


    /// @name Construction and Destruction
    //@{

    /// Constructor
    PropertyDescriptor();

    /// Copy Constructor
    PropertyDescriptor(const PropertyDescriptor& other);

    /// Destructor
    ~PropertyDescriptor();
    //@}

    /// Assignment Operator
    PropertyDescriptor& operator=(const PropertyDescriptor& other);

    /// equality operator
    bool operator==(const PropertyDescriptor& other) const;

    /**
        Retrieves the ClassID of the underlying data type that the property wraps.

        @return The ClassID
    */
    efd::ClassID GetDataClassID() const;

    /**
        Sets the ClassID of the underlying data type that this property manages.  It
        is only valid to call this before a default property has been set.

        @param classID The ClassID
    */
    void SetDataClassID(efd::ClassID classID);

    /**
        Retrieves the ClassID of the IProperty type that holds this property.

        @return The ClassID
    */
    efd::ClassID GetPropertyClassID() const;

    /**
        Sets the ClassID of the IProperty type that holds this property.  It
        is only valid to call this before a default property has been set.

        @param classID The ClassID
    */
    void SetPropertyClassID(efd::ClassID classID);

    /**
        Retrieves the ID of the current property.

        @return The PropertyID
    */
    PropertyID GetPropertyID() const;

    /**
        Sets the PropertyID.

        @param propID The PropertyID
    */
    void SetPropertyID(PropertyID propID);

    /**
        Retrieves the name of the current property.

        @return The Name
    */
    const efd::utf8string& GetName() const;

    /**
        Sets the name of the property.

        @param name The Name
    */
    void SetName(const efd::utf8string& name);

    /**
        Retrieves the value of the specified trait.

        @param trait The trait to check for
        @return Boolean indicating the value of the trait
    */
    efd::Bool GetTrait(PropertyTraits trait) const;

    /**
        Retrieves all traits as a 32bit bitfield.  Useful for testing the equality or the
        traits between two different PropertyDescriptors.

        @return UInt32 bitfield representing all traits.
    */
    efd::UInt32 GetTraits() const;

    /**
        Sets the value of the specified trait.  Note that it is undefined
        behavior of setting a trait after simulation has begun.

        @param trait The trait to set the value of
        @param val Value of the trait
    */
    void SetTrait(PropertyTraits trait, efd::Bool val);

    /**
        Retrieves a bit map of the Replication Groups that are used by this property.

        @return UInt32 bitfield representing all replication groups
    */
    efd::UInt32 GetReplicationGroups() const;

    /**
        Retrieves the value specifying the semantic type.  Currently, this is
        only used by tools to perform additional levels type checking on the
        value.

        @return String specifying the semantic type.
    */
    const efd::utf8string& GetSemanticType() const;

    /**
        Sets the value specifying the semantic type.  Currently, this is only used by tools
        to perform additional levels type checking on the value.

        @param semanticType String specifying the type.
    */
    void SetSemanticType(const efd::utf8string& semanticType);

    /**
        Retrieves the value specifying the source model for a built-in model property.  The
        source model that is also the built-in model name that is used to lookup the IBuiltinModel
        pointer within the owning entity.  Has no meaning for non-built-in properties.

        @return String the source built-in model name.
    */
    const efd::utf8string& GetSource() const;

    /**
        Sets the value specifying the source model for a built-in model property.  The source
        model is also the built-in model name that is used to lookup the IBuiltinModel pointer
        within the owning entity.

        @param source String specifying the source model for a built-in model property.
    */
    void SetSource(const efd::utf8string& source);

    /**
        Returns a pointer to a const IProperty that contains the default value.
        It is unsafe to change the default value at runtime. It is also unsafe to
        save this pointer.

        @return A pointer to a const IProperty
    */
    const IProperty* GetDefaultProperty() const;

    /**
        Sets the default property using an IProperty object.  This is meant to be used during
        initialization time.  It is unsafe to change the default value at runtime.  You must
        call SetPropertyClassID and SetDataClassID before calling this method.  The property
        that is passed in must match all type data.

        @param prop Reference to the IProperty to be used as the default value
        @return PropertyResult indicating the success of the set.
    */
    PropertyResult SetDefaultProperty(const IProperty& prop);

    /**
        Checks our membership in the given update group.

        @param index The group index to check, from 0 to 31
        @return bool indicating whether we are a member of that group
    */
    efd::Bool GetUpdateGroup(efd::UInt32 index) const;

    /**
        Retrieves all the update groups that we are members of.

        @return Bitfield for which groups this property should update into
    */
    efd::UInt32 GetUpdateGroups() const;

    /**
        Sets our membership in the given update group.

        @param index The group index to set
        @param val Membership of that update group
    */
    void SetUpdateGroup(efd::UInt32 index, efd::Bool val);

    /**
        Verifies that all data fields contain valid data and no illegal trait or type combinations
        have been specified.

        @return bool indicating whether the data fields have valid data
    */
    bool IsValid() const;

    /**
        Set the metatype for the property descriptor.
    */
    void SetPropertyMetaType(PropertyMetaType t);

    /**
        Get the metatype for the property descriptor.
    */
    PropertyMetaType GetPropertyMetaType() const;


protected:

    /// Name of the property
    efd::utf8string m_name;

    /// Name of source of the property. This is the model/object name of the built-in model that
    /// exposes this property.
    // DT32312 This could be optimized to simply store the FlatModelID instead of the name
    efd::utf8string m_source;

    /// Semantic types at tool-time are used to restrict valid values, but they have not effect
    /// at runtime other than providing addition info.
    efd::utf8string m_semanticType;

    /// ClassID of the data that is wrapped by the property class
    efd::ClassID m_dataClassID;

    /// ClassID of the property class that stores this property
    efd::ClassID m_propertyClassID;

    /// Property ID
    PropertyID m_propertyID;

    /// Traits of this property
    efd::UInt32 m_traits;

    /// Bitfield for the replication groups that this property should update into.
    efd::UInt32 m_updateGroups;

    /// Default value of this property
    IProperty* m_pDefaultProperty;

    /// The meta type for the property.
    PropertyMetaType m_metatype;
};

/// A smart pointer (reference counting, self deleting pointer) for the PropertyDescriptor class
typedef efd::SmartPointer<PropertyDescriptor> PropertyDescriptorPtr;
typedef efd::list< PropertyDescriptor* > PropertyDescriptorList;


//------------------------------------------------------------------------------------------------
} // end namespace egf

//------------------------------------------------------------------------------------------------
#include "PropertyDescriptor.inl"

#endif // EE_PROPERTYDESCRIPTOR_H
