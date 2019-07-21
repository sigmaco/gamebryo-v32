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
#ifndef NIRENDERERSETTINGS_H
#define NIRENDERERSETTINGS_H

#include "NiSettingsDialogLibType.h"
#include <NiMemObject.h>
#include <NiDX9SystemDesc.h>
#include <NiD3D10SystemDesc.h>

class NiDX9RendererDesc;
class NiD3D10RendererDesc;
class NiD3D11RendererDesc;

namespace efd
{
class IConfigManager;
class ISection;
};

class NISETTINGSDIALOG_ENTRY NiRendererSettings : public NiMemObject
{
public:
    NiRendererSettings();

    enum VertexProcessing
    {
        VERTEX_UNSUPPORTED,
        VERTEX_HARDWARE,
        VERTEX_MIXED,
        VERTEX_SOFTWARE
    };

    // Screen resolution
    unsigned int m_uiScreenWidth;
    unsigned int m_uiScreenHeight;
    // Minimum and maximum resolution settings - used to limit user's choice
    // 0 means no limit
    unsigned int m_uiMinScreenWidth;
    unsigned int m_uiMinScreenHeight;

    unsigned int m_uiAdapterIdx;
    unsigned int m_uiNVPerfHUDAdapterIdx;

    efd::SystemDesc::RendererID m_eRendererID;
    bool m_bFullscreen;
    bool m_bNVPerfHUD;
    bool m_bRefRast;
    bool m_bUse16Bit;
    bool m_bPureDevice;
    bool m_bVSync;
    bool m_bStencil;
    bool m_bMultiThread;
    bool m_bRendererDialog;
    bool m_bSaveSettings;

    VertexProcessing m_eVertexProcessing;

    NiDX9Renderer::FrameBufferFormat m_eDX9RTFormat;
    NiDX9Renderer::DepthStencilFormat m_eDX9DSFormat;
    NiDX9Renderer::FramebufferMode m_eDX9FBFormat;

    unsigned int m_uiD3D10OutputIdx;
    unsigned int m_uiD3D10MultisampleCount;
    unsigned int m_uiD3D10MultisampleQuality;
    DXGI_FORMAT m_eD3D10DSFormat;
    DXGI_FORMAT m_eD3D10RTFormat;
    DXGI_RATIONAL m_kD3D10Refresh;

    unsigned int m_uiD3D11OutputIdx;
    unsigned int m_uiD3D11MultisampleCount;
    unsigned int m_uiD3D11MultisampleQuality;
    DXGI_FORMAT m_eD3D11DSFormat;
    DXGI_FORMAT m_eD3D11RTFormat;
    DXGI_RATIONAL m_kD3D11Refresh;
    bool m_bD3D11FeatureLevel9_1;
    bool m_bD3D11FeatureLevel9_2;
    bool m_bD3D11FeatureLevel9_3;
    bool m_bD3D11FeatureLevel10_0;
    bool m_bD3D11FeatureLevel10_1;
    bool m_bD3D11FeatureLevel11_0;

    // Load / save settings.
    void LoadSettings(const char* pcFileName);
    void LoadFromConfigManager(efd::IConfigManager* pkConfigManager);
    void SaveSettings(const char* pcFileName);

protected:
    static bool ReadConfig(
        const efd::ISection* pkSection,
        const char* pcValueName,
        unsigned int& uiVal);
    static bool ReadConfig(
        const efd::ISection* pkSection,
        const char* pcValueName,
        bool& bVal);

    static void ReadUInt(const char* pcFileName, const char* pcName, unsigned int& uiVal);
    static void ReadBool(const char* pcFileName, const char* pcName, bool& bVal);
    static void WriteUInt(const char* pcFileName, const char* pcName, unsigned int uiVal);
    static void WriteBool(const char* pcFileName, const char* pcName, bool bVal);

    static const char* ms_pcSectionName;
    static const char* ms_pcScreenWidth;
    static const char* ms_pcScreenHeight;
    static const char* ms_pcMinScreenWidth;
    static const char* ms_pcMinScreenHeight;
    static const char* ms_pcVertexProcessing;
    static const char* ms_pcDX9RenderTargetMode;
    static const char* ms_pcDX9DepthSurfaceMode;
    static const char* ms_pcDX9FrameBufferMode;
    static const char* ms_pcD3D10OutputIdx;
    static const char* ms_pcD3D10MultisampleCount;
    static const char* ms_pcD3D10MultisampleQuality;
    static const char* ms_pcD3D10DSFormat;
    static const char* ms_pcD3D10RTFormat;
    static const char* ms_pcD3D10Renderer;  // Deprecated, will be overridden by ms_pcRendererID
    static const char* ms_pcD3D11OutputIdx;
    static const char* ms_pcD3D11MultisampleCount;
    static const char* ms_pcD3D11MultisampleQuality;
    static const char* ms_pcD3D11DSFormat;
    static const char* ms_pcD3D11RTFormat;
    static const char* ms_pcD3D11FeatureLevel9_1;
    static const char* ms_pcD3D11FeatureLevel9_2;
    static const char* ms_pcD3D11FeatureLevel9_3;
    static const char* ms_pcD3D11FeatureLevel10_0;
    static const char* ms_pcD3D11FeatureLevel10_1;
    static const char* ms_pcD3D11FeatureLevel11_0;
    static const char* ms_pcRendererID;
    static const char* ms_pcFullscreen;
    static const char* ms_pcNVPerfHUD;
    static const char* ms_pcRefRast;
    static const char* ms_pcUse16Bit;
    static const char* ms_pcPureDevice;
    static const char* ms_pcVSync;
    static const char* ms_pcMultiThread;
    static const char* ms_pcRendererDialog;
    static const char* ms_pcSaveSettings;
};

#include "NiRendererSettings.inl"

#endif // NIRENDERERSETTINGS_H