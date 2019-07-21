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
#ifndef NISETTINGSDIALOG_H
#define NISETTINGSDIALOG_H

#include "NiSettingsDialogLibType.h"
#include <NiRefObject.h>
#include <NiTArray.h>

class NiBaseTabController;
NiSmartPointer(NiRendererSettings);

class NISETTINGSDIALOG_ENTRY NiSettingsDialog: public NiRefObject
{
public:
    NiSettingsDialog(NiRendererSettings* pkSettings);
    virtual ~NiSettingsDialog();

    // Add custom tab to dlg's tab control. Must be called before InitDialog
    bool AddTabController(NiBaseTabController* pkTabCtrl);

    // Initialize the dialog. Return code must be checked.
    bool InitDialog(NiInstanceRef pInstance, NiWindowRef pParentWnd = NULL);

    // Show dialog. Must be called after InitDialog().
    bool ShowDialog(NiWindowRef pWnd, NiAcceleratorRef pAccel);

    // Show messagebox with info about error, returned by GetLastError()
    static void ReportWinAPIError(DWORD dwErrorCode, char* pcErrorText);

protected:
    NiWindowRef m_pDlgHandle;
    NiTPrimitiveArray<NiBaseTabController*> m_kTabArray;
    NiRendererSettings* m_pkSettings;
    bool m_bViewAdvanced;
    bool m_bInitialized;
    bool m_bDlgOK;

    void DestroyDialog();

    // Create always present (Renderer) NiXXXTabController
    bool CreateInternalTabControllers(NiWindowRef pDlgHandle);
    // Initialize / delete tab controller(s)
    NiWindowRef InitTabController(unsigned int uiIdx);
    void DeleteTabControllers();

    // Center window on the screen
    void CenterWindow();

    // Init controls in dialog
    bool InitDialogControls();

    // Move control up or down for changing to basic / advanced size
    void RepositionControl(int iControl, int iDeltaHeight);
    void ChangeSize();

    // Functions to react on user input
    bool ChangeAdvanced();
    bool ChangeNoDialog();
    bool ChangeSaveSettings();
    void ActivateTab(unsigned int uiTabIdx);
    void DeactivateTab(unsigned int uiTabIdx);

    // Message processing functions
    bool ProcessCommand(NiWindowRef pDlgHandle, WORD wID, WORD wNotifyCode);
    static BOOL CALLBACK SettingsWndProc(
        HWND pDlg,
        UINT uiMsg,
        WPARAM wParam,
        LPARAM lParam);
};

#endif // NISETTINGSDIALOG_H