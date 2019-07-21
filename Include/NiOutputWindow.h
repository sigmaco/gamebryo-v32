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

#ifndef NIOUTPUTWINDOW_H
#define NIOUTPUTWINDOW_H

#include "NiRefObject.h"
#include "NiString.h"
#include "NiOS.h"

#include "NiProgramLauncherLibType.h"

/**
    This class encapsulates the Win32 code required to create a dialog that contains
    a single text control used for displaying text messages.
 */
class NIPROGRAMLAUNCHER_ENTRY NiOutputWindow : public NiRefObject
{
public:
    NiOutputWindow();
    virtual ~NiOutputWindow();

    bool Open();
    void Close();

    inline bool IsOpen() const;
    inline HANDLE GetReadHandle();
    inline HANDLE GetWriteHandle();

    bool SetWindowTitle(const char* pcTitle);

    int DisplayMsg(const char* pcFormat, ...);
    int VDisplayMsg(const char* pcFormat, va_list kArgs);
    void Update();

    static NiString GetWindowsLastError();

protected:
    void ResizeTextControl(HWND hDlg);
    bool ReadPipe(char* pcBuf, size_t stBufSize, size_t& stBytesRead);

    static BOOL CALLBACK DialogProcedure(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HANDLE m_hPipeRead;
    HANDLE m_hPipeWrite;

    HWND m_hWndDlg;
};

#include "NiOutputWindow.inl"

#endif // NIOUTPUTWINDOW_H
