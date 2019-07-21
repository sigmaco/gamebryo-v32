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
#ifndef EE_D3D11SHADERPROGRAMFACTORY_H
#define EE_D3D11SHADERPROGRAMFACTORY_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11ComputeShader.h>
#include <ecrD3D11Renderer/D3D11DomainShader.h>
#include <ecrD3D11Renderer/D3D11GeometryShader.h>
#include <ecrD3D11Renderer/D3D11HullShader.h>
#include <ecrD3D11Renderer/D3D11Headers.h>
#include <ecrD3D11Renderer/D3D11PixelShader.h>
#include <ecrD3D11Renderer/D3D11VertexShader.h>
#include <efd/MemObject.h>

#include <NiTFixedStringMap.h>
#include <NiTPointerList.h>

namespace ecr
{

class D3D11ShaderProgramCreator;

/**
    Singleton factory class responsible for creating and caching shader programs for the 
    D3D11 renderer.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ShaderProgramFactory : public efd::MemObject
{
public:
    /// @name Construction and Destruction
    //@{
    /// Destructor
    virtual ~D3D11ShaderProgramFactory();
    //@}

    /// Returns an instance of the D3D11ShaderProgramFactory.
    static D3D11ShaderProgramFactory* GetInstance();

    /**
        Create a vertex shader from a file.

        @param pFileName Name of the file to read.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param spVertexShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateVertexShaderFromFile(
        const efd::Char* pFileName,
        const D3D_SHADER_MACRO* pDefines, 
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint, 
        const efd::Char* pShaderTarget,
        efd::UInt32 flags, 
        const efd::Char* pShaderName,
        D3D11VertexShaderPtr& spVertexShader);
    /**
        Create a vertex shader from a memory buffer containing compiled or uncompiled code.

        Even though this shader program does not come from a file, the pFileName parameter is used
        to select the appropriate D3D11ShaderProgramCreator object from the file name's extension.
        The file name can also be used to provide debug shader information.

        @param pShaderCode ID3DBlob containing the shader program code. An ID3DBlob can be created
            using D3D11Renderer::D3D10CreateBlob.
        @param pFileName Name of the shader program file.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param isCompiled Whether or not the code is compiled binary or uncompiled text.
        @param spVertexShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateVertexShaderFromBlob(
        ID3DBlob* pShaderCode,
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName, 
        efd::Bool isCompiled,
        D3D11VertexShaderPtr& spVertexShader);

    /**
        Create a hull shader from a file.

        @param pFileName Name of the file to read.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param spHullShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateHullShaderFromFile(
        const efd::Char* pFileName,
        const D3D_SHADER_MACRO* pDefines, 
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint, 
        const efd::Char* pShaderTarget,
        efd::UInt32 flags, 
        const efd::Char* pShaderName,
        D3D11HullShaderPtr& spHullShader);
    /**
        Create a hull shader from a memory buffer containing compiled or uncompiled code.

        Even though this shader program does not come from a file, the pFileName parameter is used
        to select the appropriate D3D11ShaderProgramCreator object from the file name's extension.
        The file name can also be used to provide debug shader information.

        @param pShaderCode ID3DBlob containing the shader program code. An ID3DBlob can be created
            using D3D11Renderer::D3D10CreateBlob.
        @param pFileName Name of the shader program file.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param isCompiled Whether or not the code is compiled binary or uncompiled text.
        @param spHullShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateHullShaderFromBlob(
        ID3DBlob* pShaderCode,
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName, 
        efd::Bool isCompiled,
        D3D11HullShaderPtr& spHullShader);

    /**
        Create a domain shader from a file.

        @param pFileName Name of the file to read.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param spDomainShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateDomainShaderFromFile(
        const efd::Char* pFileName,
        const D3D_SHADER_MACRO* pDefines, 
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint, 
        const efd::Char* pShaderTarget,
        efd::UInt32 flags, 
        const efd::Char* pShaderName,
        D3D11DomainShaderPtr& spDomainShader);
    /**
        Create a domain shader from a memory buffer containing compiled or uncompiled code.

        Even though this shader program does not come from a file, the pFileName parameter is used
        to select the appropriate D3D11ShaderProgramCreator object from the file name's extension.
        The file name can also be used to provide debug shader information.

        @param pShaderCode ID3DBlob containing the shader program code. An ID3DBlob can be created
            using D3D11Renderer::D3D10CreateBlob.
        @param pFileName Name of the shader program file.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param isCompiled Whether or not the code is compiled binary or uncompiled text.
        @param spDomainShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateDomainShaderFromBlob(
        ID3DBlob* pShaderCode,
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName, 
        efd::Bool isCompiled,
        D3D11DomainShaderPtr& spDomainShader);

    /**
        Create a geometry shader from a file.

        @param pFileName Name of the file to read.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param spGeometryShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateGeometryShaderFromFile(
        const efd::Char* pFileName,
        const D3D_SHADER_MACRO* pDefines, 
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint, 
        const efd::Char* pShaderTarget,
        efd::UInt32 flags, 
        const efd::Char* pShaderName,
        D3D11GeometryShaderPtr& spGeometryShader);
    /**
        Create a geometry shader from a memory buffer containing compiled or uncompiled code.

        Even though this shader program does not come from a file, the pFileName parameter is used
        to select the appropriate D3D11ShaderProgramCreator object from the file name's extension.
        The file name can also be used to provide debug shader information.

        @param pShaderCode ID3DBlob containing the shader program code. An ID3DBlob can be created
            using D3D11Renderer::D3D10CreateBlob.
        @param pFileName Name of the shader program file.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param isCompiled Whether or not the code is compiled binary or uncompiled text.
        @param spGeometryShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateGeometryShaderFromBlob(
        ID3DBlob* pShaderCode,
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName, 
        efd::Bool isCompiled,
        D3D11GeometryShaderPtr& spGeometryShader);

    /**
        Create a geometry shader with stream output from a file.

        @param pFileName Name of the file to read.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param pSODeclaration Array of D3D11_SO_DECLARATION_ENTRY describing the shader output 
            buffers.
        @param numEntries Number of entries in pSODeclaration.
        @param outputStreamStrideArray Array of strides for each output stream.
        @param numOutputStreams Number of output streams.
        @param rasterizedStream ID of output stream to be passed to the rasterizer, or 
            D3D11_SO_NO_RASTERIZED_STREAM if no stream is to be rasterized.
        @param spGeometryShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateGeometryShaderWithStreamOutputFromFile(
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude, 
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName,
        const D3D11_SO_DECLARATION_ENTRY* pSODeclaration,
        efd::UInt32 numEntries, 
        efd::UInt32* outputStreamStrideArray,
        efd::UInt32 numOutputStreams,
        efd::UInt32 rasterizedStream,
        D3D11GeometryShaderPtr& spGeometryShader);
    /**
        Create a geometry shader with stream output from a memory buffer containing compiled or 
        uncompiled code.

        Even though this shader program does not come from a file, the pFileName parameter is used
        to select the appropriate D3D11ShaderProgramCreator object from the file name's extension.
        The file name can also be used to provide debug shader information.

        @param pShaderCode ID3DBlob containing the shader program code. An ID3DBlob can be created
            using D3D11Renderer::D3D10CreateBlob.
        @param pFileName Name of the shader program file.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param pSODeclaration Array of D3D11_SO_DECLARATION_ENTRY describing the shader output 
            buffers.
        @param numEntries Number of entries in pSODeclaration.
        @param outputStreamStrideArray Array of strides for each output stream.
        @param numOutputStreams Number of output streams.
        @param rasterizedStream ID of output stream to be passed to the rasterizer, or 
            D3D11_SO_NO_RASTERIZED_STREAM if no stream is to be rasterized.
        @param isCompiled Whether or not the code is compiled binary or uncompiled text.
        @param spGeometryShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateGeometryShaderWithStreamOutputFromBlob(
        ID3DBlob* pShaderCode, 
        const efd::Char* pFileName,
        const D3D_SHADER_MACRO* pDefines, 
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint, 
        const efd::Char* pShaderTarget,
        efd::UInt32 flags, 
        const efd::Char* pShaderName,
        const D3D11_SO_DECLARATION_ENTRY* pSODeclaration,
        efd::UInt32 numEntries, 
        efd::UInt32* outputStreamStrideArray,
        efd::UInt32 numOutputStreams,
        efd::UInt32 rasterizedStream,
        efd::Bool isCompiled,
        D3D11GeometryShaderPtr& spGeometryShader);

    /**
        Create a pixel shader from a file.

        @param pFileName Name of the file to read.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param spPixelShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreatePixelShaderFromFile(
        const efd::Char* pFileName,
        const D3D_SHADER_MACRO* pDefines, 
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint, 
        const efd::Char* pShaderTarget,
        efd::UInt32 flags, 
        const efd::Char* pShaderName,
        D3D11PixelShaderPtr& spPixelShader);
    /**
        Create a pixel shader from a memory buffer containing compiled or uncompiled code.

        Even though this shader program does not come from a file, the pFileName parameter is used
        to select the appropriate D3D11ShaderProgramCreator object from the file name's extension.
        The file name can also be used to provide debug shader information.

        @param pShaderCode ID3DBlob containing the shader program code. An ID3DBlob can be created
            using D3D11Renderer::D3D10CreateBlob.
        @param pFileName Name of the shader program file.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param isCompiled Whether or not the code is compiled binary or uncompiled text.
        @param spPixelShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreatePixelShaderFromBlob(
        ID3DBlob* pShaderCode,
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName, 
        efd::Bool isCompiled,
        D3D11PixelShaderPtr& spPixelShader);

    /**
        Create a compute shader from a file.

        @param pFileName Name of the file to read.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find include files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param spComputeShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateComputeShaderFromFile(
        const efd::Char* pFileName,
        const D3D_SHADER_MACRO* pDefines, 
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint, 
        const efd::Char* pShaderTarget,
        efd::UInt32 flags, 
        const efd::Char* pShaderName,
        D3D11ComputeShaderPtr& spComputeShader);
    /**
        Create a pixel shader from a memory buffer containing compiled or uncompiled code.

        Even though this shader program does not come from a file, the pFileName parameter is used
        to select the appropriate D3D11ShaderProgramCreator object from the file name's extension.
        The file name can also be used to provide debug shader information.

        @param pShaderCode ID3DBlob containing the shader program code. An ID3DBlob can be created
            using D3D11Renderer::D3D10CreateBlob.
        @param pFileName Name of the shader program file.
        @param pDefines Set of D3D_SHADER_MACRO structures to use when compiling the shader program.
        @param pInclude ID3D11Include-derived object to use to find included files when compiling 
            the shader program.
        @param pEntryPoint Entry point of the shader program to compile.
        @param pShaderTarget Shader target to use when compiling the shader program.
        @param flags Flags to use when compiling the shader program.
        @param pShaderName Name of the shader program, used to register the shader program with the
            shader program factory.
        @param isCompiled Whether or not the code is compiled binary or uncompiled text.
        @param spComputeShader Outputs the resulting shader program.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool CreateComputeShaderFromBlob(
        ID3DBlob* pShaderCode,
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude,
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName, 
        efd::Bool isCompiled,
        D3D11ComputeShaderPtr& spComputeShader);

    /// Return flags to be ORed with incoming flags when compiling all shader programs.
    static efd::UInt32 GetUniversalShaderCreationFlags();
    /// Set flags to be ORed with incoming flags when compiling all shader programs.
    static void SetUniversalShaderCreationFlags(efd::UInt32 flags);

    /// Return the first directory to be searched for shader program files.
    const efd::Char* GetFirstProgramDirectory(NiTListIterator& iter);
    /// Return the next directory to be searched for shader program files.
    const efd::Char* GetNextProgramDirectory(NiTListIterator& iter);
    /// Add a directory to be searched for shader program files.
    void AddProgramDirectory(const efd::Char* pDirectory);
    /// Remove a directory to be searched for shader program files.
    void RemoveProgramDirectory(const efd::Char* pDirectory);
    /// Remove all directories to be searched for shader program files.
    void RemoveAllProgramDirectories();

    /**
        Register a new shader program creator with the shader program factory.

        Shader program creators are registered by file extension - when compiling a new shader
        program, the file name is searched for the file extension to determine which shader
        program creator to use. A single shader program creator can be registered with multiple
        extensions if desired.

        This can also be used to override an existing registration.

        @param pExt File extension to associate with this shader program creator.
        @param pCreator Shader program creator to register
        @return Whether the registration was successful.
    */ 
    static efd::Bool RegisterShaderCreator(
        const efd::Char* pExt, 
        D3D11ShaderProgramCreator* pCreator);
    /// Unregister a shader program creator from all extensions it has been registered with.
    static void UnregisterShaderCreator(D3D11ShaderProgramCreator* pCreator);
    /// Return the shader program creator for a given filename.
    static D3D11ShaderProgramCreator* GetShaderCreator(const efd::Char* pFilename);

