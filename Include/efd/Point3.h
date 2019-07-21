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
#ifndef EE_POINT3_H
#define EE_POINT3_H

#include <efd/MemObject.h>
#include <efd/EEMath.h>

namespace efd
{
class Archive;

/**
    This is a basic 3D point class.  The only data members are x, y, and z,
    which are both declared as public 32-bit floating point values.  This
    arrangement enables them to be accessed using structure-style notation
    (i.e. value = vector.x).
*/
class EE_EFD_ENTRY Point3 : public MemObject
{
public:
     efd::Float32 x;
     efd::Float32 y;
     efd::Float32 z;

    /**
        Constructs a new point but does not initialize the data members so that
        fast construction of arrays is possible in situations where the points
        will be filled in by application code.
    */
    inline Point3();

    /// Constructs a point from the specified values.
    inline Point3(efd::Float32 x0, efd::Float32 y0, efd::Float32 z0);

    /**
       Allows access to the point using array referencing.
       @note This method assumes the class member data is 4-byte aligned.
    */
    inline const efd::Float32& operator[](efd::SInt32 i) const;

    /**
       Const version of the array reference operator.
       @note This method assumes the class member data is 4-byte aligned.
    */
    inline efd::Float32& operator[](efd::SInt32 i);

    /**
       Equality operator using an <b>EXACT</b> comparison.
       @param pt Point with which to compare to this point.
       @return True if exactly equal, false otherwise.
    */
    inline bool operator==(const Point3& pt) const;

    /**
        Inequality operator using an <b>EXACT</b> comparison.
        @param pt Point with which to compare to this point.
        @return True if not equal, false otherwise.
    */
    inline bool operator!=(const Point3& pt) const;

    /**
        Assignment operator, copies each member
        @param pt Point3 to copy from.
        @return A reference to this Point3 instance.
      */
    inline Point3& operator=(const Point3& pt);

    /**
       Performs a component wise addition.
       @param pt The point to add to this one.
       @return A newly constructed point containing the sum of this point
           and the specified point.
    */
    inline Point3 operator+(const Point3& pt) const;

    /**
       Performs a component wise subtraction.
       @param pt The point to subtract from this one.
       @return A newly constructed point containing the difference of this
           point and the specified point.
    */
    inline Point3 operator-(const Point3& pt) const;

    /**
        Dot product operator.
        @param pt The second point with which to calculate the dot product.
        @return The dot product of this point with the specified point.
    */
    inline efd::Float32 operator*(const Point3& pt) const;

    /**
        Performs a scalar multiplication.
        @param scalar The value with which to scale this point.
        @return A newly constructed point representing the scaled version of
            this point.
    */
    inline Point3 operator*(efd::Float32 scalar) const;

    /**
        Performs a scalar division.
        @param scalar The value with which to scale this point.
        @return A newly constructed point representing the scaled version of
            this point.
    */
    inline Point3 operator/(efd::Float32 scalar) const;

    /**
        Unary negation operator.
        @return A point containing the negated version of this point.
    */
    inline Point3 operator-() const;

    /**
        scalar multiplication operator.
        @param scalar The scalar value..
        @param pt The point with which to scale.
        @return A newly constructed point containing the scaled version of the
            specified point.
    */
    inline EE_EFD_ENTRY friend Point3 operator*(
        efd::Float32 scalar,
        const Point3& pt);

    /**
        Performs a component wise multiplication of the two specified points.
        @param p0 The first point.
        @param p1 The second point.
        @return The result of the first point multiplied by the second point
            in a component wise fashion.
    */
    inline static Point3 ComponentProduct (const Point3& p0, const Point3& p1);

    /**
       Performs an in place component wise addition.
       @param pt The point to add to this point.
       @return A reference to this point plus the specified point.
    */
    inline Point3& operator+=(const Point3& pt);

    /**
        Performs an in place component wise subtraction.
        @param pt The point to subtract from this point.
        @return A reference to this point subtracted by the specified point.
    */
    inline Point3& operator-=(const Point3& pt);

    /**
        In place scalar multiplication of this point.
        @param scalar The scalar value.
        @return A reference to this point scaled by the specified scalar.
    */
    inline Point3& operator*=(efd::Float32 scalar);

    /**
        In place division of this point.
        @param scalar The scalar value.
        @return A reference to this point divided by the specified scalar.
    */
    inline Point3& operator/=(efd::Float32 scalar);

    /**
        Calculates the vector length of this point.
        @return The vector length.
    */
    inline efd::Float32 Length() const;

    /**
        Calculates the squared vector length of this point.
        @return The squared vector length.
    */
    inline efd::Float32 SqrLength() const;

    /**
        Calculates the dot product.
        @param pt The second point with which to calculate the dot product.
        @return The dot product of this point with the specified point.
    */
    inline efd::Float32 Dot(const Point3& pt) const;

    /**
        Converts this vector into a unit vector.
        @return The original length of the vector before it was normalized.
        @note If this method is called on a zero vector, it remains unchanged
            and a value of zero is returned as the result.
    */
    inline efd::Float32 Unitize();

