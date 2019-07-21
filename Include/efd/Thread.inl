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
// Thread inline functions
//--------------------------------------------------------------------------------------------------

#include "efd/StringUtilities.h"

namespace efd
{
//--------------------------------------------------------------------------------------------------
inline ThreadFunctor* Thread::GetProcedure() const
{
    return m_pProcedure;
}
//--------------------------------------------------------------------------------------------------
inline void Thread::SetStackSize(efd::UInt32 stackSize)
{
    if (stackSize == USEDEF_STACK_SIZE)
        m_stackSize = DEFAULT_STACK_SIZE;
    else
        m_stackSize = stackSize;
}
//--------------------------------------------------------------------------------------------------
inline void Thread::SetProcedure(ThreadFunctor* pProcedure)
{
    EE_ASSERT(pProcedure);
    m_pProcedure = pProcedure;
}
//--------------------------------------------------------------------------------------------------
inline Thread::Priority Thread::GetPriority() const
{
    return m_priority;
}
//--------------------------------------------------------------------------------------------------
inline bool Thread::SetThreadAffinity(const ProcessorAffinity& affinity)
{
    if (SystemSetAffinity(affinity))
    {
        m_affinity.SetAffinityMask(affinity.GetAffinityMask());
        m_affinity.SetIdealProcessor(affinity.GetIdealProcessor());
        return true;
    }
    else
    {
        return false;
    }
}
//--------------------------------------------------------------------------------------------------
inline const ProcessorAffinity Thread::GetThreadAffinity()
{
    return ProcessorAffinity(m_affinity.GetIdealProcessor(),
        m_affinity.GetAffinityMask());
}
//--------------------------------------------------------------------------------------------------
inline Thread::Status Thread::GetStatus() const
{
    return m_status;
}
//--------------------------------------------------------------------------------------------------
inline efd::UInt32 Thread::GetReturnValue() const
{
    return m_returnValue;
}
//--------------------------------------------------------------------------------------------------
inline void Thread::SetName(const efd::Char* pName)
{
    EE_FREE(m_pName);

    if (pName && pName[0] != '\0')
    {
        efd::UInt32 strLength = (efd::UInt32)strlen(pName);
        m_pName = EE_ALLOC(efd::Char, strLength + 1);
        EE_ASSERT(m_pName);
        efd::Strcpy(m_pName, strLength + 1, pName);
    }
}
//--------------------------------------------------------------------------------------------------
inline const efd::Char* Thread::GetName() const
{
    return m_pName;
}
//--------------------------------------------------------------------------------------------------
} // namespace efd
