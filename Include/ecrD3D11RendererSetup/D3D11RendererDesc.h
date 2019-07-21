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
#ifndef EE_D3D11RENDERERDESC_H
#define EE_D3D11RENDERERDESC_H

#include <ecrD3D11RendererSetup/ecrD3D11RendererSetupLibType.h>
#include <NiBaseRendererDesc.h>
#include <NiRendererSettings.h>

#include <ecrD3D11Renderer/D3D11SystemDesc.h>

namespace ecr
{

class ecr::D3D11AdapterDesc;
class ecr::D3D11DeviceDesc;
class ecr::D3D11SystemDesc;
class ecr::D3D11OutputDesc;

/**
    D3D11RendererDesc is the NiBaseRendererDesc that manages renderer settings for D3D11.

    This class defines an interface for communicating renderer settings to and from a 
    D3D11RendererOptionsView object. It provides a list of available renderer settings, 
    modifies those settings in response to user input, and saves the settings in an 
    NiRendererSettings object.
*/

class EE_ECRD3D11RENDERERSETUP_ENTRY D3D11RendererDesc : public NiBaseRendererDesc
{
public:

    /// @cond EMERGENT_INTERNAL

    /// @name Construction and Destruction
    //@{
    /// Constructs a new D3D11RendererDesc and initializes is settings from the provided
    /// NiRendererSettings object.
    D3D11RendererDesc(NiRendererSettings* pkSettings);
    //@}

    /// Initialize the dialog based on the current hardware settings and return whether or not
    /// the current configuration supports D3D11
    virtual efd::Bool Initialize();

    /// Returns which renderer this object is responsible for setting up.
    virtual efd::SystemDesc::RendererID GetRendererID();

    /// Return the list of adapters.
    virtual void GetAdapterList(NiTObjectArray<NiFixedString>& adapterList);
    /// Select a specific adapter.
    virtual efd::Bool SelectAdapter(efd::UInt32 adapterIndex);
    /// Return the default adapter index.
    virtual efd::UInt32 GetDefaultAdapter();
    /// Return whether NVIDIA's PerfHUD tool is currently active.
    virtual efd::Bool GetNVPerfHUDSupport();
    /// Return whether PerfHUD should be enabled by default.
    virtual efd::Bool GetDefaultNVPerfHUDSetting();
    /// Select the PerfHUD adapter.
    virtual efd::Bool SelectPerfHUDAdapter();

    /// Return the list of displays.
    virtual void GetDisplayList(NiTObjectArray<NiFixedString>& displayList);
    /// Select a specific display.
    virtual void SelectDisplay(efd::UInt32 displayIndex);
    /// Return the default display index.
    virtual efd::UInt32 GetDefaultDisplay();

    /// Return whether the hardware or reference device is available.
    virtual efd::Bool IsDeviceAvailable(efd::Bool refDevice);
    /// Select either the hardware or reference device.
    virtual void SelectDevice(efd::Bool isRefDevice);
    /// Return whether the default device is a reference device.
    virtual efd::Bool GetDefaultDevice();

    /// Return whether a pure device is available.
    virtual efd::Bool IsPureDeviceAvailable();
    /// Return whether the default device is a pure device.
    virtual efd::Bool GetDefaultPureDevice();
    /// Select whether the chosen device will be pure or not.
    virtual void SelectPureDevice(efd::Bool pure);
    /// Return whether software vertex processing is available.
    virtual efd::Bool IsVertexProcessingAvailable();
    /// Return the default vertex processing state.
    virtual NiRendererSettings::VertexProcessing GetDefaultVertexProcessing();
    /// Select the vertex processing state.
    virtual void SelectVertexProcessing (
        NiRendererSettings::VertexProcessing vertexProc);

    /// Set a of resolution filters
    virtual void SetResolutionFilter(ResolutionFilters resolutionFilter);
    /// Return the list of resoluction
    virtual void GetResolutionList(NiTObjectArray<NiFixedString>& resolutionList);
    /// Select a specific resolution.
    virtual void SelectResolution(efd::UInt32 resolutionIndex);
    /// Return the default resolution index.
    virtual efd::UInt32 GetDefaultResolutionIdx();

