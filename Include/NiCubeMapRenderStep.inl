// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

//---------------------------------------------------------------------------
inline unsigned int NiCubeMapRenderStep::GetCamerasPerUpdate()
{
    return m_uiCamerasPerUpdate;
}

//---------------------------------------------------------------------------
inline void NiCubeMapRenderStep::SetCamerasPerUpdate(unsigned int uiNum)
{
    m_uiCamerasPerUpdate = (uiNum <= 6) ? uiNum : 6;
}

//---------------------------------------------------------------------------
inline void NiCubeMapRenderStep::SetBackgroundColor(const NiColorA& kColor)
{
    m_kBackgroundColor = kColor;
}

//---------------------------------------------------------------------------
inline void NiCubeMapRenderStep::GetBackgroundColor(NiColorA& kColor)
{
    kColor = m_kBackgroundColor;
}

//---------------------------------------------------------------------------
inline void NiCubeMapRenderStep::SetUseRendererBackgroundColor(
    bool bUseRendererBG)
{
    SetBit(bUseRendererBG, USE_RENDERER_BG_COLOR);
}

//---------------------------------------------------------------------------
inline bool NiCubeMapRenderStep::GetUseRendererBackgroundColor()
{
    return GetBit(USE_RENDERER_BG_COLOR);
}

//---------------------------------------------------------------------------
inline void NiCubeMapRenderStep::SetPersistBackgroundColorToRenderer(
    bool bPersist)
{
    SetBit(bPersist, PERSIST_BG_COLOR);
}

//---------------------------------------------------------------------------
inline bool NiCubeMapRenderStep::GetPersistBackgroundColorToRenderer()
{
    return GetBit(PERSIST_BG_COLOR);
}

//---------------------------------------------------------------------------
inline void NiCubeMapRenderStep::SetSwapLeftRight(bool bSwapLeftRight)
{
    SetBit(bSwapLeftRight, SWAP_LEFT_RIGHT);
}

//---------------------------------------------------------------------------
inline bool NiCubeMapRenderStep::GetSwapLeftRight()
{
    return GetBit(SWAP_LEFT_RIGHT);
}

//---------------------------------------------------------------------------
