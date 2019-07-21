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
#ifndef EE_UTF8CHAR_H
#define EE_UTF8CHAR_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/Utilities.h>

namespace efd
{
class Archive;
struct utf8char_t;
struct utf16char_t;
typedef unsigned int utf32char_t;

/**
    Structure in support of UTF-8 chars, as defined by the Unicode Standard.

    In UTF-8, characters from the U+0000..U+10FFFF range (the UTF-16 accessible range) are encoded
    using sequences of 1 to 4 octets.
*/
struct utf8char_t
{
    enum {
        /// Need 5 8-bit storage units, since we keep the internal buffer null terminated.
        kReservedUnits = 5,

        /// Bytes occupied by storage units.
        kReservedBytes = kReservedUnits * sizeof(efd::Char)
    };

    /// Array of storage units.
    char bytes[kReservedUnits];

    //@{
    /// These constructors support conversions between various Unicode 3.1 encodings, but they do
    /// NOT support locale-specific translation into Unicode.
    utf8char_t();
    utf8char_t(const utf8char_t& rhs);
    utf8char_t(const utf16char_t& rhs);
    //@}

#ifdef EE_EXPLICIT_UTF8CHAR
    //@{
    /**
        These constructors are made explicit to avoid accidental or unexpected automatic type
        promotion issues.

        These constructors must be explicitly called, which prevents characters or ints from being
        automatically cast into utf8char_t types in cases where that might not be valid.  Casting
        a raw char into a utf8char_t is dangerous because technically that character is connected
        to a locale which must be used to convert the character to Unicode before we assign the
        value.  We aren't doing that step; instead we are simply assuming the char is a valid
        7-bit ASCII value.  In the case of int conversion, we are assuming the int is already a
        UTF32 value.  By making these constructors explicit, the caller will need to think about
        whether these assumptions are valid.
    */
    explicit utf8char_t(const char ch);
    explicit utf8char_t(utf32char_t rhs);
    //@}
#else
    /**
        This constructor is dangerous, since all sorts of types can automatically cast to an
        unsigned int and only a very small number of those are valid UTF32 values.

        Use of this constructor will compile without errors in many cases where you want an error
        to be generated.  On the other hand, it is very convenient, as long as its used correctly.
    */
    utf8char_t(unsigned int rhs);
#endif

    /// Construct a character from the first utf8-encoded sequence of a stream.
    static utf8char_t from_stream(const char* buffer_sz);

    /// Get a C-string representation of this character.
    inline const char* c_str() const;

    /// Validate the utf8-encoding of this character.
    inline bool is_valid() const;

    /// Convert from UTF-32.
    inline void FromUTF32(utf32char_t code);

    /// Convert to UTF-32.
    inline utf32char_t ToUTF32() const;

    /// Convert to ASCII.
    inline char ToAscii(char chDefault = '?') const;

    /// Assignment operator.
    utf8char_t& operator=(const utf8char_t& rhs);

    //@{
    /// Comparison operators.
    inline bool operator==(const utf8char_t& rhs) const;
    inline bool operator!=(const utf8char_t& rhs) const;
    inline bool operator<(const utf8char_t& rhs) const;
    inline bool operator<=(const utf8char_t& rhs) const;
    inline bool operator>(const utf8char_t& rhs) const;
    inline bool operator>=(const utf8char_t& rhs) const;

    inline bool operator==(efd::Char rhs) const;
    inline bool operator!=(efd::Char rhs) const;
    //@}

    ///  Get the size, in bytes, of this utf8-encoded character.
    inline unsigned size() const;

    /// Serialization
    EE_EFD_ENTRY void Serialize(efd::Archive& ar);
};

/**
    Structure in support of UTF-16 chars, as defined by the Unicode Standard.

    The UTF-16 accessible range is U+0000..U+10FFFF.
*/
struct utf16char_t
{
    enum {
        /// Need 3 16-bit storage units, since we keep the internal buffer null terminated.
        kReservedUnits = 3,

        /// Bytes occupied by storage units.
        kReservedBytes = kReservedUnits * sizeof(efd::WChar)
    };

    /// Array of storage units.
    efd::WChar units[kReservedUnits];

    //@{
    /// These constructors support conversions between various Unicode 3.1 encodings, but they do
    /// NOT support locale-specific translation into Unicode.
    utf16char_t();
    utf16char_t(const utf8char_t& rhs);
    utf16char_t(const utf16char_t& rhs);
    explicit utf16char_t(const wchar_t ucs2);
    explicit utf16char_t(utf32char_t ucs4);
    //@}

    /// Convert from UTF-32.
    inline void FromUTF32(utf32char_t code);

    /// Convert to UTF-32.
    inline utf32char_t ToUTF32() const;

    /// Construct a character from the first utf16-encoded sequence of a stream.
    static utf16char_t from_stream(const efd::WChar* buffer_sz);

    /// Get a C-string representation of this character.
    inline const efd::WChar* c_str() const;

    /// Validate the utf16-encoding of this character.
    inline bool is_valid() const;

    /// Assignment operator.
    utf16char_t& operator=(const utf16char_t& rhs);

    //@{
    /// Comparison operators.
    inline bool operator==(const utf16char_t& rhs) const;
    inline bool operator!=(const utf16char_t& rhs) const;
    inline bool operator<(const utf16char_t& rhs) const;
    inline bool operator<=(const utf16char_t& rhs) const;
    inline bool operator>(const utf16char_t& rhs) const;
    inline bool operator>=(const utf16char_t& rhs) const;
    //@}

    /// Get the size, in uints, of this utf8-encoded character.
    inline unsigned size() const;
};

//------------------------------------------------------------------------------------------------
/// @name UTF-8/16 Utility functions from utf8char.h

//@{

/// Return the number of bytes at the beginning of the stream used to encode the first character.
EE_EFD_ENTRY unsigned utf8_num_units(const efd::Char* buffer_sz);
EE_EFD_ENTRY unsigned utf16_num_units(const efd::WChar* buffer_sz);

//@}

/// @name UTF-8/16 Utility functions from utf8char.h

//@{
/// Given the first unit of a multi-unit sequence, return the number of units needed to encode the
/// entire character.
EE_EFD_ENTRY unsigned utf8_num_units(efd::UInt8 byte);
EE_EFD_ENTRY unsigned utf16_num_units(efd::WChar byte);
//@}

/// @name UTF-8/16 Utility functions from utf8char.h

//@{
/// Given a pointer to an encoded character and the character's length in units, return true if
/// the character is valid.
EE_EFD_ENTRY bool utf8_validate_char(
    const efd::Char* src_sz,
    unsigned size);
EE_EFD_ENTRY bool utf16_validate_char(
    const efd::WChar* src_sz,
    unsigned size);
//@}

/// @name UTF-8/16 Utility functions from utf8char.h

//@{
/// Given a buffer and the size of the buffer, determine if the last encoded character within the
/// buffer is valid.
EE_EFD_ENTRY unsigned utf8_tail_fragments(
    const efd::Char* src_sz,
    unsigned size);
EE_EFD_ENTRY unsigned utf16_tail_fragments(
    const efd::WChar* src_sz,
    unsigned size);
//@}

};  // End namespace efd.

#include <efd/utf8char.inl>
#include <efd/utf16char.inl>

#endif  // EE_UTF8CHAR_H