    /// Return whether windowed mode is available.
    virtual efd::Bool CanRenderWindowed();
    /// Select between windowed or fullscreen mode.
    virtual void SelectWindowedMode(efd::Bool fullscreen);
    /// Return whether the default mode is windowed or not.
    virtual efd::Bool GetDefaultWindowedMode();

    /// Return the default depth/stencil buffer format.
    virtual efd::UInt32 GetDefaultDSFormat();
    /// Select a specific depth/stencil buffer format.
    virtual void SelectDSFormat(efd::UInt32 dsFormatIndex);
    /// Return the list of supported depth/stencil formats.
    virtual void GetDepthSurfaceFormatList(
        NiTObjectArray<NiFixedString>& dsFormatList);

    /// Return the default render target buffer format.
    virtual efd::UInt32 GetDefaultRTFormat();
    /// Select a specific render target buffer format.
    virtual void SelectRTFormat(efd::UInt32 rtFormatIndex);
    /// Return the list of supported render target formats.
    virtual void GetRenderTargetFormatList(
        NiTObjectArray<NiFixedString>& rtFormatList);

    /// Return the default multisample state index.
    virtual efd::UInt32 GetDefaultMultisample();
    /// Select a specific multisample state index.
    virtual void SelectMultisample(efd::UInt32 msIndex);
    /// Return a list of supported multisample states.
    virtual void GetMultisampleModeList(
        NiTObjectArray<NiFixedString>& msModeList);

    //@{
    /// Feature level support
    inline void SetFeatureLevel_11_0(efd::Bool enable);
    inline void SetFeatureLevel_10_1(efd::Bool enable);
    inline void SetFeatureLevel_10_0(efd::Bool enable);
    inline void SetFeatureLevel_9_3(efd::Bool enable);
    inline void SetFeatureLevel_9_2(efd::Bool enable);
    inline void SetFeatureLevel_9_1(efd::Bool enable);
    //@}

    /// @endcond

protected:
    // Pointers to current system, adapter and device descs for convenience
    ecr::D3D11SystemDescPtr m_spSystemDesc;
    const ecr::D3D11AdapterDesc* m_pAdapterDesc;
    const ecr::D3D11DeviceDesc* m_pDeviceDesc;
    const ecr::D3D11OutputDesc* m_pOutputDesc;

    // List of all adapters, NVPerfHUD presence flag
    NiTPrimitiveArray<const ecr::D3D11AdapterDesc*> m_adapters;
    efd::Bool m_supportsNVPerfHUD;

    // List of all supported displays
    NiTPrimitiveArray<const ecr::D3D11OutputDesc*> m_displays;

    // List of supported display modes
    NiTPrimitiveArray<const DXGI_MODE_DESC*> m_modes;
    ResolutionFilters m_resolutionFilter;

    // Supported multisamples array. Higher 16 bits are count, lower - quality
    NiTPrimitiveArray<efd::UInt32> m_msModes;
    // Supported render target and depth surface formats
    NiTPrimitiveArray<DXGI_FORMAT> m_rtFormats;
    NiTPrimitiveArray<DXGI_FORMAT> m_dsFormats;

    // Functions, that rebuild info, dependent on adapter and device selection
    void RebuildAdapterDependentInfo();
    void RebuildDeviceDependentInfo();

    // Enumerations routines
    efd::Bool BuildAdapterList();
    efd::Bool BuildDisplayList();
    efd::Bool BuildResolutionList();
    efd::Bool BuildMultisamplesList();
    efd::Bool BuildRTFormatsList();
    efd::Bool BuildDSFormatsList();

    // Support routines
    efd::Bool IsWideScreenMode(const DXGI_MODE_DESC* pMode) const;
};

}   // End namespace ecr.

#include "D3D11RendererDesc.inl"

#endif // EE_D3D11RENDERERDESC_H