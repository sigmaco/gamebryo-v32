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
inline NiD3DShaderProgramCreatorAsm::NiD3DShaderProgramCreatorAsm()
{ /* */ }

//--------------------------------------------------------------------------------------------------
inline NiD3DShaderProgramCreatorAsm::~NiD3DShaderProgramCreatorAsm()
{
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiD3DShaderProgramCreatorAsm::GetShaderCreationFlags()
    const
{
    NiDX9Renderer* pkRenderer = NiDX9Renderer::GetRenderer();
    EE_ASSERT(pkRenderer);
    return pkRenderer->GetShaderCreationFlags("asm");
}

//--------------------------------------------------------------------------------------------------
inline void NiD3DShaderProgramCreatorAsm::SetShaderCreationFlags(
    unsigned int uiFlags)
{
    NiDX9Renderer* pkRenderer = NiDX9Renderer::GetRenderer();
    EE_ASSERT(pkRenderer);
    pkRenderer->SetShaderCreationFlags("asm", uiFlags);
}

//--------------------------------------------------------------------------------------------------
inline void NiD3DShaderProgramCreatorAsm::_SDMInit()
{
    ms_pkCreator = NiNew NiD3DShaderProgramCreatorAsm();

    NiD3DShaderProgramFactory::RegisterShaderCreator("vsh", ms_pkCreator);
    NiD3DShaderProgramFactory::RegisterShaderCreator("psh", ms_pkCreator);
}

//--------------------------------------------------------------------------------------------------
inline void NiD3DShaderProgramCreatorAsm::_SDMShutdown()
{
    Shutdown();
}

//--------------------------------------------------------------------------------------------------
inline NiD3DShaderProgramCreatorAsm*
    NiD3DShaderProgramCreatorAsm::GetInstance()
{
    return ms_pkCreator;
}

//--------------------------------------------------------------------------------------------------
inline void NiD3DShaderProgramCreatorAsm::Shutdown()
{
    if (ms_pkCreator)
        NiD3DShaderProgramFactory::UnregisterShaderCreator(ms_pkCreator);
    NiDelete ms_pkCreator;
    ms_pkCreator = NULL;
}

//--------------------------------------------------------------------------------------------------
