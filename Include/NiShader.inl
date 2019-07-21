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
inline unsigned int NiShader::GetOutputStreamCount() const
{
    return m_kOutputStreamDescriptors.GetSize();
}

//--------------------------------------------------------------------------------------------------
inline NiOutputStreamDescriptor& NiShader::GetOutputStreamDescriptor(
    unsigned int uiIndex) const
{
    return m_kOutputStreamDescriptors[uiIndex];
}

//--------------------------------------------------------------------------------------------------
inline void NiShader::SetOutputStreamDescriptors(
    const NiOutputStreamDescriptorArray& kDescriptors)
{
    m_kOutputStreamDescriptors.RemoveAll();
    unsigned int uiCount = kDescriptors.GetSize();
    for (unsigned int i = 0; i < uiCount; i++)
        m_kOutputStreamDescriptors.Add(kDescriptors[i]);
}

//--------------------------------------------------------------------------------------------------
