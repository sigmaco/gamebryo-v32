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

namespace efd
{

//------------------------------------------------------------------------------------------------
template<typename T>
const ParameterListMessage& ParameterListMessage::operator >>(T& data) const
{
    m_params.GetParameter(m_nextIndex++, data);
    return *this;
}

//------------------------------------------------------------------------------------------------
template<typename T>
ParameterListMessage& ParameterListMessage::operator <<(const T& data)
{
    m_params.AddParameter(data);
    return *this;
}

//------------------------------------------------------------------------------------------------
inline efd::ParameterList& ParameterListMessage::GetParameters()
{
    return m_params;
}

//------------------------------------------------------------------------------------------------
inline const efd::ParameterList& ParameterListMessage::GetParameters() const
{
    return m_params;
}

//------------------------------------------------------------------------------------------------
template<typename T>
efd::SInt32 ParameterListMessage::AddParameter(const T& parameter)
{
    return m_params.AddParameter(parameter);
}

//------------------------------------------------------------------------------------------------
template<typename T>
efd::SInt32 ParameterListMessage::AddParameter(const efd::utf8string& pszName, const T& parameter)
{
    return m_params.AddParameter(pszName, parameter);
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 ParameterListMessage::GetSize() const
{
    return m_params.GetSize();
}

//------------------------------------------------------------------------------------------------
template<typename T>
ParameterResult ParameterListMessage::GetParameter(efd::SInt32 i_index, T& o_result) const
{
    return m_params.GetParameter(i_index, o_result);
}

//------------------------------------------------------------------------------------------------
template<typename T>
ParameterResult ParameterListMessage::GetParameter(efd::UInt32 i_index, T& o_result) const
{
    return m_params.GetParameter(i_index, o_result);
}

//------------------------------------------------------------------------------------------------
template<typename T>
ParameterResult ParameterListMessage::GetParameter(const char* i_pszName, T& o_result) const
{
    return m_params.GetParameter(i_pszName, o_result);
}

//------------------------------------------------------------------------------------------------
void ParameterListMessage::Reset() const
{
    m_nextIndex = 0;
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
