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

#include <NiSystem.h>

//--------------------------------------------------------------------------------------------------
inline NiRefObject::NiRefObject()
{
    m_uiRefCount = 0;
    efd::AtomicIncrement(ms_uiObjects);
}

//--------------------------------------------------------------------------------------------------
inline NiRefObject::~NiRefObject()
{
    efd::AtomicDecrement(ms_uiObjects);
}

//--------------------------------------------------------------------------------------------------
inline void NiRefObject::IncRefCount()
{
    efd::AtomicIncrement(m_uiRefCount);
}

//--------------------------------------------------------------------------------------------------
inline void NiRefObject::DecRefCount()
{
    if (efd::AtomicDecrement(m_uiRefCount) == 0)
        DeleteThis();
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiRefObject::GetRefCount() const
{
    return m_uiRefCount;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiRefObject::GetTotalObjectCount()
{
    return ms_uiObjects;
}
