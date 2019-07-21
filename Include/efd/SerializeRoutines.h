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
#ifndef EE_SERIALIZEROUTINES_H
#define EE_SERIALIZEROUTINES_H

#include <efd/Serialize.h>

// Serialize Routines are a method to extend Serialize for handling certain common data structures
// like serializing a map or list or serializing an array of pointers that need to be allocated
// when unpacking.  It is based on templated structures each with a static Serialize function.  For
// containers you would pass in a "child routine" that would then be used for each child.  Some of
// the templates take allocators or other parameters as well.  This allows you to build complicated
// results like "array of pointers to allocated containers of serializable objects" as easy to use
// typedefs, for example the complex type I listed above might look like:
//
// @code
//     typedef SR_StdVector< SR_Allocate< SR_DefaultAllocator<>, SR_StdList< SR_Default > > >
//         SR_VectorOfListsOfObjects;
//     typedef std::vector< std::list< SerializableClass >* > MyDataType;
//     MyDataType foo;
//     SR_VectorOfListsOfObjects::Serialize(foo, archive);
// @endcode


namespace efd
{

    /// This routine simply does the default templated Serializer::SerializeObject that should
    /// work for pretty much any data type.  It exists for use as a default child routine when
    /// performing more interesting routines on containers.
    struct SR_Default
    {
        template<typename DATATYPE>
        static void Serialize(DATATYPE& io_object, efd::Archive& io_archive)
        {
            Serializer::SerializeObject(io_object, io_archive);
        }
    };


    /// This routine does a default allocation.  It exists to allow overrides if you use a
    /// custom allocator or specific heaps for specific types of data.  The default assumes the
    /// object being allocated is an efd::MemObject and thus uses our special memory manager.
    struct SR_DefaultAllocator
    {
        template<typename DATATYPE>
        void static Allocate(DATATYPE*& o_pObject)
        {
            o_pObject = EE_NEW DATATYPE();
        }
    };

    /// Similar to the default allocator, only it assumes the object should be allocated using
    /// external new.  Use this if the pointed to object is not a efd::MemObject but instead
    /// uses C++ allocation.  Of course if you want to use some other heap then simply implement
    /// your own allocator that does whatever is needed.
    struct SR_ExternalAllocator
    {
        template< typename DATATYPE >
        void static Allocate(DATATYPE*& o_pObject)
        {
            o_pObject = EE_EXTERNAL_NEW DATATYPE();
        }
    };

#if defined(_MSC_VER)
#pragma warning(push)
// The SR_Allocate routine uses a constant conditional template parameter to compile out code
// when it's not needed, but MSVC generates a warning which we then treat as an error.
#pragma warning(disable: 4127)
#endif

    /// Perhaps the simplest useful routine, the SR_Allocate routine takes a pointer and
    /// allocates a new object when unpacking.  The object must have a constructor with no
    /// arguments.
    template< typename ALLOCATOR = SR_DefaultAllocator,
              typename CHILDROUTINE = SR_Default,
              const bool ALLOW_NULL_POINTERS = false >
    struct SR_Allocate
    {
        template<typename DATATYPE>
        static void Serialize(DATATYPE*& io_object, efd::Archive& io_archive)
        {
            if (io_archive.GetError())
            {
                return;
            }

            // If NULL pointers are allowed then we serialize an extra efd::UInt8 per item for the
            // "is null" bit
            if (ALLOW_NULL_POINTERS)
            {
                bool fIsNull = (NULL == io_object);
                Serializer::SerializeObject(fIsNull, io_archive);
                if (fIsNull)
                {
                    io_object = NULL;
                    return;
                }
            }

            if (io_archive.IsUnpacking())
            {
                ALLOCATOR::Allocate(io_object);
            }

            if (!io_object)
            {
                io_archive.RaiseError();
            }
            else
            {
                CHILDROUTINE::Serialize(*io_object, io_archive);
            }
        }
        template<typename DATATYPE>
        static void Serialize(efd::SmartPointer<DATATYPE>& io_object, efd::Archive& io_archive)
        {
            DATATYPE* pData = io_object.data();
            Serialize(pData, io_archive);
            io_object = pData;
        }
    };

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

