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
inline bool NiComponentStreamInput::GetValue(NiUInt32 uiIndex, float& val)
{
    EE_ASSERT(m_eElementType == NiDataStreamElement::T_FLOAT32);
    return GetTValue<float>(uiIndex, val);
}

//--------------------------------------------------------------------------------------------------
inline bool NiComponentStreamInput::GetValue(NiUInt32 uiIndex, NiUInt32& val)
{
    EE_ASSERT(m_eElementType == NiDataStreamElement::T_UINT32);
    return GetTValue<NiUInt32>(uiIndex, val);
}

//--------------------------------------------------------------------------------------------------
inline bool NiComponentStreamInput::GetValue(NiUInt32 uiIndex, NiUInt16& val)
{
    EE_ASSERT(m_eElementType == NiDataStreamElement::T_UINT16);
    return GetTValue<NiUInt16>(uiIndex, val);
}

//--------------------------------------------------------------------------------------------------
inline bool NiComponentStreamInput::GetValue(NiUInt32 uiIndex, NiUInt8& val)
{
    EE_ASSERT(m_eElementType == NiDataStreamElement::T_UINT8);
    return GetTValue<NiUInt8>(uiIndex, val);
}

//--------------------------------------------------------------------------------------------------
inline bool NiComponentStreamInput::GetValue(NiUInt32 uiIndex, NiInt32& val)
{
    EE_ASSERT(m_eElementType == NiDataStreamElement::T_INT32);
    return GetTValue<NiInt32>(uiIndex, val);
}

//--------------------------------------------------------------------------------------------------
inline bool NiComponentStreamInput::GetValue(NiUInt32 uiIndex, NiInt16& val)
{
    EE_ASSERT(m_eElementType == NiDataStreamElement::T_INT16);
    return GetTValue<NiInt16>(uiIndex, val);
}

//--------------------------------------------------------------------------------------------------
inline bool NiComponentStreamInput::GetValue(NiUInt32 uiIndex, NiInt8& val)
{
    EE_ASSERT(m_eElementType == NiDataStreamElement::T_INT8);
    return GetTValue<NiInt8>(uiIndex, val);
}

//--------------------------------------------------------------------------------------------------
