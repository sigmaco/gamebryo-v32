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
inline NiD3DShaderProgramFactory* NiD3DShaderProgramFactory::Create()
{
    if (!ms_pkFactory)
        ms_pkFactory = NiNew NiD3DShaderProgramFactory();

    return ms_pkFactory;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int
    NiD3DShaderProgramFactory::GetUniversalShaderCreationFlags()
{
    NiDX9Renderer* pkRenderer = NiDX9Renderer::GetRenderer();
    EE_ASSERT(pkRenderer);
    return pkRenderer->GetGlobalShaderCreationFlags();
}

//--------------------------------------------------------------------------------------------------
inline void NiD3DShaderProgramFactory::SetUniversalShaderCreationFlags(
    unsigned int uiFlags)
{
    NiDX9Renderer* pkRenderer = NiDX9Renderer::GetRenderer();
    EE_ASSERT(pkRenderer);
    pkRenderer->SetGlobalShaderCreationFlags(uiFlags);
}

//--------------------------------------------------------------------------------------------------
