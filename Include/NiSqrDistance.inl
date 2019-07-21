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

//--------------------------------------------------------------------------------------------------
inline float NiSqrDistance::Compute(const NiPoint3& kPnt0,
    const NiPoint3& kPnt1)
{
    NiPoint3 kDiff = kPnt0 - kPnt1;
    return kDiff.SqrLength();
}

//--------------------------------------------------------------------------------------------------

