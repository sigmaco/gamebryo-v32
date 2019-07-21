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
inline void UnorderedAccessResource::SetUAVFlags(efd::UInt32 uavFlags)
{
    m_uavFlags = uavFlags;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 UnorderedAccessResource::GetUAVFlags() const
{
    return m_uavFlags;
}

//------------------------------------------------------------------------------------------------
inline void UnorderedAccessResource::SetResourceAsNiDataStream(NiDataStream* pDataStream)
{
    ReleaseResourceAndUAV();

    m_spDataStream = pDataStream;
    m_spTexture = NULL;

    UpdateUnorderedAccessView();
}

//------------------------------------------------------------------------------------------------
inline void UnorderedAccessResource::SetResourceAsNiTexture(NiTexture* pTexture)
{
    ReleaseResourceAndUAV();

    m_spDataStream = NULL;
    m_spTexture = pTexture;

    UpdateUnorderedAccessView();
}

//------------------------------------------------------------------------------------------------
inline void UnorderedAccessResource::SetResourceAsD3D11Resource(
    ID3D11Resource* pResource, 
    ID3D11UnorderedAccessView* pUAV)
{
    m_spDataStream = NULL;
    m_spTexture = NULL;

    SetResourceAndUAV(pResource, pUAV);
}

//------------------------------------------------------------------------------------------------
inline ID3D11Resource* UnorderedAccessResource::GetD3D11Resource() const
{
    return m_pResource;
}

//------------------------------------------------------------------------------------------------
inline ID3D11UnorderedAccessView* UnorderedAccessResource::GetUnorderedAccessView() const
{
    return m_pUAV;
}

//------------------------------------------------------------------------------------------------
inline void UnorderedAccessResource::ReleaseResourceAndUAV()
{
    if (m_pResource)
    {
        m_pResource->Release();
        m_pResource = NULL;
    }

    if (m_pUAV)
    {
        m_pUAV->Release();
        m_pUAV = NULL;
    }
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
