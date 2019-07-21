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
// NVPerfHUD functions
//--------------------------------------------------------------------------------------------------
inline bool NiD3D10RendererDesc::GetNVPerfHUDSupport()
{
    return m_bSupportsNVPerfHUD;
}

//--------------------------------------------------------------------------------------------------
inline bool NiD3D10RendererDesc::GetDefaultNVPerfHUDSetting()
{
    return m_bSupportsNVPerfHUD && m_pkSettings->m_bNVPerfHUD;
}

//--------------------------------------------------------------------------------------------------
// Device functions
//--------------------------------------------------------------------------------------------------
inline bool NiD3D10RendererDesc::IsDeviceAvailable(bool bRefDevice)
{
    const NiD3D10DeviceDesc* pkDev;
    if (bRefDevice)
        pkDev = m_pkAdapterDesc->GetRefDevice();
    else
        pkDev = m_pkAdapterDesc->GetHWDevice();

    return pkDev != NULL;
}

//--------------------------------------------------------------------------------------------------
inline bool NiD3D10RendererDesc::GetDefaultDevice()
{
    SelectDevice(m_pkSettings->m_bRefRast);
    return m_pkSettings->m_bRefRast;
}

//--------------------------------------------------------------------------------------------------
inline bool NiD3D10RendererDesc::IsPureDeviceAvailable()
{
    // Disable pure device selection for D3D10
    return false;
}

//--------------------------------------------------------------------------------------------------
inline bool NiD3D10RendererDesc::GetDefaultPureDevice()
{
    if (!IsPureDeviceAvailable())
        return false;

    return m_pkSettings->m_bPureDevice;
}

//--------------------------------------------------------------------------------------------------
inline void NiD3D10RendererDesc::SelectPureDevice(bool bPure)
{
    if (!IsPureDeviceAvailable())
        bPure = false;

    m_pkSettings->m_bPureDevice = bPure;
}

//--------------------------------------------------------------------------------------------------
// Dummy VertexProcessing functions for class interface compatibility
//--------------------------------------------------------------------------------------------------
inline bool NiD3D10RendererDesc::IsVertexProcessingAvailable()
{
    // Disable VertexProcessing selection for D3D10
    return false;
}

//--------------------------------------------------------------------------------------------------
inline NiRendererSettings::VertexProcessing
    NiD3D10RendererDesc::GetDefaultVertexProcessing()
{
    return NiRendererSettings::VERTEX_UNSUPPORTED;
}

//--------------------------------------------------------------------------------------------------
inline void NiD3D10RendererDesc::SelectVertexProcessing(
    NiRendererSettings::VertexProcessing)
{
    // Do nothing for D3D10
}

//--------------------------------------------------------------------------------------------------
// Windowed mode functions
//--------------------------------------------------------------------------------------------------
inline bool NiD3D10RendererDesc::CanRenderWindowed()
{
    // D3D10 device always can render fullscreen and windowed
    return true;
}

//--------------------------------------------------------------------------------------------------
inline void NiD3D10RendererDesc::SelectWindowedMode(bool bFullscreen)
{
    m_pkSettings->m_bFullscreen = bFullscreen;
}

//--------------------------------------------------------------------------------------------------
inline bool NiD3D10RendererDesc::GetDefaultWindowedMode()
{
    return m_pkSettings->m_bFullscreen;
}

//--------------------------------------------------------------------------------------------------
// Resolution functions
//--------------------------------------------------------------------------------------------------
inline bool NiD3D10RendererDesc::IsWideScreenMode(
    const DXGI_MODE_DESC* pkMode) const
{
    float fAspect = (float)pkMode->Width / (float)pkMode->Height;

    if (fAspect > 1.37f)    // Greater than Academy Aperture aspect ratio
        return true;

    return false;
}

//--------------------------------------------------------------------------------------------------
inline void NiD3D10RendererDesc::SetResolutionFilter(
    ResolutionFilters eResFilter)
{
    if (eResFilter != RESFILTER_NORMAL && eResFilter != RESFILTER_WIDE)
        eResFilter = RESFILTER_ALL;

    m_eResolutionFilter = eResFilter;

    BuildResolutionList();
}

//--------------------------------------------------------------------------------------------------
