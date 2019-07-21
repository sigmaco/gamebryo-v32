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

namespace efd
{

//------------------------------------------------------------------------------------------------
inline Point3::Point3()
{
    // intentionally leave members uninitialized for performance reasons.
}

//------------------------------------------------------------------------------------------------
inline Point3::Point3(efd::Float32 x0, efd::Float32 y0, efd::Float32 z0)
{
    x = x0;
    y = y0;
    z = z0;
}

//------------------------------------------------------------------------------------------------
inline const efd::Float32& Point3::operator[](efd::SInt32 i) const
{
    // warning:  safe for 4-byte aligned class member data
    EE_ASSERT(i < 3);
    const efd::Float32* base = &x;
    return (efd::Float32&)base[i];
}

//------------------------------------------------------------------------------------------------
inline efd::Float32& Point3::operator[](efd::SInt32 i)
{
    // warning:  safe for 4-byte aligned class member data
    EE_ASSERT(i < 3);
    efd::Float32* base = &x;
    return (efd::Float32&)base[i];
}

//------------------------------------------------------------------------------------------------
inline bool Point3::operator==(const Point3& pt) const
{
    return (x == pt.x && y == pt.y && z == pt.z);
}

//------------------------------------------------------------------------------------------------
inline bool Point3::operator!=(const Point3& pt) const
{
    return !(*this == pt);
}

//------------------------------------------------------------------------------------------------
inline Point3& Point3::operator=(const Point3& pt)
{
    x = pt.x;
    y = pt.y;
    z = pt.z;
    return *this;
}

//------------------------------------------------------------------------------------------------
inline Point3 Point3::operator+(const Point3& pt) const
{
    return Point3(x+pt.x, y+pt.y, z+pt.z);
}

//------------------------------------------------------------------------------------------------
inline Point3 Point3::operator-(const Point3& pt) const
{
    return Point3(x-pt.x, y-pt.y, z-pt.z);
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Point3::operator*(const Point3& pt) const
{
    return x*pt.x + y*pt.y + z*pt.z;
}

//------------------------------------------------------------------------------------------------
inline Point3 Point3::operator*(efd::Float32 scalar) const
{
    return Point3(scalar*x, scalar*y, scalar*z);
}

//------------------------------------------------------------------------------------------------
inline Point3 Point3::operator/(efd::Float32 scalar) const
{
    efd::Float32 invScalar = 1.0f/scalar;
    return Point3(invScalar*x, invScalar*y, invScalar*z);
}

//------------------------------------------------------------------------------------------------
inline Point3 Point3::operator-() const
{
    return Point3(-x,-y,-z);
}

//------------------------------------------------------------------------------------------------
inline Point3 operator*(efd::Float32 scalar, const Point3& pt)
{
    return Point3(scalar*pt.x, scalar*pt.y, scalar*pt.z);
}

//------------------------------------------------------------------------------------------------
inline Point3& Point3::operator+=(const Point3& pt)
{
    x += pt.x;
    y += pt.y;
    z += pt.z;

    return *this;
}

//------------------------------------------------------------------------------------------------
inline Point3& Point3::operator-=(const Point3& pt)
{
    x -= pt.x;
    y -= pt.y;
    z -= pt.z;

    return *this;
}

//------------------------------------------------------------------------------------------------
inline Point3& Point3::operator*=(efd::Float32 scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

//------------------------------------------------------------------------------------------------
inline Point3& Point3::operator/=(efd::Float32 scalar)
{
    efd::Float32 invScalar = 1.0f/scalar;

    x *= invScalar;
    y *= invScalar;
    z *= invScalar;

    return *this;
}

//------------------------------------------------------------------------------------------------
inline Point3 Point3::ComponentProduct(const Point3& p0, const Point3& p1)
{
    return Point3(p0.x*p1.x, p0.y*p1.y, p0.z*p1.z);
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Point3::Length() const
{
    return efd::Sqrt(x*x + y*y + z*z);
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Point3::SqrLength() const
{
    return x*x + y*y + z*z;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Point3::Dot(const Point3& pt) const
{
    return x*pt.x + y*pt.y + z*pt.z;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Point3::Unitize()
{
    efd::Float32 length = Length();

    if (length > 1e-06f)
    {
        efd::Float32 recip = 1.0f/length;
        x *= recip;
        y *= recip;
        z *= recip;
    }
    else
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        length = 0.0f;
    }

    return length;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 Point3::Unitize(const Point3& zeroLengthDefault)
{
    efd::Float32 length = Length();

    if (length > 1e-06f)
    {
        efd::Float32 recip = 1.0f/length;
        x *= recip;
        y *= recip;
        z *= recip;
    }
    else
    {
        x = zeroLengthDefault.x;
        y = zeroLengthDefault.y;
        z = zeroLengthDefault.z;
        length = 0.0f;
    }

    return length;
}

//------------------------------------------------------------------------------------------------
inline Point3 Point3::Cross(const Point3& pt) const
{
    return Point3(
        y*pt.z - z*pt.y,
        z*pt.x - x*pt.z,
        x*pt.y - y*pt.x);
}

//------------------------------------------------------------------------------------------------
inline Point3 Point3::UnitCross(const Point3& pt) const
{
    Point3 cross(
        y*pt.z - z*pt.y,
        z*pt.x - x*pt.z,
        x*pt.y - y*pt.x);

    efd::Float32 length = cross.Length();
    if (length > 1e-06f)
        return cross/length;
    else
        return Point3(0.0f,0.0f,0.0f);
}

//------------------------------------------------------------------------------------------------
// This algorithm was published as "A High Speed, Low Precision Square Root",
// by Paul Lalonde and Robert Dawon, Dalhousie University, Halifax, Nova
// Scotia, Canada, on pp. 424-6 of "Graphics Gems", edited by Andrew Glassner,
// Academic Press, 1990.

// These results are generally faster than their full-precision counterparts
// (except on modern PC hardware), but are only worth 7 bits of binary
// precision (1 in 128).
// [A table for 7-bit precision requires 256 entries.]
inline void Point3::UnitizeVector(Point3& v)
{
    efd::Float32 leng;
    efd::SInt16 exponent;

    // This pointer allows us to treat the efd::Float32 as its integer bit
    // representation.
    efd::UInt32 *pRep = (efd::UInt32*)&leng;

    // WARNING:  SERIOUS ALIASING going on here.  Be very careful with
    // optimization flags.

    // Compute the squared length normally.
    leng = v.x*v.x + v.y*v.y + v.z*v.z;

    // If the squared length is zero, exit.
    if (!(*pRep))
    {
        leng = 0.0f;
    }
    else
    {
        // Shift and mask the exponent from the efd::Float32.
        exponent = static_cast<short>(((*pRep) >> 23) - 127);

        // Mask the exponent away.
        *pRep &= 0x7fffff;

        // If the exponent is odd, use the upper half of the square root
        // table.
        if (exponent & 0x1)
            *pRep |= 0x800000;

        // Compute the sqrt'ed exponent (divide by 2).
        exponent >>= 1;

        // Build the new floating point representation by ORing the looked-up
        // mantissa with the computed exponent.
        *pRep = ms_pSqrtTable[(*pRep) >> 16] | ((exponent + 127) << 23);

        leng = 1.0f/leng; // Invert the length.
    }

    v.x *= leng;
    v.y *= leng;
    v.z *= leng;
}

//------------------------------------------------------------------------------------------------
// This algorithm was published as "A High Speed, Low Precision Square Root",
// by Paul Lalonde and Robert Dawon, Dalhousie University, Halifax, Nova
// Scotia, Canada, on pp. 424-6 of "Graphics Gems", edited by Andrew Glassner,
// Academic Press, 1990.

// These results are generally faster than their full-precision counterparts
// (except on modern PC hardware), but are only worth 7 bits of binary
// precision (1 in 128).
// [A table for 7-bit precision requires 256 entries.]
inline efd::Float32 Point3::VectorLength(const Point3& v)
{
    efd::Float32 leng;
    efd::SInt16 exponent;

    // This pointer allows us to treat the efd::Float32 as its integer bit
    // representation.
    efd::UInt32 *pRep = (efd::UInt32*)&leng;

    // WARNING:  SERIOUS ALIASING going on here.  Be very careful with
    // optimization flags.

    // Compute the squared length normally.
    leng = v.x*v.x + v.y*v.y + v.z*v.z;

    // If the squared length is zero, exit.
    if (!(*pRep))
    {
        leng = 0.0f;
    }
    else
    {
        // Shift and mask the exponent from the efd::Float32.
        exponent = static_cast<short>(((*pRep) >> 23) - 127);

        // Mask the exponent away.
        *pRep &= 0x7fffff;

        // If the exponent is odd, use the upper half of the square root
        // table.
        if (exponent & 0x1)
            *pRep |= 0x800000;

        // Compute the sqrt'ed exponent (divide by 2).
        exponent >>= 1;

        // Build the new floating point representation by ORing the looked-up
        // mantissa with the computed exponent.
        *pRep = ms_pSqrtTable[(*pRep) >> 16] | ((exponent + 127) << 23);
    }

    return leng;
}

//------------------------------------------------------------------------------------------------
inline Point3 Point3::Perpendicular() const
{
    if (efd::Abs(x) < efd::Abs(y))
    {
        if (efd::Abs(z) < efd::Abs(x))
            return UnitCross(Point3::UNIT_Z);
        else
            return UnitCross(Point3::UNIT_X);
    }
    else
    {
        if (efd::Abs(z) < efd::Abs(y))
            return UnitCross(Point3::UNIT_Z);
        else
            return UnitCross(Point3::UNIT_Y);
    }
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
