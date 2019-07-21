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
#ifndef EE_MATRIX3_H
#define EE_MATRIX3_H

// NOTE.  The(x,y,z) coordinate system is assumed to be right-handed.
// Coordinate axis rotation matrices are of the form
//   RX =    1       0       0
//           0     cos(t)  sin(t)
//           0    -sin(t)  cos(t)
// where t > 0 indicates a clockwise rotation in the yz-plane,
//   RY =  cos(t)    0    -sin(t)
//           0       1       0
//         sin(t)    0     cos(t)
// where t > 0 indicates a clockwise rotation in the zx-plane, and
//   RZ =  cos(t)  sin(t)    0
//        -sin(t)  cos(t)    0
//           0       0       1
// where t > 0 indicates a clockwise rotation in the xy-plane.  It is
// important to understand that positive angles are associated with clockwise
// rotations.  This is not the usual convention in applications.  The
// original version of Gamebryo used the positive/clockwise convention.  The
// decision was made not to convert to the standard convention to avoid
// clients having to rewrite large amounts of code and re-export their models.

#include <efd/Point3.h>
#include <efd/Point4.h>

namespace efd
{
// forward declaration
class Archive;

// Allows for typecasting to XMFLOAT4X4, XMFLOAT4X4A16
#if !defined(SWIG)
#if defined(EE_PLATFORM_XBOX360)
__declspec(align(16))
#endif
#endif

/**
    This class represents a 3x3 matrix. All Matrix3 rotation creation functions create rotation
    matrices whose rotations are clockwise about the given axis when looking toward the origin
    (assuming a positive rotation angle). In other words, a 90-degree rotation of [0,1,0] about
    [0,0,1] gives the vector [1,0,0].
*/
class EE_EFD_ENTRY Matrix3 : public MemObject
{
public:

    // Declare NiTransform as a friend so that platform specific math routines
    // can get access to the internal vector representation of Matrix3.
    // DT20118 NiTransform should be ported to foundation at some point
    //friend class NiTransform;

    /**
        Constructs a new matrix but for performance reasons does not initialize
        the values.
    */
    Matrix3();

    /**
        Constructs a new matrix using the specified columns.
    */
    Matrix3(
        const efd::Point3& col0,
        const efd::Point3& col1,
        const efd::Point3& col2);

    //@{
    /**
        Gets/Sets the specified row in the matrix.
    */
    inline void GetRow(efd::UInt32 index, efd::Point3& row) const;
    inline void SetRow(efd::UInt32 index, const efd::Point3& row);

    inline void GetRow(efd::UInt32 index, efd::Float32& f0, efd::Float32& f1, efd::Float32& f2)
        const;
    inline void SetRow(efd::UInt32 index, efd::Float32 f0, efd::Float32 f1, efd::Float32 f2);

    inline void GetRow(efd::UInt32 index, efd::Float32* pRow) const;
    inline void SetRow(efd::UInt32 index, const efd::Float32* pRow);
    //@}

    //@{
    /**
        Gets/Sets the specified column in the matrix.
    */
    inline void GetCol(efd::UInt32 index, efd::Point3& col) const;
    inline void SetCol(efd::UInt32 index, const efd::Point3& col);

    inline void GetCol(efd::UInt32 index, efd::Float32& f0, efd::Float32& f1, efd::Float32& f2)
        const;
    inline void SetCol(efd::UInt32 index, efd::Float32 f0, efd::Float32 f1, efd::Float32 f2);

    inline void GetCol(efd::UInt32 index, efd::Float32* pCol) const;
    inline void SetCol(efd::UInt32 index, const efd::Float32* pCol);
    //@}

    /// Gets the value at the specified row and column in the matrix.
    inline efd::Float32 GetEntry(efd::UInt32 row, efd::UInt32 col) const;

    /// Sets the value at the specified row and column in the matrix.
    inline void SetEntry(efd::UInt32 row, efd::UInt32 col, efd::Float32 entry);

    /// Sets this matrix to the zero matrix.
    inline void MakeZero();

    /**
        Sets this matrix to the rotation about the specified axis.
        @param angle Angle in radians.
        @param axis Axis with which to rotate about.
        @note The rotation axis should be normalized.
    */
    inline void MakeRotation(efd::Float32 angle, const efd::Point3& axis);

    /**
        Sets this matrix to the rotation about the specified axis.
        @param angle Angle in radians.
        @param x X component of the axis.
        @param y Y component of the axis.
        @param z Z component of the axis.
        @note The rotation axis should be normalized.
    */
    void MakeRotation(efd::Float32 angle, efd::Float32 x, efd::Float32 y, efd::Float32 z);

