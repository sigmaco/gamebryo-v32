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
//-------------------------------------------------------------------------------------------------
//  Point4 inline functions

namespace efd
{

//-------------------------------------------------------------------------------------------------
EE_FORCEINLINE float Point4::operator[](int iComponent) const
{
    EE_ASSERT(iComponent >= 0);
    EE_ASSERT(iComponent < 4);

    return m_afPt[iComponent];
}
//-------------------------------------------------------------------------------------------------
EE_FORCEINLINE float Point4::Set(unsigned int uiComponent, float fValue)
{
    EE_ASSERT(uiComponent < 4);

    m_afPt[uiComponent] = fValue;

    return m_afPt[uiComponent];
}
//-------------------------------------------------------------------------------------------------
inline void Point4::MakeZero()
{
    Set(0.0f, 0.0f, 0.0f, 0.0f);
}
//-------------------------------------------------------------------------------------------------
inline void Point4::Set(float fX, float fY, float fZ, float fW)
{
    SetX(fX);
    SetY(fY);
    SetZ(fZ);
    SetW(fW);
}
//-------------------------------------------------------------------------------------------------
inline void Point4::Set3VectorW0(const Point3& kPt)
{
    Set(kPt, 0.0f);
}
//-------------------------------------------------------------------------------------------------
inline Point4 Point4::operator+= (const Point4& kPt)
{
    m_afPt[0] += kPt.m_afPt[0];
    m_afPt[1] += kPt.m_afPt[1];
    m_afPt[2] += kPt.m_afPt[2];
    m_afPt[3] += kPt.m_afPt[3];
    return *this;
}
//-------------------------------------------------------------------------------------------------
inline Point4 Point4::operator-= (const Point4& kPt)
{
    m_afPt[0] -= kPt.m_afPt[0];
    m_afPt[1] -= kPt.m_afPt[1];
    m_afPt[2] -= kPt.m_afPt[2];
    m_afPt[3] -= kPt.m_afPt[3];
    return *this;
}
//-------------------------------------------------------------------------------------------------
inline Point4 Point4::operator*= (float fScalar)
{
    m_afPt[0] = m_afPt[0] * fScalar;
    m_afPt[1] = m_afPt[1] * fScalar;
    m_afPt[2] = m_afPt[2] * fScalar;
    m_afPt[3] = m_afPt[3] * fScalar;

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline Point4 Point4::operator/= (float fScalar)
{
    m_afPt[0] = m_afPt[0] / fScalar;
    m_afPt[1] = m_afPt[1] / fScalar;
    m_afPt[2] = m_afPt[2] / fScalar;
    m_afPt[3] = m_afPt[3] / fScalar;
    return *this;
}
//-------------------------------------------------------------------------------------------------
inline bool Point4::operator== (const Point4& pt) const
{
    return
        pt.m_afPt[0] == m_afPt[0] &&
        pt.m_afPt[1] == m_afPt[1] &&
        pt.m_afPt[2] == m_afPt[2] &&
        pt.m_afPt[3] == m_afPt[3];
}
//-------------------------------------------------------------------------------------------------
inline Point4& Point4::operator=(const Point4& kPt)
{
    m_afPt[0] = kPt.m_afPt[0];
    m_afPt[1] = kPt.m_afPt[1];
    m_afPt[2] = kPt.m_afPt[2];
    m_afPt[3] = kPt.m_afPt[3];
    return *this;
}
//-------------------------------------------------------------------------------------------------

}; // namespace efd
