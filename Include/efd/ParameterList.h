// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 2006-2009 Todd Berkebile.
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef EE_PARAMETERLIST_H
#define EE_PARAMETERLIST_H


#include <efd/ClassIDHelpers.h>
#include <efd/SerializeEfdHelpers.h>

namespace efd
{

// Forward declaration
class ParameterList;

/// Return values used by various ParameterList methods.
enum ParameterResult
{
    /// Success
    pr_OK,
    /// Parameter index is greater than the number of parameters
    pr_OutOfRange,
    /// Parameter name is invalid. It could be already in use during an add or not found during
    /// a get.
    pr_BadName,
    /// The parameter type does not match the requested type
    pr_TypeMismatch,
    /// The storage or retrieval of the data failed (bad/missing Serialize support for this
    /// data type? This can result from missing header files for specializing the data type.)
    pr_DataError,
    /// The container type does not match, for example you added a list but tried to read out a
    /// scalar or a map.
    pr_ContainerMismatch,
};

/// Container types used by the ParameterList class. The AddParameter and GetParameter methods are
/// specialized to support each of these types.
enum ContainerType
{
    /// An invalid container type value
    ct_Invalid,
    /// container type is a single scalar value. This is basically the "not a container" type.
    ct_Scalar,
    /// container type is an efd::list<T> where T is the GetParameterDataType class.
    ct_List,
    /// container type is an efd::map<efd::utf8string, T> where T is the GetParameterDataType class.
    ct_Map_StringKeyed,
};

/**
    An interface for defining a conversion function that can convert various parameter types into
    other closely related types. For example you might allow automatic conversion from UInt32 to
    UInt64 or from SInt32 to UInt32. If desired you can even support translations that would
    truncate or approximate the data.

    @note The EntityManager class in Game Framework registers some default property converters. No
        converters are registered by the Foundation itself.
*/
class EE_EFD_ENTRY IParameterConverter : public efd::MemObject
{
public:
    /**
        Method to retrieve a parameters from a ParameterList as a type other than the type stored
        in the list. Each converter only handles a specific destination type and a specific source
        type. A void pointer is passed in that is guaranteed to point to an instance of the
        destination type based on the ClassID value used to register the converter with the
        ParameterConverterManager class. The parameter list at the given index should always be of
        matching source type as well.

        @param[in] i_params The ParameterList from which to read a value
        @param[in] i_index The index of the value to read
        @param[out] o_result A non-NULL pointer to an instance of the correct destination type
    */
    virtual ParameterResult GetParameter(
        const ParameterList& i_params,
        efd::UInt32 i_index,
        void* o_result) const = 0;

    /// Virtual destructor
    virtual ~IParameterConverter();
};

/**
    An assignment function that can convert between two different but compatible types. If your
    assignment requires special conversion then you can specialize this template function to
    change the behavior, otherwise the default behavior is to simply use operator= with a c-style
    cast to prevent warnings. This default behavior is suitable for converting integer types where
    truncation is not a concern or converting between enumerated types and integers. The default
    can also take advantage of constructors as the compiler can generate an implicit call.

    Implementing ConvertingAssignment for two given types allows those types to be used with the
    ParameterConverter templated class in order to convert types in a ParameterList. For
    convenience such a converter can be defined and registered simply by using either the
    MakeDefaultConverter or MakeDefaultBidirectionalConverters convenience methods on the
    ParameterConverterManager class. To use the bidirectional converter you will need two
    ConvertingAssignment implementations, one going each way, although the default implementation
    might work for one direction but not the other.

    @param[out] o_out The destination variable to be set
    @param[in] i_in The desired value that needs to be converted to the correct type
*/
template<typename FROM, typename TO>
void ConvertingAssignment(TO& o_out, const FROM& i_in)
{
    o_out = (const TO)i_in;
}

/**
    A default implementation of IParameterConverter that should work for any two types that
    support the efd::ConvertingAssignment method. By simply providing a specialization of this
    assignment method you can plug an instance of this class into ParameterList to perform
    automatic type conversions.
*/
template<typename FROM, typename TO>
class ParameterConverter : public IParameterConverter
{
public:
    ParameterResult GetParameter(
        const ParameterList& i_params,
        efd::UInt32 i_index,
        void* o_result) const;
};

/**
    Class for managing a static set of converters and exposing them to the ParameterList class.
*/
class EE_EFD_ENTRY ParameterConverterManager : public MemObject
{
protected:
    static inline efd::UInt64 MakeConverterID(efd::ClassID from, efd::ClassID to);

public:
    /**
        Pass ownership of a parameter converter to manager. The manager will EE_DELETE the
        converter during SDMShutdown.
    */
    static void RegisterConverter(
        efd::ClassID from,
        efd::ClassID to,
        IParameterConverter* converter);

