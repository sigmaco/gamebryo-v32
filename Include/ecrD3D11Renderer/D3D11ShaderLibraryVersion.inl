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
inline D3D11ShaderLibraryVersion::D3D11ShaderLibraryVersion() :
    m_systemFeatureLevel(0),
    m_minFeatureLevel(0),
    m_requestedFeatureLevel(0),
    m_systemComputeShaderVersion(0),
    m_minComputeShaderVersion(0),
    m_requestedComputeShaderVersion(0),
    m_systemUserVersion(0),
    m_minUserVersion(0),
    m_requestedUserVersion(0),
    m_platform(0)
{
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetSystemFeatureLevel(efd::UInt32 featureLevel)
{
    m_systemFeatureLevel = featureLevel;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetMinFeatureLevel(efd::UInt32 featureLevel)
{
    m_minFeatureLevel = featureLevel;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetFeatureLevelRequest(efd::UInt32 featureLevel)
{
    m_requestedFeatureLevel = featureLevel;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetSystemComputeShaderVersion(efd::UInt32 version)
{
    m_systemComputeShaderVersion = version;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetMinComputeShaderVersion(efd::UInt32 version)
{
    m_minComputeShaderVersion = version;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetComputeShaderVersionRequest(efd::UInt32 version)
{
    m_requestedComputeShaderVersion = version;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetSystemComputeShaderVersion(
    efd::UInt32 major, 
    efd::UInt32 minor)
{
    m_systemComputeShaderVersion = 
        D3D11ShaderFactory::GetD3D11ShaderFactory()->CreateComputeShaderVersion(major, minor);
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetMinComputeShaderVersion(
    efd::UInt32 major, 
    efd::UInt32 minor)
{
    m_minComputeShaderVersion = 
        D3D11ShaderFactory::GetD3D11ShaderFactory()->CreateComputeShaderVersion(major, minor);
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetComputeShaderVersionRequest(
    efd::UInt32 major, 
    efd::UInt32 minor)
{
    m_requestedComputeShaderVersion = 
        D3D11ShaderFactory::GetD3D11ShaderFactory()->CreateComputeShaderVersion(major, minor);
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetSystemUserVersion(efd::UInt32 version)
{
    m_systemUserVersion = version;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetMinUserVersion(efd::UInt32 version)
{
    m_minUserVersion = version;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetUserVersionRequest(efd::UInt32 version)
{
    m_requestedUserVersion = version;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetSystemUserVersion(efd::UInt32 major, efd::UInt32 minor)
{
    m_systemUserVersion = 
        D3D11ShaderFactory::GetInstance()->CreateVertexShaderVersion(major, minor);
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetMinUserVersion(efd::UInt32 major, efd::UInt32 minor)
{
    m_minUserVersion = 
        D3D11ShaderFactory::GetInstance()->CreateVertexShaderVersion(major, minor);
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetUserVersionRequest(efd::UInt32 major, efd::UInt32 minor)
{
    m_requestedUserVersion = 
        D3D11ShaderFactory::GetInstance()->CreateVertexShaderVersion(major, minor);
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderLibraryVersion::SetPlatform(efd::UInt32 platform)
{
    m_platform = platform;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderLibraryVersion::GetSystemFeatureLevel()
    const
{
    return m_systemFeatureLevel;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderLibraryVersion::GetMinFeatureLevel()
    const
{
    return m_minFeatureLevel;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderLibraryVersion::GetFeatureLevelRequest() const
{
    return m_requestedFeatureLevel;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderLibraryVersion::GetSystemComputeShaderVersion() const
{
    return m_systemComputeShaderVersion;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderLibraryVersion::GetMinComputeShaderVersion() const
{
    return m_minComputeShaderVersion;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderLibraryVersion::GetComputeShaderVersionRequest() const
{
    return m_requestedComputeShaderVersion;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderLibraryVersion::GetSystemUserVersion() const
{
    return m_systemUserVersion;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderLibraryVersion::GetMinUserVersion() const
{
    return m_minUserVersion;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderLibraryVersion::GetUserVersionRequest() const
{
    return m_requestedUserVersion;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderLibraryVersion::GetPlatform() const
{
    return m_platform;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
