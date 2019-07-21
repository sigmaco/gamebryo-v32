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
inline efd::UInt32 ecr::RenderContext::GetRenderSurfaceCount() const
{
    return static_cast<efd::UInt32>(m_renderSurfaces.size());
}
//--------------------------------------------------------------------------------------------------
inline NiCullingProcess* ecr::RenderContext::GetCullingProcess()
{
    return m_spCuller;
}
//--------------------------------------------------------------------------------------------------
inline efd::Bool ecr::RenderContext::GetValidateFrames()
{
    return m_validate;
}
//--------------------------------------------------------------------------------------------------
inline void ecr::RenderContext::SetValidateFrames(efd::Bool validate)
{
    m_validate = validate;
}
//--------------------------------------------------------------------------------------------------
inline void ecr::RenderContext::Invalidate()
{
    m_invalid = true;
}
//--------------------------------------------------------------------------------------------------
