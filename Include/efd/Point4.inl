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
//  Point4 inline functions

namespace efd
{

//--------------------------------------------------------------------------------------------------
inline Point4::Point4()
{
    /* */
}

//--------------------------------------------------------------------------------------------------
inline Point4::Point4(float fX, float fY, float fZ, float fW)
{
    Set(fX, fY, fZ, fW);
}

//--------------------------------------------------------------------------------------------------
inline Point4::Point4(const Point3& kPt, float fW)
{
    Set(kPt, fW);
}

//--------------------------------------------------------------------------------------------------
inline Point4::Point4(const efd::Point4& kPt)
{
    Set(kPt.X(), kPt.Y(), kPt.Z(), kPt.W());
}

//--------------------------------------------------------------------------------------------------
inline Point4::operator Point3()
{
    return Point3(X(), Y(), Z());
}

//--------------------------------------------------------------------------------------------------
inline void Point4::Set(const Point3& kPt, float fW)
{
    Set(kPt.x, kPt.y, kPt.z, fW);
}

//--------------------------------------------------------------------------------------------------
inline void Point4::Set3VectorW0(float fX, float fY, float fZ)
{
    Set(fX, fY, fZ, 0.0f);
}

//--------------------------------------------------------------------------------------------------
inline float Point4::X() const
{
    return (*this)[0];
}

//--------------------------------------------------------------------------------------------------
inline float Point4::Y() const
{
    return (*this)[1];
}

//--------------------------------------------------------------------------------------------------
inline float Point4::Z() const
{
    return (*this)[2];
}

//--------------------------------------------------------------------------------------------------
inline float Point4::W() const
{
    return (*this)[3];
}

//--------------------------------------------------------------------------------------------------
inline void Point4::SetX(float fX)
{
    Set(0, fX);
}

//--------------------------------------------------------------------------------------------------
inline void Point4::SetY(float fY)
{
    Set(1, fY);
}

//--------------------------------------------------------------------------------------------------
inline void Point4::SetZ(float fZ)
{
    Set(2, fZ);
}

//--------------------------------------------------------------------------------------------------
inline void Point4::SetW(float fW)
{
    Set(3, fW);
}

//--------------------------------------------------------------------------------------------------
inline Point4 Point4::operator- () const
{
    return (*this) * -1;
}

//--------------------------------------------------------------------------------------------------
inline Point4 Point4::operator+ (const Point4& kPt) const
{
    Point4 kResult = *this;
    kResult += kPt;
    return kResult;
}

//--------------------------------------------------------------------------------------------------
inline Point4 Point4::operator- (const Point4& kPt) const
{
    Point4 kResult = *this;
    kResult -= kPt;
    return kResult;
}

//--------------------------------------------------------------------------------------------------
inline Point4 Point4::operator* (float fScalar) const
{
    Point4 kResult = *this;
    kResult *= fScalar;
    return kResult;
}

//--------------------------------------------------------------------------------------------------
inline Point4 Point4::operator/ (float fScalar) const
{
    Point4 kResult = *this;
    kResult /= fScalar;
    return kResult;
}

//--------------------------------------------------------------------------------------------------
inline bool Point4::operator!=(const Point4& kPt) const
{
    bool bEquals = (*this)==kPt;
    return !bEquals;
}

//--------------------------------------------------------------------------------------------------
inline void Point4::CompressNormalizedIntoXY(const Point3& point)
{
    EE_ASSERT(point.z > 0.0f);

    float factor = 1.0f / point.z;
    SetX(point.x * factor);
    SetY(point.y * factor);
}

//--------------------------------------------------------------------------------------------------
inline void Point4::CompressNormalizedIntoZW(const Point3& point)
{
    EE_ASSERT(point.z > 0.0f);

    float factor = 1.0f / point.z;
    SetZ(point.x * factor);
    SetW(point.y * factor);
}

//--------------------------------------------------------------------------------------------------
inline void Point4::DecompressXYIntoNormalized(Point3& point)
{
    point.x = X();
    point.y = Y();
    point.z = 1.0f;
    point.Unitize();
}

//--------------------------------------------------------------------------------------------------
inline void Point4::DecompressHighDetailIntoNormalized(Point3& point)
{
    if (W() == FLT_MAX)
    {
        point.x = X();
        point.y = Y();
        point.z = Z();
    }
    else
    {
        point.x = X();
        point.y = Y();
        point.z = 1.0f;
    }
    point.Unitize();
}

//--------------------------------------------------------------------------------------------------
inline void Point4::DecompressZWIntoNormalized(Point3& point)
{
    point.x = Z();
    point.y = W();
    point.z = 1.0f;
    point.Unitize();
}

//--------------------------------------------------------------------------------------------------
} // namespace efd
