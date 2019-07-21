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
#ifndef NICOLOREXTRADATA_H
#define NICOLOREXTRADATA_H

#include "NiColor.h"
#include "NiExtraData.h"

class NIMAIN_ENTRY NiColorExtraData : public NiExtraData
{
    NiDeclareRTTI;
    NiDeclareClone(NiColorExtraData);
    NiDeclareStream;
    NiDeclareViewerStrings;

public:
    NiColorExtraData(const NiColorA kColorA);
    NiColorExtraData(const NiColor kColor);
    ~NiColorExtraData();

    void SetValue(const NiColorA kColorA);  // 4-tuple accessors
    inline const NiColorA GetValue() const;

    void SetValue(const NiColor kColor);    // 3-tuple accessors
    inline const NiColor GetValueColor3() const;

    inline void SetRed(const float fRed);  // Component accessors
    inline void SetGreen(const float fGreen);
    inline void SetBlue(const float fBlue);
    inline void SetAlpha(const float fAlpha);
    inline float GetRed() const;
    inline float GetGreen() const;
    inline float GetBlue() const;
    inline float GetAlpha() const;

protected:
    // support for streaming
    NiColorExtraData();

    NiColorA m_kColorA;
};

NiSmartPointer(NiColorExtraData);

//--------------------------------------------------------------------------------------------------
//  Inline include
#include "NiColorExtraData.inl"

//--------------------------------------------------------------------------------------------------

#endif

