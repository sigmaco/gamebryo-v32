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
inline const efd::FixedString& D3D11EffectTechniqueSet::GetName() const
{
    return m_name;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11EffectTechniqueSet::GetImplementationCount() const
{
    return m_implementations.GetEffectiveSize();
}

//------------------------------------------------------------------------------------------------
inline D3D11EffectTechnique* D3D11EffectTechniqueSet::GetTechnique(efd::UInt32 implementation)
{
    if (implementation < m_implementations.GetSize())
        return m_implementations.GetAt(implementation);
    return NULL;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11EffectTechniqueSet::GetTechniqueArrayCount() const
{
    return m_implementations.GetSize();
}

//------------------------------------------------------------------------------------------------
inline void D3D11EffectTechniqueSet::SetName(const efd::FixedString& name)
{
    m_name = name;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
