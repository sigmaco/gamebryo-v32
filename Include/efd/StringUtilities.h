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
#ifndef EE_STRINGUTILITIES_H
#define EE_STRINGUTILITIES_H

#include <efd/OS.h>
#include <efd/efdLibType.h>
#include <efd/Asserts.h>

#include <efd/MemoryDefines.h>

/// Constant for Strncpy function
#if defined(_MSC_VER) && _MSC_VER >= 1400
    #define EE_TRUNCATE _TRUNCATE
#else
    #define EE_TRUNCATE ((size_t)-1)
#endif

namespace efd
{

/// @name Wrappers for some C Runtime functions from StringUtilities.h

//@{

// Functions defined inline, so no need for EE_EFD_ENTRY

/// Wrapper for std::strcpy using ASCII
inline efd::Char* Strcpy(efd::Char* dest, size_t destSize, const efd::Char* src);

/// Wrapper for std::strncpy using ASCII
inline efd::Char* Strncpy(efd::Char* dest, size_t destSize, const efd::Char* src, size_t count);

/// Wrapper for std::strcat using ASCII
inline efd::Char* Strcat(efd::Char* dest, size_t destSize, const efd::Char* src);

/// Wrapper for std::strncat using ASCII
inline efd::Char* Strncat(efd::Char* dest, size_t destSize, const efd::Char* src, size_t count);

/// Wrapper for std::strtok using ASCII
inline efd::Char* Strtok(efd::Char* str, const efd::Char* delimit, efd::Char** ppcContext);

/// Wrapper for std::sprintf using ASCII
EE_EFD_ENTRY efd::SInt32 Sprintf(efd::Char* dest, size_t destSize, const efd::Char* format, ...);

/// Wrapper for std::_vsprintf using ASCII
EE_EFD_ENTRY efd::SInt32 Vsprintf(efd::Char* dest, size_t destSize, const efd::Char* format,
    va_list args);

/// Wrapper for std::_vscprintf using ASCII
EE_EFD_ENTRY efd::SInt32 Vscprintf(const efd::Char* format, va_list args);

/// Wrapper for std::snprintf using ASCII
EE_EFD_ENTRY efd::SInt32 Snprintf(efd::Char* dest, size_t destSize, size_t count,
                                  const efd::Char* format, ...);

/// Wrapper for std::_vsnprintf using ASCII
EE_EFD_ENTRY efd::SInt32 Vsnprintf(efd::Char* dest, size_t destSize, size_t count,
    const efd::Char* format, va_list args);

/// Wrapper for _strupr_s using ASCII
inline efd::SInt32 Strupr(efd::Char* dest, size_t destSize);

/// Wrapper for _strlwr_s using ASCII
inline efd::SInt32 Strlwr(efd::Char* dest, size_t destSize);

/// wrapper for std::memcpy
inline efd::SInt32 Memcpy(void* dest, size_t destSize, const void* src, size_t count);

/// wrapper for std::memcpy
inline efd::SInt32 Memcpy(void* dest, const void* src, size_t count);

/// wrapper for std::memmove
inline efd::SInt32 Memmove(void* dest, size_t destSize, const void* src, size_t count);

inline efd::UInt32 Strlen(const efd::Char* str);
inline efd::UInt32 Strlen(const efd::WChar* str);

inline efd::SInt32 Strcoll(const efd::Char* str1, const efd::Char* str2);
inline efd::SInt32 Strcoll(const efd::WChar* str1, const efd::WChar* str2);

/// Wrapper around _atoi64
inline efd::UInt64 Atoi64(const efd::Char* buffer);

/// Wrapper around strtol.  For completeness and const correctness.
inline efd::SInt32 strtol(const efd::Char* buffer, const efd::Char** endPtr, efd::UInt8 base = 0);
inline efd::UInt32 strtoul(const efd::Char* buffer, const efd::Char** endPtr, efd::UInt8 base = 0);

/// Wrapper around _strtoi64 and _strtoui64
inline efd::SInt64 strtoll(const efd::Char* buffer, const efd::Char** endPtr, efd::UInt8 base = 0);
inline efd::UInt64 strtoull(const efd::Char* buffer, const efd::Char** endPtr, efd::UInt8 base = 0);

/// Wrapper around atof
inline efd::Float32 strtof(const efd::Char* buffer, const efd::Char** endPtr);
inline efd::Float64 strtod(const efd::Char* buffer, const efd::Char** endPtr);

/// wrapper for std::stricmp
EE_EFD_ENTRY efd::SInt32 Stricmp(const efd::Char* s1, const efd::Char* s2);

/// wrapper for std::strnicmp
EE_EFD_ENTRY efd::SInt32 Strnicmp(const efd::Char* s1, const efd::Char* s2, size_t n);

/// wrapper for strdup. This uses the emergent allocator instead of malloc.
EE_EFD_ENTRY efd::Char* Strdup(const efd::Char* str);

//------------------------------------------------------------------------------------------------

#if defined(EE_PLATFORM_LINUX)
//DT32425 Implement 16 bit versions of these functions for Linux
#define WStrcpy EE_COMPILETIME_ASSERT(false)
#define WStrncpy EE_COMPILETIME_ASSERT(false)
#define WStrcat EE_COMPILETIME_ASSERT(false)
#define WStrtok EE_COMPILETIME_ASSERT(false)
#define WSprintf EE_COMPILETIME_ASSERT(false)
#define WStrupr EE_COMPILETIME_ASSERT(false)
#define WStrlwr EE_COMPILETIME_ASSERT(false)
#else

/// Wrapper for strcpy using 16-bit wide chars
inline efd::WChar* WStrcpy(WChar* dest, size_t destSize, const WChar* src);

/// Wrapper for strncpy using 16-bit wide chars
inline efd::WChar* WStrncpy(WChar* dest, size_t destSize, const WChar* src, size_t count);

/// Wrapper for strcat using 16-bit wide chars
inline efd::WChar* WStrcat(WChar* dest, size_t destSize, const WChar* src);

/// Wrapper for strtok using 16-bit wide chars
inline efd::WChar* WStrtok(WChar* str, const WChar* delimiters, WChar** ppContext);

/// Wrapper for sprintf using 16-bit wide chars
inline efd::SInt32 WSprintf(WChar* dest, size_t destSize, const WChar* format, ...);

/// Wrapper for strupr using 16-bit wide chars
inline efd::SInt32 WStrupr(efd::WChar* dest, size_t destSize);

/// Wrapper for strlwr using 16-bit wide chars
inline efd::SInt32 WStrlwr(efd::WChar* dest, size_t destSize);
#endif

//@}

} // end namespace efd

#include <efd/StringConverters.h>

// Include the platform specific inline functions
#include EE_PLATFORM_SPECIFIC_INCLUDE(efd,StringUtilities,inl)

#endif // EE_STRINGUTILITIES_H

