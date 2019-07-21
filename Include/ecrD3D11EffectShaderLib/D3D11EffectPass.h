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

#pragma once
#ifndef EE_D3D11EFFECTPASS_H
#define EE_D3D11EFFECTPASS_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>
#include <ecrD3D11Renderer/D3D11Pass.h>

namespace ecr
{

class D3D11EffectTechnique;
class D3D11EffectPass;

/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectPass is an internal class for managing Gamebryo's Effects11 implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectPass : public D3D11Pass
{
public:
    static D3D11PassPtr Create();

    virtual efd::UInt32 ApplyShaderPrograms(const NiRenderCallContext& renderCallContext);
    virtual efd::UInt32 ApplyShaderConstants(const NiRenderCallContext& renderCallContext);

    // *** begin Emergent internal use only

    inline void SetStateBlockMask(const D3DX11_STATE_BLOCK_MASK* pMask);
    inline const D3DX11_STATE_BLOCK_MASK* GetStateBlockMask() const;

    inline void SetD3D11Pass(ID3DX11EffectPass* pD3D11Pass);
    inline ID3DX11EffectPass* GetD3D11Pass() const;

    efd::Bool AddEffectConstantBufferDesc(
        efd::FixedString& bufferName,
        efd::UInt32 mapIndex, 
        efd::UInt32 shaderTypes);

    // *** end Emergent internal use only

protected:
    D3D11EffectPass();
    virtual ~D3D11EffectPass();

    // Only store pointer to the mask; the struct itself will reside in
    // the D3D11EffectTechnique::EffectPass object.
    const D3DX11_STATE_BLOCK_MASK* m_pStateBlockMask;
    ID3DX11EffectPass* m_pPass;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11EffectPass
/// class.
typedef efd::SmartPointer<D3D11EffectPass> D3D11EffectPassPtr;

/// @endcond

}   // End namespace ecr.

#include <ecrD3D11EffectShaderLib/D3D11EffectPass.inl>

#endif // EE_D3D11EFFECTPASS_H
