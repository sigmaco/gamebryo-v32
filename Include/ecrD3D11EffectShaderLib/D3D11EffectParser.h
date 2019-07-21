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
#ifndef EE_D3D11EFFECTPARSER_H
#define EE_D3D11EFFECTPARSER_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>
#include <NiMemObject.h>
#include <NiShaderConstantMap.h>
#include <NiTPtrSet.h>

namespace ecr
{

class D3D11EffectParameterDesc;
class D3D11EffectParameterMatrixDesc;
class D3D11EffectParameterVectorDesc;
class D3D11EffectParameterFloatDesc;
class D3D11EffectParameterBooleanDesc;
class D3D11EffectParameterIntegerDesc;
class D3D11EffectParameterTextureDesc;
class D3D11EffectParameterPredefinedDesc;
class D3D11EffectTechniqueDesc;
class D3D11EffectParameterArrayDesc;

/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectParser is an internal class for managing Gamebryo's Effects11 implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParser : public NiMemObject
{
public:
    static D3D11EffectParameterDesc* GetParameter(
        ID3DX11Effect* pEffect,
        efd::UInt32 index);
    static efd::Bool GetTechnique(
        D3D11EffectTechniqueDesc& descriptorOut,
        ID3DX11Effect* pEffect,
        efd::UInt32 index);

    static D3D11EffectParameterDesc* GetParameterDesc(
        ID3DX11EffectVariable* pVariable);

    static void GetTechniqueDesc(
        D3D11EffectTechniqueDesc& descriptorOut,
        ID3DX11EffectTechnique* pTechnique);

    static bool IsParameterUsed(
        ID3DX11Effect* pEffect,
        const efd::Char* pParamName,
        const efd::Char* pTechName);

    static void ResetIndices();

    // *** begin Emergent internal use only ***
    static void _SDMShutdown();
    // *** end Emergent internal use only ***

protected:
    static void ParseMatrixAnnotations(
        ID3DX11EffectVariable* pVariable,
        const D3DX11_EFFECT_VARIABLE_DESC& variableDesc,
        const D3DX11_EFFECT_TYPE_DESC& typeDesc,
        D3D11EffectParameterMatrixDesc* pDesc);
    static void ParseVectorAnnotations(
        ID3DX11EffectVariable* pkVariable,
        const D3DX11_EFFECT_VARIABLE_DESC& variableDesc,
        const D3DX11_EFFECT_TYPE_DESC& typeDesc,
        D3D11EffectParameterVectorDesc* pDesc);
    static void ParseArrayAnnotations(
        ID3DX11EffectVariable* pkVariable,
        const D3DX11_EFFECT_VARIABLE_DESC& variableDesc,
        const D3DX11_EFFECT_TYPE_DESC& typeDesc,
        D3D11EffectParameterArrayDesc* pDesc);
    static void ParseFloatAnnotations(
        ID3DX11EffectVariable* pkVariable,
        const D3DX11_EFFECT_VARIABLE_DESC& variableDesc,
        const D3DX11_EFFECT_TYPE_DESC& typeDesc,
        D3D11EffectParameterFloatDesc* pDesc);
    static void ParseBooleanAnnotations(
        ID3DX11EffectVariable* pkVariable,
        const D3DX11_EFFECT_VARIABLE_DESC& variableDesc,
        const D3DX11_EFFECT_TYPE_DESC& typeDesc,
        D3D11EffectParameterBooleanDesc* pDesc);
    static void ParseIntegerAnnotations(
        ID3DX11EffectVariable* pkVariable,
        const D3DX11_EFFECT_VARIABLE_DESC& variableDesc,
        const D3DX11_EFFECT_TYPE_DESC& typeDesc,
        D3D11EffectParameterIntegerDesc* pDesc);
    static void ParseTextureAnnotations(
        ID3DX11EffectVariable* pkVariable,
        const D3DX11_EFFECT_VARIABLE_DESC& variableDesc,
        const D3DX11_EFFECT_TYPE_DESC& typeDesc,
        D3D11EffectParameterTextureDesc* pDesc);
    static void ParseTextureSemantics(
        const efd::Char* pcSemantic,
        D3D11EffectParameterTextureDesc* pDesc);
    static void ParsePredefinedAnnotations(
        ID3DX11EffectVariable* pkVariable,
        const D3DX11_EFFECT_VARIABLE_DESC& variableDesc,
        const D3DX11_EFFECT_TYPE_DESC& typeDesc,
        D3D11EffectParameterPredefinedDesc* pDesc);

    static void ParseTechniqueAnnotations(
        ID3DX11EffectTechnique* pTechnique,
        const D3DX11_TECHNIQUE_DESC& pTechDesc,
        D3D11EffectTechniqueDesc* pDesc);

    static D3D11EffectParameterDesc* QueryPredefined(
        const efd::Char* pSemantic,
        efd::Bool isColumnMatrix,
        efd::UInt32 arrayElements);

    static D3D11EffectParameterDesc* QueryObject(
        ID3DX11EffectVariable* pVariable,
        const D3DX11_EFFECT_VARIABLE_DESC& variableDesc,
        const efd::Char* pSemantic);
    static const efd::Char* LookupObjectAnnotation(
        ID3DX11EffectVariable* pVariable,
        const D3DX11_EFFECT_VARIABLE_DESC& variableDesc,
        const efd::Char* pAnnotation);
    static efd::UInt32 DetermineObjectType(
        const efd::Char* pObjectValue,
        efd::UInt32& objectIndex,
        bool foundObjectIndex);
    static bool VerifyAndAdjustMapping(
        ID3DX11EffectVariable* pVariable,
        const D3DX11_EFFECT_VARIABLE_DESC& variableDesc,
        efd::UInt32 objectType,
        efd::UInt32& mapping);

    static efd::UInt32 ms_shaderMapIndex;
    static efd::UInt32 ms_generalLightIndex;
    static efd::UInt32 ms_pointLightIndex;
    static efd::UInt32 ms_directionalLightIndex;
    static efd::UInt32 ms_spotLightIndex;
    static efd::UInt32 ms_shadowPointLightIndex;
    static efd::UInt32 ms_shadowDirectionalLightIndex;
    static efd::UInt32 ms_shadowSpotLightIndex;
    static efd::UInt32 ms_projShadowIndex;
    static efd::UInt32 ms_projLightIndex;

    static NiShaderConstantMap::PredefinedMapping* ms_pObjectSemantics;
    static const efd::UInt32 ms_numObjectSemantics;
};

/// @endcond

}   // End namespace ecr.

#endif // EE_D3D11EFFECTPARSER_H
