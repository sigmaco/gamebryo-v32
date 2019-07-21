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
#ifndef EE_D3D11EFFECTLOADER_H
#define EE_D3D11EFFECTLOADER_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>

#include <NiMain.h>

class NiShaderLibraryDesc;

namespace ecr
{

class D3D11EffectShaderLibrary;

/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectLoader is an internal class for managing Gamebryo's Effects11 implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectLoader : public NiMemObject
{
protected:
    D3D11EffectLoader();
    ~D3D11EffectLoader();

public:
    static D3D11EffectLoader* GetInstance(efd::Bool createNew = true);
    static void Destroy();

    efd::Bool LoadAllD3D11EffectFiles(
        D3D11EffectShaderLibrary* pLibrary,
        const efd::Char* pDirectory,
        efd::Bool recurseDirectories);

    efd::Bool LoadEffect(
        D3D11EffectShaderLibrary* pLibrary,
        void* pBuffer,
        efd::UInt32 bufferSize,
        efd::Bool isCompiled,
        const efd::Char* pEffectFileName);

    void AddFileExtension(const efd::Char* pExtension, efd::Bool isCompiled);
    void RemoveFileExtension(const efd::Char* pExtension);
    efd::Bool HasCompiledExtension(const efd::Char* pFileName) const;

    // *** end Emergent internal use only ***
    static efd::Char* GetShaderText(const efd::Char* pchaderName, efd::UInt32& shaderLength);
    // *** begin Emergent internal use only ***

protected:
    efd::UInt32 GetD3D11EffectFileCount() const;
    const efd::Char* GetFirstD3D11EffectFile(NiTListIterator& iter) const;
    const efd::Char* GetNextD3D11EffectFile(NiTListIterator& iter) const;

    void FindAllD3D11EffectFiles(const efd::Char* pcDirectory, efd::Bool recurseDirectories);
    efd::UInt32 FindAllD3D11EffectFilesInDirectory(
        const efd::Char* pDirectory,
        const efd::FixedString& ext,
        efd::Bool recurseDirectories,
        NiTPointerList<efd::FixedString>* pFileList);

    efd::Bool ProcessD3D11EffectFile(
        const efd::Char* pFilename,
        const efd::FixedString& ext,
        NiTPointerList<efd::FixedString>* pFileList);

    efd::Bool LoadStoredD3D11EffectFiles(D3D11EffectShaderLibrary* pLibrary);

    static efd::FixedString StandardizeExtension(const efd::Char* pFilename);

    static D3D11EffectLoader* ms_pLoader;

    NiTPointerList<efd::FixedString> m_effectList;

    NiTFixedStringMap<efd::Bool> m_shaderFileExtensions;
};

/// @endcond

}   // End namespace ecr.

#endif // EE_D3D11EFFECTLOADER_H
