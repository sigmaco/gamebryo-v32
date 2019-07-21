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

#include <efd/TemplateHelpers.h>

namespace efd
{


//--------------------------------------------------------------------------------------------------
template<class T1, class T2>
bool operator==(
                const CustomAllocator<T1>& lhs,
                const CustomAllocator<T2>& rhs) EE_EMPTY_THROW
{
    EE_UNUSED_ARG(lhs);
    EE_UNUSED_ARG(rhs);

    // The allocator has no actual members to test, any two are equivalent if their
    // types are equivalent
    return AreTypesEquivalent<T1, T2>::answer;
}

//--------------------------------------------------------------------------------------------------
template<class T1, class T2>
bool operator!=(const CustomAllocator<T1>& lhs, const CustomAllocator<T2>& rhs) EE_EMPTY_THROW
{
    EE_UNUSED_ARG(lhs);
    EE_UNUSED_ARG(rhs);

    // The allocator has no actual members to test, any two are equivalent if their
    // types are equivalent
    return !AreTypesEquivalent<T1, T2>::answer;
}

//--------------------------------------------------------------------------------------------------
// CustomAllocator()  [ctor]
template<class T>
CustomAllocator<T>::CustomAllocator() EE_EMPTY_THROW
{
}

//--------------------------------------------------------------------------------------------------
// CustomAllocator()  [copy ctor]
template<class T>
CustomAllocator<T>::CustomAllocator(const CustomAllocator<T>&) EE_EMPTY_THROW
{
}

//--------------------------------------------------------------------------------------------------
// CustomAllocator()  [copy ctor]
template<class T>
template<class U>
CustomAllocator<T>::CustomAllocator(const CustomAllocator<U>&) EE_EMPTY_THROW
{
}

//--------------------------------------------------------------------------------------------------
// ~CustomAllocator()  [dtor]
template<class T>
CustomAllocator<T>::~CustomAllocator() EE_EMPTY_THROW
{
}

//--------------------------------------------------------------------------------------------------
// address()
template<class T>
typename CustomAllocator<T>::pointer CustomAllocator<T>::address(
    typename CustomAllocator<T>::reference x) const
{
    return &(x);
}

//--------------------------------------------------------------------------------------------------
// address()
template<class T>
typename CustomAllocator<T>::const_pointer CustomAllocator<T>::address(
    typename CustomAllocator<T>::const_reference x) const
{
    return &(x);
}

//--------------------------------------------------------------------------------------------------
// allocate()
template<class T>
typename CustomAllocator<T>::pointer CustomAllocator<T>::allocate(
    typename CustomAllocator<T>::size_type count,
    typename CustomAllocator<void>::const_pointer hint)
{

#ifdef NEW_ALLOC
    void* ptr = EE_MALLOC2(count * sizeof(T), MemHint::SIZE_PROVIDED_ON_DEALLOCATE);
#else
    void* ptr = ::malloc(count * sizeof(T));
#endif

    return static_cast< typename CustomAllocator<T>::pointer >(ptr);

    EE_UNUSED_ARG(hint);
}

//--------------------------------------------------------------------------------------------------
// deallocate()
template<class T>
void CustomAllocator<T>::deallocate(typename CustomAllocator<T>::pointer p,
    typename CustomAllocator<T>::size_type count)
{
    if (p != NULL)
    {

#ifdef NEW_ALLOC
        // TODO mbailey 8/22/08 Temporarily disable memory logging for all
        // stl allocations. Currently the xml memory log files produced by
        // test apps can exceed 450 Mb due to the abundant amount of memory allocations
        // performed by stl. Disabling memory logging for stl brings this size down
        // to ~65 Mb.
        efd::gs_bDisableMemLogging = true;
        EE_FREE_KNOWN_SIZE(p, count * sizeof(T));
        efd::gs_bDisableMemLogging = false;
#else
        ::free(p);
#endif

    }

    EE_UNUSED_ARG(count);
}

//--------------------------------------------------------------------------------------------------
// max_size()
template<class T>
typename CustomAllocator<T>::size_type CustomAllocator<T>::max_size() const EE_EMPTY_THROW
{
    // Return the maximum size allocation, in number of objects, that we'll allow STL to make.
    return EE_STL_MAX_SIZE_ALLOCATION / sizeof(T);
}

//--------------------------------------------------------------------------------------------------
// construct()
template<class T>
void CustomAllocator<T>::construct(typename CustomAllocator<T>::pointer p, const T& val)
{
    // Use placement new and T's copy constructor to construct the object at the address specified
    // by p.
    // *** Note that no memory allocation occurs here; simply construction. ***
    new ((void*)p) T(val);
}

//--------------------------------------------------------------------------------------------------
// destroy()
template<class T>
void CustomAllocator<T>::destroy(typename CustomAllocator<T>::pointer p)
{
    // Destroy the object by calling its constructor directly.
    // Note that no memory free occurs here; just destruction.
    ((T*)p)->~T();
}

}   // End namespace efd.