    /**
        Converts this vector into a unit vector.
        @param zeroLengthDefault vector to default to if vector length is zero.
        @return The original length of the vector before it was normalized.
    */
    inline efd::Float32 Unitize(const Point3& zeroLengthDefault);

    /**
        Calculates the cross product of this vector with the specified vector.
        @param pt The vector with which to take the cross product.
        @return A vector containing this vector cross pt.
        @note Both this vector and the one specified are not modified.
    */
    inline Point3 Cross(const Point3& pt) const;

    /**
        Calculates the cross product of this vector with the specified vector.
        @param pt The vector with which to take the cross product.
        @return A unit length vector containing this vector cross pt.
        @note Both this vector and the one specified are not modified.
        @note This method is slower than the normal Cross method since the
            resulting vector must be normalized.
    */
    inline Point3 UnitCross(const Point3& pt) const;

    /**
        Computes one of the infinite set of perpendicular vectors to this
        vector.
        @return A perpendicular vector to this one.
    */
    Point3 Perpendicular () const;

    // Not using static initialization on SPU
#ifndef __SPU__

#if !defined(SWIG)
    /// Serialization
    void Serialize(efd::Archive& ar);
#endif

    /// Convenience static 3D point for a zero vector.
    static const Point3 ZERO;

    /// Convenience static 3D point for an x-axis unit vector (1,0,0).
    static const Point3 UNIT_X;

    /// Convenience static 3D point for a y-axis unit vector (0,1,0).
    static const Point3 UNIT_Y;

    /// Convenience static 3D point for a z-axis unit vector (0,0,1).
    static const Point3 UNIT_Z;

    /// Convenience static 3D point for a unit vector (1,1,1).
    static const Point3 UNIT_ALL;

#endif // #ifndef __SPU__

    // *** begin Emergent internal use only ***

    static void _SDMInit();
    static void _SDMShutdown();

    // *** end Emergent internal use only ***

public:
    // Methods that use fast, but less precise, square root.

    // This algorithm was published as "A High Speed, Low Precision Square
    // Root", by Paul Lalonde and Robert Dawon, Dalhousie University, Halifax,
    // Nova Scotia, Canada, on pp. 424-6 of "Graphics Gems", edited by Andrew
    // Glassner, Academic Press, 1990.

    /**
        Processes an array of vectors and normalizes each of them.
        @param pVectors A pointer to an array of vectors to process.
        @param count The number of vectors in the array.
        @param stride The number of bytes between each vector in the array.
        @note These results are generally faster than their full-precision
            counterparts (except on modern PC hardware), but are only worth 7
            bits of binary precision (1 in 128).
    */
    static void UnitizeVectors(
        Point3* EE_RESTRICT pVectors,
        efd::UInt32 count,
        efd::UInt32 stride);

    /**
        Normalizes the specified vector using a fast, but less precise square
        root algorithm.
        @param v The vector to normalize.
    */
    inline static void UnitizeVector(Point3& v);

    /**
        Calculates the length of the specified vector using a fast, but less
        precise square root algorithm.
        @param v The vector with which to calculate the length.
        @return The length of the specified vector.
    */
    inline static efd::Float32 VectorLength(const Point3& v);

    /**
        Multiplies each point in the source array by the specified scalar and
        adds the result to the corresponding point in the destination array.
        (Ex: pDst[i] += f * pSrc[i])
        @param pDst An array of points with which to write the results.
        @param f The scalar with which to multiply each incoming source point.
        @param pSrc A source array of points.
        @param count The number of points in both arrays.
        @note Both the source and destination arrays must be of equal length.
    */
    static void PointsPlusEqualFloatTimesPoints(
        Point3* EE_RESTRICT pDst,
        efd::Float32 f,
        const Point3* EE_RESTRICT pSrc,
        efd::UInt32 count);

    /**
        Multiplies (1.0f - weight) by each point in the source array and weight
        by the corresponding point in the destination array, storing the result
        in the destination.
        (Ex:  pDst[i] = oneMinusWeight * pSrc[i] + weight * pDst[i])
        @param pDst An array of points with which to multiply the weights and
            store the results.
        @param weight The weight.
        @param pSrc A source array of points with which to multiply the inverse
            weight and add to the results.
        @param count The number of points in the source and destination arrays.
        @note Both the source and destination arrays must be of equal length.
    */
    static void WeightedPointsPlusWeightedPoints(
        Point3* EE_RESTRICT pDst,
        efd::Float32 weight,
        const Point3* EE_RESTRICT pSrc,
        efd::UInt32 count);

protected:
#ifndef __SPU__
    /**
        Generates a static look up table for the fast versions of the square
        root function.
        @return A pointer to the allocated lookup table.
    */
    static efd::UInt32* InitSqrtTable();
    static efd::UInt32* ms_pSqrtTable;
#endif
};

} // end namespace efd

/// Include the platform specific inlines
#include EE_PLATFORM_SPECIFIC_INCLUDE(efd,Point3,inl)

#endif
