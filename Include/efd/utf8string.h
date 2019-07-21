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
#ifndef EE_UTF8STRING_H
#define EE_UTF8STRING_H

#include <efd/String.h>
#include <efd/utf8string_iterator.h>
#include <efd/EEBasicString.h>      // defines efd::basic_string
#include <efd/utf8char.h>
#include <efd/customalloc.h>

namespace efd
{

/**
   When describing the "size" of a UTF string there are several ways to describe it:
   \li CT_LENGTH : equivalent to the return value from the length() function.  This is the number
        of characters in the string, but a single character can be multiple units long
   \li CT_SIZE : equivalent to the return value from the size() function.  This is the number of
        units that are required to store the string.  For utf8 a unit is one byte, for utf16
        a unit is 16 bytes.
   \li CT_BYTES : this is the size in bytes.  Similar to CT_SIZE, but different UTF encodings use
        different unit sizes.  For UTF8 CT_BYTES and CT_SIZE are equivalent.  For UTF16 Bytes
        should always be equivalent to CT_SIZE*2.
*/
enum _CountType { CT_LENGTH, CT_SIZE, CT_BYTES };


/**
    A implementation of a std::string container that is UTF-8 aware. The efd::utf8string class is
    the default string used in Foundation and Game Framework.
 */
class EE_EFD_ENTRY utf8string
{
public:
    /// @cond EMERGENT_INTERNAL
    typedef efd::CustomAllocator<char> allocator_type;
    typedef efd::basic_string<char, efd::char_traits<char>, allocator_type> internal_string;
    typedef internal_string::size_type size_type;
    typedef internal_string::difference_type difference_type;
    typedef utf8char_t value_type;
    typedef utf8char_t& reference;
    typedef const utf8char_t& const_reference;
    typedef utf8string_iterator<internal_string, internal_string::iterator> iterator;
    typedef utf8string_iterator<internal_string, internal_string::const_iterator> const_iterator;
    typedef EE_STL_NAMESPACE::reverse_iterator<iterator> reverse_iterator;
    typedef EE_STL_NAMESPACE::reverse_iterator<const_iterator> const_reverse_iterator;

#if defined(EE_PLATFORM_PS3)
    static const size_t npos;
#else
    static const size_t npos = static_cast<size_t>(internal_string::npos);
#endif
    /// @endcond

    /// @name Construction and Destruction
    //@{

    /// Default constructor
    inline utf8string();

    /**
        Construct a utf8string as a partial copy of a C string.

        @note This does NOT convert the string from the local codepage, it assumes the string
            already contains UTF8 formatted data!

        @param src Pointer to the src buffer.
        @param ct The count type.
        @param count The count.
    */
    inline utf8string(const char* src, _CountType ct, size_type count);

private:
    /// @cond EMERGENT_INTERNAL

    // Note: The following is an invalid constructor, it exists only so that:
    //      utf8string("char string", 4);
    // will generate a compiler error instead of auto-promoting the char string to a basic
    // utf8 string and calling the utf8string(const utf8string& src, size_type count_mb)
    // constructor.  It might be invalid to convert since the char string might not be NULL
    // terminated.  Call utf8string(const char* src, _CountType ct, size_type count);
    // instead if you need this behavior.
    inline utf8string(const char* src, size_type count_mb);

    /// @endcond

public:
    /**
        Construct a utf8string as a partial copy of another utf8string.

        @param src The source.
        @param pos_mb The position.
        @param count_mb The count.
    */
    utf8string(
        const utf8string & src,
        size_type pos_mb,
        size_type count_mb = npos);

    /**
        Construct a utf8string as a copy of a C string.

        @note This does NOT convert the string from the local codepage, it assumes the string
            already contains UTF8 formatted data!

        @param src_sz Pointer to the const char buffer.
    */
    inline utf8string(const char* src_sz);

    /// Construct a utf8string as a copy of another utf8string (copy ctor).
    inline utf8string(const utf8string& src_utf8);

    /// Construct a utf8string as multiple characters.
    inline utf8string(size_type count_mb, const utf8char_t& uc);

    /**
       Construct a utf8string using printf-style formating.

       @note This does NOT convert strings from the local codepage, it assumes all strings
           already contain UTF8 formatted data!  See sprintf for more restrictions.

       @param format_sz The format string.
    */
    utf8string(_Formatted, const char* format_sz, ...);

    /// Destructor
    inline ~utf8string();

    //@}

    /// Provide access to the raw string buffer as a C-style string.
    inline const char* c_str() const;

    /// Provide access to the raw string buffer as a C-style string.
    inline const char* data() const;

    /// Provide access to the raw string buffer as a C++-style string.
    inline const internal_string& raw() const;

