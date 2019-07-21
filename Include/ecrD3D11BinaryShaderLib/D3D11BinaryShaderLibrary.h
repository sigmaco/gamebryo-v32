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
#ifndef EE_D3D11BINARYSHADERLIBRARY_H
#define EE_D3D11BINARYSHADERLIBRARY_H

#include <ecrD3D11BinaryShaderLib/ecrD3D11BinaryShaderLibLibType.h>

#include <NSBLoader.h>
#include <NSBShader.h>
#include <ecrD3D11Renderer/D3D11ShaderLibrary.h>
#include <NiTPointerList.h>

NiSmartPointer(NiShaderLibraryDesc);

class NSBTextureStage;
class NSBTexture;

namespace ecr
{

class D3D11BinaryShader;
class D3D11RenderStateGroup;
class D3D11ShaderConstantMap;
class D3D11Pass;

/**
    D3D11BinaryShaderLibrary is the D3D11-specific shader library that exposes NSB shaders.

    The library will create D3D11BinaryShader objects for shaders found from the NSBShader 
    objects returned NSBLoader component of NSBShaderLib.

    Applications that link in D3D11BinaryShaderLibrary using static libraries should use the
    function D3D11BinaryShaderLib_LoadShaderLibrary, found in D3D11BinaryShaderLib.h.
*/
class EE_ECRD3D11BINARYSHADERLIB_ENTRY D3D11BinaryShaderLibrary : public ecr::D3D11ShaderLibrary
{
public:
    /// @name Construction and Destruction
    //@{
    /// Destructor.
    virtual ~D3D11BinaryShaderLibrary();
    //@}

    /**
        Create an instance of the D3D11BinaryShaderLibrary. 
        
        After the library is created, the function LoadNSBShaders is called, which passes the 
        parameters to the library's NSBLoader object so it can load the NSB files it finds. 
        The NSBLoader will search for all NSB files, loading them and adding them to the library's 
        list of available shaders. 

        @param directoryCount Number of directories in the pDirectories array.
        @param pDirectories Array of directories to search for shaders.
        @param recurseSubFolders Whether or not to recursively search the directories specified in 
            pDirectories.
        @return The new library, if creation succeeded, otherwise NULL.
    */
    static D3D11BinaryShaderLibrary* Create(
        efd::SInt32 directoryCount,
        const efd::Char* pDirectories[], 
        efd::Bool recurseSubFolders);
    /// Shut down the static instance of the D3D11BinaryShaderLibrary.
    static void Shutdown();
    /// Return the static instance of the D3D11BinaryShaderLibrary.
    static D3D11BinaryShaderLibrary* GetLibrary();

    /// Return a specific shader, creating it it necessary, or return NULL if the shader library 
    /// cannot create a shader with the given name and implementation.
    virtual NiShader* GetShader(
        NiRenderer* pRenderer,
        const efd::Char* pName, 
        efd::UInt32 implementation);
    /// Release the shader library's reference to the given shader, and return whether or not
    /// the shader library had a reference to that shader.
    virtual efd::Bool ReleaseShader(
        const efd::Char* pName,
        efd::UInt32 implementationID);
    /// Release the shader library's reference to the given shader, and return whether or not
    /// the shader library had a reference to that shader.
    virtual efd::Bool ReleaseShader(NiShader* pShader);

    /// Return the shader library description.
    virtual NiShaderLibraryDesc* GetShaderLibraryDesc();

    /// Return the number of mime types the shader library supports.
    virtual efd::UInt32 GetNumSupportedMimeTypes() const;
    /// Return one of the mime types the shader library supports.
    virtual const efd::Char* GetSupportedMimeType(efd::UInt32 index) const;

    /// Load an NSBShader from the indicated file, and return whether or not the load was 
    /// successful.
    virtual efd::Bool LoadShader(const efd::Char* pFile);

    /**
        Prototype for the callback function used to create a new D3D11BinaryShader instance. 
        
        The callback receives the class name which was associated with the implementation that is 
        being converted into a run-time shader. A registered callback should use the name to 
        determine whether a custom D3D11BinaryShader-derived class is required and if so create and 
        return it. Otherwise, they should return NULL and the system will create a standard 
        D3D11BinaryShader instance. 

        This allows applications to derive their own D3D11BinaryShader-based classes, allowing
        them to extend the functionality while still gaining the benefit of having the default 
        NSF parsing do the file handling.

        @param pClassName Class name to create.
    */
    typedef ecr::D3D11BinaryShader* (*CREATED3D11BINARYSHADER)(
        const efd::Char* pClassName);

