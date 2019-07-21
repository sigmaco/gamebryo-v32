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
inline NiDataStreamRef::NiDataStreamRef() :
    m_puiSubmeshToRegionIndexMap(NULL), m_pkSemantics(NULL),
    m_bIsPerInstance(false), m_uiSubmeshToRegionIndexMapCount(0)
{
}

//--------------------------------------------------------------------------------------------------
inline NiDataStreamRef::~NiDataStreamRef()
{
    NiDelete [] m_pkSemantics;
    NiFree(m_puiSubmeshToRegionIndexMap);
}

//--------------------------------------------------------------------------------------------------
inline NiDataStream* NiDataStreamRef::GetDataStream()
{
    return m_spDataStream;
}

//--------------------------------------------------------------------------------------------------
inline const NiDataStream* NiDataStreamRef::GetDataStream() const
{
    return m_spDataStream;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiDataStreamRef::GetStride() const
{
    EE_ASSERT(m_spDataStream);
    return m_spDataStream->GetStride();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiDataStreamRef::GetSize() const
{
    EE_ASSERT(m_spDataStream);
    return m_spDataStream->GetSize();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiDataStreamRef::GetTotalCount() const
{
    EE_ASSERT(m_spDataStream);
    return m_spDataStream->GetTotalCount();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiDataStreamRef::GetCount(NiUInt32 uiSubmeshIdx) const
{
    EE_ASSERT(m_spDataStream);
    return m_spDataStream->GetCount(RemapSubmeshToRegion(uiSubmeshIdx));
}

//--------------------------------------------------------------------------------------------------
inline NiUInt8 NiDataStreamRef::GetAccessMask() const
{
    EE_ASSERT(m_spDataStream);
    return m_spDataStream->GetAccessMask();
}

//--------------------------------------------------------------------------------------------------
inline NiDataStream::Usage NiDataStreamRef::GetUsage() const
{
    EE_ASSERT(m_spDataStream);
    return m_spDataStream->GetUsage();
}

//--------------------------------------------------------------------------------------------------
inline NiDataStream::Region& NiDataStreamRef::GetRegionForSubmesh(
    NiUInt32 uiSubmeshIdx)
{
    NiUInt32 uiRegionIdx = RemapSubmeshToRegion(uiSubmeshIdx);
    EE_ASSERT(m_spDataStream);
    return m_spDataStream->GetRegion(uiRegionIdx);
}

//--------------------------------------------------------------------------------------------------
inline const NiDataStream::Region& NiDataStreamRef::GetRegionForSubmesh(
    NiUInt32 uiSubmeshIdx) const
{
    NiUInt32 uiRegionIdx = RemapSubmeshToRegion(uiSubmeshIdx);
    EE_ASSERT(m_spDataStream);
    return m_spDataStream->GetRegion(uiRegionIdx);
}

//--------------------------------------------------------------------------------------------------
inline void NiDataStreamRef::BindRegionToSubmesh(NiUInt32 uiSubmeshIdx,
    NiUInt32 uiDataStreamRegionIdx)
{
    if (m_uiSubmeshToRegionIndexMapCount <= uiSubmeshIdx)
        SetSubmeshCount(uiSubmeshIdx + 1);

    EE_ASSERT(m_spDataStream);
    EE_ASSERT(m_spDataStream->GetRegionCount() > uiDataStreamRegionIdx);
    m_puiSubmeshToRegionIndexMap[uiSubmeshIdx] =
        (NiUInt16) uiDataStreamRegionIdx;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiDataStreamRef::GetElementDescCount() const
{
    EE_ASSERT(m_spDataStream);
    return m_spDataStream->GetElementDescCount();
}

//--------------------------------------------------------------------------------------------------
inline const NiDataStreamElement& NiDataStreamRef::GetElementDescAt(
    NiUInt32 uiElementDescIdx) const
{
    EE_ASSERT(m_spDataStream);
    return m_spDataStream->GetElementDescAt(uiElementDescIdx);
}

//--------------------------------------------------------------------------------------------------
inline const NiFixedString& NiDataStreamRef::GetSemanticNameAt(
    NiUInt32 uiElementDescIdx) const
{
    EE_ASSERT(uiElementDescIdx < GetElementDescCount());
    return m_pkSemantics[uiElementDescIdx].m_kName;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiDataStreamRef::GetSemanticIndexAt(
    NiUInt32 uiElementDescIdx) const
{
    EE_ASSERT(uiElementDescIdx < GetElementDescCount());
    return m_pkSemantics[uiElementDescIdx].m_uiIndex;
}

//--------------------------------------------------------------------------------------------------
inline const NiDataStreamElement& NiDataStreamRef::FindElementDesc(
    const NiFixedString& kSemantic, NiUInt32 uiSemanticIdx) const
{
    NiUInt32 uiElementIdx = FindElementDescIndex(kSemantic, uiSemanticIdx);
    if (uiElementIdx != UINT_MAX)
        return GetElementDescAt(uiElementIdx);
    else
        return NiDataStreamElement::ms_kInvalidElement;
}

//--------------------------------------------------------------------------------------------------
inline void NiDataStreamRef::BindSemanticToElementDescAt(NiUInt32 uiElementIdx,
    const NiFixedString& kSemantic, NiUInt32 uiSemanticIdx)
{
    EE_ASSERT(uiElementIdx < GetElementDescCount());

    m_pkSemantics[uiElementIdx].m_kName = kSemantic;
    m_pkSemantics[uiElementIdx].m_uiIndex = uiSemanticIdx;
}

//--------------------------------------------------------------------------------------------------
inline bool NiDataStreamRef::IsPerInstance() const
{
    return m_bIsPerInstance;
}

//--------------------------------------------------------------------------------------------------
inline void NiDataStreamRef::SetPerInstance(bool bIsPerInstance)
{
    m_bIsPerInstance = bIsPerInstance;
}

//--------------------------------------------------------------------------------------------------
inline void NiDataStreamRef::SetActiveCount(NiUInt32 uiSubmeshIdx,
    NiUInt32 uiCount)
{
    GetRegionForSubmesh(uiSubmeshIdx).SetRange(uiCount);
}

//--------------------------------------------------------------------------------------------------
inline void NiDataStreamRef::Reset()
{
    NiDelete [] m_pkSemantics;
    m_pkSemantics = NULL;
    NiFree(m_puiSubmeshToRegionIndexMap);
    m_puiSubmeshToRegionIndexMap = NULL;
    m_uiSubmeshToRegionIndexMapCount = 0;
    m_bIsPerInstance = false;
    m_spDataStream = NULL;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiDataStreamRef::RemapSubmeshToRegion(NiUInt32 uiSubmeshIdx)
    const
{
    EE_ASSERT(m_uiSubmeshToRegionIndexMapCount > uiSubmeshIdx);
    EE_ASSERT(m_puiSubmeshToRegionIndexMap);
    return m_puiSubmeshToRegionIndexMap[uiSubmeshIdx];
}

//--------------------------------------------------------------------------------------------------
inline NiDataStreamRef::Semantic::Semantic() : m_uiIndex(0)
{
}

//--------------------------------------------------------------------------------------------------
inline bool NiDataStreamRef::GetStreamable() const
{
    return m_spDataStream->GetStreamable();
}

//--------------------------------------------------------------------------------------------------
inline void NiDataStreamRef::SetStreamable(bool bStreamable)
{
    m_spDataStream->SetStreamable(bStreamable);
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiDataStreamRef::GetRegionIndexForSubmesh(
    NiUInt32 uiSubmeshIdx) const
{
    EE_ASSERT(uiSubmeshIdx < m_uiSubmeshToRegionIndexMapCount);
    return m_puiSubmeshToRegionIndexMap[uiSubmeshIdx];
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiDataStreamRef::GetSubmeshRemapCount() const
{
    return (NiUInt32) m_uiSubmeshToRegionIndexMapCount;
}

//--------------------------------------------------------------------------------------------------
inline NiDataStreamRef NiDataStreamRef::CreateFullCopy() const
{
    NiDataStreamRef kRef = *this;
    kRef.SetDataStream(m_spDataStream->CreateFullCopy());
    return kRef;
}

//--------------------------------------------------------------------------------------------------
inline bool operator==(const NiDataStreamRef& r1,
    const NiDataStreamRef& r2)
{
    return r1.IsEqual(&r2);
}

//--------------------------------------------------------------------------------------------------
inline bool operator!=(const NiDataStreamRef& r1,
    const NiDataStreamRef& r2)
{
    return !(r1.IsEqual(&r2));
}

//--------------------------------------------------------------------------------------------------
