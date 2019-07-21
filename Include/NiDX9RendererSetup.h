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
#ifndef NIDX9RENDERERSETUP_H
#define NIDX9RENDERERSETUP_H

#include "NiDX9RendererSetupLibType.h"
#include "NiDX9RendererSetupSDM.h"
#include "NiBaseRendererSetup.h"

class NiDX9RendererOptionsView;

class NIDX9RENDERERSETUP_ENTRY NiDX9RendererSetup : public NiBaseRendererSetup
{
public:
    NiDX9RendererSetup();
    virtual ~NiDX9RendererSetup();

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
        NiWindowRef pkWndDevice,
        NiWindowRef pkWndFocus);

    NiDX9RendererOptionsView* m_pkROV;

    static NiDX9RendererSetup* ms_pkRendererSetup;
};

static NiDX9RendererSetupSDM NiDX9RendererSetupSDMObject;

//#include "NiBaseRendererSetup.inl"

#endif // #ifndef NIDX9RENDERERSETUPPCH_H
