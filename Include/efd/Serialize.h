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
#ifndef EE_SERIALIZE_H
#define EE_SERIALIZE_H


#include <efd/Archive.h>
#include <efd/ClassIDHelpers.h>


namespace efd
{

/**
    The Serialize namespace methods allow for quick marshaling to or from an Archive.  It is based
    on several primary goals:

       1.) Intended for marshaling to and from binary.  This is not meant to implement different
           output formats like XML or plain text.  Archives are binary only.
       2.) Only require a single function to be implemented.  Common marshaling implementations
           tend to use "to" and "from" functions such as separate << and >> functions.  These
           functions tend to be virtually identical and MUST exactly match in order to function, so
           why not just use a single function instead?
       3.) Must support non-intrusive usage.  You may need to serialize data types from third
           party libraries.  This means you can't rely on a common base class or class function
           to do the work (although by default we allow a member function to do the required
           work).
*/
namespace Serializer
{

/**
    By default you can serialize any object that implements a "Serialize" function.  This
    allows objects to marshal themselves without needing to change code outside the object.
    It also makes it easy to write generic code that marshals unknown types since any type
    should be passable to SerializeObject. The only objects that should not be passed to
    this method are container types that should use serialization behaviors instead.

    @param io_object the object to be serialized.
    @param io_archive The archive for serializing the data
*/
    template<typename T>
void SerializeObject(T& io_object, efd::Archive& io_archive)
{
    io_object.Serialize(io_archive);
}

/**
    Constant objects can be packed but not unpacked.  Even though the goal of this
    marshaling system is to pack and unpack using the exact same function sometimes you
    may need to deviate from that with separate const packing and non-const unpacking
    code branches.

    @param io_object the object to be serialized.
    @param io_archive The archive for serializing the data
*/
template< typename T >
void SerializeConstObject(const T& io_object, efd::Archive& io_archive)
{
    // We can't unpack into a const without violating const-ness
    EE_ASSERT(io_archive.IsPacking());
    SerializeObject(const_cast<T&>(io_object), io_archive);
}


/**
    For serializing plain-old-data types (integers, floats, enums). The data is byte swapped
    between the archive endianness and the hardware endianness as needed.

    @param i_primitive the primitive type data to serialize.
    @param io_archive The archive for serializing the data
*/
template<typename T>
inline void SerializePrimitive(T& i_primitive, efd::Archive& io_archive)
{
    efd::UInt8* pBuffer = io_archive.GetBytes(sizeof(i_primitive));
    if (pBuffer)
    {
        if (io_archive.IsPacking())
        {
            io_archive.MaybeSwap(i_primitive, *(T*)pBuffer);
        }
        else
        {
            io_archive.MaybeSwap(*(T*)pBuffer, i_primitive);
        }
    }
}


/**
    Simply memcpy some bytes into or out of the archive.  i_pData must point to at least
    i_cbData bytes worth of storage or this can crash.  This differs from SerializePrimitive
    in that it doesn't address endianness of the data.  The caller is responsible for ensuring
    that endianness is correctly handled; if you will transfer the resulting buffer between
    hardware with different endianness it is recommended that the raw data be in network byte
    order (for example, it could be the contents of a previously marshaled archive).

    @param i_pData the data buffer which must point to at least i_cbData bytes.
    @param i_cbData The size of the buffer (the data must fit within this size)
    @param io_archive The archive for serializing the data
*/
EE_EFD_ENTRY void SerializeRawBytes(
    efd::UInt8* i_pData,
    efd::UInt32 i_cbData,
    efd::Archive& io_archive);


/**
    Serialize method for NULL terminated string buffers of known max size.

    @param io_string the string buffer which must point to at least i_bufferSize characters.
    @param i_bufferSize The size of the buffer (the string must fit within this size)
    @param io_archive The archive for serializing the data
*/
EE_EFD_ENTRY void SerializeStringBuffer(
    char* io_string,
    efd::UInt32 i_bufferSize,
    efd::Archive& io_archive);


/**
    This behavior is for placing sentinel values into an archive.  A sentinel is just a known
    constant value; sometimes it is helpful for debugging purposes to stick an easily identifiable
    marker into the archive.  When unpacking, if the value in the stream does not exactly match
    the sentinel value then an error is raised.  You could also think of this value as being a
    version number if only a single version is supported at run-time.

    @param i_object the value to be serialized.
    @param io_archive The archive for serializing the data
*/
template<typename T>
void SerializeMagicValue(const T& i_object, efd::Archive& io_archive)
{
    if (io_archive.IsPacking())
    {
        SerializeConstObject(i_object, io_archive);
    }
    else
    {
        T temp;
        SerializeObject(temp, io_archive);
        if (!(temp == i_object))
        {
            io_archive.RaiseError();
        }
    }
}

} // end namespace Serializer
} // end namespace efd



