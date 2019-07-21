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
inline void D3D11EffectFile::SetName(const efd::FixedString& name)
{
    m_name = name;
}

//------------------------------------------------------------------------------------------------
inline const efd::FixedString& D3D11EffectFile::GetName() const
{
    return m_name;
}

//------------------------------------------------------------------------------------------------
inline ID3DX11Effect* D3D11EffectFile::GetEffect() const
{
    return m_pD3D11Effect;
}

//------------------------------------------------------------------------------------------------
inline void* D3D11EffectFile::GetCompiledEffectData() const
{
    if (m_pCompiledEffect)
        return m_pCompiledEffect->GetBufferPointer();

    return NULL;
}

//------------------------------------------------------------------------------------------------
inline NiUInt32 D3D11EffectFile::GetCompiledEffectDataSize() const
{
    if (m_pCompiledEffect)
        return (NiUInt32)m_pCompiledEffect->GetBufferSize();
    
    return 0;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