    /// Set the callback function for creating new binary shaders.
    static CREATED3D11BINARYSHADER SetCreateD3D11BinaryShaderCallback(
        CREATED3D11BINARYSHADER pCallback);
    /// Return the callback function for creating new binary shaders.
    static CREATED3D11BINARYSHADER GetCreateD3D11BinaryShaderCallback();

    /// Default callback function for creating new binary shaders.
    static D3D11BinaryShader* DefaultCreateD3D11BinaryShader(
        const efd::Char* pcClassName);

    /// @cond EMERGENT_INTERNAL

    /// Create and initialize a D3D11BinaryShader object based on an NSBShader.
    static D3D11BinaryShader* CreateD3D11BinaryShaderFromNSBShader(
        NSBShader* pNSBShader, 
        efd::UInt32 implementationID = NiShader::DEFAULT_IMPLEMENTATION);
    /// Create and initialize a D3D11BinaryShader object based on a specific NSBImplementation.
    static efd::Bool SetupD3D11BinaryShaderFromNSBImplementation(
        D3D11BinaryShader& shader,
        NSBImplementation* pImplementation, 
        NSBShader* pNSBShader, 
        NiShaderDesc* pShaderDesc);

    /// Set the shader library description.
    virtual void SetShaderLibraryDesc(NiShaderLibraryDesc* pLibDesc);

    /// Add a new NSBShader to the library's list.
    efd::Bool InsertNSBShaderIntoList(NSBShader* pNSBShader);
    /// Search for NSB files in a directory and load them as they are found.
    efd::Bool LoadNSBShaders(
        const efd::Char* pDirectory,
        efd::Bool bRecurseSubFolders);

    /// @endcond

protected:
    /// Hidden constructor.
    D3D11BinaryShaderLibrary();

    //@{
    /// Convert a NSBConstantMap into a D3D11ShaderConstantMap.
    static efd::Bool ExtendConstantMapWithNSBConstantMap(
        D3D11ShaderConstantMap* pAddToConstantMap, 
        NSBConstantMap* pCM, 
        NiShaderDesc* pShaderDesc);
    static D3D11ShaderConstantMap* CreateConstantMapFromNSBConstantMap(
        NSBConstantMap* pCM, 
        NiShaderDesc* pShaderDesc);
    static efd::Bool ProcessMapEntry(
        NiShaderDesc* pShaderDesc,
        NSBConstantMap::NSBCM_Entry* pEntry,
        D3D11ShaderConstantMap* pSCM);
    static efd::UInt32 FindEntryIndexInPlatformSCM(
        D3D11ShaderConstantMap* pSCM,
        const efd::Char* pName);
    //@}

    //@{
    /// Convert a NSBStateGroup into a RenderStateGroup or Sampler.
    static efd::Bool SetupRenderStateGroupFromNSBStateGroup(
        NSBStateGroup* pGroup,
        D3D11RenderStateGroup& rsGroup);
    static efd::Bool SetupSamplerFromNSBStateGroup(
        NSBStateGroup* pGroup,
        D3D11RenderStateGroup& rsGroup, 
        const efd::Char* pSamplerName);
    //@}

    //@{
    /// Convert a NSBPass into a D3D11Pass.
    static efd::Bool SetupShaderPassFromNSBPass(
        NSBPass* pNSBPass,
        D3D11Pass& passObject, 
        NiShaderDesc* pShaderDesc);
    //@}

    //@{
    /// Set up render states and shader resources from NSBTextureStage.
    static efd::Bool SetupTextureStageFromNSBTextureStage(
        NSBTextureStage* pNSBStage, 
        D3D11Pass& passObject);
    static efd::Bool SetupTextureFromNSBTexture(
        NSBTexture* pNSBStage, 
        D3D11Pass& passObject);
    //@}

    /// Interpret between NSB texture flags and NiTextureStage texture flags.
    static void InterpretTextureFlags(
        efd::UInt32 nsbTextureFlags,
        efd::UInt32& gbMap, 
        efd::UInt16& gbMapInstance);

    /// Shader declaration conversion
    static NiShaderDeclaration* GetShaderDeclaration(NSBPackingDef* pNSBPackingDef);

    /// Packing def conversion
    static NiShaderDeclaration::ShaderParameterType
        ConvertPackingDefType(NSBPackingDef::NSBPackingDefEnum packingDefType);

    //@{
    /// Convert between NSB enumerations and D3D11 enumerations
    static efd::Bool ConvertNSBRenderStateValue(
        NSBRenderStates::NSBRenderStateEnum nsbState, 
        efd::UInt32 nsbValue,
        efd::UInt32& d3d11Value);

