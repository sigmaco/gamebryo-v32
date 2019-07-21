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

namespace ecr
{

//--------------------------------------------------------------------------------------------------
inline D3D11RendererOptionsView::D3D11RendererOptionsView(
    NiRendererSettings* pkSettings)
{
    m_pD3D11RendererDesc = EE_NEW D3D11RendererDesc(pkSettings);
}

//--------------------------------------------------------------------------------------------------
inline D3D11RendererOptionsView::~D3D11RendererOptionsView()
{
    EE_DELETE m_pD3D11RendererDesc;
}

//--------------------------------------------------------------------------------------------------
// Returns pointer to D3D11RendererDesc instance
//--------------------------------------------------------------------------------------------------
inline NiBaseRendererDesc* D3D11RendererOptionsView::GetRendDesc()
{
    EE_ASSERT(m_pD3D11RendererDesc);
    return m_pD3D11RendererDesc;
}

//--------------------------------------------------------------------------------------------------
// Returns name of the renderer
//--------------------------------------------------------------------------------------------------
inline efd::Char* D3D11RendererOptionsView::GetName() const
{
    return "Direct3D 11";
}

//--------------------------------------------------------------------------------------------------
// Height adjusting functions for basic / advanced view
//--------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11RendererOptionsView::SetBasicHeight()
{
    ShowWindow(m_pD3D11DlgHandle, SW_HIDE);
    return NiBaseRendererOptionsView::SetBasicHeight();
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11RendererOptionsView::SetAdvancedHeight()
{
    ShowWindow(m_pD3D11DlgHandle, SW_SHOW);
    return NiBaseRendererOptionsView::SetAdvancedHeight();
}

//--------------------------------------------------------------------------------------------------
inline efd::SystemDesc::RendererID D3D11RendererOptionsView::GetRendererID() const
{
    return efd::SystemDesc::RENDERER_D3D11;
}

//--------------------------------------------------------------------------------------------------

}   // End namespace ecr.
