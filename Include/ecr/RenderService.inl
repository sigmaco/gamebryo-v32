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

//------------------------------------------------------------------------------------------------
inline NiRenderer* ecr::RenderService::GetRenderer() const
{
    return m_spRenderer;
}

//------------------------------------------------------------------------------------------------
void ecr::RenderService::SetParentHandle(NiWindowRef parentHandle)
{
    m_parentHandle = parentHandle;
}

//------------------------------------------------------------------------------------------------
NiWindowRef ecr::RenderService::GetParentHandle()
{
    return m_parentHandle;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ecr::RenderService::AddRenderContext(RenderContext* pContext)
{
    m_renderContexts.push_back(pContext);
    return static_cast<efd::UInt32>(m_renderContexts.size()) - 1;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool ecr::RenderService::RemoveRenderContext(RenderContext* pContext)
{
    efd::UInt32 size = static_cast<efd::UInt32>(m_renderContexts.size());
    for (efd::UInt32 ui = 0; ui < size; ui++)
    {
        if (m_renderContexts[ui] == pContext)
        {
            m_renderContexts[ui] = 0;
            if (ui == size - 1)
            {
                m_renderContexts.pop_back();
            }
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------------------------
inline ecr::RenderContextPtr ecr::RenderService::RemoveRenderContextAt(const efd::UInt32 index)
{
    RenderContextPtr spContext = m_renderContexts[index];
    m_renderContexts[index] = 0;
    if (index == static_cast<efd::UInt32>(m_renderContexts.size()) - 1)
    {
        m_renderContexts.pop_back();
    }
    return spContext;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ecr::RenderService::GetRenderContextCount() const
{
    return (efd::UInt32)m_renderContexts.size();
}

//------------------------------------------------------------------------------------------------
inline ecr::RenderContext* ecr::RenderService::GetRenderContextAt(const efd::UInt32 index)
{
    return m_renderContexts[index];
}

//------------------------------------------------------------------------------------------------
inline void ecr::RenderService::SetActiveRenderSurface(RenderSurface* pSurface)
{
    RenderSurface* pOldSurface = m_pActiveSurface;
    m_pActiveSurface = pSurface;

    for (DelegateList::iterator i = m_renderServiceDelegates.begin();
         i != m_renderServiceDelegates.end(); ++i)
    {
        (*i)->OnSurfaceActiveChanged(this, pOldSurface, pSurface);
    }
}

//------------------------------------------------------------------------------------------------
inline ecr::RenderSurface* ecr::RenderService::GetActiveRenderSurface() const
{
    return m_pActiveSurface;
}

//------------------------------------------------------------------------------------------------
inline ecr::RenderContext* ecr::RenderService::GetActiveRenderContext() const
{
    if (m_pActiveSurface)
        return m_pActiveSurface->GetContext();

    return NULL;
}

//------------------------------------------------------------------------------------------------
inline void ecr::RenderService::InvalidateRenderContexts() const
{
    efd::UInt32 size = static_cast<efd::UInt32>(m_renderContexts.size());
    for (efd::UInt32 ui = 0; ui < size; ui++)
    {
        if (m_renderContexts[ui] != NULL)
            m_renderContexts[ui]->Invalidate();
    }
}

//------------------------------------------------------------------------------------------------
inline void ecr::RenderService::AddDelegate(IRenderServiceDelegate* pDelegate)
{
    if (m_renderServiceDelegates.find(pDelegate) == m_renderServiceDelegates.end())
    {
        m_renderServiceDelegates.push_back(pDelegate);
    }
}

//------------------------------------------------------------------------------------------------
inline void ecr::RenderService::RemoveDelegate(IRenderServiceDelegate* pDelegate)
{
    efd::list<IRenderServiceDelegate*>::iterator location =
        m_renderServiceDelegates.find(pDelegate);

    if (location != m_renderServiceDelegates.end())
    {
        m_renderServiceDelegates.erase(location);
    }
}

//------------------------------------------------------------------------------------------------
inline void ecr::RenderService::RaiseSurfaceAdded(ecr::RenderSurface* pSurface)
{
    for (DelegateList::iterator i = m_renderServiceDelegates.begin();
         i != m_renderServiceDelegates.end(); ++i)
    {
        (*i)->OnSurfaceAdded(this, pSurface);
    }
}

//------------------------------------------------------------------------------------------------
inline void ecr::RenderService::RaiseSurfaceRemoved(ecr::RenderSurface* pSurface)
{
    for (DelegateList::iterator i = m_renderServiceDelegates.begin();
         i != m_renderServiceDelegates.end(); ++i)
    {
        (*i)->OnSurfaceRemoved(this, pSurface);
    }
}

//------------------------------------------------------------------------------------------------
inline void ecr::RenderService::RaisePreDrawEvent(ecr::RenderSurface* pSurface)
{
    for (DelegateList::iterator i = m_renderServiceDelegates.begin();
         i != m_renderServiceDelegates.end(); ++i)
    {
        (*i)->OnSurfacePreDraw(this, pSurface);
    }
}

//------------------------------------------------------------------------------------------------
inline void ecr::RenderService::RaisePostDrawEvent(ecr::RenderSurface* pSurface)
{
    for (DelegateList::iterator i = m_renderServiceDelegates.begin();
         i != m_renderServiceDelegates.end(); ++i)
    {
        (*i)->OnSurfacePostDraw(this, pSurface);
    }
}

//------------------------------------------------------------------------------------------------
