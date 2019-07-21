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
inline ID3D11GeometryShader* D3D11GeometryShader::GetGeometryShader() const
{
    return m_pGeometryShader;
}

//------------------------------------------------------------------------------------------------
inline const D3D11_SO_DECLARATION_ENTRY* D3D11GeometryShader::GetStreamOutputDeclaration() const
{
    return m_pSODeclaration;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11GeometryShader::GetNumStreamOutputEntries() const
{
    return m_numEntries;
}

//------------------------------------------------------------------------------------------------
inline const efd::UInt32* D3D11GeometryShader::GetOutputStreamStrideArray() const
{
    if (m_numOutputStreams == 0)
        return NULL;
    return m_outputStreamStrideArray;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11GeometryShader::GetNumStreamOutputStreams() const
{
    return m_numOutputStreams;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11GeometryShader::GetRasterizedStreamOutputStream() const
{
    return m_rasterizedStream;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