    /// @cond EMERGENT_INTERNAL

    //@{
    /// Recreate a shader program.
    static efd::Bool RecreateVertexShader(D3D11VertexShader* pShader);
    static efd::Bool RecreateHullShader(D3D11HullShader* pShader);
    static efd::Bool RecreateDomainShader(D3D11DomainShader* pShader);
    static efd::Bool RecreateGeometryShader(D3D11GeometryShader* pShader);
    static efd::Bool RecreatePixelShader(D3D11PixelShader* pShader);
    static efd::Bool RecreateComputeShader(D3D11ComputeShader* pShader);
    //@}

    //@{
    /// Release a shader program.
    static void ReleaseVertexShader(D3D11VertexShader* pShader);
    static void ReleaseHullShader(D3D11HullShader* pShader);
    static void ReleaseDomainShader(D3D11DomainShader* pShader);
    static void ReleaseGeometryShader(D3D11GeometryShader* pShader);
    static void ReleasePixelShader(D3D11PixelShader* pShader);
    static void ReleaseComputeShader(D3D11ComputeShader* pShader);
    //@}

    //@{
    /// Return an already-registered shader program, if it exists.
    D3D11VertexShader* GetVertexShader(const efd::FixedString& shaderName);
    D3D11HullShader* GetHullShader(const efd::FixedString& shaderName);
    D3D11DomainShader* GetDomainShader(const efd::FixedString& shaderName);
    D3D11GeometryShader* GetGeometryShader(const efd::FixedString& shaderName);
    D3D11PixelShader* GetPixelShader(const efd::FixedString& shaderName);
    D3D11ComputeShader* GetComputeShader(const efd::FixedString& shaderName);
    //@}

