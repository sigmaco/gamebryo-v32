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
#ifndef EE_D3D11SYSTEMDESC_H
#define EE_D3D11SYSTEMDESC_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

#include <efd/CriticalSection.h>
#include <efd/SmartPointer.h>
#include <NiRefObject.h>
#include <NiTArray.h>

namespace ecr
{

class D3D11DeviceDesc;
class D3D11OutputDesc;
class D3D11AdapterDesc;
class D3D11SystemDesc;

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11SystemDesc
/// class.
typedef efd::SmartPointer<D3D11SystemDesc> D3D11SystemDescPtr;

typedef HRESULT (WINAPI *EE_LPCREATEDXGIFACTORY)(REFIID, void**);

//------------------------------------------------------------------------------------------------
/**
    D3D11SystemDesc creates and maintains a description of the current system.

    D3D11SystemDesc exposes all of the adapters that are installed and configured in the machine. 
    Its main purpose is to serve as a container class for all of the system's Gamebryo adapter 
    descriptors. See the notes below for a hierarchy diagram of the classes that are attached to 
    this system descriptor.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11SystemDesc : public NiRefObject
{
public:
    /// Return the current system desc.
    static void GetSystemDesc(D3D11SystemDescPtr& spSystemDesc);

    /// Return whether the enumeration of adapters, devices, and outputs is valid.
    efd::Bool IsEnumerationValid() const;
    /// Start an enumeration of adapters, devices, and outputs.
    efd::Bool Enumerate();

    /// Return the number of adapters on the system.
    efd::UInt32 GetAdapterCount() const;
    /// Return a description of the adapter with the specified index.
    const D3D11AdapterDesc* GetAdapterDesc(efd::UInt32 index) const;

    /// Return the IDXGIFactory.
    IDXGIFactory* GetFactory() const;
    /// Return the IDXGIAdapter with the specified index.
    IDXGIAdapter* GetAdapter(efd::UInt32 index) const;

protected:
    /// Hidden constructor
    D3D11SystemDesc();
    /// Destructor
    virtual ~D3D11SystemDesc();

    /// Load the DXGI library.
    efd::Bool LoadDXGI();
    /// Release the DXGI library.
    efd::Bool ReleaseDXGI();

    /// Create a IDXGIFactory.
    efd::Bool CreateFactory();
    /// Release the IDXGIFactory.
    efd::Bool ReleaseFactory();

    /// Enumerate the adapters.
    efd::Bool EnumerateAdapters();
    /// Release the adapter descriptions.
    efd::Bool ReleaseAdapters();

    NiTPrimitiveArray<D3D11AdapterDesc*> m_adapters;

    static D3D11SystemDesc* ms_pSystemDesc;
    static efd::CriticalSection ms_criticalSection;

    HINSTANCE m_hDXGI;
    EE_LPCREATEDXGIFACTORY m_pCreateDXGIFactoryFunction;
    IDXGIFactory* m_pFactory;

    efd::Bool m_isEnumerationValid;
};

//------------------------------------------------------------------------------------------------
/**
    D3D11AdapterDesc describes a display adapter on the current system.

    D3D11AdapterDesc is a descriptor of the capabilities of a piece of 3D rendering hardware. 
    It describes the supported display devices attached to the adapter (as D3D11OutputDesc 
    objects), as well as the various supported driver types (as D3D11DeviceDesc objects).
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11AdapterDesc : public efd::MemObject
{
public:
    /// Return a descriptor of the hardware device.
    const D3D11DeviceDesc* GetHWDevice() const;
    /// Return a descriptor of the reference device.
    const D3D11DeviceDesc* GetRefDevice() const;
    /// Return a descriptor of the WARP device.
    const D3D11DeviceDesc* GetWARPDevice() const;

    /// Return the number of display devices attached to the adapter.
    efd::UInt32 GetOutputCount() const;
    /// Return a description of the display device at the given index.
    const D3D11OutputDesc* GetOutputDesc(efd::UInt32 index) const;
    /// Returns the DXGI_ADAPTER_DESC that describes this adapter.
    const DXGI_ADAPTER_DESC* GetDesc() const;

    /// Returns the index in the D3D11SystemDesc of this D3D11AdapterDesc.
    efd::UInt32 GetIndex() const;

    /// Returns whether this adapter is the one to use with NVIDIA's PerfHUD tool.
    efd::Bool IsPerfHUD() const;

protected:
    /// Hidden constructor.
    D3D11AdapterDesc();
    /// Destructor.
    ~D3D11AdapterDesc();

    efd::Bool EnumerateDevices(IDXGIFactory* factory);
    efd::Bool EnumerateOutputs(IDXGIFactory* factory);

    efd::UInt32 m_index;

    DXGI_ADAPTER_DESC m_adapterDesc;

    NiTPrimitiveArray<D3D11OutputDesc*> m_outputs;

    D3D11DeviceDesc* m_pHWDevice;
    D3D11DeviceDesc* m_pRefDevice;
    D3D11DeviceDesc* m_pWARPDevice;

    efd::Bool m_isPerfHUD;

    friend class D3D11SystemDesc;
};

//------------------------------------------------------------------------------------------------
/**
    D3D11DeviceDesc describes a rendering device on the current system.

    D3D11DeviceDesc reports the feature level and multisample capabilities of the device.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11DeviceDesc : public efd::MemObject
{
public:
    /// Return the driver type for this device.
    D3D_DRIVER_TYPE GetDeviceType() const;
    /// Return the feature level for this device.
    D3D_FEATURE_LEVEL GetFeatureLevel() const;

    /// Returns the highest supported multisample count on the device
    efd::UInt32 GetHighestMultisampleCount() const;
    /** 
        Returns the number of quality levels supported for a multisample count.
        
        @param samples Multisample count to query
        @param qualityLevels Outputs the number of supported quality levels.
        @return Whether the sample count is supported.
    */
    efd::Bool GetMultisampleSupport(
        efd::UInt32 samples,
        efd::UInt32& qualityLevels) const;

protected:
    /// Hidden constructor.
    D3D11DeviceDesc();
    /// Destructor.
    ~D3D11DeviceDesc();

