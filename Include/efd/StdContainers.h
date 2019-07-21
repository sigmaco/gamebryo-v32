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
#ifndef EE_STDCONTAINERS_H
#define EE_STDCONTAINERS_H

/** @file StdContainers.h
    This file contains Emergent wrapped stl containers.  These containers use stlport for cross
    platform consistency and the Emergent allocator through the use of a Custom allocator passed
    as a template parameter.
    @note use of any stlport container not listed in this file will not go through the Emergent
    allocator
*/

#include <efd/RTLib.h>

// standard template library container types that we wrap to overload their allocator:
#include <stlport/map>
#include <stlport/hash_map>
#include <stlport/list>
#include <stlport/vector>
#include <stlport/set>
#include <stlport/deque>

// Container adapter classes that we overload to use our containers (and thus our allocator):
#include <stlport/stack>
#include <stlport/queue>

#include <efd/EEBasicString.h>
#include <efd/customalloc.h>

namespace efd
{

    /// At STL vector that uses Emergent's memory allocator.
    template<class _data>
    class vector : public EE_STL_NAMESPACE::vector< _data, efd::CustomAllocator<_data> >
    {
    public:
        typedef EE_STL_NAMESPACE::vector< _data, efd::CustomAllocator<_data> > BaseClass;

        typedef typename BaseClass::allocator_type allocator_type;
        typedef _data value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type* iterator;
        typedef const value_type* const_iterator;

        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        //@{
        /**
            Construct a vector.

            Semantics are identical to std::vector.
        */
        vector() : BaseClass() {}
        explicit vector(size_type _Count) : BaseClass(_Count) {}
        vector(size_type _Count, const _data& _Val) : BaseClass(_Count, _Val) {}
        vector(const vector& _Right) : BaseClass(_Right) {}
        vector(const BaseClass& _Right) : BaseClass(_Right) {}
        template<class InputIterator> vector(InputIterator _First, InputIterator _Last)
            : BaseClass(_First, _Last) {}
        //@}

        //@{
        /**
            Returns an iterator addressing the first location of an element in a vector that has a
            data value equivalent to a specified value.

            This simply thunks to EE_STL_NAMESPACE::find.

            @param i_data
        */
        inline iterator find(const _data& i_data);
        inline const_iterator find(const _data& i_data) const;
        //@}

        /// @name Memory destruction for static containers.
        //@{
        /// Deletes any memory that this container is holding onto.  This should be used during
        /// any SDM shutdown.  Not calling this function could potentially cause the container to
        /// report memory leaks during application shutdown.  After static_shutdown(), the size
        /// and capacity of the container are zero.
        inline void static_shutdown();
        //@}
    };


    /// An STL list that uses Emergent's memory allocator
    template< class _data >
    class list : public EE_STL_NAMESPACE::list< _data, efd::CustomAllocator<_data> >
    {
    public:
        typedef EE_STL_NAMESPACE::list< _data, efd::CustomAllocator<_data> > BaseClass;
        typedef _data value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef typename BaseClass::allocator_type allocator_type;
        //typedef bidirectional_iterator_tag _Iterator_category;
        typedef typename BaseClass::iterator iterator;
        typedef typename BaseClass::const_iterator const_iterator;

        //@{
        /**
            Construct a list.

            Semantics are identical to std::list.
        */
        list() : BaseClass() {}
        explicit list(size_type _Count) : BaseClass(_Count) {}
        list(size_type _Count, const _data& _Val) : BaseClass(_Count, _Val) {}
        list(const list& _Right) : BaseClass(_Right) {}
        list(const BaseClass& _Right) : BaseClass(_Right) {}
        template<class InputIterator> list(InputIterator _First, InputIterator _Last)
            : BaseClass(_First, _Last) {}
        //@}

        /**
            Deletes the element at the beginning of a list.

            @param o_data If the list is non-empty, first item is copied here.  If the list is
            empty, then this value is guaranteed to remain unchanged from its initial value.
            @return bool True if the head was removed, false if the list was empty.
        */
        inline bool pop_front(_data& o_data);

#if !defined(SWIG)
        // Manual expose base class function to prevent it from being hidden.
        using BaseClass::pop_front;
#endif

        //@{
        /**
            Returns an iterator addressing the first location of an element in a list that has a
            data value equivalent to a specified value.

            This simply thunks to EE_STL_NAMESPACE::find.

            @param i_data
        */
        inline iterator find(const _data& i_data);
        inline const_iterator find(const _data& i_data) const;
        //@}
    };