    /// Provide access to the base string buffer as a C++-style string.
    inline const internal_string& base() const;

    /// Create an iterator to the beginning of the string.
    inline iterator begin();

    /// Create an iterator at the end of the string.
    inline iterator end();

    /// Create a const iterator to the beginning of the string.
    inline const_iterator begin() const;

    /// Create a const iterator at the end of the string.
    inline const_iterator end() const;

    /// Create a reverse iterator at the beginning of the string.
    inline reverse_iterator rbegin();

    /// Create a reverse iterator at the end of the string.
    inline reverse_iterator rend();

    /// Create a const reverse iterator at the beginning of the string.
    inline const_reverse_iterator rbegin() const;

    /// Create a const reverse iterator at the end of the string.
    inline const_reverse_iterator rend() const;

    /// Read-only random access accessor
    const value_type operator[](size_type pos) const;

    /// Read-only random access accessor
    inline const value_type at(size_type pos) const;

    /// Returns a sub string of size count_mb that begins at pos_mb.
    inline utf8string substr(
        size_type pos_mb = 0,
        size_type count_mb = npos) const;

    /// @name String comparison routines
    //@{
    /// Compares this character string to the specified string.
    /// @param cmp_utf8 The string to compare against.
    /// @return An integer indicating the relationship between this string and the specified string:
    ///    @li < 0 Means this string is less than the specified string
    ///    @li 0 Means this string is identical to the specified string
    ///    @li > 0 Means this string is greater than the specified string
    inline int compare(const utf8string& cmp_utf8) const;

    /// @overload
    /// @param cmp_sz The string to compare against.
    inline int compare(const char* cmp_sz) const;

    /// @overload
    /// @param pos_mb The first character in this string at which the comparison starts.
    /// @param count_mb The number of characters to consider in this string.
    /// @param cmp_utf8 The string to compare against.
    inline int compare(
        size_type pos_mb,
        size_type count_mb,
        const utf8string& cmp_utf8) const;

    /// @overload
    /// @param pos_mb The first character in this string at which the comparison starts.
    /// @param count_mb The number of characters to consider in this string.
    /// @param cmp_utf8 The string to compare against.
    /// @param pos2_mb The first character in the specified string at which the comparison starts.
    /// @param count2_mb The number of characters to consider in the specified string.
    inline int compare(
        size_type pos_mb,
        size_type count_mb,
        const utf8string& cmp_utf8,
        size_type pos2_mb,
        size_type count2_mb) const;

    /// @overload
    /// @param pos_mb The first character in this string at which the comparison starts.
    /// @param count_mb The number of characters to consider in this string.
    /// @param cmp_sz The string to compare against.
    /// @param count2_mb The number of characters to consider in the specified string.
    inline int compare(
        size_type pos_mb,
        size_type count_mb,
        const char* cmp_sz,
        size_type count2_mb) const;

    /// @overload
    /// @param pos_mb The first character in this string at which the comparison starts.
    /// @param count_mb The number of characters to consider in this string.
    /// @param cmp_sz The string to compare against.
    inline int compare(
        size_type pos_mb,
        size_type count_mb,
        const char* cmp_sz) const;
    //@}

    /// @name Find routines
    ///
    /// All of these routines return utf8string::npos when the search finds nothing.
    //@{
    /// Finds the position of the specified string or character within this string.
    /// @param str_utf8 The string to find.
    /// @param pos_mb The position in this string to start looking for the specified string.
    /// @return The position of the specified string within this string.
    size_type find(
        const utf8string& str_utf8,
        size_type pos_mb = 0) const;

    /// @overload
    /// @param str_sz The string to find.
    /// @param pos_mb The position in this string to start looking for the specified string.
    /// @param count_mb The number of characters to consider in this string.
    size_type find(
        const char* str_sz,
        size_type pos_mb,
        size_type count_mb) const;

    /// @overload
    /// @param str_sz The string to find.
    /// @param pos_mb The position in this string to start looking for the specified string.
    size_type find(
        const char* str_sz,
        size_type pos_mb = 0) const;

    /// @overload
    /// @param uc The character to find.
    /// @param pos_mb The position in this string to start looking for the specified string.
    size_type find(
        const utf8char_t& uc,
        size_type pos_mb = 0) const;

    /// Finds the position of the specified string or character within this string starting from
    /// the end of the string.
    /// @param str_utf8 The string to find.
    /// @param pos_mb The position in this string to start looking for the specified string.
    /// @return The position of the specified string within this string.
    size_type rfind(
        const utf8string& str_utf8,
        size_type pos_mb = npos) const;

    /// @overload
    /// @param str_sz The string to find.
    /// @param pos_mb The position in this string to start looking for the specified string.
    /// @param count_mb The number of characters to consider in this string.
    size_type rfind(
        const char* str_sz,
        size_type pos_mb,
        size_type count_mb) const;