    //@{
    /// Register or unregister a shader program with the factory.
    void InsertVertexShaderIntoMap(D3D11VertexShader* pShader);
    inline void RemoveVertexShaderFromMap(efd::FixedString& shaderName);
    void InsertHullShaderIntoMap(D3D11HullShader* pShader);
    inline void RemoveHullShaderFromMap(efd::FixedString& shaderName);
    void InsertDomainShaderIntoMap(D3D11DomainShader* pShader);
    inline void RemoveDomainShaderFromMap(efd::FixedString& shaderName);
    void InsertGeometryShaderIntoMap(D3D11GeometryShader* pShader);
    inline void RemoveGeometryShaderFromMap(efd::FixedString& shaderName);
    void InsertPixelShaderIntoMap(D3D11PixelShader* pShader);
    inline void RemovePixelShaderFromMap(efd::FixedString& shaderName);
    void InsertComputeShaderIntoMap(D3D11ComputeShader* pShader);
    inline void RemoveComputeShaderFromMap(efd::FixedString& shaderName);
    //@}

    /// Search the shader program directories for the file name, and return the full path
    /// and whether or not the file was found.
    static efd::Bool D3D11ShaderProgramFactory::ResolveShaderFileName(
        const efd::FixedString& originalName, 
        efd::FixedString& trueName);