    /// An STL map that uses Emergent's memory allocator
    template< class _key, class _data, class _compare = EE_STL_NAMESPACE::less<_key> >
    class map : public EE_STL_NAMESPACE::map< _key, _data, _compare, efd::CustomAllocator<_data> >
    {
    public:
        typedef EE_STL_NAMESPACE::map<
            _key,
            _data,
            _compare,
            efd::CustomAllocator<_data> > BaseClass;
        typedef typename BaseClass::iterator iterator;
        typedef typename BaseClass::const_iterator const_iterator;

        //@{
        /**
            Construct a map.

            Semantics are identical to std::map.
        */
        map() : BaseClass() {}
        explicit map(const _compare& _Comp) : BaseClass(_Comp) {}
        map(const map& _Right) : BaseClass(_Right) {}
        map(const BaseClass& _Right) : BaseClass(_Right) {}
        template<class InputIterator> map(InputIterator _First, InputIterator _Last)
            : BaseClass(_First, _Last) {}
        template<class InputIterator> map(
            InputIterator _First,
            InputIterator _Last,
            const _compare& _Comp)
            : BaseClass(_First, _Last, _Comp) {}
        //@}

        /**
            Find a key in the map.

            If found, copy the key into an output parameter.

            @param i_key The key to search for.
            @param o_data If key is found, data is copied here.  If key is not found, this value
                is guaranteed to remain unchanged from its initial value.
            @return bool True if the key was found; false if the key is not in the map.
        */
        inline bool find(const _key& i_key, _data& o_data) const;

#if !defined(SWIG)
        // Manual expose base class function to prevent it from being hidden.
        using BaseClass::find;
#endif
    };

    /// An STL hash_map that uses Emergent's memory allocator.
    template< class _key, class _data, class _HashFcn = EE_STL_NAMESPACE::hash<_key>,
        class _EqualKey = EE_STL_NAMESPACE::equal_to<_key> >
    class hash_map : public EE_STL_NAMESPACE::hash_map< _key, _data, _HashFcn, _EqualKey,
        CustomAllocator<_data> >
    {
    public:
        typedef EE_STL_NAMESPACE::hash_map<
            _key,
            _data,
            _HashFcn,
            _EqualKey,
            CustomAllocator<_data> > BaseClass;
        typedef typename BaseClass::iterator iterator;
        typedef typename BaseClass::const_iterator const_iterator;

        //@{
        /**
            Construct a hash_map.

            Semantics are identical to std::hash_map.
        */
        hash_map() : BaseClass() {}
        explicit hash_map(size_t __n) : BaseClass(__n) {}
        hash_map(const hash_map& _Right) : BaseClass(_Right) {}
        hash_map(const BaseClass& _Right) : BaseClass(_Right) {}
        template<class InputIterator> hash_map(InputIterator _First, InputIterator _Last)
            : BaseClass(_First, _Last) {}
        //@}

        /**
            Find a key in the hash_map.

            If found, copy the key into an output parameter.

            @param i_key The key to search for.
            @param o_data If key is found, data is copied here.  If key is not found, this value
                is guaranteed to remain unchanged from its initial value.
            @return bool True if the key was found, false if the key is not in the map.
        */
        inline bool find(const _key& i_key, _data& o_data) const;

        // Manual expose base class function to prevent it from being hidden
        using BaseClass::find;
    };

    /// An STL set that uses Emergent's memory allocator.
    template < class _data, class _compare = EE_STL_NAMESPACE::less<_data> >
    class set : public EE_STL_NAMESPACE::set< _data, _compare, efd::CustomAllocator<_data> >
    {
    public:
        typedef EE_STL_NAMESPACE::set< _data, _compare, efd::CustomAllocator<_data> > BaseClass;

        //@{
        /**
            Construct a set.

            Semantics are identical to std::set.
        */
        set() : BaseClass() {}
        explicit set(const _compare& _Comp) : BaseClass(_Comp) {}
        set(const set& _Right) : BaseClass(_Right) {}
        set(const BaseClass& _Right) : BaseClass(_Right) {}
        template<class InputIterator> set(InputIterator _First, InputIterator _Last)
            : BaseClass(_First, _Last) {}
        template<class InputIterator> set(
            InputIterator _First,
            InputIterator _Last,
            const _compare& _Comp)
            : BaseClass(_First, _Last, _Comp) {}
        //@}
    };


