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
#ifndef NSBPASS_H
#define NSBPASS_H

#include "NSBShaderLibLibType.h"
#include "NSBRenderStates.h"
#include "NSBConstantMap.h"
#include "NSBUserDefinedDataSet.h"
#include "NSBUtility.h"
#include <NiStreamOutSettings.h>

#include <NiTArray.h>

class NSBTextureStage;
class NSBTexture;
class NSBStateGroup;

class NSBSHADERLIB_ENTRY NSBPass : public NiMemObject
{
public:
    NSBPass();
    ~NSBPass();

    // Name
    inline const char* GetName() const;
    void SetName(const char* pcName);

    // RenderStateGroup
    NSBStateGroup* GetRenderStateGroup();

    // Shader Programs
    inline const char* GetShaderProgramFile(NiSystemDesc::RendererID eRenderer,
        NiGPUProgram::ProgramType eType) const;
    inline void SetShaderProgramFile(const char* pcProgramFileName,
        NiSystemDesc::RendererID eRenderer, NiGPUProgram::ProgramType eType);
    inline const char* GetShaderProgramEntryPoint(
        NiSystemDesc::RendererID eRenderer,
        NiGPUProgram::ProgramType eType) const;
    inline void SetShaderProgramEntryPoint(const char* pcEntryPoint,
        NiSystemDesc::RendererID eRenderer, NiGPUProgram::ProgramType eType);
    inline const char* GetShaderProgramShaderTarget(
        NiSystemDesc::RendererID eRenderer,
        NiGPUProgram::ProgramType eType) const;
    inline void SetShaderProgramShaderTarget(const char* pcShaderTarget,
        NiSystemDesc::RendererID eRenderer, NiGPUProgram::ProgramType eType);
    /// Is a shader program of this type present for any renderer?
    bool GetShaderPresent(NiGPUProgram::ProgramType eType) const;
    /// Is a shader program of this type present for a specific renderer?
    bool GetShaderPresent(
        NiGPUProgram::ProgramType eType, 
        efd::SystemDesc::RendererID eRendererID) const;

    inline bool GetSoftwareVertexProcessing() const;
    inline void SetSoftwareVertexProcessing(bool bSWVertexProcessing);

    inline void SetComputeThreadGroupCounts(
        unsigned int uiTGCountX, 
        unsigned int uiTGCountY, 
        unsigned int uiTGCountZ);
    inline unsigned int GetComputeThreadGroupCountX() const;
    inline unsigned int GetComputeThreadGroupCountY() const;
    inline unsigned int GetComputeThreadGroupCountZ() const;

    // Constant Maps
    inline unsigned int GetVertexConstantMapCount() const;
    inline unsigned int GetGeometryConstantMapCount() const;
    inline unsigned int GetPixelConstantMapCount() const;
    NSBConstantMap* GetVertexConstantMap(unsigned int uiIndex) const;
    NSBConstantMap* GetGeometryConstantMap(unsigned int uiIndex) const;
    NSBConstantMap* GetPixelConstantMap(unsigned int uiIndex) const;

    inline unsigned int GetConstantMapCount(NiGPUProgram::ProgramType eType) const;
    NSBConstantMap* GetConstantMap(NiGPUProgram::ProgramType eType, unsigned int uiIndex) const;
    unsigned int AddConstantMap(NiGPUProgram::ProgramType eType);

    // Stages
    unsigned int GetStageCount() const;
    NSBTextureStage* GetStage(unsigned int uiIndex, bool bCreate = true);

    // Textures
    unsigned int GetTextureCount() const;
    NSBTexture* GetTexture(unsigned int uiIndex, bool bCreate = true);

    void SetMaxTextureCount(unsigned int uiCount);
    void SetTexture(unsigned int uiIndex, NSBTexture* pkTexture);

    // User defined data set
    inline NSBUserDefinedDataSet* GetUserDefinedDataSet() const;
    inline void SetUserDefinedDataSet(NSBUserDefinedDataSet* pkUDDSet);

    // StreamOutSettings
    inline NiStreamOutSettings& GetStreamOutSettings();

    // *** begin Emergent internal use only
    bool SaveBinary(efd::BinaryStream& kStream);
    bool LoadBinary(efd::BinaryStream& kStream);

#if defined(NIDEBUG)
    void Dump(FILE* pf);
#endif  //#if defined(NIDEBUG)
    // *** end Emergent internal use only

protected:
    bool SaveBinaryShaderProgram(efd::BinaryStream& kStream,
        NiGPUProgram::ProgramType eType);
    bool SaveBinaryStages(efd::BinaryStream& kStream);
    bool SaveBinaryTextures(efd::BinaryStream& kStream);

    bool LoadBinaryVertexShaderProgram(efd::BinaryStream& kStream);
    bool LoadBinaryGeometryShaderProgram(efd::BinaryStream& kStream);
    bool LoadBinaryPixelShaderProgram(efd::BinaryStream& kStream);
    bool LoadBinaryShaderProgram(efd::BinaryStream& kStream,
        NiGPUProgram::ProgramType eType);
    bool LoadBinaryStages(efd::BinaryStream& kStream);
    bool LoadBinaryTextures(efd::BinaryStream& kStream);

    char* m_pcName;

    // User defined data set
    NSBUserDefinedDataSetPtr m_spUserDefinedDataSet;

    // 'Local' render state settings for the shader
    NSBStateGroup* m_pkRenderStateGroup;
    // 'Local' shader mapping for the shader
    NiTPrimitiveSet<NSBConstantMap*> m_akShaderConstantMaps[NSBConstantMap::NSB_SHADER_TYPE_COUNT];

    struct ShaderProgramInfo
    {
        ShaderProgramInfo();
        ~ShaderProgramInfo();

        char* m_pcProgramFile;
        char* m_pcEntryPoint;
        char* m_pcTarget;
    };

    ShaderProgramInfo m_akInfo[NiSystemDesc::RENDERER_NUM][NSBConstantMap::NSB_SHADER_TYPE_COUNT];

    bool m_bSoftwareVP;

    unsigned int m_uiThreadGroupCountX;
    unsigned int m_uiThreadGroupCountY;
    unsigned int m_uiThreadGroupCountZ;

    // Stream Out settings for the implementation
    NiStreamOutSettings m_kStreamOutSettings;

    NiTPrimitiveArray<NSBTextureStage*> m_akStages;
    NiTPrimitiveArray<NSBTexture*> m_akTextures;
};

#include "NSBPass.inl"

#endif  //NSBPASS_H
