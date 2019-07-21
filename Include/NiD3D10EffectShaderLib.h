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

#ifndef NID3D10EFFECTSHADERLIB_H
#define NID3D10EFFECTSHADERLIB_H

#include "NiD3D10EffectShaderLibType.h"
#include <NiShaderLibrary.h>

bool NiD3D10EffectShaderLib_LoadShaderLibrary(
    NiRenderer* pkRenderer, NiInt32 iDirectoryCount,
    const char* apcDirectories[], bool bRecurseSubFolders,
    NiShaderLibrary** ppkLibrary);

NiUInt32 NiD3D10EffectShaderLib_GetD3D10EffectHLSLFlags();
void NiD3D10EffectShaderLib_SetD3D10EffectHLSLFlags(NiUInt32 uiHLSLFlags);

NiUInt32 NiD3D10EffectShaderLib_GetD3D10EffectFXFlags();
void NiD3D10EffectShaderLib_SetD3D10EffectFXFlags(NiUInt32 uiFXFlags);

void NiD3D10EffectShaderLib_AddFileExtension(const char* pcExtension,
    bool bCompiled);
void NiD3D10EffectShaderLib_RemoveFileExtension(const char* pcExtension);

void NiD3D10EffectShaderLib_EnableFXLSupport(bool bEnable);

#if !defined(NID3D10EFFECTSHADER_IMPORT) && !defined(NID3D10EFFECTSHADER_EXPORT)
#include "NiD3D10EffectShaderSDM.h"
static NiD3D10EffectShaderSDM NiD3D10EffectShaderSDMObject;
#endif

#endif  //NID3D10EFFECTSHADERLIB_H