    /// The FactoryAlloc takes a factory class and allocates based on a TypeID.  You need to
    /// implement the factory yourself, it needs three things: 1.) a typedef for the TypeID, 2.) a
    /// static function to fetch the ID from an existing object, and 3.) a static function to
    /// allocate the correct object given the objects type ID.  For example, a Factory for
    /// registered COM objects might look like (theoretical sample code follows):
    ///
    /// @code
    ///     struct ComFactory
    ///     {
    ///       typedef GUID TypeID;
    ///       static bool GetType(IMyInterface** ppUnk, const GUID& guid)
    ///       {
    ///         guid = (*ppUnk)->GetIID();
    ///         return true;
    ///       }
    ///       static bool Allocate(const GUID& guid, IMyInterface** ppUnk)
    ///       {
    ///         return SUCCEEDED(CoCreateInstance(guid, NULL, 0, IID_IMyInterface, ppUnk));
    ///       }
    ///     }
    /// @endcode
    template<typename FACTORY, typename CHILDROUTINE=SR_Default>
    struct SR_FactoryAlloc
    {
        template<typename DATATYPE>
        static void Serialize(DATATYPE& io_object, efd::Archive& io_archive)
        {
            if (io_archive.GetError())
            {
                return;
            }

            // the "type" determines what type of object the factory will create.  It could be an
            // enum or a GUID or whatever you need to uniquely identify all the object types that
            // the factory can allocate.
            typename FACTORY::TypeID tid;
            if (io_archive.IsPacking())
            {
                // get the type id of this object
                if (!FACTORY::GetType(io_object, tid))
                {
                    io_archive.RaiseError();
                    return;
                }
            }

            Serializer::SerializeObject(tid, io_archive);

            if (io_archive.IsUnpacking())
            {
                if (!FACTORY::Allocate(tid, io_object))
                {
                    io_archive.RaiseError();
                    return;
                }
            }

            // serialize the object.
            if (NULL != io_object)
            {
                CHILDROUTINE::Serialize(*io_object, io_archive);
            }
        }
    };



    /// This routine saves room in the storage media by compressing a 32bit type.  Its very
    /// common to have enums or container sizes that are technically 32 bits long but are expected
    /// to contain small values.  If the value is less than 64 it will pack to a single byte.  Of
    /// course in the worst case it will take 5 bytes so this might not be a good choice if negative
    /// values are expected.
    struct SR_As32Bit_Compressed
    {
        template<typename DATATYPE>
        static void Serialize(DATATYPE& io_object, efd::Archive& io_archive)
        {
            if (io_archive.IsPacking())
            {
                const efd::UInt32 MAX_8BIT  = 0x0000003F;
                const efd::UInt32 MAX_16BIT = 0x00003FFF;
                const efd::UInt32 MAX_32BIT = 0x3FFFFFFF;

                // store the starting point so we can apply the mask to whichever byte gets packed
                // first.
                efd::UInt32 cbStart = io_archive.GetCurrentPosition();

                // cast to unsigned int.  This will convert enums and signed values to a type that
                // will shift and mask properly.
                efd::UInt32 data = (efd::UInt32)io_object;

                efd::UInt8 mask;
                if (data <= MAX_8BIT)       mask = 0x00;
                else if (data <= MAX_16BIT) mask = 0x40;
                else if (data <= MAX_32BIT) mask = 0x80;
                else                        mask = 0xC0;

                efd::UInt8 b0 = 0x00;
                efd::UInt8 b1 = (efd::UInt8)(data >> 24);
                efd::UInt8 b2 = (efd::UInt8)(data >> 16);
                efd::UInt8 b3 = (efd::UInt8)(data >> 8);
                efd::UInt8 b4 = (efd::UInt8)(data);

                switch (mask)
                {
                case 0xC0: Serializer::SerializeObject(b0, io_archive);
                case 0x80: Serializer::SerializeObject(b1, io_archive);
                           Serializer::SerializeObject(b2, io_archive);
                case 0x40: Serializer::SerializeObject(b3, io_archive);
                case 0x00: Serializer::SerializeObject(b4, io_archive);
                }

                // Now we add the mask into the first byte
                efd::UInt8* pFirstByte = io_archive.PeekBytes(cbStart, 1);
                if (!pFirstByte) { return; }
                EE_ASSERT(0 == (*pFirstByte & mask));
                *pFirstByte |= mask;
            }
            else if (io_archive.IsUnpacking())
            {
                efd::UInt8 highByte = 0;
                Serializer::SerializeObject(highByte, io_archive);

                efd::UInt32 cExtraBytes = highByte >> 6;
                // 0 means 0, 1 means 1, 2 means 3, and 3 means 4:
                if (cExtraBytes > 1) ++cExtraBytes;

                efd::UInt32 result = (efd::UInt32)(highByte & 0x3F);
                while (cExtraBytes--)
                {
                    efd::UInt8 nextByte = 0;
                    Serializer::SerializeObject(nextByte, io_archive);

                    result <<= 8;
                    result |= nextByte;
                }

                io_object = (DATATYPE)result;
            }
        }
    };




