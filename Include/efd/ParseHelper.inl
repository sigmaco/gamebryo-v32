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


//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Bool>::FromString(
    const efd::utf8string& i_value,
    efd::Bool& o_result)
{
    // Expects either a 1 or 0, error on anything else
    if (i_value == "1" || 0 == i_value.icompare("true"))
    {
        o_result = true;
        return true;
    }
    else if (i_value == "0" || 0 == i_value.icompare("false"))
    {
        o_result = false;
        return true;
    }
    else
    {
        return false;
    }
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Bool>::ToString(
    efd::Bool i_value,
    efd::utf8string& o_result)
{
    if (i_value)
    {
        o_result = "true";
    }
    else
    {
        o_result = "false";
    }
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::UInt8>::FromString(
    const efd::utf8string& i_value,
    efd::UInt8& o_result)
{
    efd::UInt32 temp;
    if (ParseHelper<efd::UInt32>::FromString(i_value, temp))
    {
        if (temp <= EE_UINT8_MAX)
        {
            o_result = static_cast<efd::UInt8>(temp);
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::UInt8>::ToString(
    efd::UInt8 i_value,
    efd::utf8string& o_result)
{
    efd::UInt32 temp = i_value;
    return ParseHelper<efd::UInt32>::ToString(temp, o_result);
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::SInt8>::FromString(
    const efd::utf8string& i_value,
    efd::SInt8& o_result)
{
    efd::SInt32 temp;
    if (ParseHelper<efd::SInt32>::FromString(i_value, temp))
    {
        if (abs(temp) <= EE_SINT8_MAX)
        {
            o_result = static_cast<efd::SInt8>(temp);
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::SInt8>::ToString(
    efd::SInt8 i_value,
    efd::utf8string& o_result)
{
    efd::SInt32 temp = i_value;
    return ParseHelper<efd::SInt32>::ToString(temp, o_result);
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::UInt16>::FromString(
    const efd::utf8string& i_value,
    efd::UInt16& o_result)
{
    efd::UInt32 temp;
    if (ParseHelper<efd::UInt32>::FromString(i_value, temp))
    {
        if (temp <= EE_UINT16_MAX)
        {
            o_result = static_cast<efd::UInt16>(temp);
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::UInt16>::ToString(
    efd::UInt16 i_value,
    efd::utf8string& o_result)
{
    efd::UInt32 temp = i_value;
    return ParseHelper<efd::UInt32>::ToString(temp, o_result);
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::SInt16>::FromString(
    const efd::utf8string& i_value,
    efd::SInt16& o_result)
{
    efd::SInt32 temp;
    if (ParseHelper<efd::SInt32>::FromString(i_value, temp))
    {
        if (abs(temp) <= EE_SINT16_MAX)
        {
            o_result = static_cast<efd::SInt16>(temp);
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::SInt16>::ToString(
    efd::SInt16 i_value,
    efd::utf8string& o_result)
{
    efd::SInt32 temp = i_value;
    return ParseHelper<efd::SInt32>::ToString(temp, o_result);
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::UInt32>::FromString(
    const efd::utf8string& i_value,
    efd::UInt32& o_result)
{
    const efd::Char* pEnd;
    o_result = efd::strtoul(i_value.c_str(), &pEnd);

    // If successful, the entire string will have been consumed and thus pEnd will point
    // to the trailing NULL terminator.
    return (*pEnd == '\0');
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::UInt32>::ToString(
    efd::UInt32 i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("%u", i_value);
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::SInt32>::FromString(
    const efd::utf8string& i_value,
    efd::SInt32& o_result)
{
    const efd::Char* pEnd;
    o_result = efd::strtol(i_value.c_str(), &pEnd);

    // If successful, the entire string will have been consumed and thus pEnd will point
    // to the trailing NULL terminator.
    return (*pEnd == '\0');
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::SInt32>::ToString(
    efd::SInt32 i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("%d", i_value);
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::UInt64>::FromString(
    const efd::utf8string& i_value,
    efd::UInt64& o_result)
{
    const efd::Char* pEnd;
    o_result = efd::strtoull(i_value.c_str(), &pEnd);

    // If successful, the entire string will have been consumed and thus pEnd will point
    // to the trailing NULL terminator.
    return (*pEnd == '\0');
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::UInt64>::ToString(
    efd::UInt64 i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("%llu", i_value);
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::SInt64>::FromString(
    const efd::utf8string& i_value,
    efd::SInt64& o_result)
{
    const efd::Char* pEnd;
    o_result = efd::strtoll(i_value.c_str(), &pEnd);

    // If successful, the entire string will have been consumed and thus pEnd will point
    // to the trailing NULL terminator.
    return (*pEnd == '\0');
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::SInt64>::ToString(
    efd::SInt64 i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("%lld", i_value);
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Float32>::FromString(
    const efd::utf8string& i_value,
    efd::Float32& o_result)
{
    const efd::Char* pEnd;
    o_result = efd::strtof(i_value.c_str(), &pEnd);

    // If successful, the entire string will have been consumed and thus pEnd will point
    // to the trailing NULL terminator.
    return (*pEnd == '\0');
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Float32>::ToString(
    efd::Float32 i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("%f", i_value);
    return true;
}


//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Float64>::FromString(
    const efd::utf8string& i_value,
    efd::Float64& o_result)
{
    const efd::Char* pEnd;
    o_result = efd::strtod(i_value.c_str(), &pEnd);

    // If successful, the entire string will have been consumed and thus pEnd will point
    // to the trailing NULL terminator.
    return (*pEnd == '\0');
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Float64>::ToString(
    efd::Float64 i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("%f", i_value);
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::utf8char_t>::FromString(
    const efd::utf8string& i_value,
    efd::utf8char_t& o_result)
{
    switch (i_value.length())
    {
    case 1:
        o_result = i_value[0];
        return true;

    case 0:
        // an empty string points to a NULL character, if we don't special case this we can't
        // ever set the value to NULL.
        o_result.FromUTF32(0);
        return true;

    default:
        break;
    }

    return false;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::utf8char_t>::ToString(
    const efd::utf8char_t& i_value,
    efd::utf8string& o_result)
{
    o_result = i_value;
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::utf16char_t>::FromString(
    const efd::utf8string& i_value,
    efd::utf16char_t& o_result)
{
    if (1 == i_value.length())
    {
        efd::utf8char_t ch = i_value[0];
        efd::utf16char_t wch(ch);
        o_result = wch;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::utf16char_t>::ToString(
    const efd::utf16char_t& i_value,
    efd::utf8string& o_result)
{
    efd::utf8char_t ch(i_value.ToUTF32());
    o_result = ch;
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::utf8string>::FromString(
    const efd::utf8string& i_value,
    efd::utf8string& o_result)
{
    o_result = i_value;
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::utf8string>::ToString(
    const efd::utf8string& i_value,
    efd::utf8string& o_result)
{
    o_result = i_value;
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Point2>::FromString(
    const efd::utf8string& i_value,
    efd::Point2& o_result)
{
    // Split the string into two tokens ignoring "<>(), \t"
    // Use Float32 parser on each sub-token
    efd::utf8string seperators(" \t,<>(){}[]");
    efd::vector<efd::utf8string> tokens(2);
    if (2 != i_value.split(seperators, tokens))
    {
        return false;
    }

    bool result = true;
    result &= ParseHelper<efd::Float32>::FromString(tokens[0], o_result.x);
    result &= ParseHelper<efd::Float32>::FromString(tokens[1], o_result.y);

    return result;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Point2>::ToString(
    const efd::Point2& i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("<%f, %f>", i_value.GetX(), i_value.GetY());
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Point3>::FromString(
    const efd::utf8string& i_value,
    efd::Point3& o_result)
{
    // Split the string into two tokens ignoring "<>(), \t"
    // Use Float32 parser on each sub-token
    efd::utf8string seperators(" \t,<>(){}[]");
    efd::vector<efd::utf8string> tokens(3);
    if (3 != i_value.split(seperators, tokens))
    {
        return false;
    }

    bool result = true;
    result &= ParseHelper<efd::Float32>::FromString(tokens[0], o_result.x);
    result &= ParseHelper<efd::Float32>::FromString(tokens[1], o_result.y);
    result &= ParseHelper<efd::Float32>::FromString(tokens[2], o_result.z);

    return result;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Point3>::ToString(
    const efd::Point3& i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("<%f, %f, %f>", i_value.x, i_value.y, i_value.z);
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Point4>::FromString(
    const efd::utf8string& i_value,
    efd::Point4& o_result)
{
    // Split the string into two tokens ignoring "<>(), \t"
    // Use Float32 parser on each sub-token
    efd::utf8string seperators(" \t,<>(){}[]");
    efd::vector<efd::utf8string> tokens(4);
    if (4 != i_value.split(seperators, tokens))
    {
        return false;
    }

    bool result = true;
    result &= ParseHelper<efd::Float32>::FromString(tokens[0], o_result.m_afPt[0]);
    result &= ParseHelper<efd::Float32>::FromString(tokens[1], o_result.m_afPt[1]);
    result &= ParseHelper<efd::Float32>::FromString(tokens[2], o_result.m_afPt[2]);
    result &= ParseHelper<efd::Float32>::FromString(tokens[3], o_result.m_afPt[3]);

    return result;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Point4>::ToString(
    const efd::Point4& i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("<%f, %f, %f, %f>",
        i_value.m_afPt[0], i_value.m_afPt[1], i_value.m_afPt[2], i_value.m_afPt[3]);
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Matrix3>::FromString(
    const efd::utf8string& i_value,
    efd::Matrix3& o_result)
{
    // Split the string into two tokens ignoring "<>(), \t"
    // Use Float32 parser on each sub-token
    efd::utf8string seperators(" \t,<>(){}[]");
    efd::vector<efd::utf8string> tokens(9);
    if (9 != i_value.split(seperators, tokens))
    {
        return false;
    }

    bool result = true;
    for (int row=0; row < 3; ++row)
    {
        for (int col=0; col < 3; ++col)
        {
            efd::Float32 temp;
            if (ParseHelper<efd::Float32>::FromString(tokens[row*3 + col], temp))
            {
                o_result.SetEntry(row, col, temp);
            }
            else
            {
                result = false;
            }
        }
    }

    return result;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Matrix3>::ToString(
    const efd::Matrix3& i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("{ (%f, %f, %f), (%f, %f, %f), (%f, %f, %f) }",
        i_value.GetEntry(0, 0), i_value.GetEntry(0, 1), i_value.GetEntry(0, 2),
        i_value.GetEntry(1, 0), i_value.GetEntry(1, 1), i_value.GetEntry(1, 2),
        i_value.GetEntry(2, 0), i_value.GetEntry(2, 1), i_value.GetEntry(2, 2));
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Color>::FromString(const efd::utf8string& i_value,
                                                        efd::Color& o_result)
{
    // Split the string into two tokens ignoring "<>(), \t"
    // Use Float32 parser on each sub-token
    efd::utf8string seperators(" \t,<>(){}[]");
    efd::vector<efd::utf8string> tokens(3);
    if (3 != i_value.split(seperators, tokens))
    {
        return false;
    }

    bool result = true;
    result &= ParseHelper<efd::Float32>::FromString(tokens[0], o_result.m_r);
    result &= ParseHelper<efd::Float32>::FromString(tokens[1], o_result.m_g);
    result &= ParseHelper<efd::Float32>::FromString(tokens[2], o_result.m_b);

    return result;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::Color>::ToString(
    const efd::Color& i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("[%f, %f, %f]", i_value.m_r, i_value.m_g, i_value.m_b);
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::ColorA>::FromString(
    const efd::utf8string& i_value,
    efd::ColorA& o_result)
{
    // Split the string into two tokens ignoring "<>(), \t"
    // Use Float32 parser on each sub-token
    efd::utf8string seperators(" \t,<>(){}[]");
    efd::vector<efd::utf8string> tokens(4);
    if (4 != i_value.split(seperators, tokens))
    {
        return false;
    }

    bool result = true;
    result &= ParseHelper<efd::Float32>::FromString(tokens[0], o_result.m_r);
    result &= ParseHelper<efd::Float32>::FromString(tokens[1], o_result.m_g);
    result &= ParseHelper<efd::Float32>::FromString(tokens[2], o_result.m_b);
    result &= ParseHelper<efd::Float32>::FromString(tokens[3], o_result.m_a);

    return result;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::ColorA>::ToString(
    const efd::ColorA& i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("[%f, %f, %f, %f]", i_value.m_r, i_value.m_g, i_value.m_b, i_value.m_a);
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::ID128>::FromString(
    const efd::utf8string& i_value,
    efd::ID128& o_result)
{
    // In order to support guid-formated values we trim any {} brackets and strip out any dashes.
    efd::utf8string value = i_value;
    value.trim(efd::TrimAll, " \t{}");
    value.replace_substr("-", "");

    if (value.length() != 32)
    {
        return false;
    }

    //xxxxxxxx xxxx xxxx xxxx xx xx xx xx xx xx
    //c4c165ca-a705-4c36-a383-cab5620a851b

    const char* strguid = value.c_str();

    unsigned char guid[16];
    unsigned char* guidptr = guid;
    for (int i = 0; i < 32; i++)
    {
        int intValue = 0;
        char charValue = strguid[i];

        if (charValue == '0')
            intValue = 0;
        else if (charValue >= '1' && charValue <= '9')
            intValue = charValue - '0';
        else if (charValue >= 'a' && charValue <= 'f')
            intValue = charValue - 'a' + 10;
        else if (charValue >= 'A' && charValue <= 'F')
            intValue = charValue - 'A' + 10;
        else
            return false;

        if (i % 2 == 0)
        {
            *guidptr = static_cast<unsigned char>(intValue << 4);
        }
        else
        {
            *guidptr = *guidptr + static_cast<unsigned char>(intValue);
            guidptr++;
        }
    }

    // First part
    o_result.m_value[0] = guid[3];
    o_result.m_value[1] = guid[2];
    o_result.m_value[2] = guid[1];
    o_result.m_value[3] = guid[0];

    // Second part
    o_result.m_value[4] = guid[5];
    o_result.m_value[5] = guid[4];

    // Third part
    o_result.m_value[6] = guid[7];
    o_result.m_value[7] = guid[6];

    // Fourth part
    o_result.m_value[8] = guid[8];
    o_result.m_value[9] = guid[9];

    // Read single byte sections
    o_result.m_value[10] = guid[10];
    o_result.m_value[11] = guid[11];
    o_result.m_value[12] = guid[12];
    o_result.m_value[13] = guid[13];
    o_result.m_value[14] = guid[14];
    o_result.m_value[15] = guid[15];

    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::ID128>::ToString(
    const efd::ID128& i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
        i_value.m_value[3], i_value.m_value[2], i_value.m_value[1], i_value.m_value[0],
        i_value.m_value[5], i_value.m_value[4], i_value.m_value[7], i_value.m_value[6],
        i_value.m_value[8], i_value.m_value[9], i_value.m_value[10], i_value.m_value[11],
        i_value.m_value[12], i_value.m_value[13], i_value.m_value[14], i_value.m_value[15]);

    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::AssetID>::ToString(
    const efd::AssetID& i_value,
    efd::utf8string& o_result)
{
    o_result.sprintf("%s", i_value.c_str());
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool efd::ParseHelper<efd::AssetID>::FromString(
    const efd::utf8string& i_value,
    efd::AssetID& o_result)
{
    o_result.SetURN(i_value);
    return true;
}


