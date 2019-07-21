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
#ifndef EE_ICPPAPI_H
#define EE_ICPPAPI_H

#include <efd/ServiceManager.h>
#include <egf/Scheduler.h>
#include <efd/ILogger.h>

/**
    We define this macro in order to support export (from the entity library)
    and import (into other users of our dll), and for static libs
    so we know the names our dll exports (if we compile for windows)
*/
#if defined(WIN32) || defined(_XENON)
#pragma warning(disable: 4786)
#ifdef EE_SCRIPT_EXPORT
// if we are including as part of XXX.dll (any script library)
#define SCRIPTENTRY __declspec (dllexport)
#elif defined(_WINDLL) || defined (USEDLL)
// if we are including as part of a client (we are a library)
#define SCRIPTENTRY __declspec (dllimport)
#else
// if we are defining for a static build (NOT a .dll)
#define SCRIPTENTRY
#endif
#else
// if we are compiling for a non-windows build
#define SCRIPTENTRY
#endif// global to keep scheduler pointer for use by user scripts


#endif //EE_ICPPAPI_H