    /**
        Tests for \b EXACT member wise in-equality.
        @param mat Matrix with which to compare against.
        @return True if not equal, false otherwise.
    */
    inline bool operator!=(const Matrix3& mat) const;

    /**
        Tests for \b EXACT member wise equality.
        @param mat Matrix with which to compare against.
        @return True if exactly equal, false otherwise.
    */
    bool operator==(const Matrix3& mat) const;

    /**
        Implements matrix multiplication.
        @param mat The matrix to multiply with this one.
        @return A new matrix containing this matrix multiplied with the
            specified matrix.
    */
    inline Matrix3 operator*(const Matrix3& mat) const;

    /**
        Member wise matrix scale.
        @param scalar Scalar value to apply.
        @return A new matrix containing the member wise multiplication of this
            matrix with the specified scalar.
    */
    inline Matrix3 operator*(efd::Float32 scalar) const;

    /**
        Transforms the specified point by this matrix.
        @param pt The point with which to transform.
        @return A new point representing the specified point transformed by
            this matrix.
    */
    inline efd::Point3 operator*(const efd::Point3& pt) const;

#ifdef EE_PLATFORM_PS3
    /**
        Transforms the specified point by this matrix.
        @param pt The point with which to transform.
        @return A new point representing the specified point transformed by
            this matrix.
    */
    inline Point4 operator*(const Point4& pt) const;
#endif

    /// Sets this matrix to be the identity matrix.
    void MakeIdentity();

// Not tested or not supported on the SPU
#ifndef __SPU__

    /**
        Sets this matrix to a pure diagonal matrix with the specified diagonal
        entries.
        @param diag0 Assigned to row 0 column 0.
        @param diag1 Assigned to row 1 column 1.
        @param diag2 Assigned to row 2 column 2.
    */
    void MakeDiagonal(efd::Float32 diag0, efd::Float32 diag1, efd::Float32 diag2);

    /**
        Sets a rotation about the x-axis.
        @param angle Angle in radians.
    */
    void MakeXRotation(efd::Float32 angle);

    /**
        Sets a rotation about the y-axis.
        @param angle Angle in radians.
    */
    void MakeYRotation(efd::Float32 angle);

    /**
        Sets a rotation about the z-axis.
        @param angle Angle in radians.
    */
    void MakeZRotation(efd::Float32 angle);

    /**
        Performs a component wise addition.
        @param mat The matrix to add with this one.
        @return A new matrix containing the component wise sum of this matrix
            and the specified matrix.
    */
    Matrix3 operator+(const Matrix3& mat) const;

    /**
        Performs a component wise subtraction.
        @param mat The matrix to subtract from this one.
        @return A new matrix containing the component wise difference of this
            matrix and the specified matrix.
    */
    Matrix3 operator-(const Matrix3& mat) const;

    /**
        Transforms a point using the transpose of the specified matrix.
        @param pt The point with which to transform.
        @param mat The transformation matrix.
        @return A new point transformed by the transpose of this specified
            matrix.
    */
    EE_EFD_ENTRY friend efd::Point3 operator*(
        const efd::Point3& pt,
        const efd::Matrix3& mat);

    /**
        Computes the inverse of this matrix.
        @return The inverse of this matrix.
    */
    Matrix3 Inverse() const;

    /**
        Computes the inverse of this matrix.
        @param inv Contains the inverse of this matrix when the operation
            has completed.
        @return True if this matrix was inverted, false if not.
    */
    bool Inverse(Matrix3& inv) const;

    /**
        Computes the transpose of this matrix.
        @return The transpose of this matrix.
        @note The use of this method can often be avoided by using the
            Point3*Matrix operator and the TransposeTimes method.
    */
    Matrix3 Transpose() const;

    /**
        Converts this matrix to an angle-axis rotation.
        @param angle Stores the resulting angle in radians.
        @param x Stores the x component of the axis.
        @param y Stores the y component of the axis.
        @param z Stores the z component of the axis.
        @note The rotation matrix must be a rigid, normalized matrix.
    */
    void ExtractAngleAndAxis(
        efd::Float32& angle,
        efd::Float32& x,
        efd::Float32& y,
        efd::Float32& z) const;

    //@{
    /**
        Converts the matrix to a series of rotations about the specified axes
        which indicate some ordering of X, Y, and Z. The matrix must be
        orthonormal in order for these functions to return meaningful results.
        Angles are defined in radians.
        @return True if there was a unique factorization, false otherwise.
    */
    bool ToEulerAnglesXYZ(
        efd::Float32& xAngle,
        efd::Float32& yAngle,
        efd::Float32& zAngle) const;

