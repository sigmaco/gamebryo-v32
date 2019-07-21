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
#ifndef EE_PHYSXTYPES_H
#define EE_PHYSXTYPES_H

#include <efdPhysX/efdPhysXLibType.h>

#include <efd/Color.h>
#include <efd/Matrix3.h>
#include <efd/Point3.h>
#include <efd/Quaternion.h>

#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4512) // assignment operator could not be generated
#pragma warning(disable: 4244) // conversion from 'type' to 'type', possible loss of data
#pragma warning(disable: 4245) // conversion from 'type' to 'type', signed/unsigned mismatch
#elif defined(EE_PLATFORM_PS3)
#pragma GCC system_header
#endif
#include <NxPhysics.h>
#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(pop)
#endif

namespace efdPhysX
{

/**
    This class provides static member functions for converting between
    Emergent Foundation classes and PhysX classes.

    @note Conversions involving quaternions may produce unexpected results
        due to the fact that there are two valid quaternion representations
        for any 3D rotation, and all the conversions guarantee is that the
        rotations are equivalent. For example, a call to QuaternionToNxMat33
        followed by NxMat33ToQuaternion on the result will not always give
        the quaternion that you started with - it may produce the one with
        all the values negated. This is the same quaternion mathematically
        because it produces the same rotation, but some tests, such as
        the efd::Quaternion equality operator, will say they are different.
*/
class EE_EFDPHYSX_ENTRY PhysXTypes
{
public:

    /// Convert a NxVec3 object to a Point3 object.
    static void NxVec3ToPoint3(const NxVec3& src, efd::Point3& dest);

    /// Convert a Point3 object to a NxVec3 object.
    static void Point3ToNxVec3(const efd::Point3& src, NxVec3& dest);

    /// Convert a NxQuat object to a Quaternion object.
    static void NxQuatToQuaternion(const NxQuat& src, efd::Quaternion& dest);

    /// Convert a Quaternion object to a NxQuat object.
    static void QuaternionToNxQuat(const efd::Quaternion& src, NxQuat& dest);

    /// Convert a NxMat33 object to a Matrix3 object.
    static void NxMat33ToMatrix3(const NxMat33& src, efd::Matrix3& dest);

    /// Convert a Matrix3 object to a NxMat33 object.
    static void Matrix3ToNxMat33(const efd::Matrix3& src, NxMat33& dest);

    /**
        Convert a NxMat33 representing a rotation into a Quaternion representing the same rotation.

        Uses PhysX's NxMat33.toQuat function.
    */
    static void NxMat33ToQuaternion(const NxMat33& src, efd::Quaternion& dest);

    /**
        Convert a Quaternion representing a rotation into a NxMat33 representing the same rotation.

        Uses PhysX's NxMat33.fromQuat function.
    */
    static void QuaternionToNxMat33(const efd::Quaternion& src, NxMat33& dest);

    /// Convert a PhysX pose matrix to a matrix and point.
    static void NxMat34ToMatrixPoint(const NxMat34& src, efd::Matrix3& matrixDest,
        efd::Point3& pointDest);

    /// Convert a matrix and point to a PhysX pose matrix.
    static void MatrixPointToNxMat34(const efd::Matrix3& matrixSrc, const efd::Point3& pointSrc,
        NxMat34& nxMDest);

    /// Convert from a PhysX pose matrix to the components of a Quaternion and Point representation.
    static void NxMat34ToQuatPoint(const NxMat34& src, efd::Quaternion& quatDest,
        efd::Point3& pointDest);

    /// Convert from a Quaternion and Point representation to a PhysX pose matrix.
    static void QuatPointToNxMat34(const efd::Quaternion& quatSrc, const efd::Point3& pointSrc,
        NxMat34& dest);

    /// Converts from the color representation used in PhysX's debug
    /// rendering to a efd::ColorA.
    static void NxColorToColorA(const NxU32 src, efd::ColorA& dest);

    /// Converts from the ARGB color representation used in PhysX's debug
    /// rendering to a ColorA_UInt8 color.
    static void NxColorToColorUInt8(const NxU32 src, efd::ColorA_UInt8& dest);

    /// A zero vector.
    static const NxVec3 ms_kNxVec3Zero;

    /// An identity matrix.
    static const NxMat33 ms_kNxMat33Identity;

    /// An identity pose.
    static const NxMat34 ms_kNxMat34Identity;

    // A default PhysX SDK descriptor.
    static const NxPhysicsSDKDesc ms_kDefaultPhysicsSDKDesc;

protected:

};

}; // namespace

#include <efdPhysX/PhysXTypes.inl>

#endif  // #ifndef EE_PHYSXTYPES_H

