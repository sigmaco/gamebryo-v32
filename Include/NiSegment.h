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
#ifndef NISEGMENT_H
#define NISEGMENT_H

#include "NiCollisionLibType.h"
#include "NiPoint3.h"

class NICOLLISION_ENTRY NiSegment : public NiMemObject
{
public:
    // line kSegment is L(s) = B + s*E for s in [0,1]
    NiPoint3 m_kOrigin;     // B
    NiPoint3 m_kDirection;  // E


    NiPoint3 GetPoint (float fS) const;

    // comparison
    bool operator==(const NiSegment& kSegment) const;
    bool operator!=(const NiSegment& kSegment) const;

    // streaming
    void LoadBinary(NiStream& kStream);
    void SaveBinary(NiStream& kStream);
};

#endif