    bool ToEulerAnglesXZY(
        efd::Float32& xAngle,
        efd::Float32& zAngle,
        efd::Float32& yAngle) const;

    bool ToEulerAnglesYXZ(
        efd::Float32& yAngle,
        efd::Float32& xAngle,
        efd::Float32& zAngle) const;

    bool ToEulerAnglesYZX(
        efd::Float32& yAngle,
        efd::Float32& zAngle,
        efd::Float32& xAngle) const;

    bool ToEulerAnglesZXY(
        efd::Float32& zAngle,
        efd::Float32& xAngle,
        efd::Float32& yAngle) const;

    bool ToEulerAnglesZYX(
        efd::Float32& zAngle,
        efd::Float32& yAngle,
        efd::Float32& xAngle) const;
    //@}

    //@{
    /**
        Legacy versions of the equivalent "ToEulerAngles" functions. These
        legacy functions do not include recent bug fixes and can be used
        if recent fixes breaks code that had been worked around.

        Converts the matrix to a series of rotations about the specified axes
        which indicate some ordering of X, Y, and Z. The matrix must be
        orthonormal in order for these functions to return meaningful results.
        Angles are defined in radians.        
        @return True if there was a unique factorization, false otherwise.
    */
    bool ToEulerAnglesXYZ_Legacy(
        efd::Float32& xAngle,
        efd::Float32& yAngle,
        efd::Float32& zAngle) const;

    bool ToEulerAnglesYZX_Legacy(
        efd::Float32& yAngle,
        efd::Float32& zAngle,
        efd::Float32& xAngle) const;

    bool ToEulerAnglesZXY_Legacy(
        efd::Float32& zAngle,
        efd::Float32& xAngle,
        efd::Float32& yAngle) const;

    bool ToEulerAnglesZYX_Legacy(
        efd::Float32& zAngle,
        efd::Float32& yAngle,
        efd::Float32& xAngle) const;
    //@}

    //@{
    /**
        Builds the matrix from the series of rotations about the specified axes
        indicated by the method signature. Angles are defined in radians.
    */
    void FromEulerAnglesXYZ(efd::Float32 xAngle, efd::Float32 yAngle, efd::Float32 zAngle);

    void FromEulerAnglesXZY(efd::Float32 xAngle, efd::Float32 zAngle, efd::Float32 yAngle);

    void FromEulerAnglesYXZ(efd::Float32 yAngle, efd::Float32 xAngle, efd::Float32 zAngle);

    void FromEulerAnglesYZX(efd::Float32 yAngle, efd::Float32 zAngle, efd::Float32 xAngle);

    void FromEulerAnglesZXY(efd::Float32 zAngle, efd::Float32 xAngle, efd::Float32 yAngle);

    void FromEulerAnglesZYX(efd::Float32 zAngle, efd::Float32 yAngle, efd::Float32 xAngle);
    //@}

    /**
        This routine should only be applied to rotation matrices. It implements
        Gram-Schmidt orthogonalization (the QR algorithm) and replaces the old
        rotation matrix with the orthogonal part Q of the decomposition.
    */
    bool Reorthogonalize();

    /**
        Computes the transpose of this matrix multiplied with the specified
        matrix.
        @param mat The matrix to multiply.
        @return A new matrix containing the product of the transpose of this
            matrix with the specified matrix.
    */
    Matrix3 TransposeTimes(const Matrix3& mat) const;

    /**
        Computes the congruence transformation rot*this*Transpose(rot).  The
        matrix 'rot' must be orthogonal.  The congruence transformation is
        a special form of a similarity transformation mat*this*Inverse(mat)
        where 'mat' can be any invertible matrix.
        @param rot Rotation matrix that must be orthogonal.
        @return A new matrix containing the resulting calculation.
        @note For Transpose(rot)*this*rot, use rot.TransposeTimes(mat)*rot.
    */
    Matrix3 Congruence(const Matrix3& rot) const;

    /**
        Transforms the given array of input vertices by the given rotation and
        translation transforms, placing the result in the pOutVertex array,
        which is assumed to be allocated and have at least vertexCount
        elements. The input and output arrays must not be the same array.
        @param rot The rotation transformation to apply.
        @param trn The translation transformation to apply.
        @param vertexCount The number of vertices in the source vertex array.
        @param pInVertex Input vertex array.
        @param pOutVertex Output vertex array that must contain at least the
            same number of elements as the input vertex array.
    */
    static void TransformVertices(const Matrix3& rot, const Point3& trn,
        efd::UInt32 vertexCount, const Point3* pInVertex,
        Point3* pOutVertex);

