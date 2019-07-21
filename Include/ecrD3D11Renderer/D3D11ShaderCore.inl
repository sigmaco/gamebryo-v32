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
inline efd::Bool D3D11ShaderCore::GetUsesNiRenderState() const
{
    return m_usesGBRenderState;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool D3D11ShaderCore::SetUsesNiRenderState(efd::Bool useGBRenderState)
{
    m_usesGBRenderState = useGBRenderState;
    return true;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderCore::GetBoneParameters(
    efd::Bool& transposeBones,
    efd::UInt32& boneMatrixRegisters, 
    efd::Bool& worldSpaceBones)
{
    transposeBones = m_transposeBones;
    boneMatrixRegisters = m_boneMatrixRegisters;
    worldSpaceBones = m_worldSpaceBones;
}

//------------------------------------------------------------------------------------------------
inline void D3D11ShaderCore::SetBoneParameters(
    efd::Bool transposeBones,
    efd::UInt32 boneMatrixRegisters, 
    efd::Bool worldSpaceBones)
{
    m_transposeBones = transposeBones;
    m_boneMatrixRegisters = boneMatrixRegisters;
    m_worldSpaceBones = worldSpaceBones;
}

//------------------------------------------------------------------------------------------------
inline const UAVSlot* D3D11ShaderCore::GetFirstUAVSlot() const
{
    return m_pUAVSlots;
}

//------------------------------------------------------------------------------------------------
inline const UAVSlot* D3D11ShaderCore::GetNextUAVSlot(const UAVSlot* pUAVSlot) const
{
    return pUAVSlot->m_pNext;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderCore::GetUAVSlotResetCount() const
{
    return m_resetIndexUAVSlots;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 D3D11ShaderCore::GetPassCount() const
{
    return m_passArray.GetSize();
}

//------------------------------------------------------------------------------------------------
inline D3D11Pass* D3D11ShaderCore::GetPass(efd::UInt32 passID)
{
    if (passID < m_passArray.GetSize())
        return m_passArray.GetAt(passID);
    return NULL;
}

//------------------------------------------------------------------------------------------------
inline const efd::FixedString& UAVSlot::GetName() const
{
    return m_name;
}

//------------------------------------------------------------------------------------------------
inline void UAVSlot::SetUnorderedAccessResource(UnorderedAccessResource* pResource)
{
    m_spResource = pResource;
}

//------------------------------------------------------------------------------------------------
inline UnorderedAccessResource* UAVSlot::GetUnorderedAccessResource() const
{
    return m_spResource;
}

//------------------------------------------------------------------------------------------------

}   // End namespace ecr.
