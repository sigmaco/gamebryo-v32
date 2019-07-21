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
inline void D3D11DeviceState::VSGetShader(
    ID3D11VertexShader** pVertexShader,
    ID3D11ClassInstance** pClassInstances,
    efd::UInt32* pNumClassInstances) const
{
    if (pVertexShader)
        *pVertexShader = m_pVertexShader;

    if (pNumClassInstances)
    {
        if (pClassInstances && 
            *pNumClassInstances >= m_classInstanceCount[NiGPUProgram::PROGRAM_VERTEX])
        {
            for (efd::UInt32 i = 0; i < m_classInstanceCount[NiGPUProgram::PROGRAM_VERTEX]; i++)
            {
                pClassInstances[i] = m_classInstanceArray[NiGPUProgram::PROGRAM_VERTEX][i];
            }
        }

        *pNumClassInstances = m_classInstanceCount[NiGPUProgram::PROGRAM_VERTEX];
    }
}

//------------------------------------------------------------------------------------------------
inline void D3D11DeviceState::HSGetShader(
    ID3D11HullShader** pHullShader,
    ID3D11ClassInstance** pClassInstances,
    efd::UInt32* pNumClassInstances) const
{
    if (!m_isHSDSSupported)
    {
        if (pHullShader)
            *pHullShader = NULL;
        if (pClassInstances && pNumClassInstances)
            memset(pClassInstances, 0, *pNumClassInstances * sizeof(*pClassInstances));
        return;
    }

    if (pHullShader)
        *pHullShader = m_pHullShader;

    if (pNumClassInstances)
    {
        if (pClassInstances && 
            *pNumClassInstances >= m_classInstanceCount[NiGPUProgram::PROGRAM_HULL])
        {
            for (efd::UInt32 i = 0; i < m_classInstanceCount[NiGPUProgram::PROGRAM_HULL]; i++)
            {
                pClassInstances[i] = m_classInstanceArray[NiGPUProgram::PROGRAM_HULL][i];
            }
        }

        *pNumClassInstances = m_classInstanceCount[NiGPUProgram::PROGRAM_HULL];
    }
}

//------------------------------------------------------------------------------------------------
inline void D3D11DeviceState::DSGetShader(
    ID3D11DomainShader** pDomainShader,
    ID3D11ClassInstance** pClassInstances,
    efd::UInt32* pNumClassInstances) const
{
    if (!m_isHSDSSupported)
    {
        if (pDomainShader)
            *pDomainShader = NULL;
        if (pClassInstances && pNumClassInstances)
            memset(pClassInstances, 0, *pNumClassInstances * sizeof(*pClassInstances));
        return;
    }

    if (pDomainShader)
        *pDomainShader = m_pDomainShader;

    if (pNumClassInstances)
    {
        if (pClassInstances && 
            *pNumClassInstances >= m_classInstanceCount[NiGPUProgram::PROGRAM_DOMAIN])
        {
            for (efd::UInt32 i = 0; i < m_classInstanceCount[NiGPUProgram::PROGRAM_DOMAIN]; i++)
            {
                pClassInstances[i] = m_classInstanceArray[NiGPUProgram::PROGRAM_DOMAIN][i];
            }
        }

        *pNumClassInstances = m_classInstanceCount[NiGPUProgram::PROGRAM_DOMAIN];
    }
}

//------------------------------------------------------------------------------------------------
inline void D3D11DeviceState::GSGetShader(
    ID3D11GeometryShader** pGeometryShader,
    ID3D11ClassInstance** pClassInstances,
    efd::UInt32* pNumClassInstances) const
{
    if (!m_isGSSupported)
    {
        if (pGeometryShader)
            *pGeometryShader = NULL;
        if (pClassInstances && pNumClassInstances)
            memset(pClassInstances, 0, *pNumClassInstances * sizeof(*pClassInstances));
        return;
    }

    if (pGeometryShader)
        *pGeometryShader = m_pGeometryShader;

    if (pNumClassInstances)
    {
        if (pClassInstances && 
            *pNumClassInstances >= m_classInstanceCount[NiGPUProgram::PROGRAM_GEOMETRY])
        {
            for (efd::UInt32 i = 0; i < m_classInstanceCount[NiGPUProgram::PROGRAM_GEOMETRY]; i++)
            {
                pClassInstances[i] = m_classInstanceArray[NiGPUProgram::PROGRAM_GEOMETRY][i];
            }
        }

        *pNumClassInstances = m_classInstanceCount[NiGPUProgram::PROGRAM_GEOMETRY];
    }
}

//------------------------------------------------------------------------------------------------
inline void D3D11DeviceState::PSGetShader(
    ID3D11PixelShader** pPixelShader,
    ID3D11ClassInstance** pClassInstances,
    efd::UInt32* pNumClassInstances) const
{
    if (pPixelShader)
        *pPixelShader = m_pPixelShader;

    if (pNumClassInstances)
    {
        if (pClassInstances && 
            *pNumClassInstances >= m_classInstanceCount[NiGPUProgram::PROGRAM_PIXEL])
        {
            for (efd::UInt32 i = 0; i < m_classInstanceCount[NiGPUProgram::PROGRAM_PIXEL]; i++)
            {
                pClassInstances[i] = m_classInstanceArray[NiGPUProgram::PROGRAM_PIXEL][i];
            }
        }

        *pNumClassInstances = m_classInstanceCount[NiGPUProgram::PROGRAM_PIXEL];
    }
}

