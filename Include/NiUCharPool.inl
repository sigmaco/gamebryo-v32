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
inline NiUCharPool::NiUCharPool(NiUInt32 uiSize, NiUInt32 uiGrowby) :
    m_uiMaxSize(0),
    m_uiCurrentSize(0),
    m_uiGrowBy(1),
    m_pucPool(0)
{
    SetGrowBy(uiGrowby);
    SetSize(uiSize);
    Reset();
}

//--------------------------------------------------------------------------------------------------
inline NiUCharPool::~NiUCharPool()
{
    NiFree(m_pucPool);
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiUCharPool::GetSize() const
{
    return m_uiCurrentSize;
}

//--------------------------------------------------------------------------------------------------
inline void NiUCharPool::SetSize(NiUInt32 uiSize)
{
    m_pucPool = (NiUInt8*)NiRealloc(m_pucPool, uiSize);

    m_uiMaxSize = uiSize;
    if (m_uiCurrentSize > m_uiMaxSize)
    {
        m_uiCurrentSize = m_uiMaxSize;
    }
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiUCharPool::GetGrowBy() const
{
    return m_uiCurrentSize;
}

//--------------------------------------------------------------------------------------------------
inline void NiUCharPool::SetGrowBy(NiUInt32 uiGrowBy)
{
    if (uiGrowBy == 0)
    {
        uiGrowBy = 1;
    }
    m_uiGrowBy = uiGrowBy;
}

//--------------------------------------------------------------------------------------------------
inline void NiUCharPool::Reset()
{
    m_kCriticalSection.Lock();
    memset(m_pucPool, 0, m_uiCurrentSize);
    m_kCriticalSection.Unlock();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiUCharPool::GetNew()
{
    m_kCriticalSection.Lock();
    if (m_uiCurrentSize == m_uiMaxSize)
    {
        SetSize(m_uiMaxSize + m_uiGrowBy);
    }

    NiUInt32 uiOldSize = m_uiCurrentSize++;
    m_kCriticalSection.Unlock();
    return uiOldSize;
}

//--------------------------------------------------------------------------------------------------
inline void NiUCharPool::ReleaseValue()
{
    m_kCriticalSection.Lock();
    m_uiCurrentSize--;
    m_kCriticalSection.Unlock();
}
//---------------------------------------------------------------------------
inline NiUInt8 NiUCharPool::GetValue(NiUInt32 uiIndex) const
{
    m_kCriticalSection.Lock();
    EE_ASSERT(uiIndex < m_uiCurrentSize);
    NiUInt8 ucResult = m_pucPool[uiIndex];
    m_kCriticalSection.Unlock();
    return ucResult;
}

//--------------------------------------------------------------------------------------------------
inline void NiUCharPool::CombineValue(NiUInt32 uiIndex,
    NiUInt8 ucValue)
{
    m_kCriticalSection.Lock();
    EE_ASSERT(uiIndex < m_uiCurrentSize);
    m_pucPool[uiIndex] |= ucValue;
    m_kCriticalSection.Unlock();
}

//--------------------------------------------------------------------------------------------------
inline void NiUCharPool::SetValue(NiUInt32 uiIndex, NiUInt8 ucValue)
{
    m_kCriticalSection.Lock();
    EE_ASSERT(uiIndex < m_uiCurrentSize);
    m_pucPool[uiIndex] = ucValue;
    m_kCriticalSection.Unlock();
}
