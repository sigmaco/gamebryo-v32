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


namespace efd
{

//==========================================================================
//  utf8string implementation
//==========================================================================

//------------------------------------------------------------------------------------------------
//  A word about naming conventions in this file:
//
//  Variables suffixed with "mb" specify a multibyte value.  These are used
//  when referring to offsets with respect to code points.  For example,
//  (pos_mb = 6) might refer to the 6th multibyte character in the string.
//
//  Variables suffixed with "sb" specify a single-byte value.  These are
//  used when referring to offsets within the underlying byte buffer.  For
//  example, the 6th multibyte character in the string may be located at
//  (pos_sb = 24).
//
//  To translate between "mb" and "sb" (and vice-versa), use
//  utf8_mb_to_sb() and utf8_sb_to_mb().
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
inline utf8string::utf8string()
: m_string()
{
}

//------------------------------------------------------------------------------------------------
inline utf8string::utf8string(const utf8string& rhs)
: m_string(rhs.m_string)
{
}

//------------------------------------------------------------------------------------------------
inline utf8string::~utf8string()
{
}

//------------------------------------------------------------------------------------------------
inline utf8string::utf8string(
    const char* src_sz,
    size_type count_mb)
{
    assign(src_sz, CT_LENGTH, count_mb);
}

//------------------------------------------------------------------------------------------------
inline utf8string::utf8string(
    const char* src_sz,
    _CountType ct,
    size_type count)
{
    assign(src_sz, ct, count);
}

//------------------------------------------------------------------------------------------------
inline utf8string::utf8string(const char* src_sz)
    : m_string(src_sz)
{
}

//------------------------------------------------------------------------------------------------
inline utf8string::utf8string(
    size_type count_mb,
    const utf8char_t &uc)
{
    (*this).append(count_mb, uc);
}

//------------------------------------------------------------------------------------------------
inline const utf8string::internal_string& utf8string::raw() const
{
    return m_string;
}

//------------------------------------------------------------------------------------------------
inline const utf8string::internal_string& utf8string::base() const
{
    return m_string;
}

//------------------------------------------------------------------------------------------------
inline const char* utf8string::c_str() const
{
    return m_string.c_str();
}

//------------------------------------------------------------------------------------------------
inline const char* utf8string::data() const
{
    return m_string.data();
}

//------------------------------------------------------------------------------------------------
inline utf8string::iterator utf8string::begin()
{
    return iterator(m_string.begin());
}

//------------------------------------------------------------------------------------------------
inline utf8string::iterator utf8string::end()
{
    return iterator(m_string.end());
}

//------------------------------------------------------------------------------------------------
inline utf8string::const_iterator utf8string::begin() const
{
    return const_iterator(m_string.begin());
}

//------------------------------------------------------------------------------------------------
inline utf8string::const_iterator utf8string::end() const
{
    return const_iterator(m_string.end());
}

//------------------------------------------------------------------------------------------------
inline utf8string::reverse_iterator utf8string::rbegin()
{
    return reverse_iterator(m_string.rbegin());
}

//------------------------------------------------------------------------------------------------
inline utf8string::reverse_iterator utf8string::rend()
{
    return reverse_iterator(m_string.rend());
}

//------------------------------------------------------------------------------------------------
inline utf8string::const_reverse_iterator utf8string::rbegin() const
{
    return const_reverse_iterator(m_string.rbegin());
}

//------------------------------------------------------------------------------------------------
inline utf8string::const_reverse_iterator utf8string::rend() const
{
    return const_reverse_iterator(m_string.rend());
}

//------------------------------------------------------------------------------------------------
inline const utf8string::value_type utf8string::at(
    size_type pos_mb) const
{
    return(*this)[pos_mb];
}

//------------------------------------------------------------------------------------------------
inline utf8string utf8string::substr(
    size_type pos_mb,
    size_type count_mb) const
{
    utf8string tmp = utf8string(*this, pos_mb, count_mb);
    return tmp;
}

//------------------------------------------------------------------------------------------------
inline int utf8string::compare(const utf8string& cmp_utf8) const
{
    return m_string.compare(cmp_utf8.m_string);
}

//------------------------------------------------------------------------------------------------
inline int utf8string::compare(const char* cmp_sz) const
{
    return m_string.compare(cmp_sz);
}

//------------------------------------------------------------------------------------------------
inline int utf8string::compare(
    size_type pos_mb,
    size_type count_mb,
    const utf8string& cmp_utf8) const
{
    return utf8string(*this, pos_mb, count_mb).compare(cmp_utf8);
}

//------------------------------------------------------------------------------------------------
inline int utf8string::compare(
    size_type pos_mb,
    size_type count_mb,
    const utf8string& cmp_utf8,
    size_type pos_mb2,
    size_type count_mb2) const
{
    return utf8string(*this, pos_mb, count_mb).compare(
        utf8string(cmp_utf8, pos_mb2, count_mb2));
}

//------------------------------------------------------------------------------------------------
inline int utf8string::compare(
    size_type pos_mb,
    size_type count_mb,
    const char* cmp_sz,
    size_type count_mb2) const
{
    return utf8string(*this, pos_mb, count_mb).compare(
        utf8string(cmp_sz, CT_LENGTH, count_mb2));
}

//------------------------------------------------------------------------------------------------
inline int utf8string::compare(
    size_type pos_mb,
    size_type count_mb,
    const char* cmp_sz) const
{
    return utf8string(*this, pos_mb, count_mb).compare(cmp_sz);
}

//------------------------------------------------------------------------------------------------
template<typename InputIterator>
utf8string& utf8string::assign(InputIterator itBegin, InputIterator itEnd)
{
    clear();

    while (itBegin != itEnd)
    {
        push_back(*itBegin);
        ++itBegin;
    }

    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::operator=(const utf8string& src_utf8)
{
    m_string = src_utf8.m_string;

    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::operator=(
    const utf8string::internal_string& src_str)
{
    m_string = src_str;

    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::operator=(const char* rhs_sz)
{
    m_string = rhs_sz;
    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::operator=(const utf8char_t& ch)
{
    m_string = &(ch.bytes[0]);
    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_first_of(
    const utf8string& match_utf8,
    utf8string::size_type pos_mb) const
{
    return _find_first_of(match_utf8, pos_mb, npos, false);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_first_of(
    const char* match_sz,
    utf8string::size_type pos_mb,
    utf8string::size_type count_mb) const
{
    return _find_first_of(match_sz, pos_mb, count_mb, false);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_first_of(
    const char* match_sz,
    utf8string::size_type pos_mb) const
{
    return _find_first_of(match_sz, pos_mb, npos, false);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_first_of(
    const utf8char_t& uc,
    utf8string::size_type pos_mb) const
{
    return find(uc.c_str(), pos_mb);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_last_of(
    const utf8string& match_utf8,
    utf8string::size_type pos_mb) const
{
    return _find_last_of(match_utf8, pos_mb, npos, false);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_last_of(
    const char* match_sz,
    utf8string::size_type pos_mb,
    utf8string::size_type count_mb) const
{
    return _find_last_of(match_sz, pos_mb, count_mb, false);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_last_of(
    const char* match_sz,
    utf8string::size_type pos_mb) const
{
    return _find_last_of(match_sz, pos_mb, npos, false);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_last_of(
    const utf8char_t& uc,
    utf8string::size_type pos_mb) const
{
    return _find_last_of(uc.c_str(), pos_mb, npos, false);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_first_not_of(
    const utf8string& match_utf8,
    utf8string::size_type pos_mb) const
{
    return _find_first_of(match_utf8, pos_mb, length(), true);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_first_not_of(
    const char* match_sz,
    utf8string::size_type pos_mb,
    utf8string::size_type count_mb) const
{
    return _find_first_of(match_sz, pos_mb, count_mb, true);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_first_not_of(
    const char* match_sz,
    utf8string::size_type pos_mb) const
{
    return _find_first_of(match_sz, pos_mb, npos, true);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_first_not_of(
    const utf8char_t& uc,
    utf8string::size_type pos_mb) const
{
    utf8string match_utf8;
    match_utf8 += uc;
    return _find_first_of(match_utf8, pos_mb, npos, true);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_last_not_of(
    const utf8string& match_utf8,
    utf8string::size_type pos_mb) const
{
    return _find_last_of(match_utf8, pos_mb, npos, true);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_last_not_of(
    const char* match_sz,
    utf8string::size_type pos_mb,
    utf8string::size_type count_mb) const
{
    return _find_last_of(match_sz, pos_mb, count_mb, true);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_last_not_of(
    const char* match_sz,
    utf8string::size_type pos_mb) const
{
    return _find_last_of(match_sz, pos_mb, npos, true);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::find_last_not_of(
    const utf8char_t& uc,
    utf8string::size_type pos_mb) const
{
    utf8string match_utf8;
    match_utf8 += uc;
    return _find_last_of(match_utf8, pos_mb, npos, true);
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::operator+=(const utf8string& src_utf8)
{
    m_string += src_utf8.m_string;
    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::operator+=(const char* src_sz)
{
    m_string += src_sz;
    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::operator+=(const utf8char_t& uc)
{
    m_string += uc.c_str();
    return(*this);
}

//------------------------------------------------------------------------------------------------
inline void utf8string::push_back(const utf8char_t& uc)
{
    m_string += uc.c_str();
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::append(const utf8string& src_utf8)
{
    m_string += src_utf8.raw();
    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::append(const utf8char_t& uc)
{
    m_string += uc.c_str();
    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::append(
    const utf8string& src_utf8,
    size_type pos_mb,
    size_type count_mb)
{
    m_string += (src_utf8.substr(pos_mb, count_mb)).raw();
    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::append(const char* src_sz)
{
    m_string += src_sz;
    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::append(
    const char* src_sz,
    size_type count_mb)
{
    m_string += (utf8string(src_sz).substr(0, count_mb)).raw();
    return(*this);
}

//------------------------------------------------------------------------------------------------
template<typename InputIterator>
utf8string& utf8string::append(InputIterator itFirst, InputIterator itLast)
{
    while (itFirst != itLast)
    {
        (*this) += (*itFirst);
        ++itFirst;
    }

    return(*this);
}

//------------------------------------------------------------------------------------------------
template<typename InputIterator>
utf8string utf8string::StreamToString(
    InputIterator itBegin,
    InputIterator itEnd)
{
    utf8string tmp;

    // DT20087 This method is not very efficient, we should start by reserving the expected amount
    // of memory  and also using operator+= below walks the string to find the end on each call.

    while (itBegin != itEnd)
    {
        tmp += (*itBegin);
        ++itBegin;
    }

    return tmp;
}

//------------------------------------------------------------------------------------------------
template<typename InputIterator>
void utf8string::insert(
    iterator itPos,
    InputIterator itBegin,
    InputIterator itEnd)
{
    const size_type pos = itPos.base() - m_string.begin();
    m_string.insert(pos, StreamToString(itBegin, itEnd).raw());
}

//------------------------------------------------------------------------------------------------
template<typename InputIterator>
utf8string& utf8string::replace(
    utf8string::iterator itDestBegin,
    utf8string::iterator itDestEnd,
    InputIterator itSrcBegin,
    InputIterator itSrcEnd)
{
    m_string.replace(
        itDestBegin.base(),
        itDestEnd.base(),
        StreamToString(itSrcBegin, itSrcEnd).raw());

    return(*this);
}

//------------------------------------------------------------------------------------------------
inline void utf8string::clear()
{
    m_string.clear();
}

//------------------------------------------------------------------------------------------------
inline utf8string& utf8string::erase()
{
    m_string.erase();
    return(*this);
}

//------------------------------------------------------------------------------------------------
inline utf8string::iterator utf8string::erase(
    utf8string::iterator itPos)
{
    return iterator(
        m_string.erase(itPos.base(), itPos.base() + (*itPos).size()));
}

//------------------------------------------------------------------------------------------------
inline utf8string::iterator utf8string::erase(
    utf8string::iterator itBegin,
    utf8string::iterator itEnd)
{
    return iterator(m_string.erase(itBegin.base(), itEnd.base()));
}

//------------------------------------------------------------------------------------------------
inline bool utf8string::empty() const
{
    return m_string.empty();
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::size() const
{
    return m_string.size();
}

//------------------------------------------------------------------------------------------------
inline void utf8string::swap(utf8string& rhs)
{
    m_string.swap(rhs.m_string);
}

//------------------------------------------------------------------------------------------------
inline void utf8string::reserve(size_type count_sb)
{
    m_string.reserve(count_sb);
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::capacity() const
{
    return m_string.capacity();
}

//------------------------------------------------------------------------------------------------
inline utf8string::size_type utf8string::max_size() const
{
    return m_string.max_size();
}

//------------------------------------------------------------------------------------------------
inline int utf8string::vsprintf(const utf8string& format_str, va_list args)
{
    return vsprintf(format_str.c_str(), args);
}

//------------------------------------------------------------------------------------------------
inline int utf8string::vsprintf_append(const utf8string& format_str, va_list args)
{
    return vsprintf_append(format_str.c_str(), args);
}

//------------------------------------------------------------------------------------------------
inline int utf8string::replace_substr(const utf8string& find_str,
                                               const utf8string& replace_str)
{
    return replace_substr(find_str.c_str(), replace_str.c_str());
}

//------------------------------------------------------------------------------------------------
inline int utf8string::ol_replace_substr(const utf8string& find_str,
                                               const utf8string& replace_str)
{
    return replace_substr(find_str.c_str(), replace_str.c_str());
}

//------------------------------------------------------------------------------------------------
inline int utf8string::icompare(const utf8string& cmp_utf8) const
{
    return icompare(cmp_utf8.data());
}

//------------------------------------------------------------------------------------------------
// global operators

//------------------------------------------------------------------------------------------------
inline bool operator==(
    const utf8string& lhs_utf8,
    const utf8string& rhs_utf8)
{
    return lhs_utf8.compare(rhs_utf8) == 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator==(
    const utf8string& lhs_utf8,
    const char* rhs_c_str)
{
    return lhs_utf8.compare(rhs_c_str) == 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator==(
    const char* lhs_c_str,
    const utf8string& rhs_utf8)
{
    return rhs_utf8.compare(lhs_c_str) == 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator!=(
    const utf8string& lhs_utf8,
    const utf8string& rhs_utf8)
{
    return !(lhs_utf8 == rhs_utf8);
}

//------------------------------------------------------------------------------------------------
inline bool operator!=(
    const utf8string& lhs_utf8,
    const char* rhs_c_str)
{
    return !(lhs_utf8 == rhs_c_str);
}

//------------------------------------------------------------------------------------------------
inline bool operator!=(
    const char* lhs_c_str,
    const utf8string& rhs_utf8)
{
    return !(rhs_utf8 == lhs_c_str);
}

//------------------------------------------------------------------------------------------------
inline bool operator<(
    const utf8string& lhs_utf8,
    const utf8string& rhs_utf8)
{
    return lhs_utf8.compare(rhs_utf8) < 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator<(
    const utf8string& lhs_utf8,
    const char* rhs_c_str)
{
    return lhs_utf8.compare(rhs_c_str) < 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator<(
    const char* lhs_c_str,
    const efd::utf8string& rhs_utf8)
{
    return rhs_utf8.compare(lhs_c_str) >= 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator<=(
    const utf8string& lhs_utf8,
    const utf8string& rhs_utf8)
{
    return lhs_utf8.compare(rhs_utf8) <= 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator<=(
    const utf8string& lhs_utf8,
    const char* rhs_c_str)
{
    return lhs_utf8.compare(rhs_c_str) <= 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator<=(
    const char* rhs_c_str,
    const efd::utf8string& lhs_utf8)
{
    return lhs_utf8.compare(rhs_c_str) > 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator>(
    const utf8string& lhs_utf8,
    const utf8string& rhs_utf8)
{
    return lhs_utf8.compare(rhs_utf8) > 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator>(
    const utf8string& lhs_utf8,
    const char* rhs_c_str)
{
    return lhs_utf8.compare(rhs_c_str) > 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator>(
    const char* lhs_c_str,
    const efd::utf8string& rhs_utf8)
{
    return rhs_utf8.compare(lhs_c_str) <= 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator>=(
    const utf8string& lhs_utf8,
    const utf8string& rhs_utf8)
{
    return lhs_utf8.compare(rhs_utf8) >= 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator>=(
    const utf8string& lhs_utf8,
    const char* rhs_c_str)
{
    return lhs_utf8.compare(rhs_c_str) >= 0;
}

//------------------------------------------------------------------------------------------------
inline bool operator>=(const char* lhs_c_str, const efd::utf8string& rhs_utf8)
{
    return rhs_utf8.compare(lhs_c_str) < 0;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string operator+(const efd::utf8string& lhs_utf8, const efd::utf8string& rhs_utf8)
{
    efd::utf8string temp(lhs_utf8);
    temp.append(rhs_utf8);
    return temp;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string operator+(const efd::utf8string& lhs_utf8, const char* rhs_c_str)
{
    efd::utf8string temp(lhs_utf8);
    temp.append(rhs_c_str);
    return temp;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string operator+(const char* lhs_c_str, const efd::utf8string& rhs_utf8)
{
    efd::utf8string temp(lhs_c_str);
    temp.append(rhs_utf8);
    return temp;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string operator+(const efd::utf8string& lhs_utf8, const efd::utf8char_t& rhs_utf8)
{
    efd::utf8string temp(lhs_utf8);
    temp.push_back(rhs_utf8);
    return temp;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string operator+(const efd::utf8char_t& lhs_utf8, const efd::utf8string& rhs_utf8)
{
    efd::utf8string temp;
    temp.push_back(lhs_utf8);
    temp.append(rhs_utf8);
    return temp;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string operator+(const efd::utf8char_t& lhs_utf8, const char* rhs_utf8)
{
    efd::utf8string temp;
    temp.push_back(lhs_utf8);
    temp.append(rhs_utf8);
    return temp;
}

//------------------------------------------------------------------------------------------------
// Iterator operators
//------------------------------------------------------------------------------------------------
template <typename IT, typename IU>
inline bool operator==(
    const efd::utf8string_iterator<efd::utf8string,IT>& lhs,
    const efd::utf8string_iterator<efd::utf8string,IU>& rhs)
{
    return(lhs.base() == rhs.base());
}

//------------------------------------------------------------------------------------------------
template <typename IT, typename IU>
inline bool operator!=(
    const efd::utf8string_iterator<efd::utf8string, IT>& lhs,
    const efd::utf8string_iterator<efd::utf8string, IU>& rhs)
{
    return(lhs.base() != rhs.base());
}

//------------------------------------------------------------------------------------------------
inline bool operator<(
    const efd::utf8string_iterator<const efd::utf8string, const efd::utf8string::iterator>& lhs,
    const efd::utf8string_iterator<const efd::utf8string, const efd::utf8string::iterator>& rhs)
{
    return(lhs.base() < rhs.base());
}

//------------------------------------------------------------------------------------------------
inline bool operator>(
    const efd::utf8string_iterator<const efd::utf8string, const efd::utf8string::iterator>& lhs,
    const efd::utf8string_iterator<const efd::utf8string, const efd::utf8string::iterator>& rhs)
{
    return(lhs.base() > rhs.base());
}

//------------------------------------------------------------------------------------------------
inline bool operator<=(
    const efd::utf8string_iterator<const efd::utf8string, const efd::utf8string::iterator>& lhs,
    const efd::utf8string_iterator<const efd::utf8string, const efd::utf8string::iterator>& rhs)
{
    return(lhs.base() <= rhs.base());
}

//------------------------------------------------------------------------------------------------
inline bool operator>=(
    const efd::utf8string_iterator<const efd::utf8string, const efd::utf8string::iterator>& lhs,
    const efd::utf8string_iterator<const efd::utf8string, const efd::utf8string::iterator>& rhs)
{
    return(lhs.base() >= rhs.base());
}

} // end namespace efd

