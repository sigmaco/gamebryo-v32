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
#ifndef EE_D3D11EFFECTTECHNIQUE_H
#define EE_D3D11EFFECTTECHNIQUE_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>
#include <ecrD3D11EffectShaderLib/D3D11EffectParameterDesc.h>

#include <ecrD3D11Renderer/D3D11Headers.h>
#include <efd/FixedString.h>

#include <NiSemanticAdapterTable.h>
#include <NiShaderRequirementDesc.h>
#include <NiTPointerList.h>

class NiShaderDesc;

namespace ecr
{

class D3D11EffectFile;
class D3D11EffectShader;
class D3D11EffectParameter;
class D3D11EffectTechniqueDesc;
typedef efd::SmartPointer<D3D11EffectShader> D3D11EffectShaderPtr;

/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectTechnique is an internal class for managing Gamebryo's Effects11 implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectTechnique : public NiRefObject
{
public:
    D3D11EffectTechnique();
    ~D3D11EffectTechnique();

    void Initialize(D3D11EffectTechniqueDesc* pTechDesc);

    inline efd::FixedString GetShaderName() const;
    inline efd::FixedString GetDescription() const;
    inline efd::FixedString GetTechniqueName() const;

    inline efd::UInt32 GetImplementation() const;
    inline D3D11EffectFile* GetFile() const;

    // Get the D3D11 shader
    D3D11EffectShader* GetD3D11Shader();
    efd::Bool ReleaseShader();

    efd::Bool IsParameterUsed(D3D11EffectParameter* pParam) const;

    // *** begin Emergent internal use only ***

    // These functions are used during the creation
    inline void SetFile(D3D11EffectFile* pFile);

    void AddParameter(D3D11EffectParameter* pkParam);
    D3D11EffectParameter* GetFirstParameter(NiTListIterator& iter);
    D3D11EffectParameter* GetNextParameter(NiTListIterator& iter);

    D3D11EffectParameter* GetParameter(
        const efd::FixedString& paramName,
        D3D11EffectParameterDesc::ParameterType paramType = D3D11EffectParameterDesc::PT_INVALID);

    inline efd::Bool GetTimeParameterPresent() const;

    NiShaderRequirementDesc* GetRequirements();

    void SetD3D11Technique(ID3DX11EffectTechnique* pTechnique);
    ID3DX11EffectTechnique* GetD3D11Technique() const;

    void SetShaderD3D11Effect(ID3DX11Effect* pEffect);

    void DestroyRendererData();

    // *** end Emergent internal use only ***

protected:
    void FillSemanticAdapterTable();

    class EffectPass : public NiMemObject
    {
    public:
        EffectPass(
            efd::UInt32 constantBufferCount);
        virtual ~EffectPass();

        ID3DX11EffectPass* GetD3D11Pass() const;
        void SetD3D11Pass(ID3DX11EffectPass* pPass);

        ID3DBlob* GetInputSignature() const;
        void SetInputSignature(ID3DBlob* pInputSignature);

        const D3DX11_STATE_BLOCK_MASK* GetStateBlockMask() const;
        void SetStateBlockMask(const D3DX11_STATE_BLOCK_MASK& mask);

        efd::UInt32 GetConstantBufferCount() const;

        void SetConstantBufferName(efd::UInt32 index, const efd::FixedString& name);
        const efd::FixedString& GetConstantBufferName(efd::UInt32 index);

        void SetConstantBufferShaderTypes(efd::UInt32 index, const efd::UInt32 shaderTypes);
        const efd::UInt32 GetConstantBufferShaderTypes(efd::UInt32 index);

    protected:
        ID3DX11EffectPass* m_pPass;
        ID3DBlob* m_pInputSignature;
        D3DX11_STATE_BLOCK_MASK m_stateBlockMask;
        NiTObjectArray<efd::FixedString> m_constantBufferNames;
        NiTPrimitiveArray<efd::UInt32> m_constantBufferShaderTypes;
    };

    NiTPrimitiveArray<EffectPass*> m_passArray;

    efd::FixedString m_techniqueName;
    efd::UInt32 m_implementation;

    D3D11EffectFile* m_pFile;

    ID3DX11EffectTechnique* m_pD3D11Technique;

    D3D11EffectShaderPtr m_spShader;

    NiSemanticAdapterTable m_adapterTable;

    NiTPointerList<D3D11EffectParameter*> m_parameters;

    efd::Bool m_hasTimeParameter;
    efd::Bool m_usesNiRenderState;

    NiShaderRequirementDesc* m_pReqDesc;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11EffectTechnique
/// class.
typedef efd::SmartPointer<D3D11EffectTechnique> D3D11EffectTechniquePtr;

/// @endcond

}   // End namespace ecr.

#include <ecrD3D11EffectShaderLib/D3D11EffectTechnique.inl>

#endif // EE_D3D11EFFECTTECHNIQUE_H
