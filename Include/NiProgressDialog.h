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
#ifndef NI_PROGRESSDIALOG_H
#define NI_PROGRESSDIALOG_H

#include "NiDialog.h"
#include "NiString.h"

class NIPLUGINTOOLKIT_ENTRY NiProgressDialog : public NiDialog
{
    public:
        NiProgressDialog(NiString strTitle);

        // Method for creating a completely modal dialog
        inline virtual int DoModal(){return IDCANCEL;}

        void SetLineOne(NiString strFullText);
        void SetLineTwo(NiString strFullText);

        void StepIt();
        void SetRangeSpan(unsigned int uiSpan);
        void SetPosition(unsigned int uiPos);

    protected:
        NiWindowRef m_hWndPB;
        float m_fPercentageComplete;
        NiString m_strTitle;
        float m_fPercentage;
        NiString m_strLineOneText;
        NiString m_strLineTwoText;

        NiProgressDialog() {};
        NiProgressDialog(NiProgressDialog&){};

        virtual void InitDialog();

        virtual BOOL OnCommand(int iWParamLow, int iWParamHigh, long lParam);

        virtual BOOL OnMessage(unsigned int uiMessage, int iWParamLow,
            int iWParamHigh, long lParam);

        virtual void OnClose();

        virtual void OnDestroy();

};

NiSmartPointer(NiProgressDialog);

#endif