    /**
        Generate a converter to allow translation of one type to another type.  The types used
        must support the efd::ConvertingAssignment templated method. To use your own custom type
        just ensure the efd::ConvertingAssignment specialization is defined prior to calling this
        method.
    */
    template<typename FROM, typename TO>
    static void MakeDefaultConverter();

    /**
        Generate bi-directional converts for any two types that support the
        efd::ConvertingAssignment templated method. To use your own custom type just ensure the
        efd::ConvertingAssignment specialization is defined prior to calling this method.
    */
    template<typename FROM, typename TO>
    static void MakeDefaultBidirectionalConverters();

    /**
        Find a previously registered converter.
    */
    static IParameterConverter* FindConverter(efd::ClassID from, efd::ClassID to);

    /**
        This will EE_DELETE a single converter, if found.
    */
    static bool RemoveConverter(efd::ClassID from, efd::ClassID to);

    /**
        This will EE_DELETE all registered converters. Called automatically during SDM shutdown.
    */
    static void RemoveAllConverters();

    typedef efd::map<UInt64, IParameterConverter*> ConverterMap;
    static ConverterMap ms_converters;
};

/**
    A list of variable type parameters.

    When using this class with custom parameter types, be sure to include the header files that
    define the efd::GetClassIDFromType and efd::Serializer::SerializeObject specializations for
    your data type.
*/
class EE_EFD_ENTRY ParameterList : public ParameterConverterManager
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CONCRETE_REFCOUNT
    /// @endcond

public:
    /// Constructor
    ParameterList();

    /**
        Adds a new unnamed parameter to the end of the parameter list.

        @param parameter The data being added
        @return The index at which the data was added, or -1 on error
    */
    template<typename T>
    efd::SInt32 AddParameter(const T& parameter);

    /**
        Adds a new named parameter to the end of the parameter list.

        @param name The name of this data item
        @param parameter The data being added
        @return The index at which the data was added, or -1 on error
    */
    template<typename T>
    efd::SInt32 AddParameter(const efd::utf8string& name, const T& parameter);

    /// Get the number of parameters in the list
    inline efd::UInt32 GetSize() const;

    /**
        Read a parameter from the list.

        @param[in] i_index The parameter to read
        @param[out] o_result The resulting value
        @return A ParameterResult indicating the result
    */
    template<typename T>
    ParameterResult GetParameter(efd::SInt32 i_index, T& o_result) const;

    /**
        Read a scalar parameter from the list.

        @param[in] i_index The parameter to read
        @param[out] o_result The resulting value
        @return A ParameterResult indicating the result
    */
    template<typename T>
    ParameterResult GetParameter(efd::UInt32 i_index, T& o_result) const;

    /**
        Read a list-style parameter from the list.

        @param[in] i_index The parameter to read
        @param[out] o_result The resulting value
        @return A ParameterResult indicating the result
    */
    template<typename T>
    ParameterResult GetParameter(efd::UInt32 i_index, efd::list<T>& o_result) const;

    /**
        Read a map-style parameter from the list.

        @param[in] i_index The parameter to read
        @param[out] o_result The resulting value
        @return A ParameterResult indicating the result
    */
    template<typename T>
    ParameterResult GetParameter(efd::UInt32 i_index, efd::map<efd::utf8string, T>& o_result) const;

