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
template<class BufferType> inline
NiTerrainDeformationBuffer<BufferType>::NiTerrainDeformationBuffer():
    m_pkBuffer(NULL),
    m_uiAllocatedSize(0),
    m_uiWidth(0),
    m_uiHeight(0)
{
}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
NiTerrainDeformationBuffer<BufferType>::NiTerrainDeformationBuffer(
    const NiTerrainDeformationBuffer& kTerrainDeformationBuffer):
    m_pkBuffer(NULL),
    m_uiAllocatedSize(0),
    m_uiWidth(0),
    m_uiHeight(0)
{
    if(SetDeformationRegion(
        kTerrainDeformationBuffer.GetAffectedSectorRange(), 
        kTerrainDeformationBuffer.GetDataRegion(), 
        kTerrainDeformationBuffer.GetTerrainSpaceRegion(),
        kTerrainDeformationBuffer.GetWidth(), 
        kTerrainDeformationBuffer.GetHeight()))
    {
        memcpy(m_pkBuffer, kTerrainDeformationBuffer.GetBuffer(), 
            kTerrainDeformationBuffer.GetSize());
    }

}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
NiTerrainDeformationBuffer<BufferType>::~NiTerrainDeformationBuffer()
{
    EE_FREE(m_pkBuffer);
}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
BufferType* NiTerrainDeformationBuffer<BufferType>::GetBuffer() const
{
    return m_pkBuffer;
}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
efd::UInt32 NiTerrainDeformationBuffer<BufferType>::GetLength() const
{
    return m_uiWidth * m_uiHeight;
}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
efd::UInt32 NiTerrainDeformationBuffer<BufferType>::GetSize() const
{
    return GetLength() * sizeof(BufferType);
}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
const NiRect<efd::SInt32>& NiTerrainDeformationBuffer<BufferType>::GetAffectedSectorRange() const
{
    return m_kAffectedSectorRange;
}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
const NiRect<efd::SInt32>& NiTerrainDeformationBuffer<BufferType>::GetDataRegion() const
{
    return m_kDataRegion;
}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
const NiRect<efd::Float32>& NiTerrainDeformationBuffer<BufferType>::GetTerrainSpaceRegion() const
{
    return m_kTerrainSpaceRegion;
}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
efd::UInt32 NiTerrainDeformationBuffer<BufferType>::GetWidth() const
{
    return m_uiWidth;
}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
efd::UInt32 NiTerrainDeformationBuffer<BufferType>::GetHeight() const
{
    return m_uiHeight;
}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
BufferType& NiTerrainDeformationBuffer<BufferType>::SamplePoint(efd::UInt32 uiX, efd::UInt32 uiY)
{
    EE_ASSERT(uiX < m_uiWidth);
    EE_ASSERT(uiY < m_uiHeight);
    return m_pkBuffer[uiX + uiY * m_uiWidth];
}

//--------------------------------------------------------------------------------------------------
template<class BufferType> inline
bool NiTerrainDeformationBuffer<BufferType>::SetDeformationRegion(
    NiRect<efd::SInt32> kAffectedSectorRange, NiRect<efd::SInt32> kDataRegion, 
    NiRect<efd::Float32> kTerrainSpaceRegion,
    efd::UInt32 uiWidth, efd::UInt32 uiHeight)
{
    EE_ASSERT(kDataRegion.m_left >= 0);
    EE_ASSERT(kDataRegion.m_right >= 0);
    EE_ASSERT(kDataRegion.m_top >= 0);
    EE_ASSERT(kDataRegion.m_bottom >= 0);

    // Make sure that the buffer is large enough
    if (uiWidth * uiHeight >= m_uiAllocatedSize)
    {
        // Insufficient buffer size
        EE_FREE(m_pkBuffer);
        m_pkBuffer = EE_ALLOC(BufferType, uiWidth * uiHeight);
        m_uiAllocatedSize = uiWidth * uiHeight;
    }

    // Assign the configuration
    m_uiWidth = uiWidth;
    m_uiHeight = uiHeight;
    m_kAffectedSectorRange = kAffectedSectorRange;
    m_kDataRegion = kDataRegion;
    m_kTerrainSpaceRegion = kTerrainSpaceRegion;

    // Initialize the buffer to 0's
    memset(GetBuffer(), 0, GetSize());
    
    return true;
}

//--------------------------------------------------------------------------------------------------
