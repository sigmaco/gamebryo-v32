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
#ifndef EE_D3D11BINARYSHADERLIB_H
#define EE_D3D11BINARYSHADERLIB_H

#include <ecrD3D11BinaryShaderLib/ecrD3D11BinaryShaderLibLibType.h>

class NiRenderer;
class NiShaderLibrary;

namespace ecr
{

/**
    Load a D3D11BinaryShaderLibrary.

    This function is provided for static-lib-based builds of applications to create a 
    D3D11BinaryShaderLibrary. The function simply creates an instance of the 
    D3D11BinaryShaderLibrary, searches the specified directories for NSB files, and returns the
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
efd::Bool D3D11BinaryShaderLib_LoadShaderLibrary(
    NiRenderer* pRenderer,
    efd::SInt32 directoryCount, 
    const efd::Char* ppDirectories[], 
    efd::Bool recurseSubFolders,
    NiShaderLibrary** ppLibrary);

}   // End namespace ecr.

#if !defined(EE_ECRD3D11BINARYSHADERLIB_IMPORT) && !defined(EE_ECRD3D11BINARYSHADERLIB_EXPORT)
#include <ecrD3D11BinaryShaderLib/ecrD3D11BinaryShaderLibSDM.h>
static ecr::ecrD3D11BinaryShaderLibSDM ecrD3D11BinaryShaderLibSDMObject;
#endif

#endif // EE_D3D11BINARYSHADERLIB_H
