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
inline NiViewRenderClick* ecr::RenderSurface::GetSceneRenderClick() const
{
    return m_spSceneRenderClick;
}
//--------------------------------------------------------------------------------------------------
inline NiRenderTargetGroup* ecr::RenderSurface::GetRenderTargetGroup()
{
    return m_spRenderStep->GetOutputRenderTargetGroup();
}
//--------------------------------------------------------------------------------------------------
inline NiCamera* ecr::RenderSurface::GetCamera()
{
    return m_spCamera;
}
//--------------------------------------------------------------------------------------------------
inline void ecr::RenderSurface::SetCamera(NiCamera* pCamera)
{
    EE_ASSERT(pCamera);
    m_spCamera = pCamera;
}
//--------------------------------------------------------------------------------------------------
inline efd::WindowRef ecr::RenderSurface::GetWindowRef()
{
    return m_windowRef;
}
//--------------------------------------------------------------------------------------------------
inline NiRenderFrame* ecr::RenderSurface::GetRenderFrame()
{
    return m_spRenderFrame;
}
//--------------------------------------------------------------------------------------------------
inline ecr::RenderContext* ecr::RenderSurface::GetContext()
{
    return m_pRenderContext;
}
//--------------------------------------------------------------------------------------------------
