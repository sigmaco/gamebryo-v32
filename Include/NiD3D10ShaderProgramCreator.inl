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
inline NiD3D10ShaderProgramCreator::NiD3D10ShaderProgramCreator()
{ /* */ }

//--------------------------------------------------------------------------------------------------
inline NiD3D10ShaderProgramCreator::~NiD3D10ShaderProgramCreator()
{ /* */ }

//--------------------------------------------------------------------------------------------------
inline unsigned int
    NiD3D10ShaderProgramCreator::GetUniversalShaderCreationFlags()
{
    NiD3D10Renderer* pkRenderer = NiD3D10Renderer::GetRenderer();
    EE_ASSERT(pkRenderer);
    return pkRenderer->GetGlobalShaderCreationFlags();
}

//--------------------------------------------------------------------------------------------------
inline void NiD3D10ShaderProgramCreator::SetUniversalShaderCreationFlags(
    unsigned int uiFlags)
{
    NiD3D10Renderer* pkRenderer = NiD3D10Renderer::GetRenderer();
    EE_ASSERT(pkRenderer);
    pkRenderer->SetGlobalShaderCreationFlags(uiFlags);
}

//--------------------------------------------------------------------------------------------------
