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
#ifndef EE_SYSTEMDESC_H
#define EE_SYSTEMDESC_H

#include <efd/MemObject.h>
#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/Asserts.h>

namespace efd
{
/**
    SystemDesc is a singleton that encapsulates platform-specific queries
    about the capabilities of the current machine.
*/
class EE_EFD_ENTRY SystemDesc : public MemObject
{
public:
    /// Method to access the singleton instance of the system description.
    static const SystemDesc& GetSystemDesc();

    typedef enum
    {
        // Renderer IDs are hard-coded to ensure future compatibility of
        // streamed values.

        RENDERER_XBOX360 = 0,
        RENDERER_PS3 = 1,
        RENDERER_DX9 = 2,
        RENDERER_D3D10 = 3,
        RENDERER_D3D11 = 6,
        RENDERER_WII = 4, // No longer supported, but remains for compatibility
        // Generic renderer is used for tool mode so that assets can be
        // generated independent of the current renderer.
        RENDERER_GENERIC = 5,

        // The total number of enumerated renderers
        RENDERER_COUNT = 7,

        // Compatibility enumerations
        RENDERER_NUM = RENDERER_COUNT,
        RENDERER_XENON = RENDERER_XBOX360
    } RendererID;

    typedef enum
    {
        // Platform IDs are hard-coded to ensure future compatibility of
        // streamed values.

        PLATFORM_WIN32 = 0,
        PLATFORM_XBOX360 = 1,
        PLATFORM_PS3 = 2,
        PLATFORM_WII = 3, // No longer supported, but remains for compatibility
        PLATFORM_LINUX = 4,

        // The total number of enumerated platforms
        PLATFORM_COUNT = 5,

        // Compatibility enumerations
        NI_WIN32 = PLATFORM_WIN32,
        NI_XENON = PLATFORM_XBOX360,
        NI_PS3 = PLATFORM_PS3,
        NI_WII = PLATFORM_WII, // No longer supported
        NI_NUM_PLATFORM_IDS = PLATFORM_COUNT
    } PlatformID;

    /// Returns a string representation of the RendererID
    static const char* GetRendererString(const RendererID eRenderer);

    /// Returns the RendererID for the string. RENDERER_GENERIC is returned
    /// if no renderers match this string.
    static RendererID GetRendererID(const char* pcRendererName);

    /// Returns a string representation of the PlatformID
    static const char* GetPlatformString(PlatformID e);

    /// Returns the PlatformID for the string. -1 is returned
    /// if no platforms match this string.
    static PlatformID GetPlatformID(const char* pString);

    /// Returns true if the specified platform is little-endian
    static bool IsPlatformLittleEndian(PlatformID ePlatform);

    /// Returns true if the specified renderer is little-endian
    static bool IsRendererLittleEndian(RendererID eRenderer);

    /// The following functions ignore tool-mode and return information about
    /// the current runtime system
    bool IsLittleEndian() const;

    /// Determine the number of physical processors for the current machine
    efd::UInt32 GetPhysicalProcessorCount() const;

    /// Determine the number of physical cores for the current machine
    efd::UInt32 GetPhysicalCoreCount() const;

    /// Determine the number of logical processors for the current machine
    efd::UInt32 GetLogicalProcessorCount() const;

    /// Determine the platform for this machine
    PlatformID GetPlatformID() const;

    /// Determine the frequency of the performance counter
    inline efd::Float32 GetPerformanceCounterHz() const;

#if defined(WIN32)
    /// Determine if the platform supports MMX instructions
    inline bool MMX_Supported(void) const;

    /// Determine if the platform supports SSE instructions
    inline bool SSE_Supported(void) const;

    /// Determine if the platform supports SSE2 instructions
    inline bool SSE2_Supported(void) const;
#endif

    // Handle tool mode renderer
    inline bool GetToolMode() const;
    inline void SetToolMode(const bool bToolMode) const;
    RendererID GetToolModeRendererID() const;
    inline void SetToolModeRendererID(const RendererID eRendererID) const;

    bool GetToolModeRendererIsLittleEndian() const;

    /// @cond EMERGENT_INTERNAL
    static void _SDMInit();
    static void _SDMShutdown();
    /// @endcond
protected:
    SystemDesc();
    SystemDesc(const SystemDesc&);

    static SystemDesc* ms_SystemDesc;

#if defined(WIN32)
    unsigned int CPUID_Init();
    unsigned int CPUID_CpuIDSupported(void);
    unsigned int CPUID_GenuineIntel(void);
    unsigned int CPUID_HWD_MTSupported(void);
    unsigned int CPUID_MMX_Supported(void);
    unsigned int CPUID_SSE_Supported(void);
    unsigned int CPUID_SSE2_Supported(void);
    unsigned int CPUID_MaxLogicalProcPerPhysicalProc(void);
    unsigned int CPUID_MaxCorePerPhysicalProc(void);
    unsigned int CPUID_Find_Maskwidth(unsigned int);
    unsigned char CPUID_GetAPIC_ID(void);
    unsigned char CPUID_GetNzbSubID(unsigned char,
                              unsigned char,
                              unsigned char);
    unsigned char CPUID_CPUCount(unsigned int *,
                           unsigned int *,
                           unsigned int *, unsigned int *,
                           unsigned int);
    unsigned int CPUID_QueryCacheType(unsigned int Index);
    unsigned int CPUID_CheckCPU_ExtendedFamilyModel(void);

#endif
    // order largest to smallest.
    efd::Float32 m_PCCyclesPerSecond;
    efd::UInt32 m_NumPhysicalProcessors;
    efd::UInt32 m_NumPhysicalCores;
    efd::UInt32 m_NumLogicalProcessors;

    // Declared mutable so they can be modified using the constant function GetSystemDesc()
    mutable RendererID m_ToolModeRendererID;

    // available only on Win32 but we don't sizeof(SystemDesc) to be different on other platforms.
    bool m_bSSE_Supported;
    bool m_bMMX_Supported;
    bool m_bSSE2_Supported;

    // Declared mutable so they can be modified using the constant function GetSystemDesc()
    mutable bool m_InToolMode;
};

#include <efd/SystemDesc.inl>

}
#endif // EE_SYSTEMDESC_H

