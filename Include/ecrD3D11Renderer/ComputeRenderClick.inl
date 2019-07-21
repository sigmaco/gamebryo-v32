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
inline void ComputeRenderClick::AppendShader(NiShader* pShader)
{
    EE_ASSERT(pShader);
    m_shaderList.AddTail(pShader);
}

//------------------------------------------------------------------------------------------------
inline void ComputeRenderClick::PrependShader(NiShader* pShader)
{
    EE_ASSERT(pShader);
    m_shaderList.AddHead(pShader);
}

//------------------------------------------------------------------------------------------------
inline void ComputeRenderClick::RemoveShader(NiShader* pShader)
{
    EE_ASSERT(pShader);
    m_shaderList.Remove(pShader);
}

//------------------------------------------------------------------------------------------------
inline void ComputeRenderClick::RemoveAllShaders()
{
    m_shaderList.RemoveAll();
}

//------------------------------------------------------------------------------------------------
inline NiTPointerList<NiShaderPtr>& ComputeRenderClick::GetShaders()
{
    return m_shaderList;
}

//------------------------------------------------------------------------------------------------
inline const NiTPointerList<NiShaderPtr>& ComputeRenderClick::GetShaders() const
{
    return m_shaderList;
}

//------------------------------------------------------------------------------------------------
inline NiShader* ComputeRenderClick::GetShaderByName(const efd::FixedString& shaderName) const
{
    NiTListIterator iter;
    return GetShaderAndPosByName(shaderName, iter);
}

//------------------------------------------------------------------------------------------------
inline NiTListIterator ComputeRenderClick::GetShaderPosByName(const efd::FixedString& shaderName) const
{
    NiTListIterator iter;
    GetShaderAndPosByName(shaderName, iter);
    return iter;
}

//------------------------------------------------------------------------------------------------
inline NiShader* ComputeRenderClick::GetShaderAndPosByName(
    const efd::FixedString& shaderName, 
    NiTListIterator& iter) const
{
    iter = m_shaderList.GetHeadPos();
    while (iter)
    {
        NiShader* pShader = m_shaderList.Get(iter);
        const efd::FixedString& name = pShader->GetName();
        if (name == shaderName)
        {
            return pShader;
        }
        iter = m_shaderList.GetNextPos(iter);
    }

    return NULL;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.

