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
inline bool NiPSSMConfiguration::GetSceneDependentFrustumsEnabled() const
{
    return GetBit(SCENEDEPENDENTFRUSTUMS);
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetSceneDependentFrustumsEnabled(bool bEnabled)
{
    SetBit(bEnabled, SCENEDEPENDENTFRUSTUMS);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSSMConfiguration::GetCustomSceneCameraFrustumEnabled() const
{
    return GetBit(CUSTOMCAMERAFRUSTUM);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSSMConfiguration::GetCustomSceneCameraFarPlaneEnabled() const
{
    return GetBit(CUSTOMFARPLANE);
}

//--------------------------------------------------------------------------------------------------
inline const NiFrustum& NiPSSMConfiguration::GetCustomSceneCameraFrustum() const
{
    return m_kCustumSceneFrustum;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetCustomSceneCameraFrustumEnabled(
    const NiFrustum& kSceneFrustum)
{
    SetBit(true, CUSTOMCAMERAFRUSTUM);
    m_kCustumSceneFrustum = kSceneFrustum;

    SetRebuildFrustums();
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetCustomSceneCameraFrustumDisabled()
{
    SetBit(false, CUSTOMCAMERAFRUSTUM);

    SetRebuildFrustums();
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSMConfiguration::GetCameraDistanceScaleFactor() const
{
    return m_fCameraDistScaleFactor;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetCameraDistanceScaleFactor(
    float fCameraDistScaleFactor)
{
    m_fCameraDistScaleFactor = fCameraDistScaleFactor;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetCustomSceneCameraFarPlaneEnabled(
    bool bEnabled)
{
    SetBit(bEnabled, CUSTOMFARPLANE);

    SetRebuildFrustums();
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetCustomSceneCameraFarPlane(float fFarPlane)
{
    m_kCustumSceneFrustum.m_fFar = fFarPlane;
    SetBit(true, CUSTOMFARPLANE);

    SetRebuildFrustums();
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSMConfiguration::GetCustomSceneCameraFarPlane()
{
    return m_kCustumSceneFrustum.m_fFar;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSSMConfiguration::GetSubTexelOffsetEnabled() const
{
    return GetBit(SUBTEXELOFFSET);
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetSubTexelOffsetEnabled(bool bEnabled)
{
    SetBit(bEnabled, SUBTEXELOFFSET);
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiPSSMConfiguration::GetExtraSplitSpacing() const
{
    return m_uiExtraSplitSpacing;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetExtraSplitSpacing(
    NiUInt32 uiExtraSplitSpacing)
{
    m_uiExtraSplitSpacing = uiExtraSplitSpacing;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSSMConfiguration::GetBorderTestingEnabled() const
{
    return GetBit(BORDERTESTING);
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetBorderTestingEnabled(bool bEnabled)
{
    SetBit(bEnabled, BORDERTESTING);
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSSMConfiguration::GetSliceTransitionEnabled() const
{
    return GetBit(SLICETRANSITIONS);
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSMConfiguration::GetSliceTransitionSize() const
{
    return m_fSliceTransitionSize;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetSliceTransitionSize(float fSize)
{
    m_fSliceTransitionSize = fSize;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSMConfiguration::GetSliceTransitionNoiseScale() const
{
    return m_fSliceTransitionScale;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetSliceTransitionNoiseScale(float fScale)
{
    EE_ASSERT(fScale >= 0.0f && fScale <= 1.0f);
    m_fSliceTransitionScale = fScale;
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSMConfiguration::GetSliceLambda() const
{
    return m_fSliceLambda;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetSliceLambda(float fLambda)
{
    m_fSliceLambda = fLambda;

    SetRebuildFrustums();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt8 NiPSSMConfiguration::GetNumSlices() const
{
    return m_ucNumSlices;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::GetPSSMSliceViewport(NiUInt8 ucSliceIndex,
    NiRect<float>& kViewport)
{
    kViewport = GetPSSMSliceViewport(ucSliceIndex);
}

//--------------------------------------------------------------------------------------------------
inline const NiRect<float>& NiPSSMConfiguration::GetPSSMSliceViewport(
    NiUInt8 ucSliceIndex) const
{
    EE_ASSERT(m_pkSliceViewports);
    EE_ASSERT(ucSliceIndex < m_ucNumSlices);

    // Assign output
    return m_pkSliceViewports[ucSliceIndex];
}

//--------------------------------------------------------------------------------------------------
inline NiRect<float>& NiPSSMConfiguration::GetPSSMSliceViewport(
    NiUInt8 ucSliceIndex)
{
    EE_ASSERT(m_pkSliceViewports);
    EE_ASSERT(ucSliceIndex < m_ucNumSlices);

    // Assign output
    return m_pkSliceViewports[ucSliceIndex];
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSMConfiguration::GetPSSMSliceMinDistance(NiUInt8 ucSliceIndex)
    const
{
    EE_ASSERT(ucSliceIndex < m_ucNumSlices);
    EE_ASSERT(m_pfSliceDistances);

    return m_pfSliceDistances[ucSliceIndex];
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetPSSMSliceMinDistance(float fDist,
     NiUInt8 ucSliceIndex)
{
    EE_ASSERT(ucSliceIndex < m_ucNumSlices);
    EE_ASSERT(m_pfSliceDistances);

    m_pfSliceDistances[ucSliceIndex] = fDist;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSSMConfiguration::GetIsBoundToGenerator() const
{
    return GetBit(ISBOUNDTOGENERATOR);
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetIsBoundToGenerator(bool bBound)
{
    SetBit(bBound, ISBOUNDTOGENERATOR);
}

//--------------------------------------------------------------------------------------------------
inline float NiPSSMConfiguration::GetPSSMSliceMaxDistance(NiUInt8 ucSliceIndex)
    const
{
    EE_ASSERT(ucSliceIndex < m_ucNumSlices);
    EE_ASSERT(m_pfSliceDistances);

    return m_pfSliceDistances[ucSliceIndex + 1];
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetPSSMSliceMaxDistance(float fDist,
    NiUInt8 ucSliceIndex)
{
    EE_ASSERT(ucSliceIndex < m_ucNumSlices);
    EE_ASSERT(m_pfSliceDistances);

    m_pfSliceDistances[ucSliceIndex + 1] = fDist;
}

//--------------------------------------------------------------------------------------------------
inline const NiCamera* NiPSSMConfiguration::GetSliceTransitionCamera() const
{
    return &m_kSliceTransitionCamera;
}

//--------------------------------------------------------------------------------------------------
inline NiCamera* NiPSSMConfiguration::GetSliceTransitionCamera()
{
    return &m_kSliceTransitionCamera;
}

//--------------------------------------------------------------------------------------------------
inline bool NiPSSMConfiguration::GetRebuildFrustums() const
{
    return GetBit(REBUILDFRUSTUMS);
}

//--------------------------------------------------------------------------------------------------
inline void NiPSSMConfiguration::SetRebuildFrustums(bool bRebuild)
{
    SetBit(bRebuild, REBUILDFRUSTUMS);
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSSMConfiguration::GetPackedSplitMatrices() const
{
    return m_pfPackedMatrices;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSSMConfiguration::GetPackedSplitDistances() const
{
    return m_pfPackedDistances;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSSMConfiguration::GetPackedSplitViewports() const
{
    return m_pfPackedViewports;
}

//--------------------------------------------------------------------------------------------------
inline float* NiPSSMConfiguration::GetPackedTransitionMatrix() const
{
    return m_pfPackedTransitionMatrix;
}

//--------------------------------------------------------------------------------------------------
inline NiAVObjectRawList* NiPSSMConfiguration::GetCasterList()
{
    if (!m_pkCasterList)
        m_pkCasterList = NiNew NiAVObjectRawList();

    return m_pkCasterList;
}

//--------------------------------------------------------------------------------------------------