    /// Create the static singleton instance of this class.
    static void _SDMInit();
    /// Release the static singleton instance of this class.
    static void _SDMShutdown();

    /// @endcond

protected:
    /// Hidden constructor.
    D3D11ShaderProgramFactory();

    /// Read a shader program file into an ID3DBlob.
    static ID3DBlob* ReadShaderFile(const efd::FixedString& fileName);

    // We are only allowing one directory at this stage
    NiTPointerList<efd::Char*> m_programDirectories;

    // Maps for shader program names to shaders.
    NiTFixedStringMap<D3D11VertexShader*> m_vertexShaderMap;
    NiTFixedStringMap<D3D11HullShader*> m_hullShaderMap;
    NiTFixedStringMap<D3D11DomainShader*> m_domainShaderMap;
    NiTFixedStringMap<D3D11GeometryShader*> m_geometryShaderMap;
    NiTFixedStringMap<D3D11PixelShader*> m_pixelShaderMap;
    NiTFixedStringMap<D3D11ComputeShader*> m_computeShaderMap;

    NiTFixedStringMap<D3D11ShaderProgramCreator*> m_shaderCreators;

    static D3D11ShaderProgramFactory* ms_pFactory;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the 
/// D3D11ShaderProgramFactory class.
typedef efd::SmartPointer<D3D11ShaderProgramFactory> D3D11ShaderProgramFactoryPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11ShaderProgramFactory.inl>

#endif // EE_D3D11SHADERPROGRAMFACTORY_H
