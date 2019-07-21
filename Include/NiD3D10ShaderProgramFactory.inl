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
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
inline void NiD3D10ShaderProgramFactory::RemoveVertexShaderFromMap(
    NiFixedString& kShaderName)
{
    m_kVertexShaderMap.RemoveAt(kShaderName);
}

//--------------------------------------------------------------------------------------------------
inline void NiD3D10ShaderProgramFactory::RemoveGeometryShaderFromMap(
    NiFixedString& kShaderName)
{
    m_kGeometryShaderMap.RemoveAt(kShaderName);
}

//--------------------------------------------------------------------------------------------------
inline void NiD3D10ShaderProgramFactory::RemovePixelShaderFromMap(
    NiFixedString& kShaderName)
{
    m_kPixelShaderMap.RemoveAt(kShaderName);
}