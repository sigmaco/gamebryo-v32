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
#ifndef EE_D3D11SHADERPROGRAMCREATOR_H
#define EE_D3D11SHADERPROGRAMCREATOR_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11ComputeShader.h>
#include <ecrD3D11Renderer/D3D11DomainShader.h>
#include <ecrD3D11Renderer/D3D11GeometryShader.h>
#include <ecrD3D11Renderer/D3D11HullShader.h>
#include <ecrD3D11Renderer/D3D11Headers.h>
#include <ecrD3D11Renderer/D3D11PixelShader.h>
#include <ecrD3D11Renderer/D3D11VertexShader.h>
#include <efd/MemObject.h>

namespace ecr
{

/**
    Base for classes that are able to generate D3D11ShaderProgram objects, usually by reading 
    in files that contain the shader in some format. This is the mechanism that Gamebryo uses to 
    support a variety of shader program formats.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ShaderProgramCreator : public efd::MemObject
{
public:
    /// @name Construction and Destruction
    //@{
    /// Destructor
    virtual ~D3D11ShaderProgramCreator();
    //@}

    /// @cond EMERGENT_INTERNAL

    
    /**
        Create a vertex shader from a compiled or uncompiled blob.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
    virtual efd::Bool CreateVertexShader(
        ID3DBlob* pShaderCode,
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude, 
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName, 
        efd::Bool isCompiled,
        D3D11VertexShaderPtr& spVertexShader) = 0;
    /**
        Create a hull shader from a compiled or uncompiled blob.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
    virtual efd::Bool CreateHullShader(
        ID3DBlob* pShaderCode,
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude, 
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName, 
        efd::Bool isCompiled,
        D3D11HullShaderPtr& spHullShader) = 0;
    /**
        Create a domain shader from a compiled or uncompiled blob.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
    virtual efd::Bool CreateDomainShader(
        ID3DBlob* pShaderCode,
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude, 
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName, 
        efd::Bool isCompiled,
        D3D11DomainShaderPtr& spDomainShader) = 0;
    /**
        Create a geometry shader from a compiled or uncompiled blob.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
   virtual efd::Bool CreateGeometryShader(
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
        D3D11GeometryShaderPtr& spGeometryShader) = 0;
    /**
        Create a pixel shader from a compiled or uncompiled blob.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
    virtual efd::Bool CreatePixelShader(
        ID3DBlob* pShaderCode,
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude, 
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName, 
        efd::Bool isCompiled,
        D3D11PixelShaderPtr& spPixelShader) = 0;
    /**
        Create a compute shader from a compiled or uncompiled blob.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
    virtual efd::Bool CreateComputeShader(
        ID3DBlob* pShaderCode,
        const efd::Char* pFileName, 
        const D3D_SHADER_MACRO* pDefines,
        ID3DInclude* pInclude, 
        const efd::Char* pEntryPoint,
        const efd::Char* pShaderTarget, 
        efd::UInt32 flags,
        const efd::Char* pShaderName, 
        efd::Bool isCompiled,
        D3D11ComputeShaderPtr& spComputeShader) = 0;

    /**
        Recreate a vertex shader.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
    virtual efd::Bool RecreateVertexShader(D3D11VertexShader* pShader) = 0;
    /**
        Recreate a hull shader.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
    virtual efd::Bool RecreateHullShader(D3D11HullShader* pShader) = 0;
    /**
        Recreate a domain shader.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
    virtual efd::Bool RecreateDomainShader(D3D11DomainShader* pShader) = 0;
    /**
        Recreate a geometry shader.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
    virtual efd::Bool RecreateGeometryShader(D3D11GeometryShader* pShader) = 0;
    /**
        Recreate a pixel shader.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
    virtual efd::Bool RecreatePixelShader(D3D11PixelShader* pShader) = 0;
    /**
        Recreate a compute shader.

        This function should never be called directly; only from the D3D11ShaderProgramFactory.
    */
    virtual efd::Bool RecreateComputeShader(D3D11ComputeShader* pShader) = 0;

    /// @endcond

protected:
    /// Hidden constructor
    D3D11ShaderProgramCreator();
};

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11ShaderProgramCreator.inl>

#endif  // EE_D3D11SHADERPROGRAMCREATOR_H
