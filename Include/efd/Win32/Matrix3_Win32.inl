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

//------------------------------------------------------------------------------------------------
// The following macros are supplied only because the Visual C++ optimizer
// does a poor job in many situations of inlining the matrix operations.  The
// input parameters should be single identifiers (to avoid side effects by
// the textual substitution).

// result = mat*pt
#define EE_MATRIX_TIMES_POINT(result,mat,pt) \
{ \
    result.x = (mat).GetEntry(0,0) * (pt).x + \
                 (mat).GetEntry(0,1) * (pt).y + \
                 (mat).GetEntry(0,2) * (pt).z;  \
    result.y = (mat).GetEntry(1,0) * (pt).x + \
                 (mat).GetEntry(1,1) * (pt).y + \
                 (mat).GetEntry(1,2) * (pt).z;  \
    result.z = (mat).GetEntry(2,0) * (pt).x + \
                 (mat).GetEntry(2,1) * (pt).y + \
                 (mat).GetEntry(2,2) * (pt).z;  \
}

// result = mat*pt0+pt1
#define EE_MATRIX_TIMES_POINT_PLUS_POINT(result,mat,pt0,pt1) \
{ \
    result.x = (mat).GetEntry(0,0) * (pt0).x +            \
                 (mat).GetEntry(0,1) * (pt0).y +            \
                 (mat).GetEntry(0,2) * (pt0).z + (pt1).x; \
    result.y = (mat).GetEntry(1,0) * (pt0).x +            \
                 (mat).GetEntry(1,1) * (pt0).y +            \
                 (mat).GetEntry(1,2) * (pt0).z + (pt1).y; \
    result.z = (mat).GetEntry(2,0) * (pt0).x +            \
                 (mat).GetEntry(2,1) * (pt0).y +            \
                 (mat).GetEntry(2,2) * (pt0).z + (pt1).z; \
}

// result = pt*transpose(mat)
#define EE_POINT_TIMES_MATRIX(result,pt,mat) \
{ \
    result.x = (mat).GetEntry(0,0) * (pt).x + \
                 (mat).GetEntry(1,0) * (pt).y + \
                 (mat).GetEntry(2,0) * (pt).z;  \
    result.y = (mat).GetEntry(0,1) * (pt).x + \
                 (mat).GetEntry(1,1) * (pt).y + \
                 (mat).GetEntry(2,1) * (pt).z;  \
    result.z = (mat).GetEntry(0,2) * (pt).x + \
                 (mat).GetEntry(1,2) * (pt).y + \
                 (mat).GetEntry(2,2) * (pt).z;  \
}

//------------------------------------------------------------------------------------------------
inline Matrix3::Matrix3()
{
    // intentionally leave members uninitialized for performance reasons.
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::MakeZero()
{
    SetCol(0, 0.0f, 0.0f, 0.0f);
    SetCol(1, 0.0f, 0.0f, 0.0f);
    SetCol(2, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::GetRow(efd::UInt32 index, Point3& row) const
{
    EE_ASSERT(index <= 2);
    row.x = m_pEntry[index][0];
    row.y = m_pEntry[index][1];
    row.z = m_pEntry[index][2];
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::SetRow(efd::UInt32 index, const Point3& row)
{
    EE_ASSERT(index <= 2);
    m_pEntry[index][0] = row.x;
    m_pEntry[index][1] = row.y;
    m_pEntry[index][2] = row.z;
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::GetRow(
    efd::UInt32 index,
    efd::Float32& f0,
    efd::Float32& f1,
    efd::Float32& f2) const
{
    EE_ASSERT(index <= 2);
    f0 = m_pEntry[index][0];
    f1 = m_pEntry[index][1];
    f2 = m_pEntry[index][2];
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::SetRow(efd::UInt32 index, efd::Float32 f0, efd::Float32 f1, efd::Float32 f2)
{
    EE_ASSERT(index <= 2);
    m_pEntry[index][0] = f0;
    m_pEntry[index][1] = f1;
    m_pEntry[index][2] = f2;
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::GetRow(efd::UInt32 index, efd::Float32* pRow) const
{
    EE_ASSERT(index <= 2);
    pRow[0] = m_pEntry[index][0];
    pRow[1] = m_pEntry[index][1];
    pRow[2] = m_pEntry[index][2];
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::SetRow(efd::UInt32 index, const efd::Float32* pRow)
{
    EE_ASSERT(index <= 2);
    m_pEntry[index][0] = pRow[0];
    m_pEntry[index][1] = pRow[1];
    m_pEntry[index][2] = pRow[2];
}

//------------------------------------------------------------------------------------------------
//  Column access functions
inline void Matrix3::GetCol(efd::UInt32 index, Point3& col) const
{
    EE_ASSERT(index <= 2);
    col.x = m_pEntry[0][index];
    col.y = m_pEntry[1][index];
    col.z = m_pEntry[2][index];
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::SetCol(efd::UInt32 index, const Point3& col)
{
    EE_ASSERT(index <= 2);
    m_pEntry[0][index] = col.x;
    m_pEntry[1][index] = col.y;
    m_pEntry[2][index] = col.z;
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::GetCol(
    efd::UInt32 index,
    efd::Float32& f0,
    efd::Float32& f1,
    efd::Float32& f2) const
{
    EE_ASSERT(index <= 2);
    f0 = m_pEntry[0][index];
    f1 = m_pEntry[1][index];
    f2 = m_pEntry[2][index];
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::SetCol(efd::UInt32 index, efd::Float32 f0, efd::Float32 f1, efd::Float32 f2)
{
    EE_ASSERT(index <= 2);
    m_pEntry[0][index] = f0;
    m_pEntry[1][index] = f1;
    m_pEntry[2][index] = f2;
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::GetCol(efd::UInt32 index, efd::Float32* pCol) const
{
    EE_ASSERT(index <= 2);
    pCol[0] = m_pEntry[0][index];
    pCol[1] = m_pEntry[1][index];
    pCol[2] = m_pEntry[2][index];
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::SetCol(efd::UInt32 index, const efd::Float32* pCol)
{
    EE_ASSERT(index <= 2);
    m_pEntry[0][index] = pCol[0];
    m_pEntry[1][index] = pCol[1];
    m_pEntry[2][index] = pCol[2];
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Matrix3::GetEntry(efd::UInt32 row, efd::UInt32 col) const
{
    EE_ASSERT(row <= 2 && col <= 2);
    return m_pEntry[row][col];
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::SetEntry(efd::UInt32 row, efd::UInt32 col, efd::Float32 entry)
{
    EE_ASSERT(row <= 2 && col <= 2);
    m_pEntry[row][col] = entry;
}

//------------------------------------------------------------------------------------------------
inline Matrix3 Matrix3::operator*(const Matrix3& mat) const
{
    Matrix3 prd;

    prd.m_pEntry[0][0] =
        m_pEntry[0][0]*mat.m_pEntry[0][0]+
        m_pEntry[0][1]*mat.m_pEntry[1][0]+
        m_pEntry[0][2]*mat.m_pEntry[2][0];
    prd.m_pEntry[1][0] =
        m_pEntry[1][0]*mat.m_pEntry[0][0]+
        m_pEntry[1][1]*mat.m_pEntry[1][0]+
        m_pEntry[1][2]*mat.m_pEntry[2][0];
    prd.m_pEntry[2][0] =
        m_pEntry[2][0]*mat.m_pEntry[0][0]+
        m_pEntry[2][1]*mat.m_pEntry[1][0]+
        m_pEntry[2][2]*mat.m_pEntry[2][0];
    prd.m_pEntry[0][1] =
        m_pEntry[0][0]*mat.m_pEntry[0][1]+
        m_pEntry[0][1]*mat.m_pEntry[1][1]+
        m_pEntry[0][2]*mat.m_pEntry[2][1];
    prd.m_pEntry[1][1] =
        m_pEntry[1][0]*mat.m_pEntry[0][1]+
        m_pEntry[1][1]*mat.m_pEntry[1][1]+
        m_pEntry[1][2]*mat.m_pEntry[2][1];
    prd.m_pEntry[2][1] =
        m_pEntry[2][0]*mat.m_pEntry[0][1]+
        m_pEntry[2][1]*mat.m_pEntry[1][1]+
        m_pEntry[2][2]*mat.m_pEntry[2][1];
    prd.m_pEntry[0][2] =
        m_pEntry[0][0]*mat.m_pEntry[0][2]+
        m_pEntry[0][1]*mat.m_pEntry[1][2]+
        m_pEntry[0][2]*mat.m_pEntry[2][2];
    prd.m_pEntry[1][2] =
        m_pEntry[1][0]*mat.m_pEntry[0][2]+
        m_pEntry[1][1]*mat.m_pEntry[1][2]+
        m_pEntry[1][2]*mat.m_pEntry[2][2];
    prd.m_pEntry[2][2] =
        m_pEntry[2][0]*mat.m_pEntry[0][2]+
        m_pEntry[2][1]*mat.m_pEntry[1][2]+
        m_pEntry[2][2]*mat.m_pEntry[2][2];

    return prd;
}

//------------------------------------------------------------------------------------------------
inline Matrix3 Matrix3::operator* (efd::Float32 scalar) const
{
    Matrix3 result;
    result.m_pEntry[0][0] = m_pEntry[0][0] * scalar;
    result.m_pEntry[0][1] = m_pEntry[0][1] * scalar;
    result.m_pEntry[0][2] = m_pEntry[0][2] * scalar;
    result.m_pEntry[1][0] = m_pEntry[1][0] * scalar;
    result.m_pEntry[1][1] = m_pEntry[1][1] * scalar;
    result.m_pEntry[1][2] = m_pEntry[1][2] * scalar;
    result.m_pEntry[2][0] = m_pEntry[2][0] * scalar;
    result.m_pEntry[2][1] = m_pEntry[2][1] * scalar;
    result.m_pEntry[2][2] = m_pEntry[2][2] * scalar;
    return result;
}

//------------------------------------------------------------------------------------------------
inline Point3 Matrix3::operator* (const Point3& pt) const
{
    return Point3
    (
        m_pEntry[0][0]*pt.x + m_pEntry[0][1]*pt.y + m_pEntry[0][2]*pt.z,
        m_pEntry[1][0]*pt.x + m_pEntry[1][1]*pt.y + m_pEntry[1][2]*pt.z,
        m_pEntry[2][0]*pt.x + m_pEntry[2][1]*pt.y + m_pEntry[2][2]*pt.z
  );
}

//------------------------------------------------------------------------------------------------
inline void Matrix3::MakeRotation(efd::Float32 angle, const Point3& axis)
{
    MakeRotation(angle,axis.x,axis.y,axis.z);
}

//------------------------------------------------------------------------------------------------
inline bool Matrix3::operator!=(const Matrix3& mat) const
{
    return !(*this == mat);
}

//------------------------------------------------------------------------------------------------
