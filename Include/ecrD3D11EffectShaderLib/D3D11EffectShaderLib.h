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
#ifndef EE_D3D11EFFECTSHADERLIB_H
#define EE_D3D11EFFECTSHADERLIB_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>

class NiRenderer;
class NiShaderLibrary;

namespace ecr
{
/**
    @class D3D11EffectShaderLib
*/
/**
    Load a D3D11EffectShaderLibrary.

    This function is provided for static-lib-based builds of applications to create a 
    D3D11EffectShaderLibrary. The function simply creates an instance of the 
    D3D11EffectShaderLibrary, searches the specified directories for FX files, and returns the
    new shader library. 

    Refer to the documentation on Exposing your ShaderLibrary to the tool-chain for more details

    @param pRenderer Current renderer.
    @param directoryCount Number of directories in the ppDirectories array.
    @param ppDirectories Array of directories to search for shaders.
    @param recurseSubFolders Whether or not to recursively search the directories specified in 
        ppDirectories.
    @param ppLibrary Outputs the new shader library.
    @return Whether or not the shader library creation succeeded.
*/
efd::Bool D3D11EffectShaderLib_LoadShaderLibrary(
    NiRenderer* pRenderer,
    efd::SInt32 directoryCount, 
    const efd::Char* ppDirectories[], 
    efd::Bool recurseSubFolders,
    NiShaderLibrary** ppLibrary);

/// Return the HLSL flags to use when compiling the FX shader.
efd::UInt32 D3D11EffectShaderLib_GetD3D11EffectHLSLFlags();
/// Set the HLSL flags to use when compiling the FX shader.
void D3D11EffectShaderLib_SetD3D11EffectHLSLFlags(efd::UInt32 hlslFlags);

/// Return the Effect flags to use when compiling the FX shader.
efd::UInt32 D3D11EffectShaderLib_GetD3D11EffectFXFlags();
/// Set the Effect flags to use when compiling the FX shader.
void D3D11EffectShaderLib_SetD3D11EffectFXFlags(efd::UInt32 fxFlags);

/// Add a new file extension to be loaded by the D3D11EffectShaderLibrary, and indicate whether
/// that file extension represents compiled binary shader code or uncompiled text shader code.
void D3D11EffectShaderLib_AddFileExtension(const efd::Char* pExtension, efd::Bool isCompiled);
/// Remove a file extension from the D3D11EffectShaderLibrary.
void D3D11EffectShaderLib_RemoveFileExtension(const efd::Char* pExtension);

}   // End namespace ecr.

#if !defined(EE_ECRD3D11EFFECTSHADER_IMPORT) && !defined(EE_ECRD3D11EFFECTSHADER_EXPORT)
#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibSDM.h>
static ecr::ecrD3D11EffectShaderLibSDM ecrD3D11EffectShaderLibSDMObject;
#endif

#endif // EE_D3D11EFFECTSHADERLIB_H
