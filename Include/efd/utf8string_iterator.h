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
#ifndef UTF8STRING_ITERATOR_HEADER
#define UTF8STRING_ITERATOR_HEADER

#include <stlport/iterator>
#include <stlport/string>
#include <efd/utf8char.h>
#include <efd/RTLib.h>

#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(push)
#pragma warning(disable:4512) // assignment operator could not be generated.
#endif

namespace efd
{

/// @cond EMERGENT_INTERNAL

/// An internal class used to iterate over a utf8string. This is used in the utf8string class and
/// in certain method implementations in utf8string.
template <typename T, typename IT>
class utf8string_iterator
{
public:
    typedef EE_STL_NAMESPACE::bidirectional_iterator_tag     iterator_category;
    typedef utf8char_t                          value_type;
    typedef typename T::difference_type         difference_type;
    typedef value_type                          reference;
    typedef void                                pointer;

    inline utf8string_iterator();

    explicit inline utf8string_iterator(const IT& pos);

    inline utf8string_iterator(
        const utf8string_iterator<T, typename T::iterator>& rhs);

    inline utf8string_iterator<T,IT> &operator=(
        const utf8string_iterator<T, typename T::iterator>& rhs);

    inline value_type operator*() const;

    inline utf8string_iterator<T,IT>& operator++();
    inline const utf8string_iterator<T,IT> operator++(int);
    inline utf8string_iterator<T,IT>& operator--();
    inline const utf8string_iterator<T,IT> operator--(int);

    inline utf8string_iterator<T,IT> operator+(int) const;
    inline utf8string_iterator<T,IT> operator-(int) const;

    inline IT base() const;

private:
    IT m_pos;
};

#include <efd/utf8string_iterator.inl>

} // end namespace efd

#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(pop)
#endif

/// @endcond

#endif // UTF8STRING_ITERATOR_HEADER