    D3D11AdapterDesc* m_pAdapter;
    D3D_DRIVER_TYPE m_deviceType;
    D3D_FEATURE_LEVEL m_featureLevel;

    efd::UInt32 m_msQualities[D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT];
    efd::UInt32 m_highestMultisampleCount;

    friend class D3D11AdapterDesc;
};

//------------------------------------------------------------------------------------------------
/**
    D3D11OutputDesc describes a display device on the current system.

    D3D11OutputDesc reports the supported display modes that the output device can handle.
*/

class EE_ECRD3D11RENDERER_ENTRY D3D11OutputDesc : public efd::MemObject
{
public:
    /// Returns the DXGI_OUTPUT_DESC that describes this output. 
    const DXGI_OUTPUT_DESC* GetDesc() const;
    /// Returns the number of display modes that are supported by this output device.
    efd::UInt32 GetDisplayModeCount() const;
    /// Returns the array of DXGI_MODE_DESC structures that are supported by this output device.
    const DXGI_MODE_DESC* GetDisplayModeArray() const;

    /// Returns the IDXGIOutput represented by this D3D11OutputDesc.
    IDXGIOutput* GetOutput() const;
    /// Returns the index in the D3D11AdapterDesc of this D3D11OutputDesc.
    efd::UInt32 GetIndex() const;

protected:
    /// Hidden constructor.
    D3D11OutputDesc();
    /// Destructor.
    ~D3D11OutputDesc();

    /// Enumerate the display modes.
    efd::Bool EnumerateDisplayModes();
    efd::UInt32 m_index;

    D3D11AdapterDesc* m_pAdapter;
    IDXGIOutput* m_pOutput;

    DXGI_OUTPUT_DESC m_outputDesc;

    DXGI_MODE_DESC* m_pDisplayModes;
    efd::UInt32 m_displayModeCount;

    friend class D3D11AdapterDesc;
};

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.

#endif // EE_D3D11SYSTEMDESC_H
