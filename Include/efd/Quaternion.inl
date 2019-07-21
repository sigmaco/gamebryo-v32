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

namespace efd
{

//-------------------------------------------------------------------------------------------------
inline Quaternion::Quaternion()
{
}
//-------------------------------------------------------------------------------------------------
inline Quaternion::Quaternion(efd::Float32 w, efd::Float32 x, efd::Float32 y, efd::Float32 z) :
    m_fW(w), m_fX(x), m_fY(y), m_fZ(z)
{
}
//-------------------------------------------------------------------------------------------------
inline void Quaternion::SetW(efd::Float32 w)
{
    m_fW = w;
}
//-------------------------------------------------------------------------------------------------
inline void Quaternion::SetX(efd::Float32 x)
{
    m_fX = x;
}
//-------------------------------------------------------------------------------------------------
inline void Quaternion::SetY(efd::Float32 y)
{
    m_fY = y;
}
//-------------------------------------------------------------------------------------------------
inline void Quaternion::SetZ(efd::Float32 z)
{
    m_fZ = z;
}
//-------------------------------------------------------------------------------------------------
inline efd::Float32 Quaternion::GetW() const
{
    return m_fW;
}
//-------------------------------------------------------------------------------------------------
inline efd::Float32 Quaternion::GetX() const
{
    return m_fX;
}
//-------------------------------------------------------------------------------------------------
inline efd::Float32 Quaternion::GetY() const
{
    return m_fY;
}
//-------------------------------------------------------------------------------------------------
inline efd::Float32 Quaternion::GetZ() const
{
    return m_fZ;
}
//-------------------------------------------------------------------------------------------------
inline void Quaternion::SetValues(efd::Float32 w, efd::Float32 x, efd::Float32 y, efd::Float32 z)
{
    m_fW = w;
    m_fX = x;
    m_fY = y;
    m_fZ = z;
}
//-------------------------------------------------------------------------------------------------
inline void Quaternion::GetValues(
    efd::Float32& w,
    efd::Float32& x,
    efd::Float32& y,
    efd::Float32& z) const
{
    w = m_fW;
    x = m_fX;
    y = m_fY;
    z = m_fZ;
}
//-------------------------------------------------------------------------------------------------
inline bool Quaternion::operator==(const Quaternion& q) const
{
    return m_fW == q.m_fW && m_fX == q.m_fX && m_fY == q.m_fY && m_fZ == q.m_fZ;
}
//-------------------------------------------------------------------------------------------------
inline bool Quaternion::operator!=(const Quaternion& q) const
{
    return m_fW != q.m_fW || m_fX != q.m_fX || m_fY != q.m_fY || m_fZ != q.m_fZ;
}
//-------------------------------------------------------------------------------------------------
inline Quaternion Quaternion::operator*(efd::Float32 c) const
{
    return Quaternion(c * m_fW, c * m_fX, c * m_fY, c * m_fZ);
}
//-------------------------------------------------------------------------------------------------
inline Quaternion operator*(efd::Float32 c, const Quaternion& q)
{
    return Quaternion(c * q.m_fW, c * q.m_fX, c * q.m_fY, c * q.m_fZ);
}
//-------------------------------------------------------------------------------------------------
inline void Quaternion::ToRotation(Matrix3& rot) const
{
    // operations (*,+,-) = 24

    efd::Float32 tx  = 2.0f*m_fX;
    efd::Float32 ty  = 2.0f*m_fY;
    efd::Float32 tz  = 2.0f*m_fZ;
    efd::Float32 twx = tx*m_fW;
    efd::Float32 twy = ty*m_fW;
    efd::Float32 twz = tz*m_fW;
    efd::Float32 txx = tx*m_fX;
    efd::Float32 txy = ty*m_fX;
    efd::Float32 txz = tz*m_fX;
    efd::Float32 tyy = ty*m_fY;
    efd::Float32 tyz = tz*m_fY;
    efd::Float32 tzz = tz*m_fZ;

    rot.SetCol(0, 1.0f-(tyy+tzz), txy+twz, txz-twy);
    rot.SetCol(1, txy-twz, 1.0f-(txx+tzz), tyz+twx);
    rot.SetCol(2, txz+twy, tyz-twx, 1.0f-(txx+tyy));
}
//-------------------------------------------------------------------------------------------------
inline efd::Float32 Quaternion::Dot(const Quaternion& p, const Quaternion& q)
{
    return p.m_fW*q.m_fW + p.m_fX*q.m_fX + p.m_fY*q.m_fY + p.m_fZ*q.m_fZ;
}
//-------------------------------------------------------------------------------------------------
inline void Quaternion::FromAngleAxisX(efd::Float32 angle)
{
    efd::SinCos(angle * 0.5f, m_fX, m_fW);
    m_fY = m_fZ = 0.0f;
}
//-------------------------------------------------------------------------------------------------
inline void Quaternion::FromAngleAxisY(efd::Float32 angle)
{
    efd::SinCos(angle * 0.5f, m_fY, m_fW);
    m_fX = m_fZ = 0.0f;
}
//-------------------------------------------------------------------------------------------------
inline void Quaternion::FromAngleAxisZ(efd::Float32 angle)
{
    efd::SinCos(angle * 0.5f, m_fZ, m_fW);
    m_fX = m_fY = 0.0f;
}
//-------------------------------------------------------------------------------------------------
inline void Quaternion::FromAngleAxesXYZ(
    efd::Float32 fAngleX, efd::Float32 fAngleY, efd::Float32 fAngleZ)
{
    // Since axes in these cases are the unit basis vectors, we can optimize
    // the FromAxisAngle function for each axis.
    float fsin0, fcos0, fsin1, fcos1, fsin2, fcos2;
    efd::SinCos(fAngleX * 0.5f, fsin0, fcos0);
    efd::SinCos(fAngleY * 0.5f, fsin1, fcos1);
    efd::SinCos(fAngleZ * 0.5f, fsin2, fcos2);

    // Multiply the final component quaternions in proper order to create a
    // single result quaternion, holding the composite rotation. We are
    // performing a reduced version of the quaternion multiply here.
    m_fW = fcos2 * fcos1 * fcos0 + fsin2 * fsin1 * fsin0;
    m_fX = fcos2 * fcos1 * fsin0 - fsin2 * fsin1 * fcos0;
    m_fY = fcos2 * fsin1 * fcos0 + fsin2 * fcos1 * fsin0;
    m_fZ = -fcos2 * fsin1 * fsin0 + fsin2 * fcos1 * fcos0;
}

//------------------------------------------------------------------------------------------------
} //namespace efd
