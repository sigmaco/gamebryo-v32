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
#ifndef NID3D10RENDERERSETUP_H
#define NID3D10RENDERERSETUP_H

#include "NiD3D10RendererSetupLibType.h"
#include "NiD3D10RendererSetupSDM.h"
#include "NiBaseRendererSetup.h"

class NiD3D10RendererOptionsView;

class NID3D10RENDERERSETUP_ENTRY NiD3D10RendererSetup : public NiBaseRendererSetup
{
public:
    NiD3D10RendererSetup();
    virtual ~NiD3D10RendererSetup();

    virtual NiBaseRendererOptionsView* GetRenderOptionsView(
        NiRendererSettings* pkSettings);
    virtual void ReleaseRendererOptionsView(NiBaseRendererOptionsView* pkROV);

    virtual efd::SystemDesc::RendererID GetRendererID() const;

    // *** begin Emergent internal use only ***

    static void _SDMInit();
    static void _SDMShutdown();

    // *** end Emergent internal use only ***

protected:
    virtual NiRendererPtr CreatePlatformRenderer(
        NiRendererSettings* pkRendererSettings,
        NiWindowRef pWndDevice,
        NiWindowRef pkWndFocus);

    NiD3D10RendererOptionsView* m_pkROV;

    static NiD3D10RendererSetup* ms_pkRendererSetup;
};

static NiD3D10RendererSetupSDM NiD3D10RendererSetupSDMObject;

//#include "NiBaseRendererSetup.inl"

#endif // #ifndef NID3D10RENDERERSETUPPCH_H
