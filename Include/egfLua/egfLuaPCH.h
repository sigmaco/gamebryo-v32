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

#include <efd/Asserts.h>
#include <efd/ServiceManager.h>
#include <efd/ILogger.h>
#include <efd/UniversalTypes.h>
#include <efd/efdLogIDs.h>
#include <egf/egfLogIDs.h>
#include <egf/egfMessageIDs.h>

#include <lua.h>
#include <lauxlib.h>

// don't care about C4505 - unreferenced local function has been removed
#if defined(_MSC_VER)
#pragma warning(disable:4505)
#endif


