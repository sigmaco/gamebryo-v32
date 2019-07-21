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
#ifndef NIBINARYSHADERLIB_H
#define NIBINARYSHADERLIB_H

#include "NiBinaryShaderLibLibType.h"

class NiRenderer;
class NiShaderLibrary;

bool NSBShaderLib_LoadShaderLibrary(NiRenderer* pkRenderer,
    int iDirectoryCount, const char* apcDirectories[], bool bRecurseSubFolders,
    NiShaderLibrary** ppkLibrary);
bool NiBinaryShaderLib_LoadShaderLibrary(NiRenderer* pkRenderer,
    int iDirectoryCount, const char* apcDirectories[], bool bRecurseSubFolders,
    NiShaderLibrary** ppkLibrary);

#if !defined(NIBINARYSHADERLIB_IMPORT) && !defined(NIBINARYSHADERLIB_EXPORT)
#include "NiBinaryShaderLibSDM.h"
static NiBinaryShaderLibSDM NiBinaryShaderLibSDMObject;
#endif

#endif  //NIBINARYSHADERLIB_H
