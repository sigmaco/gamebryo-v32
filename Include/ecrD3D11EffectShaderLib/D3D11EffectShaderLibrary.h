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
#ifndef EE_D3D11EFFECTSHADERLIBRARY_H
#define EE_D3D11EFFECTSHADERLIBRARY_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>
#include <ecrD3D11Renderer/D3D11ShaderLibrary.h>
#include <NiTPointerList.h>
#include <NiTFixedStringMap.h>

namespace ecr
{

class D3D11EffectFile;
class D3D11EffectTechniqueSet;

/**
    D3D11EffectShaderLibrary is the D3D11-specific shader library that manages FX shaders.

    The library will create D3D11EffectShader objects for shaders found loaded from FX files
    through the Effects11 framework.

    Applications that link in D3D11EffectShaderLibrary using static libraries should use the
    function D3D11EffectShaderLib_LoadShaderLibrary, found in D3D11EffectShaderLib.h.

    For information on how applications can use the library, refer to the documentation on
    "Linking and using the NiD3DXEffectShaderLib" and "Using the NiD3D10EffectShaderLib and 
    ecrD3D11EffectShaderLib" for D3D10 and D3D11-specific addenda.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectShaderLibrary :
    public ecr::D3D11ShaderLibrary
{
protected:

public:
    /// @name Construction and Destruction
    //@{
    /// Destructor.
    virtual ~D3D11EffectShaderLibrary();
    //@}

    /**
        Create an instance of the D3D11EffectShaderLibrary. 
        
        After the library is created, the function searches for FX files, loads them, and adds
        them to the library's list of available shaders. 

        @param pRenderer Current renderer.
        @param directoryCount Number of directories in the ppDirectories array.
        @param ppDirectories Array of directories to search for shaders.
        @param recurseSubFolders Whether or not to recursively search the directories specified in 
            ppDirectories.
        @return The new library, if creation succeeded, otherwise NULL.
    */
    static D3D11EffectShaderLibrary* Create(
        NiRenderer* pRenderer,
        efd::UInt32 directoryCount, 
        const efd::Char* ppDirectories[],
        efd::Bool recurseSubFolders);

    /// Return a specific shader, creating it it necessary, or return NULL if the shader library 
    /// cannot create a shader with the given name and implementation.
    virtual NiShader* GetShader(
        NiRenderer* pRenderer,
        const efd::Char* pName, 
        efd::UInt32 implementation);
    /// Release the shader library's reference to the given shader, and return whether or not
    /// the shader library had a reference to that shader.
    virtual efd::Bool ReleaseShader(const efd::Char* pName, efd::UInt32 implementation);
    /// Release the shader library's reference to the given shader, and return whether or not
    /// the shader library had a reference to that shader.
    virtual efd::Bool ReleaseShader(NiShader* pShader);

    /// Load an FX shader from the memory buffer, and return whether or not the load was successful.
    bool LoadEffect(void* pBuffer, efd::UInt32 bufferSize, const efd::Char* pEffectFileName);

    /// Return the number of mime types the shader library supports.
    virtual efd::UInt32 GetNumSupportedMimeTypes() const;
    /// Return one of the mime types the shader library supports.
    virtual const efd::Char* GetSupportedMimeType(efd::UInt32 index) const;

    /// Load an FX shader from the indicated file, and return whether or not the load was 
    /// successful.
    virtual efd::Bool LoadShader(const efd::Char* pFile);

    /// @cond EMERGENT_INTERNAL

    /// Add the D3D11EffectFile to the library's list.
    efd::Bool InsertD3D11EffectFileIntoList(D3D11EffectFile* pD3D11EffectFile);
    /// Return the number of D3D11EffectFile objects in the library's list.
    efd::UInt32 GetD3D11EffectFileCount();
    /// Return a specific D3D11EffectFile.
    D3D11EffectFile* GetD3D11EffectFile(const efd::Char* pName);
    /// Load the FX files in the specified directory.
    efd::Bool LoadD3D11EffectFiles(const efd::Char* pDirectory, efd::Bool recurseSubFolders);

    /// Return the temp device.
    ID3D11Device* GetTempDevice() const;
    /// Return the temp device context.
    ID3D11DeviceContext* GetTempDeviceContext() const;

    /// @endcond

protected:
    /// Hidden constructor
    D3D11EffectShaderLibrary();

    /// Set a temp device on the library.
    void SetTempDevice(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
    /// Release the temp device from the library.
    void ReleaseTempDevice();

    NiTPointerList<D3D11EffectFile*> m_effectFileList;
    NiTFixedStringMap<D3D11EffectTechniqueSet*> m_effectTechniqueMap;

    ID3D11Device* m_pTempDevice;
    ID3D11DeviceContext* m_pTempDeviceContext;

    static D3D11EffectShaderLibrary* ms_pLibrary;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the 
/// D3D11EffectShaderLibrary class.
typedef efd::SmartPointer<D3D11EffectShaderLibrary> D3D11EffectShaderLibraryPtr;

}   // End namespace ecr.

#endif // EE_D3D11EFFECTSHADERLIBRARY_H
