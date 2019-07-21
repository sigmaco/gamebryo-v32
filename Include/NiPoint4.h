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
#ifndef NIPOINT4_H
#define NIPOINT4_H

#include "NiPoint3.h"

#ifdef __SPU__
#include <vectormath/cpp/vectormath_aos.h>
#endif

#include <efd/Point4.h>

class NIMAIN_ENTRY NiPoint4 : public efd::Point4
{
public:
    /// Constructor
    inline NiPoint4() : efd::Point4() {}

    /// Constructor
    inline NiPoint4(float fX, float fY, float fZ, float fW) :
        efd::Point4(fX, fY, fZ, fW) {}

    /// Constructor
    inline NiPoint4(const NiPoint3& kPt, float fW = 1.0f) : efd::Point4(kPt, fW) {}

    /// Constructor
    inline NiPoint4(const efd::Point4& kPt) : efd::Point4(kPt) {}

    /// Conversion from NiPoint4 to NiPoint3. Simply drops the w component.
    inline operator NiPoint3() { return NiPoint3(X(), Y(), Z()); }
};

#endif // NIPOINT4_H
