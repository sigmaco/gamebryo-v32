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

//==========================================================================
//  utf8string_iterator implementation
//==========================================================================

//-------------------------------------------------------------------------------------------------
//  base()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline IT utf8string_iterator<T,IT>::base() const
{
    return m_pos;
}

//-------------------------------------------------------------------------------------------------
//  utf8string_iterator()  [explicit copy ctor]
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline utf8string_iterator<T,IT>::utf8string_iterator(const IT& pos)
: m_pos(pos)
{
}

//-------------------------------------------------------------------------------------------------
//  utf8string_iterator  [ctor]
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline utf8string_iterator<T,IT>::utf8string_iterator()
: m_pos()
{
}

//-------------------------------------------------------------------------------------------------
//  utf8string_iterator()  [ctor]
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline utf8string_iterator<T,IT>::utf8string_iterator(
    const utf8string_iterator<T, typename T::iterator>& rhs)
: m_pos(rhs.base())
{
}

//-------------------------------------------------------------------------------------------------
//  operator=()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
utf8string_iterator<T,IT>& utf8string_iterator<T,IT>::operator=(
    const utf8string_iterator<T, typename T::iterator>& rhs)
{
    m_pos = rhs.base();
    return (*this);
}

//-------------------------------------------------------------------------------------------------
//  operator*()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline typename utf8string_iterator<T,IT>::value_type
utf8string_iterator<T,IT>::operator*() const
{
    return utf8char_t::from_stream(&(*base()));
}

//-------------------------------------------------------------------------------------------------
//  operator++()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline utf8string_iterator<T,IT> &
utf8string_iterator<T,IT>::operator++()
{
    m_pos += utf8_num_units(*m_pos);
    return *this;
}

//-------------------------------------------------------------------------------------------------
//  operator++()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline const utf8string_iterator<T,IT> utf8string_iterator<T,IT>::operator++(int)
{
    const utf8string_iterator<T,IT> temp(*this);
    this->operator++();
    return temp;
}

//-------------------------------------------------------------------------------------------------
//  operator--()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline utf8string_iterator<T,IT>& utf8string_iterator<T,IT>::operator--()
{
    while (true)
    {
        --m_pos;

        if ((*m_pos & '\xC0') != '\x80')
        {
            break;
        }
    }

    return *this;
}

//-------------------------------------------------------------------------------------------------
//  operator--()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline const utf8string_iterator<T,IT> utf8string_iterator<T,IT>::operator--(int)
{
    const utf8string_iterator<T,IT> temp (*this);
    this->operator--();
    return temp;
}

//-------------------------------------------------------------------------------------------------
//  operator+()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline utf8string_iterator<T,IT> utf8string_iterator<T,IT>::operator+(int rhs) const
{
    utf8string_iterator<T,IT> temp(*this);

    if (rhs > 0)
    {
        for (int i = 0; i < rhs; ++i)
        {
            ++temp;
        }
    }
    else
    {
        rhs = -rhs;
        for (int i = 0; i < rhs; ++i)
        {
            --temp;
        }
    }

    return temp;
}

//-------------------------------------------------------------------------------------------------
//  operator-()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline utf8string_iterator<T,IT> utf8string_iterator<T,IT>::operator-(int rhs) const
{
    utf8string_iterator<T,IT> temp(*this);

    if (rhs >= 0)
    {
        for (int i = 0; i < rhs; ++i)
        {
            --temp;
        }
    }
    else
    {
        rhs = -rhs;
        for (int i = 0; i < rhs; ++i)
        {
            ++temp;
        }
    }

    return temp;
}

//-------------------------------------------------------------------------------------------------
//  operator==()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT, typename IU>
inline bool operator==(
    const utf8string_iterator<T,IT>& lhs,
    const utf8string_iterator<T,IU>& rhs)
{
    return (lhs.base() == rhs.base());
}

//-------------------------------------------------------------------------------------------------
//  operator!=()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT, typename IU>
inline bool operator!=(
    const utf8string_iterator<T,IT>& lhs,
    const utf8string_iterator<T,IU>& rhs)
{
    return (lhs.base() != rhs.base());
}

//-------------------------------------------------------------------------------------------------
//  operator<()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline bool operator<(
    const utf8string_iterator<T,IT>& lhs,
    const utf8string_iterator<T,IT>& rhs)
{
    return (lhs.base() < rhs.base());
}

//-------------------------------------------------------------------------------------------------
//  operator>()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline bool operator>(
    const utf8string_iterator<T,IT>& lhs,
    const utf8string_iterator<T,IT>& rhs)
{
    return (lhs.base() > rhs.base());
}

//-------------------------------------------------------------------------------------------------
//  operator<=()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline bool operator<=(
    const utf8string_iterator<T,IT>& lhs,
    const utf8string_iterator<T,IT>& rhs)
{
    return (lhs.base() <= rhs.base());
}

//-------------------------------------------------------------------------------------------------
//  operator>=()
//-------------------------------------------------------------------------------------------------
template <typename T, typename IT>
inline bool operator>=(
    const utf8string_iterator<T,IT>& lhs,
    const utf8string_iterator<T,IT>& rhs)
{
    return (lhs.base() >= rhs.base());
}