/// @def EE_SPECIALIZE_SERIALIZE
/// Use this macro if you want to quickly provide a default SerializeObject implementation
/// based on one of the standard function types above.  This is normally only done for atomic
/// types and enums, classes and structs should simply implement the Serialize function. This
/// macro should be used from the global scope, not inside another namespace, as it places all
/// of the overriding methods into the efd::Serializer namespace.
#define EE_SPECIALIZE_SERIALIZE(TYPE, SERIALIZEFUNCTION)                                \
namespace efd                                                                           \
{                                                                                       \
    namespace Serializer                                                                \
    {                                                                                   \
        template<>                                                                      \
        inline void SerializeObject<TYPE>(TYPE& io_object, efd::Archive& io_archive)    \
        {                                                                               \
            SERIALIZEFUNCTION(io_object, io_archive);                                   \
        }                                                                               \
    }                                                                                   \
}

/**
    A quick and easy way to configure an enum to serialize as if it was another POD type. This
    will also specialize the ClassID for the enum to act like the other type which will allow the
    enum type to be used in ParameterList. For enums this should be used instead of the
    EE_SPECIALIZE_SERIALIZE macro.
*/
#define EE_SPECIALIZE_ENUM(ENUMTYPE, TREATAS)                                                   \
namespace efd                                                                                   \
{                                                                                               \
    inline efd::ClassID GetClassIDFromObject(const ENUMTYPE&)                                   \
    {                                                                                           \
        return efd::GetClassIDFromType<TREATAS>();                                              \
    }                                                                                           \
    template<>                                                                                  \
    inline efd::ClassID GetClassIDFromType<ENUMTYPE>()                                          \
    {                                                                                           \
        return efd::GetClassIDFromType<TREATAS>();                                              \
    }                                                                                           \
    namespace Serializer                                                                        \
    {                                                                                           \
        template<>                                                                              \
        inline void SerializeObject<ENUMTYPE>(ENUMTYPE& io_object, efd::Archive& io_archive)    \
        {                                                                                       \
            TREATAS value = (TREATAS)io_object;                                                 \
            SerializeObject<TREATAS>(value, io_archive);                                        \
            io_object = (ENUMTYPE)value;                                                        \
        }                                                                                       \
    }                                                                                           \
}

// Specialize the POD types using the root C++ types whenever possible.  If you specialize on
// derived typedefs of these types instead then GCC will barf when it sees the source type and will
// not apply the correct partial template specialization.  It seems to work the other way around
// though.
EE_SPECIALIZE_SERIALIZE(efd::SInt8,       SerializePrimitive);
EE_SPECIALIZE_SERIALIZE(efd::SInt16,      SerializePrimitive);
EE_SPECIALIZE_SERIALIZE(efd::SInt32,      SerializePrimitive);
EE_SPECIALIZE_SERIALIZE(efd::SInt64,      SerializePrimitive);
EE_SPECIALIZE_SERIALIZE(efd::UInt8,       SerializePrimitive);
EE_SPECIALIZE_SERIALIZE(efd::UInt16,      SerializePrimitive);
EE_SPECIALIZE_SERIALIZE(efd::UInt32,      SerializePrimitive);
EE_SPECIALIZE_SERIALIZE(efd::UInt64,      SerializePrimitive);
EE_SPECIALIZE_SERIALIZE(efd::Float32,     SerializePrimitive);
EE_SPECIALIZE_SERIALIZE(efd::Float64,     SerializePrimitive);


namespace efd
{
namespace Serializer
{
    // Using "EE_SPECIALIZE_SERIALIZE(bool, SerializeAsNBit<8>)" generates compile errors because
    // template parameters don't mix with macros so instead I'll do a custom implementation for
    // bool.
    template<>
    inline void SerializeObject<bool>(bool& io_bool, efd::Archive& io_archive)
    {
        efd::UInt8 data = io_bool;
        SerializeObject(data, io_archive);

        // might as well verify we actually unpacked a valid boolean value:
        EE_ASSERT(0 == data || 1 == data);

        // Convert to 0 or 1 just in case
        io_bool = (0 != data);
    }

} // end namespace Serializer
} // end namespace efd

// Note: non-POD efd data types are specialized in <efd/SerializeEfdHelpers.h>


#endif // EE_SERIALIZE_H
