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
#ifndef EE_D3D11RENDEREROPTIONSVIEW_H
#define EE_D3D11RENDEREROPTIONSVIEW_H

#include <ecrD3D11RendererSetup/ecrD3D11RendererSetupLibType.h>
#include <ecrD3D11RendererSetup/D3D11RendererDesc.h>

#include <NiBaseRendererOptionsView.h>

namespace ecr
{

class D3D11RendererDesc;

/**
    D3D11RendererOptionsView is the NiBaseRendererOptionsView that handles the D3D11 dialog.

    This class handles the controls for the Direct3D 11-related settings in the renderer 
    section of the renderer settings dialog.

    These classes work with corresponding D3D11RendererDesc object, which manages the list of 
    available options and store the user's choices to an NiRendererSettings object. This separates 
    the data from the mechanism to view and manipulate that data. The NiD3D10RendererDesc 
    object is instantiated when the settings dialog is created by this object, and destroyed when 
    user presses OK or Cancel in the renderer settings dialog.
*/
class EE_ECRD3D11RENDERERSETUP_ENTRY D3D11RendererOptionsView : public NiBaseRendererOptionsView
{
public:
    /// @cond EMERGENT_INTERNAL

    /// @name Construction and Destruction
    //@{
    /// Constructs a new D3D11RendererOptionsView and initializes is settings from the provided
    /// NiRendererSettings object.
    D3D11RendererOptionsView(NiRendererSettings* pSettings);
    /// Destructor
    virtual ~D3D11RendererOptionsView();
    //@}

    /// @endcond

    /// Returns name of the renderer controlled by this object.
    virtual efd::Char* GetName() const;

    /// Creates and returns a dialog, as a chiled of pParentWnd, with settings for a specific 
    /// renderer.
    virtual NiWindowRef InitDialog(NiWindowRef pParentWnd);

    /// Returns the height of the dialog when in Basic mode.
    virtual efd::UInt32 SetBasicHeight();
    /// Returns the height of the dialog when in Advanced mode.
    virtual efd::UInt32 SetAdvancedHeight();

    /// Returns which renderer this object is responsible for setting up.
    virtual efd::SystemDesc::RendererID GetRendererID() const; 

protected:
    NiWindowRef m_pD3D11DlgHandle;
    D3D11RendererDesc* m_pD3D11RendererDesc;

    // Returns an instance of NiDX9RendererDesc
    virtual NiBaseRendererDesc* GetRendDesc();

    // Init controls in dialog
    virtual void InitAdapterDependentControls();
    void InitD3D11DialogControls();

    // Functions to react on user input
    bool ChangeDisplay();
    bool ChangeFeatureLevel(WORD wID);

private:
    // Message processing functions
    bool ProcessD3D11Command(
        NiWindowRef pDlgHandle,
        WORD wID,
        WORD wNotifyCode);
    static BOOL CALLBACK D3D11RendererOptionsViewWndProc(
        HWND pDlg,
        UINT uiMsg,
        WPARAM wParam,
        LPARAM lParam);
};

}   // End namespace ecr.

#include "D3D11RendererOptionsView.inl"

#endif // EE_D3D11RENDEREROPTIONSVIEW_H