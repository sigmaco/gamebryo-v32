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
#ifndef NIGEOMETRICUTILS_H
#define NIGEOMETRICUTILS_H

#include "NiPoint3.h"

class NIMAIN_ENTRY NiGeometricUtils
{
public:
    static float GetTriArea(const NiPoint3& kP0, const NiPoint3& kP1,
        const NiPoint3& kP2);
    static NiPoint3 GetTriCenter(const NiPoint3& kP0, const NiPoint3& kP1,
        const NiPoint3& kP2);
    static NiPoint3 GetTriNormal(const NiPoint3& kP0, const NiPoint3& kP1,
        const NiPoint3& kP2);
    static float GetDistToSeg(const NiPoint3& kPoint,
        const NiPoint3& kSegPoint, const NiPoint3& kSegDirection);
    static float GetDistSqrToSeg(const NiPoint3& kPoint,
        const NiPoint3& kSegPoint, const NiPoint3& kSegDirection);

protected:
    inline static NiPoint3 SegDistHelper(const NiPoint3& kPoint,
        const NiPoint3& kSegPoint, const NiPoint3& kSegDirection);
};

#include "NiGeometricUtils.inl"

#endif //NIGEOMETRICUTILS_H
