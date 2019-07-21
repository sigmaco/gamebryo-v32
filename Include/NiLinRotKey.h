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
#ifndef NILINROTKEY_H
#define NILINROTKEY_H

#include "NiRotKey.h"

class NIANIMATION_ENTRY NiLinRotKey : public NiRotKey
{
    NiDeclareAnimationStream;
public:
    // construction
    NiLinRotKey ();
    NiLinRotKey (float fTime, const NiQuaternion& quat);
    NiLinRotKey (float fTime, float fAngle, const NiPoint3& axis);
};

NiRegisterAnimationStream(NiLinRotKey);

#include "NiLinRotKey.inl"

#endif

