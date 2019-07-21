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

#ifndef NID3DXEFFECTSHADERLIB_H
#define NID3DXEFFECTSHADERLIB_H

#include "NiD3DXEffectShaderLibType.h"
#include <NiD3DShaderLibrary.h>

bool NiD3DXEffectShaderLib_LoadShaderLibrary(
    NiRenderer* pkRenderer, int iDirectoryCount, const char* apcDirectories[],
    bool bRecurseSubFolders, NiShaderLibrary** ppkLibrary);

unsigned int NiD3DXEffectShaderLib_GetD3DXEffectCreationFlags();
void NiD3DXEffectShaderLib_SetD3DXEffectCreationFlags(unsigned int uiFlags);

void NiD3DXEffectShaderLib_SetApplicationInstance(HINSTANCE hInstance);

void NiD3DXEffectShaderLib_EnableFXLSupport(bool bEnable);

#if !defined(NID3DXEFFECTSHADER_IMPORT) && !defined(NID3DXEFFECTSHADER_EXPORT)
#include "NiD3DXEffectShaderSDM.h"
static NiD3DXEffectShaderSDM NiD3DXEffectShaderSDMObject;
#endif

#endif  //NID3DXEFFECTSHADERLIB_H