    /// This routine works for containers that:  1) can be resized, 2) can be STL style iterated.
    /// For example std::vector, efd::vector, std::deque and efd::deque should work with this
    /// routine
    template< typename CHILDROUTINE = SR_Default >
    struct SR_ResizableArray
    {
        template<typename DATATYPE>
        static void Serialize(DATATYPE& io_object, efd::Archive& io_archive)
        {
            size_t cObjects = io_object.size();
            SR_As32Bit_Compressed::Serialize(cObjects, io_archive);

            if (io_archive.IsUnpacking())
            {
                // Each element will pack to at least one efd::UInt8 so lets not try to grow the
                // array to some ungodly size in case cObjects is bogus.  This is very important
                // when unpacking data that might have come from a client and thus might be hacked.
                if (cObjects > io_archive.GetRemainingSize())
                {
                    io_archive.RaiseError();
                    return;
                }

                io_object.resize(cObjects);
            }

            for (typename DATATYPE::iterator iter = io_object.begin();
                 iter != io_object.end();
                 ++iter)
            {
                CHILDROUTINE::Serialize(*iter, io_archive);
                if (io_archive.GetError())
                {
                    break;
                }
            }
        }
    };

#define SR_StdVector  SR_ResizableArray
#define SR_StdDeque   SR_ResizableArray



    /// If you can't resize the container up front but it has STL style iterators and a push_back
    /// function then you should be able to use this routine.  It should work for std::list.
    template<typename CHILDROUTINE = SR_Default>
    struct SR_StdList
    {
        template<typename DATATYPE>
        static void Serialize(DATATYPE& io_object, efd::Archive& io_archive)
        {
            size_t cObjects = io_object.size();
            SR_As32Bit_Compressed::Serialize(cObjects, io_archive);

            if (io_archive.IsUnpacking())
            {
                // Once again we use the "everything is at least one efd::UInt8" assumption to
                // sanity check the archive:
                if (cObjects > io_archive.GetRemainingSize())
                {
                    io_archive.RaiseError();
                    return;
                }

                // Remove any previous data from the container:
                io_object.clear();

                for (efd::UInt32 i = 0; i < cObjects; ++i)
                {
                    // We have two choices: 1.) Declare a local DATATYPE, unpack it, and push the
                    // result or 2.) push an "empty" DATATYPE and unpack in place.  Method 1 will
                    // result in a default constructor call and a copy constructor call where as
                    // method 2 should only result in a default constructor call, but method 2 adds
                    // the extra dependency that your object support the "back()" method which you
                    // might not be able to implement efficiently for your container type.  For
                    // std::list method 2 would be better.  Of course since we use push_back anyway
                    // perf will already be bad if you can't provide an efficient back()
                    // implementation.

                    // Method 1:
                    //typename DATATYPE::value_type data;
                    //CHILDROUTINE::Serialize(data, io_archive);
                    //io_object.push_back(data);

                    // Method 2:
                    // This extra typedef might seem odd but its the only way I could get this to
                    // compile under both GCC and MSVC.  GCC requires the extra "typename" but MSVC
                    // wouldn't allow "push_back(typename DATATYPE::value_type());"
                    typedef typename DATATYPE::value_type value_type;
                    io_object.push_back(value_type());
                    CHILDROUTINE::Serialize(io_object.back(), io_archive);
                }
            }
            else
            {
                for (typename DATATYPE::iterator iter = io_object.begin();
                     iter != io_object.end();
                     ++iter)
                {
                    CHILDROUTINE::Serialize(*iter, io_archive);
                }
            }
        }
    };




