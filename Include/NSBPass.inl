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
//------------------------------------------------------------------------------------------------
inline const char* NSBPass::GetName() const
{
    return m_pcName;
}

//------------------------------------------------------------------------------------------------
inline const char* NSBPass::GetShaderProgramFile(
    NiSystemDesc::RendererID eRenderer, NiGPUProgram::ProgramType eType) const
{
    EE_ASSERT((int)eType < (int)NSBConstantMap::NSB_SHADER_TYPE_COUNT);
    return m_akInfo[eRenderer][eType].m_pcProgramFile;
}

//------------------------------------------------------------------------------------------------
inline void NSBPass::SetShaderProgramFile(const char* pcProgramFileName,
    NiSystemDesc::RendererID eRenderer, NiGPUProgram::ProgramType eType)
{
    EE_ASSERT((int)eType < (int)NSBConstantMap::NSB_SHADER_TYPE_COUNT);
    NSBUtility::SetString(m_akInfo[eRenderer][eType].m_pcProgramFile,
        0, pcProgramFileName);
}

//------------------------------------------------------------------------------------------------
inline const char* NSBPass::GetShaderProgramEntryPoint(
    NiSystemDesc::RendererID eRenderer, NiGPUProgram::ProgramType eType) const
{
    EE_ASSERT((int)eType < (int)NSBConstantMap::NSB_SHADER_TYPE_COUNT);
    return m_akInfo[eRenderer][eType].m_pcEntryPoint;
}

//------------------------------------------------------------------------------------------------
inline void NSBPass::SetShaderProgramEntryPoint(const char* pcEntryPoint,
    NiSystemDesc::RendererID eRenderer, NiGPUProgram::ProgramType eType)
{
    EE_ASSERT((int)eType < (int)NSBConstantMap::NSB_SHADER_TYPE_COUNT);
    NSBUtility::SetString(m_akInfo[eRenderer][eType].m_pcEntryPoint,
        0, pcEntryPoint);
}

//------------------------------------------------------------------------------------------------
inline const char* NSBPass::GetShaderProgramShaderTarget(
    NiSystemDesc::RendererID eRenderer, NiGPUProgram::ProgramType eType) const
{
    EE_ASSERT((int)eType < (int)NSBConstantMap::NSB_SHADER_TYPE_COUNT);
    return m_akInfo[eRenderer][eType].m_pcTarget;
}

//------------------------------------------------------------------------------------------------
inline void NSBPass::SetShaderProgramShaderTarget(const char* pcShaderTarget,
    NiSystemDesc::RendererID eRenderer, NiGPUProgram::ProgramType eType)
{
    EE_ASSERT((int)eType < (int)NSBConstantMap::NSB_SHADER_TYPE_COUNT);
    NSBUtility::SetString(m_akInfo[eRenderer][eType].m_pcTarget, 0,
        pcShaderTarget);
}

//------------------------------------------------------------------------------------------------
inline bool NSBPass::GetSoftwareVertexProcessing() const
{
    return m_bSoftwareVP;
}

//------------------------------------------------------------------------------------------------
inline void NSBPass::SetSoftwareVertexProcessing(bool bSoftwareVP)
{
    m_bSoftwareVP = bSoftwareVP;
}

//------------------------------------------------------------------------------------------------
inline void NSBPass::SetComputeThreadGroupCounts(
    unsigned int uiTGCountX, 
    unsigned int uiTGCountY, 
    unsigned int uiTGCountZ)
{
    m_uiThreadGroupCountX = uiTGCountX;
    m_uiThreadGroupCountY = uiTGCountY;
    m_uiThreadGroupCountZ = uiTGCountZ;
}

//------------------------------------------------------------------------------------------------
inline unsigned int NSBPass::GetComputeThreadGroupCountX() const
{
    return m_uiThreadGroupCountX;
}

//------------------------------------------------------------------------------------------------
inline unsigned int NSBPass::GetComputeThreadGroupCountY() const
{
    return m_uiThreadGroupCountY;
}

//------------------------------------------------------------------------------------------------
inline unsigned int NSBPass::GetComputeThreadGroupCountZ() const
{
    return m_uiThreadGroupCountZ;
}

//------------------------------------------------------------------------------------------------
inline NSBUserDefinedDataSet* NSBPass::GetUserDefinedDataSet() const
{
    return m_spUserDefinedDataSet;
}

//------------------------------------------------------------------------------------------------
inline void NSBPass::SetUserDefinedDataSet(NSBUserDefinedDataSet* pkUDDSet)
{
    m_spUserDefinedDataSet = pkUDDSet;
}

//------------------------------------------------------------------------------------------------
inline unsigned int NSBPass::GetVertexConstantMapCount() const
{
    return GetConstantMapCount(NiGPUProgram::PROGRAM_VERTEX);
}

//------------------------------------------------------------------------------------------------
inline unsigned int NSBPass::GetGeometryConstantMapCount() const
{
    return GetConstantMapCount(NiGPUProgram::PROGRAM_GEOMETRY);
}

//------------------------------------------------------------------------------------------------
inline unsigned int NSBPass::GetPixelConstantMapCount() const
{
    return GetConstantMapCount(NiGPUProgram::PROGRAM_PIXEL);
}

//------------------------------------------------------------------------------------------------
inline unsigned int NSBPass::GetConstantMapCount(NiGPUProgram::ProgramType eType) const
{
    EE_ASSERT((int)eType < (int)NSBConstantMap::NSB_SHADER_TYPE_COUNT);
    return m_akShaderConstantMaps[eType].GetSize();
}

//------------------------------------------------------------------------------------------------
inline NiStreamOutSettings& NSBPass::GetStreamOutSettings()
{
    return m_kStreamOutSettings;
}

//------------------------------------------------------------------------------------------------
