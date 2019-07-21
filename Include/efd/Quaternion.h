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
#ifndef EE_QUATERNION_H
#define EE_QUATERNION_H

#include <efd/efdLibType.h>
#include <efd/MemObject.h>
#include <efd/UniversalTypes.h>
#include <efd/EEMath.h>
#include <efd/Matrix3.h>
#include <efd/RTLib.h>
#ifndef __SPU__
#include <efd/SerializeEfdHelpers.h>
#endif


namespace efd
{
class Archive;
class Point3;

/**
    This class supports quaternions for the representation of rotations.
    Basic algebraic and calculus operations are provided as well as linear and
    cubic interpolation routines.
*/
class EE_EFD_ENTRY Quaternion : public MemObject
{
public:

#if !defined(SWIG)
    union
    {
        efd::Float32 m_w;
        efd::Float32 m_fW;
    };

    union
    {
        efd::Float32 m_x;
        efd::Float32 m_fX;
    };

    union
    {
        efd::Float32 m_y;
        efd::Float32 m_fY;
    };

    union
    {
        efd::Float32 m_z;
        efd::Float32 m_fZ;
    };
#else
    // SWIG doesn't support nested Unions
    efd::Float32 m_w;
    efd::Float32 m_x;
    efd::Float32 m_y;
    efd::Float32 m_z;
#endif

    /**
        Constructs a new quaternion but does not initialize the data members
        so that fast construction of arrays is possible in situations where the
        rotations will be filled in by application code.
    */
    Quaternion();

    /// Constructs a quaternion from the specified values.
    Quaternion(efd::Float32 w, efd::Float32 x, efd::Float32 y, efd::Float32 z);

    /**
        Constructs a unit quaternion that corresponds to the rotation about the
        specified axis. This rotation is counter clockwise about the axis when
        looking towards the origin.
        @param angle The angle in radians.
        @param axis The axis to rotate about.
    */
    Quaternion(efd::Float32 angle, const efd::Point3& axis);

    /// Sets the w component of the quaternion.
    inline void SetW(efd::Float32 w);

    /// Sets the x component of the quaternion.
    inline void SetX(efd::Float32 x);

    /// Sets the y component of the quaternion.
    inline void SetY(efd::Float32 y);

    /// Sets the z component of the quaternion.
    inline void SetZ(efd::Float32 z);

    /// Gets the w component of the quaternion.
    inline efd::Float32 GetW() const;

    /// Gets the x component of the quaternion.
    inline efd::Float32 GetX() const;

    /// Gets the y component of the quaternion.
    inline efd::Float32 GetY() const;

    /// Gets the z component of the quaternion.
    inline efd::Float32 GetZ() const;

    /// Sets the components of the quaternion.
    void SetValues(efd::Float32 w, efd::Float32 x, efd::Float32 y, efd::Float32 z);

    /// Extracts each component from the quaternion.
    void GetValues(efd::Float32& w, efd::Float32& x, efd::Float32& y, efd::Float32& z) const;

    /**
        Performs an <b>EXACT</b> equality test.
        @param q The quaternion to compare with this one.
        @return True if exactly equal, false otherwise.
    */
    inline bool operator==(const Quaternion& q) const;

    /**
        Performs an <b>EXACT</b> in-equality test.
        @param q The quaternion to compare with this one.
        @return True if not equal, false otherwise.
    */
    inline bool operator!=(const Quaternion& q) const;

    /**
        Performs a quaternion multiplication.
        @param q The quaternion to multiply with this one.
        @return The product of this quaternion and the specified quaternion.
        @note Quaternion multiplication is generally not commutative so in most
            cases p*q != q*p.
    */
    Quaternion operator*(const Quaternion& q) const;

    /**
        Performs a quaternion rotation of a 3-vector.
        @param p The point that will be rotated as if the quaternion repsented a rotation.
        @return The rotated point.
    */
    Point3 operator*(const Point3& p) const; 

    /**
        Performs a scaler multiplication of this quaternion.
        @param c The value by which to scale this quaternion.
        @return The scaled quaternion.
    */
    inline Quaternion operator*(efd::Float32 c) const;

    /**
        Fast path version of converting an angle/axis rotation to a quaternion.
        @param angle Angle in radians about the x-axis.
    */
    inline void FromAngleAxisX(efd::Float32 angle);

    /**
        Fast path version of converting an angle/axis rotation to a quaternion.
        @param angle Angle in radians about the y-axis.
    */
    inline void FromAngleAxisY(efd::Float32 angle);

    /**
        Fast path version of converting an angle/axis rotation to a quaternion.
        @param angle Angle in radians about the z-axis.
    */
    inline void FromAngleAxisZ(efd::Float32 angle);

    /**
        Fast path version of converting an angle/axis rotation to a quaternion.
        @param angleX Angle in radians about the x-axis.
        @param angleY Angle in radians about the y-axis.
        @param angleZ Angle in radians about the z-axis.
    */
    inline void FromAngleAxesXYZ(efd::Float32 angleX, efd::Float32 angleY, efd::Float32 angleZ);

    /**
        Converts this quaternion into a 3x3 rotation matrix.
        @param rot Stores the resulting conversion.
    */
    inline void ToRotation (Matrix3& rot) const;

    /**
        This function computes the spherical linear interpolate of the
        specified quaternions.
        @param t Parametric value and must be in the interval [0,1].
        @param p The first quaternion. Must be of unit length.
        @param q The second quaternion. Must be of unit length.
        @note This function assumes the dot product of p and q is non-negative.
            (i.e. The angle between p and q is acute.)
    */
    static Quaternion Slerp(
        efd::Float32 t,
        const Quaternion& p,
        const Quaternion& q);

