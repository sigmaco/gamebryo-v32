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
#ifndef EE_D3D11SHADERFACTORY_H
#define EE_D3D11SHADERFACTORY_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>

#include <efd/ThreadLocal.h>
#include <NiShaderFactory.h>
#include <NiTStringMap.h>

namespace ecr
{

/**
    D3D11 implementation of NiShaderFactory.

    The class is essentially a self-contained singleton used by Gamebryo to attach and detach 
    shaders on NiMesh instances. Applications should, for the majority of cases, only reference 
    the functionality of this class through the base class interfaces.
*/

class EE_ECRD3D11RENDERER_ENTRY D3D11ShaderFactory : public NiShaderFactory
{
protected:
public:
    /// @name Construction and Destruction
    //@{
    /// Destructor
    virtual ~D3D11ShaderFactory();
    //@}

    /**
        Find a shader with the given name and implementation, and create it from a shader library
        if it does not already exist.

        Any shaders created will be automatically stored in the shader factory for future use.

        @param pName Name of the shader
        @param implementation Implementation ID o fthe shader
        @param reportNotFound If true, the function will call ReportError with the 
            NISHADERERR_SHADERNOTFOUND error.
    */
    virtual NiShader* RetrieveShader(
        const efd::Char* pName,
        efd::UInt32 implementation, 
        efd::Bool reportNotFound = true);
    /// Find a shader with the given name and implementation, but do not create it from a shader 
    /// library if it does not already exist.
    virtual NiShader* FindShader(const efd::Char* pName, efd::UInt32 implementation);

    /// Release the specified shader from both the shader factory and the shader library that
    /// first provided the shader, and return whether or not the shader was found.
    virtual efd::Bool ReleaseShaderFromLibrary(const efd::Char* pName, efd::UInt32 implementation);
    /// Release the specified shader from both the shader factory and the shader library that
    /// first provided the shader, and return whether or not the shader was found.
    virtual efd::Bool ReleaseShaderFromLibrary(NiShader* pShader);

    /// Return the major version number from a D3D11 vertex shader version.
    virtual efd::UInt32 GetMajorVertexShaderVersion(const efd::UInt32 version);
    /// Return the minor version number from a D3D11 vertex shader version.
    virtual efd::UInt32 GetMinorVertexShaderVersion(const efd::UInt32 version);
    /// Create a D3D11 vertex shader version from a major and minor version number.
    virtual efd::UInt32 CreateVertexShaderVersion(
        const efd::UInt32 majorVersion, 
        const efd::UInt32 minorVersion);
    /// Return the major version number from a D3D11 hull shader version.
    virtual efd::UInt32 GetMajorHullShaderVersion(const efd::UInt32 version);
    /// Return the minor version number from a D3D11 hull shader version.
    virtual efd::UInt32 GetMinorHullShaderVersion(const efd::UInt32 version);
    /// Create a D3D11 hull shader version from a major and minor version number.
    virtual efd::UInt32 CreateHullShaderVersion(
        const efd::UInt32 majorVersion, 
        const efd::UInt32 minorVersion);
    /// Return the major version number from a D3D11 domain shader version.
    virtual efd::UInt32 GetMajorDomainShaderVersion(const efd::UInt32 version);
    /// Return the minor version number from a D3D11 domain shader version.
    virtual efd::UInt32 GetMinorDomainShaderVersion(const efd::UInt32 version);
    /// Create a D3D11 domain shader version from a major and minor version number.
    virtual efd::UInt32 CreateDomainShaderVersion(
        const efd::UInt32 majorVersion, 
        const efd::UInt32 minorVersion);
    /// Return the major version number from a D3D11 geometry shader version.
    virtual efd::UInt32 GetMajorGeometryShaderVersion(const efd::UInt32 version);
    /// Return the minor version number from a D3D11 geometry shader version.
    virtual efd::UInt32 GetMinorGeometryShaderVersion(const efd::UInt32 version);
    /// Create a D3D11 geometry shader version from a major and minor version number.
    virtual efd::UInt32 CreateGeometryShaderVersion(
        const efd::UInt32 majorVersion, 
        const efd::UInt32 minorVersion);
    /// Return the major version number from a D3D11 pixel shader version.
    virtual efd::UInt32 GetMajorPixelShaderVersion(const efd::UInt32 version);
    /// Return the minor version number from a D3D11 pixel shader version.
    virtual efd::UInt32 GetMinorPixelShaderVersion(const efd::UInt32 version);
    /// Create a D3D11 pixel shader version from a major and minor version number.
    virtual efd::UInt32 CreatePixelShaderVersion(
        const efd::UInt32 majorVersion, 
        const efd::UInt32 minorVersion);
    /// Return the major version number from a D3D11 compute shader version.
    virtual efd::UInt32 GetMajorComputeShaderVersion(const efd::UInt32 version);
    /// Return the minor version number from a D3D11 compute shader version.
    virtual efd::UInt32 GetMinorComputeShaderVersion(const efd::UInt32 version);
    /// Create a D3D11 compute shader version from a major and minor version number.
    virtual efd::UInt32 CreateComputeShaderVersion(
        const efd::UInt32 majorVersion, 
        const efd::UInt32 minorVersion);

    /// Return the D3D11-specific shader factory.
    static D3D11ShaderFactory* GetD3D11ShaderFactory();

