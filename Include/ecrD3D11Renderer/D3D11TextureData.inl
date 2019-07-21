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
inline efd::Bool D3D11TextureData::IsRenderedTexture() const
{
    return (m_resourceType & RESOURCETYPE_RENDERED) != 0;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11TextureData::IsSourceTexture() const
{
    return (m_resourceType & RESOURCETYPE_SOURCE) != 0;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11TextureData::IsDynamicTexture() const
{
    return (m_resourceType & RESOURCETYPE_DYNAMIC) != 0;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11TextureData::IsCubeMap() const
{
    return (m_resourceType & RESOURCETYPE_CUBE) != 0;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11TextureData::IsBuffer() const
{
    return (m_resourceType & RESOURCETYPE_BUFFER) != 0;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11TextureData::IsTexture1D() const
{
    return (m_resourceType & RESOURCETYPE_1D) != 0;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11TextureData::IsTexture2D() const
{
    return (m_resourceType & RESOURCETYPE_2D) != 0;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11TextureData::IsTexture3D() const
{
    return (m_resourceType & RESOURCETYPE_3D) != 0;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11TextureData::GetDepth() const
{
    if (IsTexture3D())
        return m_depthOrArrayCount;
    else
        return 0;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11TextureData::GetArrayCount() const
{
    if (IsTexture1D() || IsTexture2D())
        return m_depthOrArrayCount;
    else
        return 1;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt16 D3D11TextureData::GetLevels() const
{
    return m_levels;
}

//------------------------------------------------------------------------------------------------
inline ID3D11ShaderResourceView* D3D11TextureData::GetResourceView() const
{
    return m_pResourceView;
}

//------------------------------------------------------------------------------------------------
inline ID3D11Resource* D3D11TextureData::GetResource() const
{
    return m_pD3D11Resource;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
