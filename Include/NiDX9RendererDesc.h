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
#ifndef NIDX9RENDERERDESC_H
#define NIDX9RENDERERDESC_H

#include "NiDX9RendererSetupLibType.h"
#include "NiBaseRendererDesc.h"
#include <NiDX9SystemDesc.h>

class NiRendererSettings;
class NiDX9AdapterDesc;
class NiDX9DeviceDesc;
class NiDX9SystemDesc;

// Direct3D 9 enumeration, settings selection and render creation routines
class NIDX9RENDERERSETUP_ENTRY NiDX9RendererDesc : public NiBaseRendererDesc
{
public:
    NiDX9RendererDesc(NiRendererSettings* pkSettings);

    // Initialization function
    virtual bool Initialize();

    // Indicates renderer that this object is responsible for setting up.
    virtual efd::SystemDesc::RendererID GetRendererID();

    // Adapter retrieving and selection
    virtual void GetAdapterList(NiTObjectArray<NiFixedString>& kList);
    virtual bool SelectAdapter(unsigned int uiAdaptIdx);
    virtual unsigned int GetDefaultAdapter();
    virtual bool GetNVPerfHUDSupport();
    virtual bool GetDefaultNVPerfHUDSetting();
    virtual bool SelectPerfHUDAdapter();

    // Device retrieving and selection
    virtual bool IsDeviceAvailable(bool bRefDevice);
    virtual void SelectDevice(bool bRefDevice);
    virtual bool GetDefaultDevice();

    // Device retrieve / selection options functions
    virtual bool IsPureDeviceAvailable();
    virtual bool GetDefaultPureDevice();
    virtual void SelectPureDevice(bool bPure);
    virtual bool IsVertexProcessingAvailable();
    virtual NiRendererSettings::VertexProcessing GetDefaultVertexProcessing();
    virtual void SelectVertexProcessing(
        NiRendererSettings::VertexProcessing eVertex);

    // Resolution functions
    virtual void SetResolutionFilter(ResolutionFilters eResFilter);
    virtual void GetResolutionList(NiTObjectArray<NiFixedString>& kList);
    virtual void SelectResolution(unsigned int uiResIdx);
    virtual unsigned int GetDefaultResolutionIdx();

    // Windowed mode functions
    virtual bool CanRenderWindowed();
    virtual void SelectWindowedMode(bool bFullscreen);
    virtual bool GetDefaultWindowedMode();

    // Multisample selection functions
    virtual unsigned int GetDefaultMultisample();
    virtual void SelectMultisample(unsigned int uiMultisample);
    virtual void GetMultisampleModeList(
        NiTObjectArray<NiFixedString>& kList);

    // Depth buffer format selection functions
    virtual unsigned int GetDefaultDSFormat();
    virtual void SelectDSFormat(unsigned int uiDSFmtIdx);
    virtual void GetDepthSurfaceFormatList(
        NiTObjectArray<NiFixedString>& kList);

    // Render target format selection functions
    virtual unsigned int GetDefaultRTFormat();
    virtual void SelectRTFormat(unsigned int uiRTFmtIdx);
    virtual void GetRenderTargetFormatList(
        NiTObjectArray<NiFixedString>& kList);

protected:
    // Pointers to current system, adapter and device descs for convenience
    const NiDX9SystemDesc* m_pkSystemDesc;
    const NiDX9AdapterDesc* m_pkAdapterDesc;
    const NiDX9DeviceDesc* m_pkDeviceDesc;

    // List of all adapters, NVPerfHUD presence flag
    NiTPrimitiveArray<const NiDX9AdapterDesc*> m_kAdapters;
    bool m_bSupportsNVPerfHUD;

    // List of supported display modes
    NiTPrimitiveArray<const NiDX9AdapterDesc::ModeDesc*> m_kModes;
    ResolutionFilters m_eResolutionFilter;

    // Supported multisamples, render target and depth surface formats
    NiTPrimitiveArray<NiDX9Renderer::FramebufferMode> m_kMultisamples;
    NiTPrimitiveArray<NiDX9Renderer::FrameBufferFormat> m_kRTFormats;
    NiTPrimitiveArray<NiDX9Renderer::DepthStencilFormat> m_kDSFormats;

    // Functions, that rebuild info, dependent on adapter and device selection
    void RebuildAdapterDependentInfo();
    void RebuildDeviceDependentInfo();

    // Enumerations routines
    bool BuildAdapterList();
    bool BuildResolutionList();
    bool BuildMultisamplesList();
    bool BuildRTFormatsList();
    bool BuildDSFormatsList();

    // Support routines
    bool IsWideScreenMode(const NiDX9AdapterDesc::ModeDesc* pkMode) const;
    const char* GetRTFormatName(
        NiDX9Renderer::FrameBufferFormat eFormat) const;
    const char* GetDSFormatName(
        NiDX9Renderer::DepthStencilFormat eFormat) const;
    bool IsDepthFormatSupportsStencil(
        NiDX9Renderer::DepthStencilFormat eFormat) const;
};

#include "NiDX9RendererDesc.inl"

#endif  // NIDX9RENDERERDESC_H