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
#ifndef EE_D3D11EFFECTSHADER_H
#define EE_D3D11EFFECTSHADER_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>
#include <ecrD3D11EffectShaderLib/Effects11Headers.h>
#include <ecrD3D11Renderer/D3D11ShaderCore.h>

namespace ecr
{

class D3D11EffectTechnique;
class D3D11EffectPass;

/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectShader is the D3D11-specific shader that represents an FX shader.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectShader : public ecr::D3D11ShaderCore
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /// Constructor.
    D3D11EffectShader();
    /// Destructor.
    virtual ~D3D11EffectShader();
    //@}

    /// Initialize the shader and ensure the ID3DX11Effect has been loaded.
    virtual efd::Bool Initialize();

    /// Ensure the ID3DX11Effect has been loaded.
    virtual efd::UInt32 PreProcessPipeline(const NiRenderCallContext& renderCallContext);
    /// Set the textures on the effect and fall back to D3D11ShaderCore::SetupShaderPrograms.
    virtual efd::UInt32 SetupShaderPrograms(const NiRenderCallContext& renderCallContext);
    /// Invalidate the device state to ensure Gamebryo's shadow state is accurate.
    virtual efd::UInt32 PostProcessPipeline(const NiRenderCallContext& renderCallContext);

    /// @cond EMERGENT_INTERNAL

    /// Release device resources.
    virtual void DestroyRendererData();
    /// Recreate device resources.
    virtual void RecreateRendererData();

    /// Return the array of semantics the shader expects.
    virtual efd::Bool GetVertexInputSemantics(
        NiShaderDeclaration::ShaderRegisterEntry* pSemantics,
        efd::UInt32 semanticEntryCount);

    /// Return a state block mask indicating which states the effect does not set.
    virtual const D3DX11_STATE_BLOCK_MASK* GetStateBlockMask(
        const NiRenderCallContext& renderCallContext) const;

    /// Store the D3D11EffectTechnique when first initializing the NiShader object.
    void SetEffectTechnique(D3D11EffectTechnique* pD3D11EffectTechnique);

    /// Check for time-based parameters, and adjust the mesh accordingly.
    virtual efd::Bool SetupGeometry(
        NiRenderObject* pGeometry,
        NiMaterialInstance* pMaterialInstance);

    /// Set the implementation number, ignoring the default implementation value. 
    void SetActualImplementation(efd::UInt32 actualImplementation);
    /// Return the implementation number, ignoring the default implementation value. 
    efd::UInt32 GetActualImplementation() const;

    /// Create an array of passes of the expected size.
    void InitializePassArray(efd::UInt32 passCount);
    /// Set the NiSemanticAdapterTable on the shader.
    void SetAdapterSemanticTable(const NiSemanticAdapterTable& adapterTable);
    /// Return a specific pass.
    D3D11EffectPass* GetPass(efd::UInt32 pass) const;

    /// Set the ID3DX11Effect on the shader.
    void SetD3D11Effect(ID3DX11Effect* pEffect);

    /// @endcond

protected:
    ID3DX11Effect* m_pD3D11Effect;

    D3D11EffectTechnique* m_pD3D11EffectTechnique;

    // Actual implementation number in case this shader was created
    // with the "default implementation" value.
    efd::UInt32 m_actualImplementation;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11EffectShader
/// class.
typedef efd::SmartPointer<D3D11EffectShader> D3D11EffectShaderPtr;

/// @endcond

}   // End namespace ecr.

#endif // EE_D3D11EFFECTSHADER_H
