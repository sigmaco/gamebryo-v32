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
#ifndef EE_ENDIAN_H
#define EE_ENDIAN_H

#include <efd/Asserts.h>

namespace efd
{

/**
    A platform-independent utility class to encapsulate an in-place endian
    conversion for arrays of 16, 32, and 64-bit values.
*/
class EE_EFD_ENTRY Endian
{
public:
    /// In-place swap of byte order for a 2-byte variable
    static void Swap16(char* pcValue, unsigned int uiCount = 1);

    /// In-place swap of byte order for a 4-byte variable
    static void Swap32(char* pcValue, unsigned int uiCount = 1);

    /// In-place swap of byte order for a 8-byte variable
    static void Swap64(char* pcValue, unsigned int uiCount = 1);
};

} // end namespace efd

#if defined(EE_PLATFORM_WIN32)
#include <efd/Win32/Endian_Win32.inl>
#elif defined(EE_PLATFORM_LINUX)
#include <efd/Linux/Endian_Linux.inl>
#elif defined(EE_PLATFORM_XBOX360)
#include <efd/Xbox360/Endian_Xbox360.inl>
#elif defined(EE_PLATFORM_PS3)
#include <efd/PS3/Endian_PS3.inl>
#else
#error Unknown platform
#endif

#endif
