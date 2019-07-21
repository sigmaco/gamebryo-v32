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
#ifndef NIBINARYSHADERLIBRARY_H
#define NIBINARYSHADERLIBRARY_H

#include "NiBinaryShaderLibLibType.h"

#include <NSBLoader.h>
#include <NSBShader.h>
#include <NiD3DShaderLibrary.h>
#include <NiTPointerList.h>

NiSmartPointer(NiShaderLibraryDesc);

class NSBTextureStage;
class NSBTexture;

class NIBINARYSHADERLIB_ENTRY NiBinaryShaderLibrary : public NiD3DShaderLibrary
{
protected:
    NiBinaryShaderLibrary();

public:
    virtual ~NiBinaryShaderLibrary();

    static NiBinaryShaderLibrary* Create(int iDirectoryCount,
        const char* apcDirectories[], bool bRecurseSubFolders);
    static void Shutdown();
    static NiBinaryShaderLibrary* GetLibrary();

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
    // NiBinaryShader-based classes, allowing them to extend the
    // functionality while still gaining the benefit of having the
    // default NSF parsing do the file handling.
    //
    // This is the prototype of the CreateNiBinaryShaderFunction
    typedef NiBinaryShader* (*CREATENIBINARYSHADER)(
        const char* pcClassName);

    static CREATENIBINARYSHADER SetCreateNiBinaryShaderCallback(
        CREATENIBINARYSHADER pfnCallback);
    static CREATENIBINARYSHADER GetCreateNiBinaryShaderCallback();

    static NiBinaryShader* DefaultCreateNiBinaryShader(
        const char* pcClassName);

    // *** begin Emergent internal use only ***

