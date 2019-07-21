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

//--------------------------------------------------------------------------------------------------
inline bool NiOutputWindow::IsOpen() const
{
    return (m_hWndDlg != NULL);
}

//--------------------------------------------------------------------------------------------------
inline HANDLE NiOutputWindow::GetReadHandle()
{
    return m_hPipeRead;
}

//--------------------------------------------------------------------------------------------------
inline HANDLE NiOutputWindow::GetWriteHandle()
{
    return m_hPipeWrite;
}

//--------------------------------------------------------------------------------------------------