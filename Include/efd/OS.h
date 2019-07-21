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
#ifndef EE_OS_H
#define EE_OS_H

//--------------------------------------------------------------------------------------------------

/// Detect the compiler.
#if defined(_MSC_VER)
#   define EE_MSVC_COMPILER
#elif defined(__GNUC__)
#   define EE_GCC_COMPILER
#endif

//--------------------------------------------------------------------------------------------------

/// Detect the target operating system.  For each platform, standard tool-provided macros are
/// checked first, then common user-supplied ones.  Note that the order of platform evaluation is
/// significant in some cases.

#if defined(__linux__) || defined(linux)
#   if !defined(EE_PLATFORM_LINUX)
#       define EE_PLATFORM_LINUX
#   endif
/// Warning: _WIN32 will be defined if devenv.exe is used to batch build a SN VSI project instead
/// of vsibuild.exe, which may produce difficult to diagnose compile errors.  So we check for PS3
/// first to avoid this situation.
#elif defined(SN_TARGET_PS3) || defined(_PS3) || defined(PS3)
#   if !defined(EE_PLATFORM_PS3)
#       define EE_PLATFORM_PS3
#   endif
/// Warning: _XBOX_VER check must precede _WIN32 check
#elif _XBOX_VER >= 200 || defined(_XENON)
#   if !defined(EE_PLATFORM_XBOX360)
#       define EE_PLATFORM_XBOX360
#   endif
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#   if !defined(EE_PLATFORM_WIN32)
#       define EE_PLATFORM_WIN32
#   endif
#else
#   error Could not identify platform
#endif

//--------------------------------------------------------------------------------------------------

/// Verify that a build configuration has been selected.
#if !defined(EE_EFD_CONFIG_DEBUG) && \
    !defined(EE_EFD_CONFIG_RELEASE) && \
    !defined(EE_EFD_CONFIG_SHIPPING)
#error One of EE_EFD_CONFIG_DEBUG, EE_EFD_CONFIG_RELEASE, or EE_EFD_CONFIG_SHIPPING must be defined
#endif

//--------------------------------------------------------------------------------------------------

/// Detect the current hardware architecture.
#if defined(__x86_64__) || defined(_M_X64) || defined(__LP64__)
#   define EE_ARCH_64
#else
#   define EE_ARCH_32
#endif

//--------------------------------------------------------------------------------------------------

/**
    The EE_USE_PER_THREAD_ALLOCATOR_POOLS define affects how the Small Object Allocator and
    GB Pool allocators function.  If set to 1, then per-thread storage will be used to
    provide a contention free cache of allocations.

    This increases the speed of allocations, especially in high-contention situations, but
    can result in slightly higher memory usage.  For applications where there is very little
    contention, few steady-state allocations, or memory is a major issue, it is probably best
    to turn this define off.  By default it is enabled on all platforms.
*/
#ifndef EE_USE_PER_THREAD_ALLOCATOR_POOLS
#    if defined(EE_PLATFORM_WIN32)
#        define EE_USE_PER_THREAD_ALLOCATOR_POOLS 1
#    elif defined(EE_PLATFORM_XBOX360)
#        define EE_USE_PER_THREAD_ALLOCATOR_POOLS 1
#    elif defined(EE_PLATFORM_PS3)
#        define EE_USE_PER_THREAD_ALLOCATOR_POOLS 1
#    elif defined(EE_PLATFORM_LINUX)
#        define EE_USE_PER_THREAD_ALLOCATOR_POOLS 1
#    else
#        error "Unknown platform"
#    endif
#endif

//--------------------------------------------------------------------------------------------------

/**
    The EE_PLATFORM_SPECIFIC_INCLUDE macro is used to ensure that when new platforms are added, no
    missing platform-specific includes will go unnoticed.

    As an example:
        #include EE_PLATFORM_SPECIFIC_INCLUDE(efd,OS,h)
    is equivalent to the following on Win32:
        #include <efd/Win32/OS_Win32.h>

    @note There must be no spaces in the macro invocation, or GCC will substitute them in along
        with the other tokens, constructing an invalid filename for the include.
*/
#if defined(EE_PLATFORM_LINUX)
    #define EE_PLATFORM_SPECIFIC_INCLUDE(Directory, File, Extension) \
        <Directory/Linux/File##_Linux.Extension>
#elif defined(EE_PLATFORM_PS3)
    #define EE_PLATFORM_SPECIFIC_INCLUDE(Directory, File, Extension) \
        <Directory/PS3/File##_PS3.Extension>
#elif defined(EE_PLATFORM_WIN32)
    #define EE_PLATFORM_SPECIFIC_INCLUDE(Directory, File, Extension) \
        <Directory/Win32/File##_Win32.Extension>
#elif defined(EE_PLATFORM_XBOX360)
    #define EE_PLATFORM_SPECIFIC_INCLUDE(Directory, File, Extension) \
        <Directory/Xbox360/File##_XBox360.Extension>
#else
    #error "Unsupported platform"
#endif

//--------------------------------------------------------------------------------------------------

// Include the platform specific header.
#include EE_PLATFORM_SPECIFIC_INCLUDE(efd,OS,h)

//--------------------------------------------------------------------------------------------------

#endif
