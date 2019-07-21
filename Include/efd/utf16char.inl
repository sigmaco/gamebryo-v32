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


// utf16char_t implementation

namespace efd
{

//--------------------------------------------------------------------------------------------------
// utf16char_t()  [ctor]
inline utf16char_t::utf16char_t()
{
    ::memset(units, 0, kReservedBytes);
}

//--------------------------------------------------------------------------------------------------
// utf16char_t()  [copy ctor]
inline utf16char_t::utf16char_t(const utf16char_t& rhs)
{
    ::memcpy(units, rhs.units, kReservedBytes);
}

//--------------------------------------------------------------------------------------------------
// utf16char_t()  [copy ctor]
inline utf16char_t::utf16char_t(const utf8char_t& rhs)
{
    FromUTF32(rhs.ToUTF32());
}

//--------------------------------------------------------------------------------------------------
// utf16char_t()  [ctor]
// Wikipedia definition of UTF16: http://en.wikipedia.org/wiki/UTF-16
inline utf16char_t::utf16char_t(const wchar_t wch)
{
    EE_ASSERT(wch < 0xD800 || wch > 0xDFFF);
    ::memset(units, 0, kReservedBytes);
    units[0] = wch;
}

//--------------------------------------------------------------------------------------------------
// utf16char_t()  [ctor]
// Wikipedia definition of UTF16: http://en.wikipedia.org/wiki/UTF-16
inline utf16char_t::utf16char_t(utf32char_t code)
{
    FromUTF32(code);
}

//--------------------------------------------------------------------------------------------------
// FromUTF32()
// see: http://tools.ietf.org/html/rfc2781
inline void utf16char_t::FromUTF32(utf32char_t code)
{
    // The highest valid value under the Unicode 3.1 spec is 0x10ffff.  Any value above this is
    // not a valid character.
    EE_ASSERT(code <= 0x10ffff);

    ::memset(units, 0, kReservedBytes);

    if (code < 0x10000)
    {
        units[0] = static_cast<char>(code);
    }
    else
    {
        // subtract 0x1000000
        code -= 0x10000;
        units[0] = static_cast<char>(0xD800 | (code  >> 10));
        units[1] = static_cast<char>(0xDC00 | (code & 0x3FF));
    }
}

//--------------------------------------------------------------------------------------------------
// ToUTF32()
// see: http://tools.ietf.org/html/rfc2781
inline utf32char_t utf16char_t::ToUTF32() const
{
    utf32char_t result;
    if (units[0] < 0xD800 || units[0] > 0xDFFF)
    {
        result = units[0];
    }
    else
    {
        EE_ASSERT(units[0] >= 0xD800 && units[0] <= 0xDBFF);
        EE_ASSERT(units[1] >= 0xDC00 && units[1] <= 0xDFFF);

        result = (units[0] & 0x3FF) << 10 |
                 (units[1] & 0x3FF);
        result += 0x10000;
    }

    return result;
}

//--------------------------------------------------------------------------------------------------
// from_stream()  [static]
inline utf16char_t utf16char_t::from_stream(const efd::WChar* buffer_sz)
{
    utf16char_t temp;
    unsigned s = utf16_num_units(buffer_sz);
    unsigned i;

    for (i = 0; i < s; ++i)
    {
        temp.units[i] = buffer_sz[i];
    }

    for (/*unsigned i = s*/; i < utf16char_t::kReservedUnits; ++i)
    {
        temp.units[i] = 0;
    }

    return temp;
}

//--------------------------------------------------------------------------------------------------
// is_valid()
inline bool utf16char_t::is_valid() const
{
    return utf16_validate_char(c_str(), size());
}

//--------------------------------------------------------------------------------------------------
// size()
inline unsigned utf16char_t::size() const
{
    return utf16_num_units(&(units[0]));
}

//--------------------------------------------------------------------------------------------------
// operator=()
inline utf16char_t& utf16char_t::operator=(const utf16char_t& rhs)
{
    ::memcpy(units, rhs.units, kReservedBytes);
    return (*this);
}

//--------------------------------------------------------------------------------------------------
// c_str()
inline const efd::WChar* utf16char_t::c_str() const
{
    return &(units[0]);
}

//--------------------------------------------------------------------------------------------------
// operator==()
inline bool utf16char_t::operator==(const utf16char_t& rhs) const
{
    return (efd::Strcoll(c_str(), rhs.c_str()) == 0);
}

//--------------------------------------------------------------------------------------------------
// operator!=()
inline bool utf16char_t::operator!=(const utf16char_t& rhs) const
{
    return !(*this == rhs);
}

//--------------------------------------------------------------------------------------------------
// operator<()
inline bool utf16char_t::operator<(const utf16char_t& rhs) const
{
    return (efd::Strcoll(c_str(), rhs.c_str()) < 0);
}

//--------------------------------------------------------------------------------------------------
// operator<=()
inline bool utf16char_t::operator<=(const utf16char_t& rhs) const
{
    return (efd::Strcoll(c_str(), rhs.c_str()) <= 0);
}

//--------------------------------------------------------------------------------------------------
// operator>()
inline bool utf16char_t::operator>(const utf16char_t& rhs) const
{
    return (efd::Strcoll(c_str(), rhs.c_str()) > 0);
}

//--------------------------------------------------------------------------------------------------
// operator>=()
inline bool utf16char_t::operator>=(const utf16char_t& rhs) const
{
    return (efd::Strcoll(c_str(), rhs.c_str()) >= 0);
}

//--------------------------------------------------------------------------------------------------

};  // End namespace efd.
