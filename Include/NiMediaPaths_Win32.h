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
#ifndef NIMEDIAPATHS_WIN32_H
#define NIMEDIAPATHS_WIN32_H

#include <NiMainLibType.h>
#include <NiString.h>

namespace NiMediaPaths_Win32
{
    // Places "%EMERGENT_PATH% into pBuffer
    // (returns false if the buffer was too small or the variable was missing)
    NIMAIN_ENTRY bool GetEmergentPath(char* pBuffer, size_t bufferSize);

    // Concatenates "\Media\Shaders\Data" onto pBuffer
    NIMAIN_ENTRY void AppendShaderPath(char* pBuffer, size_t bufferSize);
    NIMAIN_ENTRY bool FetchAbsoluteShaderPath(NiString& outAbsoluteShaderPath);

    // Concatenates "SDK\Win32\DLL\ShaderLibs" onto pBuffer
    NIMAIN_ENTRY void AppendShaderLibPath(char* pBuffer, size_t bufferSize);
    NIMAIN_ENTRY bool FetchAbsoluteShaderLibPath(NiString& outAbsoluteShaderLibPath);

    // Concatenates "\Media\Shaders\Data\Textures" onto pBuffer
    NIMAIN_ENTRY void AppendShaderDefaultTexturePath(char* pBuffer, size_t bufferSize);
    NIMAIN_ENTRY bool FetchAbsoluteShaderDefaultTexturePath(NiString& outAbsoluteTexturePath);

    // Concatenates "\Media\ToolPluginData\MeshProfiles" onto pBuffer
    NIMAIN_ENTRY void AppendMeshProfilePath(char* pBuffer, size_t bufferSize);

    // Concatenates "\SDK\Win32\DLL\ToolPlugins" onto pBuffer
    NIMAIN_ENTRY void AppendToolPluginsPath(char* pBuffer, size_t bufferSize);
}

#endif
