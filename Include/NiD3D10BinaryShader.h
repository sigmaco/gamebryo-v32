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
#ifndef NID3D10BINARYSHADER_H
#define NID3D10BINARYSHADER_H

#include "NiD3D10BinaryShaderLibLibType.h"
#include "NSBUserDefinedDataSet.h"

#include <NiD3D10Shader.h>
#include <NiShaderDeclaration.h>
#include <NiShaderRequirementDesc.h>

// For reporting errors...
#include <NiD3D10ShaderFactory.h>

class NSBImplementation;

class NID3D10BINARYSHADERLIB_ENTRY NiD3D10BinaryShader : public NiD3D10Shader
{
    NiDeclareRTTI;
public:
    NiD3D10BinaryShader();
    virtual ~NiD3D10BinaryShader();

    virtual bool Initialize();

    virtual unsigned int UpdatePipeline(const NiRenderCallContext& kRCC);

    inline NSBUserDefinedDataSet* GetShaderUserDefinedDataSet();
    inline NSBUserDefinedDataSet* GetImplementationUserDefinedDataSet();
    inline NSBUserDefinedDataSet* GetPassUserDefinedDataSet(
        unsigned int uiPass);

    // *** begin Emergent internal use only
    // These functions are used for the creation of the shader
    inline void SetUserDefinedDataSet(NSBUserDefinedDataSet* pkUDDSet);
    inline void SetImplementationUserDefinedDataSet(
        NSBUserDefinedDataSet* pkUDDSet);
    inline void SetPassUserDefinedDataSet(unsigned int uiPass,
        NSBUserDefinedDataSet* pkUDDSet);

    // Render State Group
    inline void SetRenderStateGroup(NiD3D10RenderStateGroup* pkRenderStateGroup);

    // Vertex shader mapping
    inline unsigned int GetVertexConstantMapCount() const;
    inline NiD3D10ShaderConstantMap* GetVertexConstantMap(unsigned int uiIndex)
        const;
    inline void SetVertexConstantMap(unsigned int uiIndex,
        NiD3D10ShaderConstantMap* pkSCMVertex);

    // Geometry shader mapping
    inline unsigned int GetGeometryConstantMapCount() const;
    inline NiD3D10ShaderConstantMap* GetGeometryConstantMap(unsigned int uiIndex)
        const;
    inline void SetGeometryConstantMap(unsigned int uiIndex,
        NiD3D10ShaderConstantMap* pkSCMGeometry);

    // Pixel shader mapping
    inline unsigned int GetPixelConstantMapCount() const;
    inline NiD3D10ShaderConstantMap* GetPixelConstantMap(unsigned int uiIndex)
        const;
    inline void SetPixelConstantMap(unsigned int uiIndex,
        NiD3D10ShaderConstantMap* pkSCMPixel);

    // Inserts the pass at the given position.
    inline bool InsertPass(unsigned int uiPass, NiD3D10Pass* pkPass);

    // For skinning shaders
    enum BoneMatrixCalcMethod
    {
        BONECALC_SKIN       = 0x00000000,
        BONECALC_NO_SKIN    = 0x00000001
    };

    inline unsigned int GetBonesPerPartition() const;
    inline void SetBonesPerPartition(unsigned int uiBones);
    inline unsigned int GetBoneMatrixRegisters() const;
    inline void SetBoneMatrixRegisters(unsigned int uiRegisters);
    BoneMatrixCalcMethod GetBoneCalcMethod() const;
    inline void SetBoneCalcMethod(BoneMatrixCalcMethod eMethod);

    inline NiShaderRequirementDesc::NBTFlags GetBinormalTangentMethod() const;
    inline void SetBinormalTangentMethod(
        NiShaderRequirementDesc::NBTFlags eNBTMethod);

    inline unsigned int GetBinormalTangentUVSource() const;
    inline void SetBinormalTangentUVSource(unsigned int uiSource);

    virtual bool SetupGeometry(NiRenderObject* pkGeometry,
        NiMaterialInstance* pkMaterialInstance);
    virtual bool IsTimeBased(NiD3D10ShaderConstantMap* pkMap);

    // *** end Emergent internal use only

protected:
    bool LoadVertexShaderProgram(NiD3D10Pass& kPass);
    bool LoadGeometryShaderProgram(NiD3D10Pass& kPass);
    bool LoadPixelShaderProgram(NiD3D10Pass& kPass);
    bool ResolveVertexShaderFileName(const char* pcOriginalName,
        char* pcTrueName, unsigned int uiNameLength);
    bool ResolveGeometryShaderFileName(const char* pcOriginalName,
        char* pcTrueName, unsigned int uiNameLength);
    bool ResolvePixelShaderFileName(const char* pcOriginalName,
        char* pcTrueName, unsigned int uiNameLength);

    void PrepareTexture(const NiRenderCallContext& kRCC,
        unsigned int uiTexture,
        NiD3D10Pass* pkPass,
        const NiTexturingProperty* pkTexProp);

    unsigned int m_uiBonesPerPartition;
    unsigned int m_uiBoneMatrixRegisters;
    BoneMatrixCalcMethod m_eBoneCalcMethod;
    NiShaderRequirementDesc::NBTFlags m_eBinormalTangentMethod;
    unsigned int m_uiBinormalTangentUVSource;

    // User defined data set
    NSBUserDefinedDataSetPtr m_spUDDSet_Shader;
    NSBUserDefinedDataSetPtr m_spUDDSet_Implementation;
    NiTObjectArray<NSBUserDefinedDataSetPtr> m_kUDDSet_PassArray;

    unsigned int m_uiPassCount;
};

#include "NiD3D10BinaryShader.inl"

#endif  //NID3D10BINARYSHADER_H