    /// @overload
    /// @param str_sz The string to find.
    /// @param pos_mb The position in this string to start looking for the specified string.
    size_type rfind(
        const char* str_sz,
        size_type pos_mb = npos) const;

    /// @overload
    /// @param uc The character to find.
    /// @param pos_mb The position in this string to start looking for the specified string.
    size_type rfind(
        const utf8char_t& uc,
        size_type pos_mb = npos) const;

    /// Finds the first occurrence of a specified character within this string.
    /// @param match_utf8 The string containing characters to find.
    /// @param pos_mb The position in this string to start looking for the specified character.
    /// @return The position of the character found within this string.
    inline utf8string::size_type find_first_of(
        const utf8string& match_utf8,
        utf8string::size_type pos_mb = 0) const;

    /// @overload
    /// @param match_sz The string containing characters to find.
    /// @param pos_mb The position in this string to start looking for the specified character.
    /// @param count_mb The number of characters to consider starting from the beginning of the
    ///     specified string.
    inline size_type find_first_of(
        const char* match_sz,
        size_type pos_mb,
        size_type count_mb) const;

    /// @overload
    /// @param match_sz The string containing characters to find.
    /// @param pos_mb The position in this string to start looking for the specified character.
    inline size_type find_first_of(
        const char* match_sz,
        size_type pos_mb = 0) const;

    /// @overload
    /// @param uc The character to find.
    /// @param pos_mb The position in this string to start looking for the specified character.
    inline size_type find_first_of(
        const utf8char_t& uc,
        size_type pos_mb = 0) const;

    /// Finds the last occurrence of a specified character within this string.
    /// @param match_utf8 The string containing characters to find.
    /// @param pos_mb The position in this string to start looking for the specified character.
    /// @return The position of the character found within this string.
    inline size_type find_last_of(
        const utf8string& match_utf8,
        size_type pos_mb = npos) const;

    /// @overload
    /// @param match_sz The string containing characters to find.
    /// @param pos_mb The position in this string to start looking for the specified character.
    /// @param count_mb The number of characters to consider starting from the beginning of the
    ///     specified string.
    inline size_type find_last_of(
        const char* match_sz,
        size_type pos_mb,
        size_type count_mb) const;

    /// @overload
    /// @param match_sz The string containing characters to find.
    /// @param pos_mb The position in this string to start looking for the specified character.
    inline size_type find_last_of(
        const char* match_sz,
        size_type pos_mb = npos) const;

    /// @overload
    /// @param uc The character to find.
    /// @param pos_mb The position in this string to start looking for the specified character.
    inline size_type find_last_of(
        const utf8char_t& uc,
        size_type pos_mb = npos) const;

    /// Finds the first occurrence of a character within this string that is \b not the specified
    ///     character.
    /// @param match_utf8 The string containing characters to look for.
    /// @param pos_mb The position in this string to start looking for characters that do \b not
    ///     match the specified character.
    /// @return The position of the character found within this string.
    inline size_type find_first_not_of(
        const utf8string& match_utf8,
        size_type pos_mb = 0) const;

    /// @overload
    /// @param match_sz The string containing characters to look for.
    /// @param pos_mb The position in this string to start looking for characters that do \b not
    ///     match the specified character.
    /// @param count_mb The number of characters to consider starting from the beginning of the
    ///     specified string.
    inline size_type find_first_not_of(
        const char* match_sz,
        size_type pos_mb,
        size_type count_mb) const;

    /// @overload
    /// @param match_sz The string containing characters to look for.
    /// @param pos_mb The position in this string to start looking for characters that do \b not
    ///     match the specified character.
    inline size_type find_first_not_of(
        const char* match_sz,
        size_type pos_mb = 0) const;

    /// @overload
    /// @param uc The character to look for.
    /// @param pos_mb The position in this string to start looking for characters that do \b not
    ///     match the specified character.
    inline size_type find_first_not_of(
        const utf8char_t& uc,
        size_type pos_mb = 0) const;

    /// Finds the last occurrence of a character within this string that is \b not the specified
    ///     character.
    /// @param match_utf8 The string containing characters to look for.
    /// @param pos_mb The position in this string to start looking for characters that do \b not
    ///     match the specified character.
    /// @return The position of the character found within this string.
    inline size_type find_last_not_of(
        const utf8string& match_utf8,
        size_type pos_mb = npos) const;

    /// @overload
    /// @param match_sz The string containing characters to look for.
    /// @param pos_mb The position in this string to start looking for characters that do \b not
    ///     match the specified character.
    /// @param count_mb The number of characters to consider starting from the beginning of the
    ///     specified string.
    inline size_type find_last_not_of(
        const char* match_sz,
        size_type pos_mb,
        size_type count_mb) const;

