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

//--------------------------------------------------------------------------------------------------
inline void NiCompositeValidator::AppendValidator(
    NiRenderClickValidator* pkValidator)
{
    EE_ASSERT(pkValidator);
    m_kValidators.AddTail(pkValidator);
}

//--------------------------------------------------------------------------------------------------
inline void NiCompositeValidator::PrependValidator(
    NiRenderClickValidator* pkValidator)
{
    EE_ASSERT(pkValidator);
    m_kValidators.AddHead(pkValidator);
}

//--------------------------------------------------------------------------------------------------
inline void NiCompositeValidator::RemoveValidator(
    NiRenderClickValidator* pkValidator)
{
    EE_ASSERT(pkValidator);
    m_kValidators.Remove(pkValidator);
}

//--------------------------------------------------------------------------------------------------
inline void NiCompositeValidator::RemoveAllValidators()
{
    m_kValidators.RemoveAll();
}

//--------------------------------------------------------------------------------------------------
inline NiTPointerList<NiRenderClickValidatorPtr>&
    NiCompositeValidator::GetValidators()
{
    return m_kValidators;
}

//--------------------------------------------------------------------------------------------------
inline const NiTPointerList<NiRenderClickValidatorPtr>&
    NiCompositeValidator::GetValidators() const
{
    return m_kValidators;
}

//--------------------------------------------------------------------------------------------------
