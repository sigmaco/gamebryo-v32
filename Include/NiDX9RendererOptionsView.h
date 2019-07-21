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
#ifndef NIDX9RENDEREROPTIONSVIEW_H
#define NIDX9RENDEREROPTIONSVIEW_H

#include "NiDX9RendererSetupLibType.h"
#include "NiBaseRendererOptionsView.h"
#include "NiDX9RendererDesc.h"

class NiDX9RendererDesc;

class NIDX9RENDERERSETUP_ENTRY NiDX9RendererOptionsView : public NiBaseRendererOptionsView
{
public:
    NiDX9RendererOptionsView(NiRendererSettings* pkSettings);
    virtual ~NiDX9RendererOptionsView();

    // Returns name of a renderer
    virtual char* GetName() const;

    // Dialog creation and controls initialization function
    virtual NiWindowRef InitDialog(NiWindowRef pParentWnd);

    virtual efd::SystemDesc::RendererID GetRendererID() const; 

protected:
    NiDX9RendererDesc* m_pkDX9RendererDesc;

    // Returns an instance of NiDX9RendererDesc
    virtual NiBaseRendererDesc* GetRendDesc();

};

#include "NiDX9RendererOptionsView.inl"

#endif // NIDX9RENDEREROPTIONSVIEW_H