    /// @overload
    /// @param match_sz The string containing characters to look for.
    /// @param pos_mb The position in this string to start looking for characters that do \b not
    ///     match the specified character.
    inline size_type find_last_not_of(
        const char* match_sz,
        size_type pos_mb = npos) const;

    /// @overload
    /// @param uc The character to look for.
    /// @param pos_mb The position in this string to start looking for characters that do \b not
    ///     match the specified character.
    inline size_type find_last_not_of(
        const utf8char_t& uc,
        size_type pos_mb = npos) const;
    //@}

    /// @name Assign overloads
    //@{
    /// Assign multiple copies of the given character *this.
    /// @param count_mb The number of copies of the character to assign to the string.
    /// @param uc The character.
    utf8string& assign(size_type count_mb, const utf8char_t& uc);

    /// Assign a string to *this.
    /// @param str_sz The string.
    utf8string& assign(const char* str_sz);

private:
    /// Assign a number of characters from the given string to *this.
    /// @param str_sz The string to assign from.
    /// @param count_mb The number of characters to assign.
    // @note Don't call this flavor, use the following one instead.
    inline utf8string& assign(const char* str_sz, size_type count_mb);
public:

    /// Assign a number of characters from the given string to *this.
    /// @param str_sz The string to assign from.
    /// @param ct Specifies how the count parameter is interpreted.
    /// @param count The number of characters to assign.
    utf8string& assign(const char* str_sz, _CountType ct, size_type count);

    /// Assign a number of characters from the given string to *this.
    /// @param str_sz The string to assign from.
    /// @param pos_mb The position within the specified string to start assigning from.
    /// @param count_mb The number of characters to assign.
    utf8string& assign(
        const char* str_sz,
        size_type pos_mb,
        size_type count_mb);

    /// Assign the given string to *this.
    /// @param str_utf8 The string to assign from.
    utf8string& assign(const utf8string& str_utf8);

    /// Assign a number of characters from the given string to *this.
    /// @param str_utf8 The string to assign from.
    /// @param count_mb The number of characters to assign.
    utf8string& assign(
        const utf8string& str_utf8,
        size_type count_mb);

    /// Assign a number of characters from the given string to *this.
    /// @param str_utf8 The string to assign from.
    /// @param pos_mb The position within the specified string to start assigning from.
    /// @param count_mb The number of characters to assign.
    utf8string& assign(
        const utf8string& str_utf8,
        size_type pos_mb,
        size_type count_mb);

    /// Assign a number of characters from the InputIterator to *this.
    /// @param itBegin The starting point to assign from.
    /// @param itEnd The ending point to assign from.
    template< typename InputIterator>
    utf8string& assign(InputIterator itBegin, InputIterator itEnd);
    //@}

    /// assignment operator
    inline utf8string& operator=(const utf8string& rhs_utf8);

    /// assignment operator
    inline utf8string& operator=(const internal_string& rhs_str);

    /// assignment operator
    /// @note rhs_sz is assumed to point to valid UTF8 formated data
    /// @param rhs_sz Points to valid UTF8 formatted data.
    inline utf8string& operator=(const char* rhs_sz);

    /// assignment operator
    inline utf8string& operator=(const utf8char_t& uc);

    /// concatenation operator
    inline utf8string& operator+=(const utf8string& rhs_utf8);

    /// concatenation operator
    /// @note rhs_sz is assumed to point to valid UTF8 formated data
    /// @param rhs_sz The right hand side.
    inline utf8string& operator+=(const char* rhs_sz);

    /// concatenation operator
    inline utf8string& operator+=(const utf8char_t& uc);

    /// Add the character to this string.
    inline void push_back(const utf8char_t& uc);

    /// @name Append overloads
    //@{
    /// Append the specified string to this string.
    inline utf8string& append(const utf8string& src_utf8);

    /// Append the character to this string.
    inline utf8string& append(const utf8char_t& uc);

    /// Append a number of characters from the given string to *this.
    /// @param src_utf8 The string to append from.
    /// @param pos_mb The position within the specified string to start appending from.
    /// @param count_mb The number of characters to append.
    inline utf8string& append(
        const utf8string& src_utf8,
        size_type pos_mb,
        size_type count_mb);

    /// Append the specified string to this string.
    inline utf8string& append(const char* src_sz);

    /// Append a number of characters from the given string to *this.
    /// @param src_sz The string to append from.
    /// @param count_mb The number of characters to append.
    inline utf8string& append(
        const char* src_sz,
        size_type count_mb);

