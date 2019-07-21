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
#ifndef EE_CUSTOMALLOC_H
#define EE_CUSTOMALLOC_H

#define NEW_ALLOC
#ifdef NEW_ALLOC
#include <efd/MemoryDefines.h>
#endif

#include <stddef.h>

namespace efd
{

// TODO mbailey 8/22/08 Temporarily disable memory logging for all
// stl allocations. Currently the xml memory log files produced by
// test applications can exceed 450 Mb due to the abundant amount of memory allocations
// performed by stl. Disabling memory logging for stl brings this size down
// to ~65 Mb.

/// Global flag for disabling memory logging.
EE_EFD_ENTRY extern bool gs_bDisableMemLogging;

/// Maximum size allocation allowed to be performed by STL, in bytes.
enum
{
#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_LINUX)
    /// 1 Gb maximum for Win32 and Linux.
    EE_STL_MAX_SIZE_ALLOCATION = 1024 * 1024 * 1024
#elif defined(EE_PLATFORM_PS3)
    /// 256 Mb maximum for PS3.
    EE_STL_MAX_SIZE_ALLOCATION  = 256 * 1024 * 1024
#elif defined(EE_PLATFORM_XBOX360)
    /// 256 Mb maximum for Xbox 360.
    EE_STL_MAX_SIZE_ALLOCATION = 256 * 1024 * 1024
#endif
};

template <class T> class CustomAllocator;

/// Specialized custom allocator for void.
template<>
class CustomAllocator<void>
{
public:
    //@{
    /// Define pointers and const pointers.
    typedef void* pointer;
    typedef const void* const_pointer;
    //@}

    /// References to void members are impossible.
    typedef void value_type;

    template <class U>
    struct rebind
    {
        typedef CustomAllocator<U> other;
    };
};

/// Custom allocator for general case.
template<class T>
class CustomAllocator
{
public:
    //@{
    /// Define pointers, const pointers, and other general types for custom allocator.
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    //@}

    template <class U>
    struct rebind
    {
        typedef CustomAllocator<U> other;
    };

    /// Custom allocator constructor.
    CustomAllocator() EE_EMPTY_THROW;

    //@{
    /// Custom allocator copy constructors.
    CustomAllocator(const CustomAllocator&) EE_EMPTY_THROW;
    template <class U> CustomAllocator(const CustomAllocator<U>&) EE_EMPTY_THROW;
    //@}

    /// Custom allocator destructor.
    ~CustomAllocator() EE_EMPTY_THROW;

    /**
        Return the address of a reference as a pointer.

        @param x Reference to allocated memory of a particular type.
        @return Address of the reference, as a pointer.
    */
    pointer address(reference x) const;

    /**
        Return the address of a const reference as a const pointer.

        @param x Const reference to allocated memory of a particular type.
        @return Address of the const reference, as a const pointer.
    */
    const_pointer address(const_reference x) const;

    /**
        Allocate memory of size "count" objects of a particular type.

        @param count Number of objects of a particular type to allocate.
        @param hint Currently not used.
        @return Pointer to allocated memory of size "count" objects of a particular type.
    */
    pointer allocate(
        size_type count,
        CustomAllocator<void>::const_pointer hint = 0);

    /**
        Deallocate a chunk of memory.

        @param p Pointer to allocated memory of a particular type.
        @param n Currently not used.
    */
    void deallocate(
        pointer p,
        size_type n);

    /**
        Return the maximum size, in number of objects, that STL is being allowed to allocate.

        @return Maximum number of objects STL is being allowed to allocate.
    */
    size_type max_size() const EE_EMPTY_THROW;

    /**
        Use placement new and T's copy constructor to construct the object at the address
        specified by p.

        @param p Pointer to previously allocated memory for an object.
        @param val Object of a particular type whose copy constructor is being used.
    */
    void construct(
        pointer p,
        const T& val);

    /**
        Destroy the object whose address is stored in p.

        @param p Pointer to object of a particular type.
    */
    void destroy(pointer p);
};

}   // End namespace efd.

#include <efd/customalloc.inl>

#endif  // EE_CUSTOMALLOC_H
