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
#ifndef NID3D10BINARYSHADERLIBRARY_H
#define NID3D10BINARYSHADERLIBRARY_H

#include "NiD3D10BinaryShaderLibLibType.h"

#include <NSBLoader.h>
#include <NSBShader.h>
#include <NiD3D10ShaderLibrary.h>
#include <NiTPointerList.h>

NiSmartPointer(NiShaderLibraryDesc);

class NSBTextureStage;
class NSBTexture;

class NiD3D10RenderStateGroup;
class NiD3D10ShaderConstantMap;
class NiD3D10Pass;

class NID3D10BINARYSHADERLIB_ENTRY NiD3D10BinaryShaderLibrary : public NiD3D10ShaderLibrary
{
protected:
    NiD3D10BinaryShaderLibrary();

public:
    virtual ~NiD3D10BinaryShaderLibrary();

    static NiD3D10BinaryShaderLibrary* Create(int iDirectoryCount,
        const char* apcDirectories[], bool bRecurseSubFolders);
    static void Shutdown();
    static NiD3D10BinaryShaderLibrary* GetLibrary();

    virtual NiShader* GetShader(NiRenderer* pkRenderer,
        const char* pcName, unsigned int uiImplementation);
    virtual bool ReleaseShader(const char* pcName,
        unsigned int uiImplementation);
    virtual bool ReleaseShader(NiShader* pkShader);

    virtual NiShaderLibraryDesc* GetShaderLibraryDesc();

    virtual unsigned int GetNumSupportedMimeTypes() const;
    virtual const char* GetSupportedMimeType(unsigned int uiIdx) const;

    virtual bool LoadShader(const char* pcFile);

    // This will allow for customers to derived their own
    // NiD3D10BinaryShader-based classes, allowing them to extend the
    // functionality while still gaining the benefit of having the
    // default NSF parsing do the file handling.
    //
    // This is the prototype of the CreateNiD3D10BinaryShaderFunction
    typedef NiD3D10BinaryShader* (*CREATENID3D10BINARYSHADER)(
        const char* pcClassName);

    static CREATENID3D10BINARYSHADER SetCreateNiD3D10BinaryShaderCallback(
        CREATENID3D10BINARYSHADER pfnCallback);
    static CREATENID3D10BINARYSHADER GetCreateNiD3D10BinaryShaderCallback();

    static NiD3D10BinaryShader* DefaultCreateNiD3D10BinaryShader(
        const char* pcClassName);

    // *** begin Emergent internal use only ***

    static NiD3D10BinaryShader* CreateNiD3D10BinaryShaderFromNSBShader(
        NSBShader* pkNSBShader, 
        unsigned int uiImplementation = NiShader::DEFAULT_IMPLEMENTATION);
    static bool SetupNiD3D10BinaryShaderFromNSBImplementation(
        NiD3D10BinaryShader& kShader,
        NSBImplementation* pkImplementation, 
        NSBShader* pkNSBShader, 
        NiShaderDesc* pkShaderDesc);

    virtual void SetShaderLibraryDesc(NiShaderLibraryDesc* pkLibDesc);

    bool InsertNSBShaderIntoList(NSBShader* pkNSBShader);
    bool LoadNSBShaders(const char* pcDirectory,
        bool bRecurseSubFolders);
    // *** end Emergent internal use only ***

protected:
    static bool RegisterTextureStageGlobals(
        NSBShader* pkShader, 
        NSBImplementation* pkImplementation);
    static bool ReleaseTextureStageGlobals(
        NSBShader* pkShader, 
        NSBImplementation* pkImplementation);

    // Constant map conversion
    static NiD3D10ShaderConstantMap* CreateConstantMapFromNSBConstantMap(
        NSBConstantMap* pkCM, 
        NiShaderDesc* pkShaderDesc);
    static bool ProcessMapEntry(
        NiShaderDesc* pkShaderDesc,
        NSBConstantMap::NSBCM_Entry* pkEntry,
        NiD3D10ShaderConstantMap* pkSCM);
    static unsigned int FindEntryIndexInPlatformSCM(
        NiD3D10ShaderConstantMap* pkSCM,
        const char* pcName);

    // Render state conversion
    static bool SetupRenderStateGroupFromNSBStateGroup(
        NSBStateGroup* pkGroup,
        NiD3D10RenderStateGroup& kRSGroup);
    static bool SetupTextureSamplerGroupFromNSBStateGroup(
        NSBStateGroup* pkGroup,
        NiD3D10RenderStateGroup& kRSGroup, 
        unsigned int uiStage);

    // Pass conversion
    static bool SetupShaderPassFromNSBPass(
        NSBPass* pkNSBPass,
        NiD3D10Pass& kPass, 
        NiShaderDesc* pkShaderDesc);

