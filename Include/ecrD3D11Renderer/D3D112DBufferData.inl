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
inline D3D112DBufferData::D3D112DBufferData() :
    m_pTexture(NULL)
{
    /* */
}

//------------------------------------------------------------------------------------------------
inline ID3D11RenderTargetView* D3D11RenderTargetBufferData::GetRenderTargetView()
    const
{
    return m_pRenderTargetView;
}

//------------------------------------------------------------------------------------------------
inline ID3D11Texture2D* D3D11RenderTargetBufferData::GetRenderTargetBuffer() const
{
    return m_pTexture;
}

//------------------------------------------------------------------------------------------------
inline D3D11SwapChainBufferData::D3D11SwapChainBufferData() :
    m_pSwapChain(NULL)
{
    /* */
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
