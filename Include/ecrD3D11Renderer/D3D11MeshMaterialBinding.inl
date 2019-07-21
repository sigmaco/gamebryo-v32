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
inline D3D11_INPUT_ELEMENT_DESC* D3D11MeshMaterialBinding::GetInputElementDescArray() const
{
    return m_elementDescArray;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11MeshMaterialBinding::GetInputElementDescCount() const
{
    return m_elementCount;
}

//------------------------------------------------------------------------------------------------
inline ID3D11InputLayout* D3D11MeshMaterialBinding::GetInputLayout() const
{
    return m_pCurrentInputLayout;
}

//------------------------------------------------------------------------------------------------
inline void D3D11MeshMaterialBinding::ReleaseCachedInputLayouts()
{
    EE_DELETE m_inputLayoutArray;
    m_inputLayoutArray = NULL;
}

//------------------------------------------------------------------------------------------------
inline void D3D11MeshMaterialBinding::ReleaseElementArray()
{
    EE_FREE(m_elementDescArray);
    m_elementDescArray = NULL;
    m_elementCount = 0;
}

//------------------------------------------------------------------------------------------------
inline const NiDataStreamRef* D3D11MeshMaterialBinding::GetIndexStreamRef() const
{
    return m_pIndexStreamRef;
}

//------------------------------------------------------------------------------------------------
inline const efd::UInt16* D3D11MeshMaterialBinding::GetStreamsToSetArray() const
{
    return m_streamsToSetArray;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt16 D3D11MeshMaterialBinding::GetLastValidStream() const
{
    return m_lastValidStream;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
