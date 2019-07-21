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
inline D3D_DRIVER_TYPE D3D11Renderer::GetD3D11DriverType(DriverType type) const
{
    return (D3D_DRIVER_TYPE)type;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Renderer::GetD3D11CreateDeviceFlags(efd::UInt32 createDeviceFlags) const
{
    return createDeviceFlags;
}

//------------------------------------------------------------------------------------------------
inline D3D_FEATURE_LEVEL D3D11Renderer::GetD3D11FeatureLevel(FeatureLevel featureLevel) const
{
    return (D3D_FEATURE_LEVEL)featureLevel;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Renderer::GetD3D11WindowAssociationFlags(
    efd::UInt32 windowAssociationFlags) const
{
    return windowAssociationFlags;
}

//------------------------------------------------------------------------------------------------
inline const D3D11ShaderLibraryVersion* D3D11Renderer::GetShaderLibraryVersion() const
{
    return &m_shaderLibraryVersion;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Renderer::GetDeviceThreadID() const
{
    return m_deviceThreadID;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11Renderer::SupportsMMX() const
{
    return m_supportsMMX;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11Renderer::SupportsSSE() const
{
    return m_supportsSSE;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11Renderer::SupportsSSE2() const
{
    return m_supportsSSE2;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Renderer::GetCreationParameters(CreationParameters& createParams) const
{
    createParams = m_initialCreateParameters;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Renderer::RemoveAllDeviceRemovedNotificationFuncs()
{
    m_deviceRemovedNotifyFuncs.RemoveAll();
    m_deviceRemovedNotifyFuncData.RemoveAll();
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Renderer::GetDeviceRemovedNotificationFuncCount() const
{
    return m_deviceRemovedNotifyFuncs.GetEffectiveSize();
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Renderer::GetDeviceRemovedNotificationFuncArrayCount() const
{
    return m_deviceRemovedNotifyFuncs.GetSize();
}

//------------------------------------------------------------------------------------------------
inline D3D11Renderer::DEVICEREMOVEDNOTIFYFUNC
D3D11Renderer::GetDeviceRemovedNotificationFunc(efd::UInt32 index) const
{
    return m_deviceRemovedNotifyFuncs.GetAt(index);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11Renderer::DoesFormatSupportFlag(DXGI_FORMAT format, efd::UInt32 flags) const
{
    return (m_formatSupportArray[(efd::UInt32)format] & flags) != 0;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Renderer::GetFormatSupportFlags(DXGI_FORMAT format) const
{
    return m_formatSupportArray[(efd::UInt32)format];
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Renderer::GetSyncInterval() const
{
    return m_syncInterval;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Renderer::SetSyncInterval(efd::UInt32 syncInterval)
{
    m_syncInterval = syncInterval;
}

//------------------------------------------------------------------------------------------------
inline D3D11DeviceState* D3D11Renderer::GetDeviceState() const
{
    return m_pDeviceState;
}

//------------------------------------------------------------------------------------------------
inline D3D11RenderStateManager* D3D11Renderer::GetRenderStateManager() const
{
    return m_pRenderStateManager;
}

//------------------------------------------------------------------------------------------------
inline D3D11ResourceManager* D3D11Renderer::GetResourceManager() const
{
    return m_pResourceManager;
}

//------------------------------------------------------------------------------------------------
inline D3D11ShaderConstantManager* D3D11Renderer::GetShaderConstantManager() const
{
    return m_pShaderConstantManager;
}

//------------------------------------------------------------------------------------------------
inline D3D11Renderer::FeatureLevel D3D11Renderer::GetFeatureLevel() const
{
    return (FeatureLevel)m_featureLevel;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Renderer::GetSupportedShaderTypeCount() const
{
    return m_supportedShaderProgramTypeCount;
}

//------------------------------------------------------------------------------------------------
inline NiGPUProgram::ProgramType D3D11Renderer::GetSupportedShaderType(efd::UInt32 index) const
{
    if (index > m_supportedShaderProgramTypeCount)
        return NiGPUProgram::PROGRAM_MAX;
    return m_supportedShaderProgramTypes[index];
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11Renderer::GetMaxComputeShader() const
{
    return m_maxComputeShaderVersion;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Renderer::InvalidateDeviceState()
{
    if (m_pDeviceState)
        m_pDeviceState->InvalidateDeviceState();
}

//------------------------------------------------------------------------------------------------
inline ID3D11Device* D3D11Renderer::GetD3D11Device() const
{
    return m_pD3D11Device;
}

//------------------------------------------------------------------------------------------------
inline ID3D11DeviceContext* D3D11Renderer::GetImmediateD3D11DeviceContext() const
{
    return m_pImmediateD3D11DeviceContext;
}

//------------------------------------------------------------------------------------------------
inline ID3D11DeviceContext* D3D11Renderer::GetCurrentD3D11DeviceContext() const
{
    return m_pCurrentD3D11DeviceContext;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11Renderer::ReleaseResources()
{
    m_spDefaultRenderTargetGroup = NULL;
    return true;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Renderer::RegisterD3D11Shader(D3D11ShaderInterface* pD3D11Shader)
{
    m_activeShaders.AddHead(pD3D11Shader);
}

//------------------------------------------------------------------------------------------------
inline void D3D11Renderer::ReleaseD3D11Shader(D3D11ShaderInterface* pD3D11Shader)
{
    m_activeShaders.Remove(pD3D11Shader);
}

//------------------------------------------------------------------------------------------------
inline void D3D11Renderer::PurgeD3D11Shader(D3D11ShaderInterface* pD3D11Shader)
{
    pD3D11Shader->DestroyRendererData();

    m_activeShaders.Remove(pD3D11Shader);
}

//------------------------------------------------------------------------------------------------
inline void D3D11Renderer::PurgeAllD3D11Shaders()
{
    while (!m_activeShaders.IsEmpty())
        PurgeD3D11Shader(m_activeShaders.GetHead());
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Renderer::GetVertexShaderProfile() const
{
    return m_pVertexShaderVersionString;
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Renderer::GetHullShaderProfile() const
{
    return m_pHullShaderVersionString;
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Renderer::GetDomainShaderProfile() const
{
    return m_pDomainShaderVersionString;
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Renderer::GetGeometryShaderProfile() const
{
    return m_pGeometryShaderVersionString;
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Renderer::GetPixelShaderProfile() const
{
    return m_pPixelShaderVersionString;
}

//------------------------------------------------------------------------------------------------
inline const efd::Char* D3D11Renderer::GetComputeShaderProfile() const
{
    return m_pComputeShaderVersionString;
}

//------------------------------------------------------------------------------------------------
inline const XMMATRIX& D3D11Renderer::GetProjectionMatrix() const
{
    return m_d3dProj;
}

//------------------------------------------------------------------------------------------------
inline const XMMATRIX& D3D11Renderer::GetViewMatrix() const
{
    return m_d3dView;
}

//------------------------------------------------------------------------------------------------
inline const XMMATRIX& D3D11Renderer::GetInverseViewMatrix() const
{
    return m_invView;
}

//------------------------------------------------------------------------------------------------
inline const XMMATRIX& D3D11Renderer::GetWorldMatrix() const
{
    return m_d3dModel;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Renderer::GetCameraNearAndFar(
    efd::Float32& nearPlane, 
    efd::Float32& farPlane) const
{
    nearPlane = m_currentFrustum.m_fNear;
    farPlane = m_currentFrustum.m_fFar;
}

//------------------------------------------------------------------------------------------------
inline void D3D11Renderer::SetModelTransform(const NiTransform& kWorld)
{
    D3D11Utility::GetD3DFromNi(m_d3dModel, kWorld);
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
