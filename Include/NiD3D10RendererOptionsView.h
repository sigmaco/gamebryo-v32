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
#ifndef NID3D10RENDEREROPTIONSVIEW_H
#define NID3D10RENDEREROPTIONSVIEW_H

#include "NiD3D10RendererSetupLibType.h"
#include "NiBaseRendererOptionsView.h"
#include "NiD3D10RendererDesc.h"

class NiD3D10RendererDesc;

class NID3D10RENDERERSETUP_ENTRY NiD3D10RendererOptionsView : public NiBaseRendererOptionsView
{
public:
    NiD3D10RendererOptionsView(NiRendererSettings* pkSettings);
    virtual ~NiD3D10RendererOptionsView();

    // Returns name of a renderer
    virtual char* GetName() const;

    // Dialog creation and controls initialization function
    virtual NiWindowRef InitDialog(NiWindowRef pParentWnd);

    // Height changing functions for basic / advanced views
    virtual unsigned int SetBasicHeight();
    virtual unsigned int SetAdvancedHeight();

    virtual efd::SystemDesc::RendererID GetRendererID() const; 

protected:
    NiWindowRef m_pD3D10DlgHandle;
    NiD3D10RendererDesc* m_pkD3D10RendererDesc;

    // Returns an instance of NiD3D10RendererDesc
    virtual NiBaseRendererDesc* GetRendDesc();

    // Init controls in dialog
    virtual void InitAdapterDependentControls();
    void InitD3D10DialogControls();

    // Functions to react on user input
    bool ChangeDisplay();

private:
    // Message processing functions
    bool ProcessD3D10Command(
        NiWindowRef pDlgHandle,
        WORD wID,
        WORD wNotifyCode);
    static BOOL CALLBACK D3D10RendererOptionsViewWndProc(
        HWND pDlg,
        UINT uiMsg,
        WPARAM wParam,
        LPARAM lParam);
};

#include "NiD3D10RendererOptionsView.inl"

#endif // NID3D10RENDEREROPTIONSVIEW_H