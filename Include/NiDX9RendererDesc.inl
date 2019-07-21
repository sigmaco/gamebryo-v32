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
// NVPerfHUD adapter functions
//--------------------------------------------------------------------------------------------------
inline bool NiDX9RendererDesc::GetNVPerfHUDSupport()
{
    return m_bSupportsNVPerfHUD;
}

//--------------------------------------------------------------------------------------------------
inline bool NiDX9RendererDesc::GetDefaultNVPerfHUDSetting()
{
    return m_bSupportsNVPerfHUD && m_pkSettings->m_bNVPerfHUD;
}

//--------------------------------------------------------------------------------------------------
// Device functions
//--------------------------------------------------------------------------------------------------
inline bool NiDX9RendererDesc::IsDeviceAvailable(bool bRefDevice)
{
    const NiDX9DeviceDesc* pkDev = m_pkAdapterDesc->GetDevice(
        bRefDevice ? D3DDEVTYPE_REF : D3DDEVTYPE_HAL);

    return pkDev != NULL;
}

//--------------------------------------------------------------------------------------------------
inline bool NiDX9RendererDesc::GetDefaultDevice()
{
    SelectDevice(m_pkSettings->m_bRefRast);
    return m_pkSettings->m_bRefRast;
}

//--------------------------------------------------------------------------------------------------
inline bool NiDX9RendererDesc::IsPureDeviceAvailable()
{
    // Disable pure checkbox when NVPerfHUD selected
    if (m_pkSettings->m_bNVPerfHUD)
        return false;

    // Pure can be selected only with HAL device
    if (m_pkSettings->m_bRefRast)
        return false;
    else
        return true;
}

//--------------------------------------------------------------------------------------------------
inline bool NiDX9RendererDesc::GetDefaultPureDevice()
{
    if (!IsPureDeviceAvailable())
        return false;

    return m_pkSettings->m_bPureDevice;
}

//--------------------------------------------------------------------------------------------------
inline void NiDX9RendererDesc::SelectPureDevice(bool bPure)
{
    if (!IsPureDeviceAvailable())
        bPure = false;

    m_pkSettings->m_bPureDevice = bPure;
}

//--------------------------------------------------------------------------------------------------
// VertexProcessing functions
//--------------------------------------------------------------------------------------------------
inline bool NiDX9RendererDesc::IsVertexProcessingAvailable()
{
    // All VertexProcessing types can be set for both HAL and REF in DX9
    // The exception is selected pure device and NVPerfHUD selection
    if (GetDefaultPureDevice() || m_pkSettings->m_bNVPerfHUD)
        return false;
    else
        return true;
}

//--------------------------------------------------------------------------------------------------
inline NiRendererSettings::VertexProcessing
    NiDX9RendererDesc::GetDefaultVertexProcessing()
{
    if (!IsVertexProcessingAvailable())
        return NiRendererSettings::VERTEX_UNSUPPORTED;

    return m_pkSettings->m_eVertexProcessing;
}

//--------------------------------------------------------------------------------------------------
inline void NiDX9RendererDesc::SelectVertexProcessing (
    NiRendererSettings::VertexProcessing eVertex)
{
    if (eVertex == NiRendererSettings::VERTEX_HARDWARE ||
        eVertex == NiRendererSettings::VERTEX_MIXED ||
        eVertex == NiRendererSettings::VERTEX_SOFTWARE)
    {
        m_pkSettings->m_eVertexProcessing = eVertex;
    }
}

//--------------------------------------------------------------------------------------------------
// Windowed mode functions
//--------------------------------------------------------------------------------------------------
inline void NiDX9RendererDesc::SelectWindowedMode(bool bFullscreen)
{
    if (!bFullscreen && !CanRenderWindowed())
        bFullscreen = true;

    m_pkSettings->m_bFullscreen = bFullscreen;
}

//--------------------------------------------------------------------------------------------------
inline bool NiDX9RendererDesc::CanRenderWindowed()
{
    return m_pkDeviceDesc->CanRenderWindowed();
}

//--------------------------------------------------------------------------------------------------
inline bool NiDX9RendererDesc::GetDefaultWindowedMode()
{
    SelectWindowedMode(m_pkSettings->m_bFullscreen);
    return m_pkSettings->m_bFullscreen;
}

//--------------------------------------------------------------------------------------------------
// Resolution functions
//--------------------------------------------------------------------------------------------------
inline bool NiDX9RendererDesc::IsWideScreenMode(
    const NiDX9AdapterDesc::ModeDesc* pkMode) const
{
    float fAspect = (float)pkMode->m_uiWidth / (float)pkMode->m_uiHeight;

    if (fAspect > 1.37f)    // Greater than Academy Aperture aspect ratio
        return true;

    return false;
}

//--------------------------------------------------------------------------------------------------
inline void NiDX9RendererDesc::SetResolutionFilter(
    ResolutionFilters eResFilter)
{
    if (eResFilter != RESFILTER_NORMAL && eResFilter != RESFILTER_WIDE)
        eResFilter = RESFILTER_ALL;

    m_eResolutionFilter = eResFilter;

    BuildResolutionList();
}

//--------------------------------------------------------------------------------------------------