    static efd::Bool ConvertNSBTextureSamplerStateValue(
        NSBStageAndSamplerStates::NSBTextureSamplerState nsbState, 
        efd::UInt32 nsbValue,
        efd::UInt32& d3d11Value);
    
    static efd::Bool ConvertNSBTextureSamplerFilterValue(
        NSBStageAndSamplerStates::NSBTextureFilter minFilter, 
        NSBStageAndSamplerStates::NSBTextureFilter magFilter,
        NSBStageAndSamplerStates::NSBTextureFilter mipFilter, 
        efd::UInt32& d3d11Value,
        efd::Bool& mipmapEnable);
    static efd::Bool GetD3D11TextureAddress(
        NSBStageAndSamplerStates::NSBTextureAddress nsbState,
        efd::UInt32& d3d11Value);
    static efd::Bool GetD3D11FillMode(
        NSBRenderStates::NSBFillMode nsbState,
        efd::UInt32& d3d11Value);
    static efd::Bool GetD3D11Blend(
        NSBRenderStates::NSBBlend nsbState, 
        efd::UInt32& d3d11Value);
    static efd::Bool GetD3D11Cull(
        NSBRenderStates::NSBCull nsbState, 
        efd::UInt32& d3d11Value);
    static efd::Bool GetD3D11CmpFunc(
        NSBRenderStates::NSBCmpFunc nsbState,
        efd::UInt32& d3d11Value);
    static efd::Bool GetD3D11StencilOp(
        NSBRenderStates::NSBStencilOp nsbState,
        efd::UInt32& d3d11Value);
    static efd::Bool GetD3D11BlendOp(
        NSBRenderStates::NSBBlendOp nsbState,
        efd::UInt32& d3d11Value);
    static efd::Bool GetD3D11FeatureLevel(
        NSBRequirements::NSBFeatureLevel nsbFeatureLevel,
        efd::UInt32& d3d11Value);
    //@}
    
    /// Return the best implementation the current hardware can use.
    static NSBImplementation* GetBestImplementation(NSBShader* pShader);

    /// Structure describing the parameters used for selecting an implementation.
    class VersionInfo : public NiMemObject
    {
    public:
        efd::UInt32 m_featureLevelSys;
        efd::UInt32 m_featureLevelMin;
        efd::UInt32 m_featureLevelReq;
        efd::UInt32 m_computeShaderSys;
        efd::UInt32 m_computeShaderMin;
        efd::UInt32 m_computeShaderReq;
        efd::UInt32 m_userSys;
        efd::UInt32 m_userMin;
        efd::UInt32 m_userReq;
        efd::UInt32 m_platform;
    };

    enum ValidityFlag
    {
        INVALID = 0,
        VALID = 1,
        VALID_REQUESTED = 2
    };

    /// Populate a VersionInfo with the current hardware capabilities.
    static void SetupVersionInfo(VersionInfo& versionInfo);
    /// Return whether a given implementation is valid on the current hardware.
    static ValidityFlag IsImplementationValid(
        NSBImplementation* pImplementation,
        VersionInfo& versionInfo);

    /// Return the requirements described by an NSBRequirements structure.
    static void GetRequirementValues(
        NSBRequirements* pReqs, 
        NSBRequirements::NSBFeatureLevel& featureLevel, 
        efd::UInt32& csVersion,
        efd::UInt32& userVersion);

    /// Register a newly-created binary shader with the shader library.
    efd::Bool RegisterNewShader(
        NSBShader* pNSBShader, 
        D3D11BinaryShader* pBinaryShader);

    /// Add the description of the NSBShader to the shader library description.
    void AddShaderDesc(NSBShader* pNSBShader);

    class ShaderSet : public NiMemObject
    {
    public:
        ShaderSet();
        virtual ~ShaderSet();

        efd::UInt32 GetImplementationCount() const;

        void InsertShader(NiShader* pShader);
        NiShader* GetShader(efd::UInt32 implementationID) const;
        void RemoveShader(efd::UInt32 implementationID);
    protected:
        efd::UInt32 m_numImplementations;
        NiShaderPtr* m_pImplementationArray;
    };

    NiTStringMap<ShaderSet*> m_shaders;

    NSBLoader* m_pNSBLoader;

    static D3D11BinaryShaderLibrary* ms_pShaderLibrary;
    static CREATED3D11BINARYSHADER ms_pCreateD3D11BinaryShader;
};

}   // End namespace ecr.

#endif // EE_D3D11BINARYSHADERLIBRARY_H
