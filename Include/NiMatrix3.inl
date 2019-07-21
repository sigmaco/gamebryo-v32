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
//  NiMatrix3 inline functions

//--------------------------------------------------------------------------------------------------
// The following macros are supplied only because the Visual C++ optimizer
// does a poor job in many situations of inlining the matrix operations.  The
// input parameters should be single identifiers (to avoid side effects by
// the textual substitution).

// result = mat*pt
#define NiMatrixTimesPoint EE_MATRIX_TIMES_POINT

// result = mat*pt0+pt1
#define NiMatrixTimesPointPlusPoint EE_MATRIX_TIMES_POINT_PLUS_POINT

// result = pt*transpose(mat)
#define NiPointTimesMatrix EE_POINT_TIMES_MATRIX

//--------------------------------------------------------------------------------------------------
inline NiMatrix3::NiMatrix3() : efd::Matrix3()
{
}

//--------------------------------------------------------------------------------------------------
inline NiMatrix3::NiMatrix3(const NiPoint3& col0, const NiPoint3& col1,
    const NiPoint3& col2) : efd::Matrix3(col0, col1, col2)
{
}

//--------------------------------------------------------------------------------------------------
inline NiMatrix3::NiMatrix3(const efd::Matrix3& kMatrix)
{
#if defined(_PS3) || defined(_XENON)
    m_pEntry[0] = ((NiMatrix3*)&kMatrix)->m_pEntry[0];
    m_pEntry[1] = ((NiMatrix3*)&kMatrix)->m_pEntry[1];
    m_pEntry[2] = ((NiMatrix3*)&kMatrix)->m_pEntry[2];
#else
    EE_COMPILETIME_ASSERT(sizeof(m_pEntry) == sizeof(float)*9);
    NiMemcpy(m_pEntry, ((NiMatrix3*)&kMatrix)->m_pEntry, sizeof(float)*9);
#endif
}

//--------------------------------------------------------------------------------------------------