    /// Append multiple copies of the given character *this.
    /// @param count_mb The number of copies of the character to append to this string.
    /// @param uc The character.
    utf8string& append(
        size_type count_mb,
        const utf8char_t& uc);

    /// Append a number of characters from the InputIterator to *this.
    /// @param itFirst The starting point to append from.
    /// @param itLast The ending point to append from.
    template < typename InputIterator>
    utf8string& append(InputIterator itFirst, InputIterator itLast);
    //@}

    /// @name Insert overloads
    //@{
    /// Inserts a string before the given position in this string.
    /// @param pos_mb The position to insert the given string.
    /// @param src_utf8 The string to insert.
    utf8string& insert(
        size_type pos_mb,
        const utf8string& src_utf8);

    /// Inserts a string before the given position in this string.
    /// @param pos_mb The position to insert the given string.
    /// @param src_sz The string to insert.
    utf8string& insert(
        size_type pos_mb,
        const char* src_sz);

    /// Inserts a substring before the given position in this string.
    /// @param pos_mb The position to insert the given substring.
    /// @param src_utf8 The string containing the substring.
    /// @param pos2_mb The starting position of the substring.
    /// @param count_mb The number of characters in the substring.
    utf8string& insert(
        size_type pos_mb,
        const utf8string& src_utf8,
        size_type pos2_mb,
        size_type count_mb);

    /// Inserts a substring before the given position in this string.
    /// @param pos_mb The position to insert the given substring.
    /// @param src_sz The string containing the substring.
    /// @param count_mb The number of characters in the substring.
    utf8string& insert(
        size_type pos_mb,
        const char* src_sz,
        size_type count_mb);

    /// Inserts multiple copies of the given character before the given position in this string.
    /// @param pos_mb The position to insert the characters.
    /// @param count_mb The number of copies of the character to insert.
    /// @param uc The character.
    utf8string& insert(
        size_type pos_mb,
        size_type count_mb,
        const utf8char_t& uc);

    /// Inserts the given character before the given position in this string.
    /// @param itPos The position to insert the character.
    /// @param uc The character.
    /// @return An iterator pointing to the newly-inserted character.
    iterator insert(
        iterator itPos,
        const utf8char_t& uc);

    /// Inserts multiple copies of the given character before the given position in this string.
    /// @param itPos The position to insert the characters.
    /// @param count_mb The number of copies of the character to insert.
    /// @param uc The character.
    void insert(
        iterator itPos,
        size_type count_mb,
        const utf8char_t& uc);

    /** Inserts the first count_mb characters of src_utf8 at pos_mb.
        @note This flavor of insert does not match any valid std::basic_string::insert function.
            In fact, some STL implementations might provide a default parameter to the:
                insert(size_type P0, const Self& _Str, size_type _Off, size_type _Count = npos)
            flavor, in which case you might expect this flavor to take an offset into the source
            string instead of a count of source characters.  Just be sure you mean to be calling
            this flavor.
            @param pos_mb The position to insert the given substring.
            @param src_utf8 The string containing the substring.
            @param count_mb The number of characters in the substring.
    */
    utf8string& insert(
        size_type pos_mb,
        const utf8string& src_utf8,
        size_type count_mb);

    /// Insert a number of characters from the InputIterator to *this.
    /// @param itPos The position to insert the characters.
    /// @param itBegin The starting point to insert from.
    /// @param itEnd The ending point to insert from.
    template< typename InputIterator>
    void insert(
        iterator itPos,
        InputIterator itBegin,
        InputIterator itEnd);
    //@}

    /// @name Replace overloads
    //@{
    /// Replaces a substring of *this with the given string.
    /// @param pos_mb The position to start replacing characters with the substring.
    /// @param count_mb The number of characters in the substring.
    /// @param src_utf8 The string containing the substring.
    utf8string& replace(
        size_type pos_mb,
        size_type count_mb,
        const utf8string& src_utf8);

    /// Replaces a substring of *this with a substring of the given string.
    /// @param pos_mb The position to start replacing characters with the substring.
    /// @param count_mb The number of characters in the substring.
    /// @param src_utf8 The string containing the substring.
    /// @param pos2_mb The starting position of the substring from the given string.
    /// @param count2_mb The number of characters in the substring from the given string.
    utf8string& replace(
        size_type pos_mb,
        size_type count_mb,
        const utf8string& src_utf8,
        size_type pos2_mb,
        size_type count2_mb);

    /// Replaces a substring of *this with the given string.
    /// @param pos_mb The position to start replacing characters with the substring.
    /// @param count_mb The number of characters in the substring.
    /// @param src_sz The string containing the substring.
    utf8string& replace(
        size_type pos_mb,
        size_type count_mb,
        const char* src_sz);

