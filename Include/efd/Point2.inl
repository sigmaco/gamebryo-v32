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
inline Point2::Point2()
{
}


//-------------------------------------------------------------------------------------------------
inline Point2::Point2(efd::Float32 x0, efd::Float32 y0)
{
    x = x0;
    y = y0;
}
//-------------------------------------------------------------------------------------------------
inline efd::Float32& Point2::operator[](efd::SInt32 i)
{
    EE_ASSERT(i < 2);
    const efd::Float32* base = &x;
    return (efd::Float32&)base[i];
}


//-------------------------------------------------------------------------------------------------
inline const efd::Float32& Point2::operator[](efd::SInt32 i) const
{
    EE_ASSERT(i < 2);
    const efd::Float32* base = &x;
    return (efd::Float32&)base[i];
}


//-------------------------------------------------------------------------------------------------
inline bool Point2::operator==(const Point2& pt) const
{
    return (x == pt.x && y == pt.y);
}


//-------------------------------------------------------------------------------------------------
inline bool Point2::operator!=(const Point2& pt) const
{
    return !operator==(pt);
}


//-------------------------------------------------------------------------------------------------
inline Point2 Point2::operator+(const Point2& pt) const
{
    Point2 result = *this;

    result.x += pt.x;
    result.y += pt.y;

    return result;
}


//-------------------------------------------------------------------------------------------------
inline Point2 Point2::operator-(const Point2& pt) const
{
    Point2 result = *this;

    result.x -= pt.x;
    result.y -= pt.y;

    return result;
}


//-------------------------------------------------------------------------------------------------
inline efd::Float32 Point2::operator*(const Point2& pt) const
{
    return x*pt.x + y*pt.y;
}


//-------------------------------------------------------------------------------------------------
inline Point2 Point2::operator*(efd::Float32 scalar) const
{
    Point2 result = *this;

    result.x *= scalar;
    result.y *= scalar;

    return result;
}


//-------------------------------------------------------------------------------------------------
inline Point2 Point2::operator/(efd::Float32 scalar) const
{
    Point2 result = *this;

    result.x /= scalar;
    result.y /= scalar;

    return result;
}


//-------------------------------------------------------------------------------------------------
inline Point2 Point2::operator-() const
{
    return Point2(-x,-y);
}
//-------------------------------------------------------------------------------------------------
inline Point2 operator*(efd::Float32 scalar, const Point2& pt)
{
    return pt*scalar;
}


//-------------------------------------------------------------------------------------------------
inline Point2& Point2::operator+=(const Point2& pt)
{
    x += pt.x;
    y += pt.y;
    return *this;
}


//-------------------------------------------------------------------------------------------------
inline Point2& Point2::operator-=(const Point2& pt)
{
    x -= pt.x;
    y -= pt.y;
    return *this;
}


//-------------------------------------------------------------------------------------------------
inline Point2& Point2::operator*=(efd::Float32 scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}


//-------------------------------------------------------------------------------------------------
inline Point2& Point2::operator/=(efd::Float32 scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}


//-------------------------------------------------------------------------------------------------
inline Point2 Point2::ComponentProduct(const Point2& p0, const Point2& p1)
{
    return Point2(p0.x*p1.x, p0.y*p1.y);
}


//-------------------------------------------------------------------------------------------------
inline efd::Float32 Point2::Length() const
{
    return efd::Sqrt(x*x + y*y);
}


//-------------------------------------------------------------------------------------------------
inline efd::Float32 Point2::SqrLength() const
{
    return x*x + y*y;
}


//-------------------------------------------------------------------------------------------------
inline efd::Float32 Point2::Dot(const Point2& pt) const
{
    return x*pt.x + y*pt.y;
}


//-------------------------------------------------------------------------------------------------
inline efd::Float32 Point2::Unitize()
{
    efd::Float32 length = Length();

    if (length > 1e-06f)
    {
        efd::Float32 recip = 1.0f / length;
        x *= recip;
        y *= recip;
    }
    else
    {
        x = 0.0f;
        y = 0.0f;
        length = 0.0f;
    }

    return length;
}

//-------------------------------------------------------------------------------------------------
inline Float32 Point2::GetX() const
{
    return x;
}
//-------------------------------------------------------------------------------------------------
inline Float32 Point2::GetY() const
{
    return y;
}
//-------------------------------------------------------------------------------------------------


} // end namespace efd

