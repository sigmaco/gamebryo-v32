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
#ifndef D3D11SHADERLIBRARYVERSION_H
#define D3D11SHADERLIBRARYVERSION_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11ShaderFactory.h>

namespace ecr
{

/**
    Container for the versioning information to use within the shader system.

    The class is accessed through the Shader version information functions of the 
    D3D11 renderer, through the functions described below.

    The system version of compute shaders and the feature level will be set automatically 
    by the renderer at creation time. If an application is utilizing the user-defined versions 
    in their shader system, it should set the system user-defined version immediately after 
    creation of the renderer.

    D3D11ShaderLibrary-derived classes should use this class to determine the shader versioning 
    information for the current run of their application.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ShaderLibraryVersion : public efd::MemObject
{
public:
    /// @name Construction and Destruction
    //@{
    D3D11ShaderLibraryVersion();
    //@}

    /** 
        Set the system feature level to the given value.
        
        Values should come from the D3D_FEATURE_LEVEL enumeration.
        The renderer should be the only one to make this call and it should be set to the 
        maximum feature level supported by the hardware.
    */
    inline void SetSystemFeatureLevel(efd::UInt32 featureLevel);
    /** 
        Set the minimum feature level the system should allow to the given value.
        
        Values should come from the D3D_FEATURE_LEVEL enumeration.
    */
    inline void SetMinFeatureLevel(efd::UInt32 featureLevel);
    /** 
        Set the requested feature level the system should use to the given value.
        
        Values should come from the D3D_FEATURE_LEVEL enumeration.
    */
    inline void SetFeatureLevelRequest(efd::UInt32 featureLevel);

    /** 
        Set the system compute shader version to the given value.
        
        Values should be formed using D3D11ShaderFactory::CreateComputeShaderVersion.
        The renderer should be the only one to make this call and it should be set to the 
        maximum compute shader version supported by the hardware.
    */
    inline void SetSystemComputeShaderVersion(efd::UInt32 version);
    /** 
        Set the minimum compute shader version the system should allow to the given value.
        
        Values should be formed using D3D11ShaderFactory::CreateComputeShaderVersion.
    */
    inline void SetMinComputeShaderVersion(efd::UInt32 version);
    /** 
        Set the requested compute shader version the system should use to the given value.
        
        Values should be formed using D3D11ShaderFactory::CreateComputeShaderVersion.
    */
    inline void SetComputeShaderVersionRequest(efd::UInt32 version);
    /** 
        Set the system compute shader version to the given major/minor values.
        
        The renderer should be the only one to make this call and it should be set to the 
        maximum compute shader version supported by the hardware.
    */
    inline void SetSystemComputeShaderVersion(efd::UInt32 major, efd::UInt32 minor);
    /** 
        Set the minimum compute shader version the system should allow to the given 
        major/minor values.
    */
    inline void SetMinComputeShaderVersion(efd::UInt32 major, efd::UInt32 minor);
    /** 
        Set the requested compute shader version the system should use to the given 
        major/minor values.
    */
    inline void SetComputeShaderVersionRequest(efd::UInt32 major, efd::UInt32 minor);

    /** 
        Set the system user-defined shader version to the given value.
        
        Values should be formed using D3D11ShaderFactory::CreateVertexShaderVersion.
        If the application uses the user-defined value as part of their shader system, 
        this value should be set immediately after creating the renderer.
    */
    inline void SetSystemUserVersion(efd::UInt32 version);
    /** 
        Set the minimum compute user-defined version the system should allow to the given value.
        
        Values should be formed using D3D11ShaderFactory::CreateVertexShaderVersion.
    */
    inline void SetMinUserVersion(efd::UInt32 version);
    /** 
        Set the requested compute user-defined version the system should use to the given value.
        
        Values should be formed using D3D11ShaderFactory::CreateVertexShaderVersion.
    */
    inline void SetUserVersionRequest(efd::UInt32 version);
    /** 
        Set the system user-defined shader version to the given major/minor values.
        
        If the application uses the user-defined value as part of their shader system, 
        this value should be set immediately after creating the renderer.
    */
    inline void SetSystemUserVersion(efd::UInt32 major, efd::UInt32 minor);
    /** 
        Set the minimum compute user-defined version the system should allow to the given 
        major/minor values.
    */
    inline void SetMinUserVersion(efd::UInt32 major, efd::UInt32 minor);
    /** 
        Set the requested compute user-defined version the system should use to the given 
        major/minor values.
    */
    inline void SetUserVersionRequest(efd::UInt32 major, efd::UInt32 minor);

