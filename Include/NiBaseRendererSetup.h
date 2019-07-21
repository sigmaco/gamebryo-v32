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
#ifndef NIBASERENDERERSETUP_H
#define NIBASERENDERERSETUP_H

#include "NiSettingsDialogLibType.h"

#include <NiMemObject.h>
#include <NiTList.h>

class NiBaseRendererOptionsView;
class NiRendererSettings;

// Abstract class, defines interface for NiXXXRendererSetup classes
class NISETTINGSDIALOG_ENTRY NiBaseRendererSetup : public NiMemObject
{
public:
    NiBaseRendererSetup();
    virtual ~NiBaseRendererSetup();

    inline static NiBaseRendererSetup* GetFirstRendererSetup(NiTListIterator& kIter);
    inline static NiBaseRendererSetup* GetNextRendererSetup(NiTListIterator& kIter);

    virtual NiBaseRendererOptionsView* GetRenderOptionsView(
        NiRendererSettings* pkSettings) = 0;
    virtual void ReleaseRendererOptionsView(NiBaseRendererOptionsView* pkROV) = 0;

    virtual efd::SystemDesc::RendererID GetRendererID() const = 0;

    static NiRendererPtr CreateRenderer(
        NiRendererSettings* pkRendererSettings,
        NiWindowRef pWndDevice,
        NiWindowRef pWndFocus);
    
protected:
    virtual NiRendererPtr CreatePlatformRenderer(
        NiRendererSettings* pkRendererSettings,
        NiWindowRef pWndDevice,
        NiWindowRef pWndFocus) = 0;

    static NiTPointerList<NiBaseRendererSetup*> ms_kRendererSetupList;
};

#include "NiBaseRendererSetup.inl"

#endif // NIBASERENDERERSETUP_H