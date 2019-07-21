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

//--------------------------------------------------------------------------------------------------
inline efd::Bool D3D11RendererDesc::GetNVPerfHUDSupport()
{
    return m_supportsNVPerfHUD;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool D3D11RendererDesc::GetDefaultNVPerfHUDSetting()
{
    return m_supportsNVPerfHUD && m_pkSettings->m_bNVPerfHUD;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool D3D11RendererDesc::IsDeviceAvailable(efd::Bool bRefDevice)
{
    const ecr::D3D11DeviceDesc* pkDev = NULL;
    if (bRefDevice)
        pkDev = m_pAdapterDesc->GetRefDevice();
    else
        pkDev = m_pAdapterDesc->GetHWDevice();

    return pkDev != NULL;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool D3D11RendererDesc::GetDefaultDevice()
{
    SelectDevice(m_pkSettings->m_bRefRast);
    return m_pkSettings->m_bRefRast;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool D3D11RendererDesc::IsPureDeviceAvailable()
{
    // Disable pure device selection for D3D11
    return false;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool D3D11RendererDesc::GetDefaultPureDevice()
{
    if (!IsPureDeviceAvailable())
        return false;

    return m_pkSettings->m_bPureDevice;
}

//--------------------------------------------------------------------------------------------------
inline void D3D11RendererDesc::SelectPureDevice(efd::Bool bPure)
{
    if (!IsPureDeviceAvailable())
        bPure = false;

    m_pkSettings->m_bPureDevice = bPure;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool D3D11RendererDesc::IsVertexProcessingAvailable()
{
    // Disable VertexProcessing selection for D3D11
    return false;
}

//--------------------------------------------------------------------------------------------------
inline NiRendererSettings::VertexProcessing
    D3D11RendererDesc::GetDefaultVertexProcessing()
{
    return NiRendererSettings::VERTEX_UNSUPPORTED;
}

//--------------------------------------------------------------------------------------------------
inline void D3D11RendererDesc::SelectVertexProcessing(
    NiRendererSettings::VertexProcessing)
{
    // Do nothing for D3D11
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool D3D11RendererDesc::CanRenderWindowed()
{
    // D3D11 device always can render fullscreen and windowed
    return true;
}

//--------------------------------------------------------------------------------------------------
inline void D3D11RendererDesc::SelectWindowedMode(efd::Bool bFullscreen)
{
    m_pkSettings->m_bFullscreen = bFullscreen;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool D3D11RendererDesc::GetDefaultWindowedMode()
{
    return m_pkSettings->m_bFullscreen;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool D3D11RendererDesc::IsWideScreenMode(
    const DXGI_MODE_DESC* pkMode) const
{
    efd::Float32 fAspect = (efd::Float32)pkMode->Width / (efd::Float32)pkMode->Height;

    if (fAspect > 1.37f)    // Greater than Academy Aperture aspect ratio
        return true;

    return false;
}

//--------------------------------------------------------------------------------------------------
inline void D3D11RendererDesc::SetResolutionFilter(
    ResolutionFilters resolutionFilter)
{
    if (resolutionFilter != RESFILTER_NORMAL && resolutionFilter != RESFILTER_WIDE)
        resolutionFilter = RESFILTER_ALL;

    m_resolutionFilter = resolutionFilter;

    BuildResolutionList();
}

//--------------------------------------------------------------------------------------------------
inline void D3D11RendererDesc::SetFeatureLevel_11_0(efd::Bool enable)
{
    m_pkSettings->m_bD3D11FeatureLevel11_0 = enable;
}

//--------------------------------------------------------------------------------------------------
inline void D3D11RendererDesc::SetFeatureLevel_10_1(efd::Bool enable)
{
    m_pkSettings->m_bD3D11FeatureLevel10_1 = enable;
}

//--------------------------------------------------------------------------------------------------
inline void D3D11RendererDesc::SetFeatureLevel_10_0(efd::Bool enable)
{
    m_pkSettings->m_bD3D11FeatureLevel10_0 = enable;
}

//--------------------------------------------------------------------------------------------------
inline void D3D11RendererDesc::SetFeatureLevel_9_3(efd::Bool enable)
{
    m_pkSettings->m_bD3D11FeatureLevel9_3 = enable;
}

//--------------------------------------------------------------------------------------------------
inline void D3D11RendererDesc::SetFeatureLevel_9_2(efd::Bool enable)
{
    m_pkSettings->m_bD3D11FeatureLevel9_2 = enable;
}

//--------------------------------------------------------------------------------------------------

inline void D3D11RendererDesc::SetFeatureLevel_9_1(efd::Bool enable)
{
    m_pkSettings->m_bD3D11FeatureLevel9_1 = enable;
}
//--------------------------------------------------------------------------------------------------

}   // End namespace ecr.
