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
inline NiTerrainRandomAccessIterator::NiTerrainRandomAccessIterator() :
    m_pfBuffer(NULL),
    m_uiElementStride(0),
    m_uiTotalStride(0),
    m_uiBufferSize(0),
    m_bCompressionEnabled(false),
    m_bMorphingEnabled(false)
{
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainRandomAccessIterator::NiTerrainRandomAccessIterator(NiDataStreamLock* pkLock,
    NiUInt32 uiRegionIndex, const NiTerrainConfiguration& kConfiguration)
{
    EE_UNUSED_ARG(uiRegionIndex);
    EE_UNUSED_ARG(pkLock);
    EE_UNUSED_ARG(kConfiguration);

    EE_FAIL("Invalid stream type");
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainRandomAccessIterator::GetTotalStride() const
{
    return m_uiTotalStride;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainRandomAccessIterator::GetElementStride() const
{
    return m_uiElementStride;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainRandomAccessIterator::GetMorphingEnabled() const
{
    return m_bMorphingEnabled;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainRandomAccessIterator::GetCompressionEnabled() const
{
    return m_bCompressionEnabled;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainRandomAccessIterator::Exists() const
{
    return m_pfBuffer != NULL;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainRandomAccessIterator::CopyFrom(NiUInt32 uiDestIndex,
    const NiTerrainRandomAccessIterator& kSource,
    NiUInt32 uiSourceIndex) const
{
    EE_ASSERT(Exists() && kSource.Exists());
    NiUInt32 uiDestOffset = GetTotalStride() * uiDestIndex;
    NiUInt32 uiSourceOffset = kSource.GetTotalStride() * uiSourceIndex;
    NiMemcpy(m_pfBuffer + uiDestOffset,
        kSource.m_pfBuffer + uiSourceOffset,
        GetElementStride());
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainRandomAccessIterator::Get(NiUInt32 uiIndex, NiPoint4& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 4);

    kPoint.SetX(m_pfBuffer[uiPos]);
    kPoint.SetY(m_pfBuffer[++uiPos]);
    kPoint.SetZ(m_pfBuffer[++uiPos]);
    kPoint.SetW(m_pfBuffer[++uiPos]);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainRandomAccessIterator::Get(NiUInt32 uiIndex, NiPoint3& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 3);

    kPoint.x = m_pfBuffer[uiPos];
    kPoint.y = m_pfBuffer[++uiPos];
    kPoint.z = m_pfBuffer[++uiPos];
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainRandomAccessIterator::Get(NiUInt32 uiIndex, NiPoint2& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 2);

    kPoint.x = m_pfBuffer[uiPos];
    kPoint.y = m_pfBuffer[++uiPos];
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainRandomAccessIterator::GetComponent(NiUInt32 uiIndex, 
    COMPONENT eComponent) const
{
    EE_ASSERT((NiUInt32)eComponent < GetElementStride());
    return m_pfBuffer[uiIndex * GetTotalStride() + (NiUInt32)eComponent];
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainRandomAccessIterator::Set(NiUInt32 uiIndex, const NiPoint4& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 4);
    EE_ASSERT((uiPos + 3) < m_uiBufferSize);

    m_pfBuffer[uiPos] = kPoint.X();
    m_pfBuffer[++uiPos] = kPoint.Y();
    m_pfBuffer[++uiPos] = kPoint.Z();
    m_pfBuffer[++uiPos] = kPoint.W();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainRandomAccessIterator::Set(NiUInt32 uiIndex, const NiPoint3& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 3);
    EE_ASSERT((uiPos + 2) < m_uiBufferSize);

    m_pfBuffer[uiPos] = kPoint.x;
    m_pfBuffer[++uiPos] = kPoint.y;
    m_pfBuffer[++uiPos] = kPoint.z;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainRandomAccessIterator::Set(NiUInt32 uiIndex, const NiPoint2& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 2);
    EE_ASSERT((uiPos + 1) < m_uiBufferSize);

    m_pfBuffer[uiPos] = kPoint.x;
    m_pfBuffer[++uiPos] = kPoint.y;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainRandomAccessIterator::SetComponent(NiUInt32 uiIndex, COMPONENT eComponent, 
    float fValue) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride() + (NiUInt32)eComponent;
    EE_ASSERT(GetElementStride() >= (NiUInt32)eComponent);
    EE_ASSERT((uiPos) < m_uiBufferSize);
    m_pfBuffer[uiPos] = fValue;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainRandomAccessIterator::GetHighDetail(NiUInt32 uiIndex, NiPoint2& kPoint) const
{
    EE_UNUSED_ARG(uiIndex);
    EE_UNUSED_ARG(kPoint);
    EE_FAIL("Invalid operation on this stream.");
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainRandomAccessIterator::GetLowDetail(NiUInt32 uiIndex,  NiPoint2& kPoint) const
{
    EE_UNUSED_ARG(uiIndex);
    EE_UNUSED_ARG(kPoint);
    EE_FAIL("Invalid operation on this stream.");
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
inline NiTerrainPositionRandomAccessIterator::NiTerrainPositionRandomAccessIterator()
{
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainPositionRandomAccessIterator::NiTerrainPositionRandomAccessIterator(
    NiDataStreamLock* pkLock, NiUInt32 uiRegionIndex, 
    const NiTerrainConfiguration& kConfiguration)
{
    NiTStridedRandomAccessIterator<float> kBaseIterator =
        pkLock->begin_region<float>(uiRegionIndex);
    if (kBaseIterator.Exists())
        m_pfBuffer = &kBaseIterator[0];
    else
        m_pfBuffer = NULL;

    m_bCompressionEnabled = false;
    m_bMorphingEnabled = kConfiguration.IsMorphingDataEnabled();
    m_uiElementStride = pkLock->GetDataStream()->GetElementDescAt(0).GetComponentCount();
    m_uiTotalStride = pkLock->GetDataStream()->GetStride() / sizeof(float);
    m_uiBufferSize = pkLock->GetDataStream()->GetSize() / sizeof(float);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainPositionRandomAccessIterator::GetHighDetail(NiUInt32 uiIndex, 
    NiPoint3& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 3);

    kPoint.x = m_pfBuffer[uiPos];
    kPoint.y = m_pfBuffer[++uiPos];
    kPoint.z = m_pfBuffer[++uiPos];
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainPositionRandomAccessIterator::GetLowDetail(NiUInt32 uiIndex, 
    NiPoint3& kPoint) const
{
    if (!GetCompressionEnabled())
        return;

    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 3);

    kPoint.x = m_pfBuffer[uiPos];
    kPoint.y = m_pfBuffer[++uiPos];
    kPoint.z = m_pfBuffer[uiPos + 2];
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainPositionRandomAccessIterator::SetHighDetail(NiUInt32 uiIndex, 
    const NiPoint3& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 3);
    EE_ASSERT((uiPos + 2) < m_uiBufferSize);

    m_pfBuffer[uiPos] = kPoint.x;
    m_pfBuffer[++uiPos] = kPoint.y;
    m_pfBuffer[++uiPos] = kPoint.z;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainPositionRandomAccessIterator::SetLowDetail(NiUInt32 uiIndex, 
    const NiPoint3& kPoint) const
{
    if (!GetMorphingEnabled())
        return;

    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 4);
    EE_ASSERT((uiPos + 3) < m_uiBufferSize);

    m_pfBuffer[uiPos] = kPoint.x;
    m_pfBuffer[++uiPos] = kPoint.y;
    m_pfBuffer[uiPos + 2] = kPoint.z;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainPositionRandomAccessIterator::SetHighDetail(NiUInt32 uiIndex, 
    const NiPoint2& kPoint) const
{
    EE_UNUSED_ARG(uiIndex);
    EE_UNUSED_ARG(kPoint);
    EE_FAIL("Invalid operation on Position stream.");
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainPositionRandomAccessIterator::SetLowDetail(NiUInt32 uiIndex, 
    const NiPoint2& kPoint) const
{
    EE_UNUSED_ARG(uiIndex);
    EE_UNUSED_ARG(kPoint);
    EE_FAIL("Invalid operation on Position stream.");
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
inline NiTerrainNormalRandomAccessIterator::NiTerrainNormalRandomAccessIterator()
{
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainNormalRandomAccessIterator::NiTerrainNormalRandomAccessIterator(
    NiDataStreamLock* pkLock, NiUInt32 uiRegionIndex, const NiTerrainConfiguration& kConfiguration)
{
    NiTStridedRandomAccessIterator<float> kBaseIterator =
        pkLock->begin_region<float>(uiRegionIndex);
    if (kBaseIterator.Exists())
        m_pfBuffer = &kBaseIterator[0];
    else
        m_pfBuffer = NULL;

    m_bCompressionEnabled = kConfiguration.IsLightingDataCompressionEnabled();
    m_bMorphingEnabled = kConfiguration.IsMorphingDataEnabled();
    m_uiElementStride = pkLock->GetDataStream()->GetElementDescAt(0).GetComponentCount();
    m_uiTotalStride = pkLock->GetDataStream()->GetStride() / sizeof(float);
    m_uiBufferSize = pkLock->GetDataStream()->GetSize() / sizeof(float);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainNormalRandomAccessIterator::GetHighDetail(NiUInt32 uiIndex,
    NiPoint3& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    
    if (GetCompressionEnabled())
    {
        EE_ASSERT(GetElementStride() >= 2);

        ((NiPoint4*)&m_pfBuffer[uiPos])->DecompressXYIntoNormalized(
            kPoint);
    }
    else
    {
        EE_ASSERT(GetElementStride() >= 3);

        kPoint.x = m_pfBuffer[uiPos];
        kPoint.y = m_pfBuffer[++uiPos];
        kPoint.z = m_pfBuffer[++uiPos];
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainNormalRandomAccessIterator::GetLowDetail(NiUInt32 uiIndex, 
    NiPoint3& kPoint) const
{
    if (!GetCompressionEnabled())
        return;

    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 4);

    ((NiPoint4*)&m_pfBuffer[uiPos])->DecompressZWIntoNormalized(kPoint);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainNormalRandomAccessIterator::GetHighDetail(NiUInt32 uiIndex, 
    NiPoint2& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    if (GetCompressionEnabled())
    {
        EE_ASSERT(GetElementStride() >= 2);

        kPoint.x = m_pfBuffer[uiPos];
        kPoint.y = m_pfBuffer[++uiPos];
    }
    else
    {
        EE_ASSERT(GetElementStride() >= 3);

        NiPoint4 kCompressed;
        kCompressed.CompressNormalizedIntoXY(
            *(NiPoint3*)&m_pfBuffer[uiPos]);
        kPoint.x = kCompressed.X();
        kPoint.y = kCompressed.Y();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainNormalRandomAccessIterator::GetLowDetail(NiUInt32 uiIndex, 
    NiPoint2& kPoint) const
{
    if (!GetCompressionEnabled())
        return;

    NiUInt32 uiPos = uiIndex * GetTotalStride() + 2;
    EE_ASSERT(GetElementStride() >= 4);

    kPoint.x = m_pfBuffer[uiPos];
    kPoint.y = m_pfBuffer[++uiPos];
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainNormalRandomAccessIterator::SetHighDetail(NiUInt32 uiIndex, 
    const NiPoint3& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();

    if (GetCompressionEnabled())
    {
        EE_ASSERT(GetElementStride() >= 2);
        EE_ASSERT((uiPos + 3) < m_uiBufferSize);

        ((NiPoint4*)&m_pfBuffer[uiPos])->CompressNormalizedIntoXY(kPoint);
    }
    else
    {
        EE_ASSERT(GetElementStride() >= 3);
        EE_ASSERT((uiPos + 2) < m_uiBufferSize);

        m_pfBuffer[uiPos] = kPoint.x;
        m_pfBuffer[++uiPos] = kPoint.y;
        m_pfBuffer[++uiPos] = kPoint.z;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainNormalRandomAccessIterator::SetLowDetail(NiUInt32 uiIndex, 
    const NiPoint3& kPoint) const
{
    if (!GetMorphingEnabled())
        return;

    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 4);
    EE_ASSERT((uiPos + 3) < m_uiBufferSize);

    ((NiPoint4*)&m_pfBuffer[uiPos])->CompressNormalizedIntoZW(kPoint);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainNormalRandomAccessIterator::SetHighDetail(NiUInt32 uiIndex, 
    const NiPoint2& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 2);

    if (GetCompressionEnabled())
    {
        EE_ASSERT((uiPos + 1) < m_uiBufferSize);
        m_pfBuffer[uiPos] = kPoint.x;
        m_pfBuffer[++uiPos] = kPoint.y;
    }
    else
    {
        EE_ASSERT((uiPos + 2) < m_uiBufferSize);
        NiPoint4 kCompressed;
        kCompressed.SetX(kPoint.x);
        kCompressed.SetY(kPoint.y);
        kCompressed.DecompressXYIntoNormalized(
            *(NiPoint3*)&m_pfBuffer[uiPos]);
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainNormalRandomAccessIterator::SetLowDetail(NiUInt32 uiIndex, 
    const NiPoint2& kPoint) const
{
    if (!GetMorphingEnabled())
        return;

    NiUInt32 uiPos = uiIndex * GetTotalStride() + 2;
    EE_ASSERT(GetElementStride() >= 4);
    EE_ASSERT((uiPos + 1) < m_uiBufferSize);

    m_pfBuffer[uiPos] = kPoint.x;
    m_pfBuffer[++uiPos] = kPoint.y;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
inline NiTerrainTangentRandomAccessIterator::NiTerrainTangentRandomAccessIterator()
{
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainTangentRandomAccessIterator::NiTerrainTangentRandomAccessIterator(
    NiDataStreamLock* pkLock, NiUInt32 uiRegionIndex, const NiTerrainConfiguration& kConfiguration)
{
    if (!kConfiguration.IsTangentDataEnabled() ||
        pkLock->GetDataStream()->GetElementDescCount() < 2)
        return;

    NiTStridedRandomAccessIterator<float> kBaseIterator =
        pkLock->begin_region<float>(uiRegionIndex);
    if (kBaseIterator.Exists())
        m_pfBuffer = &kBaseIterator[0];
    else
        m_pfBuffer = NULL;

    m_bCompressionEnabled = kConfiguration.IsLightingDataCompressionEnabled();
    m_bMorphingEnabled = kConfiguration.IsMorphingDataEnabled();
    m_uiElementStride = pkLock->GetDataStream()->GetElementDescAt(1).GetComponentCount();
    m_uiTotalStride = pkLock->GetDataStream()->GetStride() / sizeof(float);
    m_uiBufferSize = pkLock->GetDataStream()->GetSize() / sizeof(float);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTangentRandomAccessIterator::GetHighDetail(NiUInt32 uiIndex, 
    NiPoint3& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();

    if (GetCompressionEnabled())
    {
        EE_ASSERT(GetElementStride() >= 2);

        kPoint.x = m_pfBuffer[uiPos];
        kPoint.y = 0.0f;
        kPoint.z = m_pfBuffer[++uiPos];
    }
    else
    {
        EE_ASSERT(GetElementStride() >= 3);

        kPoint.x = m_pfBuffer[uiPos];
        kPoint.y = m_pfBuffer[++uiPos];
        kPoint.z = m_pfBuffer[++uiPos];
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTangentRandomAccessIterator::GetLowDetail(NiUInt32 uiIndex, 
    NiPoint3& kPoint) const
{
    if (!GetCompressionEnabled())
        return;

    NiUInt32 uiPos = uiIndex * GetTotalStride() + 2;
    EE_ASSERT(GetElementStride() >= 3);

    kPoint.x = m_pfBuffer[uiPos];
    kPoint.y = 0.0f;
    kPoint.z = m_pfBuffer[++uiPos];
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTangentRandomAccessIterator::GetHighDetail(NiUInt32 uiIndex, 
    NiPoint2& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    if (GetCompressionEnabled())
    {
        EE_ASSERT(GetElementStride() >= 2);

        kPoint.x = m_pfBuffer[uiPos];
        kPoint.y = m_pfBuffer[++uiPos];
    }
    else
    {
        EE_ASSERT(GetElementStride() >= 3);

        kPoint.x = m_pfBuffer[uiPos];
        kPoint.y = m_pfBuffer[uiPos + 2];
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTangentRandomAccessIterator::GetLowDetail(NiUInt32 uiIndex, 
    NiPoint2& kPoint) const
{
    if (!GetCompressionEnabled())
        return;

    NiUInt32 uiPos = uiIndex * GetTotalStride() + 2;
    EE_ASSERT(GetElementStride() >= 4);

    kPoint.x = m_pfBuffer[uiPos];
    kPoint.y = m_pfBuffer[++uiPos];
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTangentRandomAccessIterator::SetHighDetail(NiUInt32 uiIndex, 
    const NiPoint3& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();

    if (GetCompressionEnabled())
    {
        EE_ASSERT(GetElementStride() >= 2);
        EE_ASSERT((uiPos + 1) < m_uiBufferSize);

        m_pfBuffer[uiPos] = kPoint.x;
        m_pfBuffer[++uiPos] = kPoint.z;
    }
    else
    {
        EE_ASSERT(GetElementStride() >= 3);
        EE_ASSERT((uiPos + 2) < m_uiBufferSize);

        m_pfBuffer[uiPos] = kPoint.x;
        m_pfBuffer[++uiPos] = 0.0f;
        m_pfBuffer[++uiPos] = kPoint.z;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTangentRandomAccessIterator::SetLowDetail(NiUInt32 uiIndex, 
    const NiPoint3& kPoint) const
{
    if (!GetMorphingEnabled())
        return;

    NiUInt32 uiPos = uiIndex * GetTotalStride() + 2;
    EE_ASSERT(GetElementStride() >= 4);
    EE_ASSERT((uiPos + 1) < m_uiBufferSize);

    m_pfBuffer[uiPos] = kPoint.x;
    m_pfBuffer[++uiPos] = kPoint.z;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTangentRandomAccessIterator::SetHighDetail(NiUInt32 uiIndex, 
    const NiPoint2& kPoint) const
{
    NiUInt32 uiPos = uiIndex * GetTotalStride();
    EE_ASSERT(GetElementStride() >= 2);

    if (GetCompressionEnabled())
    {
        EE_ASSERT((uiPos + 1) < m_uiBufferSize);
        m_pfBuffer[uiPos] = kPoint.x;
        m_pfBuffer[++uiPos] = kPoint.y;
    }
    else
    {
        EE_ASSERT((uiPos + 2) < m_uiBufferSize);
        m_pfBuffer[uiPos] = kPoint.x;
        m_pfBuffer[++uiPos] = 0.0f;
        m_pfBuffer[++uiPos] = kPoint.y;
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainTangentRandomAccessIterator::SetLowDetail(NiUInt32 uiIndex, 
    const NiPoint2& kPoint) const
{
    if (!GetMorphingEnabled())
        return;

    NiUInt32 uiPos = uiIndex * GetTotalStride() + 2;
    EE_ASSERT(GetElementStride() >= 4);
    EE_ASSERT((uiPos + 1) < m_uiBufferSize);

    m_pfBuffer[uiPos] = kPoint.x;
    m_pfBuffer[++uiPos] = kPoint.y;
}

//--------------------------------------------------------------------------------------------------