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
#ifndef EE_D3D11SHADERPROGRAMCREATORHLSL_H
#define EE_D3D11SHADERPROGRAMCREATORHLSL_H

#include <ecrD3D11Renderer/D3D11ShaderProgramCreator.h>

namespace ecr
{

/**
    D3D11ShaderProgramCreator-derived class that generates D3D11ShaderProgram objects from code 
    written in D3D11 HLSL, stored either in a file or in a buffer in memory.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ShaderProgramCreatorHLSL :
    public D3D11ShaderProgramCreator
{
public:
    /// @name Construction and Destruction
    //@{
    /// Destructor
    virtual ~D3D11ShaderProgramCreatorHLSL();
    //@}

    /// @cond EMERGENT_INTERNAL

    // Overridden virtual functions inherit base documentation and thus
    // are not documented here.
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
        D3D11VertexShaderPtr& spVertexShader);
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
        D3D11HullShaderPtr& spHullShader);
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
        D3D11DomainShaderPtr& spDomainShader);
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
        D3D11GeometryShaderPtr& spGeometryShader);
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
        D3D11PixelShaderPtr& spPixelShader);
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
        D3D11ComputeShaderPtr& spComputeShader);

    // Overridden virtual functions inherit base documentation and thus
    // are not documented here.
    virtual efd::Bool RecreateVertexShader(D3D11VertexShader* pShader);
    virtual efd::Bool RecreateHullShader(D3D11HullShader* pShader);
    virtual efd::Bool RecreateDomainShader(D3D11DomainShader* pShader);
    virtual efd::Bool RecreateGeometryShader(D3D11GeometryShader* pShader);
    virtual efd::Bool RecreatePixelShader(D3D11PixelShader* pShader);
    virtual efd::Bool RecreateComputeShader(D3D11ComputeShader* pShader);

    /// Create the static singleton instance of this class.
    static void _SDMInit();
    /// Release the static singleton instance of this class.
    static void _SDMShutdown();

    /// Return the static singleton instance of this class.
    static D3D11ShaderProgramCreatorHLSL* GetInstance();

    /// Unregister this class with the D3D11ShaderProgramFactory.
    static void Shutdown();

    /// @endcond

protected:
    /// Hidden constructor.
    D3D11ShaderProgramCreatorHLSL();

    static D3D11ShaderProgramCreatorHLSL* ms_pCreator;
};

}   // End namespace ecr.

#endif // EE_D3D11SHADERPROGRAMCREATORHLSL_H