    /// @cond EMERGENT_INTERNAL

    /// Store a reference to a new shader.
    virtual void InsertShader(NiShader* pShader, efd::UInt32 uImplementation);
    /// Release the factory's reference to a shader.
    virtual void RemoveShader(const efd::Char* pName, efd::UInt32 uImplementation);
    /// Release the factory's references to all shaders.
    virtual void RemoveAllShaders();

    /// Add a new shader library to the factory's list.
    virtual void InsertLibrary(NiShaderLibrary* pLibrary);
    /// Find a shader library in the factory's list.
    virtual NiShaderLibrary* FindLibrary(const efd::Char* pName);
    /// Remove a shader library from the factory's list.
    virtual void RemoveLibrary(const efd::Char* pName);
    /// Remove all shader libraries from the factory's list.
    virtual void RemoveAllLibraries();
    /// Return the first shader library on the factory's list.
    virtual NiShaderLibrary* GetFirstLibrary();
    /// Return the next shader library on the factory's list.
    virtual NiShaderLibrary* GetNextLibrary();

    /// Release all D3D11 data for all shaders the factory has registered.
    virtual void PurgeAllShaderRendererData();
    /// Recreate all D3D11 data for all shaders the factory has registered.
    virtual void RestoreAllShaderRendererData();

#if defined(_USRDLL)
    /// Release all shader libraries that the factory loaded as DLLs, as well as their shaders
    /// and their DLL handles.
    virtual void FreeLibraryDLLs();
    /// Return the first shader library that the factory loaded as a DLL.
    virtual void* GetFirstLibraryDLL(const efd::Char*& pName);
    /// Return the next shader library that the factory loaded as a DLL.
    virtual void* GetNextLibraryDLL(const efd::Char*& pName);
    /// Release just the DLL handles for all shader libraries that the factory loaded as DLLs.
    /// Use with caution.
    virtual void ClearLibraryDLLs();
#endif
    /// Return whether an NiShader instance represents the default implementation of that shader
    virtual efd::Bool IsDefaultImplementation(NiShader* pShader);

    /// Create and initialize the singleton factory instance during application startup.
    static void _SDMInit();
    /// Release the singleton factory instance during application shutdown.
    static void _SDMShutdown();

    /// Create and initialize the singleton factory instance.
    static NiShaderFactory* Create();
    /// Release the singleton factory instance.
    static void Destroy();

    /// Set the D3D11 shader factory as the active one.
    efd::Bool SetAsActiveFactory();
    /// Return whether the D3D11 shader factory is the active one.
    inline static efd::Bool IsActiveFactory();

    /// Return a string describing which renderer this shader factory manages.
    virtual const efd::Char* GetRendererString() const;

    /// Return the default library class creation callback function.
    virtual NISHADERFACTORY_CLASSCREATIONCALLBACK GetDefaultClassCreateCallback() const;
    /// Return the default parser callback function.
    virtual NISHADERFACTORY_RUNPARSERCALLBACK GetDefaultRunParserCallback() const;
    /// Return the default error callback function.
    virtual NISHADERFACTORY_ERRORCALLBACK GetDefaultErrorCallback() const;

    /// @endcond

protected:
    /// Hidden constructor
    D3D11ShaderFactory();

    /// Get the first shader program directory on the list.
    virtual const efd::Char* GetFirstProgramDirectory(NiTListIterator& iter);
    /// Get the next shader program directory on the list.
    virtual const efd::Char* GetNextProgramDirectory(NiTListIterator& iter);
    /// Add a new shader program directory to the list.
    virtual void AddProgramDirectory(const efd::Char* pDirectory);
    /// Remove a shader program directory from the list.
    virtual void RemoveProgramDirectory(const efd::Char* pDirectory);
    /// Remove all shader program directories from the list.
    virtual void RemoveAllProgramDirectories();

    /// Return the name of the compiler used to build this library.
    static const efd::Char* GetCompilerName(efd::UInt32 version);

    NiTFixedStringMap<NiShader*> m_shaderMap;
    NiTFixedStringMap<NiShaderLibraryPtr> m_libraryMap;
    efd::ThreadLocal<NiTMapIterator> m_libraryIter;

    efd::CriticalSection m_shaderMapLock;

    /// Default Class Creation and RunParser functions for use with DLL builds
    static efd::Bool DefaultCreateClass(
        const efd::Char* pLibName,
        NiRenderer* pRenderer, 
        efd::SInt32 directoryCount,
        const efd::Char* pDirectoryArray[], 
        efd::Bool recurseSubFolders,
        NiShaderLibrary** pLibrary);
    static efd::UInt32 DefaultRunParser(
        const efd::Char* pLibName,
        NiRenderer* pRenderer, 
        const efd::Char* pDirectory,
        efd::Bool recurseSubFolders);

#if defined(_USRDLL)
    efd::ThreadLocal<NiTMapIterator> m_libraryDLLIter;
    NiTStringMap<HMODULE> m_loadedShaderLibDLLs;
#endif //#if defined(_usrdll)

    static D3D11ShaderFactory* ms_pD3D11ShaderFactory;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the 
/// D3D11ShaderFactory class.
typedef efd::SmartPointer<D3D11ShaderFactory> D3D11ShaderFactoryPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11ShaderFactory.inl>

#endif // EE_D3D11SHADERFACTORY_H