    /// Replaces a substring of *this with a substring of the given string.
    /// @param pos_mb The position to start replacing characters with the substring.
    /// @param count_mb The number of characters in the substring.
    /// @param src_utf8 The string containing the substring.
    /// @param count2_mb The number of characters in the substring starting from the
    ///     beginning of the given string.
    utf8string& replace(
        size_type pos_mb,
        size_type count_mb,
        const utf8string& src_utf8,
        size_type count2_mb);

    /// Replaces a substring of *this with multiple copies of the given character.
    /// @param pos_mb The position to start replacing characters with the substring.
    /// @param count_mb The number of characters in the substring.
    /// @param count2_mb The number of copies of the given character in the replacing substring.
    /// @param uc The character.
    utf8string& replace(
        size_type pos_mb,
        size_type count_mb,
        size_type count2_mb,
        const utf8char_t& uc);

    /// Replace a number of characters in *this with characters from the InputIterator.
    /// @param itBegin The starting point to insert from.
    /// @param itEnd The ending point to insert from.
    /// @param src_utf8 The string containing characters to replace.
    utf8string& replace(
        iterator itBegin,
        iterator itEnd,
        const utf8string& src_utf8);

    /// Replace a number of characters in *this with characters from the InputIterator.
    /// @param itBegin The starting point to insert from.
    /// @param itEnd The ending point to insert from.
    /// @param src_sz The string containing characters to replace.
    utf8string& replace(
        iterator itBegin,
        iterator itEnd,
        const char* src_sz);

    /// Replace substring of *this with the specified number of characters from the specified
    /// string.
    /// @param itBegin The starting point to insert from.
    /// @param itEnd The ending point to insert from.
    /// @param src_sz The string containing characters to replace.
    /// @param count_mb The number of copies of the given character in the replacing substring.
    utf8string& replace(
        iterator itBegin,
        iterator itEnd,
        const char* src_sz,
        size_type count_mb);

    /// Replace substring of *this with the specified number of the specified character.
    /// @param itBegin The starting point to insert from.
    /// @param itEnd The ending point to insert from.
    /// @param count_mb The number of copies of the given character in the replacing substring.
    /// @param uc The character.
    utf8string& replace(
        iterator itBegin,
        iterator itEnd,
        size_type count_mb,
        const utf8char_t& uc);

    /// Replace substring of *this with the specified number of characters from the specified
    /// string.
    /// @note This is a non-standard signature for replace.  It doesn't match any similar
    /// signature from std::basic_string::replace.
    /// @param itBegin The starting point to insert from.
    /// @param itEnd The ending point to insert from.
    /// @param src_utf8 The string containing characters to replace.
    /// @param count_mb The number of copies of the given character in the replacing substring.
    utf8string& replace(
        iterator itBegin,
        iterator itEnd,
        const utf8string& src_utf8,
        size_type count_mb);

    /// Replace substring of *this with characters from the specified range.
    /// @param itDestBegin The starting point to replace.
    /// @param itDestEnd The ending point to replace.
    /// @param itSrcBegin The starting point to replace from.
    /// @param itSrcEnd The ending point to replace from.
    template< typename InputIterator>
    utf8string& replace(
        iterator itDestBegin,
        iterator itDestEnd,
        InputIterator itSrcBegin,
        InputIterator itSrcEnd);
    //@}

    /// Clears the string.
    inline void clear();

    /// @name Erase overloads
    //@{
    /// Erases a number of characters starting at the given position.
    /// @param pos_mb The position to start erasing.
    /// @param count_mb The number of characters to erase.
    utf8string& erase(
        size_type pos_mb,
        size_type count_mb = npos);

    /// Erases the entire string.
    inline utf8string& erase();

    /// Erases a number of characters starting at the given position.
    /// @param itPos The position to start erasing.
    inline iterator erase(iterator itPos);

    /// Erases a number of characters using iterators.
    /// @param itBegin The position to start erasing.
    /// @param itEnd The position to end erasing.
    inline iterator erase(
        iterator itBegin,
        iterator itEnd);
    //@}

    /// Returns true if the string is empty.
    inline bool empty() const;

    /** Returns the number of octets in the string.  Unlike std::string,
        this is not necessarily the same as length(). */
    inline size_type size() const;

    /** Returns the number of characters in the string.  Unlike std::string,
        this is not necessarily the same as size(). */
    size_type length() const;

    /// Swap strings
    inline void swap(utf8string& rhs_utf8);

    /** Request that the string's capacity be changed.  The postcondition
        for this is, once called, capacity() >= count_sb.
        @param count_sb The number of bytes of capacity requested.
        @note The argument for this call is in single bytes, not characters. */
    inline void reserve(size_type count_sb = 0);

