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
#ifndef NISWITCHSTRINGEXTRADATA_H
#define NISWITCHSTRINGEXTRADATA_H

#include "NiExtraData.h"

class NIMAIN_ENTRY NiSwitchStringExtraData : public NiExtraData
{
    NiDeclareRTTI;
    NiDeclareClone(NiSwitchStringExtraData);
    NiDeclareStream;
    NiDeclareViewerStrings;

public:
    NiSwitchStringExtraData(const unsigned int uiSize, const char** ppcValue,
            const int iIndex);
    ~NiSwitchStringExtraData ();

    void SetValue(const unsigned int uiSize, const char** ppcValue,
            const int iIndex);
    inline void GetValue(unsigned int &uiSize, char** &ppcValue,
            int &iIndex) const;

    inline void SetActiveIndex(const int iIndex);
    inline int GetActiveIndex() const;

protected:
    // support for streaming
    NiSwitchStringExtraData ();

    unsigned int m_uiSize;
    char** m_ppcValue;

    int m_iIndex;
};
NiSmartPointer(NiSwitchStringExtraData);

//--------------------------------------------------------------------------------------------------
//  Inline include
#include "NiSwitchStringExtraData.inl"

//--------------------------------------------------------------------------------------------------

#endif

