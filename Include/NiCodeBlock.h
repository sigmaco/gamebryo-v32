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
#ifndef NICODEBLOCK_H
#define NICODEBLOCK_H

#include "NiString.h"

class NIMAIN_ENTRY NiCodeBlock : public NiRefObject
{
public:
    NiCodeBlock();
    ~NiCodeBlock();

    const NiFixedString& GetLanguage() const;
    void SetLanguage(const NiFixedString& kStr);

    const NiFixedString& GetPlatform() const;
    void SetPlatform(const NiFixedString& kStr);

    const NiFixedString& GetTarget() const;
    void SetTarget(const NiFixedString& kStr);

    const NiString& GetText() const;
    void SetText(const NiString& kCode);

protected:
    NiFixedString m_kLanguage;
    NiFixedString m_kPlatform;
    NiFixedString m_kTarget;
    NiString m_kText;
};

typedef efd::SmartPointer<NiCodeBlock> NiCodeBlockPtr;

#endif  //#ifndef NICODEBLOCK_H
