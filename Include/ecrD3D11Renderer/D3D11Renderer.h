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
#ifndef EE_D3D11RENDERER_H
#define EE_D3D11RENDERER_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D112DBufferData.h>
#include <ecrD3D11Renderer/D3D11Headers.h>
#include <ecrD3D11Renderer/D3D11DeviceState.h>
#include <ecrD3D11Renderer/D3D11MeshMaterialBinding.h>
#include <ecrD3D11Renderer/D3D11ShaderInterface.h>
#include <ecrD3D11Renderer/D3D11ShaderLibraryVersion.h>
#include <ecrD3D11Renderer/D3D11SystemDesc.h>
#include <ecrD3D11Renderer/D3D11Utility.h>

#include <NiTPointerMap.h>

#include <NiRenderer.h>
#include <NiRenderTargetGroup.h>

namespace ecr
{

/// @cond EMERGENT_INTERNAL

// D3D11 ID Number (Must be unique to all renderers).
enum { NI_D3D11_RENDER_ID = 11 };

typedef efd::SInt32 (WINAPI *EE_LPD3D11PERF_BEGINEVENT) (D3DCOLOR, LPCWSTR);
typedef efd::SInt32 (WINAPI *EE_LPD3D11PERF_ENDEVENT) (void);
typedef DWORD (WINAPI *EE_LPD3D11PERF_GETSTATUS) (void);
typedef HRESULT (WINAPI *EE_LPD3D10CREATEBLOB) (SIZE_T, LPD3D10BLOB*);

/// @endcond

class D3D11Renderer;
class D3D11DataStreamFactory;
class D3D11RenderStateManager;
class D3D11ResourceManager;
class D3D11ShaderConstantManager;

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11Renderer
/// class.
typedef efd::SmartPointer<D3D11Renderer> D3D11RendererPtr;

/**
    D3D11Renderer is the NiRenderer-derived class responsible for rendering through the D3D11 API.

    For details on the support of optional features those functions are declared in the NiRenderer
    base class, see the Feature and LImitations of the D3D11 Renderer documentation.
*/

class EE_ECRD3D11RENDERER_ENTRY D3D11Renderer : public NiRenderer
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    /// Destructor.
    virtual ~D3D11Renderer();
    //@}

    /// Mapping of D3D Driver type enumerations.
    enum DriverType
    {
        DRIVER_TYPE_UNKNOWN     = D3D_DRIVER_TYPE_UNKNOWN,
        DRIVER_TYPE_HARDWARE    = D3D_DRIVER_TYPE_HARDWARE,
        DRIVER_TYPE_REFERENCE   = D3D_DRIVER_TYPE_REFERENCE,
        DRIVER_TYPE_NULL        = D3D_DRIVER_TYPE_NULL,
        DRIVER_TYPE_SOFTWARE    = D3D_DRIVER_TYPE_SOFTWARE,
        DRIVER_TYPE_WARP        = D3D_DRIVER_TYPE_WARP
    };

    /// Mapping of D3D Create Device flags.
    enum CreateDeviceFlags
    {
        CREATE_DEVICE_SINGLETHREADED    = D3D11_CREATE_DEVICE_SINGLETHREADED,
        CREATE_DEVICE_DEBUG             = D3D11_CREATE_DEVICE_DEBUG,
        CREATE_DEVICE_SWITCH_TO_REF     = D3D11_CREATE_DEVICE_SWITCH_TO_REF,
        CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS  =
            D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS,
        CREATE_DEVICE_BGRA_SUPPORT      = D3D11_CREATE_DEVICE_BGRA_SUPPORT
    };

    /// Mapping of D3D feature level enumerations.
    enum FeatureLevel
    {
        FEATURE_LEVEL_9_1 = D3D_FEATURE_LEVEL_9_1,
        FEATURE_LEVEL_9_2 = D3D_FEATURE_LEVEL_9_2,
        FEATURE_LEVEL_9_3 = D3D_FEATURE_LEVEL_9_3,
        FEATURE_LEVEL_10_0 = D3D_FEATURE_LEVEL_10_0,
        FEATURE_LEVEL_10_1 = D3D_FEATURE_LEVEL_10_1,
        FEATURE_LEVEL_11_0 = D3D_FEATURE_LEVEL_11_0
    };

    /// Mapping of D3D window association flags.
    enum WindowAssociationFlags
    {
        WIND_ASN_NO_WINDOW_CHANGES  = DXGI_MWA_NO_WINDOW_CHANGES,
        WIND_ASN_NO_ALT_ENTER       = DXGI_MWA_NO_ALT_ENTER,
        WIND_ASN_NO_PRINT_SCREEN    = DXGI_MWA_NO_PRINT_SCREEN
    };

    /// Helper structure that contains all the parameters needed to create an ecr::D3D11Renderer
    struct EE_ECRD3D11RENDERER_ENTRY CreationParameters
    {
        /// @name Construction and Destruction
        //@{
        /**
            Default constructor.

            A renderer created with the default parameters in the CreationParameters struct will
            not have a default swap chain.
            
            The default arguments for each member of the struct are described below.
        */  
        CreationParameters();

        /// Constructor that associates the renderer with a specific window. 
        CreationParameters(HWND hWnd);
        //@}

        /**
            Adapter to use when creating the device. 
            
            Default value is 0. Index can be obtained from the D3D11AdapterDesc.
        */
        efd::UInt32 m_adapterIndex;

        /**
            Output to use when creating the default swap chain. 
            
            Default value is 0. Index can be obtained from the D3D11OutputDesc.
        */
        efd::UInt32 m_outputIndex;

        /**
            Type of D3D11 device to create.

            The default value is DRIVER_HARDWARE.
        */
        DriverType m_driverType;

        /**
            Array of feature levels to attempt to create.

            Default value is an array containing all feature levels, in descending order. D3D
            will attempt to create a device using the first feature level in the array, and if
            that fails, D3D will continue down the list until a feature level succeeds or the 
            end of the array is reached.
        */
        FeatureLevel* m_pFeatureLevels;
        /// Number of entries in the FeatureLevels array.
        efd::UInt32 m_featureLevelCount;

        /**
            Creation flags passed into D3D11CreateDevices as the Flags parameter.

            Default value is CREATE_DEVICE_DEBUG | CREATE_DEVICE_SINGLETHREADED for Debug 
            configurations, and CREATE_DEVICE_SINGLETHREADED for the remaining configurations.
        */
        efd::UInt32 m_createFlags;

