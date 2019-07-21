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

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11EffectFactory::GetD3D11EffectHLSLFlags()
{
    NiRenderer* pRenderer = NiRenderer::GetRenderer();
    EE_ASSERT(pRenderer);
    return pRenderer->GetShaderCreationFlags(ms_pDefaultExtension);
}

//------------------------------------------------------------------------------------------------
inline void D3D11EffectFactory::SetD3D11EffectHLSLFlags(efd::UInt32 uiHLSLFlags)
{
    NiRenderer* pRenderer = NiRenderer::GetRenderer();
    EE_ASSERT(pRenderer);
    pRenderer->SetShaderCreationFlags(ms_pDefaultExtension, uiHLSLFlags);
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11EffectFactory::GetD3D11EffectFXFlags()
{
    return ms_fxFlags;
}

//------------------------------------------------------------------------------------------------
inline void D3D11EffectFactory::SetD3D11EffectFXFlags(efd::UInt32 fxFlags)
{
    ms_fxFlags = fxFlags;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11EffectFactory::GetFXLSupport()
{
    return ms_fxlSupport;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
