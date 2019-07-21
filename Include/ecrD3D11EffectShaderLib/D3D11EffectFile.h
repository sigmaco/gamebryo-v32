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
#ifndef EE_D3D11EFFECTFILE_H
#define EE_D3D11EFFECTFILE_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>
#include <ecrD3D11EffectShaderLib/D3D11EffectAttributeTable.h>
#include <ecrD3D11EffectShaderLib/D3D11EffectTechniqueSet.h>
#include <ecrD3D11Renderer/D3D11Headers.h>
#include <efd/FixedString.h>
#include <NiMemObject.h>
#include <NiTFixedStringMap.h>
#include <NiUniversalTypes.h>

class NiShaderDesc;

namespace ecr
{

class D3D11EffectShader;
class D3D11ShaderConstantMap;
typedef efd::SmartPointer<D3D11ShaderConstantMap> D3D11ShaderConstantMapPtr;

/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectFile is an internal class for managing Gamebryo's Effects11 implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectFile : public NiMemObject
{

public:
    D3D11EffectFile(ID3DBlob* pCompiledEffect);
    ~D3D11EffectFile();

    // Name
    inline const efd::FixedString& GetName() inline const;

    // *** begin Emergent internal use only ***
    inline ID3DX11Effect* GetEffect() const;

    D3D11EffectTechnique* GetFirstTechnique(NiTMapIterator& iter, efd::UInt32& index) const;
    D3D11EffectTechnique* GetNextTechnique(NiTMapIterator& iter, efd::UInt32& index) const;

    D3D11EffectTechniqueSet* GetTechniqueSet(const efd::FixedString& name) const;

    NiShaderDesc* GetFirstShaderDesc(NiTMapIterator& iter) const;
    NiShaderDesc* GetNextShaderDesc(NiTMapIterator& iter) const;

    D3D11ShaderConstantMap* GetShaderConstantMap(const efd::FixedString& name) const;

    inline void SetName(const efd::FixedString& name);

    // Parse the effect - this should only ever be called once.
    efd::Bool ParseEffect(ID3DX11Effect* pEffect);

    inline void* GetCompiledEffectData() const;
    inline efd::UInt32 GetCompiledEffectDataSize() const;

    // Set/release effect and other effect-derived handles
    void SetD3D11Effect(ID3DX11Effect* pkEffect);
    void ReleaseD3D11Effect();

    // Set/release renderer-owned data, including effect-derived handles
    void LinkRendererData();
    void DestroyRendererData();

    // *** end Emergent internal use only ***

protected:

    void CreateShaderConstantMaps(ID3DX11Effect* pEffect);

    void AddTechnique(D3D11EffectTechnique* pTechnique);

    efd::FixedString m_name;

    // Techniques and parameters
    NiTFixedStringMap<D3D11EffectTechniqueSetPtr> m_techniqueSets;
    NiTPointerList<D3D11EffectParameter*> m_parameters;
    efd::UInt32 m_techniqueIndex;

    D3D11EffectAttributeTable m_attribTable;

    // Shader constant maps
    NiTFixedStringMap<D3D11ShaderConstantMapPtr> m_constantMaps;

    ID3DBlob* m_pCompiledEffect;
    ID3DX11Effect* m_pD3D11Effect;

    efd::Bool m_constantBuffersLoaded;
};

/// @endcond

}   // End namespace ecr.

#include <ecrD3D11EffectShaderLib/D3D11EffectFile.inl>

#endif // EE_D3D11EFFECTFILE_H