        /**
            Indicates whether or not to create a default swap chain.

            Default value is true if a window is passed to the constructor, and false otherwise.
            If a default swap chain is not created, the application will need to create one.
        */
        efd::Bool m_createSwapChain;

        /**
            Indicates whether or not to create a default depth stencil buffer.

            Default value is true if a window is passed to the constructor, and false otherwise.
            If a default depth stencil buffer is not created, the application will need to create 
            one.
        */
        efd::Bool m_createDepthStencilBuffer;

        /**
            Indicates whether or not to call IDXGIFactory::MakeWindowAssociation on the window.

            Default value is true if a window is passed to the constructor, and false otherwise.
            This allows the renderer to receive WM_SIZE messages from that window.
        */
        efd::Bool m_associateWithWindow;
        /** 
            Set of D3D11Renderer::WindowAssociationFlags to pass in to 
            IDXGIFactory::MakeWindowAssociation.

            Default value is 0
        */
        efd::UInt32 m_windowAssociationFlags;

        /** 
            Format of the depth stencil buffer. 

            Default value is DXG_FORMAT_UNKNOWN
        */
        DXGI_FORMAT m_depthStencilFormat;

        /**
            Description of swap chain to create.

            Default value for the parameters of the struct are:
            BufferDesc.Width: Width of HWND if provided, 640 otherwise.
            BufferDesc.Height: Height of HWND if provided, 480 otherwise.
            BufferDesc.RefreshRate: 60/1.
            BufferDesc.Format: DXXGI_FORMAT_R8G8B8A8.
            BufferDesc.ScanlineOrdering: DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE
            BufferDesc.Scaling: DXGI_MODE_SCALING_UNSPECIFIED
            SampleDesc.Count: 1
            SampleDesc.Quality: 0
            BufferUsage: DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT
            BufferCount: 1
            OutputWindow: NULL
            Windowed: false
            SwapEffect: DXGI_SWAP_EFFECT_DISCARD
            Flags: DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
        */
        DXGI_SWAP_CHAIN_DESC m_swapChain;
    };

    /**
        Create a renderer.

        @param createParams Parameters to use to create the renderer.
        @param spRenderer Outputs the newly-created renderer, if creation succeeds.
        @return True if the function succeeds, false otherwise.
    */
    static efd::Bool Create(
        CreationParameters& createParams,
        D3D11RendererPtr& spRenderer);

    /// Returns the creation parameters used to create the renderer.
    inline void GetCreationParameters(CreationParameters& createParams) const;

    /**
        Resize a swap chain.

        This function is most often called in response to a WM_SIZE message.

        This function can only be called from the device thread. Refer to the documentation on
        Restricted Thread Behavior for the D3D11Renderer.

        @param width New buffer width.
        @param height New buffer height.
        @param hOutputWnd Window whose swap chain is being resized. If this parameter is NULL,
            the default swap chain will be resized.
        @return True if the function succeeds, false otherwise.
    */
    efd::Bool ResizeBuffers(efd::UInt32 width, efd::UInt32 height, HWND hOutputWnd = NULL);

    /**
        Create a new swap chain and associated render target group.

        This function is used to provide support for rendering to multiple windows. The render 
        target group will be stored internal to the renderer, and can be obtained using
        GetSwapChainRenderTargetGroup.

        This function can only be called from the device thread. Refer to the documentation on
        Restricted Thread Behavior for the D3D11Renderer.

        @param swapChainDesc Description of the new swap chain.
        @param outputIndex Output to create the new swap chain on.
        @param createDepthStencilBuffer Whether or not to create a depth/stencil buffer for the
            new swap chain.
        @param depthStencilFormat Depth stencil format for the new depth/stencil buffer.
        @return True if the function succeeds, false otherwise.
    */
    efd::Bool CreateSwapChainRenderTargetGroup(
        DXGI_SWAP_CHAIN_DESC& swapChainDesc,
        efd::UInt32 outputIndex = 0,
        efd::Bool createDepthStencilBuffer = true,
        DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_UNKNOWN);
    /**
        Destroy a swap chain and its associated render target group.

        Note that if the render target group associated with hWnd is the current render target, 
        this function will fail. This function may be used to destroy the original render target 
        group created with the device if hWnd is the window passed in the swap chain description 
        in the original CreationParameters structure provided to the D3D11Renderer::Create 
        function. In this case, the renderer will automatically assign one of the other swap 
        chain render target groups, if any exist, as the new default render target group.

        This function can only be called from the device thread. Refer to the documentation on
        Restricted Thread Behavior for the D3D11Renderer.
    */
    void DestroySwapChainRenderTargetGroup(HWND hWnd);
    /**
        Recreates a swap chain with new parameters, leaving the swap chain's render target group 
        intact.

        This function can only be called from the device thread. Refer to the documentation on
        Restricted Thread Behavior for the D3D11Renderer.

        @param swapChainDesc Description of the new swap chain.
        @param outputIndex Output to create the new swap chain on.
        @param createDepthStencilBuffer Whether or not to create a depth/stencil buffer for the
            new swap chain.
        @param depthStencilFormat Depth stencil format for the new depth/stencil buffer.
        @return True if the function succeeds, false otherwise.
    */
    efd::Bool RecreateSwapChainRenderTargetGroup(
        DXGI_SWAP_CHAIN_DESC& swapChainDesc,
        efd::UInt32 outputIndex = 0,
        efd::Bool createDepthStencilBuffer = true,
        DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_UNKNOWN);
    /// Returns the render target group for the specified window's swap chain.
    NiRenderTargetGroup* GetSwapChainRenderTargetGroup(HWND hWnd) const;

    /**
        Makes the NiRenderTargetGroup for the specified window the default render target group.

        This function can only be called from the device thread. Refer to the documentation on
        Restricted Thread Behavior for the D3D11Renderer.
    */
    efd::Bool SetDefaultSwapChainRenderTargetGroup(HWND hWnd);

    /// Returns the D3D11 device.
    inline ID3D11Device* GetD3D11Device() const;
    /// Returns the immediate D3D11 device context.
    inline ID3D11DeviceContext* GetImmediateD3D11DeviceContext() const;
    /// Returns the current D3D11 device context.
    inline ID3D11DeviceContext* GetCurrentD3D11DeviceContext() const;

