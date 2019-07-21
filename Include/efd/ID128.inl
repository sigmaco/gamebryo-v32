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

#include <efd/RTLib.h>
#include <efd/StringUtilities.h>

namespace efd
{

//------------------------------------------------------------------------------------------------
inline ID128::ID128()
{
    memset(&m_value, 0, 16);
}

//------------------------------------------------------------------------------------------------
inline ID128::ID128(const UInt8* pCharID)
{
    efd::Memcpy(&m_value, pCharID, 16);
}

//------------------------------------------------------------------------------------------------
inline ID128::ID128(efd::UInt8 b01,
                     efd::UInt8 b02,
                     efd::UInt8 b03,
                     efd::UInt8 b04,
                     efd::UInt8 b05,
                     efd::UInt8 b06,
                     efd::UInt8 b07,
                     efd::UInt8 b08,
                     efd::UInt8 b09,
                     efd::UInt8 b10,
                     efd::UInt8 b11,
                     efd::UInt8 b12,
                     efd::UInt8 b13,
                     efd::UInt8 b14,
                     efd::UInt8 b15,
                     efd::UInt8 b16)
{
    m_value[0] = b01;
    m_value[1] = b02;
    m_value[2] = b03;
    m_value[3] = b04;
    m_value[4] = b05;
    m_value[5] = b06;
    m_value[6] = b07;
    m_value[7] = b08;
    m_value[8] = b09;
    m_value[9] = b10;
    m_value[10] = b11;
    m_value[11] = b12;
    m_value[12] = b13;
    m_value[13] = b14;
    m_value[14] = b15;
    m_value[15] = b16;
}

//------------------------------------------------------------------------------------------------
inline bool ID128::operator==(const ID128& rhs) const
{
    return (memcmp(&m_value, &rhs.m_value, 16) == 0);
}

//------------------------------------------------------------------------------------------------
inline bool ID128::operator!=(const ID128& rhs) const
{
    return (memcmp(&m_value, &rhs.m_value, 16) != 0);
}

//------------------------------------------------------------------------------------------------
inline bool ID128::operator<(const ID128& rhs) const
{
    return (memcmp(&m_value, &rhs.m_value, 16) < 0);
}

//------------------------------------------------------------------------------------------------
inline bool ID128::operator>(const ID128& rhs) const
{
    return (memcmp(&m_value, &rhs.m_value, 16) > 0);
}

//------------------------------------------------------------------------------------------------
inline bool ID128::IsValid() const
{
    static const ID128 kID128_Invalid;
    return *this != kID128_Invalid;
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
