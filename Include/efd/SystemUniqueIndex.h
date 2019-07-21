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
#ifndef __SystemUniqueIndex_h__
#define __SystemUniqueIndex_h__



/**
    @class SystemUniqueIndex

    This class creates a cross-process unique index given a base name.  For example, if you pass
    in your process name as the base name then it will give you an index that is guaranteed not
    to be in use by any of the other processes which could be used to generate, say, a unique
    log file name like "MyProcessName%d.log".  To accomplish this a named kernel object is used.
    As such the instance of the SystemUniqueIndex class must have the same lifespan as your usage
    of that index.  Indices will be reused as soon as the SystemUniqueIndex class that used that
    index is destructed.

    @note Indices start at 1, index 0 indicates an error.

 */


#if defined(EE_PLATFORM_WIN32)
#include <efd/Win32/SystemUniqueIndex_Win32.inl>
#elif defined(EE_PLATFORM_LINUX)
#include <efd/Linux/SystemUniqueIndex_Linux.inl>
#elif defined(EE_PLATFORM_PS3)
#include <efd/PS3/SystemUniqueIndex_PS3.inl>
#elif defined(EE_PLATFORM_XBOX360)
#include <efd/XBox360/SystemUniqueIndex_Xbox360.inl>
#endif


#endif // EE_IDATASTREAM_H