    /**
        Appends characters, or erases characters from the end, as necessary to make the string's
            size exactly count_sb bytes.
        @param count_sb The number of bytes of capacity requested.
        @note The argument for this call is in single bytes, not characters. If,after resizing,
            the trailing utf8 character has been severed, it will be removed entirely, such that
            the final utf8 character of the string remains valid.
    */
    void resize(size_type count_sb = 0);

    /// @overload
    /// @param count_sb The number of bytes of capacity requested.
    /// @param uc The character used to fill additional string space.
    void resize(size_type count_sb, const utf8char_t& uc);

    /// Returns the size, in bytes, to which the string can grow before memory must be reallocated.
    inline size_type capacity() const;

    /// Returns the largest possible size of the string in bytes.
    inline size_type max_size() const;

    /// Returns true if all chars in string are ASCII.
    bool is_ascii() const;

    /// @name C Run-Time style formating routines
    //@{
    /**
        @note Format strings are compiler specific, you must take care to pass in a valid
            string especially if you support multiple compilers.  For example 64bit integer
            tags vary between compiles ("%I64d" on MSVC verse "%lld" on gnu).
        @note Do NOT attempt to convert wide or narrow strings via formatting.  The result
            will not be a valid UTF8 string.  Do not use %ls, %ws, %S, %lc, or %C tags.  All
            char* strings passed in are assumed to already point to valid UTF8 formatted data.
        @note You cannot use utf8char as an argument to these format routines.  Instead pass
            in the result of utf8char::c_str() matched to a "%s" tag.

        @internal The following generates Doxygen warnings because not all methods in the group
        use all the params documented here. These warnings may be ignored.
    */

    ///@param format The printf-style format string.
    ///@return The number of bytes (not characters) written.
    int sprintf(const char* format, ...);

    ///@param format The printf-style format string.
    ///@return The number of bytes (not characters) written.
    int sprintf(const utf8string& format, ...);

    /**
        Print variable argument list into string.

        @param format The printf-style format string.
        @param args Pointer to list of arguments.
        @return The number of bytes (not characters) written.
    */
    int vsprintf(const char* format, va_list args);

    /**
        Print variable argument list into string.

        @param format The printf-style format string.
        @param args Pointer to list of arguments.
        @return The number of bytes (not characters) written.
    */
    inline int vsprintf(const utf8string& format, va_list args);

    /**
        Operates as vsprintf with append.

        @param format The printf-style format string.
        @return The number of bytes (not characters) written.
    */
    int sprintf_append(const char* format, ...);

    /**
        Operates as sprintf with append.

        @param format The printf-style format string.
        @return The number of bytes (not characters) written.
    */
    int sprintf_append(const utf8string& format, ...);

    /**
        Operates as vsprintf with append.

        @param format The printf-style format string.
        @param args Pointer to list of arguments.
        @return The number of bytes (not characters) written.
    */
    int vsprintf_append(const char* format, va_list args);

    /**
        Operates as vsprintf with append.

        @param format The printf-style format string.
        @param args Pointer to list of arguments.
        @return The number of bytes (not characters) written.
    */
    inline int vsprintf_append(const utf8string& format, va_list args);
    //@}

    /**
        Remove characters from the beginning and/or end of the string.

        @param t Either TrimFront, TrimBack, or TrimAll.
        @param set Characters to trim.  Defaults to set of standard whitespace characters
    */
    void trim(_Trim t = TrimAll, const utf8string& set = utf8string::WhiteSpace());

    /**
        Remove characters from the beginning and/or end of the string.  Set must contain only
        single byte characters, to handle multi-byte use the other version.

        @param t Either TrimFront, TrimBack, or TrimAll.
        @param set Characters to trim.  Defaults to set of standard whitespace characters
    */
    void trim(_Trim t, const char* set);

    /// These are only placeholder functions, they do not behave correctly with respect to locale.
    /// Currently they will only effect ASCII characters according to English rules.
    //@{
    utf8string& toupper();
    utf8string& tolower();
    //@}

    /**
       Replace all occurrences of a substr with another string.  This will perform a single pass
       over the string from front to back replacing only those occurrences in the original string.

       Examples:
           "fooo".replace_substr("oo", "o") => "foo"
           "foo".replace_substr("o", "oo") => "foooo"
           "flolol".replace_substr("lol", "l") => "flol"

      @return The number of replacements that were made.
    */
    //@{
    int replace_substr(const char* find_sz, const char* replace_sz);
    inline int replace_substr(const utf8string& find_str, const utf8string& replace_str);
    //@}

