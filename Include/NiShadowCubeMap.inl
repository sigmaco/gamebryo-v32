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
inline void NiShadowCubeMap::_SDMInit()
{
    ms_kMapName = "ShadowCubeMap";
}

//------------------------------------------------------------------------------------------------
inline void NiShadowCubeMap::_SDMShutdown()
{
    ms_kMapName = NULL;
}

//------------------------------------------------------------------------------------------------
inline const NiFixedString& NiShadowCubeMap::GetMapName()
{
    return ms_kMapName;
}

//------------------------------------------------------------------------------------------------
inline const float* NiShadowCubeMap::GetWorldToShadowMap(unsigned char ucIndex)
    const
{
    NiShadowRenderClick* pkRenderClick = GetRenderClick(ucIndex);
    EE_ASSERT(pkRenderClick);

    EE_ASSERT(pkRenderClick->GetRenderViews().GetSize() > 0);
    EE_ASSERT(NiIsKindOf(Ni3DRenderView,
        pkRenderClick->GetRenderViews().GetHead()));

    Ni3DRenderView* pkShadowView =
        (Ni3DRenderView*)(pkRenderClick->GetRenderViews().GetHead().data());
    EE_ASSERT(pkShadowView->GetCamera());

    return pkShadowView->GetCamera()->GetWorldToCameraMatrix();
}

//------------------------------------------------------------------------------------------------
inline NiRenderedCubeMap* NiShadowCubeMap::GetCubeMapTexture() const
{
    return ((NiRenderedCubeMap*)(m_spTexture.data()));
}

//------------------------------------------------------------------------------------------------
inline unsigned char NiShadowCubeMap::GetNumRenderClicks()
{
    return 6;
}

//------------------------------------------------------------------------------------------------
inline NiShadowRenderClick* NiShadowCubeMap::GetRenderClick(
    unsigned char ucIndex) const
{
    EE_ASSERT(ucIndex < GetNumRenderClicks());

    return m_aspRenderClicks[ucIndex];
}

//------------------------------------------------------------------------------------------------