    /// @name Occluded device notification functions
    //@{
    /**
        Callback function type for responding to an occluded device.

        The OCCLUDEDNOTIFYFUNC type is for a pointer to a function that gets called as soon as 
        the renderer encounters an occluded device, and again as soon as the renderer learns that 
        the device is no longer occluded. The renderer calls the function with beginOccluded = true 
        immediately when the occlusion starts, and beginOccluded = false as soon as the occlusion 
        ends. Any data pointer that the application provides when registering the function is 
        passed in to the callback function as the pData parameter.
    */
    typedef efd::Bool (*OCCLUDEDNOTIFYFUNC)(efd::Bool beginOccluded, void* pData);

    /**
        Register a callback function for responding to an occluded device.

        Callback functions will be made in the order they have been registered.

        @param pNotifyFunc Function to call when the device is first occluded and when the
            occlusion is over.
        @param pData Optional data pointer that will be passed in to the callback function.
        @return The index of the registered callback function.
    */
    efd::UInt32 AddOccludedNotificationFunc(OCCLUDEDNOTIFYFUNC pNotifyFunc, void* pData);
    /// Unregister the specified device-occluded callback function.
    efd::Bool RemoveOccludedNotificationFunc(OCCLUDEDNOTIFYFUNC pNotifyFunc);
    /// Unregister the specified device-occluded callback function.
    efd::Bool RemoveOccludedNotificationFunc(efd::UInt32 index);
    /// Unregister all device-occluded callback function.
    void RemoveAllOccludedNotificationFuncs();

    /// Change the data pointer that will be passed to the specified device-occluded callback
    /// function.
    efd::Bool ChangeOccludedNotificationFuncData(OCCLUDEDNOTIFYFUNC pNotifyFunc, void* pData);
    /// Change the data pointer that will be passed to the specified device-occluded callback
    /// function.
    efd::Bool ChangeOccludedNotificationFuncData(efd::UInt32 index, void* pData);

    /// Return the number of callback functions registered to respond to an occluded device.
    efd::UInt32 GetOccludedNotificationFuncCount() const;
    /// Return the size of the array of callback functions registered to respond to an occluded 
    /// device.
    efd::UInt32 GetOccludedNotificationFuncArrayCount() const;
    /// Return the index of the specified device-occluded callback function.
    efd::UInt32 FindOccludedNotificationFunc(OCCLUDEDNOTIFYFUNC pNotifyFunc) const;
    /// Return the specified device-occluded callback function.
    OCCLUDEDNOTIFYFUNC GetOccludedNotificationFunc(efd::UInt32 index) const;
    //@}

    /// @name Removed device notification functions
    //@{
    /**
        Callback function type for responding to a removed  device.

        The DEVICEREMOVEDNOTIFYFUNC type is for a pointer to a function that gets called once, 
        when the renderer first realizes that the device has been removed. Any data pointer that 
        the application provides when registering the function is passed in as the pData parameter.
    */
    typedef efd::Bool (*DEVICEREMOVEDNOTIFYFUNC)(void* pData);

    /**
        Register a callback function for responding to an removed device.

        Callback functions will be made in the order they have been registered.

        @param pNotifyFunc Function to call when the device is removed.
        @param pData Optional data pointer that will be passed in to the callback function.
        @return The index of the registered callback function.
    */
    efd::UInt32 AddDeviceRemovedNotificationFunc(DEVICEREMOVEDNOTIFYFUNC pNotifyFunc, void* pData);
    /// Unregister the specified device-removed callback function.
    efd::Bool RemoveDeviceRemovedNotificationFunc(DEVICEREMOVEDNOTIFYFUNC pNotifyFunc);
    /// Unregister the specified device-removed callback function.
    efd::Bool RemoveDeviceRemovedNotificationFunc(efd::UInt32 index);
    /// Unregister all device-removed callback function.
    inline void RemoveAllDeviceRemovedNotificationFuncs();

    /// Change the data pointer that will be passed to the specified device-removed callback
    /// function.
    efd::Bool ChangeDeviceRemovedNotificationFuncData(
        DEVICEREMOVEDNOTIFYFUNC pNotifyFunc, 
        void* pData);
    /// Change the data pointer that will be passed to the specified device-removed callback
    /// function.
    efd::Bool ChangeDeviceRemovedNotificationFuncData(efd::UInt32 index, void* pData);

    /// Return the number of callback functions registered to respond to an removed device.
    inline efd::UInt32 GetDeviceRemovedNotificationFuncCount() const;
    /// Return the size of the array of callback functions registered to respond to an removed 
    /// device.
    inline efd::UInt32 GetDeviceRemovedNotificationFuncArrayCount() const;
    /// Return the index of the specified device-removed callback function.
    efd::UInt32 FindDeviceRemovedNotificationFunc(DEVICEREMOVEDNOTIFYFUNC pNotifyFunc) const;
    /// Return the specified device-removed callback function.
    inline DEVICEREMOVEDNOTIFYFUNC GetDeviceRemovedNotificationFunc(efd::UInt32 index) const;
    //@}

    /**
        Check capabilities of a specific format on the current device.

        @param format Format to check
        @param flags Set of flags to check. These flags come from the D3D11_FORMAT_SUPPORT 
            enumeration, and can be OR-ed together to check multiple flags at once. All the 
            specified capabilities must be supported for the function to return true.
        @return True if the capability check passes, false otherwise.
    */
    inline efd::Bool DoesFormatSupportFlag(DXGI_FORMAT format, efd::UInt32 flags) const;
    /// Returns the full set of D3D11_FORMAT_SUPPORT flags for the given format.
    inline efd::UInt32 GetFormatSupportFlags(DXGI_FORMAT format) const;

    /**
        Returns the curent synchronization interval.
        
        This value that will be passed into all IDXGISwapChain::Present calls, and is used to
        synchronize the calls to the vertical refresh rate. An interval of 0 indicates new
        frames should be presented immediately, and 1 indicates the device should wait for the
        next refresh to present the frame. Values greater than 1 indicate how many refresh signals
        to wait until the frame is presented.
    */
    inline efd::UInt32 GetSyncInterval() const;
    /**
        Sets the curent synchronization interval.
        
        This value that will be passed into all IDXGISwapChain::Present calls, and is used to
        synchronize the calls to the vertical refresh rate. An interval of 0 indicates new
        frames should be presented immediately, and 1 indicates the device should wait for the
        next refresh to present the frame. Values greater than 1 indicate how many refresh signals
        to wait until the frame is presented.
    */
    inline void SetSyncInterval(efd::UInt32 syncInterval);

