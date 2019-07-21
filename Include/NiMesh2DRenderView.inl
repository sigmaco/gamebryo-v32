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
inline NiTPointerList<NiMeshScreenElementsPtr>&
    NiMesh2DRenderView::GetScreenElements()
{
    return m_kScreenElements;
}

//--------------------------------------------------------------------------------------------------
inline void NiMesh2DRenderView::AppendScreenElement(
    NiMeshScreenElements* pkScreenElement)
{
    EE_ASSERT(pkScreenElement);
    m_kScreenElements.AddTail(pkScreenElement);
}

//--------------------------------------------------------------------------------------------------
inline void NiMesh2DRenderView::PrependScreenElement(
    NiMeshScreenElements* pkScreenElement)
{
    EE_ASSERT(pkScreenElement);
    m_kScreenElements.AddHead(pkScreenElement);
}

//--------------------------------------------------------------------------------------------------
inline void NiMesh2DRenderView::RemoveScreenElement(
    NiMeshScreenElements* pkScreenElement)
{
    EE_ASSERT(pkScreenElement);
    m_kScreenElements.Remove(pkScreenElement);
}

//--------------------------------------------------------------------------------------------------
inline void NiMesh2DRenderView::RemoveAllScreenElements()
{
    m_kScreenElements.RemoveAll();
}

//--------------------------------------------------------------------------------------------------
inline const NiTPointerList<NiMeshScreenElementsPtr>&
    NiMesh2DRenderView::GetScreenElements() const
{
    return m_kScreenElements;
}

//--------------------------------------------------------------------------------------------------
