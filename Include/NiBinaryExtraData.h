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
#ifndef NIBINARYEXTRADATA_H
#define NIBINARYEXTRADATA_H

#include "NiExtraData.h"

class NIMAIN_ENTRY NiBinaryExtraData : public NiExtraData
{
    NiDeclareRTTI;
    NiDeclareClone(NiBinaryExtraData);
    NiDeclareStream;
    NiDeclareViewerStrings;

public:
    NiBinaryExtraData(const unsigned int uiSize, char* pcBinaryData);
    ~NiBinaryExtraData();

    inline void SetValue(const unsigned int uiSize, char* pcBinaryData);
    inline void GetValue(unsigned int &uiSize, char* &pcBinaryData) const;

protected:
    // support for streaming
    NiBinaryExtraData();

    char* m_pcBinaryData;
    unsigned int m_uiSize;
};

NiSmartPointer(NiBinaryExtraData);

//--------------------------------------------------------------------------------------------------
//  Inline include
#include "NiBinaryExtraData.inl"

//--------------------------------------------------------------------------------------------------

#endif