    /// Return the renderer's D3D11DeviceState.
    inline D3D11DeviceState* GetDeviceState() const;
    /// Return the renderer's D3D11RenderStateManager.
    inline D3D11RenderStateManager* GetRenderStateManager() const;
    /// Return the renderer's D3D11ResourceManager.
    inline D3D11ResourceManager* GetResourceManager() const;
    /// Return the renderer's D3D11ShaderConstantManager.
    inline D3D11ShaderConstantManager* GetShaderConstantManager() const;

    /// Return the current feature level for the device.
    inline FeatureLevel GetFeatureLevel() const;
    /**
        Return the number of supported shader program types that the devices supports.
        
        All D3D11 devices will support pixel and vertex shader programs, but other shader program 
        types are only available at higher feature levels.
    */
    inline efd::UInt32 GetSupportedShaderTypeCount() const;
    /**
        Return a supported shader program type that the devices supports.
        
        All D3D11 devices will support pixel and vertex shader programs, but other shader program 
        types are only available at higher feature levels. 
        
        @param index The index of the shader program type.
        @return A shader program type supported by the current device. If an index greater than 
            the number of supported shader program types is provided, the function will return 
            NiGPUProgram::PROGRAM_MAX.
    */
    inline NiGPUProgram::ProgramType GetSupportedShaderType(efd::UInt32 index) const;
    /**
        Return the current maximum compute shader version.
        
        The compute shader version will be encoded using D3D11 macros, and the major version
        can be obtained using D3D11_SHVER_GET_MAJOR(version) while the minor version can be 
        obtained using D3D11_SHVER_GET_MINOR(version). Alternatively, the 
        D3D11ShaderFactory::GetMajorComputeShaderVersion and GetMinorComputeShaderVersion can be
        used.

        The renderer only reports the compute shader version because that is the only shader type
        whose version specifications can not be reliably determined by feature level alone.
    */
    inline efd::UInt32 GetMaxComputeShader() const;

    /** 
        Wrapper function for D3D11DeviceState::InvalidateDeviceState.

        Invalidates the cached version of the shaders, render state objects, samplers, 
        shader resources, unordered access views, and shader constant buffers that Gamebryo 
        maintains. This may cause Gamebryo to release the only reference to objects that are on 
        the device, which will cause those objects to be deleted.

        This function can be called after an application has made calls directly on the 
        D3D11 device to inform Gamebryo that the state objects may have changed. This prevents 
        Gamebryo from incorrectly optimizing out a call to set a state object on the device.
    */
    inline void InvalidateDeviceState();

    /**
        Register an instance of a D3D11 NiShader class with the renderer.

        Most shader libraries will manage the registration of shaders themselves, but this 
        allows applications to register any of their own shaders not created through a 
        shader library.
    */
    inline void RegisterD3D11Shader(D3D11ShaderInterface* pD3D11Shader);
    /// Release an instance of a D3D11 NiShader class with the renderer.
    inline void ReleaseD3D11Shader(D3D11ShaderInterface* pD3D11Shader);
    /// Release an instance of a D3D11 NiShader class with the renderer and force it to release
    /// its D3D11 resources.
    inline void PurgeD3D11Shader(D3D11ShaderInterface* pD3D11Shader);
    /// Release and purge all D3D11 NiShader instances currently registered.
    inline void PurgeAllD3D11Shaders();

    /// Return a string describing the maximum vertex shader target for this device.
    inline const efd::Char* GetVertexShaderProfile() const;
    /// Return a string describing the maximum hull shader target for this device.
    inline const efd::Char* GetHullShaderProfile() const;
    /// Return a string describing the maximum domain shader target for this device.
    inline const efd::Char* GetDomainShaderProfile() const;
    /// Return a string describing the maximum geometry shader target for this device.
    inline const efd::Char* GetGeometryShaderProfile() const;
    /// Return a string describing the maximum pixel shader target for this device.
    inline const efd::Char* GetPixelShaderProfile() const;
    /// Return a string describing the maximum compute shader target for this device.
    inline const efd::Char* GetComputeShaderProfile() const;

    /**
        Create an NiTexture to manage a D3D11 resource and shader resource view.

        This allows applications to create any D3D11 shader resource and still let Gamebryo manage 
        and interact with it.

        @note The NiTexture will add its own reference to the resource and shader resource view.
        Applications that call this function will need to release their own references to prevent
        a resource leak.
    */
    NiTexturePtr CreateNiTextureFromD3D11Resource(
        ID3D11Resource* pD3D11Texture,
        ID3D11ShaderResourceView* pResourceView = NULL);

    /// @name NiRenderer virtual overrides
    //@{
    /// Return a string describing the renderer.
    virtual const efd::Char* GetDriverInfo() const;

    /// Return the renderer capabilities for this renderer.
    virtual efd::UInt32 GetFlags() const;

    /// Return a unique ID for the Renderer.
    virtual efd::SystemDesc::RendererID GetRendererID() const;

    /// Set depth buffer clear value.
    virtual void SetDepthClear(const efd::Float32 depthClear);
    /// Return depth buffer clear value.
    virtual efd::Float32 GetDepthClear() const;
    /// Set background clear color.
    virtual void SetBackgroundColor(const NiColor& color);
    /// Set background clear color.
    virtual void SetBackgroundColor(const NiColorA& color);
    /// Return background clear color.
    virtual void GetBackgroundColor(NiColorA& color) const;
    /// Set stencil buffer clear value.
    virtual void SetStencilClear(efd::UInt32 stencilClear);
    /// Return stencil buffer clear value.
    virtual efd::UInt32 GetStencilClear() const;

    /// Validate that a render target group can run on the current hardware.
    virtual efd::Bool ValidateRenderTargetGroup(NiRenderTargetGroup* pTarget);
    /// Check whether a render target and depth/stencil buffer can be used together.
    virtual efd::Bool IsDepthBufferCompatible(
        Ni2DBuffer* pBuffer,
        NiDepthStencilBuffer* pDSBuffer);