    // Texture stage conversion
    static bool SetupTextureStageFromNSBTextureStage(
        NSBTextureStage* pkNSBStage, 
        NiD3D10Pass& kPass);
    static bool ModifyTextureStageFromNSBTexture(
        NSBTexture* pkNSBStage, 
        NiD3D10Pass& kPass);

    static bool InterpretFlags(unsigned int uiNSBTextureFlags,
        unsigned int& uiGBMap, unsigned int& uiGBMapInstance);

    // Shader def conversion
    static NiShaderDeclaration* GetShaderDeclaration(NSBPackingDef* pkNSBPackingDef);

    // Packing def conversion
    static NiShaderDeclaration::ShaderParameterType
        ConvertPackingDefType(NSBPackingDef::NSBPackingDefEnum eType);

    // State conversions

    static bool ConvertNSBRenderStateValue(
        NSBRenderStates::NSBRenderStateEnum eNSBState, 
        unsigned int uiNSBValue,
        unsigned int& uiD3D10Value);

    static bool ConvertNSBTextureSamplerStateValue(
        NSBStageAndSamplerStates::NSBTextureSamplerState eTSS, 
        unsigned int uiNSBValue,
        unsigned int& uiD3D10Value);
    
    static bool ConvertNSBTextureSamplerFilterValue(
        NSBStageAndSamplerStates::NSBTextureFilter eMinFilter, 
        NSBStageAndSamplerStates::NSBTextureFilter eMagFilter,
        NSBStageAndSamplerStates::NSBTextureFilter eMipFilter, 
        unsigned int& uiD3D10Value,
        bool& bMipmapEnable);
    static bool GetD3D10TextureAddress(
        NSBStageAndSamplerStates::NSBTextureAddress eTA,
        unsigned int& uiD3D10Value);
    static bool GetD3D10FillMode(
        NSBRenderStates::NSBFillMode eFillMode,
        unsigned int& uiD3D10Value);
    static bool GetD3D10Blend(
        NSBRenderStates::NSBBlend eBlend, 
        unsigned int& uiD3D10Value);
    static bool GetD3D10Cull(
        NSBRenderStates::NSBCull eCull, 
        unsigned int& uiD3D10Value);
    static bool GetD3D10CmpFunc(
        NSBRenderStates::NSBCmpFunc eCmpFunc,
        unsigned int& uiD3D10Value);
    static bool GetD3D10StencilOp(
        NSBRenderStates::NSBStencilOp eStencilOp,
        unsigned int& uiD3D10Value);
    static bool GetD3D10BlendOp(
        NSBRenderStates::NSBBlendOp eBlendOp,
        unsigned int& uiD3D10Value);

    static NSBImplementation* GetBestImplementation(NSBShader* pkShader);

    class VersionInfo : public NiMemObject
    {
    public:
        unsigned int m_uiVS_Sys;
        unsigned int m_uiVS_Min;
        unsigned int m_uiVS_Req;
        unsigned int m_uiGS_Sys;
        unsigned int m_uiGS_Min;
        unsigned int m_uiGS_Req;
        unsigned int m_uiPS_Sys;
        unsigned int m_uiPS_Min;
        unsigned int m_uiPS_Req;
        unsigned int m_uiUser_Sys;
        unsigned int m_uiUser_Min;
        unsigned int m_uiUser_Req;
        unsigned int m_uiPlatform;
        bool m_bSoftwareVSCapable_Sys;
    };

    enum ValidityFlag
    {
        INVALID = 0,
        VALID = 1,
        VALID_REQUESTED = 2
    };

    static void SetupVersionInfo(VersionInfo& kVersionInfo);
    static ValidityFlag IsImplementationValid(NSBImplementation* pkImplementation,
        VersionInfo& kVersionInfo);

    static void GetRequirementValues(
        NSBRequirements* pkReqs, 
        unsigned int& uiVSVers,
        unsigned int& uiGSVers, 
        unsigned int& uiPSVers, 
        unsigned int& uiUser);

    bool RegisterNewShader(
        NSBShader* pkNSBShader, 
        NiD3D10BinaryShader* pkBinaryShader);

    void AddShaderDesc(NSBShader* pkNSBShader);

    class ShaderSet : public NiMemObject
    {
    public:
        ShaderSet();
        virtual ~ShaderSet();

        unsigned int GetImplementationCount() const;

        void InsertShader(NiShader* pkShader);
        NiShader* GetShader(unsigned int uiImplementation) const;
        void RemoveShader(unsigned int uiImplementation);
    protected:
        unsigned int m_uiNumImplementations;
        NiShaderPtr* m_pspImplementationArray;
    };

    NiTStringMap<ShaderSet*> m_kShaders;

    NSBLoader* m_pkNSBLoader;

    static NiD3D10BinaryShaderLibrary* ms_pkShaderLibrary;
    static CREATENID3D10BINARYSHADER ms_pfnCreateNiD3D10BinaryShader;
};

#endif  //NID3D10BINARYSHADERLIBRARY_H