    /// This routine can handle map-type containers such as std::map, efd::map, std::set, efd::set,
    /// std::multimap, std::hash_map, std::hash_multimap, and the like.
    template<typename SR_KEYROUTINE = SR_Default, typename SR_DATAROUTINE = SR_Default>
    struct SR_StdMap
    {
        template<typename DATATYPE>
        static void Serialize(DATATYPE& io_object, efd::Archive& io_archive)
        {
            size_t cObjects = io_object.size();
            SR_As32Bit_Compressed::Serialize(cObjects, io_archive);

            if (io_archive.IsUnpacking())
            {
                // standard safety check:
                if (2*cObjects > io_archive.GetRemainingSize())
                {
                    io_archive.RaiseError();
                    return;
                }

                // Remove any previous data from the container:
                io_object.clear();

                for (efd::UInt32 i = 0; i < cObjects; ++i)
                {
                    typename DATATYPE::key_type key;
                    typename DATATYPE::mapped_type data;
                    SR_KEYROUTINE::Serialize(key, io_archive);
                    SR_DATAROUTINE::Serialize(data, io_archive);

                    // This extra typedef might seem odd but its the only way I could get this to
                    // compile under both GCC and MSVC.  GCC requires the extra "typename" but MSVC
                    // wouldn't allow "insert(typename DATATYPE::value_type(key, data));"
                    typedef typename DATATYPE::value_type value_type;
                    io_object.insert(value_type(key, data));
                }
            }
            else
            {
                for (typename DATATYPE::iterator iter = io_object.begin();
                     iter != io_object.end();
                     ++iter)
                {
                    // The copy of the key is to get around iter->first being const.  At first I
                    // tried const_cast<DATATYPE::key_type>(iter->first) but the compiler didn't
                    // like it.
                    typename DATATYPE::key_type key = iter->first;
                    SR_KEYROUTINE::Serialize(key, io_archive);
                    SR_DATAROUTINE::Serialize(iter->second, io_archive);
                }
            }
        }
    };



    /// This routine can handle set-type containers such as std::set and efd::set.
    template<typename SR_KEYROUTINE = SR_Default>
    struct SR_StdSet
    {
        template<typename DATATYPE>
        static void Serialize(DATATYPE& io_object, efd::Archive& io_archive)
        {
            size_t cObjects = io_object.size();
            SR_As32Bit_Compressed::Serialize(cObjects, io_archive);

            if (io_archive.IsUnpacking())
            {
                // standard safety check:
                if (2*cObjects > io_archive.GetRemainingSize())
                {
                    io_archive.RaiseError();
                    return;
                }

                // Remove any previous data from the container:
                io_object.clear();

                for (efd::UInt32 i = 0; i < cObjects; ++i)
                {
                    typename DATATYPE::key_type key;
                    SR_KEYROUTINE::Serialize(key, io_archive);

                    // This extra typedef might seem odd but its the only way I could get this to
                    // compile under both GCC and MSVC.  GCC requires the extra "typename" but MSVC
                    // wouldn't allow "insert(typename DATATYPE::value_type(key));"
                    typedef typename DATATYPE::value_type value_type;
                    io_object.insert(key);
                }
            }
            else
            {
                for (typename DATATYPE::iterator iter = io_object.begin();
                    iter != io_object.end();
                    ++iter)
                {
                    // The copy of the key is to get around *iter being const.  At first I tried
                    // const_cast<DATATYPE::key_type>(*iter) but the compiler didn't like it.
                    typename DATATYPE::key_type key = *iter;
                    SR_KEYROUTINE::Serialize(key, io_archive);
                }
            }
        }
    };



    /// Serialize a std::pair style object formed from two sub-elements, one named 'first' and the
    /// other named 'second'. Separate serialization routines can be specified for each element.
    template<typename SR_FIRSTROUTINE = SR_Default, typename SR_SECONDROUTINE = SR_Default>
    struct SR_StdPair
    {
        template<typename DATATYPE>
        static void Serialize(DATATYPE& io_object, efd::Archive& io_archive)
        {
            SR_FIRSTROUTINE::Serialize(io_object.first, io_archive);
            SR_SECONDROUTINE::Serialize(io_object.second, io_archive);
        }
    };



    /// Any chunk of serialization code that you find yourself repeating frequently can be made into
    /// a routine, even something as simple as iterating a fixed size array.  This combines well
    /// with the EE_ARRAYSIZEOF macro:
    ///
    /// @code
    ///     MyClass data[10];
    ///     SR_FixedArray<EE_ARRAYSIZEOF(data)>::Serialize(data, archive);
    /// @endcode
    template<efd::UInt32 NUM_ELEMENTS, typename CHILDROUTINE = SR_Default>
    struct SR_FixedArray
    {
        template<typename DATATYPE>
        static void Serialize(DATATYPE& io_object, efd::Archive& io_archive)
        {
            for (efd::UInt32 i = 0; i < NUM_ELEMENTS; ++i)
            {
                CHILDROUTINE::Serialize(io_object[i], io_archive);
            }
        }
    };

} // end namespace efd


#endif // EE_SERIALIZEROUTINES_H
