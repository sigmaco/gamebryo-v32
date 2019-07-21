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
#ifndef EE_D3D11EFFECTPARAMETERDESC_H
#define EE_D3D11EFFECTPARAMETERDESC_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>
#include <efd/FixedString.h>
#include <NiShaderAttributeDesc.h>

namespace ecr
{

class D3D11EffectParameterMatrixDesc;
class D3D11EffectParameterVectorDesc;
class D3D11EffectParameterFloatDesc;
class D3D11EffectParameterBooleanDesc;
class D3D11EffectParameterIntegerDesc;
class D3D11EffectParameterTextureDesc;
class D3D11EffectParameterPredefinedDesc;
class D3D11EffectParameterObjectDesc;
class D3D11EffectParameterArrayDesc;

//------------------------------------------------------------------------------------------------
/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectParameterDesc is an internal class for managing Gamebryo's Effects11 implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParameterDesc : public NiMemObject
{
public:
    static D3D11EffectParameterMatrixDesc* GetMatrixDesc();
    static D3D11EffectParameterVectorDesc* GetVectorDesc();
    static D3D11EffectParameterFloatDesc* GetFloatDesc();
    static D3D11EffectParameterBooleanDesc* GetBooleanDesc();
    static D3D11EffectParameterIntegerDesc* GetIntegerDesc();
    static D3D11EffectParameterTextureDesc* GetTextureDesc();
    static D3D11EffectParameterPredefinedDesc* GetPredefinedDesc();
    static D3D11EffectParameterObjectDesc* GetObjectDesc();
    static D3D11EffectParameterArrayDesc* GetArrayDesc();

    enum ParameterType
    {
        PT_NONE = 0,
        PT_MATRIX,
        PT_VECTOR,
        PT_FLOAT,
        PT_BOOL,
        PT_UINT,
        PT_TEXTURE,
        PT_PREDEFINED,
        PT_OBJECT,
        PT_ARRAY,
        PT_NUMBER_TYPES,
        PT_INVALID
    };

    ParameterType m_paramType;
    efd::UInt32 m_flags;
    efd::Bool m_isGlobal;

    efd::FixedString m_name;
    efd::FixedString m_constantBufferName;
protected:
    static D3D11EffectParameterMatrixDesc ms_matrixDesc;
    static D3D11EffectParameterVectorDesc ms_vectorDesc;
    static D3D11EffectParameterFloatDesc ms_floatDesc;
    static D3D11EffectParameterBooleanDesc ms_booleanDesc;
    static D3D11EffectParameterIntegerDesc ms_integerDesc;
    static D3D11EffectParameterTextureDesc ms_textureDesc;
    static D3D11EffectParameterPredefinedDesc ms_predefinedDesc;
    static D3D11EffectParameterObjectDesc ms_objectDesc;
    static D3D11EffectParameterArrayDesc ms_arrayDesc;
};

//------------------------------------------------------------------------------------------------
/**
    D3D11EffectParameterMatrixDesc is an internal class for managing Gamebryo's Effects11 
    implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParameterMatrixDesc :
    public D3D11EffectParameterDesc
{
public:
    efd::FixedString m_desc;

    efd::Float32 m_initValue[16];
    efd::UInt32 m_numRows;
    efd::UInt32 m_numCols;

    efd::Bool m_isHidden;
};

//------------------------------------------------------------------------------------------------
/**
    D3D11EffectParameterVectorDesc is an internal class for managing Gamebryo's Effects11 
    implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParameterVectorDesc :
    public D3D11EffectParameterDesc
{
public:
    efd::FixedString m_desc;

    enum
    {
        MAX_ROWS = 1,
        MAX_COLUMNS = 4,
        MAX_ENTRIES = MAX_ROWS * MAX_COLUMNS
    };

    enum VectorType
    {
        TYPE_POINT2 = 0,
        TYPE_POINT3,
        TYPE_POINT4,
        TYPE_MAX
    };

    VectorType GetVectorType();

    efd::Float32 m_initValue[MAX_ENTRIES];
    efd::Float32 m_maxValue[MAX_ENTRIES];
    efd::Float32 m_minValue[MAX_ENTRIES];

    efd::UInt32 m_numRows;
    efd::UInt32 m_numCols;
    efd::UInt32 m_numAtomicElements;

    efd::Bool m_isHidden;
    efd::Bool m_isColor;
};

//------------------------------------------------------------------------------------------------
/**
    D3D11EffectParameterArrayDesc is an internal class for managing Gamebryo's Effects11 
    implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParameterArrayDesc :
    public D3D11EffectParameterDesc
{
public:
    efd::FixedString m_desc;

    enum ArrayType
    {
        TYPE_FLOAT = 0,
        TYPE_POINT2,
        TYPE_POINT3,
        TYPE_POINT4,
        TYPE_COLORA,
        TYPE_MAX
    };

    enum
    {
        MAX_ROWS = 256,
        MAX_COLUMNS = 4,
        MAX_ENTRIES = MAX_ROWS * MAX_COLUMNS
    };

    ArrayType GetArrayType();

    efd::Float32 m_initValue[MAX_ENTRIES];
    efd::Float32 m_maxValue[MAX_ENTRIES];
    efd::Float32 m_minValue[MAX_ENTRIES];
    efd::Float32 m_tempValues[MAX_ENTRIES];

    efd::UInt32 m_numRows;
    efd::UInt32 m_numCols;
    efd::UInt32 m_numElements;
    efd::UInt32 GetElementSize();

    efd::Bool m_isHidden;
    efd::Bool m_isColor;

    static efd::Bool ExpandToVector4Array(
        const efd::Float32* pSrcArray,
        XMFLOAT4* pDestArray,
        efd::UInt32 numRows,
        efd::UInt32 numColumns,
        efd::UInt32 numElements);
    static efd::Bool CompactFromVector4Array(
        const XMFLOAT4* pSrcArray,
        efd::Float32* pDestArray,
        efd::UInt32 numRows,
        efd::UInt32 numColumns,
        efd::UInt32 numElements);
};

//------------------------------------------------------------------------------------------------
/**
    D3D11EffectParameterFloatDesc is an internal class for managing Gamebryo's Effects11 
    implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParameterFloatDesc :
    public D3D11EffectParameterDesc
{
public:
    efd::FixedString m_desc;

    efd::Float32 m_initValue;
    efd::Float32 m_maxValue;
    efd::Float32 m_minValue;

    efd::Bool m_isHidden;
};

//------------------------------------------------------------------------------------------------
/**
    D3D11EffectParameterBooleanDesc is an internal class for managing Gamebryo's Effects11 
    implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParameterBooleanDesc :
    public D3D11EffectParameterDesc
{
public:
    efd::FixedString m_desc;

    efd::Bool m_initValue;

    efd::Bool m_isHidden;
};

//------------------------------------------------------------------------------------------------
/**
    D3D11EffectParameterIntegerDesc is an internal class for managing Gamebryo's Effects11 
    implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParameterIntegerDesc :
    public D3D11EffectParameterDesc
{
public:
    efd::FixedString m_desc;

    efd::UInt32 m_initValue;
    efd::UInt32 m_maxValue;
    efd::UInt32 m_minValue;

    efd::Bool m_isHidden;
};

//------------------------------------------------------------------------------------------------
/**
    D3D11EffectParameterTextureDesc is an internal class for managing Gamebryo's Effects11 
    implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParameterTextureDesc :
    public D3D11EffectParameterDesc
{
public:
    efd::FixedString m_desc;

    void* m_pInitValue;

    efd::Bool m_isHidden;

    efd::FixedString m_textureName;

    efd::FixedString m_textureMap;
    efd::UInt32 m_textureIndex;

    efd::UInt32 m_objectType;
    efd::UInt32 m_objectIndex;
};

//------------------------------------------------------------------------------------------------
/**
    D3D11EffectParameterPredefinedDesc is an internal class for managing Gamebryo's Effects11 
    implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParameterPredefinedDesc :
    public D3D11EffectParameterDesc
{
public:
    efd::FixedString m_predefined;
    efd::UInt32 m_mapping;
    efd::UInt32 m_arrayCount;
    efd::UInt32 m_extraData;
};

//------------------------------------------------------------------------------------------------
/**
    D3D11EffectParameterObjectDesc is an internal class for managing Gamebryo's Effects11 
    implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectParameterObjectDesc :
    public D3D11EffectParameterDesc
{
public:
    efd::UInt32 m_mapping;
    efd::UInt32 m_objectIndex;
    NiShaderAttributeDesc::ObjectType m_objectType;
};

//------------------------------------------------------------------------------------------------

/// @endcond

}   // End namespace ecr.

#endif // EE_D3D11EFFECTPARAMETERDESC_H