    /**
        Transforms the given array of input normals by the given rotation
        matrix, placing the result in the pOutNormal array, which is assumed to
        be allocated and have at least normalCount elements. The input and
        output arrays must not be the same array.
        @param rot The rotation transformation to apply.
        @param normalCount The number of normals in the source normal array.
        @param pInNormal Input normal array.
        @param pOutNormal Output normal array that must contain at least the
            same number of elements as the input normal array.
    */
    static void TransformNormals(const Matrix3& rot,
        efd::UInt32 normalCount, const Point3* pInNormal,
        Point3* pOutNormal);

    /**
        Performs the combination of the above methods. The two input and
        output array are assumed to be of the same size.
        @param rot The rotation transformation to apply.
        @param trn The translation transformation to apply.
        @param count Number of elements in the source and destination arrays.
        @param pInVertex Source vertex array.
        @param pOutVertex Destination vertex array.
        @param pInNormal Source normal array.
        @param pOutNormal Destination normal array.
    */
    static void TransformVerticesAndNormals(const Matrix3& rot,
        const Point3& trn, efd::UInt32 count, const Point3* pInVertex,
        Point3* pOutVertex, const Point3* pInNormal,
        Point3* pOutNormal);

    /**
        Computes the eigenvalues and corresponding eigenvectors of the calling
        matrix, which must be symmetric.
        @param eigenvalue Stores the resulting eigenvalues.
        @param eigenvector Stores the resulting eigenvectors.
    */
    void EigenSolveSymmetric(efd::Float32 eigenvalue[3], efd::Point3 eigenvector[3]);

    /// Convenience object for the zero matrix.
    static const Matrix3 ZERO;

    /// Convenience object for the identity matrix.
    static const Matrix3 IDENTITY;

#if defined(EE_PLATFORM_WIN32)
    /**
        Since it is possible to generate denormalized floating point values for
        each index, this method will clamp very small values to zero.
        @note For Emergent internal use only.
        @internal
    */
    void Snap();
#endif

#if !defined(SWIG)
    /// Serialization
    void Serialize(efd::Archive& ar);
#endif

#endif // #ifndef __SPU__

protected:

#if !defined(SWIG)
#if defined(EE_PLATFORM_XBOX360) || defined (EE_PLATFORM_PS3)
    efd::Point4 m_pEntry[3];
#else
    efd::Float32 m_pEntry[3][3];
#endif
#else
    efd::Point3 m_pEntry[3];
#endif


    // Support for the eigen decomposition of a matrix.  The return value of
    // Tridiagonal is 'true' if a Householder transformation was applied to
    // the matrix (a reflection) and 'false' if no transformation was
    // applied (the identity, a rotation).  The return value of QLAlgorithm
    // is 'true' iff the iterations converged to produce a diagonal matrix.

    /**
        Supports eigendecomposition of a matrix.
        @return True if a Householder transformation was applied to the
            matrix (a reflection) and false if no transformation was applied.
            (the identity, a rotation).
    */
    bool Tridiagonal(efd::Float32 diag[3], efd::Float32 subd[2]);

    /**
        @return True iff the iterations converged to produce a diagonal matrix.
    */
    bool QLAlgorithm(efd::Float32 diag[3], efd::Float32 subd[2]);

    /// Threshold for detecting gimbal lock during euler angle conversion
    static const efd::Float32 EE_RIGHT_ANGLE_EPSILON;
};

#if defined (EE_PLATFORM_WIN32)
#include <efd/Win32/Matrix3_Win32.inl>
#elif defined (EE_PLATFORM_XBOX360)
#include <efd/XBox360/Matrix3_XBox360.inl>
#elif defined (EE_PLATFORM_PS3)
#include <efd/PS3/Matrix3_PS3.inl>
#elif defined (EE_PLATFORM_LINUX)
#include <efd/Linux/Matrix3_Linux.inl>
#else
#error Unknown platform
#endif

/**
    Transforms a point using the transpose of the specified matrix.
    @param pt The point with which to transform.
    @param mat The transformation matrix.
    @return A new point transformed by the transpose of this specified
        matrix.
*/
EE_EFD_ENTRY efd::Point3 operator*(const efd::Point3& pt, const efd::Matrix3& mat);

} // end namespace efd

#endif
