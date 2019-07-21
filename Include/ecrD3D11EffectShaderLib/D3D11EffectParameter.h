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
#ifndef EE_D3D11EFFECTPARAMETER_H
#define EE_D3D11EFFECTPARAMETER_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>
#include <ecrD3D11EffectShaderLib/D3D11EffectParameterDesc.h>
#include <efd/FixedString.h>
#include <NiShaderConstantMap.h>

class NiRenderCallContext;
class NiTexturingProperty;

namespace ecr
{

class D3D11EffectAttributeTable;

/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectParameter is an internal class for managing Gamebryo's Effects11 implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParameter : public NiMemObject
{
public:
    D3D11EffectParameter();
    ~D3D11EffectParameter();

    efd::Bool Initialize(
        D3D11EffectParameterDesc* pParamDesc,
        D3D11EffectAttributeTable* pAttribTable);

    NiShaderError SetParameter(const NiRenderCallContext& renderCallContext);

    // *** begin Emergent internal use only ***

    inline const efd::FixedString& GetName() const;
    inline const efd::FixedString& GetConstantBufferName() inline const;


    inline void SetD3D11Parameter(ID3DX11EffectVariable* pParam);
    inline ID3DX11EffectVariable* GetD3D11Parameter() const;

    inline efd::Bool RequiresTime() const;

    void DestroyRendererData();

    inline void SetUsed(efd::Bool isUsed);
    inline efd::Bool GetUsed() const;

    const efd::Char* GetKey() const;
    inline efd::UInt32 GetFlags() const;
    inline efd::UInt32 GetExtra() const;
    inline efd::UInt32 GetDataSize() const;
    inline efd::UInt32 GetDataStride() const;

    inline NiShaderConstantMap::DefinedMappings GetPredefinedMapping() const;
    inline efd::UInt32 GetArrayCount() const;
    inline D3D11EffectParameterDesc::ParameterType GetType() const;

    // *** end Emergent internal use only ***

protected:
    ID3D11ShaderResourceView* GetNiTexture(
        NiTexturingProperty* pTexProp,
        efd::UInt32 textureFlags);

    ID3DX11EffectVariable* m_pParam;
    ID3DX11EffectShaderResourceVariable* m_pEffectSRV;
    ID3D11ShaderResourceView* m_pTextureDataRV;
	NiTexture* m_pTexture;

    efd::FixedString m_name;
    efd::FixedString m_constantBufferName;
    efd::Bool m_isGlobal;

    efd::FixedString m_predefined;
    NiShaderConstantMap::DefinedMappings m_predefinedMapping;
    NiShaderConstantMap::ObjectMappings m_objectMapping;
    D3D11EffectParameterDesc::ParameterType m_parameterType;
    efd::UInt32 m_parameterCount;
    efd::UInt32 m_arrayCount;

    efd::UInt32 m_flags;
    efd::UInt32 m_extraData;
    efd::UInt32 m_dataSize;
    efd::UInt32 m_dataStride;

    // Texture-specific variables
    efd::FixedString m_textureSource;
    efd::UInt32 m_textureFlags;

    // Object-specific variables.
    NiShaderAttributeDesc::ObjectType m_objectType;

    efd::Bool m_isUsed;
};

/// @endcond

}   // End namespace ecr.

#include <ecrD3D11EffectShaderLib/D3D11EffectParameter.inl>

#endif // EE_D3D11EFFECTPASS_H