    /**
        This function computes the spherical linear interpolate of the
        specified quaternions.
        @param t Parametric value and must be in the interval [0,1].
        @param p The first quaternion. Must be of unit length.
        @param q The second quaternion. Must be of unit length.
        @param pResults The destination quaternion. Used to store the results.
        @note This function assumes the dot product of p and q is non-negative.
        (i.e. The angle between p and q is acute.)
    */
    static void Slerp(
        efd::Float32 t,
        const Quaternion& p,
        const Quaternion& q,
        Quaternion* pResults);

    /**
        Computes the dot product of the two input quaternions by treating them
        as 4-tuples.
    */
    static efd::Float32 Dot (const Quaternion& p, const Quaternion& q);

    /**
        Normalizes this quaternion and is mostly used by sleep.
        @note Intended for Emergent internal usage only.
        @internal
    */
    void Normalize();

    /**
        Faster, but less accurate method to normalize a quaternion.
        @note Intended for Emergent internal usage only.
        @internal
    */
    void FastNormalize();

#ifndef SWIG

// Not tested or not supported on the SPU
#ifndef __SPU__

    /// Serialize method for using Quaternion with Archive and ParameterList
    void Serialize(efd::Archive& io_archive);

    /**
       Performs a component wise addition.
       @param q The quaternion to add to this one.
       @return A newly constructed quaternion containing the sum of this
           quaternion and the specified quaternion.
    */
    Quaternion operator+(const Quaternion& q) const;

    /**
       Performs a component wise subtraction.
       @param q The quaternion to add to this one.
       @return A newly constructed quaternion containing the difference of this
           quaternion and the specified quaternion.
    */
    Quaternion operator-(const Quaternion& q) const;

    /**
        Unary negation operator.
        @return A quaternion containing the negated version of this one.
    */
    Quaternion operator-() const;

    /**
        Performs a scaler multiplication of this quaternion.
        @param c The value by which to scale this quaternion.
        @param q The quaternion to multiply with this one.
        @return The scaled quaternion.
    */
    EE_EFD_ENTRY friend Quaternion operator*(
        efd::Float32 c,
        const Quaternion& q);

    /**
        Computes the inverse of the specified quaternion.
        @param q A quaternion of unit length.
        @return The multiplicative inverse of the specified quaternion.
    */
    static Quaternion UnitInverse(const Quaternion& q);

    /**
        Computes a quaternion exponential and is primarily used by Slerp and
        Squad.
        @param q A quaternion of unit length.
    */
    static Quaternion Exp(const Quaternion& q);

    /**
        Computes a quaternion logarithm and is primarily used by Slerp and
        Squad.
        @param q A quaternion of unit length.
    */
    static Quaternion Log(const Quaternion& q);

    /**
        This function is used to compute intermediate quaternions and is used
        by the quadratic spherical interpolation routines.
        @note All input quaternions must be normalized.
    */
    static Quaternion Intermediate(
        const Quaternion& q0,
        const Quaternion& q1,
        const Quaternion& q2);

    /**
        This function computes the spherical quadratic interpolate of the two
        input quaternions p and q.
        @param t Parametric value that must be in the interval [0,1].
        @param p Start input quaternion.
        @param a First input quaternion computed by Quaternion::Intermediate
        @param b Second input quaternion computed by Quaternion::Intermediate
        @param q End input quaternion.
        @note The function assumes that the dot product of p and q is
            nonnegative (i.e. The angle between p and q is acute).
        @note All quaternions must be of unit length.
    */
    static Quaternion Squad(
        efd::Float32 t,
        const Quaternion& p,
        const Quaternion& a,
        const Quaternion& b,
        const Quaternion& q);

    /**
        Converts a unit length quaternion to its angle-axis representation.
        @param angle Stores the resulting angle in radians in the interval
            [0,EE_PI].
        @param axis Stores the resulting unit length axis vector.
        @note This method makes two function calls, one to efd::Sqrt and one
            to efd::ACos.
    */
    void ToAngleAxis(efd::Float32& angle, Point3& axis) const;

    /**
        Converts from and angle/axis rotation representation to a quaternion
        and stores the result in this quaternion.
        @param angle The angle in radians between the interval [0,EE_PI].
        @param axis The unit length axis.
        @note This method makes two functions calls, one to efd::Sin and one
            to efd::Cos.
    */
    void FromAngleAxis(efd::Float32 angle, const Point3& axis);

    /**
        Converts the specified rotation matrix to a quaternion and stores the
        result in this quaternion.
        @param rot The rotation matrix to convert.
    */
    void FromRotation (const Matrix3& rot);

    /// Quaternion corresponding to the identity matrix.
    static const Quaternion IDENTITY;

    /**
        Epsilon constant used by several internal calculations.
        @note Intended for Emergent internal usage only.
        @internal
    */
    static const efd::Float32 ms_epsilon;

    /**
        Snaps all de-normalized floats to zero.
        @note Intended for Emergent internal usage only.
        @internal
    */
    void Snap();

#endif // #ifndef __SPU__
#endif // #ifndef SWIG

protected:

    /// Helper method used by Slerp.
    static efd::Float32 ISqrtApproxInNeighborhood(efd::Float32 s);

    /// Helper method used by Slerp to compute a linear interpolation of
    /// the specified quaternions.
    static efd::Float32 Lerp(efd::Float32 v0, efd::Float32 v1, efd::Float32 perc);

    /// Helper method used by Slerp.
    static efd::Float32 CounterWarp(efd::Float32 t, efd::Float32 cosine);

};


} //namespace efd

#include <efd/Quaternion.inl>

//-------------------------------------------------------------------------------------------------

#endif


