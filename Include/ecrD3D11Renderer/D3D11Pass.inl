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

namespace ecr
{

//------------------------------------------------------------------------------------------------
inline D3D11Pass::ResourceSource::ResourceSource() :
    m_dimension(RESOURCE_SOURCE_INVALID)
{
    // Rely on efd::FixedString and NiSmartPointer constructors to NULL out class members.
}

//------------------------------------------------------------------------------------------------
inline D3D11Pass::ResourceSource::ResourceSource(D3D11Pass::ResourceSource& resourceSource) :
    m_resourceName(resourceSource.m_resourceName)
{
    switch (resourceSource.m_dimension)
    {
    case RESOURCE_SOURCE_TEXTURE_MAP_FLAGS:
        SetGamebryoMapFlags(resourceSource.m_gamebryoMapFlags);
        SetCachedResource(resourceSource.m_spResource);
        break;
    case RESOURCE_SOURCE_OBJECT_FLAGS:
        SetTextureObjectFlags(resourceSource.m_textureObjectFlags);
        SetCachedResource(resourceSource.m_spResource);
        break;
    case RESOURCE_SOURCE_RESOURCE_POINTER:
        SetDirectResource(resourceSource.m_spResource);
        break;
    default:
        m_dimension = RESOURCE_SOURCE_INVALID;
    }
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::ResourceSource::SetName(const efd::FixedString& name)
{
    m_resourceName = name;
}

//------------------------------------------------------------------------------------------------
inline const efd::FixedString& D3D11Pass::ResourceSource::GetName() const
{
    return m_resourceName;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::ResourceSource::SetGamebryoMapFlags(efd::UInt32 gamebryoMapFlags)
{
    m_dimension = RESOURCE_SOURCE_TEXTURE_MAP_FLAGS;
    m_gamebryoMapFlags = gamebryoMapFlags;
    m_spResource = 0;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::ResourceSource::SetTextureObjectFlags(efd::UInt16 objectFlags)
{
    m_dimension = RESOURCE_SOURCE_OBJECT_FLAGS;
    m_textureObjectFlags = objectFlags;
    m_spResource = 0;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::ResourceSource::SetDirectResource(NiTexture* pTexture)
{
    m_dimension = RESOURCE_SOURCE_RESOURCE_POINTER;
    m_spResource = pTexture;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::ResourceSource::SetCachedResource(NiTexture* pTexture)
{
    EE_ASSERT(m_dimension != RESOURCE_SOURCE_RESOURCE_POINTER || m_spResource == pTexture);
    m_spResource = pTexture;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Pass::ResourceSource::GetGamebryoMapFlags() const
{
    if (m_dimension == RESOURCE_SOURCE_TEXTURE_MAP_FLAGS)
        return m_gamebryoMapFlags;
    return 0;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt16 D3D11Pass::ResourceSource::GetTextureObjectFlags() const
{
    if (m_dimension == RESOURCE_SOURCE_OBJECT_FLAGS)
        return m_textureObjectFlags;
    return NiTextureStage::TSOTF_IGNORE;
}

//------------------------------------------------------------------------------------------------
inline NiTexture* D3D11Pass::ResourceSource::GetDirectResource() const
{
    if (m_dimension == RESOURCE_SOURCE_RESOURCE_POINTER)
        return m_spResource;
    return NULL;
}

//------------------------------------------------------------------------------------------------
inline NiTexture* D3D11Pass::ResourceSource::GetCachedResource() const
{
    return m_spResource;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Pass::GetConstantMapCount() const
{
    return m_shaderConstantMapArray.GetSize();
}

//------------------------------------------------------------------------------------------------
inline D3D11ShaderConstantMap* D3D11Pass::GetConstantMap(efd::UInt32 index) const
{
    if (index < m_shaderConstantMapArray.GetSize())
        return m_shaderConstantMapArray.GetAt(index);
    else
        return NULL;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Pass::AddConstantMap(D3D11ShaderConstantMap* pSCMVertex)
{
    return m_shaderConstantMapArray.Add(pSCMVertex);
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::RemoveConstantMap(efd::UInt32 index)
{
    m_shaderConstantMapArray.RemoveAt(index);
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetVertexShaderProgramFileName() const
{
    return m_pVertexShaderProgramFile;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetVertexShaderProgramFileName(
    const efd::Char* pProgramFile)
{
    EE_FREE(m_pVertexShaderProgramFile);
    m_pVertexShaderProgramFile = 0;

    if (pProgramFile && pProgramFile[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pProgramFile) + 1;
        m_pVertexShaderProgramFile = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pVertexShaderProgramFile);

        efd::Strcpy(m_pVertexShaderProgramFile, stringLen, pProgramFile);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetVertexShaderProgramEntryPoint() const
{
    return m_pVertexShaderEntryPoint;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetVertexShaderProgramEntryPoint(
    const efd::Char* pEntryPoint)
{
    EE_FREE(m_pVertexShaderEntryPoint);
    m_pVertexShaderEntryPoint = 0;

    if (pEntryPoint && pEntryPoint[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pEntryPoint) + 1;
        m_pVertexShaderEntryPoint = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pVertexShaderEntryPoint);

        efd::Strcpy(m_pVertexShaderEntryPoint, stringLen, pEntryPoint);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetVertexShaderProgramShaderTarget() const
{
    return m_pVertexShaderTarget;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetVertexShaderProgramShaderTarget(
    const efd::Char* pShaderTarget)
{
    EE_FREE(m_pVertexShaderTarget);
    m_pVertexShaderTarget = 0;

    if (pShaderTarget && pShaderTarget[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pShaderTarget) + 1;
        m_pVertexShaderTarget = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pVertexShaderTarget);

        efd::Strcpy(m_pVertexShaderTarget, stringLen, pShaderTarget);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetHullShaderProgramFileName() const
{
    return m_pHullShaderProgramFile;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetHullShaderProgramFileName(
    const efd::Char* pProgramFile)
{
    EE_FREE(m_pHullShaderProgramFile);
    m_pHullShaderProgramFile = 0;

    if (pProgramFile && pProgramFile[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pProgramFile) + 1;
        m_pHullShaderProgramFile = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pHullShaderProgramFile);

        efd::Strcpy(m_pHullShaderProgramFile, stringLen, pProgramFile);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetHullShaderProgramEntryPoint() const
{
    return m_pHullShaderEntryPoint;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetHullShaderProgramEntryPoint(
    const efd::Char* pEntryPoint)
{
    EE_FREE(m_pHullShaderEntryPoint);
    m_pHullShaderEntryPoint = 0;

    if (pEntryPoint && pEntryPoint[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pEntryPoint) + 1;
        m_pHullShaderEntryPoint = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pHullShaderEntryPoint);

        efd::Strcpy(m_pHullShaderEntryPoint, stringLen, pEntryPoint);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetHullShaderProgramShaderTarget() const
{
    return m_pHullShaderTarget;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetHullShaderProgramShaderTarget(
    const efd::Char* pShaderTarget)
{
    EE_FREE(m_pHullShaderTarget);
    m_pHullShaderTarget = 0;

    if (pShaderTarget && pShaderTarget[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pShaderTarget) + 1;
        m_pHullShaderTarget = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pHullShaderTarget);

        efd::Strcpy(m_pHullShaderTarget, stringLen, pShaderTarget);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetDomainShaderProgramFileName() const
{
    return m_pDomainShaderProgramFile;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetDomainShaderProgramFileName(
    const efd::Char* pProgramFile)
{
    EE_FREE(m_pDomainShaderProgramFile);
    m_pDomainShaderProgramFile = 0;

    if (pProgramFile && pProgramFile[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pProgramFile) + 1;
        m_pDomainShaderProgramFile = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pDomainShaderProgramFile);

        efd::Strcpy(m_pDomainShaderProgramFile, stringLen, pProgramFile);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetDomainShaderProgramEntryPoint() const
{
    return m_pDomainShaderEntryPoint;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetDomainShaderProgramEntryPoint(
    const efd::Char* pEntryPoint)
{
    EE_FREE(m_pDomainShaderEntryPoint);
    m_pDomainShaderEntryPoint = 0;

    if (pEntryPoint && pEntryPoint[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pEntryPoint) + 1;
        m_pDomainShaderEntryPoint = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pDomainShaderEntryPoint);

        efd::Strcpy(m_pDomainShaderEntryPoint, stringLen, pEntryPoint);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetDomainShaderProgramShaderTarget() const
{
    return m_pDomainShaderTarget;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetDomainShaderProgramShaderTarget(
    const efd::Char* pShaderTarget)
{
    EE_FREE(m_pDomainShaderTarget);
    m_pDomainShaderTarget = 0;

    if (pShaderTarget && pShaderTarget[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pShaderTarget) + 1;
        m_pDomainShaderTarget = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pDomainShaderTarget);

        efd::Strcpy(m_pDomainShaderTarget, stringLen, pShaderTarget);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetGeometryShaderProgramFileName() const
{
    return m_pGeometryShaderProgramFile;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetGeometryShaderProgramFileName(
    const efd::Char* pProgramFile)
{
    EE_FREE(m_pGeometryShaderProgramFile);
    m_pGeometryShaderProgramFile = 0;

    if (pProgramFile && pProgramFile[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pProgramFile) + 1;
        m_pGeometryShaderProgramFile = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pGeometryShaderProgramFile);

        efd::Strcpy(m_pGeometryShaderProgramFile, stringLen, pProgramFile);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetGeometryShaderProgramEntryPoint() const
{
    return m_pGeometryShaderEntryPoint;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetGeometryShaderProgramEntryPoint(
    const efd::Char* pEntryPoint)
{
    EE_FREE(m_pGeometryShaderEntryPoint);
    m_pGeometryShaderEntryPoint = 0;

    if (pEntryPoint && pEntryPoint[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pEntryPoint) + 1;
        m_pGeometryShaderEntryPoint = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pGeometryShaderEntryPoint);

        efd::Strcpy(m_pGeometryShaderEntryPoint, stringLen, pEntryPoint);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetGeometryShaderProgramShaderTarget() const
{
    return m_pGeometryShaderTarget;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetGeometryShaderProgramShaderTarget(
    const efd::Char* pShaderTarget)
{
    EE_FREE(m_pGeometryShaderTarget);
    m_pGeometryShaderTarget = 0;

    if (pShaderTarget && pShaderTarget[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pShaderTarget) + 1;
        m_pGeometryShaderTarget = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pGeometryShaderTarget);

        efd::Strcpy(m_pGeometryShaderTarget, stringLen, pShaderTarget);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetPixelShaderProgramFileName() const
{
    return m_pPixelShaderProgramFile;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetPixelShaderProgramFileName(
    const efd::Char* pProgramFile)
{
    EE_FREE(m_pPixelShaderProgramFile);
    m_pPixelShaderProgramFile = 0;

    if (pProgramFile && pProgramFile[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pProgramFile) + 1;
        m_pPixelShaderProgramFile = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pPixelShaderProgramFile);

        efd::Strcpy(m_pPixelShaderProgramFile, stringLen, pProgramFile);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetPixelShaderProgramEntryPoint() const
{
    return m_pPixelShaderEntryPoint;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetPixelShaderProgramEntryPoint(
    const efd::Char* pEntryPoint)
{
    EE_FREE(m_pPixelShaderEntryPoint);
    m_pPixelShaderEntryPoint = 0;

    if (pEntryPoint && pEntryPoint[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pEntryPoint) + 1;
        m_pPixelShaderEntryPoint = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pPixelShaderEntryPoint);

        efd::Strcpy(m_pPixelShaderEntryPoint, stringLen, pEntryPoint);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetPixelShaderProgramShaderTarget() const
{
    return m_pPixelShaderTarget;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetPixelShaderProgramShaderTarget(
    const efd::Char* pShaderTarget)
{
    EE_FREE(m_pPixelShaderTarget);
    m_pPixelShaderTarget = 0;

    if (pShaderTarget && pShaderTarget[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pShaderTarget) + 1;
        m_pPixelShaderTarget = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pPixelShaderTarget);

        efd::Strcpy(m_pPixelShaderTarget, stringLen, pShaderTarget);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetComputeShaderProgramFileName() const
{
    return m_pComputeShaderProgramFile;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetComputeShaderProgramFileName(
    const efd::Char* pProgramFile)
{
    EE_FREE(m_pComputeShaderProgramFile);
    m_pComputeShaderProgramFile = 0;

    if (pProgramFile && pProgramFile[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pProgramFile) + 1;
        m_pComputeShaderProgramFile = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pComputeShaderProgramFile);

        efd::Strcpy(m_pComputeShaderProgramFile, stringLen, pProgramFile);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetComputeShaderProgramEntryPoint() const
{
    return m_pComputeShaderEntryPoint;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetComputeShaderProgramEntryPoint(
    const efd::Char* pEntryPoint)
{
    EE_FREE(m_pComputeShaderEntryPoint);
    m_pComputeShaderEntryPoint = 0;

    if (pEntryPoint && pEntryPoint[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pEntryPoint) + 1;
        m_pComputeShaderEntryPoint = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pComputeShaderEntryPoint);

        efd::Strcpy(m_pComputeShaderEntryPoint, stringLen, pEntryPoint);
    }
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetComputeShaderProgramShaderTarget() const
{
    return m_pComputeShaderTarget;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetComputeShaderProgramShaderTarget(
    const efd::Char* pShaderTarget)
{
    EE_FREE(m_pComputeShaderTarget);
    m_pComputeShaderTarget = 0;

    if (pShaderTarget && pShaderTarget[0] != '\0')
    {
        efd::UInt32 stringLen = efd::Strlen(pShaderTarget) + 1;
        m_pComputeShaderTarget = EE_ALLOC(efd::Char, stringLen);
        EE_ASSERT(m_pComputeShaderTarget);

        efd::Strcpy(m_pComputeShaderTarget, stringLen, pShaderTarget);
    }
}

//------------------------------------------------------------------------------------------------
inline efd::UInt8 D3D11Pass::GetShaderResourceCount() const
{
    return (efd::UInt8)m_shaderResources.GetSize();
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetStreamOutSettings(const NiStreamOutSettings& streamOutSettings)
{
    m_streamOutSettings = streamOutSettings;
}

//------------------------------------------------------------------------------------------------
inline NiStreamOutSettings& D3D11Pass::GetStreamOutSettings()
{
    return m_streamOutSettings;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetComputeThreadGroupCounts(
    efd::UInt32 threadGroupCountX, 
    efd::UInt32 threadGroupCountY, 
    efd::UInt32 threadGroupCountZ)
{
    m_threadGroupCountX = threadGroupCountX;
    m_threadGroupCountY = threadGroupCountY;
    m_threadGroupCountZ = threadGroupCountZ;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Pass::GetComputeThreadGroupCountX() const
{
    return m_threadGroupCountX;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Pass::GetComputeThreadGroupCountY() const
{
    return m_threadGroupCountY;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Pass::GetComputeThreadGroupCountZ() const
{
    return m_threadGroupCountZ;
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Pass::GetName() const
{
    return m_name;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetName(efd::Char* pName)
{
    efd::Strcpy(m_name, MAX_NAME_LENGTH, pName);
}

//------------------------------------------------------------------------------------------------
inline D3D11RenderStateGroup* D3D11Pass::GetRenderStateGroup() const
{
    return m_spRenderStateGroup;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetRenderStateGroup(D3D11RenderStateGroup* pRenderStateGroup)
{
    m_spRenderStateGroup = pRenderStateGroup;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetVertexShader(D3D11VertexShader* pVertexShader)
{
    m_shaders[NiGPUProgram::PROGRAM_VERTEX].SetShaderProgram(pVertexShader);
    if (pVertexShader)
        SetInputSignature(pVertexShader->GetShaderByteCode());
    else
        SetInputSignature(NULL);
}

//------------------------------------------------------------------------------------------------
inline D3D11VertexShader* D3D11Pass::GetVertexShader() const
{
    return NiVerifyStaticCast(
        D3D11VertexShader, 
        m_shaders[NiGPUProgram::PROGRAM_VERTEX].GetShaderProgram());
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetHullShader(D3D11HullShader* pHullShader)
{
    m_shaders[NiGPUProgram::PROGRAM_HULL].SetShaderProgram(pHullShader);
}

//------------------------------------------------------------------------------------------------
inline D3D11HullShader* D3D11Pass::GetHullShader() const
{
    return NiVerifyStaticCast(
        D3D11HullShader, 
        m_shaders[NiGPUProgram::PROGRAM_HULL].GetShaderProgram());
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetDomainShader(D3D11DomainShader* pDomainShader)
{
    m_shaders[NiGPUProgram::PROGRAM_DOMAIN].SetShaderProgram(pDomainShader);
}

//------------------------------------------------------------------------------------------------
inline D3D11DomainShader* D3D11Pass::GetDomainShader() const
{
    return NiVerifyStaticCast(
        D3D11DomainShader, 
        m_shaders[NiGPUProgram::PROGRAM_DOMAIN].GetShaderProgram());
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetGeometryShader(D3D11GeometryShader* pGeometryShader)
{
    m_shaders[NiGPUProgram::PROGRAM_GEOMETRY].SetShaderProgram(pGeometryShader);
}

//------------------------------------------------------------------------------------------------
inline D3D11GeometryShader* D3D11Pass::GetGeometryShader() const
{
    return NiVerifyStaticCast(
        D3D11GeometryShader, 
        m_shaders[NiGPUProgram::PROGRAM_GEOMETRY].GetShaderProgram());
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetPixelShader(D3D11PixelShader* pPixelShader)
{
    m_shaders[NiGPUProgram::PROGRAM_PIXEL].SetShaderProgram(pPixelShader);
}

//------------------------------------------------------------------------------------------------
inline D3D11PixelShader* D3D11Pass::GetPixelShader() const
{
    return NiVerifyStaticCast(
        D3D11PixelShader, 
        m_shaders[NiGPUProgram::PROGRAM_PIXEL].GetShaderProgram());
}

//------------------------------------------------------------------------------------------------
inline void D3D11Pass::SetComputeShader(D3D11ComputeShader* pComputeShader)
{
    m_shaders[NiGPUProgram::PROGRAM_COMPUTE].SetShaderProgram(pComputeShader);
}

//------------------------------------------------------------------------------------------------
inline D3D11ComputeShader* D3D11Pass::GetComputeShader() const
{
    return NiVerifyStaticCast(
        D3D11ComputeShader, 
        m_shaders[NiGPUProgram::PROGRAM_COMPUTE].GetShaderProgram());
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
