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
//--------------------------------------------------------------------------------------------------
// NSBShader inline functions
//--------------------------------------------------------------------------------------------------
inline const char* NSBShader::GetName()
{
    return m_pcName;
}

//--------------------------------------------------------------------------------------------------
inline const char* NSBShader::GetDescription()
{
    return m_pcDescription;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetMinPixelShaderVersion()
{
    return m_uiMinPixelShaderVersion;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetMaxPixelShaderVersion()
{
    return m_uiMaxPixelShaderVersion;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetMinComputeShaderVersion()
{
    return m_uiMinComputeShaderVersion;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetMaxComputeShaderVersion()
{
    return m_uiMaxComputeShaderVersion;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetMinVertexShaderVersion()
{
    return m_uiMinVertexShaderVersion;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetMaxVertexShaderVersion()
{
    return m_uiMaxVertexShaderVersion;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetMinUserVersion()
{
    return m_uiMinUserVersion;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetMaxUserVersion()
{
    return m_uiMaxUserVersion;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetMinFeatureLevel()
{
    return m_uiMinFeatureLevel;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetMaxFeatureLevel()
{
    return m_uiMaxFeatureLevel;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetPlatform()
{
    return m_uiPlatform;
}

//--------------------------------------------------------------------------------------------------
inline NSBAttributeTable* NSBShader::GetGlobalAttributeTable()
{
    return &m_kGlobalAttribTable;
}

//--------------------------------------------------------------------------------------------------
inline NSBAttributeTable* NSBShader::GetAttributeTable()
{
    return &m_kAttribTable;
}

//--------------------------------------------------------------------------------------------------
inline NSBObjectTable* NSBShader::GetObjectTable()
{
    return &m_kObjectTable;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMinVertexShaderVersionRequest(
    unsigned int uiVersion)
{
    m_uiMinVertexShaderVersionRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMaxVertexShaderVersionRequest(
    unsigned int uiVersion)
{
    m_uiMaxVertexShaderVersionRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMinGeometryShaderVersionRequest(
    unsigned int uiVersion)
{
    m_uiMinGeometryShaderVersionRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMaxGeometryShaderVersionRequest(
    unsigned int uiVersion)
{
    m_uiMaxGeometryShaderVersionRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMinPixelShaderVersionRequest(
    unsigned int uiVersion)
{
    m_uiMinPixelShaderVersionRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMaxPixelShaderVersionRequest(
    unsigned int uiVersion)
{
    m_uiMaxPixelShaderVersionRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMinComputeShaderVersionRequest(
    unsigned int uiVersion)
{
    m_uiMinComputeShaderVersionRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMaxComputeShaderVersionRequest(
    unsigned int uiVersion)
{
    m_uiMaxComputeShaderVersionRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMinUserVersionRequest(unsigned int uiVersion)
{
    m_uiMinUserVersionRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMaxUserVersionRequest(unsigned int uiVersion)
{
    m_uiMaxUserVersionRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMinFeatureLevelRequest(unsigned int uiVersion)
{
    m_uiMinFeatureLevelRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetMaxFeatureLevelRequest(unsigned int uiVersion)
{
    m_uiMaxFeatureLevelRequest = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::AddPlatform(unsigned int uiPlatformFlag)
{
    m_uiPlatform |= uiPlatformFlag;
}

//--------------------------------------------------------------------------------------------------
/***
inline void NSBShader::RemovePlatform(unsigned int uiPlatformFlag)
{
    m_uiPlatform &= ~uiPlatformFlag;
}
***/

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetPlatformRequest(unsigned int uiPlatform)
{
    m_uiPlatformRequest = uiPlatform;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::AddVertexShaderVersion(unsigned int uiVersion)
{
    if (m_uiMinVertexShaderVersion > uiVersion)
        m_uiMinVertexShaderVersion = uiVersion;
    if (m_uiMaxVertexShaderVersion < uiVersion)
        m_uiMaxVertexShaderVersion = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::AddGeometryShaderVersion(unsigned int uiVersion)
{
    if (m_uiMinGeometryShaderVersion > uiVersion)
        m_uiMinGeometryShaderVersion = uiVersion;
    if (m_uiMaxGeometryShaderVersion < uiVersion)
        m_uiMaxGeometryShaderVersion = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::AddPixelShaderVersion(unsigned int uiVersion)
{
    if (m_uiMinPixelShaderVersion > uiVersion)
        m_uiMinPixelShaderVersion = uiVersion;
    if (m_uiMaxPixelShaderVersion < uiVersion)
        m_uiMaxPixelShaderVersion = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::AddComputeShaderVersion(unsigned int uiVersion)
{
    if (m_uiMinComputeShaderVersion > uiVersion)
        m_uiMinComputeShaderVersion = uiVersion;
    if (m_uiMaxComputeShaderVersion < uiVersion)
        m_uiMaxComputeShaderVersion = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::AddUserVersion(unsigned int uiVersion)
{
    if (m_uiMinUserVersion > uiVersion)
        m_uiMinUserVersion = uiVersion;
    if (m_uiMaxUserVersion < uiVersion)
        m_uiMaxUserVersion = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::AddFeatureLevel(unsigned int uiVersion)
{
    if (m_uiMinFeatureLevel > uiVersion)
        m_uiMinFeatureLevel = uiVersion;
    if (m_uiMaxFeatureLevel < uiVersion)
        m_uiMaxFeatureLevel = uiVersion;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NSBShader::GetReadVersion()
{
    return ms_uiReadVersion;
}

//--------------------------------------------------------------------------------------------------
inline NSBUserDefinedDataSet* NSBShader::GetUserDefinedDataSet()
{
    return m_spUserDefinedDataSet;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::SetUserDefinedDataSet(NSBUserDefinedDataSet* pkUDDSet)
{
    m_spUserDefinedDataSet = pkUDDSet;
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::AddOutputStreamDescriptor(
    const NiOutputStreamDescriptor& kDescriptor)
{
    m_kOutputStreamDescriptors.Add(kDescriptor);
}

//--------------------------------------------------------------------------------------------------
inline void NSBShader::ClearOutputStreamDescriptors()
{
    m_kOutputStreamDescriptors.RemoveAll();
}

//--------------------------------------------------------------------------------------------------
inline const NiOutputStreamDescriptorArray&
NSBShader::GetOutputStreamDescriptors()
{
    return m_kOutputStreamDescriptors;
}

//--------------------------------------------------------------------------------------------------
