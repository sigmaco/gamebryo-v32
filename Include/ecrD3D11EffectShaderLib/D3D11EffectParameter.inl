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
inline const efd::FixedString& D3D11EffectParameter::GetName() const
{
    return m_name;
}

//------------------------------------------------------------------------------------------------
inline const efd::FixedString& D3D11EffectParameter::GetConstantBufferName() const
{
    return m_constantBufferName;
}

//------------------------------------------------------------------------------------------------
inline void D3D11EffectParameter::SetD3D11Parameter(ID3DX11EffectVariable* pParam)
{
    // if you change the parameter null the saved data fro mthe old param.
    if (m_pParam != pParam)
        DestroyRendererData();
    m_pParam = pParam;
}

//------------------------------------------------------------------------------------------------
inline ID3DX11EffectVariable* D3D11EffectParameter::GetD3D11Parameter() const
{
    return m_pParam;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11EffectParameter::RequiresTime() const
{
    return (m_predefinedMapping == NiShaderConstantMap::SCM_DEF_CONSTS_TIME ||
        m_predefinedMapping == NiShaderConstantMap::SCM_DEF_CONSTS_SINTIME ||
        m_predefinedMapping == NiShaderConstantMap::SCM_DEF_CONSTS_COSTIME ||
        m_predefinedMapping == NiShaderConstantMap::SCM_DEF_CONSTS_TANTIME ||
        m_predefinedMapping == NiShaderConstantMap::SCM_DEF_CONSTS_TIME_SINTIME_COSTIME_TANTIME);
}

//------------------------------------------------------------------------------------------------
inline void D3D11EffectParameter::SetUsed(efd::Bool isUsed)
{
    m_isUsed = isUsed;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11EffectParameter::GetUsed() const
{
    return m_isUsed;
}

//------------------------------------------------------------------------------------------------
inline NiShaderConstantMap::DefinedMappings D3D11EffectParameter::GetPredefinedMapping() const
{
    return m_predefinedMapping;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11EffectParameter::GetArrayCount() const
{
    return m_arrayCount;
}

//------------------------------------------------------------------------------------------------
inline D3D11EffectParameterDesc::ParameterType D3D11EffectParameter::GetType() const
{
    return m_parameterType;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11EffectParameter::GetFlags() const
{
    return m_flags;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11EffectParameter::GetExtra() const
{
    return m_extraData;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11EffectParameter::GetDataSize() const
{
    return m_dataSize;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11EffectParameter::GetDataStride() const
{
    return m_dataStride;
}

}   // End namespace ecr.