    /// Return the default render target group.
    virtual NiRenderTargetGroup* GetDefaultRenderTargetGroup() const;
    /// Return the currently active render target group.
    virtual const NiRenderTargetGroup* GetCurrentRenderTargetGroup() const;

    /// Return the default depth stencil buffer
    virtual NiDepthStencilBuffer* GetDefaultDepthStencilBuffer() const;
    /// Return the default backbuffer
    virtual Ni2DBuffer* GetDefaultBackBuffer() const;

    /// Return the closest supporetd D3D11-specific pixel format for a given set of format prefs.
    virtual const NiPixelFormat* FindClosestPixelFormat(NiTexture::FormatPrefs& formatPrefs) const;
    /// Return the closest supported D3D11-specific depth/stencil buffer format that can work
    /// with the provided parameters.
    virtual const NiPixelFormat* FindClosestDepthStencilFormat(
        const NiPixelFormat* pFrontBufferFormat, 
        efd::UInt32 depthBPP,
        efd::UInt32 stencilBPP) const;

    /// Return maximum number of simultaneous render targets supported.
    virtual efd::UInt32 GetMaxBuffersPerRenderTargetGroup() const;
    /// Return whether the concurrent render targets can have independent bit depths.
    virtual efd::Bool GetIndependentBufferBitDepths() const;

    /// Upload a texture to the D3D11 device
    virtual efd::Bool PrecacheTexture(NiTexture* pTexture);

    /// Precache the shader for the active material on the provided mesh.
    virtual efd::Bool PrecacheShader(NiRenderObject* pRenderObject);

    /// Upload the NiDataStreams on the mesh to the D3D11 device.
    virtual efd::Bool PrecacheMesh(
        NiRenderObject* pMesh,
        efd::Bool releaseSystemMemory = true);

    /// Perform the precaches that the renderer has queued up.
    virtual efd::Bool PerformPrecache();

    /// Set the texture mipmap skip level.
    virtual efd::Bool SetMipmapSkipLevel(efd::UInt32 skipLevel);
    /// Return the texture mipmap skip level.
    virtual efd::UInt32 GetMipmapSkipLevel() const;

    /// Purge cached renderer data for the material, which doesn't exist in D3D11.
    virtual void PurgeMaterial(NiMaterialProperty* pMaterial);
    /// Purge cached renderer data for the material, which doesn't exist in D3D11.
    virtual void PurgeEffect(NiDynamicEffect* pLight);

    /// Release the D3D11 resources for the texture.
    virtual efd::Bool PurgeTexture(NiTexture* pTexture);

    /// Release the D3D11 resources for all textures.
    virtual efd::Bool PurgeAllTextures(efd::Bool purgeLocked);

    /// Take a screen shot and return the contents in an NiPixelData object.
    virtual NiPixelData* TakeScreenShot(
        const NiRect<efd::UInt32>* pScreenRect,
        const NiRenderTargetGroup* pTarget = NULL);

    /// Take a screen shot and save the contents to file.
    virtual efd::Bool SaveScreenShot(
        const efd::Char* pFilename,
        EScreenshotFormat format);

    /**
        Copy an arbitrary region from one 2D buffer to the specified coordinates of a different 
        2D buffer. 
        
        Note that the NiPixelFormat objects of both Ni2DBuffer objects must match for this method. 
        This is the fastest path possible for copying pixel data. Also note that a NULL value for 
        the NiRect will use the dimensions of the Ni2DBuffer.
    */
    virtual efd::Bool FastCopy(
        const Ni2DBuffer* pSrc, 
        Ni2DBuffer* pDest,
        const NiRect<efd::UInt32>* pSrcRect = NULL,
        efd::UInt32 destX = 0, 
        efd::UInt32 destY = 0);
    /**
        Copy an arbitrary region from one 2D buffer to another arbitrary region in a different 
        2D buffer. 
        
        Note that the NiPixelFormat objects of both Ni2DBuffer objects may differ for this method. 
        Also note that a NULL value for either NiRect will use the dimensions of the Ni2DBuffer.
        This path is slower than the previous FastCopy method.
    */
    virtual efd::Bool Copy(
        const Ni2DBuffer* pSrc, 
        Ni2DBuffer* pDest,
        const NiRect<efd::UInt32>* pSrcRect,
        const NiRect<efd::UInt32>* pDestRect,
        Ni2DBuffer::CopyFilterPreference filterPref);

    /// Create a depth stencil buffer compatible with the passed-in buffer
    virtual NiDepthStencilBuffer* CreateCompatibleDepthStencilBuffer(
        Ni2DBuffer* pBuffer) const;

    /// Return a flag indicating reversed left-right rendering is enabled.
    virtual efd::Bool GetLeftRightSwap() const;
    /// Set a flag that reverses left-right rendering.
    virtual efd::Bool SetLeftRightSwap(efd::Bool swap);

    /// Return the maximum fog density.
    virtual efd::Float32 GetMaxFogValue() const;
    /// Set the maximum fog density.
    virtual void SetMaxFogValue(efd::Float32 fogVal);
    /// Returns the max fog factor, which is the inverse of the max fog value as set by 
    /// NiRenderer::SetMaxFogValue, minus 1.
    efd::Float32 GetMaxFogFactor() const;

    /// Set the maximum anisotropy.
    virtual void SetMaxAnisotropy(efd::UInt16 maxAnisotropy);

    /// Use the legacy fixed-function pipeline as the default material - this does nothing on D3D11,
    /// since there is no fixed-function pipeline.
    virtual void UseLegacyPipelineAsDefaultMaterial();
    //@}

    /// Return the renderer, ensuring it is a D3D11 renderer
    static D3D11Renderer* GetRenderer();

