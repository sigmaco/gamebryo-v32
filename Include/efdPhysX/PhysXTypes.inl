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
inline void efdPhysX::PhysXTypes::NxVec3ToPoint3(const NxVec3& src, efd::Point3& dest)
{
    dest.x = src.x;
    dest.y = src.y;
    dest.z = src.z;
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::Point3ToNxVec3(const efd::Point3& src, NxVec3& dest)
{
    dest.x = src.x;
    dest.y = src.y;
    dest.z = src.z;
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::NxQuatToQuaternion(const NxQuat& src, efd::Quaternion& dest)
{
    dest.SetValues(src.w, src.x, src.y, src.z);
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::QuaternionToNxQuat(const efd::Quaternion& src, NxQuat& dest)
{
    src.GetValues(dest.w, dest.x, dest.y, dest.z);
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::NxMat33ToMatrix3(const NxMat33& src, efd::Matrix3& dest)
{
    dest.SetEntry(0, 0, src(0, 0));
    dest.SetEntry(0, 1, src(0, 1));
    dest.SetEntry(0, 2, src(0, 2));
    dest.SetEntry(1, 0, src(1, 0));
    dest.SetEntry(1, 1, src(1, 1));
    dest.SetEntry(1, 2, src(1, 2));
    dest.SetEntry(2, 0, src(2, 0));
    dest.SetEntry(2, 1, src(2, 1));
    dest.SetEntry(2, 2, src(2, 2));
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::Matrix3ToNxMat33(const efd::Matrix3& src, NxMat33& dest)
{
    dest(0, 0) = src.GetEntry(0, 0);
    dest(0, 1) = src.GetEntry(0, 1);
    dest(0, 2) = src.GetEntry(0, 2);
    dest(1, 0) = src.GetEntry(1, 0);
    dest(1, 1) = src.GetEntry(1, 1);
    dest(1, 2) = src.GetEntry(1, 2);
    dest(2, 0) = src.GetEntry(2, 0);
    dest(2, 1) = src.GetEntry(2, 1);
    dest(2, 2) = src.GetEntry(2, 2);
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::NxMat33ToQuaternion(const NxMat33& src, efd::Quaternion& dest)
{
    NxQuat nxQ;

#ifdef _PS3
    nxQ.setWXYZ(0,0,0,0);
#endif

    src.toQuat(nxQ);
    NxQuatToQuaternion(nxQ, dest);
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::QuaternionToNxMat33(const efd::Quaternion& src, NxMat33& dest)
{
    NxQuat nxQ;
    QuaternionToNxQuat(src, nxQ);
    dest.fromQuat(nxQ);
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::NxMat34ToMatrixPoint(const NxMat34& src, efd::Matrix3& matrixDest,
    efd::Point3& pointDest)
{
    matrixDest.SetEntry(0, 0, src.M(0, 0));
    matrixDest.SetEntry(0, 1, src.M(0, 1));
    matrixDest.SetEntry(0, 2, src.M(0, 2));
    matrixDest.SetEntry(1, 0, src.M(1, 0));
    matrixDest.SetEntry(1, 1, src.M(1, 1));
    matrixDest.SetEntry(1, 2, src.M(1, 2));
    matrixDest.SetEntry(2, 0, src.M(2, 0));
    matrixDest.SetEntry(2, 1, src.M(2, 1));
    matrixDest.SetEntry(2, 2, src.M(2, 2));

    pointDest.x = src.t.x;
    pointDest.y = src.t.y;
    pointDest.z = src.t.z;
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::MatrixPointToNxMat34(const efd::Matrix3& matrixSrc,
    const efd::Point3& pointSrc, NxMat34& nxMDest)
{
    nxMDest.M(0, 0) = matrixSrc.GetEntry(0, 0);
    nxMDest.M(0, 1) = matrixSrc.GetEntry(0, 1);
    nxMDest.M(0, 2) = matrixSrc.GetEntry(0, 2);
    nxMDest.M(1, 0) = matrixSrc.GetEntry(1, 0);
    nxMDest.M(1, 1) = matrixSrc.GetEntry(1, 1);
    nxMDest.M(1, 2) = matrixSrc.GetEntry(1, 2);
    nxMDest.M(2, 0) = matrixSrc.GetEntry(2, 0);
    nxMDest.M(2, 1) = matrixSrc.GetEntry(2, 1);
    nxMDest.M(2, 2) = matrixSrc.GetEntry(2, 2);

    nxMDest.t.x = pointSrc.x;
    nxMDest.t.y = pointSrc.y;
    nxMDest.t.z = pointSrc.z;
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::NxMat34ToQuatPoint(const NxMat34& src, efd::Quaternion& quatDest,
    efd::Point3& pointDest)
{
#ifdef _PS3
    NxQuat nxQ;
    nxQ.setWXYZ(0,0,0,0);
    nxQ = NxQuat(src.M);
#else
    NxQuat nxQ(src.M);
#endif
    NxQuatToQuaternion(nxQ, quatDest);

    pointDest.x = src.t.x;
    pointDest.y = src.t.y;
    pointDest.z = src.t.z;
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::QuatPointToNxMat34(const efd::Quaternion& quatSrc,
    const efd::Point3& pointSrc, NxMat34& dest)
{
    NxQuat nxQ;
    QuaternionToNxQuat(quatSrc, nxQ);
    dest.M.fromQuat(nxQ);

    dest.t.x = pointSrc.x;
    dest.t.y = pointSrc.y;
    dest.t.z = pointSrc.z;
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::NxColorToColorA(const NxU32 src, efd::ColorA& dest)
{
    dest.r = NxF32((src>>16)&0xff)/255.0f;
    dest.g = NxF32((src>>8)&0xff)/255.0f;
    dest.b = NxF32((src)&0xff)/255.0f;
    dest.a = 1.0f;
}

//--------------------------------------------------------------------------------------------------
inline void efdPhysX::PhysXTypes::NxColorToColorUInt8(const NxU32 src, efd::ColorA_UInt8& dest)
{
    dest.r() = (efd::UInt8)((src>>16)&0xff);
    dest.g() = (efd::UInt8)((src>>8)&0xff);
    dest.b() = (efd::UInt8)((src)&0xff);
    dest.a() = 0xff;
}

//--------------------------------------------------------------------------------------------------
