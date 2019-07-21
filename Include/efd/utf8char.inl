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


//  utf8char_t implementation
#include "efd/StringUtilities.h"

namespace efd
{

//--------------------------------------------------------------------------------------------------
inline utf8char_t::utf8char_t()
{
    ::memset(bytes, 0, kReservedBytes);
}

//--------------------------------------------------------------------------------------------------
inline utf8char_t::utf8char_t(const utf8char_t& rhs)
{
    ::memcpy(bytes, rhs.bytes, kReservedBytes);
}

//--------------------------------------------------------------------------------------------------
inline utf8char_t::utf8char_t(const utf16char_t& rhs)
{
    FromUTF32(rhs.ToUTF32());
}

#ifdef EE_EXPLICIT_UTF8CHAR

//--------------------------------------------------------------------------------------------------
inline utf8char_t::utf8char_t(const char ch)
{
    // If this assert goes off then we have an internationalization problem.  Well, even if
    // it doesn't go off technically what we're doing is still invalid.  Previously we would
    // have simply promoted the unsigned char to a uint32 and then accepted the character
    // as if it were UTF32 formatted.  In reality the characters we were adding in this manor
    // are in the default English_US locale which isn't exactly UTF8.  Most likely all the
    // characters we're dealing with are below 0x7F and just happen to match UTF8.  I added
    // this explicit constructor so we can verify that assumption with an assert. Really what
    // we should be doing is converting this character from a given locale into Unicode and
    // then encoding the Unicode as UTF8.
    EE_ASSERT(ch <= 0x7F);
    ::memset(bytes, 0, kReservedBytes);
    bytes[0] = ch;
}

//--------------------------------------------------------------------------------------------------
// Wikipedia definition of UTF8: http://en.wikipedia.org/wiki/UTF-8
inline utf8char_t::utf8char_t(utf32char_t code)
{
    FromUTF32(code);
}

//--------------------------------------------------------------------------------------------------

#else

//--------------------------------------------------------------------------------------------------
// Wikipedia definition of UTF8: http://en.wikipedia.org/wiki/UTF-8
inline utf8char_t::utf8char_t(unsigned int code)
{
    FromUTF32((utf32char_t)code);
}

#endif // EE_EXPLICIT_UTF8CHAR


//--------------------------------------------------------------------------------------------------
// algorithm from: http://tools.ietf.org/html/rfc3629
inline void utf8char_t::FromUTF32(utf32char_t code)
{
    // The highest valid value under the Unicode 3.1 spec is 0x10ffff.  Any value above this is
    // not a valid character.
    EE_ASSERT(code <= 0x10ffff);

    ::memset(bytes, 0, kReservedBytes);

    // Input Range      Binary input value                      Binary UTF-8 encoded
    // 000000-00007F    00000000 00000000 00000000 0zzzzzzz     0zzzzzzz
    // 000080-0007FF    00000000 00000000 00000yyy yyzzzzzz     110yyyyy 10zzzzzz
    // 000800-00FFFF    00000000 00000000 xxxxyyyy yyzzzzzz     1110xxxx 10yyyyyy 10zzzzzz
    // 010000-10FFFF    00000000 000wwwxx xxxxyyyy yyzzzzzz     11110www 10xxxxxx 10yyyyyy 10zzzzzz

    if (code <= 0x7F)
    {
        bytes[0] = static_cast<char>(code);
    }
    else if (code <= 0x7FF)
    {
        bytes[0] = static_cast<char>(0xC0 | (code >> 6));
        bytes[1] = static_cast<char>(0x80 | (code & 0x3F));
    }
    else if (code <= 0xFFFF)
    {
        bytes[0] = static_cast<char>(0xE0 | (code >> 12));
        bytes[1] = static_cast<char>(0x80 | ((code >> 6) & 0x3F));
        bytes[2] = static_cast<char>(0x80 | ((code >> 0) & 0x3F));
    }
    else if (code <= 0x10FFFF)
    {
        bytes[0] = static_cast<char>(0xF0 | (code >> 18));
        bytes[1] = static_cast<char>(0x80 | ((code >> 12)& 0x3F));
        bytes[2] = static_cast<char>(0x80 | ((code >> 6) & 0x3F));
        bytes[3] = static_cast<char>(0x80 | ((code >> 0) & 0x3F));
    }
    else
    {
        // invalid character, what should we do in this case?  We already asserted.
    }
}

//--------------------------------------------------------------------------------------------------
// algorithm from: http://tools.ietf.org/html/rfc3629
inline utf32char_t utf8char_t::ToUTF32() const
{
    utf32char_t result;
    switch (size())
    {
    case 1:
        result = bytes[0];
        break;

    case 2:
        result = ((bytes[0] & 0x1F) << 6) |
                 ((bytes[1] & 0x3F) << 0);
        break;

    case 3:
        result = ((bytes[0] & 0x0F) << 12) |
                 ((bytes[1] & 0x3F) << 6)  |
                 ((bytes[2] & 0x3F) << 0);
        break;

    case 4:
        result = ((bytes[0] & 0x07) << 18) |
                 ((bytes[1] & 0x3F) << 12) |
                 ((bytes[2] & 0x3F) << 6)  |
                 ((bytes[3] & 0x3F) << 0);
        break;

    default:
        result = static_cast<utf32char_t>(-1);
        break;
    }
    return result;
}

//--------------------------------------------------------------------------------------------------
inline char utf8char_t::ToAscii(char chDefault) const
{
    // char differs by compiler as to whether it promotes as signed or unsigned, so explicitly
    // cast the type here:
    if ((UInt8)bytes[0] <= (UInt8)0x7F)
        return bytes[0];
    return chDefault;
}

//--------------------------------------------------------------------------------------------------
inline utf8char_t utf8char_t::from_stream(const char* buffer_sz)
{
    utf8char_t temp;
    unsigned s = utf8_num_units(buffer_sz);
    unsigned i;

    for (i = 0; i < s; ++i)
    {
        temp.bytes[i] = buffer_sz[i];
    }

    for (/*unsigned i = s*/; i < utf8char_t::kReservedBytes; ++i)
    {
        temp.bytes[i] = 0;
    }

    return temp;
}

//--------------------------------------------------------------------------------------------------
inline bool utf8char_t::is_valid() const
{
    return utf8_validate_char(c_str(), size());
}

//--------------------------------------------------------------------------------------------------
inline unsigned utf8char_t::size() const
{
    return utf8_num_units(&(bytes[0]));
}

//--------------------------------------------------------------------------------------------------
inline utf8char_t& utf8char_t::operator=(const utf8char_t& rhs)
{
    ::memcpy(bytes, rhs.bytes, kReservedBytes);
    return (*this);
}

//--------------------------------------------------------------------------------------------------
inline const char* utf8char_t::c_str() const
{
    return &(bytes[0]);
}

//--------------------------------------------------------------------------------------------------
inline bool utf8char_t::operator==(const utf8char_t& rhs) const
{
    return (efd::Strcoll(c_str(), rhs.c_str()) == 0);
}

//--------------------------------------------------------------------------------------------------
inline bool utf8char_t::operator==(efd::Char rhs) const
{
    return bytes[0] == rhs && bytes[1] == '\0';
}

//--------------------------------------------------------------------------------------------------
inline bool utf8char_t::operator!=(const utf8char_t& rhs) const
{
    return !(*this == rhs);
}

//--------------------------------------------------------------------------------------------------
inline bool utf8char_t::operator!=(efd::Char rhs) const
{
    return !(*this == rhs);
}

//--------------------------------------------------------------------------------------------------
inline bool utf8char_t::operator<(const utf8char_t& rhs) const
{
    return (efd::Strcoll(c_str(), rhs.c_str()) < 0);
}

//--------------------------------------------------------------------------------------------------
inline bool utf8char_t::operator<=(const utf8char_t& rhs) const
{
    return (efd::Strcoll(c_str(), rhs.c_str()) <= 0);
}

//--------------------------------------------------------------------------------------------------
inline bool utf8char_t::operator>(const utf8char_t& rhs) const
{
    return (efd::Strcoll(c_str(), rhs.c_str()) > 0);
}

//--------------------------------------------------------------------------------------------------
inline bool utf8char_t::operator>=(const utf8char_t& rhs) const
{
    return (efd::Strcoll(c_str(), rhs.c_str()) >= 0);
}

//--------------------------------------------------------------------------------------------------

} // end namespace efd.
