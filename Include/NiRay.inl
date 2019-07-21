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
inline NiRay::NiRay() :
    m_kRayOrigin(0.0f, 0.0f, 0.0f),
    m_kRayDir(0.0f, 0.0f, -1.0f),
    m_fRayLengthSqr(0.0f),
    m_fDistanceSqrToIntersection(0.0f),
    m_pkCollidedLeaf(0),
    m_kIntersectPoint(0.0f, 0.0f, 0.0f),
    m_kIntersectNormal(0.0f, 0.0f, 0.0f),
    m_bIntersected(false)
{
    SetRay(NiPoint3::ZERO, NiPoint3::UNIT_ALL, 0.0f);
}

//--------------------------------------------------------------------------------------------------
inline NiRay::NiRay(const NiPoint3& kRayOrigin, const NiPoint3& kRayDir) :
    m_kRayOrigin(kRayOrigin.x, kRayOrigin.y, kRayOrigin.z),
    m_kRayDir(kRayDir.x, kRayDir.y, kRayDir.z),
    m_fRayLengthSqr(0.0f),
    m_fDistanceSqrToIntersection(0.0f),
    m_pkCollidedLeaf(0),
    m_kIntersectPoint(0.0f, 0.0f, 0.0f),
    m_kIntersectNormal(0.0f, 0.0f, 0.0f),
    m_bIntersected(false)
{
    SetRay(kRayOrigin, kRayDir, 0.0f);
}

//--------------------------------------------------------------------------------------------------
inline float NiRay::GetLength() const
{
    return NiSqrt(m_fRayLengthSqr);
}

//--------------------------------------------------------------------------------------------------
inline float NiRay::GetDistanceToIntersection() const
{
    return NiSqrt(m_fDistanceSqrToIntersection);
}

//--------------------------------------------------------------------------------------------------
inline void NiRay::SetRay(const NiPoint3& kRayOrigin, const NiPoint3& kRayDir,
    float fRayLength)
{
    m_kRayOrigin = kRayOrigin;

    m_kRayDir = kRayDir;
    float fDirLen = m_kRayDir.Length();
    EE_ASSERT(fDirLen > 0.0f);
    m_kRayDir /= fDirLen;

    m_fRayLengthSqr = NiSqr(fRayLength);

    m_kWorldSpaceOrigin = m_kRayOrigin;
    m_kWorldSpaceDir = m_kRayDir;
    m_fWorldLengthSqr = m_fRayLengthSqr;

    ResetIntersection();
}
//---------------------------------------------------------------------------
inline void NiRay::TransformToSpace(
    const NiTransform& kSpaceTransform)
{
    bool bModifiedZ = false;

    m_kWorldSpaceOrigin = m_kRayOrigin;
    m_kWorldSpaceDir = m_kRayDir;
    m_fWorldLengthSqr = m_fRayLengthSqr;

    if (m_kRayOrigin.z == NI_INFINITY)
    {
        m_kRayOrigin.z = 0.0f;
        bModifiedZ = true;
    }

    NiTransform kInvertTransform;
    kSpaceTransform.Invert(kInvertTransform);
    m_kRayOrigin = kInvertTransform * m_kRayOrigin;

    m_kRayDir = m_kRayDir * kSpaceTransform.m_Rotate;

    m_fRayLengthSqr = m_fRayLengthSqr / NiPow(kSpaceTransform.m_fScale, 2.0f);

    if (bModifiedZ)
    {
        m_kRayOrigin -= m_kRayDir * 1000;
    }
}
//---------------------------------------------------------------------------
inline void NiRay::TransformToWorldSpace()
{
    m_kRayOrigin = m_kWorldSpaceOrigin;
    m_kRayDir = m_kWorldSpaceDir;
    m_fRayLengthSqr = m_fWorldLengthSqr;
}
//---------------------------------------------------------------------------
inline NiTransform NiRay::GetTransform() const
{
    NiTransform kTransform;
    kTransform.m_fScale = GetLength();
    kTransform.m_Translate = GetOrigin();

    return kTransform;
}

//--------------------------------------------------------------------------------------------------
inline void NiRay::SetTransform(NiTransform kTransform)
{
    SetRay(kTransform.m_Translate, m_kRayDir,
        NiSqrt(m_fRayLengthSqr) * kTransform.m_fScale);
}

//--------------------------------------------------------------------------------------------------
inline const NiPoint3& NiRay::GetDirection() const
{
    return m_kRayDir;
}

//--------------------------------------------------------------------------------------------------
inline const NiPoint3& NiRay::GetOrigin() const
{
    return m_kRayOrigin;
}

//--------------------------------------------------------------------------------------------------
inline const NiTerrainCell* NiRay::GetCollidedCell()
{
    return m_pkCollidedLeaf;
}

//--------------------------------------------------------------------------------------------------
inline void NiRay::SetCollidedLeaf(const NiTerrainCell* pkLeaf)
{
    m_pkCollidedLeaf = pkLeaf;
}

//--------------------------------------------------------------------------------------------------
inline void NiRay::ResetIntersection()
{
    m_bIntersected = false;
}