    /**
       Overlapping Replace Substring
       This will replace all occurrences of the find string with the replace string including any
       occurrences which are the result of a previous substitution.
       @note If the replacement string contains the find sting this function will return -1 and
       make no modifications to the string.
       Examples:
            "foooooo".ol_replace_substr("oo", "o") => "fo"
            "flolol".replace_substr("lol", "l") => "fl"
      @return The number of replacements that were made, or -1 if the arguments are invalid.
    */
    //@{
    int ol_replace_substr(const char* find_sz, const char* replace_sz);
    inline int ol_replace_substr(const utf8string& find_str, const utf8string& replace_str);
    //@}

    /// @name String comparison routines ignoring case
    //@{
    /// Compares this character string to the specified string ignoring case.
    /// @param cmp_utf8 The string to compare against.
    /// @return An integer indicating the relationship between this string and the specified string:
    ///    @li < 0 Means this string is less than the specified string
    ///    @li 0 Means this string is identical to the specified string
    ///    @li > 0 Means this string is greater than the specified string
    inline int icompare(const utf8string& cmp_utf8) const;

    /// @overload
    /// @param cmp_sz The string to compare against.
    int icompare(const char* cmp_sz) const;

    /// @overload
    /// @param pos_mb The first character in this string at which the comparison starts.
    /// @param count_mb The number of characters to consider in this string.
    /// @param cmp_utf8 The string to compare against.
    int icompare(
        size_type pos_mb,
        size_type count_mb,
        const utf8string& cmp_utf8) const;

    /// @overload
    /// @param pos_mb The first character in this string at which the comparison starts.
    /// @param count_mb The number of characters to consider in this string.
    /// @param cmp_utf8 The string to compare against.
    /// @param pos2_mb The first character in the specified string at which the comparison starts.
    /// @param count2_mb The number of characters to consider in the specified string.
    int icompare(
        size_type pos_mb,
        size_type count_mb,
        const utf8string& cmp_utf8,
        size_type pos2_mb,
        size_type count2_mb) const;

    /// @overload
    /// @param pos_mb The first character in this string at which the comparison starts.
    /// @param count_mb The number of characters to consider in this string.
    /// @param cmp_sz The string to compare against.
    /// @param count2_mb The number of characters to consider in the specified string.
    int icompare(
        size_type pos_mb,
        size_type count_mb,
        const char* cmp_sz,
        size_type count2_mb) const;

    /// @overload
    /// @param pos_mb The first character in this string at which the comparison starts.
    /// @param count_mb The number of characters to consider in this string.
    /// @param cmp_sz The string to compare against.
    int icompare(
        size_type pos_mb,
        size_type count_mb,
        const char* cmp_sz) const;
    //@}

    /**
        Split a string into multiple sub-strings by matching against a set of delimiters.
        Similar to strtok.
    */
    efd::UInt32 split(
        const utf8string& i_set,
        efd::vector< utf8string >& o_results) const;

    /**
        NullString is a global const string that is set to the empty or "null" string.  This is
        very helpful if you have a function that returns a "const utf8string&" and you want
        to return a default or failure value.
    */
    static const utf8string& NullString()
    {
        static utf8string ns;
        return ns;
    }

    /**
        WhiteSpace is a global const string that contains " \t\n\r\l".  It is the default argument
        to the trim function.
    */
    static const utf8string& WhiteSpace()
    {
        static utf8string ws(" \t\n\r");
        return ws;
    }

    /** utf8_mb_to_sb()
        Translates between multibyte (character) position to byte offset within a UTF-8-encoded
        buffer. If the requested position is beyond sizelimit_sb then it will return npos
    */
    static size_type utf8_mb_to_sb(
        const char* buffer_sz,
        utf8string::size_type pos_mb,
        utf8string::size_type sizelimit_sb);

    /** utf8_sb_to_mb()
        Translates between byte offset and multibyte (character) position
        within a UTF-8-encoded buffer
    */
    static size_type utf8_sb_to_mb(
        const char* buffer_sz,
        utf8string::size_type pos_sb,
        utf8string::size_type sizelimit_sb);

    /// Serialization
    void Serialize(efd::Archive& ar);

private:
    /// @cond EMERGENT_INTERNAL
    template< typename InputIterator > static
    utf8string StreamToString(InputIterator itBegin, InputIterator itEnd);

    /// Helper for implementing find methods
    size_type _find_first_of(
        const utf8string& match_utf8,
        utf8string::size_type pos_mb,
        utf8string::size_type count_mb,
        bool invert) const;

    /// Helper for implementing find methods
    size_type _find_last_of(
        const utf8string& match_utf8,
        utf8string::size_type pos_mb,
        utf8string::size_type count_mb,
        bool invert) const;

    internal_string m_string;
    /// @endcond
};


} // end namespace efd

#include <efd/utf8string.inl>

#endif //EE_UTF8STRING_H
