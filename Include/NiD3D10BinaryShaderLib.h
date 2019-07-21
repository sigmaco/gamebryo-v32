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
#ifndef NID3D10BINARYSHADERLIB_H
#define NID3D10BINARYSHADERLIB_H

#include "NiD3D10BinaryShaderLibLibType.h"

class NiRenderer;
class NiShaderLibrary;

bool NiD3D10BinaryShaderLib_LoadShaderLibrary(NiRenderer* pkRenderer,
    int iDirectoryCount, const char* apcDirectories[], bool bRecurseSubFolders,
    NiShaderLibrary** ppkLibrary);

#if !defined(NID3D10BINARYSHADERLIB_IMPORT) && !defined(NID3D10BINARYSHADERLIB_EXPORT)
#include "NiD3D10BinaryShaderLibSDM.h"
static NiD3D10BinaryShaderLibSDM NiD3D10BinaryShaderLibSDMObject;
#endif

#endif  //NID3D10BINARYSHADERLIB_H
