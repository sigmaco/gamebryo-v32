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
#ifndef EE_RTLIB_H
#define EE_RTLIB_H

/// @cond EMERGENT_INTERNAL

#include <efd/OS.h>


/// If EE_USE_NATIVE_STL is defined we attempt to use native STL instead of stlport.
/// @note Do not mix libs built with and without EE_USE_NATIVE_STL defined.
#if defined(EE_USE_NATIVE_STL)
#define EE_STL_NAMESPACE std
#else //defined(EE_USE_NATIVE_STL)
#define EE_STL_NAMESPACE efd::stlport
#endif //defined(EE_USE_NATIVE_STL)

// Disable warning C4251.  Template classes cannot be exported for the obvious
// reason that the code is not generated until an instance of the class is
// declared.  With this warning enabled, you get thousands of complaints about
// class data members that are of template type.  For example, a member such
// as 'vector<NiAVObject*> m_array' generates the warning.
//
// When maintaining the DLL code itself, you might want to enable the warning
// to check for cases where you might have failed to put the LIBRARYNAME_ENTRY
// after the class keyword.  In particular, nested classes must have
// LIBRARYNAME_ENTRY.  Also, friend functions must be tagged with
// LIBRARYNAME_ENTRY.

#ifdef EE_PLATFORM_WIN32
    #pragma warning(disable : 4251)
#endif

// Include the platform specific header
#include EE_PLATFORM_SPECIFIC_INCLUDE(efd,RTLib,h)

#include <efd/customalloc.h>

/// @endcond

#endif // EERTLIB_H
