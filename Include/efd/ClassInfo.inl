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

namespace efd
{

//-------------------------------------------------------------------------------------------------
inline ClassInfo::ClassInfo(CLASSINFO_FUNC pClassInfoFunc)
{
    m_ClassCount = 0;

    EE_ASSERT(pClassInfoFunc);

    pClassInfoFunc(this, 0);
}
//-------------------------------------------------------------------------------------------------
inline void* ClassInfo::TypeCast(const ClassID classID, const void* pSrc) const
{
    EE_ASSERT(pSrc != NULL);

    for (efd::UInt32 ui = 0; ui < m_ClassCount; ui++)
    {
        if (m_Classes[ui].m_ID == classID)
        {
            efd::UInt32 offset = m_Classes[ui].m_Offset;
            return (void*)((char*)pSrc + offset);
        }
    }

    return NULL;
}
//-------------------------------------------------------------------------------------------------
inline ClassID ClassInfo::GetClassID() const
{
    return m_Classes[0].m_ID;
}
//-------------------------------------------------------------------------------------------------
inline const char* ClassInfo::GetClassName() const
{
    return m_Classes[0].m_Name;
}
//-------------------------------------------------------------------------------------------------
inline bool ClassInfo::IsKindOf(const ClassInfo* pClassInfo, const ClassID classID)
{
    if (!pClassInfo)
        return false;

    for (efd::UInt32 ui = 0; ui < pClassInfo->m_ClassCount; ui++)
    {
        if (pClassInfo->m_Classes[ui].m_ID == classID)
            return true;
    }

    return false;
}
//-------------------------------------------------------------------------------------------------
inline bool ClassInfo::IsExactKindOf(const ClassInfo* pClassInfo, const ClassID classID)
{
    if (!pClassInfo)
        return false;

    if (pClassInfo->m_Classes[0].m_ID == classID)
        return true;

    return false;
}
//-------------------------------------------------------------------------------------------------
inline void ClassInfo::AddClass(const char* name, ClassID id, efd::UInt32 offset,
    const ClassInfo* parent)
{
    EE_ASSERT(MAX_PARENT_IDS != m_ClassCount);
    if (!IsKindOf(this, id))
    {
        EE_ASSERT(m_ClassCount != MAX_PARENT_IDS);

        m_Classes[m_ClassCount].m_ID = id;
        m_Classes[m_ClassCount].m_Name = name;
        m_Classes[m_ClassCount].m_Offset = offset;
        m_Classes[m_ClassCount].m_ClassInfo = parent;
        m_ClassCount++;
    }
}
//-------------------------------------------------------------------------------------------------

}   // End namespace efd
