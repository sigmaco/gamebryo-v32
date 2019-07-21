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


namespace egf
{

//------------------------------------------------------------------------------------------------
inline ScriptContext::ScriptContext()
: m_bImmediateStack(false)
{
}

//------------------------------------------------------------------------------------------------
inline bool ScriptContext::IsImmediateMode() const
{
    return m_bImmediateStack;
}

//------------------------------------------------------------------------------------------------
inline bool ScriptContext::PushBehavior(PendingBehavior* pBehavior)
{
    // The root behavior determines whether the entire stack is running as an immediate behavior:
    if (m_pBehaviorStack->empty())
    {
        m_bImmediateStack = pBehavior->IsImmediate();
    }

    // Only more immediate behaviors can be pushed onto an immediate stack:
    EE_ASSERT(!m_bImmediateStack || pBehavior->IsImmediate());

    m_pBehaviorStack->push(pBehavior);
    return true;
}

//------------------------------------------------------------------------------------------------
inline bool ScriptContext::PopBehavior(PendingBehavior* pBehavior)
{
    EE_ASSERT(!m_pBehaviorStack->empty());
    if (m_pBehaviorStack->top().data() == pBehavior)
    {
        m_pBehaviorStack->pop();
        if (m_pBehaviorStack->empty())
        {
            m_bImmediateStack = false;
        }
        return true;
    }

    EE_FAIL("ScriptContext::m_behaviorStack mismatch!");
    return false;
}

//------------------------------------------------------------------------------------------------
inline PendingBehavior* ScriptContext::GetCurrentBehavior() const
{
    if (EE_VERIFY(!m_pBehaviorStack->empty()))
    {
        PendingBehavior* pResult = m_pBehaviorStack->top().data();
        EE_ASSERT(pResult);
        return pResult;
    }
    return NULL;
}

//-------------------------------------------------------------------------------------------------
inline PendingBehavior* ScriptContext::GetBottomBehavior() const
{
    if (EE_VERIFY(!m_pBehaviorStack->empty()))
    {
        PendingBehavior* pResult = m_pBehaviorStack->_Get_s().front().data();
        EE_ASSERT(pResult);
        return pResult;
    }
    return NULL;
}

//-------------------------------------------------------------------------------------------------
inline bool ScriptContext::ContextIsActive() const
{
    return !m_pBehaviorStack->empty();
}

//------------------------------------------------------------------------------------------------
inline egf::Entity* ScriptContext::GetScriptEntity() const
{
    PendingBehavior* pBehavior = GetCurrentBehavior();
    EE_ASSERT(pBehavior);
    return pBehavior->GetScriptEntity();
}

//------------------------------------------------------------------------------------------------
template< typename T >
T* ScriptContext::GetScriptEntityAs() const
{
    return EE_DYNAMIC_CAST(T, GetScriptEntity());
}

//------------------------------------------------------------------------------------------------
inline const efd::ServiceManager* ScriptContext::GetServiceManager() const
{
    EE_ASSERT(m_spManager);
    return m_spManager;
}

//------------------------------------------------------------------------------------------------
inline void ScriptContext::SetServiceManager(const efd::ServiceManager* pMgr)
{
    EE_ASSERT(NULL == m_spManager || NULL == pMgr);
    m_spManager = pMgr;
}

//------------------------------------------------------------------------------------------------
template< typename T >
T* ScriptContext::GetSystemServiceAs() const
{
    EE_ASSERT(m_spManager);
    return m_spManager->GetSystemServiceAs<T>();
}

//------------------------------------------------------------------------------------------------
inline efd::ParameterList* ScriptContext::GetArgumentList() const
{
    PendingBehavior* pBehavior = GetCurrentBehavior();
    EE_ASSERT(pBehavior);
    return pBehavior->GetArgumentList();
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ScriptContext::GetNonBlocking() const
{
    PendingBehavior* pBehavior = GetCurrentBehavior();
    EE_ASSERT(pBehavior);
    return false == pBehavior->CanBlock();
}

} // end namespace egf

