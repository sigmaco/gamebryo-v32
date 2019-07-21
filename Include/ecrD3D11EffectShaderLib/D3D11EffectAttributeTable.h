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
#ifndef EE_D3D11EFFECTATTRIBUTETABLE_H
#define EE_D3D11EFFECTATTRIBUTETABLE_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>
#include <efd/FixedString.h>
#include <NiShaderAttributeDesc.h>
#include <NiTPointerList.h>

namespace ecr
{

/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectAttributeTable is an internal class for managing Gamebryo's Effects11 implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectAttributeTable : public NiMemObject
{
public:
    D3D11EffectAttributeTable();
    ~D3D11EffectAttributeTable();

    efd::Bool AddAttribDesc(NiShaderAttributeDesc* pDesc);

    efd::Bool AddAttribDesc_Bool(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        efd::Bool initValue);
    efd::Bool AddAttribDesc_String(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        const efd::Char* pInitValue,
        efd::UInt32 maxLen = 0);
    efd::Bool AddAttribDesc_UnsignedInt(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        efd::UInt32 initValue,
        efd::UInt32 lowValue = 0,
        efd::UInt32 highValue = 0);
    efd::Bool AddAttribDesc_Float(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        efd::Float32 initValue,
        efd::Float32 lowValue = 0.0f,
        efd::Float32 highValue = 0.0f);
    efd::Bool AddAttribDesc_Point2(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        efd::Float32* pInitValue,
        efd::Float32* pLowValue = NULL,
        efd::Float32* pHighValue = NULL);
    efd::Bool AddAttribDesc_Point3(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        efd::Float32* pInitValue,
        efd::Float32* pLowValue = NULL,
        efd::Float32* pHighValue = NULL);
    efd::Bool AddAttribDesc_Point4(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        efd::Float32* pInitValue,
        efd::Float32* pLowValue = NULL,
        efd::Float32* pHighValue = NULL);
    efd::Bool AddAttribDesc_Matrix3(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        efd::Float32* pInitValue);
    efd::Bool AddAttribDesc_Matrix4(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        efd::Float32* pInitValue);
    efd::Bool AddAttribDesc_Color(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        efd::Float32* pInitValue,
        efd::Float32* pLowValue = NULL,
        efd::Float32* pHighValue = NULL);
    efd::Bool AddAttribDesc_ColorA(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        efd::Float32* pInitValue,
        efd::Float32* pLowValue = NULL,
        efd::Float32* pHighValue = NULL);
    efd::Bool AddAttribDesc_Texture(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        efd::UInt32 slot,
        const efd::FixedString& pDefault = NULL,
        const efd::FixedString& pDescription = NULL);
    efd::Bool AddAttribDesc_Array(
        const efd::FixedString& attribName,
        efd::Bool isHidden,
        void* pInitValue,
        efd::UInt32 numElements,
        efd::UInt32 elementSize,
        NiShaderAttributeDesc::AttributeType subType,
        void* pLowValue = NULL,
        void* pHighValue = NULL);

    efd::UInt32 GetAttributeCount() const;

    NiShaderAttributeDesc* GetFirstAttribute(NiTListIterator& iter) const;
    NiShaderAttributeDesc* GetNextAttribute(NiTListIterator& iter) const;
    NiShaderAttributeDesc* GetAttributeByName(const efd::FixedString& pName) const;

protected:
    NiShaderAttributeDesc* CreateAttributeDesc(
        const efd::FixedString& attribName,
        NiShaderAttributeDesc::AttributeType attribType,
        efd::Bool isHidden);

    NiTPointerList<NiShaderAttributeDesc*> m_attribList;
};

/// @endcond

}   // End namespace ecr.

#endif // EE_D3D11EFFECTATTRIBUTETABLE_H
