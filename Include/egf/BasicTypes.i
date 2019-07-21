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


 // Some of our headers exist only to suck in the real platform specific header
%import "efd/UniversalTypes.h"

// Unfortunately all the real typedefs are in the platform specific file and %include does not
// recursiving include other things (which is a good thing, we don't want "-includeall" because
// it would pull in WAY too much cruft).  This means we are forced to directly include the
// platform specific stuff.
#if defined( EE_PLATFORM_WIN32 )
%import "efd/Win32/UniversalTypes_Win32.h"

#elif defined( EE_PLATFORM_XBOX360 )
%import "efd/Xbox360/UniversalTypes_Xbox360.h"

#elif defined ( EE_PLATFORM_PS3 )
%import "efd/PS3/UniversalTypes_PS3.h"

#elif defined ( EE_PLATFORM_WII )
%import "efd/Wii/UniversalTypes_Wii.h"

#elif defined( EE_PLATFORM_LINUX )

// including sys/types.h would be ideal, but because swig does not have the proper defines set and
// does not recursively include files, sys/types.h is not easy to include
#ifdef EE_ARCH_64
namespace efd
{
typedef signed long SInt64;
typedef unsigned long UInt64;
};
#endif
%import "efd/Linux/UniversalTypes_Linux.h"
#endif
