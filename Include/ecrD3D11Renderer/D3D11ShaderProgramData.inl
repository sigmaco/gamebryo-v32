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
D3D11ShaderProgramData::D3D11ShaderProgramData() :
    m_shaderConstantBufferDescs(NULL),
    m_shaderResourceNames(NULL),
    m_shaderResourceIndices(NULL),
    m_shaderSamplerNames(NULL),
    m_shaderSamplers(NULL),
    m_shaderUAVNames(NULL),
    m_shaderUAVs(NULL),
    m_shaderConstantBufferCount(0),
    m_shaderConstantBufferAllocatedSize(0),
    m_shaderResourceCount(0),
    m_shaderResourceAllocatedSize(0),
    m_shaderSamplerCount(0),
    m_shaderSamplerAllocatedSize(0),
    m_shaderUAVCount(0),
    m_shaderUAVAllocatedSize(0)
{
    /* */
}

//------------------------------------------------------------------------------------------------
D3D11ShaderProgramData::~D3D11ShaderProgramData()
{
    EE_FREE(m_shaderConstantBufferDescs); 
    EE_DELETE[] m_shaderResourceNames;
    EE_FREE(m_shaderResourceIndices);
    EE_DELETE[] m_shaderSamplerNames;
    EE_FREE(m_shaderSamplers);
    EE_DELETE[] m_shaderUAVNames;
    EE_FREE(m_shaderUAVs);
}

//------------------------------------------------------------------------------------------------
inline D3D11ShaderProgram* D3D11ShaderProgramData::GetShaderProgram() const
{
    return m_spShaderProgram;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgramData::SetShaderProgram(D3D11ShaderProgram* pShaderProgram) 
{ 
    m_spShaderProgram = pShaderProgram; 
}

//------------------------------------------------------------------------------------------------
inline efd::UInt8 D3D11ShaderProgramData::GetShaderConstantBufferCount() const
{
    return m_shaderConstantBufferCount;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt8 D3D11ShaderProgramData::GetShaderConstantBufferAllocatedSize() const
{
    return m_shaderConstantBufferAllocatedSize;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt8 D3D11ShaderProgramData::GetShaderResourceCount() const
{
    return m_shaderResourceCount;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt8 D3D11ShaderProgramData::GetShaderResourceAllocatedSize() const
{
    return m_shaderResourceAllocatedSize;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt8 D3D11ShaderProgramData::GetSamplerCount() const
{
    return m_shaderSamplerCount;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt8 D3D11ShaderProgramData::GetSamplerAllocatedSize() const
{
    return m_shaderSamplerAllocatedSize;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt8 D3D11ShaderProgramData::GetUAVCount() const
{
    return m_shaderUAVCount;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt8 D3D11ShaderProgramData::GetUAVAllocatedSize() const
{
    return m_shaderUAVAllocatedSize;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgramData::SetShaderConstantBufferDesc(
    efd::UInt8 shaderIndex, 
    ConstantBufferDesc* pCBDesc)
{
    // This will assert if the index is too large, 
    // reallocate the array if necessary, and
    // do nothing if the array is already large enough.
    SetShaderConstantBufferAllocatedSize(shaderIndex + 1);

    m_shaderConstantBufferDescs[shaderIndex] = pCBDesc;
    if (m_shaderConstantBufferCount < shaderIndex + 1)
        m_shaderConstantBufferCount = shaderIndex + 1;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11ShaderProgramData::GetShaderConstantBufferDesc(
    efd::UInt8 shaderIndex, 
    ConstantBufferDesc*& pCBDesc) const
{
    if (shaderIndex > m_shaderConstantBufferCount)
        return false;

    pCBDesc = m_shaderConstantBufferDescs[shaderIndex];
    return true;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgramData::SetShaderResourceName(
    efd::UInt8 shaderIndex, 
    efd::FixedString& name)
{
    // This will assert if the index is too large, 
    // reallocate the array if necessary, and
    // do nothing if the array is already large enough.
    SetShaderResourceAllocatedSize(shaderIndex + 1);

    m_shaderResourceNames[shaderIndex] = name;
    if (m_shaderResourceCount < shaderIndex + 1)
        m_shaderResourceCount = shaderIndex + 1;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11ShaderProgramData::GetShaderResourceName(
    efd::UInt8 shaderIndex,
    efd::FixedString& name) const
{
    if (shaderIndex > m_shaderResourceCount)
        return false;

    name = m_shaderResourceNames[shaderIndex];
    return true;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgramData::SetShaderResourceIndex(
    efd::UInt8 shaderIndex, 
    efd::UInt8 shaderResourceSourceIndex)
{
    // This will assert if the index is too large, 
    // reallocate the array if necessary, and
    // do nothing if the array is already large enough.
    SetShaderResourceAllocatedSize(shaderIndex + 1);

    m_shaderResourceIndices[shaderIndex] = shaderResourceSourceIndex;
    if (m_shaderResourceCount < shaderIndex + 1)
        m_shaderResourceCount = shaderIndex + 1;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11ShaderProgramData::GetShaderResourceIndex(
    efd::UInt8 shaderIndex, 
    efd::UInt8& shaderResourceSourceIndex) const
{
    if (shaderIndex > m_shaderResourceCount)
        return false;

    shaderResourceSourceIndex = m_shaderResourceIndices[shaderIndex];
    return true;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgramData::SetSamplerName(
    efd::UInt8 shaderIndex, 
    efd::FixedString& samplerName)
{
    // This will assert if the index is too large, 
    // reallocate the array if necessary, and
    // do nothing if the array is already large enough.
    SetSamplerAllocatedSize(shaderIndex + 1);

    m_shaderSamplerNames[shaderIndex] = samplerName;
    if (m_shaderSamplerCount < shaderIndex + 1)
        m_shaderSamplerCount = shaderIndex + 1;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11ShaderProgramData::GetSamplerName(
    efd::UInt8 shaderIndex,
    efd::FixedString& samplerName) const
{
    if (shaderIndex > m_shaderSamplerCount)
        return false;

    samplerName = m_shaderSamplerNames[shaderIndex];
    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11ShaderProgramData::GetSampler(
    efd::UInt8 shaderIndex, 
    D3D11RenderStateGroup::Sampler*& pSampler) const
{
    pSampler = NULL;
    if (shaderIndex > m_shaderSamplerCount)
        return false;

    pSampler = m_shaderSamplers[shaderIndex];
    return true;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgramData::SetUAVName(
    efd::UInt8 shaderIndex, 
    efd::FixedString& name)
{
    // This will assert if the index is too large, 
    // reallocate the array if necessary, and
    // do nothing if the array is already large enough.
    SetUAVAllocatedSize(shaderIndex + 1);

    m_shaderUAVNames[shaderIndex] = name;
    if (m_shaderUAVCount < shaderIndex + 1)
        m_shaderUAVCount = shaderIndex + 1;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11ShaderProgramData::GetUAVName(
    efd::UInt8 shaderIndex,
    efd::FixedString& name) const
{
    if (shaderIndex > m_shaderUAVCount)
        return false;

    name = m_shaderUAVNames[shaderIndex];
    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11ShaderProgramData::GetUAVSlot(
    efd::UInt8 shaderIndex, 
    UAVSlot*& pUAV) const
{
    pUAV = NULL;
    if (shaderIndex > m_shaderUAVCount)
        return false;

    pUAV = m_shaderUAVs[shaderIndex];
    return true;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
