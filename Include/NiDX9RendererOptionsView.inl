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
// Constructor / destructor
//--------------------------------------------------------------------------------------------------
inline NiDX9RendererOptionsView::NiDX9RendererOptionsView(
    NiRendererSettings* pkSettings)
{
    m_pkDX9RendererDesc = NiNew NiDX9RendererDesc(pkSettings);
}

//--------------------------------------------------------------------------------------------------
inline NiDX9RendererOptionsView::~NiDX9RendererOptionsView()
{
    NiDelete m_pkDX9RendererDesc;
}

//--------------------------------------------------------------------------------------------------
// Returns pointer to NiDX9RendererDesc instance
//--------------------------------------------------------------------------------------------------
inline NiBaseRendererDesc* NiDX9RendererOptionsView::GetRendDesc()
{
    EE_ASSERT(m_pkDX9RendererDesc);
    return m_pkDX9RendererDesc;
}

//--------------------------------------------------------------------------------------------------
// Returns name of the renderer
//--------------------------------------------------------------------------------------------------
inline char* NiDX9RendererOptionsView::GetName() const
{
    return "Direct3D 9";
}

//--------------------------------------------------------------------------------------------------
// Functions to create dialog and initialize controls in it
//--------------------------------------------------------------------------------------------------
inline NiWindowRef NiDX9RendererOptionsView::InitDialog(NiWindowRef pParentWnd)
{
    if (!m_pkDX9RendererDesc || !m_pkDX9RendererDesc->Initialize())
        return NULL;

    return NiBaseRendererOptionsView::InitDialog(pParentWnd);
}

//--------------------------------------------------------------------------------------------------
inline efd::SystemDesc::RendererID NiDX9RendererOptionsView::GetRendererID() const
{
    return efd::SystemDesc::RENDERER_DX9;
}

//--------------------------------------------------------------------------------------------------
