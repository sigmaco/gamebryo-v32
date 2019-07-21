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
//  NiPoint3 inline functions

//--------------------------------------------------------------------------------------------------
// The following macros are supplied only because the Visual C++ optimizer
// does a poor job in many situations of inlining the point operations.  The
// input parameters should be single identifiers (to avoid side effects by
// the textual substitution).

// result = pt0+pt1
#define NiPointPlusPoint(result,pt0,pt1) \
{ \
    result.x = (pt0).x + (pt1).x; \
    result.y = (pt0).y + (pt1).y; \
    result.z = (pt0).z + (pt1).z; \
}

// result = pt0-pt1
#define NiPointMinusPoint(result,pt0,pt1) \
{ \
    result.x = (pt0).x - (pt1).x; \
    result.y = (pt0).y - (pt1).y; \
    result.z = (pt0).z - (pt1).z; \
}

// result = Dot(pt0,pt1)
#define NiPointDotPoint(result,pt0,pt1) \
{ \
    result = (pt0).x * (pt1).x + (pt0).y * (pt1).y + (pt0).z * (pt1).z; \
}

// result = s*pt
#define NiScalarTimesPoint(result,s,pt) \
{ \
    result.x = s * (pt).x; \
    result.y = s * (pt).y; \
    result.z = s * (pt).z; \
}

// result = s*pt0+pt1
#define NiScalarTimesPointPlusPoint(result,s,pt0,pt1) \
{ \
    result.x = s * (pt0).x + (pt1).x; \
    result.y = s * (pt0).y + (pt1).y; \
    result.z = s * (pt0).z + (pt1).z; \
}

// result = s0*pt0+s1*pt1
#define NiScalarTimesPointPlusScalarTimesPoint(result,s0,pt0,s1,pt1) \
{ \
    result.x = s0 * (pt0).x + s1 * (pt1).x; \
    result.y = s0 * (pt0).y + s1 * (pt1).y; \
    result.z = s0 * (pt0).z + s1 * (pt1).z; \
}

// result = s0*pt0+s1*pt1+s2*pt2
#define NiAddThreeWeightedPoints(result,s0,pt0,s1,pt1,s2,pt2) \
{ \
    result.x = s0 * (pt0).x + s1 * (pt1).x + s2 * (pt2).x; \
    result.y = s0 * (pt0).y + s1 * (pt1).y + s2 * (pt2).y; \
    result.z = s0 * (pt0).z + s1 * (pt1).z + s2 * (pt2).z; \
}

// result = s0*pt0+s1*pt1+s2*pt2+s3*pt3
#define NiAddFourWeightedPoints(result,s0,pt0,s1,pt1,s2,pt2,s3,pt3) \
{ \
    result.x = s0 * (pt0).x + s1 * (pt1).x + s2 * (pt2).x + s3 * (pt3).x; \
    result.y = s0 * (pt0).y + s1 * (pt1).y + s2 * (pt2).y + s3 * (pt3).y; \
    result.z = s0 * (pt0).z + s1 * (pt1).z + s2 * (pt2).z + s3 * (pt3).z; \
}
