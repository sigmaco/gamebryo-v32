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
inline NiShadowClickGenerator::NiShadowClickGenerator(
    const NiFixedString& kName) : m_kName(kName)
{
    EE_ASSERT(m_kName.Exists());
}

//--------------------------------------------------------------------------------------------------
inline const NiFixedString& NiShadowClickGenerator::GetName() const
{
    return m_kName;
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowClickGenerator::AddRenderClick(
    NiRenderClick* pkRenderClick)
{
    NiShadowManager::AppendRenderClick(pkRenderClick);
}

//--------------------------------------------------------------------------------------------------