//------------------------------------------------------------------------------------------------
inline void D3D11DeviceState::CSGetShader(
    ID3D11ComputeShader** pComputeShader,
    ID3D11ClassInstance** pClassInstances,
    efd::UInt32* pNumClassInstances) const
{
    if (!m_isCSSupported)
    {
        if (pComputeShader)
            *pComputeShader = NULL;
        if (pClassInstances && pNumClassInstances)
            memset(pClassInstances, 0, *pNumClassInstances * sizeof(*pClassInstances));
        return;
    }

    if (pComputeShader)
        *pComputeShader = m_pComputeShader;

    if (pNumClassInstances)
    {
        if (pClassInstances && 
            *pNumClassInstances >= m_classInstanceCount[NiGPUProgram::PROGRAM_COMPUTE])
        {
            for (efd::UInt32 i = 0; i < m_classInstanceCount[NiGPUProgram::PROGRAM_COMPUTE]; i++)
            {
                pClassInstances[i] = m_classInstanceArray[NiGPUProgram::PROGRAM_COMPUTE][i];
            }
        }

        *pNumClassInstances = m_classInstanceCount[NiGPUProgram::PROGRAM_COMPUTE];
    }
}

//------------------------------------------------------------------------------------------------
inline ID3D11ClassInstance*const* D3D11DeviceState::VSGetShaderClassInstances() const
{
    return m_classInstanceArray[NiGPUProgram::PROGRAM_VERTEX];
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11DeviceState::VSGetShaderClassInstanceCount() const
{
    return m_classInstanceCount[NiGPUProgram::PROGRAM_VERTEX];
}

//------------------------------------------------------------------------------------------------
inline ID3D11ClassInstance*const* D3D11DeviceState::HSGetShaderClassInstances() const
{
    if (!m_isHSDSSupported)
        return NULL;

    return m_classInstanceArray[NiGPUProgram::PROGRAM_HULL];
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11DeviceState::HSGetShaderClassInstanceCount() const
{
    if (!m_isHSDSSupported)
        return 0;

    return m_classInstanceCount[NiGPUProgram::PROGRAM_HULL];
}

//------------------------------------------------------------------------------------------------
inline ID3D11ClassInstance*const* D3D11DeviceState::DSGetShaderClassInstances() const
{
    if (!m_isHSDSSupported)
        return NULL;

    return m_classInstanceArray[NiGPUProgram::PROGRAM_DOMAIN];
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11DeviceState::DSGetShaderClassInstanceCount() const
{
    if (!m_isHSDSSupported)
        return 0;

    return m_classInstanceCount[NiGPUProgram::PROGRAM_DOMAIN];
}

//------------------------------------------------------------------------------------------------
inline ID3D11ClassInstance*const* D3D11DeviceState::GSGetShaderClassInstances() const
{
    if (!m_isGSSupported)
        return NULL;

    return m_classInstanceArray[NiGPUProgram::PROGRAM_GEOMETRY];
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11DeviceState::GSGetShaderClassInstanceCount() const
{
    if (!m_isGSSupported)
        return 0;

    return m_classInstanceCount[NiGPUProgram::PROGRAM_GEOMETRY];
}

//------------------------------------------------------------------------------------------------
inline ID3D11ClassInstance*const* D3D11DeviceState::PSGetShaderClassInstances() const
{
    return m_classInstanceArray[NiGPUProgram::PROGRAM_PIXEL];
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11DeviceState::PSGetShaderClassInstanceCount() const
{
    return m_classInstanceCount[NiGPUProgram::PROGRAM_PIXEL];
}

//------------------------------------------------------------------------------------------------
inline ID3D11ClassInstance*const* D3D11DeviceState::CSGetShaderClassInstances() const
{
    if (!m_isCSSupported)
        return NULL;

    return m_classInstanceArray[NiGPUProgram::PROGRAM_COMPUTE];
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11DeviceState::CSGetShaderClassInstanceCount() const
{
    if (!m_isCSSupported)
        return 0;

    return m_classInstanceCount[NiGPUProgram::PROGRAM_COMPUTE];
}

//------------------------------------------------------------------------------------------------
inline ID3D11VertexShader* D3D11DeviceState::VSGetShader() const
{
    return m_pVertexShader;
}

//------------------------------------------------------------------------------------------------
inline ID3D11HullShader* D3D11DeviceState::HSGetShader() const
{
    if (!m_isHSDSSupported)
        return NULL;

    return m_pHullShader;
}

//------------------------------------------------------------------------------------------------
inline ID3D11DomainShader* D3D11DeviceState::DSGetShader() const
{
    if (!m_isHSDSSupported)
        return NULL;

    return m_pDomainShader;
}

//------------------------------------------------------------------------------------------------
inline ID3D11GeometryShader* D3D11DeviceState::GSGetShader() const
{
    if (!m_isGSSupported)
        return NULL;

    return m_pGeometryShader;
}

//------------------------------------------------------------------------------------------------
inline ID3D11PixelShader* D3D11DeviceState::PSGetShader() const
{
    return m_pPixelShader;
}

//------------------------------------------------------------------------------------------------
inline ID3D11ComputeShader* D3D11DeviceState::CSGetShader() const
{
    if (!m_isCSSupported)
        return NULL;

    return m_pComputeShader;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
