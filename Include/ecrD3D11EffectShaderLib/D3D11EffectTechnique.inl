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
inline efd::FixedString D3D11EffectTechnique::GetShaderName() const
{
    return efd::FixedString(m_pReqDesc->GetName());
}

//------------------------------------------------------------------------------------------------
inline efd::FixedString D3D11EffectTechnique::GetDescription() const
{
    return efd::FixedString(m_pReqDesc->GetDescription());
}

//------------------------------------------------------------------------------------------------
inline efd::FixedString D3D11EffectTechnique::GetTechniqueName() const
{
    if (m_techniqueName)
        return m_techniqueName;
    else
        return efd::FixedString(m_pReqDesc->GetName());
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11EffectTechnique::GetImplementation() const
{
    return m_implementation;
}

//------------------------------------------------------------------------------------------------
inline D3D11EffectFile* D3D11EffectTechnique::GetFile() const
{
    return m_pFile;
}

//------------------------------------------------------------------------------------------------
inline void D3D11EffectTechnique::SetFile(D3D11EffectFile* pFile)
{
    m_pFile = pFile;
}

//------------------------------------------------------------------------------------------------
inline bool D3D11EffectTechnique::GetTimeParameterPresent() const
{
    return m_hasTimeParameter;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