    /**
        Read a parameter from the list by name. This method looks up the index for the given name
        and then calls the index version of GetParameter.

        @param[in] i_pszName The parameter to read
        @param[out] o_result The resulting value
        @return A ParameterResult indicating the result
    */
    template<typename T>
    ParameterResult GetParameter(const char* i_pszName, T& o_result) const;

    /**
        Checks the data type and container type of the given parameter against the templated type.
        The specified type T must either be a supported scalar type, an efd::list<X>, or an
        efd::map<efd::utf8string, X> (where X is a supported scalar type).

        @note Attempting to pass any other container type will normally result is a compiler error
        since efd::GetClassIDFromType<T> is unlikely to be defined for a container.
    */
    template<typename T>
    bool IsExactKind(efd::UInt32 i_index);

    /**
        Check the data type of a parameter.

        @param i_index The parameter to read
        @return The type of the parameter, or kInvalidClassID if the index is out of range.
    */
    efd::ClassID GetParameterDataType(efd::UInt32 i_index) const;

    /**
        Check the container type of a parameter. Parameters can either be a single scalar value, a
        list of values or a map of strings to value. In all cases, the GetParameterDataType method
        describes the data type of the value.

        @param i_index The parameter to read
        @return The containter type of the parameter, or ct_Invalid if the index is out of range.
    */
    efd::ContainerType GetParameterContainerType(efd::UInt32 i_index) const;

    /**
        Get the name of a parameter by index. Not all parameters have names in which case this
        method will return a NULL pointer. Do not cache the returned pointer as it can become
        invalid if new items are added to the parameter list.

        @param i_index The parameter to read
        @return The name of the parameter, or NULL if the index is out of range or unnamed.
    */
    const char* GetParameterName(efd::UInt32 i_index) const;

    /**
        Get the index of the named parameter.

        @note This method is O(N).

        @param pszName The parameter name for which to find the index.
        @return The parameter index, or -1 if the named parameter was not found.
    */
    efd::SInt32 GetIndexFromName(const char* pszName) const;

    /**
        Serialize method for marshaling ParameterList in or out of an Archive
    */
    void Serialize(efd::Archive& io_ar);

    /**
        Get the storage window into which the parameter was stored.
    */
    const efd::SmartBuffer GetParameterStorage(efd::UInt32 index);

    /// Helper for generating memory leak reports
    static void LeakDump(void* pMem, char* o_buffer, unsigned int i_cchBuffer);

protected:
    efd::Archive PrepareNewParameter();
    void SetParameterName(const efd::utf8string& name, efd::Archive& ar);

    template<typename T> void SetParameterData(const T& parameter, efd::Archive& ar);
    template<typename T> void SetParameterData(const efd::list<T>& parameter, efd::Archive& ar);
    template<typename T>
    void SetParameterData(const efd::map<efd::utf8string, T>& parameter, efd::Archive& ar);

    efd::SInt32 FinishNewParameter(efd::Archive& ar);

    template<typename T> bool IsExactKindHelper(efd::UInt32 i_index, const T&);
    template<typename T> bool IsExactKindHelper(efd::UInt32 i_index, const efd::list<T>&);
    template<typename T>
    bool IsExactKindHelper(efd::UInt32 i_index, const efd::map<efd::utf8string, T>&);

    struct ParameterTypeInfo
    {
        efd::ClassID m_dataType;
        efd::UInt16 m_nameOffset;
        efd::UInt16 m_nameSize;
        efd::UInt16 m_offset;
        efd::UInt16 m_size;
        efd::UInt8 m_container;

        /// Serialize ParameterTypeInfo to or from an Archive
        void Serialize(efd::Archive& io_ar);
    };

    efd::SmartBuffer m_parameterStorage;
    efd::vector<ParameterTypeInfo> m_typeInfo;
};

/// A SmartPointer for the ParameterList class
typedef efd::SmartPointer<ParameterList> ParameterListPtr;

} // end namespace efd

#include <efd/ParameterList.inl>

#endif // EE_PARAMETERLIST_H
