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
inline void D3D11EffectPass::SetStateBlockMask(const D3DX11_STATE_BLOCK_MASK* pMask)
{
    m_pStateBlockMask = pMask;
}

//------------------------------------------------------------------------------------------------
inline const D3DX11_STATE_BLOCK_MASK* D3D11EffectPass::GetStateBlockMask() const
{
    return m_pStateBlockMask;
}

//------------------------------------------------------------------------------------------------
inline void D3D11EffectPass::SetD3D11Pass(ID3DX11EffectPass* pD3D11Pass)
{
    EE_ASSERT(pD3D11Pass == NULL || pD3D11Pass->IsValid());
    m_pPass = pD3D11Pass;
}

//------------------------------------------------------------------------------------------------
inline ID3DX11EffectPass* D3D11EffectPass::GetD3D11Pass() const
{
    return m_pPass;
}

//------------------------------------------------------------------------------------------------
}   // End namespace ecr.
