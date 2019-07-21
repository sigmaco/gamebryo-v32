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
inline NSBUserDefinedDataSet* D3D11BinaryShader::GetShaderUserDefinedDataSet()
{
    return m_spUDDSet_Shader;
}

//------------------------------------------------------------------------------------------------
inline NSBUserDefinedDataSet*
    D3D11BinaryShader::GetImplementationUserDefinedDataSet()
{
    return m_spUDDSet_Implementation;
}

//------------------------------------------------------------------------------------------------
inline NSBUserDefinedDataSet* D3D11BinaryShader::GetPassUserDefinedDataSet(efd::UInt32 passID)
{
    if (passID > m_passCount)
        return 0;

    return m_uddSetArray.GetAt(passID);
}

//------------------------------------------------------------------------------------------------
inline void D3D11BinaryShader::SetUserDefinedDataSet(NSBUserDefinedDataSet* pUDDSet)
{
    m_spUDDSet_Shader = pUDDSet;
}

//------------------------------------------------------------------------------------------------
inline void D3D11BinaryShader::SetImplementationUserDefinedDataSet(NSBUserDefinedDataSet* pUDDSet)
{
    m_spUDDSet_Implementation = pUDDSet;
}

//------------------------------------------------------------------------------------------------
inline void D3D11BinaryShader::SetPassUserDefinedDataSet(
    efd::UInt32 passID, 
    NSBUserDefinedDataSet* pUDDSet)
{
    m_uddSetArray.SetAtGrow(passID, pUDDSet);
}

//------------------------------------------------------------------------------------------------
inline void D3D11BinaryShader::SetRenderStateGroup(
    D3D11RenderStateGroup* pRenderStateGroup)
{
    m_spRenderStateGroup = pRenderStateGroup;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11BinaryShader::InsertPass(efd::UInt32 passID, D3D11Pass* pPass)
{
    // Increment the pass if there was none there previously
    if (m_passArray.GetAllocatedSize() <= passID ||
        m_passArray.GetAt(passID) == 0)
    {
        m_passCount++;
    }

    m_passArray.SetAtGrow(passID, pPass);

    m_uddSetArray.SetSize(m_passCount);

    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11BinaryShader::GetBonesPerPartition() const
{
    return m_bonesPerPartition;
}

//------------------------------------------------------------------------------------------------
inline void D3D11BinaryShader::SetBonesPerPartition(efd::UInt32 boneCount)
{
    m_bonesPerPartition = boneCount;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11BinaryShader::GetBoneMatrixRegisters() const
{
    return m_boneMatrixRegisters;
}

//------------------------------------------------------------------------------------------------
inline void D3D11BinaryShader::SetBoneMatrixRegisters(efd::UInt32 registerCount)
{
    m_boneMatrixRegisters = registerCount;
}

//------------------------------------------------------------------------------------------------
inline D3D11BinaryShader::BoneMatrixCalcMethod D3D11BinaryShader::GetBoneCalcMethod() const
{
    return m_boneCalcMethod;
}

//------------------------------------------------------------------------------------------------
inline void D3D11BinaryShader::SetBoneCalcMethod(D3D11BinaryShader::BoneMatrixCalcMethod method)
{
    m_boneCalcMethod = method;
}

//------------------------------------------------------------------------------------------------
inline NiShaderRequirementDesc::NBTFlags D3D11BinaryShader::GetBinormalTangentMethod() const
{
    return m_nbtMethod;
}

//------------------------------------------------------------------------------------------------
inline void D3D11BinaryShader::SetBinormalTangentMethod(NiShaderRequirementDesc::NBTFlags nbtMethod)
{
    m_nbtMethod = nbtMethod;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11BinaryShader::GetBinormalTangentUVSource()
    const
{
    return m_nbtUVSource;
}

//------------------------------------------------------------------------------------------------
inline void D3D11BinaryShader::SetBinormalTangentUVSource(efd::UInt32 nbtUVSource)
{
    m_nbtUVSource = nbtUVSource;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
