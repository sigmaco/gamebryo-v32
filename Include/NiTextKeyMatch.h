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
#ifndef NITEXTKEYMATCH_H
#define NITEXTKEYMATCH_H

#include "NiAnimationLibType.h"
#include <NiObject.h>
#include <NiFixedString.h>

class NIANIMATION_ENTRY NiTextKeyMatch : public NiObject
{
    NiDeclareRTTI;
public:
    NiTextKeyMatch(const NiFixedString& kMatchKey);
    virtual ~NiTextKeyMatch();

    virtual bool IsKeyMatch(const NiFixedString& kTextKey);
    operator const char*(void);
    inline const NiFixedString& GetLastMatchedKey() const;
private:
    NiFixedString m_kLastKeyMatched;

protected:
    NiFixedString m_kMatchKey;
    inline void SetLastMatchedKey(const NiFixedString& kTextKey);
};

#include "NiTextKeyMatch.inl"

NiSmartPointer(NiTextKeyMatch);

#endif // #ifndef NITEXTKEYMATCH_H
