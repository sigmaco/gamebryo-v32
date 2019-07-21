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
#ifndef EE_D3D11EFFECTTECHNIQUESET_H
#define EE_D3D11EFFECTTECHNIQUESET_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>
#include <ecrD3D11EffectShaderLib/D3D11EffectTechnique.h>

NiSmartPointer(NiShaderDesc);

namespace ecr
{

class D3D11EffectAttributeTable;
class D3D11EffectShader;

/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectTechniqueSet is an internal class for managing Gamebryo's Effects11 implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectTechniqueSet : public NiRefObject
{
public:
    D3D11EffectTechniqueSet();
    ~D3D11EffectTechniqueSet();

    inline const efd::FixedString& GetName() const;
    inline efd::UInt32 GetImplementationCount() const;

    // Get the D3D11 shader
    D3D11EffectShader* GetD3D11Shader(efd::UInt32 implementation);
    D3D11EffectShader* GetBestD3D11Shader();

    // *** begin Emergent internal use only ***
    NiShaderDesc* GetShaderDesc(const D3D11EffectAttributeTable* pAttribTable);
    inline D3D11EffectTechnique* GetTechnique(efd::UInt32 implementation);
    inline efd::UInt32 GetTechniqueArrayCount() const;

    void AddImplementation(D3D11EffectTechnique* pTechnique);

    void DestroyRendererData();

    // These functions are used during the creation
    inline void SetName(const efd::FixedString& name);

    // *** end Emergent internal use only ***

protected:
    efd::FixedString m_name;

    NiTObjectArray<D3D11EffectTechniquePtr> m_implementations;
    D3D11EffectTechnique* m_pBestImplementation;

    NiShaderDescPtr m_spShaderDesc;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the 
/// D3D11EffectTechniqueSet class.
typedef efd::SmartPointer<D3D11EffectTechniqueSet> D3D11EffectTechniqueSetPtr;

/// @endcond

}   // End namespace ecr.

#include <ecrD3D11EffectShaderLib/D3D11EffectTechniqueSet.inl>

#endif // EE_D3D11EFFECTTECHNIQUESET_H