    /// An STL deque that uses Emergent's memory allocator.
    template< class _data >
    class deque : public EE_STL_NAMESPACE::deque< _data, efd::CustomAllocator<_data> >
    {
    public:
        typedef EE_STL_NAMESPACE::deque< _data, efd::CustomAllocator<_data> > BaseClass;
        typedef size_t size_type;

        //@{
        /**
            Construct a deque.

            Semantics are identical to std::deque.
        */
        deque() : BaseClass() {}
        explicit deque(size_type _Count) : BaseClass(_Count) {}
        deque(size_type _Count, const _data& _Val) : BaseClass(_Count, _Val) {}
        deque(const deque& _Right) : BaseClass(_Right) {}
        deque(const BaseClass& _Right) : BaseClass(_Right) {}
        template<class InputIterator> deque(InputIterator _First, InputIterator _Last)
            : BaseClass(_First, _Last) {}
        //@}
    };


    /// An STL basic_string that uses our allocator by default.
    typedef efd::basic_string< char, efd::char_traits<char>, efd::CustomAllocator<char> > string;
    typedef efd::basic_string<
        wchar_t,
        efd::char_traits<wchar_t>,
        efd::CustomAllocator<wchar_t> > wstring;


    //---------------------------------------------------------------------------------------------
    // Container Adapter Classes
    //---------------------------------------------------------------------------------------------

    /// An STL stack that defaults the container to an efd::deque (and thus uses our allocator).
    template< class _data, class _container = deque<_data> >
    class stack : public EE_STL_NAMESPACE::stack< _data, _container >
    {
    public:
        typedef EE_STL_NAMESPACE::stack< _data, _container > BaseClass;

        //@{
        /**
            Construct a stack.

            Semantics are identical to std::stack.
        */
        stack() : BaseClass() {}
        explicit stack(const _container& _Right) : BaseClass(_Right) {}
        //@}
    };

    /// An STL queue that defaults the container to an efd::deque (and thus uses our allocator).
    template< class _data, class _container = deque<_data> >
    class queue : public EE_STL_NAMESPACE::queue< _data, _container >
    {
    public:
        typedef EE_STL_NAMESPACE::queue< _data, _container > BaseClass;

        //@{
        /**
            Construct a queue.

            Semantics are identical to std::queue.
        */
        queue() : BaseClass() {}
        explicit queue(const _container& _Right) : BaseClass(_Right) {}
        //@}
    };

    /// An STL priority_queue that defaults the container to an efd::vector (and thus uses our
    /// allocator).
    template < class _data,  class _container = vector<_data>, class _compare =
        EE_STL_NAMESPACE::less<typename _container::value_type> >
    class priority_queue : public EE_STL_NAMESPACE::priority_queue< _data, _container, _compare >
    {
    public:
        typedef EE_STL_NAMESPACE::priority_queue< _data, _container, _compare > BaseClass;
        typedef priority_queue<_data, _container, _compare> _Self;
        typedef typename _container::value_type      value_type;
        typedef typename _container::size_type       size_type;
        typedef          _container                  container_type;

        typedef typename _container::reference       reference;
        typedef typename _container::const_reference const_reference;

        //@{
        /**
            Construct a priority_queue.

            Semantics are identical to std::priority_queue.
        */
        priority_queue() : BaseClass() {}
        explicit priority_queue(const _compare& _Comp) : BaseClass(_Comp) {}
        priority_queue(const _compare& _Comp, const _container& _Cont)
            : BaseClass(_Comp, _Cont) {}
        priority_queue(const priority_queue& _Right) : BaseClass(_Right) {}
        priority_queue(const BaseClass& _Right) : BaseClass(_Right) {}
        template<class InputIterator>
        priority_queue(InputIterator _First, InputIterator _Last)
            : BaseClass(_First, _Last) {}
        template<class InputIterator>
        priority_queue(InputIterator _First, InputIterator _Last, const _compare& _Comp)
            : BaseClass(_First, _Last, _Comp) {}
        template<class InputIterator>
        priority_queue(
            InputIterator _First,
            InputIterator _Last,
            const _compare& _Comp,
            const container_type& _Cont)
            : BaseClass(_First, _Last, _Comp, _Cont) {}
        //@}
    };


} // end namespace efd

#include <efd/StdContainers.inl>


#endif // EE_STDCONTAINERS_H
