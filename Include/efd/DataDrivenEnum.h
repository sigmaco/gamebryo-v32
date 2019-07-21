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
#ifndef EE_DataDrivenEnum_h
#define EE_DataDrivenEnum_h

#include <efd/utf8string.h>

namespace efd
{

    /// Enumeration Type.  Normal means sequential integer values.  Bitwise means sequential
    /// powers of two such that each value has only one bit set.
    enum EnumType
    {
        et_Invalid,
        et_Normal,
        et_Bitwise,
    };

    /// Templated function to allow enumeration of alternate types.  For all integer types the
    /// default value of zero should work fine, but if you wanted an enumeration of, say, a class
    /// like Category you might want some other default value so you can provide an override of
    /// this method.
    template< typename T >
    T DefaultInvalidValue()
    {
        return (T)(0);
    }

    // Forward declare
    template< typename T > class DataDrivenEnum;

    /// Base class for data driven enumerations.
    class DataDrivenEnumBase : public efd::RefCount
    {
    public:
        /// Get the name of this enumeration.  All enumerations should have a unique name.
        inline const efd::utf8string& GetName() const;

        /// Get the type of this enumeration.  One of either Normal or Bitwise, the type determines
        /// how new values are assigned to the enumer, either as sequential integers or as single
        /// bit values.
        inline EnumType GetEnumType() const;

        /// Get a class ID defining the type of data stored in this enum.
        inline efd::ClassID GetStorageType() const;

        /**
            Cast this enum to an enum with the given storage type.  Example:
            @code
                efd::DataDrivenEnum<efd::UInt32>* pResult = pEnum->CastTo<efd::UInt32>();
            @endcode
            @return NULL if this enum does not have the matching storage type, this otherwise.
        */
        template< typename T > efd::DataDrivenEnum<T>* CastTo();

        /**
            Cast this enum to a const enum with the given storage type.  Example:
            @code
                const efd::DataDrivenEnum<efd::UInt32>* pResult = pEnum->CastTo<efd::UInt32>();
            @endcode
            @return NULL if this enum does not have the matching storage type, this otherwise.
        */
        template< typename T > const efd::DataDrivenEnum<T>* CastTo() const;

        /// Determine whether this enum derives from another enum
        inline bool HasBaseEnum() const;

        /// Fetch the base enumeration
        inline DataDrivenEnumBase* GetBaseEnum() const;

    protected:
        inline DataDrivenEnumBase(const efd::utf8string& i_name,
                                   efd::EnumType i_type,
                                   efd::ClassID i_storage);

        efd::utf8string m_name;
        EnumType m_type;
        efd::ClassID m_storage;

        /// The base enum that I inherit from.  The parent enum must have the same storage type.
        efd::SmartPointer< DataDrivenEnumBase > m_spParent;
    };
    typedef efd::SmartPointer<DataDrivenEnumBase> DataDrivenEnumPtr;


    template< typename T >
    class DataDrivenEnum : public efd::DataDrivenEnumBase
    {
    public:
        /// Constructor
        //@{
        DataDrivenEnum(const efd::utf8string& i_name, efd::EnumType i_type);
        DataDrivenEnum(const efd::utf8string& i_name, DataDrivenEnum<T>* pParentEnum);
        //@}

        /// Lookup the value for a given name.
        bool FindEnumValue(const efd::utf8string& i_name, T& o_value);

        /// Lookup the name for a given value.
        bool FindEnumName(const T& i_value, efd::utf8string& o_name);

        /// Get the named value, if present.  If not present, the "Invalid" value will be returned.
        /// If no "invalid" value was specified and the name is not found, zero will be returned.
        T GetEnumValue(const efd::utf8string& i_name);

        /// Get the name of the given value.  If the value is not found, a name will be built using
        /// the name of this enumeration and the numerical value.  For example:
        ///      <MyEnum 0x00001234>
        efd::utf8string GetEnumName(const T& i_value);

        /// Check if the given name is in the enum
        bool HasName(const efd::utf8string& i_name) const;

        /// Check if the given value is in the enum
        bool HasValue(const T& i_value) const;

        /// Fetch the base enumeration
        DataDrivenEnum<T>* GetBaseEnum() const;

    protected:
        /// My invalid entry info.  Note that the invalid entry also lives in the maps.
        //@{
        bool m_fUseInvalid;
        efd::utf8string m_invalidName;
        T m_invalidValue;
        //@}

        /// The maps to and from name and value.
        //@{
        typedef efd::map< efd::utf8string, T > NameToValueMap;
        NameToValueMap m_nameToValue;

        typedef efd::map< T, efd::utf8string > ValueToNameMap;
        ValueToNameMap m_valueToName;
        //@}
    };


} // end namespace efd

#include <efd/DataDrivenEnum.inl>

#endif // EE_DataDrivenEnum_h