    /**
        Set the platform flags to the given value. 
        
        Values should come from the NiShader::Platform enumeration. 
        The renderer will call this at creation.
    */
    inline void SetPlatform(efd::UInt32 platform);

    /// Returns the currently-set system feature level.
    inline efd::UInt32 GetSystemFeatureLevel() const;
    /// Returns the currently-set minimum feature level.
    inline efd::UInt32 GetMinFeatureLevel() const;
    /// Returns the currently-set requested feature level.
    inline efd::UInt32 GetFeatureLevelRequest() const;

    /** 
        Returns the currently-set system compute shader version.

        The compute shader version will be encoded using D3D11 macros, and the major version
        can be obtained using D3D11_SHVER_GET_MAJOR(version) while the minor version can be 
        obtained using D3D11_SHVER_GET_MINOR(version). Alternatively, the 
        D3D11ShaderFactory::GetMajorComputeShaderVersion and GetMinorComputeShaderVersion can be
        used.
    */
    inline efd::UInt32 GetSystemComputeShaderVersion() const;
    /** 
        Returns the currently-set minimum compute shader version.

        The compute shader version will be encoded using D3D11 macros, and the major version
        can be obtained using D3D11_SHVER_GET_MAJOR(version) while the minor version can be 
        obtained using D3D11_SHVER_GET_MINOR(version). Alternatively, the 
        D3D11ShaderFactory::GetMajorComputeShaderVersion and GetMinorComputeShaderVersion can be
        used.
    */
    inline efd::UInt32 GetMinComputeShaderVersion() const;
    /** 
        Returns the currently-set requested compute shader version.

        The compute shader version will be encoded using D3D11 macros, and the major version
        can be obtained using D3D11_SHVER_GET_MAJOR(version) while the minor version can be 
        obtained using D3D11_SHVER_GET_MINOR(version). Alternatively, the 
        D3D11ShaderFactory::GetMajorComputeShaderVersion and GetMinorComputeShaderVersion can be
        used.
    */
    inline efd::UInt32 GetComputeShaderVersionRequest() const;

    /** 
        Returns the currently-set system user-defined shader version.

        The user-defined shader version will be encoded using D3D11 macros, and the major version
        can be obtained using D3D11_SHVER_GET_MAJOR(version) while the minor version can be 
        obtained using D3D11_SHVER_GET_MINOR(version). Alternatively, the 
        D3D11ShaderFactory::GetMajorVertexShaderVersion and GetMinorVertexShaderVersion can be
        used.
    */
    inline efd::UInt32 GetSystemUserVersion() const;
    /** 
        Returns the currently-set minimum user-defined shader version.

        The user-defined shader version will be encoded using D3D11 macros, and the major version
        can be obtained using D3D11_SHVER_GET_MAJOR(version) while the minor version can be 
        obtained using D3D11_SHVER_GET_MINOR(version). Alternatively, the 
        D3D11ShaderFactory::GetMajorVertexShaderVersion and GetMinorVertexShaderVersion can be
        used.
    */
    inline efd::UInt32 GetMinUserVersion() const;
    /** 
        Returns the currently-set requested user-defined shader version.

        The user-defined shader version will be encoded using D3D11 macros, and the major version
        can be obtained using D3D11_SHVER_GET_MAJOR(version) while the minor version can be 
        obtained using D3D11_SHVER_GET_MINOR(version). Alternatively, the 
        D3D11ShaderFactory::GetMajorVertexShaderVersion and GetMinorVertexShaderVersion can be
        used.
    */
    inline efd::UInt32 GetUserVersionRequest() const;

    /// Returns the current platform as a combination of NiShader::Platform enumerations.
    inline efd::UInt32 GetPlatform() const;

protected:
    efd::UInt32 m_systemFeatureLevel;
    efd::UInt32 m_minFeatureLevel;
    efd::UInt32 m_requestedFeatureLevel;

    efd::UInt32 m_systemComputeShaderVersion;
    efd::UInt32 m_minComputeShaderVersion;
    efd::UInt32 m_requestedComputeShaderVersion;

    efd::UInt32 m_systemUserVersion;
    efd::UInt32 m_minUserVersion;
    efd::UInt32 m_requestedUserVersion;
    efd::UInt32 m_platform;
};

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11ShaderLibraryVersion.inl>

#endif // DD_D3D11SHADERLIBRARYVERSION_H

