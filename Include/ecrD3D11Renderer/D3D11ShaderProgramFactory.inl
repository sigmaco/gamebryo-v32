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
inline void D3D11ShaderProgramFactory::RemoveVertexShaderFromMap(efd::FixedString& shaderName)
{
    NiFixedString temp = shaderName;
    m_vertexShaderMap.RemoveAt(temp);
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgramFactory::RemoveHullShaderFromMap(efd::FixedString& shaderName)
{
    NiFixedString temp = shaderName;
    m_hullShaderMap.RemoveAt(temp);
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgramFactory::RemoveDomainShaderFromMap(efd::FixedString& shaderName)
{
    NiFixedString temp = shaderName;
    m_domainShaderMap.RemoveAt(temp);
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgramFactory::RemoveGeometryShaderFromMap(efd::FixedString& shaderName)
{
    NiFixedString temp = shaderName;
    m_geometryShaderMap.RemoveAt(temp);
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgramFactory::RemovePixelShaderFromMap(efd::FixedString& shaderName)
{
    NiFixedString temp = shaderName;
    m_pixelShaderMap.RemoveAt(temp);
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderProgramFactory::RemoveComputeShaderFromMap(efd::FixedString& shaderName)
{
    NiFixedString temp = shaderName;
    m_computeShaderMap.RemoveAt(temp);
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
