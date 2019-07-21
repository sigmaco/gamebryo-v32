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
inline const efd::FixedString& D3D11ShaderProgram::GetName() const
{
    return m_name;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgram::SetName(const efd::FixedString& shaderName)
{
    m_name = shaderName;
}

//------------------------------------------------------------------------------------------------
inline ID3DBlob* D3D11ShaderProgram::GetShaderByteCode() const
{
    return m_pShaderByteCode;
}

//------------------------------------------------------------------------------------------------
inline D3D11ShaderProgramCreator* D3D11ShaderProgram::GetCreator() const
{
    return m_pCreator;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgram::SetCreator(D3D11ShaderProgramCreator* pCreator)
{
    m_pCreator = pCreator;
}

//------------------------------------------------------------------------------------------------
inline ID3D11ShaderReflection* D3D11ShaderProgram::GetShaderReflection() const
{
    return m_pReflection;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgram::ClearShaderReflection()
{
    if (m_pReflection)
        m_pReflection->Release();
    m_pReflection = NULL;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
