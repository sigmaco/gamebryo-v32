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
#ifndef EE_POINT2_H
#define EE_POINT2_H

#include <efd/UniversalTypes.h>
#include <efd/MemObject.h>
#include <efd/Asserts.h>
#include <efd/EEMath.h>


namespace efd
{
class Archive;

/**
    This is a basic 2D point class.  The only data members are x and y,
    which are both declared as public 32-bit floating point values.  This
    arrangement enables them to be accessed using structure-style notation
    (i.e. value = vector.x).
*/
class EE_EFD_ENTRY Point2 : public MemObject
{
public:
    efd::Float32 x;
    efd::Float32 y;

    /**
        Constructs a new point but does not initialize the data members so that
        fast construction of arrays is possible in situations where the points
        will be filled in by application code.
    */
    Point2();

    /// Constructs a point from the specified values.
    Point2(efd::Float32 x0, efd::Float32 y0);

    /**
       Allows access to the point using array referencing.
       @note This method assumes the class member data is 4-byte aligned.
    */
    efd::Float32& operator[](efd::SInt32 i);

    /**
       Const version of the array reference operator.
       @note This method assumes the class member data is 4-byte aligned.
    */
    const efd::Float32& operator[](efd::SInt32 i) const;

    /**
       Equality operator using an <b>EXACT</b> comparison.
       @param pt Point with which to compare to this point.
       @return True if exactly equal, false otherwise.
    */
    bool operator==(const Point2& pt) const;

    /**
        Inequality operator using an <b>EXACT</b> comparison.
        @param pt Point with which to compare to this point.
        @return True if not equal, false otherwise.
    */
    bool operator!=(const Point2& pt) const;

    /**
       Performs a component wise addition.
       @param pt The point to add to this one.
       @return A newly constructed point containing the sum of this point
           and the specified point.
    */
    Point2 operator+(const Point2& pt) const;

    /**
       Performs a component wise subtraction.
       @param pt The point to subtract from this one.
       @return A newly constructed point containing the difference of this
           point and the specified point.
    */
    Point2 operator-(const Point2& pt) const;

    /**
        Dot product operator.
        @param pt The second point with which to calculate the dot product.
        @return The dot product of this point with the specified point.
    */
    efd::Float32 operator*(const Point2& pt) const;

    /**
        Performs a scalar multiplication.
        @param scalar The value with which to scale this point.
        @return A newly constructed point representing the scaled version of
            this point.
    */
    Point2 operator*(efd::Float32 scalar) const;

    /**
        Performs a scalar division.
        @param scalar The value with which to scale this point.
        @return A newly constructed point representing the scaled version of
            this point.
    */
    Point2 operator/(efd::Float32 scalar) const;

    /**
        Unary negation operator.
        @return A point containing the negated version of this point.
    */
    Point2 operator-() const;

    /**
        scalar multiplication operator.
        @param scalar The scalar value..
        @param pt The point with which to scale.
        @return A newly constructed point containing the scaled version of the
            specified point.
    */
    EE_EFD_ENTRY friend Point2 operator*(
        efd::Float32 scalar,
        const Point2& pt);

    /**
        Performs a component wise multiplication of the two specified points.
        @param p0 The first point.
        @param p1 The second point.
        @return The result of the first point multiplied by the second point
            in a component wise fashion.
    */
    static Point2 ComponentProduct(const Point2& p0, const Point2& p1);

    /**
       Performs an in place component wise addition.
       @param pt The point to add to this point.
       @return A reference to this point plus the specified point.
    */
    Point2& operator+=(const Point2& pt);

    /**
        Performs an in place component wise subtraction.
        @param pt The point to subtract from this point.
        @return A reference to this point subtracted by the specified point.
    */
    Point2& operator-=(const Point2& pt);

    /**
        In place scalar multiplication of this point.
        @param scalar The scalar value.
        @return A reference to this point scaled by the specified scalar.
    */
    Point2& operator*=(efd::Float32 scalar);

    /**
        In place division of this point.
        @param scalar The scalar value.
        @return A reference to this point divided by the specified scalar.
    */
    Point2& operator/=(efd::Float32 scalar);

    /**
        Calculates the vector length of this point.
        @return The vector length.
    */
    efd::Float32 Length() const;

    /**
        Calculates the squared vector length of this point.
        @return The squared vector length.
    */
    efd::Float32 SqrLength() const;

    /**
        Calculates the dot product.
        @param pt The second point with which to calculate the dot product.
        @return The dot product of this point with the specified point.
    */
    efd::Float32 Dot(const Point2& pt) const;

    /**
        Converts this vector into a unit vector.
        @return The original length of the vector before it was normalized.
        @note If this method is called on a zero vector, it remains unchanged
            and a value of zero is returned as the result.
    */
    efd::Float32 Unitize();

    /// Gets the x component of the quaternion.
    efd::Float32 GetX() const;

    /// Gets the y component of the quaternion.
    efd::Float32 GetY() const;

#if !defined(SWIG)
    /// Serialization
    void Serialize(efd::Archive& ar);
#endif

    /// Convenience static 2D point for a zero vector.
    static const Point2 ZERO;

    /// Convenience static 2D point for an x-axis unit vector (1,0).
    static const Point2 UNIT_X;

    /// Convenience static 2D point for a y-axis unit vector. (0,1).
    static const Point2 UNIT_Y;
};

} // end namespace efd

#include <efd/Point2.inl>

#endif