    /// Wrapper to D3D11 Library function D3D11CreateDevice
    static HRESULT D3D11CreateDevice(
        __in_opt IDXGIAdapter* pAdapter,
        D3D_DRIVER_TYPE DriverType,
        HMODULE Software,
        UINT Flags,
        __in_ecount_opt(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
        UINT FeatureLevels,
        UINT SDKVersion,
        __out_opt ID3D11Device** ppDevice,
        __out_opt D3D_FEATURE_LEVEL* pFeatureLevel,
        __out_opt ID3D11DeviceContext** ppImmediateContext);

    /// Wrapper to D3D11 Library function D3D11CreateDeviceAndSwapChain
    static HRESULT D3D11CreateDeviceAndSwapChain(
        __in_opt IDXGIAdapter* pAdapter,
        D3D_DRIVER_TYPE DriverType,
        HMODULE Software,
        UINT Flags,
        __in_ecount_opt(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
        UINT FeatureLevels,
        UINT SDKVersion,
        __in_opt CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
        __out_opt IDXGISwapChain** ppSwapChain,
        __out_opt ID3D11Device** ppDevice,
        __out_opt D3D_FEATURE_LEVEL* pFeatureLevel,
        __out_opt ID3D11DeviceContext** ppImmediateContext);

    /// Return pointer to array of D3D_SHADER_MACRO structures
    const D3D_SHADER_MACRO* GetD3D11MacroList(
        const efd::Char* pFileType,
        const D3D_SHADER_MACRO* pUserMacros = NULL);

    /// Begin a profile marker section
    virtual void PushProfileMarker(const efd::Char* pName);
    /// End a profile marker section
    virtual void PopProfileMarker();

    /// Create a new render target group to act as a swap chain for a window.
    virtual efd::Bool CreateWindowRenderTargetGroup(efd::WindowRef wndRef);
    /// Recreate the buffers in a render target group to act as a swap chain for a window.
    virtual efd::Bool RecreateWindowRenderTargetGroup(efd::WindowRef wndRef);
    /// Release a swap chain render target group for a window.
    virtual void ReleaseWindowRenderTargetGroup(efd::WindowRef wndRef);
    /// Return a previously created swap chain render target group for a window.
    virtual NiRenderTargetGroup* GetWindowRenderTargetGroup(efd::WindowRef wndRef) const;

    /// @cond EMERGENT_INTERNAL

    /// Set the model transform on the renderer.
    inline void SetModelTransform(const NiTransform& kWorld);

    /// Create the renderer data for an NiSourceTexture.
    virtual efd::Bool CreateSourceTextureRendererData(NiSourceTexture* pTexture);
    /// Create the renderer data for an NiRenderedTexture.
    virtual efd::Bool CreateRenderedTextureRendererData(
        NiRenderedTexture* pTexture,
        Ni2DBuffer::MultiSamplePreference multiSamplePref = Ni2DBuffer::MULTISAMPLE_NONE);
    /// Create the renderer data for an NiSourceCubeMap.
    virtual efd::Bool CreateSourceCubeMapRendererData(NiSourceCubeMap* pCubeMap);
    /// Create the renderer data for an NiRenderedCubeMap.
    virtual efd::Bool CreateRenderedCubeMapRendererData(NiRenderedCubeMap* pCubeMap);
    /// Create the renderer data for an NiDynamicTexture.
    virtual efd::Bool CreateDynamicTextureRendererData(NiDynamicTexture* pTexture);
    /// Create the renderer data for an NiPalette. This does nothing on D3D11.
    virtual void CreatePaletteRendererData(NiPalette* pPalette);
    /// Create the renderer data for an NiDepthStencilBuffer.
    virtual efd::Bool CreateDepthStencilRendererData(
        NiDepthStencilBuffer* pDSBuffer, 
        const NiPixelFormat* pFormat,
        Ni2DBuffer::MultiSamplePreference multiSamplePref = Ni2DBuffer::MULTISAMPLE_NONE);
    /// Create the renderer data for an NiDepthStencilBuffer.
    efd::Bool CreateDepthStencilRendererData(
        NiDepthStencilBuffer* pDSBuffer,
        const NiPixelFormat* pFormat,
        Ni2DBuffer::MultiSamplePreference msaaPref, 
        efd::Bool cubeMap);

    /// Release the renderer data for an NiRenderedCubeMap.
    virtual void RemoveRenderedCubeMapData(NiRenderedCubeMap* pCubeMap);
    /// Release the renderer data for an NiRenderedTexture.
    virtual void RemoveRenderedTextureData(NiRenderedTexture* pTexture);
    /// Release the renderer data for an NiDynamicTexture.
    virtual void RemoveDynamicTextureData(NiDynamicTexture* pTexture);

    /// Lock a dynamic texture.
    virtual void* LockDynamicTexture(
        const NiTexture::RendererData* pRData,
        efd::SInt32& pitch);
    /// Unlock a dynamic texture.
    virtual efd::Bool UnLockDynamicTexture(const NiTexture::RendererData* pRData);

    /// Return a platform-specific fragment shader for a given material descriptor.
    virtual NiShader* GetFragmentShader(NiMaterialDescriptor* pMaterialDescriptor);
    /// Return a platform-specific shadow write shader for a given material descriptor.
    virtual NiShader* GetShadowWriteShader(NiMaterialDescriptor* pMaterialDescriptor);
    /// Set a flag indicating shadow write shaders should render backfaces.
    virtual void SetRenderShadowCasterBackfaces(efd::Bool renderBackfaces);

    /// Set the renderer's default GPU program cache for fragment materials.
    virtual void SetDefaultProgramCache(
        NiFragmentMaterial* pMaterial,
        efd::Bool autoWriteToDisk, 
        efd::Bool writeDebugFile, 
        efd::Bool load,
        efd::Bool noNewProgramCreation, 
        const efd::Char* pWorkingDir);

    /// Return the current projection matrix.
    inline const XMMATRIX& GetProjectionMatrix() const;
    /// Return the current view matrix.
    inline const XMMATRIX& GetViewMatrix() const;
    /// Return the inverse of the current view matrix.
    inline const XMMATRIX& GetInverseViewMatrix() const;
    /// Return the current world matrix.
    inline const XMMATRIX& GetWorldMatrix() const;

    /// Return the camera near and far distances.
    inline void GetCameraNearAndFar(efd::Float32& nearPlane, efd::Float32& farPlane) const;

    /// Return the thread ID for the thread used to create the device.
    inline efd::UInt32 GetDeviceThreadID() const;

    /// Return the renderer's D3D11ShaderLibraryVersion.
    inline const D3D11ShaderLibraryVersion* GetShaderLibraryVersion() const;

    /// Return a D3D11_PRIMITIVE_TOPOLOGY enumeration from the NiPrimitiveType::Type and a flag
    /// indicating whether adjacency information is included.
    static D3D11_PRIMITIVE_TOPOLOGY GetD3D11TopologyFromPrimitiveType(
        NiPrimitiveType::Type primitiveType, 
        efd::Bool adjacency);

    /// Initialize static data structures for the renderer.
    static void _SDMInit();
    /// Release static data structures for the renderer.
    static void _SDMShutdown();

    /// Load the D3D11 libraries if they are not already loaded.
    static efd::Bool EnsureD3D11Loaded();

    /// Create a temp D3D11 device with the given parameters.
    static efd::Bool CreateTempDevice(
        IDXGIAdapter* pAdapter,
        D3D_DRIVER_TYPE driverype, 
        efd::UInt32 flags,
        D3D_FEATURE_LEVEL& featureLevel,
        ID3D11Device*& pDevice,
        ID3D11DeviceContext*& pDeviceContext);

    /// Return a shader and binding object for a given mesh and its active material. If no such
    /// shader can be found, return the error shader.
    D3D11ShaderInterface* GetShaderAndVertexDecl(
        NiRenderObject* pMesh,
        D3D11MeshMaterialBindingPtr& spMMB);
    /// Return a shader and binding object for a given mesh and its active material.
    D3D11ShaderInterface* GetShaderAndVertexDecl_NoErrorShader(
        NiRenderObject* pMesh, 
        D3D11MeshMaterialBindingPtr& spMMB);

#if defined (EE_ASSERTS_ARE_ENABLED)
    /// Asserts when a NiShader fails to call CompleteModifiers on the rendered meshes.
    virtual void EnforceModifierPoliciy(NiVisibleArray* pArray);
#endif

    /// Wrapper for D3D10 library function D3D10CreateBlob, since there is no D3D11 equivalent.
    static HRESULT D3D10CreateBlob(SIZE_T NumBytes, LPD3D10BLOB* ppBuffer);

    /// @endcond

protected:

    /// Load D3D11 libraries
    static efd::Bool LoadD3D11();
    /// Release D3D11 libraries
    static efd::Bool ReleaseD3D11();

    /// Hidden constructor
    D3D11Renderer();
    /// Initialize the renderer from the CreationParameters
    efd::Bool Initialize(CreationParameters& createParams);
    /// Create a D3D11 device
    efd::Bool CreateDevice(CreationParameters& createParams);
    /// Release the D3D11 device
    efd::Bool ReleaseDevice();

    /// Create instances of the various manager classes
    void CreateManagers();
    /// Release the various manager classes
    void ReleaseManagers();

    /// Read capabilities from the device and set internal caps accordingly
    void StoreDeviceSettings();

    /// Create a swap chain
    IDXGISwapChain* CreateSwapChain(
        DXGI_SWAP_CHAIN_DESC& swapChainDesc,
        efd::UInt32 outputIndex);
    /// Create an NiRenderTargetGroup for a swap chain
    NiRenderTargetGroup* CreateRenderTargetGroupFromSwapChain(
        IDXGISwapChain* pSwapChain, 
        efd::Bool createDepthStencilBuffer,
        DXGI_FORMAT depthStencilFormat);
    /// Create the Ni2DBufferData objects for a swap chain
    efd::Bool CreateBuffersFromSwapChain(
        IDXGISwapChain* pSwapChain, 
        efd::Bool createDepthStencilBuffer,
        DXGI_FORMAT depthStencilFormat, 
        Ni2DBuffer*& pBackBuffer,
        NiDepthStencilBuffer*& pDepthBuffer);

    /// Check return result from Present for occluded or lost device and manage accordingly
    efd::Bool HandleDisplayFrameResult(HRESULT hr);

    /// Release default render target group
    inline efd::Bool ReleaseResources();

    /// Indicates whether the hardware supports MMX
    efd::Bool SupportsMMX() const;
    /// Indicates whether the hardware supports SSE
    efd::Bool SupportsSSE() const;
    /// Indicates whether the hardware supports SSE2
    efd::Bool SupportsSSE2() const;

    /// Helper function to obtain the backbuffer for use with screen shots
    ID3D11Texture2D* GetBackBufferResource(
        const NiRenderTargetGroup* pTarget,
        efd::UInt32 renderTarget = 0);

    /// Renderer specific implementations
    //@{
    virtual efd::Bool Do_BeginFrame();
    virtual efd::Bool Do_EndFrame();
    virtual efd::Bool Do_DisplayFrame();
    virtual void Do_ClearBuffer(
        const NiRect<efd::Float32>* pRect,
        efd::UInt32 clearMode);
    virtual void Do_SetCameraData(
        const NiPoint3& worldLoc,
        const NiPoint3& worldDir, 
        const NiPoint3& worldUp,
        const NiPoint3& worldRight, 
        const NiFrustum& frustum,
        const NiRect<efd::Float32>& port);
    virtual void Do_GetCameraData(
        NiPoint3& worldLoc, 
        NiPoint3& worldDir,
        NiPoint3& worldUp, 
        NiPoint3& worldRight, 
        NiFrustum& frustum,
        NiRect<efd::Float32>& port);
    virtual void Do_SetScreenSpaceCameraData(
        const NiRect<efd::Float32>* pPort = NULL);
    virtual efd::Bool Do_BeginUsingRenderTargetGroup(
        NiRenderTargetGroup* pTarget,
        efd::UInt32 clearMode);
    virtual efd::Bool Do_EndUsingRenderTargetGroup();
    virtual void Do_RenderMesh(NiMesh* pMesh);
    //@}

    /// Convert from D3D11Renderer::DriverType to D3D_DRIVER_TYPE
    inline D3D_DRIVER_TYPE GetD3D11DriverType(DriverType driverType) const;
    /// Convert from D3D11Renderer::CreateDeviceFlags to D3D11_CREATE_DEVICE_FLAG
    inline efd::UInt32 GetD3D11CreateDeviceFlags(
        efd::UInt32 createDeviceFlags) const;
    /// Convert from D3D11Renderer::FeatureLevel to D3D_FEATURE_LEVEL
    inline D3D_FEATURE_LEVEL GetD3D11FeatureLevel(FeatureLevel featureLevel) const;
    /// Convert from D3D11Renderer::WindowAssociateionFlags to DXGI_MWA_* flags
    inline efd::UInt32 GetD3D11WindowAssociationFlags(
        efd::UInt32 windowAssociationFlags) const;

    XMMATRIX m_d3dView;
    XMMATRIX m_invView;
    XMMATRIX m_d3dProj;
    XMMATRIX m_d3dModel;

    CreationParameters m_initialCreateParameters;
    D3D11SystemDescPtr m_spSystemDesc;

    mutable efd::Char m_driverDesc[512];

    // Device thread ID
    efd::UInt32 m_deviceThreadID;

    ID3D11Device* m_pD3D11Device;
    ID3D11DeviceContext* m_pImmediateD3D11DeviceContext;
    ID3D11DeviceContext* m_pCurrentD3D11DeviceContext;

    enum
    {
        NULL_ADAPTER = EE_UINT32_MAX
    };
    efd::UInt32 m_adapterIndex;

    efd::Bool m_initialized;

    enum
    {
        DXGI_FORMAT_COUNT = 100
    };

    enum
    {
        HW_MAX_ANISOTROPY = 16
    };

    efd::UInt32 m_formatSupportArray[DXGI_FORMAT_COUNT];

    D3D_FEATURE_LEVEL m_featureLevel;
    NiGPUProgram::ProgramType m_supportedShaderProgramTypes[NiGPUProgram::PROGRAM_MAX];
    efd::UInt32 m_supportedShaderProgramTypeCount;
    efd::UInt32 m_maxComputeShaderVersion;

    const efd::Char* m_pVertexShaderVersionString;
    const efd::Char* m_pHullShaderVersionString;
    const efd::Char* m_pDomainShaderVersionString;
    const efd::Char* m_pGeometryShaderVersionString;
    const efd::Char* m_pPixelShaderVersionString;
    const efd::Char* m_pComputeShaderVersionString;

    NiRenderTargetGroupPtr m_spDefaultRenderTargetGroup;
    NiRenderTargetGroup* m_pCurrentRenderTargetGroup;

    NiTPointerList<D3D112DBufferDataPtr> m_buffersToUseAtDisplayFrame;

    efd::Float32 m_backgroundColor[4];
    efd::Float32 m_depthClear;
    efd::UInt8 m_stencilClear;

    // Camera-related data
    efd::Bool m_leftRightSwap;
    NiFrustum m_currentFrustum;
    NiRect<efd::Float32> m_kurrentViewPort;

    // AdditionalSwapChains
    NiTPointerMap<HWND, NiRenderTargetGroupPtr> m_swapChainRenderTargetGroups;

    // Fog parameters
    efd::Float32 m_maxFogFactor;
    efd::Float32 m_maxFogValue;

    // Shaders
    NiTPointerList<D3D11ShaderInterface*> m_activeShaders;
    D3D11ShaderLibraryVersion m_shaderLibraryVersion;

    efd::UInt32 m_syncInterval;

    D3D11DataStreamFactory* m_pDataStreamFactory;
    D3D11ResourceManager* m_pResourceManager;

    // DT33837 Support multiple device contexts.
    D3D11DeviceState* m_pDeviceState;
    D3D11RenderStateManager* m_pRenderStateManager;
    D3D11ShaderConstantManager* m_pShaderConstantManager;

    // Temporary data
    efd::Point3* m_pTempVertices;
    NiColorA* m_pTempColors;
    NiPoint2* m_pTempTexCoords;
    efd::UInt32 m_tempArraySize;

    // Default NiVisibleArray used to store meshes passed into
    // Do_RenderMesh().
    static NiVisibleArray* ms_pDefaultVisibleArray;

    // Batch rendering
    NiMaterialPtr m_spBatchMaterial;

    // Device state
    efd::Bool m_isDeviceOccluded;
    efd::Bool m_isDeviceRemoved;

    // PIX status
    efd::Bool m_isPIXActive;

    // CPU Instruction set support
    efd::Bool m_supportsMMX;
    efd::Bool m_supportsSSE;
    efd::Bool m_supportsSSE2;

    // Multithreaded feature support
    efd::Bool m_backgroundRendering;
    efd::Bool m_backgroundResourceCreation;

    // Reset notification functions
    NiTPrimitiveArray<OCCLUDEDNOTIFYFUNC> m_occludedNotifyFuncs;
    NiTPrimitiveArray<void*> m_occludedNotifyFuncData;

    // Removed Device notification functions
    NiTPrimitiveArray<DEVICEREMOVEDNOTIFYFUNC> m_deviceRemovedNotifyFuncs;
    NiTPrimitiveArray<void*> m_deviceRemovedNotifyFuncData;

    static HINSTANCE ms_hD3D11;
    // D3D10 needed for ID3D10Blob
    static HINSTANCE ms_hD3D10;
    // D3D9 needed for PIX events
    static HINSTANCE ms_hD3D9;

    static PFN_D3D11_CREATE_DEVICE ms_pD3D11CreateDeviceFunc;
    static PFN_D3D11_CREATE_DEVICE_AND_SWAP_CHAIN
        ms_pD3D11CreateDeviceAndSwapChainFunc;

    static EE_LPD3D11PERF_BEGINEVENT ms_pD3DPERF_BeginEventFunc;
    static EE_LPD3D11PERF_ENDEVENT ms_pD3DPERF_EndEventFunc;
    static EE_LPD3D11PERF_GETSTATUS ms_pD3DPERF_GetStatusFunc;
    static EE_LPD3D10CREATEBLOB ms_pD3D10CreateBlob;

    static efd::CriticalSection ms_libD3D11CriticalSection;

    D3D_SHADER_MACRO* m_pShaderMacroArray;

    efd::UInt32 m_shaderMacroCount;
};

// Assumed to be called from within an ecr::D3D11Renderer object
#define EE_ASSERT_D3D11_DEVICE_THREAD \
    EE_ASSERT(((m_initialCreateParameters.m_createFlags & \
        CREATE_DEVICE_SINGLETHREADED) == 0) || \
        m_deviceThreadID == efd::GetCurrentThreadId() || \
        !"Failing this assertion means a function was called by a thread "\
        "other than the thread on which the Renderer was created. "\
        "If this behavior is intentional, the Renderer must be created "\
        "without the CREATE_DEVICE_SINGLETHREADED flag enabled.");

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11Renderer.inl>

#endif // EE_D3D11RENDERER_H