    static NiBinaryShader* CreateNiBinaryShaderFromNSBShader(
        NSBShader* pkNSBShader, 
        unsigned int uiImplementation = NiShader::DEFAULT_IMPLEMENTATION);
    static bool SetupNiBinaryShaderFromNSBImplementation(
        NiBinaryShader& kShader,
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
    static NiD3DShaderConstantMap* CreateConstantMapFromNSBConstantMap(
        NSBConstantMap* pkCM, 
        NiShaderDesc* pkShaderDesc);
    static bool ProcessMapEntry(
        NiShaderDesc* pkShaderDesc,
        NSBConstantMap::NSBCM_Entry* pkEntry,
        NiD3DShaderConstantMap* pkSCM);
    static unsigned int FindEntryIndexInPlatformSCM(
        NiD3DShaderConstantMap* pkSCM,
        const char* pcName);

    // Render state conversion
    static bool SetupRenderStateGroupFromNSBStateGroup(
        NSBStateGroup* pkGroup,
        NiD3DRenderStateGroup& kRSGroup);
    static bool SetupTextureStageGroupFromNSBStateGroup(
        NSBStateGroup* pkGroup,
        NiD3DTextureStageGroup& kTSGroup);
    static bool SetupTextureSamplerGroupFromNSBStateGroup(
        NSBStateGroup* pkGroup,
        NiD3DTextureStageGroup& kTSGroup);

    // Pass conversion
    static bool SetupShaderPassFromNSBPass(
        NSBPass* pkNSBPass,
        NiD3DPass& kPass, 
        NiShaderDesc* pkShaderDesc);

    // Texture stage conversion
    static bool SetupTextureStageFromNSBTextureStage(
        NSBTextureStage* pkNSBStage, 
        NiD3DTextureStage& kStage);
    static bool ModifyTextureStageFromNSBTexture(
        NSBTexture* pkNSBStage, 
        NiD3DTextureStage& kStage);

    // Shader def conversion
    static NiShaderDeclaration* GetShaderDeclaration(NSBPackingDef* pkNSBPackingDef);

    // Packing def conversion
    static NiShaderDeclaration::ShaderParameterType
        ConvertPackingDefType(NSBPackingDef::NSBPackingDefEnum eType);

    // State conversions

    static bool ConvertNSBRenderStateValue(
        NSBRenderStates::NSBRenderStateEnum eNSBState, 
        unsigned int uiNSBValue,
        unsigned int& uiD3DValue);

    static bool GetD3DTextureStageState(
        NSBStageAndSamplerStates::NSBTextureStageState eTSS,
        unsigned int& uiD3DValue);
    static bool ConvertNSBTextureStageStateValue(
        NSBStageAndSamplerStates::NSBTextureStageState eTSS, 
        unsigned int uiNSBValue,
        unsigned int& uiD3DValue);
    static bool ConvertNSBTextureSamplerStateValue(
        NSBStageAndSamplerStates::NSBTextureSamplerState eTSS, 
        unsigned int uiNSBValue,
        unsigned int& uiD3DValue);

    static bool GetD3DTextureOp(
        NSBStageAndSamplerStates::NSBTextureOp eTOP,
        unsigned int& uiD3DValue);
    static bool GetD3DTextureArg(
        unsigned int uiTA,
        unsigned int& uiD3DValue);
    static bool GetD3DTextureTransformFlags(
        NSBStageAndSamplerStates::NSBTextureTransformFlags eTTF,
        unsigned int& uiD3DValue);
    static bool GetD3DTexCoordIndexFlags(
        unsigned int uiTCI,
        unsigned int& uiD3DValue);
    static bool GetD3DTextureSamplerState(
        NSBStageAndSamplerStates::NSBTextureSamplerState eTSS,
        unsigned int& uiD3DValue);
    static bool GetD3DTextureAddress(
        NSBStageAndSamplerStates::NSBTextureAddress eTA,
        unsigned int& uiD3DValue);
    static bool GetD3DTextureFilter(
        NSBStageAndSamplerStates::NSBTextureFilter eTF,
        unsigned int& uiD3DValue);

    static bool GetD3DRenderStateType(
        NSBRenderStates::NSBRenderStateEnum eRenderState,
        D3DRENDERSTATETYPE& eD3DRS);
    static bool GetD3DZBufferType(
        NSBRenderStates::NSBZBufferType eZBufferType,
        unsigned int& uiD3DValue);
    static bool GetD3DFillMode(
        NSBRenderStates::NSBFillMode eFillMode,
        unsigned int& uiD3DValue);
    static bool GetD3DShadeMode(
        NSBRenderStates::NSBShadeMode eShadeMode,
        unsigned int& uiD3DValue);
    static bool GetD3DBlend(
        NSBRenderStates::NSBBlend eBlend, 
        unsigned int& uiD3DValue);
    static bool GetD3DCull(
        NSBRenderStates::NSBCull eCull, 
        unsigned int& uiD3DValue);
    static bool GetD3DCmpFunc(
        NSBRenderStates::NSBCmpFunc eCmpFunc,
        unsigned int& uiD3DValue);
    static bool GetD3DFogMode(
        NSBRenderStates::NSBFogMode eFogMode,
        unsigned int& uiD3DValue);
    static bool GetD3DStencilOp(
        NSBRenderStates::NSBStencilOp eStencilOp,
        unsigned int& uiD3DValue);
    static bool GetD3DWrap(
        NSBRenderStates::NSBWrap eWrap, 
        unsigned int& uiD3DValue);
    static bool GetD3DMaterialColorSource(
        NSBRenderStates::NSBMaterialColorSource eMaterialColorSource,
        unsigned int& uiD3DValue);
    static bool GetD3DVertexBlendFlags(
        NSBRenderStates::NSBVertexBlendFlags eVertexBlendFlags, 
        unsigned int& uiD3DValue);
    static bool GetD3DPatchEdgeStyle(
        NSBRenderStates::NSBPatchEdgeStyle ePatchEdgeStyle,
        unsigned int& uiD3DValue);
    static bool GetD3DDebugMonitorTokens(
        NSBRenderStates::NSBDebugMonitorTokens eDebugMonitorTokens,
        unsigned int& uiD3DValue);
    static bool GetD3DBlendOp(
        NSBRenderStates::NSBBlendOp eBlendOp,
        unsigned int& uiD3DValue);
    static bool GetD3DDegreeType(
        NSBRenderStates::NSBDegreeType eDegreeType,
        unsigned int& uiD3DValue);
    static bool GetD3DTessellationMode(
        NSBRenderStates::NSBTessellationMode eTessMode,
        unsigned int& uiD3DValue);

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
        NiBinaryShader* pkBinaryShader);

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

    static NiBinaryShaderLibrary* ms_pkShaderLibrary;
    static CREATENIBINARYSHADER ms_pfnCreateNiBinaryShader;
};

#endif  //NIBINARYSHADERLIBRARY_H