//--------------------------------------------------------------------------------------------------
inline bool NiRay::SetIntersection(const NiPoint3& kIntersectionPoint,
    const NiPoint3& kIntersectionNormal, float fDistanceSqrToIntersection)
{
    if (fDistanceSqrToIntersection == 0.0f)
    {
        fDistanceSqrToIntersection = 
            NiSqr(m_kWorldSpaceOrigin.x - kIntersectionPoint.x) + 
            NiSqr(m_kWorldSpaceOrigin.y - kIntersectionPoint.y);
    }

    if (m_fWorldLengthSqr == 0.0f || fDistanceSqrToIntersection < 
        m_fWorldLengthSqr)
    {
        m_bIntersected = true;
        m_kIntersectPoint = kIntersectionPoint;
        m_kIntersectNormal = kIntersectionNormal;
        m_fDistanceSqrToIntersection = fDistanceSqrToIntersection;
    }
    return m_bIntersected;
}

//--------------------------------------------------------------------------------------------------
inline bool NiRay::UseClosestIntersection(const NiPoint3& kIntersectionPoint,
    const NiPoint3& kIntersectionNormal)
{
    float fDistanceSqrToIntersection = 
        NiSqr(m_kWorldSpaceOrigin.x - kIntersectionPoint.x) + 
        NiSqr(m_kWorldSpaceOrigin.y - kIntersectionPoint.y);
    if (!m_bIntersected ||
        m_fDistanceSqrToIntersection > fDistanceSqrToIntersection)
    {
        SetIntersection(
            kIntersectionPoint,
            kIntersectionNormal,
            fDistanceSqrToIntersection);
    }
    return m_bIntersected;
}

//---------------------------------------------------------------------------
inline bool NiRay::UseLength()
{
    return m_kWorldSpaceOrigin.z != NI_INFINITY && m_fWorldLengthSqr != 0;
}

//---------------------------------------------------------------------------
inline bool NiRay::GetIntersection(NiPoint3& kIntersectionPoint, 
    NiPoint3& kIntersectionNormal) const
{
    kIntersectionPoint = m_kIntersectPoint;
    kIntersectionNormal = m_kIntersectNormal;
    return m_bIntersected;
}

//--------------------------------------------------------------------------------------------------
inline float NiRay::DistanceTo(const NiPoint3& kPoint) const
{
    // Original concept: http://mathforum.org/library/drmath/view/54731.html
    // Note, that in our case, the secondary point = A + direction.
    // This means, that AB = direction. Since ||AB|| = 1, saves a few
    // calculations
    return NiPoint3::VectorLength(m_kRayDir.Cross(kPoint - m_kRayOrigin));
}

//--------------------------------------------------------------------------------------------------
inline bool NiRay::GetPerpendicularPassingThrough(
    const NiPoint3& kPoint, NiPoint3& kIntersection, NiPoint3& kDirection)
    const
{
    // algorithm concept from:
    // http://local.wasp.uwa.edu.au/~pbourke/geometry/pointline/

    float fProjection =
        (kPoint.x - m_kRayOrigin.x)*(m_kRayDir.x) +
        (kPoint.y - m_kRayOrigin.y)*(m_kRayDir.y) +
        (kPoint.z - m_kRayOrigin.z)*(m_kRayDir.z);

    kIntersection = m_kRayOrigin + m_kRayDir * fProjection;
    kDirection = kPoint - kIntersection;

    float fLen = NiPoint3::VectorLength(kDirection);
    if (NiAbs(fLen) < FLT_EPSILON)
    {
        return false;
    }

    kDirection /= NiPoint3::VectorLength(kDirection);
    return true;
}

//--------------------------------------------------------------------------------------------------
inline bool NiRay::PassesThroughBound(const NiBound& kBound) const
{
    float fDist = m_kRayDir.Cross(kBound.GetCenter() - m_kRayOrigin).SqrLength();

    float fRadius = kBound.GetRadius();
    float fRadiusSqr = NiSqr(fRadius);
    if (fDist > fRadiusSqr)
    {
        return false;
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
inline bool NiRay::TryTriangle(const NiPoint3& k0, const NiPoint3& k1,
    const NiPoint3& k2,
    NiPoint3& kCollisionPoint)
{
    // See: http://www.cs.cornell.edu/Courses/cs465/2003fa/homeworks/raytri.pdf

    // First, find the normal vector.
    NiPoint3 kNormal = (k1 - k0).Cross(k2 - k0);
    float fRayDotNormal = m_kRayDir.Dot(kNormal);

    // Triangle facing right direction?
    if (fRayDotNormal <= 0.0f) {
        return false;
    }

    // Find intersection point on the triangles plane
    float fDistFromPlane = -1.0f * ((m_kRayOrigin - k0).Dot(kNormal) / fRayDotNormal);

    kCollisionPoint = m_kRayOrigin + (fDistFromPlane * m_kRayDir);

    // Now see if point is on same side as all 3 triangles
    if ((k1 - k0).Cross(kCollisionPoint - k0).Dot(kNormal) >= 0.0f &&
        (k2 - k1).Cross(kCollisionPoint - k1).Dot(kNormal) >= 0.0f &&
        (k0 - k2).Cross(kCollisionPoint - k2).Dot(kNormal) >= 0.0f)
    {
        return true;
    }

    kCollisionPoint = NiPoint3::ZERO;
    return false;
}
