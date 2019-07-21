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
#ifndef EE_D3D11GPUPROGRAMCACHE_H
#define EE_D3D11GPUPROGRAMCACHE_H

#include <ecrD3D11Renderer/D3D11ShaderProgram.h>

#include <NiGPUProgramCache.h>

namespace ecr
{

/**
    D3D11-specific implementation of NiGPUProgramCache.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11GPUProgramCache : public NiGPUProgramCache
{
public:
    /// @name Construction and Destruction
    //@{
    /**
        Constructor that creates a new program cache.
        
        @param version Version ID of the cache, used to ensure backwards compatibility when loading
            existing cache files.
        @param pWorkingDir Working directory for the shader cache file
        @param shaderType The type of shader program this cache will manage.
        @param shaderProfile Shader profile used to compile the shader programs.
        @param pMaterialIdentifier A unique name that identifies the NiMaterial that this 
            cache will manage.
        @param autoWriteToDisk If true, the cache will automatically write its compiled shaders 
            into the cache file on disk after they are compiled.
        @param writeDebugHLSLFile If true, then an additional .hlsl file will be written to 
            disk each time a shader program is generated, and that file can be used to debug the 
            shader program.
        @param isLocked If true, the cache will not compile new programs, but will provide programs 
            already in the cache file.
        @param loadShaders If true, then the cache will attempt to load any cache file at the file 
            location that it would ordinarily write its cache to, and add the loaded shaders to 
            its own cache.
    */
    D3D11GPUProgramCache(
        efd::UInt32 version, 
        const efd::Char* pWorkingDir,
        NiGPUProgram::ProgramType shaderType, 
        const efd::FixedString& shaderProfile,
        const efd::Char* pMaterialIdentifier, 
        efd::Bool autoWriteToDisk,
        efd::Bool writeDebugHLSLFile, 
        efd::Bool isLocked, 
        efd::Bool loadShaders);
    //@}

    /**
        This method compiles the input text into a shader program. 
        
        If the D3D11GPUProgramCache was created with autoWriteToDisk set to true, the cache
        will automatically write the compiled program and variables to the cache file.
        
        @param pName The name of the shader program.
        @param pProgramText The text of the shader program.
        @param uniformResources Outputs the uniform variables used by the program 
        @return The compiled shader program.
    */
    virtual NiGPUProgram* GenerateProgram(
        const efd::Char* pName,
        const efd::Char* pProgramText,
        NiTObjectPtrSet<NiMaterialResourcePtr>& uniformResources);

    /// Returns "hlsl", indicating the shader language this shader program cache expects.
    virtual const efd::Char* GetPlatformSpecificCodeID() const;
    /// Returns "D3D11", identifying this platform.
    virtual const efd::Char* GetPlatform() const;

protected:
    /// Write a shader program to the cache file
    virtual efd::Bool SaveGPUProgram(efd::BinaryStream& stream, NiGPUProgram* pProgram);

    /// Load a shader program from the cache file
    virtual efd::Bool LoadGPUProgram(
        efd::BinaryStream& stream, 
        const NiFixedString& shaderName, 
        NiGPUProgramPtr& spProgram, 
        efd::Bool skip);

    /// Write out the .hlsl version of the shader program.
    virtual efd::Bool SaveDebugHLSLFile(
        const efd::Char* pFilename,
        const efd::Char* pProgramText);

    NiGPUProgram::ProgramType m_shaderType;
    efd::Bool m_writeDebugHLSLFile;
    efd::FixedString m_materialIdentifier;
};

}   // End namespace ecr.

#endif // EE_D3D11GPUPROGRAMCACHE_